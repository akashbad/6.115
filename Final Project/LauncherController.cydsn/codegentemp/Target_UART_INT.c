/*******************************************************************************
* File Name: Target_UART_INT.c
* Version 2.30
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Target_UART.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if( (Target_UART_RX_ENABLED || Target_UART_HD_ENABLED) && \
     (Target_UART_RXBUFFERSIZE > Target_UART_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: Target_UART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Target_UART_rxBuffer - RAM buffer pointer for save received data.
    *  Target_UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Target_UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Target_UART_rxBufferOverflow - software overflow flag. Set to one
    *     when Target_UART_rxBufferWrite index overtakes
    *     Target_UART_rxBufferRead index.
    *  Target_UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Target_UART_rxBufferWrite is equal to
    *    Target_UART_rxBufferRead
    *  Target_UART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Target_UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Target_UART_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START Target_UART_RXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = Target_UART_RXSTATUS_REG;

        if((readData & (Target_UART_RX_STS_BREAK | Target_UART_RX_STS_PAR_ERROR |
                        Target_UART_RX_STS_STOP_ERROR | Target_UART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START Target_UART_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & Target_UART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (Target_UART_RXHW_ADDRESS_ENABLED)
                if(Target_UART_rxAddressMode == (uint8)Target_UART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & Target_UART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & Target_UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            Target_UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            Target_UART_rxAddressDetected = 0u;
                        }
                    }

                    readData = Target_UART_RXDATA_REG;
                    if(Target_UART_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        Target_UART_rxBuffer[Target_UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    Target_UART_rxBuffer[Target_UART_rxBufferWrite] = Target_UART_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                Target_UART_rxBuffer[Target_UART_rxBufferWrite] = Target_UART_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(Target_UART_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    Target_UART_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                Target_UART_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(Target_UART_rxBufferWrite >= Target_UART_RXBUFFERSIZE)
                {
                    Target_UART_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(Target_UART_rxBufferWrite == Target_UART_rxBufferRead)
                {
                    Target_UART_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(Target_UART_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        Target_UART_RXSTATUS_MASK_REG  &= (uint8)~Target_UART_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(Target_UART_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End Target_UART_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = Target_UART_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Target_UART_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End Target_UART_RX_ENABLED && (Target_UART_RXBUFFERSIZE > Target_UART_FIFO_LENGTH) */


#if(Target_UART_TX_ENABLED && (Target_UART_TXBUFFERSIZE > Target_UART_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: Target_UART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Target_UART_txBuffer - RAM buffer pointer for transmit data from.
    *  Target_UART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  Target_UART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Target_UART_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START Target_UART_TXISR_START` */

        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((Target_UART_txBufferRead != Target_UART_txBufferWrite) &&
             ((Target_UART_TXSTATUS_REG & Target_UART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(Target_UART_txBufferRead >= Target_UART_TXBUFFERSIZE)
            {
                Target_UART_txBufferRead = 0u;
            }

            Target_UART_TXDATA_REG = Target_UART_txBuffer[Target_UART_txBufferRead];

            /* Set next pointer. */
            Target_UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Target_UART_TXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End Target_UART_TX_ENABLED && (Target_UART_TXBUFFERSIZE > Target_UART_FIFO_LENGTH) */


/* [] END OF FILE */
