//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: WinKernel.cpp 128 2013-03-02 09:02:25Z nagasima $
#include "StdAfx.h"
#include "WinKernel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CKernel *g_Kernel;
volatile bool faultmask;
volatile bool primask;
volatile uint32_t basepri;
volatile uint32_t control;
volatile uint32_t ipsr;

#define HSE_CLOCK		(8000000)
#define SYS_CLOCK		(HSE_CLOCK * 9)
#define PCLK1_CLOCK		((HSE_CLOCK * 9) >> 1)
#define PCLK2_CLOCK		(HSE_CLOCK * 9)
#define IIPM_LOCK 1

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class CCPUContext
{
public:
	CCPUContext(CKernel *pKernel);
	virtual ~CCPUContext();
private:
	HANDLE m_Thread;
	DWORD m_ThreadID;
	bool m_Terminate;
	CKernel *m_Kernel;
	TCB *m_Task;
	LONG m_SuspendCount;
	LONG m_DelaySuspend;
	bool m_Suspend;
	CString m_Name;
	static DWORD m_TlsIndex;
#if TASK_SWITCH_DEBUG
	static __int64 m_Frequency;
	struct TSuspendLog{
		double Time;
		DWORD ThreadID;
		enum TState{
			None,
			BeforePushContext,
			AfterPushContext,
			BeforePopContext,
			AfterPopContext,
			BeforeSuspend,
			AfterSuspend,
			BeforeStartDelaySuspend,
			AfterStartDelaySuspend,
			BeforeEndDelaySuspend,
			AfterEndDelaySuspend,
		}State;
		int Count;
		DWORD Ret;
	};
	static TSuspendLog m_SuspendLog[4092];
	static LONG m_SuspendLogIndex;
	static void Push(TSuspendLog &log){
		LONG Index = InterlockedIncrement(&m_SuspendLogIndex) % 4092;
		m_SuspendLog[Index] = log;
	}
#endif
	static unsigned long __stdcall ThreadProc(void *Param);
public:
	bool IsTerminated();
	bool IsFinished()
	{
		return (m_ThreadID == 0)
			|| (WaitForSingleObject(m_Thread, 0) == WAIT_OBJECT_0);
	}
	bool IsCurrent(){ return m_ThreadID == GetCurrentThreadId(); }
	void Activate(TCB *Task);
	bool Dispatch();
	bool PushContext();
	bool PopContext();
	bool Suspend();
	void Terminate(){ m_Terminate = true; ResumeThread(m_Thread); }
	void StartDelaySuspend();
	bool EndDelaySuspend();
	void Release();
	void SetThreadName(const TCHAR *szThreadName);
	static CCPUContext *GetCurrent();
};

inline bool CCPUContext::IsTerminated(){ return m_Terminate || m_Kernel->IsTerminated(); }

