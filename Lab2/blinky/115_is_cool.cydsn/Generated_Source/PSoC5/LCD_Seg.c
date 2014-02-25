/*******************************************************************************
* File Name: LCD_Seg.c
* Version 3.30
*
* Description:
*  This file provides the API source code for the Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_Seg.h"
#include <LCD_Seg_Int_Clock.h>
#include <LCD_Seg_Lcd_Dma_dma.h>
#include <LCD_Seg_Frame_Dma_dma.h>


/* Internal functions */
static uint8   LCD_Seg_DmaConfigure(void) CYREENTRANT;
static void    LCD_Seg_DmaDispose(void) CYREENTRANT;
static void    LCD_Seg_WriteControlReg(uint8 value, uint8 mask) CYREENTRANT;

/* This section contains look-up tables for
* different kinds of displays.
*/
#ifdef LCD_Seg_7SEG

  static const uint8 CYCODE LCD_Seg_7SegDigits[] = \
    /*    '0'    '1'    '2'    '3'    '4'    '5'    '6'    '7' */
        {0x3fu, 0x06u, 0x5bu, 0x4fu, 0x66u, 0x6du, 0x7du, 0x07u, \
    /*    '8'    '9'    'A'    'B'    'C'    'D'    'E'    'F'   null */
        0x7fu, 0x6fu, 0x77u, 0x7cu, 0x39u, 0x5eu, 0x79u, 0x71u, 0x00u};

#endif /* LCD_Seg_7SEG */

