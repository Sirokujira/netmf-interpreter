/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2007-2017 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_config.c 1087 2015-02-03 01:04:34Z ertl-honda $
 */

/*
 *  This file implements the following functions:
 *      - target_mprc_initialize (master processor initialization)
 *      - target_fput_log (low-level character output)
 *      - target_mmu_init (virtual memory initialization)
 *      - target_initialize (target initialization)
 *      - target_exit (target exit processing)
 */

#include "kernel_impl.h"
#include <sil.h>
#include "pl310.h"

/*
 *  entry point (start.S)
 */
extern void start(void);

/*
 *  Boot second core
 */
static void
boot_second_core(uint32_t address) {
	sil_wrw_mem((void*)BOOT_MEM_ADDR, address);
	Asm("sev":::"memory");
}

/*
 *  Master processor initialization before str_ker().
 *  (E.g.: initialize the interrupt controller or the SCU.)
 */
void
target_mprc_initialize(void)
{
	dcache_disable();
	pl310_invalidate_all();
	icache_disable();

	chip_mprc_initialize();
#if TNUM_PRCID >= 2
	boot_second_core((uint32_t)start);
#endif /* TNUM_PRCID >= 2 */
}

/*
 *  System log low-level (polling) character output
 */
extern void xuartps_pol_putc(char c);

void
target_fput_log(char c)
{
	if (c == '\n') {
		xuartps_pol_putc('\r');
	}
	xuartps_pol_putc(c);
}

/*
 * MMU initialization (called from the chip code)
 *
 * We create a simpe 1-to-1 (physical address = virtual address) memory
 * mapping and enable caching for the DDR memory.
 *
 * Note: when not using SafeG the default world is Secure. When using
 * SafeG, Secure world uses secure accesses by default. If you want to
 * access a shared memory region with non-secure access, you will have
 * to configure it manually.
 */
void
target_mmu_init(void)
{
	MEMORY_ATTRIBUTE m_attribute;

	/*
	 * Basic initialization of the whole virtual memory space to
	 * non-cachable, non-bufferable, strongly-ordered.
	 */
	m_attribute.pa   = 0x00000000;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = 0x80000000; /* 2GB */
	m_attribute.ns   = 0;     /* 0=Secure */
	m_attribute.s    = 1;     /* 1=Shared */
	m_attribute.ap   = 3;     /* Full access */
	m_attribute.tex  = 0;     /* Strongly Ordered */
	m_attribute.c    = 0;
	m_attribute.b    = 0;
	mmu_map_memory (&m_attribute);

	m_attribute.pa   = 0x80000000; /* 2GB */
	m_attribute.va   = m_attribute.pa;
	mmu_map_memory (&m_attribute);

	/*
	 *  Enable caching for the DDR
	 */
	m_attribute.pa   = 0;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = 0x20000000;
	m_attribute.ns   = 0;      /* 0=NonSecure */
	m_attribute.s    = 1;      /* 1=Shared    */
	m_attribute.ap   = 3;      /* Full access */
	m_attribute.tex  = 1;
	m_attribute.c    = 1;             
	m_attribute.b    = 1;             

	mmu_map_memory(&m_attribute);

#if defined(TOPPERS_SAFEG_SECURE) 
	/*
	 *  TRUST access to NS memory
	 */
	m_attribute.pa   = 0;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = 0x1B000000;
	m_attribute.ns   = 1;     /* 1=NonSecure */
	m_attribute.s    = 1;     /* 1=Shared */
	m_attribute.ap   = 3;     /* Full access */
	m_attribute.tex  = 1;     /* Strongly Ordered */
	m_attribute.c    = 1;     /* Inner Write-Back */
	m_attribute.b    = 1;     /* Write Allocate */
	mmu_map_memory(&m_attribute);

	/*
	 * SafeG-COM shared memory area
	 */
	m_attribute.pa   = SAFEG_COM_MEM_ADDR;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = SAFEG_COM_MEM_SIZE * 1024 * 1024;
	m_attribute.ns   = 1;          /* NonSecure    */
	m_attribute.s    = 1;          /* 共有あり     */
	m_attribute.ap   = 3;          /* フルアクセス */
	m_attribute.tex  = 0;          /* キャッシュON */
	m_attribute.c    = 1;          /* Outer and Inner */          
	m_attribute.b    = 1;          /* Inner Write-Back, Write Allocate */

	mmu_map_memory(&m_attribute);

#endif /* defined(TOPPERS_SAFEG_SECURE)  */
}

#ifdef TOPPERS_SAFEG_SECURE
/*
 *  Fist swith to NT code(target_support.S)
 */
extern uint8_t first_switch_to_nt;
extern uint8_t first_switch_to_nt_end;

