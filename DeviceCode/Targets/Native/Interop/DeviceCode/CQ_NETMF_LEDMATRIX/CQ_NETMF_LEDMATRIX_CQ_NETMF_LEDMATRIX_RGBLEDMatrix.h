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


#ifndef _CQ_NETMF_LEDMATRIX_CQ_NETMF_LEDMATRIX_RGBLEDMATRIX_H_
#define _CQ_NETMF_LEDMATRIX_CQ_NETMF_LEDMATRIX_RGBLEDMATRIX_H_

namespace CQ
{
    namespace NETMF
    {
        namespace LEDMATRIX
        {
            struct RGBLEDMatrix
            {
                // Helper Functions to access fields of managed object
                // Declaration of stubs. These functions are implemented by Interop code developers
                static void RGBLEDMatrix_Initialize( CLR_RT_TypedArray_UINT32 param0, HRESULT &hr );
                static void RGBLEDMatrix_SelectLine( UINT8 param0, HRESULT &hr );
                static void RGBLEDMatrix_TurnOn( HRESULT &hr );
                static void RGBLEDMatrix_TurnOff( HRESULT &hr );
                static void RGBLEDMatrix_DrawLine8( UINT8 param0, UINT8 param1, UINT8 param2, HRESULT &hr );
                static void RGBLEDMatrix_DrawLine64( UINT8 param0, UINT8 param1, UINT8 param2, HRESULT &hr );
                static void RGBLEDMatrix_DrawPat( CLR_RT_TypedArray_UINT8 param0, HRESULT &hr );
                static void RGBLEDMatrix_DrawFont8x8( CLR_RT_TypedArray_UINT8 param0, HRESULT &hr );
                static void RGBLEDMatrix_GetFontBitmap( UINT16 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr );
            };
        }
    }
}
#endif  //_CQ_NETMF_LEDMATRIX_CQ_NETMF_LEDMATRIX_RGBLEDMATRIX_H_
