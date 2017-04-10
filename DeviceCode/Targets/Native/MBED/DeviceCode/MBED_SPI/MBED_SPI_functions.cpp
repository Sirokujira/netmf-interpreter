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
//  Portions Copyright (c) Kentaro Sekimoto All rights reserved.
//
////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
//#include "MBED_SPI.h"
#include "mbed.h"
#include "pinmap.h"
#include "PinNames.h"
#include "PeripheralNames.h"
#include "rspi_iodefine.h"

#define DEBUG_SPI
#define NUM_OF_SPI  3
#define TIMEOUT 10000

static const PinMap PinMap_SPI_SCLK[] = {
    {P10_12, SPI_0, 4},
    {P11_12, SPI_1, 2},
    {P8_3  , SPI_2, 3},
    {NC    , NC   , 0}
};

static const PinMap PinMap_SPI_SSEL[] = {
    {P10_13, SPI_0, 4},
    {P11_13, SPI_1, 2},
    {P8_4  , SPI_2, 3},
    {NC    , NC   , 0}
};

static const PinMap PinMap_SPI_MOSI[] = {
    {P10_14, SPI_0, 4},
    {P11_14, SPI_1, 2},
    {P8_5  , SPI_2, 3},
    {NC    , NC   , 0}
};

static const PinMap PinMap_SPI_MISO[] = {
    {P10_15, SPI_0, 4},
    {P11_15, SPI_1, 2},
    {P8_6  , SPI_2, 3},
    {NC    , NC   , 0}
};

PinName MOSI[NUM_OF_SPI] = {P10_14, P11_14, P8_5};
PinName MISO[NUM_OF_SPI] = {P10_15, P11_15, P8_6};
PinName SCLK[NUM_OF_SPI] = {P10_12, P11_12, P8_3};

static const struct st_rspi *RSPI[] = RSPI_ADDRESS_LIST;
spi_t spi_obj[NUM_OF_SPI];

static inline void spi_disable(spi_t *obj);
static inline void spi_enable(spi_t *obj);
static inline int spi_readable(spi_t *obj);
static inline void spi_write(spi_t *obj, int value);
static inline int spi_read(spi_t *obj);

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel) {
    // determine the SPI to use
    volatile uint8_t dummy;
    uint32_t spi_mosi = pinmap_peripheral(mosi, PinMap_SPI_MOSI);
    uint32_t spi_miso = pinmap_peripheral(miso, PinMap_SPI_MISO);
    uint32_t spi_sclk = pinmap_peripheral(sclk, PinMap_SPI_SCLK);
    uint32_t spi_ssel = pinmap_peripheral(ssel, PinMap_SPI_SSEL);
    uint32_t spi_data = pinmap_merge(spi_mosi, spi_miso);
    uint32_t spi_cntl = pinmap_merge(spi_sclk, spi_ssel);
    uint32_t spi      = pinmap_merge(spi_data, spi_cntl);

   // MBED_ASSERT((int)spi != NC);

    obj->spi = (struct st_rspi *)RSPI[spi];

    // enable power and clocking
    switch (spi) {
        case SPI_0: CPGSTBCR10 &= ~(0x80); break;
        case SPI_1: CPGSTBCR10 &= ~(0x40); break;
        case SPI_2: CPGSTBCR10 &= ~(0x20); break;
    }
    dummy = CPGSTBCR10;

    obj->spi->SPCR   = 0x00;  // CTRL to 0
    obj->spi->SPSCR  = 0x00;  // no sequential operation
    obj->spi->SSLP   = 0x00;  // SSL 'L' active
    obj->spi->SPDCR  = 0x20;  // byte access
    obj->spi->SPCKD  = 0x00;  // SSL -> enable CLK delay : 1RSPCK
    obj->spi->SSLND  = 0x00;  // CLK end -> SSL neg delay : 1RSPCK
    obj->spi->SPND   = 0x00;  // delay between CMD : 1RSPCK + 2P1CLK
    obj->spi->SPPCR  = 0x20;  // MOSI Idle fixed value equals 0
    obj->spi->SPBFCR = 0xf0;  // and set trigger count: read 1, write 1
    obj->spi->SPBFCR = 0x30;  // and reset buffer

    // set default format and frequency
    if ((int)ssel == NC) {
        spi_format(obj, 8, 0, 0);  // 8 bits, mode 0, master
    } else {
        spi_format(obj, 8, 0, 1);  // 8 bits, mode 0, slave
    }
    spi_frequency(obj, 1000000);

    // pin out the spi pins
    pinmap_pinout(mosi, PinMap_SPI_MOSI);
    pinmap_pinout(miso, PinMap_SPI_MISO);
    pinmap_pinout(sclk, PinMap_SPI_SCLK);
    if ((int)ssel != NC) {
        pinmap_pinout(ssel, PinMap_SPI_SSEL);
    }
}

