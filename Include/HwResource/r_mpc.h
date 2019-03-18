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
* File Name    : r_mpc.h
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file includes the function of the pin.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/
#ifndef __R_MPC_H__    //[
#define __R_MPC_H__

/***********************************************************************************************************************
 Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_ctsu.h"

/***********************************************************************************************************************
 Macro definitions
***********************************************************************************************************************/
#ifdef __R_MPC_C__
    #define MPC_EXTERN
#else
    #define MPC_EXTERN    extern
#endif

/***** Protect enable set up data *************************************************************************************/
#define PRCR1_ENA               (0xA502)      /* 803FEh    Protect register                                           */
#define PRCR1_DIS               (0xA500)      /* 803FEh    Protect register                                           */

/***** Function select set up data ************************************************************************************/
#if (MCU_SERIES_T == R5F5113)
    #define P02PFS_TS2              (0x19)        /* 8C142h    P02 Pin function control register(TS2)                 */
    #define P04PFS_TS1              (0x19)        /* 8C144h    P04 Pin function control register(TS1)                 */
    #define P07PFS_TS0              (0x19)        /* 8C147h    P07 Pin function control register(TS0)                 */

    #define P20PFS_TS9              (0x19)        /* 8C150h    P20 Pin function control register(TS9)                 */
    #define P21PFS_TS8              (0x19)        /* 8C151h    P21 Pin function control register(TS8)                 */
    #define P22PFS_TS7              (0x19)        /* 8C152h    P22 Pin function control register(TS7)                 */
    #define P23PFS_TS6              (0x19)        /* 8C153h    P23 Pin function control register(TS6)                 */
    #define P24PFS_TS5              (0x19)        /* 8C154h    P24 Pin function control register(TS5)                 */
    #define P25PFS_TS4              (0x19)        /* 8C155h    P25 Pin function control register(TS4)                 */
    #define P26PFS_TSCAP            (0x19)        /* 8C156h    P26 Pin function control register(TSCAP)               */
    #define P27PFS_TS10             (0x19)        /* 8C157h    P27 Pin function control register(TS10)                */

    #define P32PFS_TS11             (0x19)        /* 8C15Ah    P32 Pin function control register(TS11)                */
    #define PJ3PFS_TS3              (0x19)        /* 8C1D3h    P32 Pin function control register(TS3)                 */
#endif    // (MCU_SERIES_T == R5F5113_12TS)

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)
#if (MAX_TS == 36)
    #define P14PFS_TS13             (0x19)        /* 8C14Ch    P20 Pin function control register(TS13)                */
    #define P15PFS_TS12             (0x19)        /* 8C14Dh    P20 Pin function control register(TS12)                */

    #define P20PFS_TS9              (0x19)        /* 8C150h    P20 Pin function control register(TS9)                 */
    #define P21PFS_TS8              (0x19)        /* 8C151h    P21 Pin function control register(TS8)                 */
    #define P22PFS_TS7              (0x19)        /* 8C152h    P22 Pin function control register(TS7)                 */
    #define P23PFS_TS6              (0x19)        /* 8C153h    P23 Pin function control register(TS6)                 */
    #define P24PFS_TS5              (0x19)        /* 8C154h    P24 Pin function control register(TS5)                 */
    #define P25PFS_TS4              (0x19)        /* 8C155h    P25 Pin function control register(TS4)                 */
    #define P26PFS_TS3              (0x19)        /* 8C156h    P26 Pin function control register(TS3)                 */
    #define P27PFS_TS2              (0x19)        /* 8C157h    P27 Pin function control register(TS2)                 */

    #define P33PFS_TS1              (0x19)        /* 8C15Bh    P20 Pin function control register(TS1)                 */
    #define P34PFS_TS0              (0x19)        /* 8C15Ch    P21 Pin function control register(TS0)                 */

    #define P50PFS_TS20             (0x19)        /* 8C168h    P20 Pin function control register(TS20)                */
    #define P51PFS_TS19             (0x19)        /* 8C169h    P21 Pin function control register(TS19)                */
    #define P52PFS_TS18             (0x19)        /* 8C16Ah    P22 Pin function control register(TS18)                */
    #define P53PFS_TS17             (0x19)        /* 8C16Ah    P22 Pin function control register(TS18)                */
    #define P54PFS_TS16             (0x19)        /* 8C16Ch    P24 Pin function control register(TS16)                */
    #define P55PFS_TS15             (0x19)        /* 8C16Dh    P25 Pin function control register(TS15)                */

    #define PC0PFS_TS35             (0x19)        /* 8C1A0h    P20 Pin function control register(TS35)                */
    #define PC1PFS_TS33             (0x19)        /* 8C1A1h    P21 Pin function control register(TS33)                */
    #define PC2PFS_TS30             (0x19)        /* 8C1A2h    P22 Pin function control register(TS30)                */
    #define PC3PFS_TS27             (0x19)        /* 8C1A3h    P23 Pin function control register(TS27)                */
    #define PC4PFS_TSCAP            (0x19)        /* 8C1A4h    P24 Pin function control register(TSCAP)               */
    #define PC5PFS_TS23             (0x19)        /* 8C1A5h    P25 Pin function control register(TS23)                */
    #define PC6PFS_TS22             (0x19)        /* 8C1A6h    P26 Pin function control register(TS22)                */
