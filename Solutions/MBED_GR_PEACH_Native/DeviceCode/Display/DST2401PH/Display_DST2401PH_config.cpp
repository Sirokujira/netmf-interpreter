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

#include "..\..\..\..\DeviceCode\Drivers\Display\ILI9325_P8\ILI9325_P8.h"

ILI9325_P8_CONFIG g_ILI9325_P8_Config = {
    240,    // UINT16 Width;
    320,    // UINT16 Height;
    16,     // UINT16 BitsPerPixel;
    0xffff, // UINT16 fcol;
    0x0000, // UINT16 bcol;

    0,      // UINT16 TextSx;
    0,      // UINT16 TextSy;
};

#if 0
#include "..\..\..\..\DeviceCode\Drivers\Display\R61580\R61580.h"

R61580_CONFIG g_R61580_Config = {
    240,    // UINT16 Width;
    320,    // UINT16 Height;
    16,     // UINT16 BitsPerPixel;
    0xffff, // UINT16 fcol;
    0x0000, // UINT16 bcol;

    0,      // UINT16 TextSx;
    0,      // UINT16 TextSy;
};

#include "..\..\..\..\DeviceCode\Drivers\Display\ILI9325\ILI9325.h"

ILI9325_CONFIG g_ILI9325_Config = {
    240,    // UINT16 Width;
    320,    // UINT16 Height;
    16,     // UINT16 BitsPerPixel;
    0xffff, // UINT16 fcol;
    0x0000, // UINT16 bcol;

    0,      // UINT16 TextSx;
    0,      // UINT16 TextSy;
};
#endif
//--//

