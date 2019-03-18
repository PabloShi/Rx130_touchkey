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
* File Name    : r_cg_cgc.h
* Version      : Code Generator for RX113 V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F51136AxFP
* Tool-Chain   : CCRX
* Description  : This file implements device driver for CGC module.
* Creation Date: 2015/02/26
***********************************************************************************************************************/
#ifndef CGC_H
#define CGC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    System Clock Control Register (SCKCR)
*/
/* Peripheral Module Clock D (PCLKD) */
#define _00000000_CGC_PCLKD_DIV_1           (0x00000000UL) /* x1 */
#define _00000001_CGC_PCLKD_DIV_2           (0x00000001UL) /* x1/2 */
#define _00000002_CGC_PCLKD_DIV_4           (0x00000002UL) /* x1/4 */
#define _00000003_CGC_PCLKD_DIV_8           (0x00000003UL) /* x1/8 */
#define _00000004_CGC_PCLKD_DIV_16          (0x00000004UL) /* x1/16 */
#define _00000005_CGC_PCLKD_DIV_32          (0x00000005UL) /* x1/32 */
#define _00000006_CGC_PCLKD_DIV_64          (0x00000006UL) /* x1/64 */
/* Peripheral Module Clock B (PCLKB) */
#define _00000000_CGC_PCLKB_DIV_1           (0x00000000UL) /* x1 */
#define _00000100_CGC_PCLKB_DIV_2           (0x00000100UL) /* x1/2 */
#define _00000200_CGC_PCLKB_DIV_4           (0x00000200UL) /* x1/4 */
#define _00000300_CGC_PCLKB_DIV_8           (0x00000300UL) /* x1/8 */
#define _00000400_CGC_PCLKB_DIV_16          (0x00000400UL) /* x1/16 */
#define _00000500_CGC_PCLKB_DIV_32          (0x00000500UL) /* x1/32 */
#define _00000600_CGC_PCLKB_DIV_64          (0x00000600UL) /* x1/64 */
/* System Clock (ICLK) */
#define _00000000_CGC_ICLK_DIV_1            (0x00000000UL) /* x1 */
#define _01000000_CGC_ICLK_DIV_2            (0x01000000UL) /* x1/2 */
#define _02000000_CGC_ICLK_DIV_4            (0x02000000UL) /* x1/4 */
#define _03000000_CGC_ICLK_DIV_8            (0x03000000UL) /* x1/8 */
#define _04000000_CGC_ICLK_DIV_16           (0x04000000UL) /* x1/16 */
#define _05000000_CGC_ICLK_DIV_32           (0x05000000UL) /* x1/32 */
#define _06000000_CGC_ICLK_DIV_64           (0x06000000UL) /* x1/64 */
/* System Clock (FCLK) */
#define _00000000_CGC_FCLK_DIV_1            (0x00000000UL) /* x1 */
#define _10000000_CGC_FCLK_DIV_2            (0x10000000UL) /* x1/2 */
#define _20000000_CGC_FCLK_DIV_4            (0x20000000UL) /* x1/4 */
#define _30000000_CGC_FCLK_DIV_8            (0x30000000UL) /* x1/8 */
#define _40000000_CGC_FCLK_DIV_16           (0x40000000UL) /* x1/16 */
#define _50000000_CGC_FCLK_DIV_32           (0x50000000UL) /* x1/32 */
#define _60000000_CGC_FCLK_DIV_64           (0x60000000UL) /* x1/64 */

/*
    System Clock Control Register 3 (SCKCR3)
*/
#define _0000_CGC_CLOCKSOURCE_LOCO          (0x0000U) /* LOCO */
#define _0100_CGC_CLOCKSOURCE_HOCO          (0x0100U) /* HOCO */
#define _0200_CGC_CLOCKSOURCE_MAINCLK       (0x0200U) /* Main clock oscillator */
#define _0300_CGC_CLOCKSOURCE_SUBCLK        (0x0300U) /* Sub-clock oscillator */
#define _0400_CGC_CLOCKSOURCE_PLL           (0x0400U) /* PLL circuit */