#endif    // (MAX_TS == 36)

#if (MAX_TS == 31)
    #define P14PFS_TS13             (0x19)        /* 8C14Ch    P20 Pin function control register(TS13)                */
    #define P15PFS_TS12             (0x19)        /* 8C14Dh    P20 Pin function control register(TS12)                */

    #define P26PFS_TS3              (0x19)        /* 8C156h    P26 Pin function control register(TS3)                 */
    #define P27PFS_TS2              (0x19)        /* 8C157h    P27 Pin function control register(TS2)                 */

    #define P54PFS_TS16             (0x19)        /* 8C16Ch    P24 Pin function control register(TS16)                */
    #define P55PFS_TS15             (0x19)        /* 8C16Dh    P25 Pin function control register(TS15)                */

    #define PC2PFS_TS30             (0x19)        /* 8C1A2h    P22 Pin function control register(TS30)                */
    #define PC3PFS_TS27             (0x19)        /* 8C1A3h    P23 Pin function control register(TS27)                */
    #define PC4PFS_TSCAP            (0x19)        /* 8C1A4h    P24 Pin function control register(TSCAP)               */
    #define PC5PFS_TS23             (0x19)        /* 8C1A5h    P25 Pin function control register(TS23)                */
    #define PC6PFS_TS22             (0x19)        /* 8C1A6h    P26 Pin function control register(TS22)                */
#endif    // (MAX_TS == 31)

#if (MAX_TS == 24)
    #define P14PFS_TS13             (0x19)        /* 8C14Ch    P20 Pin function control register(TS13)                */
    #define P15PFS_TS12             (0x19)        /* 8C14Dh    P20 Pin function control register(TS12)                */

    #define P26PFS_TS3              (0x19)        /* 8C156h    P26 Pin function control register(TS3)                 */
    #define P27PFS_TS2              (0x19)        /* 8C157h    P27 Pin function control register(TS2)                 */

    #define PC4PFS_TSCAP            (0x19)        /* 8C1A4h    P24 Pin function control register(TSCAP)               */
    #define PC5PFS_TS23             (0x19)        /* 8C1A5h    P25 Pin function control register(TS23)                */
    #define PC6PFS_TS22             (0x19)        /* 8C1A6h    P26 Pin function control register(TS22)                */
#endif    // (MAX_TS == 24)
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)

