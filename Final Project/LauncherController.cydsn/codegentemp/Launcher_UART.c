/*******************************************************************************
* File Name: Launcher_UART.c
* Version 2.60
*
* Description:
*  API for USBFS Component.
*
* Note:
*  Many of the functions use endpoint number.  RAM arrays are sized with 9
*  elements so they are indexed directly by epNumber.  The SIE and ARB
*  registers are indexed by variations of epNumber - 1.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <CyDmac.h>
#include "Launcher_UART.h"
#include "Launcher_UART_pvt.h"
#include "Launcher_UART_hid.h"
#if(Launcher_UART_DMA1_REMOVE == 0u)
    #include "Launcher_UART_ep1_dma.h"
#endif   /* End Launcher_UART_DMA1_REMOVE */
#if(Launcher_UART_DMA2_REMOVE == 0u)
    #include "Launcher_UART_ep2_dma.h"
#endif   /* End Launcher_UART_DMA2_REMOVE */
#if(Launcher_UART_DMA3_REMOVE == 0u)
    #include "Launcher_UART_ep3_dma.h"
#endif   /* End Launcher_UART_DMA3_REMOVE */
#if(Launcher_UART_DMA4_REMOVE == 0u)
    #include "Launcher_UART_ep4_dma.h"
#endif   /* End Launcher_UART_DMA4_REMOVE */
#if(Launcher_UART_DMA5_REMOVE == 0u)
    #include "Launcher_UART_ep5_dma.h"
#endif   /* End Launcher_UART_DMA5_REMOVE */
#if(Launcher_UART_DMA6_REMOVE == 0u)
    #include "Launcher_UART_ep6_dma.h"
#endif   /* End Launcher_UART_DMA6_REMOVE */
#if(Launcher_UART_DMA7_REMOVE == 0u)
    #include "Launcher_UART_ep7_dma.h"
#endif   /* End Launcher_UART_DMA7_REMOVE */
#if(Launcher_UART_DMA8_REMOVE == 0u)
    #include "Launcher_UART_ep8_dma.h"
#endif   /* End Launcher_UART_DMA8_REMOVE */


/***************************************
* Global data allocation
***************************************/

uint8 Launcher_UART_initVar = 0u;
#if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
    uint8 Launcher_UART_DmaChan[Launcher_UART_MAX_EP];
    uint8 Launcher_UART_DmaTd[Launcher_UART_MAX_EP];
#endif /* End Launcher_UART_EP_MM */


