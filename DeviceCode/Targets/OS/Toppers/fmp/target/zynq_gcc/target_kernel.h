/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2006-2017 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_kernel.h 1067 2014-12-24 14:15:10Z ertl-honda $
 */

/*
 *  This file is included by kernel.h just after including
 *  t_stddef.h.
 */
#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

#include "zynq.h"

/*
 *  Method for managing the system time
 */
#define TOPPERS_SYSTIM_LOCAL /* use timers that are local to each CPU*/
//#define TOPPERS_SYSTIM_GLOBAL /* use a global timer for all CPUs */

/*
 *  Master processor
 */
#define TOPPERS_MASTER_PRCID  1

/*
 *  Processor ID that manages the system time when using a global timer
 */
#define TOPPERS_SYSTIM_PRCID  TOPPERS_MASTER_PRCID

/*
 * Default number of processors (this value can be overwritten in the
 * application's Makefile with the desired number of processors)
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif /* TNUM_PRCID */

/*
 *  Definition of the CLASS IDs which are used to assign tasks to processors
 *  statically at initialization.
 */
#define TCL_1          1 /* Assign tasks in TCL_1 to processor 1 */
#define TCL_2          2 /* Assign tasks in TCL_2 to processor 2 */
#define TCL_1_ONLY     3 /* The same but the task cannot migrate */
#define TCL_2_ONLY     4 /* The same but the task cannot migrate */
#define TCL_SYSTIM_PRC 5 /* Used for global system timer event handler */

/*
 *  Numbers for software generated interrupts SGI
 */
#ifdef TOPPERS_SAFEG_SECURE
#define IPINO_DIS  UINT_C(14)
#define IPINO_EXT  UINT_C(15)
#else  /* !TOPPERS_SAFEG_SECURE */
#define IPINO_DIS  UINT_C(0)
#define IPINO_EXT  UINT_C(1)
#endif /* TOPPERS_SAFEG_SECURE */

/*
 *  SafeG COM shared memory address and size
 */
#define SAFEG_COM_MEM_ADDR  0x1b000000
#define SAFEG_COM_MEM_SIZE  16

/*
 *  Include shared definitions with the chip-dependent code
 */
#include "arm_gcc/mpcore/chip_kernel.h"

#endif /* TOPPERS_TARGET_KERNEL_H */
