/*******************************************************************************
* File Name: F.c  
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
#include "F.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 F__PORT == 15 && ((F__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: F_Write
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
void F_Write(uint8 value) 
{
    uint8 staticBits = (F_DR & (uint8)(~F_MASK));
    F_DR = staticBits | ((uint8)(value << F_SHIFT) & F_MASK);
}


/*******************************************************************************
* Function Name: F_SetDriveMode
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
void F_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(F_0, mode);
}


/*******************************************************************************
* Function Name: F_Read
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
*  Macro F_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 F_Read(void) 
{
    return (F_PS & F_MASK) >> F_SHIFT;
}


/*******************************************************************************
* Function Name: F_ReadDataReg
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
uint8 F_ReadDataReg(void) 
{
    return (F_DR & F_MASK) >> F_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(F_INTSTAT) 

    /*******************************************************************************
    * Function Name: F_ClearInterrupt
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
    uint8 F_ClearInterrupt(void) 
    {
        return (F_INTSTAT & F_MASK) >> F_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