/*******************************************************************************
* Function Name: Launcher_UART_Start
********************************************************************************
*
* Summary:
*  This function initialize the USB SIE, arbiter and the
*  endpoint APIs, including setting the D+ Pullup
*
* Parameters:
*  device: Contains the device number of the desired device descriptor.
*          The device number can be found in the Device Descriptor Tab of
*          "Configure" dialog, under the settings of desired Device Descriptor,
*          in the "Device Number" field.
*  mode: The operating voltage. This determines whether the voltage regulator
*        is enabled for 5V operation or if pass through mode is used for 3.3V
*        operation. Symbolic names and their associated values are given in the
*        following table.
*       Launcher_UART_3V_OPERATION - Disable voltage regulator and pass-thru
*                                       Vcc for pull-up
*       Launcher_UART_5V_OPERATION - Enable voltage regulator and use
*                                       regulator for pull-up
*       Launcher_UART_DWR_VDDD_OPERATION - Enable or Disable voltage
*                         regulator depend on Vddd Voltage configuration in DWR.
*
* Return:
*   None.
*
* Global variables:
*  The Launcher_UART_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time Launcher_UART_Start() is called.
*  This allows for component Re-Start without unnecessary re-initialization
*  in all subsequent calls to the Launcher_UART_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of UART_Start() routine, or the user may call
*  Launcher_UART_Init() and Launcher_UART_InitComponent() as done
*  in the Launcher_UART_Start() routine.
*
* Side Effects:
*   This function will reset all communication states to default.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_Start(uint8 device, uint8 mode) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Launcher_UART_initVar == 0u)
    {
        Launcher_UART_Init();
        Launcher_UART_initVar = 1u;
    }
    Launcher_UART_InitComponent(device, mode);
}


/*******************************************************************************
* Function Name: Launcher_UART_Init
********************************************************************************
*
* Summary:
*  Initialize component's hardware. Usually called in Launcher_UART_Start().
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
void Launcher_UART_Init(void) 
{
    uint8 enableInterrupts;
    #if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
        uint16 i;
    #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

    enableInterrupts = CyEnterCriticalSection();

    /* Enable USB block  */
    Launcher_UART_PM_ACT_CFG_REG |= Launcher_UART_PM_ACT_EN_FSUSB;
    /* Enable USB block for Standby Power Mode */
    Launcher_UART_PM_STBY_CFG_REG |= Launcher_UART_PM_STBY_EN_FSUSB;

    /* Enable core clock */
    Launcher_UART_USB_CLK_EN_REG = Launcher_UART_USB_CLK_ENABLE;

    Launcher_UART_CR1_REG = Launcher_UART_CR1_ENABLE_LOCK;

    /* ENABLING USBIO PADS IN USB MODE FROM I/O MODE */
    /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
    Launcher_UART_USBIO_CR0_REG &= ((uint8)(~Launcher_UART_USBIO_CR0_TEN));
    CyDelayUs(0u);  /*~50ns delay */
    /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted)
    *  high. This will have been set low by the power manger out of reset.
    *  Also confirm USBIO pull-up disabled
    */
    Launcher_UART_PM_USB_CR0_REG &= ((uint8)(~(Launcher_UART_PM_USB_CR0_PD_N |
                                                  Launcher_UART_PM_USB_CR0_PD_PULLUP_N)));

    /* Select iomode to USB mode*/
    Launcher_UART_USBIO_CR1_REG &= ((uint8)(~Launcher_UART_USBIO_CR1_IOMODE));

    /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
    Launcher_UART_PM_USB_CR0_REG |= Launcher_UART_PM_USB_CR0_REF_EN;
    /* The reference will be available 1 us after the regulator is enabled */
    CyDelayUs(1u);
    /* OR 40us after power restored */
    CyDelayUs(40u);
    /* Ensure the single ended disable bits are low (PRT15.INP_DIS[7:6])(input receiver enabled). */
    Launcher_UART_DM_INP_DIS_REG &= ((uint8)(~Launcher_UART_DM_MASK));
    Launcher_UART_DP_INP_DIS_REG &= ((uint8)(~Launcher_UART_DP_MASK));

    /* Enable USBIO */
    Launcher_UART_PM_USB_CR0_REG |= Launcher_UART_PM_USB_CR0_PD_N;
    CyDelayUs(2u);
    /* Set the USBIO pull-up enable */
    Launcher_UART_PM_USB_CR0_REG |= Launcher_UART_PM_USB_CR0_PD_PULLUP_N;

    /* Write WAx */
    CY_SET_REG8(Launcher_UART_ARB_RW1_WA_PTR,     0u);
    CY_SET_REG8(Launcher_UART_ARB_RW1_WA_MSB_PTR, 0u);

    #if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
        /* Init transfer descriptor. This will be used to detect the DMA state - initialized or not. */
        for (i = 0u; i < Launcher_UART_MAX_EP; i++)
        {
            Launcher_UART_DmaTd[i] = DMA_INVALID_TD;
        }
    #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

    CyExitCriticalSection(enableInterrupts);


    /* Set the bus reset Interrupt. */
    (void) CyIntSetVector(Launcher_UART_BUS_RESET_VECT_NUM,   &Launcher_UART_BUS_RESET_ISR);
    CyIntSetPriority(Launcher_UART_BUS_RESET_VECT_NUM, Launcher_UART_BUS_RESET_PRIOR);

    /* Set the SOF Interrupt. */
    #if(Launcher_UART_SOF_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_SOF_VECT_NUM,   &Launcher_UART_SOF_ISR);
        CyIntSetPriority(Launcher_UART_SOF_VECT_NUM, Launcher_UART_SOF_PRIOR);
    #endif   /* End Launcher_UART_SOF_ISR_REMOVE */

    /* Set the Control Endpoint Interrupt. */
    (void) CyIntSetVector(Launcher_UART_EP_0_VECT_NUM,   &Launcher_UART_EP_0_ISR);
    CyIntSetPriority(Launcher_UART_EP_0_VECT_NUM, Launcher_UART_EP_0_PRIOR);

    /* Set the Data Endpoint 1 Interrupt. */
    #if(Launcher_UART_EP1_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_1_VECT_NUM,   &Launcher_UART_EP_1_ISR);
        CyIntSetPriority(Launcher_UART_EP_1_VECT_NUM, Launcher_UART_EP_1_PRIOR);
    #endif   /* End Launcher_UART_EP1_ISR_REMOVE */

    /* Set the Data Endpoint 2 Interrupt. */
    #if(Launcher_UART_EP2_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_2_VECT_NUM,   &Launcher_UART_EP_2_ISR);
        CyIntSetPriority(Launcher_UART_EP_2_VECT_NUM, Launcher_UART_EP_2_PRIOR);
    #endif   /* End Launcher_UART_EP2_ISR_REMOVE */

    /* Set the Data Endpoint 3 Interrupt. */
    #if(Launcher_UART_EP3_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_3_VECT_NUM,   &Launcher_UART_EP_3_ISR);
        CyIntSetPriority(Launcher_UART_EP_3_VECT_NUM, Launcher_UART_EP_3_PRIOR);
    #endif   /* End Launcher_UART_EP3_ISR_REMOVE */

    /* Set the Data Endpoint 4 Interrupt. */
    #if(Launcher_UART_EP4_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_4_VECT_NUM,   &Launcher_UART_EP_4_ISR);
        CyIntSetPriority(Launcher_UART_EP_4_VECT_NUM, Launcher_UART_EP_4_PRIOR);
    #endif   /* End Launcher_UART_EP4_ISR_REMOVE */

    /* Set the Data Endpoint 5 Interrupt. */
    #if(Launcher_UART_EP5_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_5_VECT_NUM,   &Launcher_UART_EP_5_ISR);
        CyIntSetPriority(Launcher_UART_EP_5_VECT_NUM, Launcher_UART_EP_5_PRIOR);
    #endif   /* End Launcher_UART_EP5_ISR_REMOVE */

    /* Set the Data Endpoint 6 Interrupt. */
    #if(Launcher_UART_EP6_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_6_VECT_NUM,   &Launcher_UART_EP_6_ISR);
        CyIntSetPriority(Launcher_UART_EP_6_VECT_NUM, Launcher_UART_EP_6_PRIOR);
    #endif   /* End Launcher_UART_EP6_ISR_REMOVE */

     /* Set the Data Endpoint 7 Interrupt. */
    #if(Launcher_UART_EP7_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_7_VECT_NUM,   &Launcher_UART_EP_7_ISR);
        CyIntSetPriority(Launcher_UART_EP_7_VECT_NUM, Launcher_UART_EP_7_PRIOR);
    #endif   /* End Launcher_UART_EP7_ISR_REMOVE */

    /* Set the Data Endpoint 8 Interrupt. */
    #if(Launcher_UART_EP8_ISR_REMOVE == 0u)
        (void) CyIntSetVector(Launcher_UART_EP_8_VECT_NUM,   &Launcher_UART_EP_8_ISR);
        CyIntSetPriority(Launcher_UART_EP_8_VECT_NUM, Launcher_UART_EP_8_PRIOR);
    #endif   /* End Launcher_UART_EP8_ISR_REMOVE */

    #if((Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL) && (Launcher_UART_ARB_ISR_REMOVE == 0u))
        /* Set the ARB Interrupt. */
        (void) CyIntSetVector(Launcher_UART_ARB_VECT_NUM,   &Launcher_UART_ARB_ISR);
        CyIntSetPriority(Launcher_UART_ARB_VECT_NUM, Launcher_UART_ARB_PRIOR);
    #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

}


