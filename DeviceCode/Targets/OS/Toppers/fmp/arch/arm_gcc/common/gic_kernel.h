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
 *  $Id: gic_kernel.h 1203 2016-07-18 07:05:08Z ertl-honda $
 */

/*
 *		カーネルの割込みコントローラ依存部（GIC用）
 *
 *  このヘッダファイルは，target_config.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_GIC_KERNEL_H
#define TOPPERS_GIC_KERNEL_H

#include <sil.h>
#include "arm.h"

/*
 *  割込み番号のマスク（下位16bitのみが有効）
 */
#define INTNO_MASK(intno) (intno & 0xffffU)

/*
 *  割込み番号の接続プロセッサのプロセッサID（上位16bit）
 */
#define INTNO_PRCID(intno) (intno >> 16U)

/*
 *  割込みハンドラ番号のマスク（下位16bitのみが有効）
 */
#define INHNO_MASK(intno) (intno & 0xffffU)

/*
 *  割込み番号の数，最小値と最大値
 */
#define TNUM_INT		GIC_TNUM_INTNO
#define TMIN_INTNO		UINT_C(0)
#define TMAX_INTNO		(GIC_TNUM_INTNO - 1)

/*
 *  割込みハンドラ番号の数
 */
#define TNUM_INH		GIC_TNUM_INTNO
#define TMIN_INHNO		UINT_C(0)
#define TMAX_INHNO		(GIC_TNUM_INTNO - 1)

/*
 *  割込み番号の定義
 */
#define GIC_INTNO_SGI0		0U
#define GIC_INTNO_PPI0		16U
#define GIC_INTNO_SPI0		32U

/*
 *  割込み優先度の操作
 *
 *  割込み優先度の内部表現は，uint_t型で表し，0が最高優先度で，値が大き
 *  いほど優先度が下がるものとする．GICのレジスタ構成と整合させるために，
 *  優先度の段数が256段階の時にあわせて表す．
 */
#ifndef GIC_PRI_LEVEL
#define GIC_PRI_LEVEL		(TMAX_INTPRI - TMIN_INTPRI + 2)
#endif /* GIC_PRI_LEVEL */

#if GIC_PRI_LEVEL == 16
#define GIC_PRI_SHIFT		4
#define GIC_PRI_MASK		UINT_C(0x0f)
#elif GIC_PRI_LEVEL == 32
#define GIC_PRI_SHIFT		3
#define GIC_PRI_MASK		UINT_C(0x1f)
#elif GIC_PRI_LEVEL == 64
#define GIC_PRI_SHIFT		2
#define GIC_PRI_MASK		UINT_C(0x3f)
#elif GIC_PRI_LEVEL == 128
#define GIC_PRI_SHIFT		1
#define GIC_PRI_MASK		UINT_C(0x7f)
#elif GIC_PRI_LEVEL == 256
#define GIC_PRI_SHIFT		0
#define GIC_PRI_MASK		UINT_C(0xff)
#else
#error Invalid number of priority levels for GIC.
#endif /* GIC_PRI_LEVEL == 16 */

/* 外部表現への変換 */
#define EXT_IPM(pri) \
			(((PRI)((pri) >> GIC_PRI_SHIFT)) - (GIC_PRI_LEVEL - 1))

/* 内部表現への変換 */
#define INT_IPM(ipm) \
			(((uint_t)((ipm) + (GIC_PRI_LEVEL - 1))) << GIC_PRI_SHIFT)

/*
 *  GICレジスタのアドレスを定義するためのマクロ
 *
 *  GICレジスタのアドレスを，アセンブリ言語からも参照できるようにするた
 *  めのマクロ．
 */
#ifndef GIC_REG
#define GIC_REG(base, offset)	((uint32_t *)((base) + (offset ## U)))
#endif /* GIC_REG */

/*
 *  CPUインタフェース関連の定義
 */
#define GICC_CTLR		GIC_REG(GICC_BASE, 0x00)
#define GICC_PMR		GIC_REG(GICC_BASE, 0x04)
#define GICC_BPR		GIC_REG(GICC_BASE, 0x08)
#define GICC_IAR		GIC_REG(GICC_BASE, 0x0C)
#define GICC_EOIR		GIC_REG(GICC_BASE, 0x10)
#define GICC_RPR		GIC_REG(GICC_BASE, 0x14)
#define GICC_HPIR		GIC_REG(GICC_BASE, 0x18)

