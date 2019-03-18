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
* File Name    : r_ctsu.c
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file controls Capacitive Touch.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/
#define __R_CTSU_C__

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
#include "r_cg_vect.h"
#include "r_mpc.h"
#include "r_dtc.h"
#include "r_ctsu.h"
#include "r_cgc.h"
#ifdef  SCI_SERIAL_USE
    #include "r_sci.h"
#endif  // SCI_SERIAL_USE

/* S/W include header */
#include "r_cg_userdefine.h"
#include "r_touch.h"
#include "r_touch_API.h"

#include "r_serial_control.h"
#include "IEC61000_CTSU.h"

/***********************************************************************************************************************
* Global variables and functions
***********************************************************************************************************************/
const uint8_t g_ctsu_txvsel[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    0,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_CTSUTXVSEL,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_CTSUTXVSEL,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_CTSUTXVSEL,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_CTSUTXVSEL,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_CTSUTXVSEL,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_CTSUTXVSEL,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_CTSUTXVSEL,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_CTSUTXVSEL
#endif
};

const uint8_t g_ctsu_atune0[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_CTSUATUNE0,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_CTSUATUNE0
#endif
};

const uint8_t g_ctsu_atune1[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_CTSUATUNE1,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_CTSUATUNE1
#endif
};

const uint8_t g_ctsu_prratio[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_CTSUPRRATIO,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_CTSUPRRATIO
#endif
};

const uint8_t g_ctsu_prmode[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_CTSUPRMODE,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_CTSUPRMODE
#endif
};

const uint8_t g_ctsu_soff[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_CTSUSOFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_CTSUSOFF
#endif
};

const uint16_t g_ctsu_correction_std[] = 
{
    _19_2UA, _18_0UA, _16_8UA, _15_6UA, _14_4UA, _13_2UA, _12_0UA, _10_8UA,
    _09_6UA, _08_4UA, _07_2UA, _06_0UA, _04_8UA, _03_6UA, _02_4UA, _01_2UA
};

/*===== DTC transmit data ========================================================*/
#if ( SELF_METHOD_NUM == 1 )
const uint16_t g_self_ctsussc[];
const uint16_t g_self_ctsuso0[];
const uint16_t g_self_ctsuso1[];
#endif    // ( SELF_METHOD_NUM == 1 )

/*=====    Mutual 0    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 0 )
const uint16_t g_mutual0_ctsussc[];
const uint16_t g_mutual0_ctsuso0[];
const uint16_t g_mutual0_ctsuso1[];
#endif    // ( MUTUAL_METHOD_NUM > 0 )

/*=====    Mutual 1    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 1 )
const uint16_t g_mutual1_ctsussc[];
const uint16_t g_mutual1_ctsuso0[];
const uint16_t g_mutual1_ctsuso1[];
#endif    // ( MUTUAL_METHOD_NUM > 1 )

/*=====    Mutual 2    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 2 )
const uint16_t g_mutual2_ctsussc[];
const uint16_t g_mutual2_ctsuso0[];
const uint16_t g_mutual2_ctsuso1[];
#endif  // ( MUTUAL_METHOD_NUM > 2 )

/*=====    Mutual 3    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 3 )
const uint16_t g_mutual3_ctsussc[];
const uint16_t g_mutual3_ctsuso0[];
const uint16_t g_mutual3_ctsuso1[];
#endif  // ( MUTUAL_METHOD_NUM > 3 )

/*=====    Mutual 4    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 4 )
const uint16_t g_mutual4_ctsussc[];
const uint16_t g_mutual4_ctsuso0[];
const uint16_t g_mutual4_ctsuso1[];
#endif  // ( MUTUAL_METHOD_NUM > 4 )

/*=====    Mutual 5    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 5 )
const uint16_t g_mutual5_ctsussc[];
const uint16_t g_mutual5_ctsuso0[];
const uint16_t g_mutual5_ctsuso1[];
#endif  // ( MUTUAL_METHOD_NUM > 5 )

/*=====    Mutual 6    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 6 )
const uint16_t g_mutual6_ctsussc[];
const uint16_t g_mutual6_ctsuso0[];
const uint16_t g_mutual6_ctsuso1[];
#endif  // ( MUTUAL_METHOD_NUM > 6 )

/*=====    Mutual 7    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 7 )
const uint16_t g_mutual7_ctsussc[];
const uint16_t g_mutual7_ctsuso0[];
const uint16_t g_mutual7_ctsuso1[];
#endif  // ( MUTUAL_METHOD_NUM > 7 )

/***********************************************************************************************************************
* Function Name: correction_CTSU_sensor_ico
* Description  : Sensor ICO gain correction initial setting.
* Arguments    : None
* Return Value : uint8_t ret_val    : SET_SUCCESS
*              :                    : _1_ERROR
***********************************************************************************************************************/
uint8_t correction_CTSU_sensor_ico( void )
{
    uint8_t ret_val;
    uint8_t correction_method;

    correction_method  = 0xFF;                                     /* Sensor ICO correction method number setting     */
    g_correction_mode  = _1_CORRECTION;                            /* Sensor ICO correction measurement mode setting  */
    g_correction_time  = _0_1ST;                                   /* 1st measurement flag setting                    */

    g_ctsutrimr_def    = R_Get_CTSU_current_trimming_val();        /* Current trimming value storage                  */

    while (0 != CTSU.CTSUCR0.BIT.CTSUSTRT)
    {
        /* Measurement finish wait */
    }

    ret_val = correction_CTSU_sensor_selection();                  /* Measurement channel selection for correction.   */
    if (SET_SUCCESS == ret_val)
    {
        while (_1_CORRECTION == g_correction_mode)
        {
            correction_CTSU_register_parameter_set();              /* CTSU register parameter setting for correction. */
            correction_CTSU_register_txd_set();                    /* CTSU correction parameter setting by DTC.       */
            DTC_Set_Initial_of_CTSU( correction_method );          /* Sensor ICO correction for DTC transfer setting. */
            correction_CTSU_register_set();                        /* CTSU sensor ICO correction register setting     */
            R_Set_CTSU_Correction_Mode(_1_CORRECTION);             /* Sensor ICO correction mesurement setting        */
            g_ctsu_soft_mode = CTSU_READY_MODE;                    /* CTSU masurement ready mode setting              */
            correction_CTSU_measurement_start();                   /* Sensor ICO gain correction measurement start    */
            if (_0_1ST == g_correction_time)
            {
                correction_CTSU_1st_coefficient_create();          /* 1st coefficient create                          */
                correction_CTSU_2nd_standard_val_create();         /* 2nd standard value create                       */
                g_correction_time = _1_2ND;                        /* 2nd measurement flag setting                    */
                R_Set_CTSU_current_trimming_val(0xFF);             /* 0xFF set in the current trimming register       */
            }
            else
            {
                correction_CTSU_2nd_coefficient_create();          /* 2nd coefficient create                          */
                correction_CTSU_16point_coefficient_create();      /* 16point coefficient create                      */
                R_Set_CTSU_current_trimming_val(g_ctsutrimr_def);  /* Return the current trimming register to the initial value */
                R_Set_CTSU_Correction_Mode(_0_NORMAL);             /* Sensor ICO normal mesurement setting            */
                g_correction_mode = _0_NORMAL;                     /* Sensor ICO normal measurement mode setting      */
            }
        }
    }

    return ret_val;
}    /* End of function correction_CTSU_sensor_ico() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_sensor_selection
* Description  : Sensor selection for correction.
* Arguments    : None
* Return Value : uint8_t ret_val    : SET_SUCCESS
*              :                    : _1_ERROR
***********************************************************************************************************************/
uint8_t correction_CTSU_sensor_selection( void )
{
    uint8_t loop_g;                                                   /* The loop of the touch sensor enable flag.    */
    uint8_t loop_ts;                                                  /* The loop of the touch sensor number.         */
    uint8_t cmp_val;                                                  /* The value to be compared.                    */
    uint8_t ena_ts;                                                   /* Enable touch sensor number                   */
    uint8_t sensor_enable[5];                                         /* CTSUCHAC0-4 storage buffer                   */
    uint8_t status;                                                   /* Return value                                 */

    status = _1_ERROR;

#if ( SELF_METHOD_NUM == 1 )
    sensor_enable[0] = CTSUCHAC0_SELF_ENABLE_TS;                      /* The self-capacitance CTSUCHAC0 register      */
    sensor_enable[1] = CTSUCHAC1_SELF_ENABLE_TS;                      /* The self-capacitance CTSUCHAC1 register      */
    sensor_enable[2] = CTSUCHAC2_SELF_ENABLE_TS;                      /* The self-capacitance CTSUCHAC2 register      */
    sensor_enable[3] = CTSUCHAC3_SELF_ENABLE_TS;                      /* The self-capacitance CTSUCHAC3 register      */
    sensor_enable[4] = CTSUCHAC4_SELF_ENABLE_TS;                      /* The self-capacitance CTSUCHAC4 register      */
#else
    sensor_enable[0] = CTSUCHTRC0_MUTUAL0_TRANSMIT_TS;              /* The mutual-capacitance CTSUCHAC0 register    */
    sensor_enable[1] = CTSUCHTRC1_MUTUAL0_TRANSMIT_TS;              /* The mutual-capacitance CTSUCHAC1 register    */
    sensor_enable[2] = CTSUCHTRC2_MUTUAL0_TRANSMIT_TS;              /* The mutual-capacitance CTSUCHAC2 register    */
    sensor_enable[3] = CTSUCHTRC3_MUTUAL0_TRANSMIT_TS;              /* The mutual-capacitance CTSUCHAC3 register    */
    sensor_enable[4] = CTSUCHTRC4_MUTUAL0_TRANSMIT_TS;              /* The mutual-capacitance CTSUCHAC4 register    */
#endif    // ( SELF_METHOD_NUM == 1 )

    for (loop_g = 0; loop_g < 5; loop_g++)
    {
        if (0 != sensor_enable[loop_g])                                           /* Enable flag check                */
        {
            for (loop_ts = 0, cmp_val = 0x01; loop_ts < 8; loop_ts++)             /* Touch sensor number loop         */
            {
                if (1 == status)                                                  /* Setting complete check           */
                {
                    ena_ts  = sensor_enable[loop_g] & cmp_val;
                    if (0 != ena_ts)                                              /* Enable bit check                 */
                    {
                        switch (loop_g)
                        {
                            case 0:
                                g_correction_ctsu_parm.ctsu_chac01 = (uint16_t)ena_ts;
                                status = SET_SUCCESS;
                                break;
                            case 1:
                                g_correction_ctsu_parm.ctsu_chac01 = (uint16_t)(ena_ts << 8);
                                status = SET_SUCCESS;
                                break;
                            case 2:
                                g_correction_ctsu_parm.ctsu_chac23 = (uint16_t)ena_ts;
                                status = SET_SUCCESS;
                                break;
                            case 3:
                                g_correction_ctsu_parm.ctsu_chac23 = (uint16_t)(ena_ts << 8);
                                status = SET_SUCCESS;
                                break;
                            case 4:
                                g_correction_ctsu_parm.ctsu_chac4 = (uint16_t)ena_ts;
                                status = SET_SUCCESS;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        cmp_val = cmp_val << 1;                                    /* Left sift                       */
                    }
                }
            }
        }
    }

    return status;
}    /* End of function correction_CTSU_measurement_sensor_select() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_register_parameter_set
* Description  : CTSU register parameter setting for correction.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void correction_CTSU_register_parameter_set( void )
{
    g_correction_ctsu_parm.ctsu_snz        = _0_CTSUSNZ_LOW_POWER_DISABLE;
    g_correction_ctsu_parm.ctsu_txvsel     = _0_CTSUTXVSEL_VCC;
    g_correction_ctsu_parm.ctsu_pon        = _1_CTSUPON_HW_POWER_ON;
    g_correction_ctsu_parm.ctsu_sw         = _1_CTSUCSW_ON;
    g_correction_ctsu_parm.ctsu_atune0     = _0_CTSUATUNE0_NORMAL;
    g_correction_ctsu_parm.ctsu_clk        = _00_CTSUCLK_PCLK;
    g_correction_ctsu_parm.ctsu_atune1     = _0_CTSUATUNE1_NORMAL;
    g_correction_ctsu_parm.ctsu_md         = _01_CTSUMD_SELF_MULTI;
    g_correction_ctsu_parm.ctsu_prratio    = _0011_CTSUPRRATIO_RECOMMEND;
    g_correction_ctsu_parm.ctsu_prmode     = _10_CTSUPRMODE_62_PULSES;
    g_correction_ctsu_parm.ctsu_soff       = _0_CTSUSOFF_ON;
    g_correction_ctsu_parm.ctsu_sst        = _00010000_CTSUSST_RECOMMEND;
    g_correction_ctsu_parm.ctsu_ssmod      = _00_CTSUSSMOD;
    g_correction_ctsu_parm.ctsu_sscnt      = _11_CTSUSSCNT;
}    /* End of function correction_CTSU_register_parameter_set() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_register_txd_set
* Description  : CTSU correction parameters transmit setting by DTC.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void correction_CTSU_register_txd_set( void )
{
    if (0 == g_correct_value_measure)
    {
        g_correction_dtc_txd[0] = 0x0700;
        g_correction_dtc_txd[1] = 0x0000;
        switch (CTSU_INPUT_FREQUENCY_DIV)
        {
            case 32:
                g_correction_dtc_txd[2] = 0x3F0F;                                    /* 32 / 64 = 0.5MHz              */
                break;
            case 27:
                g_correction_dtc_txd[2] = 0x3A0F;                                    /* 27 / 54 = 0.5MHz              */
                break;
            case 24:
                g_correction_dtc_txd[2] = 0x370F;                                    /* 24 / 48 = 0.5MHz              */
                break;
            case 16:
                g_correction_dtc_txd[2] = 0x2F0F;                                    /* 16 / 32 = 0.5MHz              */
                break;
            case 8:
                g_correction_dtc_txd[2] = 0x270F;                                    /*  8 / 16 = 0.5MHz              */
                break;
            default:
                break;
        }
    }
}    /* End of function correction_CTSU_register_txd_set() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_register_set
* Description  : CTSU register settings for the sensor ICO correction.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint16_t correction_CTSU_register_set( void )
{
    volatile uint16_t ret_val;
    volatile uint16_t status;

    status = 0;

    /* TSCAP Capacitor discharge setting */
    R_Set_CTSU_TSCAP_Discharge();

#if (MCU_SERIES_T == R5F5113)
    /* Multi-Function Pin Controller setting */
    MPC_CTSU_set( g_correction_ctsu_parm.ctsu_chac01, 0, 0 );
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
    /* Multi-Function Pin Controller setting */
    MPC_CTSU_set( g_correction_ctsu_parm.ctsu_chac01, g_correction_ctsu_parm.ctsu_chac23, g_correction_ctsu_parm.ctsu_chac4 );
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)

    /* Operation mode Register change protect off setting */
    R_Set_CTSU_Module_Operation(_0_MSTPD10_CTSU_ENABLE);

#if (MCU_SERIES_T == R5F5130)
    /* CTSU transmit power supply set process call */
    ret_val = R_Set_CTSU_Transmit_Power_Supply(g_correction_ctsu_parm.ctsu_txvsel);
    status = ret_val;
#endif    // (MCU_SERIES_T == R5F5130)

    /* CTSU analog adjustment Signal0 set process call */
    ret_val = R_Set_CTSU_Power_Operation_Mode(g_correction_ctsu_parm.ctsu_atune0);
    status  = status | (ret_val << 1);

    /* CTSU analog adjustment Signal1 set  process call */
    ret_val = R_Set_CTSU_Power_Capacity_Adjustment(g_correction_ctsu_parm.ctsu_atune1);
    status  = status | (ret_val << 2);

    /* CTSU count Source select process call */
    ret_val = R_Set_CTSU_Operation_Clock(g_correction_ctsu_parm.ctsu_clk);
    status  = status | (ret_val << 3);

    /* CTSU sensor wait time set process call */
    ret_val = R_Set_CTSU_Sensor_Stabilization_Wait_Time(g_correction_ctsu_parm.ctsu_sst);
    status  = status | (ret_val << 4);

    /* CTSU hard macro power supply switch change process call */
    ret_val = R_Set_CTSU_Power_Supply(g_correction_ctsu_parm.ctsu_pon);
    status  = status | (ret_val << 5);

    /* CTSU measurement mode select process call */
    ret_val = R_Set_CTSU_Measurement_Mode(g_correction_ctsu_parm.ctsu_md);
    status  = status | (ret_val << 6);

    /* CTSU Sensor Drive Pulse Spectrum Diffusion Setting Register (CTSUSDPRS) */
    ret_val = R_Set_CTSU_Synchronous_Noise_Reduction(g_correction_ctsu_parm.ctsu_prratio, g_correction_ctsu_parm.ctsu_prmode, g_correction_ctsu_parm.ctsu_soff);
    status  = status | (ret_val << 7);

    /* CTSU measurement channel set process call */
    ret_val = R_Set_CTSU_Measurement_Channel(g_correction_ctsu_parm.ctsu_mch0);

    /* CTSU channel enable set process call */
    ret_val = R_Set_CTSU_Channel_Enable0(g_correction_ctsu_parm.ctsu_chac01);
    status  = status | (ret_val << 9);

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
    ret_val = R_Set_CTSU_Channel_Enable1(g_correction_ctsu_parm.ctsu_chac23);
    status  = status | (ret_val << 10);
    ret_val = R_Set_CTSU_Channel_Enable2(g_correction_ctsu_parm.ctsu_chac4);
    status  = status | (ret_val << 11);
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)

    /* CTSU Channel transmit/receive control process call */
    ret_val = R_Set_CTSU_Channel_Transmit_Receive0(g_correction_ctsu_parm.ctsu_chtrc01);
    status  = status | (ret_val << 12);

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
    ret_val = R_Set_CTSU_Channel_Transmit_Receive1(g_correction_ctsu_parm.ctsu_chtrc23);
    status  = status | (ret_val << 13);
    ret_val = R_Set_CTSU_Channel_Transmit_Receive2(g_correction_ctsu_parm.ctsu_chtrc4);
    status  = status | (ret_val << 14);
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)

    /* CTSU diffusion clock mode and oscillation frequency select process call */
    ret_val = R_Set_CTSU_High_Pass_Noise_Reduction(g_correction_ctsu_parm.ctsu_ssmod, g_correction_ctsu_parm.ctsu_sscnt);
    status  = status | (ret_val << 15);

    return status;
}    /* End of function correction_CTSU_register_set() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_measurement_start
* Description  : Sensor ICO gain correction measurement start.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void correction_CTSU_measurement_start( void )
{
    uint8_t     measure_count;
    uint32_t    sensor_ico_add;

    measure_count  = 0;
    sensor_ico_add = 0;

    while (CORRECTION_AVERAGE != measure_count)                       /* Average number of times loop                 */
    {
        while (CTSU_READY_MODE == g_ctsu_soft_mode)
        {
            DTC_Set_Start_of_CTSU( 0xFF );
            g_ctsu_soft_mode = CTSU_RUN_MODE;                         /* CTSU masurement run mode setting             */
            R_Set_CTSU_Measurement_Start( 0x01,0x00 );
        }

        if ((CTSU_FINISH_MODE == g_ctsu_soft_mode) && (1 == g_correction_status.flag.data_update))
        {
            sensor_ico_add = sensor_ico_add + g_correction_ico_data[0].sen;        /* Sensor ICO value addition       */
            measure_count  = measure_count + 1;                                    /* Measurement count up            */

            g_correction_status.flag.data_update = 0;                              /* Update flag clear               */
            g_ctsu_soft_mode = CTSU_READY_MODE;                       /* CTSU masurement run mode setting             */
        }
    }

    if (_0_1ST == g_correction_time)                                  /* 1st mesurement judgement                     */
    {
        g_correction_1st_val = sensor_ico_add >> 5;                   /* 1/32 = 5 bit right shift                     */
        sensor_ico_add       = 0;                                     /* Sensor ico addtion data clear                */
    }
    else
    {
        g_correction_2nd_val = sensor_ico_add >> 5;                   /* 1/32 = 5 bit right shift                     */
    }

}    /* End of function correction_CTSU_measurement_start() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_1st_coefficient_create
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void correction_CTSU_1st_coefficient_create( void)
{
    /*                                      (g_correction_1st_val * 1024)       g_correction_1st_val +20              */
    /*    g_correction_1st_coefficient  =  -------------------------------  =  --------------------------             */
    /*                                                     40960                            40                        */

    g_correction_1st_coefficient = (g_correction_1st_val + 20 ) / 40;
}    /* End of function correction_CTSU_1st_coefficient_create() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_2nd_standard_val_create
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void correction_CTSU_2nd_standard_val_create( void )
{
    uint32_t _1st_parm;

    /*                                  g_ctsutrimr_def + 273                    (g_ctsutrimr_def + 273) * 2560 *128  */
    /*    g_correction_2nd_std_val  =  ----------------------- * 40960 *128  =  ------------------------------------- */
    /*                                           528                                               33                 */

    _1st_parm = (g_ctsutrimr_def + 273) * 9930 + 64;
    g_correction_2nd_std_val = (uint16_t)(_1st_parm >> 7);
}    /* End of function correction_CTSU_2nd_standard_val_create() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_2nd_coefficient_create
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void correction_CTSU_2nd_coefficient_create( void)
{
    /*                                        g_correction_2nd_val                                                    */
    /*    g_correction_2nd_coefficient  =  -------------------------- * 1024                                          */
    /*                                      g_correction_2nd_std_val                                                  */

    g_correction_2nd_coefficient = ((g_correction_2nd_val << 10) + (g_correction_2nd_std_val/2)) / g_correction_2nd_std_val;
}    /* End of function correction_CTSU_2nd_coefficient_create() */

/***********************************************************************************************************************
* Function Name: correction_CTSU_16point_coefficient_create
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void correction_CTSU_16point_coefficient_create(void)
{
    uint16_t diff_coefficient;
    uint8_t  up_down;
    uint8_t  loop;
    uint8_t  loop_p;
    uint16_t fill_diff;
    uint32_t work_table;
    uint32_t work_32;
    uint16_t work_16;

    if (g_correction_2nd_coefficient > g_correction_1st_coefficient)
    {
        diff_coefficient = g_correction_2nd_coefficient - g_correction_1st_coefficient;
        up_down = 0;
    }
    else
    {
        diff_coefficient = g_correction_1st_coefficient - g_correction_2nd_coefficient;
        up_down = 1;
    }

    /*         diff_coefficient * 40960                                                                               */
    /*     ----------------------------------                                                                         */
    /*      40960 - g_correction_2nd_std_val                                                                          */
    work_32    = diff_coefficient * 40960;
    work_16    = 40960 - g_correction_2nd_std_val;
    fill_diff  = work_32 / work_16;

    /*                                                                 fill_diff * N                                  */
    /*     g_correction_16point  =  g_correction_1st_coefficient +(-) ---------------                                 */
    /*                                                                      16                                        */
    if (0 == up_down)
    {
        for (loop = 1; 16 > loop; loop++)
        {
            g_correction_16point[loop] = g_correction_1st_coefficient + ((fill_diff * loop) >> 4);
        }
    }
    else
    {
        for (loop = 1; 16 > loop; loop++)
        {
            g_correction_16point[loop] = g_correction_1st_coefficient - ((fill_diff * loop) >> 4);
        }
    }
    g_correction_16point[0] = g_correction_1st_coefficient;

    for (loop = 0, loop_p = 15; loop < 16; loop++)
    {
        work_table                       = g_ctsu_correction_std[loop] * g_correction_16point[loop];
        work_table                       = (work_table + 512)>> 10;
        
        if(0x0000FFFF < work_table)
        {
            work_table = 0x0000FFFF;
        }
        g_correction_16table[loop]       = (uint16_t)work_table;
        g_correction_16coefficient[loop] = 1000000 / g_correction_16point[loop_p];
        loop_p = loop_p - 1;
    }

    sensor_linear_interpolation();

}    /* End of function correction_CTSU_16point_coefficient_create() */

/***********************************************************************************************************************
* Function Name: sensor_linear_interpolation
* Description  : 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void sensor_linear_interpolation(void)
{
    uint8_t     loop;
    uint8_t     bnum;
    uint16_t    table_diff;
    uint16_t    coefficient_diff;

    bnum = 0;

    if (g_correction_16coefficient[1] > g_correction_16coefficient[0])
    {
        for (loop = 0; loop < 15; loop++)
        {
            table_diff       = (g_correction_16table[loop] - g_correction_16table[loop+1] + 2) / 4;
            g_linear_interpolation_table[bnum]         = g_correction_16table[loop];
            g_linear_interpolation_table[bnum+1]       = g_correction_16table[loop] - table_diff;
            g_linear_interpolation_table[bnum+2]       = g_correction_16table[loop] - table_diff * 2;
            g_linear_interpolation_table[bnum+3]       = g_correction_16table[loop] - table_diff * 3;

            coefficient_diff = (g_correction_16coefficient[loop+1] - g_correction_16coefficient[loop] +2) / 4;
            g_linear_interpolation_coefficient[bnum]   = g_correction_16coefficient[loop];
            g_linear_interpolation_coefficient[bnum+1] = g_correction_16coefficient[loop] + coefficient_diff;
            g_linear_interpolation_coefficient[bnum+2] = g_correction_16coefficient[loop] + coefficient_diff * 2;
            g_linear_interpolation_coefficient[bnum+3] = g_correction_16coefficient[loop] + coefficient_diff * 3;
            bnum = bnum +4;
        }
    }
    else
    {
        for (loop = 0; loop < 15; loop++)
        {
            table_diff       = (g_correction_16table[loop] - g_correction_16table[loop+1] + 2) / 4;
            g_linear_interpolation_table[bnum]         = g_correction_16table[loop];
            g_linear_interpolation_table[bnum+1]       = g_correction_16table[loop] - table_diff;
            g_linear_interpolation_table[bnum+2]       = g_correction_16table[loop] - table_diff * 2;
            g_linear_interpolation_table[bnum+3]       = g_correction_16table[loop] - table_diff * 3;

            coefficient_diff = (g_correction_16coefficient[loop] - g_correction_16coefficient[loop+1] +2) / 4;
            g_linear_interpolation_coefficient[bnum]   = g_correction_16coefficient[loop];
            g_linear_interpolation_coefficient[bnum+1] = g_correction_16coefficient[loop] - coefficient_diff;
            g_linear_interpolation_coefficient[bnum+2] = g_correction_16coefficient[loop] - coefficient_diff * 2;
            g_linear_interpolation_coefficient[bnum+3] = g_correction_16coefficient[loop] - coefficient_diff * 3;
            bnum = bnum +4;
        }
    }
    g_linear_interpolation_table[bnum]       = g_correction_16table[loop];
    g_linear_interpolation_coefficient[bnum] = g_correction_16coefficient[loop];
}

/***********************************************************************************************************************
* Function Name: correction_sensor_magnification_set
* Description  : 
* Arguments    : uint8_t method    : Measurement method(0-8)
* Return Value : none
***********************************************************************************************************************/
void correction_sensor_magnification_set( uint8_t method )
{
    uint8_t    loop;
    uint8_t    pt;
    uint8_t    snum;
    uint8_t    spda;
    uint8_t    mea_freq;
    uint16_t   ts_measure_time;

    for (loop = 0, pt = 1; loop < g_key_info[method].ena_num; loop++)
    {
        snum = (uint8_t)((*(g_dtc_write_data[method]  +  pt     ) & 0xFC00) >> 10);
        spda = (uint8_t)((*(g_dtc_write_data[method]  + (pt + 1)) & 0x1F00) >> 8);
        mea_freq = CTSU_INPUT_FREQUENCY_DIV * 10 / ((spda + 1) * 2);

        switch (mea_freq)
        {
            case 40:                                                            /* 4.0MHz    32MHz / 8     24MHz / 6  */
                ts_measure_time =  625 * (snum + 1);
                break;
            case 33:                                                            /* 3.3MHz    27MHz / 8  */
                ts_measure_time =  750 * (snum + 1);
                break;
            case 20:                                                            /* 2.0MHz    32MHz / 16    24MHz / 12  */
                ts_measure_time = 1250 * (snum + 1);
                break;
            case 16:                                                            /* 1.6MHz    27MHz / 16 */
                ts_measure_time = 1500 * (snum + 1);
                break;
            case 10:                                                            /* 1.0MHz    32MHz / 32    24MHz / 24  */
                ts_measure_time = 2500 * (snum + 1);
                break;
            case 8:                                                             /* 0.8MHz    27MHz / 32 */
                ts_measure_time = 3000 * (snum + 1);
                break;
            case 5:                                                             /* 0.5MHz    32MHz / 64    24MHz / 48  */
                ts_measure_time = 5000 * (snum + 1);
                break;
            case 4:                                                             /* 0.4MHz    27MHz / 64 */
                ts_measure_time = 6000 * (snum + 1);
                break;
            default:
                break;
        }

        if (5000 <= ts_measure_time)
        {
            *(g_key_info[method].counter_magni + loop) = (int8_t)(ts_measure_time / 500);
        }
        else
        {
            *(g_key_info[method].counter_magni + loop) = (int8_t)((50000 / ts_measure_time) * -1);
        }
        pt = pt + 3;
    }

}    /* End of function correction_sensor_magnification_set() */

/***********************************************************************************************************************
* Function Name: ctsu_sensor_data_address_set
* Description  : ctsu parameter address_setting
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void ctsu_sensor_data_address_set( void )
{
    uint8_t num;

    num = 0;

#if ( SELF_METHOD_NUM == 1 )
    g_dtc_write_data[num]              = &g_self_write[0];
    g_self_ico_data_pt[num]            = &g_self_ico_data[0];
    g_self_ico_sensor_pt[num]          = &g_self_ico_data[0].sen;
    g_self_add_sensor_pt[num]          = &g_self_add_sensor[0];
    g_self_sensor_cnt_pt[num]          = &g_self_sensor_cnt[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_self_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_self_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_self_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_SELF_ENABLE_TS | (CTSUCHAC1_SELF_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_SELF_ENABLE_TS | (CTSUCHAC3_SELF_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_SELF_ENABLE_TS;
    g_mpc_set_sensor0                  = g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_ctsu_parameter[num].ctsu_chac4;

    g_current_sign_pt[num]             = &g_self_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( SELF_METHOD_NUM == 1 )

#if ( MUTUAL_METHOD_NUM >= 1 )
    g_dtc_write_data[num]              = &g_mutual0_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual0_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual0_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual0_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual0_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual0_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual0_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual0_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual0_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual0_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL0_ENABLE_TS | (CTSUCHAC1_MUTUAL0_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL0_ENABLE_TS | (CTSUCHAC3_MUTUAL0_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL0_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL0_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL0_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL0_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL0_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL0_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual0_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 1 )

#if ( MUTUAL_METHOD_NUM >= 2 )
    g_dtc_write_data[num]              = &g_mutual1_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual1_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual1_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual1_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual1_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual1_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual1_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual1_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual1_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual1_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL1_ENABLE_TS | (CTSUCHAC1_MUTUAL1_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL1_ENABLE_TS | (CTSUCHAC3_MUTUAL1_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL1_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL1_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL1_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL1_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL1_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL1_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual1_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 2 )

#if ( MUTUAL_METHOD_NUM >= 3 )
    g_dtc_write_data[num]              = &g_mutual2_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual2_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual2_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual2_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual2_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual2_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual2_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual2_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual2_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual2_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL2_ENABLE_TS | (CTSUCHAC1_MUTUAL2_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL2_ENABLE_TS | (CTSUCHAC3_MUTUAL2_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL2_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL2_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL2_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL2_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL2_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL2_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual2_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 3 )

#if ( MUTUAL_METHOD_NUM >= 4 )
    g_dtc_write_data[num]              = &g_mutual3_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual3_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual3_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual3_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual3_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual3_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual3_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual3_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual3_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual3_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL3_ENABLE_TS | (CTSUCHAC1_MUTUAL3_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL3_ENABLE_TS | (CTSUCHAC3_MUTUAL3_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL3_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL3_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL3_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL3_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL3_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL3_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual3_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 4 )

#if ( MUTUAL_METHOD_NUM >= 5 )
    g_dtc_write_data[num]              = &g_mutual4_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual4_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual4_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual4_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual4_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual4_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual4_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual4_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual4_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual4_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL4_ENABLE_TS | (CTSUCHAC1_MUTUAL4_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL4_ENABLE_TS | (CTSUCHAC3_MUTUAL4_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL4_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL4_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL4_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL4_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL4_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL4_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual4_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 5 )

#if ( MUTUAL_METHOD_NUM >= 6 )
    g_dtc_write_data[num]              = &g_mutual5_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual5_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual5_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual5_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual5_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual5_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual5_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual5_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual5_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual5_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL5_ENABLE_TS | (CTSUCHAC1_MUTUAL5_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL5_ENABLE_TS | (CTSUCHAC3_MUTUAL5_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL5_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL5_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL5_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL5_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL5_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL5_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual5_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 6 )

#if ( MUTUAL_METHOD_NUM >= 7 )
    g_dtc_write_data[num]              = &g_mutual6_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual6_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual6_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual6_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual6_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual6_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual6_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual6_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual6_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual6_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL6_ENABLE_TS | (CTSUCHAC1_MUTUAL6_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL6_ENABLE_TS | (CTSUCHAC3_MUTUAL6_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL6_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL6_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL6_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL6_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL6_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL6_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual6_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 7 )

#if ( MUTUAL_METHOD_NUM >= 8 )
    g_dtc_write_data[num]              = &g_mutual7_write[0];
    g_mutual_ico_data_pt[num]          = &g_mutual7_ico_data[0];
    g_mutual_ico_pri_sensor_pt[num]    = &g_mutual7_ico_data[0].pri_sen;
    g_mutual_ico_snd_sensor_pt[num]    = &g_mutual7_ico_data[0].snd_sen;
    g_mutual_add_pri_sensor_pt[num]    = &g_mutual7_add_pri_sensor[0];
    g_mutual_add_snd_sensor_pt[num]    = &g_mutual7_add_snd_sensor[0];
    g_mutual_sensor_diff_pt[num]       = &g_mutual7_sensor_diff[0];
    g_ctsu_register_txd[num].ctsu_ssc  = &g_mutual7_ctsussc[0];
    g_ctsu_register_txd[num].ctsu_so0  = &g_mutual7_ctsuso0[0];
    g_ctsu_register_txd[num].ctsu_so1  = &g_mutual7_ctsuso1[0];

    g_ctsu_parameter[num].ctsu_chac01  = CTSUCHAC0_MUTUAL7_ENABLE_TS | (CTSUCHAC1_MUTUAL7_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac23  = CTSUCHAC2_MUTUAL7_ENABLE_TS | (CTSUCHAC3_MUTUAL7_ENABLE_TS << 8);
    g_ctsu_parameter[num].ctsu_chac4   = CTSUCHAC4_MUTUAL7_ENABLE_TS;
    g_mpc_set_sensor0                  = g_mpc_set_sensor0 | g_ctsu_parameter[num].ctsu_chac01;
    g_mpc_set_sensor1                  = g_mpc_set_sensor1 | g_ctsu_parameter[num].ctsu_chac23;
    g_mpc_set_sensor2                  = g_mpc_set_sensor2 | g_ctsu_parameter[num].ctsu_chac4;

    g_ctsu_parameter[num].ctsu_chtrc01 = CTSUCHTRC0_MUTUAL7_TRANSMIT_TS | (CTSUCHTRC1_MUTUAL7_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc23 = CTSUCHTRC2_MUTUAL7_TRANSMIT_TS | (CTSUCHTRC3_MUTUAL7_TRANSMIT_TS << 8);
    g_ctsu_parameter[num].ctsu_chtrc4  = CTSUCHTRC4_MUTUAL7_TRANSMIT_TS;

    g_current_sign_pt[num]             = &g_mutual7_current_sign[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 8 )
}    /* End of function ctsu_sensor_data_address_set() */

