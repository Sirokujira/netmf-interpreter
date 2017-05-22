//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifCorei7SCS.h 128 2013-03-02 09:02:25Z nagasima $
#ifndef SifCorei7SCSH
#define SifCorei7SCSH

//---------------------------------------------------------------------------
#include "SIFLayer.h"
#include "Corei7SCSReg.h"

enum TTimerTerm
{
	ttInterrupt,
	ttWait,
};

//------------------------------------------------------------------------------
// CSifCorei7SCS
//------------------------------------------------------------------------------
class CSifCorei7SCS :public ISifCPU, public CSystemIF, public ISysTimerSync
{
public:
	CSifCorei7SCS(TCorei7SCSReg *Corei7SCS);
	virtual ~CSifCorei7SCS();
private:
	TCorei7SCSReg *m_Corei7SCS;
	bool HasReadEvent(intptr_t Index);
	void GetByte2(intptr_t Index, unsigned char &Value);
	bool SetByte2(intptr_t Index, unsigned char Value);
	void ReadEvent(intptr_t Index);
	void WriteEvent(intptr_t Index);
private:
	TTimerTerm m_Term;
	__int64 m_Timer;						// タイマー値
	__int64 m_ResetTime;
public:
	bool InterruptEnabled(int IntNo);
	void ClearInterrupt(int IntNo);
	void SetInterrupt(int IntNo);
	unsigned int InterruptPriority(int IntNo);
	void ChangeInterruptControlRegister(int,uint8_t);
public:
	__int64 GetTimer();
	void Progress(__int64 Timer);
	void CallTimeOut(__int64 Frequency);
};

//---------------------------------------------------------------------------
#endif // SifCorei7SCSH