/*******************************************************************************
* Function Name: Launcher_UART_InitComponent
********************************************************************************
*
* Summary:
*  Initialize the component, except for the HW which is done one time in
*  the Start function.  This function pulls up D+.
*
* Parameters:
*  device: Contains the device number of the desired device descriptor.
*          The device number can be found in the Device Descriptor Tab of
*          "Configure" dialog, under the settings of desired Device Descriptor,
*          in the "Device Number" field.
*  mode: The operating voltage. This determines whether the voltage regulator
*        is enabled for 5V operation or if pass through mode is used for 3.3V
*        operation. Symbolic names and their associated values are given in the
*        following table.
*       Launcher_UART_3V_OPERATION - Disable voltage regulator and pass-thru
*                                       Vcc for pull-up
*       Launcher_UART_5V_OPERATION - Enable voltage regulator and use
*                                       regulator for pull-up
*       Launcher_UART_DWR_VDDD_OPERATION - Enable or Disable voltage
*                         regulator depend on Vddd Voltage configuration in DWR.
*
* Return:
*   None.
*
* Global variables:
*   Launcher_UART_device: Contains the device number of the desired device
*       descriptor. The device number can be found in the Device Descriptor Tab
*       of "Configure" dialog, under the settings of desired Device Descriptor,
*       in the "Device Number" field.
*   Launcher_UART_transferState: This variable used by the communication
*       functions to handle current transfer state. Initialized to
*       TRANS_STATE_IDLE in this API.
*   Launcher_UART_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   Launcher_UART_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   Launcher_UART_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   Launcher_UART_lastPacketSize initialized to 0;
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_InitComponent(uint8 device, uint8 mode) 
{
    /* Initialize _hidProtocol variable to comply with
    *  HID 7.2.6 Set_Protocol Request:
    *  "When initialized, all devices default to report protocol."
    */
    #if defined(Launcher_UART_ENABLE_HID_CLASS)
        uint8 i;

        for (i = 0u; i < Launcher_UART_MAX_INTERFACES_NUMBER; i++)
        {
            Launcher_UART_hidProtocol[i] = Launcher_UART_PROTOCOL_REPORT;
        }
    #endif /* Launcher_UART_ENABLE_HID_CLASS */

    /* Enable Interrupts. */
    CyIntEnable(Launcher_UART_BUS_RESET_VECT_NUM);
    CyIntEnable(Launcher_UART_EP_0_VECT_NUM);
    #if(Launcher_UART_EP1_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_1_VECT_NUM);
    #endif   /* End Launcher_UART_EP1_ISR_REMOVE */
    #if(Launcher_UART_EP2_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_2_VECT_NUM);
    #endif   /* End Launcher_UART_EP2_ISR_REMOVE */
    #if(Launcher_UART_EP3_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_3_VECT_NUM);
    #endif   /* End Launcher_UART_EP3_ISR_REMOVE */
    #if(Launcher_UART_EP4_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_4_VECT_NUM);
    #endif   /* End Launcher_UART_EP4_ISR_REMOVE */
    #if(Launcher_UART_EP5_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_5_VECT_NUM);
    #endif   /* End Launcher_UART_EP5_ISR_REMOVE */
    #if(Launcher_UART_EP6_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_6_VECT_NUM);
    #endif   /* End Launcher_UART_EP6_ISR_REMOVE */
    #if(Launcher_UART_EP7_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_7_VECT_NUM);
    #endif   /* End Launcher_UART_EP7_ISR_REMOVE */
    #if(Launcher_UART_EP8_ISR_REMOVE == 0u)
        CyIntEnable(Launcher_UART_EP_8_VECT_NUM);
    #endif   /* End Launcher_UART_EP8_ISR_REMOVE */
    #if((Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL) && (Launcher_UART_ARB_ISR_REMOVE == 0u))
        /* usb arb interrupt enable */
        Launcher_UART_ARB_INT_EN_REG = Launcher_UART_ARB_INT_MASK;
        CyIntEnable(Launcher_UART_ARB_VECT_NUM);
    #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

    /* Arbiter configuration for DMA transfers */
    #if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)

        #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL)
            Launcher_UART_ARB_CFG_REG = Launcher_UART_ARB_CFG_MANUAL_DMA;
        #endif   /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL */
        #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO)
            /*Set cfg cmplt this rises DMA request when the full configuration is done */
            Launcher_UART_ARB_CFG_REG = Launcher_UART_ARB_CFG_AUTO_DMA | Launcher_UART_ARB_CFG_AUTO_MEM;
        #endif   /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO */
    #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_IDLE;

    /* USB Locking: Enabled, VRegulator: depend on mode or DWR Voltage configuration*/
    switch(mode)
    {
        case Launcher_UART_3V_OPERATION:
            Launcher_UART_CR1_REG = Launcher_UART_CR1_ENABLE_LOCK;
            break;
        case Launcher_UART_5V_OPERATION:
            Launcher_UART_CR1_REG = Launcher_UART_CR1_ENABLE_LOCK | Launcher_UART_CR1_REG_ENABLE;
            break;
        default:   /*Launcher_UART_DWR_VDDD_OPERATION */
            #if(Launcher_UART_VDDD_MV < Launcher_UART_3500MV)
                Launcher_UART_CR1_REG = Launcher_UART_CR1_ENABLE_LOCK;
            #else
                Launcher_UART_CR1_REG = Launcher_UART_CR1_ENABLE_LOCK | Launcher_UART_CR1_REG_ENABLE;
            #endif /* End Launcher_UART_VDDD_MV < Launcher_UART_3500MV */
            break;
    }

    /* Record the descriptor selection */
    Launcher_UART_device = device;

    /* Clear all of the component data */
    Launcher_UART_configuration = 0u;
    Launcher_UART_interfaceNumber = 0u;
    Launcher_UART_configurationChanged = 0u;
    Launcher_UART_deviceAddress  = 0u;
    Launcher_UART_deviceStatus = 0u;

    Launcher_UART_lastPacketSize = 0u;

    /*  ACK Setup, Stall IN/OUT */
    CY_SET_REG8(Launcher_UART_EP0_CR_PTR, Launcher_UART_MODE_STALL_IN_OUT);

    /* Enable the SIE with an address 0 */
    CY_SET_REG8(Launcher_UART_CR0_PTR, Launcher_UART_CR0_ENABLE);

    /* Workaround for PSOC5LP */
    CyDelayCycles(1u);

    /* Finally, Enable d+ pullup and select iomode to USB mode*/
    CY_SET_REG8(Launcher_UART_USBIO_CR1_PTR, Launcher_UART_USBIO_CR1_USBPUEN);
}


