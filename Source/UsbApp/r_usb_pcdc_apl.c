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
* http://www.renesas.com/disclaimer *
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_usb_pcdc_echo_apl.c
* Version      : 2.11
* Description  : USB Peripheral Sample Code
*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.11.2012 2.00    Basic FW mini Ver2.00(MP Version)
*         : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
*         : 30.08.2013 2.11    Basic Mini FW Ver2.11 Release
*                                - GNU/e2studio & IAR EW Version release
*                                - Use macro for g_usb_pipe_toggle declaration
******************************************************************************/

/******************************************************************************
Section    <Section Difinition> , "Project Sections"
******************************************************************************/
#ifdef  R8CUSB
#pragma section program P_smpl
#pragma section bss B_smpl
#pragma section data R_smpl
#pragma section rom C_smpl
#endif
#ifdef  RX_USB
//#pragma section _smpl
#endif
#ifdef  RL78USB
#endif
#ifdef  RL78USB_SECTION
#pragma section @@CODE   P_SMP
#pragma section @@BASE   T_SMP
#pragma section @@CNST   C_SMP
#pragma section @@R_INIT D_SMP
#pragma section @@DATA   B_SMP
#pragma section @@INIT   R_SMP
#endif


//#pragma EI


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_cdefusbip.h"            /* USB-FW Library Header */
#include "r_usb_usrconfig.h"            /* System definition, USB-FW Library Header */
#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"

#include "r_usb_pcdc_driver.h"
#include "r_usb_pcdc_define.h"
#include "r_usb_pcdc_api.h"

#include "r_serial_control.h"

#ifdef	USB_SERIAL_USE

/******************************************************************************
Constant macro definitions
******************************************************************************/
/* CDC Host data receive size */
/* FS:64 HS:512 */
#define USB_PCDC_APL_RX_SIZE            32

/* Comm Port data receive size */
#define USB_PCDC_APL_SRX_SIZE           64

/****** Line Coding Define *******/
/* Line Coding bps */
#define USB_PCDC_SPEED_9600             ((uint32_t)9600)
#define USB_PCDC_SPEED_19200            ((uint32_t)19200)
    /* Line Coding 8Data bits */
#define USB_PCDC_DATA_BIT_8             ((uint8_t)8)
    /* Line Coding 1Stop bits */
#define USB_PCDC_STOP_BIT_1             ((uint8_t)0)
    /* Line Coding None Parity */
#define USB_PCDC_PARITY_BIT_NONE        ((uint8_t)0u)

#define TASK_LOOPS_BETWEEN_INSTRUCTIONS 0x00050000

/*****************************************************************************
Enumerated Types
******************************************************************************/
/* Peripheral CDC Sample application message command */
typedef enum
{
    /* Data receive from Host cdc */
    USB_PCDC_RX_COMP,
    /* Data send for Host cdc */
    USB_PCDC_TX_COMP
} USB_PCDC_APL_COMMAND;

/* Peripheral CDC Sample application message command */
typedef enum
{
    APP_STATE_IDLE,
    APP_STATE_RUNNING_INTRO,
    APP_STATE_INTRO_MSG0,
    APP_STATE_INTRO_MSG1,
    APP_STATE_INTRO_MSG2,
    APP_STATE_ECHO_MODE
} USB_PCDC_APL_STATE;
/******************************************************************************
External variables and functions
******************************************************************************/
extern uint16_t     usb_gpcdc_EpTbl1[ 0x14u ];
extern uint8_t      usb_gpcdc_DeviceDescriptor[ 0x12u ];
extern uint8_t      usb_gpcdc_ConfigrationF1[ 0x09u + 0x09u + 0x05u + 0x04u + 0x05u + 0x05u + 0x07u + 0x09u + 0x07u + 0x07u ];
extern uint8_t      *usb_gpcdc_StrPtr[ 0x07u ];


extern volatile uint16_t    g_usb_pipe_toggle[USB_MAX_PIPE_NO + 1];

extern void         usb_cpu_suspend_sleep( void );
extern void         usb_cpu_detach_sleep(void);

extern void         usb_smpl_set_suspend_flag(uint8_t data);
extern uint8_t      usb_smpl_get_suspend_flag(void);

