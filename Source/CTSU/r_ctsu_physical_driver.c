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
* File Name    : r_touch_physical_driver.c
* Version      : 2.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file controls thw Capacitive Touch Sensing Unit module.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : 14.11.2013   1.00     First Release
*              : xx.xx.2015   2.00     Set value error is returned by the return value.
***********************************************************************************************************************/
#define __R_CTSU_PHYSICAL_DRIVER_C__

/***********************************************************************************************************************
* Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
/* System include header */

/* H/W include header */
#include "iodefine.h"
#include "r_mpc.h"
#include "r_ctsu.h"

/* S/W include header */

/***********************************************************************************************************************
* Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_Get_CTSU_current_trimming_val
* Description  : Current trimming register value get
* Arguments    : -
* Return Value : -
***********************************************************************************************************************/
uint8_t R_Get_CTSU_current_trimming_val(void)
{
    uint8_t    value;

    /* CTSU Reference Current Calibration Register (CTSUTRMR) *********************************************************/
    /* bit7-0   Current Trimming Value                                                                                */
    /******************************************************************************************************************/
    value = CTSU.CTSUTRMR;

    return value;

}    /* End of function R_Get_CTSU_current_trimming_val() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_current_trimming_val
* Description  : Current trimming register value get
* Arguments    : -
* Return Value : -
***********************************************************************************************************************/
void R_Set_CTSU_current_trimming_val( uint8_t value )
{
    /* CTSU Reference Current Calibration Register (CTSUTRMR) *********************************************************/
    /* bit7-0   Current Trimming Value                                                                                */
    /******************************************************************************************************************/
    CTSU.CTSUTRMR = value;

}    /* End of function R_Set_CTSU_current_trimming_val() */

/***********************************************************************************************************************
* Function Name: R_Get_CTSU_TSCAP_Discharge
* Description  : TSCAP capacitor discharge
* Arguments    : -
* Return Value : -
***********************************************************************************************************************/
void R_Set_CTSU_TSCAP_Discharge(void)
{
#if (MCU_SERIES_T == R5F5113)
    PORT2.PMR.BIT.B6  = 0;                             /* Use pin as general I/O port setting                         */
    PORT2.PODR.BIT.B6 = 0;                             /* Low level setting                                           */
    PORT2.PDR.BIT.B6  = 1;                             /* Output setting                                              */
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
    PORTC.PMR.BIT.B4  = 0;                             /* Use pin as general I/O port setting                         */
    PORTC.PODR.BIT.B4 = 0;                             /* Low level setting                                           */
    PORTC.PDR.BIT.B4  = 1;                             /* Output setting                                              */
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
}

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Module_Operation
* Description  : Bit10(MSTPD10) of Module Stop Control Register D setting
* Arguments    : uint8_t mode    : 0 Module enable
*              :                 : 1 Module disable
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Module_Operation( uint8_t mode )
{
    uint8_t status;

    status = SET_ERROR;

    /* Protect Register (PRCR) ****************************************************************************************/
    /* bit15-8  PRC Key Code                                                                                          */
    /* bit7-4   Reserved                                                                                              */
    /* bit3     Protect Bit 3                                                                                         */
    /* bit2     Protect Bit 2                                                                                         */
    /* bit1     Protect Bit 1                                                                                         */
    /* bit0     Protect Bit 0                                                                                         */
    /******************************************************************************************************************/
    SYSTEM.PRCR.WORD = PRCR1_ENA;

    /* Module Stop Control Register D (MSTPCRD) ***********************************************************************/
    /* bit31-16  Reserved                                                                                             */
    /* bit15     Serial Sound Interface Module StopReserved                                                           */
    /* bit14-12  Reserved                                                                                             */
    /* bit11     LCD Controller Module Stop                                                                           */
    /* bit10     Touch Sensor Control Unit Module Stop                                                                */
    /* bit9-0    Reserved                                                                                             */
    /******************************************************************************************************************/
    if (_0_MSTPD10_CTSU_ENABLE == mode)
    {
        SYSTEM.MSTPCRD.BIT.MSTPD10 = _0_MSTPD10_CTSU_ENABLE;
        status = SET_SUCCESS;
    }
    else if  (_1_MSTPD10_CTSU_DISABLE == mode)
    {
        SYSTEM.MSTPCRD.BIT.MSTPD10 = _1_MSTPD10_CTSU_DISABLE;
        status = SET_SUCCESS;
    }
    else
    {
        /* Do Nothing */
    }

    return status;
}    /* End of function R_Set_CTSU_Module_Operation() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Measurement_Start
* Description  : Bit0(CTSUSTRT) and Bit1(CTSUCAP) of CTSU Control Register 0 setting
* Arguments    : uint8_t mode    : 0 Measurement operation stops
*              :                 : 1 Measurement operation starts
*              : uint8_t trigger : 0 Software trigger
*              :                 : 1 External trigger
* Return Value : None
***********************************************************************************************************************/
void R_Set_CTSU_Measurement_Start( uint8_t mode, uint8_t trigger)
{
    volatile uint8_t data;

    /* CTSU Control Register 0 (CTSUCR0) ******************************************************************************/
    /* bit7-5  Reserved                                                                                               */
    /* bit4    CTSU Control Block Initialization                                                                      */
    /* bit3    Reserved                                                                                               */
    /* bit2    CTSU Wait State Power-Saving Enable                                                                    */
    /* bit1    CTSU Measurement Operation Start Trigger Select                                                        */
    /* bit0    CTSU Measurement Operation Start                                                                       */
    /******************************************************************************************************************/
    data              = CTSU.CTSUCR0.BYTE;             /* CTSU Control Register 0 (CTSUCR0) storage                   */

    /*****    Hardware manual note setting     ************************************************************************/
    data               = data & 0xFE;                  /* Bit0(CTSUSTRT) = 0 setting data storage                     */
    data               = data | 0x10;                  /* Bit4(CTSUINIT) = 1 setting data storage                     */
    CTSU.CTSUCR0.BYTE  = data;                         /* CTSU Control Register 0 (CTSUCR0) setting                   */
    /******************************************************************************************************************/

    CTSU.CTSUCR0.BIT.CTSUCAP   = trigger;              /* Bit1(CTSUCAP) setting                                       */
    CTSU.CTSUCR0.BIT.CTSUSTRT  = mode;                 /* Bit0(CTSUSTRT) setting                                      */
}    /* End of function R_Set_CTSU_Measurement_Start() */

