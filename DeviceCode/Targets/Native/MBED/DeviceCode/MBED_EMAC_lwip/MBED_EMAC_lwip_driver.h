////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#ifndef MBED_EMAC_LWIP_DRIVER_H_
#define MBED_EMAC_LWIP_DRIVER_H_

#include <tinyhal.h>
#include "net_decl_lwip.h"
#include "lwip\dhcp.h"

#define MBED_EMAC_MAX_FRAME_SIZE 1536
#define UPTIME_PERIOD   1000000L         // 1sec
#define INT_PERIOD      10000L           // 5ms

struct MBED_EMAC_LWIP_DRIVER_CONFIG
{
    GPIO_PIN    PHY_PD_GPIO_Pin;    // phy power down control
};

struct MBED_EMAC_LWIP_Driver
{
    struct dhcp m_currentDhcpSession;
    static int Open(int);
    static BOOL Close(void);
    static BOOL Bind(void );
};

BOOL MBED_EMAC_LWIP_Init(struct netif *pNetIf);
BOOL MBED_EMAC_LWIP_open(struct netif *pNetIf);
void MBED_EMAC_LWIP_close(struct netif *pNetIf);
void MBED_EMAC_LWIP_interrupt(struct netif *pNetIf);
err_t MBED_EMAC_LWIP_xmit(struct netif *pNetIf, struct pbuf *pPBuf);
void MBED_EMAC_LWIP_recv (struct netif *pNetIf);
void MBED_EMAC_interrupt(void *param);
BOOL MBED_EMAC_LWIP_GetLinkStatus(void);
BOOL MBED_EMAC_LWIP_AutoNegotiate(void);

#endif /* MBED_EMAC_LWIP_DRIVER_H_ */