#ifdef  USB_LCD_ENABLE
extern void         usb_cpu_LcdDisp(uint8_t pos, uint8_t *str);
#endif /* USB_LCD_ENABLE */

/******************************************************************************
Private global variables and functions
******************************************************************************/
uint8_t     g_usb_psmpl_receive_data[USB_PCDC_APL_RX_SIZE + 4];
//uint8_t     g_usb_psmpl_send_data[USB_PCDC_APL_RX_SIZE + 4];
uint8_t     g_usb_psmpl_send_data[360 + 4];
//static      USB_PCDC_APL_STATE  app_state;
USB_PCDC_APL_STATE  app_state;

void        usb_cstd_task_start( void );
void        usb_pcdc_task_start( void );
void        usb_apl_task_switch( void );
void        usb_psmpl_driver_registration( void );
usb_er_t    usb_psmpl_change_device_state( uint16_t data, uint16_t state );
void        usb_psmpl_open( uint16_t data1, uint16_t data2 );
void        usb_psmpl_close( uint16_t data1, uint16_t data2 );
uint16_t    usb_psmpl_GetRcvDataCnt( usb_utr_t *mess );
void        usb_psmpl_MainTask( void );
void        usb_psmpl_ReceiveDataStart( void );
void        usb_psmpl_RxCB( usb_utr_t *mess );
void        usb_psmpl_TxCB( usb_utr_t *mess );
void        usb_psmpl_LineCodingInitial( void );
void        usb_psmpl_DummyFunc( usb_utr_t * );

/******************************************************************************
Renesas Peripheral Communications Devices Class Sample Code functions
******************************************************************************/


/******************************************************************************
Function Name   : usb_cstd_task_start
Description     : Start task CSTD; "common" basic USB low level task.
Arguments       : void
Return value    : void
******************************************************************************/
void usb_cstd_task_start( void )
{
    usb_pcdc_task_start();      /* Start Peripheral USB driver */

    usb_apl_task_switch();      /* Switch task for nonOS */
}   /* eof usb_cstd_task_start() */


/******************************************************************************
Function Name   : usb_phid_task_start
Description     : Set peripheral application task start conditions. 
Arguments       : void
Return value    : void
******************************************************************************/
void usb_pcdc_task_start( void )
{
#ifdef  USB_LCD_ENABLE
    /* Display Debug LCD */
    usb_cpu_LcdDisp( LCD_POS_U0, (uint8_t *)"USB CDC ");
    usb_cpu_LcdDisp( LCD_POS_D0, (uint8_t *)"Appstart");
#endif /* USB_LCD_ENABLE */

    usb_psmpl_LineCodingInitial();

    usb_psmpl_driver_registration();            /* Peripheral Application Registration */

    R_usb_pstd_PcdChangeDeviceState( USB_DO_SETHWFUNCTION );
}   /* eof usb_pcdc_task_start() */


/******************************************************************************
Function Name   : usb_apl_task_switch
Description     : Task switch loop for nonOS version.
Argument        : void
Return          : void
******************************************************************************/
void usb_apl_task_switch( void )
{
//    uint32_t i = 0;

	/* This if-statement is run only if user has not yet entered any characters into the virtual serial COM port.
	 * is Added to send instructions for demo. */
//	if (app_state != APP_STATE_ECHO_MODE)
//	{
//		if (i++ == TASK_LOOPS_BETWEEN_INSTRUCTIONS)
//		{
//			i = 0;
//			app_state = APP_STATE_INTRO_MSG0;
//			R_usb_pcdc_SendData((uint8_t *)"PCDC. ", 6, (usb_cbinfo_t)usb_psmpl_TxCB);
//		}
//	}
	/* Task schedule request check. */
	if( USB_FLGSET == R_usb_cstd_Scheduler() )
	{
		R_usb_pstd_PcdTask();       /* PCD Task */
		R_usb_pcdc_Task();          /* Peripheral PCDC Task */
		usb_psmpl_MainTask();       /* Peripheral PCDC demo sample application Task */
	}
	if ( usb_smpl_get_suspend_flag() == USB_YES )
	{
		usb_cpu_suspend_sleep();
	}
}   /* eof usb_apl_task_switch */


