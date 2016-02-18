////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////#include <tinyhal.h>
#include <tinyhal.h>
 
void SystemState_Set  ( SYSTEM_STATE State )
{
}
void SystemState_Clear( SYSTEM_STATE State )
{
}
void SystemState_SetNoLock  ( SYSTEM_STATE State )
{
}
void SystemState_ClearNoLock( SYSTEM_STATE State )
{
}
BOOL SystemState_QueryNoLock( SYSTEM_STATE State )
{
    return TRUE;
}

void HAL_EnterBooterMode()
{
}

void HAL_Initialize()
{
/*
    HAL_CONTINUATION::InitializeList();
    HAL_COMPLETION  ::InitializeList();

    HAL_Init_Custom_Heap();

    Time_Initialize();
	Events_Initialize();

    //CPU_GPIO_Initialize();
    //CPU_SPI_Initialize();

    // ENABLE_INTERRUPTS();

#if 1 //No block devices
    BlockStorageList::Initialize();
    BlockStorage_AddDevices();
    BlockStorageList::InitializeDevices();
    FS_Initialize();
    FileSystemVolumeList::Initialize();
    FS_AddVolumes();
    FileSystemVolumeList::InitializeVolumes();
#endif

    CPU_InitializeCommunication();

    LCD_Initialize();

    I2C_Initialize();

    PalEvent_Initialize();

    TimeService_Initialize();
*/    
/*
    other drivers init
*/
}


void HAL_Uninitialize()
{
/* 
    other driver uninit
*/
/*
	TimeService_UnInitialize();

    PalEvent_Uninitialize();

    I2C_Uninitialize();

    LCD_Uninitialize();

//    SOCKETS_CloseConnections();

    CPU_UninitializeCommunication();

    // DISABLE_INTERRUPTS();
    
    Events_Uninitialize();
    Time_Uninitialize();

    HAL_CONTINUATION::Uninitialize();
    HAL_COMPLETION  ::Uninitialize();
*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void HARD_Breakpoint()
{
    return;
}
/////////////////////////////////////////////////////////////////////

