////////////////////////////////////////////////////////////////////////////
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//  Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#ifndef _MBED_H_
#define _MBED_H_ 1

#include "us_ticker_api.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef BOOL
typedef unsigned int BOOL;
#endif

#define VL(x) (*(volatile unsigned long *)(x))
#define VS(x) (*(volatile unsigned short *)(x))
#define VB(x) (*(volatile unsigned char *)(x))

//////////////////////////////////////////////////////////////////////////////
// Interrupt Controller
//
struct MBED_VIC
{
};
//
// Interrupt Controller
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TIMERS
//
struct MBED_TIMER
{
    static const UINT32 c_Timer_0 = 0;
    static const UINT32 c_Timer_1 = 1;
    static const UINT32 c_Timer_2 = 2;
    static const UINT32 c_Timer_3 = 3;
};
//
// TIMER
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// GP I/O
//

#define GPIO_PORT_NUM   19
#define GPIO_PIN_NUM    (GPIO_PORT_NUM * 8)

#define MBED_MAX_GPIO_PINS    152
#define MBED_MAX_GPIO_PORTS    (MBED_MAX_GPIO_PINS/8)

#define GPIO_PORT(pin)  (pin >> 3)
#define GPIO_MASK(pin)  (1 << (pin & 7))

#define _PXXPFS(port, bit)  ((volatile UINT8 *)(0x0008c140 + port*8 + bit))
#define _PDR(port)  (*(volatile UINT8 *)(0x0008c000 + port))
#define _PODR(port) (*(volatile UINT8 *)(0x0008c020 + port))
#define _PIDR(port) (*(volatile UINT8 *)(0x0008c040 + port))
#define _PMR(port)  (*(volatile UINT8 *)(0x0008c060 + port))
#define _ODR0(port) (*(volatile UINT8 *)(0x0008c080 + port*2))
#define _ODR1(port) (*(volatile UINT8 *)(0x0008c081 + port*2))
#define _PCR(port)  (*(volatile UINT8 *)(0x0008c0C0 + port))
#define _DSCR(port) (*(volatile UINT8 *)(0x0008c0E0 + port))
#define _MPC(pin)   (*(volatile UINT8 *)(0x0008c140 + pin))

struct MBED_GPIO
{
    static const UINT32 c_Pin_None = 0xFFFFFFFF;

    static const UINT8 P00 = 0;
    static const UINT8 P01 = 1;
    static const UINT8 P02 = 2;
    static const UINT8 P03 = 3;
    static const UINT8 P04 = 4;
    static const UINT8 P05 = 5;
    static const UINT8 P06 = 6;
    static const UINT8 P07 = 7;

    static const UINT8 P10 = 8;
    static const UINT8 P11 = 9;
    static const UINT8 P12 = 10;
    static const UINT8 P13 = 11;
    static const UINT8 P14 = 12;
    static const UINT8 P15 = 13;
    static const UINT8 P16 = 14;
    static const UINT8 P17 = 15;

    static const UINT8 P20 = 16;
    static const UINT8 P21 = 17;
    static const UINT8 P22 = 18;
    static const UINT8 P23 = 19;
    static const UINT8 P24 = 20;
    static const UINT8 P25 = 21;
    static const UINT8 P26 = 22;
    static const UINT8 P27 = 23;

    static const UINT8 P30 = 24;
    static const UINT8 P31 = 25;
    static const UINT8 P32 = 26;
    static const UINT8 P33 = 27;
    static const UINT8 P34 = 28;
    static const UINT8 P35 = 29;
    static const UINT8 P36 = 30;
    static const UINT8 P37 = 31;

    static const UINT8 P40 = 32;
    static const UINT8 P41 = 33;
    static const UINT8 P42 = 34;
    static const UINT8 P43 = 35;
    static const UINT8 P44 = 36;
    static const UINT8 P45 = 37;
    static const UINT8 P46 = 38;
    static const UINT8 P47 = 39;

    static const UINT8 P50 = 40;
    static const UINT8 P51 = 41;
    static const UINT8 P52 = 42;
    static const UINT8 P53 = 43;
    static const UINT8 P54 = 44;
    static const UINT8 P55 = 45;
    static const UINT8 P56 = 46;
    static const UINT8 P57 = 47;

