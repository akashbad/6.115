/*******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:
*  The project explains the usage of CapSense CSD component. The 2 buttons and
*  linear sliders are used as sensing elements. LED displays buttons active 
*  state and slider position is shown on LCD.
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

/* Needed for Bargraph */
extern uint8 const CYCODE LCD_customFonts[];

uint16 curPos, oldPos;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  Main function performs following functions:
*   1. Enable global interrupts.
*   2. Initialize CapSense CSD and Start the sensor scanning loop.
*   3. Process scanning results and display it on LCD/LED.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{
    LCD_Start();
    CapSense_CSD_Start();
	
	/* The custom fonts for the bargraph need to be manually loaded */
	LCD_LoadCustomFonts(LCD_customFonts);
    
	LCD_Position(0u, 0u);
    LCD_PrintString("CSD01");

    /* Enable global interrupts */
    CyGlobalIntEnable;

    /* Initialize baselines */ 
    CapSense_CSD_InitializeAllBaselines();
    
    while(1u)
    {
        /* Update all baselines */
        CapSense_CSD_UpdateEnabledBaselines();
        
   		/* Start scanning all enabled sensors */
    	CapSense_CSD_ScanEnabledWidgets();
    
        /* Wait for scanning to complete */
		while(CapSense_CSD_IsBusy() != 0);

		/* Display CapSense state using LED/LCD */
        CapSense_DisplayState();
    }
}

/*******************************************************************************
* Function Name: CapSense_DisplayState
********************************************************************************
* Summary:
*  Function performs following functions:
*   Display Buttons' state using LEDs and Slider state using LCD bargraph
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_DisplayState(void)
{
    /* Display BUTTON0 state */
	if (CapSense_CSD_CheckIsWidgetActive(CapSense_CSD_BUTTON0__BTN)) 
	{
		LED1_Write(1u);
	}
	else
	{
		LED1_Write(0u);
	}
    
	/* Display BUTTON1 state */
	if (CapSense_CSD_CheckIsWidgetActive(CapSense_CSD_BUTTON1__BTN))
	{
		LED2_Write(1u);
	}
	else
	{
		LED2_Write(0u);
	}

    /* Find Slider Position */
    curPos = CapSense_CSD_GetCentroidPos(CapSense_CSD_LINEARSLIDER0__LS);    
    
    /* Reset position */
    if(curPos == 0xFFFFu)
    {
        curPos = 0u;
    }
                
    /* Move bargraph */
    if (curPos != oldPos)
    {
        oldPos = curPos;
        /* Display Slider bargraph */
        if (curPos != 0u)
        {
            LCD_DrawHorizontalBG(0u, 9u, 6u, curPos >> 2);
        }
        
        /* Display Slider position value */
        LCD_Position(1u, 10u);
        LCD_PrintInt16(curPos);
    }
}


/* [] END OF FILE */
