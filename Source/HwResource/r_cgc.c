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
* File Name    : r_cg_cgc.c
* Version      : Code Generator for RX113 V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F51136AxFP
* Tool-Chain   : CCRX
* Description  : This file implements device driver for CGC module.
* Creation Date: 2015/02/26
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
//#include "r_cg_cgc.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_ctsu.h"
#include "r_cgc.h"
static void R_CGC_Create_PLL(void);
static void R_CGC_Create_Main_Clock(void);
static void R_CGC_Create_HOCO(void);
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_CGC_Create
* Description  : This function initializes the clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CGC_Create(void)
{
    if(TOUCH_CFG_CLOCK_SOURCE == TOUCH_CLOCK_SOURCE_HOCO)
    {
        R_CGC_Create_HOCO();
    }else if(TOUCH_CFG_CLOCK_SOURCE == TOUCH_CLOCK_SOURCE_MAIN)
    {
        R_CGC_Create_Main_Clock();
    }else if(TOUCH_CFG_CLOCK_SOURCE == TOUCH_CLOCK_SOURCE_PLL)
    {
        R_CGC_Create_PLL();
    }else{
    }
}
/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_CGC_Create_HOCO
* Description  : This function initializes the HOCO clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void R_CGC_Create_HOCO(void)
{
    uint32_t sckcr_dummy;

    /* Set system clock */
    sckcr_dummy = TOUCH_SCKCR;
    SYSTEM.SCKCR.LONG = sckcr_dummy;

    while (SYSTEM.SCKCR.LONG != sckcr_dummy);

    /* Disable sub-clock */
    SYSTEM.SOSCCR.BIT.SOSTP = 1U;

    /* Wait for the register modification to complete */
    while (1U != SYSTEM.SOSCCR.BIT.SOSTP);

    /* Disable sub-clock */
    RTC.RCR3.BIT.RTCEN = 0U;

    /* Wait for the register modification to complete */
    while (0U != RTC.RCR3.BIT.RTCEN);

    /* Set HOCO */
#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
    SYSTEM.HOCOCR.BIT.HCSTP = 1U;
    SYSTEM.HOCOCR2.BYTE = TOUCH_CFG_HOCO_FREQUENCY;
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)

    SYSTEM.HOCOCR.BIT.HCSTP = 0U;

    /* Wait for HOCO wait counter overflow */
    while (1U != SYSTEM.OSCOVFSR.BIT.HCOVF);

#if (MCU_SERIES_T == R5F5113)
    /* Set HOCO wait time */
    SYSTEM.HOCOWTCR.BYTE = _06_CGC_HOCO_WAIT_CYCLE_266;
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
    /* Set to High-speed operating mode if ICLK is > 32MHz. */
    if (TOUCH_CFG_ICLK_HZ > 32000000)
    {
        SYSTEM.OPCCR.BYTE = 0x00;   // set to high-speed mode
        while(SYSTEM.OPCCR.BIT.OPCMTSF == 1)
        {
            /* Wait for transition to finish. */
        }
    
        SYSTEM.MEMWAIT.BYTE = 0x01; // Use wait states
        while (SYSTEM.MEMWAIT.BYTE != 0x01)
        {
            /* wait for bit to set */
        }
    }
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)

    /* Set clock source */
    SYSTEM.SCKCR3.WORD = _0100_CGC_CLOCKSOURCE_HOCO;

    while (SYSTEM.SCKCR3.WORD != _0100_CGC_CLOCKSOURCE_HOCO);

    /* Set LOCO */
    SYSTEM.LOCOCR.BIT.LCSTP = 1U;
}
/***********************************************************************************************************************
* Function Name: R_CGC_Create_Main_Clock
* Description  : This function initializes the Main clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void R_CGC_Create_Main_Clock(void)
{
    uint32_t sckcr_dummy;

    /* Set main clock control registers */
    if (TOUCH_CFG_XTAL_HZ > 10000000)
    {
        SYSTEM.MOFCR.BYTE = _00_CGC_MAINOSC_RESONATOR | _20_CGC_MAINOSC_OVER10M;
    }else{
        SYSTEM.MOFCR.BYTE = _00_CGC_MAINOSC_RESONATOR | _00_CGC_MAINOSC_UNDER10M;
    }
    SYSTEM.MOSCWTCR.BYTE = _06_CGC_OSC_WAIT_CYCLE_32768;

    /* Set main clock operation */
    SYSTEM.MOSCCR.BIT.MOSTP = 0U;

    /* Wait for main clock oscillator wait counter overflow */
    while (1U != SYSTEM.OSCOVFSR.BIT.MOOVF);

    /* Set system clock */
    sckcr_dummy = TOUCH_SCKCR;
    SYSTEM.SCKCR.LONG = sckcr_dummy;

    while (SYSTEM.SCKCR.LONG != sckcr_dummy);

    /* Disable sub-clock */
    SYSTEM.SOSCCR.BIT.SOSTP = 1U;

    /* Wait for the register modification to complete */
    while (1U != SYSTEM.SOSCCR.BIT.SOSTP);

    /* Disable sub-clock */
    RTC.RCR3.BIT.RTCEN = 0U;

    /* Wait for the register modification to complete */
    while (0U != RTC.RCR3.BIT.RTCEN);

