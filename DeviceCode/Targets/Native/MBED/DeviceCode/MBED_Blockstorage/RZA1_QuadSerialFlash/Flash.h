/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012 - 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/******************************************************************************
* File Name    : Flash.h
* $Rev: $
* $Date::                           $
* Description  : Flash memory interface fucntion header
******************************************************************************/
#ifndef _FLASH_H_
#define _FLASH_H_


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "sflash.h"
#include "spibsc.h"


/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/
#define SPIBSC_CH                (0)

#define FLASH_YES                (1)
#define FLASH_NO                 (0)
/******************************************************************************
Variable Externs
******************************************************************************/


/******************************************************************************
Functions Prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
__attribute__((section("SectionForFlashOperations"))) int_t Flash_Write_Init(void);
__attribute__((section("SectionForFlashOperations"))) int_t Flash_Write_Init_Dual(void);
__attribute__((section("SectionForFlashOperations"))) int_t Flash_Write_Entry(void);
__attribute__((section("SectionForFlashOperations"))) int_t Flash_Veify_Entry(void);
__attribute__((section("SectionForFlashOperations"))) int_t Flash_Write_Area(uint32_t *address, uint32_t *data, int_t size);
#ifdef __cplusplus
}
#endif

#endif  /* _FLASH_H_ */

/* End of File */
