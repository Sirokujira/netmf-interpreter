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
#include "mbed.h"
#include "RaspberryPi2_TouchPanel_Driver.h"

// XL - A0 - P1_8
// YU - A1 - P1_9
// XR - A2 - P1_10
// YD - A3 - P1_11

// XL - P10_0
// YU - P1_1
// XR - P1_0
// YD - P1_12

#define PIN_XL  ((GPIO_PIN)P10_0)
#define PIN_YU  ((GPIO_PIN)P1_1)
#define PIN_XR  ((GPIO_PIN)P1_0)
#define PIN_YD  ((GPIO_PIN)P1_12)
//--//
//#define DEBUG_TOUCHPANEL
struct RaspberryPi2_TouchPanel_Driver g_RaspberryPi2_TouchPanel_Driver;

BOOL RaspberryPi2_TouchPanel_Driver::CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT *pTCP)
{
    INT32   cDisplayWidth  = pTCP->cDisplayWidth;
    INT32   cDisplayHeight = pTCP->cDisplayHeight;
    int CalibrationRadiusX = cDisplayWidth  / 20;
    int CalibrationRadiusY = cDisplayHeight / 20;
    switch (pTCP -> PointNumber)
    {
    case    0:
        pTCP->CalibrationX = cDisplayWidth  / 2;
        pTCP->CalibrationY = cDisplayHeight / 2;
        break;

    case    1:
        pTCP->CalibrationX = CalibrationRadiusX * 2;
        pTCP->CalibrationY = CalibrationRadiusY * 2;
        break;

    case    2:
        pTCP->CalibrationX = CalibrationRadiusX * 2;
        pTCP->CalibrationY = cDisplayHeight - CalibrationRadiusY * 2;
        break;

    case    3:
        pTCP->CalibrationX = cDisplayWidth  - CalibrationRadiusX * 2;
        pTCP->CalibrationY = cDisplayHeight - CalibrationRadiusY * 2;
        break;

    case    4:
        pTCP->CalibrationX = cDisplayWidth - CalibrationRadiusX * 2;
        pTCP->CalibrationY = CalibrationRadiusY * 2;
        break;

    default:
        pTCP->CalibrationX = cDisplayWidth  / 2;
        pTCP->CalibrationY = cDisplayHeight / 2;

        return FALSE;
    }
    return TRUE;
}

HRESULT RaspberryPi2_TouchPanel_Driver::GetDeviceCaps(unsigned int iIndex, void* lpOutput)
{
    if ( lpOutput == NULL )
    {
        return FALSE;
    }
    switch ( iIndex )
    {
    case TOUCH_PANEL_SAMPLE_RATE_ID:
    {
        TOUCH_PANEL_SAMPLE_RATE   *pTSR = (TOUCH_PANEL_SAMPLE_RATE*)lpOutput;

        pTSR->SamplesPerSecondLow       = g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondLow;
        pTSR->SamplesPerSecondHigh      = g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondHigh;
        pTSR->CurrentSampleRateSetting  = g_TouchPanel_Sampling_Settings.SampleRate.CurrentSampleRateSetting;
        pTSR->MaxTimeForMoveEvent_ticks = g_TouchPanel_Sampling_Settings.SampleRate.MaxTimeForMoveEvent_ticks;
    }
    break;

    case TOUCH_PANEL_CALIBRATION_POINT_COUNT_ID:
    {
        TOUCH_PANEL_CALIBRATION_POINT_COUNT *pTCPC = (TOUCH_PANEL_CALIBRATION_POINT_COUNT*)lpOutput;

        pTCPC->flags              = 0;
        pTCPC->cCalibrationPoints = 5;
    }
    break;

    case TOUCH_PANEL_CALIBRATION_POINT_ID:
        return(CalibrationPointGet((TOUCH_PANEL_CALIBRATION_POINT*)lpOutput));

    default:
        return FALSE;
    }
    return TRUE;
}

void RaspberryPi2_TouchPanel_Driver::GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY)
{
    static BOOL stylusDown = FALSE;
    INT32 validReadCount = 0;
    *pTipState = 0;
    *pUnCalX = 0;
    *pUnCalY = 0;
    *pSource = 0;

    if (g_RaspberryPi2_TouchPanel_Driver.m_global_inX >= 3700)
        validReadCount = 0;
    else
        validReadCount = 1;
    if (stylusDown)
        *pTipState |= TouchSamplePreviousDownFlag;
    if ((validReadCount == 1) &&
        (g_RaspberryPi2_TouchPanel_Driver.m_global_touch == 1)) {
        *pTipState |= TouchSampleValidFlag;
        *pUnCalX = g_RaspberryPi2_TouchPanel_Driver.m_global_inY;  // intentionally changed x <-> y
        *pUnCalY = g_RaspberryPi2_TouchPanel_Driver.m_global_inX;  // intentionally changed x <-> y
        *pTipState |= TouchSampleDownFlag;
        stylusDown = true;
    } else {
        *pUnCalX = -1;
        *pUnCalY = -1;
        stylusDown = false;
    }
}

