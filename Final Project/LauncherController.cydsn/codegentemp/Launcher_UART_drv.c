/*******************************************************************************
* File Name: Launcher_UART_drv.c
* Version 2.60
*
* Description:
*  Endpoint 0 Driver for the USBFS Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Launcher_UART.h"
#include "Launcher_UART_pvt.h"


/***************************************
* Global data allocation
***************************************/

volatile T_Launcher_UART_EP_CTL_BLOCK Launcher_UART_EP[Launcher_UART_MAX_EP];
volatile uint8 Launcher_UART_configuration;
volatile uint8 Launcher_UART_interfaceNumber;
volatile uint8 Launcher_UART_configurationChanged;
volatile uint8 Launcher_UART_deviceAddress;
volatile uint8 Launcher_UART_deviceStatus;
volatile uint8 Launcher_UART_interfaceSetting[Launcher_UART_MAX_INTERFACES_NUMBER];
volatile uint8 Launcher_UART_interfaceSetting_last[Launcher_UART_MAX_INTERFACES_NUMBER];
volatile uint8 Launcher_UART_interfaceStatus[Launcher_UART_MAX_INTERFACES_NUMBER];
volatile uint8 Launcher_UART_device;
const uint8 CYCODE *Launcher_UART_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8 Launcher_UART_ep0Toggle;
volatile uint8 Launcher_UART_lastPacketSize;
volatile uint8 Launcher_UART_transferState;
volatile T_Launcher_UART_TD Launcher_UART_currentTD;
volatile uint8 Launcher_UART_ep0Mode;
volatile uint8 Launcher_UART_ep0Count;
volatile uint16 Launcher_UART_transferByteCount;


