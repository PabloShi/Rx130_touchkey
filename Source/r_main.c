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
* File Name    : r_main.c
* Version      : 2.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Tool-Chain   : CC-RX Compiler ( V2.02.00 )
* OS           : -
* H/W Platform : -
* Description  : This file is system main.
* Operation    : Compile and download the sample code. Click 'Reset Go' to start the software.
* Limitations  : -
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2014   1.00     First Release
*              : 05.02.2015   2.00     First Release
***********************************************************************************************************************/

/***********************************************************************************************************************
* Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
* Includes <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* System include header */
#include "r_cg_macrodriver.h"

/* H/W include header */
#include "iodefine.h"
#include "r_mpc.h"
#include "r_ctsu.h"
#include "r_cgc.h"
#include "r_dtc.h"
#include "r_cg_cmt.h"

#ifdef SCI_SERIAL_USE
    #include "r_sci.h"
#endif    // SCI_SERIAL_USE

#ifdef  USB_SERIAL_USE
/* USB H/W include header */
#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_usrconfig.h"            /* System definition */
#include "r_usb_cdefusbip.h"            /* USB-FW Library Header */
#include "r_usb_usrconfig.h"            /* System definition, USB-FW Library Header */
#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"
#include "r_usb_pcdc_driver.h"
#include "r_usb_pcdc_define.h"
#include "r_usb_pcdc_api.h"
#endif  // USB_SERIAL_USE

/* S/W include header */
#include "r_cg_userdefine.h"
#include "r_touch.h"
#include "r_touch_API.h"

#include "r_serial_control.h"

/***********************************************************************************************************************
* Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
#ifdef USB_SERIAL_USE
USB_STATIC volatile uint8_t g_usb_suspend_flag;
USB_STATIC volatile uint8_t g_usb_int_key_flag;
#endif    // USB_SERIAL_USE

/* functions */
void       main(void);

#ifdef USB_SERIAL_USE
void       R_Set_Workbench_Communication_Create(void);
void       R_USBPCDC_Create(void);
void       R_Set_Workbench_Communication_Data(void);
void       R_USBPCDC_Apl_Task_Switch(void);
void       usb_smpl_set_suspend_flag(uint8_t data);
uint8_t    usb_smpl_get_suspend_flag(void);
void       usb_smpl_set_intkey(uint8_t data);
uint8_t    usb_smpl_get_intkey(void);
#endif    // USB_SERIAL_USE

#ifdef SCI_SERIAL_USE
void       R_Set_Workbench_Communication_Create(void);
void       R_Set_Workbench_Communication_Data(void);
#endif    // SCI_SERIAL_USE

/***********************************************************************************************************************
* Imported global variables and functions (from other files)
***********************************************************************************************************************/
/* functions */
#ifdef USB_SERIAL_USE
extern void     usb_cpu_target_init(void);
extern void     usb_cstd_task_start(void);
extern void     usb_pcdc_task_start(void);
extern void     usb_apl_task_switch(void);
#endif    // USB_SERIAL_USE

/***********************************************************************************************************************
* Function Name: main
* Description  : System main function
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
    touch_result_t ts_result;

void main(void)
{
    uint8_t        method;
    uint8_t        ret_val;

    method = 0;

    PORTE.PDR.BIT.B0 = 1;
    PORTE.PODR.BIT.B0 = 0;

    ret_val = R_Set_Cap_Touch_Create( method );                    /* Capacitive touch create API call                */
    if (_0_SUCCESS == ret_val)                                     /* Create result check                             */
    {
        g_ctsu_soft_mode = CTSU_READY_MODE;                        /* CTSU measurement ready mode setting             */
    }
    else
    {
        g_ctsu_soft_mode = CTSU_STOP_MODE;                         /* CTSU measurement stop mode setting              */
    }

#if defined(USB_SERIAL_USE) || defined(SCI_SERIAL_USE)
    R_Set_Workbench_Communication_Create();                        /* Workbench communication function create API call */
#endif    // defined(USB_SERIAL_USE) || defined(SCI_SERIAL_USE)

    R_CMT0_Create();                                               /* CMT0 create API call                            */
    R_CMT0_Start();                                                /* CMT0 start API call                             */

    SerialCommandInitial();                                        /* Initialize serial command communication task    */

    while (1U)                                                     /* Main loop                                       */
    {
#if defined(USB_SERIAL_USE) || defined(SCI_SERIAL_USE)
        R_Set_Workbench_Communication_Data();
#endif    // defined(USB_SERIAL_USE) || defined(SCI_SERIAL_USE)

        if (_1_TIMING == g_touch_system.flag.timing)
        {
            g_touch_system.flag.timing = 0;
            R_Set_Cap_Touch_Measurement_Start( method );

            if (_00_GET_OK == R_Get_Cap_Touch_Data_Check( method ))
            {
                if (_1_FINISH == R_Get_Cap_Touch_Initial_Status())
                {
                    PORTE.PODR.BIT.B0 = 0;
                    if (_0_SUCCESS == R_Set_Cap_Touch_Result_Create( method ))
                    {
                        ts_result = R_Get_Cap_Touch_Result( method );
                        if (0 != (ts_result.button[0] & 0x0001))
                        { 
                            /* Touch feedback    Led etc...    */

                            /* Touch feedback    Led etc...    */
                        }
                    }
                }
                else
                {
                    PORTE.PODR.BIT.B0 = 1;
                    R_Set_Cap_Touch_Initial_Tuning( method );
                }
            }
            method = R_Set_Cap_Touch_Next_Method_Change( method );

            PrepareReplayMessage(); /* Make the replay message of the serial command from Workbench */
        }
    }
}    /* End of function main() */