/*
 *  CPUインタフェース制御レジスタ（GICC_CTLR）の設定値（GICv1でセキュリ
 *  ティ拡張がない場合）
 */
#define GICC_CTLR_DISABLE		UINT_C(0x00)
#define GICC_CTLR_ENABLE		UINT_C(0x01)

/*
 *  CPUインタフェース制御レジスタ（GICC_CTLR）の設定値（GICv2でセキュリ
 *  ティ拡張がない場合か，拡張がある場合のセキュアモード）
 */
#ifdef TOPPERS_SAFEG_SECURE
#define GICC_CTLR_ENABLEGRP0	UINT_C(0x01)
#define GICC_CTLR_ENABLEGRP1	UINT_C(0x02)
#define GICC_CTLR_FIQEN			UINT_C(0x08)
#define GICC_CTLR_CBPR			UINT_C(0x10)
#endif /* TOPPERS_SAFEG_SECURE */

/*
 *  ディストリビュータ関連の定義
 */
#define GICD_CTLR			GIC_REG(GICD_BASE, 0x000)
#define GICD_TYPER			GIC_REG(GICD_BASE, 0x004)
#define GICD_IIDR			GIC_REG(GICD_BASE, 0x008)
#define GICD_IGROUPR(n)		GIC_REG(GICD_BASE, 0x080 + (n) * 4)
#define GICD_ISENABLER(n)	GIC_REG(GICD_BASE, 0x100 + (n) * 4)
#define GICD_ICENABLER(n)	GIC_REG(GICD_BASE, 0x180 + (n) * 4)
#define GICD_ISPENDR(n)		GIC_REG(GICD_BASE, 0x200 + (n) * 4)
#define GICD_ICPENDR(n)		GIC_REG(GICD_BASE, 0x280 + (n) * 4)
#define GICD_ISACTIVER(n)	GIC_REG(GICD_BASE, 0x300 + (n) * 4)
#define GICD_ICACTIVER(n)	GIC_REG(GICD_BASE, 0x380 + (n) * 4)
#define GICD_IPRIORITYR(n)	GIC_REG(GICD_BASE, 0x400 + (n) * 4)
#define GICD_ITARGETSR(n)	GIC_REG(GICD_BASE, 0x800 + (n) * 4)
#define GICD_ICFGR(n)		GIC_REG(GICD_BASE, 0xc00 + (n) * 4)
#define GICD_NSCAR(n)		GIC_REG(GICD_BASE, 0xe00 + (n) * 4)
#define GICD_SGIR			GIC_REG(GICD_BASE, 0xf00)
#define GICD_CPENDSGIR(n)	GIC_REG(GICD_BASE, 0xf10 + (n) * 4)
#define GICD_SPENDSGIR(n)	GIC_REG(GICD_BASE, 0xf20 + (n) * 4)

/*
 *  ディストリビュータ制御レジスタ（GICD_CTLR）の設定値
 */
#define GICD_CTLR_DISABLE	UINT_C(0x00)
#define GICD_CTLR_ENABLE	UINT_C(0x01)

/*
 *  割込みコンフィギュレーションレジスタ（GICD_ICFGRn）の設定値
 *
 */
#define GICD_ICFGRn_LEVEL	UINT_C(0x00)
#define GICD_ICFGRn_EDGE	UINT_C(0x02)

/*
 *  ソフトウェア生成割込みのレジスタ（GICD_SGIR）の設定値
 */
#define GICD_SGIR_CPUTARGET_OFFSET UINT_C(16)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPUインタフェースの操作
 */

/*
 *  割込み優先度マスクを設定（priは内部表現）
 */ 
Inline void
gicc_set_priority(uint_t pri)
{
	sil_wrw_mem(GICC_PMR, pri);
}

/*
 *  割込み優先度マスクを取得（内部表現で返す）
 */ 
Inline uint_t
gicc_get_priority(void)
{
	return(sil_rew_mem(GICC_PMR));
}

/*
 *  CPUインタフェースの初期化
 */
