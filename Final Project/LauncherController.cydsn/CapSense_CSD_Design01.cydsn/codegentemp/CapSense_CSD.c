/*******************************************************************************
* File Name: CapSense_CSD.c
* Version 3.40
*
* Description:
*  This file provides the source code of scanning APIs for the CapSense CSD 
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_CSD.h"


static uint8 CapSense_CSD_initVar = 0u;
            
/* Global software variables */
volatile uint8 CapSense_CSD_csv;            /* CapSense CSD status, control variable */
volatile uint8 CapSense_CSD_sensorIndex;    /* Index of scannig sensor */

/* AutoTunning start */
#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)
    uint8 CapSense_CSD_lowLevelTuningDone = 1u;
#endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) */

#if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB)
    uint8  CapSense_CSD_extRbCh0Cur = CapSense_CSD_RBLEED1;
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
        uint8  CapSense_CSD_extRbCh1Cur = (CapSense_CSD_RBLEED1 + CapSense_CSD_TOTAL_RB_NUMBER__CH0);
    #endif /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)*/ 
#endif /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB) */ 
        
/* Global array of Raw Counts */
uint16 CapSense_CSD_sensorRaw[CapSense_CSD_TOTAL_SENSOR_COUNT]; 

uint8 CapSense_CSD_sensorEnableMask[(((CapSense_CSD_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)] = {
0x7Fu, };

uint8 CYXDATA * const CYCODE CapSense_CSD_pcTable[] = {
    (uint8 CYXDATA *)CapSense_CSD_PortCH0__Button0__BTN__PC, 
    (uint8 CYXDATA *)CapSense_CSD_PortCH0__Button1__BTN__PC, 
    (uint8 CYXDATA *)CapSense_CSD_PortCH0__LinearSlider0_e0__LS__PC, 
    (uint8 CYXDATA *)CapSense_CSD_PortCH0__LinearSlider0_e1__LS__PC, 
    (uint8 CYXDATA *)CapSense_CSD_PortCH0__LinearSlider0_e2__LS__PC, 
    (uint8 CYXDATA *)CapSense_CSD_PortCH0__LinearSlider0_e3__LS__PC, 
    (uint8 CYXDATA *)CapSense_CSD_PortCH0__LinearSlider0_e4__LS__PC, 
};

const uint8 CYCODE CapSense_CSD_portTable[] = {
    CapSense_CSD_PortCH0__Button0__BTN__PORT, 
    CapSense_CSD_PortCH0__Button1__BTN__PORT, 
    CapSense_CSD_PortCH0__LinearSlider0_e0__LS__PORT, 
    CapSense_CSD_PortCH0__LinearSlider0_e1__LS__PORT, 
    CapSense_CSD_PortCH0__LinearSlider0_e2__LS__PORT, 
    CapSense_CSD_PortCH0__LinearSlider0_e3__LS__PORT, 
    CapSense_CSD_PortCH0__LinearSlider0_e4__LS__PORT, 
};

const uint8 CYCODE CapSense_CSD_maskTable[] = {
    CapSense_CSD_PortCH0__Button0__BTN__MASK,
    CapSense_CSD_PortCH0__Button1__BTN__MASK,
    CapSense_CSD_PortCH0__LinearSlider0_e0__LS__MASK,
    CapSense_CSD_PortCH0__LinearSlider0_e1__LS__MASK,
    CapSense_CSD_PortCH0__LinearSlider0_e2__LS__MASK,
    CapSense_CSD_PortCH0__LinearSlider0_e3__LS__MASK,
    CapSense_CSD_PortCH0__LinearSlider0_e4__LS__MASK,
};

uint8 CYXDATA * const CYCODE CapSense_CSD_csTable[] = {
    (uint8 CYXDATA *)CYREG_PRT0_CAPS_SEL, (uint8 CYXDATA *)CYREG_PRT1_CAPS_SEL, (uint8 CYXDATA *)CYREG_PRT2_CAPS_SEL,
    (uint8 CYXDATA *)CYREG_PRT3_CAPS_SEL, (uint8 CYXDATA *)CYREG_PRT4_CAPS_SEL, (uint8 CYXDATA *)CYREG_PRT5_CAPS_SEL,
    (uint8 CYXDATA *)CYREG_PRT6_CAPS_SEL, (uint8 CYXDATA *)CYREG_PRT15_CAPS_SEL,
};

const uint8 CYCODE CapSense_CSD_idacSettings[] = {
    43u,41u,48u,49u,41u,38u,34u,
};

const uint8 CYCODE CapSense_CSD_widgetResolution[] = {
    CapSense_CSD_PWM_RESOLUTION_14_BITS,
    CapSense_CSD_PWM_RESOLUTION_14_BITS,
    CapSense_CSD_PWM_RESOLUTION_13_BITS,
};

uint8 CapSense_CSD_analogSwitchDivider[CapSense_CSD_TOTAL_SCANSLOT_COUNT] = {
    2u, 2u, 3u, 3u, 3u, 3u, 3u, 
};

const uint8 CYCODE CapSense_CSD_widgetNumber[] = {
    1u, /* Button0__BTN */
    2u, /* Button1__BTN */
    0u, 0u, 0u, 0u, 0u, /* LinearSlider0__LS */
    
};




/*******************************************************************************
* Function Name: CapSense_CSD_Init
********************************************************************************
*
* Summary:
*  Inits default CapSense configuration provided with customizer that defines 
*  mode of component operations and resets all sensors to an inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_Init(void) 
{
    #if ( (CapSense_CSD_PRS_OPTIONS) || \
          (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_UDB) || \
          ( (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) && \
            (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_UDB)) )
        
        uint8 enableInterrupts;
    #endif /* ( (CapSense_CSD_PRS_OPTIONS) || \
           * (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_UDB) || \
           * ( (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) && \
           * (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_UDB)) ) 
           */
    
    /* Clear all sensors */
    CapSense_CSD_ClearSensors();

    /* Set Prescaler */
    #if (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB)
        /* Do nothing = config without prescaler */
    #elif (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_FF)
        CapSense_CSD_PRESCALER_CONTROL_REG   = (CapSense_CSD_PRESCALER_CTRL_ENABLE |
                                                    CapSense_CSD_PRESCALER_CTRL_MODE_CMP);
                                               
        CapSense_CSD_PRESCALER_CONTROL2_REG |= CapSense_CSD_PRESCALER_CTRL_CMP_LESS_EQ;
    #else
        /* Do nothing = config without prescaler */
    #endif  /* (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB) */

    /* Set PRS */
    #if (CapSense_CSD_PRS_OPTIONS)
        CapSense_CSD_SetAnalogSwitchesSource(CapSense_CSD_ANALOG_SWITCHES_SRC_PRS);
    #endif /* (CapSense_CSD_PRS_OPTIONS) */

    #if (CapSense_CSD_PRS_OPTIONS == CapSense_CSD_PRS_8BITS)
        /* Aux control set FIFO as REG */
        enableInterrupts = CyEnterCriticalSection();
        CapSense_CSD_AUX_CONTROL_A_REG |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
        CyExitCriticalSection(enableInterrupts);
        
        /* Write polynomial */
        CapSense_CSD_POLYNOM_REG   = CapSense_CSD_PRS8_DEFAULT_POLYNOM;
        /* Write FIFO with seed */
        CapSense_CSD_SEED_COPY_REG = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        
    #elif (CapSense_CSD_PRS_OPTIONS == CapSense_CSD_PRS_16BITS)
        /* Aux control set FIFO as REG */ 
        enableInterrupts = CyEnterCriticalSection();  
        CapSense_CSD_AUX_CONTROL_A_REG |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
        CapSense_CSD_AUX_CONTROL_B_REG |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
        CyExitCriticalSection(enableInterrupts);
        
        /* Write polynomial */
        CY_SET_REG16(CapSense_CSD_POLYNOM_PTR, CapSense_CSD_PRS16_DEFAULT_POLYNOM);
        /* Write FIFO with seed */
        CY_SET_REG16(CapSense_CSD_SEED_COPY_PTR, CapSense_CSD_MEASURE_FULL_RANGE);
                
    #elif (CapSense_CSD_PRS_OPTIONS == CapSense_CSD_PRS_16BITS_4X)
        /* Aux control set FIFO as REG */
        enableInterrupts = CyEnterCriticalSection();
        CapSense_CSD_AUX_CONTROL_A_REG  |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
        CyExitCriticalSection(enableInterrupts);
        
        /* Write polynomial */
        CapSense_CSD_POLYNOM_A__D1_REG   = HI8(CapSense_CSD_PRS16_DEFAULT_POLYNOM);
        CapSense_CSD_POLYNOM_A__D0_REG   = LO8(CapSense_CSD_PRS16_DEFAULT_POLYNOM);
        /* Write FIFO with seed */
        CapSense_CSD_SEED_COPY_A__F1_REG = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        CapSense_CSD_SEED_COPY_A__F0_REG = CapSense_CSD_MEASURE_FULL_RANGE_LOW; 
        
    #else
        /* Do nothing = config without PRS */
    #endif  /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD_PRS_8BITS) */ 
    
    /* Set ScanSpeed */
    CapSense_CSD_SCANSPEED_PERIOD_REG = CapSense_CSD_SCANSPEED_VALUE;
    
    /* Set the Measure */
    #if (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
        /* Window PWM */
        CapSense_CSD_PWM_CH0_CONTROL_REG      = CapSense_CSD_MEASURE_CTRL_ENABLE;
        CapSense_CSD_PWM_CH0_CONTROL2_REG    |= CapSense_CSD_MEASURE_CTRL_PULSEWIDTH;
        CY_SET_REG16(CapSense_CSD_PWM_CH0_COUNTER_PTR, CapSense_CSD_MEASURE_FULL_RANGE);
        
        /* Raw Counter */
        CapSense_CSD_RAW_CH0_CONTROL_REG      = CapSense_CSD_MEASURE_CTRL_ENABLE;
        CapSense_CSD_RAW_CH0_CONTROL2_REG    |= CapSense_CSD_MEASURE_CTRL_PULSEWIDTH;
        CY_SET_REG16(CapSense_CSD_RAW_CH0_PERIOD_PTR, CapSense_CSD_MEASURE_FULL_RANGE);
    
    #else
        /*Window PWM and Raw Counter AUX set */
        enableInterrupts = CyEnterCriticalSection();
        CapSense_CSD_PWM_CH0_AUX_CONTROL_REG |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
        CapSense_CSD_RAW_CH0_AUX_CONTROL_REG |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
        CyExitCriticalSection(enableInterrupts);
        
        /* Window PWM */
        CapSense_CSD_PWM_CH0_ADD_VALUE_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        CapSense_CSD_PWM_CH0_PERIOD_LO_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        CapSense_CSD_PWM_CH0_COUNTER_LO_REG   = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        
        /* Raw Counter */
        CapSense_CSD_RAW_CH0_ADD_VALUE_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        CapSense_CSD_RAW_CH0_PERIOD_HI_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        CapSense_CSD_RAW_CH0_PERIOD_LO_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
        
    #endif  /* (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */ 
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
        #if (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
            /* Window PWM */
            CapSense_CSD_PWM_CH1_CONTROL_REG      = CapSense_CSD_MEASURE_CTRL_ENABLE;
            CapSense_CSD_PWM_CH1_CONTROL2_REG    |= CapSense_CSD_MEASURE_CTRL_PULSEWIDTH;
            CY_SET_REG16(CapSense_CSD_PWM_CH1_COUNTER_PTR, CapSense_CSD_MEASURE_FULL_RANGE);
            
            /* Raw Counter */
            CapSense_CSD_RAW_CH1_CONTROL_REG      = CapSense_CSD_MEASURE_CTRL_ENABLE;
            CapSense_CSD_RAW_CH1_CONTROL2_REG    |= CapSense_CSD_MEASURE_CTRL_PULSEWIDTH;
            CY_SET_REG16(CapSense_CSD_RAW_CH1_PERIOD_PTR, CapSense_CSD_MEASURE_FULL_RANGE);
           
        #else
            /*Window PWM and Raw Counter AUX set */
            enableInterrupts = CyEnterCriticalSection();
            CapSense_CSD_PWM_CH1_AUX_CONTROL_REG |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
            CapSense_CSD_RAW_CH1_AUX_CONTROL_REG |= CapSense_CSD_AUXCTRL_FIFO_SINGLE_REG;
            CyExitCriticalSection(enableInterrupts);
            
            /* Window PWM */
            CapSense_CSD_PWM_CH1_ADD_VALUE_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
            CapSense_CSD_PWM_CH1_PERIOD_LO_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
            CapSense_CSD_PWM_CH1_COUNTER_LO_REG   = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
            
            /* Raw Counter */
            
            CapSense_CSD_RAW_CH1_ADD_VALUE_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
            CapSense_CSD_RAW_CH1_PERIOD_HI_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
            CapSense_CSD_RAW_CH1_PERIOD_LO_REG    = CapSense_CSD_MEASURE_FULL_RANGE_LOW;
            
        #endif  /* (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */
    
    #endif  /* (CapSense_CSD_DESIGN_TYPE == TWO_CHANNELS_DESIGN) */
    
    /* Setup ISR */
    CyIntDisable(CapSense_CSD_IsrCH0_ISR_NUMBER);
    (void)CyIntSetVector(CapSense_CSD_IsrCH0_ISR_NUMBER, &CapSense_CSD_IsrCH0_ISR);
    CyIntSetPriority(CapSense_CSD_IsrCH0_ISR_NUMBER, CapSense_CSD_IsrCH0_ISR_PRIORITY);
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
        CyIntDisable(CapSense_CSD_IsrCH1_ISR_NUMBER);
        CyIntSetVector(CapSense_CSD_IsrCH1_ISR_NUMBER, CapSense_CSD_IsrCH1_ISR);
        CyIntSetPriority(CapSense_CSD_IsrCH1_ISR_NUMBER, CapSense_CSD_IsrCH1_ISR_PRIORITY);
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Setup AMux Bus: Connect Cmod, Cmp, Idac */
    CapSense_CSD_AMuxCH0_Init();
    CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_CMOD_CHANNEL);
    CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_CMP_VP_CHANNEL);
    #if (CapSense_CSD_CURRENT_SOURCE)
        CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_IDAC_CHANNEL);
    #endif  /* CapSense_CSD_CURRENT_SOURCE */
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) 
        CapSense_CSD_AMuxCH1_Init();
        CapSense_CSD_AMuxCH1_Connect(CapSense_CSD_AMuxCH1_CMOD_CHANNEL);
        CapSense_CSD_AMuxCH1_Connect(CapSense_CSD_AMuxCH1_CMP_VP_CHANNEL);
        #if (CapSense_CSD_CURRENT_SOURCE)
            CapSense_CSD_AMuxCH1_Connect(CapSense_CSD_AMuxCH1_IDAC_CHANNEL);
        #endif  /* CapSense_CSD_CURRENT_SOURCE */
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Int Rb */
    #if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB)
        CapSense_CSD_InitRb();
    #endif /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB) */
    
    /* Enable window generation */
    CapSense_CSD_CONTROL_REG |= CapSense_CSD_CTRL_WINDOW_EN__CH0;
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
        CapSense_CSD_CONTROL_REG |= CapSense_CSD_CTRL_WINDOW_EN__CH1;
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Initialize Cmp and Idac */
    CapSense_CSD_CompCH0_Init();
    #if (CapSense_CSD_CURRENT_SOURCE)
        CapSense_CSD_IdacCH0_Init();
        CapSense_CSD_IdacCH0_SetPolarity(CapSense_CSD_IdacCH0_IDIR);
        CapSense_CSD_IdacCH0_SetRange(CapSense_CSD_IDAC_RANGE_VALUE);
        CapSense_CSD_IdacCH0_SetValue(CapSense_CSD_TURN_OFF_IDAC);
    #endif  /* CapSense_CSD_CURRENT_SOURCE */
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) 
        CapSense_CSD_CompCH1_Init();
        #if (CapSense_CSD_CURRENT_SOURCE)
            CapSense_CSD_IdacCH1_Init();
            CapSense_CSD_IdacCH1_SetPolarity(CapSense_CSD_IdacCH1_IDIR);
            CapSense_CSD_IdacCH1_SetRange(CapSense_CSD_IDAC_RANGE_VALUE);
            CapSense_CSD_IdacCH1_SetValue(CapSense_CSD_TURN_OFF_IDAC);
        #endif  /* CapSense_CSD_CURRENT_SOURCE */
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Initialize Vref if as VDAC */
    #if (CapSense_CSD_VREF_OPTIONS == CapSense_CSD_VREF_VDAC)
        CapSense_CSD_VdacRefCH0_Init();
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
            CapSense_CSD_VdacRefCH1_Init();
        #endif  /* CapSense_CSD_DESIGN_TYPE */
    #endif  /* CapSense_CSD_VREF_OPTIONS */
}