static void
copy_first_switch_to_nt(void){
	int cnt;
	volatile uint8_t *dst_addr;

	dst_addr = (uint8_t*)OCM_ADDR;
	for (cnt = 0; cnt < (&first_switch_to_nt_end - &first_switch_to_nt); cnt++) {
		*(dst_addr + cnt) = *(volatile uint8_t *)(&first_switch_to_nt + cnt);
	}

	__asm__ volatile("dsb");
	__asm__ volatile("isb");
}
#endif /* TOPPERS_SAFEG_SECURE */

#ifdef TOPPERS_SAFEG_SECURE
#include "syscalls_api.h"
#include "pl310.h"

/*
 * L2 cache initialize syscall
 */
uint32_t
safeg_l2cache_init(const uint32_t core_id,
				   const uint32_t ns,
				   const uint32_t aux_val,
				   const uint32_t aux_mask,
				   const uint32_t c)
{
	pl310_init(aux_val, aux_mask);
	return SAFEG_OK(SAFEG_SYSCALL_RET__DONT_SWITCH);
}

struct safeg_syscall l2init_call = {
	.is_t_callable  = 1,
	.is_nt_callable = 1,
	.name = "l2init",
	.function = safeg_l2cache_init,
};

/*
 * Regist L2 cache debug register warite syscall
 */
uint32_t
l2cache_debug_set(const uint32_t core_id,
				  const uint32_t ns,
				  const uint32_t a,
				  const uint32_t b,
				  const uint32_t c)
{
	pl310_debug_set(a);
	return SAFEG_OK(SAFEG_SYSCALL_RET__DONT_SWITCH);
}

struct safeg_syscall l2debug_set_call = {
	.is_t_callable  = 1,
	.is_nt_callable = 1,
	.name = "l2debug",
	.function = l2cache_debug_set,
};

/*
 * Boot second core
 */
uint32_t
safeg_boot_second_core(const uint32_t core_id,
				   const uint32_t ns,
				   const uint32_t address,
				   const uint32_t b,
				   const uint32_t c)
{
	boot_second_core(address);
	return SAFEG_OK(SAFEG_SYSCALL_RET__DONT_SWITCH);
}

struct safeg_syscall boot_second_core_call = {
	.is_t_callable  = 1,
	.is_nt_callable = 1,
	.name = "bsecond",
	.function = safeg_boot_second_core,
};

#endif /* TOPPERS_SAFEG_SECURE */

/*
 *  Target-dependent initialization
 */
extern void xuartps_init();

#if !defined(TOPPERS_SAFEG_SECURE)
volatile uint32_t target_initialize_end[TNUM_PRCID];
#endif /* !TOPPERS_SAFEG_SECURE */

void
target_initialize(void)
{
	/*
	 * Initialize chip
	 */
	chip_initialize();

	/*
	 *  Initialize the UART. If we are using a
	 *  global logger (shared by all cores) only
	 *  the master processor (mprc) initializes it.
	 */
#ifdef G_SYSLOG
	if (x_sense_mprc()) {
		xuartps_init();
	}
#else /* !G_SYSLOG */
	xuartps_init();
#endif /* G_SYSLOG */


#ifdef TOPPERS_SAFEG_SECURE
	/* Set NULL(0x00) for Linux second core boot */
	sil_wrw_mem((uint32_t*)BOOT_MEM_ADDR, 0x00);
	copy_first_switch_to_nt();
#endif /* TOPPERS_SAFEG_SECURE */

#ifdef TOPPERS_SAFEG_SECURE
	if (x_sense_mprc()) {
		/* Regist L2 cache initialize syscall */
		uint32_t id;
		safeg_syscall_regdyn(&l2init_call, &id);

		/* Regist L2 cache debug register write syscall */
		safeg_syscall_regdyn(&l2debug_set_call, &id);

		/* Regist boot second core syscall */
		safeg_syscall_regdyn(&boot_second_core_call, &id);
	}
#endif /*  TOPPERS_SAFEG_SECURE */

#ifdef TOPPERS_NOSAFEG
	/* Enable L2 cache by myself in case of without safeg or with safeg Non-Secure */
	if (x_sense_mprc()) {
		uint32_t i;
		uint32_t sum = 0;
		while(1) {
			for(i = 1; i < TNUM_PRCID; i++) {
				sum += target_initialize_end[i];
			}
			if (sum == (TNUM_PRCID - 1)) {
				break;
			}
		}
		pl310_init(0, ~0x0U);
	}
	target_initialize_end[x_prc_index()] = 1;
#endif /* TOPPERS_NOSAFEG */
}

/*
 *  Target-dependent exit processing
 */
void
target_exit(void)
{
	/*
	 *  Chip exit processing
	 */
	chip_exit();

	/*
	 *  Endless loop
	 */
	while(1);
}
