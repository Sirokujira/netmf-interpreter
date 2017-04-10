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

#include <tinyhal.h>
#include "..\MBED.h"
#include "MBED_FLASH.h"

////////////////////////////////////////////////////////////////////////////
// For Debugging
////////////////////////////////////////////////////////////////////////////
//#define DEBUG_FLASH
//#define DEBUG_FLASH_SKIP
//#define DEBUG_FLASH_WriteX
//#define DEBUG_FLASH_EraseBlock
//#define DEBUG_FLASH_Read
//#define DEBUG_FLASH_Memset

#define FLASH_BUF_SIZE 0x100
#define FLASH_BUF_ADDR_MASK 0xffffff00
#define FLASH_BUF_OFF_MASK  0x000000ff

BOOL MBED_BS_Driver::ChipInitialize(void *context)
{   
#if defined(DEBUG_FLASH)
    debug_printf("ChipInitialize()\r\n");
#endif
    return TRUE;
}

BOOL MBED_BS_Driver::ChipUnInitialize(void *context)
{
#if defined(DEBUG_FLASH)
    debug_printf("ChipUnInitialize()\r\n");
#endif
    return TRUE;
}

BOOL MBED_BS_Driver::ChipReadOnly(void *context, BOOL On, UINT32 ProtectionKey)
{
#if defined(DEBUG_FLASH)
    debug_printf("ChipReadOnly()\r\n");
#endif
    return TRUE;
}

const BlockDeviceInfo* MBED_BS_Driver::GetDeviceInfo(void *context)
{
#if defined(DEBUG_FLASH)
    debug_printf("GetDeviceInfo(context=%x))\r\n", context);
#endif
    BLOCK_CONFIG *config = (BLOCK_CONFIG *)context;
    return config->BlockDeviceInformation;
}

BOOL MBED_BS_Driver::Read(void *context, ByteAddress Address, UINT32 NumBytes, BYTE *pSectorBuff)
{
#if defined(DEBUG_FLASH) || defined(DEBUG_FLASH_Read)
    debug_printf("Read(addr=%x, num=%x, psec=%x)\r\n", Address, NumBytes, pSectorBuff);
#endif
    CHIP_WORD *startAddress = (CHIP_WORD *)Address;
    CHIP_WORD *endAddress = (CHIP_WORD *)(Address + NumBytes);
    while (startAddress < endAddress) {
        *pSectorBuff++ = *startAddress++;
    }
    return TRUE;
}

BOOL MBED_BS_Driver::Write(void *context, ByteAddress Address, UINT32 NumBytes, BYTE *pSectorBuff, BOOL ReadModifyWrite)
{
    return WriteX(context, Address, NumBytes, pSectorBuff, ReadModifyWrite, TRUE);
}

static void wait(volatile int count)
{
    while (count-- > 0);
}

BOOL MBED_BS_Driver::WriteX(void *context, ByteAddress Address, UINT32 NumBytes, BYTE *pSectorBuff, BOOL ReadModifyWrite, BOOL fIncrementDataPtr)
{
#if defined(DEBUG_FLASH) || defined(DEBUG_FLASH_WriteX)
    debug_printf("WriteX(addr=%x, num=%x, psec=%x)\r\n", Address, NumBytes, pSectorBuff);
#endif
    UINT32 error_code = 0;
    bool flag;
    if (error_code == 0)
        return true;
    return false;
}

BOOL MBED_BS_Driver::Memset(void *context, ByteAddress Address, UINT8 Data, UINT32 NumBytes)
{
#if defined(DEBUG_FLASH) || defined(DEBUG_FLASH_Memset)
    debug_printf("Memset(addr=%x, num=%x, data=%x)\r\n", Address, NumBytes, Data);
#endif
    CHIP_WORD chipData;
    memset(&chipData, Data, sizeof(CHIP_WORD));
    return WriteX(context, Address, NumBytes, (BYTE *)&chipData, TRUE, FALSE);
}

