/*******************************************************************************
* File Name: Launcher_UART_pm.c
* Version 2.60
*
* Description:
*  This file provides Suspend/Resume APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "project.h"
#include "Launcher_UART.h"
#include "Launcher_UART_pvt.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static Launcher_UART_BACKUP_STRUCT  Launcher_UART_backup;


#if(Launcher_UART_DP_ISR_REMOVE == 0u)


    /*******************************************************************************
    * Function Name: Launcher_UART_DP_Interrupt
    ********************************************************************************
    *
    * Summary:
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(Launcher_UART_DP_ISR)
    {
        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        /* Clears active interrupt */
        CY_GET_REG8(Launcher_UART_DP_INTSTAT_PTR);
    }

#endif /* (Launcher_UART_DP_ISR_REMOVE == 0u) */


/*******************************************************************************
* Function Name: Launcher_UART_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
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
void Launcher_UART_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: Launcher_UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
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
void Launcher_UART_RestoreConfig(void) 
{
    if(Launcher_UART_configuration != 0u)
    {
        Launcher_UART_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_Suspend
********************************************************************************
*
* Summary:
*  This function disables the USBFS block and prepares for power donwn mode.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*  Launcher_UART_backup.enable:  modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_Suspend(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if((CY_GET_REG8(Launcher_UART_CR0_PTR) & Launcher_UART_CR0_ENABLE) != 0u)
    {   /* USB block is enabled */
        Launcher_UART_backup.enableState = 1u;

        #if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
            Launcher_UART_Stop_DMA(Launcher_UART_MAX_EP);     /* Stop all DMAs */
        #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
        Launcher_UART_USBIO_CR0_REG &= (uint8)~Launcher_UART_USBIO_CR0_TEN;
        CyDelayUs(0u);  /*~50ns delay */

        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
        Launcher_UART_PM_USB_CR0_REG &=
                                (uint8)~(Launcher_UART_PM_USB_CR0_PD_N | Launcher_UART_PM_USB_CR0_PD_PULLUP_N);

        /* Disable the SIE */
        Launcher_UART_CR0_REG &= (uint8)~Launcher_UART_CR0_ENABLE;

        CyDelayUs(0u);  /*~50ns delay */
        /* Store mode and Disable VRegulator*/
        Launcher_UART_backup.mode = Launcher_UART_CR1_REG & Launcher_UART_CR1_REG_ENABLE;
        Launcher_UART_CR1_REG &= (uint8)~Launcher_UART_CR1_REG_ENABLE;

        CyDelayUs(1u);  /* 0.5 us min delay */
        /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        Launcher_UART_PM_USB_CR0_REG &= (uint8)~Launcher_UART_PM_USB_CR0_REF_EN;

        /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pullup*/
        Launcher_UART_USBIO_CR1_REG |= Launcher_UART_USBIO_CR1_IOMODE;

        /* Disable USB in ACT PM */
        Launcher_UART_PM_ACT_CFG_REG &= (uint8)~Launcher_UART_PM_ACT_EN_FSUSB;
        /* Disable USB block for Standby Power Mode */
        Launcher_UART_PM_STBY_CFG_REG &= (uint8)~Launcher_UART_PM_STBY_EN_FSUSB;
        CyDelayUs(1u); /* min  0.5us delay required */

    }
    else
    {
        Launcher_UART_backup.enableState = 0u;
    }
    CyExitCriticalSection(enableInterrupts);

    /* Set the DP Interrupt for wake-up from sleep mode. */
    #if(Launcher_UART_DP_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_DP_INTC_VECT_NUM,   &Launcher_UART_DP_ISR);
        CyIntSetPriority(Launcher_UART_DP_INTC_VECT_NUM, Launcher_UART_DP_INTC_PRIOR);
        CyIntClearPending(Launcher_UART_DP_INTC_VECT_NUM);
        CyIntEnable(Launcher_UART_DP_INTC_VECT_NUM);
    #endif /* (Launcher_UART_DP_ISR_REMOVE == 0u) */

}


/*******************************************************************************
* Function Name: Launcher_UART_Resume
********************************************************************************
*
* Summary:
*  This function enables the USBFS block after power down mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Launcher_UART_backup - checked.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_Resume(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if(Launcher_UART_backup.enableState != 0u)
    {
        #if(Launcher_UART_DP_ISR_REMOVE == 0u)
            CyIntDisable(Launcher_UART_DP_INTC_VECT_NUM);
        #endif /* End Launcher_UART_DP_ISR_REMOVE */

        /* Enable USB block */
        Launcher_UART_PM_ACT_CFG_REG |= Launcher_UART_PM_ACT_EN_FSUSB;
        /* Enable USB block for Standby Power Mode */
        Launcher_UART_PM_STBY_CFG_REG |= Launcher_UART_PM_STBY_EN_FSUSB;
        /* Enable core clock */
        Launcher_UART_USB_CLK_EN_REG |= Launcher_UART_USB_CLK_ENABLE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        Launcher_UART_PM_USB_CR0_REG |= Launcher_UART_PM_USB_CR0_REF_EN;
        /* The reference will be available ~40us after power restored */
        CyDelayUs(40u);
        /* Return VRegulator*/
        Launcher_UART_CR1_REG |= Launcher_UART_backup.mode;
        CyDelayUs(0u);  /*~50ns delay */
        /* Enable USBIO */
        Launcher_UART_PM_USB_CR0_REG |= Launcher_UART_PM_USB_CR0_PD_N;
        CyDelayUs(2u);
        /* Set the USBIO pull-up enable */
        Launcher_UART_PM_USB_CR0_REG |= Launcher_UART_PM_USB_CR0_PD_PULLUP_N;

        /* Reinit Arbiter configuration for DMA transfers */
        #if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
            /* usb arb interrupt enable */
            Launcher_UART_ARB_INT_EN_REG = Launcher_UART_ARB_INT_MASK;
            #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL)
                Launcher_UART_ARB_CFG_REG = Launcher_UART_ARB_CFG_MANUAL_DMA;
            #endif   /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL */
            #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO)
                /*Set cfg cmplt this rises DMA request when the full configuration is done */
                Launcher_UART_ARB_CFG_REG = Launcher_UART_ARB_CFG_AUTO_DMA | Launcher_UART_ARB_CFG_AUTO_MEM;
            #endif   /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO */
        #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

        /* STALL_IN_OUT */
        CY_SET_REG8(Launcher_UART_EP0_CR_PTR, Launcher_UART_MODE_STALL_IN_OUT);
        /* Enable the SIE with a last address */
        Launcher_UART_CR0_REG |= Launcher_UART_CR0_ENABLE;
        CyDelayCycles(1u);
        /* Finally, Enable d+ pullup and select iomode to USB mode*/
        CY_SET_REG8(Launcher_UART_USBIO_CR1_PTR, Launcher_UART_USBIO_CR1_USBPUEN);

        /* Restore USB register settings */
        Launcher_UART_RestoreConfig();

    }
    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
