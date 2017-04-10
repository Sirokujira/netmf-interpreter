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
//  Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

#ifdef TEST_EVENTS

#define DBG_PRINTF

void TestEvents(void)
{
    char key[1];
    int i = 0;
#if defined(MB9BF568R)
    GPIO_PIN pin = (GPIO_PIN)0x34;
#else
    GPIO_PIN pin = (GPIO_PIN)0x34;
#endif
#if defined(PLATFORM_ARM_CQ_FRK_FM3) | defined(PLATFORM_ARM_WKFM3) | defined(PLATFORM_ARM_WXMP3PLCD_FM3)
    GPIO_PIN pin = (GPIO_PIN)0xF3;
#endif
#if defined(PLATFORM_RX62N_CQ_FRK_RX62N) | defined(PLATFORM_RX62N_WKLCD62N) | defined(PLATFORM_RX62N_WXMP3PLCD)
    GPIO_PIN pin = (GPIO_PIN)0x0D;
#endif
#if defined(PLATFORM_RX63N_GR_SAKURA)
    GPIO_PIN pin = (GPIO_PIN)86;
#endif
#if defined(PLATFORM_RZA1_MBED_GR_PEACH)
    GPIO_PIN pin = (GPIO_PIN)68;    // LED1 68, LED2 50, LED3 70, LED4 71
#endif
    BOOL state = FALSE;
    CPU_GPIO_EnableOutputPin(pin, state);
    while (true) {
        CPU_GPIO_SetPinState(pin, state);
#if defined(DBG_PRINTF)
        dbg_printf("Waiting key %d:", i);
#endif
        UINT32 Events = Events_WaitForEvents(SYSTEM_EVENT_FLAG_COM_IN, 1000);
        if (Events & SYSTEM_EVENT_FLAG_COM_IN) {
            Events_Clear(SYSTEM_EVENT_FLAG_COM_IN);
            DebuggerPort_Read(COM1, key, 1);
#if defined(DBG_PRINTF)
            dbg_printf("%c\r\n", key[0]);
#endif
        } else {
#if defined(DBG_PRINTF)
            dbg_printf("\r\n");
#endif
        }
#if defined(DBG_PRINTF)
        dbg_printf("\r\n");
#endif
        state ^= 1;
        i++;
    }
}
#endif
