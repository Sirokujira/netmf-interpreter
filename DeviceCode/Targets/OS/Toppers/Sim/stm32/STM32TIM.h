//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: STM32TIM.h 88 2011-04-05 11:03:57Z nagasima $
#ifndef STM32TIMH
#define STM32TIMH

//-----------------------------------------------------------------------------
// TIMx registers
//-----------------------------------------------------------------------------
// Control register 1
#pragma pack(push, 1)
struct TTIM_CR1
{
	uint16_t CEN : 1;
	uint16_t UDIS : 1;
	uint16_t URS : 1;
	uint16_t OPM : 1;
	uint16_t DIR : 1;
	uint16_t CMS : 1;
	uint16_t ARPE : 1;
	uint16_t CKD : 2;
	uint16_t : 6;
};
#pragma pack(pop)

// Control register 2
#pragma pack(push, 1)
struct TTIM_CR2
{
	uint16_t : 3;
	uint16_t CCDS : 1;
	uint16_t MMS : 3;
	uint16_t TI1S : 1;
	uint16_t : 8;
};
#pragma pack(pop)

// Slave mode control register
#pragma pack(push, 1)
struct TTIM_SMCR
{
	uint16_t SMS : 3;
	uint16_t : 1;
	uint16_t TS : 3;
	uint16_t MSM : 1;
	uint16_t ETF : 4;
	uint16_t ETPS : 2;
	uint16_t ECE : 1;
	uint16_t ETP : 1;
};
#pragma pack(pop)

// DMA/Interrupt enable register
#pragma pack(push, 1)
struct TTIM_DIER
{
	uint16_t UIE : 1;
	uint16_t CC1IE : 1;
	uint16_t CC2IE : 1;
	uint16_t CC3IE : 1;
	uint16_t CC4IE : 1;
	uint16_t : 1;
	uint16_t TIE : 1;
	uint16_t : 1;
	uint16_t UDE : 1;
	uint16_t CC1_DE : 1;
	uint16_t CC2_DE : 1;
	uint16_t CC3_DE : 1;
	uint16_t CC4_DE : 1;
	uint16_t : 1;
	uint16_t TDE : 1;
	uint16_t : 1;
};
#pragma pack(pop)

// Status register (TIMx_SR)
#pragma pack(push, 1)
struct TTIM_SR
{
	uint16_t UIF : 1;
	uint16_t CC1IF : 1;
	uint16_t CC2IF : 1;
	uint16_t CC3IF : 1;
	uint16_t CC4IF : 1;
	uint16_t : 1;
	uint16_t TIF : 1;
	uint16_t : 1;
	uint16_t CC1_OF : 1;
	uint16_t CC2_OF : 1;
	uint16_t CC3_OF : 1;
	uint16_t CC4_OF : 1;
	uint16_t : 1;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_EGR
{
	uint16_t UG : 1;
	uint16_t CC1G : 1;
	uint16_t CC2G : 1;
	uint16_t CC3G : 1;
	uint16_t CC4G : 1;
	uint16_t : 1;
	uint16_t TG : 1;
	uint16_t : 9;
};
#pragma pack(pop)

#pragma pack(push, 1)
union TTIM_CCMR1
{
	struct TTIM_CCMR1_O
	{
		uint16_t CC1S : 2;
		uint16_t OC1_FE : 1;
		uint16_t OC1_PE : 1;
		uint16_t OC1M : 3;
		uint16_t OC1_CE : 1;
		uint16_t CC2S : 2;
		uint16_t OC2_FE : 1;
		uint16_t OC2_PE : 1;
		uint16_t OC2M : 3;
		uint16_t OC2_CE : 1;
	};
	struct TTIM_CCMR1_I
	{
		uint16_t CC1S : 2;
		uint16_t IC1PSC : 2;
		uint16_t IC1F : 4;
		uint16_t CC2S : 2;
		uint16_t IC2PSC : 2;
		uint16_t IC2F : 4;
	};
};
#pragma pack(pop)

#pragma pack(push, 1)
union TTIM_CCMR2
{
	struct TTIM_CCMR2_O
	{
		uint16_t CC3S : 2;
		uint16_t OC3_FE : 1;
		uint16_t OC3_PE : 1;
		uint16_t OC3M : 3;
		uint16_t OC3_CE : 1;
		uint16_t CC4S : 2;
		uint16_t OC4_FE : 1;
		uint16_t OC4_PE : 1;
		uint16_t OC4M : 3;
		uint16_t OC4_CE : 1;
	};
	struct TTIM_CCMR2_I
	{
		uint16_t CC3S : 2;
		uint16_t IC3PSC : 2;
		uint16_t IC3F : 4;
		uint16_t CC4S : 2;
		uint16_t IC4PSC : 2;
		uint16_t IC4F : 4;
	};
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_CCER
{
	uint16_t CC1E : 1;
	uint16_t CC1P : 1;
	uint16_t : 1;
	uint16_t CC2E : 1;
	uint16_t CC2P : 1;
	uint16_t : 1;
	uint16_t CC3E : 1;
	uint16_t CC3P : 1;
	uint16_t : 1;
	uint16_t CC4E : 1;
	uint16_t CC4P : 1;
	uint16_t : 1;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_CNT
{
	uint16_t CNT;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_PSC
{
	uint16_t PSC;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_ARR
{
	uint16_t ARR;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_CCR1
{
	uint16_t CCR1;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_CCR2
{
	uint16_t CCR2;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_CCR3
{
	uint16_t CCR3;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_CCR4
{
	uint16_t CCR4;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_DCR
{
	uint16_t DBA : 5;
	uint16_t : 3;
	uint16_t DBL : 5;
	uint16_t : 3;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM_DMAR
{
	uint16_t DMAR;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TTIM{
	TTIM_CR1 CR1;
	uint16_t Reserved00;
	TTIM_CR2 CR2;
	uint16_t Reserved04;
	TTIM_SMCR SMCR;
	uint16_t Reserved08;
	TTIM_DIER DIER;
	uint16_t Reserved0C;
	TTIM_SR SR;
	uint16_t Reserved10;
	TTIM_EGR EGR;
	uint16_t Reserved14;
	TTIM_CCMR1 CCMR1;
	uint16_t Reserved18;
	TTIM_CCMR2 CCMR2;
	uint16_t Reserved1C;
	TTIM_CCER CCER;
	uint16_t Reserved20;
	TTIM_CNT CNT;
	uint16_t Reserved24;
	TTIM_PSC PSC;
	uint16_t Reserved28;
	TTIM_ARR ARR;
	uint16_t Reserved2C;
	uint32_t Reserved30;
	TTIM_CCR1 CCR1;
	uint16_t Reserved34;
	TTIM_CCR2 CCR2;
	uint16_t Reserved38;
	TTIM_CCR3 CCR3;
	uint16_t Reserved3C;
	TTIM_CCR4 CCR4;
	uint16_t Reserved40;
	uint32_t Reserved44;
	TTIM_DCR DCR;
	uint16_t Reserved48;
	TTIM_DMAR DMAR;
	uint16_t Reserved4C;
};
#pragma pack(pop)

//---------------------------------------------------------------------------
#endif // STM32TIMH
