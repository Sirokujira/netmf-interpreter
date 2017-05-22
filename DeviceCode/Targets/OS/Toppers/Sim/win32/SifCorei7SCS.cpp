//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifCorei7SCS.cpp 128 2017-05-22 16:30:23Z oonuma $
#include "StdAfx.h"
#include "SifCorei7SCS.h"
#include "WIN32Reg.h"
#include "WinKernel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKernel *g_Kernel;

//------------------------------------------------------------------------------
// CSifCorei7SCS
//	概要：
//	引数：
//	pKernel
//	戻り値：
//------------------------------------------------------------------------------
CSifCorei7SCS::CSifCorei7SCS(TCorei7SCSReg *corei7SCS)
: CSystemIF((intptr_t)corei7SCS, sizeof(TCorei7SCSReg))
{
	m_Corei7SCS = corei7SCS;
	m_Term = ttInterrupt;
	m_Timer = -1;
	m_ResetTime = 0;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CSifCorei7SCS::~CSifCorei7SCS()
{
}

bool CSifCorei7SCS::HasReadEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TCorei7SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCorei7SCSReg *)0)->SysTick.CSR)[1]))
	{
		return true;
	}
	else if((Index >= (intptr_t)&((TCorei7SCSReg *)0)->SysTick.CURRENT)
		&& (Index < (intptr_t)&(&((TCorei7SCSReg *)0)->SysTick.CURRENT)[1]))
	{
		return true;
	}

	return false;
}

void CSifCorei7SCS::GetByte2(intptr_t Index, unsigned char &Value)
{
	if((Index >= (intptr_t)&((TCorei7SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCorei7SCSReg *)0)->SysTick.CSR)[1]))
	{
		m_Corei7SCS->SysTick.CSR.COUNTFLAG = 0;
	}

	Value = ((unsigned char *)m_Corei7SCS)[Index];
}

bool CSifCorei7SCS::SetByte2(intptr_t Index, unsigned char Value)
{
	((unsigned char *)m_Corei7SCS)[Index] = Value;

	if((Index >= (intptr_t)&((TCorei7SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCorei7SCSReg *)0)->SysTick.CSR)[1]))
	{
		return true;
	}

	return false;
}

void CSifCorei7SCS::ReadEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TCorei7SCSReg *)0)->SysTick.CURRENT)
		&& (Index < (intptr_t)&(&((TCorei7SCSReg *)0)->SysTick.CURRENT)[1]))
	{
		__int64 Now, Frequency, Interval;

		g_Kernel->GetSystemTime(&Now, &Frequency);

		Interval = ((m_Corei7SCS->SysTick.RELOAD.RELOAD + 1) * Frequency) / g_Kernel->Frequency;
		Now -= m_ResetTime;
		Now %= Interval;
		Interval--;

		m_Corei7SCS->SysTick.CURRENT.CURRENT =
			(m_Corei7SCS->SysTick.RELOAD.RELOAD * (Interval - Now)) / Interval;
	}
}

void CSifCorei7SCS::WriteEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TCorei7SCSReg *)0)->SysTick.CSR)
		&& (Index < (intptr_t)&(&((TCorei7SCSReg *)0)->SysTick.CSR)[1]))
	{
		g_Kernel->OnSetEvent();
	}
}

bool CSifCorei7SCS::InterruptEnabled(int IntNo)
{
	extern volatile uint32_t basepri;

	if(basepri > InterruptPriority(IntNo))
		return false;

	if(IntNo < INT_BASE_NO){
		unsigned int bit = 0x01 << (IntNo & 0x0F);
		return (m_Corei7SCS->SCB.ICSR & bit) != 0;
	}
	else{
		IntNo -= INT_BASE_NO;
		unsigned int bit = 0x01 << (IntNo & 0x1F);
		return (m_Corei7SCS->NVIC.ISPR[IntNo >> 5] & bit) != 0;
	}
}

void CSifCorei7SCS::ClearInterrupt(int IntNo)
{
	if(IntNo < INT_BASE_NO){
		unsigned int bit = 0x01 << (IntNo & 0x0F);
		m_Corei7SCS->SCB.ICSR &= ~bit;
	}
	else{
		IntNo -= INT_BASE_NO;
		unsigned int bit = 0x01 << (IntNo & 0x1F);
		m_Corei7SCS->NVIC.ISPR[IntNo >> 5] &= ~bit;
	}
}

void CSifCorei7SCS::SetInterrupt(int IntNo)
{
	if(IntNo < INT_BASE_NO){
		unsigned int bit = 0x01 << (IntNo & 0x0F);
		m_Corei7SCS->SCB.ICSR |= bit;
	}
	else{
		IntNo -= INT_BASE_NO;
		unsigned int bit = 0x01 << (IntNo & 0x1F);
		m_Corei7SCS->NVIC.ISPR[IntNo >> 5] |= bit;
	}
}

unsigned int CSifCorei7SCS::InterruptPriority(int IntNo)
{
	if(IntNo < 4){
		//unsigned int bit = 0xFF << (8 * (IntNo & 0x3));
		//return m_Corei7SCS->SCB.SHPR[IntNo >> 2] & bit;
		return 0;
	}
	else if(IntNo < INT_BASE_NO){
		IntNo -= 4;
		int shift = 8 * (IntNo & 0x3);
		unsigned int bit = 0xFF << shift;
		return (m_Corei7SCS->SCB.SHPR[IntNo >> 2] & bit) >> (shift + 4);
	}
	else{
		IntNo -= INT_BASE_NO;
		int shift = 8 * (IntNo & 0x3);
		unsigned int bit = 0xFF << shift;
		return (m_Corei7SCS->NVIC.IPR[IntNo >> 2] & bit) >> (shift + 4);
	}
}

__int64 CSifCorei7SCS::GetTimer()
{
	if((m_Timer == -1) && (m_Corei7SCS->SysTick.CSR.ENABLE != 0))
		m_Timer = 0;

	return m_Timer;
}

void CSifCorei7SCS::Progress(__int64 Timer)
{
	if(m_Timer == -1)
		return;

	m_Timer -= Timer;
	if(m_Timer < 0){
		m_Timer = 0;
	}
}

void CSifCorei7SCS::CallTimeOut(__int64 Frequency)
{
	__int64 Frequency2;

	if(m_Timer != 0)
		return;

	switch(m_Term){
	case ttInterrupt:
		g_Kernel->GetSystemTime(&m_ResetTime, &Frequency2);

		m_Corei7SCS->SysTick.CSR.COUNTFLAG = 1;
		m_Corei7SCS->SysTick.CURRENT.CURRENT = 0;

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
		if(m_Corei7SCS->SysTick.CSR.ENABLE != 0)
			m_Timer = ((m_Corei7SCS->SysTick.RELOAD.RELOAD + 1) * Frequency) / g_Kernel->Frequency;
		else
			m_Timer = -1;
		m_Term = ttInterrupt;
		break;
	}
}

void CSifCorei7SCS::ChangeInterruptControlRegister(int,uint8_t)
{
}
