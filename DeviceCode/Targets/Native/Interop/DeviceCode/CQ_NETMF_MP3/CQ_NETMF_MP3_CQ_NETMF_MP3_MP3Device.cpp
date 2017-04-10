//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------


#include "CQ_NETMF_MP3.h"
#include "CQ_NETMF_MP3_CQ_NETMF_MP3_MP3Device.h"

BOOL MP3_Initialize(void);
UINT32 MP3_Play(LPCSTR path);
UINT32 MP3_Stop(LPCSTR path);
UINT32 MP3_Pause(LPCSTR path);
void MP3_Uninitialize(void);

using namespace CQ::NETMF::MP3;

void MP3Device::MP3Device_MP3_Initialize( HRESULT &hr )
{
    MP3_Initialize();
}

void MP3Device::MP3Device_MP3_Play( LPCSTR param0, HRESULT &hr )
{
    MP3_Play(param0);
}

void MP3Device::MP3Device_MP3_Stop( LPCSTR param0, HRESULT &hr )
{
    MP3_Stop(param0);
}

void MP3Device::MP3Device_MP3_Pause( LPCSTR param0, HRESULT &hr )
{
    MP3_Pause(param0);
}

void MP3Device::MP3Device_MP3_Uninitialize( HRESULT &hr )
{
    MP3_Uninitialize();
}

