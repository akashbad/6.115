/*******************************************************************************
* File Name: Launcher_UART_vnd.c
* Version 2.60
*
* Description:
*  USB vendor request handler.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Launcher_UART.h"
#include "Launcher_UART_pvt.h"

#if(Launcher_UART_EXTERN_VND == Launcher_UART_FALSE)


/***************************************
* Vendor Specific Declarations
***************************************/

/* `#START VENDOR_SPECIFIC_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: Launcher_UART_HandleVendorRqst
********************************************************************************
*
* Summary:
*  This routine provide users with a method to implement vendor specifc
*  requests.
*
*  To implement vendor specific requests, add your code in this function to
*  decode and disposition the request.  If the request is handled, your code
*  must set the variable "requestHandled" to TRUE, indicating that the
*  request has been handled.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Launcher_UART_HandleVendorRqst(void) 
{
    uint8 requestHandled = Launcher_UART_FALSE;

    if ((CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_DIR_MASK) == Launcher_UART_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(Launcher_UART_bRequest))
        {
            case Launcher_UART_GET_EXTENDED_CONFIG_DESCRIPTOR:
                #if defined(Launcher_UART_ENABLE_MSOS_STRING)
                    Launcher_UART_currentTD.pData = (volatile uint8 *)&Launcher_UART_MSOS_CONFIGURATION_DESCR[0u];
                    Launcher_UART_currentTD.count = Launcher_UART_MSOS_CONFIGURATION_DESCR[0u];
                    requestHandled  = Launcher_UART_InitControlRead();
                #endif /* End Launcher_UART_ENABLE_MSOS_STRING */
                break;
            default:
                break;
        }
    }

    /* `#START VENDOR_SPECIFIC_CODE` Place your vendor specific request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Vendor Specific Requests
********************************************************************************/

/* `#START VENDOR_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */


#endif /* Launcher_UART_EXTERN_VND */


/* [] END OF FILE */
