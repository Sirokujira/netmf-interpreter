//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifWIN32USART.cpp 128 2013-03-02 09:02:25Z nagasima $
#include "StdAfx.h"
#include "SifWIN32USART.h"
#include "WinKernel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKernel *g_Kernel;

//------------------------------------------------------------------------------
// CSifWIN32USART
//	概要：
//	引数：
//	pKernel
//	戻り値：
//------------------------------------------------------------------------------
CSifWIN32USART::CSifWIN32USART(TUSART *reg, int intNo, int devNo)
{
	m_Reg = reg;
	m_IntNo = intNo;
	m_DevNo = devNo;
	m_Term = utIdle;
	m_Timer = -1;
	m_Send = 0;
	//memset(m_SendBuf, 0, sizeof(m_SendBuf));
	m_SendBufPos = 0;
}

//------------------------------------------------------------------------------
//	概要：
//	引数：
//	戻り値：
//------------------------------------------------------------------------------
CSifWIN32USART::~CSifWIN32USART()
{
}

bool CSifWIN32USART::HasReadEvent(intptr_t Index)
{
	// 受信バッファを読み込まれたら
	if((Index >= (intptr_t)&((TUSART *)0)->DR)
		&& (Index < (intptr_t)&(&((TUSART *)0)->DR)[1]))
	{
		return true;
	}

	return false;
}

void CSifWIN32USART::GetByte2(intptr_t Index, unsigned char &Value)
{
	// 受信バッファを読み込まれたら
	if((Index >= (intptr_t)&((TUSART *)0)->DR)
		&& (Index < (intptr_t)&(&((TUSART *)0)->DR)[1]))
	{
		if(Index == (intptr_t)&((TUSART *)0)->DR)
			Value = m_RecvBuf;
	}
	else{
		Value = ((unsigned char *)m_Reg)[Index];
	}
}

bool CSifWIN32USART::SetByte2(intptr_t Index, unsigned char Value)
{
	((unsigned char *)m_Reg)[Index] = Value;

	// 送信バッファに書き込まれたら
	if((Index >= (intptr_t)&((TUSART *)0)->DR)
		&& (Index < (intptr_t)&(&((TUSART *)0)->DR)[1]))
	{
		return true;
	}

	return false;
}

void CSifWIN32USART::ReadEvent(intptr_t Index)
{
	// 受信バッファを読み込まれたら
	if((Index >= (intptr_t)&((TUSART *)0)->DR)
		&& (Index < (intptr_t)&(&((TUSART *)0)->DR)[1]))
	{
		m_Reg->SR.RXNE = 0;
	}
}

void CSifWIN32USART::WriteEvent(intptr_t Index)
{
	// 送信バッファに書き込まれたら
	if((Index >= (intptr_t)&((TUSART *)0)->DR)
		&& (Index < (intptr_t)&(&((TUSART *)0)->DR)[1])){
		m_Reg->SR.TXE = 0;
		InterlockedIncrement(&m_Send);
		g_Kernel->OnSetEvent();
	}
}

void CSifWIN32USART::RecvUSART(const void *Data, int Size)
{
	m_RecvBuf = ((unsigned char *)Data)[0];
	m_Reg->SR.RXNE = 1;
	g_Kernel->Interrupt(m_IntNo);
}

__int64 CSifWIN32USART::GetTimer()
{
	return m_Timer;
}

void CSifWIN32USART::Progress(__int64 Timer)
{
	if(m_Timer == -1)
		return;

	m_Timer -= Timer;
	if(m_Timer < 0){
		m_Timer = 0;
	}
}

void CSifWIN32USART::CallTimeOut(__int64 Frequency)
{
	if(((m_Term == utIdle) || (m_Term == utFlush)) && (m_Send != 0)){
		m_Timer = 0;
		m_Term = utIdle;
	}

	if(m_Timer != 0)
		return;

	switch(m_Term){
	case utIdle:
		m_SendBuf[m_SendBufPos++] = m_Reg->DR.DR;
		if(m_SendBufPos == (sizeof(m_SendBuf) / sizeof(m_SendBuf[0]))){
			g_Kernel->Output(m_DevNo, m_SendBuf, sizeof(m_SendBuf));
			//memset(m_SendBuf, 0, sizeof(m_SendBuf));
			m_SendBufPos = 0;
		}
		m_Term = utSending;
		m_Timer = CalcTimer(Frequency);
		break;
	case utSending:
		m_Reg->SR.TXE = 1;
		if(g_Kernel->KernelFlag())
			g_Kernel->Interrupt(m_IntNo);
		m_Timer = 0;
		m_Term = utWait;
		break;
	case utWait:
		// 割り込み処理が終了するまでスレッドスイッチ
		if((g_Kernel->InterruptEnabled(m_IntNo) || g_Kernel->InProcIntr(m_IntNo)) && g_Kernel->KernelFlag()){
			m_Timer = 0;
			m_Term = utWait;
			break;
		}
		// 送信データがなければ
		if(InterlockedDecrement(&m_Send) == 0){
			// 100[ms]待って送信（100[ms]の根拠はない）
			m_Timer = (Frequency * 100) / 1000;
			m_Term = utFlush;
		}
		else{
			m_Timer = -1;
			m_Term = utIdle;
		}
		break;
	case utFlush:
		g_Kernel->Output(m_DevNo, m_SendBuf, m_SendBufPos * sizeof(m_SendBuf[0]));
		//memset(m_SendBuf, 0, sizeof(m_SendBuf));
		m_SendBufPos = 0;

		m_Timer = -1;
		m_Term = utIdle;
		break;
	}
}

__int64 CSifWIN32USART::CalcTimer(__int64 Frequency)
{
	__int64 bits;

	// ビット数
	switch(m_Reg->CR1.PCE){
	case 0:
		// | SB | 8 bit data | STB |
		bits = 10;
		break;
	case 1:
		// | SB | 7-bit data | PB | STB |
		bits = 10;
		break;
	case 2:
		// | SB | 9-bit data | STB |
		bits = 11;
		break;
	default:
		// | SB | 8-bit data | PB | STB |
		bits = 11;
		break;
	}

	// ストップビット数加算
	switch(m_Reg->CR2.STOP){
	case 0:
	case 1:
		bits += 1;
		break;
	default:
		bits += 2;
		break;
	}

	return (Frequency * bits * (16 * m_Reg->BRR.DIV_Mantissa + m_Reg->BRR.DIV_Fraction)) / g_Kernel->Frequency;
}

void CSifWIN32USART::FlushBuffer()
{
	g_Kernel->Output(m_DevNo, m_SendBuf, m_SendBufPos * sizeof(m_SendBuf[0]));
	//memset(m_SendBuf, 0, sizeof(m_SendBuf));
	m_SendBufPos = 0;
}
