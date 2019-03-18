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
* File Name    : r_usb_pcdc_apl_descriptor.c
* Version      : 2.10
* Description  : USB Peripheral Sample Code
*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.11.2012 2.00    Basic FW mini Ver2.00(MP Version)
*         : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
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

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_cdefusbip.h"            /* USB-FW Library Header */
#include "r_usb_usrconfig.h"            /* System definition, USB-FW Library Header */
#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"

#include "r_usb_pcdc_Driver.h"
#include "r_usb_pcdc_Define.h"
#include "r_usb_pcdc_Api.h"

#ifdef	USB_SERIAL_USE

/******************************************************************************
Constant macro definitions
******************************************************************************/
    #define USB_VENDORID        (0x045Bu)       /* Vendor  ID */
    #define USB_PRODUCTID       (0x82F4u)       /* Product ID */
    
    #define USB_BCDNUM          (0x0200u)       /* bcdUSB */
    #define USB_RELEASE         (0x0100u)       /* Release Number */
    #define USB_DCPMAXP         (64u)           /* DCP max packet size */
    #define USB_CONFIGNUM       (1u)            /* Configuration number */

/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
Constant macro definitions
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/

/* Configuration 1 */
uint16_t usb_gpcdc_EpTbl1[ 0x14u ] =
{
    /* PIPE4 Definition */
    USB_PIPE4,
    USB_BULK | USB_BFREOFF | USB_DBLBON | USB_SHTNAKON | USB_DIR_P_IN | USB_EP1,
    USB_MAX_PACKET(64),
    USB_NULL,
    /* PIPE5 Definition */
    USB_PIPE5,
    USB_BULK | USB_BFREOFF | USB_DBLBON | USB_SHTNAKON | USB_DIR_P_OUT | USB_EP2,
    USB_MAX_PACKET(64),
    USB_NULL,
    /* PIPE6 Definition */
    USB_PIPE6,
    USB_INT | USB_DIR_P_IN | USB_EP3,
    USB_MAX_PACKET(16),
    USB_NULL,
    /* Pipe end */
    USB_PDTBLEND
};



/* Standard Device Descriptor */
uint8_t usb_gpcdc_DeviceDescriptor[ 0x12u ] =
{
    0x12u,                                                      /* bLength */
    0x01u,                                                      /* bDescriptorType (0x01=Device Descriptor Type) */
    0x00u,                                                      /* bcdUSB (Lower) */
    0x02u,                                                      /* bcdUSB (Upper) */
    0x02u,                                                      /* bDeviceClass    (0x02=CDC) */
    0x00u,                                                      /* bDeviceSubClass (CDC, unused at this time) */
    0x00u,                                                      /* bDeviceProtocol (CDC, unused at this time) */
    0x40u,                                                      /* bMaxPacketSize0 */
    (uint8_t)(USB_VENDORID                  & (uint8_t)0xFFu),  /* idVendor  (Lower) */
    (uint8_t)((uint8_t)(USB_VENDORID >> 8)  & (uint8_t)0xFFu),  /* idVendor  (Upper) */
    (uint8_t)(USB_PRODUCTID                 & (uint8_t)0xFFu),  /* idProduct (Lower) */
    (uint8_t)((uint8_t)(USB_PRODUCTID >> 8) & (uint8_t)0xFFu),  /* idProduct (Upper) */
    0x00u,                                                      /* bcdDevice (Lower) */
    0x10u,                                                      /* bcdDevice (Upper) */
    0x01u,                                                      /* iManufacturer */
    0x02u,                                                      /* iProduct */
    0x05u,                                                      /* iSerialNumber */
    0x01u                                                       /* bNumConfiguration */
};


/************************************************************
 *  Configuration Or Other_Speed_Configuration Descriptor   *
 ************************************************************/
