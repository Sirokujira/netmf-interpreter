/* File: startup_ARMCM3.s
 * Purpose: startup file for Cortex-M3/M4 devices. Should use with 
 *   GNU Tools for ARM Embedded Processors
 * Version: V1.1
 * Date: 17 June 2011
 * 
 * Copyright (C) 2011 ARM Limited. All rights reserved.
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3/M4 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */
    .syntax unified
    .extern _start

@ Standard definitions of mode bits and interrupt (I & F) flags in PSRs
    .equ    USR_MODE,   0x10
    .equ    FIQ_MODE,   0x11
    .equ    IRQ_MODE,   0x12
    .equ    SVC_MODE,   0x13
    .equ    ABT_MODE,   0x17
    .equ    UND_MODE,   0x1b
    .equ    SYS_MODE,   0x1f
    .equ    Thum_bit,   0x20            @ CPSR/SPSR Thumb bit

    .equ    GICI_BASE,  0xe8202000
    .equ    ICCIAR_OFFSET,  0x0000000C
    .equ    ICCEOIR_OFFSET, 0x00000010
    .equ    ICCHPIR_OFFSET, 0x00000018
    .equ    GICD_BASE, 0xe8201000
    .equ    ICDISER0_OFFSET, 0x00000100
    .equ    ICDICER0_OFFSET, 0x00000180
    .equ    ICDISPR0_OFFSET, 0x00000200
    .equ    ICDABR0_OFFSET, 0x00000300
    .equ    ICDIPR0_OFFSET, 0x00000400

    .equ    Mode_USR, 0x10
    .equ    Mode_FIQ, 0x11
    .equ    Mode_IRQ, 0x12
    .equ    Mode_SVC, 0x13
    .equ    Mode_ABT, 0x17
    .equ    Mode_UND, 0x1B
    .equ    Mode_SYS, 0x1F

    .equ     I_Bit, 0x80                @ when I bit is set, IRQ is disabled
    .equ     F_Bit, 0x40                @ when F bit is set, FIQ is disabled
    .equ     T_Bit, 0x20                @ when T bit is set, core is in Thumb state

    .equ    GIC_ERRATA_CHECK_1, 0x000003FE
    .equ    GIC_ERRATA_CHECK_2, 0x000003FF

    .equ    Sect_Normal, 0x00005c06     @outer & inner wb/wa, non-shareable, executable, rw, domain 0, base addr 0
    .equ    Sect_Normal_Cod, 0x0000dc06 @outer & inner wb/wa, non-shareable, executable, ro, domain 0, base addr 0
    .equ    Sect_Normal_RO, 0x0000dc16  @as Sect_Normal_Cod, but not executable
    .equ    Sect_Normal_RW, 0x00005c16  @as Sect_Normal_Cod, but writeable and not executable
    .equ    Sect_SO, 0x00000c12         @strongly-ordered (therefore shareable), not executable, rw, domain 0, base addr 0
    .equ    Sect_Device_RO, 0x00008c12  @device, non-shareable, non-executable, ro, domain 0, base addr 0
    .equ    Sect_Device_RW, 0x00000c12  @as Sect_Device_RO, but writeable
    .equ    Sect_Fault, 0x00000000      @this translation will fault (the bottom 2 bits are important, the rest are ignored)

    .equ    RAM_BASE, 0x80000000
    .equ    VRAM_BASE, 0x18000000
    .equ    SRAM_BASE, 0x2e000000
    .equ    ETHERNET, 0x1a000000
    .equ    CS3_PERIPHERAL_BASE,0x1c000000

@ Standard definitions of mode bits and interrupt (I & F) flags in PSRs
    .equ    USR_MODE,   0x10
    .equ    FIQ_MODE,   0x11
    .equ    IRQ_MODE,   0x12
    .equ    SVC_MODE,   0x13
    .equ    ABT_MODE,   0x17
    .equ    UND_MODE,   0x1b
    .equ    SYS_MODE,   0x1f
    .equ    Thum_bit,   0x20            @ CPSR/SPSR Thumb bit

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0xc00
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop
__AStackLimit:
    .space    Stack_Size
    .size __AStackLimit, . - __AStackLimit
__AStackTop:
    .size __AStackTop, . - __AStackTop
__BStackLimit:
    .space    Stack_Size
    .size __BStackLimit, . - __StackLimit
__BStackTop:
    .size __BStackTop, . - __BStackTop
__CStackLimit:
    .space    Stack_Size
    .size __CStackLimit, . - __CStackLimit
