/*******************************************************************************
* File Name: Launcher_UART_midi.h
* Version 2.60
*
* Description:
*  Header File for the USBFS MIDI module.
*  Contains prototypes and constant values.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_Launcher_UART_midi_H)
#define CY_USBFS_Launcher_UART_midi_H

#include "cytypes.h"
#include "Launcher_UART.h"


/***************************************
*    Data Struct Definition
***************************************/

/* The following structure is used to hold status information for
   building and parsing incoming MIDI messages. */
typedef struct
{
    uint8    length;        /* expected length */
    uint8    count;         /* current byte count */
    uint8    size;          /* complete size */
    uint8    runstat;       /* running status */
    uint8    msgBuff[4];    /* message buffer */
} Launcher_UART_MIDI_RX_STATUS;


/***************************************
*           MIDI Constants.
***************************************/

#define Launcher_UART_ONE_EXT_INTRF              (0x01u)
#define Launcher_UART_TWO_EXT_INTRF              (0x02u)

/* Flag definitions for use with MIDI device inquiry */
#define Launcher_UART_INQ_SYSEX_FLAG             (0x01u)
#define Launcher_UART_INQ_IDENTITY_REQ_FLAG      (0x02u)

/* USB-MIDI Code Index Number Classifications (MIDI Table 4-1) */
#define Launcher_UART_CIN_MASK                   (0x0Fu)
#define Launcher_UART_RESERVED0                  (0x00u)
#define Launcher_UART_RESERVED1                  (0x01u)
#define Launcher_UART_2BYTE_COMMON               (0x02u)
#define Launcher_UART_3BYTE_COMMON               (0x03u)
#define Launcher_UART_SYSEX                      (0x04u)
#define Launcher_UART_1BYTE_COMMON               (0x05u)
#define Launcher_UART_SYSEX_ENDS_WITH1           (0x05u)
#define Launcher_UART_SYSEX_ENDS_WITH2           (0x06u)
#define Launcher_UART_SYSEX_ENDS_WITH3           (0x07u)
#define Launcher_UART_NOTE_OFF                   (0x08u)
#define Launcher_UART_NOTE_ON                    (0x09u)
#define Launcher_UART_POLY_KEY_PRESSURE          (0x0Au)
#define Launcher_UART_CONTROL_CHANGE             (0x0Bu)
#define Launcher_UART_PROGRAM_CHANGE             (0x0Cu)
#define Launcher_UART_CHANNEL_PRESSURE           (0x0Du)
#define Launcher_UART_PITCH_BEND_CHANGE          (0x0Eu)
#define Launcher_UART_SINGLE_BYTE                (0x0Fu)

#define Launcher_UART_CABLE_MASK                 (0xF0u)
#define Launcher_UART_MIDI_CABLE_00              (0x00u)
#define Launcher_UART_MIDI_CABLE_01              (0x10u)

#define Launcher_UART_EVENT_BYTE0                (0x00u)
#define Launcher_UART_EVENT_BYTE1                (0x01u)
#define Launcher_UART_EVENT_BYTE2                (0x02u)
#define Launcher_UART_EVENT_BYTE3                (0x03u)
#define Launcher_UART_EVENT_LENGTH               (0x04u)

#define Launcher_UART_MIDI_STATUS_BYTE_MASK      (0x80u)
#define Launcher_UART_MIDI_STATUS_MASK           (0xF0u)
#define Launcher_UART_MIDI_SINGLE_BYTE_MASK      (0x08u)
#define Launcher_UART_MIDI_NOTE_OFF              (0x80u)
#define Launcher_UART_MIDI_NOTE_ON               (0x90u)
#define Launcher_UART_MIDI_POLY_KEY_PRESSURE     (0xA0u)
#define Launcher_UART_MIDI_CONTROL_CHANGE        (0xB0u)
#define Launcher_UART_MIDI_PROGRAM_CHANGE        (0xC0u)
#define Launcher_UART_MIDI_CHANNEL_PRESSURE      (0xD0u)
#define Launcher_UART_MIDI_PITCH_BEND_CHANGE     (0xE0u)
#define Launcher_UART_MIDI_SYSEX                 (0xF0u)
#define Launcher_UART_MIDI_EOSEX                 (0xF7u)
#define Launcher_UART_MIDI_QFM                   (0xF1u)
#define Launcher_UART_MIDI_SPP                   (0xF2u)
#define Launcher_UART_MIDI_SONGSEL               (0xF3u)
#define Launcher_UART_MIDI_TUNEREQ               (0xF6u)
#define Launcher_UART_MIDI_ACTIVESENSE           (0xFEu)

