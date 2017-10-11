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
/*******************************************************************************
* File Name   : Flash_Routine.c
* $Rev: $
* $Date::                           $
* Description : Initialize peripheral function sample
*******************************************************************************/


/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_typedefs.h"
#include "Flash.h"
#include "r_spibsc_flash_api.h"
#define SF_PAGE_SIZE    4096

/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
// st_spibsc_cfg_t g_spibsc_cfg;
extern st_spibsc_cfg_t g_spibsc_cfg;


/******************************************************************************
Private global variables and functions
******************************************************************************/
int32_t g_erased_flag[SF_NUM_OF_SECTOR];
__attribute__((section("SectionForFlashOperations"))) static void Init_Erased_Flag(void);
__attribute__((section("SectionForFlashOperations"))) static void Set_Erased_Flag(int32_t sector_no);
__attribute__((section("SectionForFlashOperations"))) static int32_t Is_Erased_Sector(int32_t sector_no);
static uint32_t Is_Sflash_Dual;


/******************************************************************************
* Function Name: Flash_Write_Init
* Description  : Initilize Flash programming function
* Arguments    : none
* Return Value : result
******************************************************************************/
int_t Flash_Write_Init(void)
{
    Init_Erased_Flag();

    Is_Sflash_Dual = SPIBSC_CMNCR_BSZ_SINGLE;

    /* ==== Initializes the SPIBSC ==== */
    if(R_SFLASH_Set_Config(SPIBSC_CH, &g_spibsc_cfg) != 0 )
    {
        return -1;
    }

    if( R_SFLASH_Exmode_Setting(SPIBSC_CH, SPIBSC_CMNCR_BSZ_SINGLE, &g_spibsc_cfg) != 0 )
    {
        return -1;
    }

    if( R_SFLASH_Spimode(SPIBSC_CH) != 0 )
    {
        return -1;
    }

    /* ==== Disables the software protection in serial flash memory ==== */
    R_SFLASH_Ctrl_Protect(SF_REQ_UNPROTECT, SPIBSC_CH, SPIBSC_CMNCR_BSZ_SINGLE, g_spibsc_cfg.udef_data_width);

    return 0;
}

/******************************************************************************
* Function Name: int_t Flash_Write_Init_Dual(void);
* Description  : Initilize Flash programming function
* Arguments    : none
* Return Value : none
******************************************************************************/
int_t Flash_Write_Init_Dual(void)
{
    if( R_SFLASH_SpibscStop(SPIBSC_CH) != 0 )
    {
        return -1;
    }

    Is_Sflash_Dual = SPIBSC_CMNCR_BSZ_DUAL;

    /* ==== Initializes the SPIBSC ==== */
    if( R_SFLASH_Exmode_Setting(SPIBSC_CH, SPIBSC_CMNCR_BSZ_DUAL, &g_spibsc_cfg) != 0 )
    {
        return -1;
    }

    if( R_SFLASH_Spimode(SPIBSC_CH) != 0 )
    {
        return -1;
    }

    /* ==== Disables the software protection in serial flash memory ==== */
    R_SFLASH_Ctrl_Protect(SF_REQ_UNPROTECT, SPIBSC_CH, SPIBSC_CMNCR_BSZ_DUAL, g_spibsc_cfg.udef_data_width);

    return 0;
}

/******************************************************************************
* Function Name: Flash_Write_Entry
* Description  : Entry to Write Mode
* Arguments    : none
* Return Value : resut to entry
******************************************************************************/
int_t Flash_Write_Entry(void)
{
    if( R_SFLASH_Spimode(SPIBSC_CH) != 0 )
    {
        return -1;
    }
    return 0;
}

/******************************************************************************
* Function Name: Flash_Veify_Entry
* Description  : Entry to Verify Mode
* Arguments    : none
* Return Value : resut to entry
******************************************************************************/
int_t Flash_Veify_Entry(void)
{
    if( R_SFLASH_Exmode(SPIBSC_CH) != 0 )
    {
        return -1;
    }
    return 0;
}

