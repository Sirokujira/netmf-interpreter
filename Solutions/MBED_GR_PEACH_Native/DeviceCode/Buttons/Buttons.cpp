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

//--//

BOOL Buttons_Initialize()
{
    NATIVE_PROFILE_PAL_BUTTONS();
    return FALSE;
}

BOOL Buttons_Uninitialize()
{
    NATIVE_PROFILE_PAL_BUTTONS();
    return FALSE;
}

BOOL Buttons_RegisterStateChange( UINT32 ButtonsPressed, UINT32 ButtonsReleased )
{
    NATIVE_PROFILE_PAL_BUTTONS();
    return FALSE;
}

BOOL Buttons_GetNextStateChange( UINT32& ButtonsPressed, UINT32& ButtonsReleased )
{
    NATIVE_PROFILE_PAL_BUTTONS();
    return FALSE;
}

UINT32 Buttons_CurrentState()
{
    NATIVE_PROFILE_PAL_BUTTONS();
    return 0;
}

UINT32 Buttons_HW_To_Hal_Button( UINT32 HW_Buttons )
{
    NATIVE_PROFILE_PAL_BUTTONS();
    return 0;
}

UINT32 Buttons_CurrentHWState()
{
    NATIVE_PROFILE_PAL_BUTTONS();
    return 0;
}

