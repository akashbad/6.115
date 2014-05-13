/* ================================================
 * Akash Badshah, Final Project, LauncherController
 *
 * This program runs the code for the launcher
 * controller and scoring machine on the PSoC.
 * It handles all button input on the CapSense pad
 * and displays the necessary output to the user 
 * over the attached lcd. It also communicates with
 * the target board over serial. It waits for a 
 * valid and complete frame to indicate a projectile
 * has been spotted and then computes the position
 * accordingly. It communicates with a PC over a 
 * USBUART and issues commands for the actual
 * projectile launcher through that interface.
 * ================================================
*/
#include <project.h>

//Frame buffer variables
uint8 frame_index;
char8 frame_samples[100];

//The function to compute position and the
//global variable to store it in
float position(char8 frame[]);
float position_value;

//Scoring and turn tracking variables
uint16 a_score;
uint16 b_score;
uint16 turn;

//A function to print a line to the computer
void print_line(char8 message[]);

//A function to score the position based on the
// current scoring scheme
uint8 score(float position);

//Variables for keeping track of the menu state
// and button states for capsense buttons that
// control the menu
char8 *messages[4];
uint8 message_index;
uint8 right_button_state;
uint8 left_button_state;

//Variables for keeping track of the current game
// pattern state, changing these will reset the
// scores back to 0
char8 *patterns[3];
uint8 pattern_index;
uint8 pattern_change_state;

//A function to update the top line of the LCD
// with the current game output
void game_output_update();

//A function to read the capsense buttons and
// make according changes to the menus and
// send appropriate signals to the computer
void cap_sense_read();

/*
* The interrupt routine for receiving a message over the Target UART
* This aggregates each frame (delimited by crlf) into a single string
* and computes the position from the frame. If not in target read
* mode it ignores any stray packets, and also shuts off target read
* mode once it has received a good frame.
*
* Because of the noisiness of sensors 0x0F & 0x10 some additional
* logic is added to ignore frames which only include those values
*/
CY_ISR(RX_INT){
    char8 data = Target_UART_ReadRxData();
    if(data == 0x0A || !Target_Control_Read()){
        //Do nothing with a line feed
        return;
    }
    if(data == 0x0D) {
        //Figure out the position on a carriage return
        if(frame_index < 100) {
            //Add the end of string character to the buffer
            frame_samples[frame_index] = '\0';
        }
        //This is included because the transistor at locations 0x0F and 0x10 often sends
        // rogue samples, this has to do with the bend in the boards and would be fixable
        // if a better production process was followed
        if(strcmp(frame_samples, "10 ") != 0 && strcmp(frame_samples, "0F ") != 0 && strcmp(frame_samples, "0F 10 ") !=0 && strcmp(frame_samples, "0C 0F ") != 0){
            //compute the position
            position_value = position(frame_samples);
            //close target read mode
            Target_Control_Write(0);
            //Add to the appropriate score according to the score function
            if(turn){
                turn = 0;
                b_score += score(position_value);
            } else {
                turn = 1;
                a_score += score(position_value);
            }
            // Return our prompt message to normal
            messages[3] = "Fire?";
        }
        //Reset the frame index
        frame_index = 0;
        return;
    }
    //Otherwise we just got data, fill up the frame with the data
    if(frame_index < 100){     
        frame_samples[frame_index] = data;
    }
    frame_index ++;
}

/*
* The main function is responsible for setting up all the
* hardware which needs to be run and also for repeatedly
* polling the CapSense buttons for changes in the game state.
* It communicates relevant game state changes to the User via
* the LCD screen and to the computer via the USBUART.
*/
int main()
{
    //Initialize the game variables
    frame_index = 0;
    position_value = 0;
    a_score = 0;
    b_score = 0;
    turn = 0;
    
    //Initialize the LCD
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("0.0  A:0   B:0  ");
    
    //Enable the target board uart interrupt
    CyGlobalIntEnable; 
    RX_INT_StartEx(RX_INT);
    
    //Start the target uart to receive messages
    // from the 8051
    Target_UART_Start();
    Target_UART_ClearRxBuffer();
    
    //Initialize the menu options
    // and button states
    message_index = 0;
    messages[0] = "Pattern: Center";
    messages[1] = "X Axis:";
    messages[2] = "Y Axis:";
    messages[3] = "Fire?";
    right_button_state = 0;
    left_button_state = 0;
    
    //Initialize the game options
    patterns[0] = "Pattern: Center";
    patterns[1] = "Pattern: Inc";
    patterns[2] = "Pattern: Dec";
    pattern_index = 0;
    pattern_change_state = 0;
    
    //Start the USBUART and wait for a connection
    // to give us a configuration
    Launcher_UART_Start(0, Launcher_UART_3V_OPERATION);
    while(!Launcher_UART_GetConfiguration());
    Launcher_UART_CDC_Init();
    
    //Start up the CapSense and initialize the baselines
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    
    /* Main Loop: */ 
    for(;;) 
    {   
        //Update the scores on the LCD
        game_output_update();
        //Read the cap sense and make necessary moves
        cap_sense_read();
    }  
}

