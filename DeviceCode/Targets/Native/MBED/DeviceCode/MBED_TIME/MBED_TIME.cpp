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
//  Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "mbed.h"

//#define DEBUG_TIMER

#define US_TICKER_TIMER_IRQn (OSTMI1TINT_IRQn)
#define CPG_STBCR5_BIT_MSTP50   (0x01u) /* OSTM1 */
#define US_TICKER_CLOCK_US_DEV (1000000)
#define MAX_TIMER_COUNT     0xffffffffL
#define MAX_TARGET_COUNT    0x0fffffffffffffffL
//#define MAX_TARGET_COUNT    0xffffffffffffffffL

volatile UINT64 g_target_count = (UINT64)MAX_TARGET_COUNT;
static volatile UINT64 g_timer_count = 0L;
static volatile UINT32 g_timer_cmp = MAX_TIMER_COUNT;
static volatile UINT32 g_timer_cnt = 0;
static float count_clock = 0;

static void Time_wait_us(UINT32 us)
{
    UINT64 start = HAL_Time_CurrentTicks();
    UINT64 diff = (UINT64)((float)us * count_clock);
    while ((HAL_Time_CurrentTicks() - start) < diff);
}


// Puts the hardware device into sleep mode for a specified number of microseconds.
// void HAL_Time_Sleep_MicroSeconds (
//         UINT32 uSec
// )
// Parameters
//    uSec: The number of microseconds that the hardware device is to remain in sleep mode.
void HAL_Time_Sleep_MicroSeconds(UINT32 uSec)
{
    Time_wait_us(uSec);
}

// Puts the hardware device into sleep mode for a specified number of microseconds.
// void HAL_Time_Sleep_MicroSeconds_InRam (
//          UINT32 uSec
// )
// Parameters
//    uSec: The number of microseconds that the hardware device is to remain in sleep mode.

// Puts the hardware device into interruptible sleep mode for a specified number of microseconds.
// void HAL_Time_Sleep_MicroSeconds_InterruptEnabled (
//          UINT32 uSec
// )
// Parameters
//    uSec: The number of microseconds that the hardware device is to remain in sleep mode.
void HAL_Time_Sleep_MicroSeconds_InterruptEnabled(UINT32 uSec)
{
    Time_wait_us(uSec);
}

UINT64 HAL_Time_CurrentTicks()
{
    g_timer_cnt = (UINT32)OSTM1CNT;
    return g_timer_count + (UINT64)g_timer_cnt;
}

static void Check_Timer_Overflow(void)
{
    if (g_timer_count >= (UINT64)MAX_TARGET_COUNT) {
        g_timer_count -= (UINT64)MAX_TARGET_COUNT;
#if defined(DEBUG_TIMER)
        lcd_printf("Timer Overflow\r\n");
#endif
        if (g_target_count >= (UINT64)MAX_TARGET_COUNT) {
            g_target_count -= (UINT64)MAX_TARGET_COUNT;
        }
    }
}

void Timer_Interrupt(void)
{
	UINT64 timer_count;
    {
        GLOBAL_LOCK(irq);
		timer_count = g_timer_count + (UINT64)OSTM1CNT;
    }
    if (timer_count >= g_target_count) {
        HAL_COMPLETION::DequeueAndExec();
    }
#if defined(DEBUG_TIMER)
    lcd_printf("Timer Int\n\r");
#endif
}

void HAL_Time_SetCompare(UINT64 CompareValue)
{
	GLOBAL_LOCK(irq);
	g_target_count = CompareValue;
	g_timer_count += (UINT64)OSTM1CNT;
    Check_Timer_Overflow();
	if (CompareValue > g_timer_count) {
	    g_timer_cmp = (UINT32)(CompareValue - g_timer_count);
	} else {
	    g_timer_cmp = (UINT32)500;
	}
	OSTM1TT = (UINT8)0x01;
    OSTM1CMP = (UINT32)g_timer_cmp;
    OSTM1CTL = (UINT8)0x02;
    OSTM1TS = (UINT8)0x01;
}

