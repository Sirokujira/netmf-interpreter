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


#include "CQ_NETMF_LEDMATRIX.h"
#include "CQ_NETMF_LEDMATRIX_CQ_NETMF_LEDMATRIX_RGBLEDMatrix.h"

#include <tinyhal.h>
void RGBLM_Initialize(GPIO_PIN* pins);
void RGBLM_SelectLine(UINT8 n);
void RGBLM_TurnOn();
void RGBLM_TurnOff();
void RGBLM_UpdateCount();
UINT8 RGBLM_GetColor8(UINT8 col64);
void RGBLM_DrawLine8(UINT8 pattern, UINT8 fcol, UINT8 bcol);
void RGBLM_DrawLine64(UINT8 pattern, UINT8 fcol, UINT8 bcol);
void RGBLM_DrawPat(UINT8 pixels[8]);
void RGBLM_WaitLine(volatile uint32_t loop);
void RGBLM_Font(UINT8* font);
void RGBLM_GetFontBitmap(UINT16 unicode, UINT8 *fb, UINT8 bytes);

using namespace CQ::NETMF::LEDMATRIX;

void RGBLEDMatrix::RGBLEDMatrix_Initialize( CLR_RT_TypedArray_UINT32 param0, HRESULT &hr )
{
	RGBLM_Initialize((GPIO_PIN*)param0.GetBuffer());
}

void RGBLEDMatrix::RGBLEDMatrix_SelectLine( UINT8 param0, HRESULT &hr )
{
	RGBLM_SelectLine(param0);
}

void RGBLEDMatrix::RGBLEDMatrix_TurnOn( HRESULT &hr )
{
	RGBLM_TurnOn();
}

void RGBLEDMatrix::RGBLEDMatrix_TurnOff( HRESULT &hr )
{
	RGBLM_TurnOff();
}

void RGBLEDMatrix::RGBLEDMatrix_DrawLine8( UINT8 param0, UINT8 param1, UINT8 param2, HRESULT &hr )
{
	RGBLM_DrawLine8(param0, param1, param2);
}

void RGBLEDMatrix::RGBLEDMatrix_DrawLine64( UINT8 param0, UINT8 param1, UINT8 param2, HRESULT &hr )
{
	RGBLM_DrawLine64(param0, param1, param2);
}

void RGBLEDMatrix::RGBLEDMatrix_DrawPat( CLR_RT_TypedArray_UINT8 param0, HRESULT &hr )
{
	RGBLM_DrawPat((UINT8*)param0.GetBuffer());
}

void RGBLEDMatrix::RGBLEDMatrix_DrawFont8x8( CLR_RT_TypedArray_UINT8 param0, HRESULT &hr )
{
	RGBLM_Font((UINT8*)param0.GetBuffer());
}

void RGBLEDMatrix::RGBLEDMatrix_GetFontBitmap( UINT16 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
	RGBLM_GetFontBitmap(param0, (UINT8*)param1.GetBuffer(), (UINT8*)param1.GetSize());
}