/*******************************************************************************
* Function Name: CapSense_CSD_Enable
********************************************************************************
*
* Summary:
*  Enables active mode power template bits for number of component used within 
*  CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_Enable(void) 
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    
    /* Enable Prescaler */
    #if (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB)
        /* Do nothing  for UDB */
    #elif (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_FF)
        CapSense_CSD_PRESCALER_ACT_PWRMGR_REG  |= CapSense_CSD_PRESCALER_ACT_PWR_EN;
        CapSense_CSD_PRESCALER_STBY_PWRMGR_REG |= CapSense_CSD_PRESCALER_STBY_PWR_EN;
        
    #else
        /* Do nothing = config without prescaler */
    #endif  /* (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB) */
    
    /* Enable ScanSpeed */
    CapSense_CSD_SCANSPEED_AUX_CONTROL_REG |= CapSense_CSD_SCANSPEED_CTRL_ENABLE;
    
    /* Enable Measure CH0 */
    #if (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
        /* Window PWM */
        CapSense_CSD_PWM_CH0_ACT_PWRMGR_REG  |= CapSense_CSD_PWM_CH0_ACT_PWR_EN;
        CapSense_CSD_PWM_CH0_STBY_PWRMGR_REG |= CapSense_CSD_PWM_CH0_STBY_PWR_EN;
        
        /* Raw Counter */
        CapSense_CSD_RAW_CH0_ACT_PWRMGR_REG  |= CapSense_CSD_RAW_CH0_ACT_PWR_EN;
        CapSense_CSD_RAW_CH0_STBY_PWRMGR_REG |= CapSense_CSD_RAW_CH0_STBY_PWR_EN;
        
    #else
        /* Window PWM -  Do nothing */
        /* Raw Counter - Do nothing */
        
    #endif  /* (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */ 
    
    /* Enable Measure CH1*/
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
        #if (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
            /* Window PWM */
            CapSense_CSD_PWM_CH1_ACT_PWRMGR_REG  |= CapSense_CSD_PWM_CH1_ACT_PWR_EN;
            CapSense_CSD_PWM_CH1_STBY_PWRMGR_REG |= CapSense_CSD_PWM_CH1_STBY_PWR_EN;
            
            /* Raw Counter */
            CapSense_CSD_RAW_CH1_ACT_PWRMGR_REG  |= CapSense_CSD_RAW_CH1_ACT_PWR_EN;
            CapSense_CSD_RAW_CH1_STBY_PWRMGR_REG |= CapSense_CSD_RAW_CH1_STBY_PWR_EN;
           
        #else
        /* Window PWM -  Do nothing */
        /* Raw Counter - Do nothing */
        
        #endif  /* (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */
    
    #endif  /* (CapSense_CSD_DESIGN_TYPE == TWO_CHANNELS_DESIGN)*/
    
    /* Enable the Clock */
    #if (CapSense_CSD_CLOCK_SOURCE == CapSense_CSD_INTERNAL_CLOCK)
       CapSense_CSD_IntClock_Enable();
    #endif  /* CapSense_CSD_CLOCK_SOURCE */
    
    /* Setup Cmp and Idac */
    CapSense_CSD_CompCH0_Enable();
    #if (CapSense_CSD_CURRENT_SOURCE)
        CapSense_CSD_IdacCH0_Enable();
    #endif  /* CapSense_CSD_CURRENT_SOURCE */
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) 
        CapSense_CSD_CompCH1_Enable();
        #if (CapSense_CSD_CURRENT_SOURCE)
            CapSense_CSD_IdacCH1_Enable();
        #endif  /* CapSense_CSD_CURRENT_SOURCE */
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Enable Vref */
    #if (CapSense_CSD_VREF_OPTIONS == CapSense_CSD_VREF_VDAC)
        CapSense_CSD_VdacRefCH0_Enable();
        CapSense_CSD_VdacRefCH0_SetValue(CapSense_CSD_VdacRefCH0_DEFAULT_DATA);
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
            CapSense_CSD_VdacRefCH1_Enable();
            CapSense_CSD_VdacRefCH1_SetValue(CapSense_CSD_VdacRefCH1_DEFAULT_DATA);
        #endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) */
    #else
        /* Enable CapSense Buf */
        CapSense_CSD_BufCH0_STBY_PWRMGR_REG |= CapSense_CSD_BufCH0_STBY_PWR_EN;
        CapSense_CSD_BufCH0_ACT_PWRMGR_REG  |= CapSense_CSD_BufCH0_ACT_PWR_EN;
        
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
            CapSense_CSD_BufCH1_STBY_PWRMGR_REG |= CapSense_CSD_BufCH1_STBY_PWR_EN;
            CapSense_CSD_BufCH1_ACT_PWRMGR_REG  |= CapSense_CSD_BufCH1_ACT_PWR_EN;
        #endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) */
    #endif  /* (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS) */
    
    /* Set reference on AMux Bus */
    #if (CapSense_CSD_VREF_OPTIONS == CapSense_CSD_VREF_VDAC)
        /* Connect Vdac to AMux Bus */
        CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_VREF_CHANNEL);
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
            CapSense_CSD_AMuxCH1_Connect(CapSense_CSD_AMuxCH1_VREF_CHANNEL);
        #endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) */
        
    #else
        /* Enable CapSense Buf */
        CapSense_CSD_BufCH0_CAPS_CFG0_REG |= CapSense_CSD_CSBUF_ENABLE;
        
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
            CapSense_CSD_BufCH1_CAPS_CFG0_REG |= CapSense_CSD_CSBUF_ENABLE;
        #endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) */
    #endif  /* (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS)*/
    
    CyExitCriticalSection(enableInterrupts);
    
    /* Enable interrupt */
    CyIntEnable(CapSense_CSD_IsrCH0_ISR_NUMBER);
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) 
        CyIntEnable(CapSense_CSD_IsrCH1_ISR_NUMBER);
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Set CapSense Enable state */
    CapSense_CSD_CONTROL_REG |= CapSense_CSD_CTRL_CAPSENSE_EN;
}


