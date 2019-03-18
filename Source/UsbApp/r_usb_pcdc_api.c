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
* File Name     : r_usb_pcdc_api.c
* Version       : 2.11
* Description   : USB Peripheral CDC class driver API function code.
*******************************************************************************/
/*******************************************************************************
* History   : DD.MM.YYYY Version Description
*           : 30.11.2012 2.00    First Release
*           : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
*           : 30.08.2013 2.11    Basic Mini FW Ver2.11 Release
*                                  - GNU/e2studio & IAR EW Version release
*                                  - Use macro for g_usb_pipe_toggle declaration
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
#include "r_usb_usbip.h"                /* Definition of the USB register & bit define */

#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"

#include "r_usb_pcdc_driver.h"
#include "r_usb_pcdc_define.h"
#include "r_usb_pcdc_api.h"

#ifdef	USB_SERIAL_USE

/******************************************************************************
Constant macro definitions
******************************************************************************/


/******************************************************************************
External variables and functions
******************************************************************************/
extern volatile uint16_t    g_usb_pipe_toggle[USB_MAX_PIPE_NO + 1];
extern uint16_t usb_gpcdc_EpTbl1[ 0x14u ];

usb_request_t   g_usb_pmsc_Request;


/******************************************************************************
Private global variables and functions
******************************************************************************/
usb_er_t    R_usb_pcdc_LineCodingInitial( usb_pcdc_LineCoding_t *linecoding );
void        R_usb_pcdc_SendData( uint8_t *Table, usb_leng_t size, usb_cbinfo_t complete );
void        R_usb_pcdc_ReceiveData( uint8_t *Table, usb_leng_t size, usb_cbinfo_t complete );
void        R_usb_pcdc_SendNotification( uint16_t serial_state, usb_cbinfo_t complete );
usb_er_t    R_usb_pcdc_Registration( usb_pcdreg_t *tbl );
void        R_usb_pcdc_ClassRequest( usb_request_t *ptr, uint16_t ctsq );
void        R_usb_pcdc_Release( void );
void        R_usb_pcdc_Task( void );

usb_pipe_t  R_usb_pcdc_epadr_2_pipe(void);
void        R_usb_pcdc_set_alternate(void);
void        R_usb_pcdc_get_alternate(void);

uint16_t    usb_gpcdc_SerialStateTable[ USB_CDC_SETUP_TBL_SIZE ] = {0x20A1,0x0000,0x0000,0x0002,0x0000};

usb_utr_t   usb_gpcdc_Mess1;        /* PCDC <--> USB massage */
usb_utr_t   usb_gpcdc_Mess2;        /* PCDC <--> USB massage */
usb_utr_t   usb_gpcdc_Mess3;        /* PCDC <--> USB massage */

usb_cb_t    usb_gpcdc_TxCB;         /* Call Back Function Info Transfer end */
usb_cb_t    usb_gpcdc_RxCB;         /* Call Back Function Info Receive complete */
usb_cb_t    usb_gpcdc_StatusCB;     /* Call Back Function Info Serial Status Transfer end*/
usb_cb_t    usb_gpcdc_AplCB;        /* Control Transfer callback (serial driver control) */


/******************************************************************************
Renesas Abstracted Peripheral Communications Devices Class Driver API functions
******************************************************************************/

/******************************************************************************
Function Name   : R_usb_pcdc_LineCodingInitial
Description     : Line Coding initial
Arguments       : usb_pcdc_LineCoding_t linecoding
Return value    : usb_er_t
******************************************************************************/
usb_er_t R_usb_pcdc_LineCodingInitial( usb_pcdc_LineCoding_t *linecoding )
{
    usb_gcdc_LineCoding.dwDTERate   = linecoding->dwDTERate;
    usb_gcdc_LineCoding.bCharFormat = linecoding->bCharFormat;
    usb_gcdc_LineCoding.bParityType = linecoding->bParityType;
    usb_gcdc_LineCoding.bDataBits   = linecoding->bDataBits;
    usb_gcdc_LineCoding.rsv         = linecoding->rsv;

    return ( USB_E_OK );
}   /* eof R_usb_pcdc_LineCodingInitial() */


