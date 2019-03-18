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
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name     : scidriver.c
* Version       : x.xx
* Description   : This is the SCI driver function code.
*******************************************************************************/
/*******************************************************************************
* History   : DD.MM.YYYY Version Description
*           : xx.xx.xxxx x.xx    Basic FW mini Ver2.00
*******************************************************************************/

/******************************************************************************
Section definitions
******************************************************************************/
#ifdef  __RX
#endif


/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_usrconfig.h"            /* System definition */
#include "iodefine.h"                   /* MCU IO definition */
#include "hw_resource.h"

#ifdef	USB_SERIAL_USE

#ifdef  USB_SCI_ENABLE
/******************************************************************************
Macro definitions
******************************************************************************/
/* There is no macro definition. */

/******************************************************************************
Typedef definitions
******************************************************************************/
/* There is no typedef definition. */


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
/* variables */

/* functions */
void usb_cpu_SciInitial(void);


/******************************************************************************
Private global variables and functions
******************************************************************************/
/* There is no private global variables and functions. */


/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/* There is no imported global variables and functions. */



/******************************************************************************
Renesas Abstracted SCI driver function
******************************************************************************/

/*****************************************************************************
* Function Name: usb_cpu_SciInitial
* Description  : This function initializes the port pins associated with 
*                channel 1 for the RSKRX111. Pins are configured for TX/RX 
*                operation.
* Arguments    : none
* Return Value : none
******************************************************************************/
void usb_cpu_SciInitial(void)
{
    MPC.PWPR.BIT.B0WI = 0;
    MPC.PWPR.BIT.PFSWE = 1;

    /* init channel 12 */
    PORTE.PODR.BIT.B1 = 0;      /* set line low (dflt)  */
    MPC.PE1PFS.BYTE = 0x0C;     /* Pin Func Select PE1 TX   */
    MPC.PE2PFS.BYTE = 0x0C;     /* Pin Func Select PE2 RX   */
    PORTE.PDR.BIT.B1 = 1;       /* set TX pin direction to output   */
    PORTE.PDR.BIT.B2 = 0;       /* set RX pin direction to input (dflt) */
    PORTE.PMR.BIT.B1 = 1;       /* set TX pin mode to peripheral    */
    PORTE.PMR.BIT.B2 = 1;       /* set RX pin mode to peripheral    */

    MPC.PWPR.BIT.PFSWE = 0;

    return;
} /* eof usb_cpu_SciInitial() */


#endif /* USB_SCI_ENABLE */

#endif	// USB_SERIAL_USE

/******************************************************************************
End Of File
******************************************************************************/