/******************************************************************************
* Function Name: Flash_Write_Area
* Description  : Flash programming function
* Arguments    : uint32_t *address : flash address
*              : uint32_t *data    : data to write
*              : int_t size        : size of data to write
* Return Value : result to write
******************************************************************************/
int_t Flash_Write_Area(uint32_t *address, uint32_t *data, int_t size)
{
    int32_t    cur_sctno = 0;
    uint32_t   addr;
    int32_t    write_size;
    uint8_t    *data_b;

    addr   = (uint32_t)( ((uint32_t)address) & 0x07FFFFFF);
    data_b = (uint8_t *)data;
    while(size > 0)
    {
        cur_sctno = (addr / SF_SECTOR_SIZE);

        if (Is_Erased_Sector(cur_sctno) == 0)
        {
            R_SFLASH_EraseSector(addr, SPIBSC_CH, Is_Sflash_Dual, g_spibsc_cfg.udef_data_width, g_spibsc_cfg.udef_addr_mode);
            Set_Erased_Flag(cur_sctno);
        }

        if( Is_Sflash_Dual == SPIBSC_CMNCR_BSZ_SINGLE )
        {
            if ( (addr % SF_PAGE_SIZE) != 0)
            {
                return -1;
            }
            else
            {
                if(size >= SF_PAGE_SIZE)
                {
                    write_size = SF_PAGE_SIZE;
                }
                else
                {
                    write_size = (int32_t)size;
                }
            }
        }
        else
        {
            if ( (addr % (SF_PAGE_SIZE * 2)) != 0)
            {
                return -1;
            }
            else
            {
                if(size >= (SF_PAGE_SIZE * 2))
                {
                    write_size = (SF_PAGE_SIZE * 2);
                }
                else
                {
                    write_size = (int32_t)size;
                    if((write_size % 2) != 0)
                    {
                        /* write_size has to be 2byte unit */
                        write_size += 1;
                    }
                }
            }
        }

        R_SFLASH_ByteProgram(addr, data_b, write_size, SPIBSC_CH, Is_Sflash_Dual, g_spibsc_cfg.udef_data_width, g_spibsc_cfg.udef_addr_mode);

        addr   += write_size;
        data_b += write_size;
        size   -= write_size;
    }

    return 0;
}

/*******************************************************************************
 * Outline          :
 * Declaration      : static void Init_Erased_Flag(void);
 * Functions        :
 * Arguments        : void
 * Return values    : void
 * Notes            : None
 ******************************************************************************/
static void Init_Erased_Flag(void)
{
    int32_t i;

    for(i = 0; i < SF_NUM_OF_SECTOR; i++)
    {
        g_erased_flag[i] = 0;
    }
}

/*******************************************************************************
 * Outline          :
 * Declaration      : static void Set_Erased_Flag(int32_t sector_no);
 * Functions        :
 * Arguments        : int32_t sector_no; I : 
 * Return values    : void
 * Notes            : None
 ******************************************************************************/
static void Set_Erased_Flag(int32_t sector_no)
{
    if( Is_Sflash_Dual == SPIBSC_CMNCR_BSZ_DUAL )
    {
        sector_no >>= 1;
    }

    if(sector_no > SF_NUM_OF_SECTOR)
    {
        return;
    }
    g_erased_flag[sector_no] = 1;

}

/*******************************************************************************
 * Outline          :
 * Declaration      : static int32_t Is_Erased_Sector(int32_t sector_no);
 * Functions        :
 * Arguments        : int32_t sector_no; I : 
 * Return values    : 0:not erased , 1:erased
 * Notes            : None
 ******************************************************************************/
static int32_t Is_Erased_Sector(int32_t sector_no)
{
    if( Is_Sflash_Dual == SPIBSC_CMNCR_BSZ_DUAL )
    {
        sector_no >>= 1;
    }

    return g_erased_flag[sector_no];
}

/* End of File */
