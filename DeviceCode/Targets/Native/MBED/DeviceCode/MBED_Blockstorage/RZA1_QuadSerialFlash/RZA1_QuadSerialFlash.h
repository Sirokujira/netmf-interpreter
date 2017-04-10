/*
 *    Copyright (C) 2010 Renesas Electronics America Inc. All rights reserved.
 */
 
#include <tinyhal.h>

//--//
#ifndef _DRIVERS_FLASH_SF_BL_H_
#define _DRIVERS_FLASH_SF_BL_H_ 1

typedef BYTE SERIAL_WORD;
#define SF_PAGE_SIZE        256
//#define SF_SECTOR_SIZE      0x1000

//--//

struct SF_BS_Driver
{
    typedef UINT8 CHIP_WORD;
    public:
    __attribute__((section("SectionForFlashOperations"))) static BOOL InitializeDevice(void *context);
    __attribute__((section("SectionForFlashOperations"))) static BOOL UnInitializeDevice(void *context);
    __attribute__((section("SectionForFlashOperations"))) static const BlockDeviceInfo *GetDeviceInfo(void *context);
    __attribute__((section("SectionForFlashOperations"))) static BOOL Read(void *context, ByteAddress Address, UINT32 NumBytes, BYTE *pSectorBuff);
    __attribute__((section("SectionForFlashOperations"))) static BOOL Write(void *context, ByteAddress Address, UINT32 NumBytes, BYTE *pSectorBuff, BOOL ReadModifyWrite);
    __attribute__((section("SectionForFlashOperations"))) static BOOL Memset(void *context, ByteAddress Address, UINT8 Data, UINT32 NumBytes);
    __attribute__((section("SectionForFlashOperations"))) static BOOL GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata);
    __attribute__((section("SectionForFlashOperations"))) static BOOL SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata);
    __attribute__((section("SectionForFlashOperations"))) static BOOL IsBlockErased(void *context, ByteAddress BlockStartAddress, UINT32 BlockLength);
    __attribute__((section("SectionForFlashOperations"))) static BOOL EraseBlock(void *context, ByteAddress Sector);
    __attribute__((section("SectionForFlashOperations"))) static void SetPowerState(void *context, UINT32 State);
    __attribute__((section("SectionForFlashOperations"))) static UINT32 MaxSectorWrite_uSec(void *context);
    __attribute__((section("SectionForFlashOperations"))) static UINT32 MaxBlockErase_uSec(void *context);
    __attribute__((section("SectionForFlashOperations"))) static BOOL WriteX(void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite, BOOL fIncrementDataPtr);
};

struct SERIALFLASH_BLOCK_CONFIG
{
    GPIO_FLAG WriteProtectionPin;
    BlockDeviceInfo *BlockDeviceInformation;
};

struct MEMORY_MAPPED_SERIAL_BLOCK_CONFIG
{
    SERIALFLASH_BLOCK_CONFIG            BlockConfig;
    CPU_MEMORY_CONFIG       Memory;
    UINT32                  ChipProtection;
    UINT32                  ManufacturerCode;
    UINT32                  DeviceCode;
};

#endif // _DRIVERS_FLASH_SF_BL_H_