__CStackTop:
    .size __CStackTop, . - __CStackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0x800
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .space    Heap_Size
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit
    
    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   0xe59ff018 // 0x00
    .long   0xe59ff018 // 0x04
    .long   0xe59ff018 // 0x08
    .long   0xe59ff018 // 0x0c
    .long   0xe59ff018 // 0x10
    .long   0xe59ff018 // 0x14
    .long   0xe59ff018 // 0x18
    .long   0xe59ff018 // 0x1c

    .long   Reset_Handler         /* 0x20 */
    .long   Undef_Handler         /* 0x24 */
    .long   SVC_Handler           /* 0x28 */
    .long   PAbt_Handler          /* 0x2c */
    .long   DAbt_Handler          /* 0x30 */
    .long   0                     /* Reserved */
    .long   IRQ_Handler           /* IRQ */
    .long   FIQ_Handler           /* FIQ */


    .size    __isr_vector, . - __isr_vector

    .text
    .align 2
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    mrc     p15, 0, r0, c0, c0, 5   @;; Read MPIDR
    ands    r0, r0, #3              @;; if not cpu0, then sleep
goToSleep:
    wfine
    bne goToSleep
@ Enable access to NEON/VFP by enabling access to Coprocessors 10 and 11.
@ Enables Full Access i.e. in both privileged and non privileged modes
    mrc p15, 0, r0, c1, c0, 2       @; Read Coprocessor Access Control Register (CPACR)
    orr r0, r0, #(0xF << 20)        @; Enable access to CP 10 & 11
    mcr p15, 0, r0, c1, c0, 2       @; Write Coprocessor Access Control Register (CPACR)
    isb
@ Switch on the VFP and NEON hardware
    mov r0, #0x40000000
    vmsr    fpexc, r0               @; Write FPEXC register, EN bit set
    mrc p15, 0, r0, c1, c0, 0       @; Read CP15 System Control register
    bic r0, r0, #(0x1 << 12)        @; Clear I bit 12 to disable I Cache
    bic r0, r0, #(0x1 <<  2)        @; Clear C bit  2 to disable D Cache
    bic r0, r0, #0x1                @; Clear M bit  0 to disable MMU
    bic r0, r0, #(0x1 << 11)        @; Clear Z bit 11 to disable branch prediction
    bic r0, r0, #(0x1 << 13)        @; Clear V bit 13 to disable hivecs
    mcr p15, 0, r0, c1, c0, 0       @; Write value back to CP15 System Control register
    isb
@ Set Vector Base Address Register (VBAR) to point to this application's vector table
    @mrc     p15, 0, r0, c1, c0, 0   @ Read SCTLR
    @mov     r1, #0xffffdfff         @ Select normal vector
    @and     r0, r1
    @mcr     p15, 0, r0, c1, c0, 0   @ Write SCTLR

    @mrc     p15, 0, r0, c12, c0, 0  @ Read vector base address
    ldr     r0, =__isr_vector       @ set SRAM top to vector base address
    mcr     p15, 0, r0, c12, c0, 0  @ Write vector base address

@ Setup Stack for each exceptional mode
    ldr     r0, =__StackTop
@ Enter Undefined Instruction Mode and set its Stack Pointer
    msr     cpsr_c, #0xdb   @ #Mode_UND:OR:I_Bit:OR:F_Bit
    mov     sp, r0
    sub     r0, r0, #0x100  @ #UND_Stack_Size
@ Enter Abort Mode and set its Stack Pointer
    msr     cpsr_c, #0xd7   @ #Mode_ABT:OR:I_Bit:OR:F_Bit
    mov     sp, r0
    sub     r0, r0, #0x100  @ #ABT_Stack_Size
@ Enter FIQ Mode and set its Stack Pointer
    msr     cpsr_c, #0xd1   @ #Mode_FIQ:OR:I_Bit:OR:F_Bit
    mov     sp, r0
    sub     r0, r0, #0x100  @ #FIQ_Stack_Size
@ Enter IRQ Mode and set its Stack Pointer
    msr     cpsr_c, #0xd2   @ #Mode_IRQ:OR:I_Bit:OR:F_Bit
    mov     sp, r0
    sub     r0, r0, #0x8000  @ #IRQ_Stack_Size
@ Enter Supervisor Mode and set its Stack Pointer
    msr     cpsr_c, #0xd3   @ #Mode_SVC:OR:I_Bit:OR:F_Bit
    mov     sp, r0
@ Enter System Mode to complete initialization and enter kernel
    msr     cpsr_c, #0xdf   @ #Mode_SYS:OR:I_Bit:OR:F_Bit
    mov     sp, r0

    isb
    ldr     r0, =RZ_A1_SetSramWriteEnable
    blx     r0
    bl      create_translation_table
    ldr     r0, =SystemInit
    blx     r0
    ldr     r0, =InitMemorySubsystem
    blx     r0

    ldr     r1, =__etext
    ldr     r2, =__data_start__
    ldr     r3, =__data_end__

