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
* File Name    : r_sci.h
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file includes the Serial Communications Interface (SCI).
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/
#ifndef __R_SCI_H__    //[
#define __R_SCI_H__

/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"

/***********************************************************************************************************************
 Macro definitions
***********************************************************************************************************************/
#ifdef __R_SCI_C__
    #define SCI_EXTERN
#else
    #define SCI_EXTERN    extern
#endif

/***********************************************************************************************************************
* Macro definitions
***********************************************************************************************************************/
#define SCI_SIZE_CHECK_COUNT            2
#define SCI_BASE_DATA_SIZE              3

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

#ifdef  SCI_SERIAL_USE
/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
SCI_EXTERN volatile uint8_t g_sci6_receive_flag;
SCI_EXTERN uint8_t g_sci6_receive_data[36];
SCI_EXTERN volatile uint8_t g_sci6_receive_count;
SCI_EXTERN uint16_t g_sci6_receive_data_size;

SCI_EXTERN volatile uint8_t g_sci6_send_flag;
SCI_EXTERN uint16_t g_sci6_send_count;
SCI_EXTERN uint8_t  g_sci6_send_data[270+SCI_BASE_DATA_SIZE];

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_SCI6_Create(void);
void R_SCI6_Start(void);
void R_SCI6_Stop(void);
void R_SCI6_Receive_Data_Check(void);
void R_SCI6_Serial_Send_Start( uint16_t send_size );
#endif  // SCI_SERIAL_USE

#endif    // __R_SCI_H__

/***********************************************************************************************************************
* End of File
***********************************************************************************************************************/
