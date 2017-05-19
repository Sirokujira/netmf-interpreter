//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: WinKernel.cpp 96 2012-03-03 06:30:56Z nagasima $
#include "StdAfx.h"
#include "sil.h"
#include "WinKernel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CKernel *g_Kernel;

//---------------------------------------------------------------------------
//  �G���f�B�A���̔��]
//---------------------------------------------------------------------------
#ifndef SIL_REV_ENDIAN_H
#define	SIL_REV_ENDIAN_H(data) \
	((uint16_t)((((uint16_t)(data) & 0xff) << 8) | (((uint16_t)(data) >> 8) & 0xff)))
#endif /* SIL_REV_ENDIAN_H */

#ifndef SIL_REV_ENDIAN_W
#define	SIL_REV_ENDIAN_W(data) \
	((uint32_t)((((uint32_t)(data) & 0xff) << 24) | (((uint32_t)(data) & 0xff00) << 8) \
		| (((uint32_t)(data)>> 8) & 0xff00) | (((uint32_t)(data) >> 24) & 0xff)))
#endif /* SIL_REV_ENDIAN_H */

//---------------------------------------------------------------------------
//  8�r�b�g�P�ʂ̓Ǐo���^������
//---------------------------------------------------------------------------
uint8_t sil_reb_mem(uint8_t * mem)
{
	return g_Kernel->GetByte((uintptr_t)mem);
}

void sil_wrb_mem(uint8_t * mem, uint8_t data)
{
	g_Kernel->SetByte((uintptr_t)mem, data);
}

//---------------------------------------------------------------------------
//  16�r�b�g�P�ʂ̓Ǐo���^������
//---------------------------------------------------------------------------
uint16_t sil_reh_mem(uint16_t * mem)
{
	return g_Kernel->GetUInt16((uintptr_t)mem);
}

void sil_wrh_mem(uint16_t * mem, uint16_t data)
{
	g_Kernel->SetUInt16((uintptr_t)mem, data);
}

uint16_t sil_reh_bem(uint16_t * mem)
{
	uint16_t	data;

	data = g_Kernel->GetUInt16((uintptr_t)mem);

	return(SIL_REV_ENDIAN_H(data));
}

void sil_wrh_bem(uint16_t * mem, uint16_t data)
{
	sil_wrh_mem(mem, SIL_REV_ENDIAN_H(data));
}

//---------------------------------------------------------------------------
//  32�r�b�g�P�ʂ̓Ǐo���^������
//---------------------------------------------------------------------------
uint32_t sil_rew_mem(uint32_t * mem)
{
	return g_Kernel->GetUInt32((uintptr_t)mem);
}

void sil_wrw_mem(uint32_t * mem, uint32_t data)
{
	g_Kernel->SetUInt32((uintptr_t)mem, data);
}

uint32_t sil_rew_bem(uint32_t * mem)
{
	uint32_t	data;

	data = g_Kernel->GetUInt32((uintptr_t)mem);

	return(SIL_REV_ENDIAN_W(data));
}

void sil_wrw_bem(uint32_t * mem, uint32_t data)
{
	g_Kernel->SetUInt32((uintptr_t)mem, SIL_REV_ENDIAN_W(data));
}