#ifdef ALPHANUMERIC

    #ifdef LCD_Seg_14SEG

        static const uint16 CYCODE LCD_Seg_14SegChars[] = {
        /*------------------------------------------------------------*/
        /*                           Blank                            */
        /*------------------------------------------------------------*/
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        /*------------------------------------------------------------*/
        /*         !       "       #       $       %       &       '  */
        /*------------------------------------------------------------*/
        0x0000u,0x0006u,0x0120u,0x3fffu,0x156du,0x2ee4u,0x2a8du,0x0200u,
        /*------------------------------------------------------------*/
        /* (       )       *       +       ,       -       .       /  */
        /*------------------------------------------------------------*/
        0x0a00u,0x2080u,0x3fc0u,0x1540u,0x2000u,0x0440u,0x1058u,0x2200u,
        /*------------------------------------------------------------*/
        /* 0       1       2       3       4       5       6       7  */
        /*------------------------------------------------------------*/
        0x223fu,0x0206u,0x045bu,0x040fu,0x0466u,0x0869u,0x047du,0x1201u,
        /*------------------------------------------------------------*/
        /* 8       9       :       ;       <       =       >       ?  */
        /*------------------------------------------------------------*/
        0x047fu,0x046fu,0x1100u,0x2100u,0x0a00u,0x0448u,0x2080u,0x1423u,
        /*------------------------------------------------------------*/
        /* @       A       B       C       D       E       F       G  */
        /*------------------------------------------------------------*/
        0x053bu,0x0477u,0x150fu,0x0039u,0x110Fu,0x0079u,0x0071u,0x043du,
        /*------------------------------------------------------------*/
        /* H       I       J       K       L       M       N       O  */
        /*------------------------------------------------------------*/
        0x0476u,0x1100u,0x001eu,0x0a70u,0x0038u,0x02b6u,0x08b6u,0x003fu,
        /*------------------------------------------------------------*/
        /* P       Q       R       S       T       U       V       W  */
        /*------------------------------------------------------------*/
        0x0473u,0x083fu,0x0C73u,0x046du,0x1101u,0x003eu,0x2230u,0x2836u,
        /*------------------------------------------------------------*/
        /* X       Y       Z       [       \       ]       ^       _  */
        /*------------------------------------------------------------*/
        0x2a80u,0x1462u,0x2209u,0x0039u,0x0880u,0x000fu,0x0003u,0x0008u,
        /*------------------------------------------------------------*/
        /* @       a       b       c       d       e       f       g  */
        /*------------------------------------------------------------*/
        0x053bu,0x0477u,0x150fu,0x0039u,0x110Fu,0x0079u,0x0071u,0x043du,
        /*------------------------------------------------------------*/
        /* h       i       j       k       l       m       n       o  */
        /*------------------------------------------------------------*/
        0x0476u,0x1100u,0x001eu,0x0a70u,0x0038u,0x02b6u,0x08b6u,0x003fu,
        /*------------------------------------------------------------*/
        /* p       q       r       s       t       u       v       w  */
        /*------------------------------------------------------------*/
        0x0473u,0x083fu,0x0C73u,0x046du,0x1101u,0x003eu,0x2230u,0x2836u,
        /*------------------------------------------------------------*/
        /* x       y       z       {       |       }        ~      O  */
        /*------------------------------------------------------------*/
        0x2a80u,0x1280u,0x2209u,0x0e00u,0x1100u,0x20C0u,0x0452u,0x003fu};

    #endif /* LCD_Seg_14SEG */

    #ifdef LCD_Seg_16SEG

        static const uint16 CYCODE LCD_Seg_16SegChars[] = {
        /*------------------------------------------------------------*/
        /*                           Blank                            */
        /*------------------------------------------------------------*/
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,0x0000u,
        /*------------------------------------------------------------*/
        /*         !       "       #       $       %       &       '  */
        /*------------------------------------------------------------*/
        0x0000u,0x000cu,0x0480u,0xffffu,0x55bbu,0xdd99u,0xaa3bu,0x0800u,
        /*------------------------------------------------------------*/
        /* (       )       *       +       ,       -       .       /  */
        /*------------------------------------------------------------*/
        0x2800u,0x8200u,0xff00u,0x5500u,0x8000u,0x1100u,0x4160u,0x8800u,
        /*------------------------------------------------------------*/
        /* 0       1       2       3       4       5       6       7  */
        /*------------------------------------------------------------*/
        0x88ffu,0x000cu,0x1177u,0x103fu,0x118cu,0x21b3u,0x11fbu,0x4803u,
        /*------------------------------------------------------------*/
        /* 8       9       :       ;       <       =       >       ?  */
        /*------------------------------------------------------------*/
        0x11ffu,0x11bfu,0x4400u,0x8400u,0x2800u,0x1130u,0x8200u,0x5087u,
        /*------------------------------------------------------------*/
        /* @       A       B       C       D       E       F       G  */
        /*------------------------------------------------------------*/
        0x14f7u,0x11cfu,0x543fu,0x00f3u,0x443fu,0x01f3u,0x01c3u,0x10fbu,
        /*------------------------------------------------------------*/
        /* H       I       J       K       L       M       N       O  */
        /*------------------------------------------------------------*/
        0x11ccu,0x4400u,0x007eu,0x29c0u,0x00f0u,0x0accu,0x22ccu,0x00ffu,
        /*------------------------------------------------------------*/
        /* P       Q       R       S       T       U       V       W  */
        /*------------------------------------------------------------*/
        0x11c7u,0x20ffu,0x31c7u,0x11bbu,0x4403u,0x00fcu,0x88c0u,0xa0ccu,
        /*------------------------------------------------------------*/
        /* X       Y       Z       [       \       ]       ^       _  */
        /*------------------------------------------------------------*/
        0xaa00u,0x5184u,0x8833u,0x4412u,0x2200u,0x4421u,0x0006u,0x0030u,
        /*------------------------------------------------------------*/
        /* @       a       b       c       d       e       f       g  */
        /*------------------------------------------------------------*/
        0x14f7u,0x11cfu,0x543fu,0x00f3u,0x443fu,0x01f3u,0x01c3u,0x10fbu,
        /*------------------------------------------------------------*/
        /* h       i       j       k       l       m       n       o  */
        /*------------------------------------------------------------*/
        0x11ccu,0x4400u,0x007eu,0x29c0u,0x00f0u,0x0accu,0x22ccu,0x00ffu,
        /*------------------------------------------------------------*/
        /* p       q       r       s       t       u       v       w  */
        /*------------------------------------------------------------*/
        0x11c7u,0x20ffu,0x31c7u,0x11bbu,0x4403u,0x00fcu,0x88c0u,0xa0ccu,
        /*------------------------------------------------------------*/
        /* x       y       z       {       |       }        ~         */
        /*------------------------------------------------------------*/
        0xaa00u,0x4A00u,0x8833u,0x3800u,0x4400u,0x8300u,0x1144u,0x0000u};

    #endif /* LCD_Seg_16SEG */

    #ifdef LCD_Seg_DOT_MATRIX
        static const uint8 CYCODE LCD_Seg_charDotMatrix[][5u] = {
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x3Eu, 0x1Cu, 0x1Cu, 0x08u, 0x08u}, {0x08u, 0x08u, 0x1Cu, 0x1Cu, 0x3Eu},
        {0x02u, 0x06u, 0x08u, 0x10u, 0x20u}, {0x00u, 0x4Fu, 0x00u, 0x4Fu, 0x00u}, {0x06u, 0x0Fu, 0x7Fu, 0x01u, 0x7Fu},
        {0x48u, 0x56u, 0x55u, 0x35u, 0x09u}, {0x0Cu, 0x0Cu, 0x0Cu, 0x0Cu, 0x0Cu}, {0x10u, 0x38u, 0x54u, 0x10u, 0x1Fu},
        {0x04u, 0x02u, 0x7Fu, 0x02u, 0x04u}, {0x10u, 0x20u, 0x7Fu, 0x20u, 0x10u}, {0x7Fu, 0x3Eu, 0x1Cu, 0x08u, 0x7Fu},
        {0x7Fu, 0x08u, 0x1Cu, 0x3Eu, 0x7Fu}, {0x7Fu, 0x08u, 0x2Au, 0x1Cu, 0x08u}, {0x08u, 0x1Cu, 0x2Au, 0x08u, 0x7Fu},
        {0x02u, 0x0Eu, 0x3Eu, 0x0Eu, 0x02u}, {0x20u, 0x38u, 0x3Eu, 0x38u, 0x20u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
        {0x00u, 0x00u, 0x4Fu, 0x00u, 0x00u}, {0x00u, 0x07u, 0x00u, 0x07u, 0x00u}, {0x14u, 0x7Fu, 0x14u, 0x7Fu, 0x14u},
        {0x24u, 0x2Au, 0x7Fu, 0x2Au, 0x12u}, {0x23u, 0x13u, 0x08u, 0x64u, 0x62u}, {0x36u, 0x49u, 0x55u, 0x22u, 0x50u},
        {0x00u, 0x05u, 0x03u, 0x00u, 0x00u}, {0x00u, 0x1Cu, 0x22u, 0x41u, 0x00u}, {0x00u, 0x41u, 0x22u, 0x1Cu, 0x00u},
        {0x14u, 0x08u, 0x3Eu, 0x08u, 0x14u}, {0x08u, 0x08u, 0x3Eu, 0x08u, 0x08u}, {0x00u, 0x50u, 0x30u, 0x00u, 0x00u},
        {0x08u, 0x08u, 0x08u, 0x08u, 0x08u}, {0x00u, 0x60u, 0x60u, 0x00u, 0x00u}, {0x20u, 0x10u, 0x08u, 0x04u, 0x02u},
        {0x3Eu, 0x51u, 0x49u, 0x45u, 0x3Eu}, {0x00u, 0x42u, 0x7Fu, 0x40u, 0x00u}, {0x42u, 0x61u, 0x51u, 0x49u, 0x46u},
        {0x21u, 0x41u, 0x45u, 0x4Bu, 0x31u}, {0x18u, 0x14u, 0x12u, 0x7Fu, 0x10u}, {0x27u, 0x45u, 0x45u, 0x45u, 0x39u},
        {0x3Cu, 0x4Au, 0x49u, 0x49u, 0x30u}, {0x01u, 0x71u, 0x09u, 0x05u, 0x03u}, {0x36u, 0x49u, 0x49u, 0x49u, 0x36u},
        {0x06u, 0x49u, 0x49u, 0x29u, 0x1Eu}, {0x00u, 0x36u, 0x36u, 0x00u, 0x00u}, {0x00u, 0x56u, 0x36u, 0x00u, 0x00u},
        {0x08u, 0x14u, 0x22u, 0x41u, 0x00u}, {0x14u, 0x14u, 0x14u, 0x14u, 0x14u}, {0x00u, 0x41u, 0x22u, 0x14u, 0x08u},
        {0x02u, 0x01u, 0x51u, 0x09u, 0x06u}, {0x32u, 0x49u, 0x79u, 0x41u, 0x3Eu}, {0x7Eu, 0x11u, 0x11u, 0x11u, 0x7Eu},
        {0x7Fu, 0x49u, 0x49u, 0x49u, 0x36u}, {0x3Eu, 0x41u, 0x41u, 0x41u, 0x22u}, {0x7Fu, 0x41u, 0x41u, 0x22u, 0x1Cu},
        {0x7Fu, 0x49u, 0x49u, 0x49u, 0x41u}, {0x7Fu, 0x09u, 0x09u, 0x09u, 0x01u}, {0x3Eu, 0x41u, 0x49u, 0x49u, 0x3Au},
        {0x7Fu, 0x08u, 0x08u, 0x08u, 0x7Fu}, {0x00u, 0x41u, 0x7Fu, 0x41u, 0x00u}, {0x20u, 0x40u, 0x41u, 0x3Fu, 0x01u},
        {0x7Fu, 0x08u, 0x14u, 0x22u, 0x41u}, {0x7Fu, 0x40u, 0x40u, 0x40u, 0x40u}, {0x7Fu, 0x02u, 0x0Cu, 0x02u, 0x7Fu},
        {0x7Fu, 0x04u, 0x08u, 0x10u, 0x7Fu}, {0x3Eu, 0x41u, 0x41u, 0x41u, 0x3Eu}, {0x7Fu, 0x09u, 0x09u, 0x09u, 0x06u},
        {0x3Eu, 0x41u, 0x51u, 0x21u, 0x5Eu}, {0x7Fu, 0x09u, 0x19u, 0x29u, 0x46u}, {0x46u, 0x49u, 0x49u, 0x49u, 0x31u},
        {0x01u, 0x01u, 0x7Fu, 0x01u, 0x01u}, {0x3Fu, 0x40u, 0x40u, 0x40u, 0x3Fu}, {0x1Fu, 0x20u, 0x40u, 0x20u, 0x1Fu},
        {0x3Fu, 0x40u, 0x38u, 0x40u, 0x3Fu}, {0x63u, 0x14u, 0x08u, 0x14u, 0x63u}, {0x07u, 0x08u, 0x70u, 0x08u, 0x07u},
        {0x61u, 0x51u, 0x49u, 0x45u, 0x43u}, {0x00u, 0x7Fu, 0x41u, 0x41u, 0x00u}, {0x15u, 0x16u, 0x7Cu, 0x16u, 0x15u},
        {0x00u, 0x41u, 0x41u, 0x7Fu, 0x00u}, {0x04u, 0x02u, 0x01u, 0x02u, 0x04u}, {0x40u, 0x40u, 0x40u, 0x40u, 0x40u},
        {0x00u, 0x01u, 0x02u, 0x04u, 0x00u}, {0x20u, 0x54u, 0x54u, 0x54u, 0x78u}, {0x7Fu, 0x48u, 0x44u, 0x44u, 0x38u},
        {0x38u, 0x44u, 0x44u, 0x44u, 0x40u}, {0x38u, 0x44u, 0x44u, 0x48u, 0x7Fu}, {0x38u, 0x54u, 0x54u, 0x54u, 0x18u},
        {0x08u, 0x7Eu, 0x09u, 0x01u, 0x02u}, {0x0Cu, 0x52u, 0x52u, 0x52u, 0x3Eu}, {0x7Fu, 0x08u, 0x04u, 0x04u, 0x78u},
        {0x00u, 0x44u, 0x7Du, 0x40u, 0x00u}, {0x20u, 0x40u, 0x40u, 0x3Du, 0x00u}, {0x7Fu, 0x10u, 0x28u, 0x44u, 0x00u},
        {0x00u, 0x41u, 0x7Fu, 0x40u, 0x00u}, {0x7Cu, 0x04u, 0x18u, 0x04u, 0x78u}, {0x7Cu, 0x08u, 0x04u, 0x04u, 0x78u},
        {0x38u, 0x44u, 0x44u, 0x44u, 0x38u}, {0x7Cu, 0x14u, 0x14u, 0x14u, 0x08u}, {0x08u, 0x14u, 0x14u, 0x18u, 0x7Cu},
        {0x7Cu, 0x08u, 0x04u, 0x04u, 0x08u}, {0x48u, 0x54u, 0x54u, 0x54u, 0x20u}, {0x04u, 0x3Fu, 0x44u, 0x40u, 0x20u},
        {0x3Cu, 0x40u, 0x40u, 0x20u, 0x7Cu}, {0x1Cu, 0x20u, 0x40u, 0x20u, 0x1Cu}, {0x3Cu, 0x40u, 0x30u, 0x40u, 0x3Cu},
        {0x44u, 0x28u, 0x10u, 0x28u, 0x44u}, {0x0Cu, 0x50u, 0x50u, 0x50u, 0x3Cu}, {0x44u, 0x64u, 0x54u, 0x4Cu, 0x44u},
        {0x00u, 0x08u, 0x36u, 0x41u, 0x00u}, {0x00u, 0x00u, 0x7Fu, 0x00u, 0x00u}, {0x00u, 0x41u, 0x36u, 0x08u, 0x00u},
        {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x08u, 0x08u, 0x2Au, 0x1Cu, 0x08u}, {0x44u, 0x44u, 0x5Fu, 0x44u, 0x44u},
        {0x22u, 0x14u, 0x08u, 0x14u, 0x22u}, {0x1Cu, 0x3Eu, 0x3Eu, 0x3Eu, 0x1Cu}, {0x7Fu, 0x41u, 0x41u, 0x41u, 0x7Fu},
        {0x7Fu, 0x5Bu, 0x41u, 0x5Fu, 0x7Fu}, {0x7Fu, 0x4Du, 0x55u, 0x59u, 0x7Fu}, {0x1Du, 0x15u, 0x17u, 0x00u, 0x00u},
        {0x15u, 0x15u, 0x1Fu, 0x00u, 0x00u}, {0x17u, 0x08u, 0x74u, 0x56u, 0x5Du}, {0x17u, 0x08u, 0x24u, 0x32u, 0x79u},
        {0x35u, 0x1Fu, 0x28u, 0x34u, 0x7Au}, {0x08u, 0x14u, 0x2Au, 0x14u, 0x22u}, {0x22u, 0x14u, 0x2Au, 0x14u, 0x08u},
        {0x08u, 0x04u, 0x08u, 0x10u, 0x08u}, {0x14u, 0x0Au, 0x14u, 0x28u, 0x14u}, {0x2Au, 0x55u, 0x2Au, 0x55u, 0x2Au},
        {0x24u, 0x3Bu, 0x2Au, 0x7Eu, 0x2Au}, {0x40u, 0x3Fu, 0x15u, 0x15u, 0x7Fu}, {0x46u, 0x20u, 0x1Fu, 0x20u, 0x46u},
        {0x24u, 0x14u, 0x7Fu, 0x18u, 0x24u}, {0x24u, 0x14u, 0x7Fu, 0x14u, 0x24u}, {0x44u, 0x6Au, 0x79u, 0x6Au, 0x44u},
        {0x40u, 0x44u, 0x7Fu, 0x44u, 0x40u}, {0x7Fu, 0x49u, 0x49u, 0x49u, 0x7Fu}, {0x02u, 0x4Cu, 0x30u, 0x0Cu, 0x02u},
        {0x04u, 0x04u, 0x3Cu, 0x04u, 0x44u}, {0x49u, 0x55u, 0x7Fu, 0x55u, 0x49u}, {0x3Au, 0x45u, 0x45u, 0x45u, 0x39u},
        {0x40u, 0x3Eu, 0x10u, 0x10u, 0x1Eu}, {0x08u, 0x54u, 0x3Eu, 0x15u, 0x08u}, {0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu},
        {0x55u, 0x2Au, 0x55u, 0x2Au, 0x55u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u}, {0x70u, 0x50u, 0x70u, 0x00u, 0x00u},
        {0x00u, 0x00u, 0x0Fu, 0x01u, 0x01u}, {0x40u, 0x40u, 0x70u, 0x00u, 0x00u}, {0x10u, 0x20u, 0x40u, 0x00u, 0x00u},
        {0x00u, 0x18u, 0x18u, 0x00u, 0x00u}, {0x0Au, 0x0Au, 0x4Au, 0x2Au, 0x1Eu}, {0x04u, 0x44u, 0x34u, 0x14u, 0x0Cu},
        {0x20u, 0x10u, 0x78u, 0x04u, 0x00u}, {0x18u, 0x08u, 0x4Cu, 0x48u, 0x38u}, {0x48u, 0x48u, 0x78u, 0x48u, 0x48u},
        {0x48u, 0x28u, 0x18u, 0x78u, 0x08u}, {0x08u, 0x7Cu, 0x08u, 0x28u, 0x18u}, {0x40u, 0x48u, 0x48u, 0x78u, 0x40u},
        {0x54u, 0x54u, 0x54u, 0x7Cu, 0x00u}, {0x18u, 0x00u, 0x58u, 0x40u, 0x38u}, {0x08u, 0x08u, 0x08u, 0x08u, 0x08u},
        {0x01u, 0x41u, 0x3Du, 0x09u, 0x07u}, {0x10u, 0x08u, 0x78u, 0x02u, 0x01u}, {0x06u, 0x02u, 0x43u, 0x22u, 0x1Eu},
        {0x42u, 0x42u, 0x7Eu, 0x42u, 0x42u}, {0x22u, 0x12u, 0x0Au, 0x7Fu, 0x02u}, {0x42u, 0x3Fu, 0x02u, 0x42u, 0x3Eu},
        {0x0Au, 0x0Au, 0x7Fu, 0x0Au, 0x0Au}, {0x08u, 0x46u, 0x42u, 0x22u, 0x1Eu}, {0x04u, 0x03u, 0x42u, 0x3Eu, 0x02u},
        {0x42u, 0x42u, 0x42u, 0x42u, 0x7Eu}, {0x02u, 0x4Fu, 0x22u, 0x1Fu, 0x02u}, {0x4Au, 0x4Au, 0x40u, 0x20u, 0x1Cu},
        {0x42u, 0x22u, 0x12u, 0x2Au, 0x46u}, {0x02u, 0x3Fu, 0x42u, 0x4Au, 0x46u}, {0x06u, 0x48u, 0x40u, 0x20u, 0x1Eu},
        {0x08u, 0x46u, 0x4Au, 0x32u, 0x1Eu}, {0x0Au, 0x4Au, 0x3Eu, 0x09u, 0x08u}, {0x0Eu, 0x00u, 0x4Eu, 0x20u, 0x1Eu},
        {0x04u, 0x45u, 0x3Du, 0x05u, 0x04u}, {0x00u, 0x7Fu, 0x08u, 0x10u, 0x00u}, {0x44u, 0x24u, 0x1Fu, 0x04u, 0x04u},
        {0x40u, 0x42u, 0x42u, 0x42u, 0x40u}, {0x42u, 0x2Au, 0x12u, 0x2Au, 0x06u}, {0x22u, 0x12u, 0x7Au, 0x16u, 0x22u},
        {0x00u, 0x40u, 0x20u, 0x1Fu, 0x00u}, {0x78u, 0x00u, 0x02u, 0x04u, 0x78u}, {0x3Fu, 0x44u, 0x44u, 0x44u, 0x44u},
        {0x02u, 0x42u, 0x42u, 0x22u, 0x1Eu}, {0x04u, 0x02u, 0x04u, 0x08u, 0x30u}, {0x32u, 0x02u, 0x7Fu, 0x02u, 0x32u},
        {0x02u, 0x12u, 0x22u, 0x52u, 0x0Eu}, {0x00u, 0x2Au, 0x2Au, 0x2Au, 0x40u}, {0x38u, 0x24u, 0x22u, 0x20u, 0x1Eu},
        {0x40u, 0x28u, 0x10u, 0x28u, 0x06u}, {0x0Au, 0x3Eu, 0x4Au, 0x4Au, 0x4Au}, {0x04u, 0x7Fu, 0x04u, 0x14u, 0x0Cu},
        {0x40u, 0x42u, 0x42u, 0x7Eu, 0x40u}, {0x4Au, 0x4Au, 0x4Au, 0x4Au, 0x7Eu}, {0x04u, 0x05u, 0x45u, 0x15u, 0x1Cu},
        {0x0Fu, 0x40u, 0x20u, 0x1Fu, 0x00u}, {0x7Cu, 0x00u, 0x7Eu, 0x40u, 0x30u}, {0x7Eu, 0x40u, 0x20u, 0x10u, 0x08u},
        {0x7Eu, 0x7Eu, 0x7Eu, 0x7Eu, 0x7Eu}, {0x0Eu, 0x02u, 0x42u, 0x22u, 0x1Eu}, {0x42u, 0x42u, 0x40u, 0x20u, 0x18u},
        {0x02u, 0x04u, 0x01u, 0x02u, 0x00u}, {0x07u, 0x05u, 0x07u, 0x00u, 0x00u}, {0x38u, 0x44u, 0x48u, 0x30u, 0x4Cu},
        {0x20u, 0x55u, 0x55u, 0x55u, 0x38u}, {0xFEu, 0x15u, 0x15u, 0x15u, 0x0Au}, {0x28u, 0x54u, 0x54u, 0x44u, 0x20u},
        {0xFFu, 0x10u, 0x10u, 0x08u, 0x1Fu}, {0x38u, 0x44u, 0x4Cu, 0x54u, 0x24u}, {0xFCu, 0x12u, 0x11u, 0x11u, 0x0Eu},
        {0x0Eu, 0xA1u, 0xA1u, 0xA1u, 0x7Fu}, {0x20u, 0x40u, 0x3Cu, 0x04u, 0x04u}, {0x04u, 0x04u, 0x00u, 0x0Eu, 0x00u},
        {0x40u, 0x80u, 0x81u, 0x7Fu, 0x00u}, {0x0Au, 0x04u, 0x0Au, 0x00u, 0x00u}, {0x18u, 0x24u, 0x7Eu, 0x24u, 0x10u},
        {0x14u, 0x7Fu, 0x54u, 0x40u, 0x40u}, {0x7Cu, 0x0Au, 0x05u, 0x05u, 0x78u}, {0x38u, 0x45u, 0x45u, 0x45u, 0x38u},
        {0xFFu, 0x12u, 0x11u, 0x11u, 0x0Eu}, {0x0Eu, 0x11u, 0x11u, 0x12u, 0xFFu}, {0x3Cu, 0x4Au, 0x4Au, 0x4Au, 0x3Cu},
        {0x30u, 0x28u, 0x10u, 0x28u, 0x18u}, {0x58u, 0x64u, 0x04u, 0x64u, 0x58u}, {0x3Cu, 0x41u, 0x40u, 0x21u, 0x7Cu},
        {0x63u, 0x55u, 0x4Au, 0x41u, 0x41u}, {0x44u, 0x3Cu, 0x04u, 0x7Cu, 0x44u}, {0x45u, 0x29u, 0x11u, 0x29u, 0x45u},
        {0x0Fu, 0x90u, 0x90u, 0x90u, 0x7Fu}, {0x14u, 0x14u, 0x7Cu, 0x14u, 0x12u}, {0x44u, 0x3Cu, 0x14u, 0x14u, 0x74u},
        {0x7Cu, 0x14u, 0x1Cu, 0x14u, 0x7Cu}, {0x10u, 0x10u, 0x54u, 0x10u, 0x10u}, {0x00u, 0x00u, 0x00u, 0x00u, 0x00u},
        {0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu}
        };
    #endif /* LCD_Seg_DOT_MATRIX */
