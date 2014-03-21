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

void main()
{
	
    for(;;)
    {   
        Pin_1_Write(1);
        CyDelay(250);
        Pin_1_Write(0);
        CyDelay(250);
        Pin_1_Write(1);
        CyDelay(250);
        Pin_1_Write(0);
        CyDelay(250);
        Pin_1_Write(1);
        CyDelay(250);
        Pin_1_Write(0);
        CyDelay(250);
        
        Pin_1_Write(1);
        CyDelay(500);
        Pin_1_Write(0);
        CyDelay(500);
        Pin_1_Write(1);
        CyDelay(500);
        Pin_1_Write(0);
        CyDelay(500);
        Pin_1_Write(1);
        CyDelay(500);
        Pin_1_Write(0);
        CyDelay(500);
        
        Pin_1_Write(1);
        CyDelay(250);
        Pin_1_Write(0);
        CyDelay(250);
        Pin_1_Write(1);
        CyDelay(250);
        Pin_1_Write(0);
        CyDelay(250);
        Pin_1_Write(1);
        CyDelay(250);
        Pin_1_Write(0);
        CyDelay(1000);
    }
}

/* [] END OF FILE */