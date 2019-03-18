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
* File Name    : r_mpc.c
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file sets the function of the pin.
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/
#define __R_MPC_C__

/***********************************************************************************************************************
 Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* System include header */
#include "r_cg_macrodriver.h"

/* H/W include header */
#include "iodefine.h"
#include "r_mpc.h"
#include "r_ctsu.h"

/* S/W include header */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: initial_port_set
* Description  : Initial port setting.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void initial_port_set( void )
{

#if (MCU_SERIES_T == R5F5113)
    /* TS0 = P07, TS1 = P04, TS2 = P02 */
    PORT0.PODR.BYTE = 0x00;
    PORT0.PDR.BYTE  = 0x94;

    /* TS3 = PJ3 */
    PORTJ.PODR.BYTE = PORTJ.PODR.BYTE & 0xF7;
    PORTJ.PDR.BYTE  = PORTJ.PDR.BYTE | 0x08;

    /* TS4 = P25, TS5 = P24, TS6 = P23, TS7 = P22, TS8 = P21, TS9 = P20, TS10 = P27, TSCAP = P26 */
    PORT2.PODR.BYTE = 0x00;
    PORT2.PDR.BYTE  = 0xFF;

    /* TS11 = P32 */
    PORT3.PODR.BYTE = PORT3.PODR.BYTE & 0xFB;
    PORT3.PDR.BYTE  = PORT3.PDR.BYTE | 0x04;
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)
#if (MAX_TS == 36)
    /* TS0 = P34, TS1 = P33  */
    PORT3.PODR.BYTE = PORT3.PODR.BYTE & 0xE7;
    PORT3.PDR.BYTE  = PORT3.PDR.BYTE | 0x18;

    /* TS2 = P27, TS3 = P26, TS4 = P25, TS5 = P24, TS6 = P23, TS7 = P22, TS8 = P21, TS9 = P20 */
    PORT2.PODR.BYTE = 0x00;
    PORT2.PDR.BYTE  = 0xFF;

    /* TS12 = P15, TS13 = P14 */
    PORT1.PODR.BYTE = PORT1.PODR.BYTE & 0xCF;
    PORT1.PDR.BYTE  = PORT1.PDR.BYTE | 0x30;

    /* TS15 = P55, TS16 = P54, TS17 = P53, TS18 = P52, TS19 = P51, TS20 = P50 */
    PORT5.PODR.BYTE = PORT5.PODR.BYTE & 0xC0;
    PORT5.PDR.BYTE  = PORT5.PDR.BYTE | 0x3F;

    /* TS22 = PC6, TS23 = PC5, TS27 = PC3, TS30 = PC2, TS33 = PC1, TS35 = PC0, TSCAP = PC4 */
    PORTC.PODR.BYTE = PORTC.PODR.BYTE & 0x80;
    PORTC.PDR.BYTE  = PORTC.PDR.BYTE | 0x7F;
#endif    // (MAX_TS == 36)

#if (MAX_TS == 31)
    /* TS2 = P27, TS3 = P26 */
    PORT2.PODR.BYTE = PORT2.PODR.BYTE & 0x3F;
    PORT2.PDR.BYTE  = PORT2.PDR.BYTE | 0xC0;

    /* TS12 = P15, TS13 = P14 */
    PORT1.PODR.BYTE = PORT1.PODR.BYTE & 0xCF;
    PORT1.PDR.BYTE  = PORT1.PDR.BYTE | 0x30;

    /* TS15 = P55, TS16 = P54 */
    PORT5.PODR.BYTE = PORT5.PODR.BYTE & 0xCF;
    PORT5.PDR.BYTE  = PORT5.PDR.BYTE | 0x30;

    /* TS22 = PC6, TS23 = PC5, TS27 = PC3, TS30 = PC2, TSCAP = PC4 */
    PORTC.PODR.BYTE = PORTC.PODR.BYTE & 0x83;
    PORTC.PDR.BYTE  = PORTC.PDR.BYTE | 0x7C;
#endif    // (MAX_TS == 31)

#if (MAX_TS == 24)
    /* TS2 = P27, TS3 = P26 */
    PORT2.PODR.BYTE = PORT2.PODR.BYTE & 0x3F;
    PORT2.PDR.BYTE  = PORT2.PDR.BYTE | 0xC0;

    /* TS12 = P15, TS13 = P14 */
    PORT1.PODR.BYTE = PORT1.PODR.BYTE & 0xCF;
    PORT1.PDR.BYTE  = PORT1.PDR.BYTE | 0x30;

    /* TS22 = PC6, TS23 = PC5, TSCAP = PC4 */
    PORTC.PODR.BYTE = PORTC.PODR.BYTE & 0x8F;
    PORTC.PDR.BYTE  = PORTC.PDR.BYTE | 0x70;
#endif    // (MAX_TS == 24)
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)

