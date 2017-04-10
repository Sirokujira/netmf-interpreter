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
#include "RawIO_Microsoft_SPOT_Hardware_AddressSpace.h"

using namespace Microsoft::SPOT::Hardware;

void AddressSpace::_ctor(CLR_RT_HeapBlock* pObj, LPCSTR Name, INT32 Width, HRESULT& hr)
{
    // scan the table to find the named adrress space
    const AddressSpace::TableEntry* pSpace = NULL;
    for (int i=0; NULL==pSpace && i< AddressSpace::NumSpaces; ++i) {
        if(strcmp(Name, AddressSpace::Spaces[i].pName) == 0)
            pSpace = AddressSpace::Spaces + i;
    }
    // if not found, complain about it
    if (NULL == pSpace) {
        hr = CLR_E_INVALID_ARGUMENT;
        return;
    }
    UINT32& ASID = AddressSpace::Get_ASID(pObj);
    ASID = reinterpret_cast<UINT32>(pSpace);
}

INT32 AddressSpace::get_BitWdith(CLR_RT_HeapBlock* pObj, HRESULT& hr)
{
    const AddressSpace::TableEntry* pEntry;
    hr = AddressSpace::GetValidEntry(pObj, pEntry);
    if(FAILED(hr))
        return 0;
    return pEntry->BitWidth;
}

UINT32 AddressSpace::get_Length(CLR_RT_HeapBlock* pObj, HRESULT& hr)
{
    const AddressSpace::TableEntry* pEntry;
    hr = AddressSpace::GetValidEntry(pObj, pEntry);
    if(FAILED(hr))
        return 0;
    return pEntry->Length;
}

// group = Internal implementation support
HRESULT AddressSpace::GetValidEntry(CLR_RT_HeapBlock* pObj, const AddressSpace::TableEntry*& pEntry)
{
    UINT32& ASID = AddressSpace::Get_ASID(pObj);
    // get the ID as a table entry pointer
    pEntry = reinterpret_cast<AddressSpace::TableEntry*>(ASID);
    // make sure it's in the table
    if (pEntry > (AddressSpace::Spaces + AddressSpace::NumSpaces) || pEntry < AddressSpace::Spaces) {
        return CLR_E_INVALID_ARGUMENT;
    }
    return S_OK;
}

HRESULT AddressSpace::GetAddress(CLR_RT_HeapBlock* pObj, UINT32 Offset, void*& pAddress)
{
    const AddressSpace::TableEntry* pEntry;
    HRESULT hr = AddressSpace::GetValidEntry(pObj, pEntry);
    if (FAILED(hr))
        return hr;
    // bounds check the offset for safety
    if (Offset >= pEntry->Length)
        return CLR_E_INDEX_OUT_OF_RANGE;
    // compute the actual address acounting for bitwidth of each "word"
    pAddress = reinterpret_cast<void*>(UINT32(pEntry->pBase) + Offset * pEntry->BitWidth/8);
    return S_OK;
}
