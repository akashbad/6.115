/*******************************************************************************
* File Name: .h
* Version 2.60
*
* Description:
*  This private file provides constants and parameter values for the
*  USBFS Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_Launcher_UART_pvt_H)
#define CY_USBFS_Launcher_UART_pvt_H


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors*/
extern const uint8 CYCODE Launcher_UART_DEVICE0_DESCR[18u];
extern const uint8 CYCODE Launcher_UART_DEVICE0_CONFIGURATION0_DESCR[67u];
extern const T_Launcher_UART_EP_SETTINGS_BLOCK CYCODE Launcher_UART_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[3u];
extern const uint8 CYCODE Launcher_UART_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_Launcher_UART_LUT CYCODE Launcher_UART_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_Launcher_UART_LUT CYCODE Launcher_UART_DEVICE0_TABLE[2u];
extern const T_Launcher_UART_LUT CYCODE Launcher_UART_TABLE[1u];
extern const uint8 CYCODE Launcher_UART_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE Launcher_UART_STRING_DESCRIPTORS[159u];


extern const uint8 CYCODE Launcher_UART_MSOS_DESCRIPTOR[Launcher_UART_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE Launcher_UART_MSOS_CONFIGURATION_DESCR[Launcher_UART_MSOS_CONF_DESCR_LENGTH];
#if defined(Launcher_UART_ENABLE_IDSN_STRING)
    extern uint8 Launcher_UART_idSerialNumberStringDescriptor[Launcher_UART_IDSN_DESCR_LENGTH];
#endif /* Launcher_UART_ENABLE_IDSN_STRING */

extern volatile uint8 Launcher_UART_interfaceNumber;
extern volatile uint8 Launcher_UART_interfaceSetting[Launcher_UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 Launcher_UART_interfaceSetting_last[Launcher_UART_MAX_INTERFACES_NUMBER];
extern volatile uint8 Launcher_UART_deviceAddress;
extern volatile uint8 Launcher_UART_interfaceStatus[Launcher_UART_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *Launcher_UART_interfaceClass;

extern volatile T_Launcher_UART_EP_CTL_BLOCK Launcher_UART_EP[Launcher_UART_MAX_EP];
extern volatile T_Launcher_UART_TD Launcher_UART_currentTD;

#if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
    extern uint8 Launcher_UART_DmaChan[Launcher_UART_MAX_EP];
    extern uint8 Launcher_UART_DmaTd[Launcher_UART_MAX_EP];
#endif /* End Launcher_UART_EP_MM */

extern volatile uint8 Launcher_UART_ep0Toggle;
extern volatile uint8 Launcher_UART_lastPacketSize;
extern volatile uint8 Launcher_UART_ep0Mode;
extern volatile uint8 Launcher_UART_ep0Count;
extern volatile uint16 Launcher_UART_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  Launcher_UART_ReInitComponent(void) ;
void  Launcher_UART_HandleSetup(void) ;
void  Launcher_UART_HandleIN(void) ;
void  Launcher_UART_HandleOUT(void) ;
void  Launcher_UART_LoadEP0(void) ;
uint8 Launcher_UART_InitControlRead(void) ;
uint8 Launcher_UART_InitControlWrite(void) ;
void  Launcher_UART_ControlReadDataStage(void) ;
void  Launcher_UART_ControlReadStatusStage(void) ;
void  Launcher_UART_ControlReadPrematureStatus(void)
                                                ;
uint8 Launcher_UART_InitControlWrite(void) ;
uint8 Launcher_UART_InitZeroLengthControlTransfer(void)
                                                ;
void  Launcher_UART_ControlWriteDataStage(void) ;
void  Launcher_UART_ControlWriteStatusStage(void) ;
void  Launcher_UART_ControlWritePrematureStatus(void)
                                                ;
uint8 Launcher_UART_InitNoDataControlTransfer(void) ;
void  Launcher_UART_NoDataControlStatusStage(void) ;
void  Launcher_UART_InitializeStatusBlock(void) ;
void  Launcher_UART_UpdateStatusBlock(uint8 completionCode) ;
uint8 Launcher_UART_DispatchClassRqst(void) ;

void Launcher_UART_Config(uint8 clearAltSetting) ;
void Launcher_UART_ConfigAltChanged(void) ;
void Launcher_UART_ConfigReg(void) ;

const T_Launcher_UART_LUT CYCODE *Launcher_UART_GetConfigTablePtr(uint8 c)
                                                            ;
const T_Launcher_UART_LUT CYCODE *Launcher_UART_GetDeviceTablePtr(void)
                                                            ;
const uint8 CYCODE *Launcher_UART_GetInterfaceClassTablePtr(void)
                                                    ;
uint8 Launcher_UART_ClearEndpointHalt(void) ;
uint8 Launcher_UART_SetEndpointHalt(void) ;
uint8 Launcher_UART_ValidateAlternateSetting(void) ;

void Launcher_UART_SaveConfig(void) ;
void Launcher_UART_RestoreConfig(void) ;

#if defined(Launcher_UART_ENABLE_IDSN_STRING)
    void Launcher_UART_ReadDieID(uint8 descr[]) ;
#endif /* Launcher_UART_ENABLE_IDSN_STRING */

#if defined(Launcher_UART_ENABLE_HID_CLASS)
    uint8 Launcher_UART_DispatchHIDClassRqst(void);
#endif /* End Launcher_UART_ENABLE_HID_CLASS */
#if defined(Launcher_UART_ENABLE_AUDIO_CLASS)
    uint8 Launcher_UART_DispatchAUDIOClassRqst(void);
#endif /* End Launcher_UART_ENABLE_HID_CLASS */
#if defined(Launcher_UART_ENABLE_CDC_CLASS)
    uint8 Launcher_UART_DispatchCDCClassRqst(void);
#endif /* End Launcher_UART_ENABLE_CDC_CLASS */

CY_ISR_PROTO(Launcher_UART_EP_0_ISR);
#if(Launcher_UART_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_1_ISR);
#endif /* End Launcher_UART_EP1_ISR_REMOVE */
#if(Launcher_UART_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_2_ISR);
#endif /* End Launcher_UART_EP2_ISR_REMOVE */
#if(Launcher_UART_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_3_ISR);
#endif /* End Launcher_UART_EP3_ISR_REMOVE */
#if(Launcher_UART_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_4_ISR);
#endif /* End Launcher_UART_EP4_ISR_REMOVE */
#if(Launcher_UART_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_5_ISR);
#endif /* End Launcher_UART_EP5_ISR_REMOVE */
#if(Launcher_UART_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_6_ISR);
#endif /* End Launcher_UART_EP6_ISR_REMOVE */
#if(Launcher_UART_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_7_ISR);
#endif /* End Launcher_UART_EP7_ISR_REMOVE */
#if(Launcher_UART_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_EP_8_ISR);
#endif /* End Launcher_UART_EP8_ISR_REMOVE */
CY_ISR_PROTO(Launcher_UART_BUS_RESET_ISR);
#if(Launcher_UART_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_SOF_ISR);
#endif /* End Launcher_UART_SOF_ISR_REMOVE */
#if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
    CY_ISR_PROTO(Launcher_UART_ARB_ISR);
#endif /* End Launcher_UART_EP_MM */
#if(Launcher_UART_DP_ISR_REMOVE == 0u)
    CY_ISR_PROTO(Launcher_UART_DP_ISR);
#endif /* End Launcher_UART_DP_ISR_REMOVE */


/***************************************
* Request Handlers
***************************************/

uint8 Launcher_UART_HandleStandardRqst(void) ;
uint8 Launcher_UART_DispatchClassRqst(void) ;
uint8 Launcher_UART_HandleVendorRqst(void) ;


/***************************************
*    HID Internal references
***************************************/
#if defined(Launcher_UART_ENABLE_HID_CLASS)
    void Launcher_UART_FindReport(void) ;
    void Launcher_UART_FindReportDescriptor(void) ;
    void Launcher_UART_FindHidClassDecriptor(void) ;
#endif /* Launcher_UART_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/
#if defined(Launcher_UART_ENABLE_MIDI_STREAMING)
    void Launcher_UART_MIDI_IN_EP_Service(void) ;
#endif /* Launcher_UART_ENABLE_MIDI_STREAMING */


#endif /* CY_USBFS_Launcher_UART_pvt_H */


/* [] END OF FILE */
