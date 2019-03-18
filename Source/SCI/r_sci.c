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
* File Name    : r_sci.c
* Version      : 1.00
* Device(s)    : R5F5113xAxFP,R5F5231xAxFP,R5F51305AxFN
* Description  : This file transmits the touch measurement data to the Workbench6. 
***********************************************************************************************************************/

/***********************************************************************************************************************
* History      : DD.MM.YYYY Version    Description
*              : xx.xx.2015   1.00     First Release
***********************************************************************************************************************/
#define __R_SCI_C__

/***********************************************************************************************************************
* Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
* Includes
***********************************************************************************************************************/
/* System include header */
#include "r_cg_macrodriver.h"

/* H/W include header */
#include "iodefine.h"
#include "r_mpc.h"
#include "r_dtc.h"
#include "r_ctsu.h"
#include "r_cgc.h"
#ifdef  SCI_SERIAL_USE
    #include "r_sci.h"
#endif  // SCI_SERIAL_USE

/* S/W include header */
#include "r_touch.h"
#include "r_serial_control.h"

/***********************************************************************************************************************
* Macro definitions
***********************************************************************************************************************/
#define MCU_MODEL_R5F51303AxFK           (1)         /* Definition for R5F51303AxFK compiling options                 */
#define MCU_MODEL_R5F51303AxFL           (2)         /* Definition for R5F51303AxFL compiling options                 */
#define MCU_MODEL_R5F51303AxFM           (3)         /* Definition for R5F51303AxFM compiling options                 */
#define MCU_MODEL_R5F51303AxFN           (4)         /* Definition for R5F51303AxFN compiling options                 */
#define MCU_MODEL_R5F51303AxNE           (5)         /* Definition for R5F51303AxNE compiling options                 */
#define MCU_MODEL_R5F51305AxFK           (6)         /* Definition for R5F51305AxFK compiling options                 */
#define MCU_MODEL_R5F51305AxFL           (7)         /* Definition for R5F51305AxFL compiling options                 */
#define MCU_MODEL_R5F51305AxFM           (8)         /* Definition for R5F51305AxFM compiling options                 */
#define MCU_MODEL_R5F51305AxFN           (9)         /* Definition for R5F51305AxFN compiling options                 */
#define MCU_MODEL_R5F51305AxNE           (10)        /* Definition for R5F51305AxNE compiling options                 */


/***********************************************************************************************************************
* Global variables and functions
***********************************************************************************************************************/

#ifdef  SCI_SERIAL_USE
/***********************************************************************************************************************
* Function Name: R_SCI6_Create
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Create(void)
{
    SYSTEM.PRCR.WORD             = PRCR1_ENA;              /* Enables writing to the registers  */
    SYSTEM.MSTPCRB.BIT.MSTPB25   = 0;                      /* SCI6 module stop mode release     */
    SYSTEM.PRCR.WORD             = PRCR1_DIS;              /* Disables writing to the registers */

//    ICU.IPR[].BIT.IPR = 5;                  /* Interrupt Source Priority Register    */
//    IPR(SCI6, RXI6) = 3;
    IPR(SCI6, ERI6) = 15;

    /* Serial Control Register (SCR) **********************************************************************************/
    /* bit7    Transmit Interrupt Enable (TIE)                                                                        */
    /* bit6    Receive Interrupt Enable (RIE)                                                                         */
    /* bit5    Transmit Enable (TE)                                                                                   */
    /* bit4    Receive Enable (RE)                                                                                    */
    /* bit3    Multi-Processor Interrupt Enable (MPIE)                                                                */
    /* bit2    Transmit End Interrupt Enable (TEIE)                                                                   */
    /* bit1-0  Clock Enable (CKE)                                                                                     */
    /******************************************************************************************************************/
    SCI6.SCR.BYTE    = 0x00;                                          /* Clear the SCR.TIE, RIE, TE, RE and TEIE bits */

    /* PDn Pin Function Control Registers (PBnPFS) ********************************************************************/
    /* bit7    Reserved                                                                                               */
    /* bit6    Interrupt Input Function Select (ISEL)                                                                 */
    /* bit5    Reserved                                                                                               */
    /* bit4-0  Pin Input/Output Function (PSEL)                                                                       */
    /******************************************************************************************************************/
