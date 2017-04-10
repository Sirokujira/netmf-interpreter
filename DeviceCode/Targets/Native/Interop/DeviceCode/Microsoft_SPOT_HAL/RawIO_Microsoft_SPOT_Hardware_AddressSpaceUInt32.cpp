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


#include "RawIO.h"
#include "RawIO_Microsoft_SPOT_Hardware_AddressSpaceUInt32.h"

using namespace Microsoft::SPOT::Hardware;

UINT32 AddressSpaceUInt32::get_Item( CLR_RT_HeapBlock* pMngObj, UINT32 param0, HRESULT &hr )
{
    void* pTemp;
    hr = AddressSpace::GetAddress(pObj, Offset, pTemp);
    if(FAILED(hr))
        return 0;
    return *reinterpret_cast<UINT32*>(pTemp);
}

void AddressSpaceUInt32::set_Item( CLR_RT_HeapBlock* pMngObj, UINT32 param0, UINT32 param1, HRESULT &hr )
{
    void* pTemp;
    hr = AddressSpace::GetAddress(pObj, Offset, pTemp);
    if(FAILED(hr))
        return;
    *reinterpret_cast<UINT32*>(pTemp) = value;
}
