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


#ifndef _CQ_NETMF_MP3_CQ_NETMF_MP3_MP3DEVICE_H_
#define _CQ_NETMF_MP3_CQ_NETMF_MP3_MP3DEVICE_H_

namespace CQ
{
    namespace NETMF
    {
        namespace MP3
        {
            struct MP3Device
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static void MP3Device_MP3_Initialize( HRESULT &hr );
                static void MP3Device_MP3_Play( LPCSTR param0, HRESULT &hr );
                static void MP3Device_MP3_Stop( LPCSTR param0, HRESULT &hr );
                static void MP3Device_MP3_Pause( LPCSTR param0, HRESULT &hr );
                static void MP3Device_MP3_Uninitialize( HRESULT &hr );
            };
        }
    }
}
#endif  //_CQ_NETMF_MP3_CQ_NETMF_MP3_MP3DEVICE_H_
