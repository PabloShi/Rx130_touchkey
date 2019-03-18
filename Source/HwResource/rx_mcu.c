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
* File Name    : rx_mcu.c
* Version      : 3.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file is the RX113 and RX231 RSK board control driver code.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History   : DD.MM.YYYY Version Description
*           : 01.08.2013 2.10    Basic Mini FW Ver2.10 Release
*           : xx.xx.2015 3.00    RX113,RX231 code addition
***********************************************************************************************************************/

/***********************************************************************************************************************
 Section definitions
***********************************************************************************************************************/

/* Start user code for pragma. Do not edit comment generated here. */
/* End user code. Do not edit comment generated here. */

/***********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <machine.h>

#include "r_usb_ctypedef.h"             /* Type define */
#include "r_usb_ckernelid.h"            /* Kernel ID definition */
#include "r_usb_usrconfig.h"            /* System definition */
#include "r_usb_cdefusbip.h"            /* USB-FW Library Header */
#include "r_usb_regaccess.h"            /* Definition of the USB register access macro */
#include "r_usb_usbip.h"                /* Definition of the USB register & bit define */

#include "iodefine.h"                   /* MCU IO definition */
#include "r_usb_api.h"                  /* USB API public function header */
#include "hw_resource.h"
#include "r_dtc.h"
#include "r_ctsu.h"
#include "r_cgc.h"

#ifdef	USB_SERIAL_USE
/***********************************************************************************************************************
 Macro definitions
***********************************************************************************************************************/
/* There is no macro definition. */

/***********************************************************************************************************************
 Bit Order Definition "LEFT"
***********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
***********************************************************************************************************************/
/* There is no typedef definition. */

/***********************************************************************************************************************
 Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
/*=== SYSTEM ================================================================*/
void        usb_cpu_target_init(void);
/*=== Interrupt =============================================================*/
void        usb_cpu_usbint_init(void);
void        usb_cpu_int_enable(void);
void        usb_cpu_int_disable(void);
/*=== TIMER =================================================================*/
void        usb_cpu_delay_1us(uint16_t time);
void        usb_cpu_delay_xms(uint16_t time);

/*=== DTC ===================================================================*/
void usb_cpu_d0fifo_interrupt_process();
void usb_cpu_buf2fifo_start_dma();
void usb_cpu_fifo2buf_start_dma();
void usb_cpu_d0fifo_stop_dma();
void usb_cpu_d0fifo_stop_usb();
void usb_cpu_d0fifo_restart_dma();
uint16_t usb_cpu_get_dtc_block_count();
void usb_cpu_d0fifo_interrupt_handler(void);

uint16_t usb_cpu_get_transfer_mode(void);
void usb_cpu_set_d0fifo_pipeX(void);


/***********************************************************************************************************************
 Private global variables and functions
***********************************************************************************************************************/
/*=== SYSTEM ================================================================*/
void        usb_cpu_set_pin_function(void);
/*=== Interrupt =============================================================*/
void        usb_cpu_usb_interrupt(void);
void        usb_cpu_usb_resume_interrupt(void);
void        usb_cpu_irq0_interrupt(void);
void        usb_cpu_d0fifo_interrupt(void);

/*=== OTHER =================================================================*/
void        usb_cpu_irq0_interrupt_enable(void);
void        usb_cpu_suspend_sleep(void);
void        usb_cpu_deep_sleep_mode(void);
void        usb_cpu_soft_stanby_mode(void);
void        usb_cpu_detach_sleep(void);

void        usb_cpu_DmaintInit(void);


/***********************************************************************************************************************
 Pragma directive
***********************************************************************************************************************/
#pragma interrupt usb_cpu_usb_interrupt(vect = VECT(USB0, USBI0))
#pragma interrupt usb_cpu_usb_resume_interrupt(vect = VECT(USB0, USBR0))
#pragma interrupt usb_cpu_irq0_interrupt(vect = VECT(ICU, IRQ0))
#pragma interrupt usb_cpu_d0fifo_interrupt(vect = VECT(USB0, D0FIFO0))

#pragma address dtc_vector36=0x00007C90U
uint32_t dtc_vector36;
dtc_register_data_t       usb_dtcreg;

/***********************************************************************************************************************
 Imported global variables and functions (from other files)
***********************************************************************************************************************/
/* variables */
extern usb_leng_t       g_usb_LibDataCnt[];                 /* PIPEn Buffer counter */
extern uint8_t          *g_usb_LibDataPtr[];                /* PIPEn Buffer pointer(8bit) */
extern usb_pipe_t       g_usb_CurrentPipe;                  /* Pipe number */

extern uint16_t         g_usb_LibTemp;                  /* macro temp */


/* functions */
extern void     usb_smpl_set_suspend_flag(uint8_t data);
extern void usb_cstd_brdy_enable(void);
extern void usb_cstd_bemp_enable(void);
extern void usb_cstd_nrdy_enable(void);
extern void usb_cstd_brdy_disable(void);
extern void usb_cstd_reg_set_pipexctr(uint16_t field);

/* Peripheral function drivers */
#ifdef USB_LCD_ENABLE
extern void     usb_cpu_LcdInitial(void);
#endif  /* USB_LCD_ENABLE */

#ifdef USB_ADC_ENABLE
extern void     usb_cpu_adc_enable(void);
#endif  /* USB_ADC_ENABLE */

#ifdef USB_LED_ENABLE
extern void     usb_cpu_LedInitial(void);
#endif  /* USB_LED_ENABLE */

#ifdef USB_KEY_ENABLE
#endif  /* USB_KEY_ENABLE */

#ifdef USB_SCI_ENABLE
extern void     usb_cpu_SciInitial(void);
#endif  /* USB_SCI_ENABLE */

extern void     usb_smpl_set_intkey(uint8_t data);

usb_intinfo_t   g_usb_LibIntMessageD0fifo;                  /* USB D0fifo Interrupt message */

/* DMA0 direction */
uint16_t        usb_gcstd_Dma0Dir;
/* DMA0 buffer size */
usb_leng_t      usb_gcstd_Dma0Size;
/* DMA0 FIFO buffer size */
uint16_t        usb_gcstd_Dma0Fifo;
/* DMA0 pipe number */
uint16_t        usb_gcstd_Dma0Pipe;

/***********************************************************************************************************************
 Section    <Section Definition> , "Project Sections"
***********************************************************************************************************************/

