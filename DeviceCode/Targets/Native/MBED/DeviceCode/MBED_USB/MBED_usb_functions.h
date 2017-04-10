////////////////////////////////////////////////////////////////////////////
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//  Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#ifndef MBED_USB_FUNCTIONS_H_
#define MBED_USB_FUNCTIONS_H_

#include "r_typedefs.h"
#include "iodefine.h"
#include "usb_iobitmask.h"
#include "rza_io_regrw.h"
//#include "USBHAL.h"
//#include "devdrv_usb_function_api.h"
//#include "usb0_function.h"
//#include "USBDevice_Types.h"

#define USB_EP_TX_DIS       0
#define USB_EP_TX_STALL     1
#define USB_EP_TX_NAK       2
#define USB_EP_TX_VALID     3
#define USB_EP_RX_DIS       0
#define USB_EP_RX_STALL     1
#define USB_EP_RX_NAK       2
#define USB_EP_RX_VALID     3

#define USB_MAX_EP      6
#define MAX_EP0_SIZE    64
#define USB_MAX_DATA_PACKET_SIZE    64

#define USB_MAX_PIPE    10  // max number of pipes
#define USB_MAX_FIFO    3   // max number of fifo
#define FIFO_CFIFO      0   // CFIFO
#define FIFO_D0FIFO     1   // DOFIFO
#define FIFO_D1FIFO     2   // D1FIFO

#define MBW_BYTE        0   // byte access
#define MBW_WORD        1   // word access

#define PIPE_BULK_ST    1   // pipe bulk start no
#define PIPE_INT_ST     6   // pipe interrupt startr no

#define PID_NAK     0
#define PID_BUF     1
#define PID_STALL_1 2
#define PID_STALL_2 3

#define DIR_IN      1       // Write
#define DIR_OUT     0       // Read

#define MASK_BEMPE  (0x0400)
#define MASK_NRDYE  (0x0200)
#define MASK_BRDYE  (0x0100)

//*********************************************************************************
// Type Definitions
//*********************************************************************************
typedef union {
    unsigned short WORD;
    struct {
        unsigned short PID:2;
        unsigned short CCPL:1;
        unsigned short :1;
        unsigned short PINGE:1;
        unsigned short PBUSY:1;
        unsigned short SQMON:1;
        unsigned short SQSET:1;
        unsigned short SQCLR:1;
        unsigned short :2;
        unsigned short SUREQCLR:1;
        unsigned short CSSTS:1;
        unsigned short CSCLR:1;
        unsigned short SUREQ:1;
        unsigned short BSTS:1;
    } BIT;
} DCPCTR;

typedef union {
    unsigned short WORD;
    struct {
        unsigned short PID:2;
        unsigned short :3;
        unsigned short PBUSY:1;
        unsigned short SQMON:1;
        unsigned short SQSET:1;
        unsigned short SQCLR:1;
        unsigned short ACLRM:1;
        unsigned short ATREPM:1;
        unsigned short :1;
        unsigned short CSSTS:1;
        unsigned short CSCLR:1;
        unsigned short INBUFM:1;
        unsigned short BSTS:1;
    } BIT;
} PIPECTR;

typedef union {
    unsigned short WORD;
    struct {
        unsigned short EPNUM:4;
        unsigned short DIR:1;
        unsigned short :2;
        unsigned short SHTNAK:1;
        unsigned short CNTMD:1;
        unsigned short DBLB:1;
        unsigned short BFRE:1;
        unsigned short :3;
        unsigned short TYPE:2;
    } BIT;
} PIPECFG;

typedef union {
    unsigned short WORD;
    struct {
        unsigned short DTLN:12;
        unsigned short :1;
        unsigned short FRDY:1;
        unsigned short BCR:1;
        unsigned short BVAL:1;
    } BIT;
} FIFOCTR;

typedef union {
    unsigned short WORD;
    struct {
        unsigned short CURPIPE:4;
        unsigned short :1;
        unsigned short ISEL:1;
        unsigned short :2;
        unsigned short BIGNED:1;
        unsigned short :1;
        unsigned short MBW:2;
        unsigned short :2;
        unsigned short REW:1;
        unsigned short RCNT:1;
    } BIT;
} FIFOSEL;