    static const UINT8 P60 = 48;
    static const UINT8 P61 = 49;
    static const UINT8 P62 = 50;
    static const UINT8 P63 = 51;
    static const UINT8 P64 = 52;
    static const UINT8 P65 = 53;
    static const UINT8 P66 = 54;
    static const UINT8 P67 = 55;

    static const UINT8 P70 = 56;
    static const UINT8 P71 = 57;
    static const UINT8 P72 = 58;
    static const UINT8 P73 = 59;
    static const UINT8 P74 = 60;
    static const UINT8 P75 = 61;
    static const UINT8 P76 = 62;
    static const UINT8 P77 = 63;

    static const UINT8 P80 = 64;
    static const UINT8 P81 = 65;
    static const UINT8 P82 = 66;
    static const UINT8 P83 = 67;
    static const UINT8 P84 = 68;
    static const UINT8 P85 = 69;
    static const UINT8 P86 = 70;
    static const UINT8 P87 = 71;

    static const UINT8 P90 = 72;
    static const UINT8 P91 = 73;
    static const UINT8 P92 = 74;
    static const UINT8 P93 = 75;
    static const UINT8 P94 = 76;
    static const UINT8 P95 = 77;
    static const UINT8 P96 = 78;
    static const UINT8 P97 = 79;

    static const UINT8 PA0 = 80;
    static const UINT8 PA1 = 81;
    static const UINT8 PA2 = 82;
    static const UINT8 PA3 = 83;
    static const UINT8 PA4 = 84;
    static const UINT8 PA5 = 85;
    static const UINT8 PA6 = 86;
    static const UINT8 PA7 = 87;

    static const UINT8 PB0 = 88;
    static const UINT8 PB1 = 89;
    static const UINT8 PB2 = 90;
    static const UINT8 PB3 = 91;
    static const UINT8 PB4 = 92;
    static const UINT8 PB5 = 93;
    static const UINT8 PB6 = 94;
    static const UINT8 PB7 = 95;

    static const UINT8 PC0 = 96;
    static const UINT8 PC1 = 97;
    static const UINT8 PC2 = 98;
    static const UINT8 PC3 = 99;
    static const UINT8 PC4 = 100;
    static const UINT8 PC5 = 101;
    static const UINT8 PC6 = 102;
    static const UINT8 PC7 = 103;

    static const UINT8 PD0 = 104;
    static const UINT8 PD1 = 105;
    static const UINT8 PD2 = 106;
    static const UINT8 PD3 = 107;
    static const UINT8 PD4 = 108;
    static const UINT8 PD5 = 109;
    static const UINT8 PD6 = 110;
    static const UINT8 PD7 = 111;

    static const UINT8 PE0 = 112;
    static const UINT8 PE1 = 113;
    static const UINT8 PE2 = 114;
    static const UINT8 PE3 = 115;
    static const UINT8 PE4 = 116;
    static const UINT8 PE5 = 117;
    static const UINT8 PE6 = 118;
    static const UINT8 PE7 = 119;

    static const UINT8 PF0 = 120;
    static const UINT8 PF1 = 121;
    static const UINT8 PF2 = 122;
    static const UINT8 PF3 = 123;
    static const UINT8 PF4 = 124;
    static const UINT8 PF5 = 125;
    static const UINT8 PF6 = 126;
    static const UINT8 PF7 = 127;

    static const UINT8 PG0 = 128;
    static const UINT8 PG1 = 129;
    static const UINT8 PG2 = 130;
    static const UINT8 PG3 = 131;
    static const UINT8 PG4 = 132;
    static const UINT8 PG5 = 132;
    static const UINT8 PG6 = 134;
    static const UINT8 PG7 = 135;

#if 0
    // PHx pin is not defined.
    static const UINT8 PH0 = 136;
    static const UINT8 PH1 = 137;
    static const UINT8 PH2 = 138;
    static const UINT8 PH3 = 139;
    static const UINT8 PH4 = 140;
    static const UINT8 PH5 = 141;
    static const UINT8 PH6 = 142;
    static const UINT8 PH7 = 143;
#endif

