//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: Sample1.h 128 2013-03-02 09:02:25Z nagasima $
#pragma once

#ifndef Sample1H
#define Sample1H

#include "WinKernel.h"
#include "SifWIN32.h"
#include "SifCorei7SCS.h"

#ifdef __cplusplus
extern "C"{
#endif

#if defined(_USRDLL)
#define DLL_EXPORT	__declspec(dllexport)
#else
#define DLL_EXPORT	__declspec(dllimport)
#endif

DLL_EXPORT void Start();

DLL_EXPORT void Exit();

DLL_EXPORT void Interrupt(int IntNo);

DLL_EXPORT void GetUnitName(TCHAR *value, int size);

DLL_EXPORT void SetUnitName(const TCHAR *value);

DLL_EXPORT void AssignOnSetEvent(TKernelEvent *OnSetEvent, void *ObjOfOnSetEvent);

DLL_EXPORT void AssignOnStart(TKernelEvent *OnStart, void *ObjOfOnStart);

DLL_EXPORT void AssignOnTerminate(TKernelEvent *OnTerminate, void *ObjOfOnTerminate);

DLL_EXPORT void AssignOnIdle(TKernelEvent *OnIdle, void *ObjOfOnIdle);

DLL_EXPORT void AssignOnOutput(TOutputEvent *OnOutput, void *ObjOfOnOutput);

DLL_EXPORT void AssignOnGetSystemTime(TGetSystemTimeEvent *OnGetSystemTime, void *ObjOfOnGetSystemTime);

DLL_EXPORT int ReadAddr(uintptr_t Addr, void *buffer, int count);

DLL_EXPORT int WriteAddr(uintptr_t Addr, const void *buffer, int count);

DLL_EXPORT bool GetBit(uintptr_t Addr, int bit);

DLL_EXPORT void SetBit(uintptr_t Addr, int bit, bool value);

DLL_EXPORT bool ProcessEvent();

DLL_EXPORT void Input(int Kind, const void *Data, int Size);

DLL_EXPORT __int64 GetTimer();

DLL_EXPORT void Progress(__int64 Timer);

DLL_EXPORT void CallTimeOut(__int64 Frequency);

#ifdef __cplusplus
}
#endif

class CSample1 : public CKernel
{
public:
	CSample1();
	virtual ~CSample1();
protected:
	void OnStart();
	void OnTerminate();
	ID OnIdle();
	void Input(int Kind, const void *Data, int Size);
private:
	CSifWIN32 *m_SifCPU;
	CSifCorei7SCS *m_SifSysCtrlSpc;
};

#endif Sample1H
