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

#ifdef TEST_LCD
#include "sample_bmp.h"

#if defined(PLATFORM_ARM_WXMP3PLCD_FM3)
unsigned short P8_LCD_read_dat(volatile unsigned short index);

void LCD_reg_dump(void)
{
    int i = 0;
    for (i = 0; i < 1; i++) {
        debug_printf("LCD reg[%02x] = %04x\r\n", i, P8_LCD_read_dat((volatile unsigned short)i));
    }
}
#endif

void TestLCD(void)
{
    LCD_Initialize();
    LCD_Clear();
    LCD_BitBltEx(0, 0, 100, 128, (UINT32 *)bmp);
}
#endif
