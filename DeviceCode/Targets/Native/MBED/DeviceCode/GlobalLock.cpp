////////////////////////////////////////////////////////////////////////////
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

//--//

#define DISABLED_MASK 0x1

__attribute__( ( always_inline ) ) void __NOP(void)
{
  __asm__ __volatile__ ("nop");
}

__attribute__( ( always_inline ) ) void __disable_irq(void)
{
    __asm__ __volatile__ ("cpsid i" : : : "memory");
}

__attribute__( ( always_inline ) ) void __enable_irq(void)
{
    __asm__ __volatile__ ("cpsie i" : : : "memory");
}

__attribute__( ( always_inline ) ) UINT32 __get_PRIMASK(void)
{
    UINT32 result;

    __asm__ __volatile__ ("MRS %0, primask" : "=r" (result) );
    return(result);
}

__attribute__( ( always_inline ) ) void __set_PRIMASK(UINT32 priMask)
{
    __asm__ __volatile__ ("MSR primask, %0" : : "r" (priMask) : "memory");
}


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
    return (m_state & DISABLED_MASK) == DISABLED_MASK;
}

void SmartPtr_IRQ::Acquire()
{
    UINT32 Cp = m_state;

    if ((Cp & DISABLED_MASK) == DISABLED_MASK)
    {
        Disable();
    }
}

void SmartPtr_IRQ::Release()
{
    UINT32 Cp = m_state;

    if ((Cp & DISABLED_MASK) == 0)
    {
        m_state = __get_PRIMASK();

        __enable_irq();
    }
}

void SmartPtr_IRQ::Probe()
{
    UINT32 Cp = m_state;

    if ((Cp & DISABLED_MASK) == 0)
    {
        UINT32 s = __get_PRIMASK();

        __enable_irq();

        // just to allow an interupt to an occur
        __NOP();

        // restore irq state
        __set_PRIMASK(s);
    }
}

BOOL SmartPtr_IRQ::GetState(void* context)
{
    return (0 == (__get_PRIMASK() & DISABLED_MASK));
}

BOOL SmartPtr_IRQ::ForceDisabled(void* context)
{
    __disable_irq();
    return true;
}

BOOL SmartPtr_IRQ::ForceEnabled(void* context)
{
    __enable_irq();
    return true;
}

void SmartPtr_IRQ::Disable()
{
    m_state = __get_PRIMASK();

    __disable_irq();
}

void SmartPtr_IRQ::Restore()
{
    UINT32 Cp = m_state;

    if ((Cp & DISABLED_MASK) == 0)
    {
        __enable_irq();
    }
}
