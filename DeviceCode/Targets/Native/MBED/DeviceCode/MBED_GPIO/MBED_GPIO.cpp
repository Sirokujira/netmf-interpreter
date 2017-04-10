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
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "mbed.h"

#define DEBUG_GPIO

#define PIN_MAX (16*12)
#define DEFAULT_GPIO_ATTRIBUTE  (GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT)
#define MIN_DEBOUNCETIMEMS  1       // 1ms
#define MAX_DEBOUNCETIMEMS  5000    // 5s

gpio_t mbed_gpio[PIN_MAX];
gpio_irq_t mbed_gpio_irq[PIN_MAX];
void *mbed_gpio_irq_param[PIN_MAX];
GPIO_INTERRUPT_SERVICE_ROUTINE mbed_gpio_isr[PIN_MAX];
UINT8 mbed_gpio_irq_status[PIN_MAX];
UINT8 m_GPIO_Reserved[PIN_MAX];
UINT32 m_DebounceTicks;

//IRQ_NONE,
//IRQ_RISE,
//IRQ_FALL

//GPIO_INT_NONE       = 0,
//GPIO_INT_EDGE_LOW   = 1,
//GPIO_INT_EDGE_HIGH  = 2,
//GPIO_INT_EDGE_BOTH  = 3,
//GPIO_INT_LEVEL_HIGH = 4,
//GPIO_INT_LEVEL_LOW  = 5

void GPIO_Handler(UINT32 id, gpio_irq_event event)
{
    BOOL PinState;
    gpio_irq_t *gpio_irq = (gpio_irq_t *)id;
    UINT32 pin = gpio_irq->pin;
    if (event == IRQ_FALL)
        PinState = FALSE;
    if (event == IRQ_RISE)
        PinState = TRUE;
    if (mbed_gpio_isr != NULL) {
        (*mbed_gpio_isr[pin])(pin, PinState, (void *)mbed_gpio_irq_param[pin]);
    }
#if defined(DEBUG_GPIO)
    // dbg_printf("EV %d\r\n", (UINT32)event);
#endif
}

#if 0
static void GPIO_HandlerByPin(GPIO_PIN Pin, UINT32 id, gpio_irq_event event)
{
    BOOL PinState;
    if (event == IRQ_FALL)
        PinState = false;
    if (event == IRQ_RISE)
        PinState = TRUE;
    if (gpio_isr != NULL) {
        (*mbed_gpio_isr[(UINT32)Pin])(Pin, PinState, (void *)id);
    }
}

static void GPIO_Hander_00(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x00, id, event); }
static void GPIO_Hander_01(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x01, id, event); }
static void GPIO_Hander_02(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x02, id, event); }
static void GPIO_Hander_03(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x03, id, event); }
static void GPIO_Hander_04(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x04, id, event); }
static void GPIO_Hander_05(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x05, id, event); }
static void GPIO_Hander_06(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x06, id, event); }
static void GPIO_Hander_07(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x07, id, event); }
static void GPIO_Hander_08(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x08, id, event); }
static void GPIO_Hander_09(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x09, id, event); }
static void GPIO_Hander_0a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x0a, id, event); }
static void GPIO_Hander_0b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x0b, id, event); }
static void GPIO_Hander_0c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x0c, id, event); }
static void GPIO_Hander_0d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x0d, id, event); }
static void GPIO_Hander_0e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x0e, id, event); }
static void GPIO_Hander_0f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x0f, id, event); }

static void GPIO_Hander_10(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x10, id, event); }
static void GPIO_Hander_11(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x11, id, event); }
static void GPIO_Hander_12(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x12, id, event); }
static void GPIO_Hander_13(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x13, id, event); }
static void GPIO_Hander_14(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x14, id, event); }
static void GPIO_Hander_15(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x15, id, event); }
static void GPIO_Hander_16(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x16, id, event); }
static void GPIO_Hander_17(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x17, id, event); }
static void GPIO_Hander_18(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x18, id, event); }
static void GPIO_Hander_19(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x19, id, event); }
static void GPIO_Hander_1a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x1a, id, event); }
static void GPIO_Hander_1b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x1b, id, event); }
static void GPIO_Hander_1c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x1c, id, event); }
static void GPIO_Hander_1d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x1d, id, event); }
static void GPIO_Hander_1e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x1e, id, event); }
static void GPIO_Hander_1f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x1f, id, event); }

