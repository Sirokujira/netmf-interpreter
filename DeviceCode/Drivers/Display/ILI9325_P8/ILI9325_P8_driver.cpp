////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010-2011 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// LCD Driver for WX-MP3PLCD-001 board (http://www.ejigu.com/ca28/53/p-r-s/)
//      DST1007PH-24 (http://www.aitendo.com/product/3138)
//      LCD controler: ILI9325_P8
//      ILI9325_P8.c (http://www.will-elec.jp/mp3p_lcd_rx62n_kpit20120402.zip)
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "ILI9325_P8.h"

void P8_Initialize(void);
void LCD_nRESET(int n);
void P8_LCD_cmd(volatile unsigned short index, volatile unsigned short data);
void P8_LCD_reg(volatile unsigned short index);
void P8_LCD_dat(volatile unsigned short data);
unsigned short P8_LCD_read_dat(volatile unsigned short index);

ILI9325_P8_Driver g_ILI9325_P8_Driver;

static void delayms(volatile UINT32 n)
{
    HAL_Time_Sleep_MicroSeconds_InterruptEnabled(n * 1000);
}

BOOL ILI9325_P8_Driver::Initialize()
{
    unsigned short id;
    P8_Initialize();

    LCD_nRESET(1);
    delayms(100);   // Delay 10ms
    LCD_nRESET(0);
    delayms(200);   // Delay 100ms
    LCD_nRESET(1);
    delayms(1000);  // Delay 100ms

    //id = P8_LCD_read_dat(0x0000);
    //P8_LCD_cmd(0x00e7, 0x0010);
    //P8_LCD_cmd(0x0000, 0x0001);
    //P8_LCD_cmd(0x00e3, 0x3008);
    //P8_LCD_cmd(0x00e7, 0x0012);
    //P8_LCD_cmd(0x00ef, 0x1231);
    P8_LCD_cmd(0x00e5, 0x0000);
    P8_LCD_cmd(0x0000, 0x0000);
    P8_LCD_cmd(0x0001, 0x0100);     // set SS and SM bit
    P8_LCD_cmd(0x0002, 0x0700);     // set 1 line inversion
    P8_LCD_cmd(0x0003, 0x1030);     // set GRAM write direction and BGR=1.
    P8_LCD_cmd(0x0004, 0x0000);     // Resize register
    //P8_LCD_cmd(0x0008, 0x0207);     // set the back porch and front porch
    P8_LCD_cmd(0x0008, 0x0202);     // set the back porch and front porch
    P8_LCD_cmd(0x0009, 0x0000);     // set non-display area refresh g_ILI9325_P8_Driver.m_cycle ISC[3:0]
    P8_LCD_cmd(0x000A, 0x0000);     // FMARK function
    P8_LCD_cmd(0x000C, 0x0000);     // RGB interface setting
    P8_LCD_cmd(0x000D, 0x0000);     // Frame marker Position
    P8_LCD_cmd(0x000F, 0x0000);     // RGB interface polarity
    P8_LCD_cmd(0x0010, 0x0000);     // SAP, BT[3:0], AP, DSTB, SLP, STB
    //P8_LCD_cmd(0x0011, 0x0007);     // DC1[2:0], DC0[2:0], VC[2:0]
    P8_LCD_cmd(0x0011, 0x0000);     // DC1[2:0], DC0[2:0], VC[2:0]
    P8_LCD_cmd(0x0012, 0x0000);     // VREG1OUT voltage
    P8_LCD_cmd(0x0013, 0x0000);     // VDV[4:0] for VCOM amplitude
    delayms(200);                   // Dis-charge capacitor power voltage
    //P8_LCD_cmd(0x0010, 0x1490);     // SAP, BT[3:0], AP, DSTB, SLP, STB
    P8_LCD_cmd(0x0010, 0x17b0);     // SAP, BT[3:0], AP, DSTB, SLP, STB
    //P8_LCD_cmd(0x0011, 0x0221);     // Set DC1[2:0], DC0[2:0], VC[2:0]
    P8_LCD_cmd(0x0011, 0x0037);     // Set DC1[2:0], DC0[2:0], VC[2:0]
    delayms(50);                    // Delay 50ms
    //P8_LCD_cmd(0x0012, 0x001c);     // External reference voltage= Vci;
    P8_LCD_cmd(0x0012, 0x0138);     // External reference voltage= Vci;
    delayms(50);                    // Delay 50ms
    //P8_LCD_cmd(0x0013, 0x0a00);     // VDV[4:0] for VCOM amplitude
    P8_LCD_cmd(0x0013, 0x1700);     // VDV[4:0] for VCOM amplitude
    //P8_LCD_cmd(0x0029, 0x000f);     // VCM[5:0] for VCOMH
    P8_LCD_cmd(0x0029, 0x000d);     // VCM[5:0] for VCOMH
    P8_LCD_cmd(0x002B, 0x000d);     // Set Frame Rate
    delayms(50);                    // Delay 50ms
    P8_LCD_cmd(0x0020, 0x0000);     // GRAM horizontal Address
    P8_LCD_cmd(0x0021, 0x0000);     // GRAM Vertical Address
    delayms(50);                    // Delay 50ms
    P8_LCD_cmd(0x0030, 0x0001);
    P8_LCD_cmd(0x0031, 0x0606);
    P8_LCD_cmd(0x0032, 0x0304);
    P8_LCD_cmd(0x0033, 0x0202);
    P8_LCD_cmd(0x0034, 0x0202);
    P8_LCD_cmd(0x0035, 0x0103);
    P8_LCD_cmd(0x0036, 0x011d);
    P8_LCD_cmd(0x0037, 0x0404);
    P8_LCD_cmd(0x0038, 0x0404);
    P8_LCD_cmd(0x0039, 0x0700);
    P8_LCD_cmd(0x003C, 0x0000);
    P8_LCD_cmd(0x003D, 0x0a1f);
    delayms(50);                    // Delay 50ms
    P8_LCD_cmd(0x0050, 0x0000);     // Horizontal GRAM Start Address
    P8_LCD_cmd(0x0051, g_ILI9325_P8_Config.Width - 1);
    P8_LCD_cmd(0x0052, 0x0000);     // Vertical GRAM Start Address
    P8_LCD_cmd(0x0053, g_ILI9325_P8_Config.Height - 1);
    P8_LCD_cmd(0x0060, 0xA700);     // Gate Scan Line
    P8_LCD_cmd(0x0061, 0x0001);     // NDL,VLE, REV
    P8_LCD_cmd(0x006A, 0x0000);     // set scrolling line
    P8_LCD_cmd(0x0080, 0x0000);
    P8_LCD_cmd(0x0081, 0x0000);
    P8_LCD_cmd(0x0082, 0x0000);
    P8_LCD_cmd(0x0083, 0x0000);
    P8_LCD_cmd(0x0084, 0x0000);
    P8_LCD_cmd(0x0085, 0x0000);
    P8_LCD_cmd(0x0090, 0x0010);
    P8_LCD_cmd(0x0092, 0x0600);
    P8_LCD_cmd(0x0093, 0x0003);
    P8_LCD_cmd(0x0095, 0x0101);
    P8_LCD_cmd(0x0097, 0x0000);
    P8_LCD_cmd(0x0098, 0x0000);
    //P8_LCD_cmd(0x0007, 0x0133);   // 262K color and display ON
    P8_LCD_cmd(0x0007, 0x0021);     // 262K color and display ON
    P8_LCD_cmd(0x0007, 0x0031);     // 262K color and display ON
    P8_LCD_cmd(0x0007, 0x0173);     // 262K color and display ON
    delayms(50);                    // Delay 50ms

#if 0
    P8_LCD_reg(0x0022);
    unsigned int i,n,m;
    unsigned short color[8]={0xf800,0x07e0,0x001f,0x07ff,0xf81f,0xffe0,0x0000,0xffff};
    for(n=0;n<8;n++)
        for(i=0;i<40;i++)
            for(m=0;m<240;m++)
                P8_LCD_dat(0xffff);

    for(n=0;n<8;n++)
        for(i=0;i<40;i++)
            for(m=0;m<240;m++)
                P8_LCD_dat(color[n]);
#endif
}

