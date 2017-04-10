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


#ifndef _CQ_NETMF_CQ_FRK_FM3_HARDWARE_CQ_NETMF_CQ_FRK_FM3_HARDWARE_FM3_I2CDEVICE_H_
#define _CQ_NETMF_CQ_FRK_FM3_HARDWARE_CQ_NETMF_CQ_FRK_FM3_HARDWARE_FM3_I2CDEVICE_H_

namespace CQ
{
    namespace NETMF
    {
        namespace CQ_FRK_FM3
        {
            namespace Hardware
            {
                struct FM3_I2CDevice
                {
                    // Helper Functions to access fields of managed object
                    static UNSUPPORTED_TYPE& Get_fm3_i2c( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UNSUPPORTED_TYPE( pMngObj, Library_CQ_NETMF_CQ_FRK_FM3_Hardware_CQ_NETMF_CQ_FRK_FM3_Hardware_FM3_I2CDevice::FIELD__fm3_i2c ); }

                    static UINT32& Get_fm3_i2c_ch( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_CQ_NETMF_CQ_FRK_FM3_Hardware_CQ_NETMF_CQ_FRK_FM3_Hardware_FM3_I2CDevice::FIELD__fm3_i2c_ch ); }

                    // Declaration of stubs. These functions are implemented by Interop code developers
                    static void I2CDevice_SetChannel( UINT32 param0, HRESULT &hr );
                };
            }
        }
    }
}
#endif  //_CQ_NETMF_CQ_FRK_FM3_HARDWARE_CQ_NETMF_CQ_FRK_FM3_HARDWARE_FM3_I2CDEVICE_H_
