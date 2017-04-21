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
#include "mbed.h"
#include "gpio_api.h"
#include "pinmap.h"
#include "PinNames.h"
#include "gpio_addrdefine.h"
//#include "..\..\..\..\DeviceCode\Targets\Native\RZA1\DeviceCode\RZA1.h"

// LCD D0-D7    P2_0-P2_7
// LCD CS       P5_7    always LOW
// LCD RS       P5_6
// LCD WR       P5_5
// LCD RESET    P5_4
// RS - WR      10ns (min)
// RS - RD      5ns (min)
// WR - RS      5ns (min)
// WR L width   50 - 500ns

#define PIN_RS  P5_6
#define PIN_WR  P5_5
#define PIN_RE  P5_4
#define LCD_BIT 8

static gpio_t obj_rs;
static gpio_t obj_wr;
static gpio_t obj_re;
static gpio_t obj_bus[LCD_BIT];

#define RS_LOW  gpio_write(&obj_rs, 0)
#define RS_HIGH gpio_write(&obj_rs, 1)
#define WR_LOW  gpio_write(&obj_wr, 0)
#define WR_HIGH gpio_write(&obj_wr, 1)
#define RES_LOW  gpio_write(&obj_re, 0)
#define RES_HIGH gpio_write(&obj_re, 1)

static PinName bus[LCD_BIT] = {
        P2_7,
        P2_6,
        P2_5,
        P2_4,
        P2_3,
        P2_2,
        P2_1,
        P2_0
};

#if 0
static void RZA_IO_RegWrite_16(volatile UINT16 * ioreg, UINT16 write_value, UINT16 shift, UINT16 mask)
{
    UINT16 reg_value;

    reg_value = *ioreg;                                         /* Read from register */
    reg_value = (reg_value & (~mask)) | (write_value << shift); /* Modify value       */
    *ioreg    = reg_value;                                      /* Write to register  */
}
#endif

static void mbed_gpio_init_out(gpio_t *obj, PinName pin, int value)
{
    gpio_init(obj, pin);
    if (pin != NC) {
        gpio_write(obj, value);
        gpio_dir(obj, PIN_OUTPUT);
    }
}

void P8_Initialize(void)
{
    UINT16 i;
    mbed_gpio_init_out(&obj_rs, PIN_RS, 1);
    mbed_gpio_init_out(&obj_wr, PIN_WR, 1);
    mbed_gpio_init_out(&obj_re, PIN_RE, 1);
    for (i = 0; i < LCD_BIT; i++){
        mbed_gpio_init_out(&obj_bus[i], bus[i], 0);
    }
    RS_HIGH;
    WR_HIGH;
}

void LCD_nRESET(int n)
{
    if (n) {
        RES_HIGH;
    }
    else {
        RES_LOW;
    }
}

static void P8_LCD_busout(UINT16 d)
{
    UINT16 i;
    for (i = 0; i < LCD_BIT; i++) {
        gpio_write(&obj_bus[i], (d & 0x1));
        d >>= 1;
    }
}

void P8_LCD_reg(volatile unsigned short index)
{
    UINT16 h, l;
    h = (index >> 8) & 0xff;
    l = index & 0xff;

    RS_LOW;
    WR_HIGH;
    P8_LCD_busout(h);
    WR_LOW;
    WR_HIGH;
    P8_LCD_busout(l);
    WR_LOW;
    WR_HIGH;
    return;
}

void P8_LCD_dat(volatile unsigned short data)
{
    UINT16 h, l;
    h = (data >> 8) & 0xff;
    l = data & 0xff;

    RS_HIGH;
    WR_HIGH;
    P8_LCD_busout(h);
    WR_LOW;
    WR_HIGH;
    P8_LCD_busout(l);
    WR_LOW;
    WR_HIGH;
}

void P8_LCD_cmd(volatile unsigned short index, volatile unsigned short data)
{
    P8_LCD_reg(index);
    P8_LCD_dat(data);
    return;
}

unsigned short P8_LCD_read_dat(volatile unsigned short index)
{
    volatile unsigned short data = 0;
    return data;
}
//--//
