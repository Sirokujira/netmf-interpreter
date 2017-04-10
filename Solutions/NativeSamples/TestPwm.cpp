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

#ifdef TEST_PWM

void TestPWM(void)
{
#if defined(MB9BF568R)
    //PWM_CHANNEL channel = (PWM_CHANNEL)0;      //
#elif defined(PLATFORM_ARM_CQ_FRK_FM3) | defined(PLATFORM_ARM_WKFM3) | defined(PLATFORM_ARM_WXMP3PLCD_FM3)
    PWM_CHANNEL channel = (PWM_CHANNEL)6;        // PF3
#elif defined(PLATFORM_RX62N_CQ_FRK_RX62N) | defined(PLATFORM_RX62N_WKLCD62N) | defined(PLATFORM_RX62N_WXMP3PLCD)
    //PWM_CHANNEL channel = (PWM_CHANNEL)0;      //
#elif defined(PLATFORM_RX63N_GR_SAKURA)
    //PWM_CHANNEL channel = (PWM_CHANNEL)6;      //
#elif defined(PLATFORM_RZA1_MBED_GR_PEACH)
    PWM_CHANNEL channel = (PWM_CHANNEL)7;        // P8_11 - D6
#endif
    PWM_SCALE_FACTOR factor = PWM_MICROSECONDS;
    PWM_Initialize(channel);
    GPIO_PIN pin = PWM_GetPinForChannel(channel);

    // from 90% to 2/3, to 50%, to 1/3 to 10%
    float dc[5] = {0.9, 0.666, 0.5, 0.333, 0.1};
    UINT32 period1 = 100;    // 10khz
    for (UINT32 idx = 0; idx < 5; ++idx) {
        UINT32 duration1 = (UINT32)((float)period1 * dc[idx]);
        PWM_ApplyConfiguration(channel, pin, period1, duration1, factor, FALSE);
        PWM_Start(channel, pin);
        //HAL_Time_Sleep_MicroSeconds_InterruptEnabled(1*1000*1000);
        Events_WaitForEvents(0, 2*1000);
        PWM_Stop(channel, pin);
    }
#if 0
    // from 10Khz to 1Khz, 50% duty cycle
    for (UINT32 period = 500; period >= 50; period -= 100) {
        UINT32 duration = period / 2;
        PWM_ApplyConfiguration(channel, pin, period, duration, factor, FALSE);
        PWM_Start(channel, pin);
        Events_WaitForEvents(0, 2*1000);
        PWM_Stop(channel, pin);
    }
#endif
    PWM_Uninitialize(channel);
}
#endif
