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
//  Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "mbed.h"
#include "SerialBase.h"

#include "mbed_assert.h"
#include "serial_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "gpio_api.h"

#include "scif_iodefine.h"
#include "cpg_iodefine.h"
#include "core_caFunc.h"

// DeviceCode\Targets\OS\mbed\libraries\mbed\targets\cmsis\core_caFunc.h
// extern "C"
// {
// void __disable_irq();
// void __enable_irq();
// }
static void USART_RxISR(UINT32 port);
static void USART_TxISR(UINT32 port);

#define UART_MAX    12
#define UART_NUM    8
#define IRQ_NUM     2

#if 0
typedef enum {
    UART0,
    UART1,
    UART2,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
} UARTName;
#endif

static void uart0_tx_irq(void);
static void uart1_tx_irq(void);
static void uart2_tx_irq(void);
static void uart3_tx_irq(void);
static void uart4_tx_irq(void);
static void uart5_tx_irq(void);
static void uart6_tx_irq(void);
static void uart7_tx_irq(void);
static void uart0_rx_irq(void);
static void uart1_rx_irq(void);
static void uart2_rx_irq(void);
static void uart3_rx_irq(void);
static void uart4_rx_irq(void);
static void uart5_rx_irq(void);
static void uart6_rx_irq(void);
static void uart7_rx_irq(void);


static const PinMap PinMap_UART_TX[] = {
    {P2_14 , UART0, 6},
    {P6_3  , UART2, 7},
    {P5_0  , UART4, 5},
    {P5_3  , UART3, 5},
    {P5_6  , UART6, 5},
    {P2_5  , UART1, 6},
    {P8_14 , UART4, 7},
    {P8_13 , UART5, 5},
    {P7_4  , UART7, 4},
    {P11_10, UART5, 3},
    {P6_6  , UART5, 5},
    {NC    , NC   , 0}
};

static const PinMap PinMap_UART_RX[] = {
    {P2_15 , UART0, 6},
    {P6_2  , UART2, 7},
    {P5_1  , UART4, 5},
    {P5_4  , UART3, 5},
    {P5_7  , UART6, 5},
    {P2_6  , UART1, 6},
    {P8_15 , UART4, 7},
    {P8_11 , UART5, 5},
    {P7_5  , UART7, 4},
    {P11_11, UART5, 3},
    {P6_7  , UART5, 5},
    {NC    , NC   , 0}
};

static PinName TX[] = {
        P2_14,
        P6_3,
        P5_0,
        P5_3,
        P5_6,
        P2_5,
        P8_14,
        P8_13,
        P7_4,
        P11_10,
        P6_6
};

static PinName RX[] = {
        P2_15,
        P6_2,
        P5_1,
        P5_4,
        P5_7,
        P2_6,
        P8_15,
        P8_11,
        P7_5,
        P11_11,
        P6_7
};

static const struct st_scif *SCIF[] = SCIF_ADDRESS_LIST;
static uart_irq_handler irq_handler;

static int stdio_uart_inited = 0;
static serial_t stdio_uart;

struct usart_global_data_s {
    uint32_t usart_irq_id;
    gpio_t sw_rts, sw_cts;
    uint8_t count, rx_irq_set_flow, rx_irq_set_api;
};

static struct usart_global_data_s uart_data[UART_NUM];

static const IRQn_Type irq_set_tbl[UART_NUM][IRQ_NUM] = {
    {SCIFRXI0_IRQn, SCIFTXI0_IRQn},
    {SCIFRXI1_IRQn, SCIFTXI1_IRQn},
    {SCIFRXI2_IRQn, SCIFTXI2_IRQn},
    {SCIFRXI3_IRQn, SCIFTXI3_IRQn},
    {SCIFRXI4_IRQn, SCIFTXI4_IRQn},
    {SCIFRXI5_IRQn, SCIFTXI5_IRQn},
    {SCIFRXI6_IRQn, SCIFTXI6_IRQn},
    {SCIFRXI7_IRQn, SCIFTXI7_IRQn}
};

static const IRQHandler hander_set_tbl[UART_NUM][IRQ_NUM] = {
    {uart0_rx_irq, uart0_tx_irq},
    {uart1_rx_irq, uart1_tx_irq},
    {uart2_rx_irq, uart2_tx_irq},
    {uart3_rx_irq, uart3_tx_irq},
    {uart4_rx_irq, uart4_tx_irq},
    {uart5_rx_irq, uart5_tx_irq},
    {uart6_rx_irq, uart6_tx_irq},
    {uart7_rx_irq, uart7_tx_irq}
};

