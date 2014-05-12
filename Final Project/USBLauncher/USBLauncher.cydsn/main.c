/*****************************************************************************
* File Name: main.c
*
* Version: 1.1
*
* Description:
* The example project will include a full speed USB component configured to enumerate 
* as a HID. The project will read a value from an ADC and monitor the status of a push
* button on a DVK board. This collected information will be transfered to the host via an
* IN tranfser. An interface application will be used in conjunction to allow the user to adjust the 
* Duty Cycle of a PWM and control the On/Off state of an LED. This information will be transfered to 
* the PSoC via an OUT transfer.
*
* Owner:
* Robert Murphy (RLRM)
*
* Hardware Dependency:
* CY8CKIT-001
* CY8CKIT-030
* CY8CKIT-050
*
* Code Tested With:
* 1. PSoC Creator 2.0
* 2. DP8051-Keil Generic Compiler
* 3. ARM GCC Compiler
******************************************************************************
* Copyright (2011), Cypress Semiconductor Corporation.
******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*****************************************************************************/

#include <project.h>
#include <stdio.h>

/* Declare defines for constant variables */
#define DEVICE_ID 0
#define IN_ENDPOINT 0x01
#define OUT_ENDPOINT 0x02
#define MAX_NUM_BYTES  8
#define UnassignedAddress 0

/* Array Positioning for IN Data */
#define Button_Status_Pos 0
#define ADC_Pos_1 1
#define ADC_Pos_2 2
#define ADC_Pos_3 3
#define ADC_Pos_4 4

/* Array Positioning for OUT Data */
#define LED_State_Pos 0
#define PWM_DC_Pos 1

/* Input and Output Data Buffers */
uint8 IN_Data_Buffer[8];  /* [0] = Button Status, [1..4] = ADC Result, [5..7] = Unused */
uint8 OUT_Data_Buffer[8]; /* [0] = LED State, [1] = PWM Duty Cycle, [2..7] = Unused */

/* Display buffer for Character LCD */
char ADC_Display_Data[10];
char PWM_Duty_Display_Data[5];

/* Various Application Variables */
int32 ADC_Result;
int8 PWM_DutyCycle;
uint8 OUT_COUNT;
uint16 LCD_Update_Timer = 0x00;

/* Function Prototypes */
void Process_EP2 (void);
void Process_EP1 (void);
void Update_LCD (void); 

void main (void)
{
	/*Enable Global Interrupts */
	CYGlobalIntEnable; 
    
	/*Initalize ADC */
	ADC_Start();
	ADC_StartConvert();
	
	/*Initalize LCD and place static text */
	LCD_Start();
	LCD_Position(0,0);
	LCD_PrintString("PSoC Generic HID");
	LCD_Position(1,0);
	LCD_PrintString("AD:");
	LCD_Position(1,11);
	LCD_PrintString("D:");
	
	/*Initalize PWM */
	PWM_Start();
	PWM_WriteCompare(10);
	
	/*Initalize LED Off */
	LED_2_Write(1);
	
    /* Start USBFS Operation for the DEVICE_ID and with 5V operation  */
    USBFS_Start(0, USBFS_DWR_VDDD_OPERATION); 
	
	/* Ensure device is configured before running code */
    while(USBFS_bGetConfiguration() == 0x00)
	{
		/* Waiting for device to be configured */
	}
	
    for(;;)
    {
		/* Prepare the push button and ADC data to be sent to the host */
		Process_EP1();
		
		/*Check to see if the IN Endpoint is empty. If so, load it with Input data to be tranfered */
		if(USBFS_GetEPState(IN_ENDPOINT) == USBFS_IN_BUFFER_EMPTY)
		{
			/* Load data located in IN_Data_Buffer and load it into the IN endpoint */
			USBFS_LoadEP(IN_ENDPOINT, IN_Data_Buffer, MAX_NUM_BYTES);
			/* Enable the OUT endpoint to recieve data */
			USBFS_EnableOutEP(OUT_ENDPOINT);
		}	
		
		/* Check to see if the OUT Endpoint is full from a recieved transaction. */
		if(USBFS_GetEPState(OUT_ENDPOINT) == USBFS_OUT_BUFFER_FULL)
		{
			/* Get the number of bytes recieved */
			OUT_COUNT = USBFS_GetEPCount(OUT_ENDPOINT);
			/* Read the OUT endpoint and store data in OUT_Data_Buffer */
			USBFS_ReadOutEP(OUT_ENDPOINT, OUT_Data_Buffer, OUT_COUNT);
			/* Re-enable OUT endpoint */
			USBFS_EnableOutEP(OUT_ENDPOINT);
		}
		
		/* Process the data recieved from the host */
		Process_EP2();
		
		/* Impliment a perodic delay for updating the LCD */
		if(LCD_Update_Timer >= 0x08FF)
		{
			/* Call function to update Character LCD with ADC and PWM Duty Cycle value */
			Update_LCD();
		}
		
		/* Increment LCD Timer */
		LCD_Update_Timer ++;
    }
}

