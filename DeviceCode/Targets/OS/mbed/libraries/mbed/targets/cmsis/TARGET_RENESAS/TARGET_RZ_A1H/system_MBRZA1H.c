/**************************************************************************//**
 * @file     system_MBRZA1H.c
 * @brief    CMSIS Device System Source File for
 *           ARMCA9 Device Series
 * @version  V1.00
 * @date     19 Sept 2013
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2011 - 2013 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#include <stdint.h>
#include "MBRZA1H.h"
#include "RZ_A1_Init.h"

#if defined(__ARMCC_VERSION)
extern void $Super$$main(void);
__asm void FPUEnable(void);
#else
void FPUEnable(void);
static inline void __enable_irq(void)
{
    __asm__("cpsie i");
}
#endif

uint32_t IRQNestLevel;

#if defined(__ARMCC_VERSION)
/**
 * Initialize the cache.
 *
 * @param  none
 * @return none
 *
 * @brief Initialise caches. Requires PL1, so implemented as an SVC in case threads are USR mode.
 */
#pragma push
#pragma arm

void InitMemorySubsystem(void) {

    /* This SVC is specific for reset where data / tlb / btac may contain undefined data, therefore before
     * enabling the cache you must invalidate the instruction cache, the data cache, TLB, and BTAC.
     * You are not required to invalidate the main TLB, even though it is recommended for safety
     * reasons. This ensures compatibility with future revisions of the processor. */

    unsigned int l2_id;

    /* Invalidate undefined data */
    __ca9u_inv_tlb_all();
    __v7_inv_icache_all();
    __v7_inv_dcache_all();
    __v7_inv_btac();

    /* Don't use this function during runtime since caches may contain valid data. For a correct cache maintenance you may need to execute a clean and
     * invalidate in order to flush the valid data to the next level cache.
     */
    __enable_mmu();

    /* After MMU is enabled and data has been invalidated, enable caches and BTAC */
    __enable_caches();
    __enable_btac();

    /* If present, you may also need to Invalidate and Enable L2 cache here */
    l2_id = PL310_GetID();
    if (l2_id)
    {
       PL310_InvAllByWay();
       PL310_Enable();
    }
}
#pragma pop

#elif defined(__GNUC__)
void __attribute__((section("SectionForBootstrapOperations"))) __v7_all_cache(uint32_t op)
{
    __asm__ __volatile__ (
            ".align 2                       \n\t"
            ".arm                           \n\t"
            "push   {r4-r11}                \n\t"
            "mrc    p15, 1, r6, c0, c0, 1   \n\t"
            "ands   r3, r6, #0x07000000     \n\t"
            "mov    r3, r3, lsr #23         \n\t"
            "beq    finished                \n\t"
            "mov    r10, #0                 \n\t"
            "loop1:                         \n\t"
            "add    r2, r10, r10, lsr #1    \n\t"
            "mov    r1, r6, lsr r2          \n\t"
            "and    r1, r1, #7              \n\t"
            "cmp    r1, #2                  \n\t"
            "blt    skip                    \n\t"
            "mcr    p15, 2, r10, c0, c0, 0  \n\t"
            "isb                            \n\t"
            "mrc    p15, 1, r1, c0, c0, 0   \n\t"
            "and    r2, r1, #7              \n\t"
            "add    r2, r2, #4              \n\t"
            "ldr    r4, =0x3ff              \n\t"
            "ands   r4, r4, r1, lsr #3      \n\t"
            "clz    r5, r4                  \n\t"
            "ldr    r7, =0x7fff             \n\t"
            "ands   r7, r7, r1, lsr #13     \n\t"
            "loop2:                         \n\t"
            "mov    r9, r4                  \n\t"
            "loop3:                         \n\t"
            "orr    r11, r10, r9, lsl r5    \n\t"
            "orr    r11, r11, r7, lsl r2    \n\t"
            "cmp    r0, #0                  \n\t"
            "bne    dccsw                   \n\t"
            "mcr    p15, 0, r11, c7, c6, 2  \n\t"
            "b      cont                    \n\t"
            "dccsw:                         \n\t"
            "cmp    r0, #1                  \n\t"
            "bne    dccisw                  \n\t"
            "mcr    p15, 0, r11, c7, c10, 2 \n\t"
            "b      cont                    \n\t"
            "dccisw:                        \n\t"
            "mcr    p15, 0, r11, c7, c14, 2 \n\t"
            "cont:                          \n\t"
            "subs   r9, r9, #1              \n\t"
            "bge    loop3                   \n\t"
            "subs   r7, r7, #1              \n\t"
            "bge    loop2                   \n\t"
            "skip:                          \n\t"
            "add    r10, r10, #2            \n\t"
            "cmp    r3, r10                 \n\t"
            "bgt    loop1                   \n\t"
            "finished:                      \n\t"
            "dsb                            \n\t"
            "pop    {r4-r11}                \n\t"
            "bx     lr                      \n\t"
    );
}