/***********************************************************************************************************************
 Renesas Abstracted RSK board control driver functions
***********************************************************************************************************************/

/***********************************************************************************************************************
Function Name   : usb_cpu_target_init
Description     : Target System Initialize
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_target_init(void)
{
    usb_cpu_set_pin_function();         /* Interim procedures */

    usb_cpu_usbint_init();              /* Initialized USB interrupt */
    usb_cpu_DmaintInit();

#ifdef USB_LED_ENABLE
    usb_cpu_LedInitial();
#endif /* USB_LED_ENABLE */

#ifdef USB_LCD_ENABLE
    usb_cpu_LcdInitial();
#endif  /* USB_LCD_ENABLE */

#ifdef USB_ADC_ENABLE
    usb_cpu_adc_enable();
#endif  /* USB_ADC_ENABLE */

#ifdef USB_SCI_ENABLE
    usb_cpu_SciInitial();       /* FOR RSKRX111 ONLY!   */
#endif  /* USB_SCI_ENABLE */

    usb_smpl_set_suspend_flag(USB_NO);  /* Interrupt notification flag clear */
    usb_cpu_irq0_interrupt_enable();
} /* eof usb_cpu_target_init() */


/***********************************************************************************************************************
Function Name   : usb_cpu_usbint_init
Description     : USB interrupt Initialize
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_usbint_init(void)
{
#if USB_FUNCSEL_PP == USB_PERI_PP
#ifdef USB_PERI_BC_ENABLE
    USB0.USBMC.BIT.VDDUSBE = 1;
#endif  /* USB_PERI_BC_ENABLE */

#if (MCU_SERIES_T == R5F5231)
    USB0.USBMC.BIT.VDCEN = USB_VDCEN;
#endif    // (MCU_SERIES_T == R5F5231)

    PORT1.PMR.BIT.B6 = 0;               /* USB0_VBUS */
    
    MPC.PWPR.BIT.B0WI = 0;
    MPC.PWPR.BIT.PFSWE = 1;

#if (MCU_SERIES_T == R5F5113)
    MPC.P16PFS.BYTE = 0x12;             /* USB0_VBUS */
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5231)
    MPC.P16PFS.BYTE = 0x11;             /* USB0_VBUS */
#endif    // (MCU_SERIES_T == R5F5231)

    MPC.PWPR.BIT.PFSWE = 0;

    PORT1.PMR.BIT.B6 = 1;               /* USB0_VBUS */

#endif  /* USB_FUNCSEL_PP == USB_PERI_PP */

#if USB_FUNCSEL_PP == USB_HOST_PP
#ifdef USB_HOST_BC_ENABLE
    USB0.USBMC.BIT.VDDUSBE = 1;
#endif  /* USB_HOST_BC_ENABLE */

    PORT2.PMR.BIT.B6 = 0;               /* USB0_VBUSEN */
    PORTB.PMR.BIT.B3 = 0;               /* USB0_OVRCURA */

    MPC.PWPR.BIT.B0WI = 0;
    MPC.PWPR.BIT.PFSWE = 1;

    MPC.P26PFS.BYTE = 0x13;             /* USB0_VBUSEN */
    MPC.PB3PFS.BYTE = 0x13;             /* USB0_OVRCURA */

    MPC.PWPR.BIT.PFSWE = 0;

    PORT2.PMR.BIT.B6 = 1;               /* USB0_VBUSEN */
    PORTB.PMR.BIT.B3 = 1;               /* USB0_OVRCURA */
#endif  /* USB_FUNCSEL_PP == USB_HOST_PP */

    /* Disable USB0 D0FIFO interrupt(D0FIFO0) */
    ICU.IER[0x04].BIT.IEN4 = 0;

    /* Disable USB0 D1FIFO interrupt(D1FIFO0) */
    ICU.IER[0x04].BIT.IEN5 = 0;

    /* Enable USB0 USBI0 interrupt(USBI0) */
    ICU.IER[0x04].BIT.IEN6 = 1;

    /* Disable USB0 Resume interrupt(USBR0) */
    ICU.IER[0x0B].BIT.IEN2 = 0;

    /* Priority D0FIFO0 = 0(Disable) */
    ICU.IPR[36].BYTE = 0x00;

    /* Priority D1FIFO0 = 0(Disable) */
    ICU.IPR[37].BYTE = 0x00;

    /* Priority USBI0 = 3(Enable) */
    ICU.IPR[38].BYTE = 0x03;

    /* Priority USBR0 = 0(Disable) */
    ICU.IPR[90].BYTE = 0x00;
} /* eof usb_cpu_usbint_init() */


/***********************************************************************************************************************
Function Name   : usb_cpu_int_enable
Description     : USB Interrupt Enable
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_int_enable(void)
{
    ICU.IER[4].BIT.IEN6 = 1;            /* Enable USBI0 interrupt */
} /* eof usb_cpu_int_enable() */


/***********************************************************************************************************************
Function Name   : usb_cpu_int_disable
Description     : USB Interrupt disable
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_int_disable(void)
{
    ICU.IER[4].BIT.IEN6 = 0;            /* Disable USBI0 interrupt */
} /* eof usb_cpu_int_disable() */


/***********************************************************************************************************************
Function Name   : usb_cpu_delay_1us
Description     : 1us Delay timer
Arguments       : uint16_t time         ; Delay time(*1us)
Return value    : none
***********************************************************************************************************************/
void usb_cpu_delay_1us(uint16_t time)
{
    volatile register uint16_t  i;

    /* Wait 1us (Please change for your MCU) */
    for( i = 0; i < (3 * time); ++i )
    {
    };
} /* eof usb_cpu_delay_1us() */


/***********************************************************************************************************************
Function Name   : usb_cpu_delay_xms
Description     : xms Delay timer
Arguments       : uint16_t time         ; Delay time(*1ms)
Return value    : none
***********************************************************************************************************************/
void usb_cpu_delay_xms(uint16_t time)
{
    /* Wait xms (Please change for your MCU) */
    volatile register uint32_t  i;

    /* Wait 1ms */
    for( i = 0; i < (2000 * time); ++i )
    {
    };
        /* When "ICLK=24MHz" is set, this code is waiting for 1ms.
          Please change this code with CPU Clock mode. */
} /* eof usb_cpu_delay_xms() */


