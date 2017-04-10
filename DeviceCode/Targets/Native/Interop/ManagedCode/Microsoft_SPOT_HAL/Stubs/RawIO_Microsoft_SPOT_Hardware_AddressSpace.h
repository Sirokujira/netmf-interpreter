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
                static UINT32& Get_ASID( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT32( pMngObj, Library_RawIO_Microsoft_SPOT_Hardware_AddressSpace::FIELD__ASID ); }

                // Declaration of stubs. These functions are implemented by Interop code developers
                static void _ctor( CLR_RT_HeapBlock* pMngObj, LPCSTR param0, INT32 param1, HRESULT &hr );
                static INT32 get_BitWdith( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                static UINT32 get_Length( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
            };
        }
    }
}
#endif  //_RAWIO_MICROSOFT_SPOT_HARDWARE_ADDRESSSPACE_H_