/*
    PLL Control Register (PLLCR)
*/
/* PLL Input Frequency Division Ratio Select (PLIDIV[1:0]) */
#define _0000_CGC_PLL_FREQ_DIV_1            (0x0000U) /* x1 */
#define _0001_CGC_PLL_FREQ_DIV_2            (0x0001U) /* x1/2 */
#define _0002_CGC_PLL_FREQ_DIV_4            (0x0002U) /* x1/4 */
/* Frequency Multiplication Factor Select (STC[5:0]) */
#define _0B00_CGC_PLL_FREQ_MUL_6            (0x0B00U) /* x6 */
#define _0F00_CGC_PLL_FREQ_MUL_8            (0x0F00U) /* x8 */

/*
    USB-dedicated PLL Control Register (UPLLCR)
*/
/* USB-dedicated PLL Input Frequency Division Ratio Select (UPLIDIV[1:0]) */
#define _0000_CGC_PLL_UPLIDIV_1             (0x0000U) /* x1 */
#define _0001_CGC_PLL_UPLIDIV_2             (0x0001U) /* x1/2 */
#define _0002_CGC_PLL_UPLIDIV_4             (0x0002U) /* x1/4 */
/* UCLK Source USB-Dedicated PLL Select (UCKUPLLSEL) */
#define _0000_CGC_UCLK_SYSCLK               (0x0000U) /* System clock is selected as UCLK */
#define _0010_CGC_UCLK_USBPLL               (0x0010U) /* USB-dedicated PLL is selected as UCLK */
/* Frequency Multiplication Factor Select (USTC[5:0]) */
#define _0B00_CGC_PLL_USTC_6                (0x0B00U) /* x6 */
#define _0F00_CGC_PLL_USTC_8                (0x0F00U) /* x8 */

/*
    Oscillation Stop Detection Control Register (OSTDCR)
*/
/* Oscillation Stop Detection Interrupt Enable (OSTDIE) */
#define _00_CGC_OSC_STOP_INT_DISABLE        (0x00U) /* The oscillation stop detection interrupt is disabled */
#define _01_CGC_OSC_STOP_INT_ENABLE         (0x01U) /* The oscillation stop detection interrupt is enabled */
/* Oscillation Stop Detection Function Enable (OSTDE) */
#define _00_CGC_OSC_STOP_DISABLE            (0x00U) /* Oscillation stop detection function is disabled */
#define _80_CGC_OSC_STOP_ENABLE             (0x80U) /* Oscillation stop detection function is enabled */

/*
    Main Clock Oscillator Wait Control Register (MOSCWTCR)
*/
/* Main Clock Oscillator Wait Time (MSTS[4:0]) */
#define _00_CGC_OSC_WAIT_CYCLE_2            (0x00U) /* Wait time = 2 cycles */
#define _01_CGC_OSC_WAIT_CYCLE_1024         (0x01U) /* Wait time = 1024 cycles */
#define _02_CGC_OSC_WAIT_CYCLE_2048         (0x02U) /* Wait time = 2048 cycles */
#define _03_CGC_OSC_WAIT_CYCLE_4096         (0x03U) /* Wait time = 4096 cycles */
#define _04_CGC_OSC_WAIT_CYCLE_8192         (0x04U) /* Wait time = 8192 cycles */
#define _05_CGC_OSC_WAIT_CYCLE_16384        (0x05U) /* Wait time = 16384 cycles */
#define _06_CGC_OSC_WAIT_CYCLE_32768        (0x06U) /* Wait time = 32768 cycles */
#define _07_CGC_OSC_WAIT_CYCLE_65536        (0x07U) /* Wait time = 65536 cycles */

/*
    HOCO Wait Control Register (HOCOWTCR)
*/
/* HOCO Wait Time (HOCOWTCR) */
#define _05_CGC_HOCO_WAIT_CYCLE_138         (0x05U) /* Wait time = 138 cycles (34.5us) */
#define _06_CGC_HOCO_WAIT_CYCLE_266         (0x06U) /* Wait time = 266 cycles (66.5us) */

