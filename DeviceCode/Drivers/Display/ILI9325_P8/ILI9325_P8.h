////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010-2011 Kentaro Sekimoto  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#ifndef ILI9325_P8_H_
#define ILI9325_P8_H_
#include "tinyhal.h"

struct ILI9325_P8_CONFIG {
    UINT16 Width;
    UINT16 Height;
    UINT16 BitsPerPixel;
    UINT16 fcol;
    UINT16 bcol;

    UINT16 TextSx;
    UINT16 TextSy;
};

extern ILI9325_P8_CONFIG g_ILI9325_P8_Config;

struct ILI9325_P8_Driver {
    UINT32 m_cx;
    UINT32 m_cy;

    static BOOL Initialize();
    static BOOL Uninitialize();
    static void PowerSave(BOOL On);
    static void Clear();
    static void BitBltEx(int x, int y, int width, int height, UINT32 data[]);
    static void BitBlt(int width, int height, int widthInWords, UINT32 data[], BOOL fUseDelta);
    static void WriteChar(unsigned char c, int row, int col);
    static void WriteFormattedChar(unsigned char c);
    static void BitBltEx565(int x, int y, int width, int height, UINT32 data[]);
private:
    static void WriteChar_Color(unsigned char c, UINT8 cx, UINT8 cy, UINT16 fgcol, UINT16 bgcol);
};

extern ILI9325_P8_Driver g_ILI9325_P8_Driver;

#endif /* ILI9325_P8_H_ */
