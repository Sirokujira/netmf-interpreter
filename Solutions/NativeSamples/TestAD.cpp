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

#ifdef TEST_AD
#if defined(PLATFORM_ARM_CQ_FRK_FM3) | defined(PLATFORM_ARM_WKFM3) | defined(PLATFORM_ARM_WXMP3PLCD_FM3)
#define AD_CH    (16)
#endif
#if defined(PLATFORM_RX63N_GR_SAKURA)
#define AD_CH    (0)
#endif
#if defined(PLATFORM_RZA1_GR_PEACH)
#define AD_CH    (0)
#endif

void TestAD(void)
{
    ANALOG_CHANNEL channel = (ANALOG_CHANNEL)AD_CH;
    AD_Initialize(channel, 12);
    GPIO_PIN pin = AD_GetPinForChannel(channel);

    UINT32 i = 100;
    while (i-- >0) {
        UINT32 value = AD_Read(channel);
        Events_WaitForEvents(0, 1000);
        dbg_printf("A/D %04d\r\n", value);
    }
}
#endif