/***********************************************************************************************************************
Function Name   : usb_cpu_set_pin_function
Description     : Set Pin Function
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_set_pin_function(void)
{
} /* eof usb_cpu_set_pin_function() */


/***********************************************************************************************************************
Function Name   : usb_cpu_usb_interrupt
Description     : USB interrupt Handler
Arguments       : void
Return value    : void
***********************************************************************************************************************/
void usb_cpu_usb_interrupt(void)
{
    /* Call USB interrupt routine */
#if USB_FUNCSEL_PP == USB_PERI_PP
    usb_pstd_interrupt_handler();
#endif  /* USBC_PERI_PP */

#if USB_FUNCSEL_PP == USB_HOST_PP
    usb_hstd_interrupt_handler();
#endif  /* USBC_HOST_PP */
} /* eof usb_cpu_usb_interrupt() */


/***********************************************************************************************************************
Function Name   : usb_cpu_usb_resume_interrupt
Description     : USB resume interrupt Handler
Arguments       : void
Return value    : void
***********************************************************************************************************************/
void usb_cpu_usb_resume_interrupt(void)
{
    usb_smpl_set_suspend_flag(USB_NO);

#ifdef USB_STOP_MODE_ENABLE
    /* Disable USB0 Resume interrupt(USBR0) */
    ICU.IER[0x0B].BIT.IEN2 = 0;

    /* Priority USBR0 = 0(Disable) */
    ICU.IPR[90].BYTE = 0x00;
#endif /* USB_STOP_MODE_ENABLE */
} /* eof usb_cpu_usb_resume_interrupt() */


/***********************************************************************************************************************
Function Name   : usb_cpu_irq0_interrupt
Description     : IRQ0 interrupt Handler
Arguments       : void
Return value    : void
***********************************************************************************************************************/
void usb_cpu_irq0_interrupt(void)
{
    usb_smpl_set_suspend_flag(USB_NO);
    usb_smpl_set_intkey(USB_YES);
} /* eof usb_cpu_irq0_interrupt() */


/***********************************************************************************************************************
Function Name   : usb_cpu_irq0_interrupt_enable
Description     : Enable IRQ0 interrupt
Arguments       : void
Return value    : void
***********************************************************************************************************************/
void usb_cpu_irq0_interrupt_enable(void)
{
    /* Interrupt enable register */
    ICU.IER[0x08].BIT.IEN0 = 0;         /* Interrupt disable */

    /* P3n port function register */
    MPC.P30PFS.BIT.ISEL = 1;

    /* IRQ control register */
    ICU.IRQCR[0].BIT.IRQMD = 1;         /* Down Edge Set */

    /* Interrupt priority register */
    ICU.IPR[64].BYTE = 0x0B;

    /* Interrupt enable register */
    ICU.IER[0x08].BIT.IEN0 = 1;         /* Interrupt enable */
} /* eof usb_cpu_irq0_interrupt_enable() */


/***********************************************************************************************************************
Function Name   : usb_cpu_suspend_sleep
Description     : MCU Low power mode for USB suspend.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_suspend_sleep(void)
{
    usb_cpu_deep_sleep_mode();
} /* eof usb_cpu_suspend_sleep() */


/***********************************************************************************************************************
Function Name   : usb_cpu_detach_sleep
Description     : MCU Low power mode for USB detach.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_detach_sleep(void)
{
    usb_cpu_soft_stanby_mode();
} /* eof usb_cpu_detach_sleep() */


/***********************************************************************************************************************
Function Name   : usb_cpu_d0fifo_interrupt
Description     : DMA interrupt routine. Send message to PCD/HCD task.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_d0fifo_interrupt(void)
{
    usb_cpu_d0fifo_interrupt_handler();
} /* eof usb_cpu_d0fifo_handler() */

/***********************************************************************************************************************
Function Name   : usb_cpu_deep_sleep_mode
Description     : 
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_deep_sleep_mode(void)
{
#if USB_FUNCSEL_PP == USB_PERI_PP
  #ifdef USB_STOP_MODE_ENABLE
    clrpsw_i();

    /* Protect register */
    SYSTEM.PRCR.WORD = 0xA503;          /* Protect off */

    SYSTEM.MSTPCRC.BIT.DSLPE = 1;

    /* DTC Transfer disable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    DTC.DTCST.BIT.DTCST         = 0;

    /* Standby control register (Software Standby disable)
    b14-b0  Reserved 0
    b15    SSBY     Software standby bit
    */
    SYSTEM.SBYCR.BIT.SSBY = 0;

    /* Enable DTC module(MSTPA28) Stop
    b8-b0   Reserved 0
    b9      MSTPA9   Multifunction timer unit0 stop bit
    b14-10  Reserved 0
    b15     MSTPA15  Compare timer unit0 stop bit
    b16     Reserved 0
    b17     MSTPA17  12bit AD stop bit
    b18     Reserved 0
    b19     MSTPA19  DA stop bit
    b27-20  Reserved 0
    b28     MSTPA28  DTC stop bit
    b31-29  Reserved 0
    */
    SYSTEM.MSTPCRA.BIT.MSTPA28 = 1;

    do
    {
    }
    while(SYSTEM.MSTPCRA.BIT.MSTPA28 != 1);

    /* Goto WAIT */
    wait();

    /* Enable DTC module(MSTPA28)
    b8-b0   Reserved 0
    b9      MSTPA9   Multifunction timer unit0 stop bit
    b14-10  Reserved 0
    b15     MSTPA15  Compare timer unit0 stop bit
    b16     Reserved 0
    b17     MSTPA17  12bit AD stop bit
    b18     Reserved 0
    b19     MSTPA19  DA stop bit
    b27-20  Reserved 0
    b28     MSTPA28  DTC stop bit
    b31-29  Reserved 0
    */
    SYSTEM.MSTPCRA.BIT.MSTPA28 = 0;

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    DTC.DTCST.BIT.DTCST         = 1;
  #endif /* USB_STOP_MODE_ENABLE */
#endif /* USB_FUNCSEL_PP == USB_PERI_PP */
} /* eof usb_cpu_deep_sleep_mode() */

