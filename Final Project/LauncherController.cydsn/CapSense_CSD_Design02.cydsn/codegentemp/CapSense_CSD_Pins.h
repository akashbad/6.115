/*******************************************************************************
* File Name: CapSense_CSD_Pins.h
* Version 3.40
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_Pins_CapSense_CSD_H)
#define CY_CAPSENSE_CSD_Pins_CapSense_CSD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CapSense_CSD.h"


/***************************************
*        Function Prototypes
***************************************/

void CapSense_CSD_SetAllSensorsDriveMode(uint8 mode) ;
void CapSense_CSD_SetAllCmodsDriveMode(uint8 mode) ;
#if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB)
    void CapSense_CSD_SetAllRbsDriveMode(uint8 mode) ;    
#endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB) */   


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CapSense_CSD_DM_ALG_HIZ         (PIN_DM_ALG_HIZ)
#define CapSense_CSD_DM_DIG_HIZ         (PIN_DM_DIG_HIZ)
#define CapSense_CSD_DM_RES_UP          (PIN_DM_RES_UP)
#define CapSense_CSD_DM_RES_DWN         (PIN_DM_RES_DWN)
#define CapSense_CSD_DM_OD_LO           (PIN_DM_OD_LO)
#define CapSense_CSD_DM_OD_HI           (PIN_DM_OD_HI)
#define CapSense_CSD_DM_STRONG          (PIN_DM_STRONG)
#define CapSense_CSD_DM_RES_UPDWN       (PIN_DM_RES_UPDWN)

/* PC registers defines for sensors */
#define CapSense_CSD_PortCH0__Button0__BTN  CapSense_CSD_PortCH0__Button0__BTN__PC
#define CapSense_CSD_PortCH0__LinearSlider0_e0__LS  CapSense_CSD_PortCH0__LinearSlider0_e0__LS__PC
#define CapSense_CSD_PortCH0__LinearSlider0_e1__LS  CapSense_CSD_PortCH0__LinearSlider0_e1__LS__PC
#define CapSense_CSD_PortCH0__LinearSlider0_e2__LS  CapSense_CSD_PortCH0__LinearSlider0_e2__LS__PC
#define CapSense_CSD_PortCH0__LinearSlider0_e3__LS  CapSense_CSD_PortCH0__LinearSlider0_e3__LS__PC
#define CapSense_CSD_PortCH0__LinearSlider0_e4__LS  CapSense_CSD_PortCH0__LinearSlider0_e4__LS__PC
#define CapSense_CSD_PortCH0__Button1__BTN  CapSense_CSD_PortCH0__Button1__BTN__PC
/* For Cmods*/
#define CapSense_CSD_CmodCH0_Cmod_CH0       CapSense_CSD_CmodCH0__Cmod_CH0__PC


#endif /* (CY_CAPSENSE_CSD_Pins_CapSense_CSD_H) */


/* [] END OF FILE */
