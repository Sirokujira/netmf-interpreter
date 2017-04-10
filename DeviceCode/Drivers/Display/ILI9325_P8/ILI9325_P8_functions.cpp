////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010-2011 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#include "tinyhal.h"
#include "ILI9325_P8.h"

BOOL LCD_Initialize()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::Initialize();
    LCD_Clear();
    return true;
}

BOOL LCD_Uninitialize()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return true;
}

void LCD_Clear()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::Clear();
}

void LCD_BitBltEx(int x, int y, int width, int height, UINT32 data[])
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::BitBltEx(x, y, width, height, data);
}

void LCD_BitBltEx565(int x, int y, int width, int height, UINT32 data[])
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::BitBltEx565(x, y, width, height, data);
}

void LCD_BitBlt(int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::BitBltEx(0, 0, width, height, data);
}

void LCD_WriteChar(unsigned char c, int row, int col)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::WriteChar(c, row, col);
}

void LCD_WriteFormattedChar(unsigned char c)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::WriteFormattedChar(c);
}

void LCD_WriteFormattedChar16(unsigned short s)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    ILI9325_P8_Driver::WriteFormattedChar((char)s);
}

INT32 LCD_GetWidth()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return g_ILI9325_P8_Config.Width;
}

INT32 LCD_GetHeight()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return g_ILI9325_P8_Config.Height;
}

INT32 LCD_GetBitsPerPixel()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return g_ILI9325_P8_Config.BitsPerPixel;
}

UINT32 LCD_GetPixelClockDivider()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return 0;
}
INT32 LCD_GetOrientation()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return 0;
}

void LCD_PowerSave(BOOL On)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
}

UINT32 *LCD_GetFrameBuffer()
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return NULL;
}

UINT32 LCD_ConvertColor(UINT32 color)
{
    NATIVE_PROFILE_HAL_DRIVERS_DISPLAY();
    return color;
}
