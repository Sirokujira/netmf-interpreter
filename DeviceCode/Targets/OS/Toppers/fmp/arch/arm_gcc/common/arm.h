/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: arm.h 1202 2016-07-18 06:36:33Z ertl-honda $
 */

/*
 *  ARMのハードウェア資源の定義
 */

#ifndef TOPPERS_ARM_H
#define TOPPERS_ARM_H

/*
 *  ARMのハードウェア資源のツール依存部の定義
 */
#include <arm_tool.h>

/*
 *  ARM 例外ベクタ
 */
#define SVC_Vector    UINT_C(0x00)
#define UND_Vector    UINT_C(0x04)
#define SWI_Vector    UINT_C(0x08)
#define PRFA_Vector   UINT_C(0x0C)
#define DATAA_Vector  UINT_C(0x10)
#define IRQ_Vector    UINT_C(0x18)
#define FIQ_Vector    UINT_C(0x1C)

/*
 * ARM 例外ベクタ番号
 */
#define SVC_Number    UINT_C(0)
#define UND_Number    UINT_C(1)
#define SWI_Number    UINT_C(2)
#define PRFA_Number   UINT_C(3)
#define DATAA_Number  UINT_C(4)
#define UNNOWN_Number UINT_C(5)
#define IRQ_Number    UINT_C(6)
#define FIQ_Number    UINT_C(7)

/*
 *  CPSR 割込み禁止ビット
 */
#define CPSR_INT_MASK UINT_C(0xC0)
#define CPSR_IRQ_BIT  UINT_C(0x80)
#define CPSR_FIQ_BIT  UINT_C(0x40)

/*
 *  CPSR のモードビット
 */
#define CPSR_MODE_MASK   UINT_C(0x1f)
#define CPSR_USER        UINT_C(0x10)
#define CPSR_FIQ         UINT_C(0x11)
#define CPSR_IRQ         UINT_C(0x12)
#define CPSR_SVC         UINT_C(0x13)
#define CPSR_ABT         UINT_C(0x17)
#define CPSR_UND         UINT_C(0x1B)
#define CPSR_SYS         UINT_C(0x1F)


#if __TARGET_ARCH_ARM >= 6
/*
 * コプロ用の定義
 */
#define CP15_CONTROL_XP_BIT   (1 << 23)
#define CP15_CONTROL_V_BIT    (1 << 13)
#define CP15_CONTROL_I_BIT    (1 << 12)
#define CP15_CONTROL_Z_BIT    (1 << 11)
#define CP15_CONTROL_C_BIT    (1 <<  2)
#define CP15_CONTROL_M_BIT    (1 <<  0)

#if __TARGET_ARCH_ARM == 6
#define CP15_AUXILIARY_SA_BIT (1 << 5)
#define CP15_CPUID_BIT        (0x0f)
#else /* __TARGET_ARCH_ARM >= 7 */
#define CP15_AUXILIARY_SA_BIT (1 << 6)
#define CP15_AUXILIARY_EX_BIT (1 << 7)
#define CP15_AUXILIARY_FW_BIT (1 << 0)
#define CP15_CPUID_BIT        (0x03)
#endif /* __TARGET_ARCH_ARM >= 7 */

#define CP15_TTB0_RGN_S       (1 << 1)
#define CP15_TTB0_RGN_WBWA    (1 << 3)

#if __TARGET_ARCH_ARM >= 7
#define CP15_TTB0_IRGN_WBWA   ((1 << 6)|(0))

#define CP15_NSACR_NS_SMP (1 << 18)

#define CCSIDR_LINE_SIZE_MASK        0x00000007
#define CCSIDR_LINE_SIZE_OFFSET      0
#define CCSIDR_ASSOCIATIVITY_MASK    0x00001FF8
#define CCSIDR_ASSOCIATIVITY_OFFSET  3
#define CCSIDR_NUM_SETS_MASK         0x0FFFE000
#define CCSIDR_NUM_SETS_OFFSET       13

#define CLIDR_CTYPE_NO_CACHE          0U
#define CLIDR_CTYPE_INSTRUCTION_ONLY  1U
#define CLIDR_CTYPE_DATA_ONLY         2U
#define CLIDR_CTYPE_INSTRUCTION_DATA  3U
#define CLIDR_CTYPE_UNIFIED           4U

#define CLIDR_MAX_CTYPE         7U
#define CLIDR_CTYPE_MASK      0x7U
#define CLIDR_CTYPE_BITWIDTH    3U

#define CSSELR_IND_DATA_UNIFIED       0U
#define CSSELR_IND_INSTRUCTION        1U

