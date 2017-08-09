@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@
@  Licensed under the Apache License, Version 2.0 (the "License")@
@  you may not use this file except in compliance with the License.
@  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
@
@  Copyright (c) Microsoft Corporation. All rights reserved.
@  Implementation for GR-PEACH: Copyright (c) Tooru Oonuma.
@
@  CORTEX-A9 Standard Entry Code 
@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@
@ This version of the "boot entry" support is used when the application is 
@ loaded or otherwise started from a bootloader. (e.g. this application isn't 
@ a boot loader). More specifically this version is used whenever the application
@ does NOT run from the power on reset vector because some other code is already
@ there.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@
    .syntax unified
    .global  EntryPoint
    .global StackBottom
    .global StackTop
    .global HeapBegin
    .global HeapEnd
    .global CustomHeapBegin
    .global CustomHeapEnd
    .global Reset_Handler

    .extern  SystemInit
    .extern  __main

    @*************************************************************************

#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x1000
#endif
    .section SectionForStackBottom,     "a", %progbits
    .align 3
    .globl  __StackTop
    .globl  __StackLimit
StackBottom:
__StackLimit:
    .space  Stack_Size
    .size   __StackLimit, . - __StackLimit
__StackTop:
    .size   __StackTop, . - __StackTop
__AStackLimit:
    .space  Stack_Size
    .size   __AStackLimit, . - __AStackLimit
__AStackTop:
    .size   __AStackTop, . - __AStackTop
__BStackLimit:
    .space  Stack_Size
    .size   __BStackLimit, . - __StackLimit
__BStackTop:
    .size   __BStackTop, . - __BStackTop
__CStackLimit:
    .space  Stack_Size
    .size   __CStackLimit, . - __CStackLimit
__CStackTop:
    .size   __CStackTop, . - __CStackTop
    .section SectionForStackTop,        "a", %progbits
StackTop:    .word 0
    .section SectionForHeapBegin,       "a", %progbits
HeapBegin:   .word 0
    .section SectionForHeapEnd,         "a", %progbits
HeapEnd:     .word 0
    .section SectionForCustomHeapBegin, "a", %progbits
CustomHeapBegin:   .word 0
    .section SectionForCustomHeapEnd,   "a", %progbits
CustomHeapEnd:     .word 0
    .section .stack

    @.section    .text, "ax", %progbits

    @.org    0x000

    .section i.EntryPoint, "ax", %progbits
    @.section .isr_vector
    .align  2
    .globl  __isr_vector
.section i.EntryPoint, "ax", %progbits

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

    .size   __isr_vector, . - __isr_vector
@ The first word has a dual role:
@ - It is the entry point of the application loaded or discovered by
@   the bootloader and therfore must be valid executable code
@ - it contains a signature word used to identify application blocks
@   in TinyBooter (see: Tinybooter_ProgramWordCheck() for more details )
@ * The additional entries in this table are completely ignored and
@   remain for backwards compatibility. Since the boot loader is hard
@   coded to look for the signature, half of which is an actual relative
@   branch instruction, removing the unused entries would require all
@   bootloaders to be updated as well. [sic.]
@   [ NOTE:
@     In the next major release where we can afford to break backwards
@     compatibility this will almost certainly change, as the whole
@     init/startup for NETMF is overly complex. The various tools used
@     for building the CLR have all come around to supporting simpler
@     init sequences we should leverage directly
@   ]
Reset_Handler:
EntryPoint:
startup:
    mrc     p15, 0, r0, c0, c0, 5   @;; Read MPIDR
    ands    r0, r0, #3              @;; if not cpu0, then sleep
goToSleep:
    wfine
    bne goToSleep
@ Enable access to NEON/VFP by enabling access to Coprocessors 10 and 11.
@ Enables Full Access i.e. in both privileged and non privileged modes
    mrc     p15, 0, r0, c1, c0, 2   @; Read Coprocessor Access Control Register (CPACR)
    orr     r0, r0, #(0xF << 20)    @; Enable access to CP 10 & 11
    mcr     p15, 0, r0, c1, c0, 2   @; Write Coprocessor Access Control Register (CPACR)
    isb
@ Switch on the VFP and NEON hardware
    mov     r0, #0x40000000
    vmsr    fpexc, r0               @; Write FPEXC register, EN bit set
    mrc     p15, 0, r0, c1, c0, 0   @; Read CP15 System Control register
    bic     r0, r0, #(0x1 << 12)    @; Clear I bit 12 to disable I Cache
    bic     r0, r0, #(0x1 <<  2)    @; Clear C bit  2 to disable D Cache
    bic     r0, r0, #0x1            @; Clear M bit  0 to disable MMU
    bic     r0, r0, #(0x1 << 11)    @; Clear Z bit 11 to disable branch prediction
    bic     r0, r0, #(0x1 << 13)    @; Clear V bit 13 to disable hivecs
    mcr     p15, 0, r0, c1, c0, 0   @; Write value back to CP15 System Control register
    isb
@ Set Vector Base Address Register (VBAR) to point to this application's vector table
    mrc     p15, 0, r0, c1, c0, 0   @ Read SCTLR
    mov     r1, #0xffffdfff         @ Select normal vector
    and     r0, r1
    mcr     p15, 0, r0, c1, c0, 0   @ Write SCTLR

    mrc     p15, 0, r0, c12, c0, 0  @ Read vector base address
    ldr     r0, =__isr_vector       @ set SRAM top to vector base address
    mcr     p15, 0, r0, c12, c0, 0  @ Write vector base address

    ldr     sp, =__AStackTop
    cps     #IRQ_MODE               @;; IRQ Mode
    ldr     sp, =__BStackTop
    cps     #FIQ_MODE               @;; FIQ Mode
    ldr     sp, =__CStackTop
    @CPS    #ABT_MODE               @;; ABT Mode
    @LDR    sp, =__StackTop
    cps     #SYS_MODE               @;; SYS Mode
@; System mode Stack pointer is set up ARM_LIB_STACK in the __main()->__entry()
    ldr     sp, =__StackTop
@    ldr    r1, =__etext
@    ldr    r2, =__data_start__
@    ldr    r3, =__data_end__
@.Lflash_to_ram_loop:
@    cmp    r2, r3
@    ittt   lt
@    ldrlt  r0, [r1], #4
@    strlt  r0, [r2], #4
@    blt    .Lflash_to_ram_loop
@
    ldr     r0, =RZ_A1_SetSramWriteEnable
    blx     r0
    bl      create_translation_table

    ldr     r0, =SystemInit
    blx     r0
    ldr     r0, =InitMemorySubsystem
    blx     r0
    @ start user program
    ldr     r0, =BootstrapCode
    blx     r0
    ldr     r0, =BootEntry
    bx      r0

    ldr     r0, sf_boot     @ dummy to keep boot loader area
loop_here:
    b       loop_here

StackTop_Ptr:
    .word     StackTop
sf_boot:
    .word   boot_loader

    .pool
    .size   Reset_Handler, . - Reset_Handler

    @.text
.end
