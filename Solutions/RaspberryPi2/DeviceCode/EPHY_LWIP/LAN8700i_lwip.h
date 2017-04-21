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

#ifndef _LAN8700i_LWIP_H_
#define _LAN8700i_LWIP_H_ 1

#define PHY_REG_BMCR	0x00        // Basic Mode Control Register
#define PHY_REG_BMSR    0x01        // Basic Mode Status Register
#define PHY_REG_IDR1    0x02        // PHY Identifier 1
#define PHY_REG_IDR2    0x03        // PHY Identifier 2
#define PHY_REG_STS    	0x10        // Status Register

#define BMCR_RESET     	0x8000
#define BMSR_AUTO_DONE  0x0020

#define PHY_AUTO_NEG    0x3000     	// Select Auto Negotiation

#define STS_LINK_ON    	0x1
#define STS_10_MBIT    	0x2
#define STS_FULL_DUP    0x4

#define MII_WR_TOUT    	1000    // MII Write timeout count
#define MII_RD_TOUT    	1000    // MII Read timeout count

#define LAN8720A_DEF_ADDR   0x00	// Default PHY device address
#define LAN8720A_ID 0x0007C0C0  // PHY Identifier

#endif
