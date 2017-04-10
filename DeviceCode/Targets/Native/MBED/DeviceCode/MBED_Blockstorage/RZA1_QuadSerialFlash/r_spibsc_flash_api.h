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
* File Name    : r_spibsc_flash_api.h
* $Rev: $
* $Date::                           $
* Description  : 
******************************************************************************/
#ifndef _R_SPIBSC_FLASH_API_H_
#define _R_SPIBSC_FLASH_API_H_


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_typedefs.h"
#include "r_spibsc_ioset_api.h"


/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Variable Externs
******************************************************************************/


/******************************************************************************
Functions Prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/* api function */
__attribute__((section("SectionForFlashOperations"))) int32_t R_SFLASH_EraseSector(uint32_t addr, uint32_t ch_no, uint32_t dual, uint8_t data_width, uint8_t addr_mode);
__attribute__((section("SectionForFlashOperations"))) int32_t R_SFLASH_ByteProgram(uint32_t addr, uint8_t *buf, int32_t size, uint32_t ch_no,
                             uint32_t dual, uint8_t data_width, uint8_t addr_mode);
__attribute__((section("SectionForFlashOperations"))) int32_t R_SFLASH_ByteRead(uint32_t addr, uint8_t * buf, int32_t size, uint32_t ch_no, uint32_t dual, uint8_t data_width, uint8_t addr_mode);
__attribute__((section("SectionForFlashOperations"))) int32_t R_SFLASH_Spibsc_Transfer(uint32_t ch_no, st_spibsc_spimd_reg_t * regset);
__attribute__((section("SectionForFlashOperations"))) int32_t R_SFLASH_Ctrl_Protect(en_sf_req_t req, uint32_t ch_no, uint32_t dual, uint8_t data_width);


/* User defined function */
__attribute__((section("SectionForFlashOperations"))) int32_t Userdef_SFLASH_Set_Mode(uint32_t ch_no, uint32_t dual, en_sf_req_t req, uint8_t data_width, uint8_t addr_mode);
__attribute__((section("SectionForFlashOperations"))) int32_t Userdef_SFLASH_Write_Enable(uint32_t ch_no);
__attribute__((section("SectionForFlashOperations"))) int32_t Userdef_SFLASH_Busy_Wait(uint32_t ch_no, uint32_t dual, uint8_t data_width);
__attribute__((section("SectionForFlashOperations"))) int32_t Userdef_SFLASH_Ctrl_Protect(en_sf_req_t req, uint32_t ch_no, uint32_t dual, uint8_t data_width);
#ifdef __cplusplus
}
#endif

#endif /* _R_SPIBSC_FLASH_API_H_ */

/* End of File */
