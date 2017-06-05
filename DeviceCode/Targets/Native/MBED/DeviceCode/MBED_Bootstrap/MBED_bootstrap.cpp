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

///////////////////////////////////////////////////////////////////////////////
// MBED clock configuration
//
///////////////////////////////////////////////////////////////////////////////

#pragma arm section code = "SectionForBootstrapOperations"

#ifdef __cplusplus
extern "C" {
#endif
    void HardwareSetup(void);
    void BootstrapCode_Board(void);
    void BootstrapCode();
#ifdef __cplusplus
}
#endif

/* Board specific initialization implemented in solution DeviceCode\Bootstrap */

extern "C"
{
	void __section("SectionForBootstrapOperations") BootstrapCode_CPU()
	{
	    //HardwareSetup();
	}

	void __section("SectionForBootstrapOperations") BootstrapCode()
	{
	    BootstrapCode_CPU();
	    BootstrapCode_Board();
	    PrepareImageRegions();
	}
}