/***********************************************************************************************************************
* Function Name   : R_Set_Workbench_Communication_Create
* Description     : Workbench communication function create
* Arguments       : None
* Return value    : None
***********************************************************************************************************************/
void R_Set_Workbench_Communication_Create(void)
{
#ifdef SCI_SERIAL_USE        /* Uart(SCI6) */
    DTC_Set_Initial_of_SCI6();
    DTC_Set_Start_of_SCI6();
    R_SCI6_Create();                                               /* SCI6 create API call                            */
    R_SCI6_Start();                                                /* SCI6 start API call                             */
#endif    // SCI_SERIAL_USE
#ifdef USB_SERIAL_USE        /* USB function */
    R_USBPCDC_Create();                                            /* USB CDC create API call                         */
#endif    // USB_SERIAL_USE
}    /* End of function R_Set_Workbench_Communication_Create() */

/***********************************************************************************************************************
* Function Name   : R_USBPCDC_Create
* Description     : 
* Arguments       : None
* Return value    : None
***********************************************************************************************************************/
void R_USBPCDC_Create(void)
{
#ifdef USB_SERIAL_USE
    SYSTEM.PRCR.WORD           = PRCR1_ENA;        /* Enables writing to the registers */
    SYSTEM.MSTPCRB.BIT.MSTPB19 = 0;                /* Module stop control register (Enable USB0 module(MSTPB19)) */
    SYSTEM.PRCR.WORD           = PRCR1_DIS;        /* Disables writing to the registers */
    usb_cpu_target_init();
    usb_smpl_set_suspend_flag(USB_NO);
    R_usb_pstd_PcdChangeDeviceState(USB_DO_INITHWFUNCTION);
    R_usb_pstd_PcdOpen();
    usb_pcdc_task_start();      /* Start Peripheral USB driver */
#endif    // USB_SERIAL_USE
}

/***********************************************************************************************************************
* Function Name   : R_Set_Workbench_Communication_Data
* Description     : Workbench communication data setting
* Arguments       : None
* Return value    : None
***********************************************************************************************************************/
void R_Set_Workbench_Communication_Data(void)
{
#ifdef SCI_SERIAL_USE        /* Uart(SCI6) */
    R_SCI6_Receive_Data_Check();
#endif    // SCI_SERIAL_USE
#ifdef USB_SERIAL_USE        /* USB function */
    R_USBPCDC_Apl_Task_Switch();                                   /* USB switch task for nonOS                       */
#endif    // USB_SERIAL_USE
}    /* End of function R_Set_Workbench_Communication_Data() */

/***********************************************************************************************************************
* Function Name   : R_USBPCDC_Apl_Task_Switch
* Description     : 
* Arguments       : None
* Return value    : None
***********************************************************************************************************************/
void R_USBPCDC_Apl_Task_Switch(void)
{
#ifdef USB_SERIAL_USE
    usb_apl_task_switch();        /* Switch task for nonOS */
#endif    // USB_SERIAL_USE
}

#ifdef  USB_SERIAL_USE
/***********************************************************************************************************************
* Function Name   : usb_smpl_set_suspend_flag
* Description     : Set resume interruptt flag
* Arguments       : uint8_t data
* Return value    : none
***********************************************************************************************************************/
void usb_smpl_set_suspend_flag(uint8_t data)
{
    g_usb_suspend_flag  = data;
}   /* End of function usb_smpl_set_suspend_flag() */

/***********************************************************************************************************************
* Function Name   : usb_smpl_get_suspend_flag
* Description     : Get resume interruptt flag
* Arguments       : none
* Return value    : g_usb_suspend_flag
***********************************************************************************************************************/
uint8_t usb_smpl_get_suspend_flag(void)
{
    return  g_usb_suspend_flag;
}   /* End of function usb_smpl_get_suspend_flag() */

/***********************************************************************************************************************
* Function Name   : usb_smpl_set_intkey
* Description     : Set external key interruptt flag
* Arguments       : uint8_t data
* Return value    : none
***********************************************************************************************************************/
void usb_smpl_set_intkey(uint8_t data)
{
    g_usb_int_key_flag  = data;
}   /* End of function usb_smpl_set_intkey() */

/***********************************************************************************************************************
* Function Name   : usb_smpl_get_intkey
* Description     : Get external key interruptt flag
* Arguments       : none
* Return value    : g_usb_int_key_flag
***********************************************************************************************************************/
uint8_t usb_smpl_get_intkey(void)
{
    return  g_usb_int_key_flag;
}   /* End of function usb_smpl_get_intkey() */

#endif  // USB_SERIAL_USE

/***********************************************************************************************************************
* End of file
***********************************************************************************************************************/
