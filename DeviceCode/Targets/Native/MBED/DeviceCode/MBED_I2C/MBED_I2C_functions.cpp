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
#include "..\MBED.h"

UINT32 ch = 1;

BOOL I2C_Internal_Initialize()
{
    return MBED_I2C_Driver::Initialize(ch);
}

BOOL I2C_Internal_Uninitialize()
{
    return MBED_I2C_Driver::Uninitialize(ch);
}

void I2C_Internal_XActionStart(I2C_HAL_XACTION* xAction, bool repeatedStart)
{
    MBED_I2C_Driver::MasterXAction_Start(ch, xAction, repeatedStart);
}

void I2C_Internal_XActionStop()
{
    MBED_I2C_Driver::MasterXAction_Stop(ch);
}

void I2C_Internal_GetClockRate(UINT32 rateKhz, UINT8& clockRate, UINT8& clockRate2)
{
    MBED_I2C_Driver::GetClockRate(ch, rateKhz, clockRate, clockRate2);
}

void I2C_Internal_GetPins(GPIO_PIN& scl, GPIO_PIN& sda)
{
    return MBED_I2C_Driver::GetPins(ch, scl, sda);
}
