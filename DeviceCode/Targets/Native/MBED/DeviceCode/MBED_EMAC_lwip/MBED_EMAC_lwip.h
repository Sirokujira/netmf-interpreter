////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#ifndef MBED_EMAC_LWIP_H_
#define MBED_EMAC_LWIP_H_

#include <tinyhal.h>

//#define HW_INTERRUPT            // handle in interrupt routine. completion API not used.
#define MBED_ETHER_PRIORITY 1    // Ethernet interrupt priority

extern NETWORK_CONFIG g_NetworkConfig;
extern INT32 PHY_AutoNegotiate(void);
extern void ETH0_IRQHandler(void* param) __attribute__((interrupt));

#endif /* MBED_EMAC_LWIP_H_ */