/*******************************************************************************
* Function Name: Launcher_UART_ReInitComponent
********************************************************************************
*
* Summary:
*  This function reinitialize the component configuration and is
*  intend to be called from the Reset interrupt.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*   Launcher_UART_device: Contains the device number of the desired device
*        descriptor. The device number can be found in the Device Descriptor Tab
*       of "Configure" dialog, under the settings of desired Device Descriptor,
*       in the "Device Number" field.
*   Launcher_UART_transferState: This variable used by the communication
*       functions to handle current transfer state. Initialized to
*       TRANS_STATE_IDLE in this API.
*   Launcher_UART_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   Launcher_UART_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   Launcher_UART_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   Launcher_UART_lastPacketSize initialized to 0;
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_ReInitComponent(void) 
{
    /* Initialize _hidProtocol variable to comply with HID 7.2.6 Set_Protocol
    *  Request: "When initialized, all devices default to report protocol."
    */
    #if defined(Launcher_UART_ENABLE_HID_CLASS)
        uint8 i;

        for (i = 0u; i < Launcher_UART_MAX_INTERFACES_NUMBER; i++)
        {
            Launcher_UART_hidProtocol[i] = Launcher_UART_PROTOCOL_REPORT;
        }
    #endif /* Launcher_UART_ENABLE_HID_CLASS */

    Launcher_UART_transferState = Launcher_UART_TRANS_STATE_IDLE;

    /* Clear all of the component data */
    Launcher_UART_configuration = 0u;
    Launcher_UART_interfaceNumber = 0u;
    Launcher_UART_configurationChanged = 0u;
    Launcher_UART_deviceAddress  = 0u;
    Launcher_UART_deviceStatus = 0u;

    Launcher_UART_lastPacketSize = 0u;


    /*  ACK Setup, Stall IN/OUT */
    CY_SET_REG8(Launcher_UART_EP0_CR_PTR, Launcher_UART_MODE_STALL_IN_OUT);

    /* Enable the SIE with an address 0 */
    CY_SET_REG8(Launcher_UART_CR0_PTR, Launcher_UART_CR0_ENABLE);

}


/*******************************************************************************
* Function Name: Launcher_UART_Stop
********************************************************************************
*
* Summary:
*  This function shuts down the USB function including to release
*  the D+ Pullup and disabling the SIE.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*   Launcher_UART_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   Launcher_UART_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   Launcher_UART_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   Launcher_UART_configurationChanged: This variable is set to one after
*       SET_CONFIGURATION request and cleared in this function.
*   Launcher_UART_intiVar variable is set to zero
*
*******************************************************************************/
void Launcher_UART_Stop(void) 
{

    #if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)
        Launcher_UART_Stop_DMA(Launcher_UART_MAX_EP);     /* Stop all DMAs */
    #endif   /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */

    /* Disable the SIE */
    Launcher_UART_CR0_REG &= (uint8)(~Launcher_UART_CR0_ENABLE);
    /* Disable the d+ pullup */
    Launcher_UART_USBIO_CR1_REG &= (uint8)(~Launcher_UART_USBIO_CR1_USBPUEN);
    /* Disable USB in ACT PM */
    Launcher_UART_PM_ACT_CFG_REG &= (uint8)(~Launcher_UART_PM_ACT_EN_FSUSB);
    /* Disable USB block for Standby Power Mode */
    Launcher_UART_PM_STBY_CFG_REG &= (uint8)(~Launcher_UART_PM_STBY_EN_FSUSB);

    /* Disable the reset and EP interrupts */
    CyIntDisable(Launcher_UART_BUS_RESET_VECT_NUM);
    CyIntDisable(Launcher_UART_EP_0_VECT_NUM);
    #if(Launcher_UART_EP1_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_1_VECT_NUM);
    #endif   /* End Launcher_UART_EP1_ISR_REMOVE */
    #if(Launcher_UART_EP2_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_2_VECT_NUM);
    #endif   /* End Launcher_UART_EP2_ISR_REMOVE */
    #if(Launcher_UART_EP3_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_3_VECT_NUM);
    #endif   /* End Launcher_UART_EP3_ISR_REMOVE */
    #if(Launcher_UART_EP4_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_4_VECT_NUM);
    #endif   /* End Launcher_UART_EP4_ISR_REMOVE */
    #if(Launcher_UART_EP5_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_5_VECT_NUM);
    #endif   /* End Launcher_UART_EP5_ISR_REMOVE */
    #if(Launcher_UART_EP6_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_6_VECT_NUM);
    #endif   /* End Launcher_UART_EP6_ISR_REMOVE */
    #if(Launcher_UART_EP7_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_7_VECT_NUM);
    #endif   /* End Launcher_UART_EP7_ISR_REMOVE */
    #if(Launcher_UART_EP8_ISR_REMOVE == 0u)
        CyIntDisable(Launcher_UART_EP_8_VECT_NUM);
    #endif   /* End Launcher_UART_EP8_ISR_REMOVE */

    /* Clear all of the component data */
    Launcher_UART_configuration = 0u;
    Launcher_UART_interfaceNumber = 0u;
    Launcher_UART_configurationChanged = 0u;
    Launcher_UART_deviceAddress  = 0u;
    Launcher_UART_deviceStatus = 0u;
    Launcher_UART_initVar = 0u;

}