#define USB_FUNCTION_ALT_NO         (255)
#define USB_FUNCTION_ALT_SET        (0xff)

#define USB_FUNCTION_BITUPLLE       (0x0002u)
#define USB_FUNCTION_BITUCKSEL      (0x0004u)
#define USB_FUNCTION_BITBWAIT       (0x003fu)

#define USB_FUNCTION_BUSWAIT_02     (0x0000u)
#define USB_FUNCTION_BUSWAIT_03     (0x0001u)
#define USB_FUNCTION_BUSWAIT_04     (0x0002u)
#define USB_FUNCTION_BUSWAIT_05     (0x0003u)
#define USB_FUNCTION_BUSWAIT_06     (0x0004u)
#define USB_FUNCTION_BUSWAIT_07     (0x0005u)
#define USB_FUNCTION_BUSWAIT_08     (0x0006u)
#define USB_FUNCTION_BUSWAIT_09     (0x0007u)
#define USB_FUNCTION_BUSWAIT_10     (0x0008u)
#define USB_FUNCTION_BUSWAIT_11     (0x0009u)
#define USB_FUNCTION_BUSWAIT_12     (0x000au)
#define USB_FUNCTION_BUSWAIT_13     (0x000bu)
#define USB_FUNCTION_BUSWAIT_14     (0x000cu)
#define USB_FUNCTION_BUSWAIT_15     (0x000du)
#define USB_FUNCTION_BUSWAIT_16     (0x000eu)
#define USB_FUNCTION_BUSWAIT_17     (0x000fu)

#define USB_FUNCTION_BITRESUME      (0x0020u)
#define USB_FUNCTION_BITUACT        (0x0010u)
#define USB_FUNCTION_HSPROC         (0x0004u)
#define USB_FUNCTION_HSMODE         (0x0003u)
#define USB_FUNCTION_FSMODE         (0x0002u)
#define USB_FUNCTION_LSMODE         (0x0001u)
#define USB_FUNCTION_UNDECID        (0x0000u)

#define USB_FUNCTION_BITRCNT        (0x8000u)
#define USB_FUNCTION_BITDREQE       (0x1000u)
#define USB_FUNCTION_BITMBW         (0x0c00u)
#define USB_FUNCTION_BITMBW_8       (0x0000u)
#define USB_FUNCTION_BITMBW_16      (0x0400u)
#define USB_FUNCTION_BITMBW_32      (0x0800u)
#define USB_FUNCTION_BITBYTE_LITTLE (0x0000u)
#define USB_FUNCTION_BITBYTE_BIG    (0x0100u)
#define USB_FUNCTION_BITISEL        (0x0020u)
#define USB_FUNCTION_BITCURPIPE     (0x000fu)

#define USB_FUNCTION_CFIFO_READ     (0x0000u)
#define USB_FUNCTION_CFIFO_WRITE    (0x0020u)

#define USB_FUNCTION_BITBVAL        (0x8000u)
#define USB_FUNCTION_BITBCLR        (0x4000u)
#define USB_FUNCTION_BITFRDY        (0x2000u)
#define USB_FUNCTION_BITDTLN        (0x0fffu)

#define USB_FUNCTION_BITVBSE        (0x8000u)
#define USB_FUNCTION_BITRSME        (0x4000u)
#define USB_FUNCTION_BITSOFE        (0x2000u)
#define USB_FUNCTION_BITDVSE        (0x1000u)
#define USB_FUNCTION_BITCTRE        (0x0800u)
#define USB_FUNCTION_BITVBINT       (0x8000u)
#define USB_FUNCTION_BITRESM        (0x4000u)
#define USB_FUNCTION_BITSOFR        (0x2000u)
#define USB_FUNCTION_BITDVST        (0x1000u)
#define USB_FUNCTION_BITCTRT        (0x0800u)

#define USB_FUNCTION_BITBEMPE       (0x0400u)
#define USB_FUNCTION_BITNRDYE       (0x0200u)
#define USB_FUNCTION_BITBRDYE       (0x0100u)
#define USB_FUNCTION_BITBEMP        (0x0400u)
#define USB_FUNCTION_BITNRDY        (0x0200u)
#define USB_FUNCTION_BITBRDY        (0x0100u)

