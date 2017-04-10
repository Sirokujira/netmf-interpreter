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

#ifdef TEST_I2C_EEPROM

void I2C_Internal_SetChannel(INT32 channel);
void memory_dump(unsigned long addr, int len);

#define I2C_STATIC_BUF
#define I2C_EEPROM_CH   5
#define I2C_EEPROM_SIZE 0x800
#define I2C_EEPROM_SIZE 0x200
#define I2C_buf_SIZE    0x100
#define I2C_EEPROM_ADDR     0x50
#define I2C_EEPROM_SPEED    1000
#define I2C_WRITE   0
#define I2C_READ    1
#define I2C_TIMEOUT 1000000

#ifdef I2C_STATIC_BUF
UINT8 qbuf[I2C_buf_SIZE+1];
#endif

BOOL EEPROMWriteSub(UINT32 EEPROM_addr, UINT8 *src, UINT32 len, BOOL fErase)
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

    lcd_printf("EEPROMWrite\r\n");
    I2C_config.ClockRate = I2C_EEPROM_SPEED;
    while (len > 0) {
        UINT32 timeout = I2C_TIMEOUT;
        I2C_config.Address = (UINT16)(I2C_EEPROM_ADDR + (EEPROM_addr >> 8));
        if (len < I2C_buf_SIZE)
            size = len;
        else
            size = I2C_buf_SIZE;
        buf[0] = (UINT8)EEPROM_addr;
        lcd_printf("addr=%04X\r\n", EEPROM_addr);
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
        lcd_printf("I2C state = %d\r\n", status);
        if (status != I2C_HAL_XACTION::c_Status_Completed)
            return FALSE;
#ifdef MEM_DUMP
        memory_dump((unsigned long)&qbuf[1], size);
#endif
        len -= size;
        EEPROM_addr += size;
        src += size;
    }
    return TRUE;
}

BOOL EEPROMReadSub(UINT32 EEPROM_addr, UINT8 *dst, UINT32 len, BOOL fEraseCheck)
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

    lcd_printf("EEPROMRead\r\n");
    I2C_config.ClockRate = I2C_EEPROM_SPEED;
    while (len > 0) {
        UINT32 timeout = I2C_TIMEOUT;
        I2C_config.Address = (UINT16)(I2C_EEPROM_ADDR + (EEPROM_addr >> 8));
        if (len < I2C_buf_SIZE)
            size = len;
        else
            size = I2C_buf_SIZE;
        buf = (UINT8)EEPROM_addr;
        lcd_printf("addr=%04X\r\n", EEPROM_addr);
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
        lcd_printf("I2C state = %d\r\n", status);
        if (status != I2C_HAL_XACTION::c_Status_Completed)
            return FALSE;
        if (fEraseCheck) {
            for (UINT32 i = 0; i < size; i++)
                if (qbuf[i] != 0) {
                    return FALSE;
                }
#ifdef MEM_DUMP
            memory_dump((unsigned long)qbuf, size);
        } else {
            memory_dump((unsigned long)dst, size);
#endif
        }
        len -= size;
        EEPROM_addr += size;
        dst += size;
    }
    return TRUE;
}

BOOL EEPROMWrite(UINT32 EEPROM_addr, UINT8 *src, UINT32 len)
{
    return EEPROMWriteSub(EEPROM_addr, src, len, FALSE);
}

BOOL EEPROMErase(UINT32 EEPROM_addr, UINT32 len)
{
    return EEPROMWriteSub(EEPROM_addr, 0, len, TRUE);
}

BOOL EEPROMRead(UINT32 EEPROM_addr, UINT8 *dst, UINT32 len)
{
    return EEPROMReadSub(EEPROM_addr, dst, len, FALSE);
}

BOOL EEPROMIsErased(UINT32 EEPROM_addr, UINT32 len)
{
    return EEPROMReadSub(EEPROM_addr, 0, len, TRUE);
}

UINT8 w_data[I2C_EEPROM_SIZE];
UINT8 r_data[I2C_EEPROM_SIZE];

void TestI2C_EEPROM()
{
    UINT32 i = 0;
    for (i = 0; i < I2C_EEPROM_SIZE; i++) {
        w_data[i] = i;
        r_data[i] = 0;
    }
    I2C_Internal_SetChannel(I2C_EEPROM_CH);
    EEPROMErase((UINT32)0, (UINT32)I2C_EEPROM_SIZE);
    if (EEPROMIsErased((UINT32)0, (UINT32)I2C_EEPROM_SIZE)) {
        lcd_printf("TestI2C Erase OK\r\n");
    } else {
        lcd_printf("TestI2C Erase NG\r\n");
    }
    EEPROMWrite((UINT32)0, (UINT8 *)&w_data, (UINT32)I2C_EEPROM_SIZE);
    EEPROMRead((UINT32)0, (UINT8 *)&r_data, (UINT32)I2C_EEPROM_SIZE);
    if (memcmp(w_data, r_data, I2C_EEPROM_SIZE) == 0) {
        lcd_printf("TestI2C R/W OK\r\n");
    } else {
        lcd_printf("TestI2C R/W NG\r\n");
    }
#ifdef MEM_DUMP
    memory_dump((unsigned long)w_data, I2C_EEPROM_SIZE);
    memory_dump((unsigned long)r_data, I2C_EEPROM_SIZE);
#endif
}
#endif
