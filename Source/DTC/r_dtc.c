/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_dtc.c
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file sets DTC to do the touch measurement and serial data send.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/
#define __R_DTC_C__

/***********************************************************************************************************************
* Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
/* System include header */
#include "r_cg_macrodriver.h"

/* H/W include header */
#include "iodefine.h"
#include "r_mpc.h"
#include "r_dtc.h"
#include "r_ctsu.h"
#include "r_cgc.h"

#ifdef  SCI_SERIAL_USE
    #include "r_sci.h"
#endif  // SCI_SERIAL_USE

/* S/W include header */
#include "r_touch.h"

/***********************************************************************************************************************
* Global variables and functions
***********************************************************************************************************************/
#if (MCU_SERIES_T == R5F5113 || MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)
    #pragma address dtc_vector60=0x00007CF0U
    uint32_t dtc_vector60;
    DTC_EXTERN dtc_register_data_t g_dtc_info_ctsu_wr;                    /* DTC transfer information for CTSU WR     */

    #pragma address dtc_vector61=0x00007CF4U
    uint32_t dtc_vector61;
    DTC_EXTERN dtc_register_data_t g_dtc_info_ctsu_rd;                    /* DTC transfer information for CTSU RD     */

#ifdef  SCI_SERIAL_USE
/*****    SCI6    *****************************************************************************************************/
    #pragma address dtc_vector228=0x00007F90U
    uint32_t dtc_vector228;
    DTC_EXTERN dtc_register_data_t g_dtc_info_sci6_tx;                    /* DTC transfer information for CTSU RD     */
#endif    // SCI_SERIAL_USE

#endif    // (MCU_SERIES_T == R5F5113 || MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)

#if (MCU_SERIES_T == R5F5130)
/*****    CTSU    *****************************************************************************************************/
    #pragma address dtc_vector60=0x000024F0U
    uint32_t dtc_vector60;
    DTC_EXTERN dtc_register_data_t g_dtc_info_ctsu_wr;                    /* DTC transfer information for CTSU WR     */

    #pragma address dtc_vector61=0x000024F4U
    uint32_t dtc_vector61;
    DTC_EXTERN dtc_register_data_t g_dtc_info_ctsu_rd;                    /* DTC transfer information for CTSU RD     */

#ifdef  SCI_SERIAL_USE
/*****    SCI6    *****************************************************************************************************/
    #pragma address dtc_vector228=0x00002790U
    uint32_t dtc_vector228;
    DTC_EXTERN dtc_register_data_t g_dtc_info_sci6_tx;                    /* DTC transfer information for CTSU RD     */
#endif    // SCI_SERIAL_USE

#endif    // (MCU_SERIES_T == R5F5130)