/*
    Clock Output Control Register (CKOCR)
*/
/* Clock Output Source Select (CKOSEL[2:0]) */
#define _0000_CGC_CLKOUT_LOCO               (0x0000U) /* LOCO */
#define _0100_CGC_CLKOUT_HOCO               (0x0100U) /* HOCO */
#define _0200_CGC_CLKOUT_MAINCLK            (0x0200U) /* Main clock oscillator */
#define _0300_CGC_CLKOUT_SUBCLK             (0x0300U) /* Sub-clock oscillator */
/* Clock Output Division Ratio Select (CKODIV[2:0]) */
#define _0000_CGC_CLKOUT_DIV_1              (0x0000U) /* x1 */
#define _1000_CGC_CLKOUT_DIV_2              (0x1000U) /* x1/2 */
#define _2000_CGC_CLKOUT_DIV_4              (0x2000U) /* x1/4 */
#define _3000_CGC_CLKOUT_DIV_8              (0x3000U) /* x1/8 */
#define _4000_CGC_CLKOUT_DIV_16             (0x4000U) /* x1/16 */
/* Clock Output Control (CKOSTP) */
#define _0000_CGC_CLKOUT_ENABLE             (0x0000U) /* CLKOUT pin output is operating */
#define _8000_CGC_CLKOUT_DISABLE            (0x8000U) /* CLKOUT pin output is stopped (fixed at low level) */

/*
    Main Clock Oscillator Forced Oscillation Control Register (MOFCR)
*/
/* Main Oscillator Drive Capability Switch (MODRV21) */
#define _00_CGC_MAINOSC_UNDER10M            (0x00U) /* 1 MHz to 10 MHz */
#define _20_CGC_MAINOSC_OVER10M             (0x20U) /* 10 MHz to 20 MHz */
/* Main Clock Oscillator Switch (MOSEL) */
#define _00_CGC_MAINOSC_RESONATOR           (0x00U) /* Resonator */
#define _40_CGC_MAINOSC_EXTERNAL            (0x40U) /* External oscillator input */

/*
    LCD Source Clock Control Register (LCDSCLKCR)
*/
/* LCD Source Clock Select (LCDSCLKSEL[2:0]) */
#define _00_CGC_LCDSCLKSEL_LOCO             (0x00U) /* LOCO */
#define _01_CGC_LCDSCLKSEL_HOCO             (0x01U) /* HOCO */
#define _02_CGC_LCDSCLKSEL_MAINCLK          (0x02U) /* Main clock oscillator */
#define _03_CGC_LCDSCLKSEL_SUBCLK           (0x03U) /* Sub-clock oscillator */
#define _04_CGC_LCDSCLKSEL_IWDT             (0x04U) /* IWDT-dedicated on-chip oscillator */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_CGC_Create(void);

/* Start user code for function. Do not edit comment generated here */

/* Select the clock condition */
#define TOUCH_CFG_CLOCK_SOURCE      (1)
#define TOUCH_CFG_HOCO_FREQUENCY    (0)
#define TOUCH_CFG_XTAL_HZ           (16000000)

/* PLL Input Frequency Division Ratio Select/Frequency Multiplication Factor Select */
#define TOUCH_CFG_UPLL_DIV          (2)         /* USB-dedicated PLL Input Frequency Division Ratio Select  */
#define TOUCH_CFG_UPLL_MUL          (6)         /* Frequency Multiplication Factor Select                   */
#define TOUCH_CFG_PLL_DIV           (4)         /* PLL Input Frequency Division Ratio Select                */
#define TOUCH_CFG_PLL_MUL           (8)         /* Frequency Multiplication Factor Select                   */

