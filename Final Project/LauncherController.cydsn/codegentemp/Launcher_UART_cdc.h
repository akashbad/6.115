/*******************************************************************************
* File Name: Launcher_UART_cdc.h
* Version 2.60
*
* Description:
*  Header File for the USFS component.
*  Contains CDC class prototypes and constant values.
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_Launcher_UART_cdc_H)
#define CY_USBFS_Launcher_UART_cdc_H

#include "cytypes.h"


/***************************************
* Prototypes of the Launcher_UART_cdc API.
***************************************/

#if (Launcher_UART_ENABLE_CDC_CLASS_API != 0u)
    void Launcher_UART_CDC_Init(void) ;
    void Launcher_UART_PutData(const uint8* pData, uint16 length) ;
    void Launcher_UART_PutString(const char8 string[]) ;
    void Launcher_UART_PutChar(char8 txDataByte) ;
    void Launcher_UART_PutCRLF(void) ;
    uint16 Launcher_UART_GetCount(void) ;
    uint8 Launcher_UART_CDCIsReady(void) ;
    uint8 Launcher_UART_DataIsReady(void) ;
    uint16 Launcher_UART_GetData(uint8* pData, uint16 length) ;
    uint16 Launcher_UART_GetAll(uint8* pData) ;
    uint8 Launcher_UART_GetChar(void) ;
    uint8 Launcher_UART_IsLineChanged(void) ;
    uint32 Launcher_UART_GetDTERate(void) ;
    uint8 Launcher_UART_GetCharFormat(void) ;
    uint8 Launcher_UART_GetParityType(void) ;
    uint8 Launcher_UART_GetDataBits(void) ;
    uint16 Launcher_UART_GetLineControl(void) ;
#endif  /* End Launcher_UART_ENABLE_CDC_CLASS_API*/


/***************************************
*  Constants for Launcher_UART_cdc API.
***************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define Launcher_UART_CDC_SET_LINE_CODING        (0x20u)
#define Launcher_UART_CDC_GET_LINE_CODING        (0x21u)
#define Launcher_UART_CDC_SET_CONTROL_LINE_STATE (0x22u)

#define Launcher_UART_LINE_CODING_CHANGED        (0x01u)
#define Launcher_UART_LINE_CONTROL_CHANGED       (0x02u)

#define Launcher_UART_1_STOPBIT                  (0x00u)
#define Launcher_UART_1_5_STOPBITS               (0x01u)
#define Launcher_UART_2_STOPBITS                 (0x02u)

#define Launcher_UART_PARITY_NONE                (0x00u)
#define Launcher_UART_PARITY_ODD                 (0x01u)
#define Launcher_UART_PARITY_EVEN                (0x02u)
#define Launcher_UART_PARITY_MARK                (0x03u)
#define Launcher_UART_PARITY_SPACE               (0x04u)

#define Launcher_UART_LINE_CODING_SIZE           (0x07u)
#define Launcher_UART_LINE_CODING_RATE           (0x00u)
#define Launcher_UART_LINE_CODING_STOP_BITS      (0x04u)
#define Launcher_UART_LINE_CODING_PARITY         (0x05u)
#define Launcher_UART_LINE_CODING_DATA_BITS      (0x06u)

#define Launcher_UART_LINE_CONTROL_DTR           (0x01u)
#define Launcher_UART_LINE_CONTROL_RTS           (0x02u)


/***************************************
* External data references
***************************************/

extern volatile uint8 Launcher_UART_lineCoding[Launcher_UART_LINE_CODING_SIZE];
extern volatile uint8 Launcher_UART_lineChanged;
extern volatile uint16 Launcher_UART_lineControlBitmap;
extern volatile uint8 Launcher_UART_cdc_data_in_ep;
extern volatile uint8 Launcher_UART_cdc_data_out_ep;

#endif /* End CY_USBFS_Launcher_UART_cdc_H */


/* [] END OF FILE */