void spi_free(spi_t *obj) {}

void spi_format(spi_t *obj, int bits, int mode, int slave) {
    int      DSS;      // DSS (data select size)
    int      polarity  = (mode & 0x2) ? 1 : 0;
    int      phase     = (mode & 0x1) ? 1 : 0;
    uint16_t tmp       = 0;
    uint16_t mask      = 0xf03;
    uint8_t  splw;

    switch (mode) {
        case 0:
        case 1:
        case 2:
        case 3:
            // Do Nothing
            break;
        default:
            //error("SPI format error");
            lcd_printf("SPI format error");
            return;
    }

    switch (bits) {
        case 8:
            DSS  = 0x7;
            splw = 0x20;
            break;
        case 16:
            DSS  = 0xf;
            splw = 0x40;
            break;
        case 32:
            DSS  = 0x2;
            splw = 0x60;
            break;
        default:
            //error("SPI module don't support other than 8/16/32bits");
            lcd_printf("SPI module don't support other than 8/16/32bits");
            return;
    }
    tmp |= phase;
    tmp |= (polarity << 1);
    tmp |= (DSS << 8);
    obj->bits = bits;

    spi_disable(obj);
    obj->spi->SPCMD0 &= ~mask;
    obj->spi->SPCMD0 |= (mask & tmp);
    obj->spi->SPDCR   = splw;
    if (slave) {
        obj->spi->SPCR &=~(1 << 3);  // MSTR to 0
    } else {
        obj->spi->SPCR |= (1 << 3);  // MSTR to 1
    }
    spi_enable(obj);
}

void spi_frequency(spi_t *obj, int hz) {
    uint32_t  pclk_base;
    uint32_t  div;
    uint32_t  brdv = 0;
    uint16_t  mask = 0x000c;

    /* set PCLK */
    //if (RZ_A1_IsClockMode0() == false) {
    //    pclk_base = CM1_RENESAS_RZ_A1_P1_CLK;
    //} else {
        pclk_base = CM0_RENESAS_RZ_A1_P1_CLK;
    //}

    if ((hz < (pclk_base / 2 / 256 / 8)) || (hz > (pclk_base / 2))) {
        //error("Couldn't setup requested SPI frequency");
        lcd_printf("Couldn't setup requested SPI frequency");
        return;
    }

    div = (pclk_base / hz / 2);
    while (div > 256) {
        div >>= 1;
        brdv++;
    }
    div  -= 1;
    brdv  = (brdv << 2);

    spi_disable(obj);
    obj->spi->SPBR = div;
    obj->spi->SPCMD0 &= ~mask;
    obj->spi->SPCMD0 |= (mask & brdv);
    spi_enable(obj);
}

static inline void spi_disable(spi_t *obj) {
    obj->spi->SPCR &= ~(1 << 6);       // SPE to 0
}

static inline void spi_enable(spi_t *obj) {
    obj->spi->SPCR |=  (1 << 6);       // SPE to 1
}

static inline int spi_readable(spi_t *obj) {
    return obj->spi->SPSR & (1 << 7);  // SPRF
}

static inline int spi_tend(spi_t *obj) {
    return obj->spi->SPSR & (1 << 6);  // TEND
}

static inline void spi_write(spi_t *obj, int value) {
    if (obj->bits == 8) {
        obj->spi->SPDR.UINT8[0]  = (uint8_t)value;
    } else if (obj->bits == 16) {
        obj->spi->SPDR.UINT16[0] = (uint16_t)value;
    } else {
        obj->spi->SPDR.UINT32    = (uint32_t)value;
    }
}