#if (MCU_SERIES_T == R5F5130)
#if (MAX_TS == 36)
    #define P14PFS_TS6              (0x19)        /* 8C14Ch    P14 Pin function control register(TS6)                 */
    #define P15PFS_TS5              (0x19)        /* 8C14Dh    P15 Pin function control register(TS5)                 */

    #define P26PFS_TS4              (0x19)        /* 8C156h    P26 Pin function control register(TS4)                 */
    #define P27PFS_TS3              (0x19)        /* 8C157h    P27 Pin function control register(TS3)                 */

    #define P30PFS_TS2              (0x19)        /* 8C158h    P30 Pin function control register(TS2)                 */
    #define P31PFS_TS1              (0x19)        /* 8C159h    P31 Pin function control register(TS1)                 */
    #define P32PFS_TS0              (0x19)        /* 8C15Ah    P32 Pin function control register(TS0)                 */

    #define P54PFS_TS12             (0x19)        /* 8C16Ch    P54 Pin function control register(TS12)                */
    #define P55PFS_TS11             (0x19)        /* 8C16Dh    P55 Pin function control register(TS11)                */

    #define PA0PFS_TS32             (0x19)        /* 8C190h    PA0 Pin function control register(TS32)                */
    #define PA1PFS_TS31             (0x19)        /* 8C191h    PA1 Pin function control register(TS31)                */
    #define PA2PFS_TS30             (0x19)        /* 8C192h    PA2 Pin function control register(TS30)                */
    #define PA3PFS_TS29             (0x19)        /* 8C193h    PA3 Pin function control register(TS29)                */
    #define PA4PFS_TS28             (0x19)        /* 8C194h    PA4 Pin function control register(TS28)                */
    #define PA5PFS_TS27             (0x19)        /* 8C195h    PA5 Pin function control register(TS27)                */
    #define PA6PFS_TS26             (0x19)        /* 8C196h    PA6 Pin function control register(TS26)                */

    #define PB0PFS_TS25             (0x19)        /* 8C198h    PA0 Pin function control register(TS25)                */
    #define PB1PFS_TS24             (0x19)        /* 8C199h    PA1 Pin function control register(TS24)                */
    #define PB2PFS_TS23             (0x19)        /* 8C19Ah    PA2 Pin function control register(TS23)                */
    #define PB3PFS_TS22             (0x19)        /* 8C19Bh    PA3 Pin function control register(TS22)                */
    #define PB4PFS_TS21             (0x19)        /* 8C19Ch    PA4 Pin function control register(TS21)                */
    #define PB5PFS_TS20             (0x19)        /* 8C19Dh    PA5 Pin function control register(TS20)                */
    #define PB6PFS_TS19             (0x19)        /* 8C19Eh    PA6 Pin function control register(TS19)                */
    #define PB7PFS_TS18             (0x19)        /* 8C19Fh    PA6 Pin function control register(TS18)                */

    #define PC2PFS_TS17             (0x19)        /* 8C1A2h    PC2 Pin function control register(TS17)                */
    #define PC3PFS_TS16             (0x19)        /* 8C1A3h    PC3 Pin function control register(TS16)                */
    #define PC4PFS_TSCAP            (0x19)        /* 8C1A4h    PC4 Pin function control register(TSCAP)               */
    #define PC5PFS_TS15             (0x19)        /* 8C1A5h    PC5 Pin function control register(TS15)                */
    #define PC6PFS_TS14             (0x19)        /* 8C1A6h    PC6 Pin function control register(TS14)                */
    #define PC7PFS_TS13             (0x19)        /* 8C1A7h    PC7 Pin function control register(TS13)                */

    #define PE2PFS_TS35             (0x19)        /* 8C1B2h    PE2 Pin function control register(TS35)                */
    #define PE3PFS_TS34             (0x19)        /* 8C1B3h    PE3 Pin function control register(TS34)                */
    #define PE4PFS_TS33             (0x19)        /* 8C1B4h    PE4 Pin function control register(TS33)                */

    #define PH0PFS_TS10             (0x19)        /* 8C1C8h    PH0 Pin function control register(TS10)                */
    #define PH1PFS_TS9              (0x19)        /* 8C1C9h    PH1 Pin function control register(TS9)                 */
    #define PH2PFS_TS8              (0x19)        /* 8C1CAh    PH2 Pin function control register(TS8)                 */
    #define PH3PFS_TS7              (0x19)        /* 8C1CBh    PH3 Pin function control register(TS7)                 */