extern void gicc_initialize(void);

/*
 *  CPUインタフェースの終了
 */
extern void gicc_terminate(void);

/*
 *  ディストリビュータの操作
 */

/*
 *  割込み禁止（割込みイネーブルのクリア）
 */
Inline void
gicd_disable_int(INTNO intno)
{
	sil_wrw_mem(GICD_ICENABLER(intno / 32), (1U << (intno % 32)));
}

/*
 *  割込み許可（割込みイネーブルのセット）
 */
Inline void
gicd_enable_int(INTNO intno)
{
	sil_wrw_mem(GICD_ISENABLER(intno / 32), (1U << (intno % 32)));
}

/*
 *  割込みペンディングのクリア
 */
Inline void
gicd_clear_pending(INTNO intno)
{
	sil_wrw_mem(GICD_ICPENDR(intno / 32), (1U << (intno % 32)));
}

/*
 *  割込みペンディングのセット
 */
Inline void
gicd_set_pending(INTNO intno)
{
	sil_wrw_mem(GICD_ISPENDR(intno / 32), (1U << (intno % 32)));
}

/*
 *  割込みペンディングのチェック
 */
Inline bool_t
gicd_probe_pending(INTNO intno)
{
	return((sil_rew_mem(GICD_ISPENDR(intno / 32)) & (1U << (intno % 32)))
																	!= 0U);
}

/*
 *  割込みのコンフィグレーション
 */
Inline void
gicd_config(INTNO intno, uint_t config)
{
	uint_t		shift = (intno % 16) * 2;
	uint32_t	reg;
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	reg = sil_rew_mem(GICD_ICFGR(intno / 16));
	reg &= ~(0x03U << shift);
	reg |= (config << shift);
	sil_wrw_mem(GICD_ICFGR(intno / 16), reg);
	SIL_UNL_SPN();
}

/*
 *  割込みグループの設定（セキュリティ拡張）
 */
Inline void
gicd_config_group(INTNO intno, uint_t group)
{
	uint_t		shift = intno % 32;
	uint32_t	reg;
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	reg = sil_rew_mem(GICD_IGROUPR(intno / 32));
	reg &= ~(0x01U << shift);
	reg |= (group << shift);
	sil_wrw_mem(GICD_IGROUPR(intno / 32), reg);
	SIL_UNL_SPN();
}

/*
 *  割込み要求ラインに対する割込み優先度の設定（priは内部表現）
 */
Inline void
gicd_set_priority(INTNO intno, uint_t pri)
{
	uint_t		shift = (intno % 4) * 8;
	uint32_t	reg;
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	reg = sil_rew_mem(GICD_IPRIORITYR(intno / 4));
	reg &= ~(0xffU << shift);
	reg |= (pri << shift);
	sil_wrw_mem(GICD_IPRIORITYR(intno / 4), reg);
	SIL_UNL_SPN();
}

/*
 *  割込みターゲットプロセッサの設定
 *
 *  prcsは，ターゲットとするプロセッサを表すビットのビット毎論理和で指
 *  定する．
 *		プロセッサ0 : 0x01
 *		プロセッサ1 : 0x02
 *		プロセッサ2 : 0x04
 *		プロセッサ3 : 0x08
 */
Inline void
gicd_set_target(INTNO intno, uint_t prcs)
{
	uint_t		shift = (intno % 4) * 8;
	uint32_t	reg;
	SIL_PRE_LOC;

	SIL_LOC_SPN();
	reg = sil_rew_mem(GICD_ITARGETSR(intno / 4));
	reg &= ~(0xffU << shift);
	reg |= (prcs << shift);
	sil_wrw_mem(GICD_ITARGETSR(intno / 4), reg);
	SIL_UNL_SPN();
}

/*
 *  ソフトウェア割込みを発行
 */
Inline void
gicd_set_sgi(int cpu, int id)
{
	CP15_DATA_SYNC_BARRIER();
	sil_wrw_mem(GICD_SGIR, (cpu << GICD_SGIR_CPUTARGET_OFFSET)|id);
	CP15_DATA_SYNC_BARRIER();
}

/*
 *  ディストリビュータの初期化
 */
extern void gicd_initialize(void);

