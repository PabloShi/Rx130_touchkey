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
* File Name    : r_cg_vect.h
* Version      : Code Generator for RX113 V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F51136AxFP
* Tool-Chain   : CCRX
* Description  : This file contains definition of vector.
* Creation Date: 2015/03/17
***********************************************************************************************************************/
#ifndef _VECT_H
#define _VECT_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Undefined */
#pragma interrupt (r_undefined_exception)
void r_undefined_exception(void);

/* Reserved */
#pragma interrupt (r_reserved_exception)
void r_reserved_exception(void);

/* NMI */
#pragma interrupt (r_nmi_exception)
void r_nmi_exception(void);

/* BRK */
#pragma interrupt (r_brk_exception(vect=0))
void r_brk_exception(void);

/* BSC BUSERR */
#pragma interrupt (Excep_BSC_BUSERR(vect=16))
void Excep_BSC_BUSERR(void);

/* ICU SWINT */
#pragma interrupt (Excep_ICU_SWINT(vect=27))
void Excep_ICU_SWINT(void);

/* CMT0 CMI0 */
//#pragma interrupt (Excep_CMT0_CMI0(vect=28))
//void Excep_CMT0_CMI0(void);

/* CMT1 CMI1 */
#pragma interrupt (Excep_CMT1_CMI1(vect=29))
void Excep_CMT1_CMI1(void);

/* CMT2 CMI2 */
#pragma interrupt (Excep_CMT2_CMI2(vect=30))
void Excep_CMT2_CMI2(void);

/* CMT3 CMI3 */
#pragma interrupt (Excep_CMT3_CMI3(vect=31))
void Excep_CMT3_CMI3(void);

/* CAC FERRF */
#pragma interrupt (Excep_CAC_FERRF(vect=32))
void Excep_CAC_FERRF(void);

/* CAC MENDF */
#pragma interrupt (Excep_CAC_MENDF(vect=33))
void Excep_CAC_MENDF(void);

/* CAC OVFF */
#pragma interrupt (Excep_CAC_OVFF(vect=34))
void Excep_CAC_OVFF(void);

/* USB0 D0FIFO0 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_USB0_D0FIFO0(vect=36))
void Excep_USB0_D0FIFO0(void);
#endif	// USB_SERIAL_USE

/* USB0 D1FIFO0 */
#pragma interrupt (Excep_USB0_D1FIFO0(vect=37))
void Excep_USB0_D1FIFO0(void);

/* USB0 USBI0 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_USB0_USBI0(vect=38))
void Excep_USB0_USBI0(void);
#endif	// USB_SERIAL_USE

/* RSPI0 SPEI0 */
#pragma interrupt (Excep_RSPI0_SPEI0(vect=44))
void Excep_RSPI0_SPEI0(void);

/* RSPI0 SPRI0 */
#pragma interrupt (Excep_RSPI0_SPRI0(vect=45))
void Excep_RSPI0_SPRI0(void);

/* RSPI0 SPTI0 */
#pragma interrupt (Excep_RSPI0_SPTI0(vect=46))
void Excep_RSPI0_SPTI0(void);

/* RSPI0 SPII0 */
#pragma interrupt (Excep_RSPI0_SPII0(vect=47))
void Excep_RSPI0_SPII0(void);

/* DOC DOPCF */
#pragma interrupt (Excep_DOC_DOPCF(vect=57))
void Excep_DOC_DOPCF(void);

/* CMPB CMPB0 */
#pragma interrupt (Excep_CMPB_CMPB0(vect=58))
void Excep_CMPB_CMPB0(void);

/* CMPB CMPB1 */
#pragma interrupt (Excep_CMPB_CMPB1(vect=59))
void Excep_CMPB_CMPB1(void);

/* CTSU CTSUWR */
#pragma interrupt (Excep_CTSU_CTSUWR(vect=60))
void Excep_CTSU_CTSUWR(void);

/* CTSU CTSURD */
#pragma interrupt (Excep_CTSU_CTSURD(vect=61))
void Excep_CTSU_CTSURD(void);