/***********************************************************************************************************************
Function Name   : usb_cpu_soft_stanby_mode
Description     : 
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_soft_stanby_mode(void)
{
#if USB_FUNCSEL_PP == USB_PERI_PP
  #ifdef USB_STOP_MODE_ENABLE
    clrpsw_i();

    /* Protect register */
    SYSTEM.PRCR.WORD = 0xA503;          /* Protect off */

    /* Standby control register (Software Standby Shift)
    b14-b0  Reserved 0
    b15    SSBY     Software standby bit
    */
    SYSTEM.SBYCR.BIT.SSBY = 1;

    /* Disable USB0 Resume interrupt(USBR0) */
    ICU.IER[0x0B].BIT.IEN2 = 1;

    /* Priority USBR0 = 3(Enable) */
    ICU.IPR[90].BYTE = 0x03;
    do
    {
    }
    while( ICU.IPR[90].BYTE != 0x03 );

    /* Goto WAIT */
    wait();
  #endif /* USB_STOP_MODE_ENABLE */
#endif /* USB_FUNCSEL_PP == USB_PERI_PP */
} /* eof usb_cpu_soft_stanby_mode() */


/***********************************************************************************************************************
Function Name   : usb_cpu_DmaintInit
Description     : DMA interrupt Initialize
Arguments       : void
Return value    : void
***********************************************************************************************************************/
void usb_cpu_DmaintInit(void)
{
    /* Enable DTC module(MSTPA28) Stop
    b8-b0   Reserved 0
    b9      MSTPA9   Multifunction timer unit0 stop bit
    b14-10  Reserved 0
    b15     MSTPA15  Compare timer unit0 stop bit
    b16     Reserved 0
    b17     MSTPA17  12bit AD stop bit
    b18     Reserved 0
    b19     MSTPA19  DA stop bit
    b27-20  Reserved 0
    b28     MSTPA28  DTC stop bit
    b31-29  Reserved 0
    */
    SYSTEM.MSTPCRA.BIT.MSTPA28  = 0;

    dtc_vector36 = (uint32_t)&usb_dtcreg;

    /* DTC vector register
    b21-b0 DTCVBR Vector table address
    */
//    DTC.DTCVBR                  = (void *)&dtc_vect_table;
    DTC.DTCVBR = (void *)0x00007C00U;

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    DTC.DTCST.BIT.DTCST         = 1;

    /* DTC address mode register (Full Address Mode)
    b0    SHORT    Short address mode bit
    b7-b1 Reserved 0
    */
    DTC.DTCADMOD.BIT.SHORT      = 0;
} /* eof usb_cpu_DmaintInit() */


/***********************************************************************************************************************
Function Name   : usb_cpu_set_d0fifo_pipeX
Description     : Changes the specified FIFO port by the specified pipe.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_set_d0fifo_pipeX(void)
{
    uint16_t    buffer;

    /* CURPIPE=pipeX */
    USB_MDF_PAT(D0FIFOSEL, (uint16_t)(g_usb_CurrentPipe), (uint16_t)(USB_CURPIPE));
    do
    {
        USB_RD(D0FIFOSEL, buffer);
    }
    while( (buffer & (uint16_t)(USB_CURPIPE)) != (uint16_t)(g_usb_CurrentPipe) );
}   /* eof usb_cstd_set_cfifo_pipeX() */


/***********************************************************************************************************************
Function Name   : usb_cpu_d0fifo_interrupt_process
Description     : Set end of DMA/DTC transfer. Set to restart DMA/DTC trans-
                : fer according to data size of remaining functions to be pro-
                : cessed.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_d0fifo_interrupt_process()
{
    uint16_t pipe;
    uint16_t maxps;
    usb_leng_t  *transfer_count;

    pipe = usb_gcstd_Dma0Pipe;
    maxps = usb_gcstd_Dma0Fifo;
    transfer_count = &g_usb_LibDataCnt[pipe];

    g_usb_CurrentPipe = pipe;

    /* DMA Transfer Request Clear */
    USB_MDF_PAT(D0FIFOSEL, (uint16_t)(0), (uint16_t)(USB_DREQE));

    /* Transfer count > MAXPS */
    if ( *transfer_count > maxps )
    {
        /* DMA Transfer count update */
        *transfer_count %= maxps;
        /* Transfer continue check */
        if( *transfer_count != 0 )
        {
            /* Transfer count != MAXPS * N */
            /* Odd size data check  */
            if( (*transfer_count & 0x0001u) != 0u )
            {
                /* if count == odd */
                USB_MDF_PAT(D0FIFOSEL, (uint16_t)(0), (uint16_t)(USB_MBW));
            }
            /* DMA Transfer size update */
            usb_gcstd_Dma0Size = *transfer_count;
            /* DMA Restart */
            usb_cpu_d0fifo_restart_dma();
            /* DMA Transfer Request Set */
            USB_MDF_PAT(D0FIFOSEL, (uint16_t)(USB_DREQE), (uint16_t)(USB_DREQE));

        }
    }
    else if( *transfer_count == 0 )
    {
        /* More than enough Interrupt */
        return;
    }
    else
    {
        /* Transfer count != MAXPS */
        if ( *transfer_count < maxps )
        {
            /* Transfer count < MAXPS */
            USB_MDF_PAT(D0FIFOCTR, (uint16_t)(USB_BVAL), (uint16_t)(USB_BVAL));
        }
        /* Transfer complete */
        *transfer_count = 0;
    }

    /* Transfer complete check */
    if( *transfer_count == 0 )
    {
        /* Transfer complete */
        usb_cpu_d0fifo_stop_dma();

        /* Enable Empty Interrupt */
        usb_cstd_bemp_enable();
    }
}/* eof usb_cpu_d0fifo_interrupt_process() */

