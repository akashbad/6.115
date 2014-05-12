/*******************************************************************************
* File Name: CapSense_IdacCH0.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  IDAC8.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include "CapSense_IdacCH0.h"

static CapSense_IdacCH0_backupStruct CapSense_IdacCH0_backup;


/*******************************************************************************
* Function Name: CapSense_IdacCH0_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_IdacCH0_SaveConfig(void) 
{
    if (!((CapSense_IdacCH0_CR1 & CapSense_IdacCH0_SRC_MASK) == CapSense_IdacCH0_SRC_UDB))
    {
        CapSense_IdacCH0_backup.data_value = CapSense_IdacCH0_Data;
    }
}


/*******************************************************************************
* Function Name: CapSense_IdacCH0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_IdacCH0_RestoreConfig(void) 
{
    if (!((CapSense_IdacCH0_CR1 & CapSense_IdacCH0_SRC_MASK) == CapSense_IdacCH0_SRC_UDB))
    {
        if((CapSense_IdacCH0_Strobe & CapSense_IdacCH0_STRB_MASK) == CapSense_IdacCH0_STRB_EN)
        {
            CapSense_IdacCH0_Strobe &= (uint8)(~CapSense_IdacCH0_STRB_MASK);
            CapSense_IdacCH0_Data = CapSense_IdacCH0_backup.data_value;
            CapSense_IdacCH0_Strobe |= CapSense_IdacCH0_STRB_EN;
        }
        else
        {
            CapSense_IdacCH0_Data = CapSense_IdacCH0_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: CapSense_IdacCH0_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  CapSense_IdacCH0_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CapSense_IdacCH0_Sleep(void) 
{
    if(CapSense_IdacCH0_ACT_PWR_EN == (CapSense_IdacCH0_PWRMGR & CapSense_IdacCH0_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        CapSense_IdacCH0_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        CapSense_IdacCH0_backup.enableState = 0u;
    }

    CapSense_IdacCH0_Stop();
    CapSense_IdacCH0_SaveConfig();
}


/*******************************************************************************
* Function Name: CapSense_IdacCH0_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  CapSense_IdacCH0_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CapSense_IdacCH0_Wakeup(void) 
{
    CapSense_IdacCH0_RestoreConfig();
    
    if(CapSense_IdacCH0_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        CapSense_IdacCH0_Enable();
        
        /* Set the data register */
        CapSense_IdacCH0_SetValue(CapSense_IdacCH0_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