/* CTSU CTSUFN */
#pragma interrupt (Excep_CTSU_CTSUFN(vect=62))
void Excep_CTSU_CTSUFN(void);

/* RTC CUP */
#pragma interrupt (Excep_RTC_CUP(vect=63))
void Excep_RTC_CUP(void);

/* ICU IRQ0 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_ICU_IRQ0(vect=64))
void Excep_ICU_IRQ0(void);
#endif	// USB_SERIAL_USE

/* ICU IRQ1 */
#pragma interrupt (Excep_ICU_IRQ1(vect=65))
void Excep_ICU_IRQ1(void);

/* ICU IRQ2 */
#pragma interrupt (Excep_ICU_IRQ2(vect=66))
void Excep_ICU_IRQ2(void);

/* ICU IRQ3 */
#pragma interrupt (Excep_ICU_IRQ3(vect=67))
void Excep_ICU_IRQ3(void);

/* ICU IRQ4 */
#pragma interrupt (Excep_ICU_IRQ4(vect=68))
void Excep_ICU_IRQ4(void);

/* ICU IRQ5 */
#pragma interrupt (Excep_ICU_IRQ5(vect=69))
void Excep_ICU_IRQ5(void);

/* ICU IRQ6 */
#pragma interrupt (Excep_ICU_IRQ6(vect=70))
void Excep_ICU_IRQ6(void);

/* ICU IRQ7 */
#pragma interrupt (Excep_ICU_IRQ7(vect=71))
void Excep_ICU_IRQ7(void);

/* LVD LVD1 */
#pragma interrupt (Excep_LVD_LVD1(vect=88))
void Excep_LVD_LVD1(void);

/* LVD LVD2 */
#pragma interrupt (Excep_LVD_LVD2(vect=89))
void Excep_LVD_LVD2(void);

/* USB0 USBR0 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_USB0_USBR0(vect=90))
void Excep_USB0_USBR0(void);
#endif	// USB_SERIAL_USE

/* RTC ALM */
#pragma interrupt (Excep_RTC_ALM(vect=92))
void Excep_RTC_ALM(void);

/* RTC PRD */
#pragma interrupt (Excep_RTC_PRD(vect=93))
void Excep_RTC_PRD(void);

/* S12AD S12ADI0 */
#pragma interrupt (Excep_S12AD_S12ADI0(vect=102))
void Excep_S12AD_S12ADI0(void);

/* S12AD GBADI */
#pragma interrupt (Excep_S12AD_GBADI(vect=103))
void Excep_S12AD_GBADI(void);

/* ELC ELSR18I */
#pragma interrupt (Excep_ELC_ELSR18I(vect=106))
void Excep_ELC_ELSR18I(void);

/* SSI0 SSIF0 */
#pragma interrupt (Excep_SSI0_SSIF0(vect=108))
void Excep_SSI0_SSIF0(void);

/* SSI0 SSIRXI0 */
#pragma interrupt (Excep_SSI0_SSIRXI0(vect=109))
void Excep_SSI0_SSIRXI0(void);

/* SSI0 SSITXI0 */
#pragma interrupt (Excep_SSI0_SSITXI0(vect=110))
void Excep_SSI0_SSITXI0(void);

/* MTU0 TGIA0 */
#pragma interrupt (Excep_MTU0_TGIA0(vect=114))
void Excep_MTU0_TGIA0(void);

/* MTU0 TGIB0 */
#pragma interrupt (Excep_MTU0_TGIB0(vect=115))
void Excep_MTU0_TGIB0(void);

/* MTU0 TGIC0 */
#pragma interrupt (Excep_MTU0_TGIC0(vect=116))
void Excep_MTU0_TGIC0(void);

/* MTU0 TGID0 */
#pragma interrupt (Excep_MTU0_TGID0(vect=117))
void Excep_MTU0_TGID0(void);

/* MTU0 TCIV0 */
#pragma interrupt (Excep_MTU0_TCIV0(vect=118))
void Excep_MTU0_TCIV0(void);

/* MTU0 TGIE0 */
#pragma interrupt (Excep_MTU0_TGIE0(vect=119))
void Excep_MTU0_TGIE0(void);