/******************************************************************************
Function Name   : R_usb_pcdc_SendData
Description     : Data send request to Host
Arguments       : usb_cbinfo_t complete    : Callback function
Return value    : void
******************************************************************************/
void R_usb_pcdc_SendData( uint8_t *Table, usb_leng_t size, usb_cbinfo_t complete )
{
    usb_gpcdc_TxCB  = (usb_cb_t)complete;
    /* PIPE Transfer set */
    usb_gpcdc_Mess1.pipenum     = usb_gpcdc_Inpipe;
    usb_gpcdc_Mess1.tranadr     = Table;
    usb_gpcdc_Mess1.tranlen     = size;
    usb_gpcdc_Mess1.setup       = 0;
    usb_gpcdc_Mess1.complete    = (usb_cb_t)&usb_pcdc_TransResult;
    usb_gpcdc_Mess1.pipectr     = g_usb_pipe_toggle[usb_gpcdc_Inpipe];
    /* Send message */
    R_usb_pstd_TransferStart( &usb_gpcdc_Mess1 );
}   /* eof R_usb_pcdc_SendData() */


/******************************************************************************
Function Name   : R_usb_pcdc_ReceiveData
Description     : Data Receive request from Host
Arguments       : usb_cbinfo_t complete    : Callback function
Return value    : void
******************************************************************************/
void R_usb_pcdc_ReceiveData( uint8_t *Table, usb_leng_t size, usb_cbinfo_t complete )
{
    usb_gpcdc_RxCB  = (usb_cb_t)complete;
    /* PIPE Transfer set */
    usb_gpcdc_Mess2.pipenum     = usb_gpcdc_Outpipe;
    usb_gpcdc_Mess2.tranadr     = Table;
    usb_gpcdc_Mess2.tranlen     = size;
    usb_gpcdc_Mess2.setup       = 0;
    usb_gpcdc_Mess2.complete    = (usb_cb_t)&usb_pcdc_TransResult;
    usb_gpcdc_Mess2.pipectr     = g_usb_pipe_toggle[usb_gpcdc_Outpipe];
    /* Send message */
    R_usb_pstd_TransferStart( &usb_gpcdc_Mess2 );
}   /* eof R_usb_pcdc_ReceiveData() */


/******************************************************************************
Function Name   : R_usb_pcdc_SendNotification
Description     : Class Notification Serial State request to Host
Arguments       : usb_cbinfo_t complete    : Callback function
Return value    : void
******************************************************************************/
void R_usb_pcdc_SendNotification( uint16_t serial_state, usb_cbinfo_t complete )
{
    usb_gpcdc_StatusCB  = (usb_cb_t)complete;
    /* PIPE Transfer set */
    usb_gpcdc_Mess3.pipenum     = usb_gpcdc_Status_pipe;
    usb_gpcdc_Mess3.tranadr     = (void *)&usb_gpcdc_SerialStateTable[0];
    usb_gpcdc_Mess3.tranlen     = (uint32_t)10;
    usb_gpcdc_Mess3.setup       = 0;
    usb_gpcdc_Mess3.complete    = (usb_cb_t)&usb_pcdc_TransResult;
    usb_gpcdc_Mess3.pipectr     = g_usb_pipe_toggle[usb_gpcdc_Status_pipe];
    usb_gpcdc_SerialStateTable[4] = serial_state;
    /* Send message */
    R_usb_pstd_TransferStart( &usb_gpcdc_Mess3 );
}   /* eof R_usb_pcdc_SendNotification() */


