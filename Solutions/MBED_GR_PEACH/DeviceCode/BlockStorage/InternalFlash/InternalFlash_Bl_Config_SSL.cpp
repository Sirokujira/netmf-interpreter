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
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>

#define FLASH_MANUFACTURER_CODE                0xffff
#define FLASH_DEVICE_CODE                      0xffff
#define FLASH_BLOCK_ERASE_MAX_TIME_USEC        96000
#define FLASH_SECTOR_WRITE_MAX_TIME_USEC       48000

#define INTERNALFLASH__CHIP_SELECT             0    // UINT8	CPU_MEMORY_CONFIG::ChipSelect;
#define INTERNALFLASH__WAIT_STATES             0    // UINT32   CPU_MEMORY_CONFIG::WaitStates;
#define INTERNALFLASH__RELEASE_COUNTS          0    // UINT32   CPU_MEMORY_CONFIG::ReleaseCounts;
#define INTERNALFLASH__BIT_WIDTH               8    // UINT32   CPU_MEMORY_CONFIG::BitWidth;
#define INTERNALFLASH__BASE_ADDRESS            FLASH_MEMORY_Base
#define INTERNALFLASH__SIZE_IN_BYTES           FLASH_MEMORY_Size
#define INTERNALFLASH__WP_GPIO_PIN             GPIO_PIN_NONE
#define INTERNALFLASH__WP_ACTIVE               FALSE

// BlockDeviceInformation
#define INTERNALFLASH__IS_REMOVABLE            FALSE
#define INTERNALFLASH__SUPPORTS_XIP            TRUE
#define INTERNALFLASH__WRITE_PROTECTED         FALSE

#define INTERNALFLASH__NUM_REGIONS             3

#define BYTES_PER_SECTOR                       16384
// REGION1
#define REGION1_XIP_ADDRESS                    (INTERNALFLASH__BASE_ADDRESS)
#define REGION1_BYTES_PER_BLK                  0x8000
#define REGION1_NUM_OF_BLOCKS                  16
// REGION2
#define REGION2_XIP_ADDRESS                    (INTERNALFLASH__BASE_ADDRESS + \
                                                (REGION1_BYTES_PER_BLK * REGION1_NUM_OF_BLOCKS))
#define REGION2_BYTES_PER_BLK                  0x4000
#define REGION2_NUM_OF_BLOCKS                  30
// REGION3
#define REGION3_XIP_ADDRESS                    (INTERNALFLASH__BASE_ADDRESS + \
                                                (REGION1_BYTES_PER_BLK * REGION1_NUM_OF_BLOCKS) + \
                                                (REGION2_BYTES_PER_BLK * REGION2_NUM_OF_BLOCKS))
#define REGION3_BYTES_PER_BLK                  0x1000
#define REGION3_NUM_OF_BLOCKS                  6    // although max=8, but it's overflow

#if defined(MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP)
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP 
#endif

#if defined(MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE)
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE
#endif

#ifdef __GNUC__
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP  BlockRange::BLOCKTYPE_BOOTSTRAP
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE       BlockRange::BLOCKTYPE_CODE
#else
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP  BlockRange::BLOCKTYPE_CODE
#define MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE       BlockRange::BLOCKTYPE_DEPLOYMENT
#endif

#ifdef R5F563NB
const BlockRange g_INTERNALFLASH_BlockRange1[] =        // 512K:32Kx16
{
    { BlockRange::BLOCKTYPE_CODE            ,  0, 15 }, // FFF00000 - FFF7FFFF
};

const BlockRange g_INTERNALFLASH_BlockRange2[] =        // 480K:16Kx30
{
    { BlockRange::BLOCKTYPE_CODE            ,  0, 29 },	// FFF80000 - FFFF7FFF
};

const BlockRange g_INTERNALFLASH_BlockRange3[] =        // 32K:4Kx8
{
    { BlockRange::BLOCKTYPE_DEPLOYMENT      ,  0,  1 }, // FFFF8000 - FFFF9FFF
    { BlockRange::BLOCKTYPE_DEPLOYMENT      ,  2,  3 }, // FFFFA000 - FFFFBFFF
    { BlockRange::BLOCKTYPE_CONFIG          ,  4,  4 }  // FFFFC000 - FFFFCFFF
};
#else
#error "CPU type not defined. Please define R5F563Nx?"
#endif

#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_BOOTSTRAP 
#undef MEMORY_BLOCKTYPE_GCC_SPECIAL_CODE    

//--//