/*******************************************************************************
* Function Name: CapSense_CSD_Start
********************************************************************************
*
* Summary:
*  Initializes registers and starts the CSD method of CapSense component. Reset 
*  all sensors to an inactive state. Enables interrupts for sensors scanning.
*  When Auto Tuning (SmartSense) mode is selected the tuning procedure is 
*  applied for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_initVar - used to check initial configuration, modified on 
*  first function call.
*  CapSense_CSD_lowLevelTuningDone - used to notify the Tuner GUI that 
*  tuning of scanning parameters are done.
*
* Reentrant:
*  No
*
* Note:
*  All widgets are enabled by default except proximity widgets. Proximity widgets 
*  must be manually enabled as their long scan time is incompatible 
*  with the fast response required of other widget types. 
*
*******************************************************************************/
void CapSense_CSD_Start(void)  
{
    if (CapSense_CSD_initVar == 0u)
    {
        CapSense_CSD_Init();
        CapSense_CSD_initVar = 1u;
    }
    CapSense_CSD_Enable();
    
    /* AutoTunning start */
    #if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)
        /* AutoTune by sensor or pair of sensor basis */
        CapSense_CSD_AutoTune();
        CapSense_CSD_lowLevelTuningDone = 1u;
    #endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) */
}


/*******************************************************************************
* Function Name: CapSense_CSD_Stop
********************************************************************************
*
* Summary:
*  Stops the sensors scanner, disables internal interrupts, and resets all 
*  sensors to an inactive state. Disables Active mode power template bits for 
*  number of component used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This function should be called after scans will be completed.
*
*******************************************************************************/
void CapSense_CSD_Stop(void) 
{
    /* Stop Capsensing */
    CapSense_CSD_CONTROL_REG &= (uint8)(~CapSense_CSD_CTRL_START);
    
    /* Disable interrupt */
    CyIntDisable(CapSense_CSD_IsrCH0_ISR_NUMBER);
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) 
        CyIntDisable(CapSense_CSD_IsrCH1_ISR_NUMBER);
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Clear all sensors */
    CapSense_CSD_ClearSensors();
    
    /* Disable Prescaler */
    #if (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB)
        /* Do nothing  for UDB */
    #elif (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_FF)        
        CapSense_CSD_PRESCALER_ACT_PWRMGR_REG  &= ~CapSense_CSD_PRESCALER_ACT_PWR_EN;
        CapSense_CSD_PRESCALER_STBY_PWRMGR_REG &= ~CapSense_CSD_PRESCALER_STBY_PWR_EN;
        
    #else
        /* Do nothing = config without prescaler */
    #endif  /* (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB) */
    
    /* Disable ScanSpeed */
    CapSense_CSD_SCANSPEED_AUX_CONTROL_REG &= (uint8)(~CapSense_CSD_SCANSPEED_CTRL_ENABLE);
    
    /* Disable Measure CH0 */
    #if (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
        /* Window PWM */
        CapSense_CSD_PWM_CH0_ACT_PWRMGR_REG  &= ~CapSense_CSD_PWM_CH0_ACT_PWR_EN;
        CapSense_CSD_PWM_CH0_STBY_PWRMGR_REG &= ~CapSense_CSD_PWM_CH0_STBY_PWR_EN;

        /* Raw Counter */
        CapSense_CSD_RAW_CH0_ACT_PWRMGR_REG  &= ~CapSense_CSD_RAW_CH0_ACT_PWR_EN;
        CapSense_CSD_RAW_CH0_STBY_PWRMGR_REG &= ~CapSense_CSD_RAW_CH0_STBY_PWR_EN;

    #else
        /* Window PWM -  Do nothing */
        /* Raw Counter - Do nothing */
        
    #endif  /* (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */ 
    
    /* Disable Measure CH1 */
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
        #if (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
            /* Window PWM */
            CapSense_CSD_PWM_CH1_ACT_PWRMGR_REG  &= ~CapSense_CSD_PWM_CH1_ACT_PWR_EN;
            CapSense_CSD_PWM_CH1_STBY_PWRMGR_REG &= ~CapSense_CSD_PWM_CH1_STBY_PWR_EN;
    
            /* Raw Counter */
            CapSense_CSD_RAW_CH1_ACT_PWRMGR_REG  &= ~CapSense_CSD_RAW_CH1_ACT_PWR_EN;
            CapSense_CSD_RAW_CH1_STBY_PWRMGR_REG &= ~CapSense_CSD_RAW_CH1_STBY_PWR_EN;
           
        #else
        /* Window PWM -  Do nothing */
        /* Raw Counter - Do nothing */
        
        #endif  /* (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */
    
    #endif  /* (CapSense_CSD_DESIGN_TYPE == TWO_CHANNELS_DESIGN)*/
    
    /* Disable the Clock */
    #if (CapSense_CSD_CLOCK_SOURCE == CapSense_CSD_INTERNAL_CLOCK)
       CapSense_CSD_IntClock_Stop();
    #endif  /* CapSense_CSD_CLOCK_SOURCE */
    
    /* Disable power from Cmp and Idac */
    CapSense_CSD_CompCH0_Stop();
    #if (CapSense_CSD_CURRENT_SOURCE)
        CapSense_CSD_IdacCH0_Stop();
    #endif  /* CapSense_CSD_CURRENT_SOURCE */
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) 
        CapSense_CSD_CompCH1_Stop();
        #if (CapSense_CSD_CURRENT_SOURCE)
            CapSense_CSD_IdacCH1_Stop();
        #endif  /* CapSense_CSD_CURRENT_SOURCE */
    #endif  /* CapSense_CSD_DESIGN_TYPE */    
    
    /* Disable Vref if as VDAC */
    #if (CapSense_CSD_VREF_OPTIONS == CapSense_CSD_VREF_VDAC)
        CapSense_CSD_VdacRefCH0_Stop();
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
            CapSense_CSD_VdacRefCH1_Stop();
        #endif  /* CapSense_CSD_DESIGN_TYPE */
    #endif  /* CapSense_CSD_VREF_OPTIONS */

    #if (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS)
        /* The Idac turn off before */
    #else
        /* Enable CapSense Buf */
        CapSense_CSD_BufCH0_CAPS_CFG0_REG &= (uint8)(~CapSense_CSD_CSBUF_ENABLE);
        CapSense_CSD_BufCH0_ACT_PWRMGR_REG &= (uint8)(~CapSense_CSD_BufCH0_ACT_PWR_EN);
        CapSense_CSD_BufCH0_STBY_PWRMGR_REG &= (uint8)(~CapSense_CSD_BufCH0_STBY_PWR_EN);
        
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
            CapSense_CSD_BufCH1_CAPS_CFG0_REG &= (uint8)(~CapSense_CSD_CSBUF_ENABLE);
            CapSense_CSD_BufCH1_ACT_PWRMGR_REG &= (uint8)(~CapSense_CSD_BufCH1_ACT_PWR_EN);
            CapSense_CSD_BufCH1_STBY_PWRMGR_REG &= (uint8)(~CapSense_CSD_BufCH1_STBY_PWR_EN);
        #endif  /*(CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) */
    #endif  /* (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS) */
    
    /* Set CapSense Disable state */
    CapSense_CSD_CONTROL_REG &= (uint8)(~CapSense_CSD_CTRL_CAPSENSE_EN);
}


