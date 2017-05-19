//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: Sample1.cpp 128 2013-03-02 09:02:25Z nagasima $
#include "stdafx.h"
#include "Sample1.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKernel *g_Kernel;

void Start()
{
	g_Kernel->Start(false);
}

void Exit()
{
	Input(0, "Q", 1);
	//g_Kernel->Terminate();
}

void Interrupt(int IntNo)
{
	g_Kernel->Interrupt(IntNo);
}

void GetUnitName(TCHAR *value, int size)
{
	_tcscpy_s(value, size, g_Kernel->GetUnitName());
}

void SetUnitName(const TCHAR *value)
{
	g_Kernel->SetUnitName(value);
}

void AssignOnSetEvent(TKernelEvent *OnSetEvent, void *ObjOfOnSetEvent)
{
	g_Kernel->AssignOnSetEvent(OnSetEvent, ObjOfOnSetEvent);
}

void AssignOnStart(TKernelEvent *OnStart, void *ObjOfOnStart)
{
	g_Kernel->AssignOnStart(OnStart, ObjOfOnStart);
}

void AssignOnTerminate(TKernelEvent *OnTerminate, void *ObjOfOnTerminate)
{
	g_Kernel->AssignOnTerminate(OnTerminate, ObjOfOnTerminate);
}

void AssignOnIdle(TKernelEvent *OnIdle, void *ObjOfOnIdle)
{
	g_Kernel->AssignOnIdle(OnIdle, ObjOfOnIdle);
}

void AssignOnOutput(TOutputEvent *OnOutput, void *ObjOfOnOutput)
{
	g_Kernel->AssignOnOutput(OnOutput, ObjOfOnOutput);
}

void AssignOnGetSystemTime(TGetSystemTimeEvent *OnGetSystemTime, void *ObjOfOnGetSystemTime)
{
	g_Kernel->AssignOnGetSystemTime(OnGetSystemTime, ObjOfOnGetSystemTime);
}

int ReadAddr(uintptr_t Addr, void *buffer, int count)
{
	return g_Kernel->ReadAddr(Addr, buffer, count);
}

int WriteAddr(uintptr_t Addr, const void *buffer, int count)
{
	return g_Kernel->WriteAddr(Addr, buffer, count);
}

bool GetBit(uintptr_t Addr, int bit)
{
	unsigned char temp = g_Kernel->GetByte(Addr);
	return (temp & (0x01 << bit)) != 0;
}

void SetBit(uintptr_t Addr, int bit, bool value)
{
	unsigned char temp = g_Kernel->GetByte(Addr);
	if (value)
		temp |= 0x01 << bit;
	else
		temp &= ~(0x01 << bit);
	g_Kernel->SetByte(Addr, temp);
}

bool ProcessEvent()
{
	return g_Kernel->ProcessEvent();
}

void Input(int Kind, const void *Data, int Size)
{
	g_Kernel->Input(Kind, Data, Size);
}

__int64 GetTimer()
{
	return g_Kernel->GetTimer();
}

void Progress(__int64 Timer)
{
	g_Kernel->Progress(Timer);
}

void CallTimeOut(__int64 Frequency)
{
	g_Kernel->CallTimeOut(Frequency);
}

TSTM32F10XReg STM32Reg;
TCortexM3SCSReg CortexM3SCSReg;

CSample1::CSample1()
	: CKernel(m_SifSysCtrlSpc = new CSifCortexM3SCS(&CortexM3SCSReg))
{
	SetUnitName(_T("Sample1"));

	// ���W�X�^�A�h���X�o�^
	m_SifCPU = new CSifSTM32(&STM32Reg);
	DefineSysIF(0x40000000, sizeof(STM32Reg), &STM32Reg, m_SifCPU);
	AddSysTimerSync(m_SifCPU);

	// ���W�X�^�A�h���X�o�^
	DefineSysIF(0xE000E000, sizeof(CortexM3SCSReg), &CortexM3SCSReg, m_SifSysCtrlSpc);
	AddSysTimerSync(m_SifSysCtrlSpc);
}

CSample1::~CSample1()
{
	if(m_SifCPU != NULL){
		delete m_SifCPU;
	}

	if(m_SifSysCtrlSpc != NULL){
		delete m_SifSysCtrlSpc;
	}
}

void CSample1::OnStart()
{
	CKernel::OnStart();
}

void CSample1::OnTerminate()
{
	__try{
		m_SifCPU->OnTerminate();
	}
	__finally{
		CKernel::OnTerminate();
	}
}

ID CSample1::OnIdle()
{
	return CKernel::OnIdle();
}

//------------------------------------------------------------------------------
//	�T�v�F
//	�����F
//	�߂�l�F
//------------------------------------------------------------------------------
void CSample1::Input(int Kind, const void *Data, int Size)
{
	switch(Kind)
	{
	case 0:
		m_SifCPU->USART1.RecvUSART(Data, Size);
		break;
	case 1:
		m_SifCPU->USART2.RecvUSART(Data, Size);
		break;
	case 2:
		m_SifCPU->USART3.RecvUSART(Data, Size);
		break;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if(g_Kernel == NULL){
			// DLL�A�����[�h���Ƀ��������[�N���`�F�b�N����悤�ݒ�
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			g_Kernel = new CSample1();
		}
		break;
	case DLL_PROCESS_DETACH:
		if(g_Kernel != NULL){
			delete g_Kernel;
			g_Kernel = NULL;
			// ���̎��_�Ń��������[�N���Ă��邩�`�F�b�N
			//_CrtDumpMemoryLeaks( );
		}
		break;
	}

	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif
