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
//  Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

#ifdef TEST_I2C

#if defined(FRAM)
void memory_dump(unsigned long addr, int len);

#define I2C_STATIC_BUF
#define I2C_FRAM_CH    1
//#define I2C_FRAM_SIZE 0x800
#define I2C_FRAM_SIZE 0x200
#define I2C_buf_SIZE 0x100
#define I2C_FRAM_ADDR    0x50
#define I2C_FRAM_SPEED    1000
#define I2C_WRITE    0
#define I2C_READ    1
#define I2C_TIMEOUT    1000000

#ifdef I2C_STATIC_BUF
UINT8 qbuf[I2C_buf_SIZE+1];
#endif

BOOL FRAMWriteSub(UINT32 addr, UINT8 *src, UINT32 len, BOOL fErase)
{
    struct I2C_USER_CONFIGURATION I2C_config;
    struct I2C_HAL_XACTION_UNIT xActionUnits[1];
    struct I2C_HAL_XACTION_UNIT *pxActionUnits[1];
    I2C_HAL_XACTION xAction;
    UINT8 buf[I2C_buf_SIZE+1];
#ifndef I2C_STATIC_BUF
    UINT8 qbuf[I2C_buf_SIZE+1];
#endif
    UINT8 status;
    UINT32 size;

    debug_printf("FRAMWrite\r\n");
    I2C_config.ClockRate = I2C_FRAM_SPEED;
    while (len > 0) {
        UINT32 timeout = I2C_TIMEOUT;
        I2C_config.Address = (UINT16)(I2C_FRAM_ADDR + (addr >> 8));
        if (len < I2C_buf_SIZE)
            size = len;
        else
            size = I2C_buf_SIZE;
        buf[0] = (UINT8)addr;
        debug_printf("addr=%04X\r\n", addr);
        if (fErase)
            memset((void *)(buf+1), 0, size);
        else
            memcpy((void *)(buf+1), (void *)src, size);
        pxActionUnits[0] = &xActionUnits[0];
        I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[0], (I2C_WORD *)&buf, (I2C_WORD *)&qbuf, (size_t)(size+1), I2C_WRITE);
        I2C_InitializeTransaction(&xAction, I2C_config, (I2C_HAL_XACTION_UNIT **)&pxActionUnits[0], 1);
        I2C_Enqueue(&xAction);
        while (timeout-- > 0) {
            status = I2C_XAction_GetState(&xAction);
            if (status == I2C_HAL_XACTION::c_Status_Completed)
                break;
        }
        debug_printf("I2C state = %d\r\n", status);
        if (status != I2C_HAL_XACTION::c_Status_Completed)
            return FALSE;
        memory_dump((unsigned long)&qbuf[1], size);
        len -= size;
        addr += size;
        src += size;
    }
    return TRUE;
}

BOOL FRAMReadSub(UINT32 addr, UINT8 *dst, UINT32 len, BOOL fEraseCheck)
{
    struct I2C_USER_CONFIGURATION I2C_config;
    struct I2C_HAL_XACTION_UNIT xActionUnits[2];
    struct I2C_HAL_XACTION_UNIT *pxActionUnits[2];
    I2C_HAL_XACTION xAction;
    UINT8 buf;
#ifndef I2C_STATIC_BUF
    UINT8 qbuf[I2C_buf_SIZE+1];
#endif
    UINT8 status;
    UINT32 size;

    debug_printf("FRAMRead\r\n");
    I2C_config.ClockRate = I2C_FRAM_SPEED;
    while (len > 0) {
        UINT32 timeout = I2C_TIMEOUT;
        I2C_config.Address = (UINT16)(I2C_FRAM_ADDR + (addr >> 8));
        if (len < I2C_buf_SIZE)
            size = len;
        else
            size = I2C_buf_SIZE;
        buf = (UINT8)addr;
        debug_printf("addr=%04X\r\n", addr);
        pxActionUnits[0] = &xActionUnits[0];
        pxActionUnits[1] = &xActionUnits[1];
        I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[0], (I2C_WORD *)&buf, (I2C_WORD *)&qbuf, 1, I2C_WRITE);
        if (fEraseCheck)
            // Erase Check
            I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[1], (I2C_WORD *)0, (I2C_WORD *)&qbuf, size, I2C_READ);
        else
            // Read
            I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[1], (I2C_WORD *)0, (I2C_WORD *)dst, size, I2C_READ);
        I2C_InitializeTransaction(&xAction, I2C_config, (I2C_HAL_XACTION_UNIT **)&pxActionUnits[0], 2);
        I2C_Enqueue(&xAction);
        while (timeout-- > 0) {
            status = I2C_XAction_GetState(&xAction);
            if (status == I2C_HAL_XACTION::c_Status_Completed)
                break;
        }
        debug_printf("I2C state = %d\r\n", status);
        if (status != I2C_HAL_XACTION::c_Status_Completed)
            return FALSE;
        if (fEraseCheck) {
            for (UINT32 i = 0; i < size; i++)
                if (qbuf[i] != 0) {
                    return FALSE;
                }
            memory_dump((unsigned long)qbuf, size);
        } else
            memory_dump((unsigned long)dst, size);
        len -= size;
        addr += size;
        dst += size;
    }
    return TRUE;
}

BOOL FRAMWrite(UINT32 addr, UINT8 *src, UINT32 len)
{
    return FRAMWriteSub(addr, src, len, FALSE);
}

BOOL FRAMErase(UINT32 addr, UINT32 len)
{
    return FRAMWriteSub(addr, 0, len, TRUE);
}

BOOL FRAMRead(UINT32 addr, UINT8 *dst, UINT32 len)
{
    return FRAMReadSub(addr, dst, len, FALSE);
}

BOOL FRAMIsErased(UINT32 addr, UINT32 len)
{
    return FRAMReadSub(addr, 0, len, TRUE);
}

UINT8 w_data[I2C_FRAM_SIZE];
UINT8 r_data[I2C_FRAM_SIZE];

void TestI2C()
{
    UINT32 i = 0;
    for (i = 0; i < I2C_FRAM_SIZE; i++) {
        w_data[i] = i;
        r_data[i] = 0;
    }
#if 1
    FRAMErase((UINT32)0, (UINT32)I2C_FRAM_SIZE);
    if (FRAMIsErased((UINT32)0, (UINT32)I2C_FRAM_SIZE)) {
        debug_printf("TestI2C Erase OK\r\n");
    } else {
        debug_printf("TestI2C Erase NG\r\n");
    }
#endif
#if 1
    FRAMWrite((UINT32)0, (UINT8 *)&w_data, (UINT32)I2C_FRAM_SIZE);
    FRAMRead((UINT32)0, (UINT8 *)&r_data, (UINT32)I2C_FRAM_SIZE);
    if (memcmp(w_data, r_data, I2C_FRAM_SIZE) == 0) {
        debug_printf("TestI2C R/W OK\r\n");
    } else {
        debug_printf("TestI2C R/W NG\r\n");
    }
    memory_dump((unsigned long)w_data, I2C_FRAM_SIZE);
    memory_dump((unsigned long)r_data, I2C_FRAM_SIZE);
#endif
#if 0
    FRAMWrite((UINT32)0, (UINT8 *)&w_data, (UINT32)I2C_FRAM_SIZE);
    FRAMRead((UINT32)0, (UINT8 *)&r_data, (UINT32)I2C_FRAM_SIZE);
    if (memcmp(w_data, r_data, I2C_FRAM_SIZE) == 0) {
        debug_printf("TestI2C R/W OK\r\n");
    } else {
        debug_printf("TestI2C R/W NG\r\n");
    }
    memory_dump((unsigned long)w_data, I2C_FRAM_SIZE);
    memory_dump((unsigned long)r_data, I2C_FRAM_SIZE);
#endif
}
#endif

#if defined(TMP102)
#define I2C_READ    1

void TMP102_Read(void)
{
    struct I2C_USER_CONFIGURATION I2C_config;
    struct I2C_HAL_XACTION_UNIT xActionUnits[1];
    struct I2C_HAL_XACTION_UNIT *pxActionUnits[1];
    I2C_HAL_XACTION xAction;
    UINT8 src[3];
    UINT8 dst[3];
    UINT8 status;
    UINT32 size = 2;
    volatile UINT32 timeout = 1000000;
    UINT16 temp;
    float ftemp;

    I2C_config.ClockRate = 400;
    I2C_config.Address = (UINT16)(0x48);
    pxActionUnits[0] = &xActionUnits[0];
    I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[0], (I2C_WORD *)&src, (I2C_WORD *)&dst, (size_t)size, I2C_READ);
    I2C_InitializeTransaction(&xAction, I2C_config, (I2C_HAL_XACTION_UNIT **)&pxActionUnits[0], 1);
    I2C_Enqueue(&xAction);
    while (timeout-- > 0) {
        status = I2C_XAction_GetState(&xAction);
        if (status == I2C_HAL_XACTION::c_Status_Completed)
            break;
    }
    temp = (((UINT16)dst[0]) << 4) | (((UINT16)dst[1]) >> 4);
    ftemp = temp*0.0625;
    dbg_printf("I2C temp=%d.%d   \r", dst[0], dst[1]);
}

void TestI2C()
{
    while (true) {
        TMP102_Read();
        HAL_Time_Sleep_MicroSeconds_InterruptEnabled(2000000);
    }
}
#endif

#if defined(EEPROM)
void memory_dump(unsigned long addr, int len);

#define I2C_buf_SIZE 0x100
#define I2C_EEPROM_SIZE     0x20    // max 32 bytes for 24c64
#define I2C_EEPROM_SPEED    400
#define I2C_EEPROM_ADDR     0x50
#define I2C_WRITE    0
#define I2C_READ    1
#define I2C_TIMEOUT    1000000

#ifdef I2C_STATIC_BUF
UINT8 qbuf[I2C_buf_SIZE+1];
#endif

BOOL EEPROM_WriteByte(UINT32 addr, UINT8 *src, UINT32 len)
{
    struct I2C_USER_CONFIGURATION I2C_config;
    struct I2C_HAL_XACTION_UNIT xActionUnits[1];
    struct I2C_HAL_XACTION_UNIT *pxActionUnits[1];
    I2C_HAL_XACTION xAction;
    UINT8 buf[I2C_buf_SIZE+2];
#ifndef I2C_STATIC_BUF
    UINT8 qbuf[I2C_buf_SIZE+2];
#endif
    UINT8 status;
    UINT32 size;

    dbg_printf("ROM_W\r\n");
    I2C_config.ClockRate = I2C_EEPROM_SPEED;
    while (len > 0) {
        UINT32 timeout = I2C_TIMEOUT;
        I2C_config.Address = (UINT16)(I2C_EEPROM_ADDR);
        if (len < I2C_buf_SIZE)
            size = len;
        else
            size = I2C_buf_SIZE;
        buf[0] = (UINT8)(addr >> 8);
        buf[1] = (UINT8)(addr & 0xff);
        dbg_printf("addr=%04X\r\n", addr);
        memcpy((void *)(buf+2), (void *)src, size);
        pxActionUnits[0] = &xActionUnits[0];
        I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[0], (I2C_WORD *)&buf, (I2C_WORD *)&qbuf, (size_t)(size+2), I2C_WRITE);
        I2C_InitializeTransaction(&xAction, I2C_config, (I2C_HAL_XACTION_UNIT **)&pxActionUnits[0], 1);
        I2C_Enqueue(&xAction);
        while (timeout-- > 0) {
            status = I2C_XAction_GetState(&xAction);
            if (status == I2C_HAL_XACTION::c_Status_Completed)
                break;
        }
        dbg_printf("I2C state = %d\r\n", status);
        if (status != I2C_HAL_XACTION::c_Status_Completed)
            return FALSE;
        memory_dump((unsigned long)&qbuf[1], size);
        len -= size;
        addr += size;
        src += size;
    }
    return TRUE;
}

