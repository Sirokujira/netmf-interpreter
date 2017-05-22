//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SifCortexM3SCS.h 128 2013-03-02 09:02:25Z nagasima $
#ifndef SifCortexM3SCSH
#define SifCortexM3SCSH

//---------------------------------------------------------------------------
#include "SIFLayer.h"
#include "CortexM3SCSReg.h"

enum TTimerTerm
{
	ttInterrupt,
	ttWait,
};

//------------------------------------------------------------------------------
// CSifCortexM3SCS
//------------------------------------------------------------------------------
class CSifCortexM3SCS :public ISifCPU, public CSystemIF, public ISysTimerSync
{
public:
	CSifCortexM3SCS(TCortexM3SCSReg *CortexM3SCS);
	virtual ~CSifCortexM3SCS();
private:
	TCortexM3SCSReg *m_CortexM3SCS;
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
#endif // SifCortexM3SCSH
