//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifWIN32.cpp 88 2011-04-05 11:03:57Z nagasima $
#include "StdAfx.h"
#include "SifWIN32.h"
#include "WinKernel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKernel *g_Kernel;

//------------------------------------------------------------------------------
// CSifWIN32
//	概要：
//	引数：
//	pKernel
//	戻り値：
//------------------------------------------------------------------------------
CSifWIN32::CSifWIN32(TWIN32F10XReg *win32)
: CSystemIF((intptr_t)win32, sizeof(TWIN32F10XReg)),
USART1(&win32->USART1, INT_BASE_NO + INT_NO_OF_USART1, -1),
USART2(&win32->USART2, INT_BASE_NO + INT_NO_OF_USART2, -2),
USART3(&win32->USART3, INT_BASE_NO + INT_NO_OF_USART3, -3)
{
	m_WIN32 = win32;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CSifWIN32::~CSifWIN32()
{
}

bool CSifWIN32::HasReadEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->RCC.CR)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->RCC.CR)[1]))
	{
		return true;
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->RCC.CFGR)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->RCC.CFGR)[1]))
	{
		return true;
	}
	// 受信バッファを読み込まれたら
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART1)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART1)[1]))
	{
		return USART1.HasReadEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART1);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART2)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART2)[1]))
	{
		return USART2.HasReadEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART2);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART3)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART3)[1]))
	{
		return USART3.HasReadEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART3);
	}

	return false;
}

void CSifWIN32::GetByte2(intptr_t Index, unsigned char &Value)
{
	if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART1)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART1)[1]))
	{
		USART1.GetByte2(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART1, Value);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART2)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART2)[1]))
	{
		USART2.GetByte2(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART2, Value);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART3)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART3)[1]))
	{
		USART3.GetByte2(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART3, Value);
	}
	else{
		Value = ((unsigned char *)m_WIN32)[Index];
	}
}

bool CSifWIN32::SetByte2(intptr_t Index, unsigned char Value)
{
	// 送信バッファに書き込まれたら
	if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART1)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART1)[1]))
	{
		return USART1.SetByte2(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART1, Value);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART2)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART2)[1]))
	{
		return USART2.SetByte2(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART2, Value);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART3)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART3)[1]))
	{
		return USART3.SetByte2(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART3, Value);
	}
	else{
		((unsigned char *)m_WIN32)[Index] = Value;
	}

	return false;
}

void CSifWIN32::ReadEvent(intptr_t Index)
{
	if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->RCC.CR)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->RCC.CR)[1])){
		if(m_WIN32->RCC.CR.HSE_ON == 0){
			m_WIN32->RCC.CR.HSE_ON = 1;
		}
		else if(m_WIN32->RCC.CR.HSE_RDY == 0){
			m_WIN32->RCC.CR.HSE_RDY = 1;
		}
		else if(m_WIN32->RCC.CR.PLL_RDY == 0){
			m_WIN32->RCC.CR.PLL_RDY = 1;
		}
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->RCC.CFGR)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->RCC.CFGR)[1])){
		if(m_WIN32->RCC.CFGR.SWS != m_WIN32->RCC.CFGR.SW)
		{
			m_WIN32->RCC.CFGR.SWS = m_WIN32->RCC.CFGR.SW;
		}
	}
	// 受信バッファを読み込まれたら
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART1)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART1)[1]))
	{
		USART1.ReadEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART1);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART2)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART2)[1]))
	{
		USART2.ReadEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART2);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART3)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART3)[1]))
	{
		USART3.ReadEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART3);
	}
}

void CSifWIN32::WriteEvent(intptr_t Index)
{
	// 送信バッファに書き込まれたら
	if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART1)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART1)[1])){
		USART1.WriteEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART1);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART2)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART2)[1])){
		USART2.WriteEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART2);
	}
	else if((Index >= (intptr_t)&((TWIN32F10XReg *)0)->USART3)
		&& (Index < (intptr_t)&(&((TWIN32F10XReg *)0)->USART3)[1])){
		USART3.WriteEvent(Index - (intptr_t)&((TWIN32F10XReg *)0)->USART3);
	}
}

__int64 CSifWIN32::GetTimer()
{
	__int64 timer = USART1.GetTimer();
	__int64 timer2 = USART2.GetTimer();

	if((timer == -1) || ((timer2 != -1) && (timer > timer2)))
		timer = timer2;

	timer2 = USART3.GetTimer();

	if((timer == -1) || ((timer2 != -1) && (timer > timer2)))
		timer = timer2;

	return timer;
}

void CSifWIN32::Progress(__int64 Timer)
{
	USART1.Progress(Timer);
	USART2.Progress(Timer);
	USART3.Progress(Timer);
}

void CSifWIN32::CallTimeOut(__int64 Frequency)
{
	USART1.CallTimeOut(Frequency);
	USART2.CallTimeOut(Frequency);
	USART3.CallTimeOut(Frequency);
}

void CSifWIN32::OnTerminate()
{
	USART1.FlushBuffer();
	USART2.FlushBuffer();
	USART3.FlushBuffer();
}