static inline int spi_read(spi_t *obj) {
    int read_data;

    if (obj->bits == 8) {
        read_data = obj->spi->SPDR.UINT8[0];
    } else if (obj->bits == 16) {
        read_data = obj->spi->SPDR.UINT16[0];
    } else {
        read_data = obj->spi->SPDR.UINT32;
    }

    return read_data;
}

int spi_master_write(spi_t *obj, int value) {
    spi_write(obj, value);
    while(!spi_tend(obj));
    return spi_read(obj);
}

int spi_slave_receive(spi_t *obj) {
    return (spi_readable(obj) && !spi_busy(obj)) ? (1) : (0);
}

int spi_slave_read(spi_t *obj) {
    return spi_read(obj);
}

void spi_slave_write(spi_t *obj, int value) {
    spi_write(obj, value);
}

int spi_busy(spi_t *obj) {
    return 0;
}

/*
struct SPI_CONFIGURATION
{
    GPIO_PIN       DeviceCS;
    BOOL           CS_Active;             // False = LOW active,      TRUE = HIGH active
    BOOL           MSK_IDLE;              // False = LOW during idle, TRUE = HIGH during idle
    BOOL           MSK_SampleEdge;        // False = sample falling edge, TRUE = samples on rising
    BOOL           MD_16bits;
    UINT32         Clock_RateKHz;
    UINT32         CS_Setup_uSecs;
    UINT32         CS_Hold_uSecs;
    UINT32         SPI_mod;
    GPIO_FLAG      BusyPin;
};
*/

BOOL CPU_SPI_Initialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    return TRUE;
}

void CPU_SPI_Uninitialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
}

BOOL CPU_SPI_nWrite16_nRead16( const SPI_CONFIGURATION& Configuration, UINT16* Write16, INT32 WriteCount, UINT16* Read16, INT32 ReadCount, INT32 ReadStartOffset )
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    if (!CPU_SPI_Xaction_Start(Configuration))
        return FALSE;
    SPI_XACTION_16 Transaction;
    Transaction.Read16          = Read16;
    Transaction.ReadCount       = ReadCount;
    Transaction.ReadStartOffset = ReadStartOffset;
    Transaction.Write16         = Write16;
    Transaction.WriteCount      = WriteCount;
    Transaction.SPI_mod         = Configuration.SPI_mod;
    if (!CPU_SPI_Xaction_nWrite16_nRead16(Transaction))
            return FALSE;
    return CPU_SPI_Xaction_Stop(Configuration);
}

BOOL CPU_SPI_nWrite8_nRead8( const SPI_CONFIGURATION& Configuration, UINT8* Write8, INT32 WriteCount, UINT8* Read8, INT32 ReadCount, INT32 ReadStartOffset )
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    if (!CPU_SPI_Xaction_Start(Configuration))
        return FALSE;
    SPI_XACTION_8 Transaction;
    Transaction.Read8           = Read8;
    Transaction.ReadCount       = ReadCount;
    Transaction.ReadStartOffset = ReadStartOffset;
    Transaction.Write8          = Write8;
    Transaction.WriteCount      = WriteCount;
    Transaction.SPI_mod         = Configuration.SPI_mod;
    if (!CPU_SPI_Xaction_nWrite8_nRead8(Transaction))
        return FALSE;
    return CPU_SPI_Xaction_Stop(Configuration);
}

BOOL CPU_SPI_Xaction_Start(const SPI_CONFIGURATION& Configuration)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    spi_t *obj;
    UINT32 ch = Configuration.SPI_mod;
    UINT32 bits = (Configuration.MD_16bits!=0)? 16:8;
    UINT32 mode = 0;
    UINT32 slave = 0;
    obj = (spi_t *)&spi_obj[ch];
    spi_init(obj, MOSI[ch], MISO[ch], SCLK[ch], (PinName)NC);
    spi_format(obj, bits, mode, slave);
    spi_frequency(obj, Configuration.Clock_RateKHz * 1000);
    CPU_GPIO_EnableOutputPin(Configuration.DeviceCS, Configuration.CS_Active);
    if (Configuration.CS_Setup_uSecs) {
        HAL_Time_Sleep_MicroSeconds_InterruptEnabled(Configuration.CS_Setup_uSecs);
    }
    return TRUE;
}

