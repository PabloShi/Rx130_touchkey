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
* File Name    : r_touch.c
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file controls touch function.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/
#define __R_TOUCH_C__

/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
/* System include header */
#include "r_cg_macrodriver.h"

/* H/W include header */
#include "r_ctsu.h"

/* S/W include header */
#include "r_cg_userdefine.h"
#include "r_touch.h"
#include "r_touch_API.h"

#include "IEC61000_CTSU.h"

/***********************************************************************************************************************
* Global variables and functions
***********************************************************************************************************************/
#ifdef KEY_USE

/*====================================================================================================================*/
/*=====    Self touch parameter definition    ========================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( SELF_METHOD_NUM == 1 )
    const uint16_t g_self_thrbuff[];
    const uint16_t g_self_hysbuff[];
#endif    // ( SELF_METHOD_NUM == 1 )

#endif    // KEY_USE

/*====================================================================================================================*/
/*=====    Mutual 0 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 0 )
    const uint16_t g_mutual0_thrbuff[];
    const uint16_t g_mutual0_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 0 )

/*====================================================================================================================*/
/*=====    Mutual 1 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 1 )
    const uint16_t g_mutual1_thrbuff[];
    const uint16_t g_mutual1_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 1 )

/*====================================================================================================================*/
/*=====    Mutual 2 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 2 )
    const uint16_t g_mutual2_thrbuff[];
    const uint16_t g_mutual2_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 2 )

/*====================================================================================================================*/
/*=====    Mutual 3 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 3 )
    const uint16_t g_mutual3_thrbuff[];
    const uint16_t g_mutual3_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 3 )

/*====================================================================================================================*/
/*=====    Mutual 4 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 4 )
    const uint16_t g_mutual4_thrbuff[];
    const uint16_t g_mutual4_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 4 )

/*====================================================================================================================*/
/*=====    Mutual 5 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 5 )
    const uint16_t g_mutual5_thrbuff[];
    const uint16_t g_mutual5_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 5 )

/*====================================================================================================================*/
/*=====    Mutual 6 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 6 )
    const uint16_t g_mutual6_thrbuff[];
    const uint16_t g_mutual6_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 6 )

/*====================================================================================================================*/
/*=====    Mutual 7 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 7 )
    const uint16_t g_mutual7_thrbuff[];
    const uint16_t g_mutual7_hysbuff[];
#endif  // ( MUTUAL_METHOD_NUM > 7 )

#if ( SELF_METHOD_NUM >= 1 )
    const uint16_t g_self_group[] = { SELF_KEY_USE_GROUP0, SELF_KEY_USE_GROUP1, SELF_KEY_USE_GROUP2 };
#endif    // ( SELF_METHOD_NUM >= 1 )

#if ( MUTUAL_METHOD_NUM >= 1 )
    const uint16_t g_mutual0_group[] = { MUTUAL0_KEY_USE_GROUP0, MUTUAL0_KEY_USE_GROUP1, MUTUAL0_KEY_USE_GROUP2, MUTUAL0_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 1 )

#if ( MUTUAL_METHOD_NUM >= 2 )
    const uint16_t g_mutual1_group[] = { MUTUAL1_KEY_USE_GROUP0, MUTUAL1_KEY_USE_GROUP1, MUTUAL1_KEY_USE_GROUP2, MUTUAL1_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 2 )

#if ( MUTUAL_METHOD_NUM >= 3 )
    const uint16_t g_mutual2_group[] = { MUTUAL2_KEY_USE_GROUP0, MUTUAL2_KEY_USE_GROUP1, MUTUAL2_KEY_USE_GROUP2, MUTUAL2_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 3 )

#if ( MUTUAL_METHOD_NUM >= 4 )
    const uint16_t g_mutual3_group[] = { MUTUAL3_KEY_USE_GROUP0, MUTUAL3_KEY_USE_GROUP1, MUTUAL3_KEY_USE_GROUP2, MUTUAL3_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 4 )

#if ( MUTUAL_METHOD_NUM >= 5 )
    const uint16_t g_mutual4_group[] = { MUTUAL4_KEY_USE_GROUP0, MUTUAL4_KEY_USE_GROUP1, MUTUAL4_KEY_USE_GROUP2, MUTUAL4_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 5 )

#if ( MUTUAL_METHOD_NUM >= 6 )
    const uint16_t g_mutual5_group[] = { MUTUAL5_KEY_USE_GROUP0, MUTUAL5_KEY_USE_GROUP1, MUTUAL5_KEY_USE_GROUP2, MUTUAL5_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 6 )

#if ( MUTUAL_METHOD_NUM >= 7 )
    const uint16_t g_mutual6_group[] = { MUTUAL6_KEY_USE_GROUP0, MUTUAL6_KEY_USE_GROUP1, MUTUAL6_KEY_USE_GROUP2, MUTUAL6_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 7 )

#if ( MUTUAL_METHOD_NUM >= 8 )
    const uint16_t g_mutual7_group[] = { MUTUAL7_KEY_USE_GROUP0, MUTUAL7_KEY_USE_GROUP1, MUTUAL7_KEY_USE_GROUP2, MUTUAL7_KEY_USE_GROUP3};
#endif    // ( MUTUAL_METHOD_NUM >= 8 )

const uint8_t g_touch_on[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_TOUCH_ON,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_TOUCH_ON
#endif
};

const uint8_t g_touch_off[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_TOUCH_OFF,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_TOUCH_OFF
#endif
};

const uint16_t g_touch_msa[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_MSA,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_MSA
#endif
};

const uint8_t g_touch_drift_enable[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_DRIFT_ENABLE,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_DRIFT_ENABLE
#endif
};

const uint16_t g_touch_drift_freq[] = 
{
#if ( SELF_METHOD_NUM == 1 )
    SELF_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 1 )
    MUTUAL0_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 2 )
    MUTUAL1_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 3 )
    MUTUAL2_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 4 )
    MUTUAL3_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 5 )
    MUTUAL4_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 6 )
    MUTUAL5_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 7 )
    MUTUAL6_DRIFT_FREQUENCY,
#endif
#if ( MUTUAL_METHOD_NUM >= 8 )
    MUTUAL7_DRIFT_FREQUENCY
#endif
};

#ifdef SLIDER_USE
const slider_info_t g_sliderInfoRom[] = {
#if (SLIDER_NUMBER > 0)
    { SLIDER0_00, SLIDER0_01, SLIDER0_02, SLIDER0_03, SLIDER0_04, SLIDER0_05,
      SLIDER0_06, SLIDER0_07, SLIDER0_08, SLIDER0_09,
      SLIDER0_SENSOR_NUMBER, SLIDER0_THRESHOLD, SLIDER0_THR_OFFSET_VAL,
      SLIDER0_RESOLUTION, 0xffff },
#endif
#if (SLIDER_NUMBER > 1)
    { SLIDER1_00, SLIDER1_01, SLIDER1_02, SLIDER1_03, SLIDER1_04, SLIDER1_05,
      SLIDER1_06, SLIDER1_07, SLIDER1_08, SLIDER1_09,
      SLIDER1_SENSOR_NUMBER, SLIDER1_THRESHOLD, SLIDER1_THR_OFFSET_VAL,
      SLIDER1_RESOLUTION, 0xffff },
#endif
#if (SLIDER_NUMBER > 2)
    { SLIDER2_00, SLIDER2_01, SLIDER2_02, SLIDER2_03, SLIDER2_04, SLIDER2_05,
      SLIDER2_06, SLIDER2_07, SLIDER2_08, SLIDER2_09,
      SLIDER2_SENSOR_NUMBER, SLIDER2_THRESHOLD, SLIDER2_THR_OFFSET_VAL,
      SLIDER2_RESOLUTION, 0xffff },
#endif
#if (SLIDER_NUMBER > 3)
    { SLIDER3_00, SLIDER3_01, SLIDER3_02, SLIDER3_03, SLIDER3_04, SLIDER3_05,
      SLIDER3_06, SLIDER3_07, SLIDER3_08, SLIDER3_09,
      SLIDER3_SENSOR_NUMBER, SLIDER3_THRESHOLD, SLIDER3_THR_OFFSET_VAL,
      SLIDER3_RESOLUTION, 0xffff },
#endif
#if (SLIDER_NUMBER > 4)
    { SLIDER4_00, SLIDER4_01, SLIDER4_02, SLIDER4_03, SLIDER4_04, SLIDER4_05,
      SLIDER4_06, SLIDER4_07, SLIDER4_08, SLIDER4_09,
      SLIDER4_SENSOR_NUMBER, SLIDER4_THRESHOLD, SLIDER4_THR_OFFSET_VAL,
      SLIDER4_RESOLUTION, 0xffff },
#endif
#if (SLIDER_NUMBER > 5)
    { SLIDER5_00, SLIDER5_01, SLIDER5_02, SLIDER5_03, SLIDER5_04, SLIDER5_05,
      SLIDER5_06, SLIDER5_07, SLIDER5_08, SLIDER5_09,
      SLIDER5_SENSOR_NUMBER, SLIDER5_THRESHOLD, SLIDER5_THR_OFFSET_VAL,
      SLIDER5_RESOLUTION, 0xffff },
#endif
#if (SLIDER_NUMBER > 6)
    { SLIDER6_00, SLIDER6_01, SLIDER6_02, SLIDER6_03, SLIDER6_04, SLIDER6_05,
      SLIDER6_06, SLIDER6_07, SLIDER6_08, SLIDER6_09,
      SLIDER6_SENSOR_NUMBER, SLIDER6_THRESHOLD, SLIDER6_THR_OFFSET_VAL,
      SLIDER6_RESOLUTION, 0xffff },
#endif
#if (SLIDER_NUMBER > 7)
    { SLIDER7_00, SLIDER7_01, SLIDER7_02, SLIDER7_03, SLIDER7_04, SLIDER7_05,
      SLIDER7_06, SLIDER7_07, SLIDER7_08, SLIDER7_09,
      SLIDER7_SENSOR_NUMBER, SLIDER7_THRESHOLD, SLIDER7_THR_OFFSET_VAL,
      SLIDER7_RESOLUTION, 0xffff },
#endif
};
#endif    //  SLIDER_USE

#ifdef WHEEL_USE
const wheel_info_t g_wheelInfoRom[] = {
#if (WHEEL_NUMBER > 0)
    { WHEEL0_00, WHEEL0_01, WHEEL0_02, WHEEL0_03, WHEEL0_04, WHEEL0_05, WHEEL0_06, WHEEL0_07,
      WHEEL0_SENSOR_NUMBER, WHEEL0_THRESHOLD, WHEEL0_THR_OFFSET_VAL,
      WHEEL0_RESOLUTION, 0xffff },
#endif
#if (WHEEL_NUMBER > 1)
    { WHEEL1_00, WHEEL1_01, WHEEL1_02, WHEEL1_03, WHEEL1_04, WHEEL1_05, WHEEL1_06, WHEEL1_07,
      WHEEL1_SENSOR_NUMBER, WHEEL1_THRESHOLD, WHEEL1_THR_OFFSET_VAL,
      WHEEL1_RESOLUTION, 0xffff },
#endif
#if (WHEEL_NUMBER > 2)
    { WHEEL2_00, WHEEL2_01, WHEEL2_02, WHEEL2_03, WHEEL2_04, WHEEL2_05, WHEEL2_06, WHEEL2_07,
      WHEEL2_SENSOR_NUMBER, WHEEL2_THRESHOLD, WHEEL2_THR_OFFSET_VAL,
      WHEEL2_RESOLUTION, 0xffff },
#endif
#if (WHEEL_NUMBER > 3)
    { WHEEL3_00, WHEEL3_01, WHEEL3_02, WHEEL3_03, WHEEL3_04, WHEEL3_05, WHEEL3_06, WHEEL3_07,
      WHEEL3_SENSOR_NUMBER, WHEEL3_THRESHOLD, WHEEL3_THR_OFFSET_VAL,
      WHEEL3_RESOLUTION, 0xffff },
#endif
#if (WHEEL_NUMBER > 4)
    { WHEEL4_00, WHEEL4_01, WHEEL4_02, WHEEL4_03, WHEEL4_04, WHEEL4_05, WHEEL4_06, WHEEL4_07,
      WHEEL4_SENSOR_NUMBER, WHEEL4_THRESHOLD, WHEEL4_THR_OFFSET_VAL,
      WHEEL4_RESOLUTION, 0xffff },
#endif
#if (WHEEL_NUMBER > 5)
    { WHEEL5_00, WHEEL5_01, WHEEL5_02, WHEEL5_03, WHEEL5_04, WHEEL5_05, WHEEL5_06, WHEEL5_07,
      WHEEL5_SENSOR_NUMBER, WHEEL5_THRESHOLD, WHEEL5_THR_OFFSET_VAL,
      WHEEL5_RESOLUTION, 0xffff },
#endif
#if (WHEEL_NUMBER > 6)
    { WHEEL6_00, WHEEL6_01, WHEEL6_02, WHEEL6_03, WHEEL6_04, WHEEL6_05, WHEEL6_06, WHEEL6_07,
      WHEEL6_SENSOR_NUMBER, WHEEL6_THRESHOLD, WHEEL6_THR_OFFSET_VAL,
      WHEEL6_RESOLUTION, 0xffff },
#endif
#if (WHEEL_NUMBER > 7)
    { WHEEL7_00, WHEEL7_01, WHEEL7_02, WHEEL7_03, WHEEL7_04, WHEEL7_05, WHEEL7_06, WHEEL7_07,
      WHEEL7_SENSOR_NUMBER, WHEEL7_THRESHOLD, WHEEL7_THR_OFFSET_VAL,
      WHEEL7_RESOLUTION, 0xffff },
#endif
};
#endif    // WHEEL_USE

/***********************************************************************************************************************
* Function Name   : touch_parameter_address_set
* Description     : Touch_parameter top address setting
* Arguments       : None
* Return value    : None
***********************************************************************************************************************/
void touch_parameter_address_set( void )
{
    uint8_t num;

    num = 0;

#if ( SELF_METHOD_NUM == 1 )
    g_key_info[num].mode               = 0;                                  /* 0 = Self-measurement                  */
    g_key_info[num].key_num            = SELF_KEY_NUM;                       /* Key function number                   */
    g_key_info[num].ena_num            = SELF_ENABLE_NUM;                    /* Enable pin number                     */
    g_key_info[num].key_max_group      = SELF_MAX_GROUP;                     /* Key group max number                  */
#if ( SELF_KEY_NUM == 0)
#else
    g_key_info[num].ref                = &g_self_ref[0];                     /* Key function's reference value        */
    g_key_info[num].thr                = &g_self_thr[0];                     /* Key function's threshold value        */
    g_key_info[num].user_thr           = &g_self_user_thr[0];                /* User setting threshold                */
    g_key_info[num].hys                = &g_self_hys[0];                     /* Hysteresis value                      */
    g_key_info[num].delta              = &g_self_delta[0];                   /* Amount of touch change                */
    g_key_info[num].touch_cnt          = &g_self_touch_cnt[0];               /* Continuous agreement touch count      */
    g_key_info[num].non_touch_cnt      = &g_self_non_touch_cnt[0];           /* Continuous agreement non-touch count  */
    g_key_info[num].in_touch           = &g_self_in_touch[0];                /* Inside touch/non-touch information    */
    g_key_info[num].out_touch          = &g_self_out_touch[0];               /* Outside touch/non-touch information   */
    g_key_info[num].touch_result       = &g_self_touch_result[0];            /* Touch/non-touch result                */
    g_key_info[num].drift_permission   = &g_self_drift_permission[0];        /* Drift permission                      */
    g_key_info[num].drift_add_ref      = &g_self_drift_ref[0];               /* Drift addition reference value        */
    g_key_info[num].drift_cnt          = &g_self_drift_cnt[0];               /* Drift counter                         */
    g_key_info[num].key_used_info      = &g_self_key_uesd_info[0];           /* Key used bit information              */

    g_key_user_parameter[num].user_thr = &g_self_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_self_hysbuff[0];
    g_touch_key_group[num].group       = &g_self_group[0];

    g_calib_info[num].calib_data       = &g_self_calib[0][0];                /* Calibration data storage buffer       */
#endif    // ( SELF_KEY_NUM == 0)
    g_key_info[num].sensor_index       = &g_self_sensor_index[0];            /* Key index                             */
    g_key_info[num].counter_magni      = &g_self_counter_magni[0];           /* Counter magni                         */

    g_touch_tuning_info[num].ctsuso    = &g_self_tune_ctsuso[0];             /*  */
    g_touch_tuning_info[num].result    = &g_self_tune_result[0];             /*  */

    num  = (uint8_t)(num + 1);
#endif    // ( SELF_METHOD_NUM == 1 )

#if ( MUTUAL_METHOD_NUM >= 1 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL0_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL0_NUM;
    g_key_info[num].key_max_group      = MUTUAL0_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual0_ref[0];
    g_key_info[num].thr                = &g_mutual0_thr[0];
    g_key_info[num].user_thr           = &g_mutual0_user_thr[0];
    g_key_info[num].hys                = &g_mutual0_hys[0];
    g_key_info[num].delta              = &g_mutual0_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual0_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual0_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual0_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual0_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual0_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual0_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual0_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual0_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual0_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual0_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual0_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual0_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual0_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual0_group[0];

    g_calib_info[num].calib_data       = &g_mutual0_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual0_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual0_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 1 )

#if ( MUTUAL_METHOD_NUM >= 2 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL1_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL1_NUM;
    g_key_info[num].key_max_group      = MUTUAL1_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual1_ref[0];
    g_key_info[num].thr                = &g_mutual1_thr[0];
    g_key_info[num].user_thr           = &g_mutual1_user_thr[0];
    g_key_info[num].hys                = &g_mutual1_hys[0];
    g_key_info[num].delta              = &g_mutual1_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual1_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual1_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual1_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual1_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual1_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual1_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual1_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual1_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual1_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual1_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual1_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual1_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual1_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual1_group[0];

    g_calib_info[num].calib_data       = &g_mutual1_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual1_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual1_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 2 )

#if ( MUTUAL_METHOD_NUM >= 3 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL2_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL2_NUM;
    g_key_info[num].key_max_group      = MUTUAL2_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual2_ref[0];
    g_key_info[num].thr                = &g_mutual2_thr[0];
    g_key_info[num].user_thr           = &g_mutual2_user_thr[0];
    g_key_info[num].hys                = &g_mutual2_hys[0];
    g_key_info[num].delta              = &g_mutual2_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual2_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual2_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual2_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual2_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual2_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual2_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual2_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual2_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual2_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual2_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual2_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual2_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual2_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual2_group[0];

    g_calib_info[num].calib_data       = &g_mutual2_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual2_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual2_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 3 )

#if ( MUTUAL_METHOD_NUM >= 4 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL3_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL3_NUM;
    g_key_info[num].key_max_group      = MUTUAL3_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual3_ref[0];
    g_key_info[num].thr                = &g_mutual3_thr[0];
    g_key_info[num].user_thr           = &g_mutual3_user_thr[0];
    g_key_info[num].hys                = &g_mutual3_hys[0];
    g_key_info[num].delta              = &g_mutual3_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual3_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual3_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual3_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual3_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual3_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual3_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual3_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual3_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual3_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual3_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual3_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual3_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual3_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual3_group[0];

    g_calib_info[num].calib_data       = &g_mutual3_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual3_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual3_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 4 )

#if ( MUTUAL_METHOD_NUM >= 5 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL4_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL4_NUM;
    g_key_info[num].key_max_group      = MUTUAL4_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual4_ref[0];
    g_key_info[num].thr                = &g_mutual4_thr[0];
    g_key_info[num].user_thr           = &g_mutual4_user_thr[0];
    g_key_info[num].hys                = &g_mutual4_hys[0];
    g_key_info[num].delta              = &g_mutual4_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual4_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual4_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual4_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual4_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual4_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual4_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual4_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual4_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual4_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual4_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual4_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual4_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual4_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual4_group[0];

    g_calib_info[num].calib_data       = &g_mutual4_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual4_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual4_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 5 )

#if ( MUTUAL_METHOD_NUM >= 6 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL5_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL5_NUM;
    g_key_info[num].key_max_group      = MUTUAL5_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual5_ref[0];
    g_key_info[num].thr                = &g_mutual5_thr[0];
    g_key_info[num].user_thr           = &g_mutual5_user_thr[0];
    g_key_info[num].hys                = &g_mutual5_hys[0];
    g_key_info[num].delta              = &g_mutual5_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual5_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual5_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual5_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual5_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual5_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual5_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual5_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual5_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual5_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual5_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual5_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual5_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual5_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual5_group[0];

    g_calib_info[num].calib_data       = &g_mutual5_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual5_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual5_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 6 )

#if ( MUTUAL_METHOD_NUM >= 7 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL6_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL6_NUM;
    g_key_info[num].key_max_group      = MUTUAL6_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual6_ref[0];
    g_key_info[num].thr                = &g_mutual6_thr[0];
    g_key_info[num].user_thr           = &g_mutual6_user_thr[0];
    g_key_info[num].hys                = &g_mutual6_hys[0];
    g_key_info[num].delta              = &g_mutual6_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual6_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual6_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual6_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual6_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual6_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual6_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual6_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual6_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual6_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual6_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual6_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual6_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual6_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual6_group[0];

    g_calib_info[num].calib_data       = &g_mutual6_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual6_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual6_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 7 )

#if ( MUTUAL_METHOD_NUM >= 8 )
    g_key_info[num].mode               = 1;
    g_key_info[num].key_num            = MUTUAL7_KEY_NUM;
    g_key_info[num].ena_num            = MUTUAL7_NUM;
    g_key_info[num].key_max_group      = MUTUAL7_MAX_GROUP;
    g_key_info[num].ref                = &g_mutual7_ref[0];
    g_key_info[num].thr                = &g_mutual7_thr[0];
    g_key_info[num].user_thr           = &g_mutual7_user_thr[0];
    g_key_info[num].hys                = &g_mutual7_hys[0];
    g_key_info[num].delta              = &g_mutual7_delta[0];
    g_key_info[num].touch_cnt          = &g_mutual7_touch_cnt[0];
    g_key_info[num].non_touch_cnt      = &g_mutual7_non_touch_cnt[0];
    g_key_info[num].in_touch           = &g_mutual7_in_touch[0];
    g_key_info[num].out_touch          = &g_mutual7_out_touch[0];
    g_key_info[num].touch_result       = &g_mutual7_touch_result[0];
    g_key_info[num].drift_permission   = &g_mutual7_drift_permission[0];
    g_key_info[num].drift_add_ref      = &g_mutual7_drift_ref[0];
    g_key_info[num].drift_cnt          = &g_mutual7_drift_cnt[0];
    g_key_info[num].key_used_info      = &g_mutual7_key_uesd_info[0];
    g_key_info[num].sensor_index       = &g_mutual7_sensor_index[0];
    g_key_info[num].counter_magni      = &g_mutual7_counter_magni[0];        /* Counter magni                         */

    g_key_user_parameter[num].user_thr = &g_mutual7_thrbuff[0];
    g_key_user_parameter[num].user_hys = &g_mutual7_hysbuff[0];
    g_touch_key_group[num].group       = &g_mutual7_group[0];

    g_calib_info[num].calib_data       = &g_mutual7_calib[0][0];

    g_touch_tuning_info[num].ctsuso    = &g_mutual7_tune_ctsuso[0];
    g_touch_tuning_info[num].result    = &g_mutual7_tune_result[0];

    num  = (uint8_t)(num + 1);
#endif    // ( MUTUAL_METHOD_NUM >= 8 )
}    /* End of function touch_parameter_address_set() */

