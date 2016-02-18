/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2012-2013 by Embedded and Real-Time Systems Laboratory
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
 *  the ZYNQ ZED board, such as the memory address, clock values,
 *  or number of interrupts.
 *
 */
#ifndef TOPPERS_ZYNQ_H
#define TOPPERS_ZYNQ_H

#include <sil.h>

/*
 * CPU clocks
 */
#define ZYNQ_CPU_6X4X_MHZ     667
#define ZYNQ_CPU_3X2X_MHZ     333
#define ZYNQ_CPU_2X_MHZ       222
#define ZYNQ_CPU_1X_MHZ       111

#define ZYNQ_CORE_CLK              ZYNQ_CPU_6X4X_MHZ
#define ZYNQ_PERIPHCLK             ZYNQ_CPU_3X2X_MHZ
#define MPCORE_GTC_CLOCK_FREQ_MHZ  ZYNQ_PERIPHCLK

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
 * Available UARTs
 */
#define ZYNQ_UART0_BASE 0xE0000000
#define ZYNQ_UART1_BASE 0xE0001000
#define ZYNQ_UART0_IRQ  (59)
#define ZYNQ_UART1_IRQ  (82)

/*
 * Memory base address and size
 */
#define DDR_ADDR 0x00000000
#define DDR_SIZE 0x10000000 /* 256MB */

/*
 *  MPCore Private Memory Region Base Address (Table 4.7 in ZYNQ manual)
 */
#define MPCORE_PMR_BASE  0xF8F00000

/*
 *  Number of interrupts supported by the GICv1.0 in this board. Note
 *  that these values could be obtained dynamically from the corresponding
 *  GIC register.
 */
#define DIC_TMIN_INTNO    0U
#define DIC_TMAX_INTNO   95U // maximum interrupt ID
#define DIC_TNUM_INT     96U // maximum number of interrupts

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
