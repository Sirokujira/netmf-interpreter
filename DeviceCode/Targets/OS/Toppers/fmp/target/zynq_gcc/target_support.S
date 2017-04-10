/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2013 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
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
 *  @(#) $Id: target_support.S 1203 2016-07-18 07:05:08Z ertl-honda $
 */

#define  TOPPERS_MACRO_ONLY
#include "kernel_impl.h"
#include "target_asm.inc"

#ifdef TOPPERS_SAFEG_SECURE
/* 
 *  First NT switch function.
 *  This function is copied to OCM at boot time.
 */
    ATEXT
    AALIGN(2)
    AGLOBAL(first_switch_to_nt)
    AGLOBAL(first_switch_to_nt_end)
ALABEL(first_switch_to_nt)
	my_core_index r0
	cmp   r0, #1
	beq   safeg_prc2_boot
	/* In case of Core0 */
	movw  r1, #(TARGET_CORE0_NS_START_ADDR & 0xffff)
	movt  r1, #((TARGET_CORE0_NS_START_ADDR >> 16) & 0xffff)
	bx    r1
safeg_prc2_boot:
	/* In case of Core0 */
	movw  r1, #(BOOT_MEM_ADDR & 0xffff)
	movt  r1, #((BOOT_MEM_ADDR >> 16) & 0xffff)
1:
	ldr   r0, [r1]
	cmp   r0, #0
	beq   1b
	mov   r2, #0
	str   r2, [r1]
	bx    r0
ALABEL(first_switch_to_nt_end)
#endif /* TOPPERS_SAFEG_SECURE */