/* For Full-Speed */
uint8_t usb_gpcdc_ConfigrationF1[ 0x09u + 0x09u + 0x05u + 0x04u + 0x05u + 0x05u + 0x07u + 0x09u + 0x07u + 0x07u ] =
{
    /* Configuration Descriptor */
    0x09u,                          /* bLength */
    0x02u,                          /* bDescriptorType (0x02=Configuration Descriptor Type) */
    0x43u,                          /* wTotalLength (Lower) */
    0x00u,                          /* wTotalLength (Upper) */
    0x02u,                          /* bNumInterface */
    0x01u,                          /* bConfigurationValue */
    0x00u,                          /* iConfiguration */
    (uint8_t)(USB_CF_RESERVED),     /* bmAttributes */
    (uint8_t)(50 / 2),              /* MaxPower */
    
    /* Interface Descriptor */
        0x09u,                      /* bLength */
        0x04u,                      /* bDescriptorType    (0x04=Interface Descriptor Type) */
        0x00u,                      /* bInterfaceNumber */
        0x00u,                      /* bAlternateSetting */
        0x01u,                      /* bNumEndpoints */
        0x02u,                      /* bInterfaceClass    (0x02=Communication Interface Class) */
        0x02u,                      /* bInterfaceSubClass (0x02=Abstract Control Model) */
        0x01u,                      /* bInterfaceProtocol (0x01=AT Commands:[V250] etc) */
        0x00u,                      /* iInterface */

    /* Sample Class-Specific Function Descriptors for Communications Class Functional Descriptors */
            0x05u,                  /* bFunctionLength */
            0x24u,                  /* bDescriptorType    (0x24=CS_INTERFACE) */
            0x00u,                  /* bDescriptorSubtype (0x00=Header. This is defined in [USBCDC1.2]) */
            0x10u,                  /* bcdCDC (Lower) */
            0x01u,                  /* bcdCDC (Upper) */

            0x04u,                  /* bFunctionLength */
            0x24u,                  /* bDescriptorType    (0x24=CS_INTERFACE) */
            0x02u,                  /* bDescriptorSubtype (0x02=Abstract Control Management functional descriptor subtype as defined in [USBCDC1.2].*/
            0x02u,                  /* bmCapabilities     (0x02=bit1:Device supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State */

            0x05u,                  /* bFunctionLength */
            0x24u,                  /* bDescriptorType        (0x24=CS_INTERFACE) */
            0x06u,                  /* bDescriptorSubtype     (0x06=Union Descriptor Functional Descriptor subtype as defined in [USBCDC1.2]. */
            0x00u,                  /* bControlInterface      (0x00=Interface number of the control (Communications Class) interface) */
            0x01u,                  /* bSubordinateInterface0 (0x01=Interface number of the subordinate (Data Class) interface */

            0x05u,                  /* bFunctionLength */
            0x24u,                  /* bDescriptorType        (0x24=CS_INTERFACE) */
            0x01u,                  /* bDescriptorSubtype     (0x01=Call Management Functional Descriptor 
subtype as defined in [USBCDC1.2].) */
            0x03u,                  /* bmCapabilities         (0x03= */
            0x01u,                  /* bDataInterface         (0x01= */

            0x07u,                  /* bLength */
            0x05u,                  /* bDescriptorType   (0x05=ENDPOINT Descriptor Type) */
            USB_EP_IN | USB_EP3,    /* bEndpointAddress  */
            0x03u,                  /* bmAttributes      (0x03=Interrupt) */
            0x10u,                  /* wMaxPacketSize (Lower) */
            0x00u,                  /* wMaxPacketSize (Upper) */
            0xffu,                  /* bInterval */

    /* Interface Descriptor */
        0x09u,                      /* bLength */
        0x04u,                      /* bDescriptorType    (0x04=Interface Descriptor Type) */
        0x01u,                      /* bInterfaceNumber */
        0x00u,                      /* bAlternateSetting */
        0x02u,                      /* bNumEndpoints */
        0x0Au,                      /* bInterfaceClass    (0x0A=) */
        0x00u,                      /* bInterfaceSubClass (0x00=) */
        0x00u,                      /* bInterfaceProtocol (0x00=) */
        0x00u,                      /* iInterface         (0x00=) */

            0x07u,                  /* bFunctionLength */
            0x05u,                  /* bDescriptorType   (0x05=ENDPOINT Descriptor Type) */
            USB_EP_IN | USB_EP1,    /* bEndpointAddress */
            0x02u,                  /* bmAttributes      (0x02=Bulk) */
            0x40u,                  /* wMaxPacketSize (Lower) */
            0x00u,                  /* wMaxPacketSize (Upper) */
            0x00u,                  /* bInterval */

            0x07u,                  /* bFunctionLength */
            0x05u,                  /* bDescriptorType   (0x05=ENDPOINT Descriptor Type) */
            USB_EP_OUT | USB_EP2,   /* bEndpointAddress */
            0x02u,                  /* bmAttributes      (0x02=Bulk) */
            0x40u,                  /* wMaxPacketSize (Lower) */
            0x00u,                  /* wMaxPacketSize (Upper) */
            0x00u                   /* bInterval */
};