/***********************************************************************************************************************
* Function Name: touch_parameter_set
* Description  : Touch parameter setting
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void touch_parameter_set( void )
{
    uint8_t     method;
    uint8_t     pt;
    uint8_t     loop;
#if (defined(SLIDER_USE) || defined(WHEEL_USE))
    uint8_t     id;
    uint8_t     ts_num;
#endif  // (defined(SLIDER_USE) || defined(WHEEL_USE))

    /* Touch system flag initial */
    g_touch_system.value = 0x00;

    for (method = 0; method < METHOD_NUM; method++)
    {
        /**************************************************************************************************************/
        /*****     Touch function parameter setting     ***************************************************************/
        /**************************************************************************************************************/
        g_touch_paramter[method].calib_key_num     = 0;

        /* Compulsion touch cancellation frequency setting    */
        g_touch_paramter[method].msa_freq          = g_touch_msa[method];

        /* Continuous agreement touch comparison frequency setting    */
        g_touch_paramter[method].touch_freq        = g_touch_on[method];

        /* Continuous agreement non-touch comparison frequency setting    */
        g_touch_paramter[method].not_touch_freq    = g_touch_off[method];

        /* Drift correction frequency setting    */
        g_touch_paramter[method].drift_freq        = g_touch_drift_freq[method];

        /**************************************************************************************************************/
        /*****     Touch function flag setting          ***************************************************************/
        /**************************************************************************************************************/
        g_touch_function[method].value             = 0x00;         /* Touch function flag initial                     */

        if (g_touch_paramter[method].msa_freq)
        {
            g_touch_function[method].flag.msa      = ON;           /* Compulsion touch cancellation function enable   */
        }

        if (g_touch_paramter[method].touch_freq)
        {
            g_touch_function[method].flag.acd0     = ON;           /* Continuous touch comparison function enable     */
        }

        if (g_touch_paramter[method].not_touch_freq)
        {
            g_touch_function[method].flag.acd1     = ON;           /* Continuous non-touch comparison function enable */
        }

        if (1 == g_touch_drift_enable[method])
        {
            g_touch_function[method].flag.drift    = ON;           /* Drift correction function enabule               */
        }
        else
        {
            g_touch_function[method].flag.drift    = OFF;
        }

#ifdef KEY_USE
        if (0 == g_key_info[method].mode)
        {
            if (0 == g_key_info[method].key_num)
            {
                g_touch_function[method].flag.calib    = OFF;      /* Calibration function disable                    */
            }
            else
            {
                g_touch_function[method].flag.calib    = ON;       /* Calibration function enable                     */
            }
        }
        else
        {
            g_touch_function[method].flag.calib        = ON;       /* Calibration function enable                     */
        }
        g_calib_info[method].calib_key                 = 0;
        g_calib_info[method].calib_cnt                 = 0;
#else
        g_touch_function[method].flag.calib            = OFF;      /* Calibration function disable                    */
#endif    // KEY_USE

        /**************************************************************************************************************/
        /*****     Threshold and Hysteresis setting     ***************************************************************/
        /**************************************************************************************************************/
#ifdef KEY_USE
        for (pt = 0; pt < g_key_info[method].key_num; pt++)
        {
             *(g_key_info[method].user_thr + pt)   = *(g_key_user_parameter[method].user_thr + pt);
             *(g_key_info[method].hys      + pt)   = *(g_key_user_parameter[method].user_hys + pt);
        }

        /**************************************************************************************************************/
        /*****     Touch parameter iniital setting     ****************************************************************/
        /**************************************************************************************************************/
        for (pt = 0; pt < g_key_info[method].key_max_group; pt++)
        {
             *(g_key_info[method].in_touch         + pt) = 0x0000;
             *(g_key_info[method].out_touch        + pt) = 0x0000;
             *(g_key_info[method].touch_result     + pt) = 0x0000;
             *(g_key_info[method].drift_permission + pt) = 0xFFFF;
             *(g_key_info[method].key_used_info    + pt) = *(g_touch_key_group[method].group + pt);
             *(g_touch_tuning_info[method].result  + pt) = 0;
        }
#endif    // KEY_USE

        for (pt = 0; pt < g_key_info[method].ena_num; pt++)
        {
             *(g_touch_tuning_info[method].result  + pt) = 0;
        }

        g_touch_all_result[method].button[0] = 0x0000;
        g_touch_all_result[method].button[1] = 0x0000;
        g_touch_all_result[method].button[2] = 0x0000;
        g_touch_all_result[method].matrix[0] = 0x0000;
        g_touch_all_result[method].matrix[1] = 0x0000;
        g_touch_all_result[method].matrix[2] = 0x0000;
        g_touch_all_result[method].matrix[3] = 0x0000;

        if (0 == g_key_info[method].mode)
        {
            if (0 == SLIDER_NUMBER)
            {
                g_touch_all_result[method].slider[0] = 0xFFFF;
            }
            if (0 == WHEEL_NUMBER)
            {
                g_touch_all_result[method].wheel[0] = 0xFFFF;
            }
        }
        else
        {
            g_touch_all_result[method].slider[0] = 0xFFFF;
            g_touch_all_result[method].wheel[0] = 0xFFFF;
        }

        /**************************************************************************************************************/
        /****    Initialize index table for conversion ts-number to SENSOR0_NUM index    ******************************/
        /**************************************************************************************************************/
        touch_sensor_index_set( method );
   }

#ifdef SLIDER_USE
    for (id = 0; id < SLIDER_NUMBER; id++)
    {
        g_touch_all_result[0].slider[id] = 0xFFFF;
        g_sliderInfo[id] = g_sliderInfoRom[id];

        for (ts_num = 0; ts_num < g_sliderInfo[id].num; ts_num++)
        {
            g_slider_index[id].data_num[ts_num] = g_self_sensor_index[g_sliderInfo[id].ts[ts_num]];
        }
    }
#endif    // SLIDER_USE

#ifdef WHEEL_USE
    for (id = 0; id < WHEEL_NUMBER; id++)
    {
        g_touch_all_result[0].wheel[id] = 0xFFFF;
        g_wheelInfo[id] = g_wheelInfoRom[id];

        for (ts_num = 0; ts_num < g_wheelInfo[id].num; ts_num++)
        {
            g_wheel_index[id].data_num[ts_num] = g_self_sensor_index[g_wheelInfo[id].ts[ts_num]];
        }
    }
#endif

    for (loop = 0; loop < METHOD_NUM; loop++)
    {
        g_offset_time[loop]          = 10;
        g_current_offset_count[loop] = 0;
    }
}    /* End of function touch_parameter_set() */

/***********************************************************************************************************************
* Function Name: touch_sensor_index_set
* Description  : 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void touch_sensor_index_set( uint8_t method )
{
    uint16_t    chac_stor;
    uint8_t     loop;
    uint8_t     pt;
    uint8_t     cmp_key[3];
    uint8_t     key_num;
    uint8_t     used_key;

    chac_stor  = g_ctsu_parameter[method].ctsu_chac01;

    if (0 == g_key_info[method].mode )
    {
        used_key = 0;
        pt = 0;

        if (32 < MAX_TS)
        {
#if (MAX_TS > 32)
            cmp_key[0] = 16;
            cmp_key[1] = 16;
            cmp_key[2] = MAX_TS - 32;
#endif
        }
        else if (16 < MAX_TS)
        {
#if (MAX_TS > 16)
            cmp_key[0] = 16;
            cmp_key[1] = MAX_TS - 16;
            cmp_key[2] = 0;
#endif
        }
        else
        {
            cmp_key[0] = MAX_TS;
            cmp_key[1] = 0;
            cmp_key[2] = 0;
        }

        for (loop = 0; loop < 3; loop++)
        {
            for (key_num = 0; key_num < cmp_key[loop]; key_num++)
            {
                if (0 != (chac_stor & (1 << key_num)))
                {
                     *(g_key_info[method].sensor_index + pt) = used_key++;
                }
                else
                {
                     *(g_key_info[method].sensor_index + pt) =  0xFF;
                }
                pt = pt + 1;
            }
            if(0 == loop)
            {
                chac_stor  = g_ctsu_parameter[method].ctsu_chac23;
            }
            else if (1 == loop)
            {
                chac_stor  = g_ctsu_parameter[method].ctsu_chac4;
            }
        }
    }
    else
    {
        for (key_num = 0, used_key = 0; key_num < g_key_info[method].ena_num; key_num++)
        {
            if (16 > key_num)
            {
                if (0 != (*g_key_info[method].key_used_info & (0x0001 << key_num)))
                {
                     *(g_key_info[method].sensor_index + key_num) = used_key++;
                }
                else
                {
                     *(g_key_info[method].sensor_index + key_num) =  0xFF;
                }
            }
            else if (32 > key_num)
            {
                if (0 != (*(g_key_info[method].key_used_info + 1) & (0x0001 << (key_num - 16))))
                {
                     *(g_key_info[method].sensor_index + key_num) = used_key++;
                }
                else
                {
                     *(g_key_info[method].sensor_index + key_num) =  0xFF;
                }
            }
            else if (48 > key_num)
            {
                if (0 != (*(g_key_info[method].key_used_info + 2) & (0x0001 << (key_num - 32))))
                {
                     *(g_key_info[method].sensor_index + key_num) = used_key++;
                }
                else
                {
                     *(g_key_info[method].sensor_index + key_num) =  0xFF;
                }
            }
            else
            {
                if (0 != (*(g_key_info[method].key_used_info + 3) & (0x0001 << (key_num - 48))))
                {
                     *(g_key_info[method].sensor_index + key_num) = used_key++;
                }
                else
                {
                     *(g_key_info[method].sensor_index + key_num) =  0xFF;
                }
            }
        }
    }
}    /* End of function touch_sensor_index_set() */

/***********************************************************************************************************************
* Function Name: touch_calibration_check
* Description  : Key data calibration
* Arguments    : uint8_t method    : Measurement method(0-8)
* Return Value : 
***********************************************************************************************************************/
uint8_t touch_calibration_check( uint8_t method, uint8_t offset_sta )
{
#ifdef KEY_USE
    uint8_t    loop;
    uint8_t    finish;
    uint8_t    calib_status;
#endif    // KEY_USE
    uint8_t    ret_val;

    ret_val = _0_RUN;

#ifdef KEY_USE
    if (_1_FINISH == offset_sta)
    {
        if (1 == g_touch_function[method].flag.average)
        {
            calib_status = touch_calibration( method );

            if (_1_FINISH == calib_status)
            {
                for (loop = 0, finish = 0; loop < METHOD_NUM; loop++)
                {
                    if (0 == g_touch_function[loop].flag.calib)
                    {
                        finish = finish + 1;
                    }
                }
                if (METHOD_NUM == finish)
                {
                    g_touch_system.flag.initial = 1;
                    ret_val = _1_FINISH;
                }
            }
        }
    }
#else
        if (_1_FINISH == offset_sta)
        {
            g_touch_system.flag.initial = 1;
            ret_val = _1_FINISH;
        }
#endif    // KEY_USE

    return ret_val;
}

#ifdef KEY_USE
/***********************************************************************************************************************
* Function Name: touch_calibration
* Description  : Key data calibration
* Arguments    : uint8_t method    : Measurement method(0-8)
* Return Value : uint8_t status    : CALIB_RUN    : 0
*              :                   : CALIB_FINISH : 1
***********************************************************************************************************************/
uint8_t touch_calibration( uint8_t method )
{
    uint8_t loop;
    uint8_t status;

    status = _0_RUN;

    while (1 == g_touch_function[method].flag.calib)
    {
        if (0 == g_key_info[method].mode)                    /* Mode = Self */
        {
            for (loop = 0; loop < MAX_TS; loop++)
            {
                if (KEY_ENABLE == touch_key_function_check( method, loop ))
                {
                    touch_initial_reference_set( method, loop );
                }
            }
        }
        else
        {
            for (loop = 0; loop < g_key_info[method].ena_num; loop++)
            {
                if (KEY_ENABLE == touch_key_function_check( method, loop ))
                {
                    touch_initial_reference_set( method, loop );
                }
            }
        }

        if (0 == g_touch_function[method].flag.calib)
        {
            g_calib_info[method].calib_cnt = 0;
            status       = _1_FINISH;
        }
        else
        {
            g_calib_info[method].calib_key = 0;
            g_calib_info[method].calib_cnt = (uint8_t)(g_calib_info[method].calib_cnt + 1);
        }
    }

    return status;
}    /* End of function touch_calibration() */

/***********************************************************************************************************************
* Function Name: touch_initial_reference_set
* Description  : Reference value setting
* Arguments    : uint8_t method    : Measurement method(0-8)
*              : uint8_t number    : Key number
* Return Value : none
***********************************************************************************************************************/
void touch_initial_reference_set( uint8_t method, uint8_t number )
{
    uint8_t     loop;
    uint8_t     loop_max;
    uint8_t     key_pt;
    uint8_t     cnt_pt;
    uint8_t     offset;
    uint8_t     max_num;
    uint32_t    work_buff[6];

    offset = 0;

    if (0 == g_calib_info[method].calib_key )
    {
        key_pt = 0;
    }
    else
    {
        key_pt = 4 * g_calib_info[method].calib_key;
    }

    if (0 == g_calib_info[method].calib_cnt )
    {
        cnt_pt = 0;
    }
    else
    {
        cnt_pt = g_calib_info[method].calib_cnt;
    }

    if (CALIB_TIME != g_calib_info[method].calib_cnt)
    {
        if (0 == g_key_info[method].mode)
        {
             *(g_calib_info[method].calib_data + key_pt + cnt_pt) = *(g_self_sensor_cnt_pt[method] + (*(g_key_info[method].sensor_index + number)));
        }
        else
        {
             *(g_calib_info[method].calib_data + key_pt + cnt_pt) = *(g_mutual_sensor_diff_pt[method] + number);
        }
        g_calib_info[method].calib_key = (uint8_t)(g_calib_info[method].calib_key + 1);
        return;
    }

    for (loop = 0; loop < g_key_info[method].key_num; loop++)
    {
        work_buff[0] = (uint32_t)(*(g_calib_info[method].calib_data + offset    ) + *(g_calib_info[method].calib_data + offset + 1));    /* buff0 + buff1 */
        work_buff[1] = (uint32_t)(*(g_calib_info[method].calib_data + offset    ) + *(g_calib_info[method].calib_data + offset + 2));    /* buff0 + buff2 */
        work_buff[2] = (uint32_t)(*(g_calib_info[method].calib_data + offset    ) + *(g_calib_info[method].calib_data + offset + 3));    /* buff0 + buff3 */
        work_buff[3] = (uint32_t)(*(g_calib_info[method].calib_data + offset + 1) + *(g_calib_info[method].calib_data + offset + 2));    /* buff1 + buff2 */
        work_buff[4] = (uint32_t)(*(g_calib_info[method].calib_data + offset + 1) + *(g_calib_info[method].calib_data + offset + 3));    /* buff1 + buff3 */
        work_buff[5] = (uint32_t)(*(g_calib_info[method].calib_data + offset + 2) + *(g_calib_info[method].calib_data + offset + 3));    /* buff2 + buff3 */

        for (loop_max = 0, max_num = 0; loop_max < 5; loop_max++)
        {
            if (work_buff[max_num] < work_buff[loop_max + 1])
            {
                max_num = (uint8_t)(loop_max + 1);
            }
        }
         *(g_key_info[method].ref + loop) = (uint16_t)(work_buff[max_num] / 2);
		 
#ifdef TOUCH_IEC61000
        Filter_ref[loop] = *(g_key_info[method].ref + loop);
#endif //TOUCH_IEC61000

        offset = offset + 4;
    }
    g_touch_function[method].flag.calib = 0;
}    /* End of function touch_initial_reference_set() */

#endif    // KEY_USE

/***********************************************************************************************************************
* Function Name: touch_key_decode
* Description  : Touch Key decoding
* Arguments    : uint8_t  method    : Measurement method(0-8)
*              : uint16_t value     : Sensor data
*              : uint8_t  number    : Key number
* Return Value : None
***********************************************************************************************************************/
void touch_key_decode( uint8_t method, uint16_t value, uint8_t number )
{
    uint8_t    key_id;
    uint8_t    offset;
    uint16_t   sBit;

    touch_judgement_parameter_create( method, value );          /* Make ON/OFFdecision-value */

    if (KEY_GROUP0 > number)
    {
        key_id = 0;
        offset = number;
    }
    else if (KEY_GROUP1 > number)
    {
        key_id = 1;
        offset = (uint8_t)(number - KEY_GROUP0);
    }
    else if (KEY_GROUP2 > number)
    {
        key_id = 2;
        offset = (uint8_t)(number - KEY_GROUP1);
    }
    else if (KEY_GROUP3 > number)
    {
        key_id = 3;
        offset = (uint8_t)(number - KEY_GROUP2);
    }
    else
    {
        return;
    }

    sBit = (uint16_t)(0x0001 << offset);
    if (0x0000 == (*(g_key_info[method].key_used_info + key_id) & sBit))
    {
        return;
    }

    touch_judgement( method, value, key_id, offset );             /* ON/OFF judgement              */
    touch_drift_correction( method, value, key_id, offset);       /* Drift correction              */

    if ((g_key_info[method].key_num - 1) == g_data_tim)
    {
        g_data_tim = 0;
    }
    else
    {
        g_data_tim = (uint8_t)(g_data_tim + 1);
    }
}    /* End of function touch_key_decode() */

/***********************************************************************************************************************
* Function Name: touch_judgement_parameter_create
* Description  : Touch/non-touch judgement parameter creatting function. Create parameters are g_dcount and g_cthr.
* Arguments    : value    Measurement value
* Return Value : None
***********************************************************************************************************************/
void touch_judgement_parameter_create( uint8_t method, uint16_t value )
{
    uint16_t over_cnt;

    if (0 == g_key_info[method].mode)
    {
        if ( *(g_key_info[method].ref  + g_data_tim) < value )
        {
            /* Dcount = g_nref - g_ncount */
             *(g_key_info[method].delta  + g_data_tim) = (uint16_t)(value  - *(g_key_info[method].ref  + g_data_tim));
        }
        else
        {
             *(g_key_info[method].delta  + g_data_tim) = 0;
        }

        over_cnt = (65535 - (*(g_key_info[method].user_thr + g_data_tim)));

        if (over_cnt > *(g_key_info[method].ref  + g_data_tim))
        {
             *(g_key_info[method].thr  + g_data_tim) = (uint16_t)(*(g_key_info[method].ref  + g_data_tim) + *(g_key_info[method].user_thr + g_data_tim));
        }
        else
        {
             *(g_key_info[method].thr  + g_data_tim) = 65535;
        }
    }
    else
    {
        if (*(g_key_info[method].ref  + g_data_tim) > value)
        {
            *(g_key_info[method].delta  + g_data_tim) = (uint16_t)(*(g_key_info[method].ref  + g_data_tim) - value);
        }
        else
        {
             *(g_key_info[method].delta  + g_data_tim) = 0;
        }

        if (*(g_key_info[method].ref  + g_data_tim) > *(g_key_info[method].thr  + g_data_tim))
        {
             *(g_key_info[method].thr  + g_data_tim) = (uint16_t)(*(g_key_info[method].ref  + g_data_tim) - *(g_key_info[method].user_thr + g_data_tim));
        }
        else
        {
             *(g_key_info[method].thr  + g_data_tim) = 0;
        }
    }
}    /* End of function touch_judgement_parameter_create() */

/***********************************************************************************************************************
* Function Name: touch_judgement
* Description  : 
* Arguments    : value    Measurement value
*              : group    Key touch/non-touch data storage buffer ID
*              : offset   Key number offset value
* Return Value : None
***********************************************************************************************************************/
void touch_judgement( uint8_t method, uint16_t value, uint8_t group, uint8_t offset )
{
    uint16_t    sBit;
    uint32_t    ntouch_val;
    uint8_t     freq;

    if (0 == g_key_info[method].mode)                                      /* Self-capacitance measurement            */
    {
        if (*(g_key_info[method].thr + g_data_tim) > *(g_key_info[method].hys + g_data_tim))
        {
            ntouch_val = (uint16_t)((*(g_key_info[method].thr + g_data_tim)) - (*(g_key_info[method].hys + g_data_tim)));
        }
        else
        {
            ntouch_val = *(g_key_info[method].thr + g_data_tim);
        }
    
        sBit = (uint16_t)( 0x0001 << offset );
        if (value > *(g_key_info[method].thr  + g_data_tim))               /* Measurement value > Threshold = Touch   */
        {
             *(g_key_info[method].in_touch + group) |= sBit;               /* Inside touch                            */
        }
        else if (value < ntouch_val )                                    /* Measurement value < Threshold = Non-Touch */
        {
             *(g_key_info[method].in_touch + group) &= (~sBit);            /* Inside non-touch                        */
        }
        else
        {
            /* Do Nothing */
        }
    }
    else                                                                   /* Mutual-capacitance measurement          */
    {
        ntouch_val = (uint32_t)(*(g_key_info[method].thr + g_data_tim)) + (uint32_t)(*(g_key_info[method].hys + g_data_tim));

        sBit = (uint16_t)( 0x0001 << offset );
        if (value < *(g_key_info[method].thr + g_data_tim))                /* Measurement value < Threshold = Touch   */
        {
             *(g_key_info[method].in_touch + group) |= sBit;               /* Inside touch                            */
        }
        else if ((uint32_t)(value) > ntouch_val)                         /* Measurement value > Threshold = Non-Touch */
        {
             *(g_key_info[method].in_touch + group) &= (~sBit);            /* Inside non-touch                        */
        }
        else
        {
            /* Do Nothing */
        }
    }

    if (0 != (*(g_key_info[method].in_touch + group) & sBit))              /* Inside touch flag check                 */
    {
         *(g_key_info[method].non_touch_cnt  + g_data_tim) = 0;            /* Inside non-touch caounter clear         */

        if ( OFF == g_touch_function[method].flag.acd0 )                   /* Total touch function enable flag check  */
        {
            freq = 1;
        }
        else
        {
            freq = g_touch_paramter[method].touch_freq;
        }

        if ((*(g_key_info[method].touch_cnt  + g_data_tim)) == (uint16_t)freq)        /* Outside touch                */
        {
             *(g_key_info[method].out_touch  + group) = (uint16_t)(*(g_key_info[method].out_touch + group) | sBit);    /* Outside touch */
            if (0 != g_touch_paramter[method].msa_freq)
            {
                *(g_key_info[method].touch_cnt  + g_data_tim) = *(g_key_info[method].touch_cnt  + g_data_tim) + 1;     /* Total touch count up */
            }
        }
        else
        {
             *(g_key_info[method].touch_cnt  + g_data_tim) = *(g_key_info[method].touch_cnt  + g_data_tim) + 1;        /* Total touch count up */
        }
    }
    else                                                               /* Outside non-touch                           */
    {
         *(g_key_info[method].touch_cnt  + g_data_tim) = 0;            /* Inside touch caounter clear                 */

        if ( OFF == g_touch_function[method].flag.acd1 )               /* Total non-touch function enable flag check  */
        {
            freq = 1;
        }
        else
        {
            freq = g_touch_paramter[method].not_touch_freq;
        }

        if ((*(g_key_info[method].non_touch_cnt  + g_data_tim)) == (uint16_t)freq)    /* Outside non-touch            */
        {
             *(g_key_info[method].out_touch  + group) = (uint16_t)(*(g_key_info[method].out_touch  + group) & (~sBit));    /* Outside non-touch */
        }
        else
        {
             *(g_key_info[method].non_touch_cnt  + g_data_tim) = *(g_key_info[method].non_touch_cnt  + g_data_tim) + 1;    /* Total non-touch count up */
        }
    }

    /* ===== The reset judgment processing at the time of continuation on ===== */
    if (1 == g_touch_function[method].flag.msa)
    {
        if (0 != g_touch_paramter[method].msa_freq)
        {
            /* If reaching (c_msa(DF_MSA_DATA) + AcdON threshold),
                it makes OnOff judgment result off and it revises a drift. */
            if ((*(g_key_info[method].touch_cnt  + g_data_tim)) == g_touch_paramter[method].msa_freq + (uint16_t)freq)
            {
                /* Real touch and Virtual touch OFF */
                 *(g_key_info[method].out_touch  + group)       &= (~sBit);
                 *(g_key_info[method].in_touch   + group)       &= (~sBit);
                 *(g_key_info[method].touch_cnt  + g_data_tim)   = 0;

                /* parameter reset */
                 *(g_key_info[method].drift_cnt     + g_data_tim)   = 0;
                 *(g_key_info[method].drift_add_ref + g_data_tim)   = 0x00000000ul;
                 *(g_key_info[method].ref           + g_data_tim)   = value;
            }
        }
    }

    /* ===== ONOFF final result ===== */
    if (0 != (*(g_key_info[method].out_touch  + group) & sBit))
    {
         *(g_key_info[method].touch_result + group) |= sBit;
    }
    else
    {
         *(g_key_info[method].touch_result + group) &= (~sBit);
    }
}    /* End of function touch_judgement() */

