////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
   
////////////////////////////////////////////////////////////////////////////////////////////////////

#if 1 // Global Lock activated

//extern "C"
//{
// UINT32   linux_InterruptsAreEnabled();
// void     linux_InterruptDisable();
// void     linux_InterruptEnable();
//}

#define ENABLE_STATE 0

SmartPtr_IRQ::SmartPtr_IRQ(void* context)
{
    m_context = context;
    Disable();
}

SmartPtr_IRQ::~SmartPtr_IRQ() 
{
    Restore();
}

BOOL SmartPtr_IRQ::WasDisabled()
{
    return (m_state != ENABLE_STATE);
}

void SmartPtr_IRQ::Acquire()
{
    UINT32 Cp = m_state;

    if(Cp != ENABLE_STATE)
    {
        Disable();
    }
}

void SmartPtr_IRQ::Release()
{
    UINT32 Cp = m_state;

    if(Cp == ENABLE_STATE)
    {
	    // Cp = !linux_InterruptsAreEnabled();
		// linux_InterruptEnable();
        m_state = Cp;
    }
}

void SmartPtr_IRQ::Probe()
{
    UINT32 Cp = m_state;

    if(Cp == ENABLE_STATE)
    {
		// linux_InterruptEnable();
		// linux_InterruptDisable();
    }
}

BOOL SmartPtr_IRQ::GetState(void* context)
{
	UINT32 Cp;
	
    // Cp = !linux_InterruptsAreEnabled();

    // return (Cp == ENABLE_STATE);
	return FALSE;
}

BOOL SmartPtr_IRQ::ForceDisabled(void* context)
{
    UINT32 Cp;

    // Cp = !linux_InterruptsAreEnabled();
	// linux_InterruptDisable();
    // return (Cp == ENABLE_STATE);
	
	return FALSE;
}

BOOL SmartPtr_IRQ::ForceEnabled(void* context)
{
    UINT32 Cp;

    // Cp = !linux_InterruptsAreEnabled();
	// linux_InterruptEnable();
    // return (Cp == ENABLE_STATE);
	
	return FALSE;
}

void SmartPtr_IRQ::Disable()
{
	UINT32 Cp;

	// Cp = !linux_InterruptsAreEnabled();
	// linux_InterruptDisable();
    // m_state = Cp;
	return ;
}

void SmartPtr_IRQ::Restore()
{
    UINT32 Cp = m_state;

    if(Cp == ENABLE_STATE)
    {
		// linux_InterruptEnable();
    }
}

#else
// Those are from GlobalLock_stubs.cpp

SmartPtr_IRQ::SmartPtr_IRQ(void* context)
{ 
}

SmartPtr_IRQ::~SmartPtr_IRQ() 
{ 
}

BOOL SmartPtr_IRQ::WasDisabled()
{
    return TRUE;
    
}

void SmartPtr_IRQ::Acquire()
{
}

void SmartPtr_IRQ::Release()
{
}

void SmartPtr_IRQ::Probe()
{
}

BOOL SmartPtr_IRQ::GetState(void* context)
{
    return TRUE;
}

BOOL SmartPtr_IRQ::ForceDisabled(void* context)
{
    return TRUE;    
}

BOOL SmartPtr_IRQ::ForceEnabled(void* context)
{
    return TRUE; 
}

void SmartPtr_IRQ::Disable()
{
}

void SmartPtr_IRQ::Restore()
{
}

#endif
