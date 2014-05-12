/*******************************************************************************
* File Name: Launcher_UART_Dp.c  
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
#include "Launcher_UART_Dp.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Launcher_UART_Dp__PORT == 15 && ((Launcher_UART_Dp__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Launcher_UART_Dp_Write
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
void Launcher_UART_Dp_Write(uint8 value) 
{
    uint8 staticBits = (Launcher_UART_Dp_DR & (uint8)(~Launcher_UART_Dp_MASK));
    Launcher_UART_Dp_DR = staticBits | ((uint8)(value << Launcher_UART_Dp_SHIFT) & Launcher_UART_Dp_MASK);
}


/*******************************************************************************
* Function Name: Launcher_UART_Dp_SetDriveMode
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
void Launcher_UART_Dp_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Launcher_UART_Dp_0, mode);
}


/*******************************************************************************
* Function Name: Launcher_UART_Dp_Read
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
*  Macro Launcher_UART_Dp_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Launcher_UART_Dp_Read(void) 
{
    return (Launcher_UART_Dp_PS & Launcher_UART_Dp_MASK) >> Launcher_UART_Dp_SHIFT;
}


/*******************************************************************************
* Function Name: Launcher_UART_Dp_ReadDataReg
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
uint8 Launcher_UART_Dp_ReadDataReg(void) 
{
    return (Launcher_UART_Dp_DR & Launcher_UART_Dp_MASK) >> Launcher_UART_Dp_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Launcher_UART_Dp_INTSTAT) 

    /*******************************************************************************
    * Function Name: Launcher_UART_Dp_ClearInterrupt
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
    uint8 Launcher_UART_Dp_ClearInterrupt(void) 
    {
        return (Launcher_UART_Dp_INTSTAT & Launcher_UART_Dp_MASK) >> Launcher_UART_Dp_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