/***********************************************************************************************************************
* Function Name: CTSU_register_initial_value_ram_set
* Description  : This function storage CTSU register initial value for RAM
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void CTSU_register_initial_value_ram_set( void )
{
    uint8_t method;

    for (method = 0; method < METHOD_NUM; method++)
    {
        /*****    A0900h CTSU channel register0 value storage    ******************************************************/
        g_ctsu_parameter[method].ctsu_snz          = _0_CTSUSNZ_LOW_POWER_DISABLE;
        g_ctsu_parameter[method].ctsu_txvsel       = g_ctsu_txvsel[method];

        /*****    A0901h CTSU channel register1 value storage    ******************************************************/
        g_ctsu_parameter[method].ctsu_pon          = _1_CTSUPON_HW_POWER_ON;
        g_ctsu_parameter[method].ctsu_sw           = _1_CTSUCSW_ON;
        g_ctsu_parameter[method].ctsu_atune0       = g_ctsu_atune0[method];
        g_ctsu_parameter[method].ctsu_clk          = _00_CTSUCLK_PCLK;
        g_ctsu_parameter[method].ctsu_atune1       = g_ctsu_atune1[method];

        if (0 == g_key_info[method].mode)
        {
            g_ctsu_parameter[method].ctsu_md       = _01_CTSUMD_SELF_MULTI;
        }
        else
        {
            g_ctsu_parameter[method].ctsu_md       = _11_CTSUMD_MUTUAL;
        }

        /*****    A0902h CTSU Sensor drive pulse spectrum diffusion set register value storage    *********************/
        g_ctsu_parameter[method].ctsu_prratio      = g_ctsu_prratio[method];
        g_ctsu_parameter[method].ctsu_prmode       = g_ctsu_prmode[method];
        g_ctsu_parameter[method].ctsu_soff         = g_ctsu_soff[method];

        /*****    A0903h CTSU Sensor wait time register value storage    **********************************************/
        g_ctsu_parameter[method].ctsu_sst          = _00010000_CTSUSST_RECOMMEND;

        /*****    A0904h CTSU Measurement channel register0 value storage    ******************************************/
        if (_00_CTSUMD_SELF_SINGLE == g_ctsu_parameter[method].ctsu_md)
        {
            g_ctsu_parameter[method].ctsu_mch0     = _000000_CTSUMCH0_TS00;
        }

        /*****    A0906h CTSU Channel enable control register0 value storage    ***************************************/
        /*****    A0907h CTSU Channel enable control register1 value storage    ***************************************/

        /*====    Prameter set by ctsu_sensor_data_address_set()    ==================================================*/

        /*****    A090Bh CTSU Channel send and receive control register0 value storage    *****************************/
        /*****    A090Ch CTSU Channel send and receive control register0 value storage    *****************************/

        /*====    Prameter set by ctsu_sensor_data_address_set()    ==================================================*/

        /*****    A0912h CTSU Spectrum diffusion control register value storage    ************************************/
        g_ctsu_parameter[method].ctsu_ssmod         = _00_CTSUSSMOD;
        g_ctsu_parameter[method].ctsu_sscnt         = _11_CTSUSSCNT;
    }
}    /* End of function CTSU_register_initial_value_ram_set() */

/***********************************************************************************************************************
* Function Name: R_Set_CTSU_All_Register
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint16_t R_Set_CTSU_All_Register( uint8_t method )
{
    volatile uint16_t ret_val;
    volatile uint16_t status;

    status = 0;

    /* TSCAP Capacitor discharge setting */
    R_Set_CTSU_TSCAP_Discharge();

    /* Multi-Function Pin Controller setting */
    MPC_CTSU_set( g_mpc_set_sensor0, g_mpc_set_sensor1, g_mpc_set_sensor2 );

    /* Operation mode Register change protect off setting */
    R_Set_CTSU_Module_Operation(_0_MSTPD10_CTSU_ENABLE);

#if (MCU_SERIES_T == R5F5130)
    /* CTSU transmit power supply set process call */
    ret_val = R_Set_CTSU_Transmit_Power_Supply(g_ctsu_parameter[method].ctsu_txvsel);
    status = ret_val;
#endif    // (MCU_SERIES_T == R5F5130)

    /* CTSU analog adjustment Signal0 set process call */
    ret_val = R_Set_CTSU_Power_Operation_Mode(g_ctsu_parameter[method].ctsu_atune0);
    status  = status | (ret_val << 1);

    /* CTSU analog adjustment Signal1 set  process call */
    ret_val = R_Set_CTSU_Power_Capacity_Adjustment(g_ctsu_parameter[method].ctsu_atune1);
    status  = status | (ret_val << 2);

    /* CTSU count Source select process call */
    ret_val = R_Set_CTSU_Operation_Clock(g_ctsu_parameter[method].ctsu_clk);
    status  = status | (ret_val << 3);

    /* CTSU sensor wait time set process call */
    ret_val = R_Set_CTSU_Sensor_Stabilization_Wait_Time(g_ctsu_parameter[method].ctsu_sst);
    status  = status | (ret_val << 4);

    /* CTSU hard macro power supply switch change process call */
    ret_val = R_Set_CTSU_Power_Supply(g_ctsu_parameter[method].ctsu_pon);
    status  = status | (ret_val << 5);

    /* CTSU measurement mode select process call */
    ret_val = R_Set_CTSU_Measurement_Mode(g_ctsu_parameter[method].ctsu_md);
    status  = status | (ret_val << 6);

    /* CTSU Sensor Drive Pulse Spectrum Diffusion Setting Register (CTSUSDPRS) */
    ret_val = R_Set_CTSU_Synchronous_Noise_Reduction(g_ctsu_parameter[method].ctsu_prratio, g_ctsu_parameter[method].ctsu_prmode, g_ctsu_parameter[method].ctsu_soff);
    status  = status | (ret_val << 7);

    /* CTSU measurement channel set process call */
    ret_val = R_Set_CTSU_Measurement_Channel(g_ctsu_parameter[method].ctsu_mch0);

    /* CTSU channel enable set process call */
    ret_val = R_Set_CTSU_Channel_Enable0(g_ctsu_parameter[method].ctsu_chac01);
    status  = status | (ret_val << 9);

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
    ret_val = R_Set_CTSU_Channel_Enable1(g_ctsu_parameter[method].ctsu_chac23);
    status  = status | (ret_val << 10);
    ret_val = R_Set_CTSU_Channel_Enable2(g_ctsu_parameter[method].ctsu_chac4);
    status  = status | (ret_val << 11);
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)

    /* CTSU Channel transmit/receive control process call */
    ret_val = R_Set_CTSU_Channel_Transmit_Receive0(g_ctsu_parameter[method].ctsu_chtrc01);
    status  = status | (ret_val << 12);

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)
    ret_val = R_Set_CTSU_Channel_Transmit_Receive1(g_ctsu_parameter[method].ctsu_chtrc23);
    status  = status | (ret_val << 13);
    ret_val = R_Set_CTSU_Channel_Transmit_Receive2(g_ctsu_parameter[method].ctsu_chtrc4);
    status  = status | (ret_val << 14);
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5130 || MCU_SERIES_T == R5F5230)

    /* CTSU diffusion clock mode and oscillation frequency select process call */
    ret_val = R_Set_CTSU_High_Pass_Noise_Reduction(g_ctsu_parameter[method].ctsu_ssmod, g_ctsu_parameter[method].ctsu_sscnt);
    status  = status | (ret_val << 15);

    return status;
}    /* End of function R_Set_CTSU_All_Register() */

/***********************************************************************************************************************
* Function Name: DTC_transmit_data_set
* Description  : DTC transmi write data storage
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void DTC_transmit_data_set(void)
{
    uint8_t method;
    uint8_t loop;
    uint8_t pt;

    for (method = 0; method < METHOD_NUM; method++)
    {
        for (loop = 0, pt = 0; loop < g_key_info[method].ena_num; loop++)
        {
            /* CTSU Spectrum Diffusion Control Register initial value    */
             *(g_dtc_write_data[method]  +  pt     )  = *(g_ctsu_register_txd[method].ctsu_ssc + loop);

            /* CTSU Sensor Offset Register 0 initial value    */
             *(g_dtc_write_data[method]  + (pt + 1))  = *(g_ctsu_register_txd[method].ctsu_so0 + loop);

            /* CTSU Sensor Offset Register 1 initial value    */
             *(g_dtc_write_data[method]  + (pt + 2))  = *(g_ctsu_register_txd[method].ctsu_so1 + loop);

            /* next buffer pointer set    */
            pt = (uint8_t)(pt + 3);
        }
    }
}    /* End of function DTC_transmit_data_set() */

/***********************************************************************************************************************
* Function Name: touch_data_moving_average
* Description  : touch data moving average
* Arguments    : uint8_t method    : Measurement method : 0-8
* Return Value : none
***********************************************************************************************************************/
void touch_data_moving_average( uint8_t method )
{
    uint8_t     pt;
    uint8_t     offset;
    uint32_t    correction_work;
    uint32_t    correction_work2;
    uint32_t    scount_work;
    uint32_t    scount_work2;

    offset  = 0;

    for (pt = 0; pt < g_key_info[method].ena_num; pt++)
    {
        if (0 == g_touch_function[method].flag.average)
        {
            if (0 == g_key_info[method].mode)
            {
                if (SET_SUCCESS == g_correction_create)
                {
                     *(g_self_add_sensor_pt[method]  + pt) = correction_sensor_cnt_create( method, pt, (pt + offset));
                }
                else
                {
                     *(g_self_add_sensor_pt[method]  + pt) = *(g_self_ico_sensor_pt[method] + (pt + offset));
                }
            }
            else
            {
                if (SET_SUCCESS == g_correction_create)
                {
                     *(g_mutual_add_pri_sensor_pt[method]  + pt) = correction_pri_sensor_cnt_create( method, pt, (pt + offset));
                     *(g_mutual_add_snd_sensor_pt[method]  + pt) = correction_snd_sensor_cnt_create( method, pt, (pt + offset));
                }
                else
                {
                     *(g_mutual_add_pri_sensor_pt[method]  + pt) = *(g_mutual_ico_pri_sensor_pt[method]  + (pt + offset));
                     *(g_mutual_add_snd_sensor_pt[method]  + pt) = *(g_mutual_ico_snd_sensor_pt[method]  + (pt + offset));
                }
            }
        }
        else
        {
            if (0 == g_key_info[method].mode)
            {
                scount_work      = *(g_self_add_sensor_pt[method]  + pt);                   /* Get Add data            */
                scount_work     -= scount_work / ADD_TIME;                                  /* Average / ADD_TIME      */
                if (SET_SUCCESS == g_correction_create)
                {
                    correction_work  = correction_sensor_cnt_create( method, pt,(pt + offset));
                    scount_work     += correction_work / ADD_TIME;                          /* Add Now data / ADD_TIME */
                }
                else
                {
                    scount_work += *(g_self_ico_sensor_pt[method] + (pt + offset)) / ADD_TIME;     /* Add Now data / ADD_TIME     */
                }
               *(g_self_add_sensor_pt[method]  + pt) = scount_work;                         /* Data store for next     */
            }
            else
            {
                scount_work      = *(g_mutual_add_pri_sensor_pt[method]  + pt);             /* Get Add data            */
                scount_work2     = *(g_mutual_add_snd_sensor_pt[method]  + pt);             /* Get Add data            */
                scount_work     -= scount_work   / ADD_TIME;                                /* Average / ADD_TIME      */
                scount_work2    -= scount_work2  / ADD_TIME;                                /* Average / ADD_TIME      */
                if (SET_SUCCESS == g_correction_create)
                {
                    correction_work  = correction_pri_sensor_cnt_create( method, pt, (pt + offset));
                    correction_work2 = correction_snd_sensor_cnt_create( method, pt, (pt + offset));
                    scount_work     += correction_work   / ADD_TIME;                        /* Add Now data / ADD_TIME */
                    scount_work2    += correction_work2  / ADD_TIME;                        /* Add Now data / ADD_TIME */
                }
                else
                {
                    scount_work   += *(g_mutual_ico_pri_sensor_pt[method] + (pt + offset)) / ADD_TIME;  /* Add Now data / ADD_TIME     */
                    scount_work2  += *(g_mutual_ico_snd_sensor_pt[method] + (pt + offset)) / ADD_TIME;  /* Add Now data / ADD_TIME     */
                }
               *(g_mutual_add_pri_sensor_pt[method]    + pt) = scount_work;                 /* Data store for next     */
               *(g_mutual_add_snd_sensor_pt[method]    + pt) = scount_work2;                /* Data store for next     */
            }
        }

        if (0 == g_key_info[method].mode)
        {
             *(g_self_sensor_cnt_pt[method]    + pt) = *(g_self_add_sensor_pt[method]    + pt);
             offset = offset + 1;
        }
        else
        {
            if (*(g_mutual_add_snd_sensor_pt[method] + (pt)) > *(g_mutual_add_pri_sensor_pt[method] + (pt)))
            {
                *(g_mutual_sensor_diff_pt[method] + pt) = (uint16_t)(*(g_mutual_add_snd_sensor_pt[method] + (pt)) - *(g_mutual_add_pri_sensor_pt[method] + (pt)));
            }
            else
            {
                 *(g_mutual_sensor_diff_pt[method] + pt) = 0;
            }
            offset = offset + 3;
        }
    }

    if ( 0 == g_touch_function[method].flag.average)
    {
        g_touch_function[method].flag.average = 1;
    }
}    /* End of function touch_data_moving_average() */

/***********************************************************************************************************************
* Function Name: initial_offset_tuning
* Description  : 
* Arguments    : uint8_t method    : Maeasurement method : 0-8
*              : uint8_t number    : Key number
* Return Value : none
***********************************************************************************************************************/
uint8_t initial_offset_tuning( uint8_t method, uint8_t number )
{
             uint8_t  loop;
             uint8_t  pt;
    volatile uint8_t  st;
    volatile uint8_t  status;
             uint16_t  beas_val;

    volatile uint16_t sensor_raw[64];             /* ICO sensor counter storage buffer[Maximum number of keys = 64] */

    status = _1_FINISH;
    pt     = 0;
    st     = 1;

    for (loop = 0; loop < number; loop++ )
    {
        if (0 == *(g_touch_tuning_info[method].result + loop))
        {
            if (0 == g_key_info[method].mode)
            {
                if (SET_SUCCESS == g_correction_create)
                {
                    sensor_raw[loop] = correction_sensor_cnt_create( method, loop, (loop + pt));      /* Sensor count get      */
                }
                else
                {
                    sensor_raw[loop] = *(g_self_ico_sensor_pt[method]  + (loop + pt));
                }
                beas_val = _07_2UA;                                                         /* 7.2uA = 15630 set     */
            }
            else
            {
                if (SET_SUCCESS == g_correction_create)
                {
                    sensor_raw[loop] = correction_pri_sensor_cnt_create( method, loop, (loop + pt));  /* Sensor count get      */
                }
                else
                {
                    sensor_raw[loop] = *(g_mutual_ico_pri_sensor_pt[method]  + (loop + pt));
                }
                beas_val = _04_8UA;                                                         /* 4.8uA = 10240 set     */
            }

           *(g_touch_tuning_info[method].ctsuso  + loop) = *(g_dtc_write_data[method] + st) & 0x03FF;

            if (beas_val < (sensor_raw[loop] - TUNING_UPPER_LIMIT))                         /* Current over check    */
            {
                if (0x03FF != *(g_touch_tuning_info[method].ctsuso  + loop))                /* CTSUSO limit check    */
                {
                   *(g_dtc_write_data[method] + st) =  (*(g_dtc_write_data[method] + st) & 0xFC00) + (*(g_touch_tuning_info[method].ctsuso + loop) + 1);
                   *(g_touch_tuning_info[method].result + loop)  = 0;
                   *(g_current_sign_pt[method] + loop) = *(g_current_sign_pt[method] + loop) + 1;    /* Plus         */
                }
                else
                {
                   *(g_touch_tuning_info[method].result + loop) = 1;                       /* Tuning finish flag set */
                }
            }
            else if (beas_val > (sensor_raw[loop] + TUNING_LOWER_LIMIT))                    /* Current down check    */
            {
                if (0x0000 != *(g_touch_tuning_info[method].ctsuso  + loop))                /* CTSUSO limit check    */
                {
                   *(g_dtc_write_data[method] + st)  = (*(g_dtc_write_data[method] + st) & 0xFC00) + (*(g_touch_tuning_info[method].ctsuso + loop) - 1);
                   *(g_touch_tuning_info[method].result + loop) = 0;
                   *(g_current_sign_pt[method] + loop) = *(g_current_sign_pt[method] + loop) - 1;
                }
                else
                {
                   *(g_touch_tuning_info[method].result + loop) = 1;
                }
            }
            else
            {
               *(g_touch_tuning_info[method].result + loop) = 1;
            }
        }

        if (10 == g_current_offset_count[method])
        {
            if ((OFFSET_CNT_PLUS >= (*(g_current_sign_pt[method] + loop))) && (OFFSET_CNT_MINUS <= (*(g_current_sign_pt[method] + loop))))
            {
                *(g_touch_tuning_info[method].result + loop) = 1;
            }
            else
            {
                g_current_offset_count[method] = 0;
               *(g_current_sign_pt[method] + loop) = 0;
            }
        }

        if (0 == g_key_info[method].mode)
        {
            pt     = pt + 1;
        }
        else
        {
            pt     = pt + 3;
        }
        st = st + 3;
    }
    g_ctsu_status[method].flag.data_update = 0;

    if (1 != g_touch_function[method].flag.tuning)
    {
        g_current_offset_count[method] = g_current_offset_count[method] + 1;
    }

    for (loop = 0; loop < number; loop++)
    {
        if (1 != *(g_touch_tuning_info[method].result + loop))
        {
            status = _0_RUN;
            return status;
        }
    }

    g_touch_function[method].flag.tuning = 1;

    for (loop = 0; loop < METHOD_NUM; loop++)
    {
        if (1 != g_touch_function[loop].flag.tuning)
        {
            status = _0_RUN;
            return status;
        }
    }

    return status;
}    /* End of function initial_offset_tuning() */

/***********************************************************************************************************************
* Function Name: correction_sensor_cnt_create
* Description  : 
* Arguments    : uint8_t method    : Maeasurement method : 0-8
*              : uint8_t number    : Key number
* Return Value : none
***********************************************************************************************************************/

