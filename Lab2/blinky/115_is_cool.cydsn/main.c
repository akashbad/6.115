/* ========================================
 *
 * 6.115 Demo Program
 * All Rights Reserved
 * North and Steven Leeb, 2013
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>
void DigitLED_Write( int);
void DigitLED_WriteHex( int);

void main()
{

    while(1)
    {
        DigitLED_WriteHex(0x06);    // 6
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x10);    // .
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x01);    // 1
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x01);    // 1
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x05);    // 5
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x01);    // I
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x05);    // S
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x0C);    // C
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x00);    // O
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_WriteHex(0x00);    // O
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(100);
        DigitLED_Write(0b11100011); // L
        CyDelay(500);
        DigitLED_WriteHex(0xff);    // null
        CyDelay(500);
    }
}

// DigitLED_Write will write the binary number "bi" to turn on/off each segment
// of the digit LED. The binary number correspond to 0b000000000 => 0bABCDEGFP
// Make each bit "0" to turn each segment "on"

void DigitLED_Write( int bi)
{
    A_Write((bi >> 7) & 1);
    B_Write((bi >> 6) & 1);
    C_Write((bi >> 5) & 1);
    D_Write((bi >> 4) & 1);
    E_Write((bi >> 3) & 1);
    F_Write((bi >> 2) & 1);
    G_Write((bi >> 1) & 1);
    P_Write((bi >> 0) & 1);
}

// DigitLED_WriteHex will write the hexadicimal number "hex" to the LED screen
void DigitLED_WriteHex( int hex)
{
    if (hex == 0x00)
        DigitLED_Write(0b00000011);
    else if (hex == 0x01)
        DigitLED_Write(0b10011111);
    else if (hex == 0x02)
        DigitLED_Write(0b00100101);  
    else if (hex == 0x03)
        DigitLED_Write(0b00001101); 
    else if (hex == 0x04)
        DigitLED_Write(0b10011001);
    else if (hex == 0x05)
        DigitLED_Write(0b01001001);
    else if (hex == 0x06)
        DigitLED_Write(0b01000001);
    else if (hex == 0x07)
        DigitLED_Write(0b00011111); 
    else if (hex == 0x08)
        DigitLED_Write(0b00000001);
    else if (hex == 0x09)
        DigitLED_Write(0b00011001);
    else if (hex == 0x0a)
        DigitLED_Write(0b00010001);
    else if (hex == 0x0b)
        DigitLED_Write(0b11000001);
    else if (hex == 0x0c)
        DigitLED_Write(0b01100011);
    else if (hex == 0x0d)
        DigitLED_Write(0b10000101);
    else if (hex == 0x0e)
        DigitLED_Write(0b01100001);
    else if (hex == 0x0f)
        DigitLED_Write(0b01110001);
    else if (hex == 0x10)
        DigitLED_Write(0b11111110);
    else
        DigitLED_Write(0b11111111);
}
/* [] END OF FILE */
