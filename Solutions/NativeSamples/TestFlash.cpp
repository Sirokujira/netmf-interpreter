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

#ifdef TEST_FLASH
void wait(volatile UINT64 count);
void memory_dump(unsigned long addr, int len);

struct BLOCK_CONFIG *pBlockConfig;
struct IBlockStorageDevice *pBlockDeviceTable;

#if defined(PLATFORM_ARM_CQ_FRK_FM3)

extern struct BLOCK_CONFIG  g_FM3_BS_Config;
extern struct IBlockStorageDevice g_FM3_Flash_DeviceTable;

#define FLASH_TEST_DATA_SIZE    0x200
#define FLASH_TEST_ADDR         0x00060000
#define FLASH_SECTOR_SIZE       0x20000
#define FLASH_READWRITE_FLAG    0

#elif defined(PLATFORM_RZA1_MBED_GR_PEACH)

extern struct BLOCK_CONFIG        g_SerialFlash_BL_Config;
extern struct IBlockStorageDevice g_SerialFlash_BL_DeviceTable;
#define FLASH_TEST_DATA_SIZE    0x200
#define FLASH_TEST_ADDR         0x18060000
#define FLASH_SECTOR_SIZE       0x10000
#define FLASH_READWRITE_FLAG    0

#endif


BYTE FlashTestData[FLASH_TEST_DATA_SIZE];

void dispFlag(int flag)
{
    if (flag)
        lcd_printf("OK\r\n");
    else
        lcd_printf("NG\r\n");
}

void TestFlashInitData()
{
    int i;
    for (i = 0; i < FLASH_TEST_DATA_SIZE; i++)
        FlashTestData[i] = (BYTE)(i & 0xff);
}

void TestFlashErase(UINT32 addr)
{
    int flag = true;
    flag = pBlockDeviceTable->EraseBlock(pBlockConfig, addr);
    lcd_printf("TestFlashErase addr=%x ", addr);
    dispFlag(flag);
    wait(1000000L);
    memory_dump(addr, 256);
    wait(1000000L);
}

void TestFlashWrite(UINT32 addr, UINT32 size)
{
    int flag;
    flag = pBlockDeviceTable->Write(pBlockConfig, addr, size, FlashTestData, FLASH_READWRITE_FLAG);
    lcd_printf("TestFlashWrite addr=%x size=%x ", addr, size);
    dispFlag(flag);
    wait(1000000L);
    memory_dump(addr & 0xffffff00, (size + 255) & 0xffffff00);
    wait(1000000L);
}

void TestFlash(void)
{
#if defined(PLATFORM_ARM_CQ_FRK_FM3)
#elif defined(PLATFORM_RZA1_MBED_GR_PEACH)
    pBlockConfig = &g_SerialFlash_BL_Config;
    pBlockDeviceTable = &g_SerialFlash_BL_DeviceTable;
#endif
//  g_FM3_FLASH_DeviceTable.InitializeDevice(pBLOCK_CONFIG_NOR);
    TestFlashInitData();
    TestFlashErase(FLASH_TEST_ADDR);
    TestFlashWrite(FLASH_TEST_ADDR+0x10, 0x20);
//  TestFlashErase(FLASH_TEST_ADDR);
    TestFlashWrite(FLASH_TEST_ADDR+0x30, 0x20);
//  TestFlashErase(FLASH_TEST_ADDR);
    TestFlashWrite(FLASH_TEST_ADDR+0x50, 0x120);
}
#endif
