/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2012-2017 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *  @(#) $Id: zynq.h 1067 2014-12-24 14:15:10Z ertl-honda $
 */

/*
 *  This file contains a few definitions that are specific to
 *  the ZYNQ ZYBO and ZEDboard, such as the memory address, clock values,
 *  or number of interrupts.
 *
 */
#ifndef TOPPERS_ZYNQ_H
#define TOPPERS_ZYNQ_H

#include <sil.h>

#if defined(BOARD_ZYBO)

/*
 * CPU clocks
 */
#define ZYNQ_CPU_6X4X_MHZ     650U
#define ZYNQ_CPU_3X2X_MHZ     325U
#define ZYNQ_CPU_2X_MHZ       222U
#define ZYNQ_CPU_1X_MHZ       111U

#define ZYNQ_CORE_CLK              ZYNQ_CPU_6X4X_MHZ
#define ZYNQ_PERIPHCLK             ZYNQ_CPU_3X2X_MHZ
#define MPCORE_GTM_CLOCK_FREQ_MHZ  ZYNQ_PERIPHCLK

/*
 * Tmer preescaler and load value to achieve 1ms per tick.
 * Note that the preescaler value must be representable with 8 bits;
 * and the load value must be a 32bit value.
 *
 * Private timers and watchdogs are clocked with PERIPHCLK which is 1/2 of
 * the CPU frequency. The formula is:
 *
 *    period = (preescaler + 1)(load + 1) / PERIPHCLK
 *      - period    = 1ms
 *      - periphclk = 325MHz
 *
 * For example:
 *      - preescaler = 0
 *      - load       = 325000
 */
#define MPCORE_WDT_PS_1MS    0U       // preescaler for private watchdog
#define MPCORE_WDT_LOAD_1MS  325000U  // load value for private watchdog

#define MPCORE_TM_PS_1MS     0U       // preescaler for private timer
#define MPCORE_TM_LOAD_1MS   325000U  // load value for private timer

/*
 * Definition of the 115200bps baud rate constants
 *        rate = clk / (CD * (BDIV + 1))
 *         clk = MR.CLKSEL? inclk : inclk/8  (e.g. inclk)
 *       inclk = MR.CCLK? uart_clock : apb clock (e.g. uart_clock=50MHz)
 */
#define UART_BAUD_115K          0x7CU
#define UART_BAUDDIV_115K       0x6U

/*
 * Memory base address and size
 */
#define DDR_ADDR 0x00000000
#define DDR_SIZE 0x20000000 /* 512MB */

/*
 *  UART base address definitions (used in target_serial.c)
 *
 */
#ifdef TOPPERS_NOSAFEG
#define     UART0_BASE  ZYNQ_UART1_BASE
#define     UART1_BASE  ZYNQ_UART0_BASE
#else
#error "SafeG is no supported yet!"
#endif

/*
 *  UART interrupt handler definitions (used in target_serial.cfg)
 *     INHNO: interrupt handler number
 *     INTNO: interrupt number
 *     INTPRI: interrupt priority (lower means higher priority)
 *     INTATR: interrupt attributes (0 means not enabled at the beginning)
 *
 */
#ifdef TOPPERS_NOSAFEG
#define    INHNO_SIO0  ZYNQ_UART1_IRQ
#define    INTNO_SIO0  ZYNQ_UART1_IRQ
#define    INTPRI_SIO0    -3
#define    INTATR_SIO0     0U
#define    INHNO_SIO1  ZYNQ_UART0_IRQ
#define    INTNO_SIO1  ZYNQ_UART0_IRQ
#define    INTPRI_SIO1    -2
#define    INTATR_SIO1     0U
#else
#error "SafeG is no supported yet!"
#endif

#elif defined(BOARD_ARDUZYNQ)

/*
 * CPU clocks
 */
#define ZYNQ_CPU_6X4X_MHZ     666U
#define ZYNQ_CPU_3X2X_MHZ     333U
#define ZYNQ_CPU_2X_MHZ       222U
#define ZYNQ_CPU_1X_MHZ       111U

#define ZYNQ_CORE_CLK              ZYNQ_CPU_6X4X_MHZ
#define ZYNQ_PERIPHCLK             ZYNQ_CPU_3X2X_MHZ
#define MPCORE_GTM_CLOCK_FREQ_MHZ  ZYNQ_PERIPHCLK

/*
 * Tmer preescaler and load value to achieve 1ms per tick.
 * Note that the preescaler value must be representable with 8 bits;
 * and the load value must be a 32bit value.
 *
 * Private timers and watchdogs are clocked with PERIPHCLK which is 1/2 of
 * the CPU frequency. The formula is:
 *
 *    period = (preescaler + 1)(load + 1) / PERIPHCLK
 *      - period    = 1ms
 *      - periphclk = 325MHz
 *
 * For example:
 *      - preescaler = 0
 *      - load       = 325000
 */
#define MPCORE_WDT_PS_1MS    0U       // preescaler for private watchdog
#define MPCORE_WDT_LOAD_1MS  333000U  // load value for private watchdog

#define MPCORE_TM_PS_1MS     0U       // preescaler for private timer
#define MPCORE_TM_LOAD_1MS   333000U  // load value for private timer

/*
 * Definition of the 115200bps baud rate constants
 *        rate = clk / (CD * (BDIV + 1))
 *         clk = MR.CLKSEL? inclk : inclk/8  (e.g. inclk)
 *       inclk = MR.CCLK? uart_clock : apb clock (e.g. uart_clock=50MHz)
 */
#define UART_BAUD_115K          0x7CU
#define UART_BAUDDIV_115K       0x06U

/*
 * Memory base address and size
 */
#define DDR_ADDR 0x00000000
#define DDR_SIZE 0x20000000 /* 512MB */

/*
 *  UART base address definitions (used in target_serial.c)
 *
 */
#ifdef TOPPERS_NOSAFEG
#define     UART0_BASE  ZYNQ_UART0_BASE
#define     UART1_BASE  ZYNQ_UART1_BASE
#else
#error "SafeG is no supported yet!"
#endif

/*
 *  UART interrupt handler definitions (used in target_serial.cfg)
 *     INHNO: interrupt handler number
 *     INTNO: interrupt number
 *     INTPRI: interrupt priority (lower means higher priority)
 *     INTATR: interrupt attributes (0 means not enabled at the beginning)
 *
 */
#ifdef TOPPERS_NOSAFEG
#define    INHNO_SIO0  ZYNQ_UART0_IRQ
#define    INTNO_SIO0  ZYNQ_UART0_IRQ
#define    INTPRI_SIO0    -3
#define    INTATR_SIO0     0U
#define    INHNO_SIO1  ZYNQ_UART1_IRQ
#define    INTNO_SIO1  ZYNQ_UART1_IRQ
#define    INTPRI_SIO1    -2
#define    INTATR_SIO1     0U
#else
#error "SafeG is no supported yet!"
#endif

#elif defined(BOARD_ZEDBOARD)

/*
 * CPU clocks
 */
#define ZYNQ_CPU_6X4X_MHZ     667
#define ZYNQ_CPU_3X2X_MHZ     333
#define ZYNQ_CPU_2X_MHZ       222
#define ZYNQ_CPU_1X_MHZ       111

#define ZYNQ_CORE_CLK              ZYNQ_CPU_6X4X_MHZ
#define ZYNQ_PERIPHCLK             ZYNQ_CPU_3X2X_MHZ
#define MPCORE_GTM_CLOCK_FREQ_MHZ  ZYNQ_PERIPHCLK

/*
 * Tmer preescaler and load value to achieve 1ms per tick.
 * Note that the preescaler value must be representable with 8 bits;
 * and the load value must be a 32bit value.
 *
 * Private timers and watchdogs are clocked with PERIPHCLK which is 1/2 of
 * the CPU frequency. The formula is:
 *
 *    period = (preescaler + 1)(load + 1) / PERIPHCLK
 *      - period    = 1ms
 *      - periphclk = 333.333MHz
 *
 * For example:
 *      - preescaler = 0
 *      - load       = 333332
 */
#define MPCORE_WDT_PS_1MS    0U       // preescaler for private watchdog
#define MPCORE_WDT_LOAD_1MS  333332U  // load value for private watchdog

#ifndef TOPPERS_ENABLE_QEMU
#define MPCORE_TM_PS_1MS     0U       // preescaler for private timer
#define MPCORE_TM_LOAD_1MS   333332U  // load value for private timer
#else
#define MPCORE_TM_PS_1MS     0U     // preescaler for private timer
#define MPCORE_TM_LOAD_1MS   100000U  // load value for private timer
#endif /* TOPPERS_ENABLE_QEMU */

/*
 * Definition of the 115200bps baud rate constants
 *        rate = clk / (CD * (BDIV + 1))
 *         clk = MR.CLKSEL? inclk : inclk/8  (e.g. inclk)
 *       inclk = MR.CCLK? uart_clock : apb clock (e.g. uart_clock=50MHz)
 *
 * Note: Linux values(in Zedboard)
 *   XUARTPS_BAUDGEN_REG: 0x3E
 *   XUARTPS_BAUDDIV_REG: 0x6
 *   XUARTPS_MR_REG: 0x20
 *   XUARTPS_RXWM_REG: 0x20
 *   XUARTPS_RXTOUT_REG: 0xA
 *   XUARTPS_CR_REG: 0x114
 */
#define UART_BAUD_115K          0x56  /* 0x56 (50MHz) or 0x11 (33.3MHz) */
#define UART_BAUDDIV_115K       0x4   /* 0x4 (50MHz) or 0x6 (33.3MHz) */

/*
 * Memory base address and size
 */
#define DDR_ADDR 0x00000000
#define DDR_SIZE 0x20000000 /* 512MB */

/*
 *  UART base address definitions (used in target_serial.c)
 *
 *  Note: When using SafeG, G_SYSLOG is defined (see Makefile.target) so
 *  we select a single UART for each world (e.g. Secure uses UART0
 *  and Nonsecure uses UART1).
 */
#ifdef TOPPERS_NOSAFEG
#define     UART0_BASE  ZYNQ_UART1_BASE
#define     UART1_BASE  ZYNQ_UART0_BASE
#elif defined(TOPPERS_SAFEG_SECURE)
#define     UART0_BASE  ZYNQ_UART0_BASE
#elif defined(TOPPERS_SAFEG_NONSECURE)
#define     UART0_BASE  ZYNQ_UART1_BASE
#else
#error "Check your Makefile.target"
#endif

/*
 *  UART interrupt handler definitions (used in target_serial.cfg)
 *     INHNO: interrupt handler number
 *     INTNO: interrupt number
 *     INTPRI: interrupt priority (lower means higher priority)
 *     INTATR: interrupt attributes (0 means not enabled at the beginning)
 *
 *  Note: When using SafeG, G_SYSLOG is defined (see Makefile.target) so
 *  we select a single UART for each world (e.g. Secure uses UART0
 *  and Nonsecure uses UART1).
 */
#ifdef TOPPERS_NOSAFEG
#define    INHNO_SIO0  ZYNQ_UART1_IRQ
#define    INTNO_SIO0  ZYNQ_UART1_IRQ
#define    INTPRI_SIO0    -3
#define    INTATR_SIO0     0U
#define    INHNO_SIO1  ZYNQ_UART0_IRQ
#define    INTNO_SIO1  ZYNQ_UART0_IRQ
#define    INTPRI_SIO1    -2
#define    INTATR_SIO1     0U
#elif defined(TOPPERS_SAFEG_SECURE)
#define    INHNO_SIO0  ZYNQ_UART0_IRQ
#define    INTNO_SIO0  ZYNQ_UART0_IRQ
#define    INTPRI_SIO0    -19
#define    INTATR_SIO0     0U
#elif defined(TOPPERS_SAFEG_NONSECURE)
#define    INHNO_SIO0  ZYNQ_UART1_IRQ
#define    INTNO_SIO0  ZYNQ_UART1_IRQ
#define    INTPRI_SIO0    -2
#define    INTATR_SIO0     0U
#else
#error "Check your Makefile.target"
#endif


/*
 *  Map the UART0 to MIO 10-11
 */
#define UART0_MIO10_11

#else
#error Specifi target board.
#endif 

/*
 * Available UARTs
 */
#define ZYNQ_UART0_BASE 0xE0000000
#define ZYNQ_UART1_BASE 0xE0001000
#define ZYNQ_UART0_IRQ  (59)
#define ZYNQ_UART1_IRQ  (82)

/*
 *  MPCore Private Memory Region Base Address (Table 4.7 in ZYNQ manual)
 */
#define MPCORE_PMR_BASE  0xF8F00000

/*
 *  GIC Base Address
 */
#define GICC_BASE		(MPCORE_PMR_BASE + 0x0100)
#define GICD_BASE		(MPCORE_PMR_BASE + 0x1000)

/*
 *  Number of interrupts supported by the GICv1.0 in this board. Note
 *  that these values could be obtained dynamically from the corresponding
 *  GIC register.
 */
#define GIC_TNUM_INTNO		96U

/*
 *  L2(PL310) Base Address
 */
#define PL310_L2CACHE_BASE	0xF8F02000

#ifndef TOPPERS_MACRO_ONLY

/*
 *  Trace log definitions (TODO: not tested)
 *
 *  TRACE_GET_TIM returns microseconds and uses the lower part of the
 *  global timer counter (32bit). This means that only around 12.89 seconds
 *  (0xFFFFFFFF/333 us) of trace can be taken until the counter wraps around.
 *
 *  Note: For traces that take more time, comment the TRACE_HW_INIT and
 *  TRACE_GET_TIM. As defined in trace_config.h, get_my_current_time()
 *  will be used instead. This allows taking a very long trace log (up to
 *  49,7 days) but the resolution will be in the milliseconds order.
 */
#ifndef MPCORE_GTC_COUNT_L
#define MPCORE_GTC_COUNT_L (MPCORE_PMR_BASE + 0x0200)
#endif

#define TRACE_HW_INIT() x_init_pcc()
#define TRACE_GET_TIM() (*((volatile uint32_t *)(MPCORE_GTC_COUNT_L)) / (MPCORE_GTC_CLOCK_FREQ_MHZ))

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  OCM Address
 */
#define OCM_ADDR  0xFFFF0000

/*
 *  Boot address memory
 */
#define BOOT_MEM_ADDR 0xFFFFFFF0

#endif /* TOPPERS_ZYNQ_H */