/*************************************
 *    String Descriptor              *
 *************************************/

/* Language ID */
uint8_t usb_gpcdc_StringDescriptor0[ 0x04u ] =
{
    0x04u,                  /* bLength */
    0x03u,                  /* bDescriptorType (0x03=String Descriptor Type) */
    0x09u,                  /* bString (Lower) (0x0409=UNICODE U.S.English)  */
    0x04u                   /* bString (Upper) (0x0409=UNICODE U.S.English)  */
};



/* iManufacturer */
uint8_t usb_gpcdc_StringDescriptor1[ 0x40u ] =
{
    0x40u,                  /* bLength */
    0x03u,                  /* bDescriptorType (0x03=String Descriptor Type) */
    'R', 0x00,
    'e', 0x00,
    'n', 0x00,
    'e', 0x00,
    's', 0x00,
    'a', 0x00,
    's', 0x00,
    ' ', 0x00,
    'E', 0x00,
    'l', 0x00,
    'e', 0x00,
    'c', 0x00,
    't', 0x00,
    'r', 0x00,
    'o', 0x00,
    'n', 0x00,
    'i', 0x00,
    'c', 0x00,
    's', 0x00,
    ' ', 0x00,
    'C', 0x00,
    'o', 0x00,
    'r', 0x00,
    'p', 0x00,
    'o', 0x00,
    'r', 0x00,
    'a', 0x00,
    't', 0x00,
    'i', 0x00,
    'o', 0x00,
    'n', 0x00
};


/* iProduct */
uint8_t usb_gpcdc_StringDescriptor2[ 0x2Cu ] =
{
    0x2Cu,                  /* bLength */
    0x03u,                  /* bDescriptorType (0x03=String Descriptor Type) */
    'T', 0x00,
    'o', 0x00,
    'u', 0x00,
    'c', 0x00,
    'h', 0x00,
    'A', 0x00,
    'P', 0x00,
    'I', 0x00,
    ' ', 0x00,
    'U', 0x00,
    'S', 0x00,
    'B', 0x00,
    '-', 0x00,
    'C', 0x00,
    'O', 0x00,
    'M', 0x00,
    ' ', 0x00,
    'P', 0x00,
    'o', 0x00,
    'r', 0x00,
    't', 0x00
};



uint8_t usb_gpcdc_StringDescriptor3[ 0x2Eu ] =
{
    0x2Eu,              /* bLength */
    0x03u,              /* bDescriptorType (0x03=String Descriptor Type) */
    'C', 0x00,
    'o', 0x00,
    'm', 0x00,
    'm', 0x00,
    'u', 0x00,
    'n', 0x00,
    'i', 0x00,
    'c', 0x00,
    'a', 0x00,
    't', 0x00,
    'i', 0x00,
    'o', 0x00,
    'n', 0x00,
    's', 0x00,
    ' ', 0x00,
    'D', 0x00,
    'e', 0x00,
    'v', 0x00,
    'i', 0x00,
    'c', 0x00,
    'e', 0x00,
    's', 0x00
};



uint8_t usb_gpcdc_StringDescriptor4[ 0x16u ] =
{
    0x16u,                  /* bLength */
    0x03u,                  /* bDescriptorType (0x03=String Descriptor Type) */
    'F', 0x00,
    'u', 0x00,
    'l', 0x00,
    'l', 0x00,
    '-', 0x00,
    'S', 0x00,
    'p', 0x00,
    'e', 0x00,
    'e', 0x00,
    'd', 0x00
};



/* iSerialNumber */
uint8_t usb_gpcdc_StringDescriptor5[ 0x1Eu ] =
{
    0x1Eu,                  /* bLength */
    0x03u,                  /* bDescriptorType (0x03=String Descriptor Type) */
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '0', 0x00,
    '1', 0x00
};



uint8_t *usb_gpcdc_StrPtr[ 0x07u ] =
{
    usb_gpcdc_StringDescriptor0,
    usb_gpcdc_StringDescriptor1,
    usb_gpcdc_StringDescriptor2,
    usb_gpcdc_StringDescriptor3,
    usb_gpcdc_StringDescriptor4,
    usb_gpcdc_StringDescriptor5,
    usb_gpcdc_StringDescriptor0
};


/******************************************************************************
Renesas Abstracted Peripheral Communications Devices Class Driver API functions
******************************************************************************/

#endif	// USB_SERIAL_USE

/******************************************************************************
End  Of File
******************************************************************************/