/*
 *  各コアで実行するDICインタフェースのSGIとPPIの初期化
 */
extern void gicd_sgi_ppi_init(void);

/*
 *  ディストリビュータの終了
 */
extern void gicd_terminate(void);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  割込み番号の範囲の判定
 */
#if TMIN_INTNO == 0
#define VALID_INTNO(prcid, intno) ((INTNO_MASK(intno) <= TMAX_INTNO) \
                                    && (INTNO_PRCID(intno) == 0U || INTNO_PRCID(intno) == prcid))
#else /* !TMIN_INTNO == 0 */
#define VALID_INTNO(prcid, intno) (((TMIN_INTNO <= (INTNO_MASK(intno)) && (INTNO_MASK(intno)) <= TMAX_INTNO)) \
                                    && (INTNO_PRCID(intno) == 0U || INTNO_PRCID(intno) == prcid))
#endif /* TMIN_INTNO == 0 */

#define VALID_INTNO_DISINT(prcid, intno)	VALID_INTNO(prcid, intno)
#define VALID_INTNO_CFGINT(prcid, intno)	VALID_INTNO(prcid, intno)

/*
 *  ターゲット非依存部に提供する関数
 */
#ifndef TOPPERS_MACRO_ONLY

/*
 *  割込み優先度マスクの設定
 */
Inline void
x_set_ipm(PRI intpri)
{
	gicc_set_priority(INT_IPM(intpri));
}

#define t_set_ipm(intpri)    x_set_ipm(intpri)
#define i_set_ipm(intpri)    x_set_ipm(intpri)

/*
 *  割込み優先度マスクの参照
 */
Inline PRI
x_get_ipm(void)
{
	return(EXT_IPM(gicc_get_priority()));
}

#define t_get_ipm()    x_get_ipm()
#define i_get_ipm()    x_get_ipm()

/*
 *  割込み属性アクセステーブル
 *
 *  割込み属性テーブルへのポインタ．割込み属性テーブルは，割込み属性が設定
 *  されていれば"1"，設定されていなければ"0"となる
 */
extern const uint8_t  const global_cfgint_table[];     /* グローバル割込み用 */

extern const uint8_t* const p_private_cfgint_table[]; /* プライベート割込み用(コア毎) */

#define my_private_cfgint_table (p_private_cfgint_table[x_prc_index()])

/*
 * 割込み属性が設定されていない割込み要求ラインかチェックする
 */
Inline bool_t
x_check_cfgint(INTNO intno) {
	if (INTNO_MASK(intno) < GIC_INTNO_SPI0){
		/* プライベート割込みの場合 */
		if (my_private_cfgint_table[INTNO_MASK(intno)] == 0){
			return(false);
		}
	}
	else {
		/* グローバル割込みの場合 */
		if (global_cfgint_table[INTNO_MASK(intno) - GIC_INTNO_SPI0] == 0){
			return(false);
		}
	}
	return(true);
}

/*
 *  割込み要求禁止フラグのセット
 *
 *  intnoで指定された割込み要求ラインに対する割込み要求禁止フラグのセッ
 *  トし，割込みを禁止する．割込み属性が設定されていない割込み要求ライ
 *  ンが指定された場合には，falseを返す．
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	if (x_check_cfgint(intno) == 0U) {
		return(false);
	}
	gicd_disable_int(INTNO_MASK(intno));
	return(true);
}

#define t_disable_int(intno)  x_disable_int(intno)
#define i_disable_int(intno)  t_disable_int(intno)

/* 
 *  割込み要求禁止フラグのクリア
 *
 *  intnoで指定された割込み要求ラインに対する割込み要求禁止フラグのクリ
 *  アし，割込みを許可する．割込み属性が設定されていない割込み要求ライ
 *  ンが指定された場合には，falseを返す．
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	if (x_check_cfgint(intno) == 0U) {
		return(false);
	}
	gicd_enable_int(INTNO_MASK(intno));
	return(true);
}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 *  割込み要求のクリア
 */
Inline void
x_clear_int(INTNO intno)
{
	gicd_clear_pending(INTNO_MASK(intno));
}

#define t_clear_int(intno) x_clear_int(intno)
#define i_clear_int(intno) x_clear_int(intno)