#endif /* ALPHANUMERIC */

uint8 LCD_Seg_initVar = 0u;

/* Stores DMA  channel number used for Frame signal transaction */
static uint8 LCD_Seg_frameChannel;

/* The one and only - Frame Buffer */
static uint8 LCD_Seg_buffer[LCD_Seg_BUFFER_LENGTH];

/* Array of common port TDs */
static uint8 LCD_Seg_lcdTd[LCD_Seg_LCD_TD_SIZE * LCD_Seg_COMM_NUM];

/* DMA channel dedicated for SegLCD commons */
static uint8 LCD_Seg_lcdChannel;

/* Start of customizer generated code */

static uint16 LCD_Seg_commons[1u] = {LCD_Seg_Com0};

static uint8 LCD_Seg_frameTx[2u] = {0x80u, 0x00u};
static uint8 LCD_Seg_frameTd[2u];


/*******************************************************************************
* Function Name: LCD_Seg_Init
********************************************************************************
*
* Summary:
*  Perform initialization of the component. Configures and enables all required
*  hardware blocks, clears frame buffer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Seg_Init(void) 
{
    /* LCD Timer configuration */
    #if(LCD_Seg_POWER_MODE == LCD_Seg__LOW_POWER_ILO)

        /* Select ILO as a wake up source */
        LCD_Seg_TIMER_CONTROL_REG = 
            LCD_Seg_TIMER_CONTROL_REG & ((uint8) ~LCD_Seg_TIMER_CLK_SEL_MASK);
        /* Set period */
        LCD_Seg_TIMER_CONTROL_REG = (LCD_Seg_TIMER_CONTROL_REG & 
                            ((uint8) ~LCD_Seg_TIMER_PERIOD_MASK))
                            | (uint8) (((uint8) LCD_Seg_TIMER_PERIOD) << LCD_Seg_TIMER_PERIOD_SHIFT);

    #elif(LCD_Seg_POWER_MODE == LCD_Seg__LOW_POWER_32XTAL)
        /* One PPS must be enabled to generate 8Khz clock for LCD Timer */
        LCD_Seg_TM_WL_GFG_REG |= LCD_Seg_ONE_PPS_EN;
        /* Select 8K tap from OPPS timer as a wake up source */
        LCD_Seg_TIMER_CONTROL_REG = LCD_Seg_TIMER_CONTROL_REG | LCD_Seg_TIMER_32XTAL_SEL;
        /* Set period */
        LCD_Seg_TIMER_CONTROL_REG = (LCD_Seg_TIMER_CONTROL_REG &
                           ((uint8) ~LCD_Seg_TIMER_PERIOD_MASK))
                           | (uint8) (((uint8) LCD_Seg_TIMER_PERIOD) << LCD_Seg_TIMER_PERIOD_SHIFT);

    #endif /* LCD_Seg_POWER_MODE == LCD_Seg__LOW_POWER_ILO */

    /* Need to clear display to start normal work */
    LCD_Seg_ClearDisplay();

    /* Select LCD DAC generated voltage as the source for LCD Driver */
    LCD_Seg_LCDDAC_SWITCH_REG0_REG = LCD_Seg_LCDDAC_VOLTAGE_SEL;
    LCD_Seg_LCDDAC_SWITCH_REG1_REG = LCD_Seg_LCDDAC_VOLTAGE_SEL;
    LCD_Seg_LCDDAC_SWITCH_REG2_REG = LCD_Seg_LCDDAC_VOLTAGE_SEL;
    LCD_Seg_LCDDAC_SWITCH_REG3_REG = LCD_Seg_LCDDAC_VOLTAGE_SEL;
    LCD_Seg_LCDDAC_SWITCH_REG4_REG = LCD_Seg_LCDDAC_VOLTAGE_SEL;

    /* Turn on the LCD DAC and set the bias type */
    LCD_Seg_LCDDAC_CONTROL_REG = (LCD_Seg_LCDDAC_CONTROL_REG & LCD_Seg_BIAS_TYPE_MASK)
        | LCD_Seg_BIAS_TYPE;

    /* Set the contrast level for LCD with value chosen in the GUI */
    (void) LCD_Seg_SetBias(LCD_Seg_BIAS_VOLTAGE);

    /* Set lower bit of HI Drive strength to LCD Driver control register */
    LCD_Seg_DRIVER_CONTROL_REG |= ((uint8) (((uint8)(((uint8) LCD_Seg_HIDRIVE_STRENGTH) << 
                                LCD_Seg_LCDDRV_MODE0_SHIFT)) & ((uint8) LCD_Seg_LCDDRV_MODE0_MASK)));

    /* Set two high bits of HI Drive strength */
    LCD_Seg_WriteControlReg((uint8) (LCD_Seg_HIDRIVE_STRENGTH & LCD_Seg_MODE_MASK),
                                     (uint8) LCD_Seg_CNTL_MODE_MASK);

    /* ISR initialization */
    (void) CyIntDisable(LCD_Seg_ISR_NUMBER);

    /* Set the ISR to point to the TD_DoneInt Interrupt. */
    (void) CyIntSetVector(LCD_Seg_ISR_NUMBER, &LCD_Seg_ISR);

    /* Set the priority. */
    CyIntSetPriority(LCD_Seg_ISR_NUMBER, LCD_Seg_ISR_PRIORITY);
     
    #if(CY_PSOC5LP)
    
        /* Wakeup ISR initialization */
        CyIntDisable(LCD_Seg_WAKEUP_ISR_NUMBER);

        /* Set the ISR to point to the Wakeup_isr Interrupt. */
        (void) CyIntSetVector(LCD_Seg_WAKEUP_ISR_NUMBER, &LCD_Seg_WAKEUP_ISR);

        /* Set the priority of Wakeup ISR. */
        CyIntSetPriority(LCD_Seg_WAKEUP_ISR_NUMBER, LCD_Seg_WAKEUP_ISR_PRIORITY);
    
    #endif /* CY_PSOC5LP */
}


