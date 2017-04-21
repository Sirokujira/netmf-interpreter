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

#include "tinyhal.h"
#include "..\..\..\..\DeviceCode\Targets\Native\RZA1\DeviceCode\RZA1.h"

#define LCD_BUS8

#if 0
//#define INSERT_NOP
//#define INSERT_WAIT
//#define LCD_WAIT    10

#define LCD_ADDRESS	(*(volatile unsigned char*)0x05000000)
#define LCD_VALUE   (*(volatile unsigned char*)0x05020000)

#ifdef LCD_BUS8
#define LCD_RESET   PORT5.PODR.BIT.B1
#endif

void P8_Initialize(void)
{
    //PORT5.PMR.BIT.B1 = 0;   // P51 GPIO
    //PORT5.PDR.BIT.B1 = 1;	// P51 output
}

void LCD_nRESET(int n)
{
#if 0
    if (n)
        LCD_RESET = 1;
    else
        LCD_RESET = 0;
#endif
}

void P8_LCD_cmd(volatile unsigned short index, volatile unsigned short data)
{
    LCD_ADDRESS = (unsigned char)(index >> 8);
    LCD_ADDRESS = (unsigned char)(index >> 0);
#ifdef INSERT_WAIT
    unsigned int n;
    for (n=0;n<LCD_WAIT;n++);
#endif
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    LCD_VALUE = (unsigned char)(data >> 8);
    LCD_VALUE = (unsigned char)(data >> 0);
#ifdef INSERT_WAIT
    for (n=0;n<LCD_WAIT;n++);
#endif
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return;
}

void P8_LCD_cmd(volatile unsigned short index)
{
    LCD_ADDRESS = (unsigned char)(index >> 8);
    LCD_ADDRESS = (unsigned char)(index >> 0);
#ifdef INSERT_WAIT
    unsigned int n;
    for (n=0;n<LCD_WAIT;n++);
#endif
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return;
}

void P8_LCD_dat(volatile unsigned short data)
{
    LCD_VALUE = (unsigned char)(data >> 8);
    LCD_VALUE = (unsigned char)(data >> 0);
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return;
}

unsigned short P8_LCD_read_dat(volatile unsigned short index)
{
    volatile unsigned short data;
    LCD_ADDRESS = (unsigned char)(index >> 8);
    LCD_ADDRESS = (unsigned char)(index >> 0);
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    data = (unsigned short)LCD_VALUE;
    data = (data << 8) + (unsigned short)LCD_VALUE;
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return data;
}
#else
#define DDR_REST    PORT9.DDR.BIT.B3
#define DR_REST     PORT9.DR.BIT.B3
#define LCD_RESET   DR_REST

void P16_Initialize(void)
{
    PORT9.DDR.BIT.B3 = 0;    // P93 GPIO
    PORT9.DR.BIT.B3 = 1;    // P93 output
}

void LCD_nRESET(int n)
{
    if (n)
        LCD_RESET = 1;
    else
        LCD_RESET = 0;
}

void P16_LCD_cmd(volatile unsigned short index, volatile unsigned short data)
{
    LCD_ADDRESS = index;
#ifdef INSERT_WAIT
    unsigned int n;
    for (n=0;n<LCD_WAIT;n++);
#endif
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
#ifdef INSERT_WAIT
    LCD_VALUE = data;
    for (n=0;n<LCD_WAIT;n++);
#endif
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return;
}

void P16_LCD_index(volatile unsigned short index)
{
    LCD_ADDRESS = index;
#ifdef INSERT_WAIT
    unsigned int n;
    for (n=0;n<LCD_WAIT;n++);
#endif
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return;
}

void P16_LCD_dat(volatile unsigned short data)
{
    LCD_VALUE = data;
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return;
}

unsigned short P16_LCD_read_dat(volatile unsigned short index)
{
    volatile unsigned short data;
    LCD_ADDRESS = index;
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    data = LCD_VALUE;
#ifdef INSERT_NOP
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
    __asm__ __volatile__("nop");
#endif
    return data;
}
#endif
//--//
