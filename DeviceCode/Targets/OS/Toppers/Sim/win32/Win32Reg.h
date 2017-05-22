//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: WIN32Reg.h 88 2011-04-05 11:03:57Z nagasima $
#ifndef WIN32RegH
#define WIN32RegH

#pragma pack(push, 1)
struct TADC
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TAFIO
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TBKP
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TCRC
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TDAC
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TDMA
{
};
#pragma pack(pop)

#include "WIN32EXTI.h"

#pragma pack(push, 1)
struct TFlash
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TGPIO
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TI2C
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TIWDG
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TPWR
{
};
#pragma pack(pop)

//-----------------------------------------------------------------------------
// RCC registers
//-----------------------------------------------------------------------------

// Clock control register
#pragma pack(push, 1)
struct TRCC_CR
{
	uint32_t HSION : 1;
	uint32_t HSI_RDY : 1;
	uint32_t : 1;
	uint32_t HSITRIM : 5;
	uint32_t HSICAL : 8;
	uint32_t HSE_ON : 1;
	uint32_t HSE_RDY : 1;
	uint32_t HSE_BYP : 1;
	uint32_t CSS_ON : 1;
	uint32_t : 4;
	uint32_t PLLON : 1;
	uint32_t PLL_RDY : 1;
	uint32_t : 6;
};
#pragma pack(pop)

