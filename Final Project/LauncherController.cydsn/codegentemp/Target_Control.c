/*******************************************************************************
* File Name: Target_Control.c  
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
#include "Target_Control.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Target_Control__PORT == 15 && ((Target_Control__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Target_Control_Write
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
void Target_Control_Write(uint8 value) 
{
    uint8 staticBits = (Target_Control_DR & (uint8)(~Target_Control_MASK));
    Target_Control_DR = staticBits | ((uint8)(value << Target_Control_SHIFT) & Target_Control_MASK);
}


/*******************************************************************************
* Function Name: Target_Control_SetDriveMode
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
void Target_Control_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Target_Control_0, mode);
}


/*******************************************************************************
* Function Name: Target_Control_Read
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
*  Macro Target_Control_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Target_Control_Read(void) 
{
    return (Target_Control_PS & Target_Control_MASK) >> Target_Control_SHIFT;
}


/*******************************************************************************
* Function Name: Target_Control_ReadDataReg
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
uint8 Target_Control_ReadDataReg(void) 
{
    return (Target_Control_DR & Target_Control_MASK) >> Target_Control_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Target_Control_INTSTAT) 

    /*******************************************************************************
    * Function Name: Target_Control_ClearInterrupt
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
    uint8 Target_Control_ClearInterrupt(void) 
    {
        return (Target_Control_INTSTAT & Target_Control_MASK) >> Target_Control_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
