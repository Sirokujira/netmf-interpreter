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

    .syntax unified
    .global  EntryPoint
    .global Reset_Handler
    .global StackBottom
    .global StackTop
    .global HeapBegin
    .global HeapEnd
    .global CustomHeapBegin
    .global CustomHeapEnd
    .global PowerOnReset
    .extern  PreStackInit


    .extern __main
    .extern BootstrapCode

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

    @ Power On Reset vector table for the device
    @ This is placed at physical address 0 by the
    @ linker. THe first entry is the initial stack
    @ pointer as defined for the ARMv6-M and ARMv7-M
    @ architecture profiles. Therefore, all such 
    @ devices MUST have some amount of SRAM available
    @ for booting

    .section SectionForPowerOnReset, "x", %progbits
PowerOnReset:
    .word    __initial_sp
    .word     Reset_Handler @ Reset
    .word     Fault_Handler @ NMI
    .word     Fault_Handler @ Hard Fault
    .word     Fault_Handler @ MMU Fault
    .word     Fault_Handler @ Bus Fault
    .word     Fault_Handler @ Usage Fault

    .text
    .thumb
    .thumb_func
    .align   2
    .global   Reset_Handler
    .type    Reset_Handler, %function

    .section i.EntryPoint, "ax", %progbits
EntryPoint:
Reset_Handler:
    bl  BootstrapCode
    b   __main

    .pool
    .size   Reset_Handler, . - Reset_Handler

    .balign   4

Fault_Handler:
    b       Fault_Handler

    .end