static void GPIO_Hander_20(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x20, id, event); }
static void GPIO_Hander_21(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x21, id, event); }
static void GPIO_Hander_22(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x22, id, event); }
static void GPIO_Hander_23(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x23, id, event); }
static void GPIO_Hander_24(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x24, id, event); }
static void GPIO_Hander_25(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x25, id, event); }
static void GPIO_Hander_26(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x26, id, event); }
static void GPIO_Hander_27(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x27, id, event); }
static void GPIO_Hander_28(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x28, id, event); }
static void GPIO_Hander_29(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x29, id, event); }
static void GPIO_Hander_2a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x2a, id, event); }
static void GPIO_Hander_2b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x2b, id, event); }
static void GPIO_Hander_2c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x2c, id, event); }
static void GPIO_Hander_2d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x2d, id, event); }
static void GPIO_Hander_2e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x2e, id, event); }
static void GPIO_Hander_2f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x2f, id, event); }

static void GPIO_Hander_30(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x30, id, event); }
static void GPIO_Hander_31(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x31, id, event); }
static void GPIO_Hander_32(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x32, id, event); }
static void GPIO_Hander_33(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x33, id, event); }
static void GPIO_Hander_34(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x34, id, event); }
static void GPIO_Hander_35(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x35, id, event); }
static void GPIO_Hander_36(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x36, id, event); }
static void GPIO_Hander_37(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x37, id, event); }
static void GPIO_Hander_38(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x38, id, event); }
static void GPIO_Hander_39(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x39, id, event); }
static void GPIO_Hander_3a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x3a, id, event); }
static void GPIO_Hander_3b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x3b, id, event); }
static void GPIO_Hander_3c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x3c, id, event); }
static void GPIO_Hander_3d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x3d, id, event); }
static void GPIO_Hander_3e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x3e, id, event); }
static void GPIO_Hander_3f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x3f, id, event); }

static void GPIO_Hander_40(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x40, id, event); }
static void GPIO_Hander_41(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x41, id, event); }
static void GPIO_Hander_42(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x42, id, event); }
static void GPIO_Hander_43(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x43, id, event); }
static void GPIO_Hander_44(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x44, id, event); }
static void GPIO_Hander_45(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x45, id, event); }
static void GPIO_Hander_46(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x46, id, event); }
static void GPIO_Hander_47(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x47, id, event); }
static void GPIO_Hander_48(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x48, id, event); }
static void GPIO_Hander_49(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x49, id, event); }
static void GPIO_Hander_4a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x4a, id, event); }
static void GPIO_Hander_4b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x4b, id, event); }
static void GPIO_Hander_4c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x4c, id, event); }
static void GPIO_Hander_4d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x4d, id, event); }
static void GPIO_Hander_4e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x4e, id, event); }
static void GPIO_Hander_4f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x4f, id, event); }

static void GPIO_Hander_50(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x50, id, event); }
static void GPIO_Hander_51(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x51, id, event); }
static void GPIO_Hander_52(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x52, id, event); }
static void GPIO_Hander_53(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x53, id, event); }
static void GPIO_Hander_54(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x54, id, event); }
static void GPIO_Hander_55(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x55, id, event); }
static void GPIO_Hander_56(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x56, id, event); }
static void GPIO_Hander_57(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x57, id, event); }
static void GPIO_Hander_58(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x58, id, event); }
static void GPIO_Hander_59(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x59, id, event); }
static void GPIO_Hander_5a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x5a, id, event); }
static void GPIO_Hander_5b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x5b, id, event); }
static void GPIO_Hander_5c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x5c, id, event); }
static void GPIO_Hander_5d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x5d, id, event); }
static void GPIO_Hander_5e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x5e, id, event); }
static void GPIO_Hander_5f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x5f, id, event); }

static void GPIO_Hander_60(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x60, id, event); }
static void GPIO_Hander_61(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x61, id, event); }
static void GPIO_Hander_62(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x62, id, event); }
static void GPIO_Hander_63(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x63, id, event); }
static void GPIO_Hander_64(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x64, id, event); }
static void GPIO_Hander_65(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x65, id, event); }
static void GPIO_Hander_66(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x66, id, event); }
static void GPIO_Hander_67(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x67, id, event); }
static void GPIO_Hander_68(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x68, id, event); }
static void GPIO_Hander_69(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x69, id, event); }
static void GPIO_Hander_6a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x6a, id, event); }
static void GPIO_Hander_6b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x6b, id, event); }
static void GPIO_Hander_6c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x6c, id, event); }
static void GPIO_Hander_6d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x6d, id, event); }
static void GPIO_Hander_6e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x6e, id, event); }
static void GPIO_Hander_6f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x6f, id, event); }

