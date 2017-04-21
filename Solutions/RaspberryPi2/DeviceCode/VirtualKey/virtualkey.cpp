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

GPIO_PIN VirtualKey_GetPins(UINT32 virtualKey)
{
    GPIO_PIN pin;
    switch (virtualKey)
    {
#if 0
    case VK_MENU:
        pin = RZA1_GPIO::P67;
        break;
    case VK_SELECT:
        pin = RZA1_GPIO::P66;
        break;
    case VK_LEFT:
        pin = RZA1_GPIO::P45;	// IRQ13-B
        break;
    case VK_RIGHT:
        pin = RZA1_GPIO::P44;	// IRQ12
        break;
    case VK_UP:
        pin = RZA1_GPIO::P47;	// IRQ15-B
        break;
    case VK_DOWN:
        pin = RZA1_GPIO::P46;	// IRQ14
        break;
    case VK_HOME:
        pin = RZA1_GPIO::PF6;
        break;
    case VK_BACK:
        pin = RZA1_GPIO::PF5;
        break;
#endif
    default:
        pin = GPIO_PIN_NONE;
        break;
    }
    return pin;
}