/* MTU0 TGIF0 */
#pragma interrupt (Excep_MTU0_TGIF0(vect=120))
void Excep_MTU0_TGIF0(void);

/* MTU1 TGIA1 */
#pragma interrupt (Excep_MTU1_TGIA1(vect=121))
void Excep_MTU1_TGIA1(void);

/* MTU1 TGIB1 */
#pragma interrupt (Excep_MTU1_TGIB1(vect=122))
void Excep_MTU1_TGIB1(void);

/* MTU1 TCIV1 */
#pragma interrupt (Excep_MTU1_TCIV1(vect=123))
void Excep_MTU1_TCIV1(void);

/* MTU1 TCIU1 */
#pragma interrupt (Excep_MTU1_TCIU1(vect=124))
void Excep_MTU1_TCIU1(void);

/* MTU2 TGIA2 */
#pragma interrupt (Excep_MTU2_TGIA2(vect=125))
void Excep_MTU2_TGIA2(void);

/* MTU2 TGIB2 */
#pragma interrupt (Excep_MTU2_TGIB2(vect=126))
void Excep_MTU2_TGIB2(void);

/* MTU2 TCIV2 */
#pragma interrupt (Excep_MTU2_TCIV2(vect=127))
void Excep_MTU2_TCIV2(void);

/* MTU2 TCIU2 */
#pragma interrupt (Excep_MTU2_TCIU2(vect=128))
void Excep_MTU2_TCIU2(void);

/* MTU3 TGIA3 */
#pragma interrupt (Excep_MTU3_TGIA3(vect=129))
void Excep_MTU3_TGIA3(void);

/* MTU3 TGIB3 */
#pragma interrupt (Excep_MTU3_TGIB3(vect=130))
void Excep_MTU3_TGIB3(void);

/* MTU3 TGIC3 */
#pragma interrupt (Excep_MTU3_TGIC3(vect=131))
void Excep_MTU3_TGIC3(void);

/* MTU3 TGID3 */
#pragma interrupt (Excep_MTU3_TGID3(vect=132))
void Excep_MTU3_TGID3(void);

/* MTU3 TCIV3 */
#pragma interrupt (Excep_MTU3_TCIV3(vect=133))
void Excep_MTU3_TCIV3(void);

/* MTU4 TGIA4 */
#pragma interrupt (Excep_MTU4_TGIA4(vect=134))
void Excep_MTU4_TGIA4(void);

/* MTU4 TGIB4 */
#pragma interrupt (Excep_MTU4_TGIB4(vect=135))
void Excep_MTU4_TGIB4(void);

/* MTU4 TGIC4 */
#pragma interrupt (Excep_MTU4_TGIC4(vect=136))
void Excep_MTU4_TGIC4(void);

/* MTU4 TGID4 */
#pragma interrupt (Excep_MTU4_TGID4(vect=137))
void Excep_MTU4_TGID4(void);

/* MTU4 TCIV4 */
#pragma interrupt (Excep_MTU4_TCIV4(vect=138))
void Excep_MTU4_TCIV4(void);

/* MTU5 TGIU5 */
#pragma interrupt (Excep_MTU5_TGIU5(vect=139))
void Excep_MTU5_TGIU5(void);

/* MTU5 TGIV5 */
#pragma interrupt (Excep_MTU5_TGIV5(vect=140))
void Excep_MTU5_TGIV5(void);

/* MTU5 TGIW5 */
#pragma interrupt (Excep_MTU5_TGIW5(vect=141))
void Excep_MTU5_TGIW5(void);

/* POE OEI1 */
#pragma interrupt (Excep_POE_OEI1(vect=170))
void Excep_POE_OEI1(void);

/* POE OEI2 */
#pragma interrupt (Excep_POE_OEI2(vect=171))
void Excep_POE_OEI2(void);

/* TMR0 CMIA0 */
#pragma interrupt (Excep_TMR0_CMIA0(vect=174))
void Excep_TMR0_CMIA0(void);

/* TMR0 CMIB0 */
#pragma interrupt (Excep_TMR0_CMIB0(vect=175))
void Excep_TMR0_CMIB0(void);