uint16_t correction_sensor_cnt_create( uint8_t method, uint8_t ts_num, uint8_t number)
{
    uint8_t  loop;

    uint32_t cmp_val;
    uint32_t correct_box;
    uint32_t correct_box2;
	uint8_t  loop_coef;
    uint16_t correction_sensor_cnt;
	
	 if ( 0 > (*(g_key_info[method].counter_magni + ts_num)))
    {
        cmp_val     = (*(g_self_ico_sensor_pt[method] + number)) * (*(g_key_info[method].counter_magni + ts_num) * -1);
        cmp_val     =  cmp_val / 10;
        correct_box = *(g_self_ico_sensor_pt[method] + number);
    }
    else
    {
        cmp_val     = ((*(g_self_ico_sensor_pt[method] + number)) * 10) / (*(g_key_info[method].counter_magni + ts_num));
        correct_box = *(g_self_ico_sensor_pt[method] + number);
    }

    if (g_linear_interpolation_table[60] >= cmp_val)
    {
        correct_box2          = correct_box * g_linear_interpolation_coefficient[0];
        correct_box2          = correct_box2 >> 10;         /* Unscaling corrected value */
        
        if(0x0000FFFF < correct_box2)
        {
            correct_box2 = 0x0000FFFF;                      /* 16bit length overflow limitter */
        }
        correction_sensor_cnt = (uint16_t)correct_box2;
    }
    else
    {
        if (g_linear_interpolation_table[29] <= cmp_val)
        {
            if (g_linear_interpolation_table[14] <= cmp_val)
            {
                for (loop = 0, loop_coef = 60; loop < 15; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2         = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2         = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
            else
            {
                for (loop = 15, loop_coef = 45; loop < 30; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2         = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2         = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
        }
        else
        {
            if (g_linear_interpolation_table[44] <= cmp_val)
            {
                for (loop = 30, loop_coef = 30; loop < 45; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2         = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2         = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
            else
            {
                for (loop = 45, loop_coef = 15; loop <= 60; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2         = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2         = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
        }
    }

    return correction_sensor_cnt;

}    /* End of function correction_sensor_cnt_create() */

/***********************************************************************************************************************
* Function Name: correction_pri_sensor_cnt_create
* Description  : 
* Arguments    : uint8_t method    : Maeasurement method : 0-8
*              : uint8_t number    : Key number
* Return Value : none
***********************************************************************************************************************/
uint16_t correction_pri_sensor_cnt_create( uint8_t method, uint8_t ts_num, uint8_t number)
{
    uint8_t  loop;
    uint8_t  loop_coef;
    uint32_t cmp_val;
    uint32_t correct_box;
    uint32_t correct_box2;
    uint16_t correction_pri_sensor_cnt;

    if ( 0 > (*(g_key_info[method].counter_magni + ts_num)))
    {
        cmp_val     = (*(g_mutual_ico_pri_sensor_pt[method] + number)) * (*(g_key_info[method].counter_magni + ts_num) * -1);
        cmp_val     =  cmp_val / 10;
        correct_box = *(g_mutual_ico_pri_sensor_pt[method] + number);
    }
    else
    {
        cmp_val     = (*(g_mutual_ico_pri_sensor_pt[method] + number) * 10) / (*(g_key_info[method].counter_magni + ts_num));
        correct_box = *(g_mutual_ico_pri_sensor_pt[method] + number);
    }

    if (g_linear_interpolation_table[60] >= cmp_val)
    {
        correct_box2              = correct_box * g_linear_interpolation_coefficient[0];
        correct_box2              = correct_box2 >> 10;     /* Unscaling corrected value */
        
        if(0x0000FFFF < correct_box2)
        {
            correct_box2 = 0x0000FFFF;                      /* 16bit length overflow limitter */
        }
        correction_pri_sensor_cnt = (uint16_t)correct_box2;
    }
    else
    {
        if (g_linear_interpolation_table[29] <= cmp_val)
        {
            if (g_linear_interpolation_table[14] <= cmp_val)
            {
                for (loop = 0, loop_coef = 60; loop < 15; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_pri_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
            else
            {
                for (loop = 15, loop_coef = 45; loop < 30; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_pri_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
        }
        else
        {
            if (g_linear_interpolation_table[44] <= cmp_val)
            {
                for (loop = 30, loop_coef = 30; loop < 45; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_pri_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
            else
            {
                for (loop = 45, loop_coef = 15; loop < 60; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_pri_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
        }
    }

    return correction_pri_sensor_cnt;

}    /* End of function correction_pri_sensor_cnt_create() */

/***********************************************************************************************************************
* Function Name: correction_snd_sensor_cnt_create
* Description  : 
* Arguments    : uint8_t method    : Maeasurement method : 0-8
*              : uint8_t number    : Key number
* Return Value : none
***********************************************************************************************************************/
uint16_t correction_snd_sensor_cnt_create( uint8_t method, uint8_t ts_num, uint8_t number)
{
    uint8_t  loop;
    uint8_t  loop_coef;
    uint32_t cmp_val;
    uint32_t correct_box;
    uint32_t correct_box2;
    uint16_t correction_snd_sensor_cnt;

    if ( 0 > (*(g_key_info[method].counter_magni + ts_num)))
    {
        cmp_val     = (*(g_mutual_ico_snd_sensor_pt[method] + number)) * (*(g_key_info[method].counter_magni + ts_num) * -1);
        cmp_val     =  cmp_val / 10;
        correct_box = *(g_mutual_ico_snd_sensor_pt[method] + number);
    }
    else
    {
        cmp_val     = (*(g_mutual_ico_snd_sensor_pt[method] + number) * 10) / (*(g_key_info[method].counter_magni + ts_num));
        correct_box = *(g_mutual_ico_snd_sensor_pt[method] + number);
    }

    if (g_linear_interpolation_table[60] >= cmp_val)
    {
        correct_box2              = correct_box * g_linear_interpolation_coefficient[0];
        correct_box2              = correct_box2 >> 10;     /* Unscaling corrected value */
        
        if(0x0000FFFF < correct_box2)
        {
            correct_box2 = 0x0000FFFF;                      /* 16bit length overflow limitter */
        }
        correction_snd_sensor_cnt = (uint16_t)correct_box2;
    }
    else
    {
        if (g_linear_interpolation_table[29] <= cmp_val)
        {
            if (g_linear_interpolation_table[14] <= cmp_val)
            {
                for (loop = 0, loop_coef = 60; loop < 15; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_snd_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
            else
            {
                for (loop = 15, loop_coef = 45; loop < 30; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_snd_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
        }
        else
        {
            if (g_linear_interpolation_table[44] <= cmp_val)
            {
                for (loop = 30, loop_coef = 30; loop < 45; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_snd_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
            else
            {
                for (loop = 45, loop_coef = 15; loop < 60; loop++)
                {
                    if (g_linear_interpolation_table[loop] <= cmp_val)
                    {
                        correct_box2              = correct_box * g_linear_interpolation_coefficient[loop_coef];
                        correct_box2              = correct_box2 >> 10;
                        
                        if(0x0000FFFF < correct_box2)
                        {
                            correct_box2 = 0x0000FFFF;
                        }
                        correction_snd_sensor_cnt = (uint16_t)correct_box2;
                        break;
                    }
                    loop_coef = loop_coef - 1;
                }
            }
        }
    }

    return correction_snd_sensor_cnt;

}    /* End of function correction_snd_sensor_cnt_create() */

/***********************************************************************************************************************
* Function Name: touch_internal_tuning
* Description  : 
* Arguments    : uint8_t mode            0 : Internal tuning stop
*              :                         1 : Internal tuning start
*              : uint16_t count          0 : Set Error
*              :                   1-65535 : Internal tuning timing
* Return Value : none
***********************************************************************************************************************/
void touch_internal_tuning( uint8_t method, uint16_t count )
{

    switch (g_ctsu_offset_mode)
    {
        case _1_START:
            if (0 != count)
            {
                if (0 == g_tuning_counter[method])
                {
                    g_tuning_counter[method] = (uint16_t)(count * 50);
                    touch_offset_tuning( method );
                }
                else
                {
                    g_tuning_counter[method] = (uint16_t)(g_tuning_counter[method] - 1);
                }
            }
            break;
        case _0_STOP:
            break;
        default:
            break;
    }
}    /* End of function touch_Internal_tuning() */

/***********************************************************************************************************************
* Function Name: touch_offset_tuning
* Description  : 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void touch_offset_tuning( uint8_t method )
{
             uint8_t  key_num;
             uint8_t  pt;
    volatile uint8_t  offset;
    volatile uint16_t so_storage;

    offset = 1;
    pt = 0;

    for (key_num = 0; key_num < g_key_info[method].ena_num; key_num++)
    {
        so_storage = (*(g_dtc_write_data[method] + offset) & 0x03FF);

        if (0 == g_key_info[method].mode)
        {
            if (_07_2UA < ((*(g_self_ico_sensor_pt[method] + key_num + pt)) - OFFSET_UPPER_LIMIT))
            {
                if (0x03FF != so_storage)
                {
                    *(g_dtc_write_data[method] + offset) = (*(g_dtc_write_data[method] + offset) & 0xFC00) + (so_storage + 1);
                }
            }
            else if (_07_2UA > ((*(g_self_ico_sensor_pt[method] + key_num + pt)) + OFFSET_LOWER_LIMIT))
            {
                if (0x0000 != so_storage)
                {
                    *(g_dtc_write_data[method] + offset) = (*(g_dtc_write_data[method] + offset) & 0xFC00) + (so_storage - 1);
                }
            }
            offset = offset + 3;
            pt = pt + 1;
        }
        else
        {
            if (_04_8UA < ((*(g_mutual_ico_pri_sensor_pt[method] + key_num + pt)) - OFFSET_UPPER_LIMIT))
            {
                *(g_dtc_write_data[method] + offset) = (*(g_dtc_write_data[method] + offset) & 0xFC00) + (so_storage + 1);
            }
            else if (_04_8UA > ((*(g_mutual_ico_pri_sensor_pt[method] + key_num + pt)) + OFFSET_LOWER_LIMIT))
            {
                if (0x0000 != so_storage)
                {
                    *(g_dtc_write_data[method] + offset) = (*(g_dtc_write_data[method] + offset) & 0xFC00) + (so_storage - 1);
                }
            }
            offset = offset + 3;
            pt = pt + 3;
        }
    }
}    /* End of function touch_offset_tuning() */

/***********************************************************************************************************************
* Function Name: Excep_CTSU_CTSUFN
* Description  : Measurement finish interruption process.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void Excep_CTSU_CTSUFN( void )
{
    CTSUInterrupt();
}    /* End of function Excep_CTSU_CTSUFN() */

/***********************************************************************************************************************
* Function Name: CTSUInterrupt
* Description  : CTSU measurement end interrupt function
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void CTSUInterrupt( void )
{

#ifdef TOUCH_IEC61000
    uint8_t loop;
    uint8_t offset;
#endif  //TOUCH_IEC61000

    uint8_t err_status;

    if (0 != CTSUGetTscapVoltageError())
    {
        if (_1_CORRECTION == g_correction_mode)
        {
            g_correction_status.flag.icomp_error = 1;                         /* TSCAP voltage error                  */
        }
        else
        {
            g_ctsu_status[g_method_stor].flag.icomp_error = 1;                /* TSCAP voltage error                  */
        }
        R_Set_CTSU_Power_Supply_Only(0x00);                                       /* TSCUPON off -> TSCUICOMP clear   */
        nop();
        nop();
        R_Set_CTSU_Power_Supply_Only(0x01);                                       /* TSCUPON on                       */

#ifdef TOUCH_IEC61000
        offset = 1;
        for (loop = 0; loop < SELF_KEY_NUM; loop++ )
        {
             *(g_dtc_write_data[0] + offset) =  (*(g_dtc_write_data[0] + offset) & 0xFC00) + (((*(g_dtc_write_data[0] + offset) & 0x3FF) *4)/5);
              offset +=3;
        }
		
		/*Clear calibration flag to do calibration again after error is gone*/
		for(loop = 0; loop < SELF_KEY_NUM; loop++)
		{
			g_self_tune_result[loop] = 0 ;  
		}
		g_touch_system.flag.initial = _0_RUN ;
		g_touch_function[0].flag.calib = 1;
#endif  //TOUCH_IEC61000
    }
    else
    {
        if (_1_CORRECTION == g_correction_mode)
        {
            g_correction_status.flag.icomp_error = 0;                         /* TSCAP voltage error clear            */
        }
        else
        {
            g_ctsu_status[g_method_stor].flag.icomp_error = 0;                /* TSCAP voltage error clear            */
        }
    }

    err_status = R_Get_CTSU_Counter_Overflow_flag();

    if (_1_CORRECTION == g_correction_mode)
    {
        switch (err_status)
        {
            case SENS_OK:
                g_correction_status.flag.sens_over = 0;
                g_correction_status.flag.ref_over = 0;
                if (g_correction_status.flag.icomp_error != 1)         /* TSCAP voltage error                    */
                {
                    g_correction_status.flag.data_update = 1;          /* Measurement data updata status set     */
                }
                g_ctsu_soft_mode = CTSU_FINISH_MODE;
                g_correction_status.flag.ctsu_measure = 1;
                break;
            case SENS_OVER:
                g_correction_status.flag.ref_over = 0;
                g_correction_status.flag.sens_over = 1;                /* Sensor Counter overflow status set     */
                g_ctsu_soft_mode = CTSU_FINISH_MODE;
				
#ifdef TOUCH_IEC61000
				offset = 1 ;
				for(loop = 0; loop < SELF_KEY_NUM; loop++)
				{
					if(g_self_ico_data[loop].sen>=65535)
					{
						*(g_dtc_write_data[0]+offset) = (*(g_dtc_write_data[0]+offset)&0xFC00)+(*(g_dtc_write_data[0]+offset)&0x3FF)+50;
					}
					offset += 3;
				}
				
				/*Clear calibration flag to do calibration again after error is gone*/
				for(loop = 0; loop < SELF_KEY_NUM; loop++)
				{
					g_self_tune_result[loop] = 0 ;  
				}
				g_touch_system.flag.initial = _0_RUN ;
				g_touch_function[0].flag.calib = 1;
#endif  //TOUCH_IEC61000
                break;
            default:
                g_ctsu_soft_mode = CTSU_STOP_MODE;
                break;
        }
    }
    else
    {
        switch (err_status)
        {
            case SENS_OK:
                g_ctsu_status[g_method_stor].flag.sens_over = 0;
                g_ctsu_status[g_method_stor].flag.ref_over = 0;
                if (g_ctsu_status[g_method_stor].flag.icomp_error != 1)         /* TSCAP voltage error                    */
                {
                    g_ctsu_status[g_method_stor].flag.data_update = 1;          /* Measurement data updata status set     */
                }
                g_ctsu_soft_mode = CTSU_FINISH_MODE;
                g_ctsu_status[g_method_stor].flag.ctsu_measure = 1;
                break;
            case SENS_OVER:
                g_ctsu_status[g_method_stor].flag.ref_over = 0;
                g_ctsu_status[g_method_stor].flag.sens_over = 1;                /* Sensor Counter overflow status set     */
                g_ctsu_soft_mode = CTSU_FINISH_MODE;
                break;
            case REF_OVER:
                g_ctsu_status[g_method_stor].flag.sens_over = 0;
                g_ctsu_status[g_method_stor].flag.ref_over = 1;                 /* Reference Counter overflow status set  */
                g_ctsu_soft_mode = CTSU_FINISH_MODE;
                break;
            case SENS_REF_OVER:
                g_ctsu_status[g_method_stor].flag.sens_over = 1;                /* Sensor Counter overflow status set     */
                g_ctsu_status[g_method_stor].flag.ref_over = 1;                 /* Reference Counter overflow status set  */
                g_ctsu_soft_mode = CTSU_FINISH_MODE;
                break;
            default:
                g_ctsu_soft_mode = CTSU_STOP_MODE;
                break;
        }
    }

#ifdef WORKBENCH_COMMAND_USE
    #if WORKBENCH_SERIAL_CONNECT != 0
    if( g_ctsu_soft_mode == CTSU_FINISH_MODE )
    {
        StoreBurstMonitorMeasureValue(g_method_stor);
    }
    #endif  // WORKBENCH_SERIAL_CONNECT
#endif  // WORKBENCH_COMMAND_USE

}    /* End of function CTSUInterrupt() */

/*===== DTC transmit data ========================================================*/
#if ( SELF_METHOD_NUM == 1 )
const uint16_t g_self_ctsussc[] =
{ 
    #if SELF_ENABLE_TS00 == 1
        CTSUSSC_TS00,
    #endif
    #if SELF_ENABLE_TS01 == 1
        CTSUSSC_TS01,
    #endif
    #if SELF_ENABLE_TS02 == 1
        CTSUSSC_TS02,
    #endif
    #if SELF_ENABLE_TS03 == 1
        CTSUSSC_TS03,
    #endif
    #if SELF_ENABLE_TS04 == 1
        CTSUSSC_TS04,
    #endif
    #if SELF_ENABLE_TS05 == 1
        CTSUSSC_TS05,
    #endif
    #if SELF_ENABLE_TS06 == 1
        CTSUSSC_TS06,
    #endif
    #if SELF_ENABLE_TS07 == 1
        CTSUSSC_TS07,
    #endif
    #if SELF_ENABLE_TS08 == 1
        CTSUSSC_TS08,
    #endif
    #if SELF_ENABLE_TS09 == 1
        CTSUSSC_TS09,
    #endif
    #if SELF_ENABLE_TS10 == 1
        CTSUSSC_TS10,
    #endif
    #if SELF_ENABLE_TS11 == 1
        CTSUSSC_TS11,
    #endif
    #if SELF_ENABLE_TS12 == 1
        CTSUSSC_TS12,
    #endif
    #if SELF_ENABLE_TS13 == 1
        CTSUSSC_TS13,
    #endif
    #if SELF_ENABLE_TS14 == 1
        CTSUSSC_TS14,
    #endif
    #if SELF_ENABLE_TS15 == 1
        CTSUSSC_TS15,
    #endif
    #if SELF_ENABLE_TS16 == 1
        CTSUSSC_TS16,
    #endif
    #if SELF_ENABLE_TS17 == 1
        CTSUSSC_TS17,
    #endif
    #if SELF_ENABLE_TS18 == 1
        CTSUSSC_TS18,
    #endif
    #if SELF_ENABLE_TS19 == 1
        CTSUSSC_TS19,
    #endif
    #if SELF_ENABLE_TS20 == 1
        CTSUSSC_TS20,
    #endif
    #if SELF_ENABLE_TS21 == 1
        CTSUSSC_TS21,
    #endif
    #if SELF_ENABLE_TS22 == 1
        CTSUSSC_TS22,
    #endif
    #if SELF_ENABLE_TS23 == 1
        CTSUSSC_TS23,
    #endif
    #if SELF_ENABLE_TS24 == 1
        CTSUSSC_TS24,
    #endif
    #if SELF_ENABLE_TS25 == 1
        CTSUSSC_TS25,
    #endif
    #if SELF_ENABLE_TS26 == 1
        CTSUSSC_TS26,
    #endif
    #if SELF_ENABLE_TS27 == 1
        CTSUSSC_TS27,
    #endif
    #if SELF_ENABLE_TS28 == 1
        CTSUSSC_TS28,
    #endif
    #if SELF_ENABLE_TS29 == 1
        CTSUSSC_TS29,
    #endif
    #if SELF_ENABLE_TS30 == 1
        CTSUSSC_TS30,
    #endif
    #if SELF_ENABLE_TS31 == 1
        CTSUSSC_TS31,
    #endif
    #if SELF_ENABLE_TS32 == 1
        CTSUSSC_TS32,
    #endif
    #if SELF_ENABLE_TS33 == 1
        CTSUSSC_TS33,
    #endif
    #if SELF_ENABLE_TS34 == 1
        CTSUSSC_TS34,
    #endif
    #if SELF_ENABLE_TS35 == 1
        CTSUSSC_TS35,
    #endif
};

const uint16_t g_self_ctsuso0[] =
{ 
    #if SELF_ENABLE_TS00 == 1
        CTSUSO0_TS00,
    #endif
    #if SELF_ENABLE_TS01 == 1
        CTSUSO0_TS01,
    #endif
    #if SELF_ENABLE_TS02 == 1
        CTSUSO0_TS02,
    #endif
    #if SELF_ENABLE_TS03 == 1
        CTSUSO0_TS03,
    #endif
    #if SELF_ENABLE_TS04 == 1
        CTSUSO0_TS04,
    #endif
    #if SELF_ENABLE_TS05 == 1
        CTSUSO0_TS05,
    #endif
    #if SELF_ENABLE_TS06 == 1
        CTSUSO0_TS06,
    #endif
    #if SELF_ENABLE_TS07 == 1
        CTSUSO0_TS07,
    #endif
    #if SELF_ENABLE_TS08 == 1
        CTSUSO0_TS08,
    #endif
    #if SELF_ENABLE_TS09 == 1
        CTSUSO0_TS09,
    #endif
    #if SELF_ENABLE_TS10 == 1
        CTSUSO0_TS10,
    #endif
    #if SELF_ENABLE_TS11 == 1
        CTSUSO0_TS11,
    #endif
    #if SELF_ENABLE_TS12 == 1
        CTSUSO0_TS12,
    #endif
    #if SELF_ENABLE_TS13 == 1
        CTSUSO0_TS13,
    #endif
    #if SELF_ENABLE_TS14 == 1
        CTSUSO0_TS14,
    #endif
    #if SELF_ENABLE_TS15 == 1
        CTSUSO0_TS15,
    #endif
    #if SELF_ENABLE_TS16 == 1
        CTSUSO0_TS16,
    #endif
    #if SELF_ENABLE_TS17 == 1
        CTSUSO0_TS17,
    #endif
    #if SELF_ENABLE_TS18 == 1
        CTSUSO0_TS18,
    #endif
    #if SELF_ENABLE_TS19 == 1
        CTSUSO0_TS19,
    #endif
    #if SELF_ENABLE_TS20 == 1
        CTSUSO0_TS20,
    #endif
    #if SELF_ENABLE_TS21 == 1
        CTSUSO0_TS21,
    #endif
    #if SELF_ENABLE_TS22 == 1
        CTSUSO0_TS22,
    #endif
    #if SELF_ENABLE_TS23 == 1
        CTSUSO0_TS23,
    #endif
    #if SELF_ENABLE_TS24 == 1
        CTSUSO0_TS24,
    #endif
    #if SELF_ENABLE_TS25 == 1
        CTSUSO0_TS25,
    #endif
    #if SELF_ENABLE_TS26 == 1
        CTSUSO0_TS26,
    #endif
    #if SELF_ENABLE_TS27 == 1
        CTSUSO0_TS27,
    #endif
    #if SELF_ENABLE_TS28 == 1
        CTSUSO0_TS28,
    #endif
    #if SELF_ENABLE_TS29 == 1
        CTSUSO0_TS29,
    #endif
    #if SELF_ENABLE_TS30 == 1
        CTSUSO0_TS30,
    #endif
    #if SELF_ENABLE_TS31 == 1
        CTSUSO0_TS31,
    #endif
    #if SELF_ENABLE_TS32 == 1
        CTSUSO0_TS32,
    #endif
    #if SELF_ENABLE_TS33 == 1
        CTSUSO0_TS33,
    #endif
    #if SELF_ENABLE_TS34 == 1
        CTSUSO0_TS34,
    #endif
    #if SELF_ENABLE_TS35 == 1
        CTSUSO0_TS35,
    #endif
};

const uint16_t g_self_ctsuso1[] =
{ 
    #if SELF_ENABLE_TS00 == 1
        CTSUSO1_TS00,
    #endif
    #if SELF_ENABLE_TS01 == 1
        CTSUSO1_TS01,
    #endif
    #if SELF_ENABLE_TS02 == 1
        CTSUSO1_TS02,
    #endif
    #if SELF_ENABLE_TS03 == 1
        CTSUSO1_TS03,
    #endif
    #if SELF_ENABLE_TS04 == 1
        CTSUSO1_TS04,
    #endif
    #if SELF_ENABLE_TS05 == 1
        CTSUSO1_TS05,
    #endif
    #if SELF_ENABLE_TS06 == 1
        CTSUSO1_TS06,
    #endif
    #if SELF_ENABLE_TS07 == 1
        CTSUSO1_TS07,
    #endif
    #if SELF_ENABLE_TS08 == 1
        CTSUSO1_TS08,
    #endif
    #if SELF_ENABLE_TS09 == 1
        CTSUSO1_TS09,
    #endif
    #if SELF_ENABLE_TS10 == 1
        CTSUSO1_TS10,
    #endif
    #if SELF_ENABLE_TS11 == 1
        CTSUSO1_TS11,
    #endif
    #if SELF_ENABLE_TS12 == 1
        CTSUSO1_TS12,
    #endif
    #if SELF_ENABLE_TS13 == 1
        CTSUSO1_TS13,
    #endif
    #if SELF_ENABLE_TS14 == 1
        CTSUSO1_TS14,
    #endif
    #if SELF_ENABLE_TS15 == 1
        CTSUSO1_TS15,
    #endif
    #if SELF_ENABLE_TS16 == 1
        CTSUSO1_TS16,
    #endif
    #if SELF_ENABLE_TS17 == 1
        CTSUSO1_TS17,
    #endif
    #if SELF_ENABLE_TS18 == 1
        CTSUSO1_TS18,
    #endif
    #if SELF_ENABLE_TS19 == 1
        CTSUSO1_TS19,
    #endif
    #if SELF_ENABLE_TS20 == 1
        CTSUSO1_TS20,
    #endif
    #if SELF_ENABLE_TS21 == 1
        CTSUSO1_TS21,
    #endif
    #if SELF_ENABLE_TS22 == 1
        CTSUSO1_TS22,
    #endif
    #if SELF_ENABLE_TS23 == 1
        CTSUSO1_TS23,
    #endif
    #if SELF_ENABLE_TS24 == 1
        CTSUSO1_TS24,
    #endif
    #if SELF_ENABLE_TS25 == 1
        CTSUSO1_TS25,
    #endif
    #if SELF_ENABLE_TS26 == 1
        CTSUSO1_TS26,
    #endif
    #if SELF_ENABLE_TS27 == 1
        CTSUSO1_TS27,
    #endif
    #if SELF_ENABLE_TS28 == 1
        CTSUSO1_TS28,
    #endif
    #if SELF_ENABLE_TS29 == 1
        CTSUSO1_TS29,
    #endif
    #if SELF_ENABLE_TS30 == 1
        CTSUSO1_TS30,
    #endif
    #if SELF_ENABLE_TS31 == 1
        CTSUSO1_TS31,
    #endif
    #if SELF_ENABLE_TS32 == 1
        CTSUSO1_TS32,
    #endif
    #if SELF_ENABLE_TS33 == 1
        CTSUSO1_TS33,
    #endif
    #if SELF_ENABLE_TS34 == 1
        CTSUSO1_TS34,
    #endif
    #if SELF_ENABLE_TS35 == 1
        CTSUSO1_TS35,
    #endif
};
#endif    // ( SELF_METHOD_NUM == 1 )

/*=====    Mutual 0    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 0 )
const uint16_t g_mutual0_ctsussc[] =
{
    #if ( MUTUAL0_NUM >= 1 )
        CTSUSSC_MUTUAL0_KEY00,
    #endif
    #if ( MUTUAL0_NUM >= 2 )
        CTSUSSC_MUTUAL0_KEY01,
    #endif
    #if ( MUTUAL0_NUM >= 3 )
        CTSUSSC_MUTUAL0_KEY02,
    #endif
    #if ( MUTUAL0_NUM >= 4 )
        CTSUSSC_MUTUAL0_KEY03,
    #endif
    #if ( MUTUAL0_NUM >= 5 )
        CTSUSSC_MUTUAL0_KEY04,
    #endif
    #if ( MUTUAL0_NUM >= 6 )
        CTSUSSC_MUTUAL0_KEY05,
    #endif
    #if ( MUTUAL0_NUM >= 7 )
        CTSUSSC_MUTUAL0_KEY06,
    #endif
    #if ( MUTUAL0_NUM >= 8 )
        CTSUSSC_MUTUAL0_KEY07,
    #endif
    #if ( MUTUAL0_NUM >= 9 )
        CTSUSSC_MUTUAL0_KEY08,
    #endif
    #if ( MUTUAL0_NUM >= 10 )
        CTSUSSC_MUTUAL0_KEY09,
    #endif
    #if ( MUTUAL0_NUM >= 11 )
        CTSUSSC_MUTUAL0_KEY10,
    #endif
    #if ( MUTUAL0_NUM >= 12 )
        CTSUSSC_MUTUAL0_KEY11,
    #endif
    #if ( MUTUAL0_NUM >= 13 )
        CTSUSSC_MUTUAL0_KEY12,
    #endif
    #if ( MUTUAL0_NUM >= 14 )
        CTSUSSC_MUTUAL0_KEY13,
    #endif
    #if ( MUTUAL0_NUM >= 15 )
        CTSUSSC_MUTUAL0_KEY14,
    #endif
    #if ( MUTUAL0_NUM >= 16 )
        CTSUSSC_MUTUAL0_KEY15,
    #endif
    #if ( MUTUAL0_NUM >= 17 )
        CTSUSSC_MUTUAL0_KEY16,
    #endif
    #if ( MUTUAL0_NUM >= 18 )
        CTSUSSC_MUTUAL0_KEY17,
    #endif
    #if ( MUTUAL0_NUM >= 19 )
        CTSUSSC_MUTUAL0_KEY18,
    #endif
    #if ( MUTUAL0_NUM >= 20 )
        CTSUSSC_MUTUAL0_KEY19,
    #endif
    #if ( MUTUAL0_NUM >= 21 )
        CTSUSSC_MUTUAL0_KEY20,
    #endif
    #if ( MUTUAL0_NUM >= 22 )
        CTSUSSC_MUTUAL0_KEY21,
    #endif
    #if ( MUTUAL0_NUM >= 23 )
        CTSUSSC_MUTUAL0_KEY22,
    #endif
    #if ( MUTUAL0_NUM >= 24 )
        CTSUSSC_MUTUAL0_KEY23,
    #endif
    #if ( MUTUAL0_NUM >= 25 )
        CTSUSSC_MUTUAL0_KEY24,
    #endif
    #if ( MUTUAL0_NUM >= 26 )
        CTSUSSC_MUTUAL0_KEY25,
    #endif
    #if ( MUTUAL0_NUM >= 27 )
        CTSUSSC_MUTUAL0_KEY26,
    #endif
    #if ( MUTUAL0_NUM >= 28 )
        CTSUSSC_MUTUAL0_KEY27,
    #endif
    #if ( MUTUAL0_NUM >= 29 )
        CTSUSSC_MUTUAL0_KEY28,
    #endif
    #if ( MUTUAL0_NUM >= 30 )
        CTSUSSC_MUTUAL0_KEY29,
    #endif
    #if ( MUTUAL0_NUM >= 31 )
        CTSUSSC_MUTUAL0_KEY30,
    #endif
    #if ( MUTUAL0_NUM >= 32 )
        CTSUSSC_MUTUAL0_KEY31,
    #endif
    #if ( MUTUAL0_NUM >= 33 )
        CTSUSSC_MUTUAL0_KEY32,
    #endif
    #if ( MUTUAL0_NUM >= 34 )
        CTSUSSC_MUTUAL0_KEY33,
    #endif
    #if ( MUTUAL0_NUM >= 35 )
        CTSUSSC_MUTUAL0_KEY34,
    #endif
    #if ( MUTUAL0_NUM >= 36 )
        CTSUSSC_MUTUAL0_KEY35,
    #endif
    #if ( MUTUAL0_NUM >= 37 )
        CTSUSSC_MUTUAL0_KEY36,
    #endif
    #if ( MUTUAL0_NUM >= 38 )
        CTSUSSC_MUTUAL0_KEY37,
    #endif
    #if ( MUTUAL0_NUM >= 39 )
        CTSUSSC_MUTUAL0_KEY38,
    #endif
    #if ( MUTUAL0_NUM >= 40 )
        CTSUSSC_MUTUAL0_KEY39,
    #endif
    #if ( MUTUAL0_NUM >= 41 )
        CTSUSSC_MUTUAL0_KEY40,
    #endif
    #if ( MUTUAL0_NUM >= 42 )
        CTSUSSC_MUTUAL0_KEY41,
    #endif
    #if ( MUTUAL0_NUM >= 43 )
        CTSUSSC_MUTUAL0_KEY42,
    #endif
    #if ( MUTUAL0_NUM >= 44 )
        CTSUSSC_MUTUAL0_KEY43,
    #endif
    #if ( MUTUAL0_NUM >= 45 )
        CTSUSSC_MUTUAL0_KEY44,
    #endif
    #if ( MUTUAL0_NUM >= 46 )
        CTSUSSC_MUTUAL0_KEY45,
    #endif
    #if ( MUTUAL0_NUM >= 47 )
        CTSUSSC_MUTUAL0_KEY46,
    #endif
    #if ( MUTUAL0_NUM >= 48 )
        CTSUSSC_MUTUAL0_KEY47,
    #endif
    #if ( MUTUAL0_NUM >= 49 )
        CTSUSSC_MUTUAL0_KEY48,
    #endif
    #if ( MUTUAL0_NUM >= 50 )
        CTSUSSC_MUTUAL0_KEY49,
    #endif
    #if ( MUTUAL0_NUM >= 51 )
        CTSUSSC_MUTUAL0_KEY50,
    #endif
    #if ( MUTUAL0_NUM >= 52 )
        CTSUSSC_MUTUAL0_KEY51,
    #endif
    #if ( MUTUAL0_NUM >= 53 )
        CTSUSSC_MUTUAL0_KEY52,
    #endif
    #if ( MUTUAL0_NUM >= 54 )
        CTSUSSC_MUTUAL0_KEY53,
    #endif
    #if ( MUTUAL0_NUM >= 55 )
        CTSUSSC_MUTUAL0_KEY54,
    #endif
    #if ( MUTUAL0_NUM >= 56 )
        CTSUSSC_MUTUAL0_KEY55,
    #endif
    #if ( MUTUAL0_NUM >= 57 )
        CTSUSSC_MUTUAL0_KEY56,
    #endif
    #if ( MUTUAL0_NUM >= 58 )
        CTSUSSC_MUTUAL0_KEY57,
    #endif
    #if ( MUTUAL0_NUM >= 59 )
        CTSUSSC_MUTUAL0_KEY58,
    #endif
    #if ( MUTUAL0_NUM >= 60 )
        CTSUSSC_MUTUAL0_KEY59,
    #endif
    #if ( MUTUAL0_NUM >= 61 )
        CTSUSSC_MUTUAL0_KEY60,
    #endif
    #if ( MUTUAL0_NUM >= 62 )
        CTSUSSC_MUTUAL0_KEY61,
    #endif
    #if ( MUTUAL0_NUM >= 63 )
        CTSUSSC_MUTUAL0_KEY62,
    #endif
    #if ( MUTUAL0_NUM >= 64 )
        CTSUSSC_MUTUAL0_KEY63
    #endif
};

const uint16_t g_mutual0_ctsuso0[] =
{
    #if ( MUTUAL0_NUM >= 1 )
        CTSUSO0_MUTUAL0_KEY00,
    #endif
    #if ( MUTUAL0_NUM >= 2 )
        CTSUSO0_MUTUAL0_KEY01,
    #endif
    #if ( MUTUAL0_NUM >= 3 )
        CTSUSO0_MUTUAL0_KEY02,
    #endif
    #if ( MUTUAL0_NUM >= 4 )
        CTSUSO0_MUTUAL0_KEY03,
    #endif
    #if ( MUTUAL0_NUM >= 5 )
        CTSUSO0_MUTUAL0_KEY04,
    #endif
    #if ( MUTUAL0_NUM >= 6 )
        CTSUSO0_MUTUAL0_KEY05,
    #endif
    #if ( MUTUAL0_NUM >= 7 )
        CTSUSO0_MUTUAL0_KEY06,
    #endif
    #if ( MUTUAL0_NUM >= 8 )
        CTSUSO0_MUTUAL0_KEY07,
    #endif
    #if ( MUTUAL0_NUM >= 9 )
        CTSUSO0_MUTUAL0_KEY08,
    #endif
    #if ( MUTUAL0_NUM >= 10 )
        CTSUSO0_MUTUAL0_KEY09,
    #endif
    #if ( MUTUAL0_NUM >= 11 )
        CTSUSO0_MUTUAL0_KEY10,
    #endif
    #if ( MUTUAL0_NUM >= 12 )
        CTSUSO0_MUTUAL0_KEY11,
    #endif
    #if ( MUTUAL0_NUM >= 13 )
        CTSUSO0_MUTUAL0_KEY12,
    #endif
    #if ( MUTUAL0_NUM >= 14 )
        CTSUSO0_MUTUAL0_KEY13,
    #endif
    #if ( MUTUAL0_NUM >= 15 )
        CTSUSO0_MUTUAL0_KEY14,
    #endif
    #if ( MUTUAL0_NUM >= 16 )
        CTSUSO0_MUTUAL0_KEY15,
    #endif
    #if ( MUTUAL0_NUM >= 17 )
        CTSUSO0_MUTUAL0_KEY16,
    #endif
    #if ( MUTUAL0_NUM >= 18 )
        CTSUSO0_MUTUAL0_KEY17,
    #endif
    #if ( MUTUAL0_NUM >= 19 )
        CTSUSO0_MUTUAL0_KEY18,
    #endif
    #if ( MUTUAL0_NUM >= 20 )
        CTSUSO0_MUTUAL0_KEY19,
    #endif
    #if ( MUTUAL0_NUM >= 21 )
        CTSUSO0_MUTUAL0_KEY20,
    #endif
    #if ( MUTUAL0_NUM >= 22 )
        CTSUSO0_MUTUAL0_KEY21,
    #endif
    #if ( MUTUAL0_NUM >= 23 )
        CTSUSO0_MUTUAL0_KEY22,
    #endif
    #if ( MUTUAL0_NUM >= 24 )
        CTSUSO0_MUTUAL0_KEY23,
    #endif
    #if ( MUTUAL0_NUM >= 25 )
        CTSUSO0_MUTUAL0_KEY24,
    #endif
    #if ( MUTUAL0_NUM >= 26 )
        CTSUSO0_MUTUAL0_KEY25,
    #endif
    #if ( MUTUAL0_NUM >= 27 )
        CTSUSO0_MUTUAL0_KEY26,
    #endif
    #if ( MUTUAL0_NUM >= 28 )
        CTSUSO0_MUTUAL0_KEY27,
    #endif
    #if ( MUTUAL0_NUM >= 29 )
        CTSUSO0_MUTUAL0_KEY28,
    #endif
    #if ( MUTUAL0_NUM >= 30 )
        CTSUSO0_MUTUAL0_KEY29,
    #endif
    #if ( MUTUAL0_NUM >= 31 )
        CTSUSO0_MUTUAL0_KEY30,
    #endif
    #if ( MUTUAL0_NUM >= 32 )
        CTSUSO0_MUTUAL0_KEY31,
    #endif
    #if ( MUTUAL0_NUM >= 33 )
        CTSUSO0_MUTUAL0_KEY32,
    #endif
    #if ( MUTUAL0_NUM >= 34 )
        CTSUSO0_MUTUAL0_KEY33,
    #endif
    #if ( MUTUAL0_NUM >= 35 )
        CTSUSO0_MUTUAL0_KEY34,
    #endif
    #if ( MUTUAL0_NUM >= 36 )
        CTSUSO0_MUTUAL0_KEY35,
    #endif
    #if ( MUTUAL0_NUM >= 37 )
        CTSUSO0_MUTUAL0_KEY36,
    #endif
    #if ( MUTUAL0_NUM >= 38 )
        CTSUSO0_MUTUAL0_KEY37,
    #endif
    #if ( MUTUAL0_NUM >= 39 )
        CTSUSO0_MUTUAL0_KEY38,
    #endif
    #if ( MUTUAL0_NUM >= 40 )
        CTSUSO0_MUTUAL0_KEY39,
    #endif
    #if ( MUTUAL0_NUM >= 41 )
        CTSUSO0_MUTUAL0_KEY40,
    #endif
    #if ( MUTUAL0_NUM >= 42 )
        CTSUSO0_MUTUAL0_KEY41,
    #endif
    #if ( MUTUAL0_NUM >= 43 )
        CTSUSO0_MUTUAL0_KEY42,
    #endif
    #if ( MUTUAL0_NUM >= 44 )
        CTSUSO0_MUTUAL0_KEY43,
    #endif
    #if ( MUTUAL0_NUM >= 45 )
        CTSUSO0_MUTUAL0_KEY44,
    #endif
    #if ( MUTUAL0_NUM >= 46 )
        CTSUSO0_MUTUAL0_KEY45,
    #endif
    #if ( MUTUAL0_NUM >= 47 )
        CTSUSO0_MUTUAL0_KEY46,
    #endif
    #if ( MUTUAL0_NUM >= 48 )
        CTSUSO0_MUTUAL0_KEY47,
    #endif
    #if ( MUTUAL0_NUM >= 49 )
        CTSUSO0_MUTUAL0_KEY48,
    #endif
    #if ( MUTUAL0_NUM >= 50 )
        CTSUSO0_MUTUAL0_KEY49,
    #endif
    #if ( MUTUAL0_NUM >= 51 )
        CTSUSO0_MUTUAL0_KEY50,
    #endif
    #if ( MUTUAL0_NUM >= 52 )
        CTSUSO0_MUTUAL0_KEY51,
    #endif
    #if ( MUTUAL0_NUM >= 53 )
        CTSUSO0_MUTUAL0_KEY52,
    #endif
    #if ( MUTUAL0_NUM >= 54 )
        CTSUSO0_MUTUAL0_KEY53,
    #endif
    #if ( MUTUAL0_NUM >= 55 )
        CTSUSO0_MUTUAL0_KEY54,
    #endif
    #if ( MUTUAL0_NUM >= 56 )
        CTSUSO0_MUTUAL0_KEY55,
    #endif
    #if ( MUTUAL0_NUM >= 57 )
        CTSUSO0_MUTUAL0_KEY56,
    #endif
    #if ( MUTUAL0_NUM >= 58 )
        CTSUSO0_MUTUAL0_KEY57,
    #endif
    #if ( MUTUAL0_NUM >= 59 )
        CTSUSO0_MUTUAL0_KEY58,
    #endif
    #if ( MUTUAL0_NUM >= 60 )
        CTSUSO0_MUTUAL0_KEY59,
    #endif
    #if ( MUTUAL0_NUM >= 61 )
        CTSUSO0_MUTUAL0_KEY60,
    #endif
    #if ( MUTUAL0_NUM >= 62 )
        CTSUSO0_MUTUAL0_KEY61,
    #endif
    #if ( MUTUAL0_NUM >= 63 )
        CTSUSO0_MUTUAL0_KEY62,
    #endif
    #if ( MUTUAL0_NUM >= 64 )
        CTSUSO0_MUTUAL0_KEY63
    #endif
};

const uint16_t g_mutual0_ctsuso1[] =
{
    #if ( MUTUAL0_NUM >= 1 )
        CTSUSO1_MUTUAL0_KEY00,
    #endif
    #if ( MUTUAL0_NUM >= 2 )
        CTSUSO1_MUTUAL0_KEY01,
    #endif
    #if ( MUTUAL0_NUM >= 3 )
        CTSUSO1_MUTUAL0_KEY02,
    #endif
    #if ( MUTUAL0_NUM >= 4 )
        CTSUSO1_MUTUAL0_KEY03,
    #endif
    #if ( MUTUAL0_NUM >= 5 )
        CTSUSO1_MUTUAL0_KEY04,
    #endif
    #if ( MUTUAL0_NUM >= 6 )
        CTSUSO1_MUTUAL0_KEY05,
    #endif
    #if ( MUTUAL0_NUM >= 7 )
        CTSUSO1_MUTUAL0_KEY06,
    #endif
    #if ( MUTUAL0_NUM >= 8 )
        CTSUSO1_MUTUAL0_KEY07,
    #endif
    #if ( MUTUAL0_NUM >= 9 )
        CTSUSO1_MUTUAL0_KEY08,
    #endif
    #if ( MUTUAL0_NUM >= 10 )
        CTSUSO1_MUTUAL0_KEY09,
    #endif
    #if ( MUTUAL0_NUM >= 11 )
        CTSUSO1_MUTUAL0_KEY10,
    #endif
    #if ( MUTUAL0_NUM >= 12 )
        CTSUSO1_MUTUAL0_KEY11,
    #endif
    #if ( MUTUAL0_NUM >= 13 )
        CTSUSO1_MUTUAL0_KEY12,
    #endif
    #if ( MUTUAL0_NUM >= 14 )
        CTSUSO1_MUTUAL0_KEY13,
    #endif
    #if ( MUTUAL0_NUM >= 15 )
        CTSUSO1_MUTUAL0_KEY14,
    #endif
    #if ( MUTUAL0_NUM >= 16 )
        CTSUSO1_MUTUAL0_KEY15,
    #endif
    #if ( MUTUAL0_NUM >= 17 )
        CTSUSO1_MUTUAL0_KEY16,
    #endif
    #if ( MUTUAL0_NUM >= 18 )
        CTSUSO1_MUTUAL0_KEY17,
    #endif
    #if ( MUTUAL0_NUM >= 19 )
        CTSUSO1_MUTUAL0_KEY18,
    #endif
    #if ( MUTUAL0_NUM >= 20 )
        CTSUSO1_MUTUAL0_KEY19,
    #endif
    #if ( MUTUAL0_NUM >= 21 )
        CTSUSO1_MUTUAL0_KEY20,
    #endif
    #if ( MUTUAL0_NUM >= 22 )
        CTSUSO1_MUTUAL0_KEY21,
    #endif
    #if ( MUTUAL0_NUM >= 23 )
        CTSUSO1_MUTUAL0_KEY22,
    #endif
    #if ( MUTUAL0_NUM >= 24 )
        CTSUSO1_MUTUAL0_KEY23,
    #endif
    #if ( MUTUAL0_NUM >= 25 )
        CTSUSO1_MUTUAL0_KEY24,
    #endif
    #if ( MUTUAL0_NUM >= 26 )
        CTSUSO1_MUTUAL0_KEY25,
    #endif
    #if ( MUTUAL0_NUM >= 27 )
        CTSUSO1_MUTUAL0_KEY26,
    #endif
    #if ( MUTUAL0_NUM >= 28 )
        CTSUSO1_MUTUAL0_KEY27,
    #endif
    #if ( MUTUAL0_NUM >= 29 )
        CTSUSO1_MUTUAL0_KEY28,
    #endif
    #if ( MUTUAL0_NUM >= 30 )
        CTSUSO1_MUTUAL0_KEY29,
    #endif
    #if ( MUTUAL0_NUM >= 31 )
        CTSUSO1_MUTUAL0_KEY30,
    #endif
    #if ( MUTUAL0_NUM >= 32 )
        CTSUSO1_MUTUAL0_KEY31,
    #endif
    #if ( MUTUAL0_NUM >= 33 )
        CTSUSO1_MUTUAL0_KEY32,
    #endif
    #if ( MUTUAL0_NUM >= 34 )
        CTSUSO1_MUTUAL0_KEY33,
    #endif
    #if ( MUTUAL0_NUM >= 35 )
        CTSUSO1_MUTUAL0_KEY34,
    #endif
    #if ( MUTUAL0_NUM >= 36 )
        CTSUSO1_MUTUAL0_KEY35,
    #endif
    #if ( MUTUAL0_NUM >= 37 )
        CTSUSO1_MUTUAL0_KEY36,
    #endif
    #if ( MUTUAL0_NUM >= 38 )
        CTSUSO1_MUTUAL0_KEY37,
    #endif
    #if ( MUTUAL0_NUM >= 39 )
        CTSUSO1_MUTUAL0_KEY38,
    #endif
    #if ( MUTUAL0_NUM >= 40 )
        CTSUSO1_MUTUAL0_KEY39,
    #endif
    #if ( MUTUAL0_NUM >= 41 )
        CTSUSO1_MUTUAL0_KEY40,
    #endif
    #if ( MUTUAL0_NUM >= 42 )
        CTSUSO1_MUTUAL0_KEY41,
    #endif
    #if ( MUTUAL0_NUM >= 43 )
        CTSUSO1_MUTUAL0_KEY42,
    #endif
    #if ( MUTUAL0_NUM >= 44 )
        CTSUSO1_MUTUAL0_KEY43,
    #endif
    #if ( MUTUAL0_NUM >= 45 )
        CTSUSO1_MUTUAL0_KEY44,
    #endif
    #if ( MUTUAL0_NUM >= 46 )
        CTSUSO1_MUTUAL0_KEY45,
    #endif
    #if ( MUTUAL0_NUM >= 47 )
        CTSUSO1_MUTUAL0_KEY46,
    #endif
    #if ( MUTUAL0_NUM >= 48 )
        CTSUSO1_MUTUAL0_KEY47,
    #endif
    #if ( MUTUAL0_NUM >= 49 )
        CTSUSO1_MUTUAL0_KEY48,
    #endif
    #if ( MUTUAL0_NUM >= 50 )
        CTSUSO1_MUTUAL0_KEY49,
    #endif
    #if ( MUTUAL0_NUM >= 51 )
        CTSUSO1_MUTUAL0_KEY50,
    #endif
    #if ( MUTUAL0_NUM >= 52 )
        CTSUSO1_MUTUAL0_KEY51,
    #endif
    #if ( MUTUAL0_NUM >= 53 )
        CTSUSO1_MUTUAL0_KEY52,
    #endif
    #if ( MUTUAL0_NUM >= 54 )
        CTSUSO1_MUTUAL0_KEY53,
    #endif
    #if ( MUTUAL0_NUM >= 55 )
        CTSUSO1_MUTUAL0_KEY54,
    #endif
    #if ( MUTUAL0_NUM >= 56 )
        CTSUSO1_MUTUAL0_KEY55,
    #endif
    #if ( MUTUAL0_NUM >= 57 )
        CTSUSO1_MUTUAL0_KEY56,
    #endif
    #if ( MUTUAL0_NUM >= 58 )
        CTSUSO1_MUTUAL0_KEY57,
    #endif
    #if ( MUTUAL0_NUM >= 59 )
        CTSUSO1_MUTUAL0_KEY58,
    #endif
    #if ( MUTUAL0_NUM >= 60 )
        CTSUSO1_MUTUAL0_KEY59,
    #endif
    #if ( MUTUAL0_NUM >= 61 )
        CTSUSO1_MUTUAL0_KEY60,
    #endif
    #if ( MUTUAL0_NUM >= 62 )
        CTSUSO1_MUTUAL0_KEY61,
    #endif
    #if ( MUTUAL0_NUM >= 63 )
        CTSUSO1_MUTUAL0_KEY62,
    #endif
    #if ( MUTUAL0_NUM >= 64 )
        CTSUSO1_MUTUAL0_KEY63
    #endif
};
#endif    // ( MUTUAL_METHOD_NUM > 0 )

/*=====    Mutual 1    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 1 )
const uint16_t g_mutual1_ctsussc[] =
{
    #if ( MUTUAL1_NUM >= 1 )
        CTSUSSC_MUTUAL1_KEY00,
    #endif
    #if ( MUTUAL1_NUM >= 2 )
        CTSUSSC_MUTUAL1_KEY01,
    #endif
    #if ( MUTUAL1_NUM >= 3 )
        CTSUSSC_MUTUAL1_KEY02,
    #endif
    #if ( MUTUAL1_NUM >= 4 )
        CTSUSSC_MUTUAL1_KEY03,
    #endif
    #if ( MUTUAL1_NUM >= 5 )
        CTSUSSC_MUTUAL1_KEY04,
    #endif
    #if ( MUTUAL1_NUM >= 6 )
        CTSUSSC_MUTUAL1_KEY05,
    #endif
    #if ( MUTUAL1_NUM >= 7 )
        CTSUSSC_MUTUAL1_KEY06,
    #endif
    #if ( MUTUAL1_NUM >= 8 )
        CTSUSSC_MUTUAL1_KEY07,
    #endif
    #if ( MUTUAL1_NUM >= 9 )
        CTSUSSC_MUTUAL1_KEY08,
    #endif
    #if ( MUTUAL1_NUM >= 10 )
        CTSUSSC_MUTUAL1_KEY09,
    #endif
    #if ( MUTUAL1_NUM >= 11 )
        CTSUSSC_MUTUAL1_KEY10,
    #endif
    #if ( MUTUAL1_NUM >= 12 )
        CTSUSSC_MUTUAL1_KEY11,
    #endif
    #if ( MUTUAL1_NUM >= 13 )
        CTSUSSC_MUTUAL1_KEY12,
    #endif
    #if ( MUTUAL1_NUM >= 14 )
        CTSUSSC_MUTUAL1_KEY13,
    #endif
    #if ( MUTUAL1_NUM >= 15 )
        CTSUSSC_MUTUAL1_KEY14,
    #endif
    #if ( MUTUAL1_NUM >= 16 )
        CTSUSSC_MUTUAL1_KEY15,
    #endif
    #if ( MUTUAL1_NUM >= 17 )
        CTSUSSC_MUTUAL1_KEY16,
    #endif
    #if ( MUTUAL1_NUM >= 18 )
        CTSUSSC_MUTUAL1_KEY17,
    #endif
    #if ( MUTUAL1_NUM >= 19 )
        CTSUSSC_MUTUAL1_KEY18,
    #endif
    #if ( MUTUAL1_NUM >= 20 )
        CTSUSSC_MUTUAL1_KEY19,
    #endif
    #if ( MUTUAL1_NUM >= 21 )
        CTSUSSC_MUTUAL1_KEY20,
    #endif
    #if ( MUTUAL1_NUM >= 22 )
        CTSUSSC_MUTUAL1_KEY21,
    #endif
    #if ( MUTUAL1_NUM >= 23 )
        CTSUSSC_MUTUAL1_KEY22,
    #endif
    #if ( MUTUAL1_NUM >= 24 )
        CTSUSSC_MUTUAL1_KEY23,
    #endif
    #if ( MUTUAL1_NUM >= 25 )
        CTSUSSC_MUTUAL1_KEY24,
    #endif
    #if ( MUTUAL1_NUM >= 26 )
        CTSUSSC_MUTUAL1_KEY25,
    #endif
    #if ( MUTUAL1_NUM >= 27 )
        CTSUSSC_MUTUAL1_KEY26,
    #endif
    #if ( MUTUAL1_NUM >= 28 )
        CTSUSSC_MUTUAL1_KEY27,
    #endif
    #if ( MUTUAL1_NUM >= 29 )
        CTSUSSC_MUTUAL1_KEY28,
    #endif
    #if ( MUTUAL1_NUM >= 30 )
        CTSUSSC_MUTUAL1_KEY29,
    #endif
    #if ( MUTUAL1_NUM >= 31 )
        CTSUSSC_MUTUAL1_KEY30,
    #endif
    #if ( MUTUAL1_NUM >= 32 )
        CTSUSSC_MUTUAL1_KEY31,
    #endif
    #if ( MUTUAL1_NUM >= 33 )
        CTSUSSC_MUTUAL1_KEY32,
    #endif
    #if ( MUTUAL1_NUM >= 34 )
        CTSUSSC_MUTUAL1_KEY33,
    #endif
    #if ( MUTUAL1_NUM >= 35 )
        CTSUSSC_MUTUAL1_KEY34,
    #endif
    #if ( MUTUAL1_NUM >= 36 )
        CTSUSSC_MUTUAL1_KEY35,
    #endif
    #if ( MUTUAL1_NUM >= 37 )
        CTSUSSC_MUTUAL1_KEY36,
    #endif
    #if ( MUTUAL1_NUM >= 38 )
        CTSUSSC_MUTUAL1_KEY37,
    #endif
    #if ( MUTUAL1_NUM >= 39 )
        CTSUSSC_MUTUAL1_KEY38,
    #endif
    #if ( MUTUAL1_NUM >= 40 )
        CTSUSSC_MUTUAL1_KEY39,
    #endif
    #if ( MUTUAL1_NUM >= 41 )
        CTSUSSC_MUTUAL1_KEY40,
    #endif
    #if ( MUTUAL1_NUM >= 42 )
        CTSUSSC_MUTUAL1_KEY41,
    #endif
    #if ( MUTUAL1_NUM >= 43 )
        CTSUSSC_MUTUAL1_KEY42,
    #endif
    #if ( MUTUAL1_NUM >= 44 )
        CTSUSSC_MUTUAL1_KEY43,
    #endif
    #if ( MUTUAL1_NUM >= 45 )
        CTSUSSC_MUTUAL1_KEY44,
    #endif
    #if ( MUTUAL1_NUM >= 46 )
        CTSUSSC_MUTUAL1_KEY45,
    #endif
    #if ( MUTUAL1_NUM >= 47 )
        CTSUSSC_MUTUAL1_KEY46,
    #endif
    #if ( MUTUAL1_NUM >= 48 )
        CTSUSSC_MUTUAL1_KEY47,
    #endif
    #if ( MUTUAL1_NUM >= 49 )
        CTSUSSC_MUTUAL1_KEY48,
    #endif
    #if ( MUTUAL1_NUM >= 50 )
        CTSUSSC_MUTUAL1_KEY49,
    #endif
    #if ( MUTUAL1_NUM >= 51 )
        CTSUSSC_MUTUAL1_KEY50,
    #endif
    #if ( MUTUAL1_NUM >= 52 )
        CTSUSSC_MUTUAL1_KEY51,
    #endif
    #if ( MUTUAL1_NUM >= 53 )
        CTSUSSC_MUTUAL1_KEY52,
    #endif
    #if ( MUTUAL1_NUM >= 54 )
        CTSUSSC_MUTUAL1_KEY53,
    #endif
    #if ( MUTUAL1_NUM >= 55 )
        CTSUSSC_MUTUAL1_KEY54,
    #endif
    #if ( MUTUAL1_NUM >= 56 )
        CTSUSSC_MUTUAL1_KEY55,
    #endif
    #if ( MUTUAL1_NUM >= 57 )
        CTSUSSC_MUTUAL1_KEY56,
    #endif
    #if ( MUTUAL1_NUM >= 58 )
        CTSUSSC_MUTUAL1_KEY57,
    #endif
    #if ( MUTUAL1_NUM >= 59 )
        CTSUSSC_MUTUAL1_KEY58,
    #endif
    #if ( MUTUAL1_NUM >= 60 )
        CTSUSSC_MUTUAL1_KEY59,
    #endif
    #if ( MUTUAL1_NUM >= 61 )
        CTSUSSC_MUTUAL1_KEY60,
    #endif
    #if ( MUTUAL1_NUM >= 62 )
        CTSUSSC_MUTUAL1_KEY61,
    #endif
    #if ( MUTUAL1_NUM >= 63 )
        CTSUSSC_MUTUAL1_KEY62,
    #endif
    #if ( MUTUAL1_NUM >= 64 )
        CTSUSSC_MUTUAL1_KEY63
    #endif
};

const uint16_t g_mutual1_ctsuso0[] =
{
    #if ( MUTUAL1_NUM >= 1 )
        CTSUSO0_MUTUAL1_KEY00,
    #endif
    #if ( MUTUAL1_NUM >= 2 )
        CTSUSO0_MUTUAL1_KEY01,
    #endif
    #if ( MUTUAL1_NUM >= 3 )
        CTSUSO0_MUTUAL1_KEY02,
    #endif
    #if ( MUTUAL1_NUM >= 4 )
        CTSUSO0_MUTUAL1_KEY03,
    #endif
    #if ( MUTUAL1_NUM >= 5 )
        CTSUSO0_MUTUAL1_KEY04,
    #endif
    #if ( MUTUAL1_NUM >= 6 )
        CTSUSO0_MUTUAL1_KEY05,
    #endif
    #if ( MUTUAL1_NUM >= 7 )
        CTSUSO0_MUTUAL1_KEY06,
    #endif
    #if ( MUTUAL1_NUM >= 8 )
        CTSUSO0_MUTUAL1_KEY07,
    #endif
    #if ( MUTUAL1_NUM >= 9 )
        CTSUSO0_MUTUAL1_KEY08,
    #endif
    #if ( MUTUAL1_NUM >= 10 )
        CTSUSO0_MUTUAL1_KEY09,
    #endif
    #if ( MUTUAL1_NUM >= 11 )
        CTSUSO0_MUTUAL1_KEY10,
    #endif
    #if ( MUTUAL1_NUM >= 12 )
        CTSUSO0_MUTUAL1_KEY11,
    #endif
    #if ( MUTUAL1_NUM >= 13 )
        CTSUSO0_MUTUAL1_KEY12,
    #endif
    #if ( MUTUAL1_NUM >= 14 )
        CTSUSO0_MUTUAL1_KEY13,
    #endif
    #if ( MUTUAL1_NUM >= 15 )
        CTSUSO0_MUTUAL1_KEY14,
    #endif
    #if ( MUTUAL1_NUM >= 16 )
        CTSUSO0_MUTUAL1_KEY15,
    #endif
    #if ( MUTUAL1_NUM >= 17 )
        CTSUSO0_MUTUAL1_KEY16,
    #endif
    #if ( MUTUAL1_NUM >= 18 )
        CTSUSO0_MUTUAL1_KEY17,
    #endif
    #if ( MUTUAL1_NUM >= 19 )
        CTSUSO0_MUTUAL1_KEY18,
    #endif
    #if ( MUTUAL1_NUM >= 20 )
        CTSUSO0_MUTUAL1_KEY19,
    #endif
    #if ( MUTUAL1_NUM >= 21 )
        CTSUSO0_MUTUAL1_KEY20,
    #endif
    #if ( MUTUAL1_NUM >= 22 )
        CTSUSO0_MUTUAL1_KEY21,
    #endif
    #if ( MUTUAL1_NUM >= 23 )
        CTSUSO0_MUTUAL1_KEY22,
    #endif
    #if ( MUTUAL1_NUM >= 24 )
        CTSUSO0_MUTUAL1_KEY23,
    #endif
    #if ( MUTUAL1_NUM >= 25 )
        CTSUSO0_MUTUAL1_KEY24,
    #endif
    #if ( MUTUAL1_NUM >= 26 )
        CTSUSO0_MUTUAL1_KEY25,
    #endif
    #if ( MUTUAL1_NUM >= 27 )
        CTSUSO0_MUTUAL1_KEY26,
    #endif
    #if ( MUTUAL1_NUM >= 28 )
        CTSUSO0_MUTUAL1_KEY27,
    #endif
    #if ( MUTUAL1_NUM >= 29 )
        CTSUSO0_MUTUAL1_KEY28,
    #endif
    #if ( MUTUAL1_NUM >= 30 )
        CTSUSO0_MUTUAL1_KEY29,
    #endif
    #if ( MUTUAL1_NUM >= 31 )
        CTSUSO0_MUTUAL1_KEY30,
    #endif
    #if ( MUTUAL1_NUM >= 32 )
        CTSUSO0_MUTUAL1_KEY31,
    #endif
    #if ( MUTUAL1_NUM >= 33 )
        CTSUSO0_MUTUAL1_KEY32,
    #endif
    #if ( MUTUAL1_NUM >= 34 )
        CTSUSO0_MUTUAL1_KEY33,
    #endif
    #if ( MUTUAL1_NUM >= 35 )
        CTSUSO0_MUTUAL1_KEY34,
    #endif
    #if ( MUTUAL1_NUM >= 36 )
        CTSUSO0_MUTUAL1_KEY35,
    #endif
    #if ( MUTUAL1_NUM >= 37 )
        CTSUSO0_MUTUAL1_KEY36,
    #endif
    #if ( MUTUAL1_NUM >= 38 )
        CTSUSO0_MUTUAL1_KEY37,
    #endif
    #if ( MUTUAL1_NUM >= 39 )
        CTSUSO0_MUTUAL1_KEY38,
    #endif
    #if ( MUTUAL1_NUM >= 40 )
        CTSUSO0_MUTUAL1_KEY39,
    #endif
    #if ( MUTUAL1_NUM >= 41 )
        CTSUSO0_MUTUAL1_KEY40,
    #endif
    #if ( MUTUAL1_NUM >= 42 )
        CTSUSO0_MUTUAL1_KEY41,
    #endif
    #if ( MUTUAL1_NUM >= 43 )
        CTSUSO0_MUTUAL1_KEY42,
    #endif
    #if ( MUTUAL1_NUM >= 44 )
        CTSUSO0_MUTUAL1_KEY43,
    #endif
    #if ( MUTUAL1_NUM >= 45 )
        CTSUSO0_MUTUAL1_KEY44,
    #endif
    #if ( MUTUAL1_NUM >= 46 )
        CTSUSO0_MUTUAL1_KEY45,
    #endif
    #if ( MUTUAL1_NUM >= 47 )
        CTSUSO0_MUTUAL1_KEY46,
    #endif
    #if ( MUTUAL1_NUM >= 48 )
        CTSUSO0_MUTUAL1_KEY47,
    #endif
    #if ( MUTUAL1_NUM >= 49 )
        CTSUSO0_MUTUAL1_KEY48,
    #endif
    #if ( MUTUAL1_NUM >= 50 )
        CTSUSO0_MUTUAL1_KEY49,
    #endif
    #if ( MUTUAL1_NUM >= 51 )
        CTSUSO0_MUTUAL1_KEY50,
    #endif
    #if ( MUTUAL1_NUM >= 52 )
        CTSUSO0_MUTUAL1_KEY51,
    #endif
    #if ( MUTUAL1_NUM >= 53 )
        CTSUSO0_MUTUAL1_KEY52,
    #endif
    #if ( MUTUAL1_NUM >= 54 )
        CTSUSO0_MUTUAL1_KEY53,
    #endif
    #if ( MUTUAL1_NUM >= 55 )
        CTSUSO0_MUTUAL1_KEY54,
    #endif
    #if ( MUTUAL1_NUM >= 56 )
        CTSUSO0_MUTUAL1_KEY55,
    #endif
    #if ( MUTUAL1_NUM >= 57 )
        CTSUSO0_MUTUAL1_KEY56,
    #endif
    #if ( MUTUAL1_NUM >= 58 )
        CTSUSO0_MUTUAL1_KEY57,
    #endif
    #if ( MUTUAL1_NUM >= 59 )
        CTSUSO0_MUTUAL1_KEY58,
    #endif
    #if ( MUTUAL1_NUM >= 60 )
        CTSUSO0_MUTUAL1_KEY59,
    #endif
    #if ( MUTUAL1_NUM >= 61 )
        CTSUSO0_MUTUAL1_KEY60,
    #endif
    #if ( MUTUAL1_NUM >= 62 )
        CTSUSO0_MUTUAL1_KEY61,
    #endif
    #if ( MUTUAL1_NUM >= 63 )
        CTSUSO0_MUTUAL1_KEY62,
    #endif
    #if ( MUTUAL1_NUM >= 64 )
        CTSUSO0_MUTUAL1_KEY63
    #endif
};

const uint16_t g_mutual1_ctsuso1[] =
{
    #if ( MUTUAL1_NUM >= 1 )
        CTSUSO1_MUTUAL1_KEY00,
    #endif
    #if ( MUTUAL1_NUM >= 2 )
        CTSUSO1_MUTUAL1_KEY01,
    #endif
    #if ( MUTUAL1_NUM >= 3 )
        CTSUSO1_MUTUAL1_KEY02,
    #endif
    #if ( MUTUAL1_NUM >= 4 )
        CTSUSO1_MUTUAL1_KEY03,
    #endif
    #if ( MUTUAL1_NUM >= 5 )
        CTSUSO1_MUTUAL1_KEY04,
    #endif
    #if ( MUTUAL1_NUM >= 6 )
        CTSUSO1_MUTUAL1_KEY05,
    #endif
    #if ( MUTUAL1_NUM >= 7 )
        CTSUSO1_MUTUAL1_KEY06,
    #endif
    #if ( MUTUAL1_NUM >= 8 )
        CTSUSO1_MUTUAL1_KEY07,
    #endif
    #if ( MUTUAL1_NUM >= 9 )
        CTSUSO1_MUTUAL1_KEY08,
    #endif
    #if ( MUTUAL1_NUM >= 10 )
        CTSUSO1_MUTUAL1_KEY09,
    #endif
    #if ( MUTUAL1_NUM >= 11 )
        CTSUSO1_MUTUAL1_KEY10,
    #endif
    #if ( MUTUAL1_NUM >= 12 )
        CTSUSO1_MUTUAL1_KEY11,
    #endif
    #if ( MUTUAL1_NUM >= 13 )
        CTSUSO1_MUTUAL1_KEY12,
    #endif
    #if ( MUTUAL1_NUM >= 14 )
        CTSUSO1_MUTUAL1_KEY13,
    #endif
    #if ( MUTUAL1_NUM >= 15 )
        CTSUSO1_MUTUAL1_KEY14,
    #endif
    #if ( MUTUAL1_NUM >= 16 )
        CTSUSO1_MUTUAL1_KEY15,
    #endif
    #if ( MUTUAL1_NUM >= 17 )
        CTSUSO1_MUTUAL1_KEY16,
    #endif
    #if ( MUTUAL1_NUM >= 18 )
        CTSUSO1_MUTUAL1_KEY17,
    #endif
    #if ( MUTUAL1_NUM >= 19 )
        CTSUSO1_MUTUAL1_KEY18,
    #endif
    #if ( MUTUAL1_NUM >= 20 )
        CTSUSO1_MUTUAL1_KEY19,
    #endif
    #if ( MUTUAL1_NUM >= 21 )
        CTSUSO1_MUTUAL1_KEY20,
    #endif
    #if ( MUTUAL1_NUM >= 22 )
        CTSUSO1_MUTUAL1_KEY21,
    #endif
    #if ( MUTUAL1_NUM >= 23 )
        CTSUSO1_MUTUAL1_KEY22,
    #endif
    #if ( MUTUAL1_NUM >= 24 )
        CTSUSO1_MUTUAL1_KEY23,
    #endif
    #if ( MUTUAL1_NUM >= 25 )
        CTSUSO1_MUTUAL1_KEY24,
    #endif
    #if ( MUTUAL1_NUM >= 26 )
        CTSUSO1_MUTUAL1_KEY25,
    #endif
    #if ( MUTUAL1_NUM >= 27 )
        CTSUSO1_MUTUAL1_KEY26,
    #endif
    #if ( MUTUAL1_NUM >= 28 )
        CTSUSO1_MUTUAL1_KEY27,
    #endif
    #if ( MUTUAL1_NUM >= 29 )
        CTSUSO1_MUTUAL1_KEY28,
    #endif
    #if ( MUTUAL1_NUM >= 30 )
        CTSUSO1_MUTUAL1_KEY29,
    #endif
    #if ( MUTUAL1_NUM >= 31 )
        CTSUSO1_MUTUAL1_KEY30,
    #endif
    #if ( MUTUAL1_NUM >= 32 )
        CTSUSO1_MUTUAL1_KEY31,
    #endif
    #if ( MUTUAL1_NUM >= 33 )
        CTSUSO1_MUTUAL1_KEY32,
    #endif
    #if ( MUTUAL1_NUM >= 34 )
        CTSUSO1_MUTUAL1_KEY33,
    #endif
    #if ( MUTUAL1_NUM >= 35 )
        CTSUSO1_MUTUAL1_KEY34,
    #endif
    #if ( MUTUAL1_NUM >= 36 )
        CTSUSO1_MUTUAL1_KEY35,
    #endif
    #if ( MUTUAL1_NUM >= 37 )
        CTSUSO1_MUTUAL1_KEY36,
    #endif
    #if ( MUTUAL1_NUM >= 38 )
        CTSUSO1_MUTUAL1_KEY37,
    #endif
    #if ( MUTUAL1_NUM >= 39 )
        CTSUSO1_MUTUAL1_KEY38,
    #endif
    #if ( MUTUAL1_NUM >= 40 )
        CTSUSO1_MUTUAL1_KEY39,
    #endif
    #if ( MUTUAL1_NUM >= 41 )
        CTSUSO1_MUTUAL1_KEY40,
    #endif
    #if ( MUTUAL1_NUM >= 42 )
        CTSUSO1_MUTUAL1_KEY41,
    #endif
    #if ( MUTUAL1_NUM >= 43 )
        CTSUSO1_MUTUAL1_KEY42,
    #endif
    #if ( MUTUAL1_NUM >= 44 )
        CTSUSO1_MUTUAL1_KEY43,
    #endif
    #if ( MUTUAL1_NUM >= 45 )
        CTSUSO1_MUTUAL1_KEY44,
    #endif
    #if ( MUTUAL1_NUM >= 46 )
        CTSUSO1_MUTUAL1_KEY45,
    #endif
    #if ( MUTUAL1_NUM >= 47 )
        CTSUSO1_MUTUAL1_KEY46,
    #endif
    #if ( MUTUAL1_NUM >= 48 )
        CTSUSO1_MUTUAL1_KEY47,
    #endif
    #if ( MUTUAL1_NUM >= 49 )
        CTSUSO1_MUTUAL1_KEY48,
    #endif
    #if ( MUTUAL1_NUM >= 50 )
        CTSUSO1_MUTUAL1_KEY49,
    #endif
    #if ( MUTUAL1_NUM >= 51 )
        CTSUSO1_MUTUAL1_KEY50,
    #endif
    #if ( MUTUAL1_NUM >= 52 )
        CTSUSO1_MUTUAL1_KEY51,
    #endif
    #if ( MUTUAL1_NUM >= 53 )
        CTSUSO1_MUTUAL1_KEY52,
    #endif
    #if ( MUTUAL1_NUM >= 54 )
        CTSUSO1_MUTUAL1_KEY53,
    #endif
    #if ( MUTUAL1_NUM >= 55 )
        CTSUSO1_MUTUAL1_KEY54,
    #endif
    #if ( MUTUAL1_NUM >= 56 )
        CTSUSO1_MUTUAL1_KEY55,
    #endif
    #if ( MUTUAL1_NUM >= 57 )
        CTSUSO1_MUTUAL1_KEY56,
    #endif
    #if ( MUTUAL1_NUM >= 58 )
        CTSUSO1_MUTUAL1_KEY57,
    #endif
    #if ( MUTUAL1_NUM >= 59 )
        CTSUSO1_MUTUAL1_KEY58,
    #endif
    #if ( MUTUAL1_NUM >= 60 )
        CTSUSO1_MUTUAL1_KEY59,
    #endif
    #if ( MUTUAL1_NUM >= 61 )
        CTSUSO1_MUTUAL1_KEY60,
    #endif
    #if ( MUTUAL1_NUM >= 62 )
        CTSUSO1_MUTUAL1_KEY61,
    #endif
    #if ( MUTUAL1_NUM >= 63 )
        CTSUSO1_MUTUAL1_KEY62,
    #endif
    #if ( MUTUAL1_NUM >= 64 )
        CTSUSO1_MUTUAL1_KEY63
    #endif
};
#endif    // ( MUTUAL_METHOD_NUM > 1 )

/*=====    Mutual 2    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 2 )
const uint16_t g_mutual2_ctsussc[] =
{
    #if ( MUTUAL2_NUM > 0 )
        CTSUSSC_MUTUAL2_KEY00,
    #endif
    #if ( MUTUAL2_NUM > 1 )
        CTSUSSC_MUTUAL2_KEY01,
    #endif
    #if ( MUTUAL2_NUM > 2 )
        CTSUSSC_MUTUAL2_KEY02,
    #endif
    #if ( MUTUAL2_NUM > 3 )
        CTSUSSC_MUTUAL2_KEY03,
    #endif
    #if ( MUTUAL2_NUM > 4 )
        CTSUSSC_MUTUAL2_KEY04,
    #endif
    #if ( MUTUAL2_NUM > 5 )
        CTSUSSC_MUTUAL2_KEY05,
    #endif
    #if ( MUTUAL2_NUM > 6 )
        CTSUSSC_MUTUAL2_KEY06,
    #endif
    #if ( MUTUAL2_NUM > 7 )
        CTSUSSC_MUTUAL2_KEY07,
    #endif
    #if ( MUTUAL2_NUM > 8 )
        CTSUSSC_MUTUAL2_KEY08,
    #endif
    #if ( MUTUAL2_NUM > 9 )
        CTSUSSC_MUTUAL2_KEY09,
    #endif
    #if ( MUTUAL2_NUM > 10 )
        CTSUSSC_MUTUAL2_KEY10,
    #endif
    #if ( MUTUAL2_NUM > 11 )
        CTSUSSC_MUTUAL2_KEY11,
    #endif
    #if ( MUTUAL2_NUM > 12 )
        CTSUSSC_MUTUAL2_KEY12,
    #endif
    #if ( MUTUAL2_NUM > 13 )
        CTSUSSC_MUTUAL2_KEY13,
    #endif
    #if ( MUTUAL2_NUM > 14 )
        CTSUSSC_MUTUAL2_KEY14,
    #endif
    #if ( MUTUAL2_NUM > 15 )
        CTSUSSC_MUTUAL2_KEY15,
    #endif
    #if ( MUTUAL2_NUM > 16 )
        CTSUSSC_MUTUAL2_KEY16,
    #endif
    #if ( MUTUAL2_NUM > 17 )
        CTSUSSC_MUTUAL2_KEY17,
    #endif
    #if ( MUTUAL2_NUM > 18 )
        CTSUSSC_MUTUAL2_KEY18,
    #endif
    #if ( MUTUAL2_NUM > 19 )
        CTSUSSC_MUTUAL2_KEY19,
    #endif
    #if ( MUTUAL2_NUM > 20 )
        CTSUSSC_MUTUAL2_KEY20,
    #endif
    #if ( MUTUAL2_NUM > 21 )
        CTSUSSC_MUTUAL2_KEY21,
    #endif
    #if ( MUTUAL2_NUM > 22 )
        CTSUSSC_MUTUAL2_KEY22,
    #endif
    #if ( MUTUAL2_NUM > 23 )
        CTSUSSC_MUTUAL2_KEY23,
    #endif
    #if ( MUTUAL2_NUM > 24 )
        CTSUSSC_MUTUAL2_KEY24,
    #endif
    #if ( MUTUAL2_NUM > 25 )
        CTSUSSC_MUTUAL2_KEY25,
    #endif
    #if ( MUTUAL2_NUM > 26 )
        CTSUSSC_MUTUAL2_KEY26,
    #endif
    #if ( MUTUAL2_NUM > 27 )
        CTSUSSC_MUTUAL2_KEY27,
    #endif
    #if ( MUTUAL2_NUM > 28 )
        CTSUSSC_MUTUAL2_KEY28,
    #endif
    #if ( MUTUAL2_NUM > 29 )
        CTSUSSC_MUTUAL2_KEY29,
    #endif
    #if ( MUTUAL2_NUM > 30 )
        CTSUSSC_MUTUAL2_KEY30,
    #endif
    #if ( MUTUAL2_NUM > 31 )
        CTSUSSC_MUTUAL2_KEY31,
    #endif
    #if ( MUTUAL2_NUM > 32 )
        CTSUSSC_MUTUAL2_KEY32,
    #endif
    #if ( MUTUAL2_NUM > 33 )
        CTSUSSC_MUTUAL2_KEY33,
    #endif
    #if ( MUTUAL2_NUM > 34 )
        CTSUSSC_MUTUAL2_KEY34,
    #endif
    #if ( MUTUAL2_NUM > 35 )
        CTSUSSC_MUTUAL2_KEY35,
    #endif
    #if ( MUTUAL2_NUM > 36 )
        CTSUSSC_MUTUAL2_KEY36,
    #endif
    #if ( MUTUAL2_NUM > 37 )
        CTSUSSC_MUTUAL2_KEY37,
    #endif
    #if ( MUTUAL2_NUM > 38 )
        CTSUSSC_MUTUAL2_KEY38,
    #endif
    #if ( MUTUAL2_NUM > 39 )
        CTSUSSC_MUTUAL2_KEY39,
    #endif
    #if ( MUTUAL2_NUM > 40 )
        CTSUSSC_MUTUAL2_KEY40,
    #endif
    #if ( MUTUAL2_NUM > 41 )
        CTSUSSC_MUTUAL2_KEY41,
    #endif
    #if ( MUTUAL2_NUM > 42 )
        CTSUSSC_MUTUAL2_KEY42,
    #endif
    #if ( MUTUAL2_NUM > 43 )
        CTSUSSC_MUTUAL2_KEY43,
    #endif
    #if ( MUTUAL2_NUM > 44 )
        CTSUSSC_MUTUAL2_KEY44,
    #endif
    #if ( MUTUAL2_NUM > 45 )
        CTSUSSC_MUTUAL2_KEY45,
    #endif
    #if ( MUTUAL2_NUM > 46 )
        CTSUSSC_MUTUAL2_KEY46,
    #endif
    #if ( MUTUAL2_NUM > 47 )
        CTSUSSC_MUTUAL2_KEY47,
    #endif
    #if ( MUTUAL2_NUM > 48 )
        CTSUSSC_MUTUAL2_KEY48,
    #endif
    #if ( MUTUAL2_NUM > 49 )
        CTSUSSC_MUTUAL2_KEY49,
    #endif
    #if ( MUTUAL2_NUM > 50 )
        CTSUSSC_MUTUAL2_KEY50,
    #endif
    #if ( MUTUAL2_NUM > 51 )
        CTSUSSC_MUTUAL2_KEY51,
    #endif
    #if ( MUTUAL2_NUM > 52 )
        CTSUSSC_MUTUAL2_KEY52,
    #endif
    #if ( MUTUAL2_NUM > 53 )
        CTSUSSC_MUTUAL2_KEY53,
    #endif
    #if ( MUTUAL2_NUM > 54 )
        CTSUSSC_MUTUAL2_KEY54,
    #endif
    #if ( MUTUAL2_NUM > 55 )
        CTSUSSC_MUTUAL2_KEY55,
    #endif
    #if ( MUTUAL2_NUM > 56 )
        CTSUSSC_MUTUAL2_KEY56,
    #endif
    #if ( MUTUAL2_NUM > 57 )
        CTSUSSC_MUTUAL2_KEY57,
    #endif
    #if ( MUTUAL2_NUM > 58 )
        CTSUSSC_MUTUAL2_KEY58,
    #endif
    #if ( MUTUAL2_NUM > 59 )
        CTSUSSC_MUTUAL2_KEY59,
    #endif
    #if ( MUTUAL2_NUM > 60 )
        CTSUSSC_MUTUAL2_KEY60,
    #endif
    #if ( MUTUAL2_NUM > 61 )
        CTSUSSC_MUTUAL2_KEY61,
    #endif
    #if ( MUTUAL2_NUM > 62 )
        CTSUSSC_MUTUAL2_KEY62,
    #endif
    #if ( MUTUAL2_NUM > 63 )
        CTSUSSC_MUTUAL2_KEY63
    #endif
};

const uint16_t g_mutual2_ctsuso0[] =
{
#if ( MUTUAL2_NUM > 0 )
    CTSUSO0_MUTUAL2_KEY00,
#endif
#if ( MUTUAL2_NUM > 1 )
    CTSUSO0_MUTUAL2_KEY01,
#endif
#if ( MUTUAL2_NUM > 2 )
    CTSUSO0_MUTUAL2_KEY02,
#endif
#if ( MUTUAL2_NUM > 3 )
    CTSUSO0_MUTUAL2_KEY03,
#endif
#if ( MUTUAL2_NUM > 4 )
    CTSUSO0_MUTUAL2_KEY04,
#endif
#if ( MUTUAL2_NUM > 5 )
    CTSUSO0_MUTUAL2_KEY05,
#endif
#if ( MUTUAL2_NUM > 6 )
    CTSUSO0_MUTUAL2_KEY06,
#endif
#if ( MUTUAL2_NUM > 7 )
    CTSUSO0_MUTUAL2_KEY07,
#endif
#if ( MUTUAL2_NUM > 8 )
    CTSUSO0_MUTUAL2_KEY08,
#endif
#if ( MUTUAL2_NUM > 9 )
    CTSUSO0_MUTUAL2_KEY09,
#endif
#if ( MUTUAL2_NUM > 10 )
    CTSUSO0_MUTUAL2_KEY10,
#endif
#if ( MUTUAL2_NUM > 11 )
    CTSUSO0_MUTUAL2_KEY11,
#endif
#if ( MUTUAL2_NUM > 12 )
    CTSUSO0_MUTUAL2_KEY12,
#endif
#if ( MUTUAL2_NUM > 13 )
    CTSUSO0_MUTUAL2_KEY13,
#endif
#if ( MUTUAL2_NUM > 14 )
    CTSUSO0_MUTUAL2_KEY14,
#endif
#if ( MUTUAL2_NUM > 15 )
    CTSUSO0_MUTUAL2_KEY15,
#endif
#if ( MUTUAL2_NUM > 16 )
    CTSUSO0_MUTUAL2_KEY16,
#endif
#if ( MUTUAL2_NUM > 17 )
    CTSUSO0_MUTUAL2_KEY17,
#endif
#if ( MUTUAL2_NUM > 18 )
    CTSUSO0_MUTUAL2_KEY18,
#endif
#if ( MUTUAL2_NUM > 19 )
    CTSUSO0_MUTUAL2_KEY19,
#endif
#if ( MUTUAL2_NUM > 20 )
    CTSUSO0_MUTUAL2_KEY20,
#endif
#if ( MUTUAL2_NUM > 21 )
    CTSUSO0_MUTUAL2_KEY21,
#endif
#if ( MUTUAL2_NUM > 22 )
    CTSUSO0_MUTUAL2_KEY22,
#endif
#if ( MUTUAL2_NUM > 23 )
    CTSUSO0_MUTUAL2_KEY23,
#endif
#if ( MUTUAL2_NUM > 24 )
    CTSUSO0_MUTUAL2_KEY24,
#endif
#if ( MUTUAL2_NUM > 25 )
    CTSUSO0_MUTUAL2_KEY25,
#endif
#if ( MUTUAL2_NUM > 26 )
    CTSUSO0_MUTUAL2_KEY26,
#endif
#if ( MUTUAL2_NUM > 27 )
    CTSUSO0_MUTUAL2_KEY27,
#endif
#if ( MUTUAL2_NUM > 28 )
    CTSUSO0_MUTUAL2_KEY28,
#endif
#if ( MUTUAL2_NUM > 29 )
    CTSUSO0_MUTUAL2_KEY29,
#endif
#if ( MUTUAL2_NUM > 30 )
    CTSUSO0_MUTUAL2_KEY30,
#endif
#if ( MUTUAL2_NUM > 31 )
    CTSUSO0_MUTUAL2_KEY31,
#endif
#if ( MUTUAL2_NUM > 32 )
    CTSUSO0_MUTUAL2_KEY32,
#endif
#if ( MUTUAL2_NUM > 33 )
    CTSUSO0_MUTUAL2_KEY33,
#endif
#if ( MUTUAL2_NUM > 34 )
    CTSUSO0_MUTUAL2_KEY34,
#endif
#if ( MUTUAL2_NUM > 35 )
    CTSUSO0_MUTUAL2_KEY35,
#endif
#if ( MUTUAL2_NUM > 36 )
    CTSUSO0_MUTUAL2_KEY36,
#endif
#if ( MUTUAL2_NUM > 37 )
    CTSUSO0_MUTUAL2_KEY37,
#endif
#if ( MUTUAL2_NUM > 38 )
    CTSUSO0_MUTUAL2_KEY38,
#endif
#if ( MUTUAL2_NUM > 39 )
    CTSUSO0_MUTUAL2_KEY39,
#endif
#if ( MUTUAL2_NUM > 40 )
    CTSUSO0_MUTUAL2_KEY40,
#endif
#if ( MUTUAL2_NUM > 41 )
    CTSUSO0_MUTUAL2_KEY41,
#endif
#if ( MUTUAL2_NUM > 42 )
    CTSUSO0_MUTUAL2_KEY42,
#endif
#if ( MUTUAL2_NUM > 43 )
    CTSUSO0_MUTUAL2_KEY43,
#endif
#if ( MUTUAL2_NUM > 44 )
    CTSUSO0_MUTUAL2_KEY44,
#endif
#if ( MUTUAL2_NUM > 45 )
    CTSUSO0_MUTUAL2_KEY45,
#endif
#if ( MUTUAL2_NUM > 46 )
    CTSUSO0_MUTUAL2_KEY46,
#endif
#if ( MUTUAL2_NUM > 47 )
    CTSUSO0_MUTUAL2_KEY47,
#endif
#if ( MUTUAL2_NUM > 48 )
    CTSUSO0_MUTUAL2_KEY48,
#endif
#if ( MUTUAL2_NUM > 49 )
    CTSUSO0_MUTUAL2_KEY49,
#endif
#if ( MUTUAL2_NUM > 50 )
    CTSUSO0_MUTUAL2_KEY50,
#endif
#if ( MUTUAL2_NUM > 51 )
    CTSUSO0_MUTUAL2_KEY51,
#endif
#if ( MUTUAL2_NUM > 52 )
    CTSUSO0_MUTUAL2_KEY52,
#endif
#if ( MUTUAL2_NUM > 53 )
    CTSUSO0_MUTUAL2_KEY53,
#endif
#if ( MUTUAL2_NUM > 54 )
    CTSUSO0_MUTUAL2_KEY54,
#endif
#if ( MUTUAL2_NUM > 55 )
    CTSUSO0_MUTUAL2_KEY55,
#endif
#if ( MUTUAL2_NUM > 56 )
    CTSUSO0_MUTUAL2_KEY56,
#endif
#if ( MUTUAL2_NUM > 57 )
    CTSUSO0_MUTUAL2_KEY57,
#endif
#if ( MUTUAL2_NUM > 58 )
    CTSUSO0_MUTUAL2_KEY58,
#endif
#if ( MUTUAL2_NUM > 59 )
    CTSUSO0_MUTUAL2_KEY59,
#endif
#if ( MUTUAL2_NUM > 60 )
    CTSUSO0_MUTUAL2_KEY60,
#endif
#if ( MUTUAL2_NUM > 61 )
    CTSUSO0_MUTUAL2_KEY61,
#endif
#if ( MUTUAL2_NUM > 62 )
    CTSUSO0_MUTUAL2_KEY62,
#endif
#if ( MUTUAL2_NUM > 63 )
    CTSUSO0_MUTUAL2_KEY63,
#endif
};

const uint16_t g_mutual2_ctsuso1[] =
{
#if ( MUTUAL2_NUM > 0 )
    CTSUSO1_MUTUAL2_KEY00,
#endif
#if ( MUTUAL2_NUM > 1 )
    CTSUSO1_MUTUAL2_KEY01,
#endif
#if ( MUTUAL2_NUM > 2 )
    CTSUSO1_MUTUAL2_KEY02,
#endif
#if ( MUTUAL2_NUM > 3 )
    CTSUSO1_MUTUAL2_KEY03,
#endif
#if ( MUTUAL2_NUM > 4 )
    CTSUSO1_MUTUAL2_KEY04,
#endif
#if ( MUTUAL2_NUM > 5 )
    CTSUSO1_MUTUAL2_KEY05,
#endif
#if ( MUTUAL2_NUM > 6 )
    CTSUSO1_MUTUAL2_KEY06,
#endif
#if ( MUTUAL2_NUM > 7 )
    CTSUSO1_MUTUAL2_KEY07,
#endif
#if ( MUTUAL2_NUM > 8 )
    CTSUSO1_MUTUAL2_KEY08,
#endif
#if ( MUTUAL2_NUM > 9 )
    CTSUSO1_MUTUAL2_KEY09,
#endif
#if ( MUTUAL2_NUM > 10 )
    CTSUSO1_MUTUAL2_KEY10,
#endif
#if ( MUTUAL2_NUM > 11 )
    CTSUSO1_MUTUAL2_KEY11,
#endif
#if ( MUTUAL2_NUM > 12 )
    CTSUSO1_MUTUAL2_KEY12,
#endif
#if ( MUTUAL2_NUM > 13 )
    CTSUSO1_MUTUAL2_KEY13,
#endif
#if ( MUTUAL2_NUM > 14 )
    CTSUSO1_MUTUAL2_KEY14,
#endif
#if ( MUTUAL2_NUM > 15 )
    CTSUSO1_MUTUAL2_KEY15,
#endif
#if ( MUTUAL2_NUM > 16 )
    CTSUSO1_MUTUAL2_KEY16,
#endif
#if ( MUTUAL2_NUM > 17 )
    CTSUSO1_MUTUAL2_KEY17,
#endif
#if ( MUTUAL2_NUM > 18 )
    CTSUSO1_MUTUAL2_KEY18,
#endif
#if ( MUTUAL2_NUM > 19 )
    CTSUSO1_MUTUAL2_KEY19,
#endif
#if ( MUTUAL2_NUM > 20 )
    CTSUSO1_MUTUAL2_KEY20,
#endif
#if ( MUTUAL2_NUM > 21 )
    CTSUSO1_MUTUAL2_KEY21,
#endif
#if ( MUTUAL2_NUM > 22 )
    CTSUSO1_MUTUAL2_KEY22,
#endif
#if ( MUTUAL2_NUM > 23 )
    CTSUSO1_MUTUAL2_KEY23,
#endif
#if ( MUTUAL2_NUM > 24 )
    CTSUSO1_MUTUAL2_KEY24,
#endif
#if ( MUTUAL2_NUM > 25 )
    CTSUSO1_MUTUAL2_KEY25,
#endif
#if ( MUTUAL2_NUM > 26 )
    CTSUSO1_MUTUAL2_KEY26,
#endif
#if ( MUTUAL2_NUM > 27 )
    CTSUSO1_MUTUAL2_KEY27,
#endif
#if ( MUTUAL2_NUM > 28 )
    CTSUSO1_MUTUAL2_KEY28,
#endif
#if ( MUTUAL2_NUM > 29 )
    CTSUSO1_MUTUAL2_KEY29,
#endif
#if ( MUTUAL2_NUM > 30 )
    CTSUSO1_MUTUAL2_KEY30,
#endif
#if ( MUTUAL2_NUM > 31 )
    CTSUSO1_MUTUAL2_KEY31,
#endif
#if ( MUTUAL2_NUM > 32 )
    CTSUSO1_MUTUAL2_KEY32,
#endif
#if ( MUTUAL2_NUM > 33 )
    CTSUSO1_MUTUAL2_KEY33,
#endif
#if ( MUTUAL2_NUM > 34 )
    CTSUSO1_MUTUAL2_KEY34,
#endif
#if ( MUTUAL2_NUM > 35 )
    CTSUSO1_MUTUAL2_KEY35,
#endif
#if ( MUTUAL2_NUM > 36 )
    CTSUSO1_MUTUAL2_KEY36,
#endif
#if ( MUTUAL2_NUM > 37 )
    CTSUSO1_MUTUAL2_KEY37,
#endif
#if ( MUTUAL2_NUM > 38 )
    CTSUSO1_MUTUAL2_KEY38,
#endif
#if ( MUTUAL2_NUM > 39 )
    CTSUSO1_MUTUAL2_KEY39,
#endif
#if ( MUTUAL2_NUM > 40 )
    CTSUSO1_MUTUAL2_KEY40,
#endif
#if ( MUTUAL2_NUM > 41 )
    CTSUSO1_MUTUAL2_KEY41,
#endif
#if ( MUTUAL2_NUM > 42 )
    CTSUSO1_MUTUAL2_KEY42,
#endif
#if ( MUTUAL2_NUM > 43 )
    CTSUSO1_MUTUAL2_KEY43,
#endif
#if ( MUTUAL2_NUM > 44 )
    CTSUSO1_MUTUAL2_KEY44,
#endif
#if ( MUTUAL2_NUM > 45 )
    CTSUSO1_MUTUAL2_KEY45,
#endif
#if ( MUTUAL2_NUM > 46 )
    CTSUSO1_MUTUAL2_KEY46,
#endif
#if ( MUTUAL2_NUM > 47 )
    CTSUSO1_MUTUAL2_KEY47,
#endif
#if ( MUTUAL2_NUM > 48 )
    CTSUSO1_MUTUAL2_KEY48,
#endif
#if ( MUTUAL2_NUM > 49 )
    CTSUSO1_MUTUAL2_KEY49,
#endif
#if ( MUTUAL2_NUM > 50 )
    CTSUSO1_MUTUAL2_KEY50,
#endif
#if ( MUTUAL2_NUM > 51 )
    CTSUSO1_MUTUAL2_KEY51,
#endif
#if ( MUTUAL2_NUM > 52 )
    CTSUSO1_MUTUAL2_KEY52,
#endif
#if ( MUTUAL2_NUM > 53 )
    CTSUSO1_MUTUAL2_KEY53,
#endif
#if ( MUTUAL2_NUM > 54 )
    CTSUSO1_MUTUAL2_KEY54,
#endif
#if ( MUTUAL2_NUM > 55 )
    CTSUSO1_MUTUAL2_KEY55,
#endif
#if ( MUTUAL2_NUM > 56 )
    CTSUSO1_MUTUAL2_KEY56,
#endif
#if ( MUTUAL2_NUM > 57 )
    CTSUSO1_MUTUAL2_KEY57,
#endif
#if ( MUTUAL2_NUM > 58 )
    CTSUSO1_MUTUAL2_KEY58,
#endif
#if ( MUTUAL2_NUM > 59 )
    CTSUSO1_MUTUAL2_KEY59,
#endif
#if ( MUTUAL2_NUM > 60 )
    CTSUSO1_MUTUAL2_KEY60,
#endif
#if ( MUTUAL2_NUM > 61 )
    CTSUSO1_MUTUAL2_KEY61,
#endif
#if ( MUTUAL2_NUM > 62 )
    CTSUSO1_MUTUAL2_KEY62,
#endif
#if ( MUTUAL2_NUM > 63 )
    CTSUSO1_MUTUAL2_KEY63,
#endif
};
#endif    // ( MUTUAL_METHOD_NUM > 2 )

/*=====    Mutual 3    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 3 )
const uint16_t g_mutual3_ctsussc[] =
{
#if ( MUTUAL3_NUM > 0 )
    CTSUSSC_MUTUAL3_KEY00,
#endif
#if ( MUTUAL3_NUM > 1 )
    CTSUSSC_MUTUAL3_KEY01,
#endif
#if ( MUTUAL3_NUM > 2 )
    CTSUSSC_MUTUAL3_KEY02,
#endif
#if ( MUTUAL3_NUM > 3 )
    CTSUSSC_MUTUAL3_KEY03,
#endif
#if ( MUTUAL3_NUM > 4 )
    CTSUSSC_MUTUAL3_KEY04,
#endif
#if ( MUTUAL3_NUM > 5 )
    CTSUSSC_MUTUAL3_KEY05,
#endif
#if ( MUTUAL3_NUM > 6 )
    CTSUSSC_MUTUAL3_KEY06,
#endif
#if ( MUTUAL3_NUM > 7 )
    CTSUSSC_MUTUAL3_KEY07,
#endif
#if ( MUTUAL3_NUM > 8 )
    CTSUSSC_MUTUAL3_KEY08,
#endif
#if ( MUTUAL3_NUM > 9 )
    CTSUSSC_MUTUAL3_KEY09,
#endif
#if ( MUTUAL3_NUM > 10 )
    CTSUSSC_MUTUAL3_KEY10,
#endif
#if ( MUTUAL3_NUM > 11 )
    CTSUSSC_MUTUAL3_KEY11,
#endif
#if ( MUTUAL3_NUM > 12 )
    CTSUSSC_MUTUAL3_KEY12,
#endif
#if ( MUTUAL3_NUM > 13 )
    CTSUSSC_MUTUAL3_KEY13,
#endif
#if ( MUTUAL3_NUM > 14 )
    CTSUSSC_MUTUAL3_KEY14,
#endif
#if ( MUTUAL3_NUM > 15 )
    CTSUSSC_MUTUAL3_KEY15,
#endif
#if ( MUTUAL3_NUM > 16 )
    CTSUSSC_MUTUAL3_KEY16,
#endif
#if ( MUTUAL3_NUM > 17 )
    CTSUSSC_MUTUAL3_KEY17,
#endif
#if ( MUTUAL3_NUM > 18 )
    CTSUSSC_MUTUAL3_KEY18,
#endif
#if ( MUTUAL3_NUM > 19 )
    CTSUSSC_MUTUAL3_KEY19,
#endif
#if ( MUTUAL3_NUM > 20 )
    CTSUSSC_MUTUAL3_KEY20,
#endif
#if ( MUTUAL3_NUM > 21 )
    CTSUSSC_MUTUAL3_KEY21,
#endif
#if ( MUTUAL3_NUM > 22 )
    CTSUSSC_MUTUAL3_KEY22,
#endif
#if ( MUTUAL3_NUM > 23 )
    CTSUSSC_MUTUAL3_KEY23,
#endif
#if ( MUTUAL3_NUM > 24 )
    CTSUSSC_MUTUAL3_KEY24,
#endif
#if ( MUTUAL3_NUM > 25 )
    CTSUSSC_MUTUAL3_KEY25,
#endif
#if ( MUTUAL3_NUM > 26 )
    CTSUSSC_MUTUAL3_KEY26,
#endif
#if ( MUTUAL3_NUM > 27 )
    CTSUSSC_MUTUAL3_KEY27,
#endif
#if ( MUTUAL3_NUM > 28 )
    CTSUSSC_MUTUAL3_KEY28,
#endif
#if ( MUTUAL3_NUM > 29 )
    CTSUSSC_MUTUAL3_KEY29,
#endif
#if ( MUTUAL3_NUM > 30 )
    CTSUSSC_MUTUAL3_KEY30,
#endif
#if ( MUTUAL3_NUM > 31 )
    CTSUSSC_MUTUAL3_KEY31,
#endif
#if ( MUTUAL3_NUM > 32 )
    CTSUSSC_MUTUAL3_KEY32,
#endif
#if ( MUTUAL3_NUM > 33 )
    CTSUSSC_MUTUAL3_KEY33,
#endif
#if ( MUTUAL3_NUM > 34 )
    CTSUSSC_MUTUAL3_KEY34,
#endif
#if ( MUTUAL3_NUM > 35 )
    CTSUSSC_MUTUAL3_KEY35,
#endif
#if ( MUTUAL3_NUM > 36 )
    CTSUSSC_MUTUAL3_KEY36,
#endif
#if ( MUTUAL3_NUM > 37 )
    CTSUSSC_MUTUAL3_KEY37,
#endif
#if ( MUTUAL3_NUM > 38 )
    CTSUSSC_MUTUAL3_KEY38,
#endif
#if ( MUTUAL3_NUM > 39 )
    CTSUSSC_MUTUAL3_KEY39,
#endif
#if ( MUTUAL3_NUM > 40 )
    CTSUSSC_MUTUAL3_KEY40,
#endif
#if ( MUTUAL3_NUM > 41 )
    CTSUSSC_MUTUAL3_KEY41,
#endif
#if ( MUTUAL3_NUM > 42 )
    CTSUSSC_MUTUAL3_KEY42,
#endif
#if ( MUTUAL3_NUM > 43 )
    CTSUSSC_MUTUAL3_KEY43,
#endif
#if ( MUTUAL3_NUM > 44 )
    CTSUSSC_MUTUAL3_KEY44,
#endif
#if ( MUTUAL3_NUM > 45 )
    CTSUSSC_MUTUAL3_KEY45,
#endif
#if ( MUTUAL3_NUM > 46 )
    CTSUSSC_MUTUAL3_KEY46,
#endif
#if ( MUTUAL3_NUM > 47 )
    CTSUSSC_MUTUAL3_KEY47,
#endif
#if ( MUTUAL3_NUM > 48 )
    CTSUSSC_MUTUAL3_KEY48,
#endif
#if ( MUTUAL3_NUM > 49 )
    CTSUSSC_MUTUAL3_KEY49,
#endif
#if ( MUTUAL3_NUM > 50 )
    CTSUSSC_MUTUAL3_KEY50,
#endif
#if ( MUTUAL3_NUM > 51 )
    CTSUSSC_MUTUAL3_KEY51,
#endif
#if ( MUTUAL3_NUM > 52 )
    CTSUSSC_MUTUAL3_KEY52,
#endif
#if ( MUTUAL3_NUM > 53 )
    CTSUSSC_MUTUAL3_KEY53,
#endif
#if ( MUTUAL3_NUM > 54 )
    CTSUSSC_MUTUAL3_KEY54,
#endif
#if ( MUTUAL3_NUM > 55 )
    CTSUSSC_MUTUAL3_KEY55,
#endif
#if ( MUTUAL3_NUM > 56 )
    CTSUSSC_MUTUAL3_KEY56,
#endif
#if ( MUTUAL3_NUM > 57 )
    CTSUSSC_MUTUAL3_KEY57,
#endif
#if ( MUTUAL3_NUM > 58 )
    CTSUSSC_MUTUAL3_KEY58,
#endif
#if ( MUTUAL3_NUM > 59 )
    CTSUSSC_MUTUAL3_KEY59,
#endif
#if ( MUTUAL3_NUM > 60 )
    CTSUSSC_MUTUAL3_KEY60,
#endif
#if ( MUTUAL3_NUM > 61 )
    CTSUSSC_MUTUAL3_KEY61,
#endif
#if ( MUTUAL3_NUM > 62 )
    CTSUSSC_MUTUAL3_KEY62,
#endif
#if ( MUTUAL3_NUM > 63 )
    CTSUSSC_MUTUAL3_KEY63,
#endif
};

const uint16_t g_mutual3_ctsuso0[] =
{
#if ( MUTUAL3_NUM > 0 )
    CTSUSO0_MUTUAL3_KEY00,
#endif
#if ( MUTUAL3_NUM > 1 )
    CTSUSO0_MUTUAL3_KEY01,
#endif
#if ( MUTUAL3_NUM > 2 )
    CTSUSO0_MUTUAL3_KEY02,
#endif
#if ( MUTUAL3_NUM > 3 )
    CTSUSO0_MUTUAL3_KEY03,
#endif
#if ( MUTUAL3_NUM > 4 )
    CTSUSO0_MUTUAL3_KEY04,
#endif
#if ( MUTUAL3_NUM > 5 )
    CTSUSO0_MUTUAL3_KEY05,
#endif
#if ( MUTUAL3_NUM > 6 )
    CTSUSO0_MUTUAL3_KEY06,
#endif
#if ( MUTUAL3_NUM > 7 )
    CTSUSO0_MUTUAL3_KEY07,
#endif
#if ( MUTUAL3_NUM > 8 )
    CTSUSO0_MUTUAL3_KEY08,
#endif
#if ( MUTUAL3_NUM > 9 )
    CTSUSO0_MUTUAL3_KEY09,
#endif
#if ( MUTUAL3_NUM > 10 )
    CTSUSO0_MUTUAL3_KEY10,
#endif
#if ( MUTUAL3_NUM > 11 )
    CTSUSO0_MUTUAL3_KEY11,
#endif
#if ( MUTUAL3_NUM > 12 )
    CTSUSO0_MUTUAL3_KEY12,
#endif
#if ( MUTUAL3_NUM > 13 )
    CTSUSO0_MUTUAL3_KEY13,
#endif
#if ( MUTUAL3_NUM > 14 )
    CTSUSO0_MUTUAL3_KEY14,
#endif
#if ( MUTUAL3_NUM > 15 )
    CTSUSO0_MUTUAL3_KEY15,
#endif
#if ( MUTUAL3_NUM > 16 )
    CTSUSO0_MUTUAL3_KEY16,
#endif
#if ( MUTUAL3_NUM > 17 )
    CTSUSO0_MUTUAL3_KEY17,
#endif
#if ( MUTUAL3_NUM > 18 )
    CTSUSO0_MUTUAL3_KEY18,
#endif
#if ( MUTUAL3_NUM > 19 )
    CTSUSO0_MUTUAL3_KEY19,
#endif
#if ( MUTUAL3_NUM > 20 )
    CTSUSO0_MUTUAL3_KEY20,
#endif
#if ( MUTUAL3_NUM > 21 )
    CTSUSO0_MUTUAL3_KEY21,
#endif
#if ( MUTUAL3_NUM > 22 )
    CTSUSO0_MUTUAL3_KEY22,
#endif
#if ( MUTUAL3_NUM > 23 )
    CTSUSO0_MUTUAL3_KEY23,
#endif
#if ( MUTUAL3_NUM > 24 )
    CTSUSO0_MUTUAL3_KEY24,
#endif
#if ( MUTUAL3_NUM > 25 )
    CTSUSO0_MUTUAL3_KEY25,
#endif
#if ( MUTUAL3_NUM > 26 )
    CTSUSO0_MUTUAL3_KEY26,
#endif
#if ( MUTUAL3_NUM > 27 )
    CTSUSO0_MUTUAL3_KEY27,
#endif
#if ( MUTUAL3_NUM > 28 )
    CTSUSO0_MUTUAL3_KEY28,
#endif
#if ( MUTUAL3_NUM > 29 )
    CTSUSO0_MUTUAL3_KEY29,
#endif
#if ( MUTUAL3_NUM > 30 )
    CTSUSO0_MUTUAL3_KEY30,
#endif
#if ( MUTUAL3_NUM > 31 )
    CTSUSO0_MUTUAL3_KEY31,
#endif
#if ( MUTUAL3_NUM > 32 )
    CTSUSO0_MUTUAL3_KEY32,
#endif
#if ( MUTUAL3_NUM > 33 )
    CTSUSO0_MUTUAL3_KEY33,
#endif
#if ( MUTUAL3_NUM > 34 )
    CTSUSO0_MUTUAL3_KEY34,
#endif
#if ( MUTUAL3_NUM > 35 )
    CTSUSO0_MUTUAL3_KEY35,
#endif
#if ( MUTUAL3_NUM > 36 )
    CTSUSO0_MUTUAL3_KEY36,
#endif
#if ( MUTUAL3_NUM > 37 )
    CTSUSO0_MUTUAL3_KEY37,
#endif
#if ( MUTUAL3_NUM > 38 )
    CTSUSO0_MUTUAL3_KEY38,
#endif
#if ( MUTUAL3_NUM > 39 )
    CTSUSO0_MUTUAL3_KEY39,
#endif
#if ( MUTUAL3_NUM > 40 )
    CTSUSO0_MUTUAL3_KEY40,
#endif
#if ( MUTUAL3_NUM > 41 )
    CTSUSO0_MUTUAL3_KEY41,
#endif
#if ( MUTUAL3_NUM > 42 )
    CTSUSO0_MUTUAL3_KEY42,
#endif
#if ( MUTUAL3_NUM > 43 )
    CTSUSO0_MUTUAL3_KEY43,
#endif
#if ( MUTUAL3_NUM > 44 )
    CTSUSO0_MUTUAL3_KEY44,
#endif
#if ( MUTUAL3_NUM > 45 )
    CTSUSO0_MUTUAL3_KEY45,
#endif
#if ( MUTUAL3_NUM > 46 )
    CTSUSO0_MUTUAL3_KEY46,
#endif
#if ( MUTUAL3_NUM > 47 )
    CTSUSO0_MUTUAL3_KEY47,
#endif
#if ( MUTUAL3_NUM > 48 )
    CTSUSO0_MUTUAL3_KEY48,
#endif
#if ( MUTUAL3_NUM > 49 )
    CTSUSO0_MUTUAL3_KEY49,
#endif
#if ( MUTUAL3_NUM > 50 )
    CTSUSO0_MUTUAL3_KEY50,
#endif
#if ( MUTUAL3_NUM > 51 )
    CTSUSO0_MUTUAL3_KEY51,
#endif
#if ( MUTUAL3_NUM > 52 )
    CTSUSO0_MUTUAL3_KEY52,
#endif
#if ( MUTUAL3_NUM > 53 )
    CTSUSO0_MUTUAL3_KEY53,
#endif
#if ( MUTUAL3_NUM > 54 )
    CTSUSO0_MUTUAL3_KEY54,
#endif
#if ( MUTUAL3_NUM > 55 )
    CTSUSO0_MUTUAL3_KEY55,
#endif
#if ( MUTUAL3_NUM > 56 )
    CTSUSO0_MUTUAL3_KEY56,
#endif
#if ( MUTUAL3_NUM > 57 )
    CTSUSO0_MUTUAL3_KEY57,
#endif
#if ( MUTUAL3_NUM > 58 )
    CTSUSO0_MUTUAL3_KEY58,
#endif
#if ( MUTUAL3_NUM > 59 )
    CTSUSO0_MUTUAL3_KEY59,
#endif
#if ( MUTUAL3_NUM > 60 )
    CTSUSO0_MUTUAL3_KEY60,
#endif
#if ( MUTUAL3_NUM > 61 )
    CTSUSO0_MUTUAL3_KEY61,
#endif
#if ( MUTUAL3_NUM > 62 )
    CTSUSO0_MUTUAL3_KEY62,
#endif
#if ( MUTUAL3_NUM > 63 )
    CTSUSO0_MUTUAL3_KEY63,
#endif
};

const uint16_t g_mutual3_ctsuso1[] =
{
#if ( MUTUAL3_NUM > 0 )
    CTSUSO1_MUTUAL3_KEY00,
#endif
#if ( MUTUAL3_NUM > 1 )
    CTSUSO1_MUTUAL3_KEY01,
#endif
#if ( MUTUAL3_NUM > 2 )
    CTSUSO1_MUTUAL3_KEY02,
#endif
#if ( MUTUAL3_NUM > 3 )
    CTSUSO1_MUTUAL3_KEY03,
#endif
#if ( MUTUAL3_NUM > 4 )
    CTSUSO1_MUTUAL3_KEY04,
#endif
#if ( MUTUAL3_NUM > 5 )
    CTSUSO1_MUTUAL3_KEY05,
#endif
#if ( MUTUAL3_NUM > 6 )
    CTSUSO1_MUTUAL3_KEY06,
#endif
#if ( MUTUAL3_NUM > 7 )
    CTSUSO1_MUTUAL3_KEY07,
#endif
#if ( MUTUAL3_NUM > 8 )
    CTSUSO1_MUTUAL3_KEY08,
#endif
#if ( MUTUAL3_NUM > 9 )
    CTSUSO1_MUTUAL3_KEY09,
#endif
#if ( MUTUAL3_NUM > 10 )
    CTSUSO1_MUTUAL3_KEY10,
#endif
#if ( MUTUAL3_NUM > 11 )
    CTSUSO1_MUTUAL3_KEY11,
#endif
#if ( MUTUAL3_NUM > 12 )
    CTSUSO1_MUTUAL3_KEY12,
#endif
#if ( MUTUAL3_NUM > 13 )
    CTSUSO1_MUTUAL3_KEY13,
#endif
#if ( MUTUAL3_NUM > 14 )
    CTSUSO1_MUTUAL3_KEY14,
#endif
#if ( MUTUAL3_NUM > 15 )
    CTSUSO1_MUTUAL3_KEY15,
#endif
#if ( MUTUAL3_NUM > 16 )
    CTSUSO1_MUTUAL3_KEY16,
#endif
#if ( MUTUAL3_NUM > 17 )
    CTSUSO1_MUTUAL3_KEY17,
#endif
#if ( MUTUAL3_NUM > 18 )
    CTSUSO1_MUTUAL3_KEY18,
#endif
#if ( MUTUAL3_NUM > 19 )
    CTSUSO1_MUTUAL3_KEY19,
#endif
#if ( MUTUAL3_NUM > 20 )
    CTSUSO1_MUTUAL3_KEY20,
#endif
#if ( MUTUAL3_NUM > 21 )
    CTSUSO1_MUTUAL3_KEY21,
#endif
#if ( MUTUAL3_NUM > 22 )
    CTSUSO1_MUTUAL3_KEY22,
#endif
#if ( MUTUAL3_NUM > 23 )
    CTSUSO1_MUTUAL3_KEY23,
#endif
#if ( MUTUAL3_NUM > 24 )
    CTSUSO1_MUTUAL3_KEY24,
#endif
#if ( MUTUAL3_NUM > 25 )
    CTSUSO1_MUTUAL3_KEY25,
#endif
#if ( MUTUAL3_NUM > 26 )
    CTSUSO1_MUTUAL3_KEY26,
#endif
#if ( MUTUAL3_NUM > 27 )
    CTSUSO1_MUTUAL3_KEY27,
#endif
#if ( MUTUAL3_NUM > 28 )
    CTSUSO1_MUTUAL3_KEY28,
#endif
#if ( MUTUAL3_NUM > 29 )
    CTSUSO1_MUTUAL3_KEY29,
#endif
#if ( MUTUAL3_NUM > 30 )
    CTSUSO1_MUTUAL3_KEY30,
#endif
#if ( MUTUAL3_NUM > 31 )
    CTSUSO1_MUTUAL3_KEY31,
#endif
#if ( MUTUAL3_NUM > 32 )
    CTSUSO1_MUTUAL3_KEY32,
#endif
#if ( MUTUAL3_NUM > 33 )
    CTSUSO1_MUTUAL3_KEY33,
#endif
#if ( MUTUAL3_NUM > 34 )
    CTSUSO1_MUTUAL3_KEY34,
#endif
#if ( MUTUAL3_NUM > 35 )
    CTSUSO1_MUTUAL3_KEY35,
#endif
#if ( MUTUAL3_NUM > 36 )
    CTSUSO1_MUTUAL3_KEY36,
#endif
#if ( MUTUAL3_NUM > 37 )
    CTSUSO1_MUTUAL3_KEY37,
#endif
#if ( MUTUAL3_NUM > 38 )
    CTSUSO1_MUTUAL3_KEY38,
#endif
#if ( MUTUAL3_NUM > 39 )
    CTSUSO1_MUTUAL3_KEY39,
#endif
#if ( MUTUAL3_NUM > 40 )
    CTSUSO1_MUTUAL3_KEY40,
#endif
#if ( MUTUAL3_NUM > 41 )
    CTSUSO1_MUTUAL3_KEY41,
#endif
#if ( MUTUAL3_NUM > 42 )
    CTSUSO1_MUTUAL3_KEY42,
#endif
#if ( MUTUAL3_NUM > 43 )
    CTSUSO1_MUTUAL3_KEY43,
#endif
#if ( MUTUAL3_NUM > 44 )
    CTSUSO1_MUTUAL3_KEY44,
#endif
#if ( MUTUAL3_NUM > 45 )
    CTSUSO1_MUTUAL3_KEY45,
#endif
#if ( MUTUAL3_NUM > 46 )
    CTSUSO1_MUTUAL3_KEY46,
#endif
#if ( MUTUAL3_NUM > 47 )
    CTSUSO1_MUTUAL3_KEY47,
#endif
#if ( MUTUAL3_NUM > 48 )
    CTSUSO1_MUTUAL3_KEY48,
#endif
#if ( MUTUAL3_NUM > 49 )
    CTSUSO1_MUTUAL3_KEY49,
#endif
#if ( MUTUAL3_NUM > 50 )
    CTSUSO1_MUTUAL3_KEY50,
#endif
#if ( MUTUAL3_NUM > 51 )
    CTSUSO1_MUTUAL3_KEY51,
#endif
#if ( MUTUAL3_NUM > 52 )
    CTSUSO1_MUTUAL3_KEY52,
#endif
#if ( MUTUAL3_NUM > 53 )
    CTSUSO1_MUTUAL3_KEY53,
#endif
#if ( MUTUAL3_NUM > 54 )
    CTSUSO1_MUTUAL3_KEY54,
#endif
#if ( MUTUAL3_NUM > 55 )
    CTSUSO1_MUTUAL3_KEY55,
#endif
#if ( MUTUAL3_NUM > 56 )
    CTSUSO1_MUTUAL3_KEY56,
#endif
#if ( MUTUAL3_NUM > 57 )
    CTSUSO1_MUTUAL3_KEY57,
#endif
#if ( MUTUAL3_NUM > 58 )
    CTSUSO1_MUTUAL3_KEY58,
#endif
#if ( MUTUAL3_NUM > 59 )
    CTSUSO1_MUTUAL3_KEY59,
#endif
#if ( MUTUAL3_NUM > 60 )
    CTSUSO1_MUTUAL3_KEY60,
#endif
#if ( MUTUAL3_NUM > 61 )
    CTSUSO1_MUTUAL3_KEY61,
#endif
#if ( MUTUAL3_NUM > 62 )
    CTSUSO1_MUTUAL3_KEY62,
#endif
#if ( MUTUAL3_NUM > 63 )
    CTSUSO1_MUTUAL3_KEY63,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 3 )

/*=====    Mutual 4    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 4 )
const uint16_t g_mutual4_ctsussc[] =
{
#if ( MUTUAL4_NUM > 0 )
    CTSUSSC_MUTUAL4_KEY00,
#endif
#if ( MUTUAL4_NUM > 1 )
    CTSUSSC_MUTUAL4_KEY01,
#endif
#if ( MUTUAL4_NUM > 2 )
    CTSUSSC_MUTUAL4_KEY02,
#endif
#if ( MUTUAL4_NUM > 3 )
    CTSUSSC_MUTUAL4_KEY03,
#endif
#if ( MUTUAL4_NUM > 4 )
    CTSUSSC_MUTUAL4_KEY04,
#endif
#if ( MUTUAL4_NUM > 5 )
    CTSUSSC_MUTUAL4_KEY05,
#endif
#if ( MUTUAL4_NUM > 6 )
    CTSUSSC_MUTUAL4_KEY06,
#endif
#if ( MUTUAL4_NUM > 7 )
    CTSUSSC_MUTUAL4_KEY07,
#endif
#if ( MUTUAL4_NUM > 8 )
    CTSUSSC_MUTUAL4_KEY08,
#endif
#if ( MUTUAL4_NUM > 9 )
    CTSUSSC_MUTUAL4_KEY09,
#endif
#if ( MUTUAL4_NUM > 10 )
    CTSUSSC_MUTUAL4_KEY10,
#endif
#if ( MUTUAL4_NUM > 11 )
    CTSUSSC_MUTUAL4_KEY11,
#endif
#if ( MUTUAL4_NUM > 12 )
    CTSUSSC_MUTUAL4_KEY12,
#endif
#if ( MUTUAL4_NUM > 13 )
    CTSUSSC_MUTUAL4_KEY13,
#endif
#if ( MUTUAL4_NUM > 14 )
    CTSUSSC_MUTUAL4_KEY14,
#endif
#if ( MUTUAL4_NUM > 15 )
    CTSUSSC_MUTUAL4_KEY15,
#endif
#if ( MUTUAL4_NUM > 16 )
    CTSUSSC_MUTUAL4_KEY16,
#endif
#if ( MUTUAL4_NUM > 17 )
    CTSUSSC_MUTUAL4_KEY17,
#endif
#if ( MUTUAL4_NUM > 18 )
    CTSUSSC_MUTUAL4_KEY18,
#endif
#if ( MUTUAL4_NUM > 19 )
    CTSUSSC_MUTUAL4_KEY19,
#endif
#if ( MUTUAL4_NUM > 20 )
    CTSUSSC_MUTUAL4_KEY20,
#endif
#if ( MUTUAL4_NUM > 21 )
    CTSUSSC_MUTUAL4_KEY21,
#endif
#if ( MUTUAL4_NUM > 22 )
    CTSUSSC_MUTUAL4_KEY22,
#endif
#if ( MUTUAL4_NUM > 23 )
    CTSUSSC_MUTUAL4_KEY23,
#endif
#if ( MUTUAL4_NUM > 24 )
    CTSUSSC_MUTUAL4_KEY24,
#endif
#if ( MUTUAL4_NUM > 25 )
    CTSUSSC_MUTUAL4_KEY25,
#endif
#if ( MUTUAL4_NUM > 26 )
    CTSUSSC_MUTUAL4_KEY26,
#endif
#if ( MUTUAL4_NUM > 27 )
    CTSUSSC_MUTUAL4_KEY27,
#endif
#if ( MUTUAL4_NUM > 28 )
    CTSUSSC_MUTUAL4_KEY28,
#endif
#if ( MUTUAL4_NUM > 29 )
    CTSUSSC_MUTUAL4_KEY29,
#endif
#if ( MUTUAL4_NUM > 30 )
    CTSUSSC_MUTUAL4_KEY30,
#endif
#if ( MUTUAL4_NUM > 31 )
    CTSUSSC_MUTUAL4_KEY31,
#endif
#if ( MUTUAL4_NUM > 32 )
    CTSUSSC_MUTUAL4_KEY32,
#endif
#if ( MUTUAL4_NUM > 33 )
    CTSUSSC_MUTUAL4_KEY33,
#endif
#if ( MUTUAL4_NUM > 34 )
    CTSUSSC_MUTUAL4_KEY34,
#endif
#if ( MUTUAL4_NUM > 35 )
    CTSUSSC_MUTUAL4_KEY35,
#endif
#if ( MUTUAL4_NUM > 36 )
    CTSUSSC_MUTUAL4_KEY36,
#endif
#if ( MUTUAL4_NUM > 37 )
    CTSUSSC_MUTUAL4_KEY37,
#endif
#if ( MUTUAL4_NUM > 38 )
    CTSUSSC_MUTUAL4_KEY38,
#endif
#if ( MUTUAL4_NUM > 39 )
    CTSUSSC_MUTUAL4_KEY39,
#endif
#if ( MUTUAL4_NUM > 40 )
    CTSUSSC_MUTUAL4_KEY40,
#endif
#if ( MUTUAL4_NUM > 41 )
    CTSUSSC_MUTUAL4_KEY41,
#endif
#if ( MUTUAL4_NUM > 42 )
    CTSUSSC_MUTUAL4_KEY42,
#endif
#if ( MUTUAL4_NUM > 43 )
    CTSUSSC_MUTUAL4_KEY43,
#endif
#if ( MUTUAL4_NUM > 44 )
    CTSUSSC_MUTUAL4_KEY44,
#endif
#if ( MUTUAL4_NUM > 45 )
    CTSUSSC_MUTUAL4_KEY45,
#endif
#if ( MUTUAL4_NUM > 46 )
    CTSUSSC_MUTUAL4_KEY46,
#endif
#if ( MUTUAL4_NUM > 47 )
    CTSUSSC_MUTUAL4_KEY47,
#endif
#if ( MUTUAL4_NUM > 48 )
    CTSUSSC_MUTUAL4_KEY48,
#endif
#if ( MUTUAL4_NUM > 49 )
    CTSUSSC_MUTUAL4_KEY49,
#endif
#if ( MUTUAL4_NUM > 50 )
    CTSUSSC_MUTUAL4_KEY50,
#endif
#if ( MUTUAL4_NUM > 51 )
    CTSUSSC_MUTUAL4_KEY51,
#endif
#if ( MUTUAL4_NUM > 52 )
    CTSUSSC_MUTUAL4_KEY52,
#endif
#if ( MUTUAL4_NUM > 53 )
    CTSUSSC_MUTUAL4_KEY53,
#endif
#if ( MUTUAL4_NUM > 54 )
    CTSUSSC_MUTUAL4_KEY54,
#endif
#if ( MUTUAL4_NUM > 55 )
    CTSUSSC_MUTUAL4_KEY55,
#endif
#if ( MUTUAL4_NUM > 56 )
    CTSUSSC_MUTUAL4_KEY56,
#endif
#if ( MUTUAL4_NUM > 57 )
    CTSUSSC_MUTUAL4_KEY57,
#endif
#if ( MUTUAL4_NUM > 58 )
    CTSUSSC_MUTUAL4_KEY58,
#endif
#if ( MUTUAL4_NUM > 59 )
    CTSUSSC_MUTUAL4_KEY59,
#endif
#if ( MUTUAL4_NUM > 60 )
    CTSUSSC_MUTUAL4_KEY60,
#endif
#if ( MUTUAL4_NUM > 61 )
    CTSUSSC_MUTUAL4_KEY61,
#endif
#if ( MUTUAL4_NUM > 62 )
    CTSUSSC_MUTUAL4_KEY62,
#endif
#if ( MUTUAL4_NUM > 63 )
    CTSUSSC_MUTUAL4_KEY63,
#endif
};

const uint16_t g_mutual4_ctsuso0[] =
{
#if ( MUTUAL4_NUM > 0 )
    CTSUSO0_MUTUAL4_KEY00,
#endif
#if ( MUTUAL4_NUM > 1 )
    CTSUSO0_MUTUAL4_KEY01,
#endif
#if ( MUTUAL4_NUM > 2 )
    CTSUSO0_MUTUAL4_KEY02,
#endif
#if ( MUTUAL4_NUM > 3 )
    CTSUSO0_MUTUAL4_KEY03,
#endif
#if ( MUTUAL4_NUM > 4 )
    CTSUSO0_MUTUAL4_KEY04,
#endif
#if ( MUTUAL4_NUM > 5 )
    CTSUSO0_MUTUAL4_KEY05,
#endif
#if ( MUTUAL4_NUM > 6 )
    CTSUSO0_MUTUAL4_KEY06,
#endif
#if ( MUTUAL4_NUM > 7 )
    CTSUSO0_MUTUAL4_KEY07,
#endif
#if ( MUTUAL4_NUM > 8 )
    CTSUSO0_MUTUAL4_KEY08,
#endif
#if ( MUTUAL4_NUM > 9 )
    CTSUSO0_MUTUAL4_KEY09,
#endif
#if ( MUTUAL4_NUM > 10 )
    CTSUSO0_MUTUAL4_KEY10,
#endif
#if ( MUTUAL4_NUM > 11 )
    CTSUSO0_MUTUAL4_KEY11,
#endif
#if ( MUTUAL4_NUM > 12 )
    CTSUSO0_MUTUAL4_KEY12,
#endif
#if ( MUTUAL4_NUM > 13 )
    CTSUSO0_MUTUAL4_KEY13,
#endif
#if ( MUTUAL4_NUM > 14 )
    CTSUSO0_MUTUAL4_KEY14,
#endif
#if ( MUTUAL4_NUM > 15 )
    CTSUSO0_MUTUAL4_KEY15,
#endif
#if ( MUTUAL4_NUM > 16 )
    CTSUSO0_MUTUAL4_KEY16,
#endif
#if ( MUTUAL4_NUM > 17 )
    CTSUSO0_MUTUAL4_KEY17,
#endif
#if ( MUTUAL4_NUM > 18 )
    CTSUSO0_MUTUAL4_KEY18,
#endif
#if ( MUTUAL4_NUM > 19 )
    CTSUSO0_MUTUAL4_KEY19,
#endif
#if ( MUTUAL4_NUM > 20 )
    CTSUSO0_MUTUAL4_KEY20,
#endif
#if ( MUTUAL4_NUM > 21 )
    CTSUSO0_MUTUAL4_KEY21,
#endif
#if ( MUTUAL4_NUM > 22 )
    CTSUSO0_MUTUAL4_KEY22,
#endif
#if ( MUTUAL4_NUM > 23 )
    CTSUSO0_MUTUAL4_KEY23,
#endif
#if ( MUTUAL4_NUM > 24 )
    CTSUSO0_MUTUAL4_KEY24,
#endif
#if ( MUTUAL4_NUM > 25 )
    CTSUSO0_MUTUAL4_KEY25,
#endif
#if ( MUTUAL4_NUM > 26 )
    CTSUSO0_MUTUAL4_KEY26,
#endif
#if ( MUTUAL4_NUM > 27 )
    CTSUSO0_MUTUAL4_KEY27,
#endif
#if ( MUTUAL4_NUM > 28 )
    CTSUSO0_MUTUAL4_KEY28,
#endif
#if ( MUTUAL4_NUM > 29 )
    CTSUSO0_MUTUAL4_KEY29,
#endif
#if ( MUTUAL4_NUM > 30 )
    CTSUSO0_MUTUAL4_KEY30,
#endif
#if ( MUTUAL4_NUM > 31 )
    CTSUSO0_MUTUAL4_KEY31,
#endif
#if ( MUTUAL4_NUM > 32 )
    CTSUSO0_MUTUAL4_KEY32,
#endif
#if ( MUTUAL4_NUM > 33 )
    CTSUSO0_MUTUAL4_KEY33,
#endif
#if ( MUTUAL4_NUM > 34 )
    CTSUSO0_MUTUAL4_KEY34,
#endif
#if ( MUTUAL4_NUM > 35 )
    CTSUSO0_MUTUAL4_KEY35,
#endif
#if ( MUTUAL4_NUM > 36 )
    CTSUSO0_MUTUAL4_KEY36,
#endif
#if ( MUTUAL4_NUM > 37 )
    CTSUSO0_MUTUAL4_KEY37,
#endif
#if ( MUTUAL4_NUM > 38 )
    CTSUSO0_MUTUAL4_KEY38,
#endif
#if ( MUTUAL4_NUM > 39 )
    CTSUSO0_MUTUAL4_KEY39,
#endif
#if ( MUTUAL4_NUM > 40 )
    CTSUSO0_MUTUAL4_KEY40,
#endif
#if ( MUTUAL4_NUM > 41 )
    CTSUSO0_MUTUAL4_KEY41,
#endif
#if ( MUTUAL4_NUM > 42 )
    CTSUSO0_MUTUAL4_KEY42,
#endif
#if ( MUTUAL4_NUM > 43 )
    CTSUSO0_MUTUAL4_KEY43,
#endif
#if ( MUTUAL4_NUM > 44 )
    CTSUSO0_MUTUAL4_KEY44,
#endif
#if ( MUTUAL4_NUM > 45 )
    CTSUSO0_MUTUAL4_KEY45,
#endif
#if ( MUTUAL4_NUM > 46 )
    CTSUSO0_MUTUAL4_KEY46,
#endif
#if ( MUTUAL4_NUM > 47 )
    CTSUSO0_MUTUAL4_KEY47,
#endif
#if ( MUTUAL4_NUM > 48 )
    CTSUSO0_MUTUAL4_KEY48,
#endif
#if ( MUTUAL4_NUM > 49 )
    CTSUSO0_MUTUAL4_KEY49,
#endif
#if ( MUTUAL4_NUM > 50 )
    CTSUSO0_MUTUAL4_KEY50,
#endif
#if ( MUTUAL4_NUM > 51 )
    CTSUSO0_MUTUAL4_KEY51,
#endif
#if ( MUTUAL4_NUM > 52 )
    CTSUSO0_MUTUAL4_KEY52,
#endif
#if ( MUTUAL4_NUM > 53 )
    CTSUSO0_MUTUAL4_KEY53,
#endif
#if ( MUTUAL4_NUM > 54 )
    CTSUSO0_MUTUAL4_KEY54,
#endif
#if ( MUTUAL4_NUM > 55 )
    CTSUSO0_MUTUAL4_KEY55,
#endif
#if ( MUTUAL4_NUM > 56 )
    CTSUSO0_MUTUAL4_KEY56,
#endif
#if ( MUTUAL4_NUM > 57 )
    CTSUSO0_MUTUAL4_KEY57,
#endif
#if ( MUTUAL4_NUM > 58 )
    CTSUSO0_MUTUAL4_KEY58,
#endif
#if ( MUTUAL4_NUM > 59 )
    CTSUSO0_MUTUAL4_KEY59,
#endif
#if ( MUTUAL4_NUM > 60 )
    CTSUSO0_MUTUAL4_KEY60,
#endif
#if ( MUTUAL4_NUM > 61 )
    CTSUSO0_MUTUAL4_KEY61,
#endif
#if ( MUTUAL4_NUM > 62 )
    CTSUSO0_MUTUAL4_KEY62,
#endif
#if ( MUTUAL4_NUM > 63 )
    CTSUSO0_MUTUAL4_KEY63,
#endif
};

const uint16_t g_mutual4_ctsuso1[] =
{
#if ( MUTUAL4_NUM > 0 )
    CTSUSO1_MUTUAL4_KEY00,
#endif
#if ( MUTUAL4_NUM > 1 )
    CTSUSO1_MUTUAL4_KEY01,
#endif
#if ( MUTUAL4_NUM > 2 )
    CTSUSO1_MUTUAL4_KEY02,
#endif
#if ( MUTUAL4_NUM > 3 )
    CTSUSO1_MUTUAL4_KEY03,
#endif
#if ( MUTUAL4_NUM > 4 )
    CTSUSO1_MUTUAL4_KEY04,
#endif
#if ( MUTUAL4_NUM > 5 )
    CTSUSO1_MUTUAL4_KEY05,
#endif
#if ( MUTUAL4_NUM > 6 )
    CTSUSO1_MUTUAL4_KEY06,
#endif
#if ( MUTUAL4_NUM > 7 )
    CTSUSO1_MUTUAL4_KEY07,
#endif
#if ( MUTUAL4_NUM > 8 )
    CTSUSO1_MUTUAL4_KEY08,
#endif
#if ( MUTUAL4_NUM > 9 )
    CTSUSO1_MUTUAL4_KEY09,
#endif
#if ( MUTUAL4_NUM > 10 )
    CTSUSO1_MUTUAL4_KEY10,
#endif
#if ( MUTUAL4_NUM > 11 )
    CTSUSO1_MUTUAL4_KEY11,
#endif
#if ( MUTUAL4_NUM > 12 )
    CTSUSO1_MUTUAL4_KEY12,
#endif
#if ( MUTUAL4_NUM > 13 )
    CTSUSO1_MUTUAL4_KEY13,
#endif
#if ( MUTUAL4_NUM > 14 )
    CTSUSO1_MUTUAL4_KEY14,
#endif
#if ( MUTUAL4_NUM > 15 )
    CTSUSO1_MUTUAL4_KEY15,
#endif
#if ( MUTUAL4_NUM > 16 )
    CTSUSO1_MUTUAL4_KEY16,
#endif
#if ( MUTUAL4_NUM > 17 )
    CTSUSO1_MUTUAL4_KEY17,
#endif
#if ( MUTUAL4_NUM > 18 )
    CTSUSO1_MUTUAL4_KEY18,
#endif
#if ( MUTUAL4_NUM > 19 )
    CTSUSO1_MUTUAL4_KEY19,
#endif
#if ( MUTUAL4_NUM > 20 )
    CTSUSO1_MUTUAL4_KEY20,
#endif
#if ( MUTUAL4_NUM > 21 )
    CTSUSO1_MUTUAL4_KEY21,
#endif
#if ( MUTUAL4_NUM > 22 )
    CTSUSO1_MUTUAL4_KEY22,
#endif
#if ( MUTUAL4_NUM > 23 )
    CTSUSO1_MUTUAL4_KEY23,
#endif
#if ( MUTUAL4_NUM > 24 )
    CTSUSO1_MUTUAL4_KEY24,
#endif
#if ( MUTUAL4_NUM > 25 )
    CTSUSO1_MUTUAL4_KEY25,
#endif
#if ( MUTUAL4_NUM > 26 )
    CTSUSO1_MUTUAL4_KEY26,
#endif
#if ( MUTUAL4_NUM > 27 )
    CTSUSO1_MUTUAL4_KEY27,
#endif
#if ( MUTUAL4_NUM > 28 )
    CTSUSO1_MUTUAL4_KEY28,
#endif
#if ( MUTUAL4_NUM > 29 )
    CTSUSO1_MUTUAL4_KEY29,
#endif
#if ( MUTUAL4_NUM > 30 )
    CTSUSO1_MUTUAL4_KEY30,
#endif
#if ( MUTUAL4_NUM > 31 )
    CTSUSO1_MUTUAL4_KEY31,
#endif
#if ( MUTUAL4_NUM > 32 )
    CTSUSO1_MUTUAL4_KEY32,
#endif
#if ( MUTUAL4_NUM > 33 )
    CTSUSO1_MUTUAL4_KEY33,
#endif
#if ( MUTUAL4_NUM > 34 )
    CTSUSO1_MUTUAL4_KEY34,
#endif
#if ( MUTUAL4_NUM > 35 )
    CTSUSO1_MUTUAL4_KEY35,
#endif
#if ( MUTUAL4_NUM > 36 )
    CTSUSO1_MUTUAL4_KEY36,
#endif
#if ( MUTUAL4_NUM > 37 )
    CTSUSO1_MUTUAL4_KEY37,
#endif
#if ( MUTUAL4_NUM > 38 )
    CTSUSO1_MUTUAL4_KEY38,
#endif
#if ( MUTUAL4_NUM > 39 )
    CTSUSO1_MUTUAL4_KEY39,
#endif
#if ( MUTUAL4_NUM > 40 )
    CTSUSO1_MUTUAL4_KEY40,
#endif
#if ( MUTUAL4_NUM > 41 )
    CTSUSO1_MUTUAL4_KEY41,
#endif
#if ( MUTUAL4_NUM > 42 )
    CTSUSO1_MUTUAL4_KEY42,
#endif
#if ( MUTUAL4_NUM > 43 )
    CTSUSO1_MUTUAL4_KEY43,
#endif
#if ( MUTUAL4_NUM > 44 )
    CTSUSO1_MUTUAL4_KEY44,
#endif
#if ( MUTUAL4_NUM > 45 )
    CTSUSO1_MUTUAL4_KEY45,
#endif
#if ( MUTUAL4_NUM > 46 )
    CTSUSO1_MUTUAL4_KEY46,
#endif
#if ( MUTUAL4_NUM > 47 )
    CTSUSO1_MUTUAL4_KEY47,
#endif
#if ( MUTUAL4_NUM > 48 )
    CTSUSO1_MUTUAL4_KEY48,
#endif
#if ( MUTUAL4_NUM > 49 )
    CTSUSO1_MUTUAL4_KEY49,
#endif
#if ( MUTUAL4_NUM > 50 )
    CTSUSO1_MUTUAL4_KEY50,
#endif
#if ( MUTUAL4_NUM > 51 )
    CTSUSO1_MUTUAL4_KEY51,
#endif
#if ( MUTUAL4_NUM > 52 )
    CTSUSO1_MUTUAL4_KEY52,
#endif
#if ( MUTUAL4_NUM > 53 )
    CTSUSO1_MUTUAL4_KEY53,
#endif
#if ( MUTUAL4_NUM > 54 )
    CTSUSO1_MUTUAL4_KEY54,
#endif
#if ( MUTUAL4_NUM > 55 )
    CTSUSO1_MUTUAL4_KEY55,
#endif
#if ( MUTUAL4_NUM > 56 )
    CTSUSO1_MUTUAL4_KEY56,
#endif
#if ( MUTUAL4_NUM > 57 )
    CTSUSO1_MUTUAL4_KEY57,
#endif
#if ( MUTUAL4_NUM > 58 )
    CTSUSO1_MUTUAL4_KEY58,
#endif
#if ( MUTUAL4_NUM > 59 )
    CTSUSO1_MUTUAL4_KEY59,
#endif
#if ( MUTUAL4_NUM > 60 )
    CTSUSO1_MUTUAL4_KEY60,
#endif
#if ( MUTUAL4_NUM > 61 )
    CTSUSO1_MUTUAL4_KEY61,
#endif
#if ( MUTUAL4_NUM > 62 )
    CTSUSO1_MUTUAL4_KEY62,
#endif
#if ( MUTUAL4_NUM > 63 )
    CTSUSO1_MUTUAL4_KEY63,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 4 )

/*=====    Mutual 5    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 5 )
const uint16_t g_mutual5_ctsussc[] =
{
#if ( MUTUAL5_NUM > 0 )
    CTSUSSC_MUTUAL5_KEY00,
#endif
#if ( MUTUAL5_NUM > 1 )
    CTSUSSC_MUTUAL5_KEY01,
#endif
#if ( MUTUAL5_NUM > 2 )
    CTSUSSC_MUTUAL5_KEY02,
#endif
#if ( MUTUAL5_NUM > 3 )
    CTSUSSC_MUTUAL5_KEY03,
#endif
#if ( MUTUAL5_NUM > 4 )
    CTSUSSC_MUTUAL5_KEY04,
#endif
#if ( MUTUAL5_NUM > 5 )
    CTSUSSC_MUTUAL5_KEY05,
#endif
#if ( MUTUAL5_NUM > 6 )
    CTSUSSC_MUTUAL5_KEY06,
#endif
#if ( MUTUAL5_NUM > 7 )
    CTSUSSC_MUTUAL5_KEY07,
#endif
#if ( MUTUAL5_NUM > 8 )
    CTSUSSC_MUTUAL5_KEY08,
#endif
#if ( MUTUAL5_NUM > 9 )
    CTSUSSC_MUTUAL5_KEY09,
#endif
#if ( MUTUAL5_NUM > 10 )
    CTSUSSC_MUTUAL5_KEY10,
#endif
#if ( MUTUAL5_NUM > 11 )
    CTSUSSC_MUTUAL5_KEY11,
#endif
#if ( MUTUAL5_NUM > 12 )
    CTSUSSC_MUTUAL5_KEY12,
#endif
#if ( MUTUAL5_NUM > 13 )
    CTSUSSC_MUTUAL5_KEY13,
#endif
#if ( MUTUAL5_NUM > 14 )
    CTSUSSC_MUTUAL5_KEY14,
#endif
#if ( MUTUAL5_NUM > 15 )
    CTSUSSC_MUTUAL5_KEY15,
#endif
#if ( MUTUAL5_NUM > 16 )
    CTSUSSC_MUTUAL5_KEY16,
#endif
#if ( MUTUAL5_NUM > 17 )
    CTSUSSC_MUTUAL5_KEY17,
#endif
#if ( MUTUAL5_NUM > 18 )
    CTSUSSC_MUTUAL5_KEY18,
#endif
#if ( MUTUAL5_NUM > 19 )
    CTSUSSC_MUTUAL5_KEY19,
#endif
#if ( MUTUAL5_NUM > 20 )
    CTSUSSC_MUTUAL5_KEY20,
#endif
#if ( MUTUAL5_NUM > 21 )
    CTSUSSC_MUTUAL5_KEY21,
#endif
#if ( MUTUAL5_NUM > 22 )
    CTSUSSC_MUTUAL5_KEY22,
#endif
#if ( MUTUAL5_NUM > 23 )
    CTSUSSC_MUTUAL5_KEY23,
#endif
#if ( MUTUAL5_NUM > 24 )
    CTSUSSC_MUTUAL5_KEY24,
#endif
#if ( MUTUAL5_NUM > 25 )
    CTSUSSC_MUTUAL5_KEY25,
#endif
#if ( MUTUAL5_NUM > 26 )
    CTSUSSC_MUTUAL5_KEY26,
#endif
#if ( MUTUAL5_NUM > 27 )
    CTSUSSC_MUTUAL5_KEY27,
#endif
#if ( MUTUAL5_NUM > 28 )
    CTSUSSC_MUTUAL5_KEY28,
#endif
#if ( MUTUAL5_NUM > 29 )
    CTSUSSC_MUTUAL5_KEY29,
#endif
#if ( MUTUAL5_NUM > 30 )
    CTSUSSC_MUTUAL5_KEY30,
#endif
#if ( MUTUAL5_NUM > 31 )
    CTSUSSC_MUTUAL5_KEY31,
#endif
#if ( MUTUAL5_NUM > 32 )
    CTSUSSC_MUTUAL5_KEY32,
#endif
#if ( MUTUAL5_NUM > 33 )
    CTSUSSC_MUTUAL5_KEY33,
#endif
#if ( MUTUAL5_NUM > 34 )
    CTSUSSC_MUTUAL5_KEY34,
#endif
#if ( MUTUAL5_NUM > 35 )
    CTSUSSC_MUTUAL5_KEY35,
#endif
#if ( MUTUAL5_NUM > 36 )
    CTSUSSC_MUTUAL5_KEY36,
#endif
#if ( MUTUAL5_NUM > 37 )
    CTSUSSC_MUTUAL5_KEY37,
#endif
#if ( MUTUAL5_NUM > 38 )
    CTSUSSC_MUTUAL5_KEY38,
#endif
#if ( MUTUAL5_NUM > 39 )
    CTSUSSC_MUTUAL5_KEY39,
#endif
#if ( MUTUAL5_NUM > 40 )
    CTSUSSC_MUTUAL5_KEY40,
#endif
#if ( MUTUAL5_NUM > 41 )
    CTSUSSC_MUTUAL5_KEY41,
#endif
#if ( MUTUAL5_NUM > 42 )
    CTSUSSC_MUTUAL5_KEY42,
#endif
#if ( MUTUAL5_NUM > 43 )
    CTSUSSC_MUTUAL5_KEY43,
#endif
#if ( MUTUAL5_NUM > 44 )
    CTSUSSC_MUTUAL5_KEY44,
#endif
#if ( MUTUAL5_NUM > 45 )
    CTSUSSC_MUTUAL5_KEY45,
#endif
#if ( MUTUAL5_NUM > 46 )
    CTSUSSC_MUTUAL5_KEY46,
#endif
#if ( MUTUAL5_NUM > 47 )
    CTSUSSC_MUTUAL5_KEY47,
#endif
#if ( MUTUAL5_NUM > 48 )
    CTSUSSC_MUTUAL5_KEY48,
#endif
#if ( MUTUAL5_NUM > 49 )
    CTSUSSC_MUTUAL5_KEY49,
#endif
#if ( MUTUAL5_NUM > 50 )
    CTSUSSC_MUTUAL5_KEY50,
#endif
#if ( MUTUAL5_NUM > 51 )
    CTSUSSC_MUTUAL5_KEY51,
#endif
#if ( MUTUAL5_NUM > 52 )
    CTSUSSC_MUTUAL5_KEY52,
#endif
#if ( MUTUAL5_NUM > 53 )
    CTSUSSC_MUTUAL5_KEY53,
#endif
#if ( MUTUAL5_NUM > 54 )
    CTSUSSC_MUTUAL5_KEY54,
#endif
#if ( MUTUAL5_NUM > 55 )
    CTSUSSC_MUTUAL5_KEY55,
#endif
#if ( MUTUAL5_NUM > 56 )
    CTSUSSC_MUTUAL5_KEY56,
#endif
#if ( MUTUAL5_NUM > 57 )
    CTSUSSC_MUTUAL5_KEY57,
#endif
#if ( MUTUAL5_NUM > 58 )
    CTSUSSC_MUTUAL5_KEY58,
#endif
#if ( MUTUAL5_NUM > 59 )
    CTSUSSC_MUTUAL5_KEY59,
#endif
#if ( MUTUAL5_NUM > 60 )
    CTSUSSC_MUTUAL5_KEY60,
#endif
#if ( MUTUAL5_NUM > 61 )
    CTSUSSC_MUTUAL5_KEY61,
#endif
#if ( MUTUAL5_NUM > 62 )
    CTSUSSC_MUTUAL5_KEY62,
#endif
#if ( MUTUAL5_NUM > 63 )
    CTSUSSC_MUTUAL5_KEY63,
#endif
};

const uint16_t g_mutual5_ctsuso0[] =
{
#if ( MUTUAL5_NUM > 0 )
    CTSUSO0_MUTUAL5_KEY00,
#endif
#if ( MUTUAL5_NUM > 1 )
    CTSUSO0_MUTUAL5_KEY01,
#endif
#if ( MUTUAL5_NUM > 2 )
    CTSUSO0_MUTUAL5_KEY02,
#endif
#if ( MUTUAL5_NUM > 3 )
    CTSUSO0_MUTUAL5_KEY03,
#endif
#if ( MUTUAL5_NUM > 4 )
    CTSUSO0_MUTUAL5_KEY04,
#endif
#if ( MUTUAL5_NUM > 5 )
    CTSUSO0_MUTUAL5_KEY05,
#endif
#if ( MUTUAL5_NUM > 6 )
    CTSUSO0_MUTUAL5_KEY06,
#endif
#if ( MUTUAL5_NUM > 7 )
    CTSUSO0_MUTUAL5_KEY07,
#endif
#if ( MUTUAL5_NUM > 8 )
    CTSUSO0_MUTUAL5_KEY08,
#endif
#if ( MUTUAL5_NUM > 9 )
    CTSUSO0_MUTUAL5_KEY09,
#endif
#if ( MUTUAL5_NUM > 10 )
    CTSUSO0_MUTUAL5_KEY10,
#endif
#if ( MUTUAL5_NUM > 11 )
    CTSUSO0_MUTUAL5_KEY11,
#endif
#if ( MUTUAL5_NUM > 12 )
    CTSUSO0_MUTUAL5_KEY12,
#endif
#if ( MUTUAL5_NUM > 13 )
    CTSUSO0_MUTUAL5_KEY13,
#endif
#if ( MUTUAL5_NUM > 14 )
    CTSUSO0_MUTUAL5_KEY14,
#endif
#if ( MUTUAL5_NUM > 15 )
    CTSUSO0_MUTUAL5_KEY15,
#endif
#if ( MUTUAL5_NUM > 16 )
    CTSUSO0_MUTUAL5_KEY16,
#endif
#if ( MUTUAL5_NUM > 17 )
    CTSUSO0_MUTUAL5_KEY17,
#endif
#if ( MUTUAL5_NUM > 18 )
    CTSUSO0_MUTUAL5_KEY18,
#endif
#if ( MUTUAL5_NUM > 19 )
    CTSUSO0_MUTUAL5_KEY19,
#endif
#if ( MUTUAL5_NUM > 20 )
    CTSUSO0_MUTUAL5_KEY20,
#endif
#if ( MUTUAL5_NUM > 21 )
    CTSUSO0_MUTUAL5_KEY21,
#endif
#if ( MUTUAL5_NUM > 22 )
    CTSUSO0_MUTUAL5_KEY22,
#endif
#if ( MUTUAL5_NUM > 23 )
    CTSUSO0_MUTUAL5_KEY23,
#endif
#if ( MUTUAL5_NUM > 24 )
    CTSUSO0_MUTUAL5_KEY24,
#endif
#if ( MUTUAL5_NUM > 25 )
    CTSUSO0_MUTUAL5_KEY25,
#endif
#if ( MUTUAL5_NUM > 26 )
    CTSUSO0_MUTUAL5_KEY26,
#endif
#if ( MUTUAL5_NUM > 27 )
    CTSUSO0_MUTUAL5_KEY27,
#endif
#if ( MUTUAL5_NUM > 28 )
    CTSUSO0_MUTUAL5_KEY28,
#endif
#if ( MUTUAL5_NUM > 29 )
    CTSUSO0_MUTUAL5_KEY29,
#endif
#if ( MUTUAL5_NUM > 30 )
    CTSUSO0_MUTUAL5_KEY30,
#endif
#if ( MUTUAL5_NUM > 31 )
    CTSUSO0_MUTUAL5_KEY31,
#endif
#if ( MUTUAL5_NUM > 32 )
    CTSUSO0_MUTUAL5_KEY32,
#endif
#if ( MUTUAL5_NUM > 33 )
    CTSUSO0_MUTUAL5_KEY33,
#endif
#if ( MUTUAL5_NUM > 34 )
    CTSUSO0_MUTUAL5_KEY34,
#endif
#if ( MUTUAL5_NUM > 35 )
    CTSUSO0_MUTUAL5_KEY35,
#endif
#if ( MUTUAL5_NUM > 36 )
    CTSUSO0_MUTUAL5_KEY36,
#endif
#if ( MUTUAL5_NUM > 37 )
    CTSUSO0_MUTUAL5_KEY37,
#endif
#if ( MUTUAL5_NUM > 38 )
    CTSUSO0_MUTUAL5_KEY38,
#endif
#if ( MUTUAL5_NUM > 39 )
    CTSUSO0_MUTUAL5_KEY39,
#endif
#if ( MUTUAL5_NUM > 40 )
    CTSUSO0_MUTUAL5_KEY40,
#endif
#if ( MUTUAL5_NUM > 41 )
    CTSUSO0_MUTUAL5_KEY41,
#endif
#if ( MUTUAL5_NUM > 42 )
    CTSUSO0_MUTUAL5_KEY42,
#endif
#if ( MUTUAL5_NUM > 43 )
    CTSUSO0_MUTUAL5_KEY43,
#endif
#if ( MUTUAL5_NUM > 44 )
    CTSUSO0_MUTUAL5_KEY44,
#endif
#if ( MUTUAL5_NUM > 45 )
    CTSUSO0_MUTUAL5_KEY45,
#endif
#if ( MUTUAL5_NUM > 46 )
    CTSUSO0_MUTUAL5_KEY46,
#endif
#if ( MUTUAL5_NUM > 47 )
    CTSUSO0_MUTUAL5_KEY47,
#endif
#if ( MUTUAL5_NUM > 48 )
    CTSUSO0_MUTUAL5_KEY48,
#endif
#if ( MUTUAL5_NUM > 49 )
    CTSUSO0_MUTUAL5_KEY49,
#endif
#if ( MUTUAL5_NUM > 50 )
    CTSUSO0_MUTUAL5_KEY50,
#endif
#if ( MUTUAL5_NUM > 51 )
    CTSUSO0_MUTUAL5_KEY51,
#endif
#if ( MUTUAL5_NUM > 52 )
    CTSUSO0_MUTUAL5_KEY52,
#endif
#if ( MUTUAL5_NUM > 53 )
    CTSUSO0_MUTUAL5_KEY53,
#endif
#if ( MUTUAL5_NUM > 54 )
    CTSUSO0_MUTUAL5_KEY54,
#endif
#if ( MUTUAL5_NUM > 55 )
    CTSUSO0_MUTUAL5_KEY55,
#endif
#if ( MUTUAL5_NUM > 56 )
    CTSUSO0_MUTUAL5_KEY56,
#endif
#if ( MUTUAL5_NUM > 57 )
    CTSUSO0_MUTUAL5_KEY57,
#endif
#if ( MUTUAL5_NUM > 58 )
    CTSUSO0_MUTUAL5_KEY58,
#endif
#if ( MUTUAL5_NUM > 59 )
    CTSUSO0_MUTUAL5_KEY59,
#endif
#if ( MUTUAL5_NUM > 60 )
    CTSUSO0_MUTUAL5_KEY60,
#endif
#if ( MUTUAL5_NUM > 61 )
    CTSUSO0_MUTUAL5_KEY61,
#endif
#if ( MUTUAL5_NUM > 62 )
    CTSUSO0_MUTUAL5_KEY62,
#endif
#if ( MUTUAL5_NUM > 63 )
    CTSUSO0_MUTUAL5_KEY63,
#endif
};

const uint16_t g_mutual5_ctsuso1[] =
{
#if ( MUTUAL5_NUM > 0 )
    CTSUSO1_MUTUAL5_KEY00,
#endif
#if ( MUTUAL5_NUM > 1 )
    CTSUSO1_MUTUAL5_KEY01,
#endif
#if ( MUTUAL5_NUM > 2 )
    CTSUSO1_MUTUAL5_KEY02,
#endif
#if ( MUTUAL5_NUM > 3 )
    CTSUSO1_MUTUAL5_KEY03,
#endif
#if ( MUTUAL5_NUM > 4 )
    CTSUSO1_MUTUAL5_KEY04,
#endif
#if ( MUTUAL5_NUM > 5 )
    CTSUSO1_MUTUAL5_KEY05,
#endif
#if ( MUTUAL5_NUM > 6 )
    CTSUSO1_MUTUAL5_KEY06,
#endif
#if ( MUTUAL5_NUM > 7 )
    CTSUSO1_MUTUAL5_KEY07,
#endif
#if ( MUTUAL5_NUM > 8 )
    CTSUSO1_MUTUAL5_KEY08,
#endif
#if ( MUTUAL5_NUM > 9 )
    CTSUSO1_MUTUAL5_KEY09,
#endif
#if ( MUTUAL5_NUM > 10 )
    CTSUSO1_MUTUAL5_KEY10,
#endif
#if ( MUTUAL5_NUM > 11 )
    CTSUSO1_MUTUAL5_KEY11,
#endif
#if ( MUTUAL5_NUM > 12 )
    CTSUSO1_MUTUAL5_KEY12,
#endif
#if ( MUTUAL5_NUM > 13 )
    CTSUSO1_MUTUAL5_KEY13,
#endif
#if ( MUTUAL5_NUM > 14 )
    CTSUSO1_MUTUAL5_KEY14,
#endif
#if ( MUTUAL5_NUM > 15 )
    CTSUSO1_MUTUAL5_KEY15,
#endif
#if ( MUTUAL5_NUM > 16 )
    CTSUSO1_MUTUAL5_KEY16,
#endif
#if ( MUTUAL5_NUM > 17 )
    CTSUSO1_MUTUAL5_KEY17,
#endif
#if ( MUTUAL5_NUM > 18 )
    CTSUSO1_MUTUAL5_KEY18,
#endif
#if ( MUTUAL5_NUM > 19 )
    CTSUSO1_MUTUAL5_KEY19,
#endif
#if ( MUTUAL5_NUM > 20 )
    CTSUSO1_MUTUAL5_KEY20,
#endif
#if ( MUTUAL5_NUM > 21 )
    CTSUSO1_MUTUAL5_KEY21,
#endif
#if ( MUTUAL5_NUM > 22 )
    CTSUSO1_MUTUAL5_KEY22,
#endif
#if ( MUTUAL5_NUM > 23 )
    CTSUSO1_MUTUAL5_KEY23,
#endif
#if ( MUTUAL5_NUM > 24 )
    CTSUSO1_MUTUAL5_KEY24,
#endif
#if ( MUTUAL5_NUM > 25 )
    CTSUSO1_MUTUAL5_KEY25,
#endif
#if ( MUTUAL5_NUM > 26 )
    CTSUSO1_MUTUAL5_KEY26,
#endif
#if ( MUTUAL5_NUM > 27 )
    CTSUSO1_MUTUAL5_KEY27,
#endif
#if ( MUTUAL5_NUM > 28 )
    CTSUSO1_MUTUAL5_KEY28,
#endif
#if ( MUTUAL5_NUM > 29 )
    CTSUSO1_MUTUAL5_KEY29,
#endif
#if ( MUTUAL5_NUM > 30 )
    CTSUSO1_MUTUAL5_KEY30,
#endif
#if ( MUTUAL5_NUM > 31 )
    CTSUSO1_MUTUAL5_KEY31,
#endif
#if ( MUTUAL5_NUM > 32 )
    CTSUSO1_MUTUAL5_KEY32,
#endif
#if ( MUTUAL5_NUM > 33 )
    CTSUSO1_MUTUAL5_KEY33,
#endif
#if ( MUTUAL5_NUM > 34 )
    CTSUSO1_MUTUAL5_KEY34,
#endif
#if ( MUTUAL5_NUM > 35 )
    CTSUSO1_MUTUAL5_KEY35,
#endif
#if ( MUTUAL5_NUM > 36 )
    CTSUSO1_MUTUAL5_KEY36,
#endif
#if ( MUTUAL5_NUM > 37 )
    CTSUSO1_MUTUAL5_KEY37,
#endif
#if ( MUTUAL5_NUM > 38 )
    CTSUSO1_MUTUAL5_KEY38,
#endif
#if ( MUTUAL5_NUM > 39 )
    CTSUSO1_MUTUAL5_KEY39,
#endif
#if ( MUTUAL5_NUM > 40 )
    CTSUSO1_MUTUAL5_KEY40,
#endif
#if ( MUTUAL5_NUM > 41 )
    CTSUSO1_MUTUAL5_KEY41,
#endif
#if ( MUTUAL5_NUM > 42 )
    CTSUSO1_MUTUAL5_KEY42,
#endif
#if ( MUTUAL5_NUM > 43 )
    CTSUSO1_MUTUAL5_KEY43,
#endif
#if ( MUTUAL5_NUM > 44 )
    CTSUSO1_MUTUAL5_KEY44,
#endif
#if ( MUTUAL5_NUM > 45 )
    CTSUSO1_MUTUAL5_KEY45,
#endif
#if ( MUTUAL5_NUM > 46 )
    CTSUSO1_MUTUAL5_KEY46,
#endif
#if ( MUTUAL5_NUM > 47 )
    CTSUSO1_MUTUAL5_KEY47,
#endif
#if ( MUTUAL5_NUM > 48 )
    CTSUSO1_MUTUAL5_KEY48,
#endif
#if ( MUTUAL5_NUM > 49 )
    CTSUSO1_MUTUAL5_KEY49,
#endif
#if ( MUTUAL5_NUM > 50 )
    CTSUSO1_MUTUAL5_KEY50,
#endif
#if ( MUTUAL5_NUM > 51 )
    CTSUSO1_MUTUAL5_KEY51,
#endif
#if ( MUTUAL5_NUM > 52 )
    CTSUSO1_MUTUAL5_KEY52,
#endif
#if ( MUTUAL5_NUM > 53 )
    CTSUSO1_MUTUAL5_KEY53,
#endif
#if ( MUTUAL5_NUM > 54 )
    CTSUSO1_MUTUAL5_KEY54,
#endif
#if ( MUTUAL5_NUM > 55 )
    CTSUSO1_MUTUAL5_KEY55,
#endif
#if ( MUTUAL5_NUM > 56 )
    CTSUSO1_MUTUAL5_KEY56,
#endif
#if ( MUTUAL5_NUM > 57 )
    CTSUSO1_MUTUAL5_KEY57,
#endif
#if ( MUTUAL5_NUM > 58 )
    CTSUSO1_MUTUAL5_KEY58,
#endif
#if ( MUTUAL5_NUM > 59 )
    CTSUSO1_MUTUAL5_KEY59,
#endif
#if ( MUTUAL5_NUM > 60 )
    CTSUSO1_MUTUAL5_KEY60,
#endif
#if ( MUTUAL5_NUM > 61 )
    CTSUSO1_MUTUAL5_KEY61,
#endif
#if ( MUTUAL5_NUM > 62 )
    CTSUSO1_MUTUAL5_KEY62,
#endif
#if ( MUTUAL5_NUM > 63 )
    CTSUSO1_MUTUAL5_KEY63,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 5 )

/*=====    Mutual 6    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 6 )
const uint16_t g_mutual6_ctsussc[] =
{
#if ( MUTUAL6_NUM > 0 )
    CTSUSSC_MUTUAL6_KEY00,
#endif
#if ( MUTUAL6_NUM > 1 )
    CTSUSSC_MUTUAL6_KEY01,
#endif
#if ( MUTUAL6_NUM > 2 )
    CTSUSSC_MUTUAL6_KEY02,
#endif
#if ( MUTUAL6_NUM > 3 )
    CTSUSSC_MUTUAL6_KEY03,
#endif
#if ( MUTUAL6_NUM > 4 )
    CTSUSSC_MUTUAL6_KEY04,
#endif
#if ( MUTUAL6_NUM > 5 )
    CTSUSSC_MUTUAL6_KEY05,
#endif
#if ( MUTUAL6_NUM > 6 )
    CTSUSSC_MUTUAL6_KEY06,
#endif
#if ( MUTUAL6_NUM > 7 )
    CTSUSSC_MUTUAL6_KEY07,
#endif
#if ( MUTUAL6_NUM > 8 )
    CTSUSSC_MUTUAL6_KEY08,
#endif
#if ( MUTUAL6_NUM > 9 )
    CTSUSSC_MUTUAL6_KEY09,
#endif
#if ( MUTUAL6_NUM > 10 )
    CTSUSSC_MUTUAL6_KEY10,
#endif
#if ( MUTUAL6_NUM > 11 )
    CTSUSSC_MUTUAL6_KEY11,
#endif
#if ( MUTUAL6_NUM > 12 )
    CTSUSSC_MUTUAL6_KEY12,
#endif
#if ( MUTUAL6_NUM > 13 )
    CTSUSSC_MUTUAL6_KEY13,
#endif
#if ( MUTUAL6_NUM > 14 )
    CTSUSSC_MUTUAL6_KEY14,
#endif
#if ( MUTUAL6_NUM > 15 )
    CTSUSSC_MUTUAL6_KEY15,
#endif
#if ( MUTUAL6_NUM > 16 )
    CTSUSSC_MUTUAL6_KEY16,
#endif
#if ( MUTUAL6_NUM > 17 )
    CTSUSSC_MUTUAL6_KEY17,
#endif
#if ( MUTUAL6_NUM > 18 )
    CTSUSSC_MUTUAL6_KEY18,
#endif
#if ( MUTUAL6_NUM > 19 )
    CTSUSSC_MUTUAL6_KEY19,
#endif
#if ( MUTUAL6_NUM > 20 )
    CTSUSSC_MUTUAL6_KEY20,
#endif
#if ( MUTUAL6_NUM > 21 )
    CTSUSSC_MUTUAL6_KEY21,
#endif
#if ( MUTUAL6_NUM > 22 )
    CTSUSSC_MUTUAL6_KEY22,
#endif
#if ( MUTUAL6_NUM > 23 )
    CTSUSSC_MUTUAL6_KEY23,
#endif
#if ( MUTUAL6_NUM > 24 )
    CTSUSSC_MUTUAL6_KEY24,
#endif
#if ( MUTUAL6_NUM > 25 )
    CTSUSSC_MUTUAL6_KEY25,
#endif
#if ( MUTUAL6_NUM > 26 )
    CTSUSSC_MUTUAL6_KEY26,
#endif
#if ( MUTUAL6_NUM > 27 )
    CTSUSSC_MUTUAL6_KEY27,
#endif
#if ( MUTUAL6_NUM > 28 )
    CTSUSSC_MUTUAL6_KEY28,
#endif
#if ( MUTUAL6_NUM > 29 )
    CTSUSSC_MUTUAL6_KEY29,
#endif
#if ( MUTUAL6_NUM > 30 )
    CTSUSSC_MUTUAL6_KEY30,
#endif
#if ( MUTUAL6_NUM > 31 )
    CTSUSSC_MUTUAL6_KEY31,
#endif
#if ( MUTUAL6_NUM > 32 )
    CTSUSSC_MUTUAL6_KEY32,
#endif
#if ( MUTUAL6_NUM > 33 )
    CTSUSSC_MUTUAL6_KEY33,
#endif
#if ( MUTUAL6_NUM > 34 )
    CTSUSSC_MUTUAL6_KEY34,
#endif
#if ( MUTUAL6_NUM > 35 )
    CTSUSSC_MUTUAL6_KEY35,
#endif
#if ( MUTUAL6_NUM > 36 )
    CTSUSSC_MUTUAL6_KEY36,
#endif
#if ( MUTUAL6_NUM > 37 )
    CTSUSSC_MUTUAL6_KEY37,
#endif
#if ( MUTUAL6_NUM > 38 )
    CTSUSSC_MUTUAL6_KEY38,
#endif
#if ( MUTUAL6_NUM > 39 )
    CTSUSSC_MUTUAL6_KEY39,
#endif
#if ( MUTUAL6_NUM > 40 )
    CTSUSSC_MUTUAL6_KEY40,
#endif
#if ( MUTUAL6_NUM > 41 )
    CTSUSSC_MUTUAL6_KEY41,
#endif
#if ( MUTUAL6_NUM > 42 )
    CTSUSSC_MUTUAL6_KEY42,
#endif
#if ( MUTUAL6_NUM > 43 )
    CTSUSSC_MUTUAL6_KEY43,
#endif
#if ( MUTUAL6_NUM > 44 )
    CTSUSSC_MUTUAL6_KEY44,
#endif
#if ( MUTUAL6_NUM > 45 )
    CTSUSSC_MUTUAL6_KEY45,
#endif
#if ( MUTUAL6_NUM > 46 )
    CTSUSSC_MUTUAL6_KEY46,
#endif
#if ( MUTUAL6_NUM > 47 )
    CTSUSSC_MUTUAL6_KEY47,
#endif
#if ( MUTUAL6_NUM > 48 )
    CTSUSSC_MUTUAL6_KEY48,
#endif
#if ( MUTUAL6_NUM > 49 )
    CTSUSSC_MUTUAL6_KEY49,
#endif
#if ( MUTUAL6_NUM > 50 )
    CTSUSSC_MUTUAL6_KEY50,
#endif
#if ( MUTUAL6_NUM > 51 )
    CTSUSSC_MUTUAL6_KEY51,
#endif
#if ( MUTUAL6_NUM > 52 )
    CTSUSSC_MUTUAL6_KEY52,
#endif
#if ( MUTUAL6_NUM > 53 )
    CTSUSSC_MUTUAL6_KEY53,
#endif
#if ( MUTUAL6_NUM > 54 )
    CTSUSSC_MUTUAL6_KEY54,
#endif
#if ( MUTUAL6_NUM > 55 )
    CTSUSSC_MUTUAL6_KEY55,
#endif
#if ( MUTUAL6_NUM > 56 )
    CTSUSSC_MUTUAL6_KEY56,
#endif
#if ( MUTUAL6_NUM > 57 )
    CTSUSSC_MUTUAL6_KEY57,
#endif
#if ( MUTUAL6_NUM > 58 )
    CTSUSSC_MUTUAL6_KEY58,
#endif
#if ( MUTUAL6_NUM > 59 )
    CTSUSSC_MUTUAL6_KEY59,
#endif
#if ( MUTUAL6_NUM > 60 )
    CTSUSSC_MUTUAL6_KEY60,
#endif
#if ( MUTUAL6_NUM > 61 )
    CTSUSSC_MUTUAL6_KEY61,
#endif
#if ( MUTUAL6_NUM > 62 )
    CTSUSSC_MUTUAL6_KEY62,
#endif
#if ( MUTUAL6_NUM > 63 )
    CTSUSSC_MUTUAL6_KEY63,
#endif
};

const uint16_t g_mutual6_ctsuso0[] =
{
#if ( MUTUAL6_NUM > 0 )
    CTSUSO0_MUTUAL6_KEY00,
#endif
#if ( MUTUAL6_NUM > 1 )
    CTSUSO0_MUTUAL6_KEY01,
#endif
#if ( MUTUAL6_NUM > 2 )
    CTSUSO0_MUTUAL6_KEY02,
#endif
#if ( MUTUAL6_NUM > 3 )
    CTSUSO0_MUTUAL6_KEY03,
#endif
#if ( MUTUAL6_NUM > 4 )
    CTSUSO0_MUTUAL6_KEY04,
#endif
#if ( MUTUAL6_NUM > 5 )
    CTSUSO0_MUTUAL6_KEY05,
#endif
#if ( MUTUAL6_NUM > 6 )
    CTSUSO0_MUTUAL6_KEY06,
#endif
#if ( MUTUAL6_NUM > 7 )
    CTSUSO0_MUTUAL6_KEY07,
#endif
#if ( MUTUAL6_NUM > 8 )
    CTSUSO0_MUTUAL6_KEY08,
#endif
#if ( MUTUAL6_NUM > 9 )
    CTSUSO0_MUTUAL6_KEY09,
#endif
#if ( MUTUAL6_NUM > 10 )
    CTSUSO0_MUTUAL6_KEY10,
#endif
#if ( MUTUAL6_NUM > 11 )
    CTSUSO0_MUTUAL6_KEY11,
#endif
#if ( MUTUAL6_NUM > 12 )
    CTSUSO0_MUTUAL6_KEY12,
#endif
#if ( MUTUAL6_NUM > 13 )
    CTSUSO0_MUTUAL6_KEY13,
#endif
#if ( MUTUAL6_NUM > 14 )
    CTSUSO0_MUTUAL6_KEY14,
#endif
#if ( MUTUAL6_NUM > 15 )
    CTSUSO0_MUTUAL6_KEY15,
#endif
#if ( MUTUAL6_NUM > 16 )
    CTSUSO0_MUTUAL6_KEY16,
#endif
#if ( MUTUAL6_NUM > 17 )
    CTSUSO0_MUTUAL6_KEY17,
#endif
#if ( MUTUAL6_NUM > 18 )
    CTSUSO0_MUTUAL6_KEY18,
#endif
#if ( MUTUAL6_NUM > 19 )
    CTSUSO0_MUTUAL6_KEY19,
#endif
#if ( MUTUAL6_NUM > 20 )
    CTSUSO0_MUTUAL6_KEY20,
#endif
#if ( MUTUAL6_NUM > 21 )
    CTSUSO0_MUTUAL6_KEY21,
#endif
#if ( MUTUAL6_NUM > 22 )
    CTSUSO0_MUTUAL6_KEY22,
#endif
#if ( MUTUAL6_NUM > 23 )
    CTSUSO0_MUTUAL6_KEY23,
#endif
#if ( MUTUAL6_NUM > 24 )
    CTSUSO0_MUTUAL6_KEY24,
#endif
#if ( MUTUAL6_NUM > 25 )
    CTSUSO0_MUTUAL6_KEY25,
#endif
#if ( MUTUAL6_NUM > 26 )
    CTSUSO0_MUTUAL6_KEY26,
#endif
#if ( MUTUAL6_NUM > 27 )
    CTSUSO0_MUTUAL6_KEY27,
#endif
#if ( MUTUAL6_NUM > 28 )
    CTSUSO0_MUTUAL6_KEY28,
#endif
#if ( MUTUAL6_NUM > 29 )
    CTSUSO0_MUTUAL6_KEY29,
#endif
#if ( MUTUAL6_NUM > 30 )
    CTSUSO0_MUTUAL6_KEY30,
#endif
#if ( MUTUAL6_NUM > 31 )
    CTSUSO0_MUTUAL6_KEY31,
#endif
#if ( MUTUAL6_NUM > 32 )
    CTSUSO0_MUTUAL6_KEY32,
#endif
#if ( MUTUAL6_NUM > 33 )
    CTSUSO0_MUTUAL6_KEY33,
#endif
#if ( MUTUAL6_NUM > 34 )
    CTSUSO0_MUTUAL6_KEY34,
#endif
#if ( MUTUAL6_NUM > 35 )
    CTSUSO0_MUTUAL6_KEY35,
#endif
#if ( MUTUAL6_NUM > 36 )
    CTSUSO0_MUTUAL6_KEY36,
#endif
#if ( MUTUAL6_NUM > 37 )
    CTSUSO0_MUTUAL6_KEY37,
#endif
#if ( MUTUAL6_NUM > 38 )
    CTSUSO0_MUTUAL6_KEY38,
#endif
#if ( MUTUAL6_NUM > 39 )
    CTSUSO0_MUTUAL6_KEY39,
#endif
#if ( MUTUAL6_NUM > 40 )
    CTSUSO0_MUTUAL6_KEY40,
#endif
#if ( MUTUAL6_NUM > 41 )
    CTSUSO0_MUTUAL6_KEY41,
#endif
#if ( MUTUAL6_NUM > 42 )
    CTSUSO0_MUTUAL6_KEY42,
#endif
#if ( MUTUAL6_NUM > 43 )
    CTSUSO0_MUTUAL6_KEY43,
#endif
#if ( MUTUAL6_NUM > 44 )
    CTSUSO0_MUTUAL6_KEY44,
#endif
#if ( MUTUAL6_NUM > 45 )
    CTSUSO0_MUTUAL6_KEY45,
#endif
#if ( MUTUAL6_NUM > 46 )
    CTSUSO0_MUTUAL6_KEY46,
#endif
#if ( MUTUAL6_NUM > 47 )
    CTSUSO0_MUTUAL6_KEY47,
#endif
#if ( MUTUAL6_NUM > 48 )
    CTSUSO0_MUTUAL6_KEY48,
#endif
#if ( MUTUAL6_NUM > 49 )
    CTSUSO0_MUTUAL6_KEY49,
#endif
#if ( MUTUAL6_NUM > 50 )
    CTSUSO0_MUTUAL6_KEY50,
#endif
#if ( MUTUAL6_NUM > 51 )
    CTSUSO0_MUTUAL6_KEY51,
#endif
#if ( MUTUAL6_NUM > 52 )
    CTSUSO0_MUTUAL6_KEY52,
#endif
#if ( MUTUAL6_NUM > 53 )
    CTSUSO0_MUTUAL6_KEY53,
#endif
#if ( MUTUAL6_NUM > 54 )
    CTSUSO0_MUTUAL6_KEY54,
#endif
#if ( MUTUAL6_NUM > 55 )
    CTSUSO0_MUTUAL6_KEY55,
#endif
#if ( MUTUAL6_NUM > 56 )
    CTSUSO0_MUTUAL6_KEY56,
#endif
#if ( MUTUAL6_NUM > 57 )
    CTSUSO0_MUTUAL6_KEY57,
#endif
#if ( MUTUAL6_NUM > 58 )
    CTSUSO0_MUTUAL6_KEY58,
#endif
#if ( MUTUAL6_NUM > 59 )
    CTSUSO0_MUTUAL6_KEY59,
#endif
#if ( MUTUAL6_NUM > 60 )
    CTSUSO0_MUTUAL6_KEY60,
#endif
#if ( MUTUAL6_NUM > 61 )
    CTSUSO0_MUTUAL6_KEY61,
#endif
#if ( MUTUAL6_NUM > 62 )
    CTSUSO0_MUTUAL6_KEY62,
#endif
#if ( MUTUAL6_NUM > 63 )
    CTSUSO0_MUTUAL6_KEY63,
#endif
};

const uint16_t g_mutual6_ctsuso1[] =
{
#if ( MUTUAL6_NUM > 0 )
    CTSUSO1_MUTUAL6_KEY00,
#endif
#if ( MUTUAL6_NUM > 1 )
    CTSUSO1_MUTUAL6_KEY01,
#endif
#if ( MUTUAL6_NUM > 2 )
    CTSUSO1_MUTUAL6_KEY02,
#endif
#if ( MUTUAL6_NUM > 3 )
    CTSUSO1_MUTUAL6_KEY03,
#endif
#if ( MUTUAL6_NUM > 4 )
    CTSUSO1_MUTUAL6_KEY04,
#endif
#if ( MUTUAL6_NUM > 5 )
    CTSUSO1_MUTUAL6_KEY05,
#endif
#if ( MUTUAL6_NUM > 6 )
    CTSUSO1_MUTUAL6_KEY06,
#endif
#if ( MUTUAL6_NUM > 7 )
    CTSUSO1_MUTUAL6_KEY07,
#endif
#if ( MUTUAL6_NUM > 8 )
    CTSUSO1_MUTUAL6_KEY08,
#endif
#if ( MUTUAL6_NUM > 9 )
    CTSUSO1_MUTUAL6_KEY09,
#endif
#if ( MUTUAL6_NUM > 10 )
    CTSUSO1_MUTUAL6_KEY10,
#endif
#if ( MUTUAL6_NUM > 11 )
    CTSUSO1_MUTUAL6_KEY11,
#endif
#if ( MUTUAL6_NUM > 12 )
    CTSUSO1_MUTUAL6_KEY12,
#endif
#if ( MUTUAL6_NUM > 13 )
    CTSUSO1_MUTUAL6_KEY13,
#endif
#if ( MUTUAL6_NUM > 14 )
    CTSUSO1_MUTUAL6_KEY14,
#endif
#if ( MUTUAL6_NUM > 15 )
    CTSUSO1_MUTUAL6_KEY15,
#endif
#if ( MUTUAL6_NUM > 16 )
    CTSUSO1_MUTUAL6_KEY16,
#endif
#if ( MUTUAL6_NUM > 17 )
    CTSUSO1_MUTUAL6_KEY17,
#endif
#if ( MUTUAL6_NUM > 18 )
    CTSUSO1_MUTUAL6_KEY18,
#endif
#if ( MUTUAL6_NUM > 19 )
    CTSUSO1_MUTUAL6_KEY19,
#endif
#if ( MUTUAL6_NUM > 20 )
    CTSUSO1_MUTUAL6_KEY20,
#endif
#if ( MUTUAL6_NUM > 21 )
    CTSUSO1_MUTUAL6_KEY21,
#endif
#if ( MUTUAL6_NUM > 22 )
    CTSUSO1_MUTUAL6_KEY22,
#endif
#if ( MUTUAL6_NUM > 23 )
    CTSUSO1_MUTUAL6_KEY23,
#endif
#if ( MUTUAL6_NUM > 24 )
    CTSUSO1_MUTUAL6_KEY24,
#endif
#if ( MUTUAL6_NUM > 25 )
    CTSUSO1_MUTUAL6_KEY25,
#endif
#if ( MUTUAL6_NUM > 26 )
    CTSUSO1_MUTUAL6_KEY26,
#endif
#if ( MUTUAL6_NUM > 27 )
    CTSUSO1_MUTUAL6_KEY27,
#endif
#if ( MUTUAL6_NUM > 28 )
    CTSUSO1_MUTUAL6_KEY28,
#endif
#if ( MUTUAL6_NUM > 29 )
    CTSUSO1_MUTUAL6_KEY29,
#endif
#if ( MUTUAL6_NUM > 30 )
    CTSUSO1_MUTUAL6_KEY30,
#endif
#if ( MUTUAL6_NUM > 31 )
    CTSUSO1_MUTUAL6_KEY31,
#endif
#if ( MUTUAL6_NUM > 32 )
    CTSUSO1_MUTUAL6_KEY32,
#endif
#if ( MUTUAL6_NUM > 33 )
    CTSUSO1_MUTUAL6_KEY33,
#endif
#if ( MUTUAL6_NUM > 34 )
    CTSUSO1_MUTUAL6_KEY34,
#endif
#if ( MUTUAL6_NUM > 35 )
    CTSUSO1_MUTUAL6_KEY35,
#endif
#if ( MUTUAL6_NUM > 36 )
    CTSUSO1_MUTUAL6_KEY36,
#endif
#if ( MUTUAL6_NUM > 37 )
    CTSUSO1_MUTUAL6_KEY37,
#endif
#if ( MUTUAL6_NUM > 38 )
    CTSUSO1_MUTUAL6_KEY38,
#endif
#if ( MUTUAL6_NUM > 39 )
    CTSUSO1_MUTUAL6_KEY39,
#endif
#if ( MUTUAL6_NUM > 40 )
    CTSUSO1_MUTUAL6_KEY40,
#endif
#if ( MUTUAL6_NUM > 41 )
    CTSUSO1_MUTUAL6_KEY41,
#endif
#if ( MUTUAL6_NUM > 42 )
    CTSUSO1_MUTUAL6_KEY42,
#endif
#if ( MUTUAL6_NUM > 43 )
    CTSUSO1_MUTUAL6_KEY43,
#endif
#if ( MUTUAL6_NUM > 44 )
    CTSUSO1_MUTUAL6_KEY44,
#endif
#if ( MUTUAL6_NUM > 45 )
    CTSUSO1_MUTUAL6_KEY45,
#endif
#if ( MUTUAL6_NUM > 46 )
    CTSUSO1_MUTUAL6_KEY46,
#endif
#if ( MUTUAL6_NUM > 47 )
    CTSUSO1_MUTUAL6_KEY47,
#endif
#if ( MUTUAL6_NUM > 48 )
    CTSUSO1_MUTUAL6_KEY48,
#endif
#if ( MUTUAL6_NUM > 49 )
    CTSUSO1_MUTUAL6_KEY49,
#endif
#if ( MUTUAL6_NUM > 50 )
    CTSUSO1_MUTUAL6_KEY50,
#endif
#if ( MUTUAL6_NUM > 51 )
    CTSUSO1_MUTUAL6_KEY51,
#endif
#if ( MUTUAL6_NUM > 52 )
    CTSUSO1_MUTUAL6_KEY52,
#endif
#if ( MUTUAL6_NUM > 53 )
    CTSUSO1_MUTUAL6_KEY53,
#endif
#if ( MUTUAL6_NUM > 54 )
    CTSUSO1_MUTUAL6_KEY54,
#endif
#if ( MUTUAL6_NUM > 55 )
    CTSUSO1_MUTUAL6_KEY55,
#endif
#if ( MUTUAL6_NUM > 56 )
    CTSUSO1_MUTUAL6_KEY56,
#endif
#if ( MUTUAL6_NUM > 57 )
    CTSUSO1_MUTUAL6_KEY57,
#endif
#if ( MUTUAL6_NUM > 58 )
    CTSUSO1_MUTUAL6_KEY58,
#endif
#if ( MUTUAL6_NUM > 59 )
    CTSUSO1_MUTUAL6_KEY59,
#endif
#if ( MUTUAL6_NUM > 60 )
    CTSUSO1_MUTUAL6_KEY60,
#endif
#if ( MUTUAL6_NUM > 61 )
    CTSUSO1_MUTUAL6_KEY61,
#endif
#if ( MUTUAL6_NUM > 62 )
    CTSUSO1_MUTUAL6_KEY62,
#endif
#if ( MUTUAL6_NUM > 63 )
    CTSUSO1_MUTUAL6_KEY63,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 6 )

/*=====    Mutual 7    DTC transmit data ========================================================*/
#if ( MUTUAL_METHOD_NUM > 7 )
const uint16_t g_mutual7_ctsussc[] =
{
#if ( MUTUAL7_NUM > 0 )
    CTSUSSC_MUTUAL7_KEY00,
#endif
#if ( MUTUAL7_NUM > 1 )
    CTSUSSC_MUTUAL7_KEY01,
#endif
#if ( MUTUAL7_NUM > 2 )
    CTSUSSC_MUTUAL7_KEY02,
#endif
#if ( MUTUAL7_NUM > 3 )
    CTSUSSC_MUTUAL7_KEY03,
#endif
#if ( MUTUAL7_NUM > 4 )
    CTSUSSC_MUTUAL7_KEY04,
#endif
#if ( MUTUAL7_NUM > 5 )
    CTSUSSC_MUTUAL7_KEY05,
#endif
#if ( MUTUAL7_NUM > 6 )
    CTSUSSC_MUTUAL7_KEY06,
#endif
#if ( MUTUAL7_NUM > 7 )
    CTSUSSC_MUTUAL7_KEY07,
#endif
#if ( MUTUAL7_NUM > 8 )
    CTSUSSC_MUTUAL7_KEY08,
#endif
#if ( MUTUAL7_NUM > 9 )
    CTSUSSC_MUTUAL7_KEY09,
#endif
#if ( MUTUAL7_NUM > 10 )
    CTSUSSC_MUTUAL7_KEY10,
#endif
#if ( MUTUAL7_NUM > 11 )
    CTSUSSC_MUTUAL7_KEY11,
#endif
#if ( MUTUAL7_NUM > 12 )
    CTSUSSC_MUTUAL7_KEY12,
#endif
#if ( MUTUAL7_NUM > 13 )
    CTSUSSC_MUTUAL7_KEY13,
#endif
#if ( MUTUAL7_NUM > 14 )
    CTSUSSC_MUTUAL7_KEY14,
#endif
#if ( MUTUAL7_NUM > 15 )
    CTSUSSC_MUTUAL7_KEY15,
#endif
#if ( MUTUAL7_NUM > 16 )
    CTSUSSC_MUTUAL7_KEY16,
#endif
#if ( MUTUAL7_NUM > 17 )
    CTSUSSC_MUTUAL7_KEY17,
#endif
#if ( MUTUAL7_NUM > 18 )
    CTSUSSC_MUTUAL7_KEY18,
#endif
#if ( MUTUAL7_NUM > 19 )
    CTSUSSC_MUTUAL7_KEY19,
#endif
#if ( MUTUAL7_NUM > 20 )
    CTSUSSC_MUTUAL7_KEY20,
#endif
#if ( MUTUAL7_NUM > 21 )
    CTSUSSC_MUTUAL7_KEY21,
#endif
#if ( MUTUAL7_NUM > 22 )
    CTSUSSC_MUTUAL7_KEY22,
#endif
#if ( MUTUAL7_NUM > 23 )
    CTSUSSC_MUTUAL7_KEY23,
#endif
#if ( MUTUAL7_NUM > 24 )
    CTSUSSC_MUTUAL7_KEY24,
#endif
#if ( MUTUAL7_NUM > 25 )
    CTSUSSC_MUTUAL7_KEY25,
#endif
#if ( MUTUAL7_NUM > 26 )
    CTSUSSC_MUTUAL7_KEY26,
#endif
#if ( MUTUAL7_NUM > 27 )
    CTSUSSC_MUTUAL7_KEY27,
#endif
#if ( MUTUAL7_NUM > 28 )
    CTSUSSC_MUTUAL7_KEY28,
#endif
#if ( MUTUAL7_NUM > 29 )
    CTSUSSC_MUTUAL7_KEY29,
#endif
#if ( MUTUAL7_NUM > 30 )
    CTSUSSC_MUTUAL7_KEY30,
#endif
#if ( MUTUAL7_NUM > 31 )
    CTSUSSC_MUTUAL7_KEY31,
#endif
#if ( MUTUAL7_NUM > 32 )
    CTSUSSC_MUTUAL7_KEY32,
#endif
#if ( MUTUAL7_NUM > 33 )
    CTSUSSC_MUTUAL7_KEY33,
#endif
#if ( MUTUAL7_NUM > 34 )
    CTSUSSC_MUTUAL7_KEY34,
#endif
#if ( MUTUAL7_NUM > 35 )
    CTSUSSC_MUTUAL7_KEY35,
#endif
#if ( MUTUAL7_NUM > 36 )
    CTSUSSC_MUTUAL7_KEY36,
#endif
#if ( MUTUAL7_NUM > 37 )
    CTSUSSC_MUTUAL7_KEY37,
#endif
#if ( MUTUAL7_NUM > 38 )
    CTSUSSC_MUTUAL7_KEY38,
#endif
#if ( MUTUAL7_NUM > 39 )
    CTSUSSC_MUTUAL7_KEY39,
#endif
#if ( MUTUAL7_NUM > 40 )
    CTSUSSC_MUTUAL7_KEY40,
#endif
#if ( MUTUAL7_NUM > 41 )
    CTSUSSC_MUTUAL7_KEY41,
#endif
#if ( MUTUAL7_NUM > 42 )
    CTSUSSC_MUTUAL7_KEY42,
#endif
#if ( MUTUAL7_NUM > 43 )
    CTSUSSC_MUTUAL7_KEY43,
#endif
#if ( MUTUAL7_NUM > 44 )
    CTSUSSC_MUTUAL7_KEY44,
#endif
#if ( MUTUAL7_NUM > 45 )
    CTSUSSC_MUTUAL7_KEY45,
#endif
#if ( MUTUAL7_NUM > 46 )
    CTSUSSC_MUTUAL7_KEY46,
#endif
#if ( MUTUAL7_NUM > 47 )
    CTSUSSC_MUTUAL7_KEY47,
#endif
#if ( MUTUAL7_NUM > 48 )
    CTSUSSC_MUTUAL7_KEY48,
#endif
#if ( MUTUAL7_NUM > 49 )
    CTSUSSC_MUTUAL7_KEY49,
#endif
#if ( MUTUAL7_NUM > 50 )
    CTSUSSC_MUTUAL7_KEY50,
#endif
#if ( MUTUAL7_NUM > 51 )
    CTSUSSC_MUTUAL7_KEY51,
#endif
#if ( MUTUAL7_NUM > 52 )
    CTSUSSC_MUTUAL7_KEY52,
#endif
#if ( MUTUAL7_NUM > 53 )
    CTSUSSC_MUTUAL7_KEY53,
#endif
#if ( MUTUAL7_NUM > 54 )
    CTSUSSC_MUTUAL7_KEY54,
#endif
#if ( MUTUAL7_NUM > 55 )
    CTSUSSC_MUTUAL7_KEY55,
#endif
#if ( MUTUAL7_NUM > 56 )
    CTSUSSC_MUTUAL7_KEY56,
#endif
#if ( MUTUAL7_NUM > 57 )
    CTSUSSC_MUTUAL7_KEY57,
#endif
#if ( MUTUAL7_NUM > 58 )
    CTSUSSC_MUTUAL7_KEY58,
#endif
#if ( MUTUAL7_NUM > 59 )
    CTSUSSC_MUTUAL7_KEY59,
#endif
#if ( MUTUAL7_NUM > 60 )
    CTSUSSC_MUTUAL7_KEY60,
#endif
#if ( MUTUAL7_NUM > 61 )
    CTSUSSC_MUTUAL7_KEY61,
#endif
#if ( MUTUAL7_NUM > 62 )
    CTSUSSC_MUTUAL7_KEY62,
#endif
#if ( MUTUAL7_NUM > 63 )
    CTSUSSC_MUTUAL7_KEY63,
#endif
};

const uint16_t g_mutual7_ctsuso0[] =
{
#if ( MUTUAL7_NUM > 0 )
    CTSUSO0_MUTUAL7_KEY00,
#endif
#if ( MUTUAL7_NUM > 1 )
    CTSUSO0_MUTUAL7_KEY01,
#endif
#if ( MUTUAL7_NUM > 2 )
    CTSUSO0_MUTUAL7_KEY02,
#endif
#if ( MUTUAL7_NUM > 3 )
    CTSUSO0_MUTUAL7_KEY03,
#endif
#if ( MUTUAL7_NUM > 4 )
    CTSUSO0_MUTUAL7_KEY04,
#endif
#if ( MUTUAL7_NUM > 5 )
    CTSUSO0_MUTUAL7_KEY05,
#endif
#if ( MUTUAL7_NUM > 6 )
    CTSUSO0_MUTUAL7_KEY06,
#endif
#if ( MUTUAL7_NUM > 7 )
    CTSUSO0_MUTUAL7_KEY07,
#endif
#if ( MUTUAL7_NUM > 8 )
    CTSUSO0_MUTUAL7_KEY08,
#endif
#if ( MUTUAL7_NUM > 9 )
    CTSUSO0_MUTUAL7_KEY09,
#endif
#if ( MUTUAL7_NUM > 10 )
    CTSUSO0_MUTUAL7_KEY10,
#endif
#if ( MUTUAL7_NUM > 11 )
    CTSUSO0_MUTUAL7_KEY11,
#endif
#if ( MUTUAL7_NUM > 12 )
    CTSUSO0_MUTUAL7_KEY12,
#endif
#if ( MUTUAL7_NUM > 13 )
    CTSUSO0_MUTUAL7_KEY13,
#endif
#if ( MUTUAL7_NUM > 14 )
    CTSUSO0_MUTUAL7_KEY14,
#endif
#if ( MUTUAL7_NUM > 15 )
    CTSUSO0_MUTUAL7_KEY15,
#endif
#if ( MUTUAL7_NUM > 16 )
    CTSUSO0_MUTUAL7_KEY16,
#endif
#if ( MUTUAL7_NUM > 17 )
    CTSUSO0_MUTUAL7_KEY17,
#endif
#if ( MUTUAL7_NUM > 18 )
    CTSUSO0_MUTUAL7_KEY18,
#endif
#if ( MUTUAL7_NUM > 19 )
    CTSUSO0_MUTUAL7_KEY19,
#endif
#if ( MUTUAL7_NUM > 20 )
    CTSUSO0_MUTUAL7_KEY20,
#endif
#if ( MUTUAL7_NUM > 21 )
    CTSUSO0_MUTUAL7_KEY21,
#endif
#if ( MUTUAL7_NUM > 22 )
    CTSUSO0_MUTUAL7_KEY22,
#endif
#if ( MUTUAL7_NUM > 23 )
    CTSUSO0_MUTUAL7_KEY23,
#endif
#if ( MUTUAL7_NUM > 24 )
    CTSUSO0_MUTUAL7_KEY24,
#endif
#if ( MUTUAL7_NUM > 25 )
    CTSUSO0_MUTUAL7_KEY25,
#endif
#if ( MUTUAL7_NUM > 26 )
    CTSUSO0_MUTUAL7_KEY26,
#endif
#if ( MUTUAL7_NUM > 27 )
    CTSUSO0_MUTUAL7_KEY27,
#endif
#if ( MUTUAL7_NUM > 28 )
    CTSUSO0_MUTUAL7_KEY28,
#endif
#if ( MUTUAL7_NUM > 29 )
    CTSUSO0_MUTUAL7_KEY29,
#endif
#if ( MUTUAL7_NUM > 30 )
    CTSUSO0_MUTUAL7_KEY30,
#endif
#if ( MUTUAL7_NUM > 31 )
    CTSUSO0_MUTUAL7_KEY31,
#endif
#if ( MUTUAL7_NUM > 32 )
    CTSUSO0_MUTUAL7_KEY32,
#endif
#if ( MUTUAL7_NUM > 33 )
    CTSUSO0_MUTUAL7_KEY33,
#endif
#if ( MUTUAL7_NUM > 34 )
    CTSUSO0_MUTUAL7_KEY34,
#endif
#if ( MUTUAL7_NUM > 35 )
    CTSUSO0_MUTUAL7_KEY35,
#endif
#if ( MUTUAL7_NUM > 36 )
    CTSUSO0_MUTUAL7_KEY36,
#endif
#if ( MUTUAL7_NUM > 37 )
    CTSUSO0_MUTUAL7_KEY37,
#endif
#if ( MUTUAL7_NUM > 38 )
    CTSUSO0_MUTUAL7_KEY38,
#endif
#if ( MUTUAL7_NUM > 39 )
    CTSUSO0_MUTUAL7_KEY39,
#endif
#if ( MUTUAL7_NUM > 40 )
    CTSUSO0_MUTUAL7_KEY40,
#endif
#if ( MUTUAL7_NUM > 41 )
    CTSUSO0_MUTUAL7_KEY41,
#endif
#if ( MUTUAL7_NUM > 42 )
    CTSUSO0_MUTUAL7_KEY42,
#endif
#if ( MUTUAL7_NUM > 43 )
    CTSUSO0_MUTUAL7_KEY43,
#endif
#if ( MUTUAL7_NUM > 44 )
    CTSUSO0_MUTUAL7_KEY44,
#endif
#if ( MUTUAL7_NUM > 45 )
    CTSUSO0_MUTUAL7_KEY45,
#endif
#if ( MUTUAL7_NUM > 46 )
    CTSUSO0_MUTUAL7_KEY46,
#endif
#if ( MUTUAL7_NUM > 47 )
    CTSUSO0_MUTUAL7_KEY47,
#endif
#if ( MUTUAL7_NUM > 48 )
    CTSUSO0_MUTUAL7_KEY48,
#endif
#if ( MUTUAL7_NUM > 49 )
    CTSUSO0_MUTUAL7_KEY49,
#endif
#if ( MUTUAL7_NUM > 50 )
    CTSUSO0_MUTUAL7_KEY50,
#endif
#if ( MUTUAL7_NUM > 51 )
    CTSUSO0_MUTUAL7_KEY51,
#endif
#if ( MUTUAL7_NUM > 52 )
    CTSUSO0_MUTUAL7_KEY52,
#endif
#if ( MUTUAL7_NUM > 53 )
    CTSUSO0_MUTUAL7_KEY53,
#endif
#if ( MUTUAL7_NUM > 54 )
    CTSUSO0_MUTUAL7_KEY54,
#endif
#if ( MUTUAL7_NUM > 55 )
    CTSUSO0_MUTUAL7_KEY55,
#endif
#if ( MUTUAL7_NUM > 56 )
    CTSUSO0_MUTUAL7_KEY56,
#endif
#if ( MUTUAL7_NUM > 57 )
    CTSUSO0_MUTUAL7_KEY57,
#endif
#if ( MUTUAL7_NUM > 58 )
    CTSUSO0_MUTUAL7_KEY58,
#endif
#if ( MUTUAL7_NUM > 59 )
    CTSUSO0_MUTUAL7_KEY59,
#endif
#if ( MUTUAL7_NUM > 60 )
    CTSUSO0_MUTUAL7_KEY60,
#endif
#if ( MUTUAL7_NUM > 61 )
    CTSUSO0_MUTUAL7_KEY61,
#endif
#if ( MUTUAL7_NUM > 62 )
    CTSUSO0_MUTUAL7_KEY62,
#endif
#if ( MUTUAL7_NUM > 63 )
    CTSUSO0_MUTUAL7_KEY63,
#endif
};

const uint16_t g_mutual7_ctsuso1[] =
{
#if ( MUTUAL7_NUM > 0 )
    CTSUSO1_MUTUAL7_KEY00,
#endif
#if ( MUTUAL7_NUM > 1 )
    CTSUSO1_MUTUAL7_KEY01,
#endif
#if ( MUTUAL7_NUM > 2 )
    CTSUSO1_MUTUAL7_KEY02,
#endif
#if ( MUTUAL7_NUM > 3 )
    CTSUSO1_MUTUAL7_KEY03,
#endif
#if ( MUTUAL7_NUM > 4 )
    CTSUSO1_MUTUAL7_KEY04,
#endif
#if ( MUTUAL7_NUM > 5 )
    CTSUSO1_MUTUAL7_KEY05,
#endif
#if ( MUTUAL7_NUM > 6 )
    CTSUSO1_MUTUAL7_KEY06,
#endif
#if ( MUTUAL7_NUM > 7 )
    CTSUSO1_MUTUAL7_KEY07,
#endif
#if ( MUTUAL7_NUM > 8 )
    CTSUSO1_MUTUAL7_KEY08,
#endif
#if ( MUTUAL7_NUM > 9 )
    CTSUSO1_MUTUAL7_KEY09,
#endif
#if ( MUTUAL7_NUM > 10 )
    CTSUSO1_MUTUAL7_KEY10,
#endif
#if ( MUTUAL7_NUM > 11 )
    CTSUSO1_MUTUAL7_KEY11,
#endif
#if ( MUTUAL7_NUM > 12 )
    CTSUSO1_MUTUAL7_KEY12,
#endif
#if ( MUTUAL7_NUM > 13 )
    CTSUSO1_MUTUAL7_KEY13,
#endif
#if ( MUTUAL7_NUM > 14 )
    CTSUSO1_MUTUAL7_KEY14,
#endif
#if ( MUTUAL7_NUM > 15 )
    CTSUSO1_MUTUAL7_KEY15,
#endif
#if ( MUTUAL7_NUM > 16 )
    CTSUSO1_MUTUAL7_KEY16,
#endif
#if ( MUTUAL7_NUM > 17 )
    CTSUSO1_MUTUAL7_KEY17,
#endif
#if ( MUTUAL7_NUM > 18 )
    CTSUSO1_MUTUAL7_KEY18,
#endif
#if ( MUTUAL7_NUM > 19 )
    CTSUSO1_MUTUAL7_KEY19,
#endif
#if ( MUTUAL7_NUM > 20 )
    CTSUSO1_MUTUAL7_KEY20,
#endif
#if ( MUTUAL7_NUM > 21 )
    CTSUSO1_MUTUAL7_KEY21,
#endif
#if ( MUTUAL7_NUM > 22 )
    CTSUSO1_MUTUAL7_KEY22,
#endif
#if ( MUTUAL7_NUM > 23 )
    CTSUSO1_MUTUAL7_KEY23,
#endif
#if ( MUTUAL7_NUM > 24 )
    CTSUSO1_MUTUAL7_KEY24,
#endif
#if ( MUTUAL7_NUM > 25 )
    CTSUSO1_MUTUAL7_KEY25,
#endif
#if ( MUTUAL7_NUM > 26 )
    CTSUSO1_MUTUAL7_KEY26,
#endif
#if ( MUTUAL7_NUM > 27 )
    CTSUSO1_MUTUAL7_KEY27,
#endif
#if ( MUTUAL7_NUM > 28 )
    CTSUSO1_MUTUAL7_KEY28,
#endif
#if ( MUTUAL7_NUM > 29 )
    CTSUSO1_MUTUAL7_KEY29,
#endif
#if ( MUTUAL7_NUM > 30 )
    CTSUSO1_MUTUAL7_KEY30,
#endif
#if ( MUTUAL7_NUM > 31 )
    CTSUSO1_MUTUAL7_KEY31,
#endif
#if ( MUTUAL7_NUM > 32 )
    CTSUSO1_MUTUAL7_KEY32,
#endif
#if ( MUTUAL7_NUM > 33 )
    CTSUSO1_MUTUAL7_KEY33,
#endif
#if ( MUTUAL7_NUM > 34 )
    CTSUSO1_MUTUAL7_KEY34,
#endif
#if ( MUTUAL7_NUM > 35 )
    CTSUSO1_MUTUAL7_KEY35,
#endif
#if ( MUTUAL7_NUM > 36 )
    CTSUSO1_MUTUAL7_KEY36,
#endif
#if ( MUTUAL7_NUM > 37 )
    CTSUSO1_MUTUAL7_KEY37,
#endif
#if ( MUTUAL7_NUM > 38 )
    CTSUSO1_MUTUAL7_KEY38,
#endif
#if ( MUTUAL7_NUM > 39 )
    CTSUSO1_MUTUAL7_KEY39,
#endif
#if ( MUTUAL7_NUM > 40 )
    CTSUSO1_MUTUAL7_KEY40,
#endif
#if ( MUTUAL7_NUM > 41 )
    CTSUSO1_MUTUAL7_KEY41,
#endif
#if ( MUTUAL7_NUM > 42 )
    CTSUSO1_MUTUAL7_KEY42,
#endif
#if ( MUTUAL7_NUM > 43 )
    CTSUSO1_MUTUAL7_KEY43,
#endif
#if ( MUTUAL7_NUM > 44 )
    CTSUSO1_MUTUAL7_KEY44,
#endif
#if ( MUTUAL7_NUM > 45 )
    CTSUSO1_MUTUAL7_KEY45,
#endif
#if ( MUTUAL7_NUM > 46 )
    CTSUSO1_MUTUAL7_KEY46,
#endif
#if ( MUTUAL7_NUM > 47 )
    CTSUSO1_MUTUAL7_KEY47,
#endif
#if ( MUTUAL7_NUM > 48 )
    CTSUSO1_MUTUAL7_KEY48,
#endif
#if ( MUTUAL7_NUM > 49 )
    CTSUSO1_MUTUAL7_KEY49,
#endif
#if ( MUTUAL7_NUM > 50 )
    CTSUSO1_MUTUAL7_KEY50,
#endif
#if ( MUTUAL7_NUM > 51 )
    CTSUSO1_MUTUAL7_KEY51,
#endif
#if ( MUTUAL7_NUM > 52 )
    CTSUSO1_MUTUAL7_KEY52,
#endif
#if ( MUTUAL7_NUM > 53 )
    CTSUSO1_MUTUAL7_KEY53,
#endif
#if ( MUTUAL7_NUM > 54 )
    CTSUSO1_MUTUAL7_KEY54,
#endif
#if ( MUTUAL7_NUM > 55 )
    CTSUSO1_MUTUAL7_KEY55,
#endif
#if ( MUTUAL7_NUM > 56 )
    CTSUSO1_MUTUAL7_KEY56,
#endif
#if ( MUTUAL7_NUM > 57 )
    CTSUSO1_MUTUAL7_KEY57,
#endif
#if ( MUTUAL7_NUM > 58 )
    CTSUSO1_MUTUAL7_KEY58,
#endif
#if ( MUTUAL7_NUM > 59 )
    CTSUSO1_MUTUAL7_KEY59,
#endif
#if ( MUTUAL7_NUM > 60 )
    CTSUSO1_MUTUAL7_KEY60,
#endif
#if ( MUTUAL7_NUM > 61 )
    CTSUSO1_MUTUAL7_KEY61,
#endif
#if ( MUTUAL7_NUM > 62 )
    CTSUSO1_MUTUAL7_KEY62,
#endif
#if ( MUTUAL7_NUM > 63 )
    CTSUSO1_MUTUAL7_KEY63,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 7 )

/***********************************************************************************************************************
* End of File
***********************************************************************************************************************/
