/******************************************************************************
* File Name     : r_usb_pcdc_driver.h
* Version       : 2.10
* Description   : USB Peripheral PCDC Header
******************************************************************************
* History   : DD.MM.YYYY Version Description
*           : 30.11.2012 2.00    First Release
*           : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
******************************************************************************/
#ifndef __R_USB_PCDC_DRIVER_H__
#define __R_USB_PCDC_DRIVER_H__


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_usrconfig.h"            /* System definition, USB-FW Library Header */
#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"

#include "r_usb_pcdc_Define.h"


/******************************************************************************
Private global variables and functions
******************************************************************************/
extern void     usb_pcdc_TransResult( usb_utr_t *mess );
extern void     usb_pcdc_ControlTrans0( usb_request_t *req );
extern void     usb_pcdc_ControlTrans1( usb_request_t *req );
extern void     usb_pcdc_ControlTrans2( usb_request_t *req );
extern void     usb_pcdc_ControlTrans3( usb_request_t *req );
extern void     usb_pcdc_ControlTrans4( usb_request_t *req );
extern void     usb_pcdc_ControlTrans5( usb_request_t *req );
extern usb_er_t usb_pcdc_PipeRegistratration( uint16_t *eptbl );
extern void     usb_pcdc_AplRequest( uint8_t key, uint16_t size, uint8_t *Table );


extern uint16_t                     usb_gcdc_SendBreakDuration;     /* Duration of Break */
extern uint8_t                      usb_gpcdc_Outpipe;              /* Pipe Direction from Host to Device */
extern uint8_t                      usb_gpcdc_Inpipe;               /* Pipe Direction from Device to Host */
extern uint8_t                      usb_gpcdc_Status_pipe;          /* Pipe Direction from Device to Host */
extern usb_pcdc_ControlLineState_t  usb_gcdc_ControlLineState;      /* Control Line Status data */
extern usb_pcdc_LineCoding_t        usb_gcdc_LineCoding;            /* Line Coding data */
extern usb_utr_t                    usb_gpcdc_Mess4;                /* PCDC <--> Application massage */


#endif  /* __R_USB_PCDC_DRIVER_H__ */
/******************************************************************************
End Of File
******************************************************************************/
