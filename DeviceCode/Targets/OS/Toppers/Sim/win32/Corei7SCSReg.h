//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010 Core-s
//------------------------------------------------------------------------------
// $Id: Corei7SCSReg.h 24 2010-05-11 09:48:31Z nagasima $
#ifndef Corei7SCS
#define Corei7SCS

// Interrupt Controller Type Register

#pragma pack(push, 1)
struct TICTR_INTLINESNUM
{
	uint32_t INTLINESNUM : 5;
	uint32_t : 11;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TICTR
{
	uint32_t Reserved0;
	TICTR_INTLINESNUM INTLINESNUM;
};
#pragma pack(pop)

// SystemTick

// SysTick Control and Status Register
#pragma pack(push, 1)
struct TSysTick_CSR
{
	uint32_t ENABLE : 1;
	uint32_t TICKINT : 1;
	uint32_t CLKSOURCE : 1;
	uint32_t : 13;
	uint32_t COUNTFLAG : 1;
	uint32_t : 15;
};
#pragma pack(pop)

// SysTick Reload Value Register
#pragma pack(push, 1)
struct TSysTick_RELOAD
{
	uint32_t RELOAD : 24;
	uint32_t : 8;
};
#pragma pack(pop)

// SysTick Current Value Register
#pragma pack(push, 1)
struct TSysTick_CURRENT
{
	uint32_t CURRENT : 24;
	uint32_t : 8;
};
#pragma pack(pop)

// SysTick Calibration Value Register
#pragma pack(push, 1)
struct TSysTick_CALIB
{
	uint32_t TENMS : 24;
	uint32_t : 6;
	uint32_t SKEW : 1;
	uint32_t NOREF : 1;
};
#pragma pack(pop)

// SystemTick
#pragma pack(push, 1)
struct TSysTick
{
	TSysTick_CSR CSR;
	TSysTick_RELOAD RELOAD;
	TSysTick_CURRENT CURRENT;
	TSysTick_CALIB CALIB;
};
#pragma pack(pop)

// Nested Vectored Interrupt Controller
#pragma pack(push, 1)
struct TNVIC
{
	uint32_t ISER[2];
	uint32_t RESERVED0[30];
	uint32_t ICER[2];
	uint32_t RESERVED1[30];
	uint32_t ISPR[2];
	uint32_t RESERVED2[30];
	uint32_t ICPR[2];
	uint32_t RESERVED3[30];
	uint32_t IABR[2];
	uint32_t RESERVED4[62];
	uint32_t IPR[11];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TSCB
{
	uint32_t CPUID;			// CPUID Base Register
	uint32_t ICSR;
	uint32_t VTOR;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint32_t SHPR[3];
	uint32_t SHCSR;
	uint32_t CFSR;
	uint32_t HFSR;
	uint32_t DFSR;
	uint32_t MMFAR;
	uint32_t BFAR;
	uint32_t AFSR;
};
#pragma pack(pop)

#define SPACE(start, end, type, name) type name; unsigned char _SPACE_TO_##end[end + 1 - start - sizeof(type)];

//------------------------------------------------------------------------------
// WIN32F10X
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TCorei7SCSReg
{
	SPACE(0xE000E000, 0xE000E00F, TICTR, ICTR);				// Interrupt Controller Type Register
	SPACE(0xE000E010, 0xE000E0FF, TSysTick, SysTick)		// SysTick Control and Status Register
	SPACE(0xE000E100, 0xE000ECFF, TNVIC, NVIC)				// Nested vectored interrupt controller
	SPACE(0xE000ED00, 0xE000EFFF, TSCB, SCB)				// CPUID Base Register
};
#pragma pack(pop)

//---------------------------------------------------------------------------
#endif // Corei7SCS