#ifdef __set_SCTLR
#undef __set_SCTLR
#endif

__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __set_SCTLR(uint32_t sctlr)
{
    //register uint32_t __regSCTLR         __ASM("cp15:0:c1:c0:0");
    //__regSCTLR = sctlr;
    __asm__ __volatile__ ("str  r0, %0" : "=m" (sctlr) : );
    __asm__ __volatile__ ("mcr  p15,#0x0,r0,c1,c0,#0");
}

#ifdef __get_SCTLR
#undef __get_SCTLR
#endif
__STATIC_INLINE uint32_t __attribute__((section("SectionForBootstrapOperations"))) __get_SCTLR()
{
    //register uint32_t __regSCTLR         __ASM("cp15:0:c1:c0:0");
    //return(__regSCTLR);
    uint32_t sctlr;
    __asm__ __volatile__ ("mrc  p15,#0x0,r0,c1,c0,#0");
    __asm__ __volatile__ ("ldr  r0, %0" : : "m" (sctlr));
    return sctlr;
}

#ifdef __ca9u_inv_tlb_all
#undef __ca9u_inv_tlb_all
#endif
__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __ca9u_inv_tlb_all()
{
    //register uint32_t __TLBIALL         __ASM("cp15:0:c8:c7:0");
    //__TLBIALL = 0;
    __asm__ __volatile__ ("mov  r0, #0");
    __asm__ __volatile__ ("mcr  p15,#0x0,r0,c8,c7,#0");
    __DSB();
    __ISB();
}

#ifdef __v7_inv_icache_all
#undef __v7_inv_icache_all
#endif
__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __v7_inv_icache_all()
{
    //register uint32_t __ICIALLU         __ASM("cp15:0:c7:c5:0");
    //__ICIALLU = 0;
    __asm__ __volatile__ ("mov  r0, #0");
    __asm__ __volatile__ ("mcr  p15,#0x0,r0,c7,c5,#0");
    __DSB();     //ensure completion of the invalidation
    __ISB();     //ensure instruction fetch path sees new I cache state
}

#ifdef __v7_inv_dcache_all
#undef __v7_inv_dcache_all
#endif
__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __v7_inv_dcache_all(void) {
    __v7_all_cache(0);
}

#ifdef __v7_inv_btac
#undef __v7_inv_btac
#endif
__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __v7_inv_btac()
{
    //register uint32_t __BPIALL          __ASM("cp15:0:c7:c5:6");
    //__BPIALL  = 0;
    __asm__ __volatile__ ("mov  r0, #0");
    __asm__ __volatile__ ("mcr  p15,#0x0,r0,c7,c5,#6");
    __DSB();     //ensure completion of the invalidation
    __ISB();     //ensure instruction fetch path sees new state
}

#ifdef __enable_mmu
#undef __enable_mmu
#endif
__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __enable_mmu()
{
    // Set M bit 0 to enable the MMU
    // Set AFE bit to enable simplified access permissions model
    // Clear TRE bit to disable TEX remap and A bit to disable strict alignment fault checking
    __set_SCTLR( (__get_SCTLR() & ~(1 << 28) & ~(1 << 1)) | 1 | (1 << 29));
    __ISB();
}