const BlockRegionInfo  g_INTERNALFLASH_BlkRegion[INTERNALFLASH__NUM_REGIONS] =
{
    {
        REGION1_XIP_ADDRESS,   		// ByteAddress 	Address;		// Start address
        REGION1_NUM_OF_BLOCKS,   	// UINT32       NumBlocks;      // total number of blocks in this region
        REGION1_BYTES_PER_BLK,    	// UINT32       BytesPerBlock;  // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
        ARRAYSIZE_CONST_EXPR(g_INTERNALFLASH_BlockRange1),
        (const BlockRange*)&g_INTERNALFLASH_BlockRange1
    },
    {
        REGION2_XIP_ADDRESS,        // ByteAddress  Address;        // Start address
        REGION2_NUM_OF_BLOCKS,      // UINT32       NumBlocks;      // total number of blocks in this region
        REGION2_BYTES_PER_BLK,      // UINT32       BytesPerBlock;  // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
        ARRAYSIZE_CONST_EXPR(g_INTERNALFLASH_BlockRange2),
        (const BlockRange*)&g_INTERNALFLASH_BlockRange2
    },
    {
        REGION3_XIP_ADDRESS,        // ByteAddress  Address;        // Start address
        REGION3_NUM_OF_BLOCKS,      // UINT32       NumBlocks;      // total number of blocks in this region
        REGION3_BYTES_PER_BLK,      // UINT32       BytesPerBlock;  // Total number of bytes per block (MUST be SectorsPerBlock * DataBytesPerSector)
        ARRAYSIZE_CONST_EXPR(g_INTERNALFLASH_BlockRange3),
        (const BlockRange*)&g_INTERNALFLASH_BlockRange3
    }
};

//--//

BlockDeviceInfo g_INTERNALFLASH_DeviceInfo =
{
    {
        INTERNALFLASH__IS_REMOVABLE,  	// BOOL Removable;
        INTERNALFLASH__SUPPORTS_XIP,    // BOOL SupportsXIP;
        INTERNALFLASH__WRITE_PROTECTED, // BOOL WriteProtected
    },
    FLASH_SECTOR_WRITE_MAX_TIME_USEC,   // UINT32 Duration_Max_WordWrite_uSec;
    FLASH_BLOCK_ERASE_MAX_TIME_USEC,    // UINT32 Duration_Max_SectorErase_uSec;
    BYTES_PER_SECTOR,                   // BytesPerSector; // Bytes Per Sector
    FLASH_MEMORY_Size,                  // UINT32 Size;
    INTERNALFLASH__NUM_REGIONS,         // UINT32 NumRegions;
    (const BlockRegionInfo*)&g_INTERNALFLASH_BlkRegion,	// const BlockRegionInfo* pRegions;
};

struct MEMORY_MAPPED_NOR_BLOCK_CONFIG g_INTERNALFLASH_Config =
{
    { // BLOCK_CONFIG
        {
            INTERNALFLASH__WP_GPIO_PIN,	// GPIO_PIN	Pin;
            INTERNALFLASH__WP_ACTIVE,   // BOOL     ActiveState;
        },
        &g_INTERNALFLASH_DeviceInfo,    // BlockDeviceinfo
    },
    { // CPU_MEMORY_CONFIG
        INTERNALFLASH__CHIP_SELECT,     // UINT8 	CPU_MEMORY_CONFIG::ChipSelect;
        TRUE,                           // UINT8    CPU_MEMORY_CONFIG::ReadOnly;
        INTERNALFLASH__WAIT_STATES,     // UINT32   CPU_MEMORY_CONFIG::WaitStates;
        INTERNALFLASH__RELEASE_COUNTS,  // UINT32   CPU_MEMORY_CONFIG::ReleaseCounts;
        INTERNALFLASH__BIT_WIDTH,       // UINT32   CPU_MEMORY_CONFIG::BitWidth;
        INTERNALFLASH__BASE_ADDRESS,    // UINT32   CPU_MEMORY_CONFIG::BaseAddress;
        INTERNALFLASH__SIZE_IN_BYTES,   // UINT32   CPU_MEMORY_CONFIG::SizeInBytes;
        0,                              // UINT8    CPU_MEMORY_CONFIG::XREADYEnable
        0,                              // UINT8    CPU_MEMORY_CONFIG::ByteSignalsForRead
        0,                              // UINT8    CPU_MEMORY_CONFIG::ExternalBufferEnable
    },
    0x0,                               	// UINT32  	ChipProtection;
    FLASH_MANUFACTURER_CODE,            // FLASH_WORD	ManufacturerCode;
    FLASH_DEVICE_CODE,                  // FLASH_WORD   DeviceCode;
};

//--//

struct BlockStorageDevice g_INTERNALFLASH;