/* System Clock Control Register (SCKCR) */
#define TOUCH_CFG_ICK_DIV           (1)         /* System Clock (ICLK) Select                               */
#define TOUCH_CFG_PCKB_DIV          (1)         /* Peripheral Module Clock B(PCLKB) Select                  */


#if (MCU_SERIES_T == R5F5113)
    #define TOUCH_CFG_FCK_DIV  TOUCH_CFG_ICK_DIV    /* FlashIF Clock (FCLK) Select                              */
    #define TOUCH_CFG_PCKD_DIV TOUCH_CFG_PCKB_DIV   /* Peripheral Module Clock D(PCLKD) Select                  */
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
    #define TOUCH_CFG_FCK_DIV  TOUCH_CFG_PCKB_DIV   /* FlashIF Clock (FCLK) Select                              */
    #define TOUCH_CFG_PCKA_DIV TOUCH_CFG_PCKB_DIV   /* Peripheral Module Clock A(PCLKA) Select                  */
    #define TOUCH_CFG_PCKD_DIV TOUCH_CFG_PCKB_DIV   /* Peripheral Module Clock D(PCLKD) Select                  */
    #define TOUCH_CFG_BCLK_DIV TOUCH_CFG_PCKB_DIV   /* External Bus Clock (BCLK) Select                         */
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)

#if (MCU_SERIES_T == R5F5130)
    #define TOUCH_CFG_FCK_DIV  TOUCH_CFG_ICK_DIV    /* FlashIF Clock (FCLK) Select                              */
    #define TOUCH_CFG_PCKD_DIV TOUCH_CFG_PCKB_DIV   /* Peripheral Module Clock D(PCLKD) Select                  */
#endif    // (MCU_SERIES_T == R5F5130)

/* Clock Source */
#define TOUCH_CLOCK_SOURCE_LOCO     (0)         /* Low Speed On-Chip Oscillator  (LOCO)                    */
#define TOUCH_CLOCK_SOURCE_HOCO     (1)         /* High Speed On-Chip Oscillator (HOCO)                    */
#define TOUCH_CLOCK_SOURCE_MAIN     (2)         /* Main Clock Oscillator                                   */
#define TOUCH_CLOCK_SOURCE_SUB      (3)         /* Sub-Clock Oscillator                                    */
#define TOUCH_CLOCK_SOURCE_PLL      (4)         /* PLL Circuit                                             */

#if   TOUCH_CFG_FCK_DIV == 1
    #define TOUCH_FCK_DIV   (0x00000000UL) /* x1 */
#elif TOUCH_CFG_FCK_DIV == 2
    #define TOUCH_FCK_DIV   (0x10000000UL) /* x1/2 */
#elif TOUCH_CFG_FCK_DIV == 4
    #define TOUCH_FCK_DIV   (0x20000000UL) /* x1/4 */
#elif TOUCH_CFG_FCK_DIV == 8
    #define TOUCH_FCK_DIV   (0x30000000UL) /* x1/8 */
#elif TOUCH_CFG_FCK_DIV == 16
    #define TOUCH_FCK_DIV   (0x40000000UL) /* x1/16 */
#elif TOUCH_CFG_FCK_DIV == 32
    #define TOUCH_FCK_DIV   (0x50000000UL) /* x1/32 */
#elif TOUCH_CFG_FCK_DIV == 64
    #define TOUCH_FCK_DIV	(0x60000000UL) /* x1/64 */
#else
    #error "Error! Invalid setting for TOUCH_CFG_FCK_DIV"
#endif

#if   TOUCH_CFG_ICK_DIV == 1
    #define TOUCH_ICK_DIV   (0x00000000UL) /* x1 */
#elif TOUCH_CFG_ICK_DIV == 2
    #define TOUCH_ICK_DIV   (0x01000000UL) /* x1/2 */
#elif TOUCH_CFG_ICK_DIV == 4
    #define TOUCH_ICK_DIV   (0x02000000UL) /* x1/4 */
#elif TOUCH_CFG_ICK_DIV == 8
    #define TOUCH_ICK_DIV   (0x03000000UL) /* x1/8 */
