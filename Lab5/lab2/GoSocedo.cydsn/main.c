/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

uint16 msDelay = 100;

void WriteLED(uint8 bi);

int main()
{    
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("MS Delay : ");
	
    ADC_IRQ_Enable();                   // Enable ADC Interrupt
    CYGlobalIntEnable;                  // Enable global interrupts
    
    ADC_Start();
    ADC_StartConvert();

    for(;;)
    {
        WriteLED(0b01000001);       // Write G
        CyDelay(msDelay);
        WriteLED(0b00000011);       // Write O
        CyDelay(msDelay);
        WriteLED(0b11111111);       // Write blank
        CyDelay(msDelay);
        WriteLED(0b01001001);       // Write S
        CyDelay(msDelay);
        WriteLED(0b00000011);       // Write O
        CyDelay(msDelay);
        WriteLED(0b01100011);       // Write C
        CyDelay(msDelay);
        WriteLED(0b01100001);       // Write E
        CyDelay(msDelay);
        WriteLED(0b10000101);       // Write d
        CyDelay(msDelay);
        WriteLED(0b00000011);       // Write O
        CyDelay(msDelay);
        WriteLED(0b11111111);       // Write blank
        CyDelay(msDelay);
    }
}

CY_ISR(ADC_ISR1)
{
    LCD_Position(0,11);
    LCD_PrintString("    ");
    LCD_Position(0,11);
    uint16 adcResult = ADC_GetResult16();
   	if (adcResult & 0x8000)
   	{
        adcResult = 0;       // ignore negative ADC results
   	}
    else if (adcResult >= 0xfff)
    {
	    adcResult = 0xfff;      // ignore high ADC results
    }
    msDelay = (adcResult*25)/128+200;
    LCD_PrintNumber(msDelay);
}

void WriteLED(uint8 bi) 
{
    LED0_Write((bi >> 0) & 1);
    LED1_Write((bi >> 1) & 1);
    LED2_Write((bi >> 2) & 1);
    LED3_Write((bi >> 3) & 1);
    LED4_Write((bi >> 4) & 1);
    LED5_Write((bi >> 5) & 1);
    LED6_Write((bi >> 6) & 1);
    LED7_Write((bi >> 7) & 1);
}

/* [] END OF FILE */