static void GPIO_Hander_70(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x70, id, event); }
static void GPIO_Hander_71(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x71, id, event); }
static void GPIO_Hander_72(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x72, id, event); }
static void GPIO_Hander_73(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x73, id, event); }
static void GPIO_Hander_74(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x74, id, event); }
static void GPIO_Hander_75(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x75, id, event); }
static void GPIO_Hander_76(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x76, id, event); }
static void GPIO_Hander_77(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x77, id, event); }
static void GPIO_Hander_78(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x78, id, event); }
static void GPIO_Hander_79(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x79, id, event); }
static void GPIO_Hander_7a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x7a, id, event); }
static void GPIO_Hander_7b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x7b, id, event); }
static void GPIO_Hander_7c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x7c, id, event); }
static void GPIO_Hander_7d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x7d, id, event); }
static void GPIO_Hander_7e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x7e, id, event); }
static void GPIO_Hander_7f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x7f, id, event); }

static void GPIO_Hander_80(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x80, id, event); }
static void GPIO_Hander_81(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x81, id, event); }
static void GPIO_Hander_82(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x82, id, event); }
static void GPIO_Hander_83(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x83, id, event); }
static void GPIO_Hander_84(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x84, id, event); }
static void GPIO_Hander_85(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x85, id, event); }
static void GPIO_Hander_86(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x86, id, event); }
static void GPIO_Hander_87(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x87, id, event); }
static void GPIO_Hander_88(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x88, id, event); }
static void GPIO_Hander_89(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x89, id, event); }
static void GPIO_Hander_8a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x8a, id, event); }
static void GPIO_Hander_8b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x8b, id, event); }
static void GPIO_Hander_8c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x8c, id, event); }
static void GPIO_Hander_8d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x8d, id, event); }
static void GPIO_Hander_8e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x8e, id, event); }
static void GPIO_Hander_8f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x8f, id, event); }

static void GPIO_Hander_90(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x90, id, event); }
static void GPIO_Hander_91(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x91, id, event); }
static void GPIO_Hander_92(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x92, id, event); }
static void GPIO_Hander_93(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x93, id, event); }
static void GPIO_Hander_94(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x94, id, event); }
static void GPIO_Hander_95(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x95, id, event); }
static void GPIO_Hander_96(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x96, id, event); }
static void GPIO_Hander_97(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x97, id, event); }
static void GPIO_Hander_98(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x98, id, event); }
static void GPIO_Hander_99(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x99, id, event); }
static void GPIO_Hander_9a(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x9a, id, event); }
static void GPIO_Hander_9b(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x9b, id, event); }
static void GPIO_Hander_9c(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x9c, id, event); }
static void GPIO_Hander_9d(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x9d, id, event); }
static void GPIO_Hander_9e(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x9e, id, event); }
static void GPIO_Hander_9f(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0x9f, id, event); }

static void GPIO_Hander_a0(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa0, id, event); }
static void GPIO_Hander_a1(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa1, id, event); }
static void GPIO_Hander_a2(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa2, id, event); }
static void GPIO_Hander_a3(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa3, id, event); }
static void GPIO_Hander_a4(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa4, id, event); }
static void GPIO_Hander_a5(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa5, id, event); }
static void GPIO_Hander_a6(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa6, id, event); }
static void GPIO_Hander_a7(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa7, id, event); }
static void GPIO_Hander_a8(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa8, id, event); }
static void GPIO_Hander_a9(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xa9, id, event); }
static void GPIO_Hander_aa(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xaa, id, event); }
static void GPIO_Hander_ab(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xab, id, event); }
static void GPIO_Hander_ac(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xac, id, event); }
static void GPIO_Hander_ad(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xad, id, event); }
static void GPIO_Hander_ae(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xae, id, event); }
static void GPIO_Hander_af(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xaf, id, event); }