#elif TOUCH_CFG_ICK_DIV == 16
    #define TOUCH_ICK_DIV   (0x04000000UL) /* x1/16 */
#elif TOUCH_CFG_ICK_DIV == 32
    #define TOUCH_ICK_DIV   (0x05000000UL) /* x1/32 */
#elif TOUCH_CFG_ICK_DIV == 64
    #define TOUCH_ICK_DIV   (0x06000000UL) /* x1/64 */
#else
    #error "Error! Invalid setting for TOUCH_CFG_ICK_DIV"
#endif

#if   TOUCH_CFG_PCKB_DIV == 1
    #define TOUCH_PCKB_DIV  (0x00000000UL) /* x1 */
#elif TOUCH_CFG_PCKB_DIV == 2
    #define TOUCH_PCKB_DIV  (0x00000100UL) /* x1/2 */
#elif TOUCH_CFG_PCKB_DIV == 4
    #define TOUCH_PCKB_DIV  (0x00000200UL) /* x1/4 */
#elif TOUCH_CFG_PCKB_DIV == 8
    #define TOUCH_PCKB_DIV  (0x00000300UL) /* x1/8 */
#elif TOUCH_CFG_PCKB_DIV == 16
    #define TOUCH_PCKB_DIV  (0x00000400UL) /* x1/16 */
#elif TOUCH_CFG_PCKB_DIV == 32
    #define TOUCH_PCKB_DIV  (0x00000500UL) /* x1/32 */
#elif TOUCH_CFG_PCKB_DIV == 64
    #define TOUCH_PCKB_DIV  (0x00000600UL) /* x1/64 */
#else
    #error "Error! Invalid setting for TOUCH_CFG_PCKB_DIV"
#endif

#if   TOUCH_CFG_PCKD_DIV == 1
    #define TOUCH_PCKD_DIV  (0x00000000UL) /* x1 */
#elif TOUCH_CFG_PCKD_DIV == 2
    #define TOUCH_PCKD_DIV  (0x00000001UL) /* x1/2 */
#elif TOUCH_CFG_PCKD_DIV == 4
    #define TOUCH_PCKD_DIV  (0x00000002UL) /* x1/4 */
#elif TOUCH_CFG_PCKD_DIV == 8
    #define TOUCH_PCKD_DIV  (0x00000003UL) /* x1/8 */
#elif TOUCH_CFG_PCKD_DIV == 16
    #define TOUCH_PCKD_DIV  (0x00000004UL) /* x1/16 */
#elif TOUCH_CFG_PCKD_DIV == 32
    #define TOUCH_PCKD_DIV  (0x00000005UL) /* x1/32 */
#elif TOUCH_CFG_PCKD_DIV == 64
    #define TOUCH_PCKD_DIV  (0x00000006UL) /* x1/64 */
#else
    #error "Error! Invalid setting for TOUCH_CFG_PCKD_DIV"
#endif

