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

#ifdef TEST_SD
#include "..\..\..\..\DeviceCode\Targets\Native\FM3\DeviceCode\FM3.h"
#include "..\..\..\..\DeviceCode\Drivers\FS\FAT\FAT_FS.h"

FILESYSTEM_DRIVER_INTERFACE g_FAT32_FILE_SYSTEM_DriverInterface;
STREAM_DRIVER_INTERFACE g_FAT32_STREAM_DriverInterface;
FileSystemVolume g_SD_FS;
struct BlockStorageDevice  g_SD_BS;
struct IBlockStorageDevice g_SD_BS_DeviceTable;
struct BLOCK_CONFIG        g_SD_BS_Config;

const WCHAR path[12] = {'\\', 'S', 'D', 'T', 'E', 'S', 'T', '.', 'T', 'X', 'T', '\0'};

void SD_InsertEjectIsr(GPIO_PIN Pin, BOOL PinState, void* Param)
{
    if (!PinState) {
        if (BlockStorageList::AddDevice(&g_SD_BS, &g_SD_BS_DeviceTable, &g_SD_BS_Config, TRUE)) {
            FS_MountVolume("SD", 0, 0, &g_SD_BS);
        }
    } else {
        FS_UnmountVolume(&g_SD_BS);
        BlockStorageList::RemoveDevice(&g_SD_BS, TRUE);
    }
}

BOOL SDOpenFile()
{
    UINT32 handle = 0;
    FileSystemVolume *pFSVolume = NULL;

    if (BlockStorageList::AddDevice(&g_SD_BS, &g_SD_BS_DeviceTable, &g_SD_BS_Config, TRUE)) {
        FS_MountVolume("SD", 0, 0, &g_SD_BS);
        pFSVolume = FileSystemVolumeList::GetFirstVolume();
        if (pFSVolume) {
            debug_printf("id:%d\r\n", pFSVolume->m_volumeId);
            debug_printf("name space:%s\r\n", pFSVolume->m_nameSpace);
            debug_printf("label:%s\r\n", pFSVolume->m_label);
            FAT_FS_Driver::Open(&pFSVolume->m_volumeId, (LPCWSTR)path, &handle);
            if (!handle) {
                debug_printf("SD can't open\r\n");
                return FALSE;
            }
        } else {
            debug_printf("SD Volume not found\r\n");
            return FALSE;
        }
        debug_printf("SD File found\r\n");
        return TRUE;
    } else {
        debug_printf("SD can't add device\r\n");
        return FALSE;
    }
}

void TestSD(void)
{
    FM3_GPIO->PFR3 &= ~0x0011;
    FM3_GPIO->DDR3 |= 0x0011;
    FM3_GPIO->PDOR3 |= 0x0011;
    SDOpenFile();
}
#endif