/*
* A function to compute the position of the impact based on the
* frame received from the 8051. It reads through and converts 
* the two character hex numbers to integers and then takes the
* average of those numbers. 
*
* Currently the noise on addresses 0x0F and 0x10 is prohibitively
* high so we automatically ignore responses from those addresses
* which creates a hole in the frame output but also protects
* real values from being biased
*/
float position(char8 frame[])
{
    //Variables to keep track of the current value
    uint16 running_total = 0;
    uint8 current_value = 0;
    uint8 number_values = 0;
    uint8 index;
    //Iterate through the characters in the string
    for(index = 0; index < strlen(frame); index++)
    {
        char8 current_character = frame[index];
        //On a space we add the value to our total
        if(current_character == ' ')
        {
            //If we receive 15 or 16 those are likely noise
            // so we automatically ignore
            if(current_value == 15 || current_value == 16)
            {
                continue;
            }
            running_total += current_value;
            number_values ++;
            continue;
        }
        //Use for shifting up by the digit in base 16
        current_value *= 16;
        //Switch to associate the character with the value
        //There is probably a better way to do this
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
    //Return the float average
    return (float)running_total/(float)number_values;
}

/*
* A function to print a line to the computer over the
* USBUART including placing a CRLF at the end of the 
* communication and appropriate waiting to make sure
* the characters make it across the line
*/
void print_line(char8 message[])
{
    while(Launcher_UART_CDCIsReady() == 0);
    Launcher_UART_PutString(message);
    while(Launcher_UART_CDCIsReady() == 0);
    Launcher_UART_PutCRLF();
}

/*
* A function to score the float position value out of 100
* based on the currently active pattern. The scoring is
* as follows:
* 0: Center based, linearly decreasing from 100-0 as you
*    get further from 16
* 1: Increasing, the higher the position number, the
*    higher the score
* 2: Decreasing, the lower the position number, the 
*    lower the score
*/
uint8 score(float position) {
    switch (pattern_index) {
        case 0:
            if(16 >= position){
                return position * 100 / 16;
            }
            return 100 - ((position - 16.0) * 100 / 16);
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

/*
* This function updates the top line of the LCD with
* the current status of the game including the last
* targeted position, and the scores of players
* A and B
*/
void game_output_update(){
    LCD_Position(0, 0);
    LCD_PrintString("     A:    B:   ");
    LCD_Position(0,0);
    LCD_PrintNumber((uint8)position_value);
    LCD_PrintString(".");
    LCD_PrintNumber((uint8)(position_value*10)%10);
    LCD_Position(0,7);
    LCD_PrintNumber(a_score);
    LCD_Position(0,13);
    LCD_PrintNumber(b_score);
}

/*
* This function does everything necessary to read the cap_sense
* board and either make changes to the menus or to send signals
* to the PC and target board. It includes processing to prevent
* repeated events from firing
*/
void cap_sense_read()
{
    //Update the baselines again
    CapSense_UpdateEnabledBaselines();
    //Scan the capsense system
    CapSense_ScanEnabledWidgets();
    while(CapSense_IsBusy() != 0);
    //The status of the left or down button
    uint8 left_button = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
    //Only activate if this is a new event
    if(left_button && !left_button_state)
    {   
        //Move the menu accordingly, down one
        if(message_index <= 0)
        {
            message_index = 4;
        }
        message_index--;
    }
    left_button_state = left_button;
    
    //The right button does the same thing but it moves the menu up
    uint8 right_button = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
    if(right_button && !right_button_state)
    {
        message_index = (message_index + 1) % 4;
    }
    right_button_state = right_button;
    
    //Now we can update the second row of the LCD with the menu value
    LCD_Position(1,0);
    LCD_PrintString("                ");
    LCD_Position(1,0);
    LCD_PrintString(messages[message_index]);
    
    //Get the value on the slider
    uint16 slider = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
    //All 1s means no touches on the slider
    if(slider == 0xFFFF)
    {
        //Code for debugging, print the frames to the computer
        // so we can see them, uncomment in production
        /*if(!Target_Control_Read())
        {
            print_line(frame_samples);
        }*/
        //We allow the pattern to change now and prevent 
        // further handling of the slider value
        pattern_change_state = 0;
        return;
    }
    //Now break the slider in half and
    //treat it at a two button pad
    uint8 slider_half = slider / 50;
    //In this case the direction is a command to be 
    // sent to the pc and potentially also to be
    // added to the LCD to inform the user
    char8 *direction;
    //What we do with the press depends on which
    // part of the menu we are in
    switch(message_index){
        case 0:
            //In this case we are changing the pattern
            LCD_Position(1,9);
            //Use this to block repeated events
            if(!pattern_change_state)
            {
                //Move up or down depending on how the slider
                // was touched
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
                //Reset the scoring variables on a 
                //pattern change
                turn = 0;
                a_score = 0;
                b_score = 0;
                position_value = 0;
            }
            messages[0] = patterns[pattern_index];
            break;
        //For either case 1 or 2 we are controlling the turret
        //itself and issue the command to the pc via uart
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
        //In the final case we are actually firing so we also
        //tell the target board to start measuring
        case 3:
            print_line("fire");
            Target_Control_Write(1);
            messages[3] = "Firing!";
            break;
    }
}