/* mbed Microcontroller Library - CMSIS
 * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
 *
 * A generic CMSIS include header, pulling in LPC1768 specifics
 */

#ifndef MBED_CMSIS_H
#define MBED_CMSIS_H

#include "MBRZA1H.h"

#if defined(__ARMCC_VERSION)

#else
//#ifndef __enable_irq
//static inline void __enable_irq(void)
//{
//    __asm__("cpsie i");
//}
//#endif
//
//#ifndef __disable_irq
//static inline void __disable_irq(void)
//{
//    __asm__("cpsid i");
//}
//#endif
#endif

#endif