.Lflash_to_ram_loop:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .Lflash_to_ram_loop

    ldr     r0, =_start
    bx      r0

    ldr     r0, sf_boot     @ dummy to keep boot loader area
loop_here:
    b       loop_here

sf_boot:
    .word   boot_loader

    .pool
    .size Reset_Handler, . - Reset_Handler

    .text

Undef_Handler:
    SRSFD   SP!, #Mode_UND
    PUSH    {R0-R4, R12}              @ Save APCS corruptible registers to UND mode stack
    MRS     R0, SPSR
    TST     R0, #T_Bit                @ Check mode
    MOVEQ   R1, #4                    @ R1 = 4 ARM mode
    MOVNE   R1, #2                    @ R1 = 2 Thumb mode
    SUB     R0, LR, R1
    LDREQ   R0, [R0]                  @ ARM mode - R0 points to offending instruction
    BEQ     undef_cont
@Thumb instruction
@Determine if it is a 32-bit Thumb instruction
    LDRH    R0, [R0]
    MOV     R2, #0x1c
    CMP     R2, R0, LSR #11
    BHS     undef_cont                @16-bit Thumb instruction
@32-bit Thumb instruction. Unaligned - we need to reconstruct the offending instruction.
    LDRH    R2, [LR]
    ORR     R0, R2, R0, LSL #16
undef_cont:
    MOV     R2, LR                    @ Set LR to third argument
@               AND     R12, SP, #4               ; Ensure stack is 8-byte aligned
    MOV     R3, SP                    @ Ensure stack is 8-byte aligned
    AND     R12, R3, #4
    SUB     SP, SP, R12               @ Adjust stack
    PUSH    {R12, LR}                 @ Store stack adjustment and dummy LR
