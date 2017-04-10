
                        README
           FMP porting for the ZYNQ-7000

             2013 (C) Daniel Sangorrin daniel.sangorrin@gmail.com
             2017 (C) Shinya Honda honda@ertl.jp

--------
Overview
--------

TOPPERS/FMP (http://www.toppers.jp/en/fmp-kernel.html) is an RTOS with 
support for multi-core processors. It is developed by the TOPPERS 
project (http://www.toppers.jp/en/index.html) and distributed as open 
source code through the TOPPERS license 
(http://www.toppers.jp/en/license.html).

FMP follows the "TOPPERS New Generation Kernels" specification 
(http://www.toppers.jp/documents.html). Contact me for an English 
translation of the specification. A good way to understand FMP's API 
is by looking at the sample program in the "fmp/sample" folder, or the 
header files in "fmp/kernel/". (Hint: it is based on the uITRON4.0 
interface).

The main characteristics of FMP are:

  - It supports SMP and AMP configurations (however, in the case of AMP
    all cores should be able to execute the same instruction set).

  - Kernel and applications are linked in a single binary without
    memory protection.

  - Tasks are assigned to processor cores during the design phase. This is
    done through a configuration file (.cfg) as shown in the sample program.

  - The kernel will not automatically migrate tasks (i.e., load balancing)
    during the execution of the system.

  - However, the API allows migrating a task to a different processor core
    at run time.

  - The execution of FMP can be traced and displayed graphically through
    the TLV tracelog visualizer (http://www.toppers.jp/tlv.html)

  - Several target boards supported (ARM Cortex-A9, NIOS2, SH2A, SH4A)

This guide provides a quickstart for running FMP on the ZYNQ-7000
(a XilinX FPGA that includes 2 ARM Cortex-A9 cores) using the Zedboard.

THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.

------------------
Change Log
------------------
- 2017/02/18
 Support 1.4.0