/*******************************************************************************
* Function Name: LCD_Seg_Enable
********************************************************************************
*
* Summary:
*  Enables the power to LCD fixed hardware and enables generation of UDB
*  signals.
*
* Parameters:
*  None.
*
* Return:
*  Status one of standard status for PSoC3 Component:
*      CYRET_SUCCESS - function completed successfully.
*      CYRET_LOCKED - the object was locked, already in use. Some of TDs or
*                     a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 LCD_Seg_Enable(void) 
{
    uint8 status;
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    /* Enable the LCD hardware */
    LCD_Seg_PWR_MGR_REG |= LCD_Seg_LCD_EN;
    LCD_Seg_PWR_MGR_STBY_REG |= LCD_Seg_LCD_STBY_EN;

    CyExitCriticalSection(interruptState);

    /* Enable internal clock */
    LCD_Seg_Int_Clock_Enable();

    status = LCD_Seg_DmaConfigure();

    /* Set LCD PWM period */
    LCD_Seg_PWM_PERIOD_REG = LCD_Seg_PWM_PERIOD_VAL;
    LCD_Seg_PWM_DRIVE_REG = LCD_Seg_PWM_DRIVE_VAL;
    LCD_Seg_PWM_LODRIVE_REG = LCD_Seg_PWM_LOWDRIVE_VAL;

    LCD_Seg_WriteControlReg((uint8) LCD_Seg_CNTL_FRAME_DONE,
    (uint8)LCD_Seg_CNTL_FRAME_DONE_MASK);

    /* Global UDB enable, will be sent by DMA */
    LCD_Seg_WriteControlReg((uint8) LCD_Seg_CNTL_CLK_EN, (uint8) LCD_Seg_CNTL_CLK_EN_MASK);

    /* Global UDB enable, this required to start normal work as
    * it enables first DMA request.
    */
    LCD_Seg_CONTROL_REG |= LCD_Seg_CNTL_CLK_EN;

    #if(LCD_Seg_POWER_MODE != LCD_Seg__NO_SLEEP)

        /* Enable generation of lp_ack signal from UBD to PM */
        LCD_Seg_LCDDAC_CONTROL_REG |= LCD_Seg_LCDDAC_UDB_LP_EN;

        /* Start the LCD timer if in one of Low Power modes */
        LCD_Seg_TIMER_CONTROL_REG |= LCD_Seg_TIMER_EN;

    #endif /* LCD_Seg_POWER_MODE == LCD_Seg__NO_SLEEP */

    return(status);
}