/***********************************************************************************************************************
Function Name   : usb_cpu_buf2fifo_start_dma
Description     : Start transfer using DMA/DTC. If transfer size is 0, write 
                : more data to buffer.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void    usb_cpu_buf2fifo_start_dma()
{
    uint32_t    dist_adr;
    usb_leng_t  size;
    uint32_t    tmp;

    /* 16bit access */
    if ( (usb_gcstd_Dma0Size & 0x0001u) == 0u )
    {
        /* DMA access Buffer to FIFO start */
        dist_adr = (uint32_t)(&USB0.D0FIFO.WORD);
    }
    else
    {
        /* 8bit access */
        /* DMA access Buffer to FIFO start */
        dist_adr = (uint32_t)(&USB0.D0FIFO.BYTE.L);
    }

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    DTC.DTCST.BIT.DTCST = 1;

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    DTC.DTCCR.BIT.RRS = 0;

    /* DTC mode register A (Block Transfer Set)
    b1-b0 Reserved 0
    b3-b2 SM       source address mode bit
    b5-b4 SZ       DTC data transfer size bit
    b7-b6 MD       DTC mode bit
    */
    usb_dtcreg.MRA.bit.MD = 2;

    if( usb_gcstd_Dma0Size >= usb_gcstd_Dma0Fifo )
    {
        tmp                     = (uint32_t)( usb_gcstd_Dma0Size / 2 );

        /* DTC mode register A (Word Size)
        b1-b0 Reserved 0
        b3-b2 SM       source address mode bit
        b5-b4 SZ       DTC data transfer size bit
        b7-b6 MD       DTC mode bit
        */
        usb_dtcreg.MRA.bit.SZ  = 1;
    }
    else
    {
        if( (usb_gcstd_Dma0Size & 0x0001) != 0 )
        {
            /* if count == odd */
            tmp = usb_gcstd_Dma0Size;

            /* DTC mode register A (Byte Size)
            b1-b0 Reserved 0
            b3-b2 SM       source address mode bit
            b5-b4 SZ       DTC data transfer size bit
            b7-b6 MD       DTC mode bit
            */
            usb_dtcreg.MRA.bit.SZ  = 0;
        }
        else
        {
            tmp                     = (uint32_t)( usb_gcstd_Dma0Size / 2 );

            /* DTC mode register A (Word Size)
            b1-b0 Reserved 0
            b3-b2 SM       source address mode bit
            b5-b4 SZ       DTC data transfer size bit
            b7-b6 MD       DTC mode bit
            */
            usb_dtcreg.MRA.bit.SZ  = 1;
        }
    }

    /* DTC mode register A (Source Address Increment)
    b1-b0 Reserved 0
    b3-b2 SM       source address mode bit
    b5-b4 SZ       DTC data transfer size bit
    b7-b6 MD       DTC mode bit
    */
    usb_dtcreg.MRA.bit.SM      = 2;

    /* DTC mode register B (Chain Transfer disable)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_dtcreg.MRB.bit.CHNE        = 0;

    /* DTC mode register B (Select Data Transfer End Interrupt)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_dtcreg.MRB.bit.DISEL   = 0;

    /* DTC mode register B (Destination Side Block Area)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_dtcreg.MRB.bit.DTS     = 0;

    /* DTC mode register B (Destination Address fixed)
    b1-b0 Reserved 0
    b3-b2 DM       Destination address mode bit
    b4    DTS      DTC transfer mode select bit
    b5    DISEL    DTC interrupt select bit
    b6    CHNS     DTC chain transfer select bit
    b7    CHNE     DTC chain transfer enable bit
    */
    usb_dtcreg.MRB.bit.DM      = 0;

    /* DTC source address register (Table address)
    b31-b0 SAR Destination address
    */
    usb_dtcreg.SAR = (uint32_t)(g_usb_LibDataPtr[usb_gcstd_Dma0Pipe]);

    /* DTC source address register (FIFO port address)
    b31-b0 SAR Source address
    */
    usb_dtcreg.DAR             = (uint32_t)(dist_adr);
    size                        = (uint8_t )(tmp);
    size                       += (uint16_t)(tmp << 8);

    /* DTC transfer count registerA
    b15-b0 CRA Transfer count
    */
    usb_dtcreg.CRA             = (uint16_t)(size);

    /* DTC transfer count registerB (Block count)
    b15-b0 CRB Transfer count
    */
    if( g_usb_LibDataCnt[usb_gcstd_Dma0Pipe] > usb_gcstd_Dma0Fifo )
    {
        usb_dtcreg.CRB = (unsigned short)( g_usb_LibDataCnt[usb_gcstd_Dma0Pipe] / usb_gcstd_Dma0Fifo );
    }
    else
    {
        usb_dtcreg.CRB = 1;
    }
    /* DTC address mode register (Full Address Mode)
    b0    SHORT    Short address mode bit
    b7-b1 Reserved 0
    */
    DTC.DTCADMOD.BIT.SHORT      = 0;

    /* DTC control register (Transfer Information Read No Skip)
    b2-b0 Reserved 0
    b3    Reserved 0
    b4    RRS      DTC Transfer Information Read Skip enable bit
    b7-b5 Reserved 0
    */
    DTC.DTCCR.BIT.RRS           = 1;

    /* Priority D0FIFO0=5
    b3-b0 IPR      Interrupt priority
    b7-b4 Reserved 0
    */
    ICU.IPR[36].BYTE          = 0x00;

    /* Interrupt enable register (USB_IP D0FIFO enable(IEN4))
    b0 IEN0 Interrupt enable bit
    b1 IEN1 Interrupt enable bit
    b2 IEN2 Interrupt enable bit
    b3 IEN3 Interrupt enable bit
    b4 IEN4 Interrupt enable bit
    b5 IEN5 Interrupt enable bit
    b6 IEN6 Interrupt enable bit
    b7 IEN7 Interrupt enable bit
    */
    ICU.IER[0x04].BIT.IEN4      = 1;

    /* DTC start enable register (USB_IP D0FIFO transfer)
    b0    DTCE     DTC start enable bit
    b7-b1 Reserved 0
    */
    ICU.DTCER[36].BIT.DTCE      = 1;

    /* Changes the FIFO port by the pipe. */
    usb_cpu_set_d0fifo_pipeX();

    /* Enable Not Ready Interrupt */
    usb_cstd_nrdy_enable();

    /* CPU access Buffer to FIFO start */
    /* Write (MEMORY -> FIFO) : USB register set */
    if( (usb_gcstd_Dma0Size & (uint16_t)0x0001) != 0 )
    {
        /* Change MBW setting */
        USB_MDF_PAT(D0FIFOSEL, (uint16_t)(0), (uint16_t)(USB_MBW));
    }
    else
    {
        /* Change MBW setting */
        USB_MDF_PAT(D0FIFOSEL, (uint16_t)(USB_MBW), (uint16_t)(USB_MBW));
    }

    /* DTC(D0FIFO) interrupt enable */
    /* Priority D0FIFO0=0(Disable)
    b3-b0 IPR      Interrupt priority
    b7-b4 Reserved 0
    */
    ICU.IPR[36].BYTE          = 0x05;

    /* Set DREQ enable */
    USB_MDF_PAT(D0FIFOSEL, (uint16_t)(USB_DREQE), (uint16_t)(USB_DREQE));
}/* eof usb_cpu_buf2fifo_start_dma() */

