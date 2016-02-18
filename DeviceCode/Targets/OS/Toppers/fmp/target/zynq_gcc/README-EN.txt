
                        README
           FMP porting for the ZYNQ-7000 Zedboard

                2013 (C) Daniel Sangorrin
                daniel.sangorrin@gmail.com

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
translation of the specification. A good way to understand FMP's API is
by looking at the sample program in the "fmp/sample" folder,
or the header files in "fmp/kernel/". (Hint: it is based on the uITRON4.0
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

----------------
Host environment
----------------

You need a UNIX-based execution environment for building FMP. In particular,
we tested it on the following operating system:

    Ubuntu 12.04 (LTS) 32 bits

If you have a different environment, we recommend to first create a virtual
machine with the same operating system and run these instructions there.

Applications and libraries that must be installed:

  - C++ Boost libraries (>1.46)
    $ sudo apt-get install libboost libboost-regex-dev libboost-system-dev \
      libboost-filesystem-dev libboost-program-options-dev

  - ARM cross-compiler: arm-none-eabi-gcc version (download "Sourcery
    CodeBench Lite 2012.03-56 at "http://www.mentor.com/embedded-software/
    sourcery-tools/sourcery-codebench/editions/lite-edition/"

  - Essential software for building applications (make, etc.)
    $ sudo apt-get install build-essential

------------------
Build instructions
------------------

Download the FMP package for Zedboard and uncompress it:

$ firefox http://www.toppers.jp/fmp-e-download.html&
$ tar zxvf fmp_zynq_gcc-xxxxx.tar.gz

The folder "fmp/target/zynq_gcc" contains the ZYNQ-dependent code (BSP):

$ ls fmp/target/
zynq_gcc

In order to build an application we first have to build the configuration
tool for FMP. This tool depends on the C++ Boost libraries so you will have
to install them too (see instructions in the "Host environment" section).

$ cd fmp/cfg/
$ ./configure --without-xml
$ make depend
$ make
$ cd ../../

The above instructions will generate the configurator binary 'cfg' (Note: when
using Cygwin the binary is named 'cfg.exe').

Now we will create an application in the folder "obj/obj_sample" by using
the application template at "fmp/sample":

$ mkdir -p fmp/obj/obj_sample
$ cd fmp/obj/obj_sample
$ perl ../../configure -T zynq_gcc -f

Next, we will build the "obj/obj_sample/" application.

$ make realclean
$ make TARGET=zynq_gcc ENABLE_QEMU=false ENABLE_G_SYSLOG=true PRC_NUM=2 KERNEL_FUNCOBJS= fmp.bin
$ cd ../../../

The resulting ELF binary (fmp) contains the kernel and the application linked
together. The option ENABLE_QEMU allows you to run it on Xilinx QEMU if you
set it to 'true'. The option PRC_NUM indicates the number of cores for FMP to
run on. It can be set to 1 or 2.

-----------------
Load instructions
-----------------

One option is to load the application binary (fmp ELF binary) using the
JTAG port either through XilinX software or another debugger
(e.g., DSTREAM). This is a good option if you need to debug your
application through JTAG.

-----
Load the binary from u-boot using the TFTP protocol.
-----
First you need to connect the board to your host computer:

        - USB cable from the UART port to the host computer.
        - Ethernet cable from the Ethernet port to the host computer.

Then, you need to set the boot jumpers (JP11 to JP7) in the possition
01100 for loading the program contained in the SDCard. The SDCard should
have a u-boot already installed (this is the default when you get the board.
If you formated it you will have to reinstall the files again).

On the host, set up a serial terminal of your choice (8n1 115200bps):

$ sudo picocom -b 115200 /dev/ttyACM0
picocom v1.4

port is        : /dev/ttyACM0
flowcontrol    : none
baudrate is    : 115200
parity is      : none
databits are   : 8
escape is      : C-a
noinit is      : no
noreset is     : no
nolock is      : no
send_cmd is    : ascii_xfr -s -v -l10
receive_cmd is : rz -vv

Terminal ready

Now, if you switch on the board, you should get u-boot running. Press
a key to stop it (otherwise Linux will be loaded instead).

U-Boot 2011.03-dirty (Jul 11 2012 - 16:07:00)

DRAM:  512 MiB
MMC:   SDHCI: 0
Using default environment

In:    serial
Out:   serial
Err:   serial
Net:   zynq_gem
Hit any key to stop autoboot:  0
zed-boot>

Now, we need to install a TFTP server for loading the binary through
the Ethernet cable:

sudo apt-get install tftpd-hpa

Create a virtual interface for your host Ethernet card in order to use
a private IP address (this IP address must match the one included in
the u-boot environment):

sudo ifconfig eth0:1 192.168.1.50 netmask 255.255.255.0
sudo service tftpd-hpa restart

Once, TFTP is working load the fmp.bin binary:

$ sudo cp fmp.bin /var/lib/tftpboot/

zed-boot> tftp 0x00100000 fmp.bin
Trying to set up GEM link...
Phy ID: 01410DD1
Resetting PHY...

PHY reset complete.
Waiting for PHY to complete auto-negotiation...
Link is now at 100Mbps!
Using zynq_gem device
TFTP from server 192.168.1.50; our IP address is 192.168.1.10
Filename 'fmp.bin'.
Load address: 0x0
Loading: #####
done
Bytes transferred = 63220 (f6f4 hex)
zed-boot> go 0
## Starting applicati
TOPPERS/FMP Kernel Release 1.2.1 for ZYNQ (Oct 30 2012, 12:11:29)
Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
Toyohashi Univ. of Technology, JAPAN
Copyright (C) 2004-2011 by Embedded and Real-Time Systems Laboratory
Graduate School of Information Science, Nagoya Univ., JAPAN

Processor 2 start.
Processor 1 start.
local_inirtn exinf = 2, counter = 1
local_inirtn exinf = 1, counter = 2
Server task 2 starts.
System logging task is started on port 1.
Server task 1 starts.
Sample program starts (exinf = 1).
select tskno 0x11
select cycid 1
select almid 1
select processor 1
select class     1
task1_1 is running (001).   |
task1_1 is running (002).   |
task1_1 is running (003).   |

-----
Load the binary from u-boot using the SD Card
-----
Another alternative option is to save your "fmp.bin" binary on the
SD Card (together with uboot) and load it with the following commands:

zed-boot> mmcinfo
zed-boot> fatload mmc 0 0x00100000 fmp.bin
zed-boot> go 0x00100000

-----
Load the elf file using the xmd
-----
First you need to connect the board to your host computer:

        - USB cable from the UART port to the host computer.
        - USB cable from the PROG port to the host computer.
        
Then, you need to set the boot jumpers (JP11 to JP7) in the possition
00000 for JTAG mode.

On the host, execute xmd(Xilinx Microprocessor Debugger) on 
application folder "obj/obj_sample"D

--
$xmd

Xilinx Microprocessor Debugger (XMD) Engine
Xilinx EDK 14.6 Build EDK_P.68d
Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.
--

Then, enter following command to load and execute to program.

--
connect arm hw
rst
connect arm hw -debugdevice cpunr 2
rst
targets 64
source ../../target/zynq_gcc/ps7_init.tcl
ps7_init
dow fmp.exe
con
targets 65
rwr pc 0x0010003c
con
--

Save above commands to xmd.in, then xmd automatically execute commands.

-------------------------------
Using a second UART on Zedboard
-------------------------------

On the Zedboard, you can use an extra UART by connecting a Serial port
converter to the MIO pins. The MIO pin connections are as follows:

  UART0 rx => MIO-10 => JE2
  UART0 tx => MIO-11 => JE3

We tested it with the following serial port converter:

https://www.olimex.com/Products/Components/Cables/USB-Serial-Cable/USB-Serial-Cable-F/

  [GND_usb] = Blue  => GND
  [TXD_usb] = Red   => JE2
  [RXD_usb] = Green => JE3

Open a new serial terminal:

        sudo picocom -b 115200 /dev/ttyUSB0

IMPORTANT: you need to close-open (Ctrl-a Ctrl-x) the terminal session each
time you power on the board.

References:

http://www.zedboard.org/content/enabling-uart-0
[UART<=>MIO mapping] http://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf
[PMOD pin <=> ZYNQ pin mapping] http://www.zedboard.org/sites/default/files/documentations/ZedBoard_HW_UG_v1_9.pdf
[ZYNQ Pin <=> MIO pin mapping] http://www.xilinx.com/support/packagefiles/z7packages/xc7z020clg484pkg.txt

..............................................................................
Note: another possible configuration is using MIO-14/15 but you need to
modify the MIO initialization at 'target_serial.c' in that case. When using
MIO pins 14/15 this is the configuration:

  UART0 rx => MIO-14 => JE9
  UART0 tx => MIO-15 => JE10

Olimex USB-Serial:

  [GND_usb] = Blue  => GND
  [TXD_usb] = Red   => JE9
  [RXD_usb] = Green => JE10
..............................................................................

If you want to have a different UART at each core, then you need to set
ENABLE_G_SYSLOG to false:

$ make TARGET=zynq_gcc ENABLE_QEMU=false ENABLE_G_SYSLOG=false PRC_NUM=2 KERNEL_FUNCOBJS= fmp.bin

--------------
QEMU emulation
--------------

The ZYNQ-7000 System-on-Chip is emulated by QEMU. In order to run FMP on
QEMU use the following steps:

1.- Fetch the latest QEMU source code with support for ZYNQ-7000.
At the moment (Dec 2012), the Xilinx branch of QEMU
(http://wiki.xilinx.com/zynq-qemu) has the best support for the board
but I had to apply the patches provided in the fmp/target/zynq_gcc/ folder.

2.- Uncompress and build QEMU.

./configure --prefix=/home/dsl/qemu/bin --target-list="arm-softmmu" --disable-strip --disable-xen --disable-kvm --disable-user --disable-docs --enable-debug --enable-debug-tcg --disable-werror
make
make install

3.- Check that the built QEMU supports the board:

/home/dsl/qemu/qemu-xilinx-zynq/bin/bin/qemu-system-arm -M ?
[...]
xilinx-zynq-a9 Xilinx Zynq Platform Baseboard for Cortex-A9

4.- Recompile the sample application with these parameters.

make ENABLE_QEMU=true PRC_NUM=2 ENABLE_G_SYSLOG=true KERNEL_FUNCOBJS=

5.- Run it on QEMU (modify the -smp option to reflect the number of cores
that you selected ans PRC_NUM)

qemu-system-arm -cpu cortex-a9 -M xilinx-zynq-a9 -smp 2 -serial vc:80Cx40C -serial vc:80Cx40C -serial vc:80Cx40C -serial vc:80Cx40C -no-reboot -icount auto -m 1024M -kernel fmp

Then, use Ctrl+Alt+4,5,6,7 for switching between each virtual console.

------------------------
Pass the TTSP test suite
------------------------

TTSP is a test suite developed for easying the verification of
TOPPERS kernels (http://www.toppers.jp/en/ttsp.html). Download
TTSP and uncompress it inside the FMP directory:

$ tar zxvf ttsp.tar.gz
$ ls
api_test  configure.sh  docs  library  scripts  sil_test  tools  ttb.sh  user.txt

The TTSP package should come with support for the ZYNQ-7000 target:

$ ls library/FMP/target/
zynq_gcc

(Note: if your TTSP version does not contain the zynq_gcc folder, please
contact with me.)

The main modifications to the TTSP that were carried for the
ZYNQ-Zedboard are contained in the following files:

fmp/ttsp/library/FMP/arch
fmp/ttsp/library/FMP/target/zynq_gcc/

Make sure that TARGET_NAME="zynq_gcc" and PROFILE_NAME="FMP" in
fmp/ttsp/configure.sh; and that in fmp/target/zynq_gcc/Makefile.target
the Cortex-A9 private timers are used (instead of the watchdog timers):

        SYSTIMER_TYPE = CA9_PRIVATE_TIMER
        KERNEL_COBJS := $(KERNEL_COBJS) chip_timer.o

You need to install ruby in order to run the TTSP tools.
The steps for running the API tests are:

$ ./ttb.sh
        - Select 1 (API tests)
        - Select 1 (Auto-code tests)
        - Select 1 (Generate a MANIFEST file for all TESRYs)
        - Select 4 (Build all program files)

This will generate a big fmp.bin inside the fmp/ttsp/obj/ folder
that you have to run with u-boot. When the program is run it
will display which tests are passed.

Note 1: you can do the tests in parts by
using the "Generate a MANIFEST file divided by specified number"
or a "MANIFEST file for each functions".

Note 2: you can also do tests for the SIL or the common functions
for timer, interrupts and exceptions.

A longer version of the execution is found below:

======================================================================
TTSP main menu
======================================================================
1: API Tests
2: SIL Tests
c: Check the Functions for Target Dependent
k: Kernel Library
q: Quit
----------------------------------------------------------------------
Please input menu no: 1

======================================================================
API Tests
======================================================================
1: Auto-Code Test
2: Scratch-Code Test
3: Configuration Error Test
4: Test for specified TESRY
r: Return to main menu
q: Quit
----------------------------------------------------------------------
Please input menu no: 1

======================================================================
API Tests (Auto-Code Test)
======================================================================
1: Generate a MANIFEST file for All TESRYs
2: Generate a MANIFEST file for each functions
3: Generate a MANIFEST file divided by specified number
4: Build all program files (No.5-8)
5: Make MANIFEST folders
6: Execute TTG
7: "make depend" for each MANIFEST folders
8: "make" for each MANIFEST folders
9: "make clean" for each MANIFEST folders
a: "make realclean" for each MANIFEST folders
b: Operate a specified MANIFEST folder
e: Run executable module (Target Dependent)
r: Return to main menu
q: Quit
----------------------------------------------------------------------
Please input menu no: 1

======================================================================
Generate a MANIFEST file for All TESRYs
======================================================================
/home/dsl/fmp-zedboard/ttsp/obj/api_test/../../api_test/ASP/mailbox/ref_mbx/ref_mbx_a-1.yaml
/home/dsl/fmp-zedboard/ttsp/obj/api_test/../../api_test/ASP/mailbox/ref_mbx/ref_mbx_a-2.yaml
/home/dsl/fmp-zedboard/ttsp/obj/api_test/../../api_test/ASP/mailbox/ref_mbx/ref_mbx_b-2.yaml

........

/home/dsl/fmp-zedboard/ttsp/obj/api_test/../../api_test/FMP/task_manage/mig_tsk/mig_tsk_F-f-2-1-3-1.yaml
/home/dsl/fmp-zedboard/ttsp/obj/api_test/../../api_test/FMP/task_manage/mig_tsk/mig_tsk_F-g-3-4-2-2.yaml

======================================================================
API Tests (Auto-Code Test)
======================================================================
1: Generate a MANIFEST file for All TESRYs
2: Generate a MANIFEST file for each functions
3: Generate a MANIFEST file divided by specified number
4: Build all program files (No.5-8)
5: Make MANIFEST folders
6: Execute TTG
7: "make depend" for each MANIFEST folders
8: "make" for each MANIFEST folders
9: "make clean" for each MANIFEST folders
a: "make realclean" for each MANIFEST folders
b: Operate a specified MANIFEST folder
e: Run executable module (Target Dependent)
r: Return to main menu
q: Quit
----------------------------------------------------------------------
Please input menu no: 4

======================================================================
Build all program files (No.5-8)
======================================================================
make auto_code_1 folder

----------------------------------------------------------------------
Execute TTG in auto_code_1
----------------------------------------------------------------------
[TTC]#################################:100.0% [ 4259 files passed.                     ]
[TTG]#################################:100.0% [ 4171 test cases passed.                ]
[IMC]#################################:100.0% [ 4171 test cases passed.                ]

======================================================================
Some files are excluded by variation mismatch.
======================================================================
* T6_F004: irc architecture (configure: combination)[local]   8 test cases
* T6_F005: timer architecture (configure: local)[global]      17 test cases
* T6_F001: processor number (configure: 2)[3]                 61 test cases
* T6_F004: irc architecture (configure: combination)[global]  2 test cases
* ======================================================================
* 88 test cases are excluded.(97% passed, 4171 / 4259 test cases)
*
* ----------------------------------------------------------------------
* make depend in auto_code_1
* ----------------------------------------------------------------------
* if ! [ -f Makefile.depend ]; then \
*                rm -f kernel_cfg.timestamp kernel_cfg.c kernel_cfg.h ; \
*                rm -f cfg1_out.c cfg1_out.o cfg1_out cfg1_out.syms cfg1_out.srec; \
*                rm -f makeoffset.s offset.h; \
*        fi
* rm -f Makefile.depend
* ../../../../cfg/cfg/cfg --pass 1 --kernel fmp -I. -I../../../../include -I../../../../arch -I../../../..  -I../../../../target/zynq_gcc -I../../../../arch/arm_gcc/mpcore -I../../../../arch/arm_gcc/common -I../../../../ttsp/library/FMP/test -I../../../../ttsp/library/FMP/target/zynq_gcc -I../../../../ttsp/library/FMP/arch/arm_gcc/mpcore --api-table ../../../../kernel/kernel_api.csv --cfg1-def-table ../../../../kernel/kernel_def.csv  --cfg1-def-table ../../../../arch/arm_gcc/mpcore/chip_def.csv --cfg1-def-table ../../../../arch/arm_gcc/common/core_def.csv out.cfg
*
* ..............
*
* out.c:402866:5: warning: variable 'ercd' set but not used [-Wunused-but-set-variable]
* out.c: In function 'fmp_pridataq_psnd_pdq_f_b_2_1_4_task3':
* out.c:402879:5: warning: variable 'ercd' set but not used [-Wunused-but-set-variable]
* out.c: In function 'fmp_pridataq_psnd_pdq_f_b_2_1_5_task2':
* out.c:403121:5: warning: variable 'ercd' set but not used [-Wunused-but-set-variable]
* out.c: In function 'fmp_pridataq_psnd_pdq_f_b_2_1_5_task3':
*
* ........
*
* arm-none-eabi-nm -C fmp > fmp.syms
* arm-none-eabi-objcopy -O srec -S fmp fmp.srec
* ../../../../cfg/cfg/cfg --pass 3 --kernel fmp -I. -I../../../../include -I../../../../arch -I../../../..  -I../../../../target/zynq_gcc -I../../../../arch/arm_gcc/mpcore -I../../../../arch/arm_gcc/common -I../../../../ttsp/library/FMP/test -I../../../../ttsp/library/FMP/target/zynq_gcc -I../../../../ttsp/library/FMP/arch/arm_gcc/mpcore \
*                                --rom-image fmp.srec --symbol-table fmp.syms \
*                                -T ../../../../target/zynq_gcc/target_check.tf --api-table ../../../../kernel/kernel_api.csv --cfg1-def-table ../../../../kernel/kernel_def.csv  --cfg1-def-table ../../../../arch/arm_gcc/mpcore/chip_def.csv --cfg1-def-table ../../../../arch/arm_gcc/common/core_def.csv out.cfg
* check complete
* arm-none-eabi-objcopy -O binary -S fmp fmp.bin
*
* ----------------------------------------------------------------------
* make in auto_code_1
* ----------------------------------------------------------------------
* make: `fmp.bin' is up to date.
*
* ======================================================================
* API Tests (Auto-Code Test)
* ======================================================================
* 1: Generate a MANIFEST file for All TESRYs
* 2: Generate a MANIFEST file for each functions
* 3: Generate a MANIFEST file divided by specified number
* 4: Build all program files (No.5-8)
* 5: Make MANIFEST folders
* 6: Execute TTG
* 7: "make depend" for each MANIFEST folders
* 8: "make" for each MANIFEST folders
* 9: "make clean" for each MANIFEST folders
* a: "make realclean" for each MANIFEST folders
* b: Operate a specified MANIFEST folder
* e: Run executable module (Target Dependent)
* r: Return to main menu
* q: Quit
* ----------------------------------------------------------------------
* Please input menu no: q
*
* sudo cp obj/api_test/auto_code_1/fmp.bin /var/lib/tftpboot/
*

zed-boot> tftp 0 fmp.bin
Trying to set up GEM link...
Phy ID: 01410DD1
Resetting PHY...

PHY reset complete.
Waiting for PHY to complete auto-negotiation...
Link is now at 100Mbps!
Using zynq_gem device
TFTP from server 192.168.1.50; our IP address is 192.168.1.10
Filename 'fmp.bin'.
Load address: 0x0
Loading: #################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
#################################################################
################################################
done
Bytes transferred = 14053048 (d66eb8 hex)
zed-boot> go 0
## Starting application at 0x00000000 ...
FMP_staticAPI_ATT_INI_F_b_1_INI1: Start
PE 1 : Check point : 1 passed.
FMP_staticAPI_ATT_INI_F_b_1_INI1: OK
FMP_staticAPI_ATT_INI_F_b_1_INI2: Start
PE 1 : Check point : 2 passed.
FMP_staticAPI_ATT_INI_F_b_1_INI2: OK
ASP_staticAPI_ATT_INI_b_INI1: Start
FMP_staticAPI_ATT_INI_F_b_2_INI1: Start
PE 1 : Check point : 3 passed.
PE 2 : Check point : 1 passed.
ASP_staticAPI_ATT_INI_b_INI1: OK
FMP_staticAPI_ATT_INI_F_b_2_INI1: OK
ASP_staticAPI_ATT_INI_b_INI2: Start
FMP_sys_manage_sns_ker_F_a_INI1: Start
PE 1 : Check point : 4 passed.
PE 2 : Check point : 2 passed.
ASP_staticAPI_ATT_INI_b_INI2: OK
FMP_sys_manage_sns_ker_F_a_INI1: OK
ASP_staticAPI_ATT_INI_b_INI3: Start
PE 1 : Check point : 5 passed.
ASP_staticAPI_ATT_INI_b_INI3: OK
ASP_sys_manage_sns_ker_a_INI1: Start
PE 1 : Check point : 6 passed.
ASP_sys_manage_sns_ker_a_INI1: OK
FMP_staticAPI_ATT_INI_F_b_1_INI3: Start
PE 1 : Check point : 7 passed.
FMP_staticAPI_ATT_INI_F_b_1_INI3: OK
FMP_staticAPI_ATT_INI_F_b_1_INI4: Start
PE 1 : Check point : 8 passed.
FMP_staticAPI_ATT_INI_F_b_1_INI4: OK
PE 1 : Check point : 9 passed.

............

PE 1 : Check point : 29711 passed.
PE 1 : Check point : 29712 passed.
PE 1 : Check point : 29713 passed.
FMP_time_manage_get_utm_F_a: OK
PE 1 : Check point : 29714 passed.
FMP_staticAPI_ATT_TER_F_b_1_TER4: Start
FMP_sys_manage_sns_ker_F_b_TER1: Start
PE 1 : Check point : 29715 passed.
PE 2 : Check point : 5818 passed.
FMP_staticAPI_ATT_TER_F_b_1_TER4: OK
FMP_sys_manage_sns_ker_F_b_TER1: OK
FMP_staticAPI_ATT_TER_F_b_1_TER3: Start
FMP_staticAPI_ATT_TER_F_b_2_TER1: Start
PE 1 : Check point : 29716 passed.
PE 2 : Check point : 5819 passed.
FMP_staticAPI_ATT_TER_F_b_1_TER3: OK
FMP_staticAPI_ATT_TER_F_b_2_TER1: OK
ASP_sys_manage_sns_ker_b_TER1: Start
PE 1 : Check point : 29717 passed.
ASP_sys_manage_sns_ker_b_TER1: OK
ASP_staticAPI_ATT_TER_b_TER3: Start
PE 1 : Check point : 29718 passed.
ASP_staticAPI_ATT_TER_b_TER3: OK
ASP_staticAPI_ATT_TER_b_TER2: Start
PE 1 : Check point : 29719 passed.
ASP_staticAPI_ATT_TER_b_TER2: OK
ASP_staticAPI_ATT_TER_b_TER1: Start
PE 1 : Check point : 29720 passed.
ASP_staticAPI_ATT_TER_b_TER1: OK
FMP_staticAPI_ATT_TER_F_b_1_TER2: Start
PE 1 : Check point : 29721 passed.
FMP_staticAPI_ATT_TER_F_b_1_TER2: OK
FMP_staticAPI_ATT_TER_F_b_1_TER1: Start
PE 1 : Check point : 29722 passed.
FMP_staticAPI_ATT_TER_F_b_1_TER1: OK
PE 1 : All check points passed.


------------------
Change Log
------------------
- 2013/11/24 : pl310.c
 Add pl310_flush_all()/pl310_disable(). 

- 2013/11/15 : target_ipi.h
 Change IPI number in T-FMP(3 and 4 used by NT-Linux).

- 2013/11/15 : pl310.h/pl310.c
 Add PL310(L2 Cache) driver.

- 2013/11/13 
 Change T-FMP base address.
 
- 2013/11/13 : target_serial.c
 comment out definition of XUARTPS_POLLING_MODE in case of use SafeG.
 
- 2013/11/12 : target_config.c
   Fix MMU setting.
   
- 2013/11/12 : Makefile.config
   Fix using WDT in NT-FMP and TIMER in T-FMP
   
- 2013/11/12 : README-EN.txt
   Add "Load the elf file using the xmd" 

