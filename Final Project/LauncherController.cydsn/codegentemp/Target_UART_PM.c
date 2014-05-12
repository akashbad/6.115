/*******************************************************************************
* File Name: Target_UART_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Target_UART.h"


/***************************************
* Local data allocation
***************************************/

static Target_UART_BACKUP_STRUCT  Target_UART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Target_UART_SaveConfig
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
* Global Variables:
*  Target_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Target_UART_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(Target_UART_CONTROL_REG_REMOVED == 0u)
            Target_UART_backup.cr = Target_UART_CONTROL_REG;
        #endif /* End Target_UART_CONTROL_REG_REMOVED */

        #if( (Target_UART_RX_ENABLED) || (Target_UART_HD_ENABLED) )
            Target_UART_backup.rx_period = Target_UART_RXBITCTR_PERIOD_REG;
            Target_UART_backup.rx_mask = Target_UART_RXSTATUS_MASK_REG;
            #if (Target_UART_RXHW_ADDRESS_ENABLED)
                Target_UART_backup.rx_addr1 = Target_UART_RXADDRESS1_REG;
                Target_UART_backup.rx_addr2 = Target_UART_RXADDRESS2_REG;
            #endif /* End Target_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End Target_UART_RX_ENABLED | Target_UART_HD_ENABLED*/

        #if(Target_UART_TX_ENABLED)
            #if(Target_UART_TXCLKGEN_DP)
                Target_UART_backup.tx_clk_ctr = Target_UART_TXBITCLKGEN_CTR_REG;
                Target_UART_backup.tx_clk_compl = Target_UART_TXBITCLKTX_COMPLETE_REG;
            #else
                Target_UART_backup.tx_period = Target_UART_TXBITCTR_PERIOD_REG;
            #endif /*End Target_UART_TXCLKGEN_DP */
            Target_UART_backup.tx_mask = Target_UART_TXSTATUS_MASK_REG;
        #endif /*End Target_UART_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(Target_UART_CONTROL_REG_REMOVED == 0u)
            Target_UART_backup.cr = Target_UART_CONTROL_REG;
        #endif /* End Target_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Target_UART_RestoreConfig
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
* Global Variables:
*  Target_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Target_UART_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(Target_UART_CONTROL_REG_REMOVED == 0u)
            Target_UART_CONTROL_REG = Target_UART_backup.cr;
        #endif /* End Target_UART_CONTROL_REG_REMOVED */

        #if( (Target_UART_RX_ENABLED) || (Target_UART_HD_ENABLED) )
            Target_UART_RXBITCTR_PERIOD_REG = Target_UART_backup.rx_period;
            Target_UART_RXSTATUS_MASK_REG = Target_UART_backup.rx_mask;
            #if (Target_UART_RXHW_ADDRESS_ENABLED)
                Target_UART_RXADDRESS1_REG = Target_UART_backup.rx_addr1;
                Target_UART_RXADDRESS2_REG = Target_UART_backup.rx_addr2;
            #endif /* End Target_UART_RXHW_ADDRESS_ENABLED */
        #endif  /* End (Target_UART_RX_ENABLED) || (Target_UART_HD_ENABLED) */

        #if(Target_UART_TX_ENABLED)
            #if(Target_UART_TXCLKGEN_DP)
                Target_UART_TXBITCLKGEN_CTR_REG = Target_UART_backup.tx_clk_ctr;
                Target_UART_TXBITCLKTX_COMPLETE_REG = Target_UART_backup.tx_clk_compl;
            #else
                Target_UART_TXBITCTR_PERIOD_REG = Target_UART_backup.tx_period;
            #endif /*End Target_UART_TXCLKGEN_DP */
            Target_UART_TXSTATUS_MASK_REG = Target_UART_backup.tx_mask;
        #endif /*End Target_UART_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(Target_UART_CONTROL_REG_REMOVED == 0u)
            Target_UART_CONTROL_REG = Target_UART_backup.cr;
        #endif /* End Target_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Target_UART_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Target_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Target_UART_Sleep(void)
{

    #if(Target_UART_RX_ENABLED || Target_UART_HD_ENABLED)
        if((Target_UART_RXSTATUS_ACTL_REG  & Target_UART_INT_ENABLE) != 0u)
        {
            Target_UART_backup.enableState = 1u;
        }
        else
        {
            Target_UART_backup.enableState = 0u;
        }
    #else
        if((Target_UART_TXSTATUS_ACTL_REG  & Target_UART_INT_ENABLE) !=0u)
        {
            Target_UART_backup.enableState = 1u;
        }
        else
        {
            Target_UART_backup.enableState = 0u;
        }
    #endif /* End Target_UART_RX_ENABLED || Target_UART_HD_ENABLED*/

    Target_UART_Stop();
    Target_UART_SaveConfig();
}


/*******************************************************************************
* Function Name: Target_UART_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Target_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Target_UART_Wakeup(void)
{
    Target_UART_RestoreConfig();
    #if( (Target_UART_RX_ENABLED) || (Target_UART_HD_ENABLED) )
        Target_UART_ClearRxBuffer();
    #endif /* End (Target_UART_RX_ENABLED) || (Target_UART_HD_ENABLED) */
    #if(Target_UART_TX_ENABLED || Target_UART_HD_ENABLED)
        Target_UART_ClearTxBuffer();
    #endif /* End Target_UART_TX_ENABLED || Target_UART_HD_ENABLED */

    if(Target_UART_backup.enableState != 0u)
    {
        Target_UART_Enable();
    }
}


/* [] END OF FILE */
