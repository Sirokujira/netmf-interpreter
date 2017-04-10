/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_config.h 1202 2016-07-18 06:36:33Z ertl-honda $
 */

/*
 *  チップ依存モジュール（MPCORE用）
 *
 *  カーネルのチップ依存部のインクルードファイル．kernel_impl.hのター
 *  ゲット依存部の位置付けとなる．
 */

#ifndef TOPPERS_CHIP_CONFIG_H
#define TOPPERS_CHIP_CONFIG_H

/*
 *  チップ依存部ののハードウェア資源の定義
 */
#include "mpcore.h"

/*
 *  GIC依存モジュール
 */
#include "arm_gcc/common/gic_kernel.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  自プロセッサのAPCBへのポインタの取得
 *  インクルード順序の関係上，target_pcb.h には記述できないためここで定義する．
 */
Inline APCB*
get_my_p_apcb(void)
{
	return &((get_my_p_tpcb())->arm_pcb);
}

/*
 *  割込みハンドラの設定
 *
 *  割込みハンドラ番号inhnoの割込みハンドラの起動番地をinthdrに設定する
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry, uint_t affinity_mask)
{
#if TMIN_INTNO == 0
		assert((INHNO_MASK(inhno) <= TMAX_INHNO));
#else /* !TMIN_INTNO == 0 */
	assert(((TMIN_INHNO <= INHNO_MASK(inhno)) && (INHNO_MASK(inhno) <= TMAX_INHNO)));
#endif /* TMIN_INTNO == 0 */
}

/*
 *  割込みハンドラの出入口処理の生成マクロ
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr)

#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  str_ker() の前でマスタプロセッサで行う初期化
 */
extern void chip_mprc_initialize(void);

/*
 *  チップ依存の初期化
 */
extern void chip_initialize(void);

/*
 *  チップ依存部の終了
 *
 *  システムを終了する時に使う．
 */
extern void chip_exit(void);

/*
 *  未定義の割込みが入った場合の処理
 */
extern void default_int_handler(void);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ARM依存モジュール
 */
#include "arm_gcc/common/core_config.h"

#endif /* TOPPERS_CHIP_CONFIG_H */
