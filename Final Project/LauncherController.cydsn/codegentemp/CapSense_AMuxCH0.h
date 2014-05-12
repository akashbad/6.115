/*******************************************************************************
* File Name: CapSense_AMuxCH0.h
* Version 3.40
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module CapSense_CSD_AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_AMUX_CapSense_AMuxCH0_H)
#define CY_CAPSENSE_CSD_AMUX_CapSense_AMuxCH0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void CapSense_AMuxCH0_Start(void);
void CapSense_AMuxCH0_Init(void);
void CapSense_AMuxCH0_Stop(void);
void CapSense_AMuxCH0_Select(uint8 channel) CYREENTRANT;
void CapSense_AMuxCH0_FastSelect(uint8 channel) CYREENTRANT;
void CapSense_AMuxCH0_DisconnectAll(void) CYREENTRANT;
/* The Connect and Disconnect functions are declared elsewhere */
/* void CapSense_AMuxCH0_Connect(uint8 channel); */
/* void CapSense_AMuxCH0_Disconnect(uint8 channel); */


/***************************************
*     Initial Parameter Constants
***************************************/

#define CapSense_AMuxCH0_CHANNELS  (7u + 2u +1u+ 0u)
#define CapSense_AMuxCH0_MUXTYPE   (1u)


/***************************************
*             API Constants
***************************************/

#define CapSense_AMuxCH0_NULL_CHANNEL   (0xFFu)
#define CapSense_AMuxCH0_MUX_SINGLE     (1u)
#define CapSense_AMuxCH0_MUX_DIFF       (2u)


/***************************************
*        Conditional Functions
***************************************/

#if (CapSense_AMuxCH0_MUXTYPE == CapSense_AMuxCH0_MUX_SINGLE)
#define CapSense_AMuxCH0_Connect(channel) CapSense_AMuxCH0_Set(channel)
#define CapSense_AMuxCH0_Disconnect(channel) CapSense_AMuxCH0_Unset(channel)
#else
    void CapSense_AMuxCH0_Connect(uint8 channel) CYREENTRANT;
    void CapSense_AMuxCH0_Disconnect(uint8 channel) CYREENTRANT;
#endif  /* End (CapSense_AMuxCH0_MUXTYPE == CapSense_AMuxCH0_MUX_SINGLE) */

#endif /* CY_CAPSENSE_CSD_AMUX_CapSense_AMuxCH0_H */


/* [] END OF FILE */
