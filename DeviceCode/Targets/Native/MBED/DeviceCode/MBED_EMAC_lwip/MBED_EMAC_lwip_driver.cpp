////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "net_decl_lwip.h"
#include "lwip\netif.h"
#include "lwip\tcp.h"
#include "lwip\tcpip.h"
#include "lwip\dhcp.h"
#include "lwip\pbuf.h"
#include "netif\etharp.h"
#include "MBED_EMAC_lwip.h"
#include "MBED_EMAC_lwip_driver.h"
#include "mbed.h"
#include "ethernet_api.h"
#include "lwip/opt.h"

//#define DEBUG_LWIP
//#define DEBUG_MBED_EMAC_LWIP_DRIVER

struct netif g_MBED_EMAC_NetIF;

#ifndef HW_INTERRUPT
HAL_COMPLETION  InterruptTaskCompletion;
#endif
HAL_COMPLETION  LwipUpTimeCompletion;
static BOOL     LwipNetworkStatus = 0;
static UINT32   LwipLastIpAddress = 0;

void MBED_EMAC_status_callback(struct netif *netif)
{
#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("MBED_status_callback\r\n");
#endif
    if (LwipLastIpAddress != netif->ip_addr.addr) {
        Network_PostEvent(NETWORK_EVENT_TYPE_ADDRESS_CHANGED, 0);
        LwipLastIpAddress = netif->ip_addr.addr;
    }
#if defined(DEBUG_LWIP)
    lcd_printf("IP: %d.%d.%d.%d\r\n",
            (netif->ip_addr.addr >> 0) & 0xFF,
            (netif->ip_addr.addr >> 8) & 0xFF,
            (netif->ip_addr.addr >> 16) & 0xFF,
            (netif->ip_addr.addr >> 24) & 0xFF);
#endif
#if defined(DEBUG)
    hal_printf("\nLink Update: \r\n");
    hal_printf("IP: %d.%d.%d.%d\r\n",
            (netif->ip_addr.addr >> 0) & 0xFF,
            (netif->ip_addr.addr >> 8) & 0xFF,
            (netif->ip_addr.addr >> 16) & 0xFF,
            (netif->ip_addr.addr >> 24) & 0xFF);
    hal_printf("GW: %d.%d.%d.%d\r\n",
            (netif->gw.addr >> 0) & 0xFF,
            (netif->gw.addr >> 8) & 0xFF,
            (netif->gw.addr >> 16) & 0xFF,
            (netif->gw.addr >> 24) & 0xFF);
#endif
}

#ifndef NETIF_FLAG_ETHERNET
#define NETIF_FLAG_ETHERNET     0x40U
#endif

err_t MBED_EMAC_ethhw_init(struct netif *myNetIf)
{
#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("MBED_EMAC_ethhw_init\r\n");
#endif
    //myNetIf->flags = NETIF_FLAG_IGMP | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET; // Added in 4.3.1
    myNetIf->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET | NETIF_FLAG_IGMP;
    myNetIf->mtu = MBED_EMAC_MAX_FRAME_SIZE;
    myNetIf->output = etharp_output;
    myNetIf->linkoutput = MBED_EMAC_LWIP_xmit;
    myNetIf->status_callback = MBED_EMAC_status_callback;
    MBED_EMAC_LWIP_open(myNetIf);
    return (err_t)ERR_OK;
}

void lwip_network_uptime_completion(void *arg)
{
    NATIVE_PROFILE_PAL_NETWORK();

    BOOL status = MBED_EMAC_LWIP_GetLinkStatus();
    if (status != LwipNetworkStatus) {
        struct netif* pNetIf = (struct netif*)arg;
        if (status) {
            SOCK_NetworkConfiguration *pNetCfg = &g_NetworkConfig.NetworkInterfaces[0];
            //PHY_AutoNegotiate();    // ENET_PHY_lwip_set_link_speed( );
            netif_set_up(pNetIf);
            if (pNetCfg->flags & SOCK_NETWORKCONFIGURATION_FLAGS_DHCP)
                dhcp_start(pNetIf);
            Network_PostEvent(NETWORK_EVENT_TYPE__AVAILABILITY_CHANGED, NETWORK_EVENT_FLAGS_IS_AVAILABLE);
        } else {
            netif_set_down((struct netif*)arg);
            Network_PostEvent(NETWORK_EVENT_TYPE__AVAILABILITY_CHANGED, 0);
        }
        LwipNetworkStatus = status;
    }
    LwipUpTimeCompletion.EnqueueDelta64(UPTIME_PERIOD);
}