#define USB_FUNCTION_BITDVSQ        (0x0070u)
#define USB_FUNCTION_BITDVSQS       (0x0030u)
#define USB_FUNCTION_DS_SPD_CNFG    (0x0070u)
#define USB_FUNCTION_DS_SPD_ADDR    (0x0060u)
#define USB_FUNCTION_DS_SPD_DFLT    (0x0050u)
#define USB_FUNCTION_DS_SPD_POWR    (0x0040u)
#define USB_FUNCTION_DS_CNFG        (0x0030u)
#define USB_FUNCTION_DS_ADDS        (0x0020u)
#define USB_FUNCTION_DS_DFLT        (0x0010u)
#define USB_FUNCTION_DS_POWR        (0x0000u)
#define USB_FUNCTION_BITVALID       (0x0008u)
#define USB_FUNCTION_BITCTSQ        (0x0007u)
#define USB_FUNCTION_CS_SQER        (0x0006u)
#define USB_FUNCTION_CS_WRND        (0x0005u)
#define USB_FUNCTION_CS_WRSS        (0x0004u)
#define USB_FUNCTION_CS_WRDS        (0x0003u)
#define USB_FUNCTION_CS_RDSS        (0x0002u)
#define USB_FUNCTION_CS_RDDS        (0x0001u)
#define USB_FUNCTION_CS_IDST        (0x0000u)

#define USB_FUNCTION_PIPExBUF       (64u)

#define USB_FUNCTION_D0FIFO         (0)
#define USB_FUNCTION_D1FIFO         (1)
#define USB_FUNCTION_DMA_READY      (0)
#define USB_FUNCTION_DMA_BUSY       (1)
#define USB_FUNCTION_DMA_BUSYEND    (2)

#define USB_FUNCTION_FIFO_USE       (0x7000)


#define USBFCLOCK_X1_48MHZ                          (0x0000u)       /* USB_X1_48MHz */
#define USBFCLOCK_EXTAL_12MHZ                       (0x0004u)       /* EXTAL_12MHz  */

#define DEVDRV_USBF_ON                              (1)
#define DEVDRV_USBF_OFF                             (0)
#define DEVDRV_USBF_YES                             (1)
#define DEVDRV_USBF_NO                              (0)

#define DEVDRV_USBF_STALL                           (-2)

#define DEVDRV_USBF_WRITEEND                        (0)
#define DEVDRV_USBF_WRITESHRT                       (1)
#define DEVDRV_USBF_WRITING                         (2)
#define DEVDRV_USBF_WRITEDMA                        (3)

#define DEVDRV_USBF_FIFOERROR                       (0xffff)

#define DEVDRV_USBF_PIPE_IDLE                       (0x00)
#define DEVDRV_USBF_PIPE_WAIT                       (0x01)
#define DEVDRV_USBF_PIPE_DONE                       (0x02)
#define DEVDRV_USBF_PIPE_NORES                      (0x03)
#define DEVDRV_USBF_PIPE_STALL                      (0x04)

#define DEVDRV_USBF_PID_NAK                         (0x0000u)
#define DEVDRV_USBF_PID_BUF                         (0x0001u)
#define DEVDRV_USBF_PID_STALL                       (0x0002u)
#define DEVDRV_USBF_PID_STALL2                      (0x0003u)

#define USB_FUNCTION_NON_SPEED                      (0)
#define USB_FUNCTION_LOW_SPEED                      (1)
#define USB_FUNCTION_FULL_SPEED                     (2)
#define USB_FUNCTION_HIGH_SPEED                     (3)

#define USB_FUNCTION_READEND                        (0)
#define USB_FUNCTION_READSHRT                       (1)
#define USB_FUNCTION_READING                        (2)
#define USB_FUNCTION_READOVER                       (3)
#define USB_FUNCTION_READZERO                       (4)

