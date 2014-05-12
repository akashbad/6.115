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

uint8 frame_index;
char8 frame_samples[100];

float position(char8 frame[]);
float position_value;

uint16 a_score;
uint16 b_score;
uint16 turn;

void print_line(char8 message[]);

uint8 score(float position);

uint8 count;
uint8 buffer[80];

char8 *messages[4];
uint8 message_index;
uint8 right_button_state;
uint8 left_button_state;

char8 *patterns[3];
uint8 pattern_index;
uint8 pattern_change_state;

CY_ISR(RX_INT){
    char8 data = Target_UART_ReadRxData();
    if(data == 0x0A){
        //Do nothing with a line feed
        return;
    }
    if(data == 0x0D) {
        //Figure out the average on a carriage return
        if(frame_index < 100) {
            frame_samples[frame_index] = '\0';
        }
        //This is included because the transistor at location 0x10 often sends
        // rogue samples
        if(strcmp(frame_samples, "10 ") != 0){
            position_value = position(frame_samples);
            Target_Control_Write(0);
            if(turn){
                turn = 0;
                b_score += score(position_value);
            } else {
                turn = 1;
                a_score += score(position_value);
            }
            messages[3] = "Fire?";
        }
        frame_index = 0;
        return;
    }
    if(frame_index < 100){      
        frame_samples[frame_index] = data;
    }
    frame_index ++;
}

int main()
{
    frame_index = 0;
    position_value = 0;
    a_score = 0;
    b_score = 0;
    turn = 0;
    
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("0   A:0   B:0  ");
    CyGlobalIntEnable; 
    RX_INT_StartEx(RX_INT);
    
    Target_UART_Start();
    Target_UART_ClearRxBuffer();
    
    message_index = 0;
    messages[0] = "Pattern: Center";
    messages[1] = "X Axis:";
    messages[2] = "Y Axis:";
    messages[3] = "Fire?";
    right_button_state = 0;
    left_button_state = 0;
    
    patterns[0] = "Pattern: Center";
    patterns[1] = "Pattern: Inc";
    patterns[2] = "Pattern: Dec";
    pattern_index = 0;
    pattern_change_state = 0;
    
    Launcher_UART_Start(0, Launcher_UART_3V_OPERATION);
    while(!Launcher_UART_GetConfiguration());
    Launcher_UART_CDC_Init();
    
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    
    /* Main Loop: */ 
    for(;;) 
    {   
        LCD_Position(0, 0);
        LCD_PrintString("    A:    B:   ");
        LCD_Position(0,0);
        LCD_PrintNumber(score(position_value));
        LCD_Position(0,5);
        LCD_PrintNumber(a_score);
        LCD_Position(0,12);
        LCD_PrintNumber(b_score);
        
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
        while(CapSense_IsBusy() != 0);
        uint8 left_button = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
        if(left_button && !left_button_state)
        {
            if(message_index <= 0)
            {
                message_index = 4;
            }
            message_index--;
        }
        left_button_state = left_button;
        
        uint8 right_button = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
        if(right_button && !right_button_state)
        {
            message_index = (message_index + 1) % 4;
        }
        right_button_state = right_button;
        
        LCD_Position(1,0);
        LCD_PrintString("                ");
        LCD_Position(1,0);
        LCD_PrintString(messages[message_index]);
        
        uint16 slider = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
        if(slider == 0xFFFF)
        {
            pattern_change_state = 0;
            continue;
        }
        uint8 slider_half = slider / 50;
        char8 *direction;
        switch(message_index){
            case 0:
                LCD_Position(1,9);
                if(!pattern_change_state)
                {
                    if(slider_half){
                        pattern_index = (pattern_index + 1) % 3;
                    } else {
                        if(pattern_index <= 0)
                        {
                            pattern_index = 3;
                        }
                        pattern_index--;
                    }
                    pattern_change_state = 1;
                }
                messages[0] = patterns[pattern_index];
                break;
            case 1:
                LCD_Position(1,8);
                direction = slider_half ? "right" : "left";
                print_line(direction);
                LCD_PrintString(direction);
                break;
            case 2:
                LCD_Position(1,8);
                direction = slider_half ? "up" : "down";
                print_line(direction);
                LCD_PrintString(direction);
                break;
            case 3:
                print_line("fire");
                Target_Control_Write(1);
                messages[3] = "Firing!";
                break;
        }
    } 

}

float position(char8 frame[])
{
    uint16 running_total = 0;
    uint8 current_value = 0;
    uint8 number_values = 0;
    uint8 index;
    for(index = 0; index < strlen(frame); index++)
    {
        char8 current_character = frame[index];
        if(current_character == ' ')
        {
            running_total += current_value;
            number_values ++;
            continue;
        }
        current_value *= 16;
        switch (current_character) {
            case '0':
                current_value += 0;
                break;
            case '1':
                current_value += 1;
                break;
            case '2':
                current_value += 2;
                break;
            case '3':
                current_value += 3;
                break;
            case '4':
                current_value += 4;
                break;
            case '5':
                current_value += 5;
                break;
            case '6':
                current_value += 6;
                break;
            case '7':
                current_value += 7;
                break;
            case '8':
                current_value += 8;
                break;
            case '9':
                current_value += 9;
                break;
            case 'A':
                current_value += 10;
                break;
            case 'B':
                current_value += 11;
                break;
            case 'C':
                current_value += 12;
                break;
            case 'D':
                current_value += 13;
                break;
            case 'E':
                current_value += 14;
                break;
            case 'F':
                current_value += 15;
                break;
        }   
    }
    return (float)running_total/(float)number_values;
}

void print_line(char8 message[])
{
    while(Launcher_UART_CDCIsReady() == 0);
    Launcher_UART_PutString(message);
    while(Launcher_UART_CDCIsReady() == 0);
    Launcher_UART_PutCRLF();
}

uint8 score(float position) {
    switch (pattern_index) {
        case 0:
            return 10;
            break;
        case 1:
            return position * 100 / 32;
            break;
        case 2:
            return 100 - (position * 100 / 32);
            break;
    }
    return 0;
}