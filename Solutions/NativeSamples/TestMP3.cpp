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

#ifdef TEST_MP3

//#include "..\..\..\..\DeviceCode\Targets\Native\FM3\DeviceCode\FM3.h"
//#include "..\..\..\..\DeviceCode\Drivers\FS\FAT\FAT_FS.h"

//FILESYSTEM_DRIVER_INTERFACE g_FAT32_FILE_SYSTEM_DriverInterface;
//STREAM_DRIVER_INTERFACE g_FAT32_STREAM_DriverInterface;
//FileSystemVolume g_SD_FS;
//struct BlockStorageDevice  g_SD_BS;
//struct IBlockStorageDevice g_SD_BS_DeviceTable;
//struct BLOCK_CONFIG        g_SD_BS_Config;

BOOL MP3_Initialize(void);
UINT32 MP3_Play(LPCSTR path);
void MP3_Uninitialize(void);

char mp3_file[] = "\\TEST00.MP3";

void TestMP3(void)
{
    //FM3_GPIO->PFR3 &= ~0x0011;
    //FM3_GPIO->DDR3 |= 0x0011;
    //FM3_GPIO->PDOR3 |= 0x0011;
    FS_MountRemovableVolumes();
    if (MP3_Initialize() == TRUE) {
        MP3_Play((LPCSTR)&mp3_file);
        MP3_Uninitialize();
    }
}
#endif
