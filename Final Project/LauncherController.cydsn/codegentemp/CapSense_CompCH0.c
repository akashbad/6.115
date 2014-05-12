/*******************************************************************************
* File Name: CapSense_CompCH0.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the Comparator component
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

uint8 CapSense_CompCH0_initVar = 0u;

/* Internal functions definitoin */
static void CapSense_CompCH0_trimAdjust(uint8 nibble) ;

/* static CapSense_CompCH0_backupStruct  CapSense_CompCH0_backup; */
#if (CY_PSOC5A)
    static CapSense_CompCH0_LOWPOWER_BACKUP_STRUCT  CapSense_CompCH0_lowPowerBackup;
#endif /* CY_PSOC5A */

/* variable to decide whether or not to restore the control register in 
   Enable() API for PSoC5A only */
#if (CY_PSOC5A)
    static uint8 CapSense_CompCH0_restoreReg = 0u;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: CapSense_CompCH0_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
* 
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_CompCH0_Init(void) 
{
    /* Set default speed/power */
    CapSense_CompCH0_SetSpeed(CapSense_CompCH0_DEFAULT_SPEED);

    /* Set default Hysteresis */
    #if ( CapSense_CompCH0_DEFAULT_HYSTERESIS == 0u )
        CapSense_CompCH0_CR |= CapSense_CompCH0_HYST_OFF;
    #else
        CapSense_CompCH0_CR &= (uint8)(~CapSense_CompCH0_HYST_OFF);
    #endif /* CapSense_CompCH0_DEFAULT_HYSTERESIS == 0u */
    /* Power down override feature is not supported for PSoC5A. */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Set default Power Down Override */
        #if ( CapSense_CompCH0_DEFAULT_PWRDWN_OVRD == 0u )
            CapSense_CompCH0_CR &= (uint8)(~CapSense_CompCH0_PWRDWN_OVRD);
        #else 
            CapSense_CompCH0_CR |= CapSense_CompCH0_PWRDWN_OVRD;
        #endif /* CapSense_CompCH0_DEFAULT_PWRDWN_OVRD == 0u */
    #endif /* CY_PSOC3 || CY_PSOC5LP */
    
    /* Set mux always on logic */
    CapSense_CompCH0_CR |= CapSense_CompCH0_MX_AO;

    /* Set default sync */
    CapSense_CompCH0_CLK &= (uint8)(~CapSense_CompCH0_SYNCCLK_MASK);
    #if ( CapSense_CompCH0_DEFAULT_BYPASS_SYNC == 0u )
        CapSense_CompCH0_CLK |= CapSense_CompCH0_SYNC_CLK_EN;
    #else
        CapSense_CompCH0_CLK |= CapSense_CompCH0_BYPASS_SYNC;
    #endif /* CapSense_CompCH0_DEFAULT_BYPASS_SYNC == 0u */
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_Enable
********************************************************************************
*
* Summary:
*  Enable the Comparator
* 
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_CompCH0_Enable(void) 
{
    CapSense_CompCH0_PWRMGR |= CapSense_CompCH0_ACT_PWR_EN;
    CapSense_CompCH0_STBY_PWRMGR |= CapSense_CompCH0_STBY_PWR_EN;
     
     /* This is to restore the value of register CR which is saved 
    in prior to the modification in stop() API */
    #if (CY_PSOC5A)
        if(CapSense_CompCH0_restoreReg == 1u)
        {
            CapSense_CompCH0_CR = CapSense_CompCH0_lowPowerBackup.compCRReg;

            /* Clear the flag */
            CapSense_CompCH0_restoreReg = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Comparator with the default values.
*
* Parameters:
*  void
*
* Return:
*  void 
*
* Global variables:
*  CapSense_CompCH0_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*  
*******************************************************************************/
void CapSense_CompCH0_Start(void) 
{

    if ( CapSense_CompCH0_initVar == 0u )
    {
        CapSense_CompCH0_Init();
        
        CapSense_CompCH0_initVar = 1u;
    }   

    /* Enable power to comparator */
    CapSense_CompCH0_Enable();    
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_CompCH0_Stop(void) 
{
    /* Disable power to comparator */
    CapSense_CompCH0_PWRMGR &= (uint8)(~CapSense_CompCH0_ACT_PWR_EN);
    CapSense_CompCH0_STBY_PWRMGR &= (uint8)(~CapSense_CompCH0_STBY_PWR_EN);
    
    #if (CY_PSOC5A)
        /* Enable the variable */
        CapSense_CompCH0_restoreReg = 1u;

        /* Save the control register before clearing it */
        CapSense_CompCH0_lowPowerBackup.compCRReg = CapSense_CompCH0_CR;
        CapSense_CompCH0_CR = CapSense_CompCH0_COMP_REG_CLR;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_SetSpeed
********************************************************************************
*
* Summary:
*  This function sets the speed of the Analog Comparator. The faster the speed
*  the more power that is used.
*
* Parameters:
*  speed: (uint8) Sets operation mode of Comparator
*
* Return:
*  void
*
*******************************************************************************/
void CapSense_CompCH0_SetSpeed(uint8 speed) 
{
    /* Clear and Set power level */    
    CapSense_CompCH0_CR = (CapSense_CompCH0_CR & (uint8)(~CapSense_CompCH0_PWR_MODE_MASK)) |
                           (speed & CapSense_CompCH0_PWR_MODE_MASK);

    /* Set trim value for high speed comparator */
    if(speed == CapSense_CompCH0_HIGHSPEED)
    {
        /* PSoC5A */
        #if (CY_PSOC5A)
            CapSense_CompCH0_TR = CapSense_CompCH0_HS_TRIM_TR0;
        #endif /* CY_PSOC5A */
        
        /* PSoC3, PSoC5LP or later */
        #if (CY_PSOC3 || CY_PSOC5LP) 
            CapSense_CompCH0_TR0 = CapSense_CompCH0_HS_TRIM_TR0;
            CapSense_CompCH0_TR1 = CapSense_CompCH0_HS_TRIM_TR1;
        #endif /* CY_PSOC3 || CY_PSOC5LP */
    }
    else
    {
    /* PSoC5A */
        #if (CY_PSOC5A)
            CapSense_CompCH0_TR = CapSense_CompCH0_LS_TRIM_TR0;
        #endif /* CY_PSOC5A */
        
        /* PSoC3, PSoC5LP or later */
        #if (CY_PSOC3 || CY_PSOC5LP) 
            CapSense_CompCH0_TR0 = CapSense_CompCH0_LS_TRIM_TR0;
            CapSense_CompCH0_TR1 = CapSense_CompCH0_LS_TRIM_TR1;
        #endif /* CY_PSOC3 || CY_PSOC5LP */
    }

}


/*******************************************************************************
* Function Name: CapSense_CompCH0_GetCompare
********************************************************************************
*
* Summary:
*  This function returns the comparator output value.
*  This value is not affected by the Polarity parameter.
*  This valuea lways reflects a noninverted state.
*
* Parameters:
*   None
*
* Return:
*  (uint8)  0     - if Pos_Input less than Neg_input
*           non 0 - if Pos_Input greater than Neg_input.
*
*******************************************************************************/
uint8 CapSense_CompCH0_GetCompare(void) 
{
    return( CapSense_CompCH0_WRK & CapSense_CompCH0_CMP_OUT_MASK);
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_trimAdjust
********************************************************************************
*
* Summary:
*  This function adjusts the value in the low nibble/high nibble of the Analog 
*  Comparator trim register
*
* Parameters:  
*  nibble:
*      0 -- adjusts the value in the low nibble
*      1 -- adjusts the value in the high nibble
*
* Return:
*  None
*
* Theory: 
*  Function assumes comparator block is setup for trim adjust.
*  Intended to be called from Comp_ZeroCal()
* 
* Side Effects:
*  Routine uses a course 1ms delay following each trim adjustment to allow 
*  the comparator output to respond.
*
*******************************************************************************/
static void CapSense_CompCH0_trimAdjust(uint8 nibble) 
{
    uint8 trimCnt, trimCntMax;
    uint8 cmpState;   

    /* get current state of comparator output */
    cmpState = CapSense_CompCH0_WRK & CapSense_CompCH0_CMP_OUT_MASK;
    
    if (nibble == 0u)
    {    
        /* if comparator output is high, negative offset adjust is required */
        if ( cmpState != 0u )
        {
            /* PSoC5A */
            #if (CY_PSOC5A)
                CapSense_CompCH0_TR |= CapSense_CompCH0_CMP_TRIM1_DIR;
            #endif /* CY_PSOC5A */
            
            /* PSoC3, PSoC5LP or later */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CapSense_CompCH0_TR0 |= CapSense_CompCH0_CMP_TR0_DIR;
            #endif /* CY_PSOC3 || CY_PSOC5LP */
        }
    }
    else
    {
        /* if comparator output is low, positive offset adjust is required */
        if ( cmpState == 0u )
        {
            /* PSoC5A */
            #if (CY_PSOC5A)
                CapSense_CompCH0_TR |= CapSense_CompCH0_CMP_TRIM2_DIR; 
            #endif /* CY_PSOC5A */
            
            /* PSoC3, PSoC5LP or later */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CapSense_CompCH0_TR1 |= CapSense_CompCH0_CMP_TR1_DIR;
            #endif /* CY_PSOC3 || CY_PSOC5LP */
        }
    }

    /* Increment trim value until compare output changes state */
	
    /* PSoC5A */
	#if (CY_PSOC5A)
	    trimCntMax = 7u;
    #endif
	
	/* PSoC3, PSoC5LP or later */
	#if (CY_PSOC3 || CY_PSOC5LP)
    	if(nibble == 0u)
    	{
    		trimCntMax = 15u;
    	}
    	else
    	{
    		trimCntMax = 7u;
    	}
	#endif
	
    for ( trimCnt = 0u; trimCnt < trimCntMax; trimCnt++ )
	{
        if (nibble == 0u)
        {
            /* PSoC5A */
            #if (CY_PSOC5A)
                CapSense_CompCH0_TR += 1u;
            #endif /* CY_PSOC5A */
            
            /* PSoC3, PSoC5LP or later */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CapSense_CompCH0_TR0 += 1u;
            #endif /* CY_PSOC3 || CY_PSOC5LP */
        }
        else
        {
            /* PSoC5A */
            #if (CY_PSOC5A)
                CapSense_CompCH0_TR += 0x10u;
            #endif /* CY_PSOC5A */
            
            /* PSoC3, PSoC5LP or later */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CapSense_CompCH0_TR1 += 1u;
            #endif /* CY_PSOC3 || CY_PSOC5LP */
        }
        
        CyDelayUs(10u);
        
        /* Check for change in comparator output */
        if ((CapSense_CompCH0_WRK & CapSense_CompCH0_CMP_OUT_MASK) != cmpState)
        {
            break;      /* output changed state, trim phase is complete */
        }        
    }    
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_ZeroCal
********************************************************************************
*
* Summary:
*  This function calibrates the offset of the Analog Comparator.
*
* Parameters:
*  None
*
* Return:
*  (uint16)  value written in trim register when calibration complete.
*
* Theory: 
*  This function is used to optimize the calibration for user specific voltage
*  range.  The comparator trim is adjusted to counter transistor offsets
*   - offset is defined as positive if the output transitions to high before inP
*     is greater than inN
*   - offset is defined as negative if the output transitions to high after inP
*     is greater than inP
*
*  PSoC5A
*  The Analog Comparator provides 1 byte for offset trim.  The byte contains two
*  4 bit trim fields - one is a course trim and the other allows smaller
*  offset adjustments only for slow modes.
*  - low nibble - fine trim
*  - high nibble - course trim
*  PSoC3, PSoC5LP or later
*  The Analog Comparator provides 2 bytes for offset trim.  The bytes contain two
*  5 bit trim fields - one is a course trim and the other allows smaller
*  offset adjustments only for slow modes.
*  - TR0 - fine trim
*  - TR1 - course trim
*
*  Trim algorithm is a two phase process
*  The first phase performs course offset adjustment
*  The second phase serves one of two purposes depending on the outcome of the
*  first phase
*  - if the first trim value was maxed out without a comparator output 
*    transition, more offset will be added by adjusting the second trim value.
*  - if the first trim phase resulted in a comparator output transition, the
*    second trim value will serve as fine trim (in the opposite direction)to
*    ensure the offset is < 1 mV.
*
* Trim Process:   
*  1) User applies a voltage to the negative input.  Voltage should be in the
*     comparator operating range or an average of the operating voltage range.
*  2) Clear registers associated with analog routing to the positive input.
*  3) Disable Hysteresis
*  4) Set the calibration bit to short the negative and positive inputs to
*     the users calibration voltage.
*  5) Clear the TR register  ( TR = 0x00 )
*  ** LOW MODES
*  6) Check if compare output is high, if so, set the MSb of course trim field 
*     to a 1.
*  7) Increment the course trim field until the compare output changes
*  8) Check if compare output is low, if so, set the MSb of fine trim field
*     to a 1.
*  9) Increment the fine trim field until the compare output changes
*  ** FAST MODE - skip the steps 8,9
*
* Side Effects:
*  Routine clears analog routing associated with the comparator positive input.  
*  This may affect routing of signals from other components that are connected
*  to the positive input of the comparator.
*
*******************************************************************************/
uint16 CapSense_CompCH0_ZeroCal(void) 
{
    uint8 tmpSW0;
    uint8 tmpSW2;
    uint8 tmpSW3;
    uint8 tmpCR;

    /* Save a copy of routing registers associated with inP */
    tmpSW0 = CapSense_CompCH0_SW0;
    tmpSW2 = CapSense_CompCH0_SW2;
    tmpSW3 = CapSense_CompCH0_SW3;

     /* Clear routing for inP, retain routing for inN */
    CapSense_CompCH0_SW0 = 0x00u;
    CapSense_CompCH0_SW2 = 0x00u;
    CapSense_CompCH0_SW3 = tmpSW3 & (uint8)(~CapSense_CompCH0_CMP_SW3_INPCTL_MASK);

    /* Preserve original configuration
     * - turn off Hysteresis
     * - set calibration bit - shorts inN to inP
    */
    tmpCR = CapSense_CompCH0_CR;
    CapSense_CompCH0_CR |= (CapSense_CompCH0_CAL_ON | CapSense_CompCH0_HYST_OFF);
    
    /* Write default low values to trim register - no offset adjust */
    /* PSoC5A */
    #if (CY_PSOC5A)
        CapSense_CompCH0_TR = CapSense_CompCH0_DEFAULT_CMP_TRIM;
    #endif /* CY_PSOC5A */
    
    /* PSoC3, PSoC5LP or later */
    #if (CY_PSOC3 || CY_PSOC5LP)
        CapSense_CompCH0_TR0 = CapSense_CompCH0_DEFAULT_CMP_TRIM;
        CapSense_CompCH0_TR1 = CapSense_CompCH0_DEFAULT_CMP_TRIM;
    #endif /* CY_PSOC3 || CY_PSOC5LP */
	
	/* Two phase trim - slow modes, one phase trim - for fast */ 
    if ( (CapSense_CompCH0_CR & CapSense_CompCH0_PWR_MODE_MASK) == CapSense_CompCH0_PWR_MODE_FAST)
    {
        CapSense_CompCH0_trimAdjust(0u);
    }
    else /* default to trim for fast modes */
    {
        CapSense_CompCH0_trimAdjust(1u);
		CapSense_CompCH0_trimAdjust(0u);
    }
   
    /* Restore Config Register */
    CapSense_CompCH0_CR = tmpCR;
    
    /* Restore routing registers for inP */
    CapSense_CompCH0_SW0 = tmpSW0;
    CapSense_CompCH0_SW2 = tmpSW2;
    CapSense_CompCH0_SW3 = tmpSW3;
    
    /* PSoC5A */
    #if (CY_PSOC5A)
        return (uint16) CapSense_CompCH0_TR;
    #endif /* CY_PSOC5A */
    
    /* PSoC3, PSoC5LP or later */
    #if (CY_PSOC3 || CY_PSOC5LP)
        return ((uint16)((uint16)CapSense_CompCH0_TR1 << 8u) | (CapSense_CompCH0_TR0));        
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/*******************************************************************************
* Function Name: CapSense_CompCH0_LoadTrim
********************************************************************************
*
* Summary:
*  This function stores a value in the Analog Comparator trim register.
*
* Parameters:  
*  uint8 trimVal - trim value.  This value is the same format as the value 
*  returned by the _ZeroCal routine.
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CompCH0_LoadTrim(uint16 trimVal) 
{
    /* Stores value in the Analog Comparator trim register */
    /* PSoC5A */
    #if (CY_PSOC5A)
        CapSense_CompCH0_TR = (uint8) trimVal;
    #endif /* CY_PSOC5A */
    
    /* PSoC3, PSoC5LP or later */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Stores value in the Analog Comparator trim register for P-type load */
        CapSense_CompCH0_TR0 = (uint8) trimVal;
        
        /* Stores value in the Analog Comparator trim register for N-type load */
        CapSense_CompCH0_TR1 = (uint8) (trimVal >> 8); 
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


#if (CY_PSOC3 || CY_PSOC5LP)

    /*******************************************************************************
    * Function Name: CapSense_CompCH0_PwrDwnOverrideEnable
    ********************************************************************************
    *
    * Summary:
    *  This is the power down over-ride feature. This function ignores sleep 
    *  parameter and allows the component to stay active during sleep mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CapSense_CompCH0_PwrDwnOverrideEnable(void) 
    {
        /* Set the pd_override bit in CMP_CR register */
        CapSense_CompCH0_CR |= CapSense_CompCH0_PWRDWN_OVRD;
    }


    /*******************************************************************************
    * Function Name: CapSense_CompCH0_PwrDwnOverrideDisable
    ********************************************************************************
    *
    * Summary:
    *  This is the power down over-ride feature. This allows the component to stay
    *  inactive during sleep.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CapSense_CompCH0_PwrDwnOverrideDisable(void) 
    {
        /* Reset the pd_override bit in CMP_CR register */
        CapSense_CompCH0_CR &= (uint8)(~CapSense_CompCH0_PWRDWN_OVRD);
    }
#endif /* (CY_PSOC3 || CY_PSOC5LP) */


/* [] END OF FILE */
