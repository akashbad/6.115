/*******************************************************************************
* File Name: G.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "G.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 G__PORT == 15 && ((G__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: G_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void G_Write(uint8 value) 
{
    uint8 staticBits = (G_DR & (uint8)(~G_MASK));
    G_DR = staticBits | ((uint8)(value << G_SHIFT) & G_MASK);
}


/*******************************************************************************
* Function Name: G_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void G_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(G_0, mode);
}


/*******************************************************************************
* Function Name: G_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro G_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 G_Read(void) 
{
    return (G_PS & G_MASK) >> G_SHIFT;
}


/*******************************************************************************
* Function Name: G_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 G_ReadDataReg(void) 
{
    return (G_DR & G_MASK) >> G_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(G_INTSTAT) 

    /*******************************************************************************
    * Function Name: G_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 G_ClearInterrupt(void) 
    {
        return (G_INTSTAT & G_MASK) >> G_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