/***********************************************************************************************************************
Function Name   : usb_cpu_fifo2buf_start_dma
Description     : Start transfer using DMA/DTC. If transfer size is 0, clear DMA. 
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void    usb_cpu_fifo2buf_start_dma()
{
    usb_leng_t  size;
    uint32_t    tmp;
    uint32_t    source_addr;
    uint16_t    trncnt;

    /* Changes the FIFO port by the pipe. */
    usb_cpu_set_d0fifo_pipeX();

    /* Data size check */
    if( usb_gcstd_Dma0Size != 0u )
    {
        /* 16bit access */
        if( (usb_gcstd_Dma0Size & 0x0001u) == 0u )
        {
            /* D0FIFO to Buffer DMA read start */
            source_addr = (uint32_t)(&USB0.D0FIFO.WORD);
        }
        else
        {
            /* 8bit access */
            /* D0FIFO to Buffer DMA read start */
            source_addr = (uint32_t)(&USB0.D0FIFO.BYTE.L);
        }

        /* DTC Transfer enable
        b0    DTCST    DTC module start bit
        b7-b1 Reserved 0
        */
        DTC.DTCST.BIT.DTCST         = 1;

        /* DTC control register (Transfer Information Read No Skip)
        b2-b0 Reserved 0
        b3    Reserved 0
        b4    RRS      DTC Transfer Information Read Skip enable bit
        b7-b5 Reserved 0
        */
        DTC.DTCCR.BIT.RRS           = 0;

        /* DTC mode register A (Block Transfer Set)
        b1-b0 Reserved 0
        b3-b2 SM       source address mode bit
        b5-b4 SZ       DTC data transfer size bit
        b7-b6 MD       DTC mode bit
        */
        usb_dtcreg.MRA.bit.MD      = 2;

        tmp                     = (uint32_t)( usb_gcstd_Dma0Fifo / 2 );

        /* DTC mode register A (Word Size)
        b1-b0 Reserved 0
        b3-b2 SM       source address mode bit
        b5-b4 SZ       DTC data transfer size bit
        b7-b6 MD       DTC mode bit
        */
        usb_dtcreg.MRA.bit.SZ  = 1;

        /* DTC mode register A (Source Address fixed)
        b1-b0 Reserved 0
        b3-b2 SM       source address mode bit
        b5-b4 SZ       DTC data transfer size bit
        b7-b6 MD       DTC mode bit
        */
        usb_dtcreg.MRA.bit.SM      = 0;

        /* DTC mode register B (Chain Transfer disable)
        b1-b0 Reserved 0
        b3-b2 DM       Destination address mode bit
        b4    DTS      DTC transfer mode select bit
        b5    DISEL    DTC interrupt select bit
        b6    CHNS     DTC chain transfer select bit
        b7    CHNE     DTC chain transfer enable bit
        */
        usb_dtcreg.MRB.bit.CHNE        = 0;

        /* DTC mode register B (Select Data Transfer End Interrupt)
        b1-b0 Reserved 0
        b3-b2 DM       Destination address mode bit
        b4    DTS      DTC transfer mode select bit
        b5    DISEL    DTC interrupt select bit
        b6    CHNS     DTC chain transfer select bit
        b7    CHNE     DTC chain transfer enable bit
        */
        usb_dtcreg.MRB.bit.DISEL   = 0;

        /* DTC mode register B (Source Side Block Area)
        b1-b0 Reserved 0
        b3-b2 DM       Destination address mode bit
        b4    DTS      DTC transfer mode select bit
        b5    DISEL    DTC interrupt select bit
        b6    CHNS     DTC chain transfer select bit
        b7    CHNE     DTC chain transfer enable bit
        */
        usb_dtcreg.MRB.bit.DTS     = 1;

        /* DTC mode register B (Destination Address Increment)
        b1-b0 Reserved 0
        b3-b2 DM       Destination address mode bit
        b4    DTS      DTC transfer mode select bit
        b5    DISEL    DTC interrupt select bit
        b6    CHNS     DTC chain transfer select bit
        b7    CHNE     DTC chain transfer enable bit
        */
        usb_dtcreg.MRB.bit.DM      = 2;

        /* DTC source address register (FIFO port address)
        b31-b0 SAR Destination address
        */
        usb_dtcreg.SAR             = source_addr;

        /* DTC source address register (Table address)
        b31-b0 SAR Source address
        */
        usb_dtcreg.DAR = (uint32_t)(g_usb_LibDataPtr[usb_gcstd_Dma0Pipe]);

        size            = (uint8_t )(tmp);
        size            += (uint16_t)(tmp << 8);

        /* DTC transfer count registerA
        b15-b0 CRA Transfer count
        */
        usb_dtcreg.CRA             = (uint16_t)(size);

        /* DTC transfer count registerB (Block count)
        b15-b0 CRB Transfer count
        */
        usb_dtcreg.CRB = (unsigned short)((g_usb_LibDataCnt[usb_gcstd_Dma0Pipe] -1) / usb_gcstd_Dma0Fifo) +1;

        /* DTC address mode register (Full Address Mode)
        b0    SHORT    Short address mode bit
        b7-b1 Reserved 0
        */
        DTC.DTCADMOD.BIT.SHORT      = 0;

        /* DTC control register (Transfer Information Read No Skip)
        b2-b0 Reserved 0
        b3    Reserved 0
        b4    RRS      DTC Transfer Information Read Skip enable bit
        b7-b5 Reserved 0
        */
        DTC.DTCCR.BIT.RRS           = 1;

        /* Priority D0FIFO0=5
        b3-b0 IPR      Interrupt priority
        b7-b4 Reserved 0
        */
        ICU.IPR[36].BYTE          = 0x00;

        /* Interrupt enable register (USB_IP D0FIFO enable(IEN4))
        b0 IEN0 Interrupt enable bit
        b1 IEN1 Interrupt enable bit
        b2 IEN2 Interrupt enable bit
        b3 IEN3 Interrupt enable bit
        b4 IEN4 Interrupt enable bit
        b5 IEN5 Interrupt enable bit
        b6 IEN6 Interrupt enable bit
        b7 IEN7 Interrupt enable bit
        */
        ICU.IER[0x04].BIT.IEN4      = 1;

        /* DTC start enable register (USB_IP D0FIFO transfer)
        b0    DTCE     DTC start enable bit
        b7-b1 Reserved 0
        */
        ICU.DTCER[36].BIT.DTCE      = 1;

        /* Packet Size check */
        if( g_usb_LibDataCnt[usb_gcstd_Dma0Pipe] != (uint32_t)0u )
        {
            /* Data length check */
            if( (g_usb_LibDataCnt[usb_gcstd_Dma0Pipe] % usb_gcstd_Dma0Fifo) == (uint32_t)0u )
            {
                /* Set Transaction counter */
                trncnt = (uint16_t)(g_usb_LibDataCnt[usb_gcstd_Dma0Pipe] / usb_gcstd_Dma0Fifo);
            }
            else
            {
                /* Set Transaction counter */
                trncnt = (uint16_t)((g_usb_LibDataCnt[usb_gcstd_Dma0Pipe] / usb_gcstd_Dma0Fifo) + (uint32_t)1u);
            }
        }

        switch( g_usb_CurrentPipe )
        {
            case USB_PIPE1:             /* Pipe1 transaction counter register set & count enable  */
                USB_SET_PAT(PIPE1TRE, USB_TRCLR);
                USB_WRW(PIPE1TRN, trncnt);
                USB_SET_PAT(PIPE1TRE, USB_TRENB);
            break;
            case USB_PIPE2:             /* Pipe2 transaction counter register set & count enable  */
                USB_SET_PAT(PIPE2TRE, USB_TRCLR);
                USB_WRW(PIPE2TRN, trncnt);
                USB_SET_PAT(PIPE2TRE, USB_TRENB);
            break;
            case USB_PIPE3:             /* Pipe3 transaction counter register set & count enable  */
                USB_SET_PAT(PIPE3TRE, USB_TRCLR);
                USB_WRW(PIPE3TRN, trncnt);
                USB_SET_PAT(PIPE3TRE, USB_TRENB);
            break;
            case USB_PIPE4:             /* Pipe4 transaction counter register set & count enable  */
                USB_SET_PAT(PIPE4TRE, USB_TRCLR);
                USB_WRW(PIPE4TRN, trncnt);
                USB_SET_PAT(PIPE4TRE, USB_TRENB);
            break;
            case USB_PIPE5:             /* Pipe5 transaction counter register set & count enable  */
                USB_SET_PAT(PIPE5TRE, USB_TRCLR);
                USB_WRW(PIPE5TRN, trncnt);
                USB_SET_PAT(PIPE5TRE, USB_TRENB);
            break;
            default:
                /* no processing */
            break;
        }

        /* Read (FIFO -> MEMORY) : USB register set */
        /* DMA buffer clear mode & MBW set */
        USB_MDF_PAT(D0FIFOSEL, (uint16_t)(USB_MBW), (uint16_t)(USB_MBW));

        USB_MDF_PAT(D0FIFOSEL, (uint16_t)(0), (uint16_t)(USB_DCLRM));

        /* Set DREQ enable */
        USB_MDF_PAT(D0FIFOSEL, (uint16_t)(USB_DREQE), (uint16_t)(USB_DREQE));
    }
    else
    {
        /* DMA buffer clear mode set */
        USB_MDF_PAT(D0FIFOSEL, (uint16_t)(USB_DCLRM), (uint16_t)(USB_DCLRM));
    }

    /* Enable Ready Interrupt */
    usb_cstd_brdy_enable();
    /* Enable Not Ready Interrupt */
    usb_cstd_nrdy_enable();
    /* Set BUF */
    usb_cstd_reg_set_pipexctr(USB_PID_BUF);
} /* eof usb_cpu_fifo2buf_start_dma() */