BOOL EEPROM_ReadByte(UINT32 addr, UINT8 *dst, UINT32 len)
{
    struct I2C_USER_CONFIGURATION I2C_config;
    struct I2C_HAL_XACTION_UNIT xActionUnits[2];
    struct I2C_HAL_XACTION_UNIT *pxActionUnits[2];
    I2C_HAL_XACTION xAction;
    UINT8 buf[2];
#ifndef I2C_STATIC_BUF
    UINT8 qbuf[I2C_buf_SIZE+1];
#endif
    UINT8 status;
    UINT32 size;

    dbg_printf("ROM_R\r\n");
    I2C_config.ClockRate = I2C_EEPROM_SPEED;
    while (len > 0) {
        UINT32 timeout = I2C_TIMEOUT;
        I2C_config.Address = (UINT16)(I2C_EEPROM_ADDR + (addr >> 8));
        if (len < I2C_buf_SIZE)
            size = len;
        else
            size = I2C_buf_SIZE;
        buf[0] = (UINT8)(addr >> 0);
        buf[1] = (UINT8)(addr & 0xff);
        dbg_printf("addr=%04X\r\n", addr);
        pxActionUnits[0] = &xActionUnits[0];
        pxActionUnits[1] = &xActionUnits[1];
        I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[0], (I2C_WORD *)&buf, (I2C_WORD *)&qbuf, 2, I2C_WRITE);
        I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[1], (I2C_WORD *)0, (I2C_WORD *)dst, size, I2C_READ);
        I2C_InitializeTransaction(&xAction, I2C_config, (I2C_HAL_XACTION_UNIT **)&pxActionUnits[0], 2);
        I2C_Enqueue(&xAction);
        while (timeout-- > 0) {
            status = I2C_XAction_GetState(&xAction);
            if (status == I2C_HAL_XACTION::c_Status_Completed)
                break;
        }
        dbg_printf("I2C state = %d\r\n", status);
        if (status != I2C_HAL_XACTION::c_Status_Completed)
            return FALSE;
        memory_dump((unsigned long)dst, size);
        len -= size;
        addr += size;
        dst += size;
    }
    return TRUE;
}

UINT8 w_data[I2C_EEPROM_SIZE];
UINT8 r_data[I2C_EEPROM_SIZE];

void TestI2C()
{
    UINT32 i = 0;
    for (i = 0; i < I2C_EEPROM_SIZE; i++) {
        w_data[i] = i;
        r_data[i] = 0;
    }
    EEPROM_WriteByte((UINT32)0, (UINT8 *)&w_data, (UINT32)I2C_EEPROM_SIZE);
    EEPROM_ReadByte((UINT32)0, (UINT8 *)&r_data, (UINT32)I2C_EEPROM_SIZE);
    if (memcmp(w_data, r_data, I2C_EEPROM_SIZE) == 0) {
        dbg_printf("TestI2C R/W OK\r\n");
    } else {
        dbg_printf("TestI2C R/W NG\r\n");
    }
    memory_dump((unsigned long)w_data, I2C_EEPROM_SIZE);
    memory_dump((unsigned long)r_data, I2C_EEPROM_SIZE);

    while (true) {
    }
}
#endif

#if defined(I2CDETECT)

// 0x7c(0x3e): AQM0802 LCD
// 0x90(0x48): ADT7410 temperature
// 0x92(0x49): PCF8591
// 0xa0(0x50): EEPROM
// 0xb8(0x5c): MLPS331 atmosphier

