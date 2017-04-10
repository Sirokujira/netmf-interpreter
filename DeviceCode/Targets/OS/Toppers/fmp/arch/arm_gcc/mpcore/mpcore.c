/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2006-2016 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: mpcore.c 1202 2016-07-18 06:36:33Z ertl-honda $
 */

#include "kernel_impl.h"

/*
 * SCU関連の関数
 */

/*
 *  CP15のAUXILIARYレジスタのSAビットとFWビットをセットしてSMPモードにする
 */
Inline void
enable_sa(void){
#if (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7)
	uint32_t bits;

	CP15_AUXILIARY_READ(bits);
	bits |= CP15_AUXILIARY_SA_BIT;
#if __TARGET_ARCH_ARM == 7
	bits |= CP15_AUXILIARY_FW_BIT;
#endif /* __TARGET_ARCH_ARM == 7 */
	CP15_AUXILIARY_WRITE(bits);
#elif (__TARGET_ARCH_ARM == 8)
	uint32_t cpuectlr_l, cpuectlr_h;

	CP15_CPUECTLR_READ(cpuectlr_l, cpuectlr_h);
	cpuectlr_l |= CPUECTLR_SMPEN;
	CP15_CPUECTLR_WRITE(cpuectlr_l, cpuectlr_h);
#endif /* (__TARGET_ARCH_ARM == 6) || (__TARGET_ARCH_ARM == 7) */
}

Inline void
scu_enable(void){
	uint32_t scu_ctrl;

	/* SCUの tag RAMS を無効に */
	sil_wrw_mem((void*)MPCORE_SCU_IALL, MPCORE_SCU_IALL_WAYS);

	/* SCUを有効に */
	scu_ctrl  = sil_rew_mem((void *)MPCORE_SCU_CTRL);
	scu_ctrl |= MPCORE_SCU_CTRL_EN;
	sil_wrw_mem((void *)MPCORE_SCU_CTRL, scu_ctrl);
}

/*
 *  SCUの初期化処理（マスタプロセッサのみ実行）
 */
void
scu_init(void){
	/* SCU を有効に */
	scu_enable();

	/* 全てのコアのモードをNORMALとする */
	sil_wrw_mem((void *)MPCORE_SCU_CPUST, 0x00U);

#ifdef TOPPERS_SAFEG_SECURE
	/* ノントラスト側からのA9内蔵プライベートタイマとWDTへのアクセスを許可 */
	sil_wrw_mem((void *)MPCORE_SCU_SNSAC, 0xFF); // 全CPUを許可
#endif /* TOPPERS_SAFEG_SECURE */
}

/*
 *  SMPモードに設定する
 */
void
smp_mode_enable(void){
	uint32_t sr;

	/* 全割込み禁止 */
	sr = current_sr();
	set_sr(sr|CPSR_IRQ_BIT|CPSR_FIQ_BIT);

	/* キャシュを無効 */
	dcache_clean_and_invalidate();
	icache_invalidate();

	/* Data Synchronization Barrier */
	data_sync_barrier();

	/* TLBの初期化 */
	invalidate_unfied_tlb();

#ifndef TOPPERS_SAFEG_NONSECURE
	/* CP15のSMP/nAMP bit をセットする */
	enable_sa();
#endif /* TOPPERS_SAFEG_NONSECURE */

	/* 割込み禁止状態を元に戻す */
	set_sr(sr);
}

#if __TARGET_ARCH_ARM == 6
/*
 * SCUカウンタの初期化（MN0を使用）
 */
void
scu_counter_init(void)
{
	/*
	 *  MN0を Cycle Count に設定
	 */
	sil_wrw_mem((void *)MPCORE_SCU_PM_EVT0,
				sil_rew_mem((void *)MPCORE_SCU_PM_EVT0) | MPCORE_SCU_PM_EVT_CYC_COUNT0_4);

	/*
	 *  リセットとスタート
	 */
	sil_wrw_mem((void *)MPCORE_SCU_PM_CTRL,
			sil_rew_mem((void *)MPCORE_SCU_PM_CTRL) | MPCORE_SCU_PM_CTRL_RST | MPCORE_SCU_PM_CTRL_ENA);
}
#endif /* __TARGET_ARCH_ARM == 6 */