void InitContinuations(struct netif *pNetIf)
{
#ifndef HW_INTERRUPT
    InterruptTaskCompletion.InitializeForISR((HAL_CALLBACK_FPN)MBED_EMAC_LWIP_recv, pNetIf);
    InterruptTaskCompletion.EnqueueDelta64(INT_PERIOD);
#endif
    LwipUpTimeCompletion.InitializeForUserMode((HAL_CALLBACK_FPN)lwip_network_uptime_completion, pNetIf);
    LwipUpTimeCompletion.EnqueueDelta64(UPTIME_PERIOD);
}

BOOL Network_Interface_Bind(int index)
{
#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("Network_Interface_Bind\r\n");
#endif
    return MBED_EMAC_LWIP_Driver::Bind();
}

int  Network_Interface_Open(int index)
{
#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("Network_Interface_Open\r\n");
#endif
    return MBED_EMAC_LWIP_Driver::Open(index);
}

BOOL Network_Interface_Close(int index)
{
#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("Network_Interface_Close\r\n");
#endif
    return MBED_EMAC_LWIP_Driver::Close();
}

int MBED_EMAC_LWIP_Driver::Open(int index)
{
    struct ip_addr ipaddr, subnetmask, gateway;
    struct netif *pNetIF;
    int len;
    const SOCK_NetworkConfiguration *iface;

#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("MBED_EMAC_LWIP_Driver::Open\r\n");
#endif
    iface = &g_NetworkConfig.NetworkInterfaces[index];
    len = g_MBED_EMAC_NetIF.hwaddr_len;
    if (len == 0 || iface->macAddressLen < len) {
        len = iface->macAddressLen;
        g_MBED_EMAC_NetIF.hwaddr_len = len;
    }
    memcpy(g_MBED_EMAC_NetIF.hwaddr, iface->macAddressBuffer, len);
    ipaddr.addr     = iface->ipaddr;
    gateway.addr    = iface->gateway;
    subnetmask.addr = iface->subnetmask;

    g_MBED_EMAC_NetIF.flags |= NETIF_FLAG_IGMP;
    pNetIF = netif_add(&g_MBED_EMAC_NetIF, &ipaddr, &subnetmask, &gateway, NULL, MBED_EMAC_ethhw_init, ethernet_input);

    netif_set_default(pNetIF);
    LwipNetworkStatus = MBED_EMAC_LWIP_GetLinkStatus();
    if (LwipNetworkStatus == TRUE) {
#if defined(DEBUG_LWIP)
        lcd_printf("Link OK\r\n");
#endif
        netif_set_up(pNetIF);
    } else {
#if defined(DEBUG_LWIP)
        lcd_printf("Link NG\r\n");
#endif
    }
    InitContinuations(pNetIF);
    return g_MBED_EMAC_NetIF.num;
}

BOOL MBED_EMAC_LWIP_Driver::Close(void)
{
    int retVal = -1;
#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("MBED_EMAC_LWIP_Driver::Close\r\n");
#endif
    LwipUpTimeCompletion.Abort();
#ifndef HW_INTERRUPT
    InterruptTaskCompletion.Abort();
#endif
    LwipNetworkStatus = 0;
    netif_set_down(&g_MBED_EMAC_NetIF);
    netif_remove(&g_MBED_EMAC_NetIF);
    MBED_EMAC_LWIP_close(&g_MBED_EMAC_NetIF);
    memset(&g_MBED_EMAC_NetIF, 0, sizeof g_MBED_EMAC_NetIF);
    return true;
}

BOOL MBED_EMAC_LWIP_Driver::Bind(void)
{
#ifdef DEBUG_MBED_EMAC_LWIP_DRIVER
    hal_printf("MBED_EMAC_LWIP_Driver::Bind\r\n");
#endif
    return true;
}

BOOL MBED_EMAC_LWIP_GetLinkStatus(void)
{
    return true;
}