/***********************************************************************************************************************
* Function Name: CTSUSetControlBlockInitial
* Description  : This API sets initial of CTSU control block.
* Arguments    : mode
* Return Value : None
***********************************************************************************************************************/
void CTSUSetControlBlockInitial( uint8_t mode )
{
    uint8_t data;

    /* CTSU Control Register 0 (CTSUCR0)
    b4        CTSU Control Block Initialization
    b3        CTSU Mutual Capacitance Simple Scan Mode Transmit Pin Control
    b1        CTSU Measurement Operation Start Trigger Select
    b0        CTSU Measurement Operation Start        */
    if( _11_CTSUMD_MUTUAL == mode )                                //    If set Control block initialization,
    {
        data = CTSU.CTSUCR0.BYTE;                //    CTSU Control Register 0 (CTSUCR0)
        data = data & 0xFE;                        //    set Measurement Stop
        data = data | 0x10;                        //    set Control Block Initialization
        CTSU.CTSUCR0.BYTE = data;                //    CTSU Control Register 0 (CTSUCR0)
    }
}

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Power_Supply
* Description  : Bit0(CTSUPON) and Bit1(CTSUCSW) of CTSU Control Register 1 setting
* Arguments    : uint8_t power   : 0 CTSU Power OFF and Capacity switch OFF
*                                : 1 CTSU Power ON  and Capacity switch ON
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Power_Supply( uint8_t power )
{
    uint8_t data;
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Control Register 1 (CTSUCR1) ******************************************************************/
            /* bit7-6  CTSU Measurement Mode Select                                                                   */
            /* bit5-4  CTSU Operating Clock Select                                                                    */
            /* bit3    CTSU Power Supply Capacity Adjustment                                                          */
            /* bit2    CTSU Power Supply Operating Mode Setting                                                       */
            /* bit1    CTSU LPF Capacitance Charging Control                                                          */
            /* bit0    CTSU Power Supply Enable                                                                       */
            /**********************************************************************************************************/
            if ( 1 == power )
            {
                data              = CTSU.CTSUCR1.BYTE;       /* CTSU Control Register 1 (CTSUCR0) storage             */

                /*****    Hardware manual note setting = Page    ******************************************************/
                data               = data | 0x03;            /* Bit0(CTSUPON) = 1 and Bit1(CTSUCSW) = 1 setting data storage  */
                CTSU.CTSUCR1.BYTE  = data;                   /* CTSU Control Register 0 (CTSUCR0) setting             */
                /******************************************************************************************************/

                status = SET_SUCCESS;
            }
            else if ( 0 == power )
            {
                data              = CTSU.CTSUCR1.BYTE;       /* CTSU Control Register 1 (CTSUCR0) storage             */
                data              = data & 0xFC;             /* Bit0(CTSUPON) = 0 and Bit1(CTSUCSW) = 0 setting data storage  */
                CTSU.CTSUCR1.BYTE = data;                    /* CTSU Control Register 0 (CTSUCR0) setting             */

                status = SET_SUCCESS;
            }
            else
            {
                /* Do Nothing */
            }
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Power_Supply() */

/***********************************************************************************************************************
* Function Name: CTSUSetPowerSupplyOnly
* Description  : This API switches  power of AFE (Analog Front End).
* Arguments    : mode
* Return Value : None
***********************************************************************************************************************/
void R_Set_CTSU_Power_Supply_Only( uint8_t mode )
{
    volatile uint8_t data;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Control Register 1 (CTSUCR1) ******************************************************************/
            /* bit7-6  CTSU Measurement Mode Select                                                                   */
            /* bit5-4  CTSU Operating Clock Select                                                                    */
            /* bit3    CTSU Power Supply Capacity Adjustment                                                          */
            /* bit2    CTSU Power Supply Operating Mode Setting                                                       */
            /* bit1    CTSU LPF Capacitance Charging Control                                                          */
            /* bit0    CTSU Power Supply Enable                                                                       */
            /**********************************************************************************************************/
            if( 1 == mode )
            {
                data              = CTSU.CTSUCR1.BYTE;       /* CTSU Control Register 1 (CTSUCR0) storage             */
                data              = data | 0x01;             /* set Power Supply on(bit0)                             */
                CTSU.CTSUCR1.BYTE = data;                    /* set  CTSU Control Register 1 (CTSUCR1)                */
            }
            else
            {
                data              = CTSU.CTSUCR1.BYTE;       /* CTSU Control Register 1 (CTSUCR0) storage             */
                data              = data & 0xFE;             /* set Power Supply off(bit0)                            */
                CTSU.CTSUCR1.BYTE = data;                    /* set  CTSU Control Register 1 (CTSUCR1)                */
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: CTSUSetLpfPinControl
* Description  : This API switches the LPF pin output.
* Arguments    : mode
* Return Value : None
***********************************************************************************************************************/
void CTSUSetLpfPinControl( uint8_t mode )
{
    /* Port Direction Register (PDR) */
    PORT2.PDR.BIT.B6 = 1;                    //    
    /* Port Output Data Register (PODR) */
    PORT2.PODR.BIT.B6 = mode;                //    
}

#if (MCU_SERIES_T == R5F5130)
/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Transmit_Power_Supply
* Description  : 
* Arguments    : uint8_t tx_power : 0 Vcc select
*                                 : 1 Interal logic power supply
* Return Value : uint8_t status   : 0 SET_SUCCESS
*              :                  : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Transmit_Power_Supply( uint8_t tx_power )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /* CTSU Control Register 0 (CTSUCR0) **********************************************************************/
            /* bit7    CTSU Transmit Power Supply Select (CTSUTXVSEL) (RX130 only)                                    */
            /* bit6-5  Reserved                                                                                       */
            /* bit4    CTSU Control Block Initialization (CTSUINIT)                                                   */
            /* bit3    Reserved                                                                                       */
            /* bit2    CTSU Wait State Power-Saving Enable (CTSUSNZ)                                                  */
            /* bit1    CTSU Measurement Operation Start Trigger Select (CTSUCAP)                                      */
            /* bit0    CTSU Measurement Operation Start (CTSUSTRT)                                                    */
            /**********************************************************************************************************/
            CTSU.CTSUCR0.BIT.CTSUTXVSEL = tx_power;
            status = SET_SUCCESS;
        }
    }
    return status;
}
#endif    // (MCU_SERIES_T == R5F5130)

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Power_Operation_Mode
* Description  : 
* Arguments    : uint8_t mode    : 0 Normal operating mode(VCC >= 2.4V only)
*                                : 1 Low-voltage operating mode
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Power_Operation_Mode( uint8_t mode )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Control Register 1 (CTSUCR1) ******************************************************************/
            /* bit7-6  CTSU Measurement Mode Select                                                                   */
            /* bit5-4  CTSU Operating Clock Select                                                                    */
            /* bit3    CTSU Power Supply Capacity Adjustment                                                          */
            /* bit2    CTSU Power Supply Operating Mode Setting                                                       */
            /* bit1    CTSU LPF Capacitance Charging Control                                                          */
            /* bit0    CTSU Power Supply Enable                                                                       */
            /**********************************************************************************************************/
            CTSU.CTSUCR1.BIT.CTSUATUNE0  = mode;               /* Bit2(CTSUATUNE0) setting data storage               */
            status = SET_SUCCESS;
        }
    }
    return status;
}    /* End of function R_Set_CTSU_Power_Operation_Mode() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Power_Capacity_Adjustment
* Description  : 
* Arguments    : uint8_t mode    : 0 Normal output
*                                : 1 High-current output
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Power_Capacity_Adjustment( uint8_t mode )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Control Register 1 (CTSUCR1) ******************************************************************/
            /* bit7-6  CTSU Measurement Mode Select                                                                   */
            /* bit5-4  CTSU Operating Clock Select                                                                    */
            /* bit3    CTSU Power Supply Capacity Adjustment                                                          */
            /* bit2    CTSU Power Supply Operating Mode Setting                                                       */
            /* bit1    CTSU LPF Capacitance Charging Control                                                          */
            /* bit0    CTSU Power Supply Enable                                                                       */
            /**********************************************************************************************************/
            CTSU.CTSUCR1.BIT.CTSUATUNE1  = mode;               /* Bit3(CTSUATUNE1) setting data storage               */
            status = SET_SUCCESS;
        }
    }
    return status;
}    /* End of function R_Set_CTSU_Power_Capacity_Adjustment() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Operation_Clock
* Description  : 
* Arguments    : uint8_t mode    : 0 PCLK
*                                : 1 PCLK/2 (PCLK divided by 2)
*                                : 2 PCLK/4 (PCLK divided by 4)
*                                : 3 Setting prohibited
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Operation_Clock( uint8_t mode )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Control Register 1 (CTSUCR1) ******************************************************************/
            /* bit7-6  CTSU Measurement Mode Select                                                                   */
            /* bit5-4  CTSU Operating Clock Select                                                                    */
            /* bit3    CTSU Power Supply Capacity Adjustment                                                          */
            /* bit2    CTSU Power Supply Operating Mode Setting                                                       */
            /* bit1    CTSU LPF Capacitance Charging Control                                                          */
            /* bit0    CTSU Power Supply Enable                                                                       */
            /**********************************************************************************************************/
            switch (mode)
            {
                case _00_CTSUCLK_PCLK:
                case _01_CTSUCLK_PCLK_DIV2:
                case _10_CTSUCLK_PCLK_DIV4:
                    CTSU.CTSUCR1.BIT.CTSUCLK = mode;               /* Bit5,4(CTSUCLK) setting data storage            */
                    status = SET_SUCCESS;
                    break;
                default:
                    break;
            }
        }
    }
    return status;
}    /* End of function R_Set_CTSU_Operation_Clock() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Measurement_Mode
* Description  : This API sets mode of CTSU measurement.
* Arguments    : uint8_t mode    : 0 Self-capacitance single scan mode
*                                : 1 Self-capacitance multi-scan mode
*                                : 2 Setting prohibited
*                                : 3 Mutual capacitance full scan mode
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Measurement_Mode( uint8_t mode )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Control Register 1 (CTSUCR1) ******************************************************************/
            /* bit7-6  CTSU Measurement Mode Select                                                                   */
            /* bit5-4  CTSU Operating Clock Select                                                                    */
            /* bit3    CTSU Power Supply Capacity Adjustment                                                          */
            /* bit2    CTSU Power Supply Operating Mode Setting                                                       */
            /* bit1    CTSU LPF Capacitance Charging Control                                                          */
            /* bit0    CTSU Power Supply Enable                                                                       */
            /**********************************************************************************************************/
            switch (mode)
            {
                case _00_CTSUMD_SELF_SINGLE:
                case _01_CTSUMD_SELF_MULTI:
                case _11_CTSUMD_MUTUAL:
                    CTSU.CTSUCR1.BIT.CTSUMD  = mode;               /* Bit7,6(CTSUMD) setting data storage             */
                    status = SET_SUCCESS;
                    break;
                default:
                    break;
            }
        }
    }
    return status;
}    /* End of function R_Set_CTSU_Measurement_Mode() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Synchronous_Noise_Reduction
* Description  : 
* Arguments    : uint8_t cycle   : 3 Recommended setting value: 3 (0011b)
*              : uint8_t mode    : 0 510 pulses
*              :                 : 1 126 pulses
*              :                 : 2 62 pulses (recommended setting value)
*              :                 : 3 Setting prohibited
*              : uint8_t edge    : 0 High-pass noise reduction function turned on
*              :                 : 1 High-pass noise reduction function turned off
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Synchronous_Noise_Reduction( uint8_t cycle, uint8_t mode, uint8_t edge )
{
    volatile uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Synchronous Noise Reduction Setting Register (CTSUSDPRS) **************************************/
            /* bit7    Reserved                                                                                       */
            /* bit6    CTSU High-Pass Noise Reduction Function Off Setting                                            */
            /* bit5-4  CTSU Base Period and Pulse Count Setting                                                       */
            /* bit3-0  CTSU Measurement Time and Pulse Count Adjustment                                               */
            /**********************************************************************************************************/
            if (0x0F >= cycle)
            {
                CTSU.CTSUSDPRS.BIT.CTSUPRRATIO     = cycle;        /* Bit3-0(CTSUPRRATIO) setting data storage        */
                status = SET_SUCCESS;
            }
            else
            {
                return status;
            }

            switch (mode)
            {
                case _00_CTSUPRMODE_510_PULSES:
                case _01_CTSUPRMODE_126_PULSES:
                case _10_CTSUPRMODE_62_PULSES:
                    CTSU.CTSUSDPRS.BIT.CTSUPRMODE  = mode;        /* Bit5,4(CTSUPRMODE) setting data storage          */
                    break;
                default:
                    status = SET_ERROR;
                    return status;
                    break;
            }

            if ((0 == edge) || (1 == edge))
            {
                CTSU.CTSUSDPRS.BIT.CTSUSOFF        = edge;        /* Bit6(CTSUSOFF) setting data storage              */
            }
            else
            {
                status = SET_ERROR;
                return status;
            }
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Synchronous_Noise_Reduction() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Sensor_Stabilization_Wait_Time
* Description  : 
* Arguments    : uint8_t time    : 0x10 The value of these bits should be fixed to 0x10 (00010000b).
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Sensor_Stabilization_Wait_Time( uint8_t time )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Sensor Stabilization Wait Control Register (CTSUSST) ******************************************/
            /* bit7-0    CTSU Sensor Stabilization Wait Control                                                       */
            /**********************************************************************************************************/
            if (0x10 == time)
            {
                CTSU.CTSUSST.BYTE = time;                         /* Bit7-0(CTSUSST) setting data storage             */
                status = SET_SUCCESS;
            }
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Sensor_Stabilization_Wait_Time() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Measurement_Channel
* Description  : Self-measurement channel setting.
* Arguments    : uint8_t channel
* Return Value : uint8_t status  : 0 SET_SUCCESS
*              :                 : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Measurement_Channel( uint8_t channel )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Measurement Channel Register 0 (CTSUMCH0) *****************************************************/
            /* bit7-4  Reserved                                                                                       */
            /* bit3-0  CTSU Measurement Channel 0                                                                     */
            /**********************************************************************************************************/
            if (_00_CTSUMD_SELF_SINGLE == CTSU.CTSUCR1.BIT.CTSUMD)
            {
                CTSU.CTSUMCH0.BYTE = channel;                     /* Bit3-0(CTSUMCH0) setting data storage            */
                status = SET_SUCCESS;
            }
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Measurement_Channel() */

