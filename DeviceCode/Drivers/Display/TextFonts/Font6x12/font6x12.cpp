////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DRIVERS_DISPLAY_SED15E0_FONT6X12_CPP_
#define _DRIVERS_DISPLAY_SED15E0_FONT6X12_CPP_ 1


#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "font_6x12"
#endif

#include "font6x12.h"

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata
#endif

/*
 *  Object:
 *      ffont               EXPORTED function
 *
 *      Returns the glyph for a character
 *
 * The font file is slightly compressed, this function knows where
 * the holes are. See comment above.
 */
const unsigned char* Font_GetGlyph(unsigned char c)
{
    c &= 0xFF;
    return &font_6x12[((unsigned int)c)*12];
}

int Font_Width()
{
    return 6;
}

int Font_Height()
{
    return 12;
}

int Font_TabWidth()
{
    return 4;
}

#endif