/***********************************************************************************************************************
* Function Name: DTC_Set_Initial_of_CTSU
* Description  : set DTC initial value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_Set_Initial_of_CTSU( uint8_t method )
{
    SYSTEM.PRCR.WORD             = PRCR1_ENA;              /* Enables writing to the registers                        */
    SYSTEM.MSTPCRA.BIT.MSTPA28   = 0;                      /* DTC module stop mode release                            */
    SYSTEM.PRCR.WORD             = PRCR1_DIS;              /* Disables writing to the registers                       */

    /* DTC Module Start Register (DTCST) ******************************************************************************/
    /* bit7-1  Reserved                                                                                               */
    /* bit0    DTC Module Start                                                                                       */
    /******************************************************************************************************************/
    DTC.DTCST.BIT.DTCST          = _0_DTCST_STOP;          /* DTC module stop                                         */

    /* DTC Control Register (DTCCR) ***********************************************************************************/
    /* bit7-5  Reserved                                                                                               */
    /* bit4    DTC Transfer Information Read Skip Enable                                                              */
    /* bit3    Reserved                                                                                               */
    /* bit2-0  Reserved                                                                                               */
    /******************************************************************************************************************/
    DTC.DTCCR.BIT.RRS            = _0_RRS_NOTSKIP;         /* Not skip setting                                        */
    DTC.DTCADMOD.BIT.SHORT       = _0_SHORT_FULL;          /* Full-address mode setting                               */

    /******************************************************************************************************************/
    /*****    Writing setting    **************************************************************************************/
    /******************************************************************************************************************/
    /* DTC Mode Register A (MRA) **************************************************************************************/
    /* bit7-6  DTC Transfer Mode Select                                                                               */
    /* bit5-4  DTC Data Transfer Size                                                                                 */
    /* bit3-2  Transfer Source Address Addressing Mode                                                                */
    /* bit1-0  Reserved                                                                                               */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_wr.word          = 0x0000;             /* Initialize MRA and MRB = 0                              */
    g_dtc_info_ctsu_wr.MRA.bit.MD    = _10_MD_BLOCK;       /* Block transfer mode setting                             */
    g_dtc_info_ctsu_wr.MRA.bit.SZ    = _01_SZ_WORD;        /* Word transfer setting                                   */
    g_dtc_info_ctsu_wr.MRA.bit.SM    = _10_SM_INC;         /* SAR value is incremented after data transfer            */

    g_dtc_info_ctsu_wr.MRB.bit.CHNE  = _0_CHNE_DISABLE;    /* Chain transfer disable setting                          */
    g_dtc_info_ctsu_wr.MRB.bit.DISEL = _0_DISEL_COMPLETED; /* when specified data transfer is completed               */
    g_dtc_info_ctsu_wr.MRB.bit.DTS   = _0_DTS_DESTINATION; /* Transfer destination side is repeat area or block area. */
    g_dtc_info_ctsu_wr.MRB.bit.DM    = _10_DM_INC;         /* DAR value is incremented after data transfer            */

    /* DTC Transfer Source Register (SAR) *****************************************************************************/
    /* bit31-0  SAR is used to set the transfer source start address                                                  */
    /******************************************************************************************************************/
    if (_1_CORRECTION == g_correction_mode)
    {
        g_dtc_info_ctsu_wr.SAR       = (uint32_t)&g_correction_dtc_txd;
    }
    else
    {
        g_dtc_info_ctsu_wr.SAR       = (uint32_t)(g_dtc_write_data[method]);
    }

    /* DTC Transfer Destination Register (DAR) ************************************************************************/
    /* bit31-0  DAR is used to set the transfer destination start address                                             */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_wr.DAR           = (uint32_t)&CTSU.CTSUSSC.WORD;

    /* DTC Transfer Count Register A (CRA) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_wr.CRA           = CTSU_DTC_WR_CNT;    /* Transfer count setting                                  */

    /* DTC Transfer Count Register B (CRB) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_wr.CRB           = 0x0000;             /* Not use in normal transfer.                             */

    /******************************************************************************************************************/
    /*****    Reading setting    **************************************************************************************/
    /******************************************************************************************************************/
    /* DTC Mode Register A (MRA) **************************************************************************************/
    /* bit7-6  DTC Transfer Mode Select                                                                               */
    /* bit5-4  DTC Data Transfer Size                                                                                 */
    /* bit3-2  Transfer Source Address Addressing Mode                                                                */
    /* bit1-0  Reserved                                                                                               */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_rd.word          = 0x0000;             /* Initialize MRA and MRB = 0                              */
    g_dtc_info_ctsu_rd.MRA.bit.MD    = _10_MD_BLOCK;       /* Block transfer mode setting                             */
    g_dtc_info_ctsu_rd.MRA.bit.SZ    = _01_SZ_WORD;        /* Word transfer setting                                   */
    g_dtc_info_ctsu_rd.MRA.bit.SM    = _10_SM_INC;         /* SAR value is incremented after data transfer            */

    g_dtc_info_ctsu_rd.MRB.bit.CHNE  = _0_CHNE_DISABLE;    /* Chain transfer disable setting                          */
    g_dtc_info_ctsu_rd.MRB.bit.DISEL = _0_DISEL_COMPLETED; /* When specified data transfer is completed               */
    g_dtc_info_ctsu_rd.MRB.bit.DTS   = _1_DTS_SOURCE;      /* Transfer source side is repeat area or block area       */
    g_dtc_info_ctsu_rd.MRB.bit.DM    = _10_DM_INC;         /* DAR value is incremented after data transfer            */

    /* DTC Transfer Source Register (SAR) *****************************************************************************/
    /* bit31-0  SAR is used to set the tra  nsfer source start address                                                  */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_rd.SAR           = (uint32_t)&CTSU.CTSUSC.WORD;    /* Transfer source start address setting       */

    /* DTC Transfer Destination Register (DAR) ************************************************************************/
    /* bit31-0  DAR is used to set the transfer destination start address                                             */
    /******************************************************************************************************************/
    if (_1_CORRECTION == g_correction_mode)
    {
        g_dtc_info_ctsu_rd.DAR     = (uint32_t)&g_correction_ico_data;
    }
    else
    {
        if (0 == g_key_info[method].mode)
        {
            g_dtc_info_ctsu_rd.DAR = (uint32_t)(g_self_ico_data_pt[method]);
        }
        else
        {
            g_dtc_info_ctsu_rd.DAR = (uint32_t)(g_mutual_ico_data_pt[method]);
        }
    }

    /* DTC Transfer Count Register A (CRA) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_rd.CRA           = CTSU_DTC_RD_CNT;          /* Transfer count setting                            */

    /* DTC Transfer Count Register B (CRB) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_rd.CRB           = 0x0000;                   /* Not use in normal transfer                        */

    /* Set transfer data start address in DTC vector table */
    dtc_vector60 = (uint32_t)&g_dtc_info_ctsu_wr;

    /* Set transfer data start address in DTC vector table */
    dtc_vector61 = (uint32_t)&g_dtc_info_ctsu_rd;

