/*******************************************************************************
* File Name: A.c  
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
#include "A.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 A__PORT == 15 && ((A__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: A_Write
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
void A_Write(uint8 value) 
{
    uint8 staticBits = (A_DR & (uint8)(~A_MASK));
    A_DR = staticBits | ((uint8)(value << A_SHIFT) & A_MASK);
}


/*******************************************************************************
* Function Name: A_SetDriveMode
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
void A_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(A_0, mode);
}


/*******************************************************************************
* Function Name: A_Read
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
*  Macro A_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 A_Read(void) 
{
    return (A_PS & A_MASK) >> A_SHIFT;
}


/*******************************************************************************
* Function Name: A_ReadDataReg
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
uint8 A_ReadDataReg(void) 
{
    return (A_DR & A_MASK) >> A_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(A_INTSTAT) 

    /*******************************************************************************
    * Function Name: A_ClearInterrupt
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
    uint8 A_ClearInterrupt(void) 
    {
        return (A_INTSTAT & A_MASK) >> A_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
