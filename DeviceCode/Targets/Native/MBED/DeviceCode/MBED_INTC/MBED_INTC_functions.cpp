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

//void IRQ_Handler()
//{
    // ToDo
//}

void CPU_INTC_Initialize()
{
    // ToDo
}

BOOL CPU_INTC_ActivateInterrupt(UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param)
{
    // ToDo
    return FALSE;
}

BOOL CPU_INTC_DeactivateInterrupt(UINT32 Irq_Index)
{
    // ToDo
    return FALSE;
}

BOOL CPU_INTC_InterruptEnable(UINT32 Irq_Index)
{
    // ToDo
    return FALSE;
}

BOOL CPU_INTC_InterruptDisable(UINT32 Irq_Index)
{
    // ToDo
    return FALSE;
}

BOOL CPU_INTC_InterruptEnableState(UINT32 Irq_Index)
{
    // ToDo
    return FALSE;
}

BOOL CPU_INTC_InterruptState(UINT32 Irq_Index)
{
    // ToDo
    return FALSE;
}
