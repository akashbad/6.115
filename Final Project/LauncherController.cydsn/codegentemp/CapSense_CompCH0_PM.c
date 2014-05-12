/*******************************************************************************
* File Name: CapSense_CompCH0.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "CapSense_CompCH0.h"

static CapSense_CompCH0_backupStruct CapSense_CompCH0_backup;


/*******************************************************************************
* Function Name: CapSense_CompCH0_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_CompCH0_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_RestoreConfig
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
********************************************************************************/
void CapSense_CompCH0_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_Sleep
********************************************************************************
*
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
*  CapSense_CompCH0_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void CapSense_CompCH0_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(CapSense_CompCH0_ACT_PWR_EN == (CapSense_CompCH0_PWRMGR & CapSense_CompCH0_ACT_PWR_EN))
    {
        /* Comp is enabled */
        CapSense_CompCH0_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        CapSense_CompCH0_backup.enableState = 0u;
    }    
    
    CapSense_CompCH0_Stop();
    CapSense_CompCH0_SaveConfig();
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_Wakeup
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
*  CapSense_CompCH0_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CapSense_CompCH0_Wakeup(void) 
{
    CapSense_CompCH0_RestoreConfig();
    
    if(CapSense_CompCH0_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        CapSense_CompCH0_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