#if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
    /*******************************************************************************
    * Function Name: CapSense_CSD_FindNextSensor
    ********************************************************************************
    *
    * Summary:
    *  Finds next sensor to scan. 
    *
    * Parameters:
    *  snsIndex:  Current index of sensor.
    *
    * Return:
    *  Returns the next sensor index to scan.
    *
    * Global Variables:
    *  CapSense_CSD_sensorEnableMask[ ] - used to store bit masks of enabled 
    *  sensors.
    *  CapSense_CSD_sensorEnableMask[0] contains the masked bits for sensors 0
    *  through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
    *  CapSense_CSD_sensorEnableMask[1] contains the masked bits for sensors 
    *  8 through 15 (if needed), and so on.
    *    0 - sensor doesn't scan by CapSense_CSD_ScanEnabledWidgets().
    *    1 - sensor scans by CapSense_CSD_ScanEnabledWidgets().
    *
    * Note: 
    *  This function has effect on current scanning scanning and should not
    *  be used outisde of component.
    *
    *******************************************************************************/
    uint8 CapSense_CSD_FindNextSensor(uint8 snsIndex) CYREENTRANT
    {
        uint8 pos;
        uint8 enMask;
        
        /* Check if sensor enabled */
        do
        {
            /* Proceed with the next sensor */
            snsIndex++;
            if(snsIndex == CapSense_CSD_TOTAL_SENSOR_COUNT)
            {
                break;
            }
            pos = (snsIndex >> 3u);
            enMask = 0x01u << (snsIndex & 0x07u);
        }    
        while((CapSense_CSD_sensorEnableMask[pos] & enMask) == 0u);
        
        return snsIndex;
    }
 #endif  /* CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN */
 
 
#if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN)
    /*******************************************************************************
    * Function Name: CapSense_CSD_FindNextPair
    ********************************************************************************
    *
    * Summary:
    *  Finds next pair or sensor to scan. Sets condition bits to skip scanning.
    *  
    * Parameters:
    *  snsIndex:  Current index pair of sensors.
    *
    * Return:
    *  Returns the next pair of sensors index to scan.
    *
    * Global Variables:
    *  CapSense_CSD_sensorEnableMask[ ] - used to store bit masks of enabled 
    *  sensors.
    *  CapSense_CSD_sensorEnableMask[0] contains the masked bits for sensors 0
    *  through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
    *  CapSense_CSD_sensorEnableMask[1] contains the masked bits for sensors 
    *  8 through 15 (if needed), and so on.
    *    0 - sensor doesn't scan by CapSense_CSD_ScanEnabledWidgets().
    *    1 - sensor scans by CapSense_CSD_ScanEnabledWidgets().
    *
    * Note: 
    *  This function has effect on control signals set for scanning and should not
    *  be used outisde of component.
    *
    *******************************************************************************/
    uint8 CapSense_CSD_FindNextPair(uint8 snsIndex) CYREENTRANT
    {
        uint8 posCh;
        uint8 enMaskCh;
        uint8 newRegValue;
        uint8 indexCh0 = snsIndex;
        uint8 indexCh1 = snsIndex + CapSense_CSD_TOTAL_SENSOR_COUNT__CH0;
        
        /* Find enabled sensor on channel 0 */
        do
        {
            /* Procced the scanning */
            indexCh0++;
            if (indexCh0 >= CapSense_CSD_TOTAL_SENSOR_COUNT__CH0)
            {
                /* Lets hadle now all from CH1 */
                indexCh0 = CapSense_CSD_END_OF_SCAN__CH0;
                break;
            }
            
            posCh = (indexCh0 >> 3u);
            enMaskCh = 0x01u << (indexCh0 & 0x07u);
        }
        while((CapSense_CSD_sensorEnableMask[posCh] & enMaskCh) == 0u);
        
        /* Find enabled sensor on channel 1 */
        do
        {
            /* Procced the scanning */
            indexCh1++;        
            if (indexCh1 >= CapSense_CSD_TOTAL_SENSOR_COUNT)
            {
                /* Lets hadle now all from CH0 */
                indexCh1 = CapSense_CSD_END_OF_SCAN__CH1;
                break;
            }
            
            posCh = (indexCh1 >> 3u);
            enMaskCh = 0x01u << (indexCh1 & 0x07u);
        } 
        while((CapSense_CSD_sensorEnableMask[posCh] & enMaskCh) == 0u);
        
        indexCh1 -= CapSense_CSD_TOTAL_SENSOR_COUNT__CH0;
        
        /* Find the pair to scan */
        if(indexCh0 == indexCh1)
        {
            /* Scans TWO Channels */
            snsIndex = indexCh0;
            
            CapSense_CSD_CONTROL_REG |= (CapSense_CSD_CTRL_WINDOW_EN__CH0 | 
                                             CapSense_CSD_CTRL_WINDOW_EN__CH1);
        }
        else if(indexCh0 < indexCh1)
        {
           /* Scans Channel ONE only */
           snsIndex = indexCh0;
           
            newRegValue = CapSense_CSD_CONTROL_REG;
            newRegValue |= CapSense_CSD_CTRL_WINDOW_EN__CH0;
            newRegValue &= ~CapSense_CSD_CTRL_WINDOW_EN__CH1;
            CapSense_CSD_CONTROL_REG = newRegValue;
        }
        else
        {
            /* Scans Channel TWO only */
            snsIndex = indexCh1;
            
            newRegValue = CapSense_CSD_CONTROL_REG;
            newRegValue |= CapSense_CSD_CTRL_WINDOW_EN__CH1;
            newRegValue &= ~CapSense_CSD_CTRL_WINDOW_EN__CH0;
            CapSense_CSD_CONTROL_REG = newRegValue;
        }
        
        return (snsIndex);
    }
#endif  /* CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN */


/*******************************************************************************
* Function Name: CapSense_CSD_SetScanSlotSettings
********************************************************************************
*
* Summary:
*  Sets the scan settings of the selected scan slot (sensor or pair of sensors). 
*  The scan settings incorporate IDAC value (for IDAC configurations) for every 
*  sensor and resolution. The resolution is the same for all sensors within 
*  widget.
*
* Parameters:
*  slot:  Scan slot number (sensor or pair of sensors).
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_idacSettings[] - used to store idac value for every sensor.
*  CapSense_CSD_widgetResolution[] - used to store scan resolution of every 
*  widget.
*
*******************************************************************************/
void CapSense_CSD_SetScanSlotSettings(uint8 slot) CYREENTRANT
{
    uint8 widget;
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
        /* Define widget sensor belongs to */
        widget = CapSense_CSD_widgetNumber[slot];
        
        /* Set Idac Value */
        #if (CapSense_CSD_CURRENT_SOURCE)
            CapSense_CSD_IdacCH0_SetValue(CapSense_CSD_idacSettings[slot]);
        #endif  /* CapSense_CSD_CURRENT_SOURCE */
        
        /* Window PWM */
        #if (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
            CY_SET_REG16(CapSense_CSD_PWM_CH0_PERIOD_PTR,
                ((uint16) CapSense_CSD_widgetResolution[widget] << 8u) | CapSense_CSD_MEASURE_FULL_RANGE_LOW);
        #else
            CapSense_CSD_PWM_CH0_PERIOD_HI_REG = CapSense_CSD_widgetResolution[widget];
        #endif  /* (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */ 

        #if ( (CapSense_CSD_MULTIPLE_PRESCALER_ENABLED) || \
              (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )
            CapSense_CSD_SetPrescaler(CapSense_CSD_analogSwitchDivider[slot]);
        #elif (CapSense_CSD_PRESCALER_OPTIONS)
            CapSense_CSD_SetPrescaler(CapSense_CSD_analogSwitchDivider);
        #endif /* ((CapSense_CSD_MULTIPLE_PRESCALER_ENABLED) || \
               *   (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING))
               */

    #else
        if(slot < CapSense_CSD_TOTAL_SENSOR_COUNT__CH0)
        {
            /* Define widget sensor belongs to */
            widget = CapSense_CSD_widgetNumber[slot];
            
            /* Set Idac Value */
            #if (CapSense_CSD_CURRENT_SOURCE)
                CapSense_CSD_IdacCH0_SetValue(CapSense_CSD_idacSettings[slot]);
            #endif  /* CapSense_CSD_CURRENT_SOURCE */
            
            /* Set Pwm Resolution */
            #if (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
                CY_SET_REG16(CapSense_CSD_PWM_CH0_PERIOD_PTR,
                  ((uint16) CapSense_CSD_widgetResolution[widget] << 8u) | CapSense_CSD_MEASURE_FULL_RANGE_LOW);
            #else
                CapSense_CSD_PWM_CH0_PERIOD_HI_REG = CapSense_CSD_widgetResolution[widget];
            #endif  /* (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)*/ 
        }
        
        if(slot < CapSense_CSD_TOTAL_SENSOR_COUNT__CH1)
        {
            widget = CapSense_CSD_widgetNumber[slot+CapSense_CSD_TOTAL_SENSOR_COUNT__CH0];
        
            /* Set Idac Value */
            #if (CapSense_CSD_CURRENT_SOURCE)
                CapSense_CSD_IdacCH1_SetValue(CapSense_CSD_idacSettings[slot+
                                                                             CapSense_CSD_TOTAL_SENSOR_COUNT__CH0]);
            #endif  /* CapSense_CSD_CURRENT_SOURCE */
            
            /* Set Pwm Resolution */
            #if (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
                CY_SET_REG16(CapSense_CSD_PWM_CH1_PERIOD_PTR,
                  ((uint16) CapSense_CSD_widgetResolution[widget] << 8u) | CapSense_CSD_MEASURE_FULL_RANGE_LOW);
            #else
                CapSense_CSD_PWM_CH1_PERIOD_HI_REG = CapSense_CSD_widgetResolution[widget];
            #endif  /* (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)*/ 
        }

        #if ( (CapSense_CSD_MULTIPLE_PRESCALER_ENABLED) || \
              (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )
            CapSense_CSD_SetPrescaler(CapSense_CSD_analogSwitchDivider[slot]);
        #elif (CapSense_CSD_PRESCALER_OPTIONS)
            CapSense_CSD_SetPrescaler(CapSense_CSD_analogSwitchDivider);
        #endif /* ((CapSense_CSD_MULTIPLE_PRESCALER_ENABLED) || \
               *   (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING))
               */

    #endif  /* CapSense_CSD_DESIGN_TYPE */
}


/*******************************************************************************
* Function Name: CapSense_CSD_ScanSensor
********************************************************************************
*
* Summary:
*  Sets scan settings and starts scanning a sensor or pair of combined sensors
*  on each channel. If two channels are configured, two sensors may be scanned 
*  at the same time. After scanning is complete the isr copies the measured 
*  sensor raw data to the global array. Use of the isr ensures this function 
*  is non-blocking. Each sensor has a unique number within the sensor array. 
*  This number is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and mode of scan as single scan.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one.
*  CapSense_CSD_sensorIndex - used to store sensor scanning sensor number.
*  Sets to provided sensor argument.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_ScanSensor(uint8 sensor)  
{
    /* Clears status/control variable and set sensorIndex */
    CapSense_CSD_csv = 0u;
    CapSense_CSD_sensorIndex = sensor;
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
        /* Start of sensor scan */
        CapSense_CSD_csv = (CapSense_CSD_SW_STS_BUSY | CapSense_CSD_SW_CTRL_SINGLE_SCAN);
        CapSense_CSD_PreScan(sensor);
        
    #else
        /* CH0: check end of scan conditions */
        if(sensor < CapSense_CSD_TOTAL_SENSOR_COUNT__CH0)
        {
            CapSense_CSD_CONTROL_REG |= CapSense_CSD_CTRL_WINDOW_EN__CH0;
        }
        else
        {
            CapSense_CSD_CONTROL_REG &= ~CapSense_CSD_CTRL_WINDOW_EN__CH0;
        }
        
        /* CH1: check end of scan conditions */
        if(sensor < CapSense_CSD_TOTAL_SENSOR_COUNT__CH1)
        {
            CapSense_CSD_CONTROL_REG |= CapSense_CSD_CTRL_WINDOW_EN__CH1;
        }
        else
        {
            CapSense_CSD_CONTROL_REG &= ~CapSense_CSD_CTRL_WINDOW_EN__CH1;
        }
        
        /* Start sensor scan */
        if( ((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH0) != 0u) || 
            ((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH1) != 0u) )
        {
        
            CapSense_CSD_csv |= (CapSense_CSD_SW_STS_BUSY | CapSense_CSD_SW_CTRL_SINGLE_SCAN);
            CapSense_CSD_PreScan(sensor);
        }
        
    #endif  /* CapSense_CSD_DESIGN_TYPE */
}


/*******************************************************************************
* Function Name: CapSense_CSD_ScanEnableWidgets
********************************************************************************
*
* Summary:
*  Scans all of the enabled widgets. Starts scanning a sensor or pair of sensors 
*  within enabled widget. The isr proceeding scanning next sensor or pair till 
*  all enabled widgets will be scanned. Use of the isr ensures this function is 
*  non-blocking. All widgets are enabled by default except proximity widgets. 
*  Proximity widgets must be manually enabled as their long scan time is 
*  incompatible with fast response desired of other widget types.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and clears single scan mode.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one. 
*  CapSense_CSD_sensorIndex - used to store sensor scanning sensor number.
*  Sets to 0xFF and provided to function CapSense_CSD_FindNextSensor or
*  CapSense_CSD_FindNextPair, these functions starts with sensor index
*  increment and overflow of uint8 gives desired index 0.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_ScanEnabledWidgets(void) 
{
    /* Clears status/control variable and set sensorIndex */
    CapSense_CSD_csv = 0u;
    CapSense_CSD_sensorIndex = 0xFFu;
    
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
        /* Find next sensor */
        CapSense_CSD_sensorIndex = CapSense_CSD_FindNextSensor(CapSense_CSD_sensorIndex);

        /* Check end of scan condition */
        if(CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT)
        {
            CapSense_CSD_csv |= CapSense_CSD_SW_STS_BUSY;
            CapSense_CSD_PreScan(CapSense_CSD_sensorIndex);
        }
        
    #else
        /* Find next sensor and set proper control register */
        CapSense_CSD_sensorIndex = CapSense_CSD_FindNextPair(CapSense_CSD_sensorIndex);
        
        /* Start sensor scan */
        if((CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT__CH0) || 
           (CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT__CH1))
        {
            CapSense_CSD_csv |= CapSense_CSD_SW_STS_BUSY;
            CapSense_CSD_PreScan(CapSense_CSD_sensorIndex);
        }
        
    #endif  /* CapSense_CSD_DESIGN_TYPE */
}


/*******************************************************************************
* Function Name: CapSense_CSD_IsBusy
********************************************************************************
*
* Summary:
*  Returns the state of CapSense component. The 1 means that scanning in 
*  progress and 0 means that scanning is complete.
*
* Parameters:
*  None
*
* Return:
*  Returns the state of scanning. 1 - scanning in progress, 0 - scanning 
*  completed.
*
* Global Variables:
*  CapSense_CSD_csv - used to provide status and mode of scanning process. 
*  Checks the busy status.
*
*******************************************************************************/
uint8 CapSense_CSD_IsBusy(void) 
{
    return ((0u != (CapSense_CSD_csv & CapSense_CSD_SW_STS_BUSY)) ? 1u : 0u);
}


/*******************************************************************************
* Function Name: CapSense_CSD_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns scan sensor raw data from the CapSense_CSD_sensorRaw[] array. 
*  Each scan sensor has a unique number within the sensor array. This number 
*  is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns current raw data value for defined sensor number.
*
* Global Variables:
*  CapSense_CSD_sensorRaw[] - used to store sensors raw data.
*
*******************************************************************************/
uint16 CapSense_CSD_ReadSensorRaw(uint8 sensor) 
{
    return (CapSense_CSD_sensorRaw[sensor]);
}


