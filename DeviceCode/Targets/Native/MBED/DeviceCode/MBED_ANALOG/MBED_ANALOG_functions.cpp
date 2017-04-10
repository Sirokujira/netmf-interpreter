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
#include "analogin_api.h"

#include "cmsis.h"
#include "pinmap.h"

#include "adc_iodefine.h"
#include "cpg_iodefine.h"

#define ANALOGIN_MEDIAN_FILTER      1

#define ADC_12BIT_RANGE             0xFFF

static const PinMap PinMap_ADC[] = {
    {P1_8,  AN0, 1},
    {P1_9,  AN1, 1},
    {P1_10, AN2, 1},
    {P1_11, AN3, 1},
    {P1_12, AN3, 1},
    {P1_13, AN5, 1},
    {P1_14, AN5, 1},
    {P1_15, AN7, 1},
    {NC,    NC,     0}
};

static volatile uint16_t *ADCDR[] = {
    &ADCADDRA,
    &ADCADDRB,
    &ADCADDRC,
    &ADCADDRD,
    &ADCADDRE,
    &ADCADDRF,
    &ADCADDRG,
    &ADCADDRH,
};

#define ADC_RANGE    ADC_12BIT_RANGE

static void MBED_analogin_init(analogin_t *obj, PinName pin)
{
    int i;
    obj->adc = (ADCName)pinmap_peripheral(pin, PinMap_ADC);
    //MBED_ASSERT(obj->adc != (ADCName)NC);

    CPGSTBCR3 &= ~(1 << 1);
    CPGSTBCR6 &= ~(1 << 7);

    // 000_0 000_1 00_00 0_xxx
    // 15: ADFlag 14: IntEn 13: start, [12:9] Triger..0
    //    [8:6] CLK 100 :: 12-bit 1054tclk
    //    [5:3] scanmode 000 :: single mode
    //    [2:0] channel select
    ADCADCSR = 0x01c0 ;

    for (i = 0; i< sizeof(PinMap_ADC)/sizeof(PinMap); i++) {
        pinmap_pinout(PinMap_ADC[i].pin, PinMap_ADC);
    }

    //pinmap_pinout(pin, PinMap_ADC);
}

static inline uint32_t MBED_adc_read(analogin_t *obj) {
    // Select the appropriate channel and start conversion

    ADCADCSR &= 0xfff8;
    ADCADCSR |= (1 << 13 | (obj->adc&0x7));

    // Repeatedly get the sample data until DONE bit
#define nothing
    while ((ADCADCSR & (1 << 15)) == 0 || (ADCADCSR & (1<<13)) != 0) ;

    // clear flag
    ADCADCSR &= ~(1 << 15);

    return ((*(ADCDR[obj->adc]))>>4) & ADC_RANGE; // 12 bit
}

#define NUM_OF_ANALOGIN 8

analogin_t analogin_obj[NUM_OF_ANALOGIN];
PinName ANALOGIN[NUM_OF_ANALOGIN] = {P1_8, P1_9, P1_10, P1_11, P1_12, P1_13, P1_14, P1_15};

BOOL AD_Initialize(ANALOG_CHANNEL channel, INT32 precisionInBits)
{
    analogin_t *obj;
    if (precisionInBits != 12)
        return FALSE;
    if ((UINT32)channel >= NUM_OF_ANALOGIN)
        return FALSE;

    obj = (analogin_t *)&analogin_obj[(UINT32)channel];
    MBED_analogin_init(obj, ANALOGIN[(UINT32)channel]);
    return TRUE;
}

void AD_Uninitialize(ANALOG_CHANNEL channel)
{
}

INT32 AD_Read(ANALOG_CHANNEL channel)
{
    INT32 value32;
    analogin_t *obj;
    obj = (analogin_t *)&analogin_obj[(UINT32)channel];
    value32 = (UINT32)MBED_adc_read(obj);
    return value32;
}

UINT32 AD_ADChannels()
{
    return (UINT32)NUM_OF_ANALOGIN;
}

GPIO_PIN AD_GetPinForChannel(ANALOG_CHANNEL channel)
{
    return (GPIO_PIN)ANALOGIN[(UINT32)channel];
}

BOOL AD_GetAvailablePrecisionsForChannel(ANALOG_CHANNEL channel, INT32* precisions, UINT32& size)
{
    size = 0;
    if (precisions == NULL || (UINT32)channel >= NUM_OF_ANALOGIN)
        return FALSE;
    precisions[0] = 12;
    size = 1;
    return TRUE;
}