#define RSAE_EN         0x01U
#define RSAE_RS_OFFSET  1U

#define RSAE_32      0x00000004U
#define RSAE_64      0x00000005U
#define RSAE_128     0x00000006U
#define RSAE_256     0x00000007U
#define RSAE_512     0x00000008U
#define RSAE_1K      0x00000009U
#define RSAE_2K      0x0000000AU
#define RSAE_4K      0x0000000BU
#define RSAE_8K      0x0000000CU
#define RSAE_16K     0x0000000DU
#define RSAE_32K     0x0000000EU
#define RSAE_64K     0x0000000FU
#define RSAE_128K    0x00000010U
#define RSAE_256K    0x00000011U
#define RSAE_512K    0x00000012U
#define RSAE_1M      0x00000013U
#define RSAE_2M      0x00000014U
#define RSAE_4M      0x00000015U
#define RSAE_8M      0x00000016U
#define RSAE_16M     0x00000017U
#define RSAE_32M     0x00000018U
#define RSAE_64M     0x00000019U
#define RSAE_128M    0x0000001AU
#define RSAE_256M    0x0000001BU
#define RSAE_512M    0x0000001CU
#define RSAE_1G      0x0000001DU
#define RSAE_2G      0x0000001EU
#define RSAE_4G      0x0000001FU

#define RAC_STRONGO_SHAR	0x00000000U

#define RAC_DEV_SHAR        0x00000001U
#define RAC_DEV_NSHAR       0x00000010U
#define RAC_NORM_OI_WT_NWA  0x00000002U
#define RAC_NORM_OI_WB_NWA  0x00000003U
#define RAC_OI_NCACHE       0x00000008U 
#define RAC_OI_WB_WA        0x0000000BU

#define RAC_NORM_I_NCACHE   0x00000020U
#define RAC_NORM_I_WB_WA    0x00000021U
#define RAC_NORM_I_WT_NWA   0x00000022U
#define RAC_NORM_I_WB_NWA   0x00000023U

#define RAC_NORM_O_NCACHE   0x00000020U
#define RAC_NORM_O_WB_WA    0x00000028U
#define RAC_NORM_O_WT_NWA   0x00000030U
#define RAC_NORM_O_WB_NWA   0x00000038U

#define RAC_AP_OFFSET       8U
#define RAC_AP_NO_ACCESS    (0x00000000U<<RAC_AP_OFFSET)
#define RAC_AP_PRW_UNA      (0x00000001U<<RAC_AP_OFFSET)
#define RAC_AP_PRW_URO      (0x00000002U<<RAC_AP_OFFSET)
#define	RAC_AP_PRW_URW      (0x00000003U<<RAC_AP_OFFSET)
#define RAC_AP_PRO_UNA      (0x00000005U<<RAC_AP_OFFSET)
#define RAC_AP_PRO_URO      (0x00000006U<<RAC_AP_OFFSET)

#define RAC_XN              0x00001000U /* Execute Never */
#define RAC_S               0x00000004U /* Share */
#endif /* __TARGET_ARCH_ARM >= 7 */

#if __TARGET_ARCH_ARM >= 8
#define CPUECTLR_SMPEN  0x40U
#endif /* __TARGET_ARCH_ARM >= 8 */

#ifdef __TARGET_PROFILE_R
#define AUXILIARY_RSDIS       (0x1 << 17)
#define AUXILIARY_BP_MASK     (0x3 << 15)
#define AUXILIARY_BP_NOP      (0x0 << 15)
#define AUXILIARY_BP_BAWT_DU  (0x1 << 15)
#define AUXILIARY_BP_BAWNT_DU (0x2 << 15)
#define AUXILIARY_ATCMPCEN    (0x1 << 25)
#define AUXILIARY_B0TCMPCEN   (0x1 << 26)
#define AUXILIARY_B1TCMPCEN   (0x1 << 27)
#define AUXILIARY_CEC_MASK    (0x7 << 3)
#define AUXILIARY_CEC_NPE     (0x5 << 3)
#define AUXILIARY_DBWR        (0x5 << 14)
#endif /* __TARGET_PROFILE_R */

#endif /* __TARGET_ARCH_ARM >= 6 */

#ifndef TOPPERS_MACRO_ONLY

#if __TARGET_ARCH_ARM >= 6
/*
 *  コプロを用いたルーチン
 */

/*
 *  High exception vector を使うかの設定
 */
