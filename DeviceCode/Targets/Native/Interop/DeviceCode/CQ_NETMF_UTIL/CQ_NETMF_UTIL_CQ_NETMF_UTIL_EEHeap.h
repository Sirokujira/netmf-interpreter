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


#ifndef _CQ_NETMF_UTIL_CQ_NETMF_UTIL_EEHEAP_H_
#define _CQ_NETMF_UTIL_CQ_NETMF_UTIL_EEHEAP_H_

namespace CQ
{
    namespace NETMF
    {
        namespace UTIL
        {
            struct EEHeap
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static UINT32 EEHeap_get_top( HRESULT &hr );
                static UINT32 EEHeap_get_size( HRESULT &hr );
                static UINT32 EEHeap_get_next( UINT32 param0, HRESULT &hr );
                static UINT32 EEHeap_get_prev( UINT32 param0, HRESULT &hr );
                static UINT32 EEHeap_get_last( HRESULT &hr );
                static UINT32 EEHeap_get_hb_flags( UINT32 param0, HRESULT &hr );
                static UINT32 EEHeap_get_hb_size( UINT32 param0, HRESULT &hr );
                static UINT32 EEHeap_get_hb_type( UINT32 param0, HRESULT &hr );
            };
        }
    }
}
#endif  //_CQ_NETMF_UTIL_CQ_NETMF_UTIL_EEHEAP_H_