/*******************************************************************************
* Function Name: CapSense_CSD_ClearSensors
********************************************************************************
*
* Summary:
*  Resets all sensors to the non-sampling state by sequentially disconnecting
*  all sensors from Analog MUX Bus and putting them to inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_ClearSensors(void) 
{
    uint8 i;
   
    for (i = 0u; i < CapSense_CSD_TOTAL_SENSOR_COUNT; i++)
    {
        CapSense_CSD_DisableScanSlot(i);
    }
}


#if (CapSense_CSD_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: CapSense_CSD_EnableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Configures the selected slot to measure during the next measurement 
    *  cycle. The corresponding pin/pins are set to Analog High-Z mode and 
    *  connected to the Analog Mux Bus. This also enables the comparator function.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Constants:
    *  CapSense_CSD_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  CapSense_CSD_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  CapSense_CSD_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The bit 7 (msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    void CapSense_CSD_EnableScanSlot(uint8 slot) CYREENTRANT
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = CapSense_CSD_portTable[slot];
        
        /* Check if sensor is complex */
        if ((snsType & CapSense_CSD_COMPLEX_SS_FLAG) == 0u)
        {
            /* Enable sensor (signle) */
            CapSense_CSD_EnableSensor(slot);
        }
        else
        {
            /* Enable complex sensor */
            snsType &= ~CapSense_CSD_COMPLEX_SS_FLAG;
            index = &CapSense_CSD_indexTable[snsType];
            snsNumber = CapSense_CSD_maskTable[slot];
                        
            for (j=0u; j < snsNumber; j++)
            {
                CapSense_CSD_EnableSensor(index[j]);
            }
        } 
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_CSD_DisableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Disables the selected slot. The corresponding pin/pis is/are disconnected 
    *  from the Analog Mux Bus and connected to GND, High_Z or Shield electrode.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  CapSense_CSD_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  CapSense_CSD_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The 7bit(msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    void CapSense_CSD_DisableScanSlot(uint8 slot) CYREENTRANT
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = CapSense_CSD_portTable[slot];
        
        /* Check if sensor is complex */
        if ((snsType & CapSense_CSD_COMPLEX_SS_FLAG) == 0u)
        {
            /* Disable sensor (signle) */
            CapSense_CSD_DisableSensor(slot);
        }
        else
        {
            /* Disable complex sensor */
            snsType &= ~CapSense_CSD_COMPLEX_SS_FLAG;
            index = &CapSense_CSD_indexTable[snsType];
            snsNumber = CapSense_CSD_maskTable[slot];
                        
            for (j=0u; j < snsNumber; j++)
            {
                CapSense_CSD_DisableSensor(index[j]);
            }
        } 
    }
#endif  /* CapSense_CSD_IS_COMPLEX_SCANSLOTS */


/*******************************************************************************
* Function Name: CapSense_CSD_EnableSensor
********************************************************************************
*
* Summary:
*  Configures the selected sensor to measure during the next measurement cycle.
*  The corresponding pins are set to Analog High-Z mode and connected to the
*  Analog Mux Bus. This also enables the comparator function.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  CapSense_CSD_maskTable[] - used to store the pin within the port for 
*  every sensor.
*  CapSense_CSD_csTable[]   - used to store the pointers to CAPS_SEL 
*  registers for every port.
*  CapSense_CSD_pcTable[]   - used to store the pointers to PC pin 
*  register for every sensor.
*  CapSense_CSD_amuxIndex[] - used to store corrected AMUX index when 
*  complex sensors are defeined.
*
*******************************************************************************/
void CapSense_CSD_EnableSensor(uint8 sensor) CYREENTRANT
{
    uint8 port = CapSense_CSD_portTable[sensor];
    uint8 mask = CapSense_CSD_maskTable[sensor];
    
    #if ((CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) && \
         (CapSense_CSD_IS_COMPLEX_SCANSLOTS))
        uint8 amuxCh = CapSense_CSD_amuxIndex[sensor];
    #endif  /* ((CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) && \
            *   (CapSense_CSD_IS_COMPLEX_SCANSLOTS))
            */
    
    /* Make sensor High-Z */
    *CapSense_CSD_pcTable[sensor] = CapSense_CSD_PRT_PC_HIGHZ;
    
    /* Connect to DSI output */
	if(port == 15u)
	{
		port = 7u;
	}
    *CapSense_CSD_csTable[port] |= mask;
    
    /* Connect to AMUX */
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
        #if (CapSense_CSD_IS_COMPLEX_SCANSLOTS)
            CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_amuxIndex[sensor]);
        #else
            CapSense_CSD_AMuxCH0_Connect(sensor);
        #endif  /* CapSense_CSD_IS_COMPLEX_SCANSLOTS */
                
    #else
        #if (CapSense_CSD_IS_COMPLEX_SCANSLOTS)
            if ((amuxCh & CapSense_CSD_CHANNEL1_FLAG) == 0u)
            {
                CapSense_CSD_AMuxCH0_Connect(amuxCh);
            } 
            else
            {
                amuxCh &= ~ CapSense_CSD_CHANNEL1_FLAG;
                CapSense_CSD_AMuxCH1_Connect(amuxCh);
            }
            
        #else
            if (sensor < CapSense_CSD_TOTAL_SENSOR_COUNT__CH0) 
            {
                CapSense_CSD_AMuxCH0_Connect(sensor);
            } 
            else
            {
                CapSense_CSD_AMuxCH1_Connect(sensor - CapSense_CSD_TOTAL_SENSOR_COUNT__CH0);
            }
            
        #endif  /* CapSense_CSD_IS_COMPLEX_SCANSLOTS */
        
    #endif  /* CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN */
}


/*******************************************************************************
* Function Name: CapSense_CSD_DisableSensor
********************************************************************************
*
* Summary:
*  Disables the selected sensor. The corresponding pin is disconnected from the
*  Analog Mux Bus and connected to GND, High_Z or Shield electrode.
*
* Parameters:
*  sensor:  Sensor number
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  CapSense_CSD_maskTable[] - used to store the pin within the port for 
*  every sensor.
*  CapSense_CSD_csTable[]   - used to store the pointers to CAPS_SEL 
*  registers for every port.
*  CapSense_CSD_pcTable[]   - used to store the pointers to PC pin 
*  register for every sensor.
*  CapSense_CSD_amuxIndex[] - used to store corrected AMUX index when 
*  complex sensors are defeined.
*
*******************************************************************************/
void CapSense_CSD_DisableSensor(uint8 sensor) CYREENTRANT
{
    uint8 port = CapSense_CSD_portTable[sensor];
    uint8 mask = CapSense_CSD_maskTable[sensor];
    
    #if ((CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) && \
         (CapSense_CSD_IS_COMPLEX_SCANSLOTS))
        uint8 amuxCh = CapSense_CSD_amuxIndex[sensor];
    #endif  /* ((CapSense_CSD_DESIGN_TYPE == CapSense_CSD_TWO_CHANNELS_DESIGN) && \
            *   (CapSense_CSD_IS_COMPLEX_SCANSLOTS))
            */
    
    /* Disconnect from AMUX */
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
        #if (CapSense_CSD_IS_COMPLEX_SCANSLOTS)
            CapSense_CSD_AMuxCH0_Disconnect(CapSense_CSD_amuxIndex[sensor]);
        #else
            CapSense_CSD_AMuxCH0_Disconnect(sensor);
        #endif  /* CapSense_CSD_IS_COMPLEX_SCANSLOTS */
                
    #else
        #if (CapSense_CSD_IS_COMPLEX_SCANSLOTS)
            if ((amuxCh & CapSense_CSD_CHANNEL1_FLAG) == 0u)
            {
                CapSense_CSD_AMuxCH0_Disconnect(amuxCh);
            } 
            else
            {
                amuxCh &= ~ CapSense_CSD_CHANNEL1_FLAG;
                CapSense_CSD_AMuxCH1_Disconnect(amuxCh);
            }
            
        #else
            if (sensor < CapSense_CSD_TOTAL_SENSOR_COUNT__CH0) 
            {
                CapSense_CSD_AMuxCH0_Disconnect(sensor);
            } 
            else
            {
                CapSense_CSD_AMuxCH1_Disconnect(sensor - CapSense_CSD_TOTAL_SENSOR_COUNT__CH0);
            }
            
        #endif  /* CapSense_CSD_IS_COMPLEX_SCANSLOTS */
        
    #endif  /* CapSense_CSD_DESIGN_TYPE */
    
    /* Disconnect from DSI output */
	if(port == 15u)
	{
		port = 7u;
	}
    *CapSense_CSD_csTable[port] &= (uint8)~mask;
    
    /* Set sensor to inactive state */
    #if (CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD_CIS_GND)
        *CapSense_CSD_pcTable[sensor] = CapSense_CSD_PRT_PC_GND;
    #elif (CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD_CIS_HIGHZ)
        *CapSense_CSD_pcTable[sensor] = CapSense_CSD_PRT_PC_HIGHZ;
    #else
        *CapSense_CSD_pcTable[sensor] = CapSense_CSD_PRT_PC_SHIELD;
    #endif  /* (CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD_CIS_GND) */
}