#endif    // (MAX_TS == 36)

#if (MAX_TS == 32)
    #define P14PFS_TS6              (0x19)        /* 8C14Ch    P14 Pin function control register(TS6)                 */
    #define P15PFS_TS5              (0x19)        /* 8C14Dh    P15 Pin function control register(TS5)                 */

    #define P26PFS_TS4              (0x19)        /* 8C156h    P26 Pin function control register(TS4)                 */
    #define P27PFS_TS3              (0x19)        /* 8C157h    P27 Pin function control register(TS3)                 */

    #define P30PFS_TS2              (0x19)        /* 8C158h    P30 Pin function control register(TS2)                 */
    #define P31PFS_TS1              (0x19)        /* 8C159h    P31 Pin function control register(TS1)                 */
    #define P32PFS_TS0              (0x19)        /* 8C15Ah    P32 Pin function control register(TS0)                 */

    #define P54PFS_TS12             (0x19)        /* 8C16Ch    P54 Pin function control register(TS12)                */
    #define P55PFS_TS11             (0x19)        /* 8C16Dh    P55 Pin function control register(TS11)                */

    #define PA0PFS_TS32             (0x19)        /* 8C190h    PA0 Pin function control register(TS32)                */
    #define PA1PFS_TS31             (0x19)        /* 8C191h    PA1 Pin function control register(TS31)                */
    #define PA3PFS_TS29             (0x19)        /* 8C193h    PA3 Pin function control register(TS29)                */
    #define PA4PFS_TS28             (0x19)        /* 8C194h    PA4 Pin function control register(TS28)                */
    #define PA6PFS_TS26             (0x19)        /* 8C196h    PA6 Pin function control register(TS26)                */

    #define PB0PFS_TS25             (0x19)        /* 8C198h    PA0 Pin function control register(TS25)                */
    #define PB1PFS_TS24             (0x19)        /* 8C199h    PA1 Pin function control register(TS24)                */
    #define PB3PFS_TS22             (0x19)        /* 8C19Bh    PA3 Pin function control register(TS22)                */
    #define PB5PFS_TS20             (0x19)        /* 8C19Dh    PA5 Pin function control register(TS20)                */
    #define PB6PFS_TS19             (0x19)        /* 8C19Eh    PA6 Pin function control register(TS19)                */
    #define PB7PFS_TS18             (0x19)        /* 8C19Fh    PA6 Pin function control register(TS18)                */

    #define PC2PFS_TS17             (0x19)        /* 8C1A2h    PC2 Pin function control register(TS17)                */
    #define PC3PFS_TS16             (0x19)        /* 8C1A3h    PC3 Pin function control register(TS16)                */
    #define PC4PFS_TSCAP            (0x19)        /* 8C1A4h    PC4 Pin function control register(TSCAP)               */
    #define PC5PFS_TS15             (0x19)        /* 8C1A5h    PC5 Pin function control register(TS15)                */
    #define PC6PFS_TS14             (0x19)        /* 8C1A6h    PC6 Pin function control register(TS14)                */
    #define PC7PFS_TS13             (0x19)        /* 8C1A7h    PC7 Pin function control register(TS13)                */

    #define PE2PFS_TS35             (0x19)        /* 8C1B2h    PE2 Pin function control register(TS35)                */
    #define PE3PFS_TS34             (0x19)        /* 8C1B3h    PE3 Pin function control register(TS34)                */
    #define PE4PFS_TS33             (0x19)        /* 8C1B4h    PE4 Pin function control register(TS33)                */

    #define PH0PFS_TS10             (0x19)        /* 8C1C8h    PH0 Pin function control register(TS10)                */
    #define PH1PFS_TS9              (0x19)        /* 8C1C9h    PH1 Pin function control register(TS9)                 */
    #define PH2PFS_TS8              (0x19)        /* 8C1CAh    PH2 Pin function control register(TS8)                 */
    #define PH3PFS_TS7              (0x19)        /* 8C1CBh    PH3 Pin function control register(TS7)                 */