    static const UINT8 PJ0 = 144;
    static const UINT8 PJ1 = 145;
    static const UINT8 PJ2 = 146;
    static const UINT8 PJ3 = 147;
    static const UINT8 PJ4 = 148;
    static const UINT8 PJ5 = 149;
    static const UINT8 PJ6 = 150;
    static const UINT8 PJ7 = 151;
};

//--//

struct MBED_GPIOIRQ
{
};
//
// GP I/O
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// UART
//

struct MBED_USART
{
    static const UINT32 c_MAX_BAUDRATE = 115200;
};
//
// UART
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// SPI
//
//
// SPI
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// I2C
//
struct MBED_I2C
{
    static const UINT8 ICSR2_TDRE = (1 << 7);
    static const UINT8 ICSR2_TEND = (1 << 6);
    static const UINT8 ICSR2_RDRF = (1 << 5);
    static const UINT8 ICSR2_NACKF = (1 << 4);
    static const UINT8 ICSR2_STOP = (1 << 3);
    static const UINT8 ICSR2_START = (1 << 2);
    static const UINT8 ICSR2_AL = (1 << 1);
    static const UINT8 ICSR2_TMOF = (1 << 0);

    static const UINT8 ICIER_TIE = (1 << 7);
    static const UINT8 ICIER_TEIE = (1 << 6);
    static const UINT8 ICIER_RIE = (1 << 5);
    static const UINT8 ICIER_NAKIE = (1 << 4);
    static const UINT8 ICIER_SPIE = (1 << 3);
    static const UINT8 ICIER_STIE = (1 << 2);
    static const UINT8 ICIER_ALIE = (1 << 1);
    static const UINT8 ICIER_TMOIE = (1 << 0);
};
//
// I2C
//////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/

//struct MBED
//{
//};

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// MBED driver
//

struct MBED_Driver
{
};

//extern MBED_Driver g_MBED_Driver;

//
// MBED driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Interrupt Controller driver
//

struct MBED_VIC_Driver
{
};

//
// Interrupt Controller driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// TIMER driver
//

struct MBED_TIMER_Driver
{
    static const UINT32 c_MaxTimers = 2;
    static const UINT16 c_MaxTimerValue = 0xFFFF;
    static const UINT32 c_Timer_System  = 0;
    static const UINT32 c_Timer_Compare = 1;
    static const UINT32 CLOCK_SOURCE_DIV8   = 0;
    static const UINT32 CLOCK_SOURCE_DIV32  = 1;
    static const UINT32 CLOCK_SOURCE_DIV128 = 2;
    static const UINT32 CLOCK_SOURCE_DIV512 = 3;

    static BOOL Initialize(UINT32 Timer, HAL_CALLBACK_FPN ISR, void* ISR_Param);
    static BOOL Uninitialize(UINT32 Timer);
    static UINT16 ReadCounter(UINT32 Timer);
    static void ForceInterrupt(UINT32 Timer);
    static void SetCompare(UINT32 Timer, UINT16 Compare);
    struct TimerISR {
        HAL_CALLBACK_FPN ISR;
        void *Arg;
        BOOL Configured;
        UINT32 id;
    } m_timers[c_MaxTimers];
};

extern MBED_TIMER_Driver g_MBED_TIMER_Driver;

//
// TIMER driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// System Time driver
//

struct MBED_TIME_Driver
{
    static const UINT32 c_OverflowCheck = 0x80000000;
    UINT64 m_lastRead;
    UINT64 m_nextCompare;

    static BOOL Initialize  ();
    static BOOL Uninitialize();
    static UINT64 CounterValue();
    static void SetCompareValue(UINT64 CompareValue);
    static INT64 TicksToTime(UINT64 Ticks);
    static INT64 CurrentTime();
    static void Sleep_uSec(UINT32 uSec);
    static void Sleep_uSec_Loop(UINT32 uSec);
private:
    static void ISR_Overflow(void* Param);
    static void ISR_Compare(void* Param);
};

extern MBED_TIME_Driver g_MBED_TIME_Driver;

//
// System Time driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// UART driver
//

struct MBED_USART_Driver
{
    static const UINT32 c_COM1 = 0;
    static const UINT32 c_COM2 = 1;
    static const UINT32 c_COM3 = 2;
    static const UINT32 c_COM4 = 3;
    INT8 m_RefFlags[2];