#ifdef  __enable_caches
#undef  __enable_caches
#endif
__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __enable_caches()
{
    // Set I bit 12 to enable I Cache
    // Set C bit  2 to enable D Cache
    __set_SCTLR( __get_SCTLR() | (1 << 12) | (1 << 2));
}

#ifdef __enable_btac
#undef __enable_btac
#endif
__STATIC_INLINE void __attribute__((section("SectionForBootstrapOperations"))) __enable_btac()
{
    __set_SCTLR( __get_SCTLR() | (1 << 11));
    __ISB();
}

void __attribute__((section("SectionForBootstrapOperations"))) InitMemorySubsystem(void) {

    /* This SVC is specific for reset where data / tlb / btac may contain undefined data, therefore before
     * enabling the cache you must invalidate the instruction cache, the data cache, TLB, and BTAC.
     * You are not required to invalidate the main TLB, even though it is recommended for safety
     * reasons. This ensures compatibility with future revisions of the processor. */

    unsigned int l2_id;

    /* Invalidate undefined data */
    __ca9u_inv_tlb_all();
    __v7_inv_icache_all();
    __v7_inv_dcache_all();
    __v7_inv_btac();

    /* Don't use this function during runtime since caches may contain valid data. For a correct cache maintenance you may need to execute a clean and
     * invalidate in order to flush the valid data to the next level cache.
     */
    __enable_mmu();

    /* After MMU is enabled and data has been invalidated, enable caches and BTAC */
    __enable_caches();
    __enable_btac();

    /* If present, you may also need to Invalidate and Enable L2 cache here */
    l2_id = PL310_GetID();
    if (l2_id)
    {
       PL310_InvAllByWay();
       PL310_Enable();
    }
}
#else

#endif

IRQHandler IRQTable[Renesas_RZ_A1_IRQ_MAX+1];

uint32_t IRQCount = sizeof IRQTable / 4;

uint32_t __attribute__((section("SectionForBootstrapOperations"))) InterruptHandlerRegister (IRQn_Type irq, IRQHandler handler)
{
    if (irq < IRQCount) {
        IRQTable[irq] = handler;
        return 0;
    }
    else {
        return 1;
    }
}