static void GPIO_Hander_b0(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb0, id, event); }
static void GPIO_Hander_b1(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb1, id, event); }
static void GPIO_Hander_b2(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb2, id, event); }
static void GPIO_Hander_b3(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb3, id, event); }
static void GPIO_Hander_b4(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb4, id, event); }
static void GPIO_Hander_b5(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb5, id, event); }
static void GPIO_Hander_b6(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb6, id, event); }
static void GPIO_Hander_b7(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb7, id, event); }
static void GPIO_Hander_b8(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb8, id, event); }
static void GPIO_Hander_b9(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xb9, id, event); }
static void GPIO_Hander_ba(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xba, id, event); }
static void GPIO_Hander_bb(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xbb, id, event); }
static void GPIO_Hander_bc(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xbc, id, event); }
static void GPIO_Hander_bd(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xbd, id, event); }
static void GPIO_Hander_be(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xbe, id, event); }
static void GPIO_Hander_bf(UINT32 id, gpio_irq_event event) { GPIO_HandlerByPin((GPIO_PIN)0xbf, id, event); }

gpio_irq_handler GPIO_Handler[] =
{
GPIO_Hander_00,
GPIO_Hander_01,
GPIO_Hander_02,
GPIO_Hander_03,
GPIO_Hander_04,
GPIO_Hander_05,
GPIO_Hander_06,
GPIO_Hander_07,
GPIO_Hander_08,
GPIO_Hander_09,
GPIO_Hander_0a,
GPIO_Hander_0b,
GPIO_Hander_0c,
GPIO_Hander_0d,
GPIO_Hander_0e,
GPIO_Hander_0f,

GPIO_Hander_10,
GPIO_Hander_11,
GPIO_Hander_12,
GPIO_Hander_13,
GPIO_Hander_14,
GPIO_Hander_15,
GPIO_Hander_16,
GPIO_Hander_17,
GPIO_Hander_18,
GPIO_Hander_19,
GPIO_Hander_1a,
GPIO_Hander_1b,
GPIO_Hander_1c,
GPIO_Hander_1d,
GPIO_Hander_1e,
GPIO_Hander_1f,

GPIO_Hander_20,
GPIO_Hander_21,
GPIO_Hander_22,
GPIO_Hander_23,
GPIO_Hander_24,
GPIO_Hander_25,
GPIO_Hander_26,
GPIO_Hander_27,
GPIO_Hander_28,
GPIO_Hander_29,
GPIO_Hander_2a,
GPIO_Hander_2b,
GPIO_Hander_2c,
GPIO_Hander_2d,
GPIO_Hander_2e,
GPIO_Hander_2f,

GPIO_Hander_30,
GPIO_Hander_31,
GPIO_Hander_32,
GPIO_Hander_33,
GPIO_Hander_34,
GPIO_Hander_35,
GPIO_Hander_36,
GPIO_Hander_37,
GPIO_Hander_38,
GPIO_Hander_39,
GPIO_Hander_3a,
GPIO_Hander_3b,
GPIO_Hander_3c,
GPIO_Hander_3d,
GPIO_Hander_3e,
GPIO_Hander_3f,

GPIO_Hander_40,
GPIO_Hander_41,
GPIO_Hander_42,
GPIO_Hander_43,
GPIO_Hander_44,
GPIO_Hander_45,
GPIO_Hander_46,
GPIO_Hander_47,
GPIO_Hander_48,
GPIO_Hander_49,
GPIO_Hander_4a,
GPIO_Hander_4b,
GPIO_Hander_4c,
GPIO_Hander_4d,
GPIO_Hander_4e,
GPIO_Hander_4f,

GPIO_Hander_50,
GPIO_Hander_51,
GPIO_Hander_52,
GPIO_Hander_53,
GPIO_Hander_54,
GPIO_Hander_55,
GPIO_Hander_56,
GPIO_Hander_57,
GPIO_Hander_58,
GPIO_Hander_59,
GPIO_Hander_5a,
GPIO_Hander_5b,
GPIO_Hander_5c,
GPIO_Hander_5d,
GPIO_Hander_5e,
GPIO_Hander_5f,

GPIO_Hander_60,
GPIO_Hander_61,
GPIO_Hander_62,
GPIO_Hander_63,
GPIO_Hander_64,
GPIO_Hander_65,
GPIO_Hander_66,
GPIO_Hander_67,
GPIO_Hander_68,
GPIO_Hander_69,
GPIO_Hander_6a,
GPIO_Hander_6b,
GPIO_Hander_6c,
GPIO_Hander_6d,
GPIO_Hander_6e,
GPIO_Hander_6f,

GPIO_Hander_70,
GPIO_Hander_71,
GPIO_Hander_72,
GPIO_Hander_73,
GPIO_Hander_74,
GPIO_Hander_75,
GPIO_Hander_76,
GPIO_Hander_77,
GPIO_Hander_78,
GPIO_Hander_79,
GPIO_Hander_7a,
GPIO_Hander_7b,
GPIO_Hander_7c,
GPIO_Hander_7d,
GPIO_Hander_7e,
GPIO_Hander_7f,

GPIO_Hander_80,
GPIO_Hander_81,
GPIO_Hander_82,
GPIO_Hander_83,
GPIO_Hander_84,
GPIO_Hander_85,
GPIO_Hander_86,
GPIO_Hander_87,
GPIO_Hander_88,
GPIO_Hander_89,
GPIO_Hander_8a,
GPIO_Hander_8b,
GPIO_Hander_8c,
GPIO_Hander_8d,
GPIO_Hander_8e,
GPIO_Hander_8f,

GPIO_Hander_90,
GPIO_Hander_91,
GPIO_Hander_92,
GPIO_Hander_93,
GPIO_Hander_94,
GPIO_Hander_95,
GPIO_Hander_96,
GPIO_Hander_97,
GPIO_Hander_98,
GPIO_Hander_99,
GPIO_Hander_9a,
GPIO_Hander_9b,
GPIO_Hander_9c,
GPIO_Hander_9d,
GPIO_Hander_9e,
GPIO_Hander_9f,

GPIO_Hander_a0,
GPIO_Hander_a1,
GPIO_Hander_a2,
GPIO_Hander_a3,
GPIO_Hander_a4,
GPIO_Hander_a5,
GPIO_Hander_a6,
GPIO_Hander_a7,
GPIO_Hander_a8,
GPIO_Hander_a9,
GPIO_Hander_aa,
GPIO_Hander_ab,
GPIO_Hander_ac,
GPIO_Hander_ad,
GPIO_Hander_ae,
GPIO_Hander_af,

GPIO_Hander_b0,
GPIO_Hander_b1,
GPIO_Hander_b2,
GPIO_Hander_b3,
GPIO_Hander_b4,
GPIO_Hander_b5,
GPIO_Hander_b6,
GPIO_Hander_b7,
GPIO_Hander_b8,
GPIO_Hander_b9,
GPIO_Hander_ba,
GPIO_Hander_bb,
GPIO_Hander_bc,
GPIO_Hander_bd,
GPIO_Hander_be,
GPIO_Hander_bf
};
#endif