/* TMR0 OVI0 */
#pragma interrupt (Excep_TMR0_OVI0(vect=176))
void Excep_TMR0_OVI0(void);

/* TMR1 CMIA1 */
#pragma interrupt (Excep_TMR1_CMIA1(vect=177))
void Excep_TMR1_CMIA1(void);

/* TMR1 CMIB1 */
#pragma interrupt (Excep_TMR1_CMIB1(vect=178))
void Excep_TMR1_CMIB1(void);

/* TMR1 OVI1 */
#pragma interrupt (Excep_TMR1_OVI1(vect=179))
void Excep_TMR1_OVI1(void);

/* TMR2 CMIA2 */
#pragma interrupt (Excep_TMR2_CMIA2(vect=180))
void Excep_TMR2_CMIA2(void);

/* TMR2 CMIB2 */
#pragma interrupt (Excep_TMR2_CMIB2(vect=181))
void Excep_TMR2_CMIB2(void);

/* TMR2 OVI2 */
#pragma interrupt (Excep_TMR2_OVI2(vect=182))
void Excep_TMR2_OVI2(void);

/* TMR3 CMIA3 */
#pragma interrupt (Excep_TMR3_CMIA3(vect=183))
void Excep_TMR3_CMIA3(void);

/* TMR3 CMIB3 */
#pragma interrupt (Excep_TMR3_CMIB3(vect=184))
void Excep_TMR3_CMIB3(void);

/* TMR3 OVI3 */
#pragma interrupt (Excep_TMR3_OVI3(vect=185))
void Excep_TMR3_OVI3(void);

/* SCI2 ERI2 */
#pragma interrupt (Excep_SCI2_ERI2(vect=186))
void Excep_SCI2_ERI2(void);

/* SCI2 RXI2 */
#pragma interrupt (Excep_SCI2_RXI2(vect=187))
void Excep_SCI2_RXI2(void);

/* SCI2 TXI2 */
#pragma interrupt (Excep_SCI2_TXI2(vect=188))
void Excep_SCI2_TXI2(void);

/* SCI2 TEI2 */
#pragma interrupt (Excep_SCI2_TEI2(vect=189))
void Excep_SCI2_TEI2(void);

/* SCI0 ERI0 */
#pragma interrupt (Excep_SCI0_ERI0(vect=214))
void Excep_SCI0_ERI0(void);

/* SCI0 RXI0 */
#pragma interrupt (Excep_SCI0_RXI0(vect=215))
void Excep_SCI0_RXI0(void);

/* SCI0 TXI0 */
#pragma interrupt (Excep_SCI0_TXI0(vect=216))
void Excep_SCI0_TXI0(void);

/* SCI0 TEI0 */
#pragma interrupt (Excep_SCI0_TEI0(vect=217))
void Excep_SCI0_TEI0(void);

/* SCI1 ERI1 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI1_ERI1(vect=218))
void Excep_SCI1_ERI1(void);
#endif	// USB_SERIAL_USE

/* SCI1 RXI1 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI1_RXI1(vect=219))
void Excep_SCI1_RXI1(void);
#endif	// USB_SERIAL_USE

/* SCI1 TXI1 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI1_TXI1(vect=220))
void Excep_SCI1_TXI1(void);
#endif	// USB_SERIAL_USE

/* SCI1 TEI1 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI1_TEI1(vect=221))
void Excep_SCI1_TEI1(void);
#endif	// USB_SERIAL_USE

/* SCI5 ERI5 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI5_ERI5(vect=222))
void Excep_SCI5_ERI5(void);
#endif	// USB_SERIAL_USE

/* SCI5 RXI5 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI5_RXI5(vect=223))
void Excep_SCI5_RXI5(void);
#endif	// USB_SERIAL_USE

/* SCI5 TXI5 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI5_TXI5(vect=224))
void Excep_SCI5_TXI5(void);
#endif	// USB_SERIAL_USE

/* SCI5 TEI5 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI5_TEI5(vect=225))
void Excep_SCI5_TEI5(void);
#endif	// USB_SERIAL_USE

/* SCI6 ERI6 */
#pragma interrupt (Excep_SCI6_ERI6(vect=226))
void Excep_SCI6_ERI6(void);