/***********************************************************************************************************************
Function Name   : usb_cpu_d0fifo_stop_dma
Description     : DMA stop
Arguments       : none 
Return value    : none
***********************************************************************************************************************/
void usb_cpu_d0fifo_stop_dma()
{
    /* Interrupt request register
    b0    IR       Interrupt status flag
    b7-b1 Reserved 0
    */
    ICU.IR[36].BIT.IR           = 0;

    /* Interrupt disable register (USB_IP D0FIFO enable(IEN4))
    b0 IEN0 Interrupt enable bit
    b1 IEN1 Interrupt enable bit
    b2 IEN2 Interrupt enable bit
    b3 IEN3 Interrupt enable bit
    b4 IEN4 Interrupt enable bit
    b5 IEN5 Interrupt enable bit
    b6 IEN6 Interrupt enable bit
    b7 IEN7 Interrupt enable bit
    */
    ICU.IER[0x04].BIT.IEN4      = 0;

    /* Priority D0FIFO0=0
    b3-b0 IPR      Interrupt priority
    b7-b4 Reserved 0
    */
    ICU.IPR[36].BYTE          = 0x00;

    /* DTC start disable register (USB_IP D0FIFO transfer)
    b0    DTCE     DTC start enable bit
    b7-b1 Reserved 0
    */
    ICU.DTCER[36].BIT.DTCE      = 0;
} /* eof usb_cpu_d0fifo_stop_dma() */


/***********************************************************************************************************************
Function Name   : usb_cpu_d0fifo_stop_usb
Description     : Setup external variables used for USB data transfer; to reg-
                : ister if you want to stop the transfer of DMA/DTC.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_d0fifo_stop_usb()
{
    uint16_t    pipe = usb_gcstd_Dma0Pipe;
    usb_leng_t  transfer_size = usb_gcstd_Dma0Size;
    usb_leng_t  *request_size = &g_usb_LibDataCnt[pipe];
    uint8_t     *tran_data_ptr = (uint8_t *)&g_usb_LibDataPtr[pipe];

    g_usb_CurrentPipe = pipe;

    USB_MDF_PAT(D0FIFOSEL, (uint16_t)(0), (uint16_t)(USB_DREQE));

    /* Direction check */
    if( usb_gcstd_Dma0Dir == USB_BUF2FIFO )
    {
        /* Buffer to FIFO */
        if( *request_size < transfer_size )
        {
            /* >yes then set BVAL */
            *tran_data_ptr += *request_size;
            *request_size = (usb_leng_t)0u;
            /* Disable Ready Interrupt */
            usb_cstd_brdy_disable();
            /* Set BVAL */
            USB_MDF_PAT(D0FIFOCTR, (uint16_t)(USB_BVAL), (uint16_t)(USB_BVAL));
        }
        else
        {
            *tran_data_ptr += transfer_size;
            /* Set data count to remain */
            *request_size -= transfer_size;
        }
    }
    else
    {
        /* FIFO to Buffer */
        *tran_data_ptr += transfer_size;
        /* Set data count to remain */
        if( *request_size < transfer_size )
        {
            *request_size = transfer_size - *request_size;
        }
        else
        {
            *request_size -= transfer_size;
        }
    }
} /* eof usb_cpu_d0fifo_stop_usb() */