#if (MCU_SERIES_T == R5F5113)
    MPC.PB0PFS.BYTE  = 0x0B;                                          /* PB0 = SCI6 TXD6 function setting             */
    PORTB.PMR.BYTE  |= 0x01;

    MPC.PB1PFS.BYTE  = 0x0B;                                          /* PB1 = SCI6 RXD6 function setting             */
    PORTB.PODR.BYTE |= 0x02;

    PORTB.PDR.BYTE  |= 0x02;
    PORTB.PMR.BYTE  |= 0x02;
#endif    // (MCU_SERIES_T == R5F5113)
#if (MCU_SERIES_T == R5F5130)
  #if (MCU_MODEL == MCU_MODEL_R5F51303AxFN || MCU_MODEL == MCU_MODEL_R5F51305AxFN)
    MPC.PD0PFS.BYTE  = 0x0B;                                          /* PD0 = SCI6 TXD6 function setting             */
    PORTD.PMR.BYTE  |= 0x01;

    MPC.PD1PFS.BYTE  = 0x0B;                                          /* PD1 = SCI6 RXD6 function setting             */
    PORTD.PODR.BYTE |= 0x02;

    PORTD.PDR.BYTE  |= 0x02;
    PORTD.PMR.BYTE  |= 0x02;
  #else     // (MCU_MODEL == MCU_MODEL_R5F51303AxFN || MCU_MODEL == MCU_MODEL_R5F51305AxFN)
    MPC.PB1PFS.BYTE  = 0x0B;                                          /* PB1 = SCI6 TXD6 function setting             */
    PORTB.PMR.BYTE  |= 0x02;

    MPC.PB0PFS.BYTE  = 0x0B;                                          /* PB0 = SCI6 RXD6 function setting             */
    PORTB.PODR.BYTE |= 0x01;

    PORTB.PDR.BYTE  |= 0x01;
    PORTB.PMR.BYTE  |= 0x01;
  #endif    // (MCU_MODEL == MCU_MODEL_R5F51303AxFN || MCU_MODEL == MCU_MODEL_R5F51305AxFN)
#endif    // (MCU_SERIES_T == R5F5130)
#if (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)
    MPC.PB0PFS.BYTE  = 0x0B;                                          /* PB0 = SCI6 TXD6 function setting             */
    PORTB.PMR.BYTE  |= 0x01;

    MPC.PB1PFS.BYTE  = 0x0B;                                          /* PB1 = SCI6 RXD6 function setting             */
    PORTB.PODR.BYTE |= 0x02;

    PORTB.PDR.BYTE  |= 0x02;
    PORTB.PMR.BYTE  |= 0x02;
