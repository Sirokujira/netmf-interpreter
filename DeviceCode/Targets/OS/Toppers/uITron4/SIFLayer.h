//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: SIFLayer.h 128 2013-03-02 09:02:25Z nagasima $
#ifndef SIFLayerH
#define SIFLayerH

//---------------------------------------------------------------------------
#define TOPPERS_size	tagSIZE
extern "C" {
#include <kernel.h>
#include <sil.h>
}

//------------------------------------------------------------------------------
// DriverÅÃSimulator
//------------------------------------------------------------------------------
class ISystemIF
{
public:
	virtual unsigned char GetByte(uintptr_t Addr) = 0;
	virtual void SetByte(uintptr_t Addr, unsigned char Value) = 0;
	virtual unsigned short GetUInt16(uintptr_t Addr) = 0;
	virtual void SetUInt16(uintptr_t Addr, unsigned short Value) = 0;
	virtual unsigned int GetUInt32(uintptr_t Addr) = 0;
	virtual void SetUInt32(uintptr_t Addr, unsigned int Value) = 0;
};

//-------------------------------------------------------------------------
// TSystemIFItem
//-------------------------------------------------------------------------
struct TSystemIFItem
{
	uintptr_t Addr;
	int Size;
	void *Substitute;
	ISystemIF *SystemIF;
};

//------------------------------------------------------------------------------
// DriverÅÃSimulator
//------------------------------------------------------------------------------
class CSystemIF : public ISystemIF
{
public:
	CSystemIF(intptr_t BaseAddr, int Size);
	virtual ~CSystemIF();
private:
	intptr_t m_BaseAddr;
	int m_Size;
protected:
	virtual bool HasReadEvent(intptr_t Index) = 0;
	virtual void GetByte2(intptr_t Index, unsigned char &Value) = 0;
	virtual bool SetByte2(intptr_t Index, unsigned char Value) = 0;
	virtual void ReadEvent(intptr_t Index) = 0;
	virtual void WriteEvent(intptr_t Index) = 0;
public:
	unsigned char GetByte(uintptr_t Addr);
	void SetByte(uintptr_t Addr, unsigned char Value);
	unsigned short GetUInt16(uintptr_t Addr);
	void SetUInt16(uintptr_t Addr, unsigned short Value);
	unsigned int GetUInt32(uintptr_t Addr);
	void SetUInt32(uintptr_t Addr, unsigned int Value);
};

//------------------------------------------------------------------------------
// DriverÅÃSimulator
//------------------------------------------------------------------------------
class ISysTimerSync
{
public:
	virtual __int64 GetTimer() = 0;
	virtual void Progress(__int64 Timer) = 0;
	virtual void CallTimeOut(__int64 Frequency) = 0;
};

//------------------------------------------------------------------------------
// CPU
//------------------------------------------------------------------------------
class ISifCPU
{
public:
	virtual bool InterruptEnabled(int IntNo) = 0;
	virtual void ClearInterrupt(int IntNo) = 0;
	virtual void SetInterrupt(int IntNo) = 0;
	virtual unsigned int InterruptPriority(int IntNo) = 0;
	virtual void ChangeInterruptControlRegister(int IntNo, uint8_t icrcmd) = 0;
};

//---------------------------------------------------------------------------
#endif // SIFLayerH
