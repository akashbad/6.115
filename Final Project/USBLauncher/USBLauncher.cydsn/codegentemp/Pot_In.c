/*******************************************************************************
* File Name: Pot_In.c  
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
#include "Pot_In.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Pot_In__PORT == 15 && ((Pot_In__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Pot_In_Write
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
void Pot_In_Write(uint8 value) 
{
    uint8 staticBits = (Pot_In_DR & (uint8)(~Pot_In_MASK));
    Pot_In_DR = staticBits | ((uint8)(value << Pot_In_SHIFT) & Pot_In_MASK);
}


/*******************************************************************************
* Function Name: Pot_In_SetDriveMode
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
void Pot_In_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pot_In_0, mode);
}


/*******************************************************************************
* Function Name: Pot_In_Read
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
*  Macro Pot_In_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pot_In_Read(void) 
{
    return (Pot_In_PS & Pot_In_MASK) >> Pot_In_SHIFT;
}


/*******************************************************************************
* Function Name: Pot_In_ReadDataReg
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
uint8 Pot_In_ReadDataReg(void) 
{
    return (Pot_In_DR & Pot_In_MASK) >> Pot_In_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pot_In_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pot_In_ClearInterrupt
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
    uint8 Pot_In_ClearInterrupt(void) 
    {
        return (Pot_In_INTSTAT & Pot_In_MASK) >> Pot_In_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