BOOL CPU_SPI_Xaction_Stop(const SPI_CONFIGURATION& Configuration)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();

    if(Configuration.CS_Hold_uSecs) {
        HAL_Time_Sleep_MicroSeconds_InterruptEnabled(Configuration.CS_Hold_uSecs);
    }
    CPU_GPIO_SetPinState(Configuration.DeviceCS, !Configuration.CS_Active);
    return TRUE;
}

BOOL CPU_SPI_Xaction_nWrite16_nRead16(SPI_XACTION_16& Transaction)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    spi_t *obj;
    UINT32 timeout;
    UINT32 spi_mod = Transaction.SPI_mod;
    if (spi_mod >= NUM_OF_SPI)
        return FALSE;

    obj = (spi_t *)&spi_obj[spi_mod];
    UINT16* wbuf = Transaction.Write16;
    UINT16* rbuf = Transaction.Read16;
    INT32 wcnt = Transaction.WriteCount;
    INT32 rcnt = Transaction.ReadCount;
    INT32 roff = Transaction.ReadStartOffset;
    INT32 i = 0;
    while (i < wcnt) {
        obj->spi->SPDR.UINT16[0] = *wbuf++;
        timeout = TIMEOUT;
        while(!spi_tend(obj)) {
            if (-- timeout == 0)
                break;
        }
        if (rcnt > 0) {
            UINT16 value = obj->spi->SPDR.UINT16[0];
            if ((i >= roff) && (i < roff + rcnt)) {
                *rbuf++ = value;
            }
        }
        i+=2;
    }
    while (i < roff + rcnt) {
        obj->spi->SPDR.UINT16[0] = 0xffff;
        timeout = TIMEOUT;
        while(!spi_tend(obj)) {
            if (-- timeout == 0)
                break;
        }
        UINT16 value = obj->spi->SPDR.UINT16[0];
        if ((i >= roff) && (i < roff + rcnt)) {
            *rbuf++ = value;
        }
        i+=2;
    }
    return TRUE;
}

BOOL CPU_SPI_Xaction_nWrite8_nRead8(SPI_XACTION_8& Transaction)
{
    NATIVE_PROFILE_HAL_PROCESSOR_SPI();
    spi_t *obj;
    UINT32 timeout;
    UINT32 spi_mod = Transaction.SPI_mod;
    if (spi_mod >= NUM_OF_SPI)
        return FALSE;

    obj = (spi_t *)&spi_obj[spi_mod];
    UINT8* wbuf = Transaction.Write8;
    UINT8* rbuf = Transaction.Read8;
    INT32 wcnt = Transaction.WriteCount;
    INT32 rcnt = Transaction.ReadCount;
    INT32 roff = Transaction.ReadStartOffset;
    INT32 i = 0;
    while (i < wcnt) {
        obj->spi->SPDR.UINT8[0] = (UINT8)*wbuf++;
        timeout = TIMEOUT;
        while(!spi_tend(obj)) {
            if (-- timeout == 0)
                break;
        }
        if (rcnt > 0) {
            UINT8 value = obj->spi->SPDR.UINT8[0];
            if ((i >= roff) && (i < roff + rcnt)) {
                *rbuf++ = value;
            }
        }
        i++;
    }
    while (i < roff + rcnt) {
        obj->spi->SPDR.UINT8[0] = (UINT8)0xff;
        timeout = TIMEOUT;
        while(!spi_tend(obj)) {
            if (-- timeout == 0)
                break;
        }
        UINT8 value = obj->spi->SPDR.UINT8[0];
        if ((i >= roff) && (i < roff + rcnt)) {
            *rbuf++ = value;
        }
        i++;
    }
    return TRUE;
}

UINT32 CPU_SPI_PortsCount()
{
    return NUM_OF_SPI;
}

void CPU_SPI_GetPins(UINT32 spi_mod, GPIO_PIN& msk, GPIO_PIN& miso, GPIO_PIN& mosi)
{
    if (spi_mod >= NUM_OF_SPI)
        return;
    msk = SCLK[spi_mod];
    miso = MISO[spi_mod];
    mosi = MOSI[spi_mod];
}
