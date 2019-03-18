/******************************************************************************
* File Name     : r_usb_pcdc_define.h
* Version       : 2.10
* Description   : USB Peripheral PCDC Header
******************************************************************************
* History   : DD.MM.YYYY Version Description
*           : 30.11.2012 2.00    First Release
*           : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
******************************************************************************/
#ifndef __R_USB_PCDC_DEFINE_H__
#define __R_USB_PCDC_DEFINE_H__


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_usrconfig.h"            /* System definition, USB-FW Library Header */
#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"


/*****************************************************************************
Macro definitions
******************************************************************************/
/* CDC Class Requests IDs*/
#define USB_PCDC_SET_LINE_CODING            0x20
#define USB_PCDC_GET_LINE_CODING            0x21
#define USB_PCDC_SET_CONTROL_LINE_STATE     0x22
#define USB_PCDC_SEND_BREAK                 0x23

/* GET_LINE_CODING request wLength */
#define USB_PCDC_GET_LINE_CODING_LENGTH     0x07

#define USB_CDC_SPEED_1200  1200u
#define USB_CDC_SPEED_2400  2400u    /* Line Coding 2400bps */
#define USB_CDC_SPEED_4800  4800u    /* Line Coding 4800bps */
#define USB_CDC_SPEED_9600  9600u    /* Line Coding 9600bps */
#define USB_CDC_SPEED_14400 14400u   /* Line Coding 14400bps */
#define USB_CDC_SPEED_19200 19200u   /* Line Coding 19200bps */
#define USB_CDC_SPEED_38400     38400u   /* Line Coding 38400bps */
#define USB_CDC_SPEED_57600     57600u   /* Line Coding 57600bps */
#define USB_CDC_SPEED_115200    115200u   /* Line Coding 115200bps */


/*****************************************************************************
Enumerated Types
******************************************************************************/
/* USB Communications Devices Device Class Phase. */
enum usb_gpcdc_Phase
{
    USB_PCDC_PCONTROL   = 0x10,     /* Class Request */
    USB_PCDC_PTRANSFER  = 0x11      /* Data Transfer */
};

typedef enum 
{
    USB_CDC_DATA_BIT_7     = 7u,   /* Line Coding 7Data bits */
    USB_CDC_DATA_BIT_8     = 8u    /* Line Coding 8Data bits */
} USB_CDC_DATA_BIT_t;

typedef enum 
{
    USB_CDC_STOP_BIT_1     = 0u,   /* Line Coding 1Stop bits */
    USB_CDC_STOP_BIT_15        = 1u,   /* Line Coding 1.5Stop bits */
    USB_CDC_STOP_BIT_2     = 2u    /* Line Coding 2Stop bits */
} USB_CDC_STOP_BIT_t;

typedef enum 
{
    USB_CDC_PARITY_BIT_NONE    = 0u,   /* Line Coding None Parity */
    USB_CDC_PARITY_BIT_ODD = 1u,   /* Line Coding Odd Parity */
    USB_CDC_PARITY_BIT_EVEN    = 2u    /* Line Coding Even Parity */
} USB_CDC_PARITY_BIT_t;

#if 0 // mura
typedef enum 
{
    USB_CDC_SPEED_1200     = 1200u,    /* Line Coding 1200bps */
    USB_CDC_SPEED_2400     = 2400u,    /* Line Coding 2400bps */
    USB_CDC_SPEED_4800     = 4800u,    /* Line Coding 4800bps */
    USB_CDC_SPEED_9600     = 9600u,    /* Line Coding 9600bps */
    USB_CDC_SPEED_14400        = 14400u,   /* Line Coding 14400bps */
    USB_CDC_SPEED_19200        = 19200u,   /* Line Coding 19200bps */
    USB_CDC_SPEED_38400        = 38400u,   /* Line Coding 38400bps */
    USB_CDC_SPEED_57600        = 57600u,   /* Line Coding 57600bps */
    USB_CDC_SPEED_115200       = 115200u   /* Line Coding 115200bps */
} USB_CDC_LINE_SPEED_t;
#endif // mura

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct
{
    uint32_t    dwDTERate;      /* Data terminal rate, in bits per second */
    uint8_t     bCharFormat;    /* Stop bits */
    uint8_t     bParityType;    /* Parity */
    uint8_t     bDataBits;      /* Data bits */
    uint8_t     rsv;            /* reserve */
} usb_pcdc_LineCoding_t;


typedef struct
{
    uint16_t    bDTR:1; /* DTR */
    uint16_t    bRTS:1; /* RTS */
    uint16_t    rsv:14; /* reserve */
} usb_pcdc_ControlLineState_t;


typedef struct
{
    
    uint16_t    bRxCarrier:1;   /* DCD signal */
    uint16_t    bTxCarrier:1;   /* DSR signal */
    uint16_t    bBreak:1;       /* State of break detection mechanism of teh device */
    uint16_t    bRingSignal:1;  /* State of ring signal detection of the device */
    uint16_t    bFraming:1;     /* Framing error */
    uint16_t    bParity:1;      /* Framing error */
    uint16_t    bOverRun:1;     /* Over Run error */
    uint16_t    rsv:9;          /* reserve */
} usb_pcdc_SerialState_t;


typedef struct
{
    uint16_t        *pipetbl;       /* Pipe Define Table address */
    uint8_t         *devicetbl;     /* Device descriptor address */
    uint8_t         *configtbl;     /* Configuration descriptor address */
    uint8_t         **stringtbl;    /* String descriptor address */
    usb_cbinfo_t    statediagram;   /* Device status */
    usb_cb_trn_t    ctrltrans;      /* Control Transfer */
    usb_cb_t        aplcb;          /* Application callback function */
} usb_cdcreg_t;


#endif  /* __R_USB_PCDC_DEFINE_H__ */
/******************************************************************************
End Of File
******************************************************************************/
