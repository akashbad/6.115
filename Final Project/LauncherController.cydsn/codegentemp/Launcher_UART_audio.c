/*******************************************************************************
* File Name: Launcher_UART_audio.c
* Version 2.60
*
* Description:
*  USB AUDIO Class request handler.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Launcher_UART.h"

#if defined(Launcher_UART_ENABLE_AUDIO_CLASS)

#include "Launcher_UART_audio.h"
#include "Launcher_UART_pvt.h"
#if defined(Launcher_UART_ENABLE_MIDI_STREAMING) 
    #include "Launcher_UART_midi.h"
#endif /* End Launcher_UART_ENABLE_MIDI_STREAMING*/


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)


/***************************************
*    AUDIO Variables
***************************************/

#if defined(Launcher_UART_ENABLE_AUDIO_STREAMING)
    volatile uint8 Launcher_UART_currentSampleFrequency[Launcher_UART_MAX_EP][Launcher_UART_SAMPLE_FREQ_LEN];
    volatile uint8 Launcher_UART_frequencyChanged;
    volatile uint8 Launcher_UART_currentMute;
    volatile uint8 Launcher_UART_currentVolume[Launcher_UART_VOLUME_LEN];
    volatile uint8 Launcher_UART_minimumVolume[Launcher_UART_VOLUME_LEN] = {Launcher_UART_VOL_MIN_LSB,
                                                                                  Launcher_UART_VOL_MIN_MSB};
    volatile uint8 Launcher_UART_maximumVolume[Launcher_UART_VOLUME_LEN] = {Launcher_UART_VOL_MAX_LSB,
                                                                                  Launcher_UART_VOL_MAX_MSB};
    volatile uint8 Launcher_UART_resolutionVolume[Launcher_UART_VOLUME_LEN] = {Launcher_UART_VOL_RES_LSB,
                                                                                     Launcher_UART_VOL_RES_MSB};
