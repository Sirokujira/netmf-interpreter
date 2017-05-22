//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: WIN32EXTI.h 88 2011-04-05 11:03:57Z nagasima $
#ifndef WIN32EXTIH
#define WIN32EXTIH

#pragma pack(push, 1)
struct TEXTI_IMR
{
	unsigned int MR0 : 1;
	unsigned int MR1 : 1;
	unsigned int MR2 : 1;
	unsigned int MR3 : 1;
	unsigned int MR4 : 1;
	unsigned int MR5 : 1;
	unsigned int MR6 : 1;
	unsigned int MR7 : 1;
	unsigned int MR8 : 1;
	unsigned int MR9 : 1;
	unsigned int MR10 : 1;
	unsigned int MR11 : 1;
	unsigned int MR12 : 1;
	unsigned int MR13 : 1;
	unsigned int MR14 : 1;
	unsigned int MR15 : 1;
	unsigned int MR16 : 1;
	unsigned int MR17 : 1;
	unsigned int MR18 : 1;
	unsigned int : 13;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TEXTI_EMR
{
	unsigned int MR0 : 1;
	unsigned int MR1 : 1;
	unsigned int MR2 : 1;
	unsigned int MR3 : 1;
	unsigned int MR4 : 1;
	unsigned int MR5 : 1;
	unsigned int MR6 : 1;
	unsigned int MR7 : 1;
	unsigned int MR8 : 1;
	unsigned int MR9 : 1;
	unsigned int MR10 : 1;
	unsigned int MR11 : 1;
	unsigned int MR12 : 1;
	unsigned int MR13 : 1;
	unsigned int MR14 : 1;
	unsigned int MR15 : 1;
	unsigned int MR16 : 1;
	unsigned int MR17 : 1;
	unsigned int MR18 : 1;
	unsigned int : 13;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TEXTI_RTSR
{
	unsigned int TR0 : 1;
	unsigned int TR1 : 1;
	unsigned int TR2 : 1;
	unsigned int TR3 : 1;
	unsigned int TR4 : 1;
	unsigned int TR5 : 1;
	unsigned int TR6 : 1;
	unsigned int TR7 : 1;
	unsigned int TR8 : 1;
	unsigned int TR9 : 1;
	unsigned int TR10 : 1;
	unsigned int TR11 : 1;
	unsigned int TR12 : 1;
	unsigned int TR13 : 1;
	unsigned int TR14 : 1;
	unsigned int TR15 : 1;
	unsigned int TR16 : 1;
	unsigned int TR17 : 1;
	unsigned int TR18 : 1;
	unsigned int : 13;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TEXTI_FTSR
{
	unsigned int TR0 : 1;
	unsigned int TR1 : 1;
	unsigned int TR2 : 1;
	unsigned int TR3 : 1;
	unsigned int TR4 : 1;
	unsigned int TR5 : 1;
	unsigned int TR6 : 1;
	unsigned int TR7 : 1;
	unsigned int TR8 : 1;
	unsigned int TR9 : 1;
	unsigned int TR10 : 1;
	unsigned int TR11 : 1;
	unsigned int TR12 : 1;
	unsigned int TR13 : 1;
	unsigned int TR14 : 1;
	unsigned int TR15 : 1;
	unsigned int TR16 : 1;
	unsigned int TR17 : 1;
	unsigned int TR18 : 1;
	unsigned int : 13;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TEXTI_SWIER
{
	unsigned int SWIER0 : 1;
	unsigned int SWIER1 : 1;
	unsigned int SWIER2 : 1;
	unsigned int SWIER3 : 1;
	unsigned int SWIER4 : 1;
	unsigned int SWIER5 : 1;
	unsigned int SWIER6 : 1;
	unsigned int SWIER7 : 1;
	unsigned int SWIER8 : 1;
	unsigned int SWIER9 : 1;
	unsigned int SWIER10 : 1;
	unsigned int SWIER11 : 1;
	unsigned int SWIER12 : 1;
	unsigned int SWIER13 : 1;
	unsigned int SWIER14 : 1;
	unsigned int SWIER15 : 1;
	unsigned int SWIER16 : 1;
	unsigned int SWIER17 : 1;
	unsigned int SWIER18 : 1;
	unsigned int : 13;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TEXTI_PR
{
	unsigned int PR0 : 1;
	unsigned int PR1 : 1;
	unsigned int PR2 : 1;
	unsigned int PR3 : 1;
	unsigned int PR4 : 1;
	unsigned int PR5 : 1;
	unsigned int PR6 : 1;
	unsigned int PR7 : 1;
	unsigned int PR8 : 1;
	unsigned int PR9 : 1;
	unsigned int PR10 : 1;
	unsigned int PR11 : 1;
	unsigned int PR12 : 1;
	unsigned int PR13 : 1;
	unsigned int PR14 : 1;
	unsigned int PR15 : 1;
	unsigned int PR16 : 1;
	unsigned int PR17 : 1;
	unsigned int PR18 : 1;
	unsigned int : 13;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TEXTI
{
	TEXTI_IMR IMR;
	TEXTI_EMR EMR;
	TEXTI_RTSR RTSR;
	TEXTI_FTSR FTSR;
	TEXTI_SWIER SWIER;
	TEXTI_PR PR;
};
#pragma pack(pop)

//---------------------------------------------------------------------------
#endif // WIN32EXTIH