/******************************************************************************
Function Name   : usb_psmpl_driver_registration
Description     : Peripheral Sample Driver Registration
Argument        : void
Return          : void
******************************************************************************/
void usb_psmpl_driver_registration( void )
{
    usb_pcdreg_t    driver;

    /* Pipe Define Table address */
    driver.pipetbl      = &usb_gpcdc_EpTbl1[0];
    /* Device descriptor Table address */
    driver.devicetbl    = (uint8_t*)&usb_gpcdc_DeviceDescriptor[0];
    /* Configuration descriptor Table address */
    driver.configtbl    = &usb_gpcdc_ConfigrationF1[0];
    /* String descriptor Table address */
    driver.stringtbl    = (uint8_t**)&usb_gpcdc_StrPtr[0];
    /* Device statediagram */
    driver.statediagram = (usb_cbinfo_t)&usb_psmpl_change_device_state;
    /* Control Transfer */
    driver.ctrltrans    = &R_usb_pcdc_ClassRequest;

    R_usb_pcdc_Registration( &driver );
    
    usb_gpcdc_AplCB     = (usb_cb_t)usb_psmpl_DummyFunc;
}   /* eof usb_psmpl_driver_registration */


/******************************************************************************
Function Name   : usb_apl_change_device_state
Description     : Device State CallBack Check
Arguments       : uint16_t state
Return value    : uint16_t data
******************************************************************************/
usb_er_t usb_psmpl_change_device_state( uint16_t data, uint16_t state )
{
    switch( state )
    {
        case USB_STS_DETACH:
            usb_psmpl_close( data, state );
            usb_smpl_set_suspend_flag(USB_NO);
#ifdef USB_STOP_MODE_ENABLE
  #ifdef __RX
            usb_cpu_detach_sleep();
  #endif  /* __RX */
#endif /* USB_STOP_MODE_ENABLE */
        break;
        case USB_STS_DEFAULT:
            usb_smpl_set_suspend_flag(USB_NO);
        break;
        case USB_STS_ADDRESS:
        break;
        case USB_STS_CONFIGURED:
            usb_psmpl_open( data, state );
            usb_smpl_set_suspend_flag(USB_NO);
        break;
        case USB_STS_SUSPEND:
            usb_smpl_set_suspend_flag(USB_YES);
        break;
        case USB_STS_RESUME:
            usb_smpl_set_suspend_flag(USB_NO);
        break;
        default:
        break;
    }   

    return ( USB_E_OK );
}   /* eof usb_psmpl_driver_registration */


/******************************************************************************
Function Name   : usb_psmpl_open
Description     : Sample Open
Argument        : uint16_t data1            : Not Use
                : uint16_t data2            : Not Use
Return          : void
******************************************************************************/
void usb_psmpl_open( uint16_t data1, uint16_t data2 )
{
    uint8_t index;
    
    for ( index = 0; index < (USB_MAX_PIPE_NO + 1); index++ )
    {
        g_usb_pipe_toggle[index] = USB_NULL;
    }
    usb_psmpl_ReceiveDataStart();
}   /* eof usb_psmpl_open */


/******************************************************************************
Function Name   : usb_psmpl_close
Description     : Sample Close
Argument        : uint16_t data1            : Not Use
                : uint16_t data2            : Not Use
Return          : void
******************************************************************************/
void usb_psmpl_close( uint16_t data1, uint16_t data2 )
{
    R_usb_pstd_TransferEnd( USB_PIPE1, USB_DATA_STOP );
    R_usb_pstd_TransferEnd( USB_PIPE2, USB_DATA_STOP );
    R_usb_pstd_TransferEnd( USB_PIPE8, USB_DATA_STOP );
}   /* eof usb_psmpl_close */


/******************************************************************************
Function Name   : usb_psmpl_GetRcvDataCnt
Description     : Get USB Receive Data count 
Arguments       : usb_utr_t
Return value    : USB receive data count
******************************************************************************/
uint16_t usb_psmpl_GetRcvDataCnt( usb_utr_t *mess )
{
    /* Receive Data Count for USB Host */
    uint16_t    rcv_cnt;

    /*----------------------------------*/
    /* Data receive from Host cdc       */
    /*----------------------------------*/
    if(mess->status == USB_DATA_OK)
    {
        /* Receive size = Request size */
        rcv_cnt = USB_PCDC_APL_RX_SIZE;
    }
    else if(mess->status == USB_DATA_SHT)
    {
        /* Receive size < Request size */
        rcv_cnt = USB_PCDC_APL_RX_SIZE - mess->tranlen;
    }
    else
    {
        rcv_cnt = 0;
    }

    return rcv_cnt;
}   /* eof usb_psmpl_GetRcvDataCnt */


/******************************************************************************
Function Name   : usb_psmpl_MainTask
Description     : Main Task
Argument        : void
Return          : void
******************************************************************************/
void usb_psmpl_MainTask( void )
{
    usb_utr_t   *mess;
    usb_er_t    err = 0l;

    /* Receive Data Count for USB Host */
    uint16_t    rcv_cnt;
    usb_leng_t  snd_cnt;
//    uint16_t    index;

    err = R_USB_RCV_MSG( USB_PSMP_MBX, (usb_msg_t**)&mess );
    if( err != USB_E_OK )
    {
        return;
    }
    
    
    switch ( mess->msginfo )
    {
    case USB_PCDC_RX_COMP:
#if	1
        /* ==== If USB can receive new data ==== */
        /* Check the number of data which USB should receive. */
        rcv_cnt = usb_psmpl_GetRcvDataCnt(mess);

        if (rcv_cnt != 0)
        {
			if (SerialCommandReceive(g_usb_psmpl_receive_data, rcv_cnt))
			{
				if (GetReplayMessage(g_usb_psmpl_send_data, (uint16_t *)&snd_cnt))
				{
            		R_usb_pcdc_SendData( &g_usb_psmpl_send_data[0], snd_cnt, (usb_cbinfo_t)&usb_psmpl_TxCB );
				}
			}
        }
        else
        {
            usb_psmpl_ReceiveDataStart();
        }
#else	// ORIGINAL
        /*----------------------------------*/
        /* Data receive from Host cdc       */
        /*----------------------------------*/

        /* ==== If USB can receive new data ==== */
        /* Check the number of data which USB should receive. */
        rcv_cnt = usb_psmpl_GetRcvDataCnt(mess);

        /* For first received character, stop the introduction text going to virtual COM port. */
        if (app_state != APP_STATE_ECHO_MODE)
        {
            app_state = APP_STATE_ECHO_MODE;
            /* Send e.g. Vertical Tab (0x0C), Bell (0x07), New Line. */
            R_usb_pcdc_SendData((uint8_t *)"Echo mode.\x0B\x07\n\r", 14, (usb_cbinfo_t)&usb_psmpl_TxCB);
        }

        /* In echo mode.
        Use R_usb_pcdc_SendData to return the received data. */
        else if (rcv_cnt != 0)
        {
            for ( index = 0; index < rcv_cnt; index++ )
            {
                g_usb_psmpl_send_data[ index ] = g_usb_psmpl_receive_data[ index ];
            }
            snd_cnt = rcv_cnt;
            
            /* Send the data back to user over USB. The Tx callback will trigger to notify that data is transmitted. */
            R_usb_pcdc_SendData( &g_usb_psmpl_send_data[0], snd_cnt, (usb_cbinfo_t)&usb_psmpl_TxCB );
        }
        else
        {
            usb_psmpl_ReceiveDataStart();
        }
#endif
        break;
    case USB_PCDC_TX_COMP:
#if	1
        /*----------------------------------*/
        /* Data send to Host cdc            */
        /*----------------------------------*/
        usb_psmpl_ReceiveDataStart();
#else	// ORIGINAL CODE
        /* Tell app process to send next user intro message. */
        if (app_state == APP_STATE_INTRO_MSG0)
        {
            R_usb_pcdc_SendData((uint8_t *)"Virtual serial COM port. Type characters into terminal.\n\r", 58, (usb_cbinfo_t)&usb_psmpl_TxCB );
            app_state = APP_STATE_INTRO_MSG1;
        }
        else if (app_state == APP_STATE_INTRO_MSG1)
        {
            R_usb_pcdc_SendData((uint8_t *)"The target will receive the characters over USB CDC, then copy them to a USB transmit buffer to be echoed back over USB.\n\n\r", 123, (usb_cbinfo_t)&usb_psmpl_TxCB );
            app_state = APP_STATE_INTRO_MSG2;
        }
        else if (app_state != APP_STATE_INTRO_MSG2)
        /* Not in intro message mode. All transmitted data should trigger this 'else'. */
        {
            ;
        }
        /*----------------------------------*/
        /* Data send to Host cdc            */
        /*----------------------------------*/
        usb_psmpl_ReceiveDataStart();
#endif
        break;
    default:
        /*----------------------------------*/
        /* Undefine message                 */
        /*----------------------------------*/
        break;
    }
}   /* eof usb_psmpl_MainTask */