#if (MCU_SERIES_T == R5F5130)
#if (MAX_TS == 36)
    /* TS0 = P32, TS1 = P31, TS2 = P30 */
    PORT3.PODR.BYTE = PORT3.PODR.BYTE & 0xF8;
    PORT3.PDR.BYTE  = PORT3.PDR.BYTE | 0x07;

    /* TS3 = P27, TS4 = P26 */
    PORT2.PODR.BYTE = PORT2.PODR.BYTE & 0x3F;
    PORT2.PDR.BYTE  = PORT2.PDR.BYTE | 0xC0;

    /* TS5 = P15, TS6 = P14 */
    PORT1.PODR.BYTE = PORT1.PODR.BYTE & 0xCF;
    PORT1.PDR.BYTE  = PORT1.PDR.BYTE | 0x30;

    /* TS7 = PH3, TS8 = PH2, TS9 = PH1, TS10 = PH0 */
    PORTH.PODR.BYTE = PORTH.PODR.BYTE & 0xF0;
    PORTH.PDR.BYTE  = PORTH.PDR.BYTE | 0x0F;

    /* TS11 = P55, TS12 = P54 */
    PORT5.PODR.BYTE = PORT5.PODR.BYTE & 0xCF;
    PORT5.PDR.BYTE  = PORT5.PDR.BYTE | 0x30;

    /* TS13 = PC7, TS14 = PC6, TS15 = PC5, TSCAP = PC4, TS16 = PC3, TS17 = PC2 */
    PORTC.PODR.BYTE = PORTC.PODR.BYTE & 0x03;
    PORTC.PDR.BYTE  = PORTC.PDR.BYTE | 0xFC;

    /* TS18 = PB7, TS19 = PB6, TS20 = PB5, TS21 = PB4, TS22 = PB3, TS23 = PB2, TS24 = PB1, TS25 = PB0 */
    PORTB.PODR.BYTE = 0x00;
    PORTB.PDR.BYTE  = 0xFF;

    /* TS26 = PA6, TS27 = PA5, TS28 = PA4, TS29 = PA3, TS30 = PA2, TS31 = PA1, TS32 = PA0 */
    PORTA.PODR.BYTE = PORTA.PODR.BYTE & 0x80;
    PORTA.PDR.BYTE  = PORTA.PDR.BYTE | 0x7F;

    /* TS33 = PE4, TS34 = PE3, TS35 = PE2 */
    PORTE.PODR.BYTE = PORTE.PODR.BYTE & 0xE3;
    PORTE.PDR.BYTE  = PORTE.PDR.BYTE | 0x8C;
#endif    // (MAX_TS == 36)

#if (MAX_TS == 32)
    /* TS0 = P32, TS1 = P31, TS2 = P30 */
    PORT3.PODR.BYTE = PORT3.PODR.BYTE & 0xF8;
    PORT3.PDR.BYTE  = PORT3.PDR.BYTE | 0x07;

    /* TS3 = P27, TS4 = P26 */
    PORT2.PODR.BYTE = PORT2.PODR.BYTE & 0x3F;
    PORT2.PDR.BYTE  = PORT2.PDR.BYTE | 0xC0;

    /* TS5 = P15, TS6 = P14 */
    PORT1.PODR.BYTE = PORT1.PODR.BYTE & 0xCF;
    PORT1.PDR.BYTE  = PORT1.PDR.BYTE | 0x30;

    /* TS7 = PH3, TS8 = PH2, TS9 = PH1, TS10 = PH0 */
    PORTH.PODR.BYTE = PORTH.PODR.BYTE & 0xF0;
    PORTH.PDR.BYTE  = PORTH.PDR.BYTE | 0x0F;

    /* TS11 = P55, TS12 = P54 */
    PORT5.PODR.BYTE = PORT5.PODR.BYTE & 0xCF;
    PORT5.PDR.BYTE  = PORT5.PDR.BYTE | 0x30;

    /* TS13 = PC7, TS14 = PC6, TS15 = PC5, TSCAP = PC4, TS16 = PC3, TS17 = PC2 */
    PORTC.PODR.BYTE = PORTC.PODR.BYTE & 0x03;
    PORTC.PDR.BYTE  = PORTC.PDR.BYTE | 0xFC;

    /* TS18 = PB7, TS19 = PB6, TS20 = PB5, TS22 = PB3, TS24 = PB1, TS25 = PB0 */
    PORTB.PODR.BYTE = PORTB.PODR.BYTE & 0x14;
    PORTB.PDR.BYTE  = PORTB.PDR.BYTE | 0xEB;

    /* TS26 = PA6, TS28 = PA4, TS29 = PA3, TS31 = PA1, TS32 = PA0 */
    PORTA.PODR.BYTE = PORTA.PODR.BYTE & 0xA4;
    PORTA.PDR.BYTE  = PORTA.PDR.BYTE | 0x5B;

    /* TS33 = PE4, TS34 = PE3, TS35 = PE2 */
    PORTE.PODR.BYTE = PORTE.PODR.BYTE & 0xE3;
    PORTE.PDR.BYTE  = PORTE.PDR.BYTE | 0x8C;
#endif    // (MAX_TS == 32)

#if (MAX_TS == 24)
    /* TS1 = P31, TS2 = P30 */
    PORT3.PODR.BYTE = PORT3.PODR.BYTE & 0xF9;
    PORT3.PDR.BYTE  = PORT3.PDR.BYTE | 0x06;

    /* TS3 = P27, TS4 = P26 */
    PORT2.PODR.BYTE = PORT2.PODR.BYTE & 0x3F;
    PORT2.PDR.BYTE  = PORT2.PDR.BYTE | 0xC0;

    /* TS5 = P15, TS6 = P14 */
    PORT1.PODR.BYTE = PORT1.PODR.BYTE & 0xCF;
    PORT1.PDR.BYTE  = PORT1.PDR.BYTE | 0x30;

    /* TS7 = PH3, TS8 = PH2, TS9 = PH1, TS10 = PH0 */
    PORTH.PODR.BYTE = PORTH.PODR.BYTE & 0xF0;
    PORTH.PDR.BYTE  = PORTH.PDR.BYTE | 0x0F;

    /* TS13 = PC7, TS14 = PC6, TS15 = PC5, TSCAP = PC4 */
    PORTC.PODR.BYTE = PORTC.PODR.BYTE & 0x0F;
    PORTC.PDR.BYTE  = PORTC.PDR.BYTE | 0xF0;

    /* TS20 = PB5, TS22 = PB3, TS24 = PB1, TS25 = PB0 */
    PORTB.PODR.BYTE = PORTB.PODR.BYTE & 0xB4;
    PORTB.PDR.BYTE  = PORTB.PDR.BYTE | 0x2B;

    /* TS26 = PA6, TS28 = PA4, TS29 = PA3, TS31 = PA1 */
    PORTA.PODR.BYTE = PORTA.PODR.BYTE & 0xA5;
    PORTA.PDR.BYTE  = PORTA.PDR.BYTE | 0x5A;

    /* TS33 = PE4, TS34 = PE3, TS35 = PE2 */
    PORTE.PODR.BYTE = PORTE.PODR.BYTE & 0xE3;
    PORTE.PDR.BYTE  = PORTE.PDR.BYTE | 0x8C;
