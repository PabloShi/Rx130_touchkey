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
* File Name    : r_touch_API.h
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file includes the touch API.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/

#ifndef __TOUCH_API_H__    //[
#define __TOUCH_API_H__

#include "r_touch.h"

/***********************************************************************************************************************
* Macro definitions
***********************************************************************************************************************/
#ifdef __TOUCH_API_C__
    #define TOUCH_API_EXTERN
#else
    #define TOUCH_API_EXTERN    extern
#endif

#define _0_SUCCESS               (0)
#define _1_ERROR                 (1)

#define _0_RUN                   (0)
#define _1_FINISH                (1)

#define _0_STOP                  (0)
#define _1_START                 (1)

#define _0_NON_UPDATE            (0)
#define _1_UPDATE                (1)

#define _0_NON_TIMING            (0)
#define _1_TIMING                (1)

#define _0_SELF_MODE             (0)
#define _1_MUTUAL_MODE           (1)

#define METHOD_CHANGE_NG         0xFF

#define _00_GET_OK               0x00
#define _01_GET_NG               0x01
#define _02_SENS_OVER            0x02
#define _03_REF_OVER             0x03
#define _04_SENS_REF_OVER        0x04
#define _05_TSCAP_ERR            0x05
#define _06_TUNING_ERR           0x06

#define _0_BUTTON                (0)
#define _1_MATRIX                (1)
#define _2_SLIDER                (2)
#define _3_WHEEL                 (3)

#define _0000_GET_ERR            0x0000

/***********************************************************************************************************************
* Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Exported global variables
***********************************************************************************************************************/
TOUCH_API_EXTERN  volatile uint8_t     g_ctsu_offset_mode;                  /* Internal offset tuning mode            */
TOUCH_API_EXTERN           uint16_t    g_tuning_counter[METHOD_NUM];        /* Internal tuning timing counter         */
TOUCH_API_EXTERN           uint16_t    g_offset_time[METHOD_NUM];           /* Offset times                           */
TOUCH_API_EXTERN           uint16_t    g_touch_main_cycle;                  /* Touch main cycle                       */

/***********************************************************************************************************************
* Exported global functions
***********************************************************************************************************************/
uint8_t        R_Set_Cap_Touch_Sensor_Correction( void );
uint8_t        R_Set_Cap_Touch_Create( uint8_t method );
uint8_t        R_Set_Cap_Touch_Next_Method_Change( uint8_t method );
void           R_Set_Cap_Touch_Measurement_Start( uint8_t method );
uint8_t        R_Get_Cap_Touch_Initial_Status( void );
uint8_t        R_Set_Cap_Touch_Initial_Tuning( uint8_t method );
uint8_t        R_Set_Cap_Touch_Offset_Timing( uint8_t method, uint16_t count );
uint8_t        R_Get_Cap_Touch_Data_Check( uint8_t method );
uint16_t       R_Set_Cap_Touch_Result_Create( uint8_t method );
touch_result_t R_Get_Cap_Touch_Result( uint8_t method );
uint16_t       R_Get_Cap_Touch_Sensor_Data( uint8_t method, uint8_t mode, uint8_t index_num );
uint16_t       R_Get_Cap_Touch_Reference_Data( uint8_t method, uint8_t index_num );
uint8_t        R_Set_Cap_Touch_Tuning_Cntrol( uint8_t mode );

#endif //] __TOUCH_API_H__

/***********************************************************************************************************************
* End of File
***********************************************************************************************************************/