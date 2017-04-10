//-----------------------------------------------------------------------------
//
//    ** DO NOT EDIT THIS FILE! **
//    This file was generated by a tool
//    re-running the tool will overwrite this file.
//
//-----------------------------------------------------------------------------


#include "CQ_NETMF_LCD.h"
#include "CQ_NETMF_LCD_CQ_NETMF_LCD_LCDDevice.h"

using namespace CQ::NETMF::LCD;


HRESULT Library_CQ_NETMF_LCD_CQ_NETMF_LCD_LCDDevice::LCDDevice_LCD_Initialize___STATIC__VOID( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        LCDDevice::LCDDevice_LCD_Initialize( hr );
        TINYCLR_CHECK_HRESULT( hr );
    }
    TINYCLR_NOCLEANUP();
}

HRESULT Library_CQ_NETMF_LCD_CQ_NETMF_LCD_LCDDevice::LCDDevice_LCD_Clear___STATIC__VOID( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        LCDDevice::LCDDevice_LCD_Clear( hr );
        TINYCLR_CHECK_HRESULT( hr );
    }
    TINYCLR_NOCLEANUP();
}

HRESULT Library_CQ_NETMF_LCD_CQ_NETMF_LCD_LCDDevice::LCDDevice_LCD_BitBltEx___STATIC__VOID__U4__U4__U4__U4__SZARRAY_U1( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        UINT32 param0;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT32( stack, 0, param0 ) );

        UINT32 param1;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT32( stack, 1, param1 ) );

        UINT32 param2;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT32( stack, 2, param2 ) );

        UINT32 param3;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT32( stack, 3, param3 ) );

        CLR_RT_TypedArray_UINT8 param4;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 4, param4 ) );

        LCDDevice::LCDDevice_LCD_BitBltEx( param0, param1, param2, param3, param4, hr );
        TINYCLR_CHECK_HRESULT( hr );
    }
    TINYCLR_NOCLEANUP();
}

HRESULT Library_CQ_NETMF_LCD_CQ_NETMF_LCD_LCDDevice::LCDDevice_LCD_WriteFormattedChar___STATIC__VOID__U2( CLR_RT_StackFrame& stack )
{
    TINYCLR_HEADER(); hr = S_OK;
    {
        UINT16 param0;
        TINYCLR_CHECK_HRESULT( Interop_Marshal_UINT16( stack, 0, param0 ) );

        LCDDevice::LCDDevice_LCD_WriteFormattedChar( param0, hr );
        TINYCLR_CHECK_HRESULT( hr );
    }
    TINYCLR_NOCLEANUP();
}
