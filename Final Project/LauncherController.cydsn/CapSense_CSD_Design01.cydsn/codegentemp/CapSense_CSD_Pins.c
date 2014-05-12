/*******************************************************************************
* File Name: CapSense_CSD_Pins.c
* Version 3.40
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_CSD_Pins.h"


/*******************************************************************************
* Function Name: CapSense_CSD_SetAllSensorsDriveMode
********************************************************************************
*
* Summary:
*  Sets the drive mode for the all pins used by capacitive sensors within 
*  CapSense component.
* 
* Parameters:  
*  mode: Desired drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void CapSense_CSD_SetAllSensorsDriveMode(uint8 mode) 
{
    /* Set pins drive mode */
    CyPins_SetPinDriveMode(CapSense_CSD_PortCH0__Button0__BTN, mode);
    CyPins_SetPinDriveMode(CapSense_CSD_PortCH0__LinearSlider0_e0__LS, mode);
    CyPins_SetPinDriveMode(CapSense_CSD_PortCH0__LinearSlider0_e1__LS, mode);
    CyPins_SetPinDriveMode(CapSense_CSD_PortCH0__LinearSlider0_e2__LS, mode);
    CyPins_SetPinDriveMode(CapSense_CSD_PortCH0__LinearSlider0_e3__LS, mode);
    CyPins_SetPinDriveMode(CapSense_CSD_PortCH0__LinearSlider0_e4__LS, mode);
    CyPins_SetPinDriveMode(CapSense_CSD_PortCH0__Button1__BTN, mode);

}



/*******************************************************************************
* Function Name: CapSense_CSD_SetAllCmodsDriveMode
********************************************************************************
*
* Summary:
*  Sets the drive mode for the all pins used by Cmod capacitors within CapSense 
*  component.
* 
* Parameters:  
*  mode: Desired drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void CapSense_CSD_SetAllCmodsDriveMode(uint8 mode) 
{
   /* Set pins drive mode */
    CyPins_SetPinDriveMode(CapSense_CSD_CmodCH0_Cmod_CH0, mode);

}


#if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB)
    /*******************************************************************************
    * Function Name: CapSense_CSD_SetAllRbsDriveMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the drive mode for the all pins used by bleed resistors (Rb) within 
    *  CapSense component. Only available when Current Source is external resistor.
    * 
    * Parameters:  
    *  mode: Desired drive mode.
    *
    * Return: 
    *  None
    *
    *******************************************************************************/
    void CapSense_CSD_SetAllRbsDriveMode(uint8 mode) 
    {
        /* Set pins drive mode */
      
    }
#endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB) */


/* [] END OF FILE */