/***********************************************************************************************************************
* Function Name: touch_drift_correction
* Description  : Drift correction function ( Reference value update )
* Arguments    : value    Measurement value
*              : group    Key touch/non-touch data storage buffer ID
*              : offset   Key number offset value
* Return Value : DRIFT_OK(0)
*              : DRIFT_OFF(2)
***********************************************************************************************************************/
uint8_t touch_drift_correction( uint8_t method, uint16_t value, uint8_t group, uint8_t offset )
{
    uint16_t    sBit;

    /* If the drift processing is a prohibition */
    if (OFF == g_touch_function[method].flag.drift)
    {
        /* There is no processing */
        return DRIFT_OFF;
    }

    sBit = (uint16_t)( 0x0001 << offset );
    /* In case of doing drift correction being and moreover On/Off judgment result 1=OFF */
#ifdef TOUCH_IEC61000
    if ((0x0000ul == (*(g_key_info[method].in_touch   + group) & sBit)) 
			&& (0x0000ul != (*(g_key_info[method].drift_permission + group) & sBit))
			&& Drift_Permission[g_data_tim] == 1)
#else   //TOUCH_IEC61000
    if ((0x0000ul == (*(g_key_info[method].in_touch   + group) & sBit)) 
			&& (0x0000ul != (*(g_key_info[method].drift_permission + group) & sBit))
#endif  //TOUCH_IEC61000
    {
        drift_reset_permission[g_data_tim] = 0;
		/* It is an addition for the drift correction average calculation */
         *(g_key_info[method].drift_add_ref  + g_data_tim) = *(g_key_info[method].drift_add_ref + g_data_tim) + value;
        /* Drift correction counter's being inclement */
         *(g_key_info[method].drift_cnt  + g_data_tim) = (uint16_t)(*(g_key_info[method].drift_cnt  + g_data_tim) + 1);

        if (*(g_key_info[method].drift_cnt  + g_data_tim) <= g_touch_paramter[method].drift_freq)
        {
            /* If reaching the correction number of times */
            if (*(g_key_info[method].drift_cnt  + g_data_tim) == g_touch_paramter[method].drift_freq)
            {
                if (g_touch_paramter[method].drift_freq == 0)
                {
                    g_touch_paramter[method].drift_freq = 1;
                }
                 *(g_key_info[method].ref  + g_data_tim)  = (uint16_t)(*(g_key_info[method].drift_add_ref  + g_data_tim) / g_touch_paramter[method].drift_freq);

                /* To REF of the average */
                 *(g_key_info[method].drift_add_ref  + g_data_tim) = 0x0000000ul;
                /* Work clear */
                 *(g_key_info[method].drift_cnt      + g_data_tim) = 0;
            }
        }
        else
        {
            *(g_key_info[method].drift_add_ref  + g_data_tim) = 0x0000000ul;
            *(g_key_info[method].drift_cnt      + g_data_tim) = 0;
        }
    }
    else
    {
         *(g_key_info[method].drift_add_ref  + g_data_tim) = 0x00000000ul;
         *(g_key_info[method].drift_cnt      + g_data_tim) = 0;

#ifdef TOUCH_IEC61000
		if(Drift_Permission[g_data_tim] == 0)
		{
			drift_reset_permission[g_data_tim]++;
			if(drift_reset_permission[g_data_tim]>300)
			{
				TOUCH_CTSU_Reset();
				drift_reset_permission[g_data_tim] = 0;
			}
		}
#endif  //TOUCH_IEC61000

    }
    return DRIFT_OK;
}

/***********************************************************************************************************************
* Function Name: touch_key_function_check
* Description  : 
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
uint8_t touch_key_function_check( uint8_t method, uint8_t loop )
{
    uint8_t     key_id;
    uint8_t     offset;
    uint16_t    sBit;

    if (KEY_GROUP0 > loop)
    {
        key_id = 0;
        offset = loop;
    }
    else if (KEY_GROUP1 > loop)
    {
        key_id = 1;
        offset = (uint8_t)(loop - KEY_GROUP0);
    }
    else if (KEY_GROUP2 > loop)
    {
        key_id = 2;
        offset = (uint8_t)(loop - KEY_GROUP1);
    }
    else if (KEY_GROUP3 > loop)
    {
        key_id = 3;
        offset = (uint8_t)(loop - KEY_GROUP2);
    }
    else
    {
        return KEY_DISENABLE;
    }

    sBit = (uint16_t)(0x0001 << offset);
    if (0x0000 == (*(g_key_info[method].key_used_info + key_id) & sBit))
    {
        return KEY_DISENABLE;
    }

    return KEY_ENABLE;
}

/***********************************************************************************************************************
* Function Name: offset_tuning_stop_judgement
* Description  : 
* Arguments    : 
* Return Value : 
***********************************************************************************************************************/
uint8_t offset_tuning_stop_judgement( uint8_t method )
{
    uint8_t status;
    uint8_t group;

    status = _1_START;

#ifdef KEY_USE
    if (0 == g_key_info[method].mode)
    {
        if (0 != g_key_info[method].key_num)
        {
            for (group = 0; group < g_key_info[method].key_max_group; group++)
            {
                if (0x0000 !=  *(g_key_info[method].touch_result + group))
                {
                    status = _0_STOP;
                }
            }
        }
    }
    else
    {
        for (group = 0; group < g_key_info[method].key_max_group; group++)
        {
            if (0x0000 !=  *(g_key_info[method].touch_result + group))
            {
                status = _0_STOP;
            }
        }
    }
#endif    // KEY_USE

#ifdef SLIDER_USE
    for (group = 0; group < SLIDER_NUMBER; group++)              /* Slider group loop                                 */
    {
        if (0xFFFF != g_slider_pos[group])                       /* Slider touch check                                */
        {
            status = _0_STOP;                                    /* Internal offset tuning flag stop setting          */
        }
    }
#endif    // SLIDER_USE

#ifdef WHEEL_USE
    for (group = 0; group < WHEEL_NUMBER; group++)               /* Wheel group loop                                  */
    {
        if (0xFFFF != g_wheel_pos[group])                        /* Wheel touch check                                 */
        {
            status = _0_STOP;                                    /* Internal offset tuning flag stop setting          */
        }
    }
#endif    // WHEEL_USE

    return status;
}

#ifdef SLIDER_USE
/***********************************************************************************************************************
* Function Name: slider_decode
* Description  : Slider decode function
* Arguments    : s_id           Slider ID( 0-7 )
* Return Value : slider_rpos    Slider touch position( 65535 = non-touch )
***********************************************************************************************************************/
uint16_t slider_decode( uint8_t s_id )
{
    uint8_t     loop;
    uint8_t     max_num;
    uint8_t     maxch1[3];
    uint16_t    d1,d2,d3;
    uint16_t    slider_vpos;        /* Slider virtual position        */
    uint16_t    slider_rpos;
    uint8_t     resol_num;
    uint16_t    resol_plus;
    uint16_t    resol_minus;

    /* Unstable Correction */
    for (loop = 0, max_num = 0; loop < (g_sliderInfo[s_id].num-1); loop++)
    {
        if (g_slider_data[max_num] < g_slider_data[loop+1])
        {
            max_num = loop + 1;
        }
    }

    /*The maximum ch number to change is put in the array. */
    maxch1[0] = max_num;

    /* Array making for slider operation-------------*/
    /*     |    Maximum change CH_No -----> Array"0"    */
    /*     |    Maximum change CH_No + 1 -> Array"2"    */
    /*     |    Maximum change CH_No - 1 -> Array"1"    */
    if (0u < g_slider_data[maxch1[0]])
    {
        if (0u == maxch1[0])
        {
            maxch1[1] = (uint8_t)(maxch1[0] + 2);
            maxch1[2] = (uint8_t)(maxch1[0] + 1);
        }
        else if (maxch1[0] == (g_sliderInfo[s_id].num - 1))
        {
            maxch1[1] = (uint8_t)(maxch1[0] - 1);
            maxch1[2] = (uint8_t)(maxch1[0] - 2);
        }
        else
        {
            maxch1[1] = (uint8_t)(maxch1[0] - 1);
            maxch1[2] = (uint8_t)(maxch1[0] + 1);
        }

        /* Constant decision for operation of angle of slider */
        /*    Three constant decisions for the operation      */
        /*    Operation of angle of slider                    */
        d1 = g_slider_data[maxch1[0]] - g_slider_data[maxch1[1]];
        d2 = g_slider_data[maxch1[0]] - g_slider_data[maxch1[2]];
        g_slider_dsum[s_id] = (uint16_t)(d1 + d2);

        if(g_slider_dsum[s_id] > g_sliderInfo[s_id].thr_offset)
        {
            g_slider_dsum[s_id] = g_slider_dsum[s_id] - g_sliderInfo[s_id].thr_offset;
        }
        else
        {
            g_slider_dsum[s_id] = 0;
        }

        if (g_slider_dsum[s_id] > g_sliderInfo[s_id].threshold)
        {
            if (ZERO_ENA != slider_decode_abnormal_judgement( s_id, d1, d2, maxch1[0] ))
            {
                 d3          = 100 + ((d2 * 100) / d1);
                 slider_vpos = ((10000 / d3) + (100 * maxch1[0]));

                 resol_num   = (uint8_t)(g_sliderInfo[s_id].num - 1);
                 resol_plus  = (uint16_t)(100 * resol_num);
                 resol_minus = (uint16_t)(50 / g_sliderInfo[s_id].resolution);

                 /* swa = 0 -> Max ------ swa output 1 to Max */
                 slider_rpos = (uint16_t)(slider_vpos / g_sliderInfo[s_id].resolution);
                 if (0 == slider_rpos)
                 {
                     slider_rpos = 1;
                 }
                 else if (slider_rpos >= (resol_plus / g_sliderInfo[s_id].resolution))
                 {
                     slider_rpos = (slider_rpos - (resol_plus / g_sliderInfo[s_id].resolution)) * 2;
                     slider_rpos = slider_rpos + (resol_plus / g_sliderInfo[s_id].resolution);
                     if (slider_rpos > ((100 / g_sliderInfo[s_id].resolution) * g_sliderInfo[s_id].num))
                     {
                         slider_rpos = ((100 / g_sliderInfo[s_id].resolution) * g_sliderInfo[s_id].num);
                     }
                 }
                 else if (slider_rpos <= (100 / g_sliderInfo[s_id].resolution))
                 {
                     if( slider_rpos < resol_minus )
                     {
                        slider_rpos = 1;
                     }
                     else
                     {
                         slider_rpos = slider_rpos - resol_minus;
                         if( slider_rpos == 0 )
                         {
                             slider_rpos = 1;
                         }
                         else
                         {
                             slider_rpos = slider_rpos * 2;
                         }
                     }
                 }
                 else
                 {
                     /* Do Nothing */
                 }
                 g_sliderInfo[s_id].value = slider_rpos;
             }
          }
        else
        {
            g_sliderInfo[s_id].value = 0xFFFFu;
            slider_rpos = 0xFFFFu;
        }
    }
    else
    {
        /* Touch Off Value */
        g_sliderInfo[s_id].value = 0xFFFFu;
        slider_rpos = 0xFFFFu;
    }
    return slider_rpos;
}    /* End of function slider_decode() */

/***********************************************************************************************************************
* Function Name: slider_decode_abnormal_judgement
* Description  : 0 operation removal
* Arguments    : id            slider ID ( 0-7 )
*              : delta1        delta value 1
*              : delta2        delta value 2
*              : maxch         Max measurement value sensor number
* Return Value : status        ZERO_ENA (0)
*              :               ZERO_DIS (1)
***********************************************************************************************************************/
uint8_t slider_decode_abnormal_judgement(uint8_t id, uint16_t delta1, uint16_t delta2, uint8_t maxch)
{
    uint8_t status;

    status = ZERO_DIS;

    if( 4 == g_sliderInfo[id].num )
    {
        if (0x0000 == delta1)
        {
            if (0 == maxch)
            {
                g_sliderInfo[id].value = 1;
            }
            else
            {
                g_sliderInfo[id].value = (100 / g_sliderInfo[id].resolution) * maxch;
            }
            status = ZERO_ENA;
        }
        else if (0x0000 == delta2)
        {
            g_sliderInfo[id].value = (100 / g_sliderInfo[id].resolution) * (maxch + 1);
            status = ZERO_ENA;
        }
    }
    return status;
}    /* End of function slider_decode_abnormal_judgement() */

#endif    // SLIDER_USE

#ifdef WHEEL_USE
/***********************************************************************************************************************
* Function Name: wheel_decode
* Description  : Wheel Decode function
* Arguments    : w_id          Wheel ID ( 0-7 )
* Return Value : wheel_rpos    Wheel touch position( 65535 = non-touch )
***********************************************************************************************************************/
uint16_t wheel_decode( uint8_t w_id )
{
    uint8_t     loop;
    uint8_t     max_num;
    uint8_t     maxch[3];
    uint16_t    d1,d2,d3;
    uint16_t    wheel_vpos;        /* Wheel virtual position    */
    uint16_t    wheel_rpos;

    /* Unstable Correction */
    for (loop = 0, max_num = 0; loop < (g_wheelInfo[w_id].num-1); loop++)
    {
        if (g_wheel_data[max_num] < g_wheel_data[loop+1])
        {
            max_num = loop + 1;
        }
    }

    /*The maximum ch number to change is put in the array. */
    maxch[0] = max_num;

    /* Array making for slider operation          */
    /*    Maximum change CH_No -----> Array"0"    */
    /*    Maximum change CH_No + 1 -> Array"2"    */
    /*    Maximum change CH_No - 1 -> Array"1"    */
    if (0u < g_wheel_data[maxch[0]])
    {
        if (0u == maxch[0])
        {
            maxch[1] = (uint8_t)(g_wheelInfo[w_id].num - 1);
            maxch[2] = (uint8_t)(maxch[0] + 1);
        }
        else if ( maxch[0] == ( g_wheelInfo[w_id].num - 1 ))
        {
            maxch[1] = (uint8_t)(maxch[0] - 1);
            maxch[2] = 0;
        }
        else
        {
            maxch[1] = (uint8_t)(maxch[0] - 1u);
            maxch[2] = (uint8_t)(maxch[0] + 1u);
        }

        /* Constant decision for operation of angle of wheel    */
        /*    Three constant decisions for the operation        */
        /*    Operation of angle of wheel                       */
        d1 = g_wheel_data[maxch[0]] - g_wheel_data[maxch[1]];
        d2 = g_wheel_data[maxch[0]] - g_wheel_data[maxch[2]];
        g_wheel_dsum[w_id] = (uint16_t)(d1 + d2);

        if(g_wheel_dsum[w_id] > g_wheelInfo[w_id].thr_offset)
        {
            g_wheel_dsum[w_id] = g_wheel_dsum[w_id] - g_wheelInfo[w_id].thr_offset;
        }
        else
        {
            g_wheel_dsum[w_id] = 0;
        }

        if (g_wheel_dsum[w_id] > g_wheelInfo[w_id].threshold)
        {
            if (ZERO_ENA != wheel_decode_abnormal_judgement( w_id, d1, d2, maxch[0] ))
            {
                d3 = 100 + ((d2 * 100) / d1);

                if( 4 == g_wheelInfo[w_id].num )
                {
                    wheel_vpos = ((9000 / d3) + ( 90 * maxch[0] ));
                }
                else
                {
                    wheel_vpos = ((4500 / d3) + ( 45 * maxch[0] ));
                }

                /* Angle division output */
                /* diff_angle_ch = 0 -> 359 ------ diff_angle_ch output 1 to 360 */
                if (0 == wheel_vpos)
                {
                    wheel_vpos = 360;
                }
                else if (361 == wheel_vpos)
                {
                    wheel_vpos = 1;
                }
                else if (361 < wheel_vpos)
                {
                    wheel_vpos = (wheel_vpos-360) >> 1;
                }
                else
                {
                    /* Do Nothing */
                }

                /* swa = 0 -> Max ------ swa output 1 to Max */
                wheel_rpos = (uint16_t)(wheel_vpos / g_wheelInfo[w_id].resolution);
                if (0 == wheel_rpos)
                {
                    wheel_rpos = 1;
                }
                g_wheelInfo[w_id].value = wheel_rpos;
            }
        }
        else
        {
            g_wheelInfo[w_id].value = 0xFFFFu;
            wheel_rpos = 0xFFFFu;
        }
    }
    else
    {
        /* Touch Off Value */
        g_wheelInfo[w_id].value = 0xFFFFu;
        wheel_rpos = 0xFFFFu;
    }
    return wheel_rpos;
}    /* End of function wheel_decode() */

/***********************************************************************************************************************
* Function Name: wheel_decode_abnormal_judgement
* Description  : 0 operation removal
* Arguments    : id            wheel ID ( 0-7 )
*              : delta1        delta value 1
*              : delta2        delta value 2
*              : maxch         Max measurement value sensor number
* Return Value : status        ZERO_ENA (0)
*              :               ZERO_DIS (1)
***********************************************************************************************************************/
uint8_t wheel_decode_abnormal_judgement(uint8_t id, uint16_t delta1, uint16_t delta2, uint8_t maxch)
{
    uint8_t status;

    status = ZERO_DIS;

    if( 4 == g_wheelInfo[id].num )
    {
        if (0x0000 == delta1)
        {
            if (0 == maxch)
            {
                g_wheelInfo[id].value = (360 / g_wheelInfo[id].resolution);
            }
            else
            {
                g_wheelInfo[id].value = (90 / g_wheelInfo[id].resolution) * maxch;
            }
            status = ZERO_ENA;
        }
        else if (0x0000 == delta2)
        {
            g_wheelInfo[id].value = (90 / g_wheelInfo[id].resolution) * (maxch + 1);
            status = ZERO_ENA;
        }
    }
    else
    {
        if (0x0000 == delta1)
        {
            if (0 == maxch)
            {
                g_wheelInfo[id].value = (360 / g_wheelInfo[id].resolution);
            }
            else
            {
                g_wheelInfo[id].value = (45 / g_wheelInfo[id].resolution) * maxch;
            }
            status = ZERO_ENA;
        }
        else if (0x0000 == delta2)
        {
            g_wheelInfo[id].value = (45 / g_wheelInfo[id].resolution) * (maxch + 1);
            status = ZERO_ENA;
        }
    }

    return status;
}    /* End of function wheel_decode_abnormal_judgement() */

#endif    //] WHEEL_USE

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Touch key parameter */
#if ( SELF_METHOD_NUM == 1 )
#if ( SELF_KEY_NUM == 0)
#else
const uint16_t g_self_thrbuff[] =
{
#if SELF_KEY_USE_00 == 1
    SELF_TS00_THR,
#endif
#if SELF_KEY_USE_01 == 1
    SELF_TS01_THR,
#endif
#if SELF_KEY_USE_02 == 1
    SELF_TS02_THR,
#endif
#if SELF_KEY_USE_03 == 1
    SELF_TS03_THR,
#endif
#if SELF_KEY_USE_04 == 1
    SELF_TS04_THR,
#endif
#if SELF_KEY_USE_05 == 1
    SELF_TS05_THR,
#endif
#if SELF_KEY_USE_06 == 1
    SELF_TS06_THR,
#endif
#if SELF_KEY_USE_07 == 1
    SELF_TS07_THR,
#endif
#if SELF_KEY_USE_08 == 1
    SELF_TS08_THR,
#endif
#if SELF_KEY_USE_09 == 1
    SELF_TS09_THR,
#endif
#if SELF_KEY_USE_10 == 1
    SELF_TS10_THR,
#endif
#if SELF_KEY_USE_11 == 1
    SELF_TS11_THR,
#endif
#if SELF_KEY_USE_12 == 1
    SELF_TS12_THR,
#endif
#if SELF_KEY_USE_13 == 1
    SELF_TS13_THR,
#endif
#if SELF_KEY_USE_14 == 1
    SELF_TS14_THR,
#endif
#if SELF_KEY_USE_15 == 1
    SELF_TS15_THR,
#endif
#if SELF_KEY_USE_16 == 1
    SELF_TS16_THR,
#endif
#if SELF_KEY_USE_17 == 1
    SELF_TS17_THR,
#endif
#if SELF_KEY_USE_18 == 1
    SELF_TS18_THR,
#endif
#if SELF_KEY_USE_19 == 1
    SELF_TS19_THR,
#endif
#if SELF_KEY_USE_20 == 1
    SELF_TS20_THR,
#endif
#if SELF_KEY_USE_21 == 1
    SELF_TS21_THR,
#endif
#if SELF_KEY_USE_22 == 1
    SELF_TS22_THR,
#endif
#if SELF_KEY_USE_23 == 1
    SELF_TS23_THR,
#endif
#if SELF_KEY_USE_24 == 1
    SELF_TS24_THR,
#endif
#if SELF_KEY_USE_25 == 1
    SELF_TS25_THR,
#endif
#if SELF_KEY_USE_26 == 1
    SELF_TS26_THR,
#endif
#if SELF_KEY_USE_27 == 1
    SELF_TS27_THR,
#endif
#if SELF_KEY_USE_28 == 1
    SELF_TS28_THR,
#endif
#if SELF_KEY_USE_29 == 1
    SELF_TS29_THR,
#endif
#if SELF_KEY_USE_30 == 1
    SELF_TS30_THR,
#endif
#if SELF_KEY_USE_31 == 1
    SELF_TS31_THR,
#endif
#if SELF_KEY_USE_32 == 1
    SELF_TS32_THR,
#endif
#if SELF_KEY_USE_33 == 1
    SELF_TS33_THR,
#endif
#if SELF_KEY_USE_34 == 1
    SELF_TS34_THR,
#endif
#if SELF_KEY_USE_35 == 1
    SELF_TS35_THR,
#endif
};

const uint16_t g_self_hysbuff[] =
{
#if ( SELF_KEY_USE_00 == 1 )
    SELF_TS00_HYS,
#endif
#if ( SELF_KEY_USE_01 == 1 )
    SELF_TS01_HYS,
#endif
#if ( SELF_KEY_USE_02 == 1 )
    SELF_TS02_HYS,
#endif
#if ( SELF_KEY_USE_03 == 1 )
    SELF_TS03_HYS,
#endif
#if ( SELF_KEY_USE_04 == 1 )
    SELF_TS04_HYS,
#endif
#if ( SELF_KEY_USE_05 == 1 )
    SELF_TS05_HYS,
#endif
#if ( SELF_KEY_USE_06 == 1 )
    SELF_TS06_HYS,
#endif
#if ( SELF_KEY_USE_07 == 1 )
    SELF_TS07_HYS,
#endif
#if ( SELF_KEY_USE_08 == 1 )
    SELF_TS08_HYS,
#endif
#if ( SELF_KEY_USE_09 == 1 )
    SELF_TS09_HYS,
#endif
#if ( SELF_KEY_USE_10 == 1 )
    SELF_TS10_HYS,
#endif
#if ( SELF_KEY_USE_11 == 1 )
    SELF_TS11_HYS,
#endif
#if ( SELF_KEY_USE_12 == 1 )
    SELF_TS12_HYS,
#endif
#if ( SELF_KEY_USE_13 == 1 )
    SELF_TS13_HYS,
#endif
#if ( SELF_KEY_USE_14 == 1 )
    SELF_TS14_HYS,
#endif
#if ( SELF_KEY_USE_15 == 1 )
    SELF_TS15_HYS,
#endif
#if ( SELF_KEY_USE_16 == 1 )
    SELF_TS16_HYS,
#endif
#if ( SELF_KEY_USE_17 == 1 )
    SELF_TS17_HYS,
#endif
#if ( SELF_KEY_USE_18 == 1 )
    SELF_TS18_HYS,
#endif
#if ( SELF_KEY_USE_19 == 1 )
    SELF_TS19_HYS,
#endif
#if ( SELF_KEY_USE_20 == 1 )
    SELF_TS20_HYS,
#endif
#if ( SELF_KEY_USE_21 == 1 )
    SELF_TS21_HYS,
#endif
#if ( SELF_KEY_USE_22 == 1 )
    SELF_TS22_HYS,
#endif
#if ( SELF_KEY_USE_23 == 1 )
    SELF_TS23_HYS,
#endif
#if ( SELF_KEY_USE_24 == 1 )
    SELF_TS24_HYS,
#endif
#if ( SELF_KEY_USE_25 == 1 )
    SELF_TS25_HYS,
#endif
#if ( SELF_KEY_USE_26 == 1 )
    SELF_TS26_HYS,
#endif
#if ( SELF_KEY_USE_27 == 1 )
    SELF_TS27_HYS,
#endif
#if ( SELF_KEY_USE_28 == 1 )
    SELF_TS28_HYS,
#endif
#if ( SELF_KEY_USE_29 == 1 )
    SELF_TS29_HYS,
#endif
#if ( SELF_KEY_USE_30 == 1 )
    SELF_TS30_HYS,
#endif
#if ( SELF_KEY_USE_31 == 1 )
    SELF_TS31_HYS,
#endif
#if ( SELF_KEY_USE_32 == 1 )
    SELF_TS32_HYS,
#endif
#if ( SELF_KEY_USE_33 == 1 )
    SELF_TS33_HYS,
#endif
#if ( SELF_KEY_USE_34 == 1 )
    SELF_TS34_HYS,
#endif
#if ( SELF_KEY_USE_35 == 1 )
    SELF_TS35_HYS,
#endif
};
#endif    // ( SELF_KEY_NUM == 0)
#endif    // ( SELF_METHOD_NUM == 1 )

/*====================================================================================================================*/
/*=====    Mutual 0 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 0 )
const uint16_t g_mutual0_thrbuff[] =
{
#if ( MUTUAL0_KEY00_USE == 1 )
    MUTUAL0_KEY00_THR,
#endif
#if ( MUTUAL0_KEY01_USE == 1 )
    MUTUAL0_KEY01_THR,
#endif
#if ( MUTUAL0_KEY02_USE == 1 )
    MUTUAL0_KEY02_THR,
#endif
#if ( MUTUAL0_KEY03_USE == 1 )
    MUTUAL0_KEY03_THR,
#endif
#if ( MUTUAL0_KEY04_USE == 1 )
    MUTUAL0_KEY04_THR,
#endif
#if ( MUTUAL0_KEY05_USE == 1 )
    MUTUAL0_KEY05_THR,
#endif
#if ( MUTUAL0_KEY06_USE == 1 )
    MUTUAL0_KEY06_THR,
#endif
#if ( MUTUAL0_KEY07_USE == 1 )
    MUTUAL0_KEY07_THR,
#endif
#if ( MUTUAL0_KEY08_USE == 1 )
    MUTUAL0_KEY08_THR,
#endif
#if ( MUTUAL0_KEY09_USE == 1 )
    MUTUAL0_KEY09_THR,
#endif
#if ( MUTUAL0_KEY10_USE == 1 )
    MUTUAL0_KEY10_THR,
#endif
#if ( MUTUAL0_KEY11_USE == 1 )
    MUTUAL0_KEY11_THR,
#endif
#if ( MUTUAL0_KEY12_USE == 1 )
    MUTUAL0_KEY12_THR,
#endif
#if ( MUTUAL0_KEY13_USE == 1 )
    MUTUAL0_KEY13_THR,
#endif
#if ( MUTUAL0_KEY14_USE == 1 )
    MUTUAL0_KEY14_THR,
#endif
#if ( MUTUAL0_KEY15_USE == 1 )
    MUTUAL0_KEY15_THR,
#endif
#if ( MUTUAL0_KEY16_USE == 1 )
    MUTUAL0_KEY16_THR,
#endif
#if ( MUTUAL0_KEY17_USE == 1 )
    MUTUAL0_KEY17_THR,
#endif
#if ( MUTUAL0_KEY18_USE == 1 )
    MUTUAL0_KEY18_THR,
#endif
#if ( MUTUAL0_KEY19_USE == 1 )
    MUTUAL0_KEY19_THR,
#endif
#if ( MUTUAL0_KEY20_USE == 1 )
    MUTUAL0_KEY20_THR,
#endif
#if ( MUTUAL0_KEY21_USE == 1 )
    MUTUAL0_KEY21_THR,
#endif
#if ( MUTUAL0_KEY22_USE == 1 )
    MUTUAL0_KEY22_THR,
#endif
#if ( MUTUAL0_KEY23_USE == 1 )
    MUTUAL0_KEY23_THR,
#endif
#if ( MUTUAL0_KEY24_USE == 1 )
    MUTUAL0_KEY24_THR,
#endif
#if ( MUTUAL0_KEY25_USE == 1 )
    MUTUAL0_KEY25_THR,
#endif
#if ( MUTUAL0_KEY26_USE == 1 )
    MUTUAL0_KEY26_THR,
#endif
#if ( MUTUAL0_KEY27_USE == 1 )
    MUTUAL0_KEY27_THR,
#endif
#if ( MUTUAL0_KEY28_USE == 1 )
    MUTUAL0_KEY28_THR,
#endif
#if ( MUTUAL0_KEY29_USE == 1 )
    MUTUAL0_KEY29_THR,
#endif
#if ( MUTUAL0_KEY30_USE == 1 )
    MUTUAL0_KEY30_THR,
#endif
#if ( MUTUAL0_KEY31_USE == 1 )
    MUTUAL0_KEY31_THR,
#endif
#if ( MUTUAL0_KEY32_USE == 1 )
    MUTUAL0_KEY32_THR,
#endif
#if ( MUTUAL0_KEY33_USE == 1 )
    MUTUAL0_KEY33_THR,
#endif
#if ( MUTUAL0_KEY34_USE == 1 )
    MUTUAL0_KEY34_THR,
#endif
#if ( MUTUAL0_KEY35_USE == 1 )
    MUTUAL0_KEY35_THR,
#endif
#if ( MUTUAL0_KEY36_USE == 1 )
    MUTUAL0_KEY36_THR,
#endif
#if ( MUTUAL0_KEY37_USE == 1 )
    MUTUAL0_KEY37_THR,
#endif
#if ( MUTUAL0_KEY38_USE == 1 )
    MUTUAL0_KEY38_THR,
#endif
#if ( MUTUAL0_KEY39_USE == 1 )
    MUTUAL0_KEY39_THR,
#endif
#if ( MUTUAL0_KEY40_USE == 1 )
    MUTUAL0_KEY40_THR,
#endif
#if ( MUTUAL0_KEY41_USE == 1 )
    MUTUAL0_KEY41_THR,
#endif
#if ( MUTUAL0_KEY42_USE == 1 )
    MUTUAL0_KEY42_THR,
#endif
#if ( MUTUAL0_KEY43_USE == 1 )
    MUTUAL0_KEY43_THR,
#endif
#if ( MUTUAL0_KEY44_USE == 1 )
    MUTUAL0_KEY44_THR,
#endif
#if ( MUTUAL0_KEY45_USE == 1 )
    MUTUAL0_KEY45_THR,
#endif
#if ( MUTUAL0_KEY46_USE == 1 )
    MUTUAL0_KEY46_THR,
#endif
#if ( MUTUAL0_KEY47_USE == 1 )
    MUTUAL0_KEY47_THR,
#endif
#if ( MUTUAL0_KEY48_USE == 1 )
    MUTUAL0_KEY48_THR,
#endif
#if ( MUTUAL0_KEY49_USE == 1 )
    MUTUAL0_KEY49_THR,
#endif
#if ( MUTUAL0_KEY50_USE == 1 )
    MUTUAL0_KEY50_THR,
#endif
#if ( MUTUAL0_KEY51_USE == 1 )
    MUTUAL0_KEY51_THR,
#endif
#if ( MUTUAL0_KEY52_USE == 1 )
    MUTUAL0_KEY52_THR,
#endif
#if ( MUTUAL0_KEY53_USE == 1 )
    MUTUAL0_KEY53_THR,
#endif
#if ( MUTUAL0_KEY54_USE == 1 )
    MUTUAL0_KEY54_THR,
#endif
#if ( MUTUAL0_KEY55_USE == 1 )
    MUTUAL0_KEY55_THR,
#endif
#if ( MUTUAL0_KEY56_USE == 1 )
    MUTUAL0_KEY56_THR,
#endif
#if ( MUTUAL0_KEY57_USE == 1 )
    MUTUAL0_KEY57_THR,
#endif
#if ( MUTUAL0_KEY58_USE == 1 )
    MUTUAL0_KEY58_THR,
#endif
#if ( MUTUAL0_KEY59_USE == 1 )
    MUTUAL0_KEY59_THR,
#endif
#if ( MUTUAL0_KEY60_USE == 1 )
    MUTUAL0_KEY60_THR,
#endif
#if ( MUTUAL0_KEY61_USE == 1 )
    MUTUAL0_KEY61_THR,
#endif
#if ( MUTUAL0_KEY62_USE == 1 )
    MUTUAL0_KEY62_THR,
#endif
#if ( MUTUAL0_KEY63_USE == 1 )
    MUTUAL0_KEY63_THR,
#endif
};

const uint16_t g_mutual0_hysbuff[] =
{
#if ( MUTUAL0_KEY00_USE == 1 )
    MUTUAL0_KEY00_HYS,
#endif
#if ( MUTUAL0_KEY01_USE == 1 )
    MUTUAL0_KEY01_HYS,
#endif
#if ( MUTUAL0_KEY02_USE == 1 )
    MUTUAL0_KEY02_HYS,
#endif
#if ( MUTUAL0_KEY03_USE == 1 )
    MUTUAL0_KEY03_HYS,
#endif
#if ( MUTUAL0_KEY04_USE == 1 )
    MUTUAL0_KEY04_HYS,
#endif
#if ( MUTUAL0_KEY05_USE == 1 )
    MUTUAL0_KEY05_HYS,
#endif
#if ( MUTUAL0_KEY06_USE == 1 )
    MUTUAL0_KEY06_HYS,
#endif
#if ( MUTUAL0_KEY07_USE == 1 )
    MUTUAL0_KEY07_HYS,
#endif
#if ( MUTUAL0_KEY08_USE == 1 )
    MUTUAL0_KEY08_HYS,
#endif
#if ( MUTUAL0_KEY09_USE == 1 )
    MUTUAL0_KEY09_HYS,
#endif
#if ( MUTUAL0_KEY10_USE == 1 )
    MUTUAL0_KEY10_HYS,
#endif
#if ( MUTUAL0_KEY11_USE == 1 )
    MUTUAL0_KEY11_HYS,
#endif
#if ( MUTUAL0_KEY12_USE == 1 )
    MUTUAL0_KEY12_HYS,
#endif
#if ( MUTUAL0_KEY13_USE == 1 )
    MUTUAL0_KEY13_HYS,
#endif
#if ( MUTUAL0_KEY14_USE == 1 )
    MUTUAL0_KEY14_HYS,
#endif
#if ( MUTUAL0_KEY15_USE == 1 )
    MUTUAL0_KEY15_HYS,
#endif
#if ( MUTUAL0_KEY16_USE == 1 )
    MUTUAL0_KEY16_HYS,
#endif
#if ( MUTUAL0_KEY17_USE == 1 )
    MUTUAL0_KEY17_HYS,
#endif
#if ( MUTUAL0_KEY18_USE == 1 )
    MUTUAL0_KEY18_HYS,
#endif
#if ( MUTUAL0_KEY19_USE == 1 )
    MUTUAL0_KEY19_HYS,
#endif
#if ( MUTUAL0_KEY20_USE == 1 )
    MUTUAL0_KEY20_HYS,
#endif
#if ( MUTUAL0_KEY21_USE == 1 )
    MUTUAL0_KEY21_HYS,
#endif
#if ( MUTUAL0_KEY22_USE == 1 )
    MUTUAL0_KEY22_HYS,
#endif
#if ( MUTUAL0_KEY23_USE == 1 )
    MUTUAL0_KEY23_HYS,
#endif
#if ( MUTUAL0_KEY24_USE == 1 )
    MUTUAL0_KEY24_HYS,
#endif
#if ( MUTUAL0_KEY25_USE == 1 )
    MUTUAL0_KEY25_HYS,
#endif
#if ( MUTUAL0_KEY26_USE == 1 )
    MUTUAL0_KEY26_HYS,
#endif
#if ( MUTUAL0_KEY27_USE == 1 )
    MUTUAL0_KEY27_HYS,
#endif
#if ( MUTUAL0_KEY28_USE == 1 )
    MUTUAL0_KEY28_HYS,
#endif
#if ( MUTUAL0_KEY29_USE == 1 )
    MUTUAL0_KEY29_HYS,
#endif
#if ( MUTUAL0_KEY30_USE == 1 )
    MUTUAL0_KEY30_HYS,
#endif
#if ( MUTUAL0_KEY31_USE == 1 )
    MUTUAL0_KEY31_HYS,
#endif
#if ( MUTUAL0_KEY32_USE == 1 )
    MUTUAL0_KEY32_HYS,
#endif
#if ( MUTUAL0_KEY33_USE == 1 )
    MUTUAL0_KEY33_HYS,
#endif
#if ( MUTUAL0_KEY34_USE == 1 )
    MUTUAL0_KEY34_HYS,
#endif
#if ( MUTUAL0_KEY35_USE == 1 )
    MUTUAL0_KEY35_HYS,
#endif
#if ( MUTUAL0_KEY36_USE == 1 )
    MUTUAL0_KEY36_HYS,
#endif
#if ( MUTUAL0_KEY37_USE == 1 )
    MUTUAL0_KEY37_HYS,
#endif
#if ( MUTUAL0_KEY38_USE == 1 )
    MUTUAL0_KEY38_HYS,
#endif
#if ( MUTUAL0_KEY39_USE == 1 )
    MUTUAL0_KEY39_HYS,
#endif
#if ( MUTUAL0_KEY40_USE == 1 )
    MUTUAL0_KEY40_HYS,
#endif
#if ( MUTUAL0_KEY41_USE == 1 )
    MUTUAL0_KEY41_HYS,
#endif
#if ( MUTUAL0_KEY42_USE == 1 )
    MUTUAL0_KEY42_HYS,
#endif
#if ( MUTUAL0_KEY43_USE == 1 )
    MUTUAL0_KEY43_HYS,
#endif
#if ( MUTUAL0_KEY44_USE == 1 )
    MUTUAL0_KEY44_HYS,
#endif
#if ( MUTUAL0_KEY45_USE == 1 )
    MUTUAL0_KEY45_HYS,
#endif
#if ( MUTUAL0_KEY46_USE == 1 )
    MUTUAL0_KEY46_HYS,
#endif
#if ( MUTUAL0_KEY47_USE == 1 )
    MUTUAL0_KEY47_HYS,
#endif
#if ( MUTUAL0_KEY48_USE == 1 )
    MUTUAL0_KEY48_HYS,
#endif
#if ( MUTUAL0_KEY49_USE == 1 )
    MUTUAL0_KEY49_HYS,
#endif
#if ( MUTUAL0_KEY50_USE == 1 )
    MUTUAL0_KEY50_HYS,
#endif
#if ( MUTUAL0_KEY51_USE == 1 )
    MUTUAL0_KEY51_HYS,
#endif
#if ( MUTUAL0_KEY52_USE == 1 )
    MUTUAL0_KEY52_HYS,
#endif
#if ( MUTUAL0_KEY53_USE == 1 )
    MUTUAL0_KEY53_HYS,
#endif
#if ( MUTUAL0_KEY54_USE == 1 )
    MUTUAL0_KEY54_HYS,
#endif
#if ( MUTUAL0_KEY55_USE == 1 )
    MUTUAL0_KEY55_HYS,
#endif
#if ( MUTUAL0_KEY56_USE == 1 )
    MUTUAL0_KEY56_HYS,
#endif
#if ( MUTUAL0_KEY57_USE == 1 )
    MUTUAL0_KEY57_HYS,
#endif
#if ( MUTUAL0_KEY58_USE == 1 )
    MUTUAL0_KEY58_HYS,
#endif
#if ( MUTUAL0_KEY59_USE == 1 )
    MUTUAL0_KEY59_HYS,
#endif
#if ( MUTUAL0_KEY60_USE == 1 )
    MUTUAL0_KEY60_HYS,
#endif
#if ( MUTUAL0_KEY61_USE == 1 )
    MUTUAL0_KEY61_HYS,
#endif
#if ( MUTUAL0_KEY62_USE == 1 )
    MUTUAL0_KEY62_HYS,
#endif
#if ( MUTUAL0_KEY63_USE == 1 )
    MUTUAL0_KEY63_HYS,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 0 )

/*====================================================================================================================*/
/*=====    Mutual 1 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 1 )
const uint16_t g_mutual1_thrbuff[] =
{
#if ( MUTUAL1_KEY00_USE == 1 )
    MUTUAL1_KEY00_THR,
#endif
#if ( MUTUAL1_KEY01_USE == 1 )
    MUTUAL1_KEY01_THR,
#endif
#if ( MUTUAL1_KEY02_USE == 1 )
    MUTUAL1_KEY02_THR,
#endif
#if ( MUTUAL1_KEY03_USE == 1 )
    MUTUAL1_KEY03_THR,
#endif
#if ( MUTUAL1_KEY04_USE == 1 )
    MUTUAL1_KEY04_THR,
#endif
#if ( MUTUAL1_KEY05_USE == 1 )
    MUTUAL1_KEY05_THR,
#endif
#if ( MUTUAL1_KEY06_USE == 1 )
    MUTUAL1_KEY06_THR,
#endif
#if ( MUTUAL1_KEY07_USE == 1 )
    MUTUAL1_KEY07_THR,
#endif
#if ( MUTUAL1_KEY08_USE == 1 )
    MUTUAL1_KEY08_THR,
#endif
#if ( MUTUAL1_KEY09_USE == 1 )
    MUTUAL1_KEY09_THR,
#endif
#if ( MUTUAL1_KEY10_USE == 1 )
    MUTUAL1_KEY10_THR,
#endif
#if ( MUTUAL1_KEY11_USE == 1 )
    MUTUAL1_KEY11_THR,
#endif
#if ( MUTUAL1_KEY12_USE == 1 )
    MUTUAL1_KEY12_THR,
#endif
#if ( MUTUAL1_KEY13_USE == 1 )
    MUTUAL1_KEY13_THR,
#endif
#if ( MUTUAL1_KEY14_USE == 1 )
    MUTUAL1_KEY14_THR,
#endif
#if ( MUTUAL1_KEY15_USE == 1 )
    MUTUAL1_KEY15_THR,
#endif
#if ( MUTUAL1_KEY16_USE == 1 )
    MUTUAL1_KEY16_THR,
#endif
#if ( MUTUAL1_KEY17_USE == 1 )
    MUTUAL1_KEY17_THR,
#endif
#if ( MUTUAL1_KEY18_USE == 1 )
    MUTUAL1_KEY18_THR,
#endif
#if ( MUTUAL1_KEY19_USE == 1 )
    MUTUAL1_KEY19_THR,
#endif
#if ( MUTUAL1_KEY20_USE == 1 )
    MUTUAL1_KEY20_THR,
#endif
#if ( MUTUAL1_KEY21_USE == 1 )
    MUTUAL1_KEY21_THR,
#endif
#if ( MUTUAL1_KEY22_USE == 1 )
    MUTUAL1_KEY22_THR,
#endif
#if ( MUTUAL1_KEY23_USE == 1 )
    MUTUAL1_KEY23_THR,
#endif
#if ( MUTUAL1_KEY24_USE == 1 )
    MUTUAL1_KEY24_THR,
#endif
#if ( MUTUAL1_KEY25_USE == 1 )
    MUTUAL1_KEY25_THR,
#endif
#if ( MUTUAL1_KEY26_USE == 1 )
    MUTUAL1_KEY26_THR,
#endif
#if ( MUTUAL1_KEY27_USE == 1 )
    MUTUAL1_KEY27_THR,
#endif
#if ( MUTUAL1_KEY28_USE == 1 )
    MUTUAL1_KEY28_THR,
#endif
#if ( MUTUAL1_KEY29_USE == 1 )
    MUTUAL1_KEY29_THR,
#endif
#if ( MUTUAL1_KEY30_USE == 1 )
    MUTUAL1_KEY30_THR,
#endif
#if ( MUTUAL1_KEY31_USE == 1 )
    MUTUAL1_KEY31_THR,
#endif
#if ( MUTUAL1_KEY32_USE == 1 )
    MUTUAL1_KEY32_THR,
#endif
#if ( MUTUAL1_KEY33_USE == 1 )
    MUTUAL1_KEY33_THR,
#endif
#if ( MUTUAL1_KEY34_USE == 1 )
    MUTUAL1_KEY34_THR,
#endif
#if ( MUTUAL1_KEY35_USE == 1 )
    MUTUAL1_KEY35_THR,
#endif
#if ( MUTUAL1_KEY36_USE == 1 )
    MUTUAL1_KEY36_THR,
#endif
#if ( MUTUAL1_KEY37_USE == 1 )
    MUTUAL1_KEY37_THR,
#endif
#if ( MUTUAL1_KEY38_USE == 1 )
    MUTUAL1_KEY38_THR,
#endif
#if ( MUTUAL1_KEY39_USE == 1 )
    MUTUAL1_KEY39_THR,
#endif
#if ( MUTUAL1_KEY40_USE == 1 )
    MUTUAL1_KEY40_THR,
#endif
#if ( MUTUAL1_KEY41_USE == 1 )
    MUTUAL1_KEY41_THR,
#endif
#if ( MUTUAL1_KEY42_USE == 1 )
    MUTUAL1_KEY42_THR,
#endif
#if ( MUTUAL1_KEY43_USE == 1 )
    MUTUAL1_KEY43_THR,
#endif
#if ( MUTUAL1_KEY44_USE == 1 )
    MUTUAL1_KEY44_THR,
#endif
#if ( MUTUAL1_KEY45_USE == 1 )
    MUTUAL1_KEY45_THR,
#endif
#if ( MUTUAL1_KEY46_USE == 1 )
    MUTUAL1_KEY46_THR,
#endif
#if ( MUTUAL1_KEY47_USE == 1 )
    MUTUAL1_KEY47_THR,
#endif
#if ( MUTUAL1_KEY48_USE == 1 )
    MUTUAL1_KEY48_THR,
#endif
#if ( MUTUAL1_KEY49_USE == 1 )
    MUTUAL1_KEY49_THR,
#endif
#if ( MUTUAL1_KEY50_USE == 1 )
    MUTUAL1_KEY50_THR,
#endif
#if ( MUTUAL1_KEY51_USE == 1 )
    MUTUAL1_KEY51_THR,
#endif
#if ( MUTUAL1_KEY52_USE == 1 )
    MUTUAL1_KEY52_THR,
#endif
#if ( MUTUAL1_KEY53_USE == 1 )
    MUTUAL1_KEY53_THR,
#endif
#if ( MUTUAL1_KEY54_USE == 1 )
    MUTUAL1_KEY54_THR,
#endif
#if ( MUTUAL1_KEY55_USE == 1 )
    MUTUAL1_KEY55_THR,
#endif
#if ( MUTUAL1_KEY56_USE == 1 )
    MUTUAL1_KEY56_THR,
#endif
#if ( MUTUAL1_KEY57_USE == 1 )
    MUTUAL1_KEY57_THR,
#endif
#if ( MUTUAL1_KEY58_USE == 1 )
    MUTUAL1_KEY58_THR,
#endif
#if ( MUTUAL1_KEY59_USE == 1 )
    MUTUAL1_KEY59_THR,
#endif
#if ( MUTUAL1_KEY60_USE == 1 )
    MUTUAL1_KEY60_THR,
#endif
#if ( MUTUAL1_KEY61_USE == 1 )
    MUTUAL1_KEY61_THR,
#endif
#if ( MUTUAL1_KEY62_USE == 1 )
    MUTUAL1_KEY62_THR,
#endif
#if ( MUTUAL1_KEY63_USE == 1 )
    MUTUAL1_KEY63_THR,
#endif
};

const uint16_t g_mutual1_hysbuff[] =
{
#if ( MUTUAL1_KEY00_USE == 1 )
    MUTUAL1_KEY00_HYS,
#endif
#if ( MUTUAL1_KEY01_USE == 1 )
    MUTUAL1_KEY01_HYS,
#endif
#if ( MUTUAL1_KEY02_USE == 1 )
    MUTUAL1_KEY02_HYS,
#endif
#if ( MUTUAL1_KEY03_USE == 1 )
    MUTUAL1_KEY03_HYS,
#endif
#if ( MUTUAL1_KEY04_USE == 1 )
    MUTUAL1_KEY04_HYS,
#endif
#if ( MUTUAL1_KEY05_USE == 1 )
    MUTUAL1_KEY05_HYS,
#endif
#if ( MUTUAL1_KEY06_USE == 1 )
    MUTUAL1_KEY06_HYS,
#endif
#if ( MUTUAL1_KEY07_USE == 1 )
    MUTUAL1_KEY07_HYS,
#endif
#if ( MUTUAL1_KEY08_USE == 1 )
    MUTUAL1_KEY08_HYS,
#endif
#if ( MUTUAL1_KEY09_USE == 1 )
    MUTUAL1_KEY09_HYS,
#endif
#if ( MUTUAL1_KEY10_USE == 1 )
    MUTUAL1_KEY10_HYS,
#endif
#if ( MUTUAL1_KEY11_USE == 1 )
    MUTUAL1_KEY11_HYS,
#endif
#if ( MUTUAL1_KEY12_USE == 1 )
    MUTUAL1_KEY12_HYS,
#endif
#if ( MUTUAL1_KEY13_USE == 1 )
    MUTUAL1_KEY13_HYS,
#endif
#if ( MUTUAL1_KEY14_USE == 1 )
    MUTUAL1_KEY14_HYS,
#endif
#if ( MUTUAL1_KEY15_USE == 1 )
    MUTUAL1_KEY15_HYS,
#endif
#if ( MUTUAL1_KEY16_USE == 1 )
    MUTUAL1_KEY16_HYS,
#endif
#if ( MUTUAL1_KEY17_USE == 1 )
    MUTUAL1_KEY17_HYS,
#endif
#if ( MUTUAL1_KEY18_USE == 1 )
    MUTUAL1_KEY18_HYS,
#endif
#if ( MUTUAL1_KEY19_USE == 1 )
    MUTUAL1_KEY19_HYS,
#endif
#if ( MUTUAL1_KEY20_USE == 1 )
    MUTUAL1_KEY20_HYS,
#endif
#if ( MUTUAL1_KEY21_USE == 1 )
    MUTUAL1_KEY21_HYS,
#endif
#if ( MUTUAL1_KEY22_USE == 1 )
    MUTUAL1_KEY22_HYS,
#endif
#if ( MUTUAL1_KEY23_USE == 1 )
    MUTUAL1_KEY23_HYS,
#endif
#if ( MUTUAL1_KEY24_USE == 1 )
    MUTUAL1_KEY24_HYS,
#endif
#if ( MUTUAL1_KEY25_USE == 1 )
    MUTUAL1_KEY25_HYS,
#endif
#if ( MUTUAL1_KEY26_USE == 1 )
    MUTUAL1_KEY26_HYS,
#endif
#if ( MUTUAL1_KEY27_USE == 1 )
    MUTUAL1_KEY27_HYS,
#endif
#if ( MUTUAL1_KEY28_USE == 1 )
    MUTUAL1_KEY28_HYS,
#endif
#if ( MUTUAL1_KEY29_USE == 1 )
    MUTUAL1_KEY29_HYS,
#endif
#if ( MUTUAL1_KEY30_USE == 1 )
    MUTUAL1_KEY30_HYS,
#endif
#if ( MUTUAL1_KEY31_USE == 1 )
    MUTUAL1_KEY31_HYS,
#endif
#if ( MUTUAL1_KEY32_USE == 1 )
    MUTUAL1_KEY32_HYS,
#endif
#if ( MUTUAL1_KEY33_USE == 1 )
    MUTUAL1_KEY33_HYS,
#endif
#if ( MUTUAL1_KEY34_USE == 1 )
    MUTUAL1_KEY34_HYS,
#endif
#if ( MUTUAL1_KEY35_USE == 1 )
    MUTUAL1_KEY35_HYS,
#endif
#if ( MUTUAL1_KEY36_USE == 1 )
    MUTUAL1_KEY36_HYS,
#endif
#if ( MUTUAL1_KEY37_USE == 1 )
    MUTUAL1_KEY37_HYS,
#endif
#if ( MUTUAL1_KEY38_USE == 1 )
    MUTUAL1_KEY38_HYS,
#endif
#if ( MUTUAL1_KEY39_USE == 1 )
    MUTUAL1_KEY39_HYS,
#endif
#if ( MUTUAL1_KEY40_USE == 1 )
    MUTUAL1_KEY40_HYS,
#endif
#if ( MUTUAL1_KEY41_USE == 1 )
    MUTUAL1_KEY41_HYS,
#endif
#if ( MUTUAL1_KEY42_USE == 1 )
    MUTUAL1_KEY42_HYS,
#endif
#if ( MUTUAL1_KEY43_USE == 1 )
    MUTUAL1_KEY43_HYS,
#endif
#if ( MUTUAL1_KEY44_USE == 1 )
    MUTUAL1_KEY44_HYS,
#endif
#if ( MUTUAL1_KEY45_USE == 1 )
    MUTUAL1_KEY45_HYS,
#endif
#if ( MUTUAL1_KEY46_USE == 1 )
    MUTUAL1_KEY46_HYS,
#endif
#if ( MUTUAL1_KEY47_USE == 1 )
    MUTUAL1_KEY47_HYS,
#endif
#if ( MUTUAL1_KEY48_USE == 1 )
    MUTUAL1_KEY48_HYS,
#endif
#if ( MUTUAL1_KEY49_USE == 1 )
    MUTUAL1_KEY49_HYS,
#endif
#if ( MUTUAL1_KEY50_USE == 1 )
    MUTUAL1_KEY50_HYS,
#endif
#if ( MUTUAL1_KEY51_USE == 1 )
    MUTUAL1_KEY51_HYS,
#endif
#if ( MUTUAL1_KEY52_USE == 1 )
    MUTUAL1_KEY52_HYS,
#endif
#if ( MUTUAL1_KEY53_USE == 1 )
    MUTUAL1_KEY53_HYS,
#endif
#if ( MUTUAL1_KEY54_USE == 1 )
    MUTUAL1_KEY54_HYS,
#endif
#if ( MUTUAL1_KEY55_USE == 1 )
    MUTUAL1_KEY55_HYS,
#endif
#if ( MUTUAL1_KEY56_USE == 1 )
    MUTUAL1_KEY56_HYS,
#endif
#if ( MUTUAL1_KEY57_USE == 1 )
    MUTUAL1_KEY57_HYS,
#endif
#if ( MUTUAL1_KEY58_USE == 1 )
    MUTUAL1_KEY58_HYS,
#endif
#if ( MUTUAL1_KEY59_USE == 1 )
    MUTUAL1_KEY59_HYS,
#endif
#if ( MUTUAL1_KEY60_USE == 1 )
    MUTUAL1_KEY60_HYS,
#endif
#if ( MUTUAL1_KEY61_USE == 1 )
    MUTUAL1_KEY61_HYS,
#endif
#if ( MUTUAL1_KEY62_USE == 1 )
    MUTUAL1_KEY62_HYS,
#endif
#if ( MUTUAL1_KEY63_USE == 1 )
    MUTUAL1_KEY63_HYS,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 1 )

/*====================================================================================================================*/
/*=====    Mutual 2 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 2 )
const uint16_t g_mutual2_thrbuff[] =
{
#if ( MUTUAL2_KEY00_USE == 1 )
    MUTUAL2_KEY00_THR,
#endif
#if ( MUTUAL2_KEY01_USE == 1 )
    MUTUAL2_KEY01_THR,
#endif
#if ( MUTUAL2_KEY02_USE == 1 )
    MUTUAL2_KEY02_THR,
#endif
#if ( MUTUAL2_KEY03_USE == 1 )
    MUTUAL2_KEY03_THR,
#endif
#if ( MUTUAL2_KEY04_USE == 1 )
    MUTUAL2_KEY04_THR,
#endif
#if ( MUTUAL2_KEY05_USE == 1 )
    MUTUAL2_KEY05_THR,
#endif
#if ( MUTUAL2_KEY06_USE == 1 )
    MUTUAL2_KEY06_THR,
#endif
#if ( MUTUAL2_KEY07_USE == 1 )
    MUTUAL2_KEY07_THR,
#endif
#if ( MUTUAL2_KEY08_USE == 1 )
    MUTUAL2_KEY08_THR,
#endif
#if ( MUTUAL2_KEY09_USE == 1 )
    MUTUAL2_KEY09_THR,
#endif
#if ( MUTUAL2_KEY10_USE == 1 )
    MUTUAL2_KEY10_THR,
#endif
#if ( MUTUAL2_KEY11_USE == 1 )
    MUTUAL2_KEY11_THR,
#endif
#if ( MUTUAL2_KEY12_USE == 1 )
    MUTUAL2_KEY12_THR,
#endif
#if ( MUTUAL2_KEY13_USE == 1 )
    MUTUAL2_KEY13_THR,
#endif
#if ( MUTUAL2_KEY14_USE == 1 )
    MUTUAL2_KEY14_THR,
#endif
#if ( MUTUAL2_KEY15_USE == 1 )
    MUTUAL2_KEY15_THR,
#endif
#if ( MUTUAL2_KEY16_USE == 1 )
    MUTUAL2_KEY16_THR,
#endif
#if ( MUTUAL2_KEY17_USE == 1 )
    MUTUAL2_KEY17_THR,
#endif
#if ( MUTUAL2_KEY18_USE == 1 )
    MUTUAL2_KEY18_THR,
#endif
#if ( MUTUAL2_KEY19_USE == 1 )
    MUTUAL2_KEY19_THR,
#endif
#if ( MUTUAL2_KEY20_USE == 1 )
    MUTUAL2_KEY20_THR,
#endif
#if ( MUTUAL2_KEY21_USE == 1 )
    MUTUAL2_KEY21_THR,
#endif
#if ( MUTUAL2_KEY22_USE == 1 )
    MUTUAL2_KEY22_THR,
#endif
#if ( MUTUAL2_KEY23_USE == 1 )
    MUTUAL2_KEY23_THR,
#endif
#if ( MUTUAL2_KEY24_USE == 1 )
    MUTUAL2_KEY24_THR,
#endif
#if ( MUTUAL2_KEY25_USE == 1 )
    MUTUAL2_KEY25_THR,
#endif
#if ( MUTUAL2_KEY26_USE == 1 )
    MUTUAL2_KEY26_THR,
#endif
#if ( MUTUAL2_KEY27_USE == 1 )
    MUTUAL2_KEY27_THR,
#endif
#if ( MUTUAL2_KEY28_USE == 1 )
    MUTUAL2_KEY28_THR,
#endif
#if ( MUTUAL2_KEY29_USE == 1 )
    MUTUAL2_KEY29_THR,
#endif
#if ( MUTUAL2_KEY30_USE == 1 )
    MUTUAL2_KEY30_THR,
#endif
#if ( MUTUAL2_KEY31_USE == 1 )
    MUTUAL2_KEY31_THR,
#endif
#if ( MUTUAL2_KEY32_USE == 1 )
    MUTUAL2_KEY32_THR,
#endif
#if ( MUTUAL2_KEY33_USE == 1 )
    MUTUAL2_KEY33_THR,
#endif
#if ( MUTUAL2_KEY34_USE == 1 )
    MUTUAL2_KEY34_THR,
#endif
#if ( MUTUAL2_KEY35_USE == 1 )
    MUTUAL2_KEY35_THR,
#endif
#if ( MUTUAL2_KEY36_USE == 1 )
    MUTUAL2_KEY36_THR,
#endif
#if ( MUTUAL2_KEY37_USE == 1 )
    MUTUAL2_KEY37_THR,
#endif
#if ( MUTUAL2_KEY38_USE == 1 )
    MUTUAL2_KEY38_THR,
#endif
#if ( MUTUAL2_KEY39_USE == 1 )
    MUTUAL2_KEY39_THR,
#endif
#if ( MUTUAL2_KEY40_USE == 1 )
    MUTUAL2_KEY40_THR,
#endif
#if ( MUTUAL2_KEY41_USE == 1 )
    MUTUAL2_KEY41_THR,
#endif
#if ( MUTUAL2_KEY42_USE == 1 )
    MUTUAL2_KEY42_THR,
#endif
#if ( MUTUAL2_KEY43_USE == 1 )
    MUTUAL2_KEY43_THR,
#endif
#if ( MUTUAL2_KEY44_USE == 1 )
    MUTUAL2_KEY44_THR,
#endif
#if ( MUTUAL2_KEY45_USE == 1 )
    MUTUAL2_KEY45_THR,
#endif
#if ( MUTUAL2_KEY46_USE == 1 )
    MUTUAL2_KEY46_THR,
#endif
#if ( MUTUAL2_KEY47_USE == 1 )
    MUTUAL2_KEY47_THR,
#endif
#if ( MUTUAL2_KEY48_USE == 1 )
    MUTUAL2_KEY48_THR,
#endif
#if ( MUTUAL2_KEY49_USE == 1 )
    MUTUAL2_KEY49_THR,
#endif
#if ( MUTUAL2_KEY50_USE == 1 )
    MUTUAL2_KEY50_THR,
#endif
#if ( MUTUAL2_KEY51_USE == 1 )
    MUTUAL2_KEY51_THR,
#endif
#if ( MUTUAL2_KEY52_USE == 1 )
    MUTUAL2_KEY52_THR,
#endif
#if ( MUTUAL2_KEY53_USE == 1 )
    MUTUAL2_KEY53_THR,
#endif
#if ( MUTUAL2_KEY54_USE == 1 )
    MUTUAL2_KEY54_THR,
#endif
#if ( MUTUAL2_KEY55_USE == 1 )
    MUTUAL2_KEY55_THR,
#endif
#if ( MUTUAL2_KEY56_USE == 1 )
    MUTUAL2_KEY56_THR,
#endif
#if ( MUTUAL2_KEY57_USE == 1 )
    MUTUAL2_KEY57_THR,
#endif
#if ( MUTUAL2_KEY58_USE == 1 )
    MUTUAL2_KEY58_THR,
#endif
#if ( MUTUAL2_KEY59_USE == 1 )
    MUTUAL2_KEY59_THR,
#endif
#if ( MUTUAL2_KEY60_USE == 1 )
    MUTUAL2_KEY60_THR,
#endif
#if ( MUTUAL2_KEY61_USE == 1 )
    MUTUAL2_KEY61_THR,
#endif
#if ( MUTUAL2_KEY62_USE == 1 )
    MUTUAL2_KEY62_THR,
#endif
#if ( MUTUAL2_KEY63_USE == 1 )
    MUTUAL2_KEY63_THR,
#endif
};

const uint16_t g_mutual2_hysbuff[] =
{
#if ( MUTUAL2_KEY00_USE == 1 )
    MUTUAL2_KEY00_HYS,
#endif
#if ( MUTUAL2_KEY01_USE == 1 )
    MUTUAL2_KEY01_HYS,
#endif
#if ( MUTUAL2_KEY02_USE == 1 )
    MUTUAL2_KEY02_HYS,
#endif
#if ( MUTUAL2_KEY03_USE == 1 )
    MUTUAL2_KEY03_HYS,
#endif
#if ( MUTUAL2_KEY04_USE == 1 )
    MUTUAL2_KEY04_HYS,
#endif
#if ( MUTUAL2_KEY05_USE == 1 )
    MUTUAL2_KEY05_HYS,
#endif
#if ( MUTUAL2_KEY06_USE == 1 )
    MUTUAL2_KEY06_HYS,
#endif
#if ( MUTUAL2_KEY07_USE == 1 )
    MUTUAL2_KEY07_HYS,
#endif
#if ( MUTUAL2_KEY08_USE == 1 )
    MUTUAL2_KEY08_HYS,
#endif
#if ( MUTUAL2_KEY09_USE == 1 )
    MUTUAL2_KEY09_HYS,
#endif
#if ( MUTUAL2_KEY10_USE == 1 )
    MUTUAL2_KEY10_HYS,
#endif
#if ( MUTUAL2_KEY11_USE == 1 )
    MUTUAL2_KEY11_HYS,
#endif
#if ( MUTUAL2_KEY12_USE == 1 )
    MUTUAL2_KEY12_HYS,
#endif
#if ( MUTUAL2_KEY13_USE == 1 )
    MUTUAL2_KEY13_HYS,
#endif
#if ( MUTUAL2_KEY14_USE == 1 )
    MUTUAL2_KEY14_HYS,
#endif
#if ( MUTUAL2_KEY15_USE == 1 )
    MUTUAL2_KEY15_HYS,
#endif
#if ( MUTUAL2_KEY16_USE == 1 )
    MUTUAL2_KEY16_HYS,
#endif
#if ( MUTUAL2_KEY17_USE == 1 )
    MUTUAL2_KEY17_HYS,
#endif
#if ( MUTUAL2_KEY18_USE == 1 )
    MUTUAL2_KEY18_HYS,
#endif
#if ( MUTUAL2_KEY19_USE == 1 )
    MUTUAL2_KEY19_HYS,
#endif
#if ( MUTUAL2_KEY20_USE == 1 )
    MUTUAL2_KEY20_HYS,
#endif
#if ( MUTUAL2_KEY21_USE == 1 )
    MUTUAL2_KEY21_HYS,
#endif
#if ( MUTUAL2_KEY22_USE == 1 )
    MUTUAL2_KEY22_HYS,
#endif
#if ( MUTUAL2_KEY23_USE == 1 )
    MUTUAL2_KEY23_HYS,
#endif
#if ( MUTUAL2_KEY24_USE == 1 )
    MUTUAL2_KEY24_HYS,
#endif
#if ( MUTUAL2_KEY25_USE == 1 )
    MUTUAL2_KEY25_HYS,
#endif
#if ( MUTUAL2_KEY26_USE == 1 )
    MUTUAL2_KEY26_HYS,
#endif
#if ( MUTUAL2_KEY27_USE == 1 )
    MUTUAL2_KEY27_HYS,
#endif
#if ( MUTUAL2_KEY28_USE == 1 )
    MUTUAL2_KEY28_HYS,
#endif
#if ( MUTUAL2_KEY29_USE == 1 )
    MUTUAL2_KEY29_HYS,
#endif
#if ( MUTUAL2_KEY30_USE == 1 )
    MUTUAL2_KEY30_HYS,
#endif
#if ( MUTUAL2_KEY31_USE == 1 )
    MUTUAL2_KEY31_HYS,
#endif
#if ( MUTUAL2_KEY32_USE == 1 )
    MUTUAL2_KEY32_HYS,
#endif
#if ( MUTUAL2_KEY33_USE == 1 )
    MUTUAL2_KEY33_HYS,
#endif
#if ( MUTUAL2_KEY34_USE == 1 )
    MUTUAL2_KEY34_HYS,
#endif
#if ( MUTUAL2_KEY35_USE == 1 )
    MUTUAL2_KEY35_HYS,
#endif
#if ( MUTUAL2_KEY36_USE == 1 )
    MUTUAL2_KEY36_HYS,
#endif
#if ( MUTUAL2_KEY37_USE == 1 )
    MUTUAL2_KEY37_HYS,
#endif
#if ( MUTUAL2_KEY38_USE == 1 )
    MUTUAL2_KEY38_HYS,
#endif
#if ( MUTUAL2_KEY39_USE == 1 )
    MUTUAL2_KEY39_HYS,
#endif
#if ( MUTUAL2_KEY40_USE == 1 )
    MUTUAL2_KEY40_HYS,
#endif
#if ( MUTUAL2_KEY41_USE == 1 )
    MUTUAL2_KEY41_HYS,
#endif
#if ( MUTUAL2_KEY42_USE == 1 )
    MUTUAL2_KEY42_HYS,
#endif
#if ( MUTUAL2_KEY43_USE == 1 )
    MUTUAL2_KEY43_HYS,
#endif
#if ( MUTUAL2_KEY44_USE == 1 )
    MUTUAL2_KEY44_HYS,
#endif
#if ( MUTUAL2_KEY45_USE == 1 )
    MUTUAL2_KEY45_HYS,
#endif
#if ( MUTUAL2_KEY46_USE == 1 )
    MUTUAL2_KEY46_HYS,
#endif
#if ( MUTUAL2_KEY47_USE == 1 )
    MUTUAL2_KEY47_HYS,
#endif
#if ( MUTUAL2_KEY48_USE == 1 )
    MUTUAL2_KEY48_HYS,
#endif
#if ( MUTUAL2_KEY49_USE == 1 )
    MUTUAL2_KEY49_HYS,
#endif
#if ( MUTUAL2_KEY50_USE == 1 )
    MUTUAL2_KEY50_HYS,
#endif
#if ( MUTUAL2_KEY51_USE == 1 )
    MUTUAL2_KEY51_HYS,
#endif
#if ( MUTUAL2_KEY52_USE == 1 )
    MUTUAL2_KEY52_HYS,
#endif
#if ( MUTUAL2_KEY53_USE == 1 )
    MUTUAL2_KEY53_HYS,
#endif
#if ( MUTUAL2_KEY54_USE == 1 )
    MUTUAL2_KEY54_HYS,
#endif
#if ( MUTUAL2_KEY55_USE == 1 )
    MUTUAL2_KEY55_HYS,
#endif
#if ( MUTUAL2_KEY56_USE == 1 )
    MUTUAL2_KEY56_HYS,
#endif
#if ( MUTUAL2_KEY57_USE == 1 )
    MUTUAL2_KEY57_HYS,
#endif
#if ( MUTUAL2_KEY58_USE == 1 )
    MUTUAL2_KEY58_HYS,
#endif
#if ( MUTUAL2_KEY59_USE == 1 )
    MUTUAL2_KEY59_HYS,
#endif
#if ( MUTUAL2_KEY60_USE == 1 )
    MUTUAL2_KEY60_HYS,
#endif
#if ( MUTUAL2_KEY61_USE == 1 )
    MUTUAL2_KEY61_HYS,
#endif
#if ( MUTUAL2_KEY62_USE == 1 )
    MUTUAL2_KEY62_HYS,
#endif
#if ( MUTUAL2_KEY63_USE == 1 )
    MUTUAL2_KEY63_HYS,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 2 )

/*====================================================================================================================*/
/*=====    Mutual 3 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 3 )
const uint16_t g_mutual3_thrbuff[] =
{
#if ( MUTUAL3_KEY00_USE == 1 )
    MUTUAL3_KEY00_THR,
#endif
#if ( MUTUAL3_KEY01_USE == 1 )
    MUTUAL3_KEY01_THR,
#endif
#if ( MUTUAL3_KEY02_USE == 1 )
    MUTUAL3_KEY02_THR,
#endif
#if ( MUTUAL3_KEY03_USE == 1 )
    MUTUAL3_KEY03_THR,
#endif
#if ( MUTUAL3_KEY04_USE == 1 )
    MUTUAL3_KEY04_THR,
#endif
#if ( MUTUAL3_KEY05_USE == 1 )
    MUTUAL3_KEY05_THR,
#endif
#if ( MUTUAL3_KEY06_USE == 1 )
    MUTUAL3_KEY06_THR,
#endif
#if ( MUTUAL3_KEY07_USE == 1 )
    MUTUAL3_KEY07_THR,
#endif
#if ( MUTUAL3_KEY08_USE == 1 )
    MUTUAL3_KEY08_THR,
#endif
#if ( MUTUAL3_KEY09_USE == 1 )
    MUTUAL3_KEY09_THR,
#endif
#if ( MUTUAL3_KEY10_USE == 1 )
    MUTUAL3_KEY10_THR,
#endif
#if ( MUTUAL3_KEY11_USE == 1 )
    MUTUAL3_KEY11_THR,
#endif
#if ( MUTUAL3_KEY12_USE == 1 )
    MUTUAL3_KEY12_THR,
#endif
#if ( MUTUAL3_KEY13_USE == 1 )
    MUTUAL3_KEY13_THR,
#endif
#if ( MUTUAL3_KEY14_USE == 1 )
    MUTUAL3_KEY14_THR,
#endif
#if ( MUTUAL3_KEY15_USE == 1 )
    MUTUAL3_KEY15_THR,
#endif
#if ( MUTUAL3_KEY16_USE == 1 )
    MUTUAL3_KEY16_THR,
#endif
#if ( MUTUAL3_KEY17_USE == 1 )
    MUTUAL3_KEY17_THR,
#endif
#if ( MUTUAL3_KEY18_USE == 1 )
    MUTUAL3_KEY18_THR,
#endif
#if ( MUTUAL3_KEY19_USE == 1 )
    MUTUAL3_KEY19_THR,
#endif
#if ( MUTUAL3_KEY20_USE == 1 )
    MUTUAL3_KEY20_THR,
#endif
#if ( MUTUAL3_KEY21_USE == 1 )
    MUTUAL3_KEY21_THR,
#endif
#if ( MUTUAL3_KEY22_USE == 1 )
    MUTUAL3_KEY22_THR,
#endif
#if ( MUTUAL3_KEY23_USE == 1 )
    MUTUAL3_KEY23_THR,
#endif
#if ( MUTUAL3_KEY24_USE == 1 )
    MUTUAL3_KEY24_THR,
#endif
#if ( MUTUAL3_KEY25_USE == 1 )
    MUTUAL3_KEY25_THR,
#endif
#if ( MUTUAL3_KEY26_USE == 1 )
    MUTUAL3_KEY26_THR,
#endif
#if ( MUTUAL3_KEY27_USE == 1 )
    MUTUAL3_KEY27_THR,
#endif
#if ( MUTUAL3_KEY28_USE == 1 )
    MUTUAL3_KEY28_THR,
#endif
#if ( MUTUAL3_KEY29_USE == 1 )
    MUTUAL3_KEY29_THR,
#endif
#if ( MUTUAL3_KEY30_USE == 1 )
    MUTUAL3_KEY30_THR,
#endif
#if ( MUTUAL3_KEY31_USE == 1 )
    MUTUAL3_KEY31_THR,
#endif
#if ( MUTUAL3_KEY32_USE == 1 )
    MUTUAL3_KEY32_THR,
#endif
#if ( MUTUAL3_KEY33_USE == 1 )
    MUTUAL3_KEY33_THR,
#endif
#if ( MUTUAL3_KEY34_USE == 1 )
    MUTUAL3_KEY34_THR,
#endif
#if ( MUTUAL3_KEY35_USE == 1 )
    MUTUAL3_KEY35_THR,
#endif
#if ( MUTUAL3_KEY36_USE == 1 )
    MUTUAL3_KEY36_THR,
#endif
#if ( MUTUAL3_KEY37_USE == 1 )
    MUTUAL3_KEY37_THR,
#endif
#if ( MUTUAL3_KEY38_USE == 1 )
    MUTUAL3_KEY38_THR,
#endif
#if ( MUTUAL3_KEY39_USE == 1 )
    MUTUAL3_KEY39_THR,
#endif
#if ( MUTUAL3_KEY40_USE == 1 )
    MUTUAL3_KEY40_THR,
#endif
#if ( MUTUAL3_KEY41_USE == 1 )
    MUTUAL3_KEY41_THR,
#endif
#if ( MUTUAL3_KEY42_USE == 1 )
    MUTUAL3_KEY42_THR,
#endif
#if ( MUTUAL3_KEY43_USE == 1 )
    MUTUAL3_KEY43_THR,
#endif
#if ( MUTUAL3_KEY44_USE == 1 )
    MUTUAL3_KEY44_THR,
#endif
#if ( MUTUAL3_KEY45_USE == 1 )
    MUTUAL3_KEY45_THR,
#endif
#if ( MUTUAL3_KEY46_USE == 1 )
    MUTUAL3_KEY46_THR,
#endif
#if ( MUTUAL3_KEY47_USE == 1 )
    MUTUAL3_KEY47_THR,
#endif
#if ( MUTUAL3_KEY48_USE == 1 )
    MUTUAL3_KEY48_THR,
#endif
#if ( MUTUAL3_KEY49_USE == 1 )
    MUTUAL3_KEY49_THR,
#endif
#if ( MUTUAL3_KEY50_USE == 1 )
    MUTUAL3_KEY50_THR,
#endif
#if ( MUTUAL3_KEY51_USE == 1 )
    MUTUAL3_KEY51_THR,
#endif
#if ( MUTUAL3_KEY52_USE == 1 )
    MUTUAL3_KEY52_THR,
#endif
#if ( MUTUAL3_KEY53_USE == 1 )
    MUTUAL3_KEY53_THR,
#endif
#if ( MUTUAL3_KEY54_USE == 1 )
    MUTUAL3_KEY54_THR,
#endif
#if ( MUTUAL3_KEY55_USE == 1 )
    MUTUAL3_KEY55_THR,
#endif
#if ( MUTUAL3_KEY56_USE == 1 )
    MUTUAL3_KEY56_THR,
#endif
#if ( MUTUAL3_KEY57_USE == 1 )
    MUTUAL3_KEY57_THR,
#endif
#if ( MUTUAL3_KEY58_USE == 1 )
    MUTUAL3_KEY58_THR,
#endif
#if ( MUTUAL3_KEY59_USE == 1 )
    MUTUAL3_KEY59_THR,
#endif
#if ( MUTUAL3_KEY60_USE == 1 )
    MUTUAL3_KEY60_THR,
#endif
#if ( MUTUAL3_KEY61_USE == 1 )
    MUTUAL3_KEY61_THR,
#endif
#if ( MUTUAL3_KEY62_USE == 1 )
    MUTUAL3_KEY62_THR,
#endif
#if ( MUTUAL3_KEY63_USE == 1 )
    MUTUAL3_KEY63_THR,
#endif
};

const uint16_t g_mutual3_hysbuff[] =
{
#if ( MUTUAL3_KEY00_USE == 1 )
    MUTUAL3_KEY00_HYS,
#endif
#if ( MUTUAL3_KEY01_USE == 1 )
    MUTUAL3_KEY01_HYS,
#endif
#if ( MUTUAL3_KEY02_USE == 1 )
    MUTUAL3_KEY02_HYS,
#endif
#if ( MUTUAL3_KEY03_USE == 1 )
    MUTUAL3_KEY03_HYS,
#endif
#if ( MUTUAL3_KEY04_USE == 1 )
    MUTUAL3_KEY04_HYS,
#endif
#if ( MUTUAL3_KEY05_USE == 1 )
    MUTUAL3_KEY05_HYS,
#endif
#if ( MUTUAL3_KEY06_USE == 1 )
    MUTUAL3_KEY06_HYS,
#endif
#if ( MUTUAL3_KEY07_USE == 1 )
    MUTUAL3_KEY07_HYS,
#endif
#if ( MUTUAL3_KEY08_USE == 1 )
    MUTUAL3_KEY08_HYS,
#endif
#if ( MUTUAL3_KEY09_USE == 1 )
    MUTUAL3_KEY09_HYS,
#endif
#if ( MUTUAL3_KEY10_USE == 1 )
    MUTUAL3_KEY10_HYS,
#endif
#if ( MUTUAL3_KEY11_USE == 1 )
    MUTUAL3_KEY11_HYS,
#endif
#if ( MUTUAL3_KEY12_USE == 1 )
    MUTUAL3_KEY12_HYS,
#endif
#if ( MUTUAL3_KEY13_USE == 1 )
    MUTUAL3_KEY13_HYS,
#endif
#if ( MUTUAL3_KEY14_USE == 1 )
    MUTUAL3_KEY14_HYS,
#endif
#if ( MUTUAL3_KEY15_USE == 1 )
    MUTUAL3_KEY15_HYS,
#endif
#if ( MUTUAL3_KEY16_USE == 1 )
    MUTUAL3_KEY16_HYS,
#endif
#if ( MUTUAL3_KEY17_USE == 1 )
    MUTUAL3_KEY17_HYS,
#endif
#if ( MUTUAL3_KEY18_USE == 1 )
    MUTUAL3_KEY18_HYS,
#endif
#if ( MUTUAL3_KEY19_USE == 1 )
    MUTUAL3_KEY19_HYS,
#endif
#if ( MUTUAL3_KEY20_USE == 1 )
    MUTUAL3_KEY20_HYS,
#endif
#if ( MUTUAL3_KEY21_USE == 1 )
    MUTUAL3_KEY21_HYS,
#endif
#if ( MUTUAL3_KEY22_USE == 1 )
    MUTUAL3_KEY22_HYS,
#endif
#if ( MUTUAL3_KEY23_USE == 1 )
    MUTUAL3_KEY23_HYS,
#endif
#if ( MUTUAL3_KEY24_USE == 1 )
    MUTUAL3_KEY24_HYS,
#endif
#if ( MUTUAL3_KEY25_USE == 1 )
    MUTUAL3_KEY25_HYS,
#endif
#if ( MUTUAL3_KEY26_USE == 1 )
    MUTUAL3_KEY26_HYS,
#endif
#if ( MUTUAL3_KEY27_USE == 1 )
    MUTUAL3_KEY27_HYS,
#endif
#if ( MUTUAL3_KEY28_USE == 1 )
    MUTUAL3_KEY28_HYS,
#endif
#if ( MUTUAL3_KEY29_USE == 1 )
    MUTUAL3_KEY29_HYS,
#endif
#if ( MUTUAL3_KEY30_USE == 1 )
    MUTUAL3_KEY30_HYS,
#endif
#if ( MUTUAL3_KEY31_USE == 1 )
    MUTUAL3_KEY31_HYS,
#endif
#if ( MUTUAL3_KEY32_USE == 1 )
    MUTUAL3_KEY32_HYS,
#endif
#if ( MUTUAL3_KEY33_USE == 1 )
    MUTUAL3_KEY33_HYS,
#endif
#if ( MUTUAL3_KEY34_USE == 1 )
    MUTUAL3_KEY34_HYS,
#endif
#if ( MUTUAL3_KEY35_USE == 1 )
    MUTUAL3_KEY35_HYS,
#endif
#if ( MUTUAL3_KEY36_USE == 1 )
    MUTUAL3_KEY36_HYS,
#endif
#if ( MUTUAL3_KEY37_USE == 1 )
    MUTUAL3_KEY37_HYS,
#endif
#if ( MUTUAL3_KEY38_USE == 1 )
    MUTUAL3_KEY38_HYS,
#endif
#if ( MUTUAL3_KEY39_USE == 1 )
    MUTUAL3_KEY39_HYS,
#endif
#if ( MUTUAL3_KEY40_USE == 1 )
    MUTUAL3_KEY40_HYS,
#endif
#if ( MUTUAL3_KEY41_USE == 1 )
    MUTUAL3_KEY41_HYS,
#endif
#if ( MUTUAL3_KEY42_USE == 1 )
    MUTUAL3_KEY42_HYS,
#endif
#if ( MUTUAL3_KEY43_USE == 1 )
    MUTUAL3_KEY43_HYS,
#endif
#if ( MUTUAL3_KEY44_USE == 1 )
    MUTUAL3_KEY44_HYS,
#endif
#if ( MUTUAL3_KEY45_USE == 1 )
    MUTUAL3_KEY45_HYS,
#endif
#if ( MUTUAL3_KEY46_USE == 1 )
    MUTUAL3_KEY46_HYS,
#endif
#if ( MUTUAL3_KEY47_USE == 1 )
    MUTUAL3_KEY47_HYS,
#endif
#if ( MUTUAL3_KEY48_USE == 1 )
    MUTUAL3_KEY48_HYS,
#endif
#if ( MUTUAL3_KEY49_USE == 1 )
    MUTUAL3_KEY49_HYS,
#endif
#if ( MUTUAL3_KEY50_USE == 1 )
    MUTUAL3_KEY50_HYS,
#endif
#if ( MUTUAL3_KEY51_USE == 1 )
    MUTUAL3_KEY51_HYS,
#endif
#if ( MUTUAL3_KEY52_USE == 1 )
    MUTUAL3_KEY52_HYS,
#endif
#if ( MUTUAL3_KEY53_USE == 1 )
    MUTUAL3_KEY53_HYS,
#endif
#if ( MUTUAL3_KEY54_USE == 1 )
    MUTUAL3_KEY54_HYS,
#endif
#if ( MUTUAL3_KEY55_USE == 1 )
    MUTUAL3_KEY55_HYS,
#endif
#if ( MUTUAL3_KEY56_USE == 1 )
    MUTUAL3_KEY56_HYS,
#endif
#if ( MUTUAL3_KEY57_USE == 1 )
    MUTUAL3_KEY57_HYS,
#endif
#if ( MUTUAL3_KEY58_USE == 1 )
    MUTUAL3_KEY58_HYS,
#endif
#if ( MUTUAL3_KEY59_USE == 1 )
    MUTUAL3_KEY59_HYS,
#endif
#if ( MUTUAL3_KEY60_USE == 1 )
    MUTUAL3_KEY60_HYS,
#endif
#if ( MUTUAL3_KEY61_USE == 1 )
    MUTUAL3_KEY61_HYS,
#endif
#if ( MUTUAL3_KEY62_USE == 1 )
    MUTUAL3_KEY62_HYS,
#endif
#if ( MUTUAL3_KEY63_USE == 1 )
    MUTUAL3_KEY63_HYS,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 3 )

/*====================================================================================================================*/
/*=====    Mutual 4 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 4 )
const uint16_t g_mutual4_thrbuff[] =
{
#if ( MUTUAL4_KEY00_USE == 1 )
    MUTUAL4_KEY00_THR,
#endif
#if ( MUTUAL4_KEY01_USE == 1 )
    MUTUAL4_KEY01_THR,
#endif
#if ( MUTUAL4_KEY02_USE == 1 )
    MUTUAL4_KEY02_THR,
#endif
#if ( MUTUAL4_KEY03_USE == 1 )
    MUTUAL4_KEY03_THR,
#endif
#if ( MUTUAL4_KEY04_USE == 1 )
    MUTUAL4_KEY04_THR,
#endif
#if ( MUTUAL4_KEY05_USE == 1 )
    MUTUAL4_KEY05_THR,
#endif
#if ( MUTUAL4_KEY06_USE == 1 )
    MUTUAL4_KEY06_THR,
#endif
#if ( MUTUAL4_KEY07_USE == 1 )
    MUTUAL4_KEY07_THR,
#endif
#if ( MUTUAL4_KEY08_USE == 1 )
    MUTUAL4_KEY08_THR,
#endif
#if ( MUTUAL4_KEY09_USE == 1 )
    MUTUAL4_KEY09_THR,
#endif
#if ( MUTUAL4_KEY10_USE == 1 )
    MUTUAL4_KEY10_THR,
#endif
#if ( MUTUAL4_KEY11_USE == 1 )
    MUTUAL4_KEY11_THR,
#endif
#if ( MUTUAL4_KEY12_USE == 1 )
    MUTUAL4_KEY12_THR,
#endif
#if ( MUTUAL4_KEY13_USE == 1 )
    MUTUAL4_KEY13_THR,
#endif
#if ( MUTUAL4_KEY14_USE == 1 )
    MUTUAL4_KEY14_THR,
#endif
#if ( MUTUAL4_KEY15_USE == 1 )
    MUTUAL4_KEY15_THR,
#endif
#if ( MUTUAL4_KEY16_USE == 1 )
    MUTUAL4_KEY16_THR,
#endif
#if ( MUTUAL4_KEY17_USE == 1 )
    MUTUAL4_KEY17_THR,
#endif
#if ( MUTUAL4_KEY18_USE == 1 )
    MUTUAL4_KEY18_THR,
#endif
#if ( MUTUAL4_KEY19_USE == 1 )
    MUTUAL4_KEY19_THR,
#endif
#if ( MUTUAL4_KEY20_USE == 1 )
    MUTUAL4_KEY20_THR,
#endif
#if ( MUTUAL4_KEY21_USE == 1 )
    MUTUAL4_KEY21_THR,
#endif
#if ( MUTUAL4_KEY22_USE == 1 )
    MUTUAL4_KEY22_THR,
#endif
#if ( MUTUAL4_KEY23_USE == 1 )
    MUTUAL4_KEY23_THR,
#endif
#if ( MUTUAL4_KEY24_USE == 1 )
    MUTUAL4_KEY24_THR,
#endif
#if ( MUTUAL4_KEY25_USE == 1 )
    MUTUAL4_KEY25_THR,
#endif
#if ( MUTUAL4_KEY26_USE == 1 )
    MUTUAL4_KEY26_THR,
#endif
#if ( MUTUAL4_KEY27_USE == 1 )
    MUTUAL4_KEY27_THR,
#endif
#if ( MUTUAL4_KEY28_USE == 1 )
    MUTUAL4_KEY28_THR,
#endif
#if ( MUTUAL4_KEY29_USE == 1 )
    MUTUAL4_KEY29_THR,
#endif
#if ( MUTUAL4_KEY30_USE == 1 )
    MUTUAL4_KEY30_THR,
#endif
#if ( MUTUAL4_KEY31_USE == 1 )
    MUTUAL4_KEY31_THR,
#endif
#if ( MUTUAL4_KEY32_USE == 1 )
    MUTUAL4_KEY32_THR,
#endif
#if ( MUTUAL4_KEY33_USE == 1 )
    MUTUAL4_KEY33_THR,
#endif
#if ( MUTUAL4_KEY34_USE == 1 )
    MUTUAL4_KEY34_THR,
#endif
#if ( MUTUAL4_KEY35_USE == 1 )
    MUTUAL4_KEY35_THR,
#endif
#if ( MUTUAL4_KEY36_USE == 1 )
    MUTUAL4_KEY36_THR,
#endif
#if ( MUTUAL4_KEY37_USE == 1 )
    MUTUAL4_KEY37_THR,
#endif
#if ( MUTUAL4_KEY38_USE == 1 )
    MUTUAL4_KEY38_THR,
#endif
#if ( MUTUAL4_KEY39_USE == 1 )
    MUTUAL4_KEY39_THR,
#endif
#if ( MUTUAL4_KEY40_USE == 1 )
    MUTUAL4_KEY40_THR,
#endif
#if ( MUTUAL4_KEY41_USE == 1 )
    MUTUAL4_KEY41_THR,
#endif
#if ( MUTUAL4_KEY42_USE == 1 )
    MUTUAL4_KEY42_THR,
#endif
#if ( MUTUAL4_KEY43_USE == 1 )
    MUTUAL4_KEY43_THR,
#endif
#if ( MUTUAL4_KEY44_USE == 1 )
    MUTUAL4_KEY44_THR,
#endif
#if ( MUTUAL4_KEY45_USE == 1 )
    MUTUAL4_KEY45_THR,
#endif
#if ( MUTUAL4_KEY46_USE == 1 )
    MUTUAL4_KEY46_THR,
#endif
#if ( MUTUAL4_KEY47_USE == 1 )
    MUTUAL4_KEY47_THR,
#endif
#if ( MUTUAL4_KEY48_USE == 1 )
    MUTUAL4_KEY48_THR,
#endif
#if ( MUTUAL4_KEY49_USE == 1 )
    MUTUAL4_KEY49_THR,
#endif
#if ( MUTUAL4_KEY50_USE == 1 )
    MUTUAL4_KEY50_THR,
#endif
#if ( MUTUAL4_KEY51_USE == 1 )
    MUTUAL4_KEY51_THR,
#endif
#if ( MUTUAL4_KEY52_USE == 1 )
    MUTUAL4_KEY52_THR,
#endif
#if ( MUTUAL4_KEY53_USE == 1 )
    MUTUAL4_KEY53_THR,
#endif
#if ( MUTUAL4_KEY54_USE == 1 )
    MUTUAL4_KEY54_THR,
#endif
#if ( MUTUAL4_KEY55_USE == 1 )
    MUTUAL4_KEY55_THR,
#endif
#if ( MUTUAL4_KEY56_USE == 1 )
    MUTUAL4_KEY56_THR,
#endif
#if ( MUTUAL4_KEY57_USE == 1 )
    MUTUAL4_KEY57_THR,
#endif
#if ( MUTUAL4_KEY58_USE == 1 )
    MUTUAL4_KEY58_THR,
#endif
#if ( MUTUAL4_KEY59_USE == 1 )
    MUTUAL4_KEY59_THR,
#endif
#if ( MUTUAL4_KEY60_USE == 1 )
    MUTUAL4_KEY60_THR,
#endif
#if ( MUTUAL4_KEY61_USE == 1 )
    MUTUAL4_KEY61_THR,
#endif
#if ( MUTUAL4_KEY62_USE == 1 )
    MUTUAL4_KEY62_THR,
#endif
#if ( MUTUAL4_KEY63_USE == 1 )
    MUTUAL4_KEY63_THR,
#endif
};

const uint16_t g_mutual4_hysbuff[] =
{
#if ( MUTUAL4_KEY00_USE == 1 )
    MUTUAL4_KEY00_HYS,
#endif
#if ( MUTUAL4_KEY01_USE == 1 )
    MUTUAL4_KEY01_HYS,
#endif
#if ( MUTUAL4_KEY02_USE == 1 )
    MUTUAL4_KEY02_HYS,
#endif
#if ( MUTUAL4_KEY03_USE == 1 )
    MUTUAL4_KEY03_HYS,
#endif
#if ( MUTUAL4_KEY04_USE == 1 )
    MUTUAL4_KEY04_HYS,
#endif
#if ( MUTUAL4_KEY05_USE == 1 )
    MUTUAL4_KEY05_HYS,
#endif
#if ( MUTUAL4_KEY06_USE == 1 )
    MUTUAL4_KEY06_HYS,
#endif
#if ( MUTUAL4_KEY07_USE == 1 )
    MUTUAL4_KEY07_HYS,
#endif
#if ( MUTUAL4_KEY08_USE == 1 )
    MUTUAL4_KEY08_HYS,
#endif
#if ( MUTUAL4_KEY09_USE == 1 )
    MUTUAL4_KEY09_HYS,
#endif
#if ( MUTUAL4_KEY10_USE == 1 )
    MUTUAL4_KEY10_HYS,
#endif
#if ( MUTUAL4_KEY11_USE == 1 )
    MUTUAL4_KEY11_HYS,
#endif
#if ( MUTUAL4_KEY12_USE == 1 )
    MUTUAL4_KEY12_HYS,
#endif
#if ( MUTUAL4_KEY13_USE == 1 )
    MUTUAL4_KEY13_HYS,
#endif
#if ( MUTUAL4_KEY14_USE == 1 )
    MUTUAL4_KEY14_HYS,
#endif
#if ( MUTUAL4_KEY15_USE == 1 )
    MUTUAL4_KEY15_HYS,
#endif
#if ( MUTUAL4_KEY16_USE == 1 )
    MUTUAL4_KEY16_HYS,
#endif
#if ( MUTUAL4_KEY17_USE == 1 )
    MUTUAL4_KEY17_HYS,
#endif
#if ( MUTUAL4_KEY18_USE == 1 )
    MUTUAL4_KEY18_HYS,
#endif
#if ( MUTUAL4_KEY19_USE == 1 )
    MUTUAL4_KEY19_HYS,
#endif
#if ( MUTUAL4_KEY20_USE == 1 )
    MUTUAL4_KEY20_HYS,
#endif
#if ( MUTUAL4_KEY21_USE == 1 )
    MUTUAL4_KEY21_HYS,
#endif
#if ( MUTUAL4_KEY22_USE == 1 )
    MUTUAL4_KEY22_HYS,
#endif
#if ( MUTUAL4_KEY23_USE == 1 )
    MUTUAL4_KEY23_HYS,
#endif
#if ( MUTUAL4_KEY24_USE == 1 )
    MUTUAL4_KEY24_HYS,
#endif
#if ( MUTUAL4_KEY25_USE == 1 )
    MUTUAL4_KEY25_HYS,
#endif
#if ( MUTUAL4_KEY26_USE == 1 )
    MUTUAL4_KEY26_HYS,
#endif
#if ( MUTUAL4_KEY27_USE == 1 )
    MUTUAL4_KEY27_HYS,
#endif
#if ( MUTUAL4_KEY28_USE == 1 )
    MUTUAL4_KEY28_HYS,
#endif
#if ( MUTUAL4_KEY29_USE == 1 )
    MUTUAL4_KEY29_HYS,
#endif
#if ( MUTUAL4_KEY30_USE == 1 )
    MUTUAL4_KEY30_HYS,
#endif
#if ( MUTUAL4_KEY31_USE == 1 )
    MUTUAL4_KEY31_HYS,
#endif
#if ( MUTUAL4_KEY32_USE == 1 )
    MUTUAL4_KEY32_HYS,
#endif
#if ( MUTUAL4_KEY33_USE == 1 )
    MUTUAL4_KEY33_HYS,
#endif
#if ( MUTUAL4_KEY34_USE == 1 )
    MUTUAL4_KEY34_HYS,
#endif
#if ( MUTUAL4_KEY35_USE == 1 )
    MUTUAL4_KEY35_HYS,
#endif
#if ( MUTUAL4_KEY36_USE == 1 )
    MUTUAL4_KEY36_HYS,
#endif
#if ( MUTUAL4_KEY37_USE == 1 )
    MUTUAL4_KEY37_HYS,
#endif
#if ( MUTUAL4_KEY38_USE == 1 )
    MUTUAL4_KEY38_HYS,
#endif
#if ( MUTUAL4_KEY39_USE == 1 )
    MUTUAL4_KEY39_HYS,
#endif
#if ( MUTUAL4_KEY40_USE == 1 )
    MUTUAL4_KEY40_HYS,
#endif
#if ( MUTUAL4_KEY41_USE == 1 )
    MUTUAL4_KEY41_HYS,
#endif
#if ( MUTUAL4_KEY42_USE == 1 )
    MUTUAL4_KEY42_HYS,
#endif
#if ( MUTUAL4_KEY43_USE == 1 )
    MUTUAL4_KEY43_HYS,
#endif
#if ( MUTUAL4_KEY44_USE == 1 )
    MUTUAL4_KEY44_HYS,
#endif
#if ( MUTUAL4_KEY45_USE == 1 )
    MUTUAL4_KEY45_HYS,
#endif
#if ( MUTUAL4_KEY46_USE == 1 )
    MUTUAL4_KEY46_HYS,
#endif
#if ( MUTUAL4_KEY47_USE == 1 )
    MUTUAL4_KEY47_HYS,
#endif
#if ( MUTUAL4_KEY48_USE == 1 )
    MUTUAL4_KEY48_HYS,
#endif
#if ( MUTUAL4_KEY49_USE == 1 )
    MUTUAL4_KEY49_HYS,
#endif
#if ( MUTUAL4_KEY50_USE == 1 )
    MUTUAL4_KEY50_HYS,
#endif
#if ( MUTUAL4_KEY51_USE == 1 )
    MUTUAL4_KEY51_HYS,
#endif
#if ( MUTUAL4_KEY52_USE == 1 )
    MUTUAL4_KEY52_HYS,
#endif
#if ( MUTUAL4_KEY53_USE == 1 )
    MUTUAL4_KEY53_HYS,
#endif
#if ( MUTUAL4_KEY54_USE == 1 )
    MUTUAL4_KEY54_HYS,
#endif
#if ( MUTUAL4_KEY55_USE == 1 )
    MUTUAL4_KEY55_HYS,
#endif
#if ( MUTUAL4_KEY56_USE == 1 )
    MUTUAL4_KEY56_HYS,
#endif
#if ( MUTUAL4_KEY57_USE == 1 )
    MUTUAL4_KEY57_HYS,
#endif
#if ( MUTUAL4_KEY58_USE == 1 )
    MUTUAL4_KEY58_HYS,
#endif
#if ( MUTUAL4_KEY59_USE == 1 )
    MUTUAL4_KEY59_HYS,
#endif
#if ( MUTUAL4_KEY60_USE == 1 )
    MUTUAL4_KEY60_HYS,
#endif
#if ( MUTUAL4_KEY61_USE == 1 )
    MUTUAL4_KEY61_HYS,
#endif
#if ( MUTUAL4_KEY62_USE == 1 )
    MUTUAL4_KEY62_HYS,
#endif
#if ( MUTUAL4_KEY63_USE == 1 )
    MUTUAL4_KEY63_HYS,
#endif
};
#endif  // ( MUTUAL_METHOD_NUM > 4 )

/*====================================================================================================================*/
/*=====    Mutual 5 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 5 )
const uint16_t g_mutual5_thrbuff[] =
{
#if ( MUTUAL5_KEY00_USE == 1 )
    MUTUAL5_KEY00_THR,
#endif
#if ( MUTUAL5_KEY01_USE == 1 )
    MUTUAL5_KEY01_THR,
#endif
#if ( MUTUAL5_KEY02_USE == 1 )
    MUTUAL5_KEY02_THR,
#endif
#if ( MUTUAL5_KEY03_USE == 1 )
    MUTUAL5_KEY03_THR,
#endif
#if ( MUTUAL5_KEY04_USE == 1 )
    MUTUAL5_KEY04_THR,
#endif
#if ( MUTUAL5_KEY05_USE == 1 )
    MUTUAL5_KEY05_THR,
#endif
#if ( MUTUAL5_KEY06_USE == 1 )
    MUTUAL5_KEY06_THR,
#endif
#if ( MUTUAL5_KEY07_USE == 1 )
    MUTUAL5_KEY07_THR,
#endif
#if ( MUTUAL5_KEY08_USE == 1 )
    MUTUAL5_KEY08_THR,
#endif
#if ( MUTUAL5_KEY09_USE == 1 )
    MUTUAL5_KEY09_THR,
#endif
#if ( MUTUAL5_KEY10_USE == 1 )
    MUTUAL5_KEY10_THR,
#endif
#if ( MUTUAL5_KEY11_USE == 1 )
    MUTUAL5_KEY11_THR,
#endif
#if ( MUTUAL5_KEY12_USE == 1 )
    MUTUAL5_KEY12_THR,
#endif
#if ( MUTUAL5_KEY13_USE == 1 )
    MUTUAL5_KEY13_THR,
#endif
#if ( MUTUAL5_KEY14_USE == 1 )
    MUTUAL5_KEY14_THR,
#endif
#if ( MUTUAL5_KEY15_USE == 1 )
    MUTUAL5_KEY15_THR,
#endif
#if ( MUTUAL5_KEY16_USE == 1 )
    MUTUAL5_KEY16_THR,
#endif
#if ( MUTUAL5_KEY17_USE == 1 )
    MUTUAL5_KEY17_THR,
#endif
#if ( MUTUAL5_KEY18_USE == 1 )
    MUTUAL5_KEY18_THR,
#endif
#if ( MUTUAL5_KEY19_USE == 1 )
    MUTUAL5_KEY19_THR,
#endif
#if ( MUTUAL5_KEY20_USE == 1 )
    MUTUAL5_KEY20_THR,
#endif
#if ( MUTUAL5_KEY21_USE == 1 )
    MUTUAL5_KEY21_THR,
#endif
#if ( MUTUAL5_KEY22_USE == 1 )
    MUTUAL5_KEY22_THR,
#endif
#if ( MUTUAL5_KEY23_USE == 1 )
    MUTUAL5_KEY23_THR,
#endif
#if ( MUTUAL5_KEY24_USE == 1 )
    MUTUAL5_KEY24_THR,
#endif
#if ( MUTUAL5_KEY25_USE == 1 )
    MUTUAL5_KEY25_THR,
#endif
#if ( MUTUAL5_KEY26_USE == 1 )
    MUTUAL5_KEY26_THR,
#endif
#if ( MUTUAL5_KEY27_USE == 1 )
    MUTUAL5_KEY27_THR,
#endif
#if ( MUTUAL5_KEY28_USE == 1 )
    MUTUAL5_KEY28_THR,
#endif
#if ( MUTUAL5_KEY29_USE == 1 )
    MUTUAL5_KEY29_THR,
#endif
#if ( MUTUAL5_KEY30_USE == 1 )
    MUTUAL5_KEY30_THR,
#endif
#if ( MUTUAL5_KEY31_USE == 1 )
    MUTUAL5_KEY31_THR,
#endif
#if ( MUTUAL5_KEY32_USE == 1 )
    MUTUAL5_KEY32_THR,
#endif
#if ( MUTUAL5_KEY33_USE == 1 )
    MUTUAL5_KEY33_THR,
#endif
#if ( MUTUAL5_KEY34_USE == 1 )
    MUTUAL5_KEY34_THR,
#endif
#if ( MUTUAL5_KEY35_USE == 1 )
    MUTUAL5_KEY35_THR,
#endif
#if ( MUTUAL5_KEY36_USE == 1 )
    MUTUAL5_KEY36_THR,
#endif
#if ( MUTUAL5_KEY37_USE == 1 )
    MUTUAL5_KEY37_THR,
#endif
#if ( MUTUAL5_KEY38_USE == 1 )
    MUTUAL5_KEY38_THR,
#endif
#if ( MUTUAL5_KEY39_USE == 1 )
    MUTUAL5_KEY39_THR,
#endif
#if ( MUTUAL5_KEY40_USE == 1 )
    MUTUAL5_KEY40_THR,
#endif
#if ( MUTUAL5_KEY41_USE == 1 )
    MUTUAL5_KEY41_THR,
#endif
#if ( MUTUAL5_KEY42_USE == 1 )
    MUTUAL5_KEY42_THR,
#endif
#if ( MUTUAL5_KEY43_USE == 1 )
    MUTUAL5_KEY43_THR,
#endif
#if ( MUTUAL5_KEY44_USE == 1 )
    MUTUAL5_KEY44_THR,
#endif
#if ( MUTUAL5_KEY45_USE == 1 )
    MUTUAL5_KEY45_THR,
#endif
#if ( MUTUAL5_KEY46_USE == 1 )
    MUTUAL5_KEY46_THR,
#endif
#if ( MUTUAL5_KEY47_USE == 1 )
    MUTUAL5_KEY47_THR,
#endif
#if ( MUTUAL5_KEY48_USE == 1 )
    MUTUAL5_KEY48_THR,
#endif
#if ( MUTUAL5_KEY49_USE == 1 )
    MUTUAL5_KEY49_THR,
#endif
#if ( MUTUAL5_KEY50_USE == 1 )
    MUTUAL5_KEY50_THR,
#endif
#if ( MUTUAL5_KEY51_USE == 1 )
    MUTUAL5_KEY51_THR,
#endif
#if ( MUTUAL5_KEY52_USE == 1 )
    MUTUAL5_KEY52_THR,
#endif
#if ( MUTUAL5_KEY53_USE == 1 )
    MUTUAL5_KEY53_THR,
#endif
#if ( MUTUAL5_KEY54_USE == 1 )
    MUTUAL5_KEY54_THR,
#endif
#if ( MUTUAL5_KEY55_USE == 1 )
    MUTUAL5_KEY55_THR,
#endif
#if ( MUTUAL5_KEY56_USE == 1 )
    MUTUAL5_KEY56_THR,
#endif
#if ( MUTUAL5_KEY57_USE == 1 )
    MUTUAL5_KEY57_THR,
#endif
#if ( MUTUAL5_KEY58_USE == 1 )
    MUTUAL5_KEY58_THR,
#endif
#if ( MUTUAL5_KEY59_USE == 1 )
    MUTUAL5_KEY59_THR,
#endif
#if ( MUTUAL5_KEY60_USE == 1 )
    MUTUAL5_KEY60_THR,
#endif
#if ( MUTUAL5_KEY61_USE == 1 )
    MUTUAL5_KEY61_THR,
#endif
#if ( MUTUAL5_KEY62_USE == 1 )
    MUTUAL5_KEY62_THR,
#endif
#if ( MUTUAL5_KEY63_USE == 1 )
    MUTUAL5_KEY63_THR,
#endif
};

const uint16_t g_mutual5_hysbuff[] =
{
#if ( MUTUAL5_KEY00_USE == 1 )
    MUTUAL5_KEY00_HYS,
#endif
#if ( MUTUAL5_KEY01_USE == 1 )
    MUTUAL5_KEY01_HYS,
#endif
#if ( MUTUAL5_KEY02_USE == 1 )
    MUTUAL5_KEY02_HYS,
#endif
#if ( MUTUAL5_KEY03_USE == 1 )
    MUTUAL5_KEY03_HYS,
#endif
#if ( MUTUAL5_KEY04_USE == 1 )
    MUTUAL5_KEY04_HYS,
#endif
#if ( MUTUAL5_KEY05_USE == 1 )
    MUTUAL5_KEY05_HYS,
#endif
#if ( MUTUAL5_KEY06_USE == 1 )
    MUTUAL5_KEY06_HYS,
#endif
#if ( MUTUAL5_KEY07_USE == 1 )
    MUTUAL5_KEY07_HYS,
#endif
#if ( MUTUAL5_KEY08_USE == 1 )
    MUTUAL5_KEY08_HYS,
#endif
#if ( MUTUAL5_KEY09_USE == 1 )
    MUTUAL5_KEY09_HYS,
#endif
#if ( MUTUAL5_KEY10_USE == 1 )
    MUTUAL5_KEY10_HYS,
#endif
#if ( MUTUAL5_KEY11_USE == 1 )
    MUTUAL5_KEY11_HYS,
#endif
#if ( MUTUAL5_KEY12_USE == 1 )
    MUTUAL5_KEY12_HYS,
#endif
#if ( MUTUAL5_KEY13_USE == 1 )
    MUTUAL5_KEY13_HYS,
#endif
#if ( MUTUAL5_KEY14_USE == 1 )
    MUTUAL5_KEY14_HYS,
#endif
#if ( MUTUAL5_KEY15_USE == 1 )
    MUTUAL5_KEY15_HYS,
#endif
#if ( MUTUAL5_KEY16_USE == 1 )
    MUTUAL5_KEY16_HYS,
#endif
#if ( MUTUAL5_KEY17_USE == 1 )
    MUTUAL5_KEY17_HYS,
#endif
#if ( MUTUAL5_KEY18_USE == 1 )
    MUTUAL5_KEY18_HYS,
#endif
#if ( MUTUAL5_KEY19_USE == 1 )
    MUTUAL5_KEY19_HYS,
#endif
#if ( MUTUAL5_KEY20_USE == 1 )
    MUTUAL5_KEY20_HYS,
#endif
#if ( MUTUAL5_KEY21_USE == 1 )
    MUTUAL5_KEY21_HYS,
#endif
#if ( MUTUAL5_KEY22_USE == 1 )
    MUTUAL5_KEY22_HYS,
#endif
#if ( MUTUAL5_KEY23_USE == 1 )
    MUTUAL5_KEY23_HYS,
#endif
#if ( MUTUAL5_KEY24_USE == 1 )
    MUTUAL5_KEY24_HYS,
#endif
#if ( MUTUAL5_KEY25_USE == 1 )
    MUTUAL5_KEY25_HYS,
#endif
#if ( MUTUAL5_KEY26_USE == 1 )
    MUTUAL5_KEY26_HYS,
#endif
#if ( MUTUAL5_KEY27_USE == 1 )
    MUTUAL5_KEY27_HYS,
#endif
#if ( MUTUAL5_KEY28_USE == 1 )
    MUTUAL5_KEY28_HYS,
#endif
#if ( MUTUAL5_KEY29_USE == 1 )
    MUTUAL5_KEY29_HYS,
#endif
#if ( MUTUAL5_KEY30_USE == 1 )
    MUTUAL5_KEY30_HYS,
#endif
#if ( MUTUAL5_KEY31_USE == 1 )
    MUTUAL5_KEY31_HYS,
#endif
#if ( MUTUAL5_KEY32_USE == 1 )
    MUTUAL5_KEY32_HYS,
#endif
#if ( MUTUAL5_KEY33_USE == 1 )
    MUTUAL5_KEY33_HYS,
#endif
#if ( MUTUAL5_KEY34_USE == 1 )
    MUTUAL5_KEY34_HYS,
#endif
#if ( MUTUAL5_KEY35_USE == 1 )
    MUTUAL5_KEY35_HYS,
#endif
#if ( MUTUAL5_KEY36_USE == 1 )
    MUTUAL5_KEY36_HYS,
#endif
#if ( MUTUAL5_KEY37_USE == 1 )
    MUTUAL5_KEY37_HYS,
#endif
#if ( MUTUAL5_KEY38_USE == 1 )
    MUTUAL5_KEY38_HYS,
#endif
#if ( MUTUAL5_KEY39_USE == 1 )
    MUTUAL5_KEY39_HYS,
#endif
#if ( MUTUAL5_KEY40_USE == 1 )
    MUTUAL5_KEY40_HYS,
#endif
#if ( MUTUAL5_KEY41_USE == 1 )
    MUTUAL5_KEY41_HYS,
#endif
#if ( MUTUAL5_KEY42_USE == 1 )
    MUTUAL5_KEY42_HYS,
#endif
#if ( MUTUAL5_KEY43_USE == 1 )
    MUTUAL5_KEY43_HYS,
#endif
#if ( MUTUAL5_KEY44_USE == 1 )
    MUTUAL5_KEY44_HYS,
#endif
#if ( MUTUAL5_KEY45_USE == 1 )
    MUTUAL5_KEY45_HYS,
#endif
#if ( MUTUAL5_KEY46_USE == 1 )
    MUTUAL5_KEY46_HYS,
#endif
#if ( MUTUAL5_KEY47_USE == 1 )
    MUTUAL5_KEY47_HYS,
#endif
#if ( MUTUAL5_KEY48_USE == 1 )
    MUTUAL5_KEY48_HYS,
#endif
#if ( MUTUAL5_KEY49_USE == 1 )
    MUTUAL5_KEY49_HYS,
#endif
#if ( MUTUAL5_KEY50_USE == 1 )
    MUTUAL5_KEY50_HYS,
#endif
#if ( MUTUAL5_KEY51_USE == 1 )
    MUTUAL5_KEY51_HYS,
#endif
#if ( MUTUAL5_KEY52_USE == 1 )
    MUTUAL5_KEY52_HYS,
#endif
#if ( MUTUAL5_KEY53_USE == 1 )
    MUTUAL5_KEY53_HYS,
#endif
#if ( MUTUAL5_KEY54_USE == 1 )
    MUTUAL5_KEY54_HYS,
#endif
#if ( MUTUAL5_KEY55_USE == 1 )
    MUTUAL5_KEY55_HYS,
#endif
#if ( MUTUAL5_KEY56_USE == 1 )
    MUTUAL5_KEY56_HYS,
#endif
#if ( MUTUAL5_KEY57_USE == 1 )
    MUTUAL5_KEY57_HYS,
#endif
#if ( MUTUAL5_KEY58_USE == 1 )
    MUTUAL5_KEY58_HYS,
#endif
#if ( MUTUAL5_KEY59_USE == 1 )
    MUTUAL5_KEY59_HYS,
#endif
#if ( MUTUAL5_KEY60_USE == 1 )
    MUTUAL5_KEY60_HYS,
#endif
#if ( MUTUAL5_KEY61_USE == 1 )
    MUTUAL5_KEY61_HYS,
#endif
#if ( MUTUAL5_KEY62_USE == 1 )
    MUTUAL5_KEY62_HYS,
#endif
#if ( MUTUAL5_KEY63_USE == 1 )
    MUTUAL5_KEY63_HYS,
#endif
};
#endif// ( MUTUAL_METHOD_NUM > 5 )

/*====================================================================================================================*/
/*=====    Mutual 6 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 6 )
const uint16_t g_mutual6_thrbuff[] =
{
#if ( MUTUAL6_KEY00_USE == 1 )
    MUTUAL6_KEY00_THR,
#endif
#if ( MUTUAL6_KEY01_USE == 1 )
    MUTUAL6_KEY01_THR,
#endif
#if ( MUTUAL6_KEY02_USE == 1 )
    MUTUAL6_KEY02_THR,
#endif
#if ( MUTUAL6_KEY03_USE == 1 )
    MUTUAL6_KEY03_THR,
#endif
#if ( MUTUAL6_KEY04_USE == 1 )
    MUTUAL6_KEY04_THR,
#endif
#if ( MUTUAL6_KEY05_USE == 1 )
    MUTUAL6_KEY05_THR,
#endif
#if ( MUTUAL6_KEY06_USE == 1 )
    MUTUAL6_KEY06_THR,
#endif
#if ( MUTUAL6_KEY07_USE == 1 )
    MUTUAL6_KEY07_THR,
#endif
#if ( MUTUAL6_KEY08_USE == 1 )
    MUTUAL6_KEY08_THR,
#endif
#if ( MUTUAL6_KEY09_USE == 1 )
    MUTUAL6_KEY09_THR,
#endif
#if ( MUTUAL6_KEY10_USE == 1 )
    MUTUAL6_KEY10_THR,
#endif
#if ( MUTUAL6_KEY11_USE == 1 )
    MUTUAL6_KEY11_THR,
#endif
#if ( MUTUAL6_KEY12_USE == 1 )
    MUTUAL6_KEY12_THR,
#endif
#if ( MUTUAL6_KEY13_USE == 1 )
    MUTUAL6_KEY13_THR,
#endif
#if ( MUTUAL6_KEY14_USE == 1 )
    MUTUAL6_KEY14_THR,
#endif
#if ( MUTUAL6_KEY15_USE == 1 )
    MUTUAL6_KEY15_THR,
#endif
#if ( MUTUAL6_KEY16_USE == 1 )
    MUTUAL6_KEY16_THR,
#endif
#if ( MUTUAL6_KEY17_USE == 1 )
    MUTUAL6_KEY17_THR,
#endif
#if ( MUTUAL6_KEY18_USE == 1 )
    MUTUAL6_KEY18_THR,
#endif
#if ( MUTUAL6_KEY19_USE == 1 )
    MUTUAL6_KEY19_THR,
#endif
#if ( MUTUAL6_KEY20_USE == 1 )
    MUTUAL6_KEY20_THR,
#endif
#if ( MUTUAL6_KEY21_USE == 1 )
    MUTUAL6_KEY21_THR,
#endif
#if ( MUTUAL6_KEY22_USE == 1 )
    MUTUAL6_KEY22_THR,
#endif
#if ( MUTUAL6_KEY23_USE == 1 )
    MUTUAL6_KEY23_THR,
#endif
#if ( MUTUAL6_KEY24_USE == 1 )
    MUTUAL6_KEY24_THR,
#endif
#if ( MUTUAL6_KEY25_USE == 1 )
    MUTUAL6_KEY25_THR,
#endif
#if ( MUTUAL6_KEY26_USE == 1 )
    MUTUAL6_KEY26_THR,
#endif
#if ( MUTUAL6_KEY27_USE == 1 )
    MUTUAL6_KEY27_THR,
#endif
#if ( MUTUAL6_KEY28_USE == 1 )
    MUTUAL6_KEY28_THR,
#endif
#if ( MUTUAL6_KEY29_USE == 1 )
    MUTUAL6_KEY29_THR,
#endif
#if ( MUTUAL6_KEY30_USE == 1 )
    MUTUAL6_KEY30_THR,
#endif
#if ( MUTUAL6_KEY31_USE == 1 )
    MUTUAL6_KEY31_THR,
#endif
#if ( MUTUAL6_KEY32_USE == 1 )
    MUTUAL6_KEY32_THR,
#endif
#if ( MUTUAL6_KEY33_USE == 1 )
    MUTUAL6_KEY33_THR,
#endif
#if ( MUTUAL6_KEY34_USE == 1 )
    MUTUAL6_KEY34_THR,
#endif
#if ( MUTUAL6_KEY35_USE == 1 )
    MUTUAL6_KEY35_THR,
#endif
#if ( MUTUAL6_KEY36_USE == 1 )
    MUTUAL6_KEY36_THR,
#endif
#if ( MUTUAL6_KEY37_USE == 1 )
    MUTUAL6_KEY37_THR,
#endif
#if ( MUTUAL6_KEY38_USE == 1 )
    MUTUAL6_KEY38_THR,
#endif
#if ( MUTUAL6_KEY39_USE == 1 )
    MUTUAL6_KEY39_THR,
#endif
#if ( MUTUAL6_KEY40_USE == 1 )
    MUTUAL6_KEY40_THR,
#endif
#if ( MUTUAL6_KEY41_USE == 1 )
    MUTUAL6_KEY41_THR,
#endif
#if ( MUTUAL6_KEY42_USE == 1 )
    MUTUAL6_KEY42_THR,
#endif
#if ( MUTUAL6_KEY43_USE == 1 )
    MUTUAL6_KEY43_THR,
#endif
#if ( MUTUAL6_KEY44_USE == 1 )
    MUTUAL6_KEY44_THR,
#endif
#if ( MUTUAL6_KEY45_USE == 1 )
    MUTUAL6_KEY45_THR,
#endif
#if ( MUTUAL6_KEY46_USE == 1 )
    MUTUAL6_KEY46_THR,
#endif
#if ( MUTUAL6_KEY47_USE == 1 )
    MUTUAL6_KEY47_THR,
#endif
#if ( MUTUAL6_KEY48_USE == 1 )
    MUTUAL6_KEY48_THR,
#endif
#if ( MUTUAL6_KEY49_USE == 1 )
    MUTUAL6_KEY49_THR,
#endif
#if ( MUTUAL6_KEY50_USE == 1 )
    MUTUAL6_KEY50_THR,
#endif
#if ( MUTUAL6_KEY51_USE == 1 )
    MUTUAL6_KEY51_THR,
#endif
#if ( MUTUAL6_KEY52_USE == 1 )
    MUTUAL6_KEY52_THR,
#endif
#if ( MUTUAL6_KEY53_USE == 1 )
    MUTUAL6_KEY53_THR,
#endif
#if ( MUTUAL6_KEY54_USE == 1 )
    MUTUAL6_KEY54_THR,
#endif
#if ( MUTUAL6_KEY55_USE == 1 )
    MUTUAL6_KEY55_THR,
#endif
#if ( MUTUAL6_KEY56_USE == 1 )
    MUTUAL6_KEY56_THR,
#endif
#if ( MUTUAL6_KEY57_USE == 1 )
    MUTUAL6_KEY57_THR,
#endif
#if ( MUTUAL6_KEY58_USE == 1 )
    MUTUAL6_KEY58_THR,
#endif
#if ( MUTUAL6_KEY59_USE == 1 )
    MUTUAL6_KEY59_THR,
#endif
#if ( MUTUAL6_KEY60_USE == 1 )
    MUTUAL6_KEY60_THR,
#endif
#if ( MUTUAL6_KEY61_USE == 1 )
    MUTUAL6_KEY61_THR,
#endif
#if ( MUTUAL6_KEY62_USE == 1 )
    MUTUAL6_KEY62_THR,
#endif
#if ( MUTUAL6_KEY63_USE == 1 )
    MUTUAL6_KEY63_THR,
#endif
};

const uint16_t g_mutual6_hysbuff[] =
{
#if ( MUTUAL6_KEY00_USE == 1 )
    MUTUAL6_KEY00_HYS,
#endif
#if ( MUTUAL6_KEY01_USE == 1 )
    MUTUAL6_KEY01_HYS,
#endif
#if ( MUTUAL6_KEY02_USE == 1 )
    MUTUAL6_KEY02_HYS,
#endif
#if ( MUTUAL6_KEY03_USE == 1 )
    MUTUAL6_KEY03_HYS,
#endif
#if ( MUTUAL6_KEY04_USE == 1 )
    MUTUAL6_KEY04_HYS,
#endif
#if ( MUTUAL6_KEY05_USE == 1 )
    MUTUAL6_KEY05_HYS,
#endif
#if ( MUTUAL6_KEY06_USE == 1 )
    MUTUAL6_KEY06_HYS,
#endif
#if ( MUTUAL6_KEY07_USE == 1 )
    MUTUAL6_KEY07_HYS,
#endif
#if ( MUTUAL6_KEY08_USE == 1 )
    MUTUAL6_KEY08_HYS,
#endif
#if ( MUTUAL6_KEY09_USE == 1 )
    MUTUAL6_KEY09_HYS,
#endif
#if ( MUTUAL6_KEY10_USE == 1 )
    MUTUAL6_KEY10_HYS,
#endif
#if ( MUTUAL6_KEY11_USE == 1 )
    MUTUAL6_KEY11_HYS,
#endif
#if ( MUTUAL6_KEY12_USE == 1 )
    MUTUAL6_KEY12_HYS,
#endif
#if ( MUTUAL6_KEY13_USE == 1 )
    MUTUAL6_KEY13_HYS,
#endif
#if ( MUTUAL6_KEY14_USE == 1 )
    MUTUAL6_KEY14_HYS,
#endif
#if ( MUTUAL6_KEY15_USE == 1 )
    MUTUAL6_KEY15_HYS,
#endif
#if ( MUTUAL6_KEY16_USE == 1 )
    MUTUAL6_KEY16_HYS,
#endif
#if ( MUTUAL6_KEY17_USE == 1 )
    MUTUAL6_KEY17_HYS,
#endif
#if ( MUTUAL6_KEY18_USE == 1 )
    MUTUAL6_KEY18_HYS,
#endif
#if ( MUTUAL6_KEY19_USE == 1 )
    MUTUAL6_KEY19_HYS,
#endif
#if ( MUTUAL6_KEY20_USE == 1 )
    MUTUAL6_KEY20_HYS,
#endif
#if ( MUTUAL6_KEY21_USE == 1 )
    MUTUAL6_KEY21_HYS,
#endif
#if ( MUTUAL6_KEY22_USE == 1 )
    MUTUAL6_KEY22_HYS,
#endif
#if ( MUTUAL6_KEY23_USE == 1 )
    MUTUAL6_KEY23_HYS,
#endif
#if ( MUTUAL6_KEY24_USE == 1 )
    MUTUAL6_KEY24_HYS,
#endif
#if ( MUTUAL6_KEY25_USE == 1 )
    MUTUAL6_KEY25_HYS,
#endif
#if ( MUTUAL6_KEY26_USE == 1 )
    MUTUAL6_KEY26_HYS,
#endif
#if ( MUTUAL6_KEY27_USE == 1 )
    MUTUAL6_KEY27_HYS,
#endif
#if ( MUTUAL6_KEY28_USE == 1 )
    MUTUAL6_KEY28_HYS,
#endif
#if ( MUTUAL6_KEY29_USE == 1 )
    MUTUAL6_KEY29_HYS,
#endif
#if ( MUTUAL6_KEY30_USE == 1 )
    MUTUAL6_KEY30_HYS,
#endif
#if ( MUTUAL6_KEY31_USE == 1 )
    MUTUAL6_KEY31_HYS,
#endif
#if ( MUTUAL6_KEY32_USE == 1 )
    MUTUAL6_KEY32_HYS,
#endif
#if ( MUTUAL6_KEY33_USE == 1 )
    MUTUAL6_KEY33_HYS,
#endif
#if ( MUTUAL6_KEY34_USE == 1 )
    MUTUAL6_KEY34_HYS,
#endif
#if ( MUTUAL6_KEY35_USE == 1 )
    MUTUAL6_KEY35_HYS,
#endif
#if ( MUTUAL6_KEY36_USE == 1 )
    MUTUAL6_KEY36_HYS,
#endif
#if ( MUTUAL6_KEY37_USE == 1 )
    MUTUAL6_KEY37_HYS,
#endif
#if ( MUTUAL6_KEY38_USE == 1 )
    MUTUAL6_KEY38_HYS,
#endif
#if ( MUTUAL6_KEY39_USE == 1 )
    MUTUAL6_KEY39_HYS,
#endif
#if ( MUTUAL6_KEY40_USE == 1 )
    MUTUAL6_KEY40_HYS,
#endif
#if ( MUTUAL6_KEY41_USE == 1 )
    MUTUAL6_KEY41_HYS,
#endif
#if ( MUTUAL6_KEY42_USE == 1 )
    MUTUAL6_KEY42_HYS,
#endif
#if ( MUTUAL6_KEY43_USE == 1 )
    MUTUAL6_KEY43_HYS,
#endif
#if ( MUTUAL6_KEY44_USE == 1 )
    MUTUAL6_KEY44_HYS,
#endif
#if ( MUTUAL6_KEY45_USE == 1 )
    MUTUAL6_KEY45_HYS,
#endif
#if ( MUTUAL6_KEY46_USE == 1 )
    MUTUAL6_KEY46_HYS,
#endif
#if ( MUTUAL6_KEY47_USE == 1 )
    MUTUAL6_KEY47_HYS,
#endif
#if ( MUTUAL6_KEY48_USE == 1 )
    MUTUAL6_KEY48_HYS,
#endif
#if ( MUTUAL6_KEY49_USE == 1 )
    MUTUAL6_KEY49_HYS,
#endif
#if ( MUTUAL6_KEY50_USE == 1 )
    MUTUAL6_KEY50_HYS,
#endif
#if ( MUTUAL6_KEY51_USE == 1 )
    MUTUAL6_KEY51_HYS,
#endif
#if ( MUTUAL6_KEY52_USE == 1 )
    MUTUAL6_KEY52_HYS,
#endif
#if ( MUTUAL6_KEY53_USE == 1 )
    MUTUAL6_KEY53_HYS,
#endif
#if ( MUTUAL6_KEY54_USE == 1 )
    MUTUAL6_KEY54_HYS,
#endif
#if ( MUTUAL6_KEY55_USE == 1 )
    MUTUAL6_KEY55_HYS,
#endif
#if ( MUTUAL6_KEY56_USE == 1 )
    MUTUAL6_KEY56_HYS,
#endif
#if ( MUTUAL6_KEY57_USE == 1 )
    MUTUAL6_KEY57_HYS,
#endif
#if ( MUTUAL6_KEY58_USE == 1 )
    MUTUAL6_KEY58_HYS,
#endif
#if ( MUTUAL6_KEY59_USE == 1 )
    MUTUAL6_KEY59_HYS,
#endif
#if ( MUTUAL6_KEY60_USE == 1 )
    MUTUAL6_KEY60_HYS,
#endif
#if ( MUTUAL6_KEY61_USE == 1 )
    MUTUAL6_KEY61_HYS,
#endif
#if ( MUTUAL6_KEY62_USE == 1 )
    MUTUAL6_KEY62_HYS,
#endif
#if ( MUTUAL6_KEY63_USE == 1 )
    MUTUAL6_KEY63_HYS,
#endif
};
#endif// ( MUTUAL_METHOD_NUM > 6 )

/*====================================================================================================================*/
/*=====    Mutual 7 touch parameter definition    ====================================================================*/
/*====================================================================================================================*/
/* Touch key parameter */
#if ( MUTUAL_METHOD_NUM > 7 )
const uint16_t g_mutual7_thrbuff[] =
{
#if ( MUTUAL7_KEY00_USE == 1 )
    MUTUAL7_KEY00_THR,
#endif
#if ( MUTUAL7_KEY01_USE == 1 )
    MUTUAL7_KEY01_THR,
#endif
#if ( MUTUAL7_KEY02_USE == 1 )
    MUTUAL7_KEY02_THR,
#endif
#if ( MUTUAL7_KEY03_USE == 1 )
    MUTUAL7_KEY03_THR,
#endif
#if ( MUTUAL7_KEY04_USE == 1 )
    MUTUAL7_KEY04_THR,
#endif
#if ( MUTUAL7_KEY05_USE == 1 )
    MUTUAL7_KEY05_THR,
#endif
#if ( MUTUAL7_KEY06_USE == 1 )
    MUTUAL7_KEY06_THR,
#endif
#if ( MUTUAL7_KEY07_USE == 1 )
    MUTUAL7_KEY07_THR,
#endif
#if ( MUTUAL7_KEY08_USE == 1 )
    MUTUAL7_KEY08_THR,
#endif
#if ( MUTUAL7_KEY09_USE == 1 )
    MUTUAL7_KEY09_THR,
#endif
#if ( MUTUAL7_KEY10_USE == 1 )
    MUTUAL7_KEY10_THR,
#endif
#if ( MUTUAL7_KEY11_USE == 1 )
    MUTUAL7_KEY11_THR,
#endif
#if ( MUTUAL7_KEY12_USE == 1 )
    MUTUAL7_KEY12_THR,
#endif
#if ( MUTUAL7_KEY13_USE == 1 )
    MUTUAL7_KEY13_THR,
#endif
#if ( MUTUAL7_KEY14_USE == 1 )
    MUTUAL7_KEY14_THR,
#endif
#if ( MUTUAL7_KEY15_USE == 1 )
    MUTUAL7_KEY15_THR,
#endif
#if ( MUTUAL7_KEY16_USE == 1 )
    MUTUAL7_KEY16_THR,
#endif
#if ( MUTUAL7_KEY17_USE == 1 )
    MUTUAL7_KEY17_THR,
#endif
#if ( MUTUAL7_KEY18_USE == 1 )
    MUTUAL7_KEY18_THR,
#endif
#if ( MUTUAL7_KEY19_USE == 1 )
    MUTUAL7_KEY19_THR,
#endif
#if ( MUTUAL7_KEY20_USE == 1 )
    MUTUAL7_KEY20_THR,
#endif
#if ( MUTUAL7_KEY21_USE == 1 )
    MUTUAL7_KEY21_THR,
#endif
#if ( MUTUAL7_KEY22_USE == 1 )
    MUTUAL7_KEY22_THR,
#endif
#if ( MUTUAL7_KEY23_USE == 1 )
    MUTUAL7_KEY23_THR,
#endif
#if ( MUTUAL7_KEY24_USE == 1 )
    MUTUAL7_KEY24_THR,
#endif
#if ( MUTUAL7_KEY25_USE == 1 )
    MUTUAL7_KEY25_THR,
#endif
#if ( MUTUAL7_KEY26_USE == 1 )
    MUTUAL7_KEY26_THR,
#endif
#if ( MUTUAL7_KEY27_USE == 1 )
    MUTUAL7_KEY27_THR,
#endif
#if ( MUTUAL7_KEY28_USE == 1 )
    MUTUAL7_KEY28_THR,
#endif
#if ( MUTUAL7_KEY29_USE == 1 )
    MUTUAL7_KEY29_THR,
#endif
#if ( MUTUAL7_KEY30_USE == 1 )
    MUTUAL7_KEY30_THR,
#endif
#if ( MUTUAL7_KEY31_USE == 1 )
    MUTUAL7_KEY31_THR,
#endif
#if ( MUTUAL7_KEY32_USE == 1 )
    MUTUAL7_KEY32_THR,
#endif
#if ( MUTUAL7_KEY33_USE == 1 )
    MUTUAL7_KEY33_THR,
#endif
#if ( MUTUAL7_KEY34_USE == 1 )
    MUTUAL7_KEY34_THR,
#endif
#if ( MUTUAL7_KEY35_USE == 1 )
    MUTUAL7_KEY35_THR,
#endif
#if ( MUTUAL7_KEY36_USE == 1 )
    MUTUAL7_KEY36_THR,
#endif
#if ( MUTUAL7_KEY37_USE == 1 )
    MUTUAL7_KEY37_THR,
#endif
#if ( MUTUAL7_KEY38_USE == 1 )
    MUTUAL7_KEY38_THR,
#endif
#if ( MUTUAL7_KEY39_USE == 1 )
    MUTUAL7_KEY39_THR,
#endif
#if ( MUTUAL7_KEY40_USE == 1 )
    MUTUAL7_KEY40_THR,
#endif
#if ( MUTUAL7_KEY41_USE == 1 )
    MUTUAL7_KEY41_THR,
#endif
#if ( MUTUAL7_KEY42_USE == 1 )
    MUTUAL7_KEY42_THR,
#endif
#if ( MUTUAL7_KEY43_USE == 1 )
    MUTUAL7_KEY43_THR,
#endif
#if ( MUTUAL7_KEY44_USE == 1 )
    MUTUAL7_KEY44_THR,
#endif
#if ( MUTUAL7_KEY45_USE == 1 )
    MUTUAL7_KEY45_THR,
#endif
#if ( MUTUAL7_KEY46_USE == 1 )
    MUTUAL7_KEY46_THR,
#endif
#if ( MUTUAL7_KEY47_USE == 1 )
    MUTUAL7_KEY47_THR,
#endif
#if ( MUTUAL7_KEY48_USE == 1 )
    MUTUAL7_KEY48_THR,
#endif
#if ( MUTUAL7_KEY49_USE == 1 )
    MUTUAL7_KEY49_THR,
#endif
#if ( MUTUAL7_KEY50_USE == 1 )
    MUTUAL7_KEY50_THR,
#endif
#if ( MUTUAL7_KEY51_USE == 1 )
    MUTUAL7_KEY51_THR,
#endif
#if ( MUTUAL7_KEY52_USE == 1 )
    MUTUAL7_KEY52_THR,
#endif
#if ( MUTUAL7_KEY53_USE == 1 )
    MUTUAL7_KEY53_THR,
#endif
#if ( MUTUAL7_KEY54_USE == 1 )
    MUTUAL7_KEY54_THR,
#endif
#if ( MUTUAL7_KEY55_USE == 1 )
    MUTUAL7_KEY55_THR,
#endif
#if ( MUTUAL7_KEY56_USE == 1 )
    MUTUAL7_KEY56_THR,
#endif
#if ( MUTUAL7_KEY57_USE == 1 )
    MUTUAL7_KEY57_THR,
#endif
#if ( MUTUAL7_KEY58_USE == 1 )
    MUTUAL7_KEY58_THR,
#endif
#if ( MUTUAL7_KEY59_USE == 1 )
    MUTUAL7_KEY59_THR,
#endif
#if ( MUTUAL7_KEY60_USE == 1 )
    MUTUAL7_KEY60_THR,
#endif
#if ( MUTUAL7_KEY61_USE == 1 )
    MUTUAL7_KEY61_THR,
#endif
#if ( MUTUAL7_KEY62_USE == 1 )
    MUTUAL7_KEY62_THR,
#endif
#if ( MUTUAL7_KEY63_USE == 1 )
    MUTUAL7_KEY63_THR,
#endif
};

const uint16_t g_mutual7_hysbuff[] =
{
#if ( MUTUAL7_KEY00_USE == 1 )
    MUTUAL7_KEY00_HYS,
#endif
#if ( MUTUAL7_KEY01_USE == 1 )
    MUTUAL7_KEY01_HYS,
#endif
#if ( MUTUAL7_KEY02_USE == 1 )
    MUTUAL7_KEY02_HYS,
#endif
#if ( MUTUAL7_KEY03_USE == 1 )
    MUTUAL7_KEY03_HYS,
#endif
#if ( MUTUAL7_KEY04_USE == 1 )
    MUTUAL7_KEY04_HYS,
#endif
#if ( MUTUAL7_KEY05_USE == 1 )
    MUTUAL7_KEY05_HYS,
#endif
#if ( MUTUAL7_KEY06_USE == 1 )
    MUTUAL7_KEY06_HYS,
#endif
#if ( MUTUAL7_KEY07_USE == 1 )
    MUTUAL7_KEY07_HYS,
#endif
#if ( MUTUAL7_KEY08_USE == 1 )
    MUTUAL7_KEY08_HYS,
#endif
#if ( MUTUAL7_KEY09_USE == 1 )
    MUTUAL7_KEY09_HYS,
#endif
#if ( MUTUAL7_KEY10_USE == 1 )
    MUTUAL7_KEY10_HYS,
#endif
#if ( MUTUAL7_KEY11_USE == 1 )
    MUTUAL7_KEY11_HYS,
#endif
#if ( MUTUAL7_KEY12_USE == 1 )
    MUTUAL7_KEY12_HYS,
#endif
#if ( MUTUAL7_KEY13_USE == 1 )
    MUTUAL7_KEY13_HYS,
#endif
#if ( MUTUAL7_KEY14_USE == 1 )
    MUTUAL7_KEY14_HYS,
#endif
#if ( MUTUAL7_KEY15_USE == 1 )
    MUTUAL7_KEY15_HYS,
#endif
#if ( MUTUAL7_KEY16_USE == 1 )
    MUTUAL7_KEY16_HYS,
#endif
#if ( MUTUAL7_KEY17_USE == 1 )
    MUTUAL7_KEY17_HYS,
#endif
#if ( MUTUAL7_KEY18_USE == 1 )
    MUTUAL7_KEY18_HYS,
#endif
#if ( MUTUAL7_KEY19_USE == 1 )
    MUTUAL7_KEY19_HYS,
#endif
#if ( MUTUAL7_KEY20_USE == 1 )
    MUTUAL7_KEY20_HYS,
#endif
#if ( MUTUAL7_KEY21_USE == 1 )
    MUTUAL7_KEY21_HYS,
#endif
#if ( MUTUAL7_KEY22_USE == 1 )
    MUTUAL7_KEY22_HYS,
#endif
#if ( MUTUAL7_KEY23_USE == 1 )
    MUTUAL7_KEY23_HYS,
#endif
#if ( MUTUAL7_KEY24_USE == 1 )
    MUTUAL7_KEY24_HYS,
#endif
#if ( MUTUAL7_KEY25_USE == 1 )
    MUTUAL7_KEY25_HYS,
#endif
#if ( MUTUAL7_KEY26_USE == 1 )
    MUTUAL7_KEY26_HYS,
#endif
#if ( MUTUAL7_KEY27_USE == 1 )
    MUTUAL7_KEY27_HYS,
#endif
#if ( MUTUAL7_KEY28_USE == 1 )
    MUTUAL7_KEY28_HYS,
#endif
#if ( MUTUAL7_KEY29_USE == 1 )
    MUTUAL7_KEY29_HYS,
#endif
#if ( MUTUAL7_KEY30_USE == 1 )
    MUTUAL7_KEY30_HYS,
#endif
#if ( MUTUAL7_KEY31_USE == 1 )
    MUTUAL7_KEY31_HYS,
#endif
#if ( MUTUAL7_KEY32_USE == 1 )
    MUTUAL7_KEY32_HYS,
#endif
#if ( MUTUAL7_KEY33_USE == 1 )
    MUTUAL7_KEY33_HYS,
#endif
#if ( MUTUAL7_KEY34_USE == 1 )
    MUTUAL7_KEY34_HYS,
#endif
#if ( MUTUAL7_KEY35_USE == 1 )
    MUTUAL7_KEY35_HYS,
#endif
#if ( MUTUAL7_KEY36_USE == 1 )
    MUTUAL7_KEY36_HYS,
#endif
#if ( MUTUAL7_KEY37_USE == 1 )
    MUTUAL7_KEY37_HYS,
#endif
#if ( MUTUAL7_KEY38_USE == 1 )
    MUTUAL7_KEY38_HYS,
#endif
#if ( MUTUAL7_KEY39_USE == 1 )
    MUTUAL7_KEY39_HYS,
#endif
#if ( MUTUAL7_KEY40_USE == 1 )
    MUTUAL7_KEY40_HYS,
#endif
#if ( MUTUAL7_KEY41_USE == 1 )
    MUTUAL7_KEY41_HYS,
#endif
#if ( MUTUAL7_KEY42_USE == 1 )
    MUTUAL7_KEY42_HYS,
#endif
#if ( MUTUAL7_KEY43_USE == 1 )
    MUTUAL7_KEY43_HYS,
#endif
#if ( MUTUAL7_KEY44_USE == 1 )
    MUTUAL7_KEY44_HYS,
#endif
#if ( MUTUAL7_KEY45_USE == 1 )
    MUTUAL7_KEY45_HYS,
#endif
#if ( MUTUAL7_KEY46_USE == 1 )
    MUTUAL7_KEY46_HYS,
#endif
#if ( MUTUAL7_KEY47_USE == 1 )
    MUTUAL7_KEY47_HYS,
#endif
#if ( MUTUAL7_KEY48_USE == 1 )
    MUTUAL7_KEY48_HYS,
#endif
#if ( MUTUAL7_KEY49_USE == 1 )
    MUTUAL7_KEY49_HYS,
#endif
#if ( MUTUAL7_KEY50_USE == 1 )
    MUTUAL7_KEY50_HYS,
#endif
#if ( MUTUAL7_KEY51_USE == 1 )
    MUTUAL7_KEY51_HYS,
#endif
#if ( MUTUAL7_KEY52_USE == 1 )
    MUTUAL7_KEY52_HYS,
#endif
#if ( MUTUAL7_KEY53_USE == 1 )
    MUTUAL7_KEY53_HYS,
#endif
#if ( MUTUAL7_KEY54_USE == 1 )
    MUTUAL7_KEY54_HYS,
#endif
#if ( MUTUAL7_KEY55_USE == 1 )
    MUTUAL7_KEY55_HYS,
#endif
#if ( MUTUAL7_KEY56_USE == 1 )
    MUTUAL7_KEY56_HYS,
#endif
#if ( MUTUAL7_KEY57_USE == 1 )
    MUTUAL7_KEY57_HYS,
#endif
#if ( MUTUAL7_KEY58_USE == 1 )
    MUTUAL7_KEY58_HYS,
#endif
#if ( MUTUAL7_KEY59_USE == 1 )
    MUTUAL7_KEY59_HYS,
#endif
#if ( MUTUAL7_KEY60_USE == 1 )
    MUTUAL7_KEY60_HYS,
#endif
#if ( MUTUAL7_KEY61_USE == 1 )
    MUTUAL7_KEY61_HYS,
#endif
#if ( MUTUAL7_KEY62_USE == 1 )
    MUTUAL7_KEY62_HYS,
#endif
#if ( MUTUAL7_KEY63_USE == 1 )
    MUTUAL7_KEY63_HYS,
#endif
};
#endif// ( MUTUAL_METHOD_NUM > 7 )

/***********************************************************************************************************************
* End of File
***********************************************************************************************************************/
