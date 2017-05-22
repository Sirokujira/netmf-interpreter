//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifSTM32USART.h 118 2013-02-12 13:05:51Z nagasima $
#ifndef SifSTM32USARTH
#define SifSTM32USARTH

//---------------------------------------------------------------------------
#include "SIFLayer.h"
#include "STM32USART.h"

enum TSTM32USARTTerm
{
	utIdle,
	utSending,
	utWait,
	utFlush,
};

//------------------------------------------------------------------------------
// CSifSTM32USART
//------------------------------------------------------------------------------
class CSifSTM32USART : public ISysTimerSync
{
public:
	CSifSTM32USART(TUSART *reg, int intNo, int devNo);
	virtual ~CSifSTM32USART();
private:
	TUSART *m_Reg;
	int m_IntNo;
	int m_DevNo;
	unsigned char m_SendBuf[256];
	int m_SendBufPos;
	unsigned char m_RecvBuf;
	TSTM32USARTTerm m_Term;
	LONG m_Send;
	__int64 m_Timer;
	__int64 CalcTimer(__int64 Frequency);
public:
	bool HasReadEvent(intptr_t Index);
	void GetByte2(intptr_t Index, unsigned char &Value);
	bool SetByte2(intptr_t Index, unsigned char Value);
	void ReadEvent(intptr_t Index);
	void WriteEvent(intptr_t Index);
	void RecvUSART(const void *Data, int Size);
public:
	__int64 GetTimer();
	void Progress(__int64 Timer);
	void CallTimeOut(__int64 Frequency);
	void FlushBuffer();
};

//---------------------------------------------------------------------------
#endif // SifSTM32USARTH