// Initializes the driver for the system clock.
// BOOL HAL_Time_Initialize ()
// Return Value
//    true if the system clock driver was successfully initialized; otherwise, false.
BOOL HAL_Time_Initialize()
{
    GLOBAL_LOCK(irq);
    count_clock = ((float)CM0_RENESAS_RZ_A1_P0_CLK / (float)US_TICKER_CLOCK_US_DEV);
    /* Power Control for Peripherals      */
    CPGSTBCR5 &= ~(CPG_STBCR5_BIT_MSTP50); /* enable OSTM1 clock */
    // timer settings
    OSTM1TT   = (UINT8)0x01;
    OSTM1CTL  = (UINT8)0x02;
    OSTM1CMP  = (UINT32)MAX_TIMER_COUNT;
    g_timer_cmp = (UINT32)MAX_TIMER_COUNT;
    OSTM1TS   = (UINT8)0x01;     // start
    g_timer_count = (UINT64)OSTM1CNT;
    g_target_count = (UINT64)(-1L);
    // INTC settings
    InterruptHandlerRegister(US_TICKER_TIMER_IRQn, Timer_Interrupt);
    GIC_SetPriority(US_TICKER_TIMER_IRQn, 5);
    GIC_EnableIRQ(US_TICKER_TIMER_IRQn);
    return TRUE;
}

// Uninitializes the driver (resets the time) for the system clock.
// BOOL HAL_Time_Uninitialize ()
// Return Value
//    true if the reset succeeded; otherwise, false.
BOOL HAL_Time_Uninitialize()
{
    GIC_DisableIRQ(US_TICKER_TIMER_IRQn);
    return TRUE;
}

// Converts a specified number of real-time clock ticks to common language runtime (CLR) base time, in 100-nanosecond (ns) increments.
// INT64 HAL_Time_TicksToTime (
//         UINT64 Ticks
// )
// Parameters
//    Ticks: The number of real-time clock ticks to be converted to 100-ns CLR increments.
// Return Value
//    The number of 100-ns CLR increments that is equivalent to the specified number of real-time clock ticks.
INT64 HAL_Time_TicksToTime(UINT64 Ticks)
{
    return CPU_TicksToTime(Ticks);
}

INT64 HAL_Time_CurrentTime()
{
    return CPU_TicksToTime(HAL_Time_CurrentTicks());
}

// Obtains the clock drift parameters.
// a: After the function call returns, contains a pointer to the divisor.
// b: After the function call returns, contains a pointer to the multiplication factor.
// c: After the function call returns, contains a pointer to the offset, if any.
// correct_time = (raw_time * b + c) / a
void HAL_Time_GetDriftParameters (INT32* a, INT32* b, INT64* c)
{
    *a = 1;
    *b = 1;
    *c = 0;
}

UINT32 CPU_SystemClock()
{
    return SYSTEM_CLOCK_HZ;            // ICLK=400MHz
}

UINT32 CPU_TicksPerSecond()
{
    return SLOW_CLOCKS_PER_SECOND;        // PCLK
}

// Converts a specified number of real-time clock ticks to common language runtime (CLR) base time, in 100-nanosecond (ns) increments.
// UINT64 CPU_TicksToTime (
//         UINT64 Ticks32
// )
// Parameters
//    Ticks64
//    The number of real-time clock ticks to be converted to 100-ns CLR increments.
// Return Value
//    The number of 100-ns CLR increments that is equivalent to the specified number of real-time clock ticks.
UINT64 CPU_TicksToTime(UINT64 Ticks)
{
    return (UINT64)((Ticks * (UINT64)TEN_MHZ) / (UINT64)SLOW_CLOCKS_PER_SECOND);
}

// Converts a specified number of real-time clock ticks to common language runtime (CLR) base time, in 100-nanosecond (ns) increments.
// UINT32 CPU_TicksToTime (
//         UINT64 Ticks32
// )
// Parameters
//    Ticks32
//    The number of real-time clock ticks to be converted to 100-ns CLR increments.
// Return Value
//    The number of 100-ns CLR increments that is equivalent to the specified number of real-time clock ticks.
UINT64 CPU_TicksToTime(UINT32 Ticks32)
{
    return CPU_TicksToTime((UINT64)Ticks32);
}