#endif    // (MAX_TS == 24)
#endif    // (MCU_SERIES_T == R5F5130)

}    /* End of function initial_port_set() */

/***********************************************************************************************************************
* Function Name: MPC_CTSU_set
* Description  : CTSU measurement pin function setting.
* Arguments    : uint16_t    sensor_ena0
*              : uint16_t    sensor_ena1
*              : uint16_t    sensor_ena2
* Return Value : None
***********************************************************************************************************************/
void MPC_CTSU_set( uint16_t sensor_ena0, uint16_t sensor_ena1, uint16_t sensor_ena2 )
{
    /* Port functon change protect off setting */
    MPC.PWPR.BIT.B0WI  = OFF;
    MPC.PWPR.BIT.PFSWE = ON;

#if (MCU_SERIES_T == R5F5113)

    /* Pin function is set in touch sensor */
    if (0x0001 == (sensor_ena0 & 0x0001))
    {
        MPC.P07PFS.BYTE  = P07PFS_TS0;
        PORT0.PMR.BIT.B7 = 1;
    }

    if (0x0002 == (sensor_ena0 & 0x0002))
    {
        MPC.P04PFS.BYTE  = P04PFS_TS1;
        PORT0.PMR.BIT.B4 = 1;
    }

    if (0x0004 == (sensor_ena0 & 0x0004))
    {
        MPC.P02PFS.BYTE  = P02PFS_TS2;
        PORT0.PMR.BIT.B2 = 1;
    }

    if (0x0008 == (sensor_ena0 & 0x0008))
    {
        MPC.PJ3PFS.BYTE  = PJ3PFS_TS3;
        PORTJ.PMR.BIT.B3 = 1;
    }

    if (0x0010 == (sensor_ena0 & 0x0010))
    {
        MPC.P25PFS.BYTE  = P25PFS_TS4;
        PORT2.PMR.BIT.B5 = 1;
    }

    if (0x0020 == (sensor_ena0 & 0x0020))
    {
        MPC.P24PFS.BYTE  = P24PFS_TS5;
        PORT2.PMR.BIT.B4 = 1;
    }

    if (0x0040 == (sensor_ena0 & 0x0040))
    {
        MPC.P23PFS.BYTE  = P23PFS_TS6;
        PORT2.PMR.BIT.B3 = 1;
    }

    if (0x0080 == (sensor_ena0 & 0x0080))
    {
        MPC.P22PFS.BYTE  = P22PFS_TS7;
        PORT2.PMR.BIT.B2 = 1;
    }

    if (0x0100 == (sensor_ena0 & 0x0100))
    {
        MPC.P21PFS.BYTE  = P21PFS_TS8;
        PORT2.PMR.BIT.B1 = 1;
    }

    if (0x0200 == (sensor_ena0 & 0x0200))
    {
        MPC.P20PFS.BYTE  = P20PFS_TS9;
        PORT2.PMR.BIT.B0 = 1;
    }

    if (0x0400 == (sensor_ena0 & 0x0400))
    {
        MPC.P27PFS.BYTE  = P27PFS_TS10;
        PORT2.PMR.BIT.B7 = 1;
    }

    if (0x0800 == (sensor_ena0 & 0x0800))
    {
        MPC.P32PFS.BYTE  = P32PFS_TS11;
        PORT3.PMR.BIT.B2 = 1;
    }

    if (0x0000 != sensor_ena0)
    {
        MPC.P26PFS.BYTE  = P26PFS_TSCAP;
        PORT2.PMR.BIT.B6 = 1;
    }
#endif    // (MCU_SERIES_T == R5F5113)

#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)
#if (MAX_TS == 36)

    /* Pin function is set in touch sensor */
    if (0x0001 == (sensor_ena0 & 0x0001))
    {
        MPC.P34PFS.BYTE  = P34PFS_TS0;
        PORT3.PMR.BIT.B4 = 1;
    }

    if (0x0002 == (sensor_ena0 & 0x0002))
    {
        MPC.P33PFS.BYTE  = P33PFS_TS1;
        PORT3.PMR.BIT.B3 = 1;
    }

    if (0x0004 == (sensor_ena0 & 0x0004))
    {
        MPC.P27PFS.BYTE  = P27PFS_TS2;
        PORT2.PMR.BIT.B7 = 1;
    }

    if (0x0008 == (sensor_ena0 & 0x0008))
    {
        MPC.P26PFS.BYTE  = P26PFS_TS3;
        PORT2.PMR.BIT.B6 = 1;
    }

    if (0x0010 == (sensor_ena0 & 0x0010))
    {
        MPC.P25PFS.BYTE  = P25PFS_TS4;
        PORT2.PMR.BIT.B5 = 1;
    }

    if (0x0020 == (sensor_ena0 & 0x0020))
    {
        MPC.P24PFS.BYTE  = P24PFS_TS5;
        PORT2.PMR.BIT.B4 = 1;
    }

    if (0x0040 == (sensor_ena0 & 0x0040))
    {
        MPC.P23PFS.BYTE  = P23PFS_TS6;
        PORT2.PMR.BIT.B3 = 1;
    }

    if (0x0080 == (sensor_ena0 & 0x0080))
    {
        MPC.P22PFS.BYTE  = P22PFS_TS7;
        PORT2.PMR.BIT.B2 = 1;
    }

    if (0x0100 == (sensor_ena0 & 0x0100))
    {
        MPC.P21PFS.BYTE  = P21PFS_TS8;
        PORT2.PMR.BIT.B1 = 1;
    }

    if (0x0200 == (sensor_ena0 & 0x0200))
    {
        MPC.P20PFS.BYTE  = P20PFS_TS9;
        PORT2.PMR.BIT.B0 = 1;
    }

    /* There is no TS10 */
    /* There is no TS11 */

    if (0x1000 == (sensor_ena0 & 0x1000))
    {
        MPC.P15PFS.BYTE  = P15PFS_TS12;
        PORT1.PMR.BIT.B5 = 1;
    }

    if (0x2000 == (sensor_ena0 & 0x2000))
    {
        MPC.P14PFS.BYTE  = P14PFS_TS13;
        PORT1.PMR.BIT.B4 = 1;
    }

    /* There is no TS14 */

    if (0x8000 == (sensor_ena0 & 0x8000))
    {
        MPC.P55PFS.BYTE  = P55PFS_TS15;
        PORT5.PMR.BIT.B5 = 1;
    }

    /*===== TS16-TS31 =====*/
    if (0x0001 == (sensor_ena1 & 0x0001))
    {
        MPC.P54PFS.BYTE  = P54PFS_TS16;
        PORT5.PMR.BIT.B4 = 1;
    }

    if (0x0002 == (sensor_ena1 & 0x0002))
    {
        MPC.P53PFS.BYTE  = P53PFS_TS17;
        PORT5.PMR.BIT.B3 = 1;
    }

    if (0x0004 == (sensor_ena1 & 0x0004))
    {
        MPC.P52PFS.BYTE  = P52PFS_TS18;
        PORT5.PMR.BIT.B2 = 1;
    }

    if (0x0008 == (sensor_ena1 & 0x0008))
    {
        MPC.P51PFS.BYTE  = P51PFS_TS19;
        PORT5.PMR.BIT.B1 = 1;
    }

    if (0x0010 == (sensor_ena1 & 0x0010))
    {
        MPC.P50PFS.BYTE  = P50PFS_TS20;
        PORT5.PMR.BIT.B0 = 1;
    }

    /* There is no TS21 */

    if (0x0040 == (sensor_ena1 & 0x0040))
    {
        MPC.PC6PFS.BYTE  = PC6PFS_TS22;
        PORTC.PMR.BIT.B6 = 1;
    }

    if (0x0080 == (sensor_ena1 & 0x0080))
    {
        MPC.PC5PFS.BYTE  = PC5PFS_TS23;
        PORTC.PMR.BIT.B5 = 1;
    }

    /* There is no TS24 */
    /* There is no TS25 */
    /* There is no TS26 */

    if (0x0800 == (sensor_ena1 & 0x0800))
    {
        MPC.PC3PFS.BYTE  = PC3PFS_TS27;
        PORTC.PMR.BIT.B3 = 1;
    }

    /* There is no TS28 */
    /* There is no TS29 */

    if (0x4000 == (sensor_ena1 & 0x4000))
    {
        MPC.PC2PFS.BYTE  = PC2PFS_TS30;
        PORTC.PMR.BIT.B2 = 1;
    }

    /* There is no TS31 */

    /*===== TS32-TS35 =====*/

    /* There is no TS32 */

    if (0x0002 == (sensor_ena2 & 0x0002))
    {
        MPC.PC1PFS.BYTE  = PC1PFS_TS33;
        PORTC.PMR.BIT.B1 = 1;
    }

    /* There is no TS34 */

    if (0x0008 == (sensor_ena2 & 0x0008))
    {
        MPC.PC0PFS.BYTE  = PC0PFS_TS35;
        PORTC.PMR.BIT.B0 = 1;
    }

    if ((0x0000 != sensor_ena0) || (0x0000 != sensor_ena1) || (0x0000 != sensor_ena2))
    {
        MPC.PC4PFS.BYTE  = PC4PFS_TSCAP;
        PORTC.PMR.BIT.B4 = 1;
    }
#endif    // (MAX_TS == 36)

#if (MAX_TS == 31)

    if (0x0004 == (sensor_ena0 & 0x0004))
    {
        MPC.P27PFS.BYTE  = P27PFS_TS2;
        PORT2.PMR.BIT.B7 = 1;
    }

    if (0x0008 == (sensor_ena0 & 0x0008))
    {
        MPC.P26PFS.BYTE  = P26PFS_TS3;
        PORT2.PMR.BIT.B6 = 1;
    }

    if (0x1000 == (sensor_ena0 & 0x1000))
    {
        MPC.P15PFS.BYTE  = P15PFS_TS12;
        PORT1.PMR.BIT.B5 = 1;
    }

    if (0x2000 == (sensor_ena0 & 0x2000))
    {
        MPC.P14PFS.BYTE  = P14PFS_TS13;
        PORT1.PMR.BIT.B4 = 1;
    }

    if (0x8000 == (sensor_ena0 & 0x8000))
    {
        MPC.P55PFS.BYTE  = P55PFS_TS15;
        PORT5.PMR.BIT.B5 = 1;
    }

    if (0x0001 == (sensor_ena1 & 0x0001))
    {
        MPC.P54PFS.BYTE  = P54PFS_TS16;
        PORT5.PMR.BIT.B4 = 1;
    }

    if (0x0040 == (sensor_ena1 & 0x0040))
    {
        MPC.PC6PFS.BYTE  = PC6PFS_TS22;
        PORTC.PMR.BIT.B6 = 1;
    }

    if (0x0080 == (sensor_ena1 & 0x0080))
    {
        MPC.PC5PFS.BYTE  = PC5PFS_TS23;
        PORTC.PMR.BIT.B5 = 1;
    }

    if (0x0800 == (sensor_ena1 & 0x0800))
    {
        MPC.PC3PFS.BYTE  = PC3PFS_TS27;
        PORTC.PMR.BIT.B3 = 1;
    }

    if (0x4000 == (sensor_ena1 & 0x4000))
    {
        MPC.PC2PFS.BYTE  = PC2PFS_TS30;
        PORTC.PMR.BIT.B2 = 1;
    }

    if ((0x0000 != sensor_ena0) || (0x0000 != sensor_ena1) || (0x0000 != sensor_ena2))
    {
        MPC.PC4PFS.BYTE  = PC4PFS_TSCAP;
        PORTC.PMR.BIT.B4 = 1;
    }
#endif    // (MAX_TS == 31)

#if (MAX_TS == 24)

    if (0x0004 == (sensor_ena0 & 0x0004))
    {
        MPC.P27PFS.BYTE  = P27PFS_TS2;
        PORT2.PMR.BIT.B7 = 1;
    }

    if (0x0008 == (sensor_ena0 & 0x0008))
    {
        MPC.P26PFS.BYTE  = P26PFS_TS3;
        PORT2.PMR.BIT.B6 = 1;
    }

    if (0x1000 == (sensor_ena0 & 0x1000))
    {
        MPC.P15PFS.BYTE  = P15PFS_TS12;
        PORT1.PMR.BIT.B5 = 1;
    }

    if (0x2000 == (sensor_ena0 & 0x2000))
    {
        MPC.P14PFS.BYTE  = P14PFS_TS13;
        PORT1.PMR.BIT.B4 = 1;
    }

    if (0x0040 == (sensor_ena1 & 0x0040))
    {
        MPC.PC6PFS.BYTE  = PC6PFS_TS22;
        PORTC.PMR.BIT.B6 = 1;
    }

    if (0x0080 == (sensor_ena1 & 0x0080))
    {
        MPC.PC5PFS.BYTE  = PC5PFS_TS23;
        PORTC.PMR.BIT.B5 = 1;
    }

    if ((0x0000 != sensor_ena0) || (0x0000 != sensor_ena1) || (0x0000 != sensor_ena2))
    {
        MPC.PC4PFS.BYTE  = PC4PFS_TSCAP;
        PORTC.PMR.BIT.B4 = 1;
    }
#endif    // (MAX_TS == 24)
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)