#endif /* End Launcher_UART_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: Launcher_UART_DispatchAUDIOClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches class requests
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   Launcher_UART_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   Launcher_UART_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       if((Launcher_UART_frequencyChanged != 0) &&
*       (Launcher_UART_transferState == Launcher_UART_TRANS_STATE_IDLE))
*       {
*          Launcher_UART_frequencyChanged = 0;
*       }
*       Launcher_UART_transferState variable is checked to be sure that
*             transfer completes.
*   Launcher_UART_currentMute: Contains mute configuration set by Host.
*   Launcher_UART_currentVolume: Contains volume level set by Host.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Launcher_UART_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = Launcher_UART_FALSE;

    #if defined(Launcher_UART_ENABLE_AUDIO_STREAMING)
        uint8 epNumber;
        epNumber = CY_GET_REG8(Launcher_UART_wIndexLo) & Launcher_UART_DIR_UNUSED;
    #endif /* End Launcher_UART_ENABLE_AUDIO_STREAMING */

    if ((CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_DIR_MASK) == Launcher_UART_RQST_DIR_D2H)
    {
        /* Control Read */
        if((CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_RCPT_MASK) == \
                                                                                    Launcher_UART_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(Launcher_UART_bRequest))
            {
                case Launcher_UART_GET_CUR:
                #if defined(Launcher_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* Endpoint Control Selector is Sampling Frequency */
                        Launcher_UART_currentTD.wCount = Launcher_UART_SAMPLE_FREQ_LEN;
                        Launcher_UART_currentTD.pData  = Launcher_UART_currentSampleFrequency[epNumber];
                        requestHandled   = Launcher_UART_InitControlRead();
                    }
                #endif /* End Launcher_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_RCPT_MASK) == \
                                                                                    Launcher_UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(Launcher_UART_bRequest))
            {
                case Launcher_UART_GET_CUR:
                #if defined(Launcher_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */
                        
                         /* Entity ID Control Selector is MUTE */
                        Launcher_UART_currentTD.wCount = 1u;
                        Launcher_UART_currentTD.pData  = &Launcher_UART_currentMute;
                        requestHandled   = Launcher_UART_InitControlRead();
                    }
                    else if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME, */
                        Launcher_UART_currentTD.wCount = Launcher_UART_VOLUME_LEN;
                        Launcher_UART_currentTD.pData  = Launcher_UART_currentVolume;
                        requestHandled   = Launcher_UART_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                    break;
                case Launcher_UART_GET_MIN:    /* GET_MIN */
                    if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        Launcher_UART_currentTD.wCount = Launcher_UART_VOLUME_LEN;
                        Launcher_UART_currentTD.pData  = &Launcher_UART_minimumVolume[0];
                        requestHandled   = Launcher_UART_InitControlRead();
                    }
                    break;
                case Launcher_UART_GET_MAX:    /* GET_MAX */
                    if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        Launcher_UART_currentTD.wCount = Launcher_UART_VOLUME_LEN;
                        Launcher_UART_currentTD.pData  = &Launcher_UART_maximumVolume[0];
                        requestHandled   = Launcher_UART_InitControlRead();
                    }
                    break;
                case Launcher_UART_GET_RES:    /* GET_RES */
                    if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        Launcher_UART_currentTD.wCount = Launcher_UART_VOLUME_LEN;
                        Launcher_UART_currentTD.pData  = &Launcher_UART_resolutionVolume[0];
                        requestHandled   = Launcher_UART_InitControlRead();
                    }
                    break;
                /* The contents of the status message is reserved for future use.
                *  For the time being, a null packet should be returned in the data stage of the
                *  control transfer, and the received null packet should be ACKed.
                */
                case Launcher_UART_GET_STAT:
                        Launcher_UART_currentTD.wCount = 0u;
                        requestHandled   = Launcher_UART_InitControlWrite();

                #endif /* End Launcher_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {   /* Launcher_UART_RQST_RCPT_OTHER */
        }
    }
    else if ((CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_DIR_MASK) == \
                                                                                    Launcher_UART_RQST_DIR_H2D)
    {
        /* Control Write */
        if((CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_RCPT_MASK) == \
                                                                                    Launcher_UART_RQST_RCPT_EP)
        {
            /* Endpoint */
            switch (CY_GET_REG8(Launcher_UART_bRequest))
            {
                case Launcher_UART_SET_CUR:
                #if defined(Launcher_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_SAMPLING_FREQ_CONTROL)
                    {
                         /* Endpoint Control Selector is Sampling Frequency */
                        Launcher_UART_currentTD.wCount = Launcher_UART_SAMPLE_FREQ_LEN;
                        Launcher_UART_currentTD.pData  = Launcher_UART_currentSampleFrequency[epNumber];
                        requestHandled   = Launcher_UART_InitControlWrite();
                        Launcher_UART_frequencyChanged = epNumber;
                    }
                #endif /* End Launcher_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else if((CY_GET_REG8(Launcher_UART_bmRequestType) & Launcher_UART_RQST_RCPT_MASK) == \
                                                                                    Launcher_UART_RQST_RCPT_IFC)
        {
            /* Interface or Entity ID */
            switch (CY_GET_REG8(Launcher_UART_bRequest))
            {
                case Launcher_UART_SET_CUR:
                #if defined(Launcher_UART_ENABLE_AUDIO_STREAMING)
                    if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is MUTE */
                        Launcher_UART_currentTD.wCount = 1u;
                        Launcher_UART_currentTD.pData  = &Launcher_UART_currentMute;
                        requestHandled   = Launcher_UART_InitControlWrite();
                    }
                    else if(CY_GET_REG8(Launcher_UART_wValueHi) == Launcher_UART_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                        /* Entity ID Control Selector is VOLUME */
                        Launcher_UART_currentTD.wCount = Launcher_UART_VOLUME_LEN;
                        Launcher_UART_currentTD.pData  = Launcher_UART_currentVolume;
                        requestHandled   = Launcher_UART_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */
                    }
                #endif /* End Launcher_UART_ENABLE_AUDIO_STREAMING */

                /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                /* `#END` */
                    break;
                default:
                    break;
            }
        }
        else
        {   /* Launcher_UART_RQST_RCPT_OTHER */
        }
    }
    else
    {   /* requestHandled is initialized as FALSE by default */
    }

    return(requestHandled);
}


#endif /* USER_SUPPLIED_AUDIO_HANDLER */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* End Launcher_UART_ENABLE_AUDIO_CLASS*/


/* [] END OF FILE */
