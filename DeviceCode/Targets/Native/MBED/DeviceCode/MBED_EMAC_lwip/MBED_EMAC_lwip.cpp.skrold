////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "mbed.h"
#include "ethernet_api.h"
#include "net_decl_lwip.h"
#include "MBED_EMAC_LWIP.h"
#include "MBED_EMAC_LWIP_driver.h"
#include "lwip/opt.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"

//#define DEBUG_LWIP_TX
//#define DEBUG_LWIP_RX

extern INT32 dbg_printf( const char* format, ... );   // COM1 and LCD. defined in tinycrt.cpp
extern struct netif g_MBED_EMAC_NetIF;
extern HAL_COMPLETION    InterruptTaskCompletion;

#if 0
#ifdef __cplusplus
extern "C" {
#endif
int ethernetext_init(ethernet_cfg_t *p_ethcfg);
#ifdef __cplusplus
}
#endif
#endif

extern INT32 dbg_printf( const char* format, ... );   // COM1 and LCD. defined in tinycrt.cpp
extern struct netif g_MBED_EMAC_NetIF;
extern HAL_COMPLETION InterruptTaskCompletion;

// MAC Address
char MACAddr[6];
char Broadcast[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

BOOL MBED_EMAC_LWIP_Init(struct netif *pNetIf)
{
    ethernet_init();
    return TRUE;
}

BOOL MBED_EMAC_LWIP_open(struct netif *pNetIf)
{
    return MBED_EMAC_LWIP_Init(pNetIf);
}

void MBED_EMAC_LWIP_close(struct netif *pNetIf)
{
    ethernet_free();
}

err_t MBED_EMAC_LWIP_xmit(struct netif *pNetIf, struct pbuf *p)
{
    UINT32 cnt;
    INT32 write_size;
    struct pbuf *q;
    err_t err = ERR_OK;

    GLOBAL_LOCK(irq);
    if (!pNetIf || !p)
        return ERR_ARG;
    if ((p->payload != NULL) && (p->len != 0)) {
        /* If the first data can't be written, transmit descriptor is full. */
        for (cnt = 0; cnt < 100; cnt++) {
            write_size = ethernet_write((char *)p->payload, p->len);
            if (write_size != 0) {
//#if defined(DEBUG_LWIP)
//                dbg_printf("TX%d OK\r\n", write_size);
//#endif
                err = ERR_OK;
                break;
            }
        }
        if (write_size != 0) {
            for (q = p->next; q != NULL; q = q->next) {
                (void)ethernet_write((char *)q->payload, q->len);
                write_size = q->len;
            }
            if (ethernet_send() == 1) {
#if defined(DEBUG_LWIP_TX)
                dbg_printf("TY%d OK\r\n", write_size);
#endif
                err = ERR_OK;
            } else {
#if defined(DEBUG_LWIP_TX)
                dbg_printf("TY%d NG\r\n", write_size);
#endif
                err = ERR_MEM;
            }
        }
    }
    return err;
}

void MBED_EMAC_LWIP_recv(struct netif *pNetIf)
{
    INT16 recvd;
    struct pbuf *p, *q;

    GLOBAL_LOCK(irq);
    while (1) {
        recvd = ethernet_receive();
        if (recvd == 0)
            break;
#if defined(DEBUG_LWIP_RX)
        dbg_printf("RX%d ", recvd);
#endif
        //p = pbuf_alloc(PBUF_RAW, recvd, PBUF_RAM);
        p = pbuf_alloc(PBUF_RAW, recvd, PBUF_POOL);
        if (p == NULL) {
            dbg_printf("Can't alloc pPBuf\r\n");
            break;
        }
        //(void)ethernet_read((char *)p->payload, recvd);
        for (q = p; q != NULL; q = q->next) {
            (void)ethernet_read((char *)q->payload, q->len);
        }
        if ((pNetIf != 0) && (pNetIf->input != 0)) {
            if (pNetIf->input(p, pNetIf) == ERR_OK) {
#if defined(DEBUG_LWIP_RX)
                dbg_printf("OK\r\n");
#endif
                break;
            } else {
#if defined(DEBUG_LWIP_RX)
                dbg_printf("NG\r\n");
#endif
                break;
            }
        }
    }
#ifndef HW_INTERRUPT
    InterruptTaskCompletion.EnqueueDelta64(INT_PERIOD);
#endif
}