/*******************************************************************************
* Function Name: LCD_Seg_DmaConfigure
********************************************************************************
*
* Summary:
*  Configures DMA for the components usage, transfering dasplay data and
*  generating frame signal. Allocates required number of TDs and configures
*  them, enables DMA channels.
*
* Parameters:
*  None.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - function completed successfully.
*       CYRET_LOCKED - the object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Global variables:
*  LCD_Seg_lcdTd[] - used to store a set of allocated TD IDs that are
*  used by this component.
*
*  LCD_Seg_lcdChannel - stores a DMA Channel allocated for an LCD
*  usage.
*
*  LCD_Seg_frameTd[] - used to store a set of allocated TD IDs that
*  are used by this component for Frame signal generation.
*
*  LCD_Seg_LcdPort_DMA_TD_PROTO_BLOCK[] - used as a parameter for
*  DMA configuration.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static uint8 LCD_Seg_DmaConfigure(void) CYREENTRANT
{
    uint8   status = CYRET_SUCCESS;
    uint8   i;
    uint8   j;
    uint32  srcAddr;
    uint32  dstAddr;
    /* DMA_PROTO_TD_DEF */
    static const struct LCD_Seg_DMA_TD_PROTO_ENTRY CYCODE LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[1u] =
    {
        {0u, 2u},
    };

    /* Take source and destination address */
    /* Conditional compilation is needed to avoid MISRA warning */
    #if(CY_PSOC5)
        srcAddr = (uint32) LCD_Seg_frameTx;
        dstAddr = (uint32) LCD_Seg_CONTROL_PTR;
        
        /* Get the DMA channel for the Frame and check it for validness */
        LCD_Seg_frameChannel = LCD_Seg_Frame_Dma_DmaInitialize(0u, 0u, HI16(srcAddr), 
                                                                            HI16(LCD_Seg_CONTROL_REG_BASE));
    #else
        srcAddr = LCD_Seg_DMA_ADDRESS_MASK & ((uint32) LCD_Seg_frameTx);
        dstAddr = LCD_Seg_DMA_ADDRESS_MASK & ((uint32) LCD_Seg_CONTROL_PTR);
        
        /* Get the DMA channel for the Frame and check it for validness.
        * Upper 2 bytes of destination and source addrresses are always 0.
        */
        LCD_Seg_frameChannel = LCD_Seg_Frame_Dma_DmaInitialize(0u, 0u, 0u, 0u);
    #endif /* CY_PSOC5 */

    if(LCD_Seg_frameChannel == DMA_INVALID_CHANNEL)
    {
        status = CYRET_LOCKED;
    }

    /* The DMA configuration for Type A and Type B waveforms differs because of
    *  the their specification. Type A waveforms use only two TDs no matter what
    *  is the number of commons and Type B waveforms TDs usage is  dependent on
    *  the number of commons.
    */
    #if(LCD_Seg_WAVEFORM_TYPE == LCD_Seg__TYPE_A)

        for(i = 0u; i < LCD_Seg_CONTROL_WRITE_COUNT; i++)
        {   /* Allocate a TD and check it if it valid. */
            LCD_Seg_frameTd[i]= CyDmaTdAllocate();
            
            if(DMA_INVALID_TD == LCD_Seg_frameTd[i])
            {
                status = CYRET_LOCKED;
            }
        }
        
        /* Set configuration for the first TD */
        (void) CyDmaTdSetConfiguration(LCD_Seg_frameTd[0u],
                                       1u,
                                       LCD_Seg_frameTd[1u],
                                       TD_INC_SRC_ADR | LCD_Seg_Frame_Dma__TD_TERMOUT_EN);

        (void) CyDmaTdSetAddress(LCD_Seg_frameTd[0u], LO16(srcAddr), LO16(dstAddr));

        /* Set configuration for the second TD */
        (void) CyDmaTdSetConfiguration(LCD_Seg_frameTd[1u],
                                       1u,
                                       LCD_Seg_frameTd[0u],
                                       TD_INC_SRC_ADR | LCD_Seg_Frame_Dma__TD_TERMOUT_EN);

        (void) CyDmaTdSetAddress(LCD_Seg_frameTd[1u], LO16(srcAddr + 1u), LO16(dstAddr));

    #else /* Waveform Type B */

        for(i = 0u; i < LCD_Seg_CONTROL_WRITE_COUNT; i++)
        {
            LCD_Seg_frameTd[i]= CyDmaTdAllocate();
            if(DMA_INVALID_TD == LCD_Seg_frameTd[i])
            {
                status = CYRET_LOCKED;
            }
        }

        for(i = 0u; i < LCD_Seg_CONTROL_WRITE_COUNT; i++)
        {
            if((LCD_Seg_CONTROL_WRITE_COUNT - 1u) != i)
            {
                (void) CyDmaTdSetConfiguration(LCD_Seg_frameTd[i],
                                               1u,
                                               LCD_Seg_frameTd[i + 1u],
                                               TD_INC_SRC_ADR | 
                                               LCD_Seg_Frame_Dma__TD_TERMOUT_EN);
            }
            else
            {
                (void) CyDmaTdSetConfiguration(LCD_Seg_frameTd[i],
                                               1u,
                                               LCD_Seg_frameTd[0u],
                                               TD_INC_SRC_ADR | 
                                               LCD_Seg_Frame_Dma__TD_TERMOUT_EN);
            }
            (void) CyDmaTdSetAddress(LCD_Seg_frameTd[i], LO16(srcAddr) + i , LO16(dstAddr));
        }

    #endif /* LCD_Seg_WAVEFORM_TYPE == LCD_Seg__TYPE_A */

    if(CYRET_LOCKED != status)
    {
        (void) CyDmaChSetInitialTd(LCD_Seg_frameChannel, LCD_Seg_frameTd[0u]);
        (void) CyDmaChEnable(LCD_Seg_frameChannel, 1u);
    }

    /* Conditional compilation is needed to avoid MISRA warning */
    #if(CY_PSOC5LP)
        srcAddr = (uint32) LCD_Seg_buffer;
        dstAddr = (uint32) LCD_Seg_ALIASED_AREA_PTR;
        
        LCD_Seg_lcdChannel = LCD_Seg_Lcd_Dma_DmaInitialize(0u, 0u, HI16(srcAddr), 
                                                                        HI16(LCD_Seg_ALIASED_AREA_PTR));
    #else
        srcAddr = LCD_Seg_DMA_ADDRESS_MASK & ((uint32) LCD_Seg_buffer);
        dstAddr = LCD_Seg_DMA_ADDRESS_MASK & ((uint32) LCD_Seg_ALIASED_AREA_PTR);
        
        LCD_Seg_lcdChannel = LCD_Seg_Lcd_Dma_DmaInitialize(0u, 0u, 0u, 0u);
    #endif /* CY_PSOC5 */

    if(LCD_Seg_lcdChannel == DMA_INVALID_CHANNEL)
    {
        status = CYRET_LOCKED;
    }

    for(j = 0u; j < LCD_Seg_COMM_NUM; j++)
    {
        #if(1 == LCD_Seg_SegLcdPort_DMA_TD_PROTO_COUNT)
                
            LCD_Seg_lcdTd[j] = CyDmaTdAllocate();
            
            if(DMA_INVALID_TD == LCD_Seg_lcdTd[j])
            {
                status = CYRET_LOCKED;
            }

        #else
        
            i = 0u;
            
            do{
                LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i] = CyDmaTdAllocate();
                
                if(DMA_INVALID_TD == LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i])
                {
                    status = CYRET_LOCKED;
                }
            
                i++;
                
            } while(i < LCD_Seg_LCD_TD_SIZE);
            
        #endif /* (1 == LCD_Seg_SegLcdPort_DMA_TD_PROTO_COUNT) */
    }

    for(j = 0u; j < LCD_Seg_COMM_NUM; j++)
    {
        /* This is to supress MISRA warning. Depending on
        * LCD_Seg_SegLcdPort_DMA_TD_PROTO_COUNT need to differentiate
        * 2 or 3 configurations of LCD DMA transaction descriptors.
        */
        #if(1 == LCD_Seg_SegLcdPort_DMA_TD_PROTO_COUNT)
            
            if(LCD_Seg_COM_TD_COUNT == j)
            {
                /* The last TD need to point to TD[0] */
                (void) CyDmaTdSetConfiguration(LCD_Seg_lcdTd[j],
                                               (uint16)LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[0].length,
                                               LCD_Seg_lcdTd[0u],
                                               TD_INC_DST_ADR | TD_INC_SRC_ADR | 
                                               LCD_Seg_Lcd_Dma__TD_TERMOUT_EN);
            }
            /* Create a chain of TDs in which current TD ponts to next TD. 
            * Each of this TDs should be seperatelly requested.
            */
            else
            {
                (void) CyDmaTdSetConfiguration(LCD_Seg_lcdTd[j],
                                               (uint16) LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[0].length,
                                               LCD_Seg_lcdTd[j + 1u],
                                               TD_INC_DST_ADR | TD_INC_SRC_ADR | 
                                               LCD_Seg_Lcd_Dma__TD_TERMOUT_EN);
            }
            
            (void) CyDmaTdSetAddress(LCD_Seg_lcdTd[j],
                                     LO16(srcAddr) + (((uint16) j) * LCD_Seg_ROW_LENGTH) +
                                     ((uint16) LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[0].offset),
                                     LO16(dstAddr) + LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[0].offset);
        #else

            for(i = 0u; i < LCD_Seg_LCD_TD_SIZE; i++)
            {
                if(LCD_Seg_COM_TD_COUNT == ((j * LCD_Seg_LCD_TD_SIZE) + i))
                {
                    /* The last TD need to point to TD[0] */
                    (void) CyDmaTdSetConfiguration(LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i],
                                                   (uint16)LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[i].length,
                                                   LCD_Seg_lcdTd[0u],
                                                   TD_INC_DST_ADR | TD_INC_SRC_ADR | 
                                                   LCD_Seg_Lcd_Dma__TD_TERMOUT_EN);
                }
                /* Create a chain of TDs in which current TD ponts to next TD. 
                * Each of this TDs should be seperatelly requested.
                */
                else if(i == (LCD_Seg_LCD_TD_SIZE - 1u))
                {
                    (void) CyDmaTdSetConfiguration(LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i],
                                                   (uint16) LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[i].length,
                                                   LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i + 1u],
                                                   TD_INC_DST_ADR | TD_INC_SRC_ADR | 
                                                   LCD_Seg_Lcd_Dma__TD_TERMOUT_EN);
                }
                /* Create a chain of TDs in which current TD ponts to next TD. 
                * After completion of transferring this TD following should
                * be automatically requested.
                */
                else
                {
                    (void) CyDmaTdSetConfiguration(LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i],
                                                   (uint16) LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[i].length,
                                                   LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i + 1u],
                                                   TD_INC_DST_ADR |  TD_INC_SRC_ADR | 
                                                   TD_AUTO_EXEC_NEXT);
                }
                
                (void) CyDmaTdSetAddress(LCD_Seg_lcdTd[(j * LCD_Seg_LCD_TD_SIZE) + i],
                                     LO16(srcAddr) + (((uint16) j) * LCD_Seg_ROW_LENGTH) +
                                     ((uint16) LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[i].offset),
                                      LO16(dstAddr) + LCD_Seg_SegLcdPort_DMA_TD_PROTO_BLOCK[i].offset);
            }
            
        #endif /* (1 == LCD_Seg_SegLcdPort_DMA_TD_PROTO_COUNT) */
    }

    if(CYRET_LOCKED != status)
    {
        (void) CyDmaChSetInitialTd(LCD_Seg_lcdChannel, LCD_Seg_lcdTd[0u]);
        (void) CyDmaChEnable(LCD_Seg_lcdChannel, 1u);
    }

    return(status);
}


