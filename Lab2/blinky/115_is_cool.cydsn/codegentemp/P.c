/*******************************************************************************
* File Name: P.c  
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
#include "P.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 P__PORT == 15 && ((P__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: P_Write
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
void P_Write(uint8 value) 
{
    uint8 staticBits = (P_DR & (uint8)(~P_MASK));
    P_DR = staticBits | ((uint8)(value << P_SHIFT) & P_MASK);
}


/*******************************************************************************
* Function Name: P_SetDriveMode
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
void P_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(P_0, mode);
}


/*******************************************************************************
* Function Name: P_Read
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
*  Macro P_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 P_Read(void) 
{
    return (P_PS & P_MASK) >> P_SHIFT;
}


/*******************************************************************************
* Function Name: P_ReadDataReg
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
uint8 P_ReadDataReg(void) 
{
    return (P_DR & P_MASK) >> P_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(P_INTSTAT) 

    /*******************************************************************************
    * Function Name: P_ClearInterrupt
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
    uint8 P_ClearInterrupt(void) 
    {
        return (P_INTSTAT & P_MASK) >> P_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