/***********************************************************************************************************************
* Function Name: R_Get_CTSU_Transmit_Channel
* Description  : 
* Arguments    : None
* Return Value : uint8_t transmit_ts    0-11 : 
***********************************************************************************************************************/
uint8_t R_Get_CTSU_Transmit_Channel( void )
{
    uint8_t transmit_ts;

    transmit_ts  = 0xFF;

    /* CTSU Measurement Channel Register 1 (CTSUMCH1)
    b3-0    CTSU Measurement Channel 1        */
    if (_11_CTSUMD_MUTUAL == CTSU.CTSUCR1.BIT.CTSUMD)
    {
        transmit_ts = CTSU.CTSUMCH1.BYTE;                //    CTSU Measurement Channel 1
    }

    return transmit_ts;
}    /* End of function R_Get_CTSU_Transmit_Channel() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Channel_Enable0
* Description  : 
* Arguments    : uint16_t channel  :
* Return Value : uint8_t status    : 0 SET_SUCCESS
*              :                   : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Channel_Enable0( uint16_t channel )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Channel Enable Control Register 0 (CTSUCHAC0) *************************************************/
            /*                                         100pin         80pin  64pin         48pin                      */
            /* bit7    TS7 Measurement target select  ( RX113, RX231, RX130,        RX130,        RX130 )             */
            /* bit6    TS6 Measurement target select  ( RX113, RX231, RX130,        RX130,        RX130 )             */
            /* bit5    TS5 Measurement target select  ( RX113, RX231, RX130,        RX130,        RX130 )             */
            /* bit4    TS4 Measurement target select  ( RX113, RX231, RX130,        RX130,        RX130 )             */
            /* bit3    TS3 Measurement target select  ( RX113, RX231, RX130, RX231, RX130, RX231, RX130 )             */
            /* bit2    TS2 Measurement target select  ( RX113, RX231, RX130, RX231, RX130, RX231, RX130 )             */
            /* bit1    TS1 Measurement target select  ( RX113, RX231, RX130,        RX130,        RX130 )             */
            /* bit0    TS0 Measurement target select  ( RX113, RX231, RX130,        RX130,              )             */
            /**********************************************************************************************************/

            /***** CTSU Channel Enable Control Register 1 (CTSUCHAC1) *************************************************/
            /*                                          100pin         80pin  64pin         48pin                     */
            /* bit7    TS15 Measurement target select  (        RX231, RX130, RX231, RX130,        RX130 )            */
            /* bit6    TS14 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit5    TS13 Measurement target select  (        RX231, RX130, RX231, RX130, RX231, RX130 )            */
            /* bit4    TS12 Measurement target select  (        RX231, RX130, RX231, RX130, RX231        )            */
            /* bit3    TS11 Measurement target select  ( RX113,        RX130,        RX130               )            */
            /* bit2    TS10 Measurement target select  ( RX113,        RX130,        RX130,        RX130 )            */
            /* bit1    TS9  Measurement target select  ( RX113, RX231, RX130,        RX130,        RX130 )            */
            /* bit0    TS8  Measurement target select  ( RX113, RX231, RX130,        RX130,        RX130 )            */
            /**********************************************************************************************************/
            CTSU.CTSUCHAC0.BYTE  = (uint8_t)channel;              /* Bit7-0(CTSUCHAC0) setting                        */
            CTSU.CTSUCHAC1.BYTE  = (uint8_t)(channel >> 8);       /* Bit7-0(CTSUCHAC1) setting                        */
            status = SET_SUCCESS;
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Channel_Enable0() */

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Channel_Enable1
* Description  : 
* Arguments    : uint16_t channel  :
* Return Value : uint8_t status    : 0 SET_SUCCESS
*              :                   : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Channel_Enable1( uint16_t channel )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Channel Enable Control Register 1 (CTSUCHAC2) *************************************************/
            /*                                          100pin         80pin  64pin         48pin                     */
            /* bit7    TS23 Measurement target select  (        RX231, RX130, RX231,        RX231        )            */
            /* bit6    TS22 Measurement target select  (        RX231, RX130, RX231, RX130, RX231, RX130 )            */
            /* bit5    TS21 Measurement target select  (               RX130                             )            */
            /* bit4    TS20 Measurement target select  (        RX231, RX130,        RX130,        RX130 )            */
            /* bit3    TS19 Measurement target select  (        RX231, RX130,        RX130,              )            */
            /* bit2    TS18 Measurement target select  (        RX231, RX130,        RX130,              )            */
            /* bit1    TS17 Measurement target select  (        RX231, RX130, RX231, RX130               )            */
            /* bit0    TS16 Measurement target select  (        RX231, RX130, RX231, RX130               )            */
            /**********************************************************************************************************/

            /***** CTSU Channel Enable Control Register 1 (CTSUCHAC3) *************************************************/
            /*                                          100pin         80pin  64pin         48pin                     */
            /* bit7    TS31 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit6    TS30 Measurement target select  (        RX231, RX130, RX231                      )            */
            /* bit5    TS29 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit4    TS28 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit3    TS27 Measurement target select  (        RX231, RX130, RX231                      )            */
            /* bit2    TS26 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit1    TS25 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit0    TS24 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /**********************************************************************************************************/
            CTSU.CTSUCHAC2.BYTE  = (uint8_t)channel;              /* Bit7-0(CTSUCHAC2) setting                        */
            CTSU.CTSUCHAC3.BYTE  = (uint8_t)(channel >> 8);       /* Bit7-0(CTSUCHAC3) setting                        */
            status = SET_SUCCESS;
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Channel_Enable1() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Channel_Enable2
* Description  : 
* Arguments    : uint16_t channel  :
* Return Value : uint8_t status    : 0 SET_SUCCESS
*              :                   : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Channel_Enable2( uint16_t channel )
{
    uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Channel Enable Control Register 4 (CTSUCHAC4) *************************************************/
            /*                                           100pin         80pin  64pin         48pin                    */
            /* bit7    Reserved                                                                                       */
            /* bit6    Reserved                                                                                       */
            /* bit5    Reserved                                                                                       */
            /* bit4    Reserved                                                                                       */
            /* bit3    TS35 Measurement target select  (        RX231, RX130,        RX130,        RX130 )            */
            /* bit2    TS34 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit1    TS33 Measurement target select  (               RX130,        RX130,        RX130 )            */
            /* bit0    TS32 Measurement target select  (        RX231, RX130,        RX130               )            */
            /**********************************************************************************************************/
            CTSU.CTSUCHAC4.BYTE  = (uint8_t)(channel & 0x0F);             /* Bit7-0(CTSUCHAC4) setting                */
            status = SET_SUCCESS;
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Channel_Enable2() */
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Channel_Transmit_Receive0
* Description  : 
* Arguments    : uint16_t channel  :
* Return Value : uint8_t status    : 0 SET_SUCCESS
*              :                   : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Channel_Transmit_Receive0( uint16_t channel )
{
    uint8_t  status;
#if (MCU_SERIES_T == R5F5130)
    uint16_t storage_ch;
    uint16_t cmp_ch;
#endif    // (MCU_SERIES_T == R5F5130)

    status     = SET_ERROR;
#if (MCU_SERIES_T == R5F5130)
    storage_ch = 0x0000;
    cmp_ch     = 0x0000;
#endif    // (MCU_SERIES_T == R5F5130)

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
#if (MCU_SERIES_T == R5F5130)
            if (_0_CTSUTXVSEL_VCC == CTSU.CTSUCR0.BIT.CTSUTXVSEL)
            {
                /***** CTSU Channel Transmit/Receive Control Register 0 (CTSUCHTRC0) **********************************/
                /*                                                 100pin         80pin  64pin         48pin          */
                /* bit7    TS7 Reception or Transmission select  ( RX113, RX231, RX130,        RX130,        RX130 )  */
                /* bit6    TS6 Reception or Transmission select  ( RX113, RX231, RX130,        RX130,        RX130 )  */
                /* bit5    TS5 Reception or Transmission select  ( RX113, RX231, RX130,        RX130,        RX130 )  */
                /* bit4    TS4 Reception or Transmission select  ( RX113, RX231, RX130,        RX130,        RX130 )  */
                /* bit3    TS3 Reception or Transmission select  ( RX113, RX231, RX130, RX231, RX130, RX231, RX130 )  */
                /* bit2    TS2 Reception or Transmission select  ( RX113, RX231, RX130, RX231, RX130, RX231, RX130 )  */
                /* bit1    TS1 Reception or Transmission select  ( RX113, RX231, RX130,        RX130,        RX130 )  */
                /* bit0    TS0 Reception or Transmission select  ( RX113, RX231, RX130,        RX130,              )  */
                /******************************************************************************************************/

                /***** CTSU Channel Transmit/Receive Control Register 1 (CTSUCHTRC1) **********************************/
                /*                                                  100pin         80pin  64pin         48pin         */
                /* bit7    TS15 Reception or Transmission select  (        RX231, RX130, RX231, RX130,        RX130 ) */
                /* bit6    TS14 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit5    TS13 Reception or Transmission select  (        RX231, RX130, RX231, RX130, RX231, RX130 ) */
                /* bit4    TS12 Reception or Transmission select  (        RX231, RX130, RX231, RX130, RX231        ) */
                /* bit3    TS11 Reception or Transmission select  ( RX113,        RX130,        RX130               ) */
                /* bit2    TS10 Reception or Transmission select  ( RX113,        RX130,        RX130,        RX130 ) */
                /* bit1    TS9  Reception or Transmission select  ( RX113, RX231, RX130,        RX130,        RX130 ) */
                /* bit0    TS8  Reception or Transmission select  ( RX113, RX231, RX130,        RX130,        RX130 ) */
                /******************************************************************************************************/
                CTSU.CTSUCHTRC0.BYTE = (uint8_t)channel;                  /* Bit7-0(CTSUCHTRC0) setting               */
                CTSU.CTSUCHTRC1.BYTE = (uint8_t)(channel >> 8);           /* Bit7-0(CTSUCHTRC1) setting               */
                status = SET_SUCCESS;
            }
            else
            {
                storage_ch = channel;
                cmp_ch     = channel & 0xE7E0;

                if (cmp_ch == storage_ch)
                {
                    CTSU.CTSUCHTRC0.BYTE = (uint8_t)channel;              /* Bit7-0(CTSUCHTRC0) setting               */
                    CTSU.CTSUCHTRC1.BYTE = (uint8_t)(channel >> 8);       /* Bit7-0(CTSUCHTRC1) setting               */
                    status = SET_SUCCESS;
                }
            }
#else
            CTSU.CTSUCHTRC0.BYTE = (uint8_t)channel;                      /* Bit7-0(CTSUCHTRC0) setting               */
            CTSU.CTSUCHTRC1.BYTE = (uint8_t)(channel >> 8);               /* Bit7-0(CTSUCHTRC1) setting               */
            status = SET_SUCCESS;
#endif    // (MCU_SERIES_T == R5F5130)
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Channel_Transmit_Receive0() */

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Channel_Transmit_Receive1
* Description  : 
* Arguments    : uint16_t channel  :
* Return Value : uint8_t status    : 0 SET_SUCCESS
*              :                   : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Channel_Transmit_Receive1( uint16_t channel )
{
    uint8_t  status;
#if (MCU_SERIES_T == R5F5130)
    uint16_t storage_ch;
    uint16_t cmp_ch;
#endif    // (MCU_SERIES_T == R5F5130)

    status     = SET_ERROR;
#if (MCU_SERIES_T == R5F5130)
    storage_ch = 0x0000;
    cmp_ch     = 0x0000;
#endif    // (MCU_SERIES_T == R5F5130)

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
#if (MCU_SERIES_T == R5F5130)
            if (_0_CTSUTXVSEL_VCC == CTSU.CTSUCR0.BIT.CTSUTXVSEL)
            {
                /***** CTSU Channel Transmit/Receive Control Register 2 (CTSUCHTRC2) **********************************/
                /*                                                  100pin         80pin  64pin         48pin         */
                /* bit7    TS23 Reception or Transmission select  (        RX231, RX130, RX231,        RX231        ) */
                /* bit6    TS22 Reception or Transmission select  (        RX231, RX130, RX231, RX130, RX231, RX130 ) */
                /* bit5    TS21 Reception or Transmission select  (               RX130                             ) */
                /* bit4    TS20 Reception or Transmission select  (        RX231, RX130,        RX130,        RX130 ) */
                /* bit3    TS19 Reception or Transmission select  (        RX231, RX130,        RX130,              ) */
                /* bit2    TS18 Reception or Transmission select  (        RX231, RX130,        RX130,              ) */
                /* bit1    TS17 Reception or Transmission select  (        RX231, RX130, RX231, RX130               ) */
                /* bit0    TS16 Reception or Transmission select  (        RX231, RX130, RX231, RX130               ) */
                /******************************************************************************************************/

                /***** CTSU Channel Transmit/Receive Control Register 3 (CTSUCHTRC3) **********************************/
                /*                                                  100pin         80pin  64pin         48pin         */
                /* bit7    TS31 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit6    TS30 Reception or Transmission select  (        RX231, RX130, RX231                      ) */
                /* bit5    TS29 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit4    TS28 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit3    TS27 Reception or Transmission select  (        RX231, RX130, RX231                      ) */
                /* bit2    TS26 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit1    TS25 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit0    TS24 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /******************************************************************************************************/
                CTSU.CTSUCHTRC2.BYTE = (uint8_t)channel;                  /* Bit7-0(CTSUCHTRC2) setting               */
                CTSU.CTSUCHTRC3.BYTE = (uint8_t)(channel >> 8);           /* Bit7-0(CTSUCHTRC3) setting               */
                status = SET_SUCCESS;
            }
            else
            {
                storage_ch = channel;
                cmp_ch     = channel & 0x3750;

                if (cmp_ch == storage_ch)
                {
                    CTSU.CTSUCHTRC2.BYTE = (uint8_t)channel;              /* Bit7-0(CTSUCHTRC2) setting               */
                    CTSU.CTSUCHTRC3.BYTE = (uint8_t)(channel >> 8);       /* Bit7-0(CTSUCHTRC3) setting               */
                    status = SET_SUCCESS;
                }
            }
#else
            CTSU.CTSUCHTRC2.BYTE = (uint8_t)channel;                      /* Bit7-0(CTSUCHTRC2) setting               */
            CTSU.CTSUCHTRC3.BYTE = (uint8_t)(channel >> 8);               /* Bit7-0(CTSUCHTRC3) setting               */
            status = SET_SUCCESS;
#endif    // (MCU_SERIES_T == R5F5130)
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Channel_Transmit_Receive1() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Channel_Transmit_Receive2
* Description  : 
* Arguments    : uint16_t channel  :
* Return Value : uint8_t status    : 0 SET_SUCCESS
*              :                   : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_Channel_Transmit_Receive2( uint16_t channel )
{
    uint8_t  status;
#if (MCU_SERIES_T == R5F5130)
    uint16_t storage_ch;
    uint16_t cmp_ch;
#endif    // (MCU_SERIES_T == R5F5130)

    status     = SET_ERROR;
#if (MCU_SERIES_T == R5F5130)
    storage_ch = 0x0000;
    cmp_ch     = 0x0000;
#endif    // (MCU_SERIES_T == R5F5130)

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
#if (MCU_SERIES_T == R5F5130)
            if (_0_CTSUTXVSEL_VCC == CTSU.CTSUCR0.BIT.CTSUTXVSEL)
            {
                /***** CTSU Channel Transmit/Receive Control Register 4 (CTSUCHTRC4) **********************************/
                /*                                                  100pin         80pin  64pin         48pin         */
                /* bit7    Reserved                                                                                   */
                /* bit6    Reserved                                                                                   */
                /* bit5    Reserved                                                                                   */
                /* bit4    Reserved                                                                                   */
                /* bit3    TS35 Reception or Transmission select  (        RX231, RX130,        RX130,        RX130 ) */
                /* bit2    TS34 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit1    TS33 Reception or Transmission select  (               RX130,        RX130,        RX130 ) */
                /* bit0    TS32 Reception or Transmission select  (        RX231, RX130,        RX130               ) */
                /******************************************************************************************************/
                CTSU.CTSUCHTRC4.BYTE = (uint8_t)(channel & 0x0F);         /* Bit7-0(CTSUCHTRC4) setting               */
                status = SET_SUCCESS;
            }
            else
            {
                storage_ch = channel;
                cmp_ch     = channel & 0x0000;

                if (cmp_ch == storage_ch)
                {
                    CTSU.CTSUCHTRC4.BYTE = (uint8_t)channel;             /* Bit7-0(CTSUCHTRC4) setting                */
                    status = SET_SUCCESS;
                }
            }
#else
            CTSU.CTSUCHTRC4.BYTE = (uint8_t)channel;                     /* Bit7-0(CTSUCHTRC4) setting                */
            status = SET_SUCCESS;
#endif    // (MCU_SERIES_T == R5F5130)
        }
    }

    return status;
}    /* End of function R_Set_CTSU_Channel_Transmit_Receive2() */
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_High_Pass_Noise_Reduction
* Description  : 
* Arguments    : uint8_t mode      : 0 These bits should be set to 00b.
*              : uint8_t clock     : 3 These bits should be set to 11b.
* Return Value : uint8_t status    : 0 SET_SUCCESS
*              :                   : 1 SET_ERROR
***********************************************************************************************************************/
uint8_t R_Set_CTSU_High_Pass_Noise_Reduction( uint8_t mode, uint8_t clock )
{
    volatile uint8_t status;

    status = SET_ERROR;

    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Channel Transmit/Receive Control Register 0 (CTSUCHTRC0) **************************************/
            /* bit7-6  Reserved                                                                                       */
            /* bit5-4  CTSU Diffusion Clock Control                                                                   */
            /* bit3-2  Reserved                                                                                       */
            /* bit1-0  CTSU Diffusion Clock Mode Select                                                               */
            /**********************************************************************************************************/
            if (0x00 == mode)
            {
                CTSU.CTSUDCLKC.BIT.CTSUSSMOD = mode;              /* Bit1,0(CTSUSSMOD) setting                        */
                status = SET_SUCCESS;
            }
            else
            {
                return status;
            }

            if (0x03 == clock)
            {
                CTSU.CTSUDCLKC.BIT.CTSUSSCNT = clock;             /* Bit5,4(CTSUSSCNT) setting                        */
            }
            else
            {
                status = SET_ERROR;
                return status;
            }
        }
    }

    return status;
}    /* End of function R_Set_CTSU_High_Pass_Noise_Reduction() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_Correction_Mode
* Description  : 
* Arguments    : uint8_t mode    : 0 Normal mode    1 Test mode
* Return Value : none
***********************************************************************************************************************/
void R_Set_CTSU_Correction_Mode( uint8_t mode )
{
    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD10)
    {
        if (0 == CTSU.CTSUCR0.BIT.CTSUSTRT)
        {
            /***** CTSU Channel Transmit/Receive Control Register 0 (CTSUCHTRC0) **************************************/
            /* bit15   TSCAP Voltage Error Flag                                                                       */
            /* bit14-8 Reserved                                                                                       */
            /* bit7    CTSU Test Mode Select                                                                          */
            /* bit6-2  Reserved                                                                                       */
            /* bit1-0  CTSU Reference Current Test Mode (VDC Stop)                                                    */
            /**********************************************************************************************************/
            if (0 == mode)
            {
                CTSU.CTSUERRS.BIT.CTSUTSOC = 0;                       /* Bit7(CTSUTSOC)   setting                     */
                CTSU.CTSUERRS.BIT.CTSUSPMD = 0;                       /* Bit1,0(CTSUSPMD) setting                     */
            }
            else
            {
                CTSU.CTSUERRS.BIT.CTSUTSOC = 1;                       /* Bit7(CTSUTSOC)   setting                     */
                CTSU.CTSUERRS.BIT.CTSUSPMD = 2;                       /* Bit1,0(CTSUSPMD) setting                     */
            }
        }
    }
}    /* End of function R_Set_CTSU_Correction_Mode() */