/*******************************************************************************
* Function Name: Launcher_UART_CheckActivity
********************************************************************************
*
* Summary:
*  Returns the activity status of the bus.  Clears the status hardware to
*  provide fresh activity status on the next call of this routine.
*
* Parameters:
*  None.
*
* Return:
*  1 - If bus activity was detected since the last call to this function
*  0 - If bus activity not was detected since the last call to this function
*
*******************************************************************************/
uint8 Launcher_UART_CheckActivity(void) 
{
    uint8 r;

    r = CY_GET_REG8(Launcher_UART_CR1_PTR);
    CY_SET_REG8(Launcher_UART_CR1_PTR, (r & ((uint8)(~Launcher_UART_CR1_BUS_ACTIVITY))));

    return((r & Launcher_UART_CR1_BUS_ACTIVITY) >> Launcher_UART_CR1_BUS_ACTIVITY_SHIFT);
}


/*******************************************************************************
* Function Name: Launcher_UART_GetConfiguration
********************************************************************************
*
* Summary:
*  Returns the current configuration setting
*
* Parameters:
*  None.
*
* Return:
*  configuration.
*
*******************************************************************************/
uint8 Launcher_UART_GetConfiguration(void) 
{
    return(Launcher_UART_configuration);
}


/*******************************************************************************
* Function Name: Launcher_UART_IsConfigurationChanged
********************************************************************************
*
* Summary:
*  Returns the clear on read configuration state. It is usefull when PC send
*  double SET_CONFIGURATION request with same configuration number.
*
* Parameters:
*  None.
*
* Return:
*  Not zero value when new configuration has been changed, otherwise zero is
*  returned.
*
* Global variables:
*   Launcher_UART_configurationChanged: This variable is set to one after
*       SET_CONFIGURATION request and cleared in this function.
*
*******************************************************************************/
uint8 Launcher_UART_IsConfigurationChanged(void) 
{
    uint8 res = 0u;

    if(Launcher_UART_configurationChanged != 0u)
    {
        res = Launcher_UART_configurationChanged;
        Launcher_UART_configurationChanged = 0u;
    }

    return(res);
}


/*******************************************************************************
* Function Name: Launcher_UART_GetInterfaceSetting
********************************************************************************
*
* Summary:
*  Returns the alternate setting from current interface
*
* Parameters:
*  uint8 interfaceNumber, interface number
*
* Return:
*  Alternate setting.
*
*******************************************************************************/
uint8  Launcher_UART_GetInterfaceSetting(uint8 interfaceNumber)
                                                    
{
    return(Launcher_UART_interfaceSetting[interfaceNumber]);
}


/*******************************************************************************
* Function Name: Launcher_UART_GetEPState
********************************************************************************
*
* Summary:
*  Returned the state of the requested endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*
* Return:
*  State of the requested endpoint.
*
*******************************************************************************/
uint8 Launcher_UART_GetEPState(uint8 epNumber) 
{
    return(Launcher_UART_EP[epNumber].apiEpState);
}


/*******************************************************************************
* Function Name: Launcher_UART_GetEPCount
********************************************************************************
*
* Summary:
*  This function supports Data Endpoints only(EP1-EP8).
*  Returns the transfer count for the requested endpoint.  The value from
*  the count registers includes 2 counts for the two byte checksum of the
*  packet.  This function subtracts the two counts.
*
* Parameters:
*  epNumber: Data Endpoint Number.
*            Valid values are between 1 and 8.
*
* Return:
*  Returns the current byte count from the specified endpoint or 0 for an
*  invalid endpoint.
*
*******************************************************************************/
uint16 Launcher_UART_GetEPCount(uint8 epNumber) 
{
    uint8 ri;
    uint16 result = 0u;

    if((epNumber > Launcher_UART_EP0) && (epNumber < Launcher_UART_MAX_EP))
    {
        ri = ((epNumber - Launcher_UART_EP1) << Launcher_UART_EPX_CNTX_ADDR_SHIFT);

        result = (uint8)(CY_GET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CNT0_IND + ri)) &
                          Launcher_UART_EPX_CNT0_MASK);
        result = (result << 8u) | CY_GET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CNT1_IND + ri));
        result -= Launcher_UART_EPX_CNTX_CRC_COUNT;
    }
    return(result);
}


#if(Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL)


    /*******************************************************************************
    * Function Name: Launcher_UART_InitEP_DMA
    ********************************************************************************
    *
    * Summary:
    *  This function allocates and initializes a DMA channel to be used by the
    *  Launcher_UART_LoadInEP() or Launcher_UART_ReadOutEP() APIs for data
    *  transfer.
    *
    * Parameters:
    *  epNumber: Contains the data endpoint number.
    *            Valid values are between 1 and 8.
    *  *pData: Pointer to a data array that is related to the EP transfers.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Launcher_UART_InitEP_DMA(uint8 epNumber, const uint8 *pData)
                                                                    
    {
        uint16 src;
        uint16 dst;
        #if (CY_PSOC3)                  /* PSoC 3 */
            src = HI16(CYDEV_SRAM_BASE);
            dst = HI16(CYDEV_PERIPH_BASE);
            pData = pData;
        #else                           /* PSoC 5 */
            if((Launcher_UART_EP[epNumber].addr & Launcher_UART_DIR_IN) != 0u )
            {   /* for the IN EP source is the SRAM memory buffer */
                src = HI16(pData);
                dst = HI16(CYDEV_PERIPH_BASE);
            }
            else
            {   /* for the OUT EP source is the SIE register */
                src = HI16(CYDEV_PERIPH_BASE);
                dst = HI16(pData);
            }
        #endif  /* End C51 */
        switch(epNumber)
        {
            case Launcher_UART_EP1:
                #if(Launcher_UART_DMA1_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep1_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA1_REMOVE */
                break;
            case Launcher_UART_EP2:
                #if(Launcher_UART_DMA2_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep2_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA2_REMOVE */
                break;
            case Launcher_UART_EP3:
                #if(Launcher_UART_DMA3_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep3_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA3_REMOVE */
                break;
            case Launcher_UART_EP4:
                #if(Launcher_UART_DMA4_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep4_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA4_REMOVE */
                break;
            case Launcher_UART_EP5:
                #if(Launcher_UART_DMA5_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep5_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA5_REMOVE */
                break;
            case Launcher_UART_EP6:
                #if(Launcher_UART_DMA6_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep6_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA6_REMOVE */
                break;
            case Launcher_UART_EP7:
                #if(Launcher_UART_DMA7_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep7_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA7_REMOVE */
                break;
            case Launcher_UART_EP8:
                #if(Launcher_UART_DMA8_REMOVE == 0u)
                    Launcher_UART_DmaChan[epNumber] = Launcher_UART_ep8_DmaInitialize(
                        Launcher_UART_DMA_BYTES_PER_BURST, Launcher_UART_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End Launcher_UART_DMA8_REMOVE */
                break;
            default:
                /* Do not support EP0 DMA transfers */
                break;
        }
        if((epNumber > Launcher_UART_EP0) && (epNumber < Launcher_UART_MAX_EP))
        {
            Launcher_UART_DmaTd[epNumber] = CyDmaTdAllocate();
        }
    }


    /*******************************************************************************
    * Function Name: Launcher_UART_Stop_DMA
    ********************************************************************************
    *
    * Summary: Stops and free DMA
    *
    * Parameters:
    *  epNumber: Contains the data endpoint number or
    *           Launcher_UART_MAX_EP to stop all DMAs
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Launcher_UART_Stop_DMA(uint8 epNumber) 
    {
        uint8 i;
        i = (epNumber < Launcher_UART_MAX_EP) ? epNumber : Launcher_UART_EP1;
        do
        {
            if(Launcher_UART_DmaTd[i] != DMA_INVALID_TD)
            {
                (void) CyDmaChDisable(Launcher_UART_DmaChan[i]);
                CyDmaTdFree(Launcher_UART_DmaTd[i]);
                Launcher_UART_DmaTd[i] = DMA_INVALID_TD;
            }
            i++;
        }while((i < Launcher_UART_MAX_EP) && (epNumber == Launcher_UART_MAX_EP));
    }

#endif /* End Launcher_UART_EP_MM != Launcher_UART__EP_MANUAL */


