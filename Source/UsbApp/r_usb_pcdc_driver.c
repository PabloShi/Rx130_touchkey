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
* File Name     : r_usb_pcdc_driver.c
* Version       : 2.11
* Description   : USB Peripheral CDC class driver code.
*******************************************************************************/
/*******************************************************************************
* History   : DD.MM.YYYY Version Description
*           : 30.11.2012 2.00    First Release
*           : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
*           : 30.08.2013 2.11    Basic Mini FW Ver2.11 Release
*                                  - GNU/e2studio & IAR EW Version release
*                                  - Use macro for g_usb_pipe_toggle declaration
*                                  - Revise of usb_psmpl_DummyFunc() declaration
*******************************************************************************/

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

#ifdef	USB_SERIAL_USE

/******************************************************************************
Constant macro definitions
******************************************************************************/

#define USB_PCDC_SET_LINE_CODING_LENGTH             7u
#define USB_PCDC_SET_CONTROL_LINE_STATE_LENGTH      2u
#define USB_PCDC_SEND_BREAK_LENGTH                  2u

/******************************************************************************
External variables and functions
******************************************************************************/
extern void usb_psmpl_DummyFunc( usb_utr_t * );

volatile uint16_t   g_usb_pipe_toggle[ USB_MAX_PIPE_NO + 1 ];


/******************************************************************************
Private global variables and functions
******************************************************************************/
void        usb_pcdc_TransResult( usb_utr_t *mess );
void        usb_pcdc_ControlTrans0( usb_request_t *req );
void        usb_pcdc_ControlTrans1( usb_request_t *req );
void        usb_pcdc_ControlTrans2( usb_request_t *req );
void        usb_pcdc_ControlTrans3( usb_request_t *req );
void        usb_pcdc_ControlTrans4( usb_request_t *req );
void        usb_pcdc_ControlTrans5( usb_request_t *req );
usb_er_t    usb_pcdc_PipeRegistratration( uint16_t *eptbl );
void        usb_pcdc_AplRequest( uint8_t key, uint16_t size, uint8_t *Table );


uint16_t                        usb_gcdc_SendBreakDuration;     /* Duration of Break */
uint8_t                         usb_gpcdc_Outpipe;              /* Pipe Direction from Host to Device */
uint8_t                         usb_gpcdc_Inpipe;               /* Pipe Direction from Device to Host */
uint8_t                         usb_gpcdc_Status_pipe;          /* Pipe Direction from Device to Host */
usb_pcdc_ControlLineState_t     usb_gcdc_ControlLineState;      /* Control Line Status data */
usb_pcdc_LineCoding_t           usb_gcdc_LineCoding;            /* Line Coding data */
usb_utr_t                       usb_gpcdc_Mess4;                /* PCDC <--> Application massage */


/******************************************************************************
Renesas Abstracted Peripheral Communications Devices Class Driver API functions
******************************************************************************/


/******************************************************************************
Function Name   : usb_pcdc_StatusTransResult
Description     : CallBack Function
Arguments       : usb_utr_t *mess           : message
Return value    : void
******************************************************************************/
void usb_pcdc_TransResult( usb_utr_t *mess )
{
    usb_er_t    err;


    g_usb_pipe_toggle[mess->pipenum] = mess->pipectr;


    /* From USB device to PCDC */
    mess->msginfo = (uint16_t)USB_PCDC_PTRANSFER;
    if( mess->status == USB_DATA_STOP )
    {
    }
    
    err = R_USB_SND_MSG(USB_PCDC_MBX, (usb_msg_t*)mess);
    if( err != USB_E_OK )
    {
        /* Send message failure */
    }
}   /* eof usb_pcdc_TransResult() */


/******************************************************************************
Function Name   : usb_pcdc_ControlTrans0
Description     : Process class request (idle or setup stage)
Arguments       : usb_request_t *req        : request
Return value    : void
******************************************************************************/
void usb_pcdc_ControlTrans0( usb_request_t *req )
{
}   /* eof usb_pcdc_ControlTrans0() */