BOOL ILI9325_P8_Driver::Uninitialize()
{
}

void ILI9325_P8_Driver::PowerSave(BOOL On)
{
}

void ILI9325_P8_Driver::Clear()
{
    UINT32 x;
    g_ILI9325_P8_Driver.m_cx = 0;
    g_ILI9325_P8_Driver.m_cy = 0;
    P8_LCD_cmd(0x0020, 0);
    P8_LCD_cmd(0x0021, 0);
    P8_LCD_reg(0x0022);
    for (x = 0; x < (g_ILI9325_P8_Config.Width * g_ILI9325_P8_Config.Height); x++){
        P8_LCD_dat(0x0000);
    }
}

void ILI9325_P8_Driver::BitBltEx( int x, int y, int width, int height, UINT32 data[] )
{
    int i, j;
    UINT16 v1, v2;
    UINT16 *pdata = (UINT16 *)data;
    pdata += (y * g_ILI9325_P8_Config.Width + x);
    for (j = 0; j < height; j ++) {
        P8_LCD_cmd(0x0020, x);
        P8_LCD_cmd(0x0021, y + j);
        P8_LCD_reg(0x0022);
        for (i = 0; i < width; i ++) {
            P8_LCD_dat(*(pdata + i));
        }
        pdata += g_ILI9325_P8_Config.Width;
    }
}