/*******************************************************************************
* Function Name: Launcher_UART_LoadInEP
********************************************************************************
*
* Summary:
*  Loads and enables the specified USB data endpoint for an IN interrupt or bulk
*  transfer.
*
* Parameters:
*  epNumber: Contains the data endpoint number.
*            Valid values are between 1 and 8.
*  *pData: A pointer to a data array from which the data for the endpoint space
*          is loaded.
*  length: The number of bytes to transfer from the array and then send as a
*          result of an IN request. Valid values are between 0 and 512.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_LoadInEP(uint8 epNumber, const uint8 pData[], uint16 length)
                                                                        
{
    uint8 ri;
    reg8 *p;
    #if(Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL)
        uint16 i;
    #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL */

    if((epNumber > Launcher_UART_EP0) && (epNumber < Launcher_UART_MAX_EP))
    {
        ri = ((epNumber - Launcher_UART_EP1) << Launcher_UART_EPX_CNTX_ADDR_SHIFT);
        p = (reg8 *)(Launcher_UART_ARB_RW1_DR_IND + ri);

        #if(Launcher_UART_EP_MM != Launcher_UART__EP_DMAAUTO)
            /* Limits length to available buffer space, auto MM could send packets up to 1024 bytes */
            if(length > (Launcher_UART_EPX_DATA_BUF_MAX - Launcher_UART_EP[epNumber].buffOffset))
            {
                length = Launcher_UART_EPX_DATA_BUF_MAX - Launcher_UART_EP[epNumber].buffOffset;
            }
        #endif /* End Launcher_UART_EP_MM != Launcher_UART__EP_DMAAUTO */

        /* Set the count and data toggle */
        CY_SET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CNT0_IND + ri),
                            (length >> 8u) | (Launcher_UART_EP[epNumber].epToggle));
        CY_SET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CNT1_IND + ri),  length & 0xFFu);

        #if(Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL)
            if(pData != NULL)
            {
                /* Copy the data using the arbiter data register */
                for (i = 0u; i < length; i++)
                {
                    CY_SET_REG8(p, pData[i]);
                }
            }
            Launcher_UART_EP[epNumber].apiEpState = Launcher_UART_NO_EVENT_PENDING;
            /* Write the Mode register */
            CY_SET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CR0_IND + ri), Launcher_UART_EP[epNumber].epMode);
        #else
            /* Init DMA if it was not initialized */
            if(Launcher_UART_DmaTd[epNumber] == DMA_INVALID_TD)
            {
                Launcher_UART_InitEP_DMA(epNumber, pData);
            }
        #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL */

        #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL)
            Launcher_UART_EP[epNumber].apiEpState = Launcher_UART_NO_EVENT_PENDING;
            if((pData != NULL) && (length > 0u))
            {
                /* Enable DMA in mode2 for transferring data */
                (void) CyDmaChDisable(Launcher_UART_DmaChan[epNumber]);
                (void) CyDmaTdSetConfiguration(Launcher_UART_DmaTd[epNumber], length, CY_DMA_DISABLE_TD,
                                                                                 TD_TERMIN_EN | TD_INC_SRC_ADR);
                (void) CyDmaTdSetAddress(Launcher_UART_DmaTd[epNumber],  LO16((uint32)pData), LO16((uint32)p));
                /* Enable the DMA */
                (void) CyDmaChSetInitialTd(Launcher_UART_DmaChan[epNumber], Launcher_UART_DmaTd[epNumber]);
                (void) CyDmaChEnable(Launcher_UART_DmaChan[epNumber], 1u);
                /* Generate DMA request */
                * (reg8 *)(Launcher_UART_ARB_EP1_CFG_IND + ri) |= Launcher_UART_ARB_EPX_CFG_DMA_REQ;
                * (reg8 *)(Launcher_UART_ARB_EP1_CFG_IND + ri) &= ((uint8)(~Launcher_UART_ARB_EPX_CFG_DMA_REQ));
                /* Mode register will be written in arb ISR after DMA transfer complete */
            }
            else
            {
                /* When zero-length packet - write the Mode register directly */
                CY_SET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CR0_IND + ri), Launcher_UART_EP[epNumber].epMode);
            }
        #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL */

        #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO)
            if(pData != NULL)
            {
                /* Enable DMA in mode3 for transferring data */
                (void) CyDmaChDisable(Launcher_UART_DmaChan[epNumber]);
                (void) CyDmaTdSetConfiguration(Launcher_UART_DmaTd[epNumber], length,
                                               Launcher_UART_DmaTd[epNumber], TD_TERMIN_EN | TD_INC_SRC_ADR);
                (void) CyDmaTdSetAddress(Launcher_UART_DmaTd[epNumber],  LO16((uint32)pData), LO16((uint32)p));
                /* Clear Any potential pending DMA requests before starting the DMA channel to transfer data */
                (void) CyDmaClearPendingDrq(Launcher_UART_DmaChan[epNumber]);
                /* Enable the DMA */
                (void) CyDmaChSetInitialTd(Launcher_UART_DmaChan[epNumber], Launcher_UART_DmaTd[epNumber]);
                (void) CyDmaChEnable(Launcher_UART_DmaChan[epNumber], 1u);
            }
            else
            {
                Launcher_UART_EP[epNumber].apiEpState = Launcher_UART_NO_EVENT_PENDING;
                if(length > 0u)
                {
                    /* Set Data ready status, This will generate DMA request */
                    * (reg8 *)(Launcher_UART_ARB_EP1_CFG_IND + ri) |= Launcher_UART_ARB_EPX_CFG_IN_DATA_RDY;
                    /* Mode register will be written in arb ISR(In Buffer Full) after first DMA transfer complete */
                }
                else
                {
                    /* When zero-length packet - write the Mode register directly */
                    CY_SET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CR0_IND + ri), Launcher_UART_EP[epNumber].epMode);
                }
            }
        #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO */

    }
}


