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

//#define TEST_AD
//#define TEST_BUTTON
//#define TEST_COMPLETION
//#define TEST_EVENTS
#define TEST_FLASH
//#define TEST_I2C
//#define TEST_LCD
//#define TEST_LWIP
//#define TEST_MEMORY
//#define TEST_MP3
//#define TEST_PWM
//#define TEST_SD
//#define TEST_TOUCHPANEL
//#define TEST_USB

#include <tinyhal.h>
#include "nativesample.h"

#ifdef TEST_AD
#include "..\NativeSamples\TestAD.cpp"
void TestAD(void);
#endif

#ifdef TEST_BUTTON
#include "..\NativeSamples\TestButton.cpp"
void TestButton(void);
#endif

#ifdef TEST_COMPLETION
#include "TestCompletion.cpp"
void TestCompletion(void);
#endif

#ifdef TEST_EVENTS
#include "..\NativeSamples\TestEvents.cpp"
void TestEvent(void);
#endif

#ifdef TEST_FLASH
#include "..\NativeSamples\TestFlash.cpp"
void TestFlash(void);
#endif

#ifdef TEST_I2C
//#define TMP102
//#define EEPROM
#define I2CDETECT
#include "..\NativeSamples\TestI2C.cpp"
void TestI2C(void);
#endif

#ifdef TEST_LCD
#include "..\NativeSamples\TestLCD.cpp"
void TestLCD(void);
#endif

#ifdef TEST_LWIP
#include "..\NativeSamples\TestlwIP.cpp"
void TestlwIP(void);
#endif

#ifdef TEST_MEMORY
#include "..\NativeSamples\TestMemory.cpp"
void TestMemory(void);
#endif

#ifdef TEST_MP3
#include "..\NativeSamples\TestMP3.cpp"
//void TestMP3(void);
#endif

#ifdef TEST_PWM
#include "..\NativeSamples\TestPWM.cpp"
void TestPWM(void);
#endif

#ifdef TEST_SD
#include "..\NativeSamples\TestSD.cpp"
void TestSD(void);
#endif

#ifdef TEST_TOUCHPANEL
#include "..\NativeSamples\TestTouchPanel.cpp"
void TestTouchPanel(void);
#endif

#ifdef TEST_USB
#include "..\NativeSamples\TestUSB.cpp"
void TestUSB(void);
#endif

//HAL_DECLARE_NULL_HEAP();
HAL_DECLARE_CUSTOM_HEAP(SimpleHeap_Allocate, SimpleHeap_Release,SimpleHeap_ReAllocate);

#ifndef TEST_TOUCHPANEL
void PostManagedEvent(UINT8 category, UINT8 subCategory, UINT16 data1, UINT32 data2)
{
}
#endif

void wait(volatile UINT64 count)
{
    while (count-- > 0) ;
}

void memory_dump(unsigned long addr, int len)
{
    int i;
    char *p = (char *)addr;
    for (i = 0; i < len; i++) {
        if ((i & 0xf) == 0) {
            debug_printf("%08x ", (unsigned long)p);
        }
        debug_printf("%02x ", (unsigned char)(*p & 0xff));
        if ((i & 0xf) == 0xf) {
            debug_printf("\r\n");
        }
        p++;
    }
    debug_printf("\r\n");
}

#if 0
void JTAG_init(void)
{
    CPU_GPIO_DisablePin(0x00, (GPIO_RESISTOR)0, 0, (GPIO_ALT_MODE)1);
    CPU_GPIO_DisablePin(0x01, (GPIO_RESISTOR)0, 0, (GPIO_ALT_MODE)1);
    CPU_GPIO_DisablePin(0x02, (GPIO_RESISTOR)0, 0, (GPIO_ALT_MODE)1);
    CPU_GPIO_DisablePin(0x03, (GPIO_RESISTOR)0, 0, (GPIO_ALT_MODE)1);
    CPU_GPIO_DisablePin(0x04, (GPIO_RESISTOR)0, 0, (GPIO_ALT_MODE)1);
}
#endif

void ApplicationEntryPoint()
{
    UINT8 *BaseAddress;
    UINT32 SizeInBytes;
    //  JTAG_init();
    HeapLocation(BaseAddress, SizeInBytes);
    SimpleHeap_Initialize(BaseAddress, SizeInBytes);
    HalSystemConfig.DebugTextPort = COM1;
    DebuggerPort_Initialize(HalSystemConfig.DebugTextPort);

#ifdef TEST_MEMORY
    TestMemory();
#endif
#ifdef TEST_AD
    TestAD();
#endif
#ifdef TEST_BUTTON
    TestButton();
#endif
#ifdef TEST_COMPLETION
    TestCompletion();
#endif
#ifdef TEST_EVENTS
    TestEvents();
#endif
#ifdef TEST_FLASH
    TestFlash();
#endif
#ifdef TEST_I2C
    TestI2C();
#endif
#ifdef TEST_LCD
    TestLCD();
#endif
#ifdef TEST_LWIP
    TestlwIP();
#endif
#ifdef TEST_MP3
    TestMP3();
#endif
#ifdef TEST_PWM
    TestPWM();
#endif
#ifdef TEST_SD
    TestSD();
#endif
#ifdef TEST_TOUCHPANEL
    TestTouchPanel();
#endif
#ifdef TEST_USB
    TestUSB();
#endif
    while (true);
}
