/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2016 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: generic_timer.h 1203 2016-07-18 07:05:08Z ertl-honda $
 */

/*
 *  タイマドライバ（ARMv7 Generic Timer用）
 */

#ifndef TOPPERS_CORE_TIMER_H
#define TOPPERS_CORE_TIMER_H

#include <sil.h>

/*
 *  Generic Timer Register
 */
#define CNTHCTL_EL1PCEN_BIT		(1 << 1)
#define CNTHCTL_EL1PCTEN_BIT	(1 << 0)
#define CNTKCTL_EL0PTEN_BIT		(1 << 9)
#define CNTKCTL_EL0VTEN_BIT		(1 << 8)
#define CNTKCTL_EL0PCTEN_BIT	(1 << 0)
#define CNTKCTL_EL0VCTEN_BIT	(1 << 1)
#define CNTP_CTL_ISTATUS_BIT    (1 << 2)
#define CNTP_CTL_IMASK_BIT      (1 << 1)
#define CNTP_CTL_ENABLE_BIT     (1 << 0)
#define CNTPS_CTL_ISTATUS_BIT   (1 << 2)
#define CNTPS_CTL_IMASK_BIT     (1 << 1)
#define CNTPS_CTL_ENABLE_BIT    (1 << 0)
#define CNTV_CTL_ISTATUS_BIT    (1 << 2)
#define CNTV_CTL_IMASK_BIT      (1 << 1)
#define CNTV_CTL_ENABLE_BIT     (1 << 0)

/*
 *  ローカルタイマ方式用の定義
 */
#define INHNO_TIMER_PRC1     (0x00010000 | IRQNO_GTIM) /* 割込みハンドラ番号 */
#define INHNO_TIMER_PRC2     (0x00020000 | IRQNO_GTIM) /* 割込みハンドラ番号 */
#define INHNO_TIMER_PRC3     (0x00030000 | IRQNO_GTIM) /* 割込みハンドラ番号 */
#define INHNO_TIMER_PRC4     (0x00040000 | IRQNO_GTIM) /* 割込みハンドラ番号 */

#define INTNO_TIMER_PRC1     (0x00010000 | IRQNO_GTIM) /* 割込み番号 */
#define INTNO_TIMER_PRC2     (0x00020000 | IRQNO_GTIM) /* 割込み番号 */
#define INTNO_TIMER_PRC3     (0x00030000 | IRQNO_GTIM) /* 割込み番号 */
#define INTNO_TIMER_PRC4     (0x00040000 | IRQNO_GTIM) /* 割込み番号 */

/*
 *  グローバルタイマ方式用の定義
 */
#if TOPPERS_SYSTIM_PRCID == 1
#define INHNO_TIMER_SYSTIM    (0x00010000 | IRQNO_GTIM)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x00010000 | IRQNO_GTIM)  /* 割込み番号 */
#elif TOPPERS_SYSTIM_PRCID == 2
#define INHNO_TIMER_SYSTIM    (0x00020000 | IRQNO_GTIM)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x00020000 | IRQNO_GTIM)  /* 割込み番号 */
#elif TOPPERS_SYSTIM_PRCID == 3
#define INHNO_TIMER_SYSTIM    (0x00030000 | IRQNO_GTIM)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x00030000 | IRQNO_GTIM)  /* 割込み番号 */
#elif TOPPERS_SYSTIM_PRCID == 4
#define INHNO_TIMER_SYSTIM    (0x00040000 | IRQNO_GTIM)  /* 割込みハンドラ番号 */
#define INTNO_TIMER_SYSTIM    (0x00040000 | IRQNO_GTIM)  /* 割込み番号 */
#endif /* TOPPERS_SYSTIM_PRCID == 1 */

#define INTATR_TIMER    0U            /* 割込み属性 */

#ifndef INTPRI_TIMER
#define INTPRI_TIMER    -6            /* 割込み優先度 */
#endif /* INTPRI_TIMER */

#ifndef INTATR_TIMER
#define INTATR_TIMER    0U            /* 割込み属性 */
#endif /* INTATR_TIMER */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  タイマ値の内部表現の型
 */
typedef uint32_t CLOCK;

/*
 *  タイマのクロックを保持する変数
 *  単位はkHz
 *  target_initialize() で初期化される
 */
extern uint32_t timer_clock;

/*
 *  タイマの設定値
 */
extern uint64_t timer_cval[];

/*
 *  タイマ値の内部表現とミリ秒・μ秒単位との変換
 */
#define TO_CLOCK(nume, deno) (timer_clock * (nume) / (deno))
#define TO_USEC(clock)       (((SYSUTM) clock) * 1000U / timer_clock)

/*
 *  タイマの現在値を割込み発生前の値とみなすかの判断
 */
#define GET_TOLERANCE    100U    /* 処理遅れの見積り値（単位は内部表現）*/
#define BEFORE_IREQ(clock) \
            ((clock) >= TO_CLOCK(TIC_NUME, TIC_DENO) - GET_TOLERANCE)

/*
 *  タイマの起動処理
 *
 *  タイマを初期化し，周期的なタイマ割込み要求を発生させる．
 */
extern void target_timer_initialize(intptr_t exinf);

/*
 *  タイマの停止処理
 *
 *  タイマの動作を停止させる．
 */
extern void target_timer_terminate(intptr_t exinf);

/*
 *  タイマの現在値の読出し
 */
Inline CLOCK
target_timer_get_current(void)
{
	int32_t cnt;
	CNTP_TVAL_READ(cnt);

	return TO_CLOCK(TIC_NUME, TIC_DENO) - cnt;
}

/*
 *  タイマ割込み要求のチェック
 */
Inline bool_t
target_timer_probe_int(void)
{
#if 0
	uint32_t ctl;

#if defined(TOPPERS_SAFEG_SECURE)
	CNTPS_CTL_READ(ctl);
#else
	CNTP_CTL_READ(ctl);
#endif
	return ((ctl & CNTP_CTL_ISTATUS_BIT) == CNTP_CTL_ISTATUS_BIT);
#else
	/*
	 * Generic Timerはタイムアウト後はCNTP_CVALを更新するまで，CNTP_TVALの値は0のまま
	 * であるため， target_timer_probe_int()がtrueを返すとget_utm()に不整合が発生するため，
	 * 常にfalseを返すこととする． 
	 */
	return false;
#endif /* 0 */
}

/*
 *  タイマ割込みハンドラ
 */
extern void target_timer_handler(void);

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CORE_TIMER_H */
