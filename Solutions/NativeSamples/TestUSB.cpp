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

#ifdef TEST_USB
#include <pal\com\usb\USB.h>

static char wStr[] = "FM3 USB\n";

#if 1
#define BUF_SIZE 100
char key[BUF_SIZE];

void TestUSB()
{
    BOOL state = TRUE;
    GPIO_PIN pin = (GPIO_PIN)0xF3;
    CPU_GPIO_EnableOutputPin(pin, state);
    int controller = 0;
    if (USB_CONFIG_ERR_OK == USB_Configure(controller, NULL)) {
        BOOL flag = USB_Initialize(controller);
        debug_printf("USB_Initialize flag = %d\r\n", flag);
        flag = USB_OpenStream(controller, USB_DEBUG_EP_WRITE, USB_DEBUG_EP_READ);
        debug_printf("USB_OpenStream flag = %d\r\n", flag);
        wait(20000000);
        int i = 0;
        int ret;
        while (true) {
            hal_printf("Waiting key %d:", i);
            lcd_printf("Waiting key %d:", i);
            UINT32 Events = Events_WaitForEvents(SYSTEM_EVENT_FLAG_USB_IN, 1500);
            if (Events & SYSTEM_EVENT_FLAG_USB_IN) {
                ret = USB_Read(controller, key, BUF_SIZE);
                if (ret <= BUF_SIZE-1)
                    key[ret] = 0;
                else
                    key[BUF_SIZE-1] = 0;
                Events_Clear(SYSTEM_EVENT_FLAG_USB_IN);
                hal_printf("%s\r\n", key);
                lcd_printf("%s\r\n", key);
            } else {
                hal_printf("\r\n");
                lcd_printf("\r\n");
            }
            ret = USB_Write(controller, wStr, sizeof(wStr));
            debug_printf("USB_Write ret = %d\r\n", ret);
            CPU_GPIO_SetPinState(pin, state);
            state ^= 1;
            i++;
        }
    }
}
#endif

#if 0
//#define USB_INIT

void TestUSB(void)
{
    char key[64];
    int i = 0;
    GPIO_PIN pin = (GPIO_PIN)0xF3;
    BOOL state = TRUE;
    CPU_GPIO_EnableOutputPin(pin, state);
    BOOL flag = TRUE;
    int ret;
    int controller = 0;
#ifdef USB_INIT
    if (USB_CONFIG_ERR_OK == USB_Configure(controller, NULL)) {
        flag = USB_Initialize(controller);
        debug_printf("USB_Initialize flag = %d\r\n", flag);
        flag = USB_OpenStream(controller, USB_DEBUG_EP_WRITE, USB_DEBUG_EP_READ);
        debug_printf("USB_OpenStream flag = %d\r\n", flag);
    }
#endif
    DebuggerPort_Initialize(HalSystemConfig.DebuggerPorts[0]);
    if (flag) {
        while (true) {
            CPU_GPIO_SetPinState(pin, state);
//           lcd_printf("Waiting key %d:", i);
            hal_printf("Waiting key %d:", i);
            UINT32 Events = Events_WaitForEvents(SYSTEM_EVENT_FLAG_USB_IN, 3000);
            if (Events & SYSTEM_EVENT_FLAG_USB_IN) {
                Events_Clear(SYSTEM_EVENT_FLAG_USB_IN);
                ret = USB_Read(controller, key, sizeof(key));
//                lcd_printf("%c\r\n", key[0]);
                hal_printf("%c\r\n", key[0]);
            } else {
//                lcd_printf("\r\n");
                hal_printf("\r\n");
            }
            state ^= 1;
            i++;
        }
    }
}
#endif
#endif