#if (MCU_SERIES_T == R5F5113 || MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)
    DTC.DTCVBR = (void *)0x00007C00U;
#endif    // (MCU_SERIES_T == R5F5113 || MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)

#if (MCU_SERIES_T == R5F5130)
    DTC.DTCVBR = (void *)0x00002400U;
#endif    // (MCU_SERIES_T == R5F5130)

}    /* End of function DTC_Set_Initial_of_CTSU() */

/***********************************************************************************************************************
* Function Name: CTSUSetDtcStart
* Description  : set DTC start trigger
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_Set_Start_of_CTSU( uint8_t method )
{
    /* DTC Module Start Register (DTCST) ******************************************************************************/
    /* bit7-1  Reserved                                                                                               */
    /* bit0    DTC Module Start                                                                                       */
    /******************************************************************************************************************/
//    DTC.DTCST.BIT.DTCST          = _0_DTCST_STOP;      /* DTC module stop                                           */

    /* DTC Control Register (DTCCR) ***********************************************************************************/
    /* bit7-5  Reserved                                                                                               */
    /* bit4    DTC Transfer Information Read Skip Enable                                                              */
    /* bit3    Reserved                                                                                               */
    /* bit2-0  Reserved                                                                                               */
    /******************************************************************************************************************/
    DTC.DTCCR.BIT.RRS            = _0_RRS_NOTSKIP;         /* Not skip setting                                        */

    /******************************************************************************************************************/
    /*****    Writing setting    **************************************************************************************/
    /******************************************************************************************************************/
    /* DTC Transfer Source Register (SAR) *****************************************************************************/
    /* bit31-0  SAR is used to set the transfer source start address                                                  */
    /******************************************************************************************************************/
    if (_1_CORRECTION == g_correction_mode)
    {
        g_dtc_info_ctsu_wr.SAR   = (uint32_t)&g_correction_dtc_txd;           /* Transfer source start address        */
    }
    else
    {
        g_dtc_info_ctsu_wr.SAR   = (uint32_t)(g_dtc_write_data[method]);      /* Transfer source start address        */
    }

    /* DTC Transfer Count Register A (CRA) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_wr.CRA       = CTSU_DTC_WR_CNT;        /* Transfer count                                          */

    /* DTC Transfer Count Register B (CRB) ****************************************************************************/
    /* bit15-0  CRB is used to set the block transfer count for block transfer mode                                   */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_wr.CRB       = 0x0000;                 /* Not use in normal transfer                              */

    /******************************************************************************************************************/
    /*****    Reading setting    **************************************************************************************/
    /******************************************************************************************************************/
    /* DTC Transfer Destination Register (DAR) ************************************************************************/
    /* bit31-0  DAR is used to set the transfer destination start address.e                                           */
    /******************************************************************************************************************/
    if (_1_CORRECTION == g_correction_mode)
    {
        g_dtc_info_ctsu_rd.DAR     = (uint32_t)&g_correction_ico_data;
    }
    else
    {
        if (0 == g_key_info[method].mode)
        {
            g_dtc_info_ctsu_rd.DAR = (uint32_t)(g_self_ico_data_pt[method]);
        }
        else
        {
            g_dtc_info_ctsu_rd.DAR = (uint32_t)(g_mutual_ico_data_pt[method]);
        }
    }

    /* DTC Transfer Count Register A (CRA) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_rd.CRA       = CTSU_DTC_RD_CNT;        /* Transfer count                                          */

    /* DTC Transfer Count Register B (CRB) ****************************************************************************/
    /* bit15-0  CRB is used to set the block transfer count for block transfer mode                                   */
    /******************************************************************************************************************/
    g_dtc_info_ctsu_rd.CRB       = 0x0000;                 /* Not use in normal transfer                              */

    /* DTC Control Register (DTCCR) ***********************************************************************************/
    /* bit7-5  Reserved                                                                                               */
    /* bit4    DTC Transfer Information Read Skip Enable                                                              */
    /* bit3    Reserved                                                                                               */
    /* bit2-0  Reserved                                                                                               */
    /******************************************************************************************************************/
    DTC.DTCCR.BIT.RRS            = _1_RRS_SKIP;            /* Skip setting                                            */

    DTCE(CTSU,CTSUWR)            = 1;                      /* DTC activation by CTSU WR interrupt request is enabled  */
    DTCE(CTSU,CTSURD)            = 1;                      /* DTC activation by CTSU RD interrupt request is enabled  */

    /* DTC Module Start Register (DTCST) ******************************************************************************/
    /* bit7-1  Reserved                                                                                               */
    /* bit0    DTC Module Start                                                                                       */
    /******************************************************************************************************************/
    DTC.DTCST.BIT.DTCST          = _1_DTCST_START;         /* DTC module start                                        */

    /* Interrupt Request Enable Register m (IERm) (m = 02h to 1Fh) ****************************************************/
    /* bit7    Interrupt Request Enable 7                                                                             */
    /* bit6    Interrupt Request Enable 6                                                                             */
    /* bit5    Interrupt Request Enable 5                                                                             */
    /* bit4    Interrupt Request Enable 4                                                                             */
    /* bit3    Interrupt Request Enable 3                                                                             */
    /* bit2    Interrupt Request Enable 2                                                                             */
    /* bit1    Interrupt Request Enable 1                                                                             */
    /* bit0    Interrupt Request Enable 0                                                                             */
    /******************************************************************************************************************/
    ICU.IER[0x07].BIT.IEN4       = 1;                      /* CTSUWR[IER07.IEN4] Interrupt Request Enable Register    */
    ICU.IER[0x07].BIT.IEN5       = 1;                      /* CTSURD[IER07.IEN5] Interrupt Request Enable Register    */
    ICU.IER[0x07].BIT.IEN6       = 1;                      /* CTSUFN[IER07.IEN6] Interrupt Request Enable Register    */
    ICU.IPR[IPR_CTSU_CTSUFN].BIT.IPR = 5;                  /* IPR_CTSU_CTSUFN[IPR60] Interrupt Source Priority Register */

}    /* End of function DTC_Set_Start_of_CTSU() */