/***********************************************************************************************************************
* Function Name: R_Get_CTSU_Measurement_Status
* Description  : 
* Arguments    : None
* Return Value : uint8_t status    : CTSUST Register's CTSUSTC Symbol
***********************************************************************************************************************/
uint8_t R_Get_CTSU_Measurement_Status( void )
{
    uint8_t status;

    /***** CTSU Channel Transmit/Receive Control Register 1 (CTSUCHTRC1) **********************************************/
    /* bit7    CTSU Mutual Capacitance Status Flag                                                                    */
    /* bit6    CTSU Reference Counter Overflow Flag                                                                   */
    /* bit5    CTSU Sensor Counter Overflow Flag                                                                      */
    /* bit4    CTSU Data Transfer Status Flag                                                                         */
    /* bit3    Reserved                                                                                               */
    /* bit2-0  CTSU Measurement Status Counter                                                                        */
    /******************************************************************************************************************/
    status = CTSU.CTSUST.BIT.CTSUSTC;                              /* Bit2-0(CTSUSTC) reading data storage            */
    return status;
}    /* End of function R_Get_CTSU_Measurement_Status() */

/***********************************************************************************************************************
* Function Name: R_Get_CTSU_Data_Transfer_flag
* Description  : 
* Arguments    : None
* Return Value : uint8_t    flag    0 : Measurement result has been read
*              :                    1 : Measurement result has not been read
***********************************************************************************************************************/
uint8_t R_Get_CTSU_Data_Transfer_flag( void )
{
    uint8_t flag;

    /***** CTSU Channel Transmit/Receive Control Register 1 (CTSUCHTRC1) **********************************************/
    /* bit7    CTSU Mutual Capacitance Status Flag                                                                    */
    /* bit6    CTSU Reference Counter Overflow Flag                                                                   */
    /* bit5    CTSU Sensor Counter Overflow Flag                                                                      */
    /* bit4    CTSU Data Transfer Status Flag                                                                         */
    /* bit3    Reserved                                                                                               */
    /* bit2-0  CTSU Measurement Status Counter                                                                        */
    /******************************************************************************************************************/
    flag = CTSU.CTSUST.BIT.CTSUDTSR;                               /* Bit4(CTSUDTSR) reading data storage             */
    return flag;
}    /* End of function R_Get_CTSU_Data_Transfer_flag() */