/***********************************************************************************************************************
Function Name   : usb_cpu_d0fifo_restart_dma
Description     : DMA Restart
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_d0fifo_restart_dma()
{
    usb_leng_t  size;
    uint32_t    tmp;

    /* Check direction */
    if( usb_gcstd_Dma0Dir == USB_BUF2FIFO )
    {
        if( usb_gcstd_Dma0Size >= usb_gcstd_Dma0Fifo )
        {
            tmp = (uint32_t)( usb_gcstd_Dma0Fifo / 2 );

            /* DTC mode register A (Word Size)
            b1-b0 Reserved 0
            b3-b2 SM       source address mode bit
            b5-b4 SZ       DTC data transfer size bit
            b7-b6 MD       DTC mode bit
            */
            usb_dtcreg.MRA.bit.SZ  = 1;
        }
        else
        {
            if( (usb_gcstd_Dma0Size & 0x0001u) != 0u )
            {
                /* if count == odd */
                tmp = usb_gcstd_Dma0Size;

                /* DTC mode register A (Byte Size)
                b1-b0 Reserved 0
                b3-b2 SM       source address mode bit
                b5-b4 SZ       DTC data transfer size bit
                b7-b6 MD       DTC mode bit
                */
                usb_dtcreg.MRA.bit.SZ  = 0;
            }
            else
            {
                tmp = (uint32_t)( usb_gcstd_Dma0Size / 2 );

                /* DTC mode register A (Word Size)
                b1-b0 Reserved 0
                b3-b2 SM       source address mode bit
                b5-b4 SZ       DTC data transfer size bit
                b7-b6 MD       DTC mode bit
                */
                usb_dtcreg.MRA.bit.SZ  = 1;
            }
        }
    }else{
        /* DTC mode register A (Word Size)
        b1-b0 Reserved 0
        b3-b2 SM       source address mode bit
        b5-b4 SZ       DTC data transfer size bit
        b7-b6 MD       DTC mode bit
        */
        usb_dtcreg.MRA.bit.SZ  = 1;

        /* DTC transfer count registerA
        b15-b0 CRA Transfer count
        */
        tmp = usb_gcstd_Dma0Fifo / 2;
    }
    size                        = (uint8_t )(tmp);
    size                       += (uint16_t)(tmp << 8);

    /* DTC transfer count registerA
    b15-b0 CRA Transfer count
    */
    usb_dtcreg.CRA             = (uint16_t)(size);

    /* DTC transfer count registerB (Block count)
    b15-b0 CRB Transfer count
    */
    usb_dtcreg.CRB             = (uint16_t)(1);

    /* DTC Transfer enable
    b0    DTCST    DTC module start bit
    b7-b1 Reserved 0
    */
    DTC.DTCST.BIT.DTCST         = 1;

    /* DTC start enable register (USB_IP D0FIFO transfer)
    b0    DTCE     DTC start enable bit
    b7-b1 Reserved 0
    */
    ICU.DTCER[36].BIT.DTCE      = 1;
} /* eof usb_cpu_d0fifo_restart_dma() */


/***********************************************************************************************************************
Function Name   : usb_cpu_get_dtc_block_count
Description     : 
Arguments       : 
Return value    : 
***********************************************************************************************************************/
uint16_t usb_cpu_get_dtc_block_count()
{
    return usb_dtcreg.CRB;
}   /* eof usb_cpu_get_dtc_block_count() */


/***********************************************************************************************************************
Function Name   : usb_cpu_d0fifo_interrupt_handler
Description     : DMA interrupt routine. Send message to PCD/HCD task.
Arguments       : none
Return value    : none
***********************************************************************************************************************/
void usb_cpu_d0fifo_interrupt_handler(void)
{
    usb_intinfo_t   *ptr;

    /* Call USB interrupt routine */
#if USB_FUNCSEL_PP == USB_PERI_PP
    ptr = &g_usb_LibIntMessageD0fifo;
    /* Peripheral Function */
    ptr->msginfo = USB_DO_D0FIFO_INTERRUPT;

    if( R_USB_ISND_MSG(USB_PCD_MBX, (usb_msg_t*)ptr) != USB_E_OK )
    {
        /* Because it is an error that must not occur in the system, it stops.  */
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_HWR | USB_DEBUG_HOOK_CODE1);
    }
#endif  /* USBC_PERI_PP */

#if USB_FUNCSEL_PP == USB_HOST_PP
    ptr = &g_usb_LibIntMessageD0fifo;
    ptr->msginfo = USB_DO_D0FIFO_INTERRUPT;

    if( R_USB_ISND_MSG(USB_HCD_MBX, (usb_msg_t*)ptr) != USB_E_OK )
    {
        /* Because it is an error that must not occur in the system, it stops.  */
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_HWR | USB_DEBUG_HOOK_CODE2);
    }
#endif  /* USBC_HOST_PP */
} /* eof usb_cpu_d0fifo_interrupt_handler() */

/***********************************************************************************************************************
Function Name   : usb_cpu_get_transfer_mode
Description     : Get Pipe transfer mode.
Arguments       : none
Return value    : Pipe Transfer mode.(USB_CUSE/USB_D0DMA)
***********************************************************************************************************************/
uint16_t usb_cpu_get_transfer_mode(void)
{
    uint16_t    ret = USB_CUSE;     /* CPU transfer */

    if( (DTC_USE_PIPE_NUM == g_usb_CurrentPipe) &&  ( USB_PIPE0 != g_usb_CurrentPipe ) )
    {
        ret = USB_D0DMA;    /* Pipe1 to Pipe5 DTC use transfer */
    }

    return ret;
} /* eof usb_cpu_get_transfer_mode() */

#endif	// USB_SERIAL_USE

/***********************************************************************************************************************
End Of File
***********************************************************************************************************************/