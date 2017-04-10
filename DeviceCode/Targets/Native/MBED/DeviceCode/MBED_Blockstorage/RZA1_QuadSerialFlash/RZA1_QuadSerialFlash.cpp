#include <tinyhal.h>
#include "RZA1_QuadSerialFlash.h"
#include "r_spibsc_flash_api.h"
#include "r_spibsc_ioset_api.h"
#include "sflash.h"
#include "spibsc.h"
#include "Flash.h"
#include "r_typedefs.h"
#include "iodefine.h"
#include "rza_io_regrw.h"

#if 0
#ifdef __cplusplus
extern "C" {
#endif
INT32 Flash_Write_Init(void);
INT32 Flash_Write_Init_Dual(void);
INT32 Flash_Write_Entry(void);
INT32 Flash_Veify_Entry(void);
INT32 Flash_Write_Area(UINT32 *address, UINT32 *data, INT32 size);
int32_t R_SFLASH_Exmode_Setting(uint32_t ch_no, uint32_t dual, st_spibsc_cfg_t *spibsccfg);
int32_t R_SFLASH_Exmode(uint32_t ch_no);
int32_t R_SFLASH_Spimode(uint32_t ch_no);
INT32 R_SFLASH_EraseSector(UINT32 addr, UINT32 ch_no, UINT32 dual, UINT8 data_width, UINT8 addr_mode);
INT32 R_SFLASH_ByteProgram(UINT32 addr, UINT8 *buf, INT32 size, UINT32 ch_no, UINT32 dual, UINT8 data_width, UINT8 addr_mode);
INT32 R_SFLASH_ByteRead(UINT32 addr, UINT8 * buf, INT32 size, UINT32 ch_no, UINT32 dual, UINT8 data_width, UINT8 addr_mode);
#ifdef __cplusplus
}
#endif
#endif

extern volatile struct st_spibsc*  SPIBSC[];

//#define QSF_VERIFY
//#define DEBUG_FLASH_NG_ONLY
//#define DEBUG_FLASH_Init
//#define DEBUG_FLASH_Write
//#define DEBUG_FLASH_EraseBlock_NG
//#define DEBUG_FLASH_EraseBlock_OK
//#define qsf_printf  lcd_printf
//--//

extern struct MEMORY_MAPPED_SERIAL_BLOCK_CONFIG g_SerialFlash_BL_Config;

extern FILESYSTEM_DRIVER_INTERFACE g_FAT32_FILE_SYSTEM_DriverInterface;
extern STREAM_DRIVER_INTERFACE g_FAT32_STREAM_DriverInterface;
extern struct BlockStorageDevice g_SerialFlash_Device;

extern FileSystemVolume g_SerialFlash_FS;

static int QSF_Initialized = 0;
static BYTE wbuf[SF_PAGE_SIZE];
static BYTE rbuf[SF_PAGE_SIZE];

#define FLASH_BUF_SIZE SF_PAGE_SIZE
#define FLASH_BUF_ADDR_MASK 0xffffff00
#define FLASH_BUF_OFF_MASK  0x000000ff

st_spibsc_cfg_t g_spibsc_cfg;

INT32 QSF_SetSPIMode(void)
{
    INT32 iret = 0;
    iret = R_SFLASH_Spimode(0);
    return iret;
}

INT32 QSF_SetExAddrReadMode(void)
{
    INT32 iret = 0;
    iret = R_SFLASH_Exmode(0);
    return iret;
}

INT32 QSF_Init(void)
{
    INT32 iret;
    if (QSF_Initialized)
    	return iret;
    QSF_Initialized = 1;
    GLOBAL_LOCK(irq);
    spibsc_stop(0);
    iret = Flash_Write_Init();
    QSF_SetExAddrReadMode();
    return iret;
}

INT32 QSF_ByteRead(UINT32 addr, UINT8* buf, UINT32 size, UINT8 data_width, UINT8 addr_mode)
{
    INT32 iret;
    GLOBAL_LOCK(irq);
    QSF_SetSPIMode();
    iret = R_SFLASH_ByteRead(addr, buf, size, 0, 0, data_width, addr_mode);
    QSF_SetExAddrReadMode();
    return iret;
}

 INT32 QSF_ByteWrite(UINT32 addr, UINT8* buf, UINT32 size, UINT8 data_width, UINT8 addr_mode)
{
    INT32 iret;
    GLOBAL_LOCK(irq);
    QSF_SetSPIMode();
    iret = R_SFLASH_ByteProgram(addr, buf, size, 0, 0, data_width, addr_mode);
    QSF_SetExAddrReadMode();
    return iret;
}

INT32 QSF_EraseSector(UINT32 addr, UINT8 data_width, UINT8 addr_mode)
{
    INT32 iret;
    GLOBAL_LOCK(irq);
    QSF_SetSPIMode();
    iret = R_SFLASH_EraseSector(addr, 0, 0, data_width, addr_mode);
    //RZA_IO_RegWrite_32(&SPIBSC[ 1 ]->DRCR, 1, SPIBSC_DRCR_RBE_SHIFT, SPIBSC_DRCR_RBE);
    QSF_SetExAddrReadMode();
    return iret;
}

BOOL SF_BS_Driver::InitializeDevice(void *context)
{
    BOOL ret = TRUE;
    INT32 iret;
    BLOCK_CONFIG *config = (BLOCK_CONFIG*)context;
    unsigned char id[10];
    id[0] = id[1] = id[2] = 0;
    if (!config || !config->BlockDeviceInformation) {
        ret = FALSE;
    } else {
        iret = QSF_Init();
        if (iret < 0)
            ret = FALSE;
    }
    return ret;
}

BOOL SF_BS_Driver::UnInitializeDevice(void *context)
{    
    return TRUE;
}

const BlockDeviceInfo *SF_BS_Driver::GetDeviceInfo(void *context)
{
    BLOCK_CONFIG *config = (BLOCK_CONFIG*)context;

    return config->BlockDeviceInformation;
}

BOOL SF_BS_Driver::Read(void *context, ByteAddress phyAddress, UINT32 NumBytes, BYTE *pSectorBuff)
{
#if defined(DEBUG_FLASH_Read) && !defined(DEBUG_FLASH_NG_ONLY)
    qsf_printf("R(addr=%x, num=%x, psec=%x)\r\n", phyAddress, NumBytes, pSectorBuff);
#endif
    CHIP_WORD *startAddress = (CHIP_WORD *)phyAddress;
    CHIP_WORD *endAddress = (CHIP_WORD *)(phyAddress + NumBytes);
    while (startAddress < endAddress) {
        *pSectorBuff++ = *startAddress++;
    }
    return TRUE;
}

BOOL SF_BS_Driver::Write(void *context, ByteAddress Address, UINT32 NumBytes, UINT8 *pSectorBuff, BOOL ReadModifyWrite)
{
    NATIVE_PROFILE_PAL_FLASH();
//    qsf_printf("Write(addr=%x, num=%x, psec=%x)\r\n", Address, NumBytes, pSectorBuff);
    UINT8 *pData;
    UINT8 *pBuf = NULL;
    BOOL fRet = TRUE;
    MEMORY_MAPPED_NOR_BLOCK_CONFIG* config = (MEMORY_MAPPED_NOR_BLOCK_CONFIG*)context;
    const BlockDeviceInfo * deviceInfo = config->BlockConfig.BlockDeviceInformation;
    UINT32 region, range;
    if (ReadModifyWrite) {
        if (!deviceInfo->FindRegionFromAddress(Address, region, range))
            return FALSE;
        UINT32      bytesPerBlock   = deviceInfo->Regions[region].BytesPerBlock;
        UINT32      regionEnd       = deviceInfo->Regions[region].Start + deviceInfo->Regions[region].Size();
        UINT32      offset          = Address % bytesPerBlock;
        ByteAddress addr            = Address;
        ByteAddress addrEnd         = Address + NumBytes;
        UINT32      index           = 0;
        pBuf = (UINT8 *)private_malloc(bytesPerBlock);
        if (pBuf == NULL)
            return FALSE;
        while(fRet && addr < addrEnd) {
            ByteAddress sectAddr = (addr - offset);
            if (offset == 0 && NumBytes >= bytesPerBlock) {
                pData = &pSectorBuff[index];
            } else {
                int bytes = __min(bytesPerBlock - offset, NumBytes);
                memcpy( &pBuf[0]     ,    (void*)sectAddr, bytesPerBlock );
                memcpy( &pBuf[offset], &pSectorBuff[index], bytes );
                pData = pBuf;
            }
            if (!EraseBlock(context, sectAddr)) {
                fRet = FALSE;
                break;
            }
            fRet = WriteX(context, sectAddr, bytesPerBlock, pData, ReadModifyWrite, TRUE);
            NumBytes -= bytesPerBlock - offset;
            addr     += bytesPerBlock - offset;
            index    += bytesPerBlock - offset;
            offset    = 0;
            if (NumBytes > 0 && addr >= regionEnd) {
                region++;
                if (region >= deviceInfo->NumRegions) {
                    fRet = FALSE;
                } else {
                    regionEnd       = deviceInfo->Regions[region].Start + deviceInfo->Regions[region].Size();
                    bytesPerBlock   = deviceInfo->Regions[region].BytesPerBlock;
                    private_free(pBuf);
                    pBuf = (UINT8 *)private_malloc(bytesPerBlock);
                    if (pBuf == NULL) {
                        fRet = FALSE;
                    }
                }
            }
        }
        if (pBuf != NULL) {
            private_free(pBuf);
        }
        return fRet;
    } else {
        return WriteX(context, Address, NumBytes, pSectorBuff, ReadModifyWrite, TRUE);
    }
}

BOOL SF_BS_Driver::Memset(void *context, ByteAddress phyAddr, UINT8 Data, UINT32 NumBytes)
{
    NATIVE_PROFILE_PAL_FLASH();
    return WriteX(context, phyAddr, NumBytes, &Data, TRUE, FALSE);
}

BOOL SF_BS_Driver::WriteX(void *context, ByteAddress phyAddress, UINT32 NumBytes, UINT8 *pSectorBuff, BOOL ReadModifyWrite, BOOL fIncrementDataPtr)
{
    NATIVE_PROFILE_PAL_FLASH();
#ifdef DEBUG_FLASH_Write
    qsf_printf("W(%x) %x", phyAddress, NumBytes);
#endif
    BOOL ret = TRUE;
    INT32 iret;
    UINT32 RangeIndex;
    UINT32 RegionIndex;
    UINT32 count;
    BOOL flag;
    UINT32 startAddress  = phyAddress & FLASH_BUF_ADDR_MASK;
    UINT32 offset = phyAddress & FLASH_BUF_OFF_MASK;
    UINT32 endAddress = phyAddress + NumBytes;

    MEMORY_MAPPED_SERIAL_BLOCK_CONFIG* pConfig = (MEMORY_MAPPED_SERIAL_BLOCK_CONFIG*)context;
    const BlockDeviceInfo *deviceInfo = pConfig->BlockConfig.BlockDeviceInformation;
    if (deviceInfo->FindRegionFromAddress(phyAddress, RegionIndex, RangeIndex)) {
        GLOBAL_LOCK(irq);
        while (startAddress < endAddress) {
            memcpy(wbuf, (unsigned char *)startAddress, FLASH_BUF_SIZE);
            if (NumBytes + offset > FLASH_BUF_SIZE) {
                count = FLASH_BUF_SIZE - offset;
                NumBytes -= count;
            } else
                count = NumBytes;
            if (fIncrementDataPtr)
                memcpy(wbuf + offset, pSectorBuff, count);
            else
                memset(wbuf + offset, (int)*pSectorBuff, count);
            iret = QSF_ByteWrite(startAddress + offset, (unsigned char *)(wbuf + offset), count, g_spibsc_cfg.udef_data_width, g_spibsc_cfg.udef_addr_mode);
            if (iret < 0) {
                ret = FALSE;
                break;
            }
#if 0
            if (fIncrementDataPtr) {
                iret = memcmp((void *)(startAddress + offset), wbuf + offset, count);
                if (iret != 0) {
                    ret = FALSE;
                    break;
                }
            }
#endif
            offset = 0;
            startAddress += FLASH_BUF_SIZE;
            pSectorBuff += count;
        }
    } else {
        ret = FALSE;
    }
#ifdef DEBUG_FLASH_Write
    qsf_printf(":%d\r\n", ret);
#endif
    return ret;
}