/***********************************************************************************************************************
* Function Name: R_Get_CTSU_Counter_Overflow_flag
* Description  : 
* Arguments    : None
* Return Value : uint8_t flag    bit1 CTSU Reference Counter Overflow Flag    0 : No overflow
*              :                                                              1 : An overflow
*              :                 bit0 CTSU Sensor Counter Overflow Flag       0 : No overflow
*              :                                                              1 : An overflow
***********************************************************************************************************************/
uint8_t R_Get_CTSU_Counter_Overflow_flag( void )
{
    uint8_t flag;

    /***** CTSU Channel Transmit/Receive Control Register 1 (CTSUCHTRC1) **********************************************/
    /* bit7    CTSU Mutual Capacitance Status Flag                                                                    */
    /* bit6    CTSU Reference Counter Overflow Flag                                                                   */
    /* bit5    CTSU Sensor Counter Overflow Flag                                                                      */
    /* bit4    CTSU Data Transfer Status Flag                                                                         */
    /* bit3    Reserved                                                                                               */
    /* bit2-0  CTSU Measurement Status Counter                                                                        */
    /******************************************************************************************************************/
    flag = CTSU.CTSUST.BYTE >> 5;                      /* CTSUST Register value 5 right sift reading data storage     */
    flag = flag & 0x03;                                /* bit1,bit0 without mask                                      */
    return flag;
}    /* End of function R_Get_CTSU_Counter_Overflow_flag() */

