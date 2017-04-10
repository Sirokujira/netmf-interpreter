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


#ifndef _RAWIO_MICROSOFT_SPOT_HARDWARE_ADDRESSSPACE_H_
#define _RAWIO_MICROSOFT_SPOT_HARDWARE_ADDRESSSPACE_H_

namespace Microsoft
{
    namespace SPOT
    {
        namespace Hardware
        {
            struct AddressSpace
            {
                // Helper Functions to access fields of managed object
                static UINT32& Get_ASID( CLR_RT_HeapBlock* pMngObj )
                {
                    return Interop_Marshal_GetField_UINT32( pMngObj
                         , Library_RawIO_Microsoft_SPOT_Hardware_AddressSpace::FIELD__ASID );
                }
                // Declaration of stubs. These functions are implemented by Interop code developers
                static void _ctor( CLR_RT_HeapBlock* pObj, LPCSTR Name, INT32 Width, HRESULT& hr);
                static INT32 get_BitWdith( CLR_RT_HeapBlock* pObj, HRESULT& hr);
                static UINT32 get_Length( CLR_RT_HeapBlock* pObj, HRESULT& hr);

                struct TableEntry
                {
                    LPCSTR pName;     // Unique name of the address space
                    void* pBase;      // Base address of the address space
                    UINT32 BitWidth;  // Bit width for "words" in the address space
                    UINT32 Length;    // Length of the address space in "words"
                };
                // Converts an AddressSpace ID from the managed code into a
                // TableEntry*. If the ASID is not valid (e.g. doesn't point
                // to an entry in the table) an error code is returned.
                static HRESULT GetValidEntry(CLR_RT_HeapBlock* pObj, const TableEntry*& pEntry);
                // verifies ASID is in the table and offset is
                // within the allowed range; If all is OK it fills
                // in the address.
                // error: index out of range or invalid argument
                static HRESULT GetAddress(CLR_RT_HeapBlock* pObj, UINT32 offset, void*& pAddress);
                // Definition for these are provided by the HAL...
                // Table of HAL specific address spaces to expose to managed code
                static const TableEntry Spaces[];
                // Number of entries in the Spaces table
                static const size_t NumSpaces;            };
        }
    }
}
#endif  //_RAWIO_MICROSOFT_SPOT_HARDWARE_ADDRESSSPACE_H_