#define I2C_WRITE   0
#define I2C_READ    1
#define I2C_TIMEOUT    10000

#define I2C_ENABLE_OUTPUT

UINT8 I2CReadOneByte(UINT32 addr, UINT8 *dst)
{
    struct I2C_USER_CONFIGURATION I2C_config;
    struct I2C_HAL_XACTION_UNIT xActionUnits[1];
    struct I2C_HAL_XACTION_UNIT *pxActionUnits[1];
    I2C_HAL_XACTION xAction;
    UINT8 src[3];
    UINT8 status;
    UINT32 size = 1;
    volatile UINT32 timeout = I2C_TIMEOUT;
    UINT8 count = 0;
    float ftemp;

    I2C_config.ClockRate = 400;
    I2C_config.Address = (UINT16)addr;
    pxActionUnits[0] = &xActionUnits[0];
    I2C_InitializeTransactionUnit((I2C_HAL_XACTION_UNIT *)&xActionUnits[0], (I2C_WORD *)&src, (I2C_WORD *)&dst, (size_t)size, I2C_READ);
    I2C_InitializeTransaction(&xAction, I2C_config, (I2C_HAL_XACTION_UNIT **)&pxActionUnits[0], 1);
    I2C_Enqueue(&xAction);
    while (timeout-- > 0) {
        status = I2C_XAction_GetState(&xAction);
        if (status == I2C_HAL_XACTION::c_Status_Completed) {
            count = I2C_XAction_TransactedBytes(&xAction);
            break;
        }
        if (status == I2C_HAL_XACTION::c_Status_Aborted) {
            count = I2C_XAction_TransactedBytes(&xAction);
            break;
        }
    }
    return count;
}

#define MAX_LINE_CHAR   256
#define MAX_DEVICE  256

UINT8 line[MAX_LINE_CHAR];
UINT8 founddevices[MAX_DEVICE];

UINT32 ScanI2CBus(UINT32 first, UINT32 last, UINT8 *devices)
{
    UINT32 i;
    UINT32 j;
    int res;
    UINT8 dst;
    UINT32 count = 0;

#if defined(I2C_ENABLE_OUTPUT)
    dbg_printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
#endif
    for (i = 0; i < 128; i += 16)
    {
#if defined(I2C_ENABLE_OUTPUT)
        dbg_printf("%02x: ", i);
#endif
        for (j = 0; j < 16; j++)
        {
            if (i + j < first || i + j > last)
            {
#if defined(I2C_ENABLE_OUTPUT)
                dbg_printf("   ");
#endif
                continue;
            }
            if ((i + j >= 0x30 && i + j <= 0x37) || (i + j >= 0x50 && i + j <= 0x5F))
                res = I2CReadOneByte(i+j, &dst);
            else
                res = I2CReadOneByte(i+j, &dst);
            if (res == 0) {
#if defined(I2C_ENABLE_OUTPUT)
                dbg_printf("-- ");
#endif
            } else {
#if defined(I2C_ENABLE_OUTPUT)
                dbg_printf("%02x ", (UINT8)(i+j));
#endif
                *devices++ = (UINT8)(i+j);
                count++;
            }
        }
#if defined(I2C_ENABLE_OUTPUT)
        dbg_printf("\r\n");
#endif
    }
    return count;
}

void TestI2C()
{
    UINT32 start = 0x21;
    UINT32 end = 0x7f;
    UINT32 count = 0;
    UINT32 i = 0;
    dbg_printf("I2C Detect addr(%02x-%02x)\r\n", start, end);
    count = ScanI2CBus(start, end, (UINT8 *)&founddevices);
    dbg_printf("%d devices found.\r\n", count);
    while (count-- > 0) {
        dbg_printf("0x%02x ", founddevices[i++]);
    }
    dbg_printf("\r\n");
    while (1) {
    }
}
#endif

#endif