#if (MCU_SERIES_T == R5F5130)
#if (MAX_TS == 36)

    /* Pin function is set in touch sensor */
    if (0x0001 == (sensor_ena0 & 0x0001))
    {
        MPC.P32PFS.BYTE  = P32PFS_TS0;
        PORT3.PMR.BIT.B2 = 1;
    }

    if (0x0002 == (sensor_ena0 & 0x0002))
    {
        MPC.P31PFS.BYTE  = P31PFS_TS1;
        PORT3.PMR.BIT.B1 = 1;
    }

    if (0x0004 == (sensor_ena0 & 0x0004))
    {
        MPC.P30PFS.BYTE  = P30PFS_TS2;
        PORT3.PMR.BIT.B0 = 1;
    }

    if (0x0008 == (sensor_ena0 & 0x0008))
    {
        MPC.P27PFS.BYTE  = P27PFS_TS3;
        PORT2.PMR.BIT.B7 = 1;
    }

    if (0x0010 == (sensor_ena0 & 0x0010))
    {
        MPC.P26PFS.BYTE  = P26PFS_TS4;
        PORT2.PMR.BIT.B6 = 1;
    }

    if (0x0020 == (sensor_ena0 & 0x0020))
    {
        MPC.P15PFS.BYTE  = P15PFS_TS5;
        PORT1.PMR.BIT.B5 = 1;
    }

    if (0x0040 == (sensor_ena0 & 0x0040))
    {
        MPC.P14PFS.BYTE  = P14PFS_TS6;
        PORT1.PMR.BIT.B4 = 1;
    }

    if (0x0080 == (sensor_ena0 & 0x0080))
    {
        MPC.PH3PFS.BYTE  = PH3PFS_TS7;
        PORTH.PMR.BIT.B3 = 1;
    }

    if (0x0100 == (sensor_ena0 & 0x0100))
    {
        MPC.PH2PFS.BYTE  = PH2PFS_TS8;
        PORTH.PMR.BIT.B2 = 1;
    }

    if (0x0200 == (sensor_ena0 & 0x0200))
    {
        MPC.PH1PFS.BYTE  = PH1PFS_TS9;
        PORTH.PMR.BIT.B1 = 1;
    }

    if (0x0400 == (sensor_ena0 & 0x0400))
    {
        MPC.PH0PFS.BYTE  = PH0PFS_TS10;
        PORTH.PMR.BIT.B0 = 1;
    }

    if (0x0800 == (sensor_ena0 & 0x0800))
    {
        MPC.P55PFS.BYTE  = P55PFS_TS11;
        PORT5.PMR.BIT.B5 = 1;
    }

    if (0x1000 == (sensor_ena0 & 0x1000))
    {
        MPC.P54PFS.BYTE  = P54PFS_TS12;
        PORT5.PMR.BIT.B4 = 1;
    }

    if (0x2000 == (sensor_ena0 & 0x2000))
    {
        MPC.PC7PFS.BYTE  = PC7PFS_TS13;
        PORTC.PMR.BIT.B7 = 1;
    }

    if (0x4000 == (sensor_ena0 & 0x4000))
    {
        MPC.PC6PFS.BYTE  = PC6PFS_TS14;
        PORTC.PMR.BIT.B6 = 1;
    }

    if (0x8000 == (sensor_ena0 & 0x8000))
    {
        MPC.PC5PFS.BYTE  = PC5PFS_TS15;
        PORTC.PMR.BIT.B5 = 1;
    }

    /*===== TS16-TS31 =====*/
    if (0x0001 == (sensor_ena1 & 0x0001))
    {
        MPC.PC3PFS.BYTE  = PC3PFS_TS16;
        PORTC.PMR.BIT.B3 = 1;
    }

    if (0x0002 == (sensor_ena1 & 0x0002))
    {
        MPC.PC2PFS.BYTE  = PC2PFS_TS17;
        PORTC.PMR.BIT.B2 = 1;
    }

    if (0x0004 == (sensor_ena1 & 0x0004))
    {
        MPC.PB7PFS.BYTE  = PB7PFS_TS18;
        PORTB.PMR.BIT.B7 = 1;
    }

    if (0x0008 == (sensor_ena1 & 0x0008))
    {
        MPC.PB6PFS.BYTE  = PB6PFS_TS19;
        PORTB.PMR.BIT.B6 = 1;
    }

    if (0x0010 == (sensor_ena1 & 0x0010))
    {
        MPC.PB5PFS.BYTE  = PB5PFS_TS20;
        PORTB.PMR.BIT.B5 = 1;
    }

    if (0x0020 == (sensor_ena1 & 0x0020))
    {
        MPC.PB4PFS.BYTE  = PB4PFS_TS21;
        PORTB.PMR.BIT.B4 = 1;
    }

    if (0x0040 == (sensor_ena1 & 0x0040))
    {
        MPC.PB3PFS.BYTE  = PB3PFS_TS22;
        PORTB.PMR.BIT.B3 = 1;
    }

    if (0x0080 == (sensor_ena1 & 0x0080))
    {
        MPC.PB2PFS.BYTE  = PB2PFS_TS23;
        PORTB.PMR.BIT.B2 = 1;
    }

    if (0x0100 == (sensor_ena1 & 0x0100))
    {
        MPC.PB1PFS.BYTE  = PB1PFS_TS24;
        PORTB.PMR.BIT.B1 = 1;
    }

    if (0x0200 == (sensor_ena1 & 0x0200))
    {
        MPC.PB0PFS.BYTE  = PB0PFS_TS25;
        PORTB.PMR.BIT.B0 = 1;
    }

    if (0x0400 == (sensor_ena1 & 0x0400))
    {
        MPC.PA6PFS.BYTE  = PA6PFS_TS26;
        PORTA.PMR.BIT.B6 = 1;
    }

    if (0x0800 == (sensor_ena1 & 0x0800))
    {
        MPC.PA5PFS.BYTE  = PA5PFS_TS27;
        PORTA.PMR.BIT.B5 = 1;
    }

    if (0x1000 == (sensor_ena1 & 0x1000))
    {
        MPC.PA4PFS.BYTE  = PA4PFS_TS28;
        PORTA.PMR.BIT.B4 = 1;
    }

    if (0x2000 == (sensor_ena1 & 0x2000))
    {
        MPC.PA3PFS.BYTE  = PA3PFS_TS29;
        PORTA.PMR.BIT.B3 = 1;
    }

    if (0x4000 == (sensor_ena1 & 0x4000))
    {
        MPC.PA2PFS.BYTE  = PA2PFS_TS30;
        PORTA.PMR.BIT.B2 = 1;
    }

    if (0x8000 == (sensor_ena1 & 0x8000))
    {
        MPC.PA1PFS.BYTE  = PA1PFS_TS31;
        PORTA.PMR.BIT.B1 = 1;
    }

    /*===== TS32-TS35 =====*/

    if (0x0001 == (sensor_ena2 & 0x0001))
    {
        MPC.PA0PFS.BYTE  = PA0PFS_TS32;
        PORTA.PMR.BIT.B0 = 1;
    }

    if (0x0002 == (sensor_ena2 & 0x0002))
    {
        MPC.PE4PFS.BYTE  = PE4PFS_TS33;
        PORTE.PMR.BIT.B4 = 1;
    }

    if (0x0004 == (sensor_ena2 & 0x0004))
    {
        MPC.PE3PFS.BYTE  = PE3PFS_TS34;
        PORTE.PMR.BIT.B3 = 1;
    }

    if (0x0008 == (sensor_ena2 & 0x0008))
    {
        MPC.PE2PFS.BYTE  = PE2PFS_TS35;
        PORTE.PMR.BIT.B2 = 1;
    }

    if ((0x0000 != sensor_ena0) || (0x0000 != sensor_ena1) || (0x0000 != sensor_ena2))
    {
        MPC.PC4PFS.BYTE  = PC4PFS_TSCAP;
        PORTC.PMR.BIT.B4 = 1;
    }
