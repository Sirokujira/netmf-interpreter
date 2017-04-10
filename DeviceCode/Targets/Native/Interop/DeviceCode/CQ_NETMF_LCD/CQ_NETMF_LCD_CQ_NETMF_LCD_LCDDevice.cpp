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


#include "CQ_NETMF_LCD.h"
#include "CQ_NETMF_LCD_CQ_NETMF_LCD_LCDDevice.h"

using namespace CQ::NETMF::LCD;

void LCD_BitBltEx565(int x, int y, int width, int height, UINT32 data[]);
void LCD_WriteFormattedChar16(unsigned short s);

void LCDDevice::LCDDevice_LCD_Initialize( HRESULT &hr )
{
    LCD_Initialize();
}

void LCDDevice::LCDDevice_LCD_Clear( HRESULT &hr )
{
    LCD_Clear();
}

void LCDDevice::LCDDevice_LCD_BitBltEx( UINT32 param0, UINT32 param1, UINT32 param2, UINT32 param3, CLR_RT_TypedArray_UINT8 param4, HRESULT &hr )
{
    LCD_BitBltEx565(param0, param1, param2, param3, (UINT32 *)((UINT8 *)param4.GetBuffer()));
}

void LCDDevice::LCDDevice_LCD_WriteFormattedChar( UINT16 param0, HRESULT &hr )
{
    LCD_WriteFormattedChar16(param0);
}