// Clock configuration register
#pragma pack(push, 1)
struct TRCC_CFGR
{
	uint32_t USB_PRE : 1;
	uint32_t SW : 2;
	uint32_t SWS : 2;
	uint32_t HPRE : 4;
	uint32_t PPRE1 : 3;
	uint32_t PPRE2 : 3;
	uint32_t ADC_PRE : 2;
	uint32_t PLL_SRC : 1;
	uint32_t PLL_XTPRE : 1;
	uint32_t PLLMUL : 4;
	uint32_t : 1;
	uint32_t MCO: 3;
	uint32_t : 5;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TRCC
{
	TRCC_CR CR;
	TRCC_CFGR CFGR;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TRTC
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TReserved
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TSDIO
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TSPI
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TSPI_I2S
{
};
#pragma pack(pop)

#include "WIN32TIM.h"
#include "WIN32USART.h"
#include "WIN32USB.h"

#pragma pack(push, 1)
struct TUSB_CAN
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TWWDG
{
};
#pragma pack(pop)


#pragma pack(push, 1)
struct TbxCAN
{
};
#pragma pack(pop)


#define SPACE(start, end, type, name) type name; unsigned char _SPACE_TO_##end[end + 1 - start - sizeof(type)];

//------------------------------------------------------------------------------
// WIN32F10X
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TWIN32F10XReg
{
	SPACE(0x40000000, 0x400003FF, TTIM, TIM2)				// timer
	SPACE(0x40000400, 0x400007FF, TTIM, TIM3)				// timer
	SPACE(0x40000800, 0x40000BFF, TTIM, TIM4)				// timer
	SPACE(0x40000C00, 0x40000FFF, TTIM, TIM5)				// timer
	SPACE(0x40001000, 0x400013FF, TTIM, TIM6)				// timer
	SPACE(0x40001400, 0x400017FF, TTIM, TIM7)				// timer
	SPACE(0x40001800, 0x400027FF, TReserved, Reserved1)		// Reserved
	SPACE(0x40002800, 0x40002BFF, TRTC, RTC)				// RTC
	SPACE(0x40002C00, 0x40002FFF, TWWDG, WWDG)				// Window watchdog
	SPACE(0x40003000, 0x400033FF, TIWDG, IWDG)				// Independent watchdog
	SPACE(0x40003400, 0x400037FF, TReserved, Reserved2)		// Reserved
	SPACE(0x40003800, 0x40003BFF, TSPI_I2S, SPI2_I2S)		// SPI2/I2S
	SPACE(0x40003C00, 0x40003FFF, TSPI_I2S, SPI3_I2S)		// SPI3/I2S
	SPACE(0x40004000, 0x400043FF, TReserved, Reserved3)		// Reserved
	SPACE(0x40004400, 0x400047FF, TUSART, USART2)			// USART2
	SPACE(0x40004800, 0x40004BFF, TUSART, USART3)			// USART3
	SPACE(0x40004C00, 0x40004FFF, TUSART, UART4)			// UART4
	SPACE(0x40005000, 0x400053FF, TUSART, UART5)			// UART5
	SPACE(0x40005400, 0x400057FF, TI2C, I2C1)				// I2C1
	SPACE(0x40005800, 0x40005BFF, TI2C, I2C2)				// I2C2
	SPACE(0x40005C00, 0x40005FFF, TUSB, USB)				// USB device FS registers
	SPACE(0x40006000, 0x400063FF, TUSB_CAN, USB_CAN)		// Shared USB/CAN SRAM 512 bytes
	SPACE(0x40006400, 0x400067FF, TbxCAN, bxCAN)			// bxCAN
	SPACE(0x40006800, 0x40006BFF, TReserved, Reserved4)		// Reserved
	SPACE(0x40006C00, 0x40006FFF, TBKP, BKP)				// Backup registers
	SPACE(0x40007000, 0x400073FF, TPWR, PWR)				// Power control
	SPACE(0x40007400, 0x400077FF, TDAC, DAC)				// DAC
	SPACE(0x40007800, 0x4000FFFF, TReserved, Reserved5)		// Reserved
	SPACE(0x40010000, 0x400103FF, TAFIO, AFIO)				// AFIO
	SPACE(0x40010400, 0x400107FF, TEXTI, EXTI)				// EXTI
	SPACE(0x40010800, 0x40010BFF, TGPIO, GPIOA)				// GPIO Port A
	SPACE(0x40010C00, 0x40010FFF, TGPIO, GPIOB)				// GPIO Port B
	SPACE(0x40011000, 0x400113FF, TGPIO, GPIOC)				// GPIO Port C
	SPACE(0x40011400, 0x400117FF, TGPIO, GPIOD)				// GPIO Port D
	SPACE(0x40011800, 0x40011BFF, TGPIO, GPIOE)				// GPIO Port E
	SPACE(0x40011C00, 0x40011FFF, TGPIO, GPIOF)				// GPIO Port F
	SPACE(0x40012000, 0x400123FF, TGPIO, GPIOG)				// GPIO Port G
	SPACE(0x40012400, 0x400127FF, TADC, ADC1)				// ADC1
	SPACE(0x40012800, 0x40012BFF, TADC, ADC2)				// ADC2
	SPACE(0x40012C00, 0x40012FFF, TTIM, TIM1)				// timer
	SPACE(0x40013000, 0x400133FF, TSPI, SPI1)				// SPI1
	SPACE(0x40013400, 0x400137FF, TTIM, TIM8)				// timer
	SPACE(0x40013800, 0x40013BFF, TUSART, USART1)			// USART1
	SPACE(0x40013C00, 0x40013FFF, TADC, ADC3)				// ADC3
	SPACE(0x40014000, 0x40017FFF, TReserved, Reserved6)		// Reserved
	SPACE(0x40018000, 0x400183FF, TSDIO, SDIO)				// SDIO
	SPACE(0x40018400, 0x4001FFFF, TReserved, Reserved7)		// Reserved
	SPACE(0x40020000, 0x400203FF, TDMA, DMA1)				// DMA1
	SPACE(0x40020400, 0x400207FF, TDMA, DMA2)				// DMA2
	SPACE(0x40020800, 0x40020FFF, TReserved, Reserved8)		// Reserved
	SPACE(0x40021000, 0x400213FF, TRCC, RCC)				// Reset and clock control
	SPACE(0x40021400, 0x40021FFF, TReserved, Reserved9)		// Reserved
	SPACE(0x40022000, 0x40022FFF, TFlash, Flash)			// Flash memory interface
	SPACE(0x40023000, 0x400233FF, TCRC, CRC)				// CRC
	SPACE(0x40023400, 0x40023FFF, TReserved, Reserved10)	// Reserved
};
#pragma pack(pop)

#define INT_BASE_NO					16

#define INT_NO_OF_WWDG				0		// Window watchdog interrupt 0x0000_0040
#define INT_NO_OF_PVD				1		// PVD through EXTI Line detection interrupt 0x0000_0044
#define INT_NO_OF_TAMPER			2		// Tamper interrupt 0x0000_0048
#define INT_NO_OF_RTC				3		// RTC global interrupt 0x0000_004C
#define INT_NO_OF_FLASH				4		// Flash global interrupt 0x0000_0050
#define INT_NO_OF_RCC				5		// RCC global interrupt 0x0000_0054
#define INT_NO_OF_EXTI0				6		// EXTI Line0 interrupt 0x0000_0058
#define INT_NO_OF_EXTI1				7		// EXTI Line1 interrupt 0x0000_005C
#define INT_NO_OF_EXTI2				8		// EXTI Line2 interrupt 0x0000_0060
#define INT_NO_OF_EXTI3				9		// EXTI Line3 interrupt 0x0000_0064
#define INT_NO_OF_EXTI4				10		// EXTI Line4 interrupt 0x0000_0068
#define INT_NO_OF_DMA1_Channel1		11		// DMA1 Channel1 global interrupt 0x0000_006C
#define INT_NO_OF_DMA1_Channel2		12		// DMA1 Channel2 global interrupt 0x0000_0070
#define INT_NO_OF_DMA1_Channel3		13		// DMA1 Channel3 global interrupt 0x0000_0074
#define INT_NO_OF_DMA1_Channel4		14		// DMA1 Channel4 global interrupt 0x0000_0078
#define INT_NO_OF_DMA1_Channel5		15		// DMA1 Channel5 global interrupt 0x0000_007C
#define INT_NO_OF_DMA1_Channel6		16		// DMA1 Channel6 global interrupt 0x0000_0080
#define INT_NO_OF_DMA1_Channel7		17		// DMA1 Channel7 global interrupt 0x0000_0084
#define INT_NO_OF_ADC1_2			18		// ADC1 and ADC2 global interrupt 0x0000_0088
#define INT_NO_OF_USB_HP_CAN_TX		19		// USB High Priority or CAN TX interrupts 0x0000_008C
#define INT_NO_OF_USB_LP_CAN_RX0	20		// USB Low Priority or CAN RX0 interrupts 0x0000_0090
#define INT_NO_OF_CAN_RX1			21		// CAN RX1 interrupt 0x0000_0094
#define INT_NO_OF_CAN_SCE			22		// CAN SCE interrupt 0x0000_0098
#define INT_NO_OF_EXTI9_5			23		// EXTI Line[9:5] interrupts 0x0000_009C
#define INT_NO_OF_TIM1_BRK			24		// TIM1 Break interrupt 0x0000_00A0
#define INT_NO_OF_TIM1_UP			25		// TIM1 Update interrupt 0x0000_00A4
#define INT_NO_OF_TIM1_TRG_COM		26		// TIM1 Trigger and Commutation interrupts 0x0000_00A8
#define INT_NO_OF_TIM1_CC			27		// TIM1 Capture Compare interrupt 0x0000_00AC
#define INT_NO_OF_TIM2				28		// TIM2 global interrupt 0x0000_00B0
#define INT_NO_OF_TIM3				29		// TIM3 global interrupt 0x0000_00B4
#define INT_NO_OF_TIM4				30		// TIM4 global interrupt 0x0000_00B8
#define INT_NO_OF_I2C1_EV			31		// I2C1 event interrupt 0x0000_00BC
#define INT_NO_OF_I2C1_ER			32		// I2C1 error interrupt 0x0000_00C0
#define INT_NO_OF_I2C2_EV			33		// I2C2 event interrupt 0x0000_00C4
#define INT_NO_OF_I2C2_ER			34		// I2C2 error interrupt 0x0000_00C8
#define INT_NO_OF_SPI1				35		// SPI1 global interrupt 0x0000_00CC
#define INT_NO_OF_SPI2				36		// SPI2 global interrupt 0x0000_00D0
#define INT_NO_OF_USART1			37		// USART1 global interrupt 0x0000_00D4
#define INT_NO_OF_USART2			38		// USART2 global interrupt 0x0000_00D8
#define INT_NO_OF_USART3			39		// USART3 global interrupt 0x0000_00DC
#define INT_NO_OF_EXTI15_10			40		// EXTI Line[15:10] interrupts 0x0000_00E0
#define INT_NO_OF_RTCAlarm			41		// RTC alarm through EXTI line interrupt 0x0000_00E4
#define INT_NO_OF_USBWakeup			42		// USB wakeup from suspend through EXTI line interrupt 0x0000_00E8
#define INT_NO_OF_TIM8_BRK			43		// TIM8 Break interrupt 0x0000_00EC
#define INT_NO_OF_TIM8_UP			44		// TIM8 Update interrupt 0x0000_00F0
#define INT_NO_OF_TIM8_TRG_COM		45		// TIM8 Trigger and Commutation interrupts 0x0000_00F4
#define INT_NO_OF_TIM8_CC			46		// TIM8 Capture Compare interrupt 0x0000_00F8
#define INT_NO_OF_ADC3				47		// ADC3 global interrupt 0x0000_00FC
#define INT_NO_OF_FSMC				48		// FSMC global interrupt 0x0000_0100
#define INT_NO_OF_SDIO				49		// SDIO global interrupt 0x0000_0104
#define INT_NO_OF_TIM5				50		// TIM5 global interrupt 0x0000_0108
#define INT_NO_OF_SPI3				51		// SPI3 global interrupt 0x0000_010C
#define INT_NO_OF_UART4				52		// UART4 global interrupt 0x0000_0110
#define INT_NO_OF_UART5				53		// UART5 global interrupt 0x0000_0114
#define INT_NO_OF_TIM6				54		// TIM6 global interrupt 0x0000_0118
#define INT_NO_OF_TIM7				55		// TIM7 global interrupt 0x0000_011C
#define INT_NO_OF_DMA2_Channel1		56		// DMA2 Channel1 global interrupt 0x0000_0120
#define INT_NO_OF_DMA2_Channel2		57		// DMA2 Channel2 global interrupt 0x0000_0124
#define INT_NO_OF_DMA2_Channel3		58		// DMA2 Channel3 global interrupt 0x0000_0128
#define INT_NO_OF_DMA2_Channel4_5	59		// DMA2 Channel4 and DMA2 Channel5 global interrupts 0x0000_012C

//---------------------------------------------------------------------------
#endif // WIN32RegH
