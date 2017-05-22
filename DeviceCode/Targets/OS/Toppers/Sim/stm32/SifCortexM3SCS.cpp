//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifCortexM3SCS.cpp 128 2013-03-02 09:02:25Z nagasima $
#include "StdAfx.h"
#include "SifCortexM3SCS.h"
#include "STM32Reg.h"
#include "WinKernel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKernel *g_Kernel;

//------------------------------------------------------------------------------
// CSifCortexM3SCS
//	概要：
//	引数：
//	pKernel
//	戻り値：
//------------------------------------------------------------------------------
CSifCortexM3SCS::CSifCortexM3SCS(TCortexM3SCSReg *CortexM3SCS)
	: CSystemIF((intptr_t)CortexM3SCS, sizeof(TCortexM3SCSReg))
{
	m_CortexM3SCS = CortexM3SCS;
	m_Term = ttInterrupt;
	m_Timer = -1;
	m_ResetTime = 0;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CSifCortexM3SCS::~CSifCortexM3SCS()
{
}

bool CSifCortexM3SCS::HasReadEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TCortexM3SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCortexM3SCSReg *)0)->SysTick.CSR)[1]))
	{
		return true;
	}
	else if((Index >= (intptr_t)&((TCortexM3SCSReg *)0)->SysTick.CURRENT)
		&& (Index < (intptr_t)&(&((TCortexM3SCSReg *)0)->SysTick.CURRENT)[1]))
	{
		return true;
	}

	return false;
}

void CSifCortexM3SCS::GetByte2(intptr_t Index, unsigned char &Value)
{
	if((Index >= (intptr_t)&((TCortexM3SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCortexM3SCSReg *)0)->SysTick.CSR)[1]))
	{
		m_CortexM3SCS->SysTick.CSR.COUNTFLAG = 0;
	}

	Value = ((unsigned char *)m_CortexM3SCS)[Index];
}

bool CSifCortexM3SCS::SetByte2(intptr_t Index, unsigned char Value)
{
	((unsigned char *)m_CortexM3SCS)[Index] = Value;

	if((Index >= (intptr_t)&((TCortexM3SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCortexM3SCSReg *)0)->SysTick.CSR)[1]))
	{
		return true;
	}

	return false;
}

void CSifCortexM3SCS::ReadEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TCortexM3SCSReg *)0)->SysTick.CURRENT)
		&& (Index < (intptr_t)&(&((TCortexM3SCSReg *)0)->SysTick.CURRENT)[1]))
	{
		__int64 Now, Frequency, Interval;

		g_Kernel->GetSystemTime(&Now, &Frequency);

		Interval = ((m_CortexM3SCS->SysTick.RELOAD.RELOAD + 1) * Frequency) / g_Kernel->Frequency;
		Now -= m_ResetTime;
		Now %= Interval;
		Interval--;

		m_CortexM3SCS->SysTick.CURRENT.CURRENT =
			(m_CortexM3SCS->SysTick.RELOAD.RELOAD * (Interval - Now)) / Interval;
	}
}

void CSifCortexM3SCS::WriteEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TCortexM3SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCortexM3SCSReg *)0)->SysTick.CSR)[1]))
	{
		g_Kernel->OnSetEvent();
	}
}

bool CSifCortexM3SCS::InterruptEnabled(int IntNo)
{
	extern volatile uint32_t basepri;

	if(basepri > InterruptPriority(IntNo))
		return false;

	if(IntNo < INT_BASE_NO){
		unsigned int bit = 0x01 << (IntNo & 0x0F);
		return (m_CortexM3SCS->SCB.ICSR & bit) != 0;
	}
	else{
		IntNo -= INT_BASE_NO;
		unsigned int bit = 0x01 << (IntNo & 0x1F);
		return (m_CortexM3SCS->NVIC.ISPR[IntNo >> 5] & bit) != 0;
	}
}

void CSifCortexM3SCS::ClearInterrupt(int IntNo)
{
	if(IntNo < INT_BASE_NO){
		unsigned int bit = 0x01 << (IntNo & 0x0F);
		m_CortexM3SCS->SCB.ICSR &= ~bit;
	}
	else{
		IntNo -= INT_BASE_NO;
		unsigned int bit = 0x01 << (IntNo & 0x1F);
		m_CortexM3SCS->NVIC.ISPR[IntNo >> 5] &= ~bit;
	}
}

void CSifCortexM3SCS::SetInterrupt(int IntNo)
{
	if(IntNo < INT_BASE_NO){
		unsigned int bit = 0x01 << (IntNo & 0x0F);
		m_CortexM3SCS->SCB.ICSR |= bit;
	}
	else{
		IntNo -= INT_BASE_NO;
		unsigned int bit = 0x01 << (IntNo & 0x1F);
		m_CortexM3SCS->NVIC.ISPR[IntNo >> 5] |= bit;
	}
}

unsigned int CSifCortexM3SCS::InterruptPriority(int IntNo)
{
	if(IntNo < 4){
		//unsigned int bit = 0xFF << (8 * (IntNo & 0x3));
		//return m_CortexM3SCS->SCB.SHPR[IntNo >> 2] & bit;
		return 0;
	}
	else if(IntNo < INT_BASE_NO){
		IntNo -= 4;
		int shift = 8 * (IntNo & 0x3);
		unsigned int bit = 0xFF << shift;
		return (m_CortexM3SCS->SCB.SHPR[IntNo >> 2] & bit) >> (shift + 4);
	}
	else{
		IntNo -= INT_BASE_NO;
		int shift = 8 * (IntNo & 0x3);
		unsigned int bit = 0xFF << shift;
		return (m_CortexM3SCS->NVIC.IPR[IntNo >> 2] & bit) >> (shift + 4);
	}
}

__int64 CSifCortexM3SCS::GetTimer()
{
	if((m_Timer == -1) && (m_CortexM3SCS->SysTick.CSR.ENABLE != 0))
		m_Timer = 0;

	return m_Timer;
}

void CSifCortexM3SCS::Progress(__int64 Timer)
{
	if(m_Timer == -1)
		return;

	m_Timer -= Timer;
	if(m_Timer < 0){
		m_Timer = 0;
	}
}

void CSifCortexM3SCS::CallTimeOut(__int64 Frequency)
{
	__int64 Frequency2;

	if(m_Timer != 0)
		return;

	switch(m_Term){
	case ttInterrupt:
		g_Kernel->GetSystemTime(&m_ResetTime, &Frequency2);

		m_CortexM3SCS->SysTick.CSR.COUNTFLAG = 1;
		m_CortexM3SCS->SysTick.CURRENT.CURRENT = 0;

		g_Kernel->Interrupt(15/*IRQNO_SYSTICK*/);
		m_Timer = 0;
		m_Term = ttWait;
		break;
	case ttWait:
		// 割り込み処理が終了するまでスレッドスイッチ
		if((InterruptEnabled(15/*IRQNO_SYSTICK*/) || g_Kernel->InProcIntr(15/*IRQNO_SYSTICK*/)) && g_Kernel->KernelFlag()){
			m_Timer = 0;
			m_Term = ttWait;
			break;
		}
		if(m_CortexM3SCS->SysTick.CSR.ENABLE != 0)
			m_Timer = ((m_CortexM3SCS->SysTick.RELOAD.RELOAD + 1) * Frequency) / g_Kernel->Frequency;
		else
			m_Timer = -1;
		m_Term = ttInterrupt;
		break;
	}
}

void CSifCortexM3SCS::ChangeInterruptControlRegister(int,uint8_t)
{
}
