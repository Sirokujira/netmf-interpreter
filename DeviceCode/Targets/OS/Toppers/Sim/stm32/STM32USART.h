//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: STM32USART.h 88 2011-04-05 11:03:57Z nagasima $
#ifndef STM32USARTH
#define STM32USARTH

//------------------------------------------------------------------------------
// USART registers
//------------------------------------------------------------------------------
// Status register
#pragma pack(push, 1)
struct TUSART_SR
{
	uint32_t PE : 1;
	uint32_t FE : 1;
	uint32_t NE : 1;
	uint32_t ORE : 1;
	uint32_t IDLE : 1;
	uint32_t RXNE : 1;
	uint32_t TC : 1;
	uint32_t TXE : 1;
	uint32_t LBD : 1;
	uint32_t CTS : 1;
	uint32_t : 22;
};
#pragma pack(pop)

// Data register
#pragma pack(push, 1)
struct TUSART_DR
{
	uint32_t DR : 9;
	uint32_t : 23;
};
#pragma pack(pop)

// Baud rate register
#pragma pack(push, 1)
struct TUSART_BRR
{
	uint32_t DIV_Fraction : 4;
	uint32_t DIV_Mantissa : 12;
	uint32_t : 16;
};
#pragma pack(pop)

// Control register 1
#pragma pack(push, 1)
struct TUSART_CR1
{
	uint32_t SBK : 1;
	uint32_t RWU : 1;
	uint32_t RE : 1;
	uint32_t TE : 1;
	uint32_t IDLEIE : 1;
	uint32_t RXNE_IE : 1;
	uint32_t TCIE : 1;
	uint32_t TXEIE : 1;
	uint32_t PEIE : 1;
	uint32_t PS : 1;
	uint32_t PCE : 1;
	uint32_t WAKE : 1;
	uint32_t M : 1;
	uint32_t UE : 1;
	uint32_t : 18;
};
#pragma pack(pop)

// Control register 2
#pragma pack(push, 1)
struct TUSART_CR2
{
	uint32_t ADD : 4;
	uint32_t : 1;
	uint32_t LBDL : 1;
	uint32_t LBDIE : 1;
	uint32_t : 1;
	uint32_t LBCL : 1;
	uint32_t CPHA : 1;
	uint32_t CPOL : 1;
	uint32_t CLK_EN : 1;
	uint32_t STOP : 2;
	uint32_t LINEN : 1;
	uint32_t : 17;
};
#pragma pack(pop)

// Control register 3
#pragma pack(push, 1)
struct TUSART_CR3
{
	uint32_t EIE : 1;
	uint32_t IREN : 1;
	uint32_t IRLP : 1;
	uint32_t HD_SEL : 1;
	uint32_t NACK : 1;
	uint32_t SCEN : 1;
	uint32_t DMAR : 1;
	uint32_t DMAT : 1;
	uint32_t RTSE : 1;
	uint32_t CTSE : 1;
	uint32_t CTSIE : 1;
	uint32_t : 21;
};
#pragma pack(pop)

// Guard time and prescaler register
#pragma pack(push, 1)
struct TUSART_GTPR
{
	uint32_t PSC : 8;
	uint32_t GT : 8;
	uint32_t : 16;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TUSART{
	TUSART_SR SR;
	TUSART_DR DR;
	TUSART_BRR BRR;
	TUSART_CR1 CR1;
	TUSART_CR2 CR2;
	TUSART_CR3 CR3;
	TUSART_GTPR GTPR;
};
#pragma pack(pop)

//---------------------------------------------------------------------------
#endif // STM32USARTH