/***********************************************************************************************************************
* Function Name: CTSUGetTscapVoltageError
* Description  : This API reads the value in [CTSU Error Status Register (CTSUERRS)].
* Arguments    : None
* Return Value : data
***********************************************************************************************************************/
uint8_t CTSUGetTscapVoltageError( void )
{
    /* CTSU Error Status Register (CTSUERRS)
    b15        CTSU TSCAP voltage error
    b14-0    Reserved    */
    return(CTSU.CTSUERRS.BIT.CTSUICOMP);                    //    CTSU Error Status Register (CTSUICOMP)
}

/***********************************************************************************************************************
* Function Name: R_Set_CTSUMCH1
* Description  : This API writes the value in [CTSU Measurement Channel Register 1 (CTSUMCH1)].
* Arguments    : data
* Return Value : None
***********************************************************************************************************************/
void R_Set_CTSUMCH1( uint8_t data )
{
    /* CTSU Measurement Channel Register 1 (CTSUMCH1)
    b4-7    Reserved
    b3-0    CTSU Measurement Channel 1        */
    CTSU.CTSUMCH1.BYTE = data;                //    CTSU Measurement Channel Register 1 (CTSUMCH1)
}

/***********************************************************************************************************************
* Function Name: R_Get_CTSUMCH1
* Description  : This API reads the value in [CTSU Measurement Channel Register 1 (CTSUMCH1)].
* Arguments    : None
* Return Value : data
***********************************************************************************************************************/
uint8_t R_Get_CTSUMCH1( void )
{
    /* CTSU Measurement Channel Register 1 (CTSUMCH1)
    b4-7    Reserved
    b3-0    CTSU Measurement Channel 1        */
    return( CTSU.CTSUMCH1.BYTE );                //    CTSU Measurement Channel Register 1 (CTSUMCH1)
}