Inline void
set_high_vector(bool_t enable)
{
	uint32_t control;

	CP15_CONTROL_READ(control);

	if (enable) {
		control |= CP15_CONTROL_V_BIT;
	}
	else {
		control &= ~CP15_CONTROL_V_BIT;
	}

	CP15_CONTROL_WRITE(control);
}

/*
 *  プロセッサINDEX（0オリジン）の取得
 */
Inline uint32_t
x_prc_index(void)
{
	uint32_t index;

	CP15_CPUID_READ(index);
	return((index & CP15_CPUID_BIT));
}

/*
 *  Data Synchronization Barrier
 *  ・先に発行された read と write の終了を待つ
 *  ・キャッシュ，ブランチプリディクション，TLBの操作の終了を待つ
 *  ・この命令の後に書かれた命令は実行されない
 */
Inline void
data_sync_barrier(void)
{
	CP15_DATA_SYNC_BARRIER();
}

/*
 *  Data Memory Barrier
 *  ・プログラムの記述に従って，先に書かれた命令でのメモリアクセスが
 *     終了するまで待つ．
 *
 */
Inline void
data_memory_barrier(void)
{
	CP15_DATA_MEMORY_BARRIER();
}

/*
 *  プリフェッチバッファをクリア
 */
Inline void
pbuffer_flash(void)
{
	CP15_PBUFFER_FLUSH();
}

#ifdef __TARGET_PROFILE_A

/*
 *  ブランチプリディクターの全無効化
 */
Inline void
bpi_invalidate_all(void)
{
	CP15_BPI_INVALIDATEALL(0);
	CP15_DATA_SYNC_BARRIER();
	CP15_PBUFFER_FLUSH();
}

/*
 *  ブランチプリディクターを有効に
 */
Inline void
btac_enable(void)
{
	uint32_t tmp;

	CP15_CONTROL_READ(tmp);
	tmp |= CP15_CONTROL_Z_BIT;
	CP15_CONTROL_WRITE(tmp);
}

#if __TARGET_ARCH_ARM == 6
Inline void
invalidate_dcache_all(void)
{
	CP15_DCACHE_INVALIDATE();
}

Inline void
clean_invalidate_dcache_all(void)
{
	CP15_DCACHE_CLEAN_AND_INVALIDATE();
}

Inline void
clean_dcache_all(void)
{
	
}
#else /* __TARGET_ARCH_ARM >= 7 */
extern void invalidate_dcache_all();
extern void clean_invalidate_dcache_all();
extern void clean_dcache_all();
#endif /* __TARGET_ARCH_ARM == 6 */

/*
 *  Dキャッシュの無効化
 */
Inline void
dcache_invalidate(void)
{
	invalidate_dcache_all();
}

/*
 *  Dキャッシュのクリーンと無効化
 */
Inline void
dcache_clean_and_invalidate(void)
{
	clean_invalidate_dcache_all();
}

/*
 *  Dキャッシュのクリーン
 */
Inline void
dcache_clean(void)
{
	clean_dcache_all();
}

/*
 *  Iキャッシュの無効化
 */
Inline void
icache_invalidate(void)
{
	CP15_ICACHE_INVALIDATE();
	CP15_BRANCHP_INVALIDATE();
	CP15_DATA_SYNC_BARRIER();
	CP15_PBUFFER_FLUSH();
}

/*
 *  I/Dキャッシュを両方を有効に
 */
extern void cache_enable(void);

/*
 *  I/Dキャッシュを両方を無効に
 */
extern void cache_disable(void);

/*
 *  Iキャッシュを有効に
 */
extern void icache_enable(void);

/*
 *  Iキャッシュを無効に
 */
extern void icache_disable(void);

/*
 *  Dキャッシュを有効に
 */
extern void dcache_enable(void);

/*
 *  Dキャッシュを無効に
 */
extern void dcache_disable(void);

/*
 *  L2キャッシュのフラッシュ（各依存部で定義）
 */
extern void outer_cache_flush(void);

/*
 *  MMU関連
 */

/*
 *  TLBの無効化
 */
Inline void
invalidate_unfied_tlb(void)
{
	CP15_DATA_SYNC_BARRIER();
}

/*
 * 変換テーブルへの設定内容
 * va   : 仮想アドレス
 * pa   : 物理アドレス
 * size : サイズ
 * s    : 共有指定
 * tex  : C Bとの組み合わせで変化
 * ap   : アクセス権
 * c    : キャッシュ
 * b    : バッファ
 */
typedef struct{
	uintptr_t   va;
	uintptr_t   pa;
	uint32_t    size;
	uint8_t     ns;
	uint8_t     s;
	uint8_t     tex;
	uint8_t     ap;
	uint8_t     c;
	uint8_t     b;
}MEMORY_ATTRIBUTE;