#endif    // (MAX_TS == 32)

#if (MAX_TS == 24)
    #define P14PFS_TS6              (0x19)        /* 8C14Ch    P14 Pin function control register(TS6)                 */
    #define P15PFS_TS5              (0x19)        /* 8C14Dh    P15 Pin function control register(TS5)                 */

    #define P26PFS_TS4              (0x19)        /* 8C156h    P26 Pin function control register(TS4)                 */
    #define P27PFS_TS3              (0x19)        /* 8C157h    P27 Pin function control register(TS3)                 */

    #define P30PFS_TS2              (0x19)        /* 8C15Bh    P30 Pin function control register(TS2)                 */
    #define P31PFS_TS1              (0x19)        /* 8C15Ch    P31 Pin function control register(TS1)                 */

    #define PA1PFS_TS31             (0x19)        /* 8C191h    PA1 Pin function control register(TS31)                */
    #define PA3PFS_TS29             (0x19)        /* 8C193h    PA3 Pin function control register(TS29)                */
    #define PA4PFS_TS28             (0x19)        /* 8C194h    PA4 Pin function control register(TS28)                */
    #define PA6PFS_TS26             (0x19)        /* 8C196h    PA6 Pin function control register(TS26)                */

    #define PB0PFS_TS25             (0x19)        /* 8C198h    PA0 Pin function control register(TS25)                */
    #define PB1PFS_TS24             (0x19)        /* 8C199h    PA1 Pin function control register(TS24)                */
    #define PB3PFS_TS22             (0x19)        /* 8C19Bh    PA3 Pin function control register(TS22)                */
    #define PB5PFS_TS20             (0x19)        /* 8C19Dh    PA5 Pin function control register(TS20)                */

    #define PC4PFS_TSCAP            (0x19)        /* 8C1A4h    PC4 Pin function control register(TSCAP)               */
    #define PC5PFS_TS15             (0x19)        /* 8C1A5h    PC5 Pin function control register(TS15)                */
    #define PC6PFS_TS14             (0x19)        /* 8C1A6h    PC6 Pin function control register(TS14)                */
    #define PC7PFS_TS13             (0x19)        /* 8C1A7h    PC7 Pin function control register(TS13)                */

    #define PE2PFS_TS35             (0x19)        /* 8C1B2h    PE2 Pin function control register(TS35)                */
    #define PE3PFS_TS34             (0x19)        /* 8C1B3h    PE3 Pin function control register(TS34)                */
    #define PE4PFS_TS33             (0x19)        /* 8C1B4h    PE4 Pin function control register(TS33)                */

    #define PH0PFS_TS10             (0x19)        /* 8C1C8h    PH0 Pin function control register(TS10)                */
    #define PH1PFS_TS9              (0x19)        /* 8C1C9h    PH1 Pin function control register(TS9)                 */
    #define PH2PFS_TS8              (0x19)        /* 8C1CAh    PH2 Pin function control register(TS8)                 */
    #define PH3PFS_TS7              (0x19)        /* 8C1CBh    PH3 Pin function control register(TS7)                 */
#endif    // (MAX_TS == 24)
#endif    // (MCU_SERIES_T == R5F5130)

/***********************************************************************************************************************
 Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
 Global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
 Global functions
***********************************************************************************************************************/
void initial_port_set( void );
void MPC_CTSU_set( uint16_t sensor_ena0, uint16_t sensor_ena1, uint16_t sensor_ena2 );

#endif    // __R_DTC_H__
