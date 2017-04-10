/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: core_sil.h 1202 2016-07-18 06:36:33Z ertl-honda $
 */

/*
 *  sil.hのコア依存部（ARM用）
 */

#ifndef TOPPERS_CORE_SIL_H
#define TOPPERS_CORE_SIL_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  メモリが変更されることをコンパイラに伝えるためのマクロ
 */
#define ARM_MEMORY_CHANGED Asm("":::"memory")

/*
 *  Memory Synchronization
 */
#if __TARGET_ARCH_ARM == 6
#define SIL_DMB  Asm("mcr p15, 0, %0, c7, c10, 5"::"r" (0));
#define SIL_DSB  Asm("mcr	p15, 0, %0, c7, c10, 4"::"r"(0));
#elif __TARGET_ARCH_ARM >= 7
#define SIL_DMB  Asm("dmb");
#define SIL_DSB  Asm("dsb");
#endif /* __TARGET_ARCH_ARM >= 7 */

#ifdef __thumb__
/*
 *  制御レジスタの操作関数
 */

/*
 *  ステータスレジスタ（CPSR）の現在値の読出し
 */
extern uint32_t current_sr(void);

/*
 *  ステータスレジスタ（CPSR）の現在値の変更
 */
extern void set_sr(uint32_t sr);
#endif /* __thumb__ */

#ifndef USE_GIC_CPULOCK
/*
 *  すべての割込み（FIQとIRQ）の禁止
 */
Inline uint32_t
TOPPERS_disint(void)
{
	uint32_t  cpsr;
	uint32_t  irq_fiq_mask;

#ifndef __thumb__
	Asm("mrs  %0,CPSR" : "=r"(cpsr));
	irq_fiq_mask = cpsr & (0x40|0x80);
	cpsr |= (0x40|0x80);
	Asm("msr CPSR, %0" : : "r"(cpsr) :"memory", "cc");
#else /* __thumb__ */
	cpsr = current_sr();
	irq_fiq_mask = cpsr & (0x40|0x80);
	cpsr |= (0x40|0x80);
	set_sr(cpsr);
#endif /* __thumb__ */

	return(irq_fiq_mask);
}

/*
 *  FIQ,IRQの設定
 */
Inline void
TOPPERS_set_fiq_irq(uint32_t TOPPERS_irq_fiq_mask)
{
	uint32_t  cpsr;

#ifndef __thumb__
	Asm("mrs  %0,CPSR" : "=r"(cpsr));
	cpsr = cpsr & ~(0x40|0x80);
	cpsr = cpsr | (TOPPERS_irq_fiq_mask & (0x40|0x80));
	Asm("msr CPSR, %0" : : "r"(cpsr):"memory", "cc");
#else /* __thumb__ */
	cpsr = current_sr();
	cpsr = cpsr &  ~(0x40|0x80);
	cpsr = cpsr | (TOPPERS_irq_fiq_mask&  (0x40|0x80));
	set_sr(cpsr);
#endif /* __thumb__ */
}

/*
 *  全割込みロック状態の制御
 */
#define SIL_PRE_LOC   uint32_t TOPPERS_irq_fiq_mask
#define SIL_LOC_INT() ((void)(TOPPERS_irq_fiq_mask = TOPPERS_disint()))
#define SIL_UNL_INT() (TOPPERS_set_fiq_irq(TOPPERS_irq_fiq_mask))

#else /* USE_GIC_CPULOCK */

#define SIL_DIC_CPUIF_PMR  (SIL_MPCORE_PMR_BASE + 0x0104)  /* 優先度マスクレジスタ */

#if __TARGET_ARCH_ARM == 6
#define SIL_DIC_CPUIF_PMR_OFFSET 0x04
#elif __TARGET_ARCH_ARM >= 7
#define SIL_DIC_CPUIF_PMR_OFFSET 0x03
#endif /* __TARGET_ARCH_ARM >= 7 */

Inline void
TOPPERS_set_iipm(uint8_t iipm)
{
	*((volatile uint32_t *)SIL_DIC_CPUIF_PMR) = iipm << SIL_DIC_CPUIF_PMR_OFFSET;
}

Inline uint8_t
TOPPERS_get_iipm(void)
{
	return ((uint8_t)(*((volatile uint32_t *)SIL_DIC_CPUIF_PMR) >> SIL_DIC_CPUIF_PMR_OFFSET));
}

/*
 *  すべての割込みの禁止
 */
Inline uint8_t
TOPPERS_disint(void)
{
	uint8_t iipm;
	iipm = TOPPERS_get_iipm();
	TOPPERS_set_iipm(0);
	return iipm;
}

/*
 *  全割込みロック状態の制御
 */
#define SIL_PRE_LOC   uint8_t TOPPERS_iipm
#define SIL_LOC_INT() ((void)(TOPPERS_iipm = TOPPERS_disint()))
#define SIL_UNL_INT() (TOPPERS_set_iipm(TOPPERS_iipm))

#endif /* USE_GIC_CPULOCK */

/*
 *  微少時間待ち
 */
#ifndef TOPPERS_CUSTOM_SILDLYNSE
Inline void
sil_dly_nse(ulong_t dlytim)
{
	register uint32_t r0 asm("r0") = (uint32_t) dlytim;
	Asm("bl _sil_dly_nse" : "=g"(r0) : "0"(r0) : "lr","cc");
}
#endif /* TOPPERS_CUSTOM_SILDLYNSE */

#if __TARGET_ARCH_ARM >= 6
/*
 *  プロセッサIDの取得
 */