#endif    // (MAX_TS == 36)

#if (MAX_TS == 32)

/* Pin function is set in touch sensor */
    if (0x0001 == (sensor_ena0 & 0x0001))
    {
        MPC.P32PFS.BYTE  = P32PFS_TS0;
        PORT3.PMR.BIT.B2 = 1;
    }

    if (0x0002 == (sensor_ena0 & 0x0002))
    {
        MPC.P31PFS.BYTE  = P31PFS_TS1;
        PORT3.PMR.BIT.B1 = 1;
    }

    if (0x0004 == (sensor_ena0 & 0x0004))
    {
        MPC.P30PFS.BYTE  = P30PFS_TS2;
        PORT3.PMR.BIT.B0 = 1;
    }

    if (0x0008 == (sensor_ena0 & 0x0008))
    {
        MPC.P27PFS.BYTE  = P27PFS_TS3;
        PORT2.PMR.BIT.B7 = 1;
    }

    if (0x0010 == (sensor_ena0 & 0x0010))
    {
        MPC.P26PFS.BYTE  = P26PFS_TS4;
        PORT2.PMR.BIT.B6 = 1;
    }

    if (0x0020 == (sensor_ena0 & 0x0020))
    {
        MPC.P15PFS.BYTE  = P15PFS_TS5;
        PORT1.PMR.BIT.B5 = 1;
    }

    if (0x0040 == (sensor_ena0 & 0x0040))
    {
        MPC.P14PFS.BYTE  = P14PFS_TS6;
        PORT1.PMR.BIT.B4 = 1;
    }

    if (0x0080 == (sensor_ena0 & 0x0080))
    {
        MPC.PH3PFS.BYTE  = PH3PFS_TS7;
        PORTH.PMR.BIT.B3 = 1;
    }

    if (0x0100 == (sensor_ena0 & 0x0100))
    {
        MPC.PH2PFS.BYTE  = PH2PFS_TS8;
        PORTH.PMR.BIT.B2 = 1;
    }

    if (0x0200 == (sensor_ena0 & 0x0200))
    {
        MPC.PH1PFS.BYTE  = PH1PFS_TS9;
        PORTH.PMR.BIT.B1 = 1;
    }

    if (0x0400 == (sensor_ena0 & 0x0400))
    {
        MPC.PH0PFS.BYTE  = PH0PFS_TS10;
        PORTH.PMR.BIT.B0 = 1;
    }

    if (0x0800 == (sensor_ena0 & 0x0800))
    {
        MPC.P55PFS.BYTE  = P55PFS_TS11;
        PORT5.PMR.BIT.B5 = 1;
    }

    if (0x1000 == (sensor_ena0 & 0x1000))
    {
        MPC.P54PFS.BYTE  = P54PFS_TS12;
        PORT5.PMR.BIT.B4 = 1;
    }

    if (0x2000 == (sensor_ena0 & 0x2000))
    {
        MPC.PC7PFS.BYTE  = PC7PFS_TS13;
        PORTC.PMR.BIT.B7 = 1;
    }

    if (0x4000 == (sensor_ena0 & 0x4000))
    {
        MPC.PC6PFS.BYTE  = PC6PFS_TS14;
        PORTC.PMR.BIT.B6 = 1;
    }

    if (0x8000 == (sensor_ena0 & 0x8000))
    {
        MPC.PC5PFS.BYTE  = PC5PFS_TS15;
        PORTC.PMR.BIT.B5 = 1;
    }

    /*===== TS16-TS31 =====*/
    if (0x0001 == (sensor_ena1 & 0x0001))
    {
        MPC.PC3PFS.BYTE  = PC3PFS_TS16;
        PORTC.PMR.BIT.B3 = 1;
    }

    if (0x0002 == (sensor_ena1 & 0x0002))
    {
        MPC.PC2PFS.BYTE  = PC2PFS_TS17;
        PORTC.PMR.BIT.B2 = 1;
    }

    if (0x0004 == (sensor_ena1 & 0x0004))
    {
        MPC.PB7PFS.BYTE  = PB7PFS_TS18;
        PORTB.PMR.BIT.B7 = 1;
    }

    if (0x0008 == (sensor_ena1 & 0x0008))
    {
        MPC.PB6PFS.BYTE  = PB6PFS_TS19;
        PORTB.PMR.BIT.B6 = 1;
    }

    if (0x0010 == (sensor_ena1 & 0x0010))
    {
        MPC.PB5PFS.BYTE  = PB5PFS_TS20;
        PORTB.PMR.BIT.B5 = 1;
    }

    /* There is no TS21 */

    if (0x0040 == (sensor_ena1 & 0x0040))
    {
        MPC.PB3PFS.BYTE  = PB3PFS_TS22;
        PORTB.PMR.BIT.B3 = 1;
    }

    /* There is no TS23 */

    if (0x0100 == (sensor_ena1 & 0x0100))
    {
        MPC.PB1PFS.BYTE  = PB1PFS_TS24;
        PORTB.PMR.BIT.B1 = 1;
    }

    if (0x0200 == (sensor_ena1 & 0x0200))
    {
        MPC.PB0PFS.BYTE  = PB0PFS_TS25;
        PORTB.PMR.BIT.B0 = 1;
    }

    if (0x0400 == (sensor_ena1 & 0x0400))
    {
        MPC.PA6PFS.BYTE  = PA6PFS_TS26;
        PORTA.PMR.BIT.B6 = 1;
    }

    /* There is no TS27 */

    if (0x1000 == (sensor_ena1 & 0x1000))
    {
        MPC.PA4PFS.BYTE  = PA4PFS_TS28;
        PORTA.PMR.BIT.B4 = 1;
    }

    if (0x2000 == (sensor_ena1 & 0x2000))
    {
        MPC.PA3PFS.BYTE  = PA3PFS_TS29;
        PORTA.PMR.BIT.B3 = 1;
    }

    /* There is no TS30 */

    if (0x8000 == (sensor_ena1 & 0x8000))
    {
        MPC.PA1PFS.BYTE  = PA1PFS_TS31;
        PORTA.PMR.BIT.B1 = 1;
    }

    /*===== TS32-TS35 =====*/

    if (0x0001 == (sensor_ena2 & 0x0001))
    {
        MPC.PA0PFS.BYTE  = PA0PFS_TS32;
        PORTA.PMR.BIT.B0 = 1;
    }

    if (0x0002 == (sensor_ena2 & 0x0002))
    {
        MPC.PE4PFS.BYTE  = PE4PFS_TS33;
        PORTE.PMR.BIT.B4 = 1;
    }

    if (0x0004 == (sensor_ena2 & 0x0004))
    {
        MPC.PE3PFS.BYTE  = PE3PFS_TS34;
        PORTE.PMR.BIT.B3 = 1;
    }

    if (0x0008 == (sensor_ena2 & 0x0008))
    {
        MPC.PE2PFS.BYTE  = PE2PFS_TS35;
        PORTE.PMR.BIT.B2 = 1;
    }

    if ((0x0000 != sensor_ena0) || (0x0000 != sensor_ena1) || (0x0000 != sensor_ena2))
    {
        MPC.PC4PFS.BYTE  = PC4PFS_TSCAP;
        PORTC.PMR.BIT.B4 = 1;
    }