/******************************************************************************
Function Name   : R_usb_pcdc_Registration
Description     : Peripheral Communications Devices Class Task Open
Arguments       : void
Return value    : void
******************************************************************************/
usb_er_t R_usb_pcdc_Registration( usb_pcdreg_t *tbl )
{
    usb_pcdreg_t    driver;
    usb_er_t err;

    err = usb_pcdc_PipeRegistratration(tbl->pipetbl);
    if (err == USB_E_OK)
    {
        /* Driver registration */
        driver.pipetbl      = tbl->pipetbl;
        driver.devicetbl    = tbl->devicetbl;
        driver.configtbl    = tbl->configtbl;
        driver.stringtbl    = tbl->stringtbl;
        driver.statediagram = tbl->statediagram;
        driver.ctrltrans    = tbl->ctrltrans;
        R_usb_pstd_DriverRegistration(&driver);
    }
    else {
        while ( 1 ) {
        }
    }
    
    return err;
}   /* eof R_usb_pcdc_Registration() */


/******************************************************************************
Function Name   : R_usb_pcdc_ClassRequest
Description     : Control transfer
Arguments       : usb_request_t *ptr        : request
                : uint16_t ctsq             : control stage
Return value    : void
******************************************************************************/
void R_usb_pcdc_ClassRequest(usb_request_t *request, uint16_t data)
{
    usb_pipe_t  pipe;

    g_usb_pmsc_Request = *request;

    
    switch( g_usb_pmsc_Request.WORD.BIT.bType )
    {
        case    USB_STANDARD:
            switch( data )
            {
                case USB_SET_INTERFACE:
                    R_usb_pcdc_set_alternate();
                break;
                
                case USB_GET_INTERFACE:
                    R_usb_pcdc_get_alternate();
                break;
                
                case USB_SETREMOTE:
                    /* Processing from which remote wake up is permitted */
                break;

                case USB_CLEARREMOTE:
                    /* Processing from which remote wake up is prohibited */
                break;

                case USB_SETSTALL:
                    /* Processing when the communicating pipe(PIPEx) is set to STALL. */
                break;

                case USB_CLEARSTALL:
                    /* Processing when the communicating pipe(PIPEx) is clear to STALL. */
                    pipe    = R_usb_pcdc_epadr_2_pipe();
                    g_usb_pipe_toggle[pipe] = USB_NULL;
                break;

                case USB_RECIPIENT:
                    /* The report descriptor or and so on respond if it is HID class.  */
                break;

                default:
                break;
            }
        break;
        case    USB_CLASS:
            switch( data )
            {
                case USB_CS_IDST:                           /* Idle or setup stage */
                    usb_pcdc_ControlTrans0(request);
                break;
                case USB_CS_RDDS:                           /* Control read data stage */
                    usb_pcdc_ControlTrans1(request);
                break;
                case USB_CS_WRDS:                           /* Control write data stage */
                    usb_pcdc_ControlTrans2(request);
                break;
                case USB_CS_WRND:                           /* Control write nodata status stage */
                    usb_pcdc_ControlTrans3(request);
                break;
                case USB_CS_RDSS:                           /* Control read status stage */
                    usb_pcdc_ControlTrans4(request);
                break;
                case USB_CS_WRSS:                           /* Control write status stage */
                    usb_pcdc_ControlTrans5(request);
                break;
                case USB_CS_SQER:                           /* Control sequence error */
                    R_usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
                break;
                default:                                    /* Illegal */
                    R_usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
                break;
            }
            break;
        case    USB_VENDOR:
            R_usb_pstd_SetStallPipe0();
        break;
        default:                                            /* Special function */
        break;
    }
}   /* eof R_usb_pcdc_ClassRequest() */


/******************************************************************************
Function Name   : R_usb_pcdc_Release
Description     : Peripheral Communications Devices Class Task Close
Arguments       : void
Return value    : void
******************************************************************************/
void R_usb_pcdc_Release( void )
{
}   /* eof R_usb_pcdc_Release() */