#define USB_FUNCTION_MAX_PIPE_NO                    (15u)
#define USB_FUNCTION_PIPE0                          (0)
#define USB_FUNCTION_PIPE1                          (1)
#define USB_FUNCTION_PIPE2                          (2)
#define USB_FUNCTION_PIPE3                          (3)
#define USB_FUNCTION_PIPE4                          (4)
#define USB_FUNCTION_PIPE5                          (5)
#define USB_FUNCTION_PIPE6                          (6)
#define USB_FUNCTION_PIPE7                          (7)
#define USB_FUNCTION_PIPE8                          (8)
#define USB_FUNCTION_PIPE9                          (9)
#define USB_FUNCTION_PIPEA                          (10)
#define USB_FUNCTION_PIPEB                          (11)
#define USB_FUNCTION_PIPEC                          (12)
#define USB_FUNCTION_PIPED                          (13)
#define USB_FUNCTION_PIPEE                          (14)
#define USB_FUNCTION_PIPEF                          (15)

#define USB_FUNCTION_ISO                            (0xc000u)
#define USB_FUNCTION_INTERRUPT                      (0x8000u)
#define USB_FUNCTION_BULK                           (0x4000u)

#define USB_FUNCTION_NONE                           (0x0000u)
#define USB_FUNCTON_BFREFIELD                       (0x0400u)
#define USB_FUNCTION_BFREON                         (0x0400u)
#define USB_FUNCTION_BFREOFF                        (0x0000u)
#define USB_FUNCTION_DBLBFIELD                      (0x0200u)
#define USB_FUNCTION_DBLBON                         (0x0200u)
#define USB_FUNCTION_DBLBOFF                        (0x0000u)
#define USB_FUNCTION_CNTMDFIELD                     (0x0100u)
#define USB_FUNCTION_CNTMDON                        (0x0100u)
#define USB_FUNCTION_CNTMDOFF                       (0x0000u)
#define USB_FUNCTION_SHTNAKON                       (0x0080u)
#define USB_FUNCTION_SHTNAKOFF                      (0x0000u)
#define USB_FUNCTION_DIRFIELD                       (0x0010u)
#define USB_FUNCTION_DIR_P_OUT                      (0x0000u)
#define USB_FUNCTION_DIR_P_IN                       (0x0010u)
#define USB_FUNCTION_EPNUMFIELD                     (0x000fu)
#define USB_FUNCTION_MAX_EP_NO                      (15u)
#define USB_FUNCTION_EP0                            (0u)
#define USB_FUNCTION_EP1                            (1u)
#define USB_FUNCTION_EP2                            (2u)
#define USB_FUNCTION_EP3                            (3u)
#define USB_FUNCTION_EP4                            (4u)
#define USB_FUNCTION_EP5                            (5u)
#define USB_FUNCTION_EP6                            (6u)
#define USB_FUNCTION_EP7                            (7u)
#define USB_FUNCTION_EP8                            (8u)
#define USB_FUNCTION_EP9                            (9u)
#define USB_FUNCTION_EP10                           (10u)
#define USB_FUNCTION_EP11                           (11u)
#define USB_FUNCTION_EP12                           (12u)
#define USB_FUNCTION_EP13                           (13u)
#define USB_FUNCTION_EP14                           (14u)
#define USB_FUNCTION_EP15                           (15u)

#define USB_FUNCTION_EPTABLE_LENGTH                 (5u)

#define USB_FUNCTION_CUSE                           (0)
#define USB_FUNCTION_D0USE                          (1)
#define USB_FUNCTION_D0DMA                          (2)
#define USB_FUNCTION_D1USE                          (3)
#define USB_FUNCTION_D1DMA                          (4)

#define USB_FUNCTION_CFIFO_USE                      (0x0000)
#define USB_FUNCTION_D0FIFO_USE                     (0x1000)
#define USB_FUNCTION_D1FIFO_USE                     (0x2000)
#define USB_FUNCTION_D0FIFO_DMA                     (0x5000)
#define USB_FUNCTION_D1FIFO_DMA                     (0x6000)

#define USB_FUNCTION_BUF2FIFO                       (0)
#define USB_FUNCTION_FIFO2BUF                       (1)

#define USB_FUNCTION_DVST_POWERED                   (0x0001)
#define USB_FUNCTION_DVST_DEFAULT                   (0x0002)
#define USB_FUNCTION_DVST_ADDRESS                   (0x0003)
#define USB_FUNCTION_DVST_CONFIGURED                (0x0004)
#define USB_FUNCTION_DVST_SUSPEND                   (0x0005)
#define USB_FUNCTION_DVST_CONFIGURED_SUSPEND        (0x0006)

