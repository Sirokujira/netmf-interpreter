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

#ifndef _TOUCH_PANEL_DRIVER_H_
#define _TOUCH_PANEL_DRIVER_H_ 1

#include <tinyhal.h>

//--//

#define TOUCHPANEL_POLL_TIMESPAN    3000    // 4ms

#if 0
// CN2-01 PB0(AN16) XIN - X-axis and Touch Check
// CN2-02 PB1(AN17) YIN - Y-axis
#define XR_HI   {FM3_GPIO->DDRB |= 0x00000004; FM3_GPIO->PDORB |= 0x00000004;}
#define XR_LO   {FM3_GPIO->DDRB |= 0x00000004; FM3_GPIO->PDORB &= ~0x00000004;}
#define XR_IN   {FM3_GPIO->DDRB &= ~0x00000004;}
#define XR_HZ   {FM3_GPIO->PZRB |= 0x00000004;}
#define XL_HI   {FM3_GPIO->DDRB |= 0x00000010; FM3_GPIO->PDORB |= 0x00000010;}
#define XL_LO   {FM3_GPIO->DDRB |= 0x00000010; FM3_GPIO->PDORB &= ~0x00000010;}
#define XL_IN   {FM3_GPIO->DDRB &= ~0x00000010;}
#define XL_HZ   {FM3_GPIO->PZRB |= 0x00000010;}
#define YU_HI   {FM3_GPIO->DDRB |= 0x00000008; FM3_GPIO->PDORB |= 0x00000008;}
#define YU_LO   {FM3_GPIO->DDRB |= 0x00000008; FM3_GPIO->PDORB &= ~0x00000008;}
#define YU_IN   {FM3_GPIO->DDRB &= ~0x00000008;}
#define YU_HZ   {FM3_GPIO->PZRB |= 0x00000008;}
#define YD_HI   {FM3_GPIO->DDRB |= 0x00000020; FM3_GPIO->PDORB |= 0x00000020;}
#define YD_LO   {FM3_GPIO->DDRB |= 0x00000020; FM3_GPIO->PDORB &= ~0x00000020;}
#define YD_IN   {FM3_GPIO->DDRB &= ~0x00000020;}
#define YD_HZ   {FM3_GPIO->PZRB |= 0x00000020;}
#define PD_HI   {FM3_GPIO->DDRB |= 0x00000040; FM3_GPIO->PDORB |= 0x00000040;}
#define PD_LO   {FM3_GPIO->DDRB |= 0x00000040; FM3_GPIO->PDORB &= ~0x00000040;}
#define PD_IN   {FM3_GPIO->DDRB &= ~0x00000040;}
#define PD_HZ   {FM3_GPIO->PZRB |= 0x00000040;}
#define PDINT_IN    {FM3_GPIO->DDRB &= ~0x00000080;}

#if 0
#define IDLE            {FM3_GPIO->DDRB = 0x000000000; FM3_GPIO->PDORB = 0x00000000;}
#define SENSE_ON        {FM3_GPIO->DDRB = 0x000000068; FM3_GPIO->PDORB = 0x00000040;}
#define SENSE_Y_ON      {FM3_GPIO->DDRB = 0x000000028; FM3_GPIO->PDORB = 0x00000008;}
#define SENSE_X_ON      {FM3_GPIO->DDRB = 0x000000014; FM3_GPIO->PDORB = 0x00000004;}
#else
#define IDLE            {XR_IN;XL_IN;YU_IN;YD_IN;PD_IN;}
#define SENSE_ON        {XR_IN;XL_IN;YU_LO;YD_LO;PD_HI;}
#define SENSE_Y_ON      {XR_IN;XL_IN;YU_LO;YD_HI;PD_IN;}
#define SENSE_X_ON      {XR_HI;XL_LO;YU_IN;YD_IN;PD_IN;}
#endif
#define AD_Y_ENABLE  {FM3_GPIO->ADE |= 0x00010000;  FM3_GPIO->PFRB |= 0x00000001;}
#define TOUCH_CHK       (!(FM3_GPIO->PDIRB & 0x00000001))
#define AD_Y_DISABLE {FM3_GPIO->ADE &= ~0x00010000; FM3_GPIO->PFRB &= ~0x00000001;}
#define AD_X_ENABLE  {FM3_GPIO->ADE |= 0x00020000;  FM3_GPIO->PFRB |= 0x00000002;}
#define AD_X_DISABLE {FM3_GPIO->ADE &= ~0x00020000; FM3_GPIO->PFRB &= ~0x00000002;}

// default calibration values
#define X_UL    834
#define Y_UL    657
#define X_DL    880
#define Y_DL    3636
#define X_UR    3351
#define Y_UR    648
#define X_DR    3272
#define Y_DR    3587

/*
 * FM3 A-D converter
 * Register Bit Definition
 */
#define ADCR_OVRIE           0x01U
#define ADCR_CMPIE           0x02U
#define ADCR_PCIE            0x04U
#define ADCR_SCIE            0x08U
#define ADCR_CMPIF           0x20U
#define ADCR_PCIF            0x40U
#define ADCR_SCIF            0x80U
#define ADCR_IFALL           (ADCR_CMPIF | ADCR_PCIF | ADCR_SCIF)

#define ADSR_SCS             0x01U
#define ADSR_PCS             0x02U
#define ADSR_PCNS            0x04U
#define ADSR_FDAS            0x40U
#define ADSR_ADSTP           0x80U

#define SCCR_SSTR            0x01U
#define SCCR_SHEN            0x02U
#define SCCR_RPT             0x04U
#define SCCR_SFCLR           0x10U
#define SCCR_SOVR            0x20U
#define SCCR_SFUL            0x40U
#define SCCR_SEMP            0x80U
#define SCFDL_INVL           0x1000U

#define PCCR_PSTR            0x01U
#define PCCR_PHEN            0x02U
#define PCCR_PEEN            0x04U
#define PCCR_ESCE            0x08U
#define PCCR_PFCLR           0x10U
#define PCCR_POVR            0x20U
#define PCCR_PFUL            0x40U
#define PCCR_PEMP            0x80U
#define PCFDL_INVL           0x1000U

#define CMPCR_CMD0           0x20U
#define CMPCR_CMD1           0x40U
#define CMPCR_CMPEN          0x80U

#define ADCEN_ENBL           0x01U
#define ADCEN_READY          0x02U
#endif

class MBED_GR_PEACH_TouchPanel_Driver
{
public:
    static BOOL Initialize(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc);
    static BOOL Uninitialize();
    static HRESULT GetDeviceCaps(unsigned int iIndex, void* lpOutput);
    static void GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY);
private:
    static void Poll();
    static void TouchCompletion(void* arg);
    static BOOL CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT *pTCP);
    //
    INT32 m_global_touch;
    UINT16 m_global_inX;
    UINT16 m_global_inY;
    HAL_COMPLETION    m_touchCompletion;
    INT32 m_samplingTimespan;
};
#endif

