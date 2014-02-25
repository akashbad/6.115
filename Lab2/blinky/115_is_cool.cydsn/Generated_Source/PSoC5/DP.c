/*******************************************************************************
* File Name: DP.c  
* Version 1.80
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
#include "DP.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DP__PORT == 15 && ((DP__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DP_Write
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
void DP_Write(uint8 value) 
{
    uint8 staticBits = (DP_DR & (uint8)(~DP_MASK));
    DP_DR = staticBits | ((uint8)(value << DP_SHIFT) & DP_MASK);
}


/*******************************************************************************
* Function Name: DP_SetDriveMode
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
void DP_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DP_0, mode);
}


/*******************************************************************************
* Function Name: DP_Read
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
*  Macro DP_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DP_Read(void) 
{
    return (DP_PS & DP_MASK) >> DP_SHIFT;
}


/*******************************************************************************
* Function Name: DP_ReadDataReg
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
uint8 DP_ReadDataReg(void) 
{
    return (DP_DR & DP_MASK) >> DP_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DP_INTSTAT) 

    /*******************************************************************************
    * Function Name: DP_ClearInterrupt
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
    uint8 DP_ClearInterrupt(void) 
    {
        return (DP_INTSTAT & DP_MASK) >> DP_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