#ifdef  SCI_SERIAL_USE
/***********************************************************************************************************************
* Function Name: DTC_Set_Initial_of_SCI6
* Description  : set DTC initial value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_Set_Initial_of_SCI6(void)
{
    /* DTC Module Start Register (DTCST) ******************************************************************************/
    /* bit7-1  Reserved                                                                                               */
    /* bit0    DTC Module Start                                                                                       */
    /******************************************************************************************************************/
    DTC.DTCST.BIT.DTCST          = _0_DTCST_STOP;          /* DTC module stop                                         */

    /* DTC Control Register (DTCCR) ***********************************************************************************/
    /* bit7-5  Reserved                                                                                               */
    /* bit4    DTC Transfer Information Read Skip Enable                                                              */
    /* bit3    Reserved                                                                                               */
    /* bit2-0  Reserved                                                                                               */
    /******************************************************************************************************************/
    DTC.DTCCR.BIT.RRS            = _0_RRS_NOTSKIP;         /* Not skip setting                                        */
    DTC.DTCADMOD.BIT.SHORT       = _0_SHORT_FULL;          /* Full-address mode setting                               */

    /******************************************************************************************************************/
    /*****    SCI_TXI6 setting    *************************************************************************************/
    /******************************************************************************************************************/
    /* DTC Mode Register A (MRA) **************************************************************************************/
    /* bit7-6  DTC Transfer Mode Select                                                                               */
    /* bit5-4  DTC Data Transfer Size                                                                                 */
    /* bit3-2  Transfer Source Address Addressing Mode                                                                */
    /* bit1-0  Reserved                                                                                               */
    /******************************************************************************************************************/
    g_dtc_info_sci6_tx.word          = 0x0000;             /* Initialize MRA and MRB = 0                              */
    g_dtc_info_sci6_tx.MRA.bit.MD    = _00_MD_NORMAL;      /* Block transfer mode setting                             */
    g_dtc_info_sci6_tx.MRA.bit.SZ    = _00_SZ_BYTE;        /* Byte transfer setting                                   */
    g_dtc_info_sci6_tx.MRA.bit.SM    = _10_SM_INC;         /* SAR value is incremented after data transfer            */

    g_dtc_info_sci6_tx.MRB.bit.CHNE  = _0_CHNE_DISABLE;    /* Chain transfer disable setting                          */
    g_dtc_info_sci6_tx.MRB.bit.DISEL = _0_DISEL_COMPLETED; /* When specified data transfer is completed               */
    g_dtc_info_sci6_tx.MRB.bit.DTS   = _0_DTS_DESTINATION; /* Transfer source side is repeat area or block area       */
    g_dtc_info_sci6_tx.MRB.bit.DM    = _00_DM_FIXED;       /* Address in the DAR register is fixed                    */

    /* DTC Transfer Source Register (SAR) *****************************************************************************/
    /* bit31-0  SAR is used to set the transfer source start address                                                  */
    /******************************************************************************************************************/
    g_dtc_info_sci6_tx.SAR           = (uint32_t)&g_sci6_send_data[1];

    /* DTC Transfer Destination Register (DAR) ************************************************************************/
    /* bit31-0  DAR is used to set the transfer destination start address                                             */
    /******************************************************************************************************************/
    g_dtc_info_sci6_tx.DAR           = (uint32_t)&SCI6.TDR;

    /* DTC Transfer Count Register A (CRA) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_sci6_tx.CRA           = 0x0000;                   /* Transfer count setting                            */

    /* DTC Transfer Count Register B (CRB) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_sci6_tx.CRB           = 0x0000;                   /* Not use in normal transfer                        */

    /* Set transfer data start address in DTC vector table */
    dtc_vector228  = (uint32_t)&g_dtc_info_sci6_tx;

