/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_config.c 1202 2016-07-18 06:36:33Z ertl-honda $
 */

/*
 * ターゲット依存モジュール（MPCORE用）
 */

#include "kernel_impl.h"
#include <sil.h>
#include "mp.h"
#include "target_ipi.h"

#ifdef TOPPERS_ENA_PERF
extern PERFCNT perf_boot_time[];
#endif /* TOPPERS_ENA_PERF */


/*
 *  str_ker() の実行前にマスタプロセッサのみ実行される初期化処理
 */
void
chip_mprc_initialize(void)
{
#ifdef TOPPERS_ENA_PERF
	x_get_pcc(&perf_boot_time[0]);
	x_rst_pcc();
#endif /* TOPPERS_ENA_PERF */

	/*
	 *  GICディストリビュータの初期化
	 */
	gicd_initialize();

	/*
	 *  SCUの初期化
	 */
	scu_init();

#ifdef USE_GIC_CPULOCK
	/*
	 *  CPUロックフラグ実現のための変数の初期化
	 */
	(get_my_p_tpcb())->lock_flag = true;
	(get_my_p_tpcb())->saved_iipm = IIPM_ENAALL;
#endif /* USE_GIC_CPULOCK */
}

/*
 *  ベクターテーブル（core_support.S）
 */
extern void *vector_table;

/*
 *  チップ依存の初期化
 */
void
chip_initialize(void)
{
	TPCB *p_tpcb = get_my_p_tpcb();
	uint32_t index = x_prc_index();

#ifdef TOPPERS_ENA_PERF
	if (x_sense_mprc()) {
		x_get_pcc(&perf_boot_time[1]);
		x_rst_pcc();
	}
#endif /* TOPPERS_ENA_PERF */

	/*
	 * ARM依存の初期化
	 */
	core_initialize();

	/*
	 * キャッシュを無効に
	 */
	cache_disable();

	/*
	 *  ブランチプリディクタを全無効化
	 */
	bpi_invalidate_all();

	/*
	 * MMUを有効に
	 */
	mmu_init();

	/*
	 * SMPモードへ
	 */
	smp_mode_enable();

	/*
	 * キャッシュを有効に
	 */
	cache_enable();

	/*
	 *  ブランチプリディクタを有効化
	 */
	btac_enable();

	/*
	 *  GICの各コアのSGIとPPIの設定
	 */
	gicd_sgi_ppi_init();

	/*
	 *  GICのCPUインタフェース初期化
	 */
	gicc_initialize();

	/*
	 *  割込みハンドラテーブルへのポインタの初期化
	 */
	p_tpcb = get_my_p_tpcb();
	p_tpcb->p_inh_tbl = p_inh_table[index];

#ifndef OMIT_VBAR_SETUP
	CP15_SET_VBAR((uint32_t) &vector_table);
#endif /* OMIT_VBAR_SETUP */

#ifdef TOPPERS_ENA_PERF
	if (x_sense_mprc()) {
		x_get_pcc(&perf_boot_time[2]);
		x_rst_pcc();
	}
#endif /* TOPPERS_ENA_PERF */
}

/*
 *  チップ依存の終了処理
 */
void
chip_exit(void)
{
	/*
	 *  ARM依存の終了処理
	 */
	core_terminate();

	/*
	 *  DICのCPUインタフェースを停止
	 */
	gicc_terminate();

	/*
	 *  DICのDISインタフェースを停止
	 */
	if (x_sense_mprc()) {
		gicd_terminate();
	}
}

#ifndef OMIT_DEFAULT_INT_HANDLER

/*
 *  未定義の割込みが入った場合の処理
 */
void
default_int_handler(void){
	ID prc_id = ID_PRC(x_prc_index());
	
	syslog_1(LOG_EMERG, "Processor %d : Unregistered Interrupt occurs.", prc_id);
	target_exit();
}

#endif /* OMIT_DEFAULT_INT_HANDLER */

#ifdef TOPPERS_ENA_PERF
void
perf_boot_init(void)
{
	if (x_sense_mprc()) {
		x_init_pcc();
		x_rst_pcc();
	}
}
#endif /* TOPPERS_ENA_PERF */
