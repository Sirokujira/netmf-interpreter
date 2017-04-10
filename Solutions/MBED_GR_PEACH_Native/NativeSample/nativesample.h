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

//-- Stream --//
#define	STREAM__OUT	STREAM__SERIAL

//--  RamTest --//
#define	BUS_WIDTH	0x00008000
#define	RAMTestBase	0x08400000
#define	RAMTestSize	0x00010000
#define	ENDIANESS	LE_ENDIAN

//--  Serial Port  --//
#define	COMTestPort	COM1

//-- GPIO --//
#define	GPIOTestPin	RX62N_GPIO::P15

//-- SPI --//
#define	SPIChipSelect	GPIO_PIN_NONE
#define	SPIModule		GPIO_PIN_NONE

//-- Timer --//
#define	DisplayInterval	5
#define	TimerDuration	30

//--//