static __IO uint16_t *SCSCR_MATCH[] = {
    &SCSCR_0,
    &SCSCR_1,
    &SCSCR_2,
    &SCSCR_3,
    &SCSCR_4,
    &SCSCR_5,
    &SCSCR_6,
    &SCSCR_7,
};

static __IO uint16_t *SCFSR_MATCH[] = {
    &SCFSR_0,
    &SCFSR_1,
    &SCFSR_2,
    &SCFSR_3,
    &SCFSR_4,
    &SCFSR_5,
    &SCFSR_6,
    &SCFSR_7,
};

static serial_t usart_obj[UART_MAX];


/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/

static void uart_tx_irq(IRQn_Type irq_num, uint32_t index) {
    //__IO uint16_t *dmy_rd_scscr;
    __IO uint16_t *dmy_rd_scfsr;

    //dmy_rd_scscr = SCSCR_MATCH[index];
    //*dmy_rd_scscr &= 0x007B;                    // Clear TIE and Write to bit15~8,2 is always 0
    dmy_rd_scfsr = SCFSR_MATCH[index];
    *dmy_rd_scfsr = (*dmy_rd_scfsr & ~0x0020);  // Clear TDFE

    USART_TxISR(index);
}

static void uart_rx_irq(IRQn_Type irq_num, uint32_t index) {
    //__IO uint16_t *dmy_rd_scscr;
    __IO uint16_t *dmy_rd_scfsr;

    //dmy_rd_scscr = SCSCR_MATCH[index];
    //*dmy_rd_scscr &= 0x00B3;                    // Clear RIE,REIE and Write to bit15~8,2 is always 0
    dmy_rd_scfsr = SCFSR_MATCH[index];
    *dmy_rd_scfsr = (*dmy_rd_scfsr & ~0x0003);  // Clear RDF,DR

    USART_RxISR(index);
}

/* TX handler */
static void uart0_tx_irq(void)  {uart_tx_irq(SCIFTXI0_IRQn, 0);}
static void uart1_tx_irq(void)  {uart_tx_irq(SCIFTXI1_IRQn, 1);}
static void uart2_tx_irq(void)  {uart_tx_irq(SCIFTXI2_IRQn, 2);}
static void uart3_tx_irq(void)  {uart_tx_irq(SCIFTXI3_IRQn, 3);}
static void uart4_tx_irq(void)  {uart_tx_irq(SCIFTXI4_IRQn, 4);}
static void uart5_tx_irq(void)  {uart_tx_irq(SCIFTXI5_IRQn, 5);}
static void uart6_tx_irq(void)  {uart_tx_irq(SCIFTXI6_IRQn, 6);}
static void uart7_tx_irq(void)  {uart_tx_irq(SCIFTXI7_IRQn, 7);}
/* RX handler */
static void uart0_rx_irq(void)  {uart_rx_irq(SCIFRXI0_IRQn, 0);}
static void uart1_rx_irq(void)  {uart_rx_irq(SCIFRXI1_IRQn, 1);}
static void uart2_rx_irq(void)  {uart_rx_irq(SCIFRXI2_IRQn, 2);}
static void uart3_rx_irq(void)  {uart_rx_irq(SCIFRXI3_IRQn, 3);}
static void uart4_rx_irq(void)  {uart_rx_irq(SCIFRXI4_IRQn, 4);}
static void uart5_rx_irq(void)  {uart_rx_irq(SCIFRXI5_IRQn, 5);}
static void uart6_rx_irq(void)  {uart_rx_irq(SCIFRXI6_IRQn, 6);}
static void uart7_rx_irq(void)  {uart_rx_irq(SCIFRXI7_IRQn, 7);}

static void usart_irq_set_internal(serial_t *obj, SerialIrq irq, uint32_t enable, uint32_t priority) {
    IRQn_Type IRQn;
    IRQHandler handler;

    IRQn = irq_set_tbl[obj->index][irq];
    handler = hander_set_tbl[obj->index][irq];

    if ((obj->index >= 0) && (obj->index <= 7)) {
        if (enable) {
            InterruptHandlerRegister(IRQn, handler);
            GIC_SetPriority(IRQn, priority);
            GIC_EnableIRQ(IRQn);
        } else {
            GIC_DisableIRQ(IRQn);
        }
    }
}

static void serial_tx_int_enable(serial_t *obj, int enable)
{
    if (enable != 0)
        obj->uart->SCSCR |= 0x0080;
    else
        obj->uart->SCSCR &= 0xFF7F;
}