    static BOOL Initialize(int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue);
    static BOOL Uninitialize(int ComPortNum);
    static BOOL TxBufferEmpty(int ComPortNum);
    static void WriteCharToTxBuffer(int ComPortNum, UINT8 c);
    static void TxBufferEmptyInterruptEnable(int ComPortNum, BOOL Enable);
    static BOOL TxBufferEmptyInterruptState(int ComPortNum);
    static void RxBufferFullInterruptEnable(int ComPortNum, BOOL Enable);
    static BOOL RxBufferFullInterruptState(int ComPortNum);
    static BOOL TxHandshakeEnabledState(int comPortNum);
    static void ProtectPins(int ComPortNum, BOOL On);
    static void GetPins(int comPort,  GPIO_PIN& rxPin, GPIO_PIN& txPin,GPIO_PIN& ctsPin, GPIO_PIN& rtsPin);
    static void BaudrateBoundary(int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz);
    static BOOL IsBaudrateSupported(int ComPortNum, UINT32 & BaudrateHz);
    static void UART_IntHandler(void *Param);
    static BOOL IsValidPortNum(int ComPortNum);
};

extern MBED_USART_Driver g_MBED_USART_Driver;

//
// UART driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// GPIO driver
//

#define MBED_GPIO_POLLING_INTERVAL 5000

struct MBED_GPIO_Driver
{
    struct PIN_ISR_DESCRIPTOR
    {
        static const UINT8 c_Flags_Debounce        = 0x01;
        static const UINT8 c_Flags_RequireLowEdge  = 0x02;
        static const UINT8 c_Flags_RequireHighEdge = 0x04;
        static const UINT8 c_Status_AllowLowEdge   = 0x01;
        static const UINT8 c_Status_AllowHighEdge  = 0x02;

        HAL_COMPLETION m_completion;
        GPIO_INTERRUPT_SERVICE_ROUTINE m_isr;
        void *m_param;
        GPIO_PIN m_pin;
        GPIO_INT_EDGE m_intEdge;
        UINT8 m_flags;
        UINT8 m_status;

        static void Fire(void *arg);
    };

    static const UINT8 c_GPIO_ResistorMode  = (1<<RESISTOR_DISABLED) |(1<<RESISTOR_PULLDOWN) | (1<<RESISTOR_PULLUP) ;
    static const UINT8 c_GPIO_InterruptMode = (1<<GPIO_INT_EDGE_LOW) | (1<<GPIO_INT_EDGE_HIGH ) | (1<<GPIO_INT_EDGE_BOTH) | (1<<GPIO_INT_LEVEL_HIGH) | (1<<GPIO_INT_LEVEL_LOW);
    static const UINT32 c_MaxPins = MBED_MAX_GPIO_PINS;
    static const UINT32 c_MaxPorts = MBED_MAX_GPIO_PORTS;
    static const INT32 c_MinDebounceTimeMs = 1;    // 1ms
    static const INT32 c_MaxDebounceTimeMs = 5000;    // 5s

    PIN_ISR_DESCRIPTOR m_PinIsr[c_MaxPins];
    UINT8 m_GPIO_Reserved[c_MaxPins];
    UINT8 m_GPIO_PortLastValues[c_MaxPorts];
    UINT8 m_GPIO_PortReservedMask[c_MaxPorts];
    UINT8 m_GPIO_Driver_Initialized;
    HAL_COMPLETION m_GPIO_Completion;
    UINT32 m_DebounceTicks;
    BOOL m_GPIO_InISR;