/*******************************************************************************
* Function Name: Launcher_UART_ReadOutEP
********************************************************************************
*
* Summary:
*  Read data from an endpoint.  The application must call
*  Launcher_UART_GetEPState to see if an event is pending.
*
* Parameters:
*  epNumber: Contains the data endpoint number.
*            Valid values are between 1 and 8.
*  pData: A pointer to a data array from which the data for the endpoint space
*         is loaded.
*  length: The number of bytes to transfer from the USB Out endpoint and loads
*          it into data array. Valid values are between 0 and 1023. The function
*          moves fewer than the requested number of bytes if the host sends
*          fewer bytes than requested.
*
* Returns:
*  Number of bytes received, 0 for an invalid endpoint.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 Launcher_UART_ReadOutEP(uint8 epNumber, uint8 pData[], uint16 length)
                                                                        
{
    uint8 ri;
    reg8 *p;
    #if(Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL)
        uint16 i;
    #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL */
    #if(Launcher_UART_EP_MM != Launcher_UART__EP_DMAAUTO)
        uint16 xferCount;
    #endif /* End Launcher_UART_EP_MM != Launcher_UART__EP_DMAAUTO */

    if((epNumber > Launcher_UART_EP0) && (epNumber < Launcher_UART_MAX_EP) && (pData != NULL))
    {
        ri = ((epNumber - Launcher_UART_EP1) << Launcher_UART_EPX_CNTX_ADDR_SHIFT);
        p = (reg8 *)(Launcher_UART_ARB_RW1_DR_IND + ri);

        #if(Launcher_UART_EP_MM != Launcher_UART__EP_DMAAUTO)
            /* Determine which is smaller the requested data or the available data */
            xferCount = Launcher_UART_GetEPCount(epNumber);
            if (length > xferCount)
            {
                length = xferCount;
            }
        #endif /* End Launcher_UART_EP_MM != Launcher_UART__EP_DMAAUTO */

        #if(Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL)
            /* Copy the data using the arbiter data register */
            for (i = 0u; i < length; i++)
            {
                pData[i] = CY_GET_REG8(p);
            }

            /* (re)arming of OUT endpoint */
            Launcher_UART_EnableOutEP(epNumber);
        #else
            /*Init DMA if it was not initialized */
            if(Launcher_UART_DmaTd[epNumber] == DMA_INVALID_TD)
            {
                Launcher_UART_InitEP_DMA(epNumber, pData);
            }
        #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_MANUAL */

        #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL)
            /* Enable DMA in mode2 for transferring data */
            (void) CyDmaChDisable(Launcher_UART_DmaChan[epNumber]);
            (void) CyDmaTdSetConfiguration(Launcher_UART_DmaTd[epNumber], length, CY_DMA_DISABLE_TD,
                                                                                TD_TERMIN_EN | TD_INC_DST_ADR);
            (void) CyDmaTdSetAddress(Launcher_UART_DmaTd[epNumber],  LO16((uint32)p), LO16((uint32)pData));
            /* Enable the DMA */
            (void) CyDmaChSetInitialTd(Launcher_UART_DmaChan[epNumber], Launcher_UART_DmaTd[epNumber]);
            (void) CyDmaChEnable(Launcher_UART_DmaChan[epNumber], 1u);

            /* Generate DMA request */
            * (reg8 *)(Launcher_UART_ARB_EP1_CFG_IND + ri) |= Launcher_UART_ARB_EPX_CFG_DMA_REQ;
            * (reg8 *)(Launcher_UART_ARB_EP1_CFG_IND + ri) &= ((uint8)(~Launcher_UART_ARB_EPX_CFG_DMA_REQ));
            /* Out EP will be (re)armed in arb ISR after transfer complete */
        #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAMANUAL */

        #if(Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO)
            /* Enable DMA in mode3 for transferring data */
            (void) CyDmaChDisable(Launcher_UART_DmaChan[epNumber]);
            (void) CyDmaTdSetConfiguration(Launcher_UART_DmaTd[epNumber], length, Launcher_UART_DmaTd[epNumber],
                                                                                TD_TERMIN_EN | TD_INC_DST_ADR);
            (void) CyDmaTdSetAddress(Launcher_UART_DmaTd[epNumber],  LO16((uint32)p), LO16((uint32)pData));

            /* Clear Any potential pending DMA requests before starting the DMA channel to transfer data */
            (void) CyDmaClearPendingDrq(Launcher_UART_DmaChan[epNumber]);
            /* Enable the DMA */
            (void) CyDmaChSetInitialTd(Launcher_UART_DmaChan[epNumber], Launcher_UART_DmaTd[epNumber]);
            (void) CyDmaChEnable(Launcher_UART_DmaChan[epNumber], 1u);
            /* Out EP will be (re)armed in arb ISR after transfer complete */
        #endif /* End Launcher_UART_EP_MM == Launcher_UART__EP_DMAAUTO */

    }
    else
    {
        length = 0u;
    }

    return(length);
}


