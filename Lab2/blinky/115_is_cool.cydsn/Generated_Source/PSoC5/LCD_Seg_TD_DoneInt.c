/*******************************************************************************
* File Name: LCD_Seg_TD_DoneInt.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <LCD_Seg_TD_DoneInt.H>

#if !defined(LCD_Seg_TD_DoneInt__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START LCD_Seg_TD_DoneInt_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_Start(void)
{
    /* For all we know the interrupt is active. */
    LCD_Seg_TD_DoneInt_Disable();

    /* Set the ISR to point to the LCD_Seg_TD_DoneInt Interrupt. */
    LCD_Seg_TD_DoneInt_SetVector(&LCD_Seg_TD_DoneInt_Interrupt);

    /* Set the priority. */
    LCD_Seg_TD_DoneInt_SetPriority((uint8)LCD_Seg_TD_DoneInt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LCD_Seg_TD_DoneInt_Enable();
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    LCD_Seg_TD_DoneInt_Disable();

    /* Set the ISR to point to the LCD_Seg_TD_DoneInt Interrupt. */
    LCD_Seg_TD_DoneInt_SetVector(address);

    /* Set the priority. */
    LCD_Seg_TD_DoneInt_SetPriority((uint8)LCD_Seg_TD_DoneInt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LCD_Seg_TD_DoneInt_Enable();
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_Stop(void)
{
    /* Disable this interrupt. */
    LCD_Seg_TD_DoneInt_Disable();

    /* Set the ISR to point to the passive one. */
    LCD_Seg_TD_DoneInt_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for LCD_Seg_TD_DoneInt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(LCD_Seg_TD_DoneInt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START LCD_Seg_TD_DoneInt_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling LCD_Seg_TD_DoneInt_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use LCD_Seg_TD_DoneInt_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)LCD_Seg_TD_DoneInt__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress LCD_Seg_TD_DoneInt_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)LCD_Seg_TD_DoneInt__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling LCD_Seg_TD_DoneInt_Start
*   or LCD_Seg_TD_DoneInt_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   LCD_Seg_TD_DoneInt_Start or LCD_Seg_TD_DoneInt_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_SetPriority(uint8 priority)
{
    *LCD_Seg_TD_DoneInt_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 LCD_Seg_TD_DoneInt_GetPriority(void)
{
    uint8 priority;


    priority = *LCD_Seg_TD_DoneInt_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_Enable(void)
{
    /* Enable the general interrupt. */
    *LCD_Seg_TD_DoneInt_INTC_SET_EN = LCD_Seg_TD_DoneInt__INTC_MASK;
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 LCD_Seg_TD_DoneInt_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*LCD_Seg_TD_DoneInt_INTC_SET_EN & (uint32)LCD_Seg_TD_DoneInt__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_Disable(void)
{
    /* Disable the general interrupt. */
    *LCD_Seg_TD_DoneInt_INTC_CLR_EN = LCD_Seg_TD_DoneInt__INTC_MASK;
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_SetPending(void)
{
    *LCD_Seg_TD_DoneInt_INTC_SET_PD = LCD_Seg_TD_DoneInt__INTC_MASK;
}


/*******************************************************************************
* Function Name: LCD_Seg_TD_DoneInt_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void LCD_Seg_TD_DoneInt_ClearPending(void)
{
    *LCD_Seg_TD_DoneInt_INTC_CLR_PD = LCD_Seg_TD_DoneInt__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