/*
 *  割込み要求のチェック
 */
Inline bool_t
x_probe_int(INTNO intno)
{
	return(gicd_probe_pending(INTNO_MASK(intno)));
}

#define t_probe_int(intno) x_probe_int(intno)
#define i_probe_int(intno) x_probe_int(intno)

/*
 *  割込み要求ラインの属性の設定
 *
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask);

/*
 *  割込みハンドラの登録用テーブル（kernel_cfg.c）
 */
extern const FP* const p_inh_table[TNUM_PRCID];

/*
 * 割込みハンドラの入り口で必要なIRC操作
 *
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 * 割込みハンドラの出口で必要なIRC操作
 */
Inline void
i_end_int(INTNO intno)
{
}

#ifdef USE_IPI_DIS_HANDER_BYPASS
#define OMIT_KER_REQ_ON_IPI

/*
 *  カーネル終了処理要求
 */
extern void ext_ker_request(void);
#endif /* USE_IPI_DIS_HANDER_BYPASS */

#ifdef USE_GIC_CPULOCK

/*
 *  USE_GIC_CPULOCK時の設定
 */

/*
 *  TIPM_ENAALL（割込み優先度マスク全解除）の内部表現
 */
#define IIPM_ENAALL        (INT_IPM(TIPM_ENAALL))

#define IIPM_LOCK 0x00

#ifndef TOPPERS_MACRO_ONLY

/*
 *  IPM（ハードウェアの割込み優先度マスク，内部表現）の現在値の読出し
 */
Inline uint8_t
current_iipm(void)
{
	return(gicc_get_priority());
}

/*
 *  IPM（ハードウェアの割込み優先度マスク，内部表現）の現在値の設定
 */
Inline void
set_iipm(uint8_t iipm)
{
	gicc_cpu_set_priority(iipm);
}

/*
 *  コンテキストの参照(USE_GIC_CPULOCK時)
 *
 *  ARMでは，タスクコンテキストと非タスクコンテキストの両方をスーパー
 *  バイザーモードで動作させる．そのため，CPSRの内容では判別できない．
 *  そのため，例外（割込み/CPU例外）のネスト回数をカウントする変数
 *  （excpt_nest_count）を用意し，例外の入り口でインクリメントすること
 *  で，コンテキストを判定する．
 */
Inline bool_t
sense_context(void)
{
	uint32_t tmp;
	uint8_t saved_iipm;
	APCB* my_p_apcb;

	/*
	 *  マイグレーションされることを考慮して割込みを禁止してからチェッ
	 *  クする．
	 */
	saved_iipm = current_iipm();
	set_iipm(IIPM_LOCK);
	ARM_MEMORY_CHANGED;
	my_p_apcb = get_my_p_apcb();
	tmp = my_p_apcb->excpt_nest_count;
	set_iipm(saved_iipm);
	ARM_MEMORY_CHANGED;

	return(tmp > 0U);
}

/*
 *  CPUロック状態への移行(USE_GIC_CPULOCK時)
 *
 *  IPM（ハードウェアの割込み優先度マスク）を，saved_iipmに保存し，カー
 *  ネル管理外のものを除くすべての割込みをマスクする値（TIPM_LOCK）に設
 *  定する．また，lock_flagをtrueにする．
 *
 *  IPMが，最初からTIPM_LOCKと同じかそれより高い場合には，それを
 *  saved_iipmに保存するのみで，TIPM_LOCKには設定しない．これはモデル
 *  上の割込み優先度マスクが，TIPM_LOCKと同じかそれより高いレベルに設定
 *  されている状態にあたる．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）で呼ばれることは
 *  ないものと想定している．
 */
Inline void
x_lock_cpu(void)
{
	uint8_t iipm;

	/*
	*  current_iipm()の返り値を直接saved_iipmに保存せず，一時変数iipm
	*  を用いているのは，current_iipm()を呼んだ直後に割込みが発生し，
	*  起動された割込み処理でsaved_iipmが変更される可能性があるためで
	*  ある．
	*/
	iipm = current_iipm();
	set_iipm(IIPM_LOCK);
	get_my_p_tpcb()->saved_iipm = iipm;
	get_my_p_tpcb()->lock_flag = true;

	/* クリティカルセクションの前後でメモリが書き換わる可能性がある */
	ARM_MEMORY_CHANGED;
}

