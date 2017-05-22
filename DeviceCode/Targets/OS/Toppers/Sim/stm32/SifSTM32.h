//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifSTM32.h 118 2013-02-12 13:05:51Z nagasima $
#ifndef SifSTM32H
#define SifSTM32H

//---------------------------------------------------------------------------
#include "SIFLayer.h"
#include "STM32Reg.h"
#include "SifSTM32USART.h"

//------------------------------------------------------------------------------
// CSifSTM32
//------------------------------------------------------------------------------
class CSifSTM32 : public CSystemIF, public ISysTimerSync
{
public:
	CSifSTM32(TSTM32F10XReg *STM32);
	virtual ~CSifSTM32();
private:
	TSTM32F10XReg *m_STM32;
	bool HasReadEvent(intptr_t Index);
	void GetByte2(intptr_t Index, unsigned char &Value);
	bool SetByte2(intptr_t Index, unsigned char Value);
	void ReadEvent(intptr_t Index);
	void WriteEvent(intptr_t Index);
public:
	CSifSTM32USART USART1;
	CSifSTM32USART USART2;
	CSifSTM32USART USART3;
public:
	__int64 GetTimer();
	void Progress(__int64 Timer);
	void CallTimeOut(__int64 Frequency);
	void OnTerminate();
};

//---------------------------------------------------------------------------
#endif // SifSTM32H