/*******************************************************************************
* Function Name: Launcher_UART_EnableOutEP
********************************************************************************
*
* Summary:
*  This function enables an OUT endpoint.  It should not be
*  called for an IN endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Return:
*   None.
*
* Global variables:
*  Launcher_UART_EP[epNumber].apiEpState - set to NO_EVENT_PENDING
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_EnableOutEP(uint8 epNumber) 
{
    uint8 ri;

    if((epNumber > Launcher_UART_EP0) && (epNumber < Launcher_UART_MAX_EP))
    {
        ri = ((epNumber - Launcher_UART_EP1) << Launcher_UART_EPX_CNTX_ADDR_SHIFT);
        Launcher_UART_EP[epNumber].apiEpState = Launcher_UART_NO_EVENT_PENDING;
        /* Write the Mode register */
        CY_SET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CR0_IND + ri), Launcher_UART_EP[epNumber].epMode);
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_DisableOutEP
********************************************************************************
*
* Summary:
*  This function disables an OUT endpoint.  It should not be
*  called for an IN endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Return:
*  None.
*
*******************************************************************************/
void Launcher_UART_DisableOutEP(uint8 epNumber) 
{
    uint8 ri ;

    if((epNumber > Launcher_UART_EP0) && (epNumber < Launcher_UART_MAX_EP))
    {
        ri = ((epNumber - Launcher_UART_EP1) << Launcher_UART_EPX_CNTX_ADDR_SHIFT);
        /* Write the Mode register */
        CY_SET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CR0_IND + ri), Launcher_UART_MODE_NAK_OUT);
    }
}


/*******************************************************************************
* Function Name: Launcher_UART_Force
********************************************************************************
*
* Summary:
*  Forces the bus state
*
* Parameters:
*  bState
*    Launcher_UART_FORCE_J
*    Launcher_UART_FORCE_K
*    Launcher_UART_FORCE_SE0
*    Launcher_UART_FORCE_NONE
*
* Return:
*  None.
*
*******************************************************************************/
void Launcher_UART_Force(uint8 bState) 
{
    CY_SET_REG8(Launcher_UART_USBIO_CR0_PTR, bState);
}


/*******************************************************************************
* Function Name: Launcher_UART_GetEPAckState
********************************************************************************
*
* Summary:
*  Returns the ACK of the CR0 Register (ACKD)
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Returns
*  0 if nothing has been ACKD, non-=zero something has been ACKD
*
*******************************************************************************/
uint8 Launcher_UART_GetEPAckState(uint8 epNumber) 
{
    uint8 ri;
    uint8 cr = 0u;

    if((epNumber > Launcher_UART_EP0) && (epNumber < Launcher_UART_MAX_EP))
    {
        ri = ((epNumber - Launcher_UART_EP1) << Launcher_UART_EPX_CNTX_ADDR_SHIFT);
        cr = CY_GET_REG8((reg8 *)(Launcher_UART_SIE_EP1_CR0_IND + ri)) & Launcher_UART_MODE_ACKD;
    }

    return(cr);
}


/*******************************************************************************
* Function Name: Launcher_UART_SetPowerStatus
********************************************************************************
*
* Summary:
*  Sets the device power status for reporting in the Get Device Status
*  request
*
* Parameters:
*  powerStatus: Launcher_UART_DEVICE_STATUS_BUS_POWERED(0) - Bus Powered,
*               Launcher_UART_DEVICE_STATUS_SELF_POWERED(1) - Self Powered
*
* Return:
*   None.
*
* Global variables:
*  Launcher_UART_deviceStatus - set power status
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Launcher_UART_SetPowerStatus(uint8 powerStatus) 
{
    if (powerStatus != Launcher_UART_DEVICE_STATUS_BUS_POWERED)
    {
        Launcher_UART_deviceStatus |=  Launcher_UART_DEVICE_STATUS_SELF_POWERED;
    }
    else
    {
        Launcher_UART_deviceStatus &=  ((uint8)(~Launcher_UART_DEVICE_STATUS_SELF_POWERED));
    }
}


#if (Launcher_UART_MON_VBUS == 1u)

    /*******************************************************************************
    * Function Name: Launcher_UART_VBusPresent
    ********************************************************************************
    *
    * Summary:
    *  Determines VBUS presence for Self Powered Devices.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  1 if VBUS is present, otherwise 0.
    *
    *******************************************************************************/
    uint8 Launcher_UART_VBusPresent(void) 
    {
        return((0u != (CY_GET_REG8(Launcher_UART_VBUS_PS_PTR) & Launcher_UART_VBUS_MASK)) ? 1u : 0u);
    }

#endif /* Launcher_UART_MON_VBUS */


/*******************************************************************************
* Function Name: Launcher_UART_RWUEnabled
********************************************************************************
*
* Summary:
*  Returns TRUE if Remote Wake Up is enabled, otherwise FALSE
*
* Parameters:
*   None.
*
* Return:
*  TRUE -  Remote Wake Up Enabled
*  FALSE - Remote Wake Up Disabled
*
* Global variables:
*  Launcher_UART_deviceStatus - checked to determine remote status
*
*******************************************************************************/
uint8 Launcher_UART_RWUEnabled(void) 
{
    uint8 result = Launcher_UART_FALSE;
    if((Launcher_UART_deviceStatus & Launcher_UART_DEVICE_STATUS_REMOTE_WAKEUP) != 0u)
    {
        result = Launcher_UART_TRUE;
    }

    return(result);
}


/* [] END OF FILE */