/*******************************************************************************
* Function Name: Launcher_UART_ep_0_Interrupt
********************************************************************************
*
* Summary:
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(Launcher_UART_EP_0_ISR)
{
    uint8 bRegTemp;
    uint8 modifyReg;


    bRegTemp = CY_GET_REG8(Launcher_UART_EP0_CR_PTR);
    if ((bRegTemp & Launcher_UART_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((bRegTemp & Launcher_UART_MODE_SETUP_RCVD) != 0u)
        {
            if((bRegTemp & Launcher_UART_MODE_MASK) != Launcher_UART_MODE_NAK_IN_OUT)
            {
                modifyReg = 0u;                                     /* When mode not NAK_IN_OUT => invalid setup */
            }
            else
            {
                Launcher_UART_HandleSetup();
                if((Launcher_UART_ep0Mode & Launcher_UART_MODE_SETUP_RCVD) != 0u)
                {
                    modifyReg = 0u;                         /* if SETUP bit set -> exit without modifying the mode */
                }

            }
        }
        else if ((bRegTemp & Launcher_UART_MODE_IN_RCVD) != 0u)
        {
            Launcher_UART_HandleIN();
        }
        else if ((bRegTemp & Launcher_UART_MODE_OUT_RCVD) != 0u)
        {
            Launcher_UART_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        if(modifyReg != 0u)
        {
            bRegTemp = CY_GET_REG8(Launcher_UART_EP0_CR_PTR);    /* unlock registers */
            if((bRegTemp & Launcher_UART_MODE_SETUP_RCVD) == 0u)  /* Check if SETUP bit is not set, otherwise exit */
            {
                /* Update the count register */
                bRegTemp = Launcher_UART_ep0Toggle | Launcher_UART_ep0Count;
                CY_SET_REG8(Launcher_UART_EP0_CNT_PTR, bRegTemp);
                if(bRegTemp == CY_GET_REG8(Launcher_UART_EP0_CNT_PTR))   /* continue if writing was successful */
                {
                    do
                    {
                        modifyReg = Launcher_UART_ep0Mode;       /* Init temporary variable */
                        /* Unlock registers */
                        bRegTemp = CY_GET_REG8(Launcher_UART_EP0_CR_PTR) & Launcher_UART_MODE_SETUP_RCVD;
                        if(bRegTemp == 0u)                          /* Check if SETUP bit is not set */
                        {
                            /* Set the Mode Register  */
                            CY_SET_REG8(Launcher_UART_EP0_CR_PTR, Launcher_UART_ep0Mode);
                            /* Writing check */
                            modifyReg = CY_GET_REG8(Launcher_UART_EP0_CR_PTR) & Launcher_UART_MODE_MASK;
                        }
                    }while(modifyReg != Launcher_UART_ep0Mode);  /* Repeat if writing was not successful */
                }
            }
        }
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_HandleSetup
********************************************************************************
*
* Summary:
*  This Routine dispatches requests for the four USB request types
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
void Launcher_UART_HandleSetup(void) 
{
    uint8 requestHandled;

    requestHandled = CY_GET_REG8(Launcher_UART_EP0_CR_PTR);      /* unlock registers */
    CY_SET_REG8(Launcher_UART_EP0_CR_PTR, requestHandled);       /* clear setup bit */
    requestHandled = CY_GET_REG8(Launcher_UART_EP0_CR_PTR);      /* reread register */
    if((requestHandled & Launcher_UART_MODE_SETUP_RCVD) != 0u)
    {
        Launcher_UART_ep0Mode = requestHandled;        /* if SETUP bit set -> exit without modifying the mode */
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        Launcher_UART_UpdateStatusBlock(Launcher_UART_XFER_PREMATURE);

        switch (CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_TYPE_MASK)
        {
            case Launcher_UART_RQST_TYPE_STD:
                requestHandled = Launcher_UART_HandleStandardRqst();
                break;
            case Launcher_UART_RQST_TYPE_CLS:
                requestHandled = Launcher_UART_DispatchClassRqst();
                break;
            case Launcher_UART_RQST_TYPE_VND:
                requestHandled = Launcher_UART_HandleVendorRqst();
                break;
            default:
                requestHandled = Launcher_UART_FALSE;
                break;
        }
        if (requestHandled == Launcher_UART_FALSE)
        {
            Launcher_UART_ep0Mode = Launcher_UART_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_HandleIN
********************************************************************************
*
* Summary:
*  This routine handles EP0 IN transfers.
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
void Launcher_UART_HandleIN(void) 
{
    switch (Launcher_UART_transferState)
    {
        case Launcher_UART_TRANS_STATE_IDLE:
            break;
        case Launcher_UART_TRANS_STATE_CONTROL_READ:
            Launcher_UART_ControlReadDataStage();
            break;
        case Launcher_UART_TRANS_STATE_CONTROL_WRITE:
            Launcher_UART_ControlWriteStatusStage();
            break;
        case Launcher_UART_TRANS_STATE_NO_DATA_CONTROL:
            Launcher_UART_NoDataControlStatusStage();
            break;
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_HandleOUT
********************************************************************************
*
* Summary:
*  This routine handles EP0 OUT transfers.
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
void Launcher_UART_HandleOUT(void) 
{
    switch (Launcher_UART_transferState)
    {
        case Launcher_UART_TRANS_STATE_IDLE:
            break;
        case Launcher_UART_TRANS_STATE_CONTROL_READ:
            Launcher_UART_ControlReadStatusStage();
            break;
        case Launcher_UART_TRANS_STATE_CONTROL_WRITE:
            Launcher_UART_ControlWriteDataStage();
            break;
        case Launcher_UART_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            Launcher_UART_UpdateStatusBlock(Launcher_UART_XFER_ERROR);
            /* We expect no more data, so stall INs and OUTs */
            Launcher_UART_ep0Mode = Launcher_UART_MODE_STALL_IN_OUT;
            break;
        default:    /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_LoadEP0
********************************************************************************
*
* Summary:
*  This routine loads the EP0 data registers for OUT transfers.  It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  Launcher_UART_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  Launcher_UART_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  Launcher_UART_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  Launcher_UART_ep0Toggle - inverted
*  Launcher_UART_ep0Mode  - prepare for mode register content.
*  Launcher_UART_transferState - set to TRANS_STATE_CONTROL_READ
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    Launcher_UART_transferByteCount += Launcher_UART_lastPacketSize;
    /* Now load the next transaction */
    while ((Launcher_UART_currentTD.count > 0u) && (ep0Count < 8u))
    {
        CY_SET_REG8((reg8 *)(Launcher_UART_EP0_DR0_IND + ep0Count), *Launcher_UART_currentTD.pData);
        Launcher_UART_currentTD.pData = &Launcher_UART_currentTD.pData[1u];
        ep0Count++;
        Launcher_UART_currentTD.count--;
    }
    /* Support zero-length packet*/
    if( (Launcher_UART_lastPacketSize == 8u) || (ep0Count > 0u) )
    {
        /* Update the data toggle */
        Launcher_UART_ep0Toggle ^= Launcher_UART_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        Launcher_UART_ep0Mode = Launcher_UART_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        Launcher_UART_transferState = Launcher_UART_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        Launcher_UART_ep0Mode = Launcher_UART_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        Launcher_UART_transferState = Launcher_UART_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    Launcher_UART_lastPacketSize = ep0Count;
    Launcher_UART_ep0Count = ep0Count;
}


/*******************************************************************************
* Function Name: Launcher_UART_InitControlRead
********************************************************************************
*
* Summary:
*  Initialize a control read transaction, usable to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  Launcher_UART_currentTD.count - counts of data to be sent.
*  Launcher_UART_currentTD.pData - data pointer.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Launcher_UART_InitControlRead(void) 
{
    uint16 xferCount;
    if(Launcher_UART_currentTD.count == 0u)
    {
        (void) Launcher_UART_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        Launcher_UART_transferState = Launcher_UART_TRANS_STATE_CONTROL_READ;
        /* Set the toggle, it gets updated in LoadEP */
        Launcher_UART_ep0Toggle = 0u;
        /* Initialize the Status Block */
        Launcher_UART_InitializeStatusBlock();
        xferCount = (((uint16)CY_GET_REG8(Launcher_UART_lengthHi) << 8u) | (CY_GET_REG8(Launcher_UART_lengthLo)));

        if (Launcher_UART_currentTD.count > xferCount)
        {
            Launcher_UART_currentTD.count = xferCount;
        }
        Launcher_UART_LoadEP0();
    }

    return(Launcher_UART_TRUE);
}


/*******************************************************************************
* Function Name: Launcher_UART_InitZeroLengthControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a zero length data IN transfer.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  Launcher_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  Launcher_UART_ep0Mode  - prepare for mode register content.
*  Launcher_UART_transferState - set to TRANS_STATE_CONTROL_READ
*  Launcher_UART_ep0Count - cleared, means the zero-length packet.
*  Launcher_UART_lastPacketSize - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Launcher_UART_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_CONTROL_READ;
    /* Set the data toggle */
    Launcher_UART_ep0Toggle = Launcher_UART_EP0_CNT_DATA_TOGGLE;
    /* Set the Mode Register  */
    Launcher_UART_ep0Mode = Launcher_UART_MODE_ACK_IN_STATUS_OUT;
    /* Save the packet size for next time */
    Launcher_UART_lastPacketSize = 0u;
    Launcher_UART_ep0Count = 0u;

    return(Launcher_UART_TRUE);
}


/*******************************************************************************
* Function Name: Launcher_UART_ControlReadDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control read transfer.
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
void Launcher_UART_ControlReadDataStage(void) 

{
    Launcher_UART_LoadEP0();
}


/*******************************************************************************
* Function Name: Launcher_UART_ControlReadStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control read transfer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_USBFS_transferByteCount - updated with last packet size.
*  Launcher_UART_transferState - set to TRANS_STATE_IDLE.
*  Launcher_UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    Launcher_UART_transferByteCount += Launcher_UART_lastPacketSize;
    /* Go Idle */
    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    Launcher_UART_UpdateStatusBlock(Launcher_UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    Launcher_UART_ep0Mode =  Launcher_UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: Launcher_UART_InitControlWrite
********************************************************************************
*
* Summary:
*  Initialize a control write transaction
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  Launcher_UART_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  Launcher_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  Launcher_UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Launcher_UART_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_CONTROL_WRITE;
    /* This might not be necessary */
    Launcher_UART_ep0Toggle = Launcher_UART_EP0_CNT_DATA_TOGGLE;
    /* Initialize the Status Block */
    Launcher_UART_InitializeStatusBlock();

    xferCount = (((uint16)CY_GET_REG8(Launcher_UART_lengthHi) << 8u) | (CY_GET_REG8(Launcher_UART_lengthLo)));

    if (Launcher_UART_currentTD.count > xferCount)
    {
        Launcher_UART_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    Launcher_UART_ep0Mode = Launcher_UART_MODE_ACK_OUT_STATUS_IN;

    return(Launcher_UART_TRUE);
}


/*******************************************************************************
* Function Name: Launcher_UART_ControlWriteDataStage
********************************************************************************
*
* Summary:
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  Launcher_UART_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  Launcher_UART_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  Launcher_UART_ep0Toggle - inverted
*  Launcher_UART_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (CY_GET_REG8(Launcher_UART_EP0_CNT_PTR) & Launcher_UART_EPX_CNT0_MASK) -
               Launcher_UART_EPX_CNTX_CRC_COUNT;

    Launcher_UART_transferByteCount += ep0Count;

    while ((Launcher_UART_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *Launcher_UART_currentTD.pData = CY_GET_REG8((reg8 *)(Launcher_UART_EP0_DR0_IND + regIndex));
        Launcher_UART_currentTD.pData = &Launcher_UART_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        Launcher_UART_currentTD.count--;
    }
    Launcher_UART_ep0Count = ep0Count;
    /* Update the data toggle */
    Launcher_UART_ep0Toggle ^= Launcher_UART_EP0_CNT_DATA_TOGGLE;
    /* Expect Data or Status Stage */
    Launcher_UART_ep0Mode = Launcher_UART_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: Launcher_UART_ControlWriteStatusStage
********************************************************************************
*
* Summary:
*  Handle the Status Stage of a control write transfer
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_transferState - set to TRANS_STATE_IDLE.
*  Launcher_UART_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    Launcher_UART_UpdateStatusBlock(Launcher_UART_XFER_STATUS_ACK);
    /* We expect no more data, so stall INs and OUTs */
    Launcher_UART_ep0Mode = Launcher_UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: Launcher_UART_InitNoDataControlTransfer
********************************************************************************
*
* Summary:
*  Initialize a no data control transfer
*
* Parameters:
*  None.
*
* Return:
*  requestHandled state.
*
* Global variables:
*  Launcher_UART_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  Launcher_UART_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  Launcher_UART_ep0Count - cleared.
*  Launcher_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Launcher_UART_InitNoDataControlTransfer(void) 
{
    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_NO_DATA_CONTROL;
    Launcher_UART_ep0Mode = Launcher_UART_MODE_STATUS_IN_ONLY;
    Launcher_UART_ep0Toggle = Launcher_UART_EP0_CNT_DATA_TOGGLE;
    Launcher_UART_ep0Count = 0u;

    return(Launcher_UART_TRUE);
}


/*******************************************************************************
* Function Name: Launcher_UART_NoDataControlStatusStage
********************************************************************************
* Summary:
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_transferState - set to TRANS_STATE_IDLE.
*  Launcher_UART_ep0Mode  - set to MODE_STALL_IN_OUT.
*  Launcher_UART_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  Launcher_UART_deviceAddress - used to set new address and cleared
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_NoDataControlStatusStage(void) 
{
    /* Change the USB address register if we got a SET_ADDRESS. */
    if (Launcher_UART_deviceAddress != 0u)
    {
        CY_SET_REG8(Launcher_UART_CR0_PTR, Launcher_UART_deviceAddress | Launcher_UART_CR0_ENABLE);
        Launcher_UART_deviceAddress = 0u;
    }
    /* Go Idle */
    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_IDLE;
    /* Update the completion block */
    Launcher_UART_UpdateStatusBlock(Launcher_UART_XFER_STATUS_ACK);
     /* We expect no more data, so stall INs and OUTs */
    Launcher_UART_ep0Mode = Launcher_UART_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: Launcher_UART_UpdateStatusBlock
********************************************************************************
*
* Summary:
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the Launcher_UART_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
* Parameters:
*  completionCode - status.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  Launcher_UART_currentTD.pStatusBlock->length - updated.
*  Launcher_UART_currentTD.pStatusBlock - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_UpdateStatusBlock(uint8 completionCode) 
{
    if (Launcher_UART_currentTD.pStatusBlock != NULL)
    {
        Launcher_UART_currentTD.pStatusBlock->status = completionCode;
        Launcher_UART_currentTD.pStatusBlock->length = Launcher_UART_transferByteCount;
        Launcher_UART_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_InitializeStatusBlock
********************************************************************************
*
* Summary:
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes Launcher_UART_transferByteCount.  Save some space,
*  this is the only consumer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  Launcher_UART_currentTD.pStatusBlock->length - cleared.
*  Launcher_UART_transferByteCount - cleared.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_InitializeStatusBlock(void) 
{
    Launcher_UART_transferByteCount = 0u;
    if(Launcher_UART_currentTD.pStatusBlock != NULL)
    {
        Launcher_UART_currentTD.pStatusBlock->status = Launcher_UART_XFER_IDLE;
        Launcher_UART_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