/**********************************************************************
* NAME: Process_EP2
* 
* DESCRIPTION: Function to process the OUT data (data sent from the PC).
* This data includes the state of LED_2 (On or Off) and the duty cycle
* of the PWM attached to LED_1.
* 
***********************************************************************/
void Process_EP2 (void)
{
	/* Update PWM Compare Value */
	if((OUT_Data_Buffer[PWM_DC_Pos] > 0) && (OUT_Data_Buffer[PWM_DC_Pos] <= 100))
	{
		PWM_DutyCycle = OUT_Data_Buffer[PWM_DC_Pos];
		PWM_WriteCompare(PWM_DutyCycle);
	}
	
	/* Check to see if LED_2 Should be on */
	if(OUT_Data_Buffer[LED_State_Pos] != 0)
	{
		LED_2_Write(1);
	}
	else
	{
		LED_2_Write(0);
	}
}

/**********************************************************************
* NAME: Process_EP1
* 
* DESCRIPTION: Function to process the IN data (data sent to the PC).
* This data includes the value read from the DelSig ADC and the current 
* status of push button connected to SW_In.
* 
***********************************************************************/
void Process_EP1 (void)
{
	/* Check Status of Switch 1 */
	if(SW_In_Read() != 0)
	{
		IN_Data_Buffer[Button_Status_Pos] = 0x00;
	}
	else
	{
		IN_Data_Buffer[Button_Status_Pos] = 0xff;
	}
	
	/* Check if ADC data is ready */
	if(ADC_IsEndConversion(ADC_RETURN_STATUS) != 0x00)
	{
		/* Read ADC Sample */
		ADC_Result = ADC_GetResult32();
		
		/* Load Bits 7-0 of ADC_Value into the Input Buffer */
		IN_Data_Buffer[ADC_Pos_1] = (int8) 0x000000FF & (ADC_Result >>  24);
		
		/* Load Bits 15-8 of ADC_Value into the Input Buffer */
		IN_Data_Buffer[ADC_Pos_2] = (int8) 0x000000FF & (ADC_Result >>  16);
		
		/* Load Bits 23-16 of ADC_Value into the Input Buffer */
		IN_Data_Buffer[ADC_Pos_3] = (int8) 0x000000FF & (ADC_Result >>  8);
		
		/* Load Bits 31-24 of ADC_Value into the Input Buffer */
		IN_Data_Buffer[ADC_Pos_4] = (int8) 0x000000FF & ADC_Result;
	}
}

/**********************************************************************
    * NAME: Update_LCD
* 
* DESCRIPTION: Function periodically update the Character LCD with the
* ADC value and PWM duty cycle.
* 
***********************************************************************/
void Update_LCD (void)
{
	/* Convert ADC Value to CHAR and display on Character LCD */
	sprintf(ADC_Display_Data, "%-7ld", ADC_Result);
	LCD_Position(1,3);
	LCD_PrintString(ADC_Display_Data);
	
	/* Convert PWM Duty Cycle to CHAR and display on Character LCD */
	sprintf(PWM_Duty_Display_Data, "%-3d", (int16)PWM_ReadCompare());
	LCD_Position(1,13);
	LCD_PrintString(PWM_Duty_Display_Data);	
	
	/* Reset LCD Update Timer */
	LCD_Update_Timer = 0x00;
}
/* [] END OF FILE */