#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
    #if   TOUCH_CFG_PCKA_DIV == 1
        #define TOUCH_PCKA_DIV  (0x00000000UL) /* x1 */
    #elif TOUCH_CFG_PCKA_DIV == 2
        #define TOUCH_PCKA_DIV  (0x00001000UL) /* x1/2 */
    #elif TOUCH_CFG_PCKA_DIV == 4
        #define TOUCH_PCKA_DIV  (0x00002000UL) /* x1/4 */
    #elif TOUCH_CFG_PCKA_DIV == 8
        #define TOUCH_PCKA_DIV  (0x00003000UL) /* x1/8 */
    #elif TOUCH_CFG_PCKA_DIV == 16
        #define TOUCH_PCKA_DIV  (0x00004000UL) /* x1/16 */
    #elif TOUCH_CFG_PCKA_DIV == 32
        #define TOUCH_PCKA_DIV  (0x00005000UL) /* x1/32 */
    #elif TOUCH_CFG_PCKA_DIV == 64
        #define TOUCH_PCKA_DIV  (0x00006000UL) /* x1/64 */
    #else
        #error "Error! Invalid setting for TOUCH_CFG_PCKA_DIV"
    #endif

    #if   TOUCH_CFG_BCLK_DIV == 1
        #define TOUCH_BCLK_DIV  (0x00000000UL) /* x1 */
    #elif TOUCH_CFG_BCLK_DIV == 2
        #define TOUCH_BCLK_DIV  (0x00010000UL) /* x1/2 */
    #elif TOUCH_CFG_BCLK_DIV == 4
        #define TOUCH_BCLK_DIV  (0x00020000UL) /* x1/4 */
    #elif TOUCH_CFG_BCLK_DIV == 8
        #define TOUCH_BCLK_DIV  (0x00030000UL) /* x1/8 */
    #elif TOUCH_CFG_BCLK_DIV == 16
        #define TOUCH_BCLK_DIV  (0x00040000UL) /* x1/16 */
    #elif TOUCH_CFG_BCLK_DIV == 32
        #define TOUCH_BCLK_DIV  (0x00050000UL) /* x1/32 */
    #elif TOUCH_CFG_BCLK_DIV == 64
        #define TOUCH_BCLK_DIV  (0x00060000UL) /* x1/64 */
    #else
        #error "Error! Invalid setting for TOUCH_BCLK_DIV"
    #endif
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)


#if (MCU_SERIES_T == R5F5113)
    #define TOUCH_SCKCR     TOUCH_PCKD_DIV | TOUCH_PCKB_DIV | TOUCH_ICK_DIV | TOUCH_FCK_DIV
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
     #define TOUCH_SCKCR     TOUCH_PCKD_DIV | TOUCH_PCKB_DIV | TOUCH_PCKA_DIV | TOUCH_BCLK_DIV | TOUCH_ICK_DIV  | TOUCH_FCK_DIV
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)

#if (MCU_SERIES_T == R5F5130)
    #define TOUCH_SCKCR     TOUCH_PCKD_DIV | TOUCH_PCKB_DIV | TOUCH_ICK_DIV | TOUCH_FCK_DIV
#endif    // (MCU_SERIES_T == R5F5130)

#if(TOUCH_CFG_CLOCK_SOURCE == TOUCH_CLOCK_SOURCE_PLL)
    #if   TOUCH_CFG_PLL_DIV == 1
        #define TOUCH_PLL_DIV  (0x0000U) /* x1 */
    #elif TOUCH_CFG_PLL_DIV == 2
        #define TOUCH_PLL_DIV  (0x0001U) /* x1/2 */
    #elif TOUCH_CFG_PLL_DIV == 4
        #define TOUCH_PLL_DIV  (0x0002U) /* x1/4 */
    #else
        #error "Error! Invalid setting for TOUCH_CFG_PLL_DIV"
    #endif

#if (MCU_SERIES_T == R5F5113)
    #if   TOUCH_CFG_PLL_MUL == 6
        #define TOUCH_PLL_MUL  (0x0B00U) /* x6 */
    #elif TOUCH_CFG_PLL_MUL == 8
        #define TOUCH_PLL_MUL  (0x0F00U) /* x8 */
    #else
        #error "Error! Invalid setting for TOUCH_CFG_PLL_MUL"
    #endif
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)
     #define TOUCH_PLL_MUL  (((uint8_t)((float)TOUCH_CFG_PLL_MUL * 2.0)) - 1) << 8;
#endif    // (MCU_SERIES_T == R5F5230 || MCU_SERIES_T == R5F5231)

#if (MCU_SERIES_T == R5F5130)
     #define TOUCH_PLL_MUL  (((uint8_t)((float)TOUCH_CFG_PLL_MUL * 2.0)) - 1) << 8;
#endif    // (MCU_SERIES_T == R5F5130)

    #define TOUCH_PLLCR     TOUCH_PLL_DIV | TOUCH_PLL_MUL
#endif

