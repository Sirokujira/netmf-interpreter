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


#include "CQ_NETMF_CQ_FRK_FM3_Hardware.h"
#include "CQ_NETMF_CQ_FRK_FM3_Hardware_CQ_NETMF_CQ_FRK_FM3_Hardware_FM3_I2CDevice.h"

void I2C_Internal_SetChannel(INT32 channel);

using namespace CQ::NETMF::CQ_FRK_FM3::Hardware;

void FM3_I2CDevice::I2CDevice_SetChannel( UINT32 param0, HRESULT &hr )
{
    I2C_Internal_SetChannel(param0);
}