DWORD CCPUContext::m_TlsIndex = 0xFFFFFFFF;
#if TASK_SWITCH_DEBUG
__int64 CCPUContext::m_Frequency;
CCPUContext::TSuspendLog CCPUContext::m_SuspendLog[4092];
LONG CCPUContext::m_SuspendLogIndex;
#endif

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CCPUContext::CCPUContext(CKernel *pKernel)
{
	m_Kernel = pKernel;
	m_Thread = NULL;
	m_ThreadID = 0;
	m_Terminate = false;
	m_Task = NULL;
	m_DelaySuspend = 0;
	m_SuspendCount = 0;

	if(m_TlsIndex == 0xFFFFFFFF){
		m_TlsIndex = TlsAlloc();
	}

#if TASK_SWITCH_DEBUG
	m_SuspendLogIndex = 0;
	memset(m_SuspendLog, 0, sizeof(m_SuspendLog));
	QueryPerformanceFrequency((LARGE_INTEGER *)&m_Frequency);
#endif
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CCPUContext::~CCPUContext()
{
	if(m_Thread != NULL){
		CloseHandle(m_Thread);
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned long __stdcall CCPUContext::ThreadProc(void *Param)
{
	CCPUContext *This = (CCPUContext *)Param;

	TlsSetValue(m_TlsIndex, This);

	if(!This->m_Terminate){
		try{
			// This->m_Task->tskctxb.start();
			while(This->m_Kernel->GetCurrent() != This)
				SwitchToThread();
			This->m_Task->p_tinib->task(This->m_Task->p_tinib->exinf);
		}catch(...){
		}
	}

	This->m_ThreadID = 0;

	CKernel *Kernel = This->m_Kernel;

	if(Kernel->GetCurrent() != This)
		delete This;

	Kernel->ExitCPUContext(This);

	return 0;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CCPUContext::Activate(TCB *Task)
{
	if(m_ThreadID != 0)
		throw 1;

	m_Task = Task;
	m_SuspendCount = 0;

	m_Thread = CreateThread(NULL, 0, &ThreadProc, (void *)this, CREATE_SUSPENDED,
		&m_ThreadID);
	if(m_Thread == NULL){
		m_Kernel->OutputLastErrorMessage();
		throw 1;
	}
	SetThreadPriority(m_Thread, THREAD_PRIORITY_LOWEST);
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CCPUContext::Dispatch()
{
	assert(IsCurrent());

	if(IsTerminated()){
		return false;
	}

	m_Kernel->SwitchKernelMode(this);

	if(IsTerminated()){
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CCPUContext::PushContext()
{
	assert(m_Kernel->InKernelMode());

#if TASK_SWITCH_DEBUG
	__int64 Time;
	TSuspendLog Log;
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::BeforePushContext;
	Log.Count = m_SuspendCount;
	Log.Ret = -1;
	Push(Log);
#endif

	LONG Count = InterlockedExchangeAdd(&m_SuspendCount, -2);

	assert((Count & 0x2) != 0);

	DWORD ret = -1;
	if((m_SuspendCount == 0) && (Count == 3)){
		ret = SuspendThread(m_Thread);
		if(ret == -1)
			m_Kernel->OutputLastErrorMessage();
		if((ret == -1) || ((ret != 0) && (ret != 1)))
			throw 1;
	}

#if TASK_SWITCH_DEBUG
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::AfterPushContext;
	Log.Count = m_SuspendCount;
	Log.Ret = ret;
	Push(Log);
#endif

	return true;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CCPUContext::PopContext()
{
	assert(m_Kernel->InKernelMode());

#if TASK_SWITCH_DEBUG
	__int64 Time;
	TSuspendLog Log;
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::BeforePopContext;
	Log.Count = m_SuspendCount;
	Log.Ret = -1;
	Push(Log);
#endif

	LONG Count = InterlockedExchangeAdd(&m_SuspendCount, 2);

	// Test用
	// assert((Count & 0x2) == 0);

	DWORD ret = -1;
	if((m_SuspendCount & 0x6) != 0){
		ret = ResumeThread(m_Thread);
		if(ret == -1)
			m_Kernel->OutputLastErrorMessage();
		if((ret != 2) && (ret != 1) && (ret != 0))
			throw 1;
		if((Count & 0x4) != 0)
			m_Suspend = false;
	}

#if TASK_SWITCH_DEBUG
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::AfterPopContext;
	Log.Count = m_SuspendCount;
	Log.Ret = ret;
	Push(Log);
#endif

	return true;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CCPUContext::Suspend()
{
	assert(IsCurrent());

#if TASK_SWITCH_DEBUG
	__int64 Time;
	TSuspendLog Log;
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::BeforeSuspend;
	Log.Count = m_SuspendCount;
	Log.Ret = -1;
	Push(Log);
#endif

	m_Suspend = true;

	LONG Count = InterlockedExchangeAdd(&m_SuspendCount, 4);

	assert((Count & 0x4) == 0x0);

	DWORD ret;
	do{
		ret = SuspendThread(m_Thread);
		if(ret == -1)
			m_Kernel->OutputLastErrorMessage();
		if((ret == -1) || ((ret != 0) && (ret != 1)))
			throw 1;
	}while(m_Suspend && !IsTerminated());

	Count = InterlockedExchangeAdd(&m_SuspendCount, -4);

	assert((Count & 0x4) != 0x0);

#if TASK_SWITCH_DEBUG
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::AfterSuspend;
	Log.Count = m_SuspendCount;
	Log.Ret = ret;
	Push(Log);
#endif

	return true;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CCPUContext::StartDelaySuspend()
{
	assert(IsCurrent());

#if TASK_SWITCH_DEBUG
	__int64 Time;
	TSuspendLog Log;
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::BeforeStartDelaySuspend;
	Log.Count = m_SuspendCount;
	Log.Ret = -1;
	Push(Log);
#endif

	m_DelaySuspend++;

	if(m_DelaySuspend == 1){
		LONG Count = InterlockedExchangeAdd(&m_SuspendCount, 1);

		assert((Count & 0x1) == 0);
	}

#if TASK_SWITCH_DEBUG
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::AfterStartDelaySuspend;
	Log.Count = m_SuspendCount;
	Log.Ret = -1;
	Push(Log);
#endif
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CCPUContext::EndDelaySuspend()
{
	assert(IsCurrent());
	assert(m_DelaySuspend > 0);

#if TASK_SWITCH_DEBUG
	__int64 Time;
	TSuspendLog Log;
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::BeforeEndDelaySuspend;
	Log.Count = m_SuspendCount;
	Log.Ret = -1;
	Push(Log);
#endif

	m_DelaySuspend--;

	if(m_DelaySuspend == 0)
	{
		LONG Count = InterlockedExchangeAdd(&m_SuspendCount, -1);

		assert((Count & 0x1) != 0);

		if(m_SuspendCount == 0){
			DWORD ret = SuspendThread(m_Thread);
			if(ret == -1)
				m_Kernel->OutputLastErrorMessage();
			if((ret == -1) || ((ret != 0) && (ret != 1)))
				throw 1;
		}
	}

#if TASK_SWITCH_DEBUG
	QueryPerformanceCounter((LARGE_INTEGER *)&Time);
	Log.Time = (double)Time / (double)m_Frequency;
	Log.ThreadID = m_ThreadID;
	Log.State = TSuspendLog::AfterEndDelaySuspend;
	Log.Count = m_SuspendCount;
	Log.Ret = -1;
	Push(Log);
#endif

	return true;
}

void CCPUContext::Release()
{
	m_ThreadID = 0;
}

#define MS_VC_EXCEPTION 0x406D1388

typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;

void SetThreadName(DWORD dwThreadID, LPCSTR szThreadName)
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = szThreadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(DWORD), (DWORD*)&info );
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CCPUContext::SetThreadName(const TCHAR *szThreadName)
{
	m_Name = szThreadName;
	size_t Size = _tcslen(szThreadName);
	char *Temp = new char[Size + 1];
	try{
		wcstombs_s(&Size, Temp, Size + 1, m_Name.c_str(), Size);

		::SetThreadName(m_ThreadID, Temp);
	}catch(...){
	}
	delete Temp;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CCPUContext *CCPUContext::GetCurrent()
{
	return (CCPUContext *)TlsGetValue(m_TlsIndex);
}

extern "C" void *new_context(void *p_tcb)
{
	CCPUContext *CPUContext = new CCPUContext(g_Kernel);
	CPUContext->Activate((TCB *)p_tcb);
	return CPUContext;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CKernel::CKernel(ISifCPU *sifCPU)
{
	m_Frequency = SYS_CLOCK;
	m_SifCPU = sifCPU;
	m_Current = NULL;
	m_ObjOfOnSetEvent = NULL;
	m_OnSetEvent = NULL;
	m_ObjOfOnStart = NULL;
	m_OnStart = NULL;
	m_ObjOfOnTerminate = NULL;
	m_OnTerminate = NULL;
	m_ObjOfOnIdle = NULL;
	m_OnIdle = NULL;
	m_ObjOfOnOutput = NULL;
	m_OnOutput = NULL;
	m_ObjOfOnGetSystemTime = NULL;
	m_OnGetSystemTime = NULL;
	memset(m_IntHandler, 0, sizeof(m_IntHandler));
	memset(m_InProcIntr, 0, sizeof(m_InProcIntr));

	m_Thread = NULL;
	m_ThreadID = 0;
	m_Terminate = false;
	m_IntEvent = NULL;
	m_Locked = 0;
	m_TaskMode = false;
	m_TlsIndex = TlsAlloc();
	m_SysSem = ::CreateSemaphore(NULL, 1, 1, NULL);
	m_CallbackSem = ::CreateSemaphore(NULL, 1, 1, NULL);

	//memset(m_SendBuf, 0, sizeof(m_SendBuf));
	m_SendBufPos = 0;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CKernel::~CKernel()
{
	m_Terminate = true;

	if(m_IntEvent != NULL)
	{
		while(!IsFinished())
		{
			SetEvent(m_IntEvent);
			SwitchToThread();
		}
		CloseHandle(m_IntEvent);
		CloseHandle(m_Thread);
	}

	CloseHandle(m_SysSem);
	CloseHandle(m_CallbackSem);

	TlsFree(m_TlsIndex);

	m_SystemIFList.clear();

	TCallbackEvent callback;

	while(m_EventQueue.size() > 0)
	{
		callback = m_EventQueue.front();
		m_EventQueue.pop_front();

		if(callback.Data != NULL){
			delete callback.Data;
		}
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::Start(bool CreateSuspend)
{
	if(m_ThreadID != 0)
		throw 1;

	m_Thread = CreateThread(NULL, 0, &ThreadProc, (void *)this, CreateSuspend ? CREATE_SUSPENDED : 0, &m_ThreadID);
	if(m_Thread == NULL)
		throw 1;
	SetThreadPriority(m_Thread, THREAD_PRIORITY_HIGHEST);

	m_IntEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(m_IntEvent == NULL)
	{
		CloseHandle(m_Thread);
		throw 1;
	}

	SetThreadName(m_ThreadID, _T("Kernel"));
}

void CKernel::Terminate()
{
	if(m_Terminate && m_ThreadID == 0){
		OnTerminate();
	}
	else{
		m_Terminate = true;
		SetEvent(m_IntEvent);
	}
	if((m_Current != NULL) && m_Current->IsCurrent()){
		m_Current->Release();

		// UnlockCPUでは、deleteしたm_Currentに対してEndDelaySuspendを
		// 呼んでしまうので、その手前の処理のみ実行。
		int TlsLockCount = (int)TlsGetValue(m_TlsIndex);
		TlsLockCount--;

		// ロック解除
		if(TlsLockCount == 0){
			ReleaseSemaphore(m_SysSem, 1, NULL);
			InterlockedDecrement(&m_Locked);
		}

		TlsSetValue(m_TlsIndex, (LPVOID)TlsLockCount);

		ExitThread(0);
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned long __stdcall CKernel::ThreadProc(void *Param)
{
	CKernel *This = (CKernel *)Param;

	if(!This->m_Terminate){
		try{
			This->Execute();
		}catch(...){
		}
	}

	This->m_ThreadID = 0;

	return 0;
}

void CKernel::OnSetEvent()
{
	if(m_OnSetEvent != NULL)
		m_OnSetEvent(m_ObjOfOnSetEvent);
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::OnStart()
{
	//hardware_init_hook();

	//software_init_hook();

	TCallbackEvent callback;

	memset(&callback, 0, sizeof(callback));

	callback.Func = 0;

	if(WaitForSingleObject(m_CallbackSem, INFINITE) != WAIT_OBJECT_0)
		throw 1;

	__try{
		m_EventQueue.push_back(callback);
	}
	__finally{
		ReleaseSemaphore(m_CallbackSem, 1, NULL);
	}

	OnSetEvent();
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::OnTerminate()
{
	TCallbackEvent callback;

	memset(&callback, 0, sizeof(callback));

	callback.Func = 1;

	if(WaitForSingleObject(m_CallbackSem, INFINITE) != WAIT_OBJECT_0)
		throw 1;

	__try{
		m_EventQueue.push_back(callback);
	}
	__finally{
		ReleaseSemaphore(m_CallbackSem, 1, NULL);
	}

	OnSetEvent();
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::Execute()
{
	__try{
		LockCPU();
		__try{
			OnStart();

			sta_ker();

			MainLoop();
		}
		__finally{
			UnlockCPU();
		}

		exit_kernel();

		ClearAllTask();
	}
	__finally{
		OnTerminate();
	}
}

void CKernel::TraceLogPut(char c)
{
	m_SendBuf[m_SendBufPos++] = c;
	if(m_SendBufPos == (sizeof(m_SendBuf) / sizeof(m_SendBuf[0]))){
		Output(1, m_SendBuf, sizeof(m_SendBuf));
		//memset(m_SendBuf, 0, sizeof(m_SendBuf));
		m_SendBufPos = 0;
	}
}

void CKernel::TraceLogFlush()
{
	Output(1, m_SendBuf, m_SendBufPos * sizeof(m_SendBuf[0]));
	//memset(m_SendBuf, 0, sizeof(m_SendBuf));
	m_SendBufPos = 0;
}

/*
 * システムログの低レベル出力のための文字出力
 */
void CKernel::TraceLogPutC(char c)
{
	if (c == '\n') {
		g_Kernel->TraceLogPut('\r');
	}
	g_Kernel->TraceLogPut(c);
}

extern volatile uint32_t basepri;

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::MainLoop()
{
	TOPPERS_dummy_t prm;

	lock_flag = false;

	do{
		prm.TOPPERS_dummy_field = 0;

		uint32_t end = basepri;

		for(uint32_t prio = IIPM_LOCK; prio > end; prio--)
		{
			for(int IntNo = 0; IntNo < INTERRUPT_COUNT; IntNo++)
			{
				if(prio == InterruptPriority(IntNo)){
					if(InterruptEnabled(IntNo)){
						m_InProcIntr[IntNo] = true;

						ClearInterrupt(IntNo);

						if(m_IntHandler[IntNo] != NULL){
#ifdef LOG_INH_ENTER
							LOG_INH_ENTER(IntNo);
#endif /* LOG_INH_ENTER */
							try{
								m_IntHandler[IntNo](prm);
							}catch(...){
							}
#ifdef LOG_INH_ENTER
							LOG_INH_LEAVE(IntNo);
#endif /* LOG_INH_ENTER */
						}

						m_InProcIntr[IntNo] = false;
					}
				}
			}
		}

#ifdef LOG_DSP_ENTER
		LOG_DSP_ENTER(p_runtsk);
#endif /* LOG_DSP_ENTER */

		if(dspflg)
			p_runtsk = p_schedtsk;

		if(p_runtsk == NULL){
			if(IsTerminated())
				return;
			Idle();
		}
		else{
			m_Current = (CCPUContext *)p_runtsk->tskctxb.cpu_context;
			// m_Current = (CCPUContext *)p_runtsk->tskctxb.env;
			m_Current->PopContext();

#ifdef LOG_DSP_LEAVE
			LOG_DSP_LEAVE(p_runtsk);
#endif /* LOG_DSP_LEAVE */

			lock_flag = false;
			basepri = NULL; // saved_iipm;

			UnlockCPU();

			m_TaskMode = true;

			// if(WaitForSingleObject(m_IntEvent, INFINITE) != WAIT_OBJECT_0)
			// {
			// 	Terminate();
			// }

			m_TaskMode = false;

			LockCPU();

			// CCPUContext *CPUContext = (CCPUContext *)m_Current;
			// m_Current = NULL;
			// if(CPUContext->IsFinished()){
			// 	ExitCPUContext(CPUContext);
			// 	delete CPUContext;
			// }
			// else
			// 	CPUContext->PushContext();
		}

		trace_dump((intptr_t)CKernel::TraceLogPutC);

	}while(!IsTerminated());

	TraceLogFlush();
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::ClearAllTask()
{
	TCB *Task;
	CCPUContext *CPUContext;
	bool end;

	do{
		end = true;
		for (uint_t i = 0; i < tnum_tsk; i++) {
			Task = &tcb_table[i];
			if(Task->p_tinib != NULL){
				CPUContext = (CCPUContext *)Task->tskctxb.cpu_context;
				if(!CPUContext->IsFinished()){
					CPUContext->Terminate();
					end = false;
				}
			}
		}
		SwitchToThread();
	}while(!end);
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::Idle()
{
	ID tskid;

	tskid = OnIdle();

	if(tskid != TSK_NONE){
		TCB *Task;

		Task = get_tcb(tskid);
		if(Task != NULL){
			make_runnable(Task);
		}
	}
	else{
		lock_flag = false;
		basepri = NULL; // saved_iipm;

		UnlockCPU();

		if(WaitForSingleObject(m_IntEvent, INFINITE) != WAIT_OBJECT_0)
		{
			Terminate();
		}

		LockCPU();
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CKernel::Dispatch()
{
	CCPUContext *CPUContext = (CCPUContext *)p_runtsk->tskctxb.cpu_context;

	return CPUContext->Dispatch();
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
ID CKernel::OnIdle()
{
	ID tskid = TSK_NONE;

	TCallbackEvent callback;

	memset(&callback, 0, sizeof(callback));

	callback.Func = 2;

	if(WaitForSingleObject(m_CallbackSem, INFINITE) != WAIT_OBJECT_0)
		throw 1;

	__try{
		m_EventQueue.push_back(callback);
	}
	__finally{
		ReleaseSemaphore(m_CallbackSem, 1, NULL);
	}

	OnSetEvent();

	return tskid;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::ReleaseCPUContext(CCPUContext *CPUContext)
{
	if(CPUContext->IsCurrent()){
		CPUContext->Release();
		SetEvent(m_IntEvent);
		ExitThread(0);
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::ExitCPUContext(CCPUContext *CPUContext)
{
	for (uint_t i = 0; i < tnum_tsk; i++) {
		TCB *Task = &tcb_table[i];
		if (CPUContext == (CCPUContext *)Task->tskctxb.cpu_context)
		{
			tcb_table[i].p_tinib = NULL;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::LockCPU()
{
	int TlsLockCount = (int)TlsGetValue(m_TlsIndex);

	// 他のスレッドが動かないようロック
	if(TlsLockCount == 0){
		InterlockedIncrement(&m_Locked);
		for(;;){
			if(WaitForSingleObject(m_SysSem, INFINITE) != WAIT_OBJECT_0){
				Terminate();
				break;
			}
			// 実行を意図したスレッドかチェック
			CCPUContext *Context = CCPUContext::GetCurrent();
			if((Context == NULL) || (Context == m_Current) || (m_Current == NULL))
				break;
			// 実行したくないスレッドはもう一度待つ
			ReleaseSemaphore(m_SysSem, 1, NULL);
			SwitchToThread();
		}
	}

	TlsLockCount++;
	TlsSetValue(m_TlsIndex, (LPVOID)TlsLockCount);

	if(TlsLockCount == 1){
		CCPUContext *LockCPUContext = CCPUContext::GetCurrent();
		if(LockCPUContext != NULL)
			LockCPUContext->StartDelaySuspend();
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::UnlockCPU()
{
	int TlsLockCount = (int)TlsGetValue(m_TlsIndex);
	TlsLockCount--;

	assert(TlsLockCount >= 0);

	// ロック解除
	if(TlsLockCount == 0){
		ReleaseSemaphore(m_SysSem, 1, NULL);
		InterlockedDecrement(&m_Locked);
	}

	TlsSetValue(m_TlsIndex, (LPVOID)TlsLockCount);

	if(TlsLockCount == 0){
		CCPUContext *LockCPUContext = CCPUContext::GetCurrent();
		if(LockCPUContext != NULL)
			LockCPUContext->EndDelaySuspend();
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	CPUContext
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SwitchKernelMode(CCPUContext *CPUContext)
{
	int i = 0, TlsLockCount;

	TlsLockCount = (int)TlsGetValue(m_TlsIndex);

	assert(TlsLockCount > 0);

	while((m_Locked == 0) && !m_TaskMode)
		SwitchToThread();

	// ロック解除
	ReleaseSemaphore(m_SysSem, 1, NULL);
	InterlockedExchangeAdd(&m_Locked, -TlsLockCount);

	TlsSetValue(m_TlsIndex, (LPVOID)0);

	SetEvent(m_IntEvent);

	CPUContext->Suspend();

	// 他のスレッドが動かないようロック
	InterlockedExchangeAdd(&m_Locked, TlsLockCount);
	if(WaitForSingleObject(m_SysSem, INFINITE) != WAIT_OBJECT_0){
		Terminate();
	}

	TlsSetValue(m_TlsIndex, (LPVOID)TlsLockCount);
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	IntNo
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::Interrupt(int IntNo)
{
	if((IntNo >= 0) && (IntNo < INTERRUPT_COUNT)){
		SetInterrupt(IntNo);
		SetEvent(m_IntEvent);
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
ER CKernel::DefineInterruptHandler(uint_t dintno, FP pk_dint)
{
	if(/*(dintno < 0) || */(dintno >= INTERRUPT_COUNT))
		return E_PAR;

	// 登録破棄の場合
	if((intptr_t)pk_dint == -1){
		m_IntHandler[dintno] = NULL;
	}
	// 登録の場合
	else{
		m_IntHandler[dintno] = pk_dint;
	}

	return E_OK;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
ER CKernel::ChangeInterruptControlRegister(uint_t dintno, uint8_t icrcmd)
{
	if(/*(dintno < 0) || */(dintno >= sizeof(m_IntHandler) / sizeof(m_IntHandler[0])))
		return E_PAR;

	m_SifCPU->ChangeInterruptControlRegister(dintno, icrcmd);

	return E_OK;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CCPUContext *CKernel::StartDelaySuspend()
{
	CCPUContext *CPUContext = CCPUContext::GetCurrent();

	if(CPUContext != NULL){
		CPUContext->StartDelaySuspend();
	}

	return CPUContext;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::EndDelaySuspend(CCPUContext *CPUContext)
{
	if(CPUContext == NULL)
		return;

	if(!CPUContext->EndDelaySuspend())
	{
		CPUContext->Terminate();
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CKernel::InTaskContext()
{
	return CCPUContext::GetCurrent() != NULL;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CKernel::DefineSysIF(uintptr_t Addr, int Size, void *Substitute,
	::ISystemIF *SystemIF)
{
	TSystemIFItem Item;

	Item.Addr = Addr;
	Item.Size = Size;
	Item.Substitute = Substitute;
	Item.SystemIF = SystemIF;

	m_SystemIFList.push_back(Item);

	return E_OK;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::AddSysTimerSync(ISysTimerSync *SysTimerSync)
{
	m_SysTimerSyncList.push_back(SysTimerSync);
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned char CKernel::GetSubByte(uintptr_t SubAddr)
{
	unsigned char Result;
	list<TSystemIFItem>::iterator Item;
	uintptr_t Addr;
	bool OK = false;

	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
		{
			Addr = SubAddr - (uintptr_t)Item->Substitute + Item->Addr;

			if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
				Result = Item->SystemIF->GetByte(SubAddr);
				OK = true;
				break;
			}
		}
	}
	catch(...){
	}
	EndDelaySuspend(CPUContext);

	if(!OK){
		Result = *((unsigned char *)SubAddr);
	}

	return Result;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetSubByte(uintptr_t SubAddr, unsigned char Value)
{
	list<TSystemIFItem>::iterator Item;
	uintptr_t Addr;
	bool OK = false;

	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
		{
			Addr = SubAddr - (uintptr_t)Item->Substitute + Item->Addr;

			if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
				Item->SystemIF->SetByte(SubAddr, Value);
				OK = true;
				break;
			}
		}
	}
	catch(...){
	}
	EndDelaySuspend(CPUContext);

	if(!OK){
		*((unsigned char *)SubAddr) = Value;
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned short CKernel::GetSubUInt16(uintptr_t SubAddr)
{
	unsigned short Result;
	list<TSystemIFItem>::iterator Item;
	uintptr_t Addr;
	bool OK = false;

	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
		{
			Addr = SubAddr - (uintptr_t)Item->Substitute + Item->Addr;

			if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
				Result = Item->SystemIF->GetUInt16(SubAddr);
				OK = true;
				break;
			}
		}
	}
	catch(...){
	}
	EndDelaySuspend(CPUContext);

	if(!OK){
		Result = *((unsigned short *)SubAddr);
	}

	return Result;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetSubUInt16(uintptr_t SubAddr, unsigned short Value)
{
	list<TSystemIFItem>::iterator Item;
	uintptr_t Addr;
	bool OK = false;

	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
		{
			Addr = SubAddr - (uintptr_t)Item->Substitute + Item->Addr;

			if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
				Item->SystemIF->SetUInt16(SubAddr, Value);
				OK = true;
				break;
			}
		}
	}
	catch(...){
	}
	EndDelaySuspend(CPUContext);

	if(!OK){
		*((unsigned short *)SubAddr) = Value;
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned int CKernel::GetSubUInt32(uintptr_t SubAddr)
{
	unsigned int Result;
	list<TSystemIFItem>::iterator Item;
	uintptr_t Addr;
	bool OK = false;

	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
		{
			Addr = SubAddr - (uintptr_t)Item->Substitute + Item->Addr;

			if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
				Result = Item->SystemIF->GetUInt32(SubAddr);
				OK = true;
				break;
			}
		}
	}
	catch(...){
	}
	EndDelaySuspend(CPUContext);

	if(!OK){
		Result = *((unsigned int *)SubAddr);
	}

	return Result;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetSubUInt32(uintptr_t SubAddr, unsigned int Value)
{
	list<TSystemIFItem>::iterator Item;
	uintptr_t Addr;
	bool OK = false;

	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
		{
			Addr = SubAddr - (uintptr_t)Item->Substitute + Item->Addr;

			if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
				Item->SystemIF->SetUInt32(SubAddr, Value);
				OK = true;
				break;
			}
		}
	}
	catch(...){
	}
	EndDelaySuspend(CPUContext);

	if(!OK){
		*((unsigned int *)SubAddr) = Value;
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned char CKernel::GetByte(uintptr_t Addr)
{
	list<TSystemIFItem>::iterator Item;

	for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
	{
		if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
			return Item->SystemIF->GetByte((uintptr_t)Item->Substitute + Addr - Item->Addr);
		}
	}

	return 0xFF;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetByte(uintptr_t Addr, unsigned char Value)
{
	list<TSystemIFItem>::iterator Item;

	for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
	{
		if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
			Item->SystemIF->SetByte((uintptr_t)Item->Substitute + Addr - Item->Addr, Value);
			return;
		}
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned short CKernel::GetUInt16(uintptr_t Addr)
{
	list<TSystemIFItem>::iterator Item;

	for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
	{
		if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
			return Item->SystemIF->GetUInt16((uintptr_t)Item->Substitute + Addr - Item->Addr);
		}
	}

	return 0xFFFF;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetUInt16(uintptr_t Addr, unsigned short Value)
{
	list<TSystemIFItem>::iterator Item;

	for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
	{
		if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
			Item->SystemIF->SetUInt16((uintptr_t)Item->Substitute + Addr - Item->Addr, Value);
			return;
		}
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
unsigned int CKernel::GetUInt32(uintptr_t Addr)
{
	list<TSystemIFItem>::iterator Item;

	for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
	{
		if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
			return Item->SystemIF->GetUInt32((uintptr_t)Item->Substitute + Addr - Item->Addr);
		}
	}

	return 0xFFFFFFFF;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetUInt32(uintptr_t Addr, unsigned int Value)
{
	list<TSystemIFItem>::iterator Item;

	for(Item = m_SystemIFList.begin(); Item != m_SystemIFList.end(); Item++)
	{
		if((Addr >= Item->Addr) && (Addr < Item->Addr + Item->Size)){
			Item->SystemIF->SetUInt32((uintptr_t)Item->Substitute + Addr - Item->Addr, Value);
			return;
		}
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::Output(int Kind, const void *Data, int Size)
{
	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		TCallbackEvent callback;

		memset(&callback, 0, sizeof(callback));

		if(Size > sizeof(callback.Buffer)){
			callback.Func = 3;
			callback.Kind = Kind;
			callback.Data = new char[Size];
			memcpy(callback.Data, Data, Size);
			callback.Size = Size;
		}
		else{
			callback.Func = 4;
			callback.Kind = Kind;
			memcpy(callback.Buffer, Data, Size);
			callback.Size = Size;
		}

		if(WaitForSingleObject(m_CallbackSem, INFINITE) != WAIT_OBJECT_0)
			throw 1;

		//__try{
			m_EventQueue.push_back(callback);
		//}
		//__finally{
			ReleaseSemaphore(m_CallbackSem, 1, NULL);
		//}
	
		OnSetEvent();
	}catch(...){
	}

	if(CPUContext != NULL)
		EndDelaySuspend(CPUContext);
}

__int64 CKernel::GetTimer()
{
	__int64 result = -1;
	list<ISysTimerSync *>::iterator Item;

	for(Item = m_SysTimerSyncList.begin(); Item != m_SysTimerSyncList.end(); Item++)
	{
		__int64 temp = (*Item)->GetTimer();
		if((result == -1) || ((temp != -1) && (result > temp)))
			result = temp;
	}
	return result;
}

void CKernel::Progress(__int64 Timer)
{
	list<ISysTimerSync *>::iterator Item;

	for(Item = m_SysTimerSyncList.begin(); Item != m_SysTimerSyncList.end(); Item++)
	{
		(*Item)->Progress(Timer);
	}
}

void CKernel::CallTimeOut(__int64 Frequency)
{
	list<ISysTimerSync *>::iterator Item;

	for(Item = m_SysTimerSyncList.begin(); Item != m_SysTimerSyncList.end(); Item++)
	{
		(*Item)->CallTimeOut(Frequency);
	}
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::Log(const TCHAR *Text)
{
	g_Kernel->Output(0, Text, (_tcslen(Text) + 1) * sizeof(TCHAR));
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
int CKernel::GetFullPathName(TCHAR *FilePath, int Size, const TCHAR *Extension)
{
	TCHAR Buffer[2024];
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	int i, j;
	CString str = m_UnitName;

	i = GetModuleFileName(NULL, Buffer, sizeof(Buffer) / sizeof(TCHAR));
	if(i <= 0){
		return 0;
	}

	_tsplitpath_s(Buffer, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

	if(str.empty()){
		str = fname;
		if((j = str.find(_T(".vshost"))) > 0){
			str = str.substr(0, j);
		}
		m_UnitName = str;
	}

	i = i - _tcslen(ext) + _tcslen(Extension);
	if(FilePath != NULL){
		if(i > Size){
			return 0;
		}
		_tmakepath_s(FilePath, Size / sizeof(TCHAR), drive, dir, str.c_str(), Extension);
	}

	return i;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
int CKernel::ReadFile(TCHAR *Ext, int Pos, void *Data, int Size)
{
	int result = 0;
	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		int i;
		TCHAR FileName[2024];
		fstream File;

		i = GetFullPathName(FileName, sizeof(FileName), Ext);
		if(i > 0){
			//__try{
				File.open(FileName, fstream::binary | fstream::in);
				File.seekg(Pos, fstream::beg);
				result = File.read((char *)Data, Size).gcount();
			//}
			//__finally{
				File.close();
			//}
		}
	}catch(...){
	}
	EndDelaySuspend(CPUContext);

	return result;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
int CKernel::WriteFile(TCHAR *Ext, int Pos, void *Data, int Size)
{
	int result = 0;
	CCPUContext *CPUContext = StartDelaySuspend();
	try{
		int i;
		TCHAR FileName[2024];
		fstream File;

		i = GetFullPathName(FileName, sizeof(FileName), Ext);
		if(i > 0){
			//__try{
				File.open(FileName, fstream::binary | fstream::in | fstream::out);
				if(File.fail())
					File.open(FileName, fstream::binary | fstream::in | fstream::out | fstream::trunc);
				File.seekp(Pos, fstream::beg);
				File.write((char *)Data, Size);
				result = (int)File.tellp() - Pos;
			//}
			//__finally{
				File.close();
			//}
		}
	}catch(...){
	}
	EndDelaySuspend(CPUContext);

	return result;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
int CKernel::ReadAddr(uintptr_t Addr, void *buffer, int count)
{
	int *di;
	short *ds;
	char *dc;
	int i, n = count;

	// ２バイト境界へアライメント調整
	dc = (char *)buffer;
	if(Addr & 0x01){
		*dc++ = GetByte(Addr);
		Addr++;
		n--;
	}

	if(n > 1){
		// ４バイト境界へアライメント調整
		ds = (short *)dc;
		if(Addr & 0x02){
			*ds++ = GetUInt16(Addr);
			Addr += 2;
			n -= 2;
		}

		di = (int *)ds;
		i = n >> 2;
		n -= i << 2;

		// ４バイト単位でデータバイト数分繰り返し
		while (--i >= 0){
			// ４バイトコピー
			*di++ = GetUInt32(Addr);
			Addr += 4;
		}

		ds = (short *)di;
		i = n >> 1;
		n -= i << 1;

		// ２バイト単位でデータバイト数分繰り返し
		while (--i >= 0){
			// ２バイトコピー
			*ds++ = GetUInt16(Addr);
			Addr += 2;
		}

		dc = (char *)ds;
	}

	// 残りのデータバイト数分繰り返し
	while (--n >= 0){
		// １バイトコピー
		*dc++ = GetByte(Addr);
		Addr++;
	}

	return count;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
int CKernel::WriteAddr(uintptr_t Addr, const void *buffer, int count)
{
	int *di;
	short *ds;
	char *dc;
	int i, n = count;

	// ２バイト境界へアライメント調整
	dc = (char *)buffer;
	if(Addr & 0x01){
		SetByte(Addr, *dc++);
		Addr++;
		n--;
	}

	if(n > 1){
		// ４バイト境界へアライメント調整
		ds = (short *)dc;
		if(Addr & 0x02){
			SetUInt16(Addr, *ds++);
			Addr += 2;
			n -= 2;
		}

		di = (int *)ds;
		i = n >> 2;
		n -= i << 2;

		// ４バイト単位でデータバイト数分繰り返し
		while (--i >= 0){
			// ４バイトコピー
			SetUInt32(Addr, *di++);
			Addr += 4;
		}

		ds = (short *)di;
		i = n >> 1;
		n -= i << 1;

		// ２バイト単位でデータバイト数分繰り返し
		while (--i >= 0){
			// ２バイトコピー
			SetUInt16(Addr, *ds++);
			Addr += 2;
		}

		dc = (char *)ds;
	}

	// 残りのデータバイト数分繰り返し
	while (--n >= 0){
		// １バイトコピー
		SetByte(Addr, *dc++);
		Addr++;
	}

	return count;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
bool CKernel::ProcessEvent()
{
	TCallbackEvent callback;

	while(m_EventQueue.size() > 0)
	{
		if(WaitForSingleObject(m_CallbackSem, INFINITE) != WAIT_OBJECT_0)
			return false;

		__try{
			callback = m_EventQueue.front();
			m_EventQueue.pop_front();
		}
		__finally{
			ReleaseSemaphore(m_CallbackSem, 1, NULL);
		}

		switch(callback.Func){
		case 0:
			if(m_OnStart != NULL){
				m_OnStart(m_ObjOfOnStart);
			}
			break;
		case 1:
			if(m_OnTerminate != NULL){
				m_OnTerminate(m_ObjOfOnTerminate);
			}
			return false;
		case 2:
			if(m_OnIdle != NULL){
				m_OnIdle(m_ObjOfOnIdle);
			}
			break;
		case 3:
			if(m_OnOutput != NULL){
				m_OnOutput(m_ObjOfOnOutput, callback.Kind, callback.Data, callback.Size);
			}
			delete callback.Data;
			break;
		case 4:
			if(m_OnOutput != NULL){
				m_OnOutput(m_ObjOfOnOutput, callback.Kind, callback.Buffer, callback.Size);
			}
			break;
		}
	}

	return !IsTerminated();
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetTaskName(ID tskid, const TCHAR *szName)
{
	CCPUContext *CPUContext = g_Kernel->StartDelaySuspend();
	try{
		CString Name = g_Kernel->m_UnitName + _T("::") + szName;

		TCB *Task = get_tcb(tskid);

		CCPUContext *tc;
		for(;;){
			tc = (CCPUContext *)Task->tskctxb.cpu_context;
			if(tc != NULL){
				tc->SetThreadName(Name.c_str());
				break;
			}
			//if(Task->tstat == TS_DORMANT)
			//	break;
			SwitchToThread();
		}
	}catch(...){
	}
	g_Kernel->EndDelaySuspend(CPUContext);
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::SetThreadName(DWORD dwThreadID, const TCHAR *szName)
{
	char *Temp = NULL;

	CCPUContext *CPUContext = g_Kernel->StartDelaySuspend();
	try{
		CString Name = g_Kernel->m_UnitName + _T("::") + szName;
		size_t Size = Name.length() + 1;
		Temp = new char[Size];
		try{
			wcstombs_s(&Size, Temp, Size, Name.c_str(), Size - 1);

			::SetThreadName(dwThreadID, Temp);
		}catch(...){
		}
		delete Temp;
	}catch(...){
	}
	g_Kernel->EndDelaySuspend(CPUContext);
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::GetSystemTime(__int64 *Now, __int64 *Frequency)
{
	if(m_OnGetSystemTime != NULL)
		m_OnGetSystemTime(m_ObjOfOnGetSystemTime, Now, Frequency);
}

//------------------------------------------------------------------------------
//  概要：
//  ・1Bitアクセスで１を書き込み
//  引数：
//  ・bit：ビット
//  ・addr：アドレス
//  戻り値：
//------------------------------------------------------------------------------
void CKernel::SetBit(unsigned int bit, unsigned int addr)
{
	SetByte(addr, GetByte(addr) | (1 << (bit & 7)));
}

//------------------------------------------------------------------------------
//  概要：
//  ・1Bitアクセスで０を書き込み
//  引数：
//  ・bit：ビット
//  ・addr：アドレス
//  戻り値：
//------------------------------------------------------------------------------
void CKernel::ClearBit(unsigned int bit, unsigned int addr)
{
	SetByte(addr, GetByte(addr) & (~(1 << (bit & 7))));
}

//------------------------------------------------------------------------------
//  概要：
//  ・1Bitアクセスで読み込み
//  引数：
//  ・bit：ビット
//  ・addr：アドレス
//  戻り値：
//------------------------------------------------------------------------------
unsigned int CKernel::TestBit(unsigned int bit, unsigned int addr)
{
	return (GetByte(addr) & (1 << (bit & 7))) != 0;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
void CKernel::OutputLastErrorMessage()
{
	LPVOID lpMsgBuf;

	BOOL ret = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER
		| FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, ::GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	Output(-1, lpMsgBuf, (_tcslen((LPTSTR)lpMsgBuf) + 1) * sizeof(TCHAR));
	
	LocalFree(lpMsgBuf);
}

bool CKernel::KernelFlag()
{
	return kerflg;
}

extern "C" void software_term_hook()
{
}

extern "C" void TOPPERS_assert_abort(void)
{
	if(g_Kernel->IsTerminated())
		return;

	throw 1;
}
