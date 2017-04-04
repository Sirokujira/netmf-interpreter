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
#include "..\..\..\DeviceCode\Targets\Native\MBED\DeviceCode\MBED_EMAC_lwip\MBED_EMAC_lwip.h"
#include "..\..\..\DeviceCode\Targets\Native\MBED\DeviceCode\MBED_EMAC_lwip\MBED_EMAC_lwip_driver.h"
#include "LAN8700i_lwip.h"

//#define DEBUG_PHY_LCD

extern void MBED_EDMAC_lwip_SetLinkSpeed(BOOL speed, BOOL fullduplex);

#define ICS1894_ADDR    0x10        // PHY device address for Wakamatsu FM3 LAN board
#define LAN8187_ADDR    0x06        // PHY device address for Wakamatsu ARM LAN board
#define DP83848_ADDR    0x01        // PHY device address for DP83848
#define LAN8700_ADDR    0x1F        // PHY device address for Will Electronics WX-PHY
#define LAN8720_ADDR    0x00        // PHY device address for GR-SAKURA
#define ICS1894_ID      0x0015f450  // PHY Identifier of ICS1894
#define LAN8187_ID      0x0006C0C4  // PHY Identifier of LAN8187
#define DP83848_ID      0x20005C90  // PHY Identifier of DP83848
#define LAN8700_ID      0x0007C0C0  // PHY Identifier of LAN8700i
#define LAN8720_ID      0x0007C0F1  // PHY Identifier of LAN8720A
#define PHY_ADDR        LAN8720_ADDR

// PHY Address
static char PhyAddr[] = {
    LAN8720_ADDR,
    ICS1894_ADDR,
    LAN8187_ADDR,
    DP83848_ADDR,
    LAN8700_ADDR
};
static UINT32 phy_addr = PHY_ADDR;
#define PHY_MAX (sizeof(PhyAddr)/sizeof(char))

static BOOL PhyReset(UINT32 addr)
{
    UINT32 i;
    UINT32 data;
#if 0
    if (!MBED_EDMAC_lwip_WritePhy(addr, PHY_REG_BMCR, BMCR_RESET, MII_WR_TOUT))
        return (FALSE);
    for (i = 0; i < MII_WR_TOUT; i++) {
        if (!MBED_EDMAC_lwip_ReadPhy(addr, PHY_REG_BMCR, &data, MII_RD_TOUT))
            return( FALSE );
        if (!(data & BMCR_RESET))
            return true;
    }
#endif
    return false;
}

static BOOL PhyVerifyId(UINT32 addr)
{
    UINT32 id1,id2;
#if 0
    if (!MBED_EDMAC_lwip_ReadPhy(addr, PHY_REG_IDR1, &id1, MII_RD_TOUT))
        return false;
#if defined(DEBUG_PHY_LCD)
    dbg_printf("PHY: ReadID OK %04x\r\n", id1);
#endif
    if (!MBED_EDMAC_lwip_ReadPhy(addr, PHY_REG_IDR2, &id2, MII_RD_TOUT))
        return false;
#if defined(DEBUG_PHY_LCD)
    dbg_printf("PHY: ReadID OK %04x\r\n", id2);
#endif
#endif
    return true;
}

static BOOL PhyAutoNegotiate(UINT32 addr)
{
    UINT32 i, data;

#if 0
    if (!MBED_EDMAC_lwip_WritePhy(addr, PHY_REG_BMCR, PHY_AUTO_NEG, MII_WR_TOUT))
        return false;
    for (i = 0; i < 10; i++) {
        HAL_Time_Sleep_MicroSeconds(1000000);
        MBED_EDMAC_lwip_ReadPhy(addr, PHY_REG_BMSR, &data, MII_RD_TOUT);
        if (data & BMSR_AUTO_DONE)
            return true;
    }
#endif
    return false;
}

static BOOL PhySetLinkSpeed (UINT32 addr)
{
    UINT32 data;
    BOOL full_duplex, mbit_100;

#if 0
    if (!PhyAutoNegotiate(addr)) {
#if defined(DEBUG_PHY_LCD)
        dbg_printf("Warning: Ethernet PHY Link autonegotiation failure.\r\n");
#endif
        mbit_100 = true;
        full_duplex = true;
    } else {
#if defined(DEBUG_PHY_LCD)
        dbg_printf("PHY: Auto Neg OK\r\n");
#endif
        if (!MBED_EDMAC_lwip_ReadPhy(addr, PHY_REG_BMSR, &data, MII_RD_TOUT))
            return false;
        if (data & STS_FULL_DUP)
            full_duplex = true;
        else
            full_duplex = false;

        if (data & STS_10_MBIT)
            mbit_100 = false;
        else
            mbit_100 = true;
    }
    MBED_EDMAC_lwip_SetLinkSpeed(mbit_100, full_duplex);
#endif
    return true;
}

static BOOL PHY_Find(UINT32 *addr)
{
    UINT32 i;
    for (i = 0; i < PHY_MAX; i++) {
        if (PhyReset((UINT32)PhyAddr[i])) {
            *addr = (UINT32)PhyAddr[i];
            return true;
        }
    }
    return false;
}

BOOL ENET_PHY_lwip_init (void)
{
    phy_addr = PHY_ADDR;
    if (PHY_Find(&phy_addr)) {
#if defined(DEBUG_PHY_LCD)
        dbg_printf("PHY: Find OK id=%02x\r\n", phy_addr);
#endif
    } else {
#if defined(DEBUG_PHY_LCD)
        dbg_printf("PHY: Find NG\r\n");
#endif
        return false;
    }
    if (!PhyReset(phy_addr)) {
#if defined(DEBUG_PHY_LCD)
        dbg_printf("Error: Phy reset\r\n");
#endif
        return false;
    }
    if (!PhyVerifyId(phy_addr)) {
#if defined(DEBUG_PHY_LCD)
        dbg_printf("Error: Invalid Phy Id\r\n");
#endif
        return false;
    }
    if (!PhySetLinkSpeed(phy_addr)) {
#if defined(DEBUG_PHY_LCD)
        dbg_printf("Error: Link speed failure\r\n");
#endif
        return false;
    }
    return true;
}

UINT32 ENET_PHY_lwip_get_MDC_Clk_Div(void)
{
    return 1;
}

BOOL ENET_PHY_lwip_get_MII_mode(void)
{
    return false;
}

BOOL ENET_PHY_lwip_get_link_status(void)
{
    UINT32 data;
    BOOL link_status = false;

#if 0
    if (MBED_EDMAC_lwip_ReadPhy(phy_addr, PHY_REG_STS, &data, MII_RD_TOUT))
        link_status = (data & STS_LINK_ON);
#endif
    return link_status;
}

BOOL ENET_PHY_lwip_set_link_speed(void)
{
    return PhySetLinkSpeed(phy_addr);
}
