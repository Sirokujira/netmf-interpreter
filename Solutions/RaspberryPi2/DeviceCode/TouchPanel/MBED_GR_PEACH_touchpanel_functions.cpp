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

#include "tinyhal.h"
#include "RaspberryPi2_touchpanel_driver.h"

//--//

BOOL TOUCH_PANEL_Driver_Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc)
{
    return RaspberryPi2_TouchPanel_Driver::Initialize(touchIsrProc);
}

BOOL TOUCH_PANEL_Driver_Disable()
{
    return RaspberryPi2_TouchPanel_Driver::Uninitialize();
}

void TOUCH_PANEL_Driver_GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY)
{
    RaspberryPi2_TouchPanel_Driver::GetPoint(pTipState, pSource, pUnCalY, pUnCalX);
}

HRESULT TOUCH_PANEL_Driver_GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
    return RaspberryPi2_TouchPanel_Driver::GetDeviceCaps(iIndex, lpOutput);
}

BOOL HAL_TOUCH_PANEL_Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc)
{
    return TOUCH_PANEL_Driver_Enable(touchIsrProc);
}

BOOL HAL_TOUCH_PANEL_Disable()
{
    return TOUCH_PANEL_Driver_Disable();
}

void HAL_TOUCH_PANEL_GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY)
{
    TOUCH_PANEL_Driver_GetPoint(pTipState, pSource, pUnCalX, pUnCalY);
}

HRESULT HAL_TOUCH_PANEL_GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
    return TOUCH_PANEL_Driver_GetDeviceCaps(iIndex, lpOutput);
}