/******************************************************************************
Function Name   : usb_psmpl_ReceiveDataStart
Description     : Start Data Receive request for Host
Arguments       : void
Return value    : void
******************************************************************************/
void usb_psmpl_ReceiveDataStart( void )
{
    R_usb_pcdc_ReceiveData( (uint8_t *)&g_usb_psmpl_receive_data[0],
                            (uint32_t)USB_PCDC_APL_RX_SIZE,
                            (usb_cbinfo_t)&usb_psmpl_RxCB);
}   /* eof usb_psmpl_ReceiveDataStart */


/******************************************************************************
Function Name   : usb_psmpl_RxCB
Description     : CDC Host Rx complete Callback
Argument        : usb_utr_t *mess           : message
Return          : void
******************************************************************************/
void usb_psmpl_RxCB( usb_utr_t *mess )
{
    usb_er_t        err;

    mess->msginfo = USB_PCDC_RX_COMP;
    /* Send message */
    err = R_USB_SND_MSG(USB_PSMP_MBX, (usb_msg_t*)mess);
    if( err != USB_E_OK )
    {
        /* Send Message failure */
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_APL | USB_DEBUG_HOOK_CODE1);
    }
}   /* eof usb_psmpl_RxCB */


/******************************************************************************
Function Name   : usb_psmpl_TxCB
Description     : CDC Host Tx complete Callback
Argument        : usb_utr_t *mess           : message
Return          : void
******************************************************************************/
void usb_psmpl_TxCB( usb_utr_t *mess )
{
    usb_er_t        err;

    mess->msginfo = USB_PCDC_TX_COMP;

    /* Send message */
    err = R_USB_SND_MSG(USB_PSMP_MBX, (usb_msg_t*)mess);
    if( err != USB_E_OK )
    {
        /* Send Message failure */
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_APL | USB_DEBUG_HOOK_CODE2);
    }
}   /* eof usb_psmpl_TxCB */


/******************************************************************************
Function Name   : usb_psmpl_LineCodingInitial
Description     : Line coding initial
Arguments       : void
Return value    : void
******************************************************************************/
void usb_psmpl_LineCodingInitial( void )
{
    usb_pcdc_LineCoding_t linecoding;
    
    //linecoding.dwDTERate        = USB_PCDC_SPEED_19200;
	linecoding.dwDTERate        = ((uint32_t)115200u);
    linecoding.bCharFormat      = USB_PCDC_STOP_BIT_1;
    linecoding.bParityType      = USB_PCDC_PARITY_BIT_NONE;
    linecoding.bDataBits        = USB_PCDC_DATA_BIT_8;
    linecoding.rsv              = (uint8_t)0;
    R_usb_pcdc_LineCodingInitial( &linecoding );
}   /* eof usb_psmpl_LineCodingInitial */


/******************************************************************************
Function Name   : usb_psmpl_DummyFunc
Description     : 
Arguments       : void
Return value    : void
******************************************************************************/
void usb_psmpl_DummyFunc( usb_utr_t *mess )
{
}   /* usb_psmpl_DummyFunc */

#endif	// USB_SERIAL_USE

/******************************************************************************
End  Of File
******************************************************************************/