/*******************************************************************************
* Function Name: CapSense_CSD_PreScan
********************************************************************************
*
* Summary:
*  Set required settings, enable sensor, remove Vref from AMUX and start the 
*  scanning process of the sensor.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_rbTable[] - used to store pointers to PC pin registers for 
*  every bleed resistor (Rb). Only available when Current Source is External 
*  resistor.
*
*******************************************************************************/
void CapSense_CSD_PreScan(uint8 sensor) CYREENTRANT
{
    /* Set Sensor Settings */
    CapSense_CSD_SetScanSlotSettings(sensor);
    
    /* Place disable interrupts here to eliminate influence on start of scanning */
    /* `#START CapSense_CSD_PreScan_DisableInt` */

    /* `#END` */
    
    /* Resets digital and pre-charge clocks */
    CapSense_CSD_CONTROL_REG |= CapSense_CSD_CTRL_SYNC_EN;
        
    #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
        #if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SOURCE)
            /* Disable Vref from AMux */
            #if (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS)
                CapSense_CSD_AMuxCH0_Disconnect(CapSense_CSD_AMuxCH0_VREF_CHANNEL);
            #else
                CapSense_CSD_BufCH0_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
            #endif  /* (CapSense_CSD_VREF_VDAC != CapSense_CSD_VREF_OPTIONS) */

            /* Enable Sensor */
            CapSense_CSD_EnableScanSlot(sensor);
            
        #elif (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK)
            /* Connect IDAC */
            CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_IDAC_CHANNEL);
            
            /* Enable Sensor */
            CapSense_CSD_EnableScanSlot(sensor);
                
            /* Disable CapSense Buffer */
            CapSense_CSD_BufCH0_CAPS_CFG0_REG &= (uint8)~CapSense_CSD_CSBUF_ENABLE;
            
        #else
            /* Connect DSI output to Rb */
            *CapSense_CSD_rbTable[CapSense_CSD_extRbCh0Cur] |= CapSense_CSD_BYP_MASK;
            
            /* Enable Sensor */
            CapSense_CSD_EnableScanSlot(sensor);
             
            /* Disable CapSense Buffer */
            CapSense_CSD_BufCH0_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
        
        #endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SOURCE) */
        
    #else

        if((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH0) != 0u)
        {
            #if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SOURCE)
                /* Disable Vref from AMux */
                #if (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS)
                    CapSense_CSD_AMuxCH0_Disconnect(CapSense_CSD_AMuxCH0_VREF_CHANNEL);
                #else
                    CapSense_CSD_BufCH0_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
                #endif  /* (CapSense_CSD_VREF_VDAC != CapSense_CSD_VREF_OPTIONS) */
                
                /* Enable Sensor */
                CapSense_CSD_EnableScanSlot(sensor);
                
            #elif (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK)
                /* Connect IDAC */
                CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_IDAC_CHANNEL);
                
                /* Enable Sensor */
                CapSense_CSD_EnableScanSlot(sensor);
                    
                /* Disable Vref from AMux */
                CapSense_CSD_BufCH0_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
                
            #else
                /* Connect DSI output to Rb */
                *CapSense_CSD_rbTable[CapSense_CSD_extRbCh0Cur] |= CapSense_CSD_BYP_MASK;
                
                /* Enable Sensor */
                CapSense_CSD_EnableScanSlot(sensor);
                    
                /* Disable Vref from AMux */
                CapSense_CSD_BufCH0_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
            
            #endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SOURCE) */
            
        }
        
        if((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH1) != 0u)
        {
            sensor += CapSense_CSD_TOTAL_SENSOR_COUNT__CH0;
            
            #if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SOURCE)
                /* Disable Vref from AMux */
                #if (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS)
                   CapSense_CSD_AMuxCH1_Disconnect(CapSense_CSD_AMuxCH1_VREF_CHANNEL);
                #else 
                    CapSense_CSD_BufCH1_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
                #endif  /* (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS) */
                
                /* Enable Sensor */
                CapSense_CSD_EnableScanSlot(sensor);
                
            #elif (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK)
                /* Connect IDAC */
                CapSense_CSD_AMuxCH1_Connect(CapSense_CSD_AMuxCH1_IDAC_CHANNEL);
                
                /* Enable Sensor */
                CapSense_CSD_EnableScanSlot(sensor);
                    
                /* Disable Vref from AMux */
                CapSense_CSD_BufCH1_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
                
            #else
                /* Connect DSI output to Rb */
                *CapSense_CSD_rbTable[CapSense_CSD_extRbCh1Cur] |= CapSense_CSD_BYP_MASK;
                
                /* Enable Sensor */
                CapSense_CSD_EnableScanSlot(sensor);
                
                /* Disable Vref from AMux */
                CapSense_CSD_BufCH1_CAPS_CFG0_REG &= ~CapSense_CSD_CSBUF_ENABLE;
            
            #endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SOURCE) */
        }
    
    #endif  /* (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN) */
    
    /* Start measurament, pre-charge clocks are running and PRS as well */
    CapSense_CSD_CONTROL_REG |= CapSense_CSD_CTRL_START;
    
    /* Place enable interrupts here to eliminate influence on start of scanning */
    /* `#START CapSense_CSD_PreScan_EnableInt` */

    /* `#END` */
}


#if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
    /*******************************************************************************
    * Function Name: CapSense_CSD_PostScan
    ********************************************************************************
    *
    * Summary:
    *  Store results of measurament in CapSense_CSD_SensorResult[] array,
    *  sets scan sensor in none sampling state, turn off Idac(Current Source IDAC),
    *  disconnect IDAC(Sink mode) or bleed resistor (Rb) and apply Vref on AMUX.
    *  Only one channel designs.
    *
    * Parameters:
    *  sensor:  Sensor number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_sensorRaw[] - used to store sensors raw data.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_CSD_PostScan(uint8 sensor) CYREENTRANT
    {
        /* Stop Capsensing and rearm sync */
        CapSense_CSD_CONTROL_REG &= (uint8)~(CapSense_CSD_CTRL_START | CapSense_CSD_CTRL_SYNC_EN);
        
        /* Read SlotResult from Raw Counter */
        #if (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
            CapSense_CSD_sensorRaw[sensor]  = CapSense_CSD_MEASURE_FULL_RANGE - 
                                                      CY_GET_REG16(CapSense_CSD_RAW_CH0_COUNTER_PTR);
        #else
            CapSense_CSD_sensorRaw[sensor]  = ((uint16) CapSense_CSD_RAW_CH0_COUNTER_HI_REG << 8u);
            CapSense_CSD_sensorRaw[sensor] |= (uint16) CapSense_CSD_RAW_CH0_COUNTER_LO_REG;
            CapSense_CSD_sensorRaw[sensor]  = CapSense_CSD_MEASURE_FULL_RANGE -
                                                      CapSense_CSD_sensorRaw[sensor];
        #endif  /* (CapSense_CSD_IMPLEMENTATION == CapSense_CSD_MEASURE_IMPLEMENTATION_FF) */
        
        /* Disable Sensor */
        CapSense_CSD_DisableScanSlot(sensor);
        
        #if(CapSense_CSD_CURRENT_SOURCE)
            /* Turn off IDAC */
            CapSense_CSD_IdacCH0_SetValue(CapSense_CSD_TURN_OFF_IDAC);
            #if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK)
                /* Disconnect IDAC */
                CapSense_CSD_AMuxCH0_Disconnect(CapSense_CSD_AMuxCH0_IDAC_CHANNEL);
            #endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK) */
        #else
            /* Disconnect DSI output from Rb */
            *CapSense_CSD_rbTable[CapSense_CSD_extRbCh0Cur] &= ~CapSense_CSD_BYP_MASK; 
        #endif  /* (CapSense_CSD_CURRENT_SOURCE)*/
            
        /* Enable Vref on AMUX */
        #if (CapSense_CSD_VREF_OPTIONS == CapSense_CSD_VREF_VDAC)
            CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_VREF_CHANNEL);
        #else
            CapSense_CSD_BufCH0_CAPS_CFG0_REG |= CapSense_CSD_CSBUF_ENABLE;
        #endif  /* (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS) */
    }
    