    static BOOL Initialize();
    static BOOL Uninitialize();
    static UINT32 Attributes(GPIO_PIN pin);
    static void DisablePin(GPIO_PIN pin, GPIO_RESISTOR resistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction);
    static void EnableOutputPin(GPIO_PIN pin, BOOL initialState);
    static BOOL EnableInputPin(GPIO_PIN pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, void* Param, GPIO_INT_EDGE intEdge, GPIO_RESISTOR resistorState);
    static BOOL GetPinState(GPIO_PIN pin);
    static void SetPinState(GPIO_PIN pin, BOOL pinState);
    static BOOL PinIsBusy(GPIO_PIN pin);
    static BOOL ReservePin(GPIO_PIN pin, BOOL fReserve);
    static UINT32 GetDebounce();
    static BOOL SetDebounce(INT64 debounceTimeMilliseconds);
    static INT32 GetPinCount();
    static void GetPinsMap(UINT8* pins, size_t size);
    static UINT8 GetSupportedResistorModes(GPIO_PIN pin);
    static UINT8 GetSupportedInterruptModes(GPIO_PIN pin);
    static void STUB_ISRVector(GPIO_PIN pin, BOOL PinState, void* Param);
//
    static INT32 GetBitPos(UINT8 val);
    static void UpdatePinValue(GPIO_PIN pin);
    static void EnableInputPolling(GPIO_PIN pin);
    static void DisableInputPolling(GPIO_PIN pin);
    static UINT32 ChkPinChange(void);
    static void ISR(void);
private:
    static void STUB_GPIOISRVector(GPIO_PIN pin, BOOL PinState, void *Param);
};

//extern MBED_GPIO_Driver g_MBED_GPIO_Driver;

//
// GP I/O driver
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// SPI  driver
//

//
// SPI driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// I2C driver
//

struct I2C_HAL_XACTION_UNIT;
struct I2C_HAL_XACTION;
struct I2C_CONFIGURATION;

struct MBED_I2C_Driver
{
    static const UINT8 c_DirectionRead = 1;
    static const UINT8 c_DirectionWrite = 0;
    I2C_HAL_XACTION *m_currentXAction;
    I2C_HAL_XACTION_UNIT *m_currentXActionUnit;
    BOOL m_initialized;

    //--//

    static BOOL Initialize(UINT32 ch);
    static BOOL Uninitialize(UINT32 ch);
    static void MasterXAction_Start(UINT32 ch,I2C_HAL_XACTION *xAction, bool repeatedStart);
    static void MasterXAction_Stop(UINT32 ch);
    static void GetClockRate(UINT32 ch, UINT32 rateKhz, UINT8& clockRate, UINT8& clockRate2);

    static void WriteToSubordinate(UINT32 ch, I2C_HAL_XACTION_UNIT *unit);
    static void ReadFromSubordinate(UINT32 ch, I2C_HAL_XACTION_UNIT *unit);
    static void GetPins(UINT32 ch, GPIO_PIN& scl, GPIO_PIN& sda);
    static void ReadLastByte(UINT32 ch);
    static void StopCondition(UINT32 ch);
    static void Abort(UINT32 ch);

    static void MBED_I2C_ICEEI_ISR(void);
    static void MBED_I2C_ICRXI_ISR(void);
    static void MBED_I2C_ICTXI_ISR(void);
    static void MBED_I2C_ICTEI_ISR(void);
private:
};

//extern MBED_I2C_Driver g_MBED_I2C_Driver;

//
// I2C driver
//////////////////////////////////////////////////////////////////////////////

struct MBED_I2CSW_Driver
{
    static const UINT8 c_DirectionRead = 1;
    static const UINT8 c_DirectionWrite = 0;
    I2C_HAL_XACTION *m_currentXAction;
    I2C_HAL_XACTION_UNIT *m_currentXActionUnit;
    BOOL m_initialized;

    //--//

    static BOOL Initialize();
    static BOOL Uninitialize();
    static void MasterXAction_Start(I2C_HAL_XACTION *xAction, bool repeatedStart);
    static void MasterXAction_Stop();
    static void GetClockRate(UINT32 rateKhz, UINT8& clockRate, UINT8& clockRate2);
    static void WriteToSubordinate(I2C_HAL_XACTION_UNIT *unit);
    static void ReadFromSubordinate(I2C_HAL_XACTION_UNIT *unit);
    static void GetPins(GPIO_PIN& scl, GPIO_PIN& sda);
    static void Abort(void);

private:
};

//////////////////////////////////////////////////////////////////////////////
// Watchdog driver
//

struct MBED_WATCHDOG_Driver

{
};

//extern MBED_WATCHDOG_Driver g_MBED_WATCHDOG_Driver;


//
// Watchdog driver
//////////////////////////////////////////////////////////////////////////////

#endif // _MBED_H_ 1
