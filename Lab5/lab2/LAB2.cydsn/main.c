/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * This file is necessary for your project to build.
 * Please do not delete it.
 *
 * ========================================
*/

#include <device.h>

uint16 adcResult = 0;

void main()
{
	unsigned char j = 50;				// milliseconds delay
	
	
	LCD_Char_1_Start();					// initialize lcd
	LCD_Char_1_ClearDisplay();
	LCD_Char_1_PrintString("ADC : ");
	
	ADC_DelSig_1_Start();				// start the ADC_DelSig_1
	ADC_DelSig_1_StartConvert();		// start the ADC_DelSig_1 conversion


    for(;;)
    {
		if( ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT) )
		{
			LCD_Char_1_Position(0, 6);
			LCD_Char_1_PrintString("     ");			// clean up the previous display
			LCD_Char_1_Position(0, 6);
			adcResult = ADC_DelSig_1_GetResult16();		// read the adc and assign the value adcResult 
   		    if (adcResult & 0x8000)
   		    {
    		    adcResult = 0;       // ignore negative ADC results
   		    }
   		    else if (adcResult >= 0xfff)
   		    {
    		    adcResult = 0xfff;      // ignore high ADC results
   		    }
			LCD_Char_1_PrintNumber(adcResult);
			CyDelay(j);									// delay in milliseconds
		}
    }
}

/* [] END OF FILE */