/******************************************************************************
Function Name   : usb_pcdc_ControlTrans1
Description     : Process class request (control read)
Arguments       : usb_request_t *req        : request
Return value    : void
******************************************************************************/
void usb_pcdc_ControlTrans1( usb_request_t *req )
{
    if ( (req->WORD.BIT.bRequest == USB_PCDC_GET_LINE_CODING) &&
         (req->wValue   == 0x0000) &&
         (req->wIndex   == 0x0000) &&
         (req->wLength  == USB_PCDC_GET_LINE_CODING_LENGTH) )
    {   /* if bRequest is get_line_coding then */
         R_usb_pstd_ControlRead( (usb_leng_t)USB_PCDC_GET_LINE_CODING_LENGTH, (uint8_t *)&usb_gcdc_LineCoding );
    }
    else
    {   /* if request error then */
        R_usb_pstd_SetStallPipe0();     /* Set Stall */
    }
}   /* eof usb_pcdc_ControlTrans1() */


/******************************************************************************
Function Name   : usb_pcdc_ControlTrans2
Description     : Process class request (control write data stage)
Arguments       : usb_request_t *req        : request
Return value    : void
******************************************************************************/
void usb_pcdc_ControlTrans2( usb_request_t *req )
{
    if ( (req->WORD.BIT.bRequest == USB_PCDC_SET_LINE_CODING) &&
         (req->wValue   == 0x0000) &&
         (req->wIndex   == 0x0000) &&
         (req->wLength  == USB_PCDC_SET_LINE_CODING_LENGTH) )
    {   /* if bRequest is Set_Line_Coding then */
        R_usb_pstd_ControlWrite( (uint32_t)USB_PCDC_SET_LINE_CODING_LENGTH, (uint8_t *)&usb_gcdc_LineCoding );
    }
    else
    {   /* if request error then */
        R_usb_pstd_SetStallPipe0();     /* Set Stall */
    }
}   /* eof usb_pcdc_ControlTrans2() */


/******************************************************************************
Function Name   : usb_pcdc_ControlTrans3
Description     : Process class request (control no data write)
Arguments       : usb_request_t *req        : request
Return value    : void
******************************************************************************/
void usb_pcdc_ControlTrans3( usb_request_t *req )
{
    if ( (req->WORD.BIT.bRequest == USB_PCDC_SET_CONTROL_LINE_STATE) &&
         (req->wIndex   == 0x0000) &&
         (req->wLength  == 0x0000) )
    {   /* DTR & RTS set value store */
        *(uint16_t *)&usb_gcdc_ControlLineState = req->wValue;
        
        R_usb_cstd_SetBufPipe0();
        
        usb_pcdc_AplRequest( USB_PCDC_SET_CONTROL_LINE_STATE,
                             USB_PCDC_SET_CONTROL_LINE_STATE_LENGTH,
                             (uint8_t *)&usb_gcdc_ControlLineState );
    }
    else
    {   /* if request error then */
        R_usb_pstd_SetStallPipe0();     /* Req Error */
    }
    
    R_usb_pstd_ControlEnd( (uint16_t)USB_CTRL_END );
}   /* eof usb_pcdc_ControlTrans3() */


/******************************************************************************
Function Name   : usb_pcdc_ControlTrans4
Description     : Process class request (control read status stage)
Arguments       : usb_request_t *req        : request
Return value    : void
******************************************************************************/
void usb_pcdc_ControlTrans4( usb_request_t *req )
{
    if ( req->WORD.BIT.bRequest == USB_PCDC_GET_LINE_CODING )
    {
            R_usb_cstd_SetBufPipe0();
    }
    else
    {
        /* Set Stall */
        R_usb_pstd_SetStallPipe0();     /* Req Error */
    }
    
    R_usb_pstd_ControlEnd( (uint16_t)USB_CTRL_END );
}   /* eof usb_pcdc_ControlTrans4() */