#define t_lock_cpu()    x_lock_cpu()
#define i_lock_cpu()    x_lock_cpu()

/*
 *  CPUロック状態の解除(USE_GIC_CPULOCK時)
 *
 *  lock_flagをfalseにし，IPM（ハードウェアの割込み優先度マスク）を，
 *  saved_iipmに保存した値に戻す．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）でのみ呼ばれるも
 *  のと想定している．
 */
Inline void
x_unlock_cpu(void)
{
	/* クリティカルセクションの前後でメモリが書き換わる可能性がある */
	ARM_MEMORY_CHANGED;
	get_my_p_tpcb()->lock_flag = false;
	set_iipm(get_my_p_tpcb()->saved_iipm);
}

#define t_unlock_cpu()    x_unlock_cpu()
#define i_unlock_cpu()    x_unlock_cpu()

/*
 *  CPUロック状態の参照(USE_GIC_CPULOCK時)
 */
Inline bool_t
x_sense_lock(void)
{
	return(get_my_p_tpcb()->lock_flag);
}

#define t_sense_lock()    x_sense_lock()
#define i_sense_lock()    x_sense_lock()


/*
 * （モデル上の）割込み優先度マスクの設定(USE_GIC_CPULOCK時)
 *
 *  CPUロックフラグがクリアされている時は，ハードウェアの割込み優先度マ
 *  スクを設定する．CPUロックフラグがセットされている時は，saved_iipm
 *  を設定し，さらに，ハードウェアの割込み優先度マスクを，設定しようと
 *  した（モデル上の）割込み優先度マスクとTIPM_LOCKの高い方に設定する．
 */
Inline void
x_set_ipm(PRI intpri)
{
	uint8_t   iipm = INT_IPM(intpri);

	if (!get_my_p_tpcb()->lock_flag) {
		set_iipm(iipm);
	}
	else {
		get_my_p_tpcb()->saved_iipm = iipm;
		/*
		 *  OS内からのみ呼び出されるため，この時点でハードウェアの割込み優先
		 *  度マスクが必ず最大値に設定されているため，設定する必要はない．
		 */
	}
}

#define t_set_ipm(intpri)    x_set_ipm(intpri)
#define i_set_ipm(intpri)    x_set_ipm(intpri)

/*
 * （モデル上の）割込み優先度マスクの参照(USE_GIC_CPULOCK時)
 *
 *  CPUロックフラグがクリアされている時はハードウェアの割込み優先度マ
 *  スクを，セットされている時はsaved_iipmを参照する．
 */
Inline PRI
x_get_ipm(void)
{
	uint8_t iipm;

	if (!get_my_p_tpcb()->lock_flag) {
		iipm = current_iipm();
	}
	else {
		iipm = get_my_p_tpcb()->saved_iipm;
	}
	return(EXT_IPM(iipm));
}

#define t_get_ipm()    x_get_ipm()
#define i_get_ipm()    x_get_ipm()

/*
 *  CPU例外の発生した時の(モデル上の)割込み優先度マスクの参照(USE_GIC_CPULOCK時)
 */
Inline PRI
exc_get_ipm(void *p_excinf)
{
	if (!((exc_frame_t *)(p_excinf))->lock_flag) {
		return((PRI)(((exc_frame_t *)(p_excinf))->ipm));
	}
	else {
		return((PRI)(((exc_frame_t *)(p_excinf))->saved_iipm));
	}
}

/*
 * CPUロック状態か(USE_GIC_CPULOCK時)
 */
Inline bool_t
exc_sense_lock(void *p_excinf)
{
	return(((exc_frame_t *)(p_excinf))->lock_flag);
}

/*
 * 割込みロック状態か(USE_GIC_CPULOCK時)
 */
Inline bool_t
exc_sense_int_lock(void *p_excinf)
{
	return(((exc_frame_t *)(p_excinf))->lock_flag);
}

#endif /* TOPPERS_MACRO_ONLY */

#endif /* USE_GIC_CPULOCK */

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_GIC_KERNEL_H */
