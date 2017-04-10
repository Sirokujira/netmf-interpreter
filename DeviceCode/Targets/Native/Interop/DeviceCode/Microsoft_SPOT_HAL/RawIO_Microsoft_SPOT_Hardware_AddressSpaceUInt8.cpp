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
#include "RawIO_Microsoft_SPOT_Hardware_AddressSpaceUInt8.h"

using namespace Microsoft::SPOT::Hardware;

UINT8 AddressSpaceUInt8::get_Item(CLR_RT_HeapBlock* pObj, UINT32 Offset, HRESULT& hr)
{
    void* pTemp;
    hr = AddressSpace::GetAddress(pObj, Offset, pTemp);
    if(FAILED(hr))
        return 0;
    return *reinterpret_cast<UINT8*>(pTemp);
}

void AddressSpaceUInt8::set_Item(CLR_RT_HeapBlock* pObj, UINT32 Offset, UINT8 value, HRESULT& hr)
{
    void* pTemp;
    hr = AddressSpace::GetAddress(pObj, Offset, pTemp);
    if(FAILED(hr))
        return;
    *reinterpret_cast<UINT8*>(pTemp) = value;
}

