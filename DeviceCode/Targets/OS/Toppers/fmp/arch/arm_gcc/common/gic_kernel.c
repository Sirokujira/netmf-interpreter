/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2006-2016 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: gic_kernel.c 1203 2016-07-18 07:05:08Z ertl-honda $
 */

/*
 *		カーネルの割込みコントローラ依存部（GIC用）
 */

#include "kernel_impl.h"
#include "interrupt.h"
#include <sil.h>
#include "arm.h"
#include "mp.h"

/*
 *  CPUインタフェースの操作
 */

/*
 *  CPUインタフェースの初期化
 */
void
gicc_initialize(void)
{
	/*
	 *  CPUインタフェースをディスエーブル
	 */
	sil_wrw_mem(GICC_CTLR, GICC_CTLR_DISABLE);

	/*
	 *  割込み優先度マスクを最低優先度に設定
	 */
	gicc_set_priority((GIC_PRI_LEVEL - 1) << GIC_PRI_SHIFT);

	/*
	 *  割込み優先度の全ビット有効に
	 */
	sil_wrw_mem(GICC_BPR, 0U);

	/*
	 *  アクティブな割込みがあれば，EOIによりクリアする
	 */
	sil_wrw_mem(GICC_EOIR, sil_rew_mem(GICC_IAR));

	/*
	 *  CPUインタフェースをイネーブル
	 */
#ifdef TOPPERS_SAFEG_SECURE
	sil_wrw_mem(GICC_CTLR, (GICC_CTLR_FIQEN|GICC_CTLR_ENABLEGRP1
												|GICC_CTLR_ENABLEGRP0));
#else /* TOPPERS_SAFEG_SECURE */
	sil_wrw_mem(GICC_CTLR, GICC_CTLR_ENABLE);
#endif /* TOPPERS_SAFEG_SECURE */
}

/*
 *  CPUインタフェースの終了処理
 */
void
gicc_terminate(void)
{
	sil_wrw_mem(GICC_CTLR, GICC_CTLR_DISABLE);
}

/*
 *  ディストリビュータの操作
 */

/*
 *  ディストリビュータの初期化
 */
void
gicd_initialize(void)
{
	int		i;

	/*
	 *  ディストリビュータをディスエーブル
	 */
	sil_wrw_mem(GICD_CTLR, GICD_CTLR_DISABLE);

#ifdef TOPPERS_SAFEG_SECURE
	/*
	 *  すべての割込みをグループ1（IRQ）に設定
	 */
	for (i = GIC_INTNO_SPI0 / 32; i < (GIC_TNUM_INTNO + 31) / 32; i++) {
		sil_wrw_mem(GICD_IGROUPR(i), 0xffffffffU);
	}
#endif /* TOPPERS_SAFEG_SECURE */

	/*
	 *  すべての割込みを禁止
	 */
	for (i = GIC_INTNO_SPI0 / 32; i < (GIC_TNUM_INTNO + 31) / 32; i++) {
		sil_wrw_mem(GICD_ICENABLER(i), 0xffffffffU);
	}

	/*
	 *  すべての割込みペンディングをクリア
	 */
	for (i = GIC_INTNO_SPI0 / 32; i < (GIC_TNUM_INTNO + 31) / 32; i++) {
		sil_wrw_mem(GICD_ICPENDR(i), 0xffffffffU);
	}

	/*
	 *  すべての割込みを最低優先度に設定
	 */
	for (i = GIC_INTNO_SPI0 / 4; i < (GIC_TNUM_INTNO + 3) / 4; i++){
		sil_wrw_mem(GICD_IPRIORITYR(i), 0xffffffffU);
	}

	/*
	 *  すべての共有ペリフェラル割込みのターゲットをプロセッサ0に設定
	 */
	for (i = GIC_INTNO_SPI0 / 4; i < (GIC_TNUM_INTNO + 3) / 4; i++) {
		sil_wrw_mem(GICD_ITARGETSR(i), 0x01010101U);
	}

	/*
	 *  すべてのペリフェラル割込みをレベルトリガに設定
	 */
	for (i = GIC_INTNO_PPI0 / 16; i < (GIC_TNUM_INTNO + 15) / 16; i++) {
		sil_wrw_mem(GICD_ICFGR(i), 0x00000000U);
	}

	/*
	 *  ディストリビュータをイネーブル
	 */
	sil_wrw_mem(GICD_CTLR, GICD_CTLR_ENABLE);
}

/*
 *  ディストリビュータの終了処理
 */
void
gicd_terminate(void)
{
	sil_wrw_mem(GICD_CTLR, GICD_CTLR_DISABLE);
}

/*
 *  各コアで実行するDICインタフェースのSGIとPPIの初期化
 */