#endif    // (MCU_SERIES_T == R5F5231 || MCU_SERIES_T == R5F5230)

    /* Serial Control Register (SCR) **********************************************************************************/
    /* bit7    Transmit Interrupt Enable (TIE)                                                                        */
    /* bit6    Receive Interrupt Enable (RIE)                                                                         */
    /* bit5    Transmit Enable (TE)                                                                                   */
    /* bit4    Receive Enable (RE)                                                                                    */
    /* bit3    Multi-Processor Interrupt Enable (MPIE)                                                                */
    /* bit2    Transmit End Interrupt Enable (TEIE)                                                                   */
    /* bit1-0  Clock Enable (CKE)                                                                                     */
    /******************************************************************************************************************/
     SCI6.SCR.BIT.CKE    = 0;

    /* I2C Mode Register 1 (SIMR1) ************************************************************************************/
    /* bit7-3  SSDA Output Delay Select (IICDL)                                                                       */
    /* bit2-1  Reserved                                                                                               */
    /* bit0    Simple I2C Mode Select (IICM)                                                                          */
    /******************************************************************************************************************/
    SCI6.SIMR1.BIT.IICM = 0;

    /* SPI Mode Register (SPMR) ***************************************************************************************/
    /* bit7    Clock Phase Select (CKPH)                                                                              */
    /* bit6    Clock Polarity Select (CKPOL)                                                                          */
    /* bit5    Reserved                                                                                               */
    /* bit4    Mode Fault Flag (MFF)                                                                                  */
    /* bit3    Reserved                                                                                               */
    /* bit2    Master Slave Select (MSS)                                                                              */
    /* bit1    CTS Enable (CTSE)                                                                                      */
    /* bit0    SSn# Pin Function Enable (SSE)                                                                         */
    /******************************************************************************************************************/
    SCI6.SPMR.BYTE = 0x00;

    /* Serial Mode Register (SMR) *************************************************************************************/
    /* bit7    Communications Mode (CM)                                                                               */
    /* bit6    Character Length (CHR)                                                                                 */
    /* bit5    Parity Enable (PE)                                                                                     */
    /* bit4    Parity Mode (PM)                                                                                       */
    /* bit3    Stop Bit Length (STOP)                                                                                 */
    /* bit2    Multi-Processor Mode (MP)                                                                              */
    /* bit1-0  Clock Select (CKS)                                                                                     */
    /******************************************************************************************************************/
    SCI6.SMR.BIT.CKS  = 0x01;                                           /* Clock Select = PCLK/4                      */
                                                                        /* Multi-processor communication is disabled  */
                                                                        /* 1 stop bit                                 */
                                                                        /* Selects even parity                        */
                                                                        /* Parity bit addition is not performed       */
                                                                        /* Selects 8 bits as the data length          */
                                                                        /* Asynchronous mode                          */

    /* Smart Card Mode Register (SCMR) ********************************************************************************/
    /* bit7    Base Clock Pulse 2 (BCP2)                                                                              */
    /* bit6-5  Reserved                                                                                               */
    /* bit4    Character Length 1 (CHR1)                                                                              */
    /* bit3    Transmitted/Received Data Transfer Direction (SDIR)                                                    */
    /* bit2    Transmitted/Received Data Invert (SINV)                                                                */
    /* bit1    Reserved                                                                                               */
    /* bit0    Smart Card Interface Mode Select (SMIF)                                                                */
    /******************************************************************************************************************/
    SCI6.SCMR.BYTE    = 0x72;

    /* Serial Extended Mode Register (SEMR) ***************************************************************************/
    /* bit7    Asynchronous Start Bit Edge Detection Select (RXDESEL)                                                 */
    /* bit6    Reserved                                                                                               */
    /* bit5    Digital Noise Filter Function Enable (NFEN)                                                            */
    /* bit4    Asynchronous Mode Base Clock Select (ABCS)                                                             */
    /* bit3-1  Reserved                                                                                               */
    /* bit0    Asynchronous Mode Clock Source Select (ACS0)                                                           */
    /******************************************************************************************************************/
    SCI6.SEMR.BYTE    = 0x10;

    /* Bit Rate Register (BRR) ****************************************************************************************/
    /* bit7-0  Bitrate Select                                                                                         */
    /******************************************************************************************************************/
    SCI6.BRR = 0x0C;                                                    /* 38400bps                                   */
//    SCI6.BRR = 0x08;                                                    /* 57600bps                                   */

}    /* End of function R_SCI6_Create() */

/***********************************************************************************************************************
* Function Name: R_SCI6_Start
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Start(void)
{
    SCI6.SCR.BIT.TE  = 1;      /* Disable serial transmit */
    SCI6.SCR.BIT.RE  = 1;      /* Disable serial receive */
    SCI6.SCR.BIT.TIE = 1;     /* Disable TXI interrupt */
    SCI6.SCR.BIT.RIE = 1;     /* Disable RXI and ERI interrupt */
    IR(SCI6,TXI6) = 0U;
    IR(SCI6,TEI6) = 0U;
    IR(SCI6,RXI6) = 0U;
    IR(SCI6,ERI6) = 0U;
    IEN(SCI6,TXI6) = 1U;
    IEN(SCI6,RXI6) = 1U;
}    /* End of function R_SCI6_Start() */

/***********************************************************************************************************************
* Function Name: R_SCI6_Stop
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Stop(void)
{
    PORTB.PMR.BYTE  &= 0xFDU;
    SCI6.SCR.BIT.TE  = 0U;      /* Disable serial transmit */
    SCI6.SCR.BIT.RE  = 0U;      /* Disable serial receive */
    SCI6.SCR.BIT.TIE = 0U;     /* Disable TXI interrupt */
    SCI6.SCR.BIT.RIE = 0U;     /* Disable RXI and ERI interrupt */
    IR(SCI6,TXI6)    = 0U;
    IR(SCI6,TEI6)    = 0U;
    IR(SCI6,RXI6)    = 0U;
    IR(SCI6,ERI6)    = 0U;
}    /* End of function R_SCI6_Stop() */