/******************************************************************************
Function Name   : usb_pcdc_ControlTrans5
Description     : Process class request (control write status stage)
Arguments       : usb_request_t *req        : request
Return value    : void
******************************************************************************/
void usb_pcdc_ControlTrans5( usb_request_t *req )
{
    if ( req->WORD.BIT.bRequest == USB_PCDC_SET_LINE_CODING )
    {
        R_usb_cstd_SetBufPipe0();
        
        usb_pcdc_AplRequest( USB_PCDC_SET_LINE_CODING,
                             USB_PCDC_SET_LINE_CODING_LENGTH,
                             (uint8_t *)&usb_gcdc_LineCoding );
    }
    else
    {   /* if request error then */
        R_usb_pstd_SetStallPipe0();     /* Set stall */
    }
    
    R_usb_pstd_ControlEnd( (uint16_t)USB_CTRL_END );
}   /* eof usb_pcdc_ControlTrans5() */


/******************************************************************************
Function Name   : usb_pcdc_PipeRegistratration
Description     : PipeRegistratration
Arguments       : uint16_t *eptbl            : EndPoint Table
Return value    : usb_er_t
******************************************************************************/
usb_er_t usb_pcdc_PipeRegistratration( uint16_t *eptbl )
{
    uint16_t i;

    usb_gpcdc_Outpipe       = USB_PIPE0;
    usb_gpcdc_Inpipe        = USB_PIPE0;
    usb_gpcdc_Status_pipe   = USB_PIPE0;

    for(i=0;eptbl[0]!=USB_PDTBLEND;i++,eptbl+=USB_EPL)
    {
        switch(eptbl[1]&USB_TYPFIELD)
        {
        case    USB_BULK:
            if ( (eptbl[1]&USB_DIRFIELD) == USB_DIR_P_IN )
            {
                usb_gpcdc_Inpipe    = (uint8_t)eptbl[0];
            }
            else if ( (eptbl[1]&USB_DIRFIELD) == USB_DIR_P_OUT )
            {
                usb_gpcdc_Outpipe   = (uint8_t)eptbl[0];
            }
            break;
        case    USB_INT:
            usb_gpcdc_Status_pipe   = (uint8_t)eptbl[0];
            break;
        default:
        break;
        }
    }
    
    if(    (usb_gpcdc_Outpipe     == USB_PIPE0)
        || (usb_gpcdc_Inpipe      == USB_PIPE0)
        || (usb_gpcdc_Status_pipe == USB_PIPE0) )
    {
        return USB_E_ERROR;
    }
    
    return USB_E_OK;
}   /* eof usb_pcdc_PipeRegistratration() */


/******************************************************************************
Function Name   : usb_pcdc_AplRequest
Description     : 
Arguments       : uint16_t key    : 
                : uint16_t size   : 
                : uint8_t *Table  : 
Return value    : void
******************************************************************************/
void usb_pcdc_AplRequest( uint8_t key, uint16_t size, uint8_t *Table )
{
    usb_er_t    err;


    /* PIPE Transfer set */
    usb_gpcdc_Mess4.msginfo     = (uint16_t) USB_PCDC_PCONTROL;
    usb_gpcdc_Mess4.pipenum     = key;
    usb_gpcdc_Mess4.tranadr     = Table;
    usb_gpcdc_Mess4.tranlen     = size;
    usb_gpcdc_Mess4.setup       = 0;
    usb_gpcdc_Mess4.complete    = (usb_cb_t)&usb_psmpl_DummyFunc;
    err = R_USB_SND_MSG(USB_PCDC_MBX, (usb_msg_t*)&usb_gpcdc_Mess4);
    if( err != USB_E_OK )
    {
        /* Send message failure */
        while ( 1 )
        {
        }
    }
}   /* eof usb_pcdc_AplRequest() */

#endif	// USB_SERIAL_USE

/******************************************************************************
End Of File
******************************************************************************/