void
gicd_sgi_ppi_init(void)
{
	int i;
#ifdef TOPPERS_SAFEG_SECURE
	/*
	 *  全てNon-Secureにする
	 */
	/* SGIの設定 */
	for(i = GIC_INTNO_SGI0; i < GIC_INTNO_PPI0; i++) {
		gicd_config_group(i, 1);
	}
	/* PPIの設定 */
	for(i = GIC_INTNO_PPI0; i < GIC_INTNO_SPI0; i++) {
		gicd_config_group(i, 1);
	}
#endif /* TOPPERS_SAFEG_SECURE */

	/* 割込みを全て禁止 */
	for(i = 0; i < GIC_INTNO_SPI0/32; i++){
		sil_wrw_mem(GICD_ICENABLER(i), 0xffffffffU);
	}

	/* ペンディングをクリア */
	for(i = 0; i < GIC_INTNO_SPI0/32; i++){
		sil_wrw_mem(GICD_ICPENDR(i), 0xffffffffU);
	}

#ifdef TOPPERS_SAFEG_SECURE
	/* 優先度最低に設定  */
	/* Linuxが初期化しないため代わりに初期化 */
	for(i = 0; i < GIC_INTNO_SPI0/4; i++){
		/*
		 * 本来は0xffffffffでよいが，Linuxがセカンダリコア以降の
		 * コアの割込み優先度を設定しないため，ここで設定する．
		 * (Linuxでは，0xa0a0a0a0ですべての割込みを初期化しているが
		 *  ノンセキュア側からの優先度割込みはセキュア側から見ると
		 *  1ビットシフトし，上位ビットが1となったものに見えるため
		 *  0xd0d0d0d0の値になる)
		 */
		sil_wrw_mem(GICD_IPRIORITYR(i), 0xd0d0d0d0U);
	}
#else /* !TOPPERS_SAFEG_SECURE */
	/* 優先度最低に設定  */
	for(i = 0; i < GIC_INTNO_SPI0/4; i++){
		sil_wrw_mem(GICD_IPRIORITYR(i), 0xffffffffU);
	}
#endif /* TOPPERS_SAFEG_SECURE */

	/* モード初期化(1-N Level) */
	for(i = 0; i < GIC_INTNO_SPI0/16; i++){
		sil_wrw_mem(GICD_ICFGR(i), 0x00000000U);
	}
}

#ifndef OMIT_GIC_INITIALIZE_INTERRUPT

/*
 *  割込み要求ラインの属性の設定
 *
 *  ASPカーネルでの利用を想定して，パラメータエラーはアサーションでチェッ
 *  クしている．
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask)
{
	assert(VALID_INTNO_CFGINT(ID_PRC(x_prc_index()), intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/*
	 *  割込みを禁止
	 *
	 *  割込みを受け付けたまま，レベルトリガ／エッジトリガの設定や，割
	 *  込み優先度の設定を行うのは危険なため，割込み属性にかかわらず，
	 *  一旦マスクする．
	 */
	x_disable_int(intno);

	/*
	 *  割込みをコンフィギュレーション
	 */
#ifdef TOPPERS_SAFEG_SECURE
	gicd_config_group(INTNO_MASK(intno), 0U);
#endif /* TOPPERS_SAFEG_SECURE */

	if ((intatr & TA_EDGE) != 0U) {
		gicd_config(INTNO_MASK(intno), GICD_ICFGRn_EDGE);
		x_clear_int(intno);
	}
	else {
		gicd_config(INTNO_MASK(intno), GICD_ICFGRn_LEVEL);
	}

	/*
	 *  割込み優先度とターゲットプロセッサを設定
	 */
	gicd_set_priority(INTNO_MASK(intno), INT_IPM(intpri));

	/*
	 * ターゲットCPUの設定（グローバル割込みのみ）
	 */
	if (INTNO_MASK(intno) >= GIC_INTNO_SPI0) {
		gicd_set_target(INTNO_MASK(intno), (1 << x_prc_index()));
	}

	/*
	 * 割込みを許可
	 */
	if ((intatr & TA_ENAINT) != 0U) {
		x_enable_int(INTNO_MASK(intno));
	}
}
#endif /* OMIT_GIC_INITIALIZE_INTERRUPT */

#ifdef USE_IPI_DIS_HANDER_BYPASS

/*
 *  終了処理開始フラグ
 */
static bool_t ext_ker_reqflg;

/*
 *  カーネル終了処理要求
 */
void
ext_ker_request(void)
{
	ID prcid;
	volatile int i;

	/* すでに要求が出ていればリターン */
	if (ext_ker_reqflg) {
		return;
	}

	ext_ker_reqflg = true;

	for(prcid = 1; prcid <= TNUM_PRCID; prcid++){
		if (prcid != ID_PRC(x_prc_index())) {
			gicd_set_sgi((1<<(prcid-1)), IPINO_EXT);
			/*
			 * gicd_set_sgi()を連続して発行すると割込みを正しく付けないプロセッ
			 * サがいるためループを挿入
			 */
			for(i = 0; i < 10; i++);
		}
	}
}

/*
 *  カーネル終了処理用のプロセッサ間割込みハンドラ
 */
void
_kernel_ipi_ext_handler(void)
{
	ext_ker();
}
#endif /* USE_IPI_DIS_HANDER_BYPASS */