#if (MCU_SERIES_T == R5F5230)
    DTC.DTCVBR = (void *)0x00007C00U;
#endif    // (MCU_SERIES_T == R5F5230)

#if (MCU_SERIES_T == R5F5130)
    DTC.DTCVBR = (void *)0x00002400U;
#endif    // (MCU_SERIES_T == R5F5130)

}    /* End of function DTC_Set_Initial_of_CTSU() */

/***********************************************************************************************************************
* Function Name: DTC_Set_Start_of_SCI6
* Description  : This function enables operation of transfer data DTC0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_Set_Start_of_SCI6(void)
{
    /* Set enable bit for start source interrupt */
    ICU.DTCER[228].BIT.DTCE = 1U;

    /* DTC Module Start Register (DTCST) ******************************************************************************/
    /* bit7-1  Reserved                                                                                               */
    /* bit0    DTC Module Start                                                                                       */
    /******************************************************************************************************************/
    DTC.DTCST.BIT.DTCST          = _1_DTCST_START;         /* DTC module start                                        */
}

/***********************************************************************************************************************
* Function Name: DTC_Set_Stop_of_SCI6
* Description  : This function disables operation of transfer data DTC0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_Set_Stop_of_SCI6(void)
{
    /* Clear enable bit for start source interrupt */
    ICU.DTCER[228].BIT.DTCE = 0U;
}

/***********************************************************************************************************************
* Function Name: DTC_Set_Start_of_SCI6
* Description  : This function enables operation of transfer data DTC0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_Set_Data_Size_of_SCI6( uint16_t size )
{
    /* DTC Transfer Count Register A (CRA) ****************************************************************************/
    /* bit15-0  Transfer count                                                                                        */
    /******************************************************************************************************************/
    g_dtc_info_sci6_tx.CRA           = size;                     /* Transfer count setting                            */
}

/***********************************************************************************************************************
* Function Name: DTC_Set_Start_of_SCI6
* Description  : This function enables operation of transfer data DTC0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_Set_Restart_SCI6(void)
{
    /* DTC Transfer Source Register (SAR) *****************************************************************************/
    /* bit31-0  SAR is used to set the transfer source start address                                                  */
    /******************************************************************************************************************/
    g_dtc_info_sci6_tx.SAR           = (uint32_t)&g_sci6_send_data[1];
}
#endif  // SCI_SERIAL_USE

/***********************************************************************************************************************
* End of file
***********************************************************************************************************************/