/******************************************************************************
Function Name   : R_usb_pcdc_Task
Description     : Peripheral Communications Devices Class main task
Arguments       : usb_vp_int_t stacd        : start code
Return value    : void
******************************************************************************/
void R_usb_pcdc_Task( void )
{
    usb_utr_t   *mess;
    usb_er_t    err = 0l;

    
    /* Pipe Transfer */
    err = R_USB_RCV_MSG( USB_PCDC_MBX, (usb_msg_t**)&mess );
    if( err != USB_E_OK )
    {
        return;
    }

    switch( mess->msginfo )
    {
    case USB_PCDC_PCONTROL:
        /* Control Transfer callback (serial driver control) */
#ifdef __CA78K0R__
        ((void (*)(usb_utr_t*))usb_gpcdc_AplCB)(mess); /* for CA78K0R compiler */
#else
        (usb_gpcdc_AplCB)(mess);
#endif
        break;
    case USB_PCDC_PTRANSFER:
        if (mess->status  == USB_DATA_STOP)
        {
            return;
        }
        
        if (mess->pipenum == usb_gpcdc_Outpipe)
        {
            /* Data Receive Transfer complete call back */
#ifdef __CA78K0R__
            ((void (*)(usb_utr_t*))usb_gpcdc_RxCB)(mess); /* for CA78K0R compiler */
#else
            (usb_gpcdc_RxCB)(mess);
#endif
        }
        else if (mess->pipenum == usb_gpcdc_Inpipe)
        {
            /* Data Send Transfer complete call back */
#ifdef __CA78K0R__
            ((void (*)(usb_utr_t*))usb_gpcdc_TxCB)(mess); /* for CA78K0R compiler */
#else
            (usb_gpcdc_TxCB)(mess);
#endif
        }
        else if (mess->pipenum == usb_gpcdc_Status_pipe)
        {
            /* Status Send Transfer complete call back */
#ifdef __CA78K0R__
            ((void (*)(usb_utr_t*))usb_gpcdc_StatusCB)(mess); /* for CA78K0R compiler */
#else
            (usb_gpcdc_StatusCB)(mess);
#endif
        }
        else
        {
        }
        break;
    default:
        break;
    }
}   /* eof R_usb_pcdc_Task() */


/******************************************************************************
Function Name   : R_usb_pcdc_epadr_2_pipe
Description     : 
Arguments       : void
Return value    : usb_pipe_t
******************************************************************************/
usb_pipe_t R_usb_pcdc_epadr_2_pipe(void)
{
    uint16_t    *table;
    uint8_t     direp, tmp;

    /* Get PIPE Number from Endpoint address */
    direp           = (uint8_t)(g_usb_pmsc_Request.wIndex & 0x0Fu);
    direp         |= (uint8_t)((g_usb_pmsc_Request.wIndex & 0x80u) >> 3);

    table           = usb_gpcdc_EpTbl1;

    /* Information table search */
    for( ; *table != USB_PDTBLEND; table += USB_EPL )
    {
        /* EP table endpoint dir check */
        tmp = (uint8_t)(table[1] & (USB_DIRFIELD | USB_EPNUMFIELD));
        if( direp == tmp )
        {
            return  (usb_pipe_t)(*table);
        }
    }
    return  USB_PIPE0;
}   /* eof R_usb_pcdc_epadr_2_pipe() */


/******************************************************************************
Function Name   : R_usb_pcdc_set_alternate
Description     : 
Arguments       : void
Return value    : void
******************************************************************************/
void R_usb_pcdc_set_alternate(void)
{
    if ( g_usb_pmsc_Request.wIndex == USB_0 )
    {
        R_usb_pstd_SetPipeRegister(usb_gpcdc_EpTbl1, USB_YES);
    }
}   /* eof R_usb_pcdc_set_alternate() */


/******************************************************************************
Function Name   : R_usb_pcdc_get_alternate
Description     : 
Arguments       : void
Return value    : void
******************************************************************************/
void R_usb_pcdc_get_alternate(void)
{
    uint8_t alternate_num;
    
    alternate_num = USB_0;
    R_usb_pstd_ControlRead(USB_1, &alternate_num);
}   /* eof R_usb_pcdc_get_alternate() */

#endif	// USB_SERIAL_USE

/******************************************************************************
End Of File
******************************************************************************/
