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

//--//

void HAL_AssertEx()
{
    // ToDo
    //hal_printf("\f=== HAL_AssertEx() ===\r\n");
    //while (true);
}

//--//

BOOL CPU_Initialize()
{
    // ToDo
    return true;
}

void CPU_Reset()
{
    // ToDo
}

void CPU_Sleep(SLEEP_LEVEL level, UINT64 wakeEvents)
{
    // ToDo
#if 0
    switch (level)
    {
    case SLEEP_LEVEL__AWAKE:            // 0x00
    case SLEEP_LEVEL__SELECTIVE_OFF:    // 0x10
    case SLEEP_LEVEL__SLEEP:            // 0x20
    case SLEEP_LEVEL__DEEP_SLEEP:       // 0x30
    case SLEEP_LEVEL__OFF:              // 0x40
        break;
    default:
        break;
    }
    __asm("wait");
#endif
}

void CPU_ChangePowerLevel(POWER_LEVEL level)
{
    // ToDo
}

BOOL CPU_IsSoftRebootSupported ()
{
    // ToDo
    return true;
}

void CPU_Halt()
{
    // ToDo
    while (true);
}