/***********************************************************************************************************************
* Function Name: R_Set_CTSUSSC
* Description  : This API writes the value in [CTSU Spectrum Diffusion Control Register (CTSUSSC)].
* Arguments    : data
* Return Value : None
***********************************************************************************************************************/
void R_Set_CTSUSSC( uint16_t *g_write, uint8_t *g_index, uint16_t data, uint8_t ts ,uint8_t mode, uint8_t max_ts )
{
    /* CTSU Spectrum Diffusion Control Register (CTSUSSC)
    b15-12    Reserved
    b11-8    CTSU Spectrum Diffusion Sampling Cycle Control
    b7-0    Reserved        */
    if(_01_CTSUMD_SELF_MULTI == mode)
    {
        /* Fail safe */
        if( *(g_index + ts) >= max_ts )
        {
            return;
        }
        *(g_write + (*(g_index + ts) * 3) + 0) = data;
    }
    else
    {
        /* Fail safe */
        if( ts >= max_ts )
        {
            return;
        }
        *(g_write + (ts * 3) + 0) = data;
    }
}

/***********************************************************************************************************************
* Function Name: R_Get_CTSUSSC
* Description  : This API reads the value in [CTSU Spectrum Diffusion Control Register (CTSUSSC)].
* Arguments    : None
* Return Value : data
***********************************************************************************************************************/
uint16_t R_Get_CTSUSSC( uint16_t *g_write, uint8_t *g_index, uint8_t ts, uint8_t mode, uint8_t max_ts )
{
    /* CTSU Spectrum Diffusion Control Register (CTSUSSC)
    b15-12    Reserved
    b11-8    CTSU Spectrum Diffusion Sampling Cycle Control
    b7-0    Reserved        */
    if(_01_CTSUMD_SELF_MULTI == mode)
    {
        /* Fail safe */
        if( *(g_index + ts) >= max_ts )
        {
            return(0);
        }
        return( *(g_write + (*(g_index + ts) * 3) + 0) );    //    CTSU Spectrum Diffusion Control Register (CTSUSSC)
    }
    else
    {
        /* Fail safe */
        if( ts >= max_ts )
        {
            return(0);
        }
        return( *(g_write + (ts * 3) + 0) );                //    CTSU Spectrum Diffusion Control Register (CTSUSSC)
    }
}