BOOL SF_BS_Driver::GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
    return FALSE;
}

BOOL SF_BS_Driver::SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata)
{
    return FALSE;
}

BOOL SF_BS_Driver::IsBlockErased(void *context, ByteAddress phyAddress, UINT32 NumBytes)
{
    NATIVE_PROFILE_HAL_DRIVERS_FLASH();
#if defined(DEBUG_FLASH)
    debug_printf("IsBlockErased(addr=%x, len=%x)\r\n", Address, BlockLength);
#endif
    CHIP_WORD *startAddress = (CHIP_WORD *)phyAddress;
    CHIP_WORD *endAddress = (CHIP_WORD *)(phyAddress + NumBytes);
    while (startAddress < endAddress)
        if (*startAddress++ != (CHIP_WORD)0xFFFFFFFF)
            return FALSE;
    return TRUE;
}

BOOL SF_BS_Driver::EraseBlock(void *context, ByteAddress phyAddress)
{
    NATIVE_PROFILE_HAL_DRIVERS_FLASH();
    BOOL ret = TRUE;
    int iret;
    UINT32 iRegion, iRange, BytesPerSector, i, j, k;
    MEMORY_MAPPED_SERIAL_BLOCK_CONFIG* config = (MEMORY_MAPPED_SERIAL_BLOCK_CONFIG*)context;
    const BlockDeviceInfo *    deviceInfo = config->BlockConfig.BlockDeviceInformation;
    if (! deviceInfo->Attribute.WriteProtected) {
        if (deviceInfo->FindRegionFromAddress(phyAddress, iRegion, iRange)) {
            iret = QSF_EraseSector((UINT32)phyAddress, g_spibsc_cfg.udef_data_width, g_spibsc_cfg.udef_addr_mode);
            if (iret < 0) {
                ret = FALSE;
            }
        } else
            ret = FALSE;
    } else
        ret = FALSE;
    if (ret == FALSE) {
#if defined(DEBUG_FLASH_EraseBlock_NG)
    qsf_printf("E(%x):NG\r\n", phyAddress);
#endif
    } else {
#if defined(DEBUG_FLASH_EraseBlock_OK) && !defined(DEBUG_FLASH_NG_ONLY)
    qsf_printf("E(%x):OK\r\n", phyAddress);
#endif
    }
    return ret;
}

void SF_BS_Driver::SetPowerState(void *context, UINT32 State)
{
    // our flash driver is always Power ON
    return ;
}

UINT32 SF_BS_Driver::MaxSectorWrite_uSec(void *context)
{
    NATIVE_PROFILE_PAL_FLASH();

    BLOCK_CONFIG *config = (BLOCK_CONFIG*)context;

    return config->BlockDeviceInformation->MaxSectorWrite_uSec;
}

UINT32 SF_BS_Driver::MaxBlockErase_uSec(void *context)
{
    NATIVE_PROFILE_PAL_FLASH();

    BLOCK_CONFIG *config = (BLOCK_CONFIG*)context;

    return config->BlockDeviceInformation->MaxBlockErase_uSec;
}

struct IBlockStorageDevice g_SerialFlash_BL_DeviceTable = 
{                          
    &SF_BS_Driver::InitializeDevice,
    &SF_BS_Driver::UnInitializeDevice,
    &SF_BS_Driver::GetDeviceInfo,
    &SF_BS_Driver::Read,
    &SF_BS_Driver::Write,
    &SF_BS_Driver::Memset,
    &SF_BS_Driver::GetSectorMetadata,
    &SF_BS_Driver::SetSectorMetadata,
    &SF_BS_Driver::IsBlockErased,
    &SF_BS_Driver::EraseBlock,
    &SF_BS_Driver::SetPowerState,
    &SF_BS_Driver::MaxSectorWrite_uSec,
    &SF_BS_Driver::MaxBlockErase_uSec,
};