BOOL CPU_GPIO_Initialize()
{
    UINT32 i;
    for (i = 0; i < PIN_MAX; i++) {
        //gpio_init(&mbed_gpio[i], (PinName)i);
        mbed_gpio_irq_param[i] = (void *)NULL;
        mbed_gpio_isr[i] = (GPIO_INTERRUPT_SERVICE_ROUTINE)NULL;
        mbed_gpio_irq_status[i] = 0;
    }
    return TRUE;
}

BOOL CPU_GPIO_Uninitialize()
{
    UINT32 i;
    for (i = 0; i < PIN_MAX; i++) {
        mbed_gpio_irq_param[i] = (void *)NULL;
        if (mbed_gpio_irq_status[i]) {
            gpio_irq_disable(&mbed_gpio_irq[i]);
            gpio_irq_free(&mbed_gpio_irq[i]);
        }
    }
    return TRUE;
}

UINT32 CPU_GPIO_Attributes(GPIO_PIN Pin)
{
    if ((PinName)Pin != NC) {
        return (GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT);
    } else {
        return GPIO_ATTRIBUTE_NONE;
    }
}

void CPU_GPIO_DisablePin(GPIO_PIN Pin, GPIO_RESISTOR ResistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction)
{
}

void CPU_GPIO_EnableOutputPin(GPIO_PIN Pin, BOOL InitialState)
{
    gpio_t *obj;
    if ((PinName)Pin != NC) {
        obj = &mbed_gpio[(int)Pin];
        gpio_init(obj, (PinName)Pin);
        gpio_write(obj, InitialState);
        gpio_dir(obj, PIN_OUTPUT);
        //gpio_mode(obj, 0);
    }
}

BOOL CPU_GPIO_EnableInputPin(GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState)
{
    CPU_GPIO_EnableInputPin2(Pin, GlitchFilterEnable, ISR, (void*)NULL, IntEdge, ResistorState);
}

