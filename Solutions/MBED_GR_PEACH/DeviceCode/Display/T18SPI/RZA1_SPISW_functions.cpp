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
#include "mbed.h"

void SPISW_GPIO_Initialize(void);

gpio_t obj_ck;
gpio_t obj_di;
gpio_t obj_cs;
gpio_t obj_rs;
gpio_t obj_re;

#define SPISWPIN    0

#if (SPISWPIN == 0)
// GR_PEACH + Aitendo T18SPI LCD Shield
// 4 line SPI mode
// CLK  D2 P11_15
// DI   D3 P11_14
// CS   D4 P11_13
// RS   D5 P11_12
// Res  D6 P8_11
#define PIN_CK  P11_15
#define PIN_DI  P11_14
#define PIN_CS  P11_13
#define PIN_RS  P11_12
#define PIN_RE  P8_11

#define MOSI(v) gpio_write(&obj_di, v)
#define CS_LOW  gpio_write(&obj_cs, 0)
#define CS_HIGH gpio_write(&obj_cs, 1)
#define CK_LOW  gpio_write(&obj_ck, 0)
#define CK_HIGH gpio_write(&obj_ck, 1)
#define DI_LOW  gpio_write(&obj_di, 0)
#define DI_HIGH gpio_write(&obj_di, 1)
#define RS_LOW  gpio_write(&obj_rs, 0)
#define RS_HIGH gpio_write(&obj_rs, 1)
#define RES_LOW  gpio_write(&obj_re, 0)
#define RES_HIGH gpio_write(&obj_re, 1)
#endif

void SPISW_GPIO_Initialize(void)
{
    gpio_init_out(&obj_ck, PIN_CK);
    gpio_init_out(&obj_di, PIN_DI);
    gpio_init_out(&obj_cs, PIN_CS);
    gpio_init_out(&obj_rs, PIN_RS);
    gpio_init_out(&obj_re, PIN_RE);
}

void SPISW_Initialize(void)
{
    SPISW_GPIO_Initialize();
    CS_HIGH;
    CK_HIGH;
}

void SPISW_Reset(UINT32 v)
{
    if (v) {
        RES_HIGH;
    } else {
        RES_LOW;
    }
}

void SPISW_Write(UINT8 dat)
{
    UINT8 i = 8;
    while (i-- > 0) {
        MOSI((dat & 0x80) ? 1 : 0);
        CK_LOW;
        CK_HIGH;
        dat <<= 1;
    }
}

void SPISW_LCD_cmd(UINT8 dat)
{
    // Enter command mode: SDATA=LOW at rising edge of 1st SCLK
    CS_LOW;
    RS_LOW;
    SPISW_Write(dat);
    CS_HIGH;
}

void SPISW_LCD_dat(UINT8 dat)
{
    // Enter data mode: SDATA=HIGH at rising edge of 1st SCLK
    CS_LOW;
    RS_HIGH;
    SPISW_Write(dat);
    CS_HIGH;
}