#define USB_FUNCTION_FUNCTION_TEST_SELECT           (0xff00u)
#define USB_FUNCTION_FUNCTION_TEST_J                (0x0100u)
#define USB_FUNCTION_FUNCTION_TEST_K                (0x0200u)
#define USB_FUNCTION_FUNCTION_TEST_SE0_NAK          (0x0300u)
#define USB_FUNCTION_FUNCTION_TEST_PACKET           (0x0400u)
#define USB_FUNCTION_FUNCTION_TEST_FORCE_ENABLE     (0x0500u)
#define USB_FUNCTION_FUNCTION_TEST_STSelectors      (0x0600u)
#define USB_FUNCTION_FUNCTION_TEST_Reserved         (0x4000u)
#define USB_FUNCTION_FUNCTION_TEST_VSTModes         (0xc000u)

#define USB_FUNCTION_DT_TYPE                        (0xff00u)
#define USB_FUNCTION_DT_INDEX                       (0xff)
#define USB_FUNCTION_DT_DEVICE                      (0x01)
#define USB_FUNCTION_DT_CONFIGURATION               (0x02)
#define USB_FUNCTION_DT_STRING                      (0x03)
#define USB_FUNCTION_DT_INTERFACE                   (0x04)
#define USB_FUNCTION_DT_ENDPOINT                    (0x05)
#define USB_FUNCTION_DT_DEVICE_QUALIFIER            (0x06)
#define USB_FUNCTION_DT_OTHER_SPEED_CONFIGURATION   (0x07)
#define USB_FUNCTION_DT_INTERFACE_POWER             (0x08)

#define USB_FUNCTION_CF_RESERVED                    (0x80)
#define USB_FUNCTION_CF_SELF                        (0x40)
#define USB_FUNCTION_CF_RWUP                        (0x20)
#define USB_FUNCTION_CF_NORWUP                      (0x00)
#define USB_FUNCTION_EP_ERROR                       (0xff)

#define USB_FUNCTION_EP_OUT                         (0x00)
#define USB_FUNCTION_EP_IN                          (0x80)
#define USB_FUNCTION_EP_CNTRL                       (0x00)
#define USB_FUNCTION_EP_ISO                         (0x01)
#define USB_FUNCTION_EP_BULK                        (0x02)
#define USB_FUNCTION_EP_INT                         (0x03)

#define USB_FUNCTION_STANDARD_REQUEST               (0x0000u)
#define USB_FUNCTION_CLASS_REQUEST                  (0x0020u)
#define USB_FUNCTION_VENDOR_REQUEST                 (0x0040u)
#define USB_FUNCTION_DEVICE_REQUEST                 (0x0000u)
#define USB_FUNCTION_INTERFACE_REQUEST              (0x0001u)
#define USB_FUNCTION_ENDPOINT_REQUEST               (0x0002u)

#define USB_FUNCTION_GETSTATUS_BUSPOWERD            (0x0000u)
#define USB_FUNCTION_GETSTATUS_SELFPOWERD           (0x0001u)
#define USB_FUNCTION_GETSTATUS_REMOTEWAKEUP         (0x0002u)
#define USB_FUNCTION_GETSTATUS_NOTHALT              (0x0000u)
#define USB_FUNCTION_GETSTATUS_HALT                 (0x0001u)

#define USB_FUNCTION_FEATURE_ENDPOINT_HALT          (0x0000u)
#define USB_FUNCTION_FEATURE_REMOTE_WAKEUP          (0x0001u)
#define USB_FUNCTION_FEATURE_TEST_MODE              (0x0002u)

#define USB_FUNCTION_bRequest                       (0xff00u)       /* b15-8:bRequest */
#define USB_FUNCTION_bmRequestType                  (0x00ffu)       /* b7-0: bmRequestType */
#define USB_FUNCTION_bmRequestTypeDir               (0x0080u)       /* b7  : Data transfer direction */
#define USB_FUNCTION_bmRequestTypeType              (0x0060u)       /* b6-5: Type */
#define USB_FUNCTION_bmRequestTypeRecip             (0x001fu)       /* b4-0: Recipient */
#endif /* MBED_USB_FUNCTIONS_H_ */