/***********************************************************************************************************************
* Function Name: R_Set_CTSUSO0
* Description  : This API writes the value in [CTSU Sensor Offset Register 0 (CTSUSO0)].
* Arguments    : data
* Return Value : None
***********************************************************************************************************************/
void R_Set_CTSUSO0( uint16_t *g_write, uint8_t *g_index, uint16_t data, uint8_t ts, uint8_t mode, uint8_t max_ts )
{
    /* CTSU Sensor Offset Register 0 (CTSUSO0)
    b15-10    CTSU Measurement Count Setting
    b9-0    CTSU Sensor Offset Adjustment        */
    if(_01_CTSUMD_SELF_MULTI == mode)
    {
        /* Fail safe */
        if( *(g_index + ts) >= max_ts )
        {
            return;
        }
        *(g_write + (*(g_index + ts) * 3) + 1) = data;
    }
    else
    {
        /* Fail safe */
        if( ts >= max_ts )
        {
            return;
        }
        *(g_write + (ts * 3) + 1) = data;
    }
}

/***********************************************************************************************************************
* Function Name: R_Get_CTSUSO0
* Description  : This API writes the value in [CTSU Sensor Offset Register 0 (CTSUSO0)].
* Arguments    : None
* Return Value : data
***********************************************************************************************************************/
uint16_t R_Get_CTSUSO0( uint16_t *g_write, uint8_t *g_index, uint8_t ts, uint8_t mode, uint8_t max_ts )
{
    /* CTSU Sensor Offset Register 0 (CTSUSO0)
    b15-10    CTSU Measurement Count Setting
    b9-0    CTSU Sensor Offset Adjustment        */
    if(_01_CTSUMD_SELF_MULTI == mode)
    {
        /* Fail safe */
        if( *(g_index + ts) >= max_ts )
        {
            return(0);
        }
        return( *(g_write + (*(g_index + ts) * 3) + 1) );    //    CTSU Sensor Offset Register 0 (CTSUSO0)
    }
    else
    {
        /* Fail safe */
        if( ts >= max_ts )
        {
            return(0);
        }
        return (*(g_write + (ts * 3) + 1));    //    CTSU Sensor Offset Register 0 (CTSUSO0)
    }
}

/***********************************************************************************************************************
* Function Name: R_Set_CTSUSO1
* Description  : This API writes the value in [CTSU Sensor Offset Register 1 (CTSUSO1)].
* Arguments    : data
* Return Value : None
***********************************************************************************************************************/
void R_Set_CTSUSO1( uint16_t *g_write, uint8_t *g_index,uint16_t data, uint8_t ts , uint8_t mode, uint8_t max_ts )
{
    /* CTSU Sensor Offset Register 1 (CTSUSO1)
    b15        Reserved
    b14,13    CTSU ICO Gain Adjustment
    b12-8    CTSU Sensor Drive Pulse Division Control
    b7-0    CTSU Reference ICO Current Adjustment        */
    if(_01_CTSUMD_SELF_MULTI == mode)
    {
        /* Fail safe */
        if( *(g_index + ts) >= max_ts )
        {
            return;
        }
        *(g_write + (*(g_index + ts) * 3) + 2) = data;
    }
    else
    {
        /* Fail safe */
        if( ts >= max_ts )
        {
            return;
        }
        *(g_write + (ts * 3) + 2) = data;
    }
}

/***********************************************************************************************************************
* Function Name: R_Get_CTSUSO1
* Description  : This API reads the value in [CTSU Sensor Offset Register 1 (CTSUSO1)].
* Arguments    : None
* Return Value : data
***********************************************************************************************************************/
uint16_t R_Get_CTSUSO1( uint16_t *g_write, uint8_t *g_index, uint8_t ts, uint8_t mode, uint8_t max_ts )
{
    /* CTSU Sensor Offset Register 1 (CTSUSO1)
    b15        Reserved
    b14,13    CTSU ICO Gain Adjustment
    b12-8    CTSU Sensor Drive Pulse Division Control
    b7-0    CTSU Reference ICO Current Adjustment        */
    if(_01_CTSUMD_SELF_MULTI == mode)
    {
        /* Fail safe */
        if( *(g_index + ts) >= max_ts )
        {
            return(0);
        }
        return( *(g_write + (*(g_index + ts) * 3) + 2) );    //    CTSU Sensor Offset Register 1 (CTSUSO1)
    }
    else
    {
        /* Fail safe */
        if( ts >= max_ts )
        {
            return(0);
        }
        return( *(g_write + (ts * 3) + 2) );                //    CTSU Sensor Offset Register 1 (CTSUSO1)
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