#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
    /* Set to High-speed operating mode if ICLK is > 32MHz. */
    if (TOUCH_CFG_ICLK_HZ > 32000000)
    {
        SYSTEM.OPCCR.BYTE = 0x00;   // set to high-speed mode
        while(SYSTEM.OPCCR.BIT.OPCMTSF == 1)
        {
            /* Wait for transition to finish. */
        }
    
        SYSTEM.MEMWAIT.BYTE = 0x01; // Use wait states
        while (SYSTEM.MEMWAIT.BYTE != 0x01)
        {
            /* wait for bit to set */
        }
    }
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)

    /* Set clock source */
    SYSTEM.SCKCR3.WORD = _0200_CGC_CLOCKSOURCE_MAINCLK;

    while (SYSTEM.SCKCR3.WORD != _0200_CGC_CLOCKSOURCE_MAINCLK);

    /* Set LOCO */
    SYSTEM.LOCOCR.BIT.LCSTP = 1U;
}
/***********************************************************************************************************************
* Function Name: R_CGC_Create_PLL
* Description  : This function initializes the PLL clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void R_CGC_Create_PLL(void)
{
#if(TOUCH_CFG_CLOCK_SOURCE == TOUCH_CLOCK_SOURCE_PLL)
    uint32_t sckcr_dummy;

    /* Set main clock control registers */
    if (TOUCH_CFG_XTAL_HZ > 10000000)
    {
        SYSTEM.MOFCR.BYTE = _00_CGC_MAINOSC_RESONATOR | _20_CGC_MAINOSC_OVER10M;
    }else{
        SYSTEM.MOFCR.BYTE = _00_CGC_MAINOSC_RESONATOR | _00_CGC_MAINOSC_UNDER10M;
    }
    SYSTEM.MOSCWTCR.BYTE = _06_CGC_OSC_WAIT_CYCLE_32768;

    /* Set main clock operation */
    SYSTEM.MOSCCR.BIT.MOSTP = 0U;

    /* Wait for main clock oscillator wait counter overflow */
    while (1U != SYSTEM.OSCOVFSR.BIT.MOOVF);

    /* Set system clock */
    sckcr_dummy = TOUCH_SCKCR;
    SYSTEM.SCKCR.LONG = sckcr_dummy;

    while (SYSTEM.SCKCR.LONG != sckcr_dummy);

    /* Set PLL circuit */
    SYSTEM.PLLCR.WORD = TOUCH_PLLCR;
    SYSTEM.PLLCR2.BIT.PLLEN = 0U;

    /* Wait for PLL wait counter overflow */
    while (1U != SYSTEM.OSCOVFSR.BIT.PLOVF);

    /* Disable sub-clock */
    SYSTEM.SOSCCR.BIT.SOSTP = 1U;

    /* Wait for the register modification to complete */
    while (1U != SYSTEM.SOSCCR.BIT.SOSTP);

    /* Disable sub-clock */
    RTC.RCR3.BIT.RTCEN = 0U;

    /* Wait for the register modification to complete */
    while (0U != RTC.RCR3.BIT.RTCEN);

    #ifdef USB_SERIAL_USE
    /* Set UCLK */
    SYSTEM.UPLLCR.WORD = TOUCH_UPLLCR;
    SYSTEM.UPLLCR2.BIT.UPLLEN = 0U;

    while (1U != SYSTEM.OSCOVFSR.BIT.UPLOVF);
    #endif

#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
    /* Set to High-speed operating mode if ICLK is > 32MHz. */
    if (TOUCH_CFG_ICLK_HZ > 32000000)
    {
        SYSTEM.OPCCR.BYTE = 0x00;   // set to high-speed mode
        while(SYSTEM.OPCCR.BIT.OPCMTSF == 1)
        {
            /* Wait for transition to finish. */
        }
    
        SYSTEM.MEMWAIT.BYTE = 0x01; // Use wait states
        while (SYSTEM.MEMWAIT.BYTE != 0x01)
        {
            /* wait for bit to set */
        }
    }
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)

    /* Set clock source */
    SYSTEM.SCKCR3.WORD = _0400_CGC_CLOCKSOURCE_PLL;

    while (SYSTEM.SCKCR3.WORD != _0400_CGC_CLOCKSOURCE_PLL);

    /* Set LOCO */
    SYSTEM.LOCOCR.BIT.LCSTP = 1U;
#endif
}


/* End user code. Do not edit comment generated here */
