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

#ifdef TEST_BUTTON
void TestButton(void)
{
    UINT32 ButtonsPressed = 0;
    UINT32 ButtonsReleased = 0;
    Buttons_Initialize();
    while (true) {
        UINT32 Events = Events_WaitForEvents(SYSTEM_EVENT_FLAG_BUTTON, 200);
        if (Events & SYSTEM_EVENT_FLAG_BUTTON) {
            Events_Clear(SYSTEM_EVENT_FLAG_BUTTON);
            while (Buttons_GetNextStateChange(ButtonsPressed, ButtonsReleased))
                ;
            if (ButtonsPressed)
                lcd_printf("ButtonPressed = 0x%08d.\r\n", ButtonsPressed);
            if (ButtonsReleased)
                lcd_printf("ButtonReleased = 0x%08d.\r\n", ButtonsReleased);
            if (ButtonsReleased & BUTTON_B0) {
                lcd_printf("Exiting\r\n");
                break;
            }
        }
    }
    Buttons_Uninitialize();
}
#endif