/* MIDI Universal System Exclusive defines */
#define Launcher_UART_MIDI_SYSEX_NON_REAL_TIME   (0x7Eu)
#define Launcher_UART_MIDI_SYSEX_REALTIME        (0x7Fu)
/* ID of target device */
#define Launcher_UART_MIDI_SYSEX_ID_ALL          (0x7Fu)
/* Sub-ID#1*/
#define Launcher_UART_MIDI_SYSEX_GEN_INFORMATION (0x06u)
#define Launcher_UART_MIDI_SYSEX_GEN_MESSAGE     (0x09u)
/* Sub-ID#2*/
#define Launcher_UART_MIDI_SYSEX_IDENTITY_REQ    (0x01u)
#define Launcher_UART_MIDI_SYSEX_IDENTITY_REPLY  (0x02u)
#define Launcher_UART_MIDI_SYSEX_SYSTEM_ON       (0x01u)
#define Launcher_UART_MIDI_SYSEX_SYSTEM_OFF      (0x02u)

#define Launcher_UART_CUSTOM_UART_TX_PRIOR_NUM   (0x04u)
#define Launcher_UART_CUSTOM_UART_RX_PRIOR_NUM   (0x02u)

#define Launcher_UART_ISR_SERVICE_MIDI_OUT     \
        ( (Launcher_UART_ENABLE_MIDI_API != 0u) && \
          (Launcher_UART_MIDI_OUT_BUFF_SIZE > 0) && (Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO) )
#define Launcher_UART_ISR_SERVICE_MIDI_IN     \
        ( (Launcher_UART_ENABLE_MIDI_API != 0u) && (Launcher_UART_MIDI_IN_BUFF_SIZE > 0) )

/***************************************
* External function references
***************************************/

void Launcher_UART_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg)
                                                     ;


/***************************************
*    External references
***************************************/

#if (Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_ONE_EXT_INTRF)
    #include "MIDI1_UART.h"
#endif /* End Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_ONE_EXT_INTRF */
#if (Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_TWO_EXT_INTRF)
    #include "MIDI2_UART.h"
#endif /* End Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_TWO_EXT_INTRF */
#if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
    #include <CyDmac.h>
#endif /* End Launcher_UART_EP_MM */


/***************************************
*    Private function prototypes
***************************************/

void Launcher_UART_PrepareInBuffer(uint8 ic, const uint8 srcBuff[], uint8 eventLen, uint8 cable)
                                                                 ;
#if (Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_ONE_EXT_INTRF)
    void Launcher_UART_MIDI_Init(void) ;
    uint8 Launcher_UART_ProcessMidiIn(uint8 mData, Launcher_UART_MIDI_RX_STATUS *rxStat)
                                                                ;
    uint8 Launcher_UART_MIDI1_GetEvent(void) ;
    void Launcher_UART_MIDI1_ProcessUsbOut(const uint8 epBuf[])
                                                     ;

    #if (Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_TWO_EXT_INTRF)
        uint8 Launcher_UART_MIDI2_GetEvent(void) ;
        void Launcher_UART_MIDI2_ProcessUsbOut(const uint8 epBuf[])
                                                    ;
    #endif /* End Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_TWO_EXT_INTRF */
#endif /* End Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_ONE_EXT_INTRF */


/***************************************
* External data references
***************************************/

#if defined(Launcher_UART_ENABLE_MIDI_STREAMING)

#if (Launcher_UART_MIDI_IN_BUFF_SIZE > 0)
    #if (Launcher_UART_MIDI_IN_BUFF_SIZE >= 256)
        extern volatile uint16 Launcher_UART_midiInPointer;                       /* Input endpoint buffer pointer */
    #else
        extern volatile uint8 Launcher_UART_midiInPointer;                        /* Input endpoint buffer pointer */
    #endif /* End Launcher_UART_MIDI_IN_BUFF_SIZE >=256 */
    extern volatile uint8 Launcher_UART_midi_in_ep;                               /* Input endpoint number */
    extern uint8 Launcher_UART_midiInBuffer[Launcher_UART_MIDI_IN_BUFF_SIZE];  /* Input endpoint buffer */
#endif /* Launcher_UART_MIDI_IN_BUFF_SIZE > 0 */

#if (Launcher_UART_MIDI_OUT_BUFF_SIZE > 0)
    extern volatile uint8 Launcher_UART_midi_out_ep;                               /* Output endpoint number */
    extern uint8 Launcher_UART_midiOutBuffer[Launcher_UART_MIDI_OUT_BUFF_SIZE]; /* Output endpoint buffer */
#endif /* Launcher_UART_MIDI_OUT_BUFF_SIZE > 0 */

#if (Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_ONE_EXT_INTRF)
    extern volatile uint8 Launcher_UART_MIDI1_InqFlags;                              /* Device inquiry flag */
    #if (Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_TWO_EXT_INTRF)
        extern volatile uint8 Launcher_UART_MIDI2_InqFlags;                          /* Device inquiry flag */
    #endif /* End Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_TWO_EXT_INTRF */
#endif /* End Launcher_UART_MIDI_EXT_MODE >= Launcher_UART_ONE_EXT_INTRF */

#endif /* Launcher_UART_ENABLE_MIDI_STREAMING */


#endif /* End CY_USBFS_Launcher_UART_midi_H */


/* [] END OF FILE */