/* Clock Frequency */
#define TOUCH_SAMPLE_4MHZ           (4000000)   /* 4MHz                                                  */
#define TOUCH_SAMPLE_6MHZ           (6000000)   /* 6MHz                                                  */
#define TOUCH_SAMPLE_8MHZ           (8000000)   /* 8MHz                                                  */
#define TOUCH_SAMPLE_10MHZ          (10000000)  /* 10MHz                                                 */
#define TOUCH_SAMPLE_12MHZ          (12000000)  /* 12MHz                                                 */
#define TOUCH_SAMPLE_16MHZ          (16000000)  /* 16MHz                                                 */
#define TOUCH_SAMPLE_32MHZ          (32000000)  /* 32MHz                                                 */


/* USB Serial Use */
#if (MCU_SERIES_T == R5F5113)
    #ifdef TOUCH_WITHOUT_USB
        #undef USB_SERIAL_USE
    #else
        #if(TOUCH_CFG_CLOCK_SOURCE == TOUCH_CLOCK_SOURCE_PLL)    /* PLL Select(Main Clock)                    */
            #if(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_16MHZ)
                #define USB_SERIAL_USE
            #elif(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_12MHZ)
                #define USB_SERIAL_USE
            #elif(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_8MHZ)
                #define USB_SERIAL_USE
            #elif(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_6MHZ)
                #define USB_SERIAL_USE
            #else
                #undef USB_SERIAL_USE
            #endif
        #else
            #undef USB_SERIAL_USE
        #endif
    #endif

    #ifdef USB_SERIAL_USE
        #if   TOUCH_CFG_UPLL_DIV == 1
            #define TOUCH_UPLL_DIV  (0x0000U) /* x1 */
        #elif TOUCH_CFG_UPLL_DIV == 2
            #define TOUCH_UPLL_DIV  (0x0001U) /* x1/2 */
        #elif TOUCH_CFG_UPLL_DIV == 4
            #define TOUCH_UPLL_DIV  (0x0002U) /* x1/4 */
        #else
            #error "Error! Invalid setting for TOUCH_CFG_UPLL_DIV"
        #endif

        #if   TOUCH_CFG_UPLL_MUL == 6
            #define TOUCH_UPLL_MUL  (0x0B00U) /* x6 */
        #elif TOUCH_CFG_UPLL_MUL == 8
            #define TOUCH_UPLL_MUL  (0x0F00U) /* x8 */
        #else
            #error "Error! Invalid setting for TOUCH_CFG_UPLL_MUL"
        #endif

        #define TOUCH_UPLLCR    TOUCH_UPLL_DIV | _0010_CGC_UCLK_USBPLL | TOUCH_UPLL_MUL
    #endif

#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5231)
    #ifdef TOUCH_WITHOUT_USB
        #undef USB_SERIAL_USE
    #else
        #if(TOUCH_CFG_CLOCK_SOURCE == TOUCH_CLOCK_SOURCE_PLL)    /* PLL Select(Main Clock)                    */
            #if(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_16MHZ)
                #define USB_SERIAL_USE
            #elif(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_12MHZ)
                #define USB_SERIAL_USE
            #elif(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_8MHZ)
                #define USB_SERIAL_USE
            #elif(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_6MHZ)
                #define USB_SERIAL_USE
            #elif(TOUCH_CFG_XTAL_HZ == TOUCH_SAMPLE_4MHZ)
                #define USB_SERIAL_USE
            #else
                #undef USB_SERIAL_USE
            #endif
        #else
            #undef USB_SERIAL_USE
        #endif
    #endif

    #ifdef USB_SERIAL_USE
        #if   TOUCH_CFG_UPLL_DIV == 1
            #define TOUCH_UPLL_DIV  (0x0000U) /* x1 */
        #elif TOUCH_CFG_UPLL_DIV == 2
            #define TOUCH_UPLL_DIV  (0x0001U) /* x1/2 */
        #elif TOUCH_CFG_UPLL_DIV == 4
            #define TOUCH_UPLL_DIV  (0x0002U) /* x1/4 */
        #else
            #error "Error! Invalid setting for TOUCH_CFG_UPLL_DIV"
        #endif

        #if TOUCH_CFG_UPLL_MUL == 4
            #define TOUCH_UPLL_MUL  (0x0700U) /* x4 */
        #elif TOUCH_CFG_UPLL_MUL == 6
            #define TOUCH_UPLL_MUL  (0x0B00U) /* x6 */
        #elif TOUCH_CFG_UPLL_MUL == 8
            #define TOUCH_UPLL_MUL  (0x0F00U) /* x8 */
        #elif TOUCH_CFG_UPLL_MUL == 12
            #define TOUCH_UPLL_MUL  (0x1700U) /* x12 */
        #else
            #error "Error! Invalid setting for TOUCH_CFG_UPLL_MUL"
        #endif

        #define TOUCH_UPLLCR    TOUCH_UPLL_DIV | _0010_CGC_UCLK_USBPLL | TOUCH_UPLL_MUL
    #endif

