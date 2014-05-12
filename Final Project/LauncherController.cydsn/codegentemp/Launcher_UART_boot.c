/*******************************************************************************
* File Name: Launcher_UART_boot.c
* Version 2.60
*
* Description:
*  Boot loader API for USBFS Component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Launcher_UART.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Launcher_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*    Bootloader defines
***************************************/

#define Launcher_UART_CyBtLdrStarttimer(X, T)         {Launcher_UART_universalTime = T * 10; X = 0u;}
#define Launcher_UART_CyBtLdrChecktimer(X)            ((X++ < Launcher_UART_universalTime) ? 1u : 0u)

#define Launcher_UART_BTLDR_OUT_EP      (0x01u)
#define Launcher_UART_BTLDR_IN_EP       (0x02u)


/***************************************
*    Bootloader Variables
***************************************/

static uint16 Launcher_UART_universalTime;
static uint8 Launcher_UART_started = 0u;


/*******************************************************************************
* Function Name: Launcher_UART_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Starts the component and enables the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  This function starts the USB with 3V or 5V operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_CyBtldrCommStart(void) 
{
    CyGlobalIntEnable;      /* Enable Global Interrupts */

    /*Start USBFS Operation/device 0 and with 5V or 3V operation depend on Voltage Configuration in DWR */
    Launcher_UART_Start(0u, Launcher_UART_DWR_VDDD_OPERATION);

    /* USB component started, the correct enumeration will be checked in first Read operation */
    Launcher_UART_started = 1u;

}


/*******************************************************************************
* Function Name: Launcher_UART_CyBtldrCommStop.
********************************************************************************
*
* Summary:
*  Disable the component and disable the interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Launcher_UART_CyBtldrCommStop(void) 
{
    Launcher_UART_Stop();
}


/*******************************************************************************
* Function Name: Launcher_UART_CyBtldrCommReset.
********************************************************************************
*
* Summary:
*  Resets the receive and transmit communication Buffers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_CyBtldrCommReset(void) 
{
    Launcher_UART_EnableOutEP(Launcher_UART_BTLDR_OUT_EP);  /* Enable the OUT endpoint */
}


/*******************************************************************************
* Function Name: Launcher_UART_CyBtldrCommWrite.
********************************************************************************
*
* Summary:
*  Allows the caller to write data to the boot loader host. The function will
*  handle polling to allow a block of data to be completely sent to the host
*  device.
*
* Parameters:
*  pData:    A pointer to the block of data to send to the device
*  size:     The number of bytes to write.
*  count:    Pointer to an unsigned short variable to write the number of
*             bytes actually written.
*  timeOut:  Number of units to wait before returning because of a timeout.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No.
*
*******************************************************************************/
cystatus Launcher_UART_CyBtldrCommWrite(uint8 *pData, uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    uint16 time;
    cystatus status;

    /* Enable IN transfer */
    Launcher_UART_LoadInEP(Launcher_UART_BTLDR_IN_EP, pData, Launcher_UART_BTLDR_SIZEOF_READ_BUFFER);

    /* Start a timer to wait on. */
    Launcher_UART_CyBtLdrStarttimer(time, timeOut);

    /* Wait for the master to read it. */
    while((Launcher_UART_GetEPState(Launcher_UART_BTLDR_IN_EP) == Launcher_UART_IN_BUFFER_FULL) && \
           Launcher_UART_CyBtLdrChecktimer(time))
    {
        CyDelay(1u); /* 1ms delay */
    }

    if (Launcher_UART_GetEPState(Launcher_UART_BTLDR_IN_EP) == Launcher_UART_IN_BUFFER_FULL)
    {
        status = CYRET_TIMEOUT;
    }
    else
    {
        *count = size;
        status = CYRET_SUCCESS;
    }

    return(status);
}


/*******************************************************************************
* Function Name: Launcher_UART_CyBtldrCommRead.
********************************************************************************
*
* Summary:
*  Allows the caller to read data from the boot loader host. The function will
*  handle polling to allow a block of data to be completely received from the
*  host device.
*
* Parameters:
*  pData:    A pointer to the area to store the block of data received
*             from the device.
*  size:     The number of bytes to read.
*  count:    Pointer to an unsigned short variable to write the number
*             of bytes actually read.
*  timeOut:  Number of units to wait before returning because of a timeOut.
*            Timeout is measured in 10s of ms.
*
* Return:
*  Returns the value that best describes the problem.
*
* Reentrant:
*  No.
*
*******************************************************************************/
cystatus Launcher_UART_CyBtldrCommRead(uint8 *pData, uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            
{
    cystatus status;
    uint16 time;

    if(size > Launcher_UART_BTLDR_SIZEOF_WRITE_BUFFER)
    {
        size = Launcher_UART_BTLDR_SIZEOF_WRITE_BUFFER;
    }
    /* Start a timer to wait on. */
    Launcher_UART_CyBtLdrStarttimer(time, timeOut);

    /* Wait on enumeration in first time */
    if(Launcher_UART_started)
    {
        /* Wait for Device to enumerate */
        while(!Launcher_UART_GetConfiguration() && Launcher_UART_CyBtLdrChecktimer(time))
        {
            CyDelay(1u); /* 1ms delay */
        }
        /* Enable first OUT, if enumeration complete */
        if(Launcher_UART_GetConfiguration())
        {
            Launcher_UART_IsConfigurationChanged();  /* Clear configuration changes state status */
            Launcher_UART_CyBtldrCommReset();
            Launcher_UART_started = 0u;
        }
    }
    else /* Check for configuration changes, has been done by Host */
    {
        if(Launcher_UART_IsConfigurationChanged() != 0u) /* Host could send double SET_INTERFACE request or RESET */
        {
            if(Launcher_UART_GetConfiguration() != 0u)   /* Init OUT endpoints when device reconfigured */
            {
                Launcher_UART_CyBtldrCommReset();
            }
        }
    }
    /* Wait on next packet */
    while((Launcher_UART_GetEPState(Launcher_UART_BTLDR_OUT_EP) != Launcher_UART_OUT_BUFFER_FULL) && \
           Launcher_UART_CyBtLdrChecktimer(time))
    {
        CyDelay(1u); /* 1ms delay */
    }

    /* OUT EP has completed */
    if (Launcher_UART_GetEPState(Launcher_UART_BTLDR_OUT_EP) == Launcher_UART_OUT_BUFFER_FULL)
    {
        *count = Launcher_UART_ReadOutEP(Launcher_UART_BTLDR_OUT_EP, pData, size);
        status = CYRET_SUCCESS;
    }
    else
    {
        *count = 0u;
        status = CYRET_TIMEOUT;
    }
    return(status);
}

#endif /* End CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Launcher_UART */


/* [] END OF FILE */