/*******************************************************************************
* Function Name: LCD_Seg_DmaDispose
********************************************************************************
*
* Summary:
*  Releases allocated TDs disables DMA Channels used for component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  LCD_Seg_lcdTd[] - used to hold a set of allocated TD IDs that are
*  used by this component which will be released by this function.
*
*  LCD_Seg_lcdChannel- holds the channel number used by the LCD
*  component that will be released by this function.
*
*  LCD_Seg_frameTd[] - used to hold a set of allocated TD IDs that
*  are used by this component for Frame signal generation, which will be
*  released by this function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void LCD_Seg_DmaDispose(void) CYREENTRANT
{
    uint8 i;

    /* Release LCD DMA handle */
    LCD_Seg_Lcd_Dma_DmaRelease();

    /* Free the LCD DMA channel */
    (void) CyDmaChFree(LCD_Seg_lcdChannel);

    /* Release LCD Frame DMA handle */
    LCD_Seg_Frame_Dma_DmaRelease();

    /* Free the channel used in generation Frame signal */
    (void) CyDmaChFree(LCD_Seg_frameChannel);

    #if(LCD_Seg_WAVEFORM_TYPE == LCD_Seg__TYPE_A)
        for(i = 0u; i < 2u; i++)
        {
            CyDmaTdFree(LCD_Seg_frameTd[i]);
        }
    #else
        for(i = 0u; i < (LCD_Seg_COMM_NUM * 2u); i++)
        {
            CyDmaTdFree(LCD_Seg_frameTd[i]);
        }
    #endif /* LCD_Seg_WAVEFORM_TYPE == LCD_Seg__TYPE_A */

    /* Release all allocated TDs */
    for(i = 0u; i < (LCD_Seg_COMM_NUM * LCD_Seg_LCD_TD_SIZE); i++)
    {
        CyDmaTdFree(LCD_Seg_lcdTd[i]);
    }
}


/*******************************************************************************
* Function Name: LCD_Seg_Start
********************************************************************************
*
* Summary:
*  Starts the LCD component, DMA channels, frame buffer and hardware. Does not
*  clear the frame buffer SRAM if previously defined.
*
* Parameters:
*  None.
*
* Return:
*  Status one of standard status for PSoC3 Component
*      CYRET_SUCCESS - function completed successfully.
*      CYRET_LOCKED - the object was locked, already in use. Some of TDs or
*                     a channel already in use.
*
* Global variables:
*  LCD_Seg_initVar - is used to indicate initial configuration of
*  this component. The variable is initialized to zero and set to 1 the
*  first time LCD_Seg_Start() is called. This allows for component
*  initialization without re-initialization in all subsequent calls to the
*  LCD_Seg_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 LCD_Seg_Start(void) 
{
    uint8 status;

    /* If not Initialized then initialize all required hardware and software */
    if(LCD_Seg_initVar == 0u)
    {
        LCD_Seg_initVar = 1u;
        LCD_Seg_Init();
    }

    status = LCD_Seg_Enable();

    return(status);
}


/*******************************************************************************
* Function Name: LCD_Seg_Stop
********************************************************************************
*
* Summary:
*  Disables the LCD component and DMA channels. Automatically blanks the display
*  to avoid damage from DC offsets. Does not clear the frame buffer. Also it
*  turns off the power for the entire LCD system.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Seg_Stop(void) 
{
    uint8   interruptState;

    /* Global UDB disable */
    LCD_Seg_WriteControlReg(0u, (uint8) LCD_Seg_CNTL_CLK_EN_MASK);

    #if(LCD_Seg_POWER_MODE != LCD_Seg__NO_SLEEP)

        /* Disable generation of lp_ack signal from UBD to PM */
        LCD_Seg_LCDDAC_CONTROL_REG &= ((uint8) ~LCD_Seg_LCDDAC_UDB_LP_EN);

        /* Disable LCD timer */
        LCD_Seg_TIMER_CONTROL_REG &= ((uint8) ~LCD_Seg_TIMER_EN);

    #endif /* LCD_Seg_POWER_MODE != LCD_Seg__NO_SLEEP */

    /* Clear Continous Drive */
    LCD_Seg_LCDDAC_CONTROL_REG &= ((uint8) ~LCD_Seg_LCDDAC_CONT_DRIVE);
    /* Clear Continous Display Blink bit */
    LCD_Seg_LCDDAC_CONTROL_REG &= ((uint8) ~LCD_Seg_LCDDRV_DISPLAY_BLNK);
    /* Clear Continous Bypass Enable bit */
    LCD_Seg_LCDDAC_CONTROL_REG &= ((uint8) ~LCD_Seg_LCDDRV_BYPASS_EN);

    interruptState = CyEnterCriticalSection();

    /* Disable LCD fixed function HW in PM */
    LCD_Seg_PWR_MGR_REG &= ((uint8) ~LCD_Seg_LCD_EN);
    LCD_Seg_PWR_MGR_STBY_REG &= ((uint8) ~LCD_Seg_LCD_STBY_EN);

    CyExitCriticalSection(interruptState);

    /* Release DMA channels and TDs */
    LCD_Seg_DmaDispose();

    /* Set off component enable signal and stop all clocks */
    LCD_Seg_Int_Clock_Disable();
}


/*******************************************************************************
* Function Name: LCD_Seg_EnableInt
********************************************************************************
*
* Summary:
*  Enables the LCD "every subframe" and LCD wakeup interrupts.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  When you using PSoC5 LP it is required to have an interrupt with an ISR 
*  (even if it is empty) to wakeup CPU from sleep. It is specific of PSoC5 LP
*  CPU that uses "wait for interrupt" command when it enters into a sleep and
*  it won't wakeup if there won't be an actual interrupt. This API shoul always 
*  be called when component's operation in sleep is desired. 
*
*******************************************************************************/
void LCD_Seg_EnableInt(void) 
{
    /* Enable every sub-frame interrupt */
    CyIntEnable(LCD_Seg_ISR_NUMBER);
    
    #if(CY_PSOC5LP)
    
        /* Enable Wakeup ISR interrupt */
        CyIntEnable(LCD_Seg_WAKEUP_ISR_NUMBER);
    
    #endif /* CY_PSOC5LP */
}


/*******************************************************************************
* Function Name: LCD_Seg_DisableInt
********************************************************************************
*
* Summary:
*  Disables the LCD "every subframe" and LCD wakeup interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Seg_DisableInt(void) 
{
    /* Disable every sub-frame interrupt */
    CyIntDisable(LCD_Seg_ISR_NUMBER);
    
    #if(CY_PSOC5LP)
    
        /* Disable Wakeup ISR interrupt */
        CyIntDisable(LCD_Seg_WAKEUP_ISR_NUMBER);
    
    #endif /* CY_PSOC5LP */
}