/* SCI6 RXI6 */
#pragma interrupt (Excep_SCI6_RXI6(vect=227))
void Excep_SCI6_RXI6(void);

/* SCI6 TXI6 */
#pragma interrupt (Excep_SCI6_TXI6(vect=228))
void Excep_SCI6_TXI6(void);

/* SCI6 TEI6 */
#pragma interrupt (Excep_SCI6_TEI6(vect=229))
void Excep_SCI6_TEI6(void);

/* SCI8 ERI8 */
#pragma interrupt (Excep_SCI8_ERI8(vect=230))
void Excep_SCI8_ERI8(void);

/* SCI8 RXI8 */
#pragma interrupt (Excep_SCI8_RXI8(vect=231))
void Excep_SCI8_RXI8(void);

/* SCI8 TXI8 */
#pragma interrupt (Excep_SCI8_TXI8(vect=232))
void Excep_SCI8_TXI8(void);

/* SCI8 TEI8 */
#pragma interrupt (Excep_SCI8_TEI8(vect=233))
void Excep_SCI8_TEI8(void);

/* SCI9 ERI9 */
#pragma interrupt (Excep_SCI9_ERI9(vect=234))
void Excep_SCI9_ERI9(void);

/* SCI9 RXI9 */
#pragma interrupt (Excep_SCI9_RXI9(vect=235))
void Excep_SCI9_RXI9(void);

/* SCI9 TXI9 */
#pragma interrupt (Excep_SCI9_TXI9(vect=236))
void Excep_SCI9_TXI9(void);

/* SCI9 TEI9 */
#pragma interrupt (Excep_SCI9_TEI9(vect=237))
void Excep_SCI9_TEI9(void);

/* SCI12 ERI12 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI12_ERI12(vect=238))
void Excep_SCI12_ERI12(void);
#endif	// USB_SERIAL_USE

/* SCI12 RXI12 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI12_RXI12(vect=239))
void Excep_SCI12_RXI12(void);
#endif	// USB_SERIAL_USE

/* SCI12 TXI12 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI12_TXI12(vect=240))
void Excep_SCI12_TXI12(void);
#endif	//USB_SERIAL_USE

/* SCI12 TEI12 */
#ifndef	USB_SERIAL_USE
#pragma interrupt (Excep_SCI12_TEI12(vect=241))
void Excep_SCI12_TEI12(void);
#endif	// USB_SERIAL_USE


/* SCI12 SCIX0 */
#pragma interrupt (Excep_SCI12_SCIX0(vect=242))
void Excep_SCI12_SCIX0(void);

/* SCI12 SCIX1 */
#pragma interrupt (Excep_SCI12_SCIX1(vect=243))
void Excep_SCI12_SCIX1(void);

/* SCI12 SCIX2 */
#pragma interrupt (Excep_SCI12_SCIX2(vect=244))
void Excep_SCI12_SCIX2(void);

/* SCI12 SCIX3 */
#pragma interrupt (Excep_SCI12_SCIX3(vect=245))
void Excep_SCI12_SCIX3(void);

/* RIIC0 EEI0 */
#pragma interrupt (Excep_RIIC0_EEI0(vect=246))
void Excep_RIIC0_EEI0(void);

/* RIIC0 RXI0 */
#pragma interrupt (Excep_RIIC0_RXI0(vect=247))
void Excep_RIIC0_RXI0(void);

/* RIIC0 TXI0 */
#pragma interrupt (Excep_RIIC0_TXI0(vect=248))
void Excep_RIIC0_TXI0(void);

/* RIIC0 TEI0 */
#pragma interrupt (Excep_RIIC0_TEI0(vect=249))
void Excep_RIIC0_TEI0(void);

/*;<<VECTOR DATA START (POWER ON RESET)>> */
/*;Power On Reset PC */
extern void PowerON_Reset(void);
/*;<<VECTOR DATA END (POWER ON RESET)>> */

#endif