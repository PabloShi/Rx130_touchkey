/******************************************************************************
* File Name     : r_usb_pcdc_api.h
* Version       : 2.10
* Description   : USB Peripheral PCDC Header
******************************************************************************
* History   : DD.MM.YYYY Version Description
*           : 30.11.2012 2.00    First Release
*           : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
******************************************************************************/
#ifndef __R_USB_PCDC_API_H__
#define __R_USB_PCDC_API_H__


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_usrconfig.h"            /* System definition, USB-FW Library Header */
#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"


/******************************************************************************
Constant macro definitions
******************************************************************************/

#define USB_CDC_SETUP_TBL_SIZE  5   /* setup packet table size (uint16_t * 5) */


/******************************************************************************
Private global variables and functions
******************************************************************************/
extern usb_er_t     R_usb_pcdc_LineCodingInitial( usb_pcdc_LineCoding_t *linecoding );
extern void         R_usb_pcdc_SendData( uint8_t *Table, usb_leng_t size, usb_cbinfo_t complete );
extern void         R_usb_pcdc_ReceiveData( uint8_t *Table, usb_leng_t size, usb_cbinfo_t complete );
extern void         R_usb_pcdc_SendNotification( uint16_t serial_state, usb_cbinfo_t complete );
extern usb_er_t     R_usb_pcdc_Registration( usb_pcdreg_t *tbl );
extern void         R_usb_pcdc_ClassRequest( usb_request_t *ptr, uint16_t ctsq );
extern void         R_usb_pcdc_Release( void );
extern void         R_usb_pcdc_Task( void );



extern uint16_t     usb_gpcdc_SerialStateTable[ USB_CDC_SETUP_TBL_SIZE ];


extern usb_utr_t    usb_gpcdc_Mess1;        /* PCDC <--> USB massage */
extern usb_utr_t    usb_gpcdc_Mess2;        /* PCDC <--> USB massage */
extern usb_utr_t    usb_gpcdc_Mess3;        /* PCDC <--> USB massage */

extern usb_cb_t     usb_gpcdc_TxCB;         /* Call Back Function Info Transfer end */
extern usb_cb_t     usb_gpcdc_RxCB;         /* Call Back Function Info Receive complete */
extern usb_cb_t     usb_gpcdc_StatusCB;     /* Call Back Function Info Serial Status Transfer end*/
extern usb_cb_t     usb_gpcdc_AplCB;        /* Control Transfer callback (serial driver control) */



#endif  /* __R_USB_PCDC_API_H__ */
/******************************************************************************
End Of File
******************************************************************************/