static int serial_tx_int_state(serial_t *obj)
{
    return ((obj->uart->SCSCR & 0x0080) != 0);
}

static void usart_rx_int_enable(serial_t *obj, int enable)
{
    if (enable != 0)
        obj->uart->SCSCR |= 0x0040;
    else
        obj->uart->SCSCR &= 0xFFBF;
}

static int usart_rx_int_state(serial_t *obj)
{
    return ((obj->uart->SCSCR & 0x0040) != 0);
}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/
static int usart_readable(serial_t *obj) {
    return obj->uart->SCFSR & 0x02;  // RDF
}

static int usart_writable(serial_t *obj) {
    return obj->uart->SCFSR & 0x20;  // TDFE
}

static void usart_clear(serial_t *obj) {
    obj->uart->SCFCR = 0x06;
    obj->uart->SCFCR = 0x06;
}

static int usart_getc(serial_t *obj) {
    uint16_t dummy_read;
#if 0
    if ((obj->uart->SCFSR & 0x9c) | (obj->uart->SCLSR & 0x01)) {
        dummy_read = obj->uart->SCFSR;
        obj->uart->SCFCR |= 0x02;
        obj->uart->SCFCR &= ~0x02;
        obj->uart->SCFSR = (dummy_read & ~0x9c);
        obj->uart->SCLSR &= ~0x01;
    }
    while (!usart_readable(obj)) ;
    data = obj->uart->SCFRDR & 0xff;
    obj->uart->SCFSR &= 0xfffc;     // Clear DR,RDF
#endif
    if ((obj->uart->SCFSR & 0x9c) | (obj->uart->SCLSR & 0x01)) {
        dummy_read = obj->uart->SCFSR;
        obj->uart->SCFCR |= 0x02;
        obj->uart->SCFCR &= ~0x02;
        obj->uart->SCFSR = (dummy_read & ~0x9c);
        obj->uart->SCLSR &= ~0x01;
    }
#if 0
    if (obj->uart->SCFSR & 0x93) {
        dummy_read = obj->uart->SCFSR;
        obj->uart->SCFSR = (dummy_read & ~0x93);
    }
#endif
    obj->uart->SCSCR |= 0x0040;     // Set RIE
    while (!serial_readable(obj));
    int data = obj->uart->SCFRDR & 0xff;
                /* Clear DR,RDF */
    obj->uart->SCFSR &= 0xfffc;
    return data;
}

static void usart_putc(serial_t *obj, int c) {
    uint16_t dummy_read;
    
    obj->uart->SCSCR |= 0x0080;     // Set TIE
    while (!usart_writable(obj));
    obj->uart->SCFTDR = c;
    dummy_read = obj->uart->SCFSR;
    obj->uart->SCFSR = (dummy_read & 0xff9f);  // Clear TEND/TDFE
    uart_data[obj->index].count++;
}

static void usart_pinout_tx(PinName tx) {
    pinmap_pinout(tx, PinMap_UART_TX);
}

static void usart_break_set(serial_t *obj) {
}

static void usart_break_clear(serial_t *obj) {
}

static void usart_baud(serial_t *obj, int baudrate) {

    uint32_t _PCLK = 66666666;

    uint16_t DL = (_PCLK / (32 * baudrate)) -1;

    // set LCR[DLAB] to enable writing to divider registers
    obj->uart->SCBRR = DL;
}

static void usart_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits) {
    int parity_enable;
    int parity_select;

    MBED_ASSERT((stop_bits == 1) || (stop_bits == 2)); // 0: 1 stop bits, 1: 2 stop bits
    MBED_ASSERT((data_bits > 6) && (data_bits < 9)); // 0: 5 data bits ... 3: 8 data bits
    MBED_ASSERT((parity == ParityNone) || (parity == ParityOdd) || (parity == ParityEven) ||
           (parity == ParityForced1) || (parity == ParityForced0));

    stop_bits = (stop_bits == 1)? 0:
                (stop_bits == 2)? 1:
                0; // must not to be

    data_bits = (data_bits == 8)? 0:
                (data_bits == 7)? 1:
                0; // must not to be

    switch (parity) {
        case ParityNone:
            parity_enable = 0;
            parity_select = 0;
            break;
        case ParityOdd:
            parity_enable = 1;
            parity_select = 0;
            break;
        case ParityEven:
            parity_enable = 1;
            parity_select = 1;
            break;
        default:
            parity_enable = 0;
            parity_select = 0;
            break;
    }

    obj->uart->SCSMR = data_bits          << 6
                   | parity_enable        << 5
                   | parity_select        << 4
                   | stop_bits            << 3;
}

