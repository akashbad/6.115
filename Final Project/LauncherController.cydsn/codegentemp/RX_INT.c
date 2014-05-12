/*******************************************************************************
* File Name: RX_INT.c  
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


#include <cydevice_trm.h>
#include <CyLib.h>
#include <RX_INT.h>

#if !defined(RX_INT__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START RX_INT_intc` */

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
* Function Name: RX_INT_Start
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
void RX_INT_Start(void)
{
    /* For all we know the interrupt is active. */
    RX_INT_Disable();

    /* Set the ISR to point to the RX_INT Interrupt. */
    RX_INT_SetVector(&RX_INT_Interrupt);

    /* Set the priority. */
    RX_INT_SetPriority((uint8)RX_INT_INTC_PRIOR_NUMBER);

    /* Enable it. */
    RX_INT_Enable();
}


/*******************************************************************************
* Function Name: RX_INT_StartEx
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
void RX_INT_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    RX_INT_Disable();

    /* Set the ISR to point to the RX_INT Interrupt. */
    RX_INT_SetVector(address);

    /* Set the priority. */
    RX_INT_SetPriority((uint8)RX_INT_INTC_PRIOR_NUMBER);

    /* Enable it. */
    RX_INT_Enable();
}


/*******************************************************************************
* Function Name: RX_INT_Stop
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
void RX_INT_Stop(void)
{
    /* Disable this interrupt. */
    RX_INT_Disable();

    /* Set the ISR to point to the passive one. */
    RX_INT_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: RX_INT_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for RX_INT.
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
CY_ISR(RX_INT_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START RX_INT_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: RX_INT_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling RX_INT_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use RX_INT_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void RX_INT_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)RX_INT__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: RX_INT_GetVector
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
cyisraddress RX_INT_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)RX_INT__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: RX_INT_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling RX_INT_Start
*   or RX_INT_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   RX_INT_Start or RX_INT_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void RX_INT_SetPriority(uint8 priority)
{
    *RX_INT_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: RX_INT_GetPriority
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
uint8 RX_INT_GetPriority(void)
{
    uint8 priority;


    priority = *RX_INT_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: RX_INT_Enable
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
void RX_INT_Enable(void)
{
    /* Enable the general interrupt. */
    *RX_INT_INTC_SET_EN = RX_INT__INTC_MASK;
}


/*******************************************************************************
* Function Name: RX_INT_GetState
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
uint8 RX_INT_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*RX_INT_INTC_SET_EN & (uint32)RX_INT__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: RX_INT_Disable
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
void RX_INT_Disable(void)
{
    /* Disable the general interrupt. */
    *RX_INT_INTC_CLR_EN = RX_INT__INTC_MASK;
}


/*******************************************************************************
* Function Name: RX_INT_SetPending
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
void RX_INT_SetPending(void)
{
    *RX_INT_INTC_SET_PD = RX_INT__INTC_MASK;
}


/*******************************************************************************
* Function Name: RX_INT_ClearPending
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
void RX_INT_ClearPending(void)
{
    *RX_INT_INTC_CLR_PD = RX_INT__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