#endif    // (MAX_TS == 32)

#if (MAX_TS == 24)

    /* Pin function is set in touch sensor */

    /* There is no TS0 */

    if (0x0002 == (sensor_ena0 & 0x0002))
    {
        MPC.P31PFS.BYTE  = P31PFS_TS1;
        PORT3.PMR.BIT.B1 = 1;
    }

    if (0x0004 == (sensor_ena0 & 0x0004))
    {
        MPC.P30PFS.BYTE  = P30PFS_TS2;
        PORT3.PMR.BIT.B0 = 1;
    }

    if (0x0008 == (sensor_ena0 & 0x0008))
    {
        MPC.P27PFS.BYTE  = P27PFS_TS3;
        PORT2.PMR.BIT.B7 = 1;
    }

    if (0x0010 == (sensor_ena0 & 0x0010))
    {
        MPC.P26PFS.BYTE  = P26PFS_TS4;
        PORT2.PMR.BIT.B6 = 1;
    }

    if (0x0020 == (sensor_ena0 & 0x0020))
    {
        MPC.P15PFS.BYTE  = P15PFS_TS5;
        PORT1.PMR.BIT.B5 = 1;
    }

    if (0x0040 == (sensor_ena0 & 0x0040))
    {
        MPC.P14PFS.BYTE  = P14PFS_TS6;
        PORT1.PMR.BIT.B4 = 1;
    }

    if (0x0080 == (sensor_ena0 & 0x0080))
    {
        MPC.PH3PFS.BYTE  = PH3PFS_TS7;
        PORTH.PMR.BIT.B3 = 1;
    }

    if (0x0100 == (sensor_ena0 & 0x0100))
    {
        MPC.PH2PFS.BYTE  = PH2PFS_TS8;
        PORTH.PMR.BIT.B2 = 1;
    }

    if (0x0200 == (sensor_ena0 & 0x0200))
    {
        MPC.PH1PFS.BYTE  = PH1PFS_TS9;
        PORTH.PMR.BIT.B1 = 1;
    }

    if (0x0400 == (sensor_ena0 & 0x0400))
    {
        MPC.PH0PFS.BYTE  = PH0PFS_TS10;
        PORTH.PMR.BIT.B0 = 1;
    }

    /* There is no TS11 */
    /* There is no TS12 */

    if (0x2000 == (sensor_ena0 & 0x2000))
    {
        MPC.PC7PFS.BYTE  = PC7PFS_TS13;
        PORTC.PMR.BIT.B7 = 1;
    }

    if (0x4000 == (sensor_ena0 & 0x4000))
    {
        MPC.PC6PFS.BYTE  = PC6PFS_TS14;
        PORTC.PMR.BIT.B6 = 1;
    }

    if (0x8000 == (sensor_ena0 & 0x8000))
    {
        MPC.PC5PFS.BYTE  = PC5PFS_TS15;
        PORTC.PMR.BIT.B5 = 1;
    }

    /*===== TS16-TS31 =====*/

    /* There is no TS16 */
    /* There is no TS17 */
    /* There is no TS18 */
    /* There is no TS19 */

    if (0x0010 == (sensor_ena1 & 0x0010))
    {
        MPC.PB5PFS.BYTE  = PB5PFS_TS20;
        PORTB.PMR.BIT.B5 = 1;
    }

    /* There is no TS21 */

    if (0x0040 == (sensor_ena1 & 0x0040))
    {
        MPC.PB3PFS.BYTE  = PB3PFS_TS22;
        PORTB.PMR.BIT.B3 = 1;
    }

    /* There is no TS23 */

    if (0x0100 == (sensor_ena1 & 0x0100))
    {
        MPC.PB1PFS.BYTE  = PB1PFS_TS24;
        PORTB.PMR.BIT.B1 = 1;
    }

    if (0x0200 == (sensor_ena1 & 0x0200))
    {
        MPC.PB0PFS.BYTE  = PB0PFS_TS25;
        PORTB.PMR.BIT.B0 = 1;
    }

    if (0x0400 == (sensor_ena1 & 0x0400))
    {
        MPC.PA6PFS.BYTE  = PA6PFS_TS26;
        PORTA.PMR.BIT.B6 = 1;
    }

    /* There is no TS27 */

    if (0x1000 == (sensor_ena1 & 0x1000))
    {
        MPC.PA4PFS.BYTE  = PA4PFS_TS28;
        PORTA.PMR.BIT.B4 = 1;
    }

    if (0x2000 == (sensor_ena1 & 0x2000))
    {
        MPC.PA3PFS.BYTE  = PA3PFS_TS29;
        PORTA.PMR.BIT.B3 = 1;
    }

    /* There is no TS30 */

    if (0x8000 == (sensor_ena1 & 0x8000))
    {
        MPC.PA1PFS.BYTE  = PA1PFS_TS31;
        PORTA.PMR.BIT.B1 = 1;
    }

    /*===== TS32-TS35 =====*/

    /* There is no TS32 */

    if (0x0002 == (sensor_ena2 & 0x0002))
    {
        MPC.PE4PFS.BYTE  = PE4PFS_TS33;
        PORTE.PMR.BIT.B4 = 1;
    }

    if (0x0004 == (sensor_ena2 & 0x0004))
    {
        MPC.PE3PFS.BYTE  = PE3PFS_TS34;
        PORTE.PMR.BIT.B3 = 1;
    }

    if (0x0008 == (sensor_ena2 & 0x0008))
    {
        MPC.PE2PFS.BYTE  = PE2PFS_TS35;
        PORTE.PMR.BIT.B2 = 1;
    }

    if ((0x0000 != sensor_ena0) || (0x0000 != sensor_ena1) || (0x0000 != sensor_ena2))
    {
        MPC.PC4PFS.BYTE  = PC4PFS_TSCAP;
        PORTC.PMR.BIT.B4 = 1;
    }
#endif    // (MAX_TS == 24)
#endif    // (MCU_SERIES_T == R5F5130)
}

/***********************************************************************************************************************
    END OF TEXT
***********************************************************************************************************************/