void RaspberryPi2_TouchPanel_Driver::TouchCompletion(void* arg)
{
    g_RaspberryPi2_TouchPanel_Driver.Poll();
    if (!g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.IsLinked()) {
        g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.EnqueueDelta(g_RaspberryPi2_TouchPanel_Driver.m_samplingTimespan);
    } else
    {
        g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.Abort();
    }
}

BOOL RaspberryPi2_TouchPanel_Driver::Initialize(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc)
{
    CPU_GPIO_EnableOutputPin(PIN_XL, false);
    CPU_GPIO_EnableOutputPin(PIN_YU, false);
    CPU_GPIO_EnableOutputPin(PIN_XR, false);
    CPU_GPIO_EnableOutputPin(PIN_YD, false);

    g_RaspberryPi2_TouchPanel_Driver.m_global_inX = 0;
    g_RaspberryPi2_TouchPanel_Driver.m_global_inY = 0;
    g_RaspberryPi2_TouchPanel_Driver.m_global_touch = 0;
    g_RaspberryPi2_TouchPanel_Driver.m_samplingTimespan = TOUCHPANEL_POLL_TIMESPAN;
    g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.Initialize();
    g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.InitializeForISR(RaspberryPi2_TouchPanel_Driver::TouchCompletion, NULL);
    g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.EnqueueDelta(g_RaspberryPi2_TouchPanel_Driver.m_samplingTimespan);
#if 0
    if (!::CPU_GPIO_EnableInputPin2(
            0xB4,
            FALSE,
            touchIsrProc,
            NULL,
            GPIO_INT_EDGE_BOTH,
            RESISTOR_PULLUP))
    {
        return FALSE;
    }
#endif
    return TRUE;
}

BOOL RaspberryPi2_TouchPanel_Driver::Uninitialize()
{
    if (g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.IsLinked())
    {
        g_RaspberryPi2_TouchPanel_Driver.m_touchCompletion.Abort();
    }
    return TRUE;
}

void RaspberryPi2_TouchPanel_Driver::Poll()
{
#if 0
    static UINT32 t_state;
    UINT32 value;

    switch(t_state) {
    case 0:
        SENSE_ON;
        t_state++;
        break;
    case 1:
        if (TOUCH_CHK)
            t_state++;
        else {
            IDLE;
            g_RaspberryPi2_TouchPanel_Driver.m_global_touch = 0;
            t_state = 0;
        }
        break;
    case 2:    // skip for chattering
    case 3:
        t_state++;
        break;
#if 0
    case 4:
        if (TOUCH_CHK) {
            SENSE_Y_ON;
            t_state++;
        } else {
            IDLE;
            g_RaspberryPi2_TouchPanel_Driver.m_global_touch = 0;
            t_state = 0;
        }
        break;
    case 5: // start A-D for getting Y axis
        AD_Y_ENABLE;
        FM3_ADC1->SCCR |= SCCR_SSTR;    // A/D start
        t_state++;
        break;
    case 6: // sense power on
        value = FM3_ADC1->SCFD;
        g_RaspberryPi2_TouchPanel_Driver.m_global_inX = (UINT16)(value >> 16);
        AD_Y_DISABLE;
        SENSE_ON;
        t_state++;
        break;
#else
    case 4:
        if (TOUCH_CHK) {
            GLOBAL_LOCK(irq);
            SENSE_Y_ON;
            AD_Y_ENABLE;
            volatile int i = 10000;
            while (i-- > 0);
            FM3_ADC1->SCCR |= SCCR_SSTR;    // A/D start
            do {
                value = FM3_ADC1->SCFD;
            } while (((value & SCFDL_INVL) != 0) || (16 != (value & 0x1F)));
            g_RaspberryPi2_TouchPanel_Driver.m_global_inY = (UINT16)(value >> 16);
            AD_Y_DISABLE;
            SENSE_ON;
            t_state += 3;
        } else {
            IDLE;
            g_RaspberryPi2_TouchPanel_Driver.m_global_touch = 0;
            t_state = 0;
        }
        break;
#endif
    case 7:
        if (TOUCH_CHK) {
            SENSE_X_ON;
            t_state++;
        } else {
            IDLE;
            g_RaspberryPi2_TouchPanel_Driver.m_global_touch = 0;
            t_state = 0;
        }
        break;
    case 8:    // start A-D for sensing X axis
        AD_X_ENABLE;
        FM3_ADC2->SCCR |= SCCR_SSTR;    // A/D start
        t_state++;
        break;
    case 9:    // sense power on
        value = FM3_ADC2->SCFD;
        g_RaspberryPi2_TouchPanel_Driver.m_global_inX = (UINT16)(value >> 16);
        AD_X_DISABLE;
        SENSE_ON;
        t_state++;
        break;
    case 10:    //  skip for chattering
    case 11:
        t_state++;
        break;
    case 12:
        if (TOUCH_CHK) {
            g_RaspberryPi2_TouchPanel_Driver.m_global_touch = 1;
#ifdef DEBUG_TOUCHPANEL
            lcd_printf("x=%d y=%d\r\n",
                    g_RaspberryPi2_TouchPanel_Driver.m_global_inX,
                    g_RaspberryPi2_TouchPanel_Driver.m_global_inY);
#endif
        }
        IDLE;
        t_state = 0;
        break;
    default:
        t_state = 0;
        break;
    }
#endif
}