#else

    /*******************************************************************************
    * Function Name: CapSense_CSD_PostScan
    ********************************************************************************
    *
    * Summary:
    *  Store results of measurament in CapSense_CSD_SensorResult[] array,
    *  sets scan sensor in none sampling state, turn off Idac(Current Source IDAC),
    *  disconnect IDAC(Sink mode) or bleed resistor (Rb) and apply Vref on AMUX.
    *  Only used for channel 0 in two channes designs.
    *
    * Parameters:
    *  sensor:  Sensor number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_sensorRaw[] - used to store sensors raw data.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_CSD_PostScanCh0(uint8 sensor) CYREENTRANT
    {
        if (((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH0) == 0u) && 
            ((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH1) == 0u)) 
        {
            /* Stop Capsensing and rearm sync */
            CapSense_CSD_CONTROL_REG &= ~(CapSense_CSD_CTRL_START | CapSense_CSD_CTRL_SYNC_EN);
        }
        
        /* Read SlotResult from Raw Counter */
        #if (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
            CapSense_CSD_sensorRaw[sensor]  = CapSense_CSD_MEASURE_FULL_RANGE - 
                                                      CY_GET_REG16(CapSense_CSD_RAW_CH0_COUNTER_PTR);
        #else
            CapSense_CSD_sensorRaw[sensor]  = ((uint16) CapSense_CSD_RAW_CH0_COUNTER_HI_REG << 8u);
            CapSense_CSD_sensorRaw[sensor] |= (uint16) CapSense_CSD_RAW_CH0_COUNTER_LO_REG;
            CapSense_CSD_sensorRaw[sensor]  = CapSense_CSD_MEASURE_FULL_RANGE - 
                                                      CapSense_CSD_sensorRaw[sensor];
        #endif  /* (CapSense_CSD_IMPLEMENTATION_CH0 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)*/
        
        /* Disable Sensor */
        CapSense_CSD_DisableScanSlot(sensor);
        
        #if (CapSense_CSD_CURRENT_SOURCE)
            /* Turn off IDAC */
            CapSense_CSD_IdacCH0_SetValue(CapSense_CSD_TURN_OFF_IDAC);
            #if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK)
                /* Disconnect IDAC */
                CapSense_CSD_AMuxCH0_Disconnect(CapSense_CSD_AMuxCH0_IDAC_CHANNEL);
            #endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK) */
        #else
            /* Disconnect DSI output from Rb */
            *CapSense_CSD_rbTable[CapSense_CSD_extRbCh0Cur] &= ~CapSense_CSD_BYP_MASK; 
        #endif  /* (CapSense_CSD_CURRENT_SOURCE)*/
        
        /* Enable Vref on AMUX */
        #if (CapSense_CSD_VREF_OPTIONS == CapSense_CSD_VREF_VDAC)
            CapSense_CSD_AMuxCH0_Connect(CapSense_CSD_AMuxCH0_VREF_CHANNEL);
        #else
            CapSense_CSD_BufCH0_CAPS_CFG0_REG |= CapSense_CSD_CSBUF_ENABLE;
        #endif  /* (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS) */
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_CSD_PostScanCh1
    ********************************************************************************
    *
    * Summary:
    *  Store results of measurament in CapSense_CSD_SensorResult[] array,
    *  sets scan sensor in none sampling state, turn off Idac(Current Source IDAC), 
    *  disconnect IDAC(Sink mode) or bleed resistor (Rb) and apply Vref on AMUX.
    *  Only used for channel 1 in two channes designs.
    *
    * Parameters:
    *  sensor:  Sensor number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_sensorRaw[] - used to store sensors raw data.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_CSD_PostScanCh1(uint8 sensor) CYREENTRANT
    {
        if (((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH0) == 0u) && 
            ((CapSense_CSD_CONTROL_REG & CapSense_CSD_CTRL_WINDOW_EN__CH1) == 0u))
        {
            /* Stop Capsensing and rearm sync */
            CapSense_CSD_CONTROL_REG &= ~(CapSense_CSD_CTRL_START | CapSense_CSD_CTRL_SYNC_EN);
        }
        
        /* Read SlotResult from Raw Counter */
        #if (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)
            CapSense_CSD_sensorRaw[sensor]  = CapSense_CSD_MEASURE_FULL_RANGE - 
                                                      CY_GET_REG16(CapSense_CSD_RAW_CH1_COUNTER_PTR);
        #else
            CapSense_CSD_sensorRaw[sensor]  = ((uint16) CapSense_CSD_RAW_CH1_COUNTER_HI_REG << 8u);
            CapSense_CSD_sensorRaw[sensor] |= (uint16) CapSense_CSD_RAW_CH1_COUNTER_LO_REG;
            CapSense_CSD_sensorRaw[sensor]  = CapSense_CSD_MEASURE_FULL_RANGE - 
                                                      CapSense_CSD_sensorRaw[sensor];
        #endif  /* (CapSense_CSD_IMPLEMENTATION_CH1 == CapSense_CSD_MEASURE_IMPLEMENTATION_FF)*/
        
        /* Disable Sensor */
        CapSense_CSD_DisableScanSlot(sensor);
        
        #if (CapSense_CSD_CURRENT_SOURCE)
            /* Turn off IDAC */
            CapSense_CSD_IdacCH1_SetValue(CapSense_CSD_TURN_OFF_IDAC);
            #if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK)
                /* Disconnect IDAC */
                CapSense_CSD_AMuxCH1_Disconnect(CapSense_CSD_AMuxCH1_IDAC_CHANNEL);
            #endif  /* (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_IDAC_SINK) */
        #else
            /* Disconnect DSI output from Rb */
            *CapSense_CSD_rbTable[CapSense_CSD_extRbCh1Cur] &= ~CapSense_CSD_BYP_MASK; 
        #endif  /* (CapSense_CSD_CURRENT_SOURCE)*/

        /* Enable Vref on AMUX */
        #if (CapSense_CSD_VREF_OPTIONS == CapSense_CSD_VREF_VDAC)
            CapSense_CSD_AMuxCH1_Connect(CapSense_CSD_AMuxCH1_VREF_CHANNEL);
        #else
            CapSense_CSD_BufCH1_CAPS_CFG0_REG |= CapSense_CSD_CSBUF_ENABLE;
        #endif  /* (CapSense_CSD_VREF_VDAC == CapSense_CSD_VREF_OPTIONS) */
    }
    
#endif  /* CapSense_CSD_DESIGN_TYPE */


#if (CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB)
    /*******************************************************************************
    * Function Name:  CapSense_CSD_InitRb
    ********************************************************************************
    *
    * Summary:
    *  Sets all Rbleed resistor to High-Z mode. The first Rbleed resistor is active
    *  while next measure.
    *  This function is available only if Current Source is External Resistor.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    ********************************************************************************/
    void CapSense_CSD_InitRb(void) 
    {
        uint8 i;
        
        /* Disable all Rb */
        for(i = 0u; i < CapSense_CSD_TOTAL_RB_NUMBER; i++)
        {
            /* Make High-Z */
            *CapSense_CSD_rbTable[i] = CapSense_CSD_PRT_PC_HIGHZ;
        }
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_CSD_SetRBleed
    ********************************************************************************
    *
    * Summary:
    *  Sets the pin to use for the bleed resistor (Rb) connection. This function
    *  can be called at runtime to select the current Rb pin setting from those 
    *  defined customizer. The function overwrites the component parameter setting. 
    *  This function is available only if Current Source is External Resistor.
    * 
    * Parameters:
    *  rbleed:  Ordering number for bleed resistor terminal defined in CapSense
    *  customizer.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_extRbCh0Cur - used to store current number of active 
    *  bleed resistor (Rb) of channel 0.
    *  CapSense_CSD_extRbCh1Cur - used to store current number of active 
    *  bleed resistor (Rb) of channel 1.
    *  The active bleed resistor (Rb) pin will be used while next measurement  
    *  cycle.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_CSD_SetRBleed(uint8 rbleed) 
    {
        #if (CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN)
            CapSense_CSD_extRbCh0Cur = rbleed;
            
        #else
            if(rbleed < CapSense_CSD_TOTAL_RB_NUMBER__CH0)
            {
                CapSense_CSD_extRbCh0Cur = rbleed;
            }
            else
            {
                CapSense_CSD_extRbCh1Cur = (rbleed - CapSense_CSD_TOTAL_RB_NUMBER__CH0);   
            }
    
        #endif  /* CapSense_CSD_DESIGN_TYPE == CapSense_CSD_ONE_CHANNEL_DESIGN */ 
    }
#endif /* CapSense_CSD_CURRENT_SOURCE == CapSense_CSD_EXTERNAL_RB */ 

#if (CapSense_CSD_PRESCALER_OPTIONS)
    /*******************************************************************************
    * Function Name: CapSense_CSD_SetPrescaler
    ********************************************************************************
    *
    * Summary:
    *  Sets analog switch divider.
    *
    * Parameters:
    *  prescaler:  Sets prescaler divider values.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void CapSense_CSD_SetPrescaler(uint8 prescaler) CYREENTRANT
    {
        /* Set Prescaler */
        #if (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB)
            CapSense_CSD_PRESCALER_PERIOD_REG = prescaler;
            CapSense_CSD_PRESCALER_COMPARE_REG = (prescaler >> 1u);
        #elif (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_FF)
            CY_SET_REG16(CapSense_CSD_PRESCALER_PERIOD_PTR, (uint16) prescaler);
            CY_SET_REG16(CapSense_CSD_PRESCALER_COMPARE_PTR, (uint16) (prescaler >> 1u));
        #else
            /* Do nothing = config without prescaler */
        #endif  /* (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB) */
    }


    /*******************************************************************************
    * Function Name: CapSense_CSD_GetPrescaler
    ********************************************************************************
    *
    * Summary:
    *  Gets analog switch divider.
    *
    * Parameters:
    *  None
    *
    * Return:
    *   Returns the prescaler divider value.
    *
    *******************************************************************************/
    uint8 CapSense_CSD_GetPrescaler(void) 
    {
        uint8 prescaler = 0u;

        /* Get Prescaler */
        #if (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB)
            prescaler = CapSense_CSD_PRESCALER_PERIOD_REG;
            
        #elif (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_FF)
            prescaler = (uint8) CY_GET_REG16(CapSense_CSD_PRESCALER_PERIOD_PTR);
            
        #else
            /* Do nothing = config without prescaler */
        #endif  /* (CapSense_CSD_PRESCALER_OPTIONS == CapSense_CSD_PRESCALER_UDB) */
        
        return (prescaler);
    }
#endif  /* CapSense_CSD_PRESCALER_OPTIONS */


/*******************************************************************************
* Function Name: CapSense_CSD_SetScanSpeed
********************************************************************************
*
* Summary:
*  Sets ScanSpeed divider.
*
* Parameters:
*  scanspeed:  Sets ScanSpeed divider.
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_SetScanSpeed(uint8 scanSpeed) 
{
    CapSense_CSD_SCANSPEED_PERIOD_REG = scanSpeed; 
}


#if (CapSense_CSD_PRS_OPTIONS)
    /*******************************************************************************
    * Function Name: CapSense_CSD_SetAnalogSwitchesSource
    ********************************************************************************
    *
    * Summary:
    *  Selects the Analog switches source between PRS and prescaler. It is useful
    *  for sensor capacitance determination for sensors with low self-capacitance.
    *  This function is used in auto-tuning procedure.
    *
    * Parameters:
    *  src:  analog switches source:
    *           CapSense_CSD_ANALOG_SWITCHES_SRC_PRESCALER - selects prescaler
    *           CapSense_CSD_ANALOG_SWITCHES_SRC_PRS - selects PRS
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *******************************************************************************/
    void CapSense_CSD_SetAnalogSwitchesSource(uint8 src)
                      
    {
        if(src == CapSense_CSD_ANALOG_SWITCHES_SRC_PRESCALER)
        {
            CapSense_CSD_CONTROL_REG &= (uint8)~0x10u;
        }
        else
        {
            CapSense_CSD_CONTROL_REG |= 0x10u;
        }
    }
#endif /* (CapSense_CSD_PRS_OPTIONS) */

/* [] END OF FILE */
