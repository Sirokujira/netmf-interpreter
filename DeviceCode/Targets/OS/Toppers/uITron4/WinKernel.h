//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: WinKernel.h 128 2013-03-02 09:02:25Z nagasima $
#ifndef KernelH
#define KernelH

//---------------------------------------------------------------------------
#include "SIFLayer.h"

class CCPUContext;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
typedef void CALLBACK TKernelEvent(void *Obj);
typedef void CALLBACK TOutputEvent(void *Obj, int Kind, const void *Data, int Size);
typedef void CALLBACK TGetSystemTimeEvent(void *Obj, __int64 *Now, __int64 *Frequency);

struct TCallbackEvent
{
	int Func;
	int Kind;
	int Size;
	union{
		void *Data;
		unsigned char Buffer[4];
	};
};

#define INTERRUPT_COUNT 64

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class CKernel
{
public:
	CKernel(ISifCPU *m_SifCPU);
	virtual ~CKernel();
private:
	HANDLE m_Thread;
	DWORD m_ThreadID;
	bool m_Terminate;
	HANDLE m_IntEvent;
	HANDLE m_SysSem;
	DWORD m_TlsIndex;
	LONG m_Locked;
	bool m_TaskMode;
	__int64 m_Frequency;
	CCPUContext *m_Current;
	void *m_ObjOfOnSetEvent;
	TKernelEvent *m_OnSetEvent;
	void *m_ObjOfOnStart;
	TKernelEvent *m_OnStart;
	void *m_ObjOfOnTerminate;
	TKernelEvent *m_OnTerminate;
	void *m_ObjOfOnIdle;
	TKernelEvent *m_OnIdle;
	void *m_ObjOfOnOutput;
	TOutputEvent *m_OnOutput;
	void *m_ObjOfOnGetSystemTime;
	TGetSystemTimeEvent *m_OnGetSystemTime;
	list<TSystemIFItem> m_SystemIFList;
	list<ISysTimerSync *> m_SysTimerSyncList;
	CString m_UnitName;
private:
	ISifCPU *m_SifCPU;
	unsigned char m_SendBuf[256];
	int m_SendBufPos;
	FP m_IntHandler[INTERRUPT_COUNT];
	bool m_InProcIntr[INTERRUPT_COUNT];
	static unsigned long __stdcall ThreadProc(void *Param);
	void Execute();
	void MainLoop();
	void Idle();
	void ClearAllTask();
	void TraceLogPut(char c);
	void TraceLogFlush();
	static void TraceLogPutC(char c);
protected:
	virtual void OnStart();
	virtual void OnTerminate();
	virtual ID OnIdle();
public:
	CCPUContext *GetCurrent(){ return m_Current; }
	struct PFrequency{
		operator __int64() const {
			return ((CKernel *)((intptr_t)this - (intptr_t)&((CKernel *)0)->Frequency))->m_Frequency; 
		}
	}Frequency;
	void SwitchKernelMode(CCPUContext *CPUContext);
	void Interrupt(int IntNo);
	bool InKernelMode(){ return m_ThreadID == GetCurrentThreadId(); }
	bool IsLocked(){ return m_Locked > 0; }
	DWORD GetThreadID(){ return m_ThreadID; }
	void Start(bool CreateSuspend);
	void Terminate();
	bool IsTerminated(){ return m_Terminate; }
	bool IsFinished(){
		return (m_ThreadID == NULL)
			|| (WaitForSingleObject(m_Thread, 0) == WAIT_OBJECT_0);
	}
	void ReleaseCPUContext(CCPUContext *CPUContext);
	void ExitCPUContext(CCPUContext *CPUContext);
	bool Dispatch();
	void LockCPU();
	void UnlockCPU();
	CCPUContext *StartDelaySuspend();
	void EndDelaySuspend(CCPUContext *CPUContext);
	bool InTaskContext();
	void AssignOnSetEvent(TKernelEvent *OnSetEvent, void *ObjOfOnSetEvent)
	{
		m_OnSetEvent = OnSetEvent;
		m_ObjOfOnSetEvent = ObjOfOnSetEvent;
	}
	void AssignOnStart(TKernelEvent *OnStart, void *ObjOfOnStart)
	{
		m_OnStart = OnStart;
		m_ObjOfOnStart = ObjOfOnStart;
	}
	void AssignOnTerminate(TKernelEvent *OnTerminate, void *ObjOfOnTerminate)
	{
		m_OnTerminate = OnTerminate;
		m_ObjOfOnTerminate = ObjOfOnTerminate;
	}
	void AssignOnIdle(TKernelEvent *OnIdle, void *ObjOfOnIdle)
	{
		m_OnIdle = OnIdle;
		m_ObjOfOnIdle = ObjOfOnIdle;
	}
	void AssignOnOutput(TOutputEvent *OnOutput, void *ObjOfOnOutput)
	{
		m_OnOutput = OnOutput;
		m_ObjOfOnOutput = ObjOfOnOutput;
	}
	void AssignOnGetSystemTime(TGetSystemTimeEvent *OnGetSystemTime, void *ObjOfOnGetSystemTime)
	{
		m_OnGetSystemTime = OnGetSystemTime;
		m_ObjOfOnGetSystemTime = ObjOfOnGetSystemTime;
	}
	virtual ER DefineInterruptHandler(uint_t dintno, FP pk_dint);
	virtual ER ChangeInterruptControlRegister(uint_t dintno, uint8_t icrcmd);
	// DriverÅÃSimulator
	bool DefineSysIF(uintptr_t Addr, int Size, void *Substitute, ISystemIF *SystemIF);
	void AddSysTimerSync(ISysTimerSync *SysTimerSync);
	unsigned char GetSubByte(uintptr_t Addr);
	void SetSubByte(uintptr_t Addr, unsigned char Value);
	unsigned short GetSubUInt16(uintptr_t Addr);
	void SetSubUInt16(uintptr_t Addr, unsigned short Value);
	unsigned int GetSubUInt32(uintptr_t Addr);
	void SetSubUInt32(uintptr_t Addr, unsigned int Value);
	// DriverÅÃSimulator
	unsigned char GetByte(uintptr_t Addr);
	void SetByte(uintptr_t Addr, unsigned char Value);
	unsigned short GetUInt16(uintptr_t Addr);
	void SetUInt16(uintptr_t Addr, unsigned short Value);
	unsigned int GetUInt32(uintptr_t Addr);
	void SetUInt32(uintptr_t Addr, unsigned int Value);
	void Output(int Kind, const void *Data, int Size);
	virtual void Input(int Kind, const void *Data, int Size) = 0;
	__int64 GetTimer();
	void Progress(__int64 Timer);
	void CallTimeOut(__int64 Frequency);
	//
	const TCHAR *GetUnitName(){ return m_UnitName.c_str(); }
	void SetUnitName(const TCHAR *value){ m_UnitName = value; }
	int GetFullPathName(TCHAR *FilePath, int Size, const TCHAR *Extension);
	int ReadFile(TCHAR *Ext, int Pos, void *Data, int Size);
	int WriteFile(TCHAR *Ext, int Pos, void *Data, int Size);
	int ReadAddr(uintptr_t Addr, void *buffer, int count);
	int WriteAddr(uintptr_t Addr, const void *buffer, int count);
	void SetBit(unsigned int bit, unsigned int addr);
	void ClearBit(unsigned int bit, unsigned int addr);
	unsigned int TestBit(unsigned int bit, unsigned int addr);
	// 
	static void SetTaskName(ID tskid, const TCHAR *szName);
	static void SetThreadName(DWORD dwThreadID, const TCHAR *szName);
	//
	void OutputLastErrorMessage();
private:
	HANDLE m_CallbackSem;
	list<TCallbackEvent> m_EventQueue;
public:
	static void Log(const TCHAR *Text);
	void OnSetEvent();
	bool ProcessEvent();
	bool InProcIntr(int IntNo){ return m_InProcIntr[IntNo]; }
	void GetSystemTime(__int64 *Now, __int64 *Frequency);
public:
	bool InterruptEnabled(int IntNo) { return m_SifCPU->InterruptEnabled(IntNo); }
	void ClearInterrupt(int IntNo) { m_SifCPU->ClearInterrupt(IntNo); }
	void SetInterrupt(int IntNo) { m_SifCPU->SetInterrupt(IntNo); }
	unsigned int InterruptPriority(int IntNo) { return m_SifCPU->InterruptPriority(IntNo); }
	bool KernelFlag();
};

//---------------------------------------------------------------------------
#endif // KernelH