/*******************************************************************************
* Function Name: LCD_Seg_SetBias
********************************************************************************
*
* Summary:
*  This function sets the bias level for the LCD glass to one of up to 64
*  values. The actual number of values is limited by the Analog supply voltage
*  Vdda as the bias voltage can not exceed Vdda. Changing the bias level affects
*  the LCD contrast.
*
* Parameters:
*  biasLevel : bias level for the diplay.
*
* Return:
*  Status one of standard status for PSoC3 Component:
*      CYRET_SUCCESS - function completed successfully.
*      CYRET_BAD_PARAM - evaluation of biasLevel parameter is failed.
*
*******************************************************************************/
uint8 LCD_Seg_SetBias(uint8 biasLevel) 
{
    uint8 status;

    if(biasLevel < 64u)
    {
        LCD_Seg_CONTRAST_CONTROL_REG = biasLevel;
        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return(status);
}


/*******************************************************************************
* Function Name: LCD_Seg_WriteInvertState
********************************************************************************
*
* Summary:
*  This function inverts the display based on invertState.
*
* Parameters:
*  invertState: the values can be - 0 (#LCD_Seg_NORMAL_STATE) for
*               normal noninverted display and 1
*                (#LCD_Seg_INVERTED_STATE) for inverted display.
*
* Return:
*  Status one of standard status for PSoC3 Component:
*      CYRET_SUCCESS - function completed successfully.
*      CYRET_BAD_PARAM - evaluation of invertState parameter is failed.
*
* Theory:
*  This function enables hardware invertor which inverts the data on the
*  outputs of port data registers. As the inversion occurs on all outputs no
*  mater is this a common or segment pin the frame buffer data for commons
*  requires to be changed to prevent DC ofsset in the LCD. So depending on the
*  function argument commons are initialized in the proper way.
*
*******************************************************************************/
uint8 LCD_Seg_WriteInvertState(uint8 invertState) 
{
    uint8 status;
    uint8 pixelState;
    uint16 pixelNumber;
    uint16 j;
    uint8 i;

    /* If parameter is valid then procced with driver control register write
    * operation, we don't want to affect other bits then invert bit.
    */
    if(invertState <= LCD_Seg_INVERTED_STATE)
    {
        if(invertState == LCD_Seg_NORMAL_STATE)
        {
            pixelState = LCD_Seg_PIXEL_STATE_OFF;
        }
        else
        {
            pixelState = LCD_Seg_PIXEL_STATE_ON;
        }

        #if defined(LCD_Seg_GANG)

            for(i = 0u; i < LCD_Seg_COMM_NUM; i++)
            {
                pixelNumber = LCD_Seg_gCommons[i];

                for(j = 0u; j < LCD_Seg_COMM_NUM; j++)
                {
                    pixelNumber = (pixelNumber & ((uint16) ~LCD_Seg_ROW_MASK)) | 
                                  (((uint16) j) << LCD_Seg_ROW_SHIFT);
                    
                    LCD_Seg_WRITE_PIXEL(pixelNumber, pixelState);
                }
            }

            for(i = 0u; i < LCD_Seg_COMM_NUM; i++)
            {
                LCD_Seg_WRITE_PIXEL(LCD_Seg_gCommons[i],
                                            (((uint8) ~pixelState) & ((uint8)LCD_Seg_STATE_MASK)));
            }

        #endif /* LCD_Seg_GANG */

        for(i = 0u; i < LCD_Seg_COMM_NUM; i++)
        {
            pixelNumber = LCD_Seg_commons[i];

            for(j = 0u; j < LCD_Seg_COMM_NUM; j++)
            {
                pixelNumber =  (pixelNumber & ((uint16)~LCD_Seg_ROW_MASK)) | 
                               (((uint16) j) << LCD_Seg_ROW_SHIFT);
                
                LCD_Seg_WRITE_PIXEL(pixelNumber, pixelState);
            }
        }

        /* Reinitialize the commons */
        for(i = 0u; i < LCD_Seg_COMM_NUM; i++)
        {
            LCD_Seg_WRITE_PIXEL(LCD_Seg_commons[i],
                                        (((uint8)~pixelState) & ((uint8)LCD_Seg_STATE_MASK)));
        }

        LCD_Seg_DRIVER_CONTROL_REG = (LCD_Seg_DRIVER_CONTROL_REG & 
                                              ((uint8)LCD_Seg_STATE_MASK)) | 
                                              ((uint8)(invertState << LCD_Seg_INVERT_SHIFT));

        status = CYRET_SUCCESS;
    }
    else
    {
        status = CYRET_BAD_PARAM;
    }

    return(status);
}


/*******************************************************************************
* Function Name: LCD_Seg_ReadInvertState
********************************************************************************
*
* Summary:
*  This function returns the current normal or inverted state of the display.
*
* Parameters:
*  None.
*
* Return:
*  State of the LCD - 0(#LCD_Seg_NORMAL_STATE) for normal non-inverted
*  display and 1(#LCD_Seg_INVERTED_STATE) for inverted display.
*
*******************************************************************************/
uint8 LCD_Seg_ReadInvertState(void) 
{
    /* Get only invert bit of Driver Control Register */
    return((LCD_Seg_DRIVER_CONTROL_REG & LCD_Seg_INVERT_BIT_MASK) >> LCD_Seg_INVERT_SHIFT);
}


/*******************************************************************************
* Function Name: LCD_Seg_ClearDisplay
********************************************************************************
*
* Summary:
*  This function clears the display RAM of the frame buffer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  LCD_Seg_buffer[] - an array is modified by this API. Clears the
*  frame buffer to all zeroes and then reinitialize it with a 1 in the
*  locations specified by the values from LCD_Seg_commons[].
*
*  LCD_Seg_commons[] - holds the pixel locations for common lines.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Seg_ClearDisplay(void) 
{
    uint16 i;
    uint8 dispState;

    /* Clear entire frame buffer to all zeroes */
    for(i = 0u; i < LCD_Seg_BUFFER_LENGTH; i++)
    {
        LCD_Seg_buffer[i] = 0u;
    }

    /* Reinitialize the commons */
    for(i = 0u; i < LCD_Seg_COMM_NUM; i++)
    {
        #ifdef LCD_Seg_GANG
            LCD_Seg_WRITE_PIXEL(LCD_Seg_gCommons[i], LCD_Seg_PIXEL_STATE_ON);
        #endif /* LCD_Seg_GANG */

        LCD_Seg_WRITE_PIXEL(LCD_Seg_commons[i], LCD_Seg_PIXEL_STATE_ON);
    }

    /* Read invert state. */
    dispState = (uint8)(((uint8)(LCD_Seg_DRIVER_CONTROL_REG &((uint8) ~LCD_Seg_STATE_MASK))) >> 
                LCD_Seg_INVERT_SHIFT);

    /* If we were in inverted state before the display was cleared, then we must
    * call WriteInvertState() as there is no separate API to clear inverted
    * display.
    */
    if(dispState == LCD_Seg_INVERTED_STATE)
    {
        (void) LCD_Seg_WriteInvertState(dispState);
    }
}


/*******************************************************************************
* Function Name: LCD_Seg_WritePixel
********************************************************************************
*
* Summary:
*  This function sets or clears a pixel based on pixelState in a frame buffer.
*  The Pixel is addressed by a packed number. User code can also directly write
*  the frame buffer RAM to create optimized interactions.
*
* Parameters:
*  pixelNumber: is the packed number that points to the pixel's location in the
*               frame buffer. The lowest three bits in the LSB low nibble are
*               the bit position in the byte, the LSB upper nibble (4 bits) is
*               the byte address in the multiplex row and the MSB low nibble
*               (4 bits) is the multiplex row number.
*  pixelState: 0 for pixel off,1 for pixel on, 2 for pixel invert.
*
* Return:
*  Status one of standard status for PSoC3 Component:
*      CYRET_SUCCESS - function completed successfully.
*      CYRET_BAD_PARAM - evaluation of parameters is failed.
*
* Global variables:
*  LCD_Seg_buffer[] - an array is modified by this API. This API
*  may set or clear certain bit in the array defined by the input parameter.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 LCD_Seg_WritePixel(uint16 pixelNumber, uint8 pixelState) 
{
    uint8 mask;
    uint8 row;
    uint8 port;
    uint8 pin;
    uint8 status;

    if((LCD_Seg_NOT_CON != pixelNumber) || (!(pixelState > LCD_Seg_PIXEL_STATE_INVERT)))
    {
        if(pixelState == LCD_Seg_PIXEL_STATE_INVERT)
        {
            /* Invert actual pixel state */
            pixelState = LCD_Seg_ReadPixel(pixelNumber);
            pixelState = ~pixelState;
        }

        /* Extract the pixel information to locate desired pixel in the frame
        * buffer.
        */
        row = LCD_Seg_EXTRACT_ROW(pixelNumber);
        port = LCD_Seg_EXTRACT_PORT(pixelNumber);
        pin = LCD_Seg_EXTRACT_PIN(pixelNumber);

        /* Write new pixel's value to the frame buffer. */
        mask = (uint8) ~((uint8)(((uint8)LCD_Seg_PIXEL_STATE_ON) << pin));

        /* Write new pixel's value to the frame buffer. */
        LCD_Seg_buffer[(row * LCD_Seg_MAX_BUFF_ROWS) + port] =
            (LCD_Seg_buffer[(row * LCD_Seg_MAX_BUFF_ROWS) + port] & mask) | 
                ((uint8)(((uint8) pixelState) << pin));

        status = CYRET_SUCCESS;
    }
    else
    {
        /* Let the User know he is entered wrong parameter. */
        status = CYRET_BAD_PARAM;
    }

    return(status);
}


/*******************************************************************************
* Function Name: LCD_Seg_ReadPixel
********************************************************************************
*
* Summary:
*  This function reads a pixels state in a frame buffer. The Pixel is addressed
*  by a packed number. User code can also directly read the frame buffer RAM to
*  create optimized interactions.
*
* Parameters:
*  pixelNumber: is the packed number that points to the pixel's location in the
*               frame buffer. The lowest three bits in the LSB low nibble are
*               the bit position in the byte, the LSB upper nibble (4 bits) is
*               the byte address in the multiplex row and the MSB low nibble
*               (4 bits) is the multiplex row number.
*
* Return:
*  Pixel State:
*       LCD_Seg_PIXEL_STATE_OFF - for pixel off.
*       LCD_Seg_PIXEL_STATE_ON - for pixel on.
*       LCD_Seg_PIXEL_UNKNOWN_STATE - for not assigned pixel.
*
* Global variables:
*  LCD_Seg_buffer[] - holds the state of every pixel of the LCD glass
*  which can be read by this function.
*
*******************************************************************************/
uint8 LCD_Seg_ReadPixel(uint16 pixelNumber) 
{
    uint8 pixelState;
    uint8 row;
    uint8 port;
    uint8 pin;

    if(pixelNumber != LCD_Seg_NOT_CON)
    {
        /* Extract the pixel information to locate desired pixel in the frame
        * buffer.
        */
        row = LCD_Seg_EXTRACT_ROW(pixelNumber);
        port = LCD_Seg_EXTRACT_PORT(pixelNumber);
        pin = LCD_Seg_EXTRACT_PIN(pixelNumber);

        pixelState = (((LCD_Seg_buffer[(row * LCD_Seg_MAX_BUFF_ROWS) + port]) >> pin) &
                    LCD_Seg_PIXEL_STATE_ON);
    }
    else
    {
        pixelState = LCD_Seg_PIXEL_UNKNOWN_STATE;
    }

    return(pixelState);
}