@R0 Offending instruction
@R1 =2 (Thumb) or =4 (ARM)
    BL      CUndefHandler
    POP     {R12, LR}                 @ Get stack adjustment & discard dummy LR
    ADD     SP, SP, R12               @ Unadjust stack
    LDR     LR, [SP, #24]             @ Restore stacked LR and possibly adjust for retry
    SUB     LR, LR, R0
    LDR     R0, [SP, #28]             @ Restore stacked SPSR
    msr     spsr_cxsf, r0
    POP     {R0-R4, R12}              @ Restore stacked APCS registers
    ADD     SP, SP, #8                @ Adjust SP for already-restored banked registers
    MOVS    PC, LR

PAbt_Handler:
    SUB     LR, LR, #4                @ Pre-adjust LR
    SRSFD   SP!, #Mode_ABT            @ Save LR and SPRS to ABT mode stack
    PUSH    {R0-R4, R12}              @ Save APCS corruptible registers to ABT mode stack
    MRC     p15, 0, R0, c5, c0, 1     @ IFSR
    MRC     p15, 0, R1, c6, c0, 2     @ IFAR
    MOV     R2, LR                    @ Set LR to third argument
@   AND     R12, SP, #4               @ Ensure stack is 8-byte aligned
    MOV     R3, SP                    @ Ensure stack is 8-byte aligned
    AND     R12, R3, #4
    SUB     SP, SP, R12               @ Adjust stack
    PUSH    {R12, LR}                 @ Store stack adjustment and dummy LR
    BL      CPAbtHandler
    POP     {R12, LR}                 @ Get stack adjustment & discard dummy LR
    ADD     SP, SP, R12               @ Unadjust stack
    POP     {R0-R4, R12}              @ Restore stack APCS registers
    RFEFD   SP!                       @ Return from exception

DAbt_Handler:
    SUB     LR, LR, #8                @ Pre-adjust LR
    SRSFD   SP!, #Mode_ABT            @ Save LR and SPRS to ABT mode stack
    PUSH    {R0-R4, R12}              @ Save APCS corruptible registers to ABT mode stack
    CLREX                             @ State of exclusive monitors unknown after taken data abort
    MRC     p15, 0, R0, c5, c0, 0     @ DFSR
    MRC     p15, 0, R1, c6, c0, 0     @ DFAR
    MOV     R2, LR                    @ Set LR to third argument
@   AND     R12, SP, #4               @ Ensure stack is 8-byte aligned
    MOV     R3, SP                    @ Ensure stack is 8-byte aligned
    AND     R12, R3, #4
    SUB     SP, SP, R12               @ Adjust stack
    PUSH    {R12, LR}                 @ Store stack adjustment and dummy LR
    BL      CDAbtHandler
    POP     {R12, LR}                 @ Get stack adjustment & discard dummy LR
    ADD     SP, SP, R12               @ Unadjust stack
    POP     {R0-R4, R12}              @ Restore stacked APCS registers
    RFEFD   SP!                       @ Return from exception

FIQ_Handler:
@ An FIQ might occur between the dummy read and the real read of the GIC in IRQ_Handler,
@ so if a real FIQ Handler is implemented, this will be needed before returning:
@ LDR     R1, =GICI_BASE
@ LDR     R0, [R1, #ICCHPIR_OFFSET]   @ Dummy Read ICCHPIR (GIC CPU Interface register) to avoid GIC 390 errata 801120
    B       .

SVC_Handler:
    B       .

IRQ_Handler:
@prologue
    SUB     LR, LR, #4                  @ Pre-adjust LR
    SRSFD   SP!, #Mode_SVC              @ Save LR_IRQ and SPRS_IRQ to SVC mode stack
    CPS     #Mode_SVC                   @ Switch to SVC mode, to avoid a nested interrupt corrupting LR on a BL
    PUSH    {R0-R3, R12}                @ Save remaining APCS corruptible registers to SVC stack
@   AND     R1, SP, #4                  @ Ensure stack is 8-byte aligned
    MOV     R3, SP                      @ Ensure stack is 8-byte aligned
    AND     R1, R3, #4
    SUB     SP, SP, R1                  @ Adjust stack
    PUSH    {R1, LR}                    @ Store stack adjustment and LR_SVC to SVC stack
    LDR     R0, =IRQNestLevel           @ Get address of nesting counter
    LDR     R1, [R0]
    ADD     R1, R1, #1                  @ Increment nesting counter
    STR     R1, [R0]
@identify and acknowledge interrupt
    LDR     R1, =GICI_BASE
    LDR     R0, [R1, #ICCHPIR_OFFSET]   @ Dummy Read ICCHPIR (GIC CPU Interface register) to avoid GIC 390 errata 801120
    LDR     R0, [R1, #ICCIAR_OFFSET]    @ Read ICCIAR (GIC CPU Interface register)
    DSB                                 @ Ensure that interrupt acknowledge completes before re-enabling interrupts
@ Workaround GIC 390 errata 733075
@ If the ID is not 0, then service the interrupt as normal.
@ If the ID is 0 and active, then service interrupt ID 0 as normal.
@ If the ID is 0 but not active, then the GIC CPU interface may be locked-up, so unlock it
@   with a dummy write to ICDIPR0.  This interrupt should be treated as spurious and not serviced.
@
    LDR     R2, =GICD_BASE
    LDR     R3, =GIC_ERRATA_CHECK_1
    CMP     R0, R3
    BEQ     unlock_cpu
    LDR     R3, =GIC_ERRATA_CHECK_2
    CMP     R0, R3
    BEQ     unlock_cpu
    CMP     R0, #0
    BNE     int_active                  @ If the ID is not 0, then service the interrupt
    LDR     R3, [R2, #ICDABR0_OFFSET]   @ Get the interrupt state
    TST     R3, #1
    BNE     int_active                  @ If active, then service the interrupt
unlock_cpu:
    LDR     R3, [R2, #ICDIPR0_OFFSET]   @ Not active, so unlock the CPU interface
    STR     R3, [R2, #ICDIPR0_OFFSET]   @   with a dummy write
    DSB                                 @ Ensure the write completes before continuing
    B       ret_irq                     @ Do not service the spurious interrupt
@ End workaround
int_active:
    LDR     R2, =IRQCount               @ Read number of IRQs
    LDR     R2, [R2]
    CMP     R0, R2                      @ Clean up and return if no handler
    BHS     ret_irq                     @ In a single-processor system, spurious interrupt ID 1023 does not need any special handling
    LDR     R2, =IRQTable               @ Get address of handler
    LDR     R2, [R2, R0, LSL #2]
    CMP     R2, #0                      @ Clean up and return if handler address is 0
    BEQ     ret_irq
    PUSH    {R0,R1}
    CPSIE   i                           @ Now safe to re-enable interrupts
    BLX     R2                          @ Call handler. R0 will be IRQ number
    CPSID   i                           @ Disable interrupts again
@write EOIR (GIC CPU Interface register)
    POP     {R0,R1}
    DSB                                 @ Ensure that interrupt source is cleared before we write the EOIR
ret_irq:
@epilogue
    STR     R0, [R1, #ICCEOIR_OFFSET]
    LDR     R0, =IRQNestLevel           @ Get address of nesting counter
    LDR     R1, [R0]
    SUB     R1, R1, #1                  @ Decrement nesting counter
    STR     R1, [R0]

    POP     {R1, LR}                    @ Get stack adjustment and restore LR_SVC
    ADD     SP, SP, R1                  @ Unadjust stack

    POP     {R0-R3,R12}                 @ Restore stacked APCS registers
    RFEFD   SP!                         @ Return from exception

    .text
    .end