/***********************************************************************************************************************
* Function Name: R_SCI6_Receive_Data_Check
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Receive_Data_Check(void)
{
    if (1 == SCI6.SSR.BIT.FER)
    {
        g_sci6_receive_flag  = 0;
        g_sci6_receive_count = 0;
        SCI6.SSR.BIT.FER = 0;
        return;
    }

    if (1 == g_sci6_receive_flag)
    {
        if (0 == g_sci6_send_flag)
        {
            if (SerialCommandReceive(g_sci6_receive_data, g_sci6_receive_data_size))
            {
                if (GetReplayMessage(g_sci6_send_data, (uint16_t *)&g_sci6_send_count))
                {
                      R_SCI6_Serial_Send_Start( g_sci6_send_count );
                }
            }
        }
    }
}    /* End of function R_SCI6_Receive_Data_Check() */

/***********************************************************************************************************************
* Function Name: R_SCI6_Serial_Send_Start
* Description  : Transmits SCI6 data.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Serial_Send_Start( uint16_t send_size )
{
    send_size = send_size - 1;
    DTC_Set_Data_Size_of_SCI6( send_size );

    g_sci6_send_flag = 1;
    SCI6.TDR = g_sci6_send_data[0];

}    /* End of function R_SCI6_Serial_Send() */

/***********************************************************************************************************************
* Function Name: r_sci6_transmit_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCI6_TXI6
#pragma interrupt r_sci6_transmit_interrupt(vect=VECT(SCI6,TXI6),fint)
#else
#pragma interrupt r_sci6_transmit_interrupt(vect=VECT(SCI6,TXI6))
#endif

static void r_sci6_transmit_interrupt(void)
{
    if (g_dtc_send_finish == 0)
    {
        g_sci6_receive_flag  = 0;
        g_sci6_receive_count = 0;
        DTC_Set_Restart_SCI6();
        g_dtc_send_finish = 1;
    }
    else
    {
        ICU.DTCER[228].BIT.DTCE = 1U;
        g_dtc_send_finish = 0;
        g_sci6_send_flag = 0;
    }
}

/***********************************************************************************************************************
* Function Name: r_sci6_receive_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCI6_RXI6
#pragma interrupt r_sci6_receive_interrupt(vect=VECT(SCI6,RXI6),fint)
#else
#pragma interrupt r_sci6_receive_interrupt(vect=VECT(SCI6,RXI6))
#endif

static void r_sci6_receive_interrupt(void)
{
    g_sci6_receive_data[g_sci6_receive_count] = SCI6.RDR;                /* Receive data ---> buffer storage          */

    if (SCI_SIZE_CHECK_COUNT == g_sci6_receive_count)                    /* SCI6 Receive data size check              */
    {
        if (0x00 == g_sci6_receive_data[g_sci6_receive_count])           /* Receive data = 0 check                    */
        {
            /* Data size = 3 setting (main command + sub command + size + check sum) */
            g_sci6_receive_data_size = SCI_BASE_DATA_SIZE;
        }
        else
        {
            /* Data size = (3 + data size) setting (main command + sub command + size + check sum + data size) */
            g_sci6_receive_data_size = (uint16_t)(SCI_BASE_DATA_SIZE + g_sci6_receive_data[SCI_SIZE_CHECK_COUNT]);
        }
    }

    if (SCI_SIZE_CHECK_COUNT < g_sci6_receive_count)
    {
        if (g_sci6_receive_data_size == g_sci6_receive_count)
        {
            g_sci6_receive_flag  = 1;
            g_sci6_receive_count = 0;
            g_sci6_receive_data_size = g_sci6_receive_data_size + 1;
        }
        else
        {
          g_sci6_receive_count = g_sci6_receive_count + 1;
        }
    }
    else
    {
        g_sci6_receive_count = g_sci6_receive_count + 1;
    }
}
#endif  // SCI_SERIAL_USE

/***********************************************************************************************************************
* End of file
***********************************************************************************************************************/

