/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stddef.h>
#include "us_ticker_api.h"
#include "PeripheralNames.h"
#include "ostm_iodefine.h"
#include "RZ_A1_Init.h"
#include "MBRZA1H.h"

#define DEBUG_US_TICKER

#define US_TICKER_TIMER_IRQn (OSTMI1TINT_IRQn)
#define CPG_STBCR5_BIT_MSTP50   (0x01u) /* OSTM1 */

#define US_TICKER_CLOCK_US_DEV (1000000)
#define TIMER_MAX   (0xffffffffL)

int us_ticker_inited = 0;
float count_clock = 0.0;
uint64_t m_SetCompare = 0L;
static uint64_t m_lastRead = 0L;
static uint64_t m_lastCompare = (uint64_t)TIMER_MAX;
#if defined(DEBUG_US_TICKER)
static uint32_t m_cnt = 0;
#endif
void (*netmf_handler)(void) = 0;

void us_ticker_interrupt(void) {
    m_lastRead += m_lastCompare;
    if (m_lastCompare == (uint64_t)TIMER_MAX) {
        if (m_SetCompare != (uint64_t)0L) {
            m_SetCompare -= (uint64_t)TIMER_MAX;
            if (m_SetCompare >= (uint64_t)TIMER_MAX) {
                m_lastCompare = (uint64_t)TIMER_MAX;
            } else {
                m_lastCompare = m_SetCompare;
            }
        } else {
            m_lastCompare = (uint64_t)TIMER_MAX;
        }
    } else {
        //us_ticker_irq_handler();
        if (netmf_handler != 0)
            netmf_handler();
        m_SetCompare = 0L;
        m_lastCompare = TIMER_MAX;
    }
    OSTM1TT = 0x01;
    OSTM1CMP = (uint32_t)m_lastCompare;
    OSTM1CTL = 0x02;
    OSTM1TS = 0x1;
#if defined(DEBUG_US_TICKER)
    m_cnt = (uint32_t)OSTM1CNT;
#endif
    GIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

void us_ticker_init(void) {
    int i;
    if (us_ticker_inited) return;
    us_ticker_inited = 1;
    m_lastRead = 0L;
    m_lastCompare = (uint64_t)TIMER_MAX;
    m_SetCompare = 0L;
    /* set Counter Clock(us) */
    if (false == RZ_A1_IsClockMode0()) {
        count_clock = ((float)CM1_RENESAS_RZ_A1_P0_CLK / (float)US_TICKER_CLOCK_US_DEV);
    } else {
        count_clock = ((float)CM0_RENESAS_RZ_A1_P0_CLK / (float)US_TICKER_CLOCK_US_DEV);
    }

    /* Power Control for Peripherals      */
    CPGSTBCR5 &= ~(CPG_STBCR5_BIT_MSTP50); /* enable OSTM1 clock */

    // timer settings
    OSTM1TT   = 0x01;    /* Stop the counter and clears the OSTM1TE bit.     */
    OSTM1CMP  = TIMER_MAX;
    OSTM1CTL  = 0x02;    /* Free running timer mode. Interrupt disabled when star counter  */
    OSTM1TS   = 0x1;    /* Start the counter and sets the OSTM0TE bit.     */
#if defined(DEBUG_US_TICKER)
    m_cnt = (uint32_t)OSTM1CNT;
#endif

    // INTC settings
    InterruptHandlerRegister(US_TICKER_TIMER_IRQn, (void (*)(uint32_t))us_ticker_interrupt);
    GIC_SetPriority(US_TICKER_TIMER_IRQn, 6);
    GIC_EnableIRQ(US_TICKER_TIMER_IRQn);
}

uint64_t cnt_ticker_read() {
    uint64_t val;
    if (!us_ticker_inited)
        us_ticker_init();
    /* read counter */
    val = m_lastRead + (uint64_t)OSTM1CNT;
    return val;
}

uint32_t us_ticker_read() {
    /* clock to us */
    return (uint32_t)(cnt_ticker_read() / count_clock);
}

void us_ticker_set_interrupt(timestamp_t timestamp) {
    // set match value
    __disable_irq();
    m_lastRead = (uint64_t)cnt_ticker_read();
    if (m_SetCompare >= (uint64_t)TIMER_MAX) {
        m_lastCompare = (uint64_t)TIMER_MAX;
    } else {
        m_lastCompare = m_SetCompare;
    }
    OSTM1TT = 0x01;
    OSTM1CMP = (uint32_t)m_lastCompare;
    OSTM1CTL = 0x02;
    OSTM1TS = 0x1;
#if defined(DEBUG_US_TICKER)
    m_cnt = (uint32_t)OSTM1CNT;
#endif
    __enable_irq();
}

void us_ticker_disable_interrupt(void) {
    GIC_DisableIRQ(US_TICKER_TIMER_IRQn);
}

void us_ticker_clear_interrupt(void) {
    /* There are no Flags of OSTM1 to clear here */
    /* Do Nothing */
}