BOOL CPU_USART_Initialize(int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue)
{
    serial_t *obj = &usart_obj[ComPortNum];
    PinName tx = PinMap_UART_TX[ComPortNum].pin;
    PinName rx = PinMap_UART_RX[ComPortNum].pin;
    volatile uint8_t dummy ;
    int is_stdio_uart = 0;
    // determine the UART to use
    uint32_t uart_tx = pinmap_peripheral(tx, PinMap_UART_TX);
    uint32_t uart_rx = pinmap_peripheral(rx, PinMap_UART_RX);
    uint32_t uart = pinmap_merge(uart_tx, uart_rx);

    //MBED_ASSERT((int)uart != NC);

    __disable_irq();
    obj->uart = (struct st_scif *)SCIF[uart];
    // enable power
    switch (uart) {
        case UART0: CPG.STBCR4 &= ~(1 <<  7); break;
        case UART1: CPG.STBCR4 &= ~(1 <<  6); break;
        case UART2: CPG.STBCR4 &= ~(1 <<  5); break;
        case UART3: CPG.STBCR4 &= ~(1 <<  4); break;
        case UART4: CPG.STBCR4 &= ~(1 <<  3); break;
        case UART5: CPG.STBCR4 &= ~(1 <<  2); break;
        case UART6: CPG.STBCR4 &= ~(1 <<  1); break;
        case UART7: CPG.STBCR4 &= ~(1 <<  0); break;
    }
    dummy = CPG.STBCR4;

    /* ==== SCIF initial setting ==== */
    /* ---- Serial control register (SCSCR) setting ---- */
    /* B'00 : Internal CLK */
    obj->uart->SCSCR = 0x0000u;          /* SCIF transmitting and receiving operations stop */

    /* ---- FIFO control register (SCFCR) setting ---- */
    /* Transmit FIFO reset & Receive FIFO data register reset */
    obj->uart->SCFCR = 0x0006;

    /* ---- Serial status register (SCFSR) setting ---- */
    dummy = obj->uart->SCFSR;
    obj->uart->SCFSR = (dummy & 0xFF6Cu);         /* ER,BRK,DR bit clear */

    /* ---- Line status register (SCLSR) setting ---- */
    /* ORER bit clear */
    dummy = obj->uart->SCLSR;
    obj->uart->SCLSR = (dummy & 0x0001);

    /* ---- Serial extension mode register (SCEMR) setting ----
    b7 BGDM - Baud rate generator double-speed mode  : Normal mode
    b0 ABCS - Base clock select in asynchronous mode : Base clock is 16 times the bit rate */
    obj->uart->SCEMR = 0x0000u;

    /* ---- Bit rate register (SCBRR) setting ---- */
    usart_baud  (obj, BaudRate);
    usart_format(obj, 8, ParityNone, 1);

    /* ---- FIFO control register (SCFCR) setting ---- */
    //obj->uart->SCFCR = 0x0030u;
    obj->uart->SCFCR = 0x0030u;

    /* ---- Serial port register (SCSPTR) setting ----
    b1 SPB2IO - Serial port break output : disabled
    b0 SPB2DT - Serial port break data   : High-level */
    //obj->uart->SCSPTR |= 0x0000u;

    obj->uart->SCSCR = 0x00F0;

    // pinout the chosen uart
    pinmap_pinout(tx, PinMap_UART_TX);
    pinmap_pinout(rx, PinMap_UART_RX);

    switch (uart) {
        case UART0: obj->index = 0; break;
        case UART1: obj->index = 1; break;
        case UART2: obj->index = 2; break;
        case UART3: obj->index = 3; break;
        case UART4: obj->index = 4; break;
        case UART5: obj->index = 5; break;
        case UART6: obj->index = 6; break;
        case UART7: obj->index = 7; break;
    }
    uart_data[obj->index].sw_rts.pin = NC;
    uart_data[obj->index].sw_cts.pin = NC;

    is_stdio_uart = (uart == STDIO_UART) ? (1) : (0);

    if (is_stdio_uart) {
        stdio_uart_inited = 1;
        memcpy(&stdio_uart, obj, sizeof(serial_t));
    }
    usart_irq_set_internal(obj, RxIrq, 1, 11);
    usart_irq_set_internal(obj, TxIrq, 1, 11);
    __enable_irq();
    return TRUE;
}