BOOL CPU_GPIO_EnableInputPin2(GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, void* ISR_Param, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState)
{
    gpio_t *obj;
    gpio_irq_t *gpio_irq;
    gpio_irq_event event;
    int ret;

    if ((PinName)Pin != NC) {
        obj = (gpio_t *)&mbed_gpio[(int)Pin];
        gpio_init(obj, (PinName)Pin);
        gpio_dir(obj, PIN_INPUT);
        //gpio_mode(obj, 0);
        if (ISR != NULL) {
            gpio_irq = (gpio_irq_t *)&mbed_gpio_irq[(int)Pin];
            ret = gpio_irq_init(gpio_irq, (PinName)Pin, (gpio_irq_handler)GPIO_Handler, (UINT32)gpio_irq);
            if (ret < 0)
                return FALSE;
            mbed_gpio_isr[Pin] = (GPIO_INTERRUPT_SERVICE_ROUTINE)ISR;
            mbed_gpio_irq_param[Pin] = ISR_Param;
            switch (IntEdge) {
            case GPIO_INT_EDGE_LOW:
            case GPIO_INT_LEVEL_LOW:
                gpio_irq_set(gpio_irq, IRQ_FALL, 1);
                break;
            case GPIO_INT_EDGE_HIGH:
            case GPIO_INT_LEVEL_HIGH:
                gpio_irq_set(gpio_irq, IRQ_RISE, 1);
                break;
            case GPIO_INT_EDGE_BOTH:
                gpio_irq_set(gpio_irq, IRQ_FALL, 1);
                gpio_irq_set(gpio_irq, IRQ_RISE, 1);
                break;
            default:
                break;
            }
        }
        return TRUE;
    } else
        return FALSE;
}

BOOL CPU_GPIO_GetPinState(GPIO_PIN Pin)
{
    gpio_t *obj;
    if ((PinName)Pin != NC) {
        obj = &mbed_gpio[(int)Pin];
        return (gpio_read(obj) != 0);
    } else
        return FALSE;
}

void CPU_GPIO_SetPinState(GPIO_PIN Pin, BOOL PinState)
{
    gpio_t *obj;
    if ((PinName)Pin != NC) {
        obj = &mbed_gpio[(int)Pin];
        gpio_write(obj, PinState);
    }
}

INT32 CPU_GPIO_GetPinCount()
{
    return PIN_MAX; // dummy
}

void CPU_GPIO_GetPinsMap(UINT8* pins, size_t size)
{
    int i;
    GPIO_PIN pin;
    for (pin = (GPIO_PIN)0; pin < (GPIO_PIN)PIN_MAX; pin++) {
        if (size-- == 0)
            break;
        *pins++ = (UINT8)DEFAULT_GPIO_ATTRIBUTE;
    }
}

UINT8 CPU_GPIO_GetSupportedResistorModes(GPIO_PIN pin)
{
    return (1 << RESISTOR_DISABLED) | (1 << RESISTOR_PULLUP);   // RESISTOR_PULLUP is dummy configuration
}

UINT8 CPU_GPIO_GetSupportedInterruptModes(GPIO_PIN pin)
{
    return (1 << GPIO_INT_EDGE_LOW) |
           (1 << GPIO_INT_EDGE_HIGH ) |
           (1 << GPIO_INT_EDGE_BOTH);
}

BOOL CPU_GPIO_PinIsBusy(GPIO_PIN Pin)
{
    if ((UINT32)Pin >= PIN_MAX)
        return TRUE;
    return m_GPIO_Reserved[Pin];
}

BOOL CPU_GPIO_ReservePin(GPIO_PIN Pin, BOOL fReserve)
{
    if ((UINT32)Pin >= PIN_MAX)
        return FALSE;
    m_GPIO_Reserved[Pin] = fReserve;
    return TRUE;
}

UINT32 CPU_GPIO_GetDebounce()
{
    return CPU_TicksToTime(m_DebounceTicks) / 10000;
}

BOOL CPU_GPIO_SetDebounce(INT64 debounceTimeMilliseconds)
{
    if (debounceTimeMilliseconds < MIN_DEBOUNCETIMEMS || MAX_DEBOUNCETIMEMS < debounceTimeMilliseconds)
        return false;
    m_DebounceTicks = CPU_MillisecondsToTicks((UINT32)debounceTimeMilliseconds);
    return TRUE;
}