#endif    // (MCU_SERIES_T == R5F5231)

#if (MCU_SERIES_T == R5F5230)
    #undef USB_SERIAL_USE
#endif    // (MCU_SERIES_T == R5F5230)

#if (MCU_SERIES_T == R5F5130)
    #undef USB_SERIAL_USE
#endif  // (MCU_SERIES_T == R5F5130)

/* Workbench serial connection setting */
#define	WORKBENCH_SERIAL_CONNECT         (1)       /* 0: Unuse, 1: Uart(SCI6), 2: USB function */

    #if WORKBENCH_SERIAL_CONNECT == 0
        #undef USB_SERIAL_USE
        #undef SCI_SERIAL_USE
    #elif WORKBENCH_SERIAL_CONNECT == 1
        #undef USB_SERIAL_USE
        #define SCI_SERIAL_USE
    #elif WORKBENCH_SERIAL_CONNECT == 2
        #undef SCI_SERIAL_USE
    #else
        #error "Error! Invalid setting for WORKBENCH_SERIAL_CONNECT"
    #endif

/***** Touch measurement cycle ****************************************************************************************/
/* Touch Measurement cycle (ms) */
#define TOUCH_MAIN_TIMING_MS              (2)

/* Touch Measurement cycle macro (ms) */
#define TOUCH_MEASUREMENT_2MS            (2)
#define TOUCH_MEASUREMENT_4MS            (4)

/* Compare Match Timer Control Register Clock Select PCLK/xxx */
#define CTSU_CMCOR_CKS         (8)

#if(TOUCH_MAIN_TIMING_MS == TOUCH_MEASUREMENT_2MS)
    #define TOUCH_CMT_FREQUENCY_HZ      (500)      /* 2ms = 500Hz */
#elif(TOUCH_MAIN_TIMING_MS == TOUCH_MEASUREMENT_4MS)
    #define TOUCH_CMT_FREQUENCY_HZ      (250)      /* 4ms = 250Hz */
#else
#endif

/* ICK clock frequency in Hz */
#define TOUCH_CFG_ICLK_HZ           (32000000)

#if TOUCH_CFG_ICLK_HZ > TOUCH_SAMPLE_32MHZ
    #define TOUCH_CMT_BASE_HZ           TOUCH_CFG_ICLK_HZ / 2
#else
    #define TOUCH_CMT_BASE_HZ           TOUCH_CFG_ICLK_HZ
#endif

/* Compare Match Constant Register for Touch */
#define TOUCH_CMCOR_VALUE       ((TOUCH_CMT_BASE_HZ/CTSU_CMCOR_CKS)/TOUCH_CMT_FREQUENCY_HZ) - 1

/***** Voltage parameter ****************************************************************************************/
#define USB_VDCEN                           (1)          /* 0: (Vcc 3.0V-3.6V) 1: (Vcc 3.8V-5.5V) */

/* End user code. Do not edit comment generated here */
#endif