void ILI9325_P8_Driver::BitBltEx565(int x, int y, int width, int height, UINT32 data[])
{
    int i, j;
    UINT16 v1, v2;
    UINT16 *pdata = (UINT16 *)data;
    for (j = 0; j < height; j ++) {
        P8_LCD_cmd(0x0020, x);
        P8_LCD_cmd(0x0021, y + j);
        P8_LCD_reg(0x0022);
        for (i = 0; i < width; i ++) {
            P8_LCD_dat(*(pdata + i));
        }
        pdata += g_ILI9325_P8_Config.Width;
    }
}

void ILI9325_P8_Driver::WriteChar_Color(unsigned char c, UINT8 cx, UINT8 cy, UINT16 fgcol, UINT16 bgcol)
{
    UINT8 x, y;
    UINT16 col;
    UINT16 sx = cx * Font_Width() + g_ILI9325_P8_Config.TextSx;
    UINT16 sy = cy * Font_Height() + g_ILI9325_P8_Config.TextSy;

    unsigned char *font = (unsigned char *)Font_GetGlyph(c);
    for (y = 0; y < Font_Height(); y++) {
        P8_LCD_cmd(0x0020, sx);
        P8_LCD_cmd(0x0021, sy + y);
        P8_LCD_reg(0x0022);
        for (x = 0; x < Font_Width(); x++) {
            if (font[y] & (0x80 >> x)) {
                col = fgcol;
            } else {
                col = bgcol;
            }
            P8_LCD_dat(col);
        }
    }
}

void ILI9325_P8_Driver::WriteChar(unsigned char c, int cx, int cy)
{
    WriteChar_Color(c, (UINT8)cx, (UINT8)cy, g_ILI9325_P8_Config.fcol, g_ILI9325_P8_Config.bcol);
}

void ILI9325_P8_Driver::WriteFormattedChar(unsigned char ch)
{
    UINT16 colums = g_ILI9325_P8_Config.Width/Font_Width();
    UINT16 rows = g_ILI9325_P8_Config.Height/Font_Height();
    if (ch == 0xc) {
        Clear();
        g_ILI9325_P8_Driver.m_cx = 0;
        g_ILI9325_P8_Driver.m_cy = 0;
    } else if (ch == '\n') {
        g_ILI9325_P8_Driver.m_cy++;
        if (g_ILI9325_P8_Driver.m_cy == rows) {
            g_ILI9325_P8_Driver.m_cy = 0;
        }
    } else if (ch == '\r') {
        g_ILI9325_P8_Driver.m_cx = 0;
    } else {
        WriteChar(ch, g_ILI9325_P8_Driver.m_cx, g_ILI9325_P8_Driver.m_cy);
        g_ILI9325_P8_Driver.m_cx ++;
        if (g_ILI9325_P8_Driver.m_cx == colums) {
            g_ILI9325_P8_Driver.m_cx = 0;
            g_ILI9325_P8_Driver.m_cy ++;
            if (g_ILI9325_P8_Driver.m_cy == rows) {
                g_ILI9325_P8_Driver.m_cy = 0;
            }
        }
    }
}