BOOL CPU_USART_Uninitialize(int ComPortNum)
{
    serial_t *obj = &usart_obj[ComPortNum];
#if 0
    __disable_irq();
    usart_irq_set_internal(obj, RxIrq, 0, 11);
    usart_irq_set_internal(obj, TxIrq, 0, 11);
    uart_data[obj->index].usart_irq_id = 0;
    __enable_irq();
#endif
    return TRUE;
}

BOOL CPU_USART_TxBufferEmpty(int ComPortNum)
{
    serial_t *obj = &usart_obj[ComPortNum];
    return usart_writable(obj)? TRUE:FALSE;
}

BOOL CPU_USART_TxShiftRegisterEmpty(int ComPortNum)
{
    return CPU_USART_TxBufferEmpty(ComPortNum);
}

void CPU_USART_WriteCharToTxBuffer(int ComPortNum, UINT8 c)
{
    serial_t *obj = &usart_obj[ComPortNum];
    while (FALSE == CPU_USART_TxShiftRegisterEmpty(ComPortNum));
    usart_putc(obj, (int)c);
}

void CPU_USART_TxBufferEmptyInterruptEnable(int ComPortNum, BOOL Enable)
{
    serial_t *obj = &usart_obj[ComPortNum];
    serial_tx_int_enable(obj, (int)Enable);
}

BOOL CPU_USART_TxBufferEmptyInterruptState(int ComPortNum)
{
    serial_t *obj = &usart_obj[ComPortNum];
    return serial_tx_int_state(obj);
}

void CPU_USART_RxBufferFullInterruptEnable(int ComPortNum, BOOL Enable)
{
    serial_t *obj = &usart_obj[ComPortNum];
    usart_rx_int_enable(obj, (int)Enable);
}

BOOL CPU_USART_RxBufferFullInterruptState(int ComPortNum)
{
    serial_t *obj = &usart_obj[ComPortNum];
    return usart_rx_int_state(obj);
}

void CPU_USART_ProtectPins(int ComPortNum, BOOL On)
{
    if (On) {
        CPU_USART_RxBufferFullInterruptEnable(ComPortNum, FALSE);
        CPU_USART_TxBufferEmptyInterruptEnable(ComPortNum, FALSE);
    } else {
        CPU_USART_TxBufferEmptyInterruptEnable(ComPortNum, TRUE);
        CPU_USART_RxBufferFullInterruptEnable(ComPortNum, TRUE);
    }
}

UINT32 CPU_USART_PortsCount()
{
    return TOTAL_USART_PORT;
}

void CPU_USART_GetPins(int ComPortNum, GPIO_PIN& rxPin, GPIO_PIN& txPin, GPIO_PIN& ctsPin, GPIO_PIN& rtsPin)
{
    rxPin = (GPIO_PIN)RX[ComPortNum];
    txPin = (GPIO_PIN)TX[ComPortNum];
    ctsPin= GPIO_PIN_NONE;
    rtsPin= GPIO_PIN_NONE;
    return;
}

BOOL CPU_USART_SupportNonStandardBaudRate (int ComPortNum)
{
    // ToDO
    return TRUE;
}

void CPU_USART_GetBaudrateBoundary(int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz)
{
    maxBaudrateHz = 115200;
    minBaudrateHz = 2400;
}

BOOL CPU_USART_IsBaudrateSupported(int ComPortNum, UINT32 & BaudrateHz)
{
    // ToDO
    if (BaudrateHz <= 230400)
        return TRUE;
    return FALSE;
}

BOOL CPU_USART_TxHandshakeEnabledState(int comPort)
{
    // ToDo
    return TRUE;
}

static void USART_RxISR(UINT32 port)
{
    char c;
    serial_t *obj = &usart_obj[port];
    GLOBAL_LOCK(irq);
    if (usart_readable(obj)) {
        c = (char)usart_getc(obj);
        USART_AddCharToRxBuffer(port, c);
    }
}

static void USART_TxISR(UINT32 port)
{
    char c;
    GLOBAL_LOCK(irq);
    if (USART_RemoveCharFromTxBuffer(port, c)) {
        CPU_USART_WriteCharToTxBuffer(port, c);
        Events_Set(SYSTEM_EVENT_FLAG_COM_OUT);
    } else {
        CPU_USART_TxBufferEmptyInterruptEnable(port, FALSE);
    }
}

#if 0
__attribute__((aligned(8))) static void USART_RxISR0(void)
{
    USART_RxISR(0);
}

__attribute__((aligned(8))) static void USART_TxISR0(void)
{
    USART_TxISR(0);
}
#endif