/*******************************************************************************
* Function Name: LCD_Seg_Write7SegDigit_0
********************************************************************************
*
* Summary:
*  This function displays an 4-bit Hex digit in the range of 0-9 and A-F 
*  7 segment display. The user must have defined what portion of the displays
*  segments make up the 7 segment display portion in the component customizer.
*  Multiple, separate 7 segment displays can be created in the frame buffer and
*  are addressed through the index (n) in the function name. Function/s only
*  included if component 7 segment customizerwizard defines the 7 segment option.
*
* Parameters:
*  digit : unsigned integer value in the range of 0 to 16 to be displayed as a
*  hexadecimal digit. The ASCII numbers of a hexadecimal characters are also
*  valid. In case of a invalid digit value displays 0 in position specified.
*  position : Position of the digit as counted right to left starting at 0 on the
*  right. If the defined display does not contain a digit in the position then
*  the digit will not be displayed.
*
* Return: 
*  None.
*
* Global variables:
*  LCD_Seg_7SegDigits[] - used as a look-up table for 7 Segment helper.
*  Holds decoded digit's pixel reflection for the helper.
*
*  LCD_Seg_disp0[][] - holds pixels locations for 7 Segment helper in 
*  the Frame Buffer.
*
*  LCD_Seg_DIGIT_NUM_0 - holds the maximum digit number for the helper.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Seg_Write7SegDigit_0(uint8 digit, uint8 position) 
{
    static const uint16 CYCODE LCD_Seg_disp0[1u][7u] = {{LCD_Seg_NOT_CON, LCD_Seg_NOT_CON, LCD_Seg_NOT_CON,
    LCD_Seg_NOT_CON, LCD_Seg_NOT_CON, LCD_Seg_NOT_CON, LCD_Seg_NOT_CON}};
    uint8 i;

    /* if digit < 16 then do nothing (we have correct data) */
    if(digit <= 16u)
    {
        /* nothing to do, as we have correct digit value */
    }
    /* if digit <= 0x39 then digit is ascii code of a number (0-9) */
    else if(digit <= 0x39u)
    {
        digit -= 0x30u;
    }
    /* if digit <= 0x39 then digit is ascii code of a hex number (A-F) */
    else if(digit <= 0x47u)
    {
        digit -= 0x37u;
    }
    /* else we have invalid digit, and we will print '8' instead */
    else
    {
        digit = 0u;
    }

    if((position / LCD_Seg_DIGIT_NUM_0) == 0u)
    {
        position = LCD_Seg_DIGIT_NUM_0 - position - 1u;
        for(i = 0u; i < LCD_Seg_7SEG_PIX_NUM; i++)
        {
            /* Select pixel state for the digit base on value in look-up table */
            LCD_Seg_WRITE_PIXEL(LCD_Seg_disp0[position][i],
            ((uint8)(LCD_Seg_7SegDigits[digit] >> i)) & ((uint8)LCD_Seg_PIXEL_STATE_ON));
        }
    }
}


/*******************************************************************************
* Function Name: LCD_Seg_Write7SegNumber_0
********************************************************************************
*
* Summary:
*  This function displays a 16-bit integer value on a 1 to 5 digit on 7 segment
*  display. The user must have defined what portion of the display's segments
*  make up the 7 segment display portion in the customizer. Multiple, separate
*  7 segment displays can be created in the frame buffer and are addressed
*  through the index (n) in the function name. Function/s only included if
*  component 7 segment customizer defines the 7 segment option.
*
* Parameters:  
*  value:    unsigned integer value to be displayed.
*  position: position of the least significant digit as counted right to left
*            starting at 0 on the right. If the defined display contains fewer
*            digits then the value requires for display for the most significant
*            digit/s will not be displayed.
*  mode:     0 - no leading zeroes, 1 - leading zeroes are displayed.
*
* Return: 
*  None.
*
* Global variables:
*  LCD_Seg_DIGIT_NUM_0 - holds the maximum digit number for the helper.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Seg_Write7SegNumber_0(uint16 value, uint8 position, uint8 mode) 
{ 
    uint8 i;
    uint8 num;

    if(0u != LCD_Seg_DIGIT_NUM_0)
    {
        position = position % LCD_Seg_DIGIT_NUM_0;
    }

    /* While current digit position in the range of display keep processing the output */
    for(i = position; i < LCD_Seg_DIGIT_NUM_0; i++)
    {
        num = (uint8)(value % 10u);
        if((0u == value) && (0u == mode)) 
        {
            /* In case of 'no leading zeros' each extra digit will be cleared */ 
            LCD_Seg_Write7SegDigit_0(LCD_Seg_7SEG_BLANK_DIG, i);
        }
        else
        {
            /* Display subsequent digit or '0' if 'no leading zeros' mode */ 
            LCD_Seg_Write7SegDigit_0(num, i);
        }
        value /= 10u; 
    }
}


/*******************************************************************************
* Function Name: LCD_Seg_WriteBargraph_1
********************************************************************************
*
* Summary:
*  This function displays an 8-bit integer location on a 1 to 255 segment
*  bar-graph (numbered left to right). The bar graph may be any user defined
*  size between 1 and 255 The bar graph may be any user defined created in a
*  circle to display rotary position. The user defines what portion of the
*  displays segments make up the bar-graph portion. Multiple, separate bargraph
*  displays can be created in the frame buffer and are addressed through the
*  index (n) in the function name. Function/s only included if component
*  bar-graph customizer defines the 7 segment option
*
* Parameters:
*  location: unsigned integer Location to be displayed. 0 - all bar-graph
*            elements off. Max Value = the number of segments in the bar-graph.
*            Locations greater then the number of segments in the bar-graph will
*            be limited to the number of segments physically provided.
*  mode:     0 - only the Location segment is turned on, 1 - The Location 
*            segment and all segments to the left are turned on, -1 - the
*            location segment and all segments to the right are turned on. 2-10
*            display the location segment and 2-10 segments to the right to
*            create wide indicators.
*
* Return: 
*  None.
*
* Global variables:
*  LCD_Seg_DIGIT_NUM_1 - holds the maximum digit number for the helper.
*
*  LCD_Seg_disp1[][] - stores pixels locations for BarGraph helper 
*  in the Frame Buffer.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Seg_WriteBargraph_1(uint16 location, int8 mode) 
{
    static const uint16 CYCODE LCD_Seg_disp1[2u][1u] = {{0u}, {LCD_Seg_NOT_CON}};
    uint16 i;
    uint16 maxValue = 1u;
    uint16 locationInt = location;
    int8 modeInt = mode;

    if (locationInt != 0u)
    {
        /* If location greater then the number of elements in bar graph then
        * set location to a maxvalue and set mode to 0.
        */
        if(locationInt > maxValue)
        {
            locationInt = 1u;
            modeInt = -1;
        }
        
        for(i = 1u; i <= ((uint16)LCD_Seg_DIGIT_NUM_1); i++) 
        {
            LCD_Seg_WRITE_PIXEL(LCD_Seg_disp1[i][0u], LCD_Seg_PIXEL_STATE_OFF);
        }
        
        switch(modeInt)
        {
            case 0:
                LCD_Seg_WRITE_PIXEL(LCD_Seg_disp1[locationInt][0u], LCD_Seg_PIXEL_STATE_ON);
                break;
            case 1:
                for(i = locationInt; i >= 1u; i--) 
                {
                    LCD_Seg_WRITE_PIXEL(LCD_Seg_disp1[i][0u], LCD_Seg_PIXEL_STATE_ON);
                }
                break;
            case -1:
                for(i = locationInt; i <= maxValue; i++) 
                {
                    LCD_Seg_WRITE_PIXEL(LCD_Seg_disp1[i][0u], LCD_Seg_PIXEL_STATE_ON);
                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                if(((uint16) ((locationInt + ((uint16) modeInt)) - 1u)) <= maxValue) 
                {
                    maxValue = (locationInt + ((uint16) modeInt)) - 1u;
                }
                for(i = locationInt; i <= maxValue; i++) 
                {
                    LCD_Seg_WRITE_PIXEL(LCD_Seg_disp1[i][0u], LCD_Seg_PIXEL_STATE_ON);
                }
                break;
            default:
                break;
        }
    }
    else 
    {
        for (i = 1u; i <= maxValue; i++) 
        {
            LCD_Seg_WRITE_PIXEL(LCD_Seg_disp1[i][0u], LCD_Seg_PIXEL_STATE_OFF);
        }
    }
}

/*******************************************************************************
* Function Name: LCD_Seg_WriteControlReg
********************************************************************************
*
* Summary:
*  This function dedicated for internal component usage only. It used to prepare
*  the values for LCD Control Register wich will be later writen to it by DMA.
*
* Parameters:
*  value: value to be written to Control Register.
*  mask: mask for the respective value. Mask should contain '0' in bit positions
*        that dessired to be set. For example for the value 0x03(00000011) mask
*        will be 0xFC(11111100).
*
* Return:
*  None.
*
* Global variables:
*  LCD_Seg_frameTx[] - used to store a set of precalculated values
*  for control register which is generated by this function.
*
* Theory:
*  Non API function. Users should never use this function directly. To save UDB
*  resources there is only one Control Register used for LCD operation. This
*  Control Register contains Frame bit which is used to generate Frame signal.
*  This is a dynamic signal which is transfered by the DMA. So all other
*  control bist will be owervriten on every DMA transaction. That's why all the
*  data that need to be remained in the Control Register are written to array
*  where predefined values of Frame contain.
*
*******************************************************************************/
static void LCD_Seg_WriteControlReg(uint8 value, uint8 mask) CYREENTRANT
{
    uint8 i;

    for(i = 0u; i < LCD_Seg_CONTROL_WRITE_COUNT; i++)
    {
        /* Write the value for control register to each element of the array. */
        LCD_Seg_frameTx[i] = (LCD_Seg_frameTx[i] & mask) | value;
    }
}


/* [] END OF FILE */
