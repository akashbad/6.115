/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*   Enumerates as a Virtual Com port.  Receives data from hyper terminal, then 
*   send received data backward. LCD shows the Line settings.
*   
*  To test project:
*   1. Build the project and program the hex file on to the target device.
*   2. Select 3.3V in SW3 and plug-in power to the CY8CKIT-001
*   3. Connect USB cable from the computer to the CY8CKIT-001.
*   4. Select the USB_UART.inf file from the project directory, as the driver 
*      for this example once Windows asks for it.
*   5. Open "Device Manager" and note the COM port number for "Example Project"
*      device.
*   6. Open "HyperTerminal" application and make new connection to noted COM port
*   7. Type the message, observe echo data received.
*
* Related Document:
*  Universal Serial Bus Specification Revision 2.0 
*  Universal Serial Bus Class Definitions for Communications Devices 
*  Revision 1.2
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>
#include "stdio.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif


#define BUFFER_LEN  64u

char8 *parity[] = { "None", "Odd", "Even", "Mark", "Space" };
char8 *stop[] = { "1", "1.5", "2" };

void main()
{
    uint16 count;
    uint8 buffer[BUFFER_LEN];
    char8 lineStr[20];
    uint8 state;
    
    /* Enable Global Interrupts */
    CyGlobalIntEnable;                        

    /* Start USBFS Operation with 3V operation */
    USBUART_1_Start(0u, USBUART_1_3V_OPERATION);

    /* Start LCD */
    LCD_Start();
    LCD_PrintString("USB-UART example");
    
    /* Wait for Device to enumerate */
    while(!USBUART_1_GetConfiguration());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_1_CDC_Init();

    /* Main Loop: */
    for(;;)
    {
        if(USBUART_1_DataIsReady() != 0u)               /* Check for input data from PC */
        {   
            count = USBUART_1_GetAll(buffer);           /* Read received data and re-enable OUT endpoint */
            if(count != 0u)
            {
                while(USBUART_1_CDCIsReady() == 0u);    /* Wait till component is ready to send more data to the PC */ 
                USBUART_1_PutData(buffer, count);       /* Send data back to PC */
            }
        }  
        
        state = USBUART_1_IsLineChanged();              /* Check for Line settings changed */
        if(state != 0u)
        {  
            if(state & USBUART_1_LINE_CODING_CHANGED)   /* Show new settings */
            {
                sprintf(lineStr,"BR:%4ld,DB:%d",USBUART_1_GetDTERate(),(uint16)USBUART_1_GetDataBits());
                LCD_Position(0u, 0u);
                LCD_PrintString("                    ");
                LCD_Position(0u, 0u);
                LCD_PrintString(lineStr);
                sprintf(lineStr,"SB:%s,Parity:%s", stop[(uint16)USBUART_1_GetCharFormat()], \
                                                     parity[(uint16)USBUART_1_GetParityType()]);
                LCD_Position(1u, 0u);
                LCD_PrintString("                    ");
                LCD_Position(1u, 0u);
                LCD_PrintString(lineStr);
            }
            if(state & USBUART_1_LINE_CONTROL_CHANGED)  /* Show new settings */
            {   
                state = USBUART_1_GetLineControl();
                sprintf(lineStr,"DTR:%s,RTS:%s",  (state & USBUART_1_LINE_CONTROL_DTR) ? "ON" : "OFF", \
                                                    (state & USBUART_1_LINE_CONTROL_RTS) ? "ON" : "OFF");
                LCD_Position(1u, 0u);
                LCD_PrintString("                    ");
                LCD_Position(1u, 0u);
                LCD_PrintString(lineStr);
            
            }
        }
    }   
}


/* [] END OF FILE */