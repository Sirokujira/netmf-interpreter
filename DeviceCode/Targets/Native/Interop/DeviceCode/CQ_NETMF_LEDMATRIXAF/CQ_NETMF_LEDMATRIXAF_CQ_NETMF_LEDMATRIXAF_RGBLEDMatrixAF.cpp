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


#include "CQ_NETMF_LEDMATRIXAF.h"
#include "CQ_NETMF_LEDMATRIXAF_CQ_NETMF_LEDMATRIXAF_RGBLEDMatrixAF.h"

#include <tinyhal.h>
void RGBLMAF_Initialize(GPIO_PIN* pins);
void RGBLMAF_SelectLine(UINT8 n);
void RGBLMAF_TurnOn();
void RGBLMAF_TurnOff();
void RGBLMAF_DrawLine_Color2(UINT32 pat1, UINT8 *fcol1, UINT8 *bcol1, UINT32 pat2, UINT8 *fcol2, UINT8 *bcol2);
void RGBLMAF_DrawScreen_Color2(UINT32 *pat1, UINT32 off1, UINT8 *fcol1, UINT8 *bcol1, UINT32 *pat2, UINT32 off2, UINT8 *fcol2, UINT8 *bcol2, UINT32 loop);
void RGBLMAF_DrawScreen_Color64(UINT8 *pat1, UINT32 off1, UINT8 *pat2, UINT32 off2, UINT32 loop);
void RGBLMAF_GetFontBitmap(UINT16 unicode, UINT8 *fb, UINT8 bytes);
void RGBLMAF_SetFontsToBuf(UINT16 *unicode, UINT8 *buf);
void RGBLMAF_RotateXBuf8(UINT32 *buf, INT32 rx);
void RGBLMAF_Pset(UINT8 *buf, INT32 x, INT32 y, UINT8 col_type, UINT8 col);
void RGBLMAF_Line(UINT8 *buf, INT32 x1, INT32 y1, INT32 x2, INT32 y2, UINT8 col_type, UINT8 col);
void RGBLMAF_Circle(UINT8 *buf, INT32 x, INT32 y, INT32 r, UINT8 col_type, UINT8 col);

using namespace CQ::NETMF::LEDMATRIXAF;

void RGBLEDMatrixAF::RGBLEDMatrixAF_Initialize( CLR_RT_TypedArray_UINT32 param0, HRESULT &hr )
{
	RGBLMAF_Initialize((GPIO_PIN*)param0.GetBuffer());
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_SelectLine( UINT8 param0, HRESULT &hr )
{
	RGBLMAF_SelectLine(param0);
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_TurnOn( HRESULT &hr )
{
	RGBLMAF_TurnOn();
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_TurnOff( HRESULT &hr )
{
	RGBLMAF_TurnOff();
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_DrawLineColor2( UINT32 param0, CLR_RT_TypedArray_UINT8 param1, CLR_RT_TypedArray_UINT8 param2, UINT32 param3, CLR_RT_TypedArray_UINT8 param4, CLR_RT_TypedArray_UINT8 param5, HRESULT &hr )
{
    RGBLMAF_DrawLine_Color2(param0, (UINT8 *)param1.GetBuffer(), (UINT8 *)param2.GetBuffer(), param3,  (UINT8 *)param4.GetBuffer(), (UINT8 *)param5.GetBuffer());
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_DrawScreenColor2( CLR_RT_TypedArray_UINT32 param0, UINT32 param1, CLR_RT_TypedArray_UINT8 param2, CLR_RT_TypedArray_UINT8 param3, CLR_RT_TypedArray_UINT32 param4, UINT32 param5, CLR_RT_TypedArray_UINT8 param6, CLR_RT_TypedArray_UINT8 param7, UINT32 param8, HRESULT &hr )
{
    RGBLMAF_DrawScreen_Color2((UINT32 *)param0.GetBuffer(), param1, (UINT8 *)param2.GetBuffer(), (UINT8 *)param3.GetBuffer(), (UINT32 *)param4.GetBuffer(), param5, (UINT8 *)param6.GetBuffer(), (UINT8 *)param7.GetBuffer(), param8);
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_DrawScreenColor2( CLR_RT_TypedArray_UINT8 param0, UINT32 param1, CLR_RT_TypedArray_UINT8 param2, CLR_RT_TypedArray_UINT8 param3, CLR_RT_TypedArray_UINT32 param4, UINT32 param5, CLR_RT_TypedArray_UINT8 param6, CLR_RT_TypedArray_UINT8 param7, UINT32 param8, HRESULT &hr )
{
    RGBLMAF_DrawScreen_Color2((UINT32 *)param0.GetBuffer(), param1, (UINT8 *)param2.GetBuffer(), (UINT8 *)param3.GetBuffer(), (UINT32 *)param4.GetBuffer(), param5, (UINT8 *)param6.GetBuffer(), (UINT8 *)param7.GetBuffer(), param8);
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_DrawScreenColor64( CLR_RT_TypedArray_UINT8 param0, UINT32 param1, CLR_RT_TypedArray_UINT8 param2, UINT32 param3, UINT32 param4, HRESULT &hr )
{
    RGBLMAF_DrawScreen_Color64((UINT8 *)param0.GetBuffer(), param1, (UINT8 *)param2.GetBuffer(), param3, param4);
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_GetFontBitmap( UINT16 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
    RGBLMAF_GetFontBitmap(param0, (UINT8*)param1.GetBuffer(), (UINT8)param1.GetSize());
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_SetFontsToBuf( CLR_RT_TypedArray_UINT16 param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr )
{
	RGBLMAF_SetFontsToBuf((UINT16 *)param0.GetBuffer(), (UINT8 *)param1.GetBuffer());
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_SetFontsToBuf( CLR_RT_TypedArray_UINT16 param0, CLR_RT_TypedArray_UINT32 param1, HRESULT &hr )
{
    RGBLMAF_SetFontsToBuf((UINT16 *)param0.GetBuffer(), (UINT8 *)param1.GetBuffer());
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_RotateXBufColor2( CLR_RT_TypedArray_UINT32 param0, INT32 param1, HRESULT &hr )
{
    RGBLMAF_RotateXBuf8((UINT32 *)param0.GetBuffer(), param1);
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_Pset( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, UINT8 param3, UINT8 param4, HRESULT &hr )
{
    RGBLMAF_Pset((UINT8 *)param0.GetBuffer(), param1, param2, param3, param4);
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_Line( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, INT32 param3, INT32 param4, UINT8 param5, UINT8 param6, HRESULT &hr )
{
    RGBLMAF_Line((UINT8 *)param0.GetBuffer(), param1, param2, param3, param4, param5, param6);
}

void RGBLEDMatrixAF::RGBLEDMatrixAF_Circle( CLR_RT_TypedArray_UINT8 param0, INT32 param1, INT32 param2, INT32 param3, UINT8 param4, UINT8 param5, HRESULT &hr )
{
    RGBLMAF_Circle((UINT8 *)param0.GetBuffer(), param1, param2, param3, param4, param5);
}