BOOL MBED_BS_Driver::GetSectorMetadata(void *context, ByteAddress SectorStart, SectorMetadata *pSectorMetadata)
{
#if defined(DEBUG_FLASH)
    debug_printf("GetSectorMetadata(start=%x, psecmetadata=%x)\r\n", SectorStart, pSectorMetadata);
#endif
    return FALSE;
}

BOOL MBED_BS_Driver::SetSectorMetadata(void *context, ByteAddress SectorStart, SectorMetadata *pSectorMetadata)
{
#if defined(DEBUG_FLASH)
    debug_printf("SetSectorMetadata(start=%x, psecmetadata=%x)\r\n", SectorStart, pSectorMetadata);
#endif
    return FALSE;
}

BOOL MBED_BS_Driver::IsBlockErased(void *context, ByteAddress Address, UINT32 BlockLength)
{
#if defined(DEBUG_FLASH)
    debug_printf("IsBlockErased(addr=%x, len=%x)\r\n", Address, BlockLength);
#endif
    CHIP_WORD *startAddress = (CHIP_WORD *)Address;
    CHIP_WORD *endAddress = (CHIP_WORD *)(Address + BlockLength);
    while (startAddress < endAddress)
        if (*startAddress++ != (CHIP_WORD)0xFFFFFFFF)
            return FALSE;
    return TRUE;
}

// erase one page
BOOL MBED_BS_Driver::EraseBlock(void *context, ByteAddress Address)
{
#if defined(DEBUG_FLASH) || defined(DEBUG_FLASH_EraseBlock)
    debug_printf("EraseBlock(addr=%x)\r\n", Address);
#endif
    UINT32 error_code = 0;
    bool flag;
    if (error_code == 0)
        return true;
    return false;
}

void MBED_BS_Driver::SetPowerState(void *context, UINT32 State)
{
#if defined(DEBUG_FLASH)
    debug_printf("SetPowerState(state=%x)\r\n", State);
#endif
    return;
}

UINT32 MBED_BS_Driver::MaxSectorWrite_uSec(void *context)
{
#if defined(DEBUG_FLASH)
    debug_printf("MaxSectorWrite_uSec()\r\n");
#endif
    NATIVE_PROFILE_PAL_FLASH();
    MEMORY_MAPPED_NOR_BLOCK_CONFIG *config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG *)context;

    return config->BlockConfig.BlockDeviceInformation->MaxSectorWrite_uSec;
}

UINT32 MBED_BS_Driver::MaxBlockErase_uSec(void *context)
{
#if defined(DEBUG_FLASH)
    debug_printf("MaxBlockErase_uSec()\r\n");
#endif
    NATIVE_PROFILE_PAL_FLASH();
    MEMORY_MAPPED_NOR_BLOCK_CONFIG *config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG *)context;

    return config->BlockConfig.BlockDeviceInformation->MaxBlockErase_uSec;
}

////////////////////////////////////////////////////////////////////////////
// IBlockStorage structure
////////////////////////////////////////////////////////////////////////////

struct IBlockStorageDevice g_MBED_INTERNALFLASH_DeviceTable =
{
    &MBED_BS_Driver::ChipInitialize,
    &MBED_BS_Driver::ChipUnInitialize,
    &MBED_BS_Driver::GetDeviceInfo,
    &MBED_BS_Driver::Read,
    &MBED_BS_Driver::Write,
    &MBED_BS_Driver::Memset,
    &MBED_BS_Driver::GetSectorMetadata,
    &MBED_BS_Driver::SetSectorMetadata,
    &MBED_BS_Driver::IsBlockErased,
    &MBED_BS_Driver::EraseBlock,
    &MBED_BS_Driver::SetPowerState,
    &MBED_BS_Driver::MaxSectorWrite_uSec,
    &MBED_BS_Driver::MaxBlockErase_uSec,
};