Inline void
sil_get_pid(ID *p_prcid)
{
	uint32_t index;

	Asm("mrc p15, 0, %0, c0, c0, 5":"=r"(index));
	*p_prcid = (index & 0x0f) + 1;
}

/*
 *  スピンロック変数（core_config.c）
 */
extern uint32_t TOPPERS_spn_var;

#ifndef USE_GIC_CPULOCK

/*
 *  スピンロックの取得
 */
Inline uint32_t
TOPPERS_sil_loc_spn(void)
{
	uint32_t irq_fiq_mask;
	uint32_t locked;
	uint32_t pre_cpsr_c;
	uint32_t dis_cpsr_c;
	ID       prcid;

	sil_get_pid(&prcid);

	/* 呼び出し時のcpsrのbit0～7の状態 */
	Asm("mrs  %0,CPSR" : "=r"(pre_cpsr_c));

	/* 全割込みロック状態へ */
	irq_fiq_mask = TOPPERS_disint();

	/* 全割込みロック状態移行後のcpsrのbit0～7の状態 */
	Asm("mrs  %0,CPSR" : "=r"(dis_cpsr_c));

	while(true) {
		/*
		 * スピンロックの取得
		 * プロセッサIDを書き込む
		 */
		Asm("   mov      r2, %4      \n"
			"\t ldrex    r1, [%1]    \n"
			"\t cmp      r1, #0x00   \n"
			"\t msrne    cpsr_c, %2  \n" /* 呼び出し時の状態へ（割込み許可） */
			#ifndef TOPPERS_OMIT_USE_WFE
			"\t wfene                \n"
			#endif /* TOPPERS_OMIT_USE_WFE */
			"\t msrne    cpsr_c, %3  \n" /* 全割込みロック状態へ */
			"\t strexeq  r1, r2,[%1] \n"
			"\t mov      %0, r1      \n"
			:"=r"(locked)
			:"r"(&TOPPERS_spn_var),"r"(pre_cpsr_c),"r"(dis_cpsr_c),"r"(prcid)
			:"r1","r2", "cc");

		if (locked == 0) {
			/* スピンロックが取得成功 */
			/* Data meory barrier */
			SIL_DMB;
			ARM_MEMORY_CHANGED;
			return irq_fiq_mask;
		}
	}
}

/*
 *  スピンロックの返却
 */
Inline void
TOPPERS_sil_unl_spn(uint32_t irq_fiq_mask)
{
	/* メモリの内容が書き換わる可能性がある */
	ARM_MEMORY_CHANGED;
	/* Data meory barrier */
	SIL_DMB;
	TOPPERS_spn_var = 0U;
	/* Data Sync Barrier */
	SIL_DSB;
	/* スピンロック待ちのタスクへイベントを送る */
	Asm("sev");

	/* スピンロックの取得前の状態へ */
	TOPPERS_set_fiq_irq(irq_fiq_mask);
}

/*
 *  スピンロック
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_irq_fiq_mask = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_irq_fiq_mask))

#else /* USE_GIC_CPULOCK */

/*
 *  スピンロックの取得(USE_GIC_CPULOCK)
 */
Inline uint8_t
TOPPERS_sil_loc_spn(void)
{
	uint8_t  iipm;
	uint32_t locked;
	ID       prcid;

	sil_get_pid(&prcid);

	iipm = TOPPERS_get_iipm();

	/* 全割込みロック状態へ */
	TOPPERS_set_iipm(0);

	while(true) {
		/*
		 * スピンロックの取得
		 * プロセッサIDを書き込む
		 */
		Asm("   mov      r2, %2      \n"
			"\t ldrex    r1, [%1]    \n"
			"\t cmp      r1, #0x00   \n"
			"\t strexeq  r1, r2,[%1] \n"
			"\t mov      %0, r1      \n"
			:"=r"(locked)
			:"r"(&TOPPERS_spn_var),"r"(prcid)
			:"r1","r2", "cc");

		if (locked == 0) {
			/* スピンロックが取得成功 */
			/* Data meory barrier */
			SIL_DMB;
			ARM_MEMORY_CHANGED;
			return iipm;
		}else{
			/* 一旦割込みを許可にする */
			TOPPERS_set_iipm(iipm);
			TOPPERS_set_iipm(0);
		}
	}
}

/*
 *  スピンロックの返却(USE_GIC_CPULOCK)
 */
Inline void
TOPPERS_sil_unl_spn(uint8_t iipm)
{
	/* メモリの内容が書き換わる可能性がある */
	ARM_MEMORY_CHANGED;
	/* Data meory barrier */
	SIL_DMB;
	TOPPERS_spn_var = 0U;
	/* Data Sync Barrier */
	SIL_DSB;
	/* スピンロック待ちのタスクへイベントを送る */
	Asm("sev");

	/* スピンロックの取得前の状態へ */
	TOPPERS_set_iipm(iipm);
}

/*
 *  スピンロック
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_iipm = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_iipm))

#endif /* USE_GIC_CPULOCK */

/*
 *  スピンロックの強制解放
 *  自プロセッサがスピンロックを取得している場合に解放する．
 */
Inline void
TOPPERS_sil_force_unl_spn(void)
{
	ID prcid;

	sil_get_pid(&prcid);

	if (TOPPERS_spn_var == prcid) {
		TOPPERS_spn_var = 0U;
		/* スピンロック待ちのタスクへイベントを送る */
		Asm("sev");
	}
}

#endif /* __TARGET_ARCH_ARM >= 6 */

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CORE_SIL_H */
