//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifWIN32.h 118 2013-02-12 13:05:51Z nagasima $
#ifndef SifWIN32H
#define SifWIN32H

//---------------------------------------------------------------------------
#include "SIFLayer.h"
#include "WIN32Reg.h"
#include "SifWIN32USART.h"

//------------------------------------------------------------------------------
// CSifWIN32
//------------------------------------------------------------------------------
class CSifWIN32 : public CSystemIF, public ISysTimerSync
{
public:
	CSifWIN32(TWIN32F10XReg *win32);
	virtual ~CSifWIN32();
private:
	TWIN32F10XReg *m_WIN32;
	bool HasReadEvent(intptr_t Index);
	void GetByte2(intptr_t Index, unsigned char &Value);
	bool SetByte2(intptr_t Index, unsigned char Value);
	void ReadEvent(intptr_t Index);
	void WriteEvent(intptr_t Index);
public:
	CSifWIN32USART USART1;
	CSifWIN32USART USART2;
	CSifWIN32USART USART3;
public:
	__int64 GetTimer();
	void Progress(__int64 Timer);
	void CallTimeOut(__int64 Frequency);
	void OnTerminate();
};

//---------------------------------------------------------------------------
#endif // SifWIN32H