/*
 *  MMUの初期化
 */
extern void mmu_init(void);

/*
 *  MMUによるメモリのマッピング
 */
extern void mmu_map_memory(MEMORY_ATTRIBUTE *m_attribute);

#endif /* __TARGET_PROFILE_A */


#ifdef __TARGET_PROFILE_R

Inline void
icache_enable(void)
{
	uint32_t control;

	CP15_CONTROL_READ(control);
	control |= CP15_CONTROL_I_BIT;
	CP15_DATA_SYNC_BARRIER();
	CP15_CONTROL_WRITE(control);
	CP15_PBUFFER_FLUSH();
}

Inline void
icache_disable(void)
{
	uint32_t control;

	CP15_CONTROL_READ(control);
	control &= ~CP15_CONTROL_I_BIT;
	CP15_DATA_SYNC_BARRIER();
	CP15_CONTROL_WRITE(control);
	CP15_PBUFFER_FLUSH();
}

Inline void
icache_invalidate(void)
{
	CP15_ICACHE_INVALIDATE();
	CP15_PBUFFER_FLUSH();
}

Inline void
dcache_enable(void)
{
	uint32_t control;

	CP15_CONTROL_READ(control);
	control |= CP15_CONTROL_C_BIT;
	CP15_DATA_SYNC_BARRIER();
	CP15_CONTROL_WRITE(control);
	CP15_PBUFFER_FLUSH();
}

Inline void
dcache_disable(void)
{
	uint32_t control;

	CP15_CONTROL_READ(control);
	control &= ~CP15_CONTROL_C_BIT;
	CP15_DATA_SYNC_BARRIER();
	CP15_CONTROL_WRITE(control);
	CP15_PBUFFER_FLUSH();
}

Inline void
bp_enable(void)
{
	uint32_t acontrol;
	CP15_AUXILIARY_READ(acontrol);
	acontrol &= ~AUXILIARY_RSDIS;
	acontrol &= ~AUXILIARY_BP_MASK;
	/* Disable DBWR for errata 780125 */
	acontrol |=  AUXILIARY_DBWR;
	CP15_AUXILIARY_WRITE(acontrol);
	CP15_DATA_SYNC_BARRIER();
}

Inline void
bp_disable(void)
{
	uint32_t acontrol;
	CP15_AUXILIARY_READ(acontrol);
	acontrol |= AUXILIARY_RSDIS;
	acontrol = (acontrol & ~AUXILIARY_BP_MASK) | AUXILIARY_BP_BAWNT_DU;
	CP15_AUXILIARY_WRITE(acontrol);
	CP15_DATA_SYNC_BARRIER();
}

Inline void
tcm_ecc_disable(void)
{
	uint32_t acontrol;
	CP15_AUXILIARY_READ(acontrol);
	acontrol &= ~(AUXILIARY_ATCMPCEN|AUXILIARY_B0TCMPCEN|AUXILIARY_B1TCMPCEN);
	CP15_AUXILIARY_WRITE(acontrol);
	CP15_DATA_SYNC_BARRIER();
}

Inline void
cache_parity_disable(void)
{
	uint32_t acontrol;
	CP15_AUXILIARY_READ(acontrol);
	acontrol &= ~AUXILIARY_CEC_MASK;
	acontrol |= AUXILIARY_CEC_NPE;
	CP15_AUXILIARY_WRITE(acontrol);
	CP15_DATA_SYNC_BARRIER();
}

Inline void
mpu_enable(void)
{
	uint32_t control;

	CP15_CONTROL_READ(control);
	control |= CP15_CONTROL_M_BIT;
	CP15_DATA_SYNC_BARRIER();
	CP15_CONTROL_WRITE(control);
	CP15_PBUFFER_FLUSH();
}

Inline void
mpu_disable(void)
{
	uint32_t control;

	CP15_CONTROL_READ(control);
	control &= ~CP15_CONTROL_M_BIT;
	CP15_DATA_SYNC_BARRIER();
	CP15_CONTROL_WRITE(control);
	CP15_PBUFFER_FLUSH();
}

/*
 *  全リージョンを無効
 */
extern void mpu_disable_allregion(void);

/*
 *  MPUのリージョンの属性を設定
 */
extern void mpu_set_region(uint32_t base, uint32_t size, uint32_t number, uint32_t attr);

#endif /* __TARGET_PROFILE_R */

#endif /* __TARGET_ARCH_ARM >= 6 */
#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_ARM_H */
