/*******************************************************************************
* File Name: CapSense_TunerHelper.h
* Version 3.40
*
* Description:
*  This file provides constants and structure declarations for the tunner hepl
*  APIs for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_CapSense_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_CapSense_H

#include "CapSense.h"
#include "CapSense_CSHL.h"
#if (CapSense_TUNER_API_GENERATE)
    #include "CapSense_MBX.h"
    #include "EZI2C.h"
#endif /* (CapSense_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define CapSense_DEFAULT_MAILBOXES_NUMBER   (1u)


/***************************************
*        Function Prototypes
***************************************/

void CapSense_TunerStart(void) ;
void CapSense_TunerComm(void) ;

#if (CapSense_TUNER_API_GENERATE)
    CapSense_NO_STRICT_VOLATILE void CapSense_ProcessAllWidgets(volatile CapSense_OUTBOX *outbox)
	                                        					;

    extern volatile CapSense_MAILBOXES CapSense_mailboxesComm;
#endif /* (CapSense_TUNER_API_GENERATE) */

#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_CapSense_H)*/


/* [] END OF FILE */