// Converts a specified number of milliseconds to the corresponding number of real-time clock ticks, for large values.
// UINT64 CPU_MillisecondsToTicks (
//         UINT64 mSec
// )
// Parameters
//    mSec: The number of milliseconds to be converted to real-time clock ticks.
// Return Value
//    The number of real-time clock ticks that is equivalent to the specified number of milliseconds.
UINT64 CPU_MillisecondsToTicks(UINT64 Ticks)
{
    return (UINT64)((Ticks * (UINT64)SLOW_CLOCKS_PER_SECOND) / (UINT64)1000L);
}

// Converts a specified number of milliseconds to the corresponding number of real-time clock ticks, for large values.
// UINT64 CPU_MillisecondsToTicks (
//         UINT32 mSec
// )
// Parameters
//    mSec: The number of milliseconds to be converted to real-time clock ticks.
// Return Value
//    The number of real-time clock ticks that is equivalent to the specified number of milliseconds.
UINT64 CPU_MillisecondsToTicks(UINT32 Ticks32)
{
    return CPU_MillisecondsToTicks((UINT64)Ticks32);
}

// Converts a specified number of microseconds to the corresponding number of real-time clock ticks.
// UINT64 CPU_MicrosecondsToTicks (
//         UINT64 uSec
//)
// Parameters
//    uSec: The number of microseconds to be converted to real-time clock ticks.
// Return Value
//    The number of real-time clock ticks that is equivalent to the specified number of microseconds.

//UINT64 CPU_MicrosecondsToTicks(UINT64 uSec) __attribute__ ((section ("SectionForFlashOperations")));
UINT64 CPU_MicrosecondsToTicks(UINT64 uSec)
{
    return (UINT64)((uSec * (UINT64)SLOW_CLOCKS_PER_SECOND) / (UINT64)ONE_MHZ);
}

// Converts a specified number of microseconds to the corresponding number of real-time clock ticks.
// UINT32 CPU_MicrosecondsToTicks (
//         UINT32 uSec
// )
// Parameters
//    uSec: The number of microseconds to be converted to real-time clock ticks.
// Return Value
//    The number of real-time clock ticks that is equivalent to the specified number of microseconds.
//UINT32 CPU_MicrosecondsToTicks(UINT32 uSec) __attribute__ ((section ("SectionForFlashOperations")));
UINT32 CPU_MicrosecondsToTicks(UINT32 uSec)
{
    return CPU_MicrosecondsToTicks((UINT64)uSec);
}

// Converts a specified number of microseconds to the corresponding number of system clock ticks.
// UINT32 CPU_MicrosecondsToSystemClocks (
//    UINT32 uSec
// )
// Parameters
//    uSec: The number of microseconds to be converted to system clock ticks.
// Return Value
//    The number of system clock ticks that is equivalent to the specified number of microseconds.
UINT32 CPU_MicrosecondsToSystemClocks(UINT32 uSec)
{
    return uSec * ((UINT32)SYSTEM_CLOCK_HZ / (UINT32)ONE_MHZ);
}

int CPU_MicrosecondsToSystemClocks(int uSec)
{
    return (int)CPU_MicrosecondsToSystemClocks((UINT32)uSec);
}

int CPU_SystemClocksToMicroseconds(int Ticks)
{
    return (int)(((UINT64)Ticks * (UINT64)ONE_MHZ) / (UINT64)SYSTEM_CLOCK_HZ);
}

#define MBED_SLEEP_USEC_FIXED_OVERHEAD_CLOCKS 3

#ifdef __cplusplus
extern "C" {
#endif
void __attribute__ ((section ("SectionForFlashOperations"))) IDelayLoop(volatile int count)
{
    while (count-- > 0) {
        __asm__ __volatile ("nop");
    }
}
#ifdef __cplusplus
}
#endif