uint32_t __attribute__((section("SectionForBootstrapOperations"))) InterruptHandlerUnregister (IRQn_Type irq)
{
    if (irq < IRQCount) {
        IRQTable[irq] = 0;
        return 0;
    }
    else {
        return 1;
    }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void __attribute__((section("SectionForBootstrapOperations"))) SystemInit (void)
{
    IRQNestLevel = 0;
/*       do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards.          */
    RZ_A1_InitClock();
    RZ_A1_InitBus();

	//Configure GIC ICDICFR GIC_SetICDICFR()
    GIC_Enable();
    __enable_irq();

}


//Fault Status Register (IFSR/DFSR) definitions
#define FSR_ALIGNMENT_FAULT                  0x01   //DFSR only. Fault on first lookup
#define FSR_INSTRUCTION_CACHE_MAINTAINANCE   0x04   //DFSR only - async/external
#define FSR_SYNC_EXT_TTB_WALK_FIRST          0x0c   //sync/external
#define FSR_SYNC_EXT_TTB_WALK_SECOND         0x0e   //sync/external
#define FSR_SYNC_PARITY_TTB_WALK_FIRST       0x1c   //sync/external
#define FSR_SYNC_PARITY_TTB_WALK_SECOND      0x1e   //sync/external
#define FSR_TRANSLATION_FAULT_FIRST          0x05   //MMU Fault - internal
#define FSR_TRANSLATION_FAULT_SECOND         0x07   //MMU Fault - internal
#define FSR_ACCESS_FLAG_FAULT_FIRST          0x03   //MMU Fault - internal
#define FSR_ACCESS_FLAG_FAULT_SECOND         0x06   //MMU Fault - internal
#define FSR_DOMAIN_FAULT_FIRST               0x09   //MMU Fault - internal
#define FSR_DOMAIN_FAULT_SECOND              0x0b   //MMU Fault - internal
#define FSR_PERMISION_FAULT_FIRST            0x0f   //MMU Fault - internal
#define FSR_PERMISION_FAULT_SECOND           0x0d   //MMU Fault - internal
#define FSR_DEBUG_EVENT                      0x02   //internal
#define FSR_SYNC_EXT_ABORT                   0x08   //sync/external
#define FSR_TLB_CONFLICT_ABORT               0x10   //sync/external
#define FSR_LOCKDOWN                         0x14   //internal
#define FSR_COPROCESSOR_ABORT                0x1a   //internal
#define FSR_SYNC_PARITY_ERROR                0x19   //sync/external
#define FSR_ASYNC_EXTERNAL_ABORT             0x16   //DFSR only - async/external
#define FSR_ASYNC_PARITY_ERROR               0x18   //DFSR only - async/external

void __attribute__((section("SectionForBootstrapOperations"))) CDAbtHandler(uint32_t DFSR, uint32_t DFAR, uint32_t LR) {
    uint32_t FS = (DFSR & (1 << 10)) >> 6 | (DFSR & 0x0f); //Store Fault Status

    switch(FS) {
        //Synchronous parity errors - retry
        case FSR_SYNC_PARITY_ERROR:
        case FSR_SYNC_PARITY_TTB_WALK_FIRST:
        case FSR_SYNC_PARITY_TTB_WALK_SECOND:
            return;

        //Your code here. Value in DFAR is invalid for some fault statuses.
        case FSR_ALIGNMENT_FAULT:
        case FSR_INSTRUCTION_CACHE_MAINTAINANCE:
        case FSR_SYNC_EXT_TTB_WALK_FIRST:
        case FSR_SYNC_EXT_TTB_WALK_SECOND:
        case FSR_TRANSLATION_FAULT_FIRST:
        case FSR_TRANSLATION_FAULT_SECOND:
        case FSR_ACCESS_FLAG_FAULT_FIRST:
        case FSR_ACCESS_FLAG_FAULT_SECOND:
        case FSR_DOMAIN_FAULT_FIRST:
        case FSR_DOMAIN_FAULT_SECOND:
        case FSR_PERMISION_FAULT_FIRST:
        case FSR_PERMISION_FAULT_SECOND:
        case FSR_DEBUG_EVENT:
        case FSR_SYNC_EXT_ABORT:
        case FSR_TLB_CONFLICT_ABORT:
        case FSR_LOCKDOWN:
        case FSR_COPROCESSOR_ABORT:
        case FSR_ASYNC_EXTERNAL_ABORT: //DFAR invalid
        case FSR_ASYNC_PARITY_ERROR:   //DFAR invalid
        default:
            while(1);
    }
}

void __attribute__((section("SectionForBootstrapOperations"))) CPAbtHandler(uint32_t IFSR, uint32_t IFAR, uint32_t LR) {
    uint32_t FS = (IFSR & (1 << 10)) >> 6 | (IFSR & 0x0f); //Store Fault Status

    switch(FS) {
        //Synchronous parity errors - retry
        case FSR_SYNC_PARITY_ERROR:
        case FSR_SYNC_PARITY_TTB_WALK_FIRST:
        case FSR_SYNC_PARITY_TTB_WALK_SECOND:
            return;

        //Your code here. Value in IFAR is invalid for some fault statuses.
        case FSR_SYNC_EXT_TTB_WALK_FIRST:
        case FSR_SYNC_EXT_TTB_WALK_SECOND:
        case FSR_TRANSLATION_FAULT_FIRST:
        case FSR_TRANSLATION_FAULT_SECOND:
        case FSR_ACCESS_FLAG_FAULT_FIRST:
        case FSR_ACCESS_FLAG_FAULT_SECOND:
        case FSR_DOMAIN_FAULT_FIRST:
        case FSR_DOMAIN_FAULT_SECOND:
        case FSR_PERMISION_FAULT_FIRST:
        case FSR_PERMISION_FAULT_SECOND:
        case FSR_DEBUG_EVENT: //IFAR invalid
        case FSR_SYNC_EXT_ABORT:
        case FSR_TLB_CONFLICT_ABORT:
        case FSR_LOCKDOWN:
        case FSR_COPROCESSOR_ABORT:
        default:
            while(1);
    }
}

//returns amount to decrement lr by
//this will be 0 when we have emulated the instruction and simply want to execute the next instruction
//this will be 2 when we have performed some maintenance and want to retry the instruction in thumb (state == 2)
//this will be 4 when we have performed some maintenance and want to retry the instruction in arm (state == 4)
uint32_t __attribute__((section("SectionForBootstrapOperations"))) CUndefHandler(uint32_t opcode, uint32_t state, uint32_t LR) {
    const int THUMB = 2;
    const int ARM = 4;
    //Lazy VFP/NEON initialisation and switching
    if ((state == ARM   && ((opcode & 0x0C000000)) >> 26 == 0x03) ||
        (state == THUMB && ((opcode & 0xEC000000)) >> 26 == 0x3B)) {
        if (((opcode & 0x00000E00) >> 9) == 5) { //fp instruction?
            FPUEnable();
            return state;
        }
    }

    //Add code here for other Undef cases
    while(1);
}

#if defined(__ARMCC_VERSION)
#pragma push
#pragma arm

//Critical section, called from undef handler, so systick is disabled
__asm void FPUEnable(void) {
        ARM

        //Permit access to VFP registers by modifying CPACR
        MRC     p15,0,R1,c1,c0,2
        ORR     R1,R1,#0x00F00000
        MCR     p15,0,R1,c1,c0,2

        //Enable VFP
        VMRS    R1,FPEXC
        ORR     R1,R1,#0x40000000
        VMSR    FPEXC,R1

        //Initialise VFP registers to 0
        MOV     R2,#0
        VMOV    D0, R2,R2
        VMOV    D1, R2,R2
        VMOV    D2, R2,R2
        VMOV    D3, R2,R2
        VMOV    D4, R2,R2
        VMOV    D5, R2,R2
        VMOV    D6, R2,R2
        VMOV    D7, R2,R2
        VMOV    D8, R2,R2
        VMOV    D9, R2,R2
        VMOV    D10,R2,R2
        VMOV    D11,R2,R2
        VMOV    D12,R2,R2
        VMOV    D13,R2,R2
        VMOV    D14,R2,R2
        VMOV    D15,R2,R2

        //Initialise FPSCR to a known state
        VMRS    R2,FPSCR
        LDR     R3,=0x00086060 //Mask off all bits that do not have to be preserved. Non-preserved bits can/should be zero.
        AND     R2,R2,R3
        VMSR    FPSCR,R2

        BX      LR
}
#pragma pop
#elif defined(__GNUC__)
void FPUEnable(void)
{
    __asm__ __volatile__ (
            ".align 2                   \n\t"
            ".arm                       \n\t"
            "mrc    p15,0,r1,c1,c0,2    \n\t"
            "orr    r1,r1,#0x00f00000   \n\t"
            "mcr    p15,0,r1,c1,c0,2    \n\t"
            "vmrs   r1,fpexc            \n\t"
            "orr    r1,r1,#0x40000000   \n\t"
            "vmsr   fpexc,r1            \n\t"
            "mov    r2,#0               \n\t"
            "vmov   d0, r2,r2           \n\t"
            "vmov   d1, r2,r2           \n\t"
            "vmov   d2, r2,r2           \n\t"
            "vmov   d3, r2,r2           \n\t"
            "vmov   d4, r2,r2           \n\t"
            "vmov   d5, r2,r2           \n\t"
            "vmov   d6, r2,r2           \n\t"
            "vmov   d7, r2,r2           \n\t"
            "vmov   d8, r2,r2           \n\t"
            "vmov   d9, r2,r2           \n\t"
            "vmov   d10,r2,r2           \n\t"
            "vmov   d11,r2,r2           \n\t"
            "vmov   d12,r2,r2           \n\t"
            "vmov   d13,r2,r2           \n\t"
            "vmov   d14,r2,r2           \n\t"
            "vmov   d15,r2,r2           \n\t"
            "vmrs   r2,fpscr            \n\t"
            "ldr    r3,=0x00086060      \n\t"
            "and    r2,r2,r3            \n\t"
            "vmsr   fpscr,r2            \n\t"
            "bx     lr                  \n\t"
    );
}
#else
#endif
