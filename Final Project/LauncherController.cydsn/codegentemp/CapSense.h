/*******************************************************************************
* File Name: CapSense.h
* Version 3.40
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semicondu)ctor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end u)ser license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CapSense_H)
#define CY_CAPSENSE_CSD_CapSense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cydevice_trm.h"
#include "CyLib.h"


#include "CapSense_IntClock.h"

#include "CapSense_AMuxCH0.h"
#include "CapSense_CompCH0.h"
#include "CapSense_IdacCH0.h"




/***************************************
*   Condition compilation parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component CapSense_CSD_v3_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


#define CapSense_DESIGN_TYPE                (1u)

#define CapSense_CONNECT_INACTIVE_SNS       (0u)
#define CapSense_IS_COMPLEX_SCANSLOTS       (0u)

#define CapSense_CLOCK_SOURCE               (0u)

#define CapSense_CURRENT_SOURCE             (1u)
#define CapSense_IDAC_RANGE_VALUE           (4u)

#define CapSense_PRESCALER_OPTIONS          (2u)
#define CapSense_MULTIPLE_PRESCALER_ENABLED (1u)

#define CapSense_PRS_OPTIONS                (2u)
#define CapSense_SCANSPEED_VALUE            (7u)

#define CapSense_VREF_OPTIONS               (0u)

#define CapSense_WATER_PROOF                (0u)

#define CapSense_TUNING_METHOD              (2u)
#define CapSense_TUNER_API_GENERATE         (0u)

#define CapSense_IMPLEMENTATION_CH0         (1u)
#define CapSense_IMPLEMENTATION_CH1         (1u)

#define CapSense_GUARD_SENSOR               (0u)

/* Design types definitions */
#define CapSense_ONE_CHANNEL_DESIGN         (1u)
#define CapSense_TWO_CHANNELS_DESIGN        (2u)

/* Clock sources definitions */
#define CapSense_INTERNAL_CLOCK             (0u)
#define CapSense_EXTERNAL_CLOCK             (1u)

/* Current source definitions */
#define CapSense_EXTERNAL_RB                (0u)
#define CapSense_IDAC_SOURCE                (1u)
#define CapSense_IDAC_SINK                  (2u)

/* Prescaler option definitions */
#define CapSense_PRESCALER_NONE             (0u)
#define CapSense_PRESCALER_UDB              (1u)
#define CapSense_PRESCALER_FF               (2u)

/* Prs options definitions */
#define CapSense_PRS_NONE                   (0u)
#define CapSense_PRS_8BITS                  (1u)
#define CapSense_PRS_16BITS                 (2u)
#define CapSense_PRS_16BITS_4X              (3u)

/* Seed values */
#define CapSense_PRS8_SEED_VALUE            (0xFFu)
#define CapSense_PRS16_SEED_VALUE           (0xFFFFu)

/* Reference source types definitions */
#define CapSense_VREF_REFERENCE_1_024V      (0u)
#define CapSense_VREF_REFERENCE_1_2V        (1u)
#define CapSense_VREF_VDAC                  (2u)

/* Connection of inactive sensors definitions */
#define CapSense_CIS_GND                    (0u)
#define CapSense_CIS_HIGHZ                  (1u)
#define CapSense_CIS_SHIELD                 (2u)

/* Method of tunning */
#define CapSense_NO_TUNING                  (0u)
#define CapSense_MANUAL_TUNING              (1u)
#define CapSense_AUTO_TUNING                (2u)

/* Measure Channel implementation */
#define CapSense_MEASURE_IMPLEMENTATION_FF  (0u)
#define CapSense_MEASURE_IMPLEMENTATION_UDB (1u)

/* Guard sensor definition */
#define CapSense_GUARD_SENSOR_DISABLE       (0u)
#define CapSense_GUARD_SENSOR_ENABLE        (1u)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

    /* Set CONTROL_REG */
    uint8 ctrlReg;
} CapSense_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void CapSense_Init(void) ;
void CapSense_Enable(void) ;
void CapSense_Start(void) ;
void CapSense_Stop(void) ;
void CapSense_SaveConfig(void) ;
void CapSense_Sleep(void) ;
void CapSense_RestoreConfig(void) ;
void CapSense_Wakeup(void) ;
uint8 CapSense_IsBusy(void) ;
void CapSense_ScanSensor(uint8 sensor) ;
void CapSense_ScanEnabledWidgets(void) ;
void CapSense_SetScanSlotSettings(uint8 slot) CYREENTRANT;
uint16 CapSense_ReadSensorRaw(uint8 sensor) ;
void CapSense_ClearSensors(void) ;
void CapSense_EnableSensor(uint8 sensor) CYREENTRANT;
void CapSense_DisableSensor(uint8 sensor) CYREENTRANT;

void CapSense_SetAnalogSwitchesSource(uint8 src) ;

#if (CapSense_CURRENT_SOURCE == CapSense_EXTERNAL_RB)
    void CapSense_SetRBleed(uint8 rbeed) ;
#endif  /* (CapSense_CURRENT_SOURCE == CapSense_EXTERNAL_RB) */

/* Interrupt handler */
CY_ISR_PROTO(CapSense_IsrCH0_ISR);
#if (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
    CY_ISR_PROTO(CapSense_IsrCH1_ISR);
#endif  /* (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN) */

#if (CapSense_PRESCALER_OPTIONS)
    uint8 CapSense_GetPrescaler(void) ;
#endif /* (CapSense_PRESCALER_OPTIONS) */

/***************************************
*           API Constants
***************************************/

#define CapSense_TOTAL_SENSOR_COUNT            (7u)
#define CapSense_TOTAL_SCANSLOT_COUNT            (7u)
#define CapSense_TOTAL_RB_NUMBER            (1u)
#define CapSense_TOTAL_RB_NUMBER__CH0            (1u)

/* Define Sensors */
#define CapSense_SENSOR_BUTTON0__BTN    (0u)
#define CapSense_SENSOR_BUTTON1__BTN    (1u)
#define CapSense_SENSOR_LINEARSLIDER0_E0__LS    (2u)
#define CapSense_SENSOR_LINEARSLIDER0_E1__LS    (3u)
#define CapSense_SENSOR_LINEARSLIDER0_E2__LS    (4u)
#define CapSense_SENSOR_LINEARSLIDER0_E3__LS    (5u)
#define CapSense_SENSOR_LINEARSLIDER0_E4__LS    (6u)
/* AMux Cmod, Comparator and Idac Channels definitions */
#define CapSense_AMuxCH0_CMOD_CHANNEL          (7u)
#define CapSense_AMuxCH0_CMP_VP_CHANNEL        (8u)
#define CapSense_AMuxCH0_IDAC_CHANNEL          (9u)



/* Vdac value for Vref = Vdac */
#define CapSense_VREF_VDAC_VALUE            (64u)

/* Scan Speed Type */
#define CapSense_SCAN_SPEED_ULTRA_FAST      (0x01u)
#define CapSense_SCAN_SPEED_FAST            (0x03u)
#define CapSense_SCAN_SPEED_NORMAL          (0x07u)
#define CapSense_SCAN_SPEED_SLOW            (0x0Fu)

/* PWM Resolution */
#define CapSense_PWM_WINDOW_APPEND          (0xFEu)
#define CapSense_PWM_RESOLUTION_8_BITS      (0x00u)
#define CapSense_PWM_RESOLUTION_9_BITS      (0x01u)
#define CapSense_PWM_RESOLUTION_10_BITS     (0x03u)
#define CapSense_PWM_RESOLUTION_11_BITS     (0x07u)
#define CapSense_PWM_RESOLUTION_12_BITS     (0x0Fu)
#define CapSense_PWM_RESOLUTION_13_BITS     (0x1Fu)
#define CapSense_PWM_RESOLUTION_14_BITS     (0x3Fu)
#define CapSense_PWM_RESOLUTION_15_BITS     (0x7Fu)
#define CapSense_PWM_RESOLUTION_16_BITS     (0xFFu)

/* Software Status Register Bit Masks */
#define CapSense_SW_STS_BUSY                (0x01u)
/* Software Status Register Bit Masks */
#define CapSense_SW_CTRL_SINGLE_SCAN        (0x80u)

/* Init Idac current */
#define CapSense_TURN_OFF_IDAC              (0x00u)

/* Rbleed definitions */
#define CapSense_RBLEED1                    (0u)
#define CapSense_RBLEED2                    (1u)
#define CapSense_RBLEED3                    (2u)

/* Flag of complex scan slot */
#define CapSense_COMPLEX_SS_FLAG            (0x80u)
#define CapSense_CHANNEL1_FLAG              (0x80u)


#define CapSense_ANALOG_SWITCHES_SRC_PRESCALER (0x01u)
#define CapSense_ANALOG_SWITCHES_SRC_PRS       (0x02u)


/***************************************
*             Registers
***************************************/

/* Control REG */
#define CapSense_CONTROL_REG    (*(reg8 *) \
                                            CapSense_ClockGen_SyncCtrl_CtrlReg__CONTROL_REG )
#define CapSense_CONTROL_PTR    ( (reg8 *) \
                                            CapSense_ClockGen_SyncCtrl_CtrlReg__CONTROL_REG )

/* Clock Gen - ScanSpeed REGs definitions */
#define CapSense_SCANSPEED_AUX_CONTROL_REG (*(reg8 *) CapSense_ClockGen_ScanSpeed__CONTROL_AUX_CTL_REG )
#define CapSense_SCANSPEED_AUX_CONTROL_PTR ( (reg8 *) CapSense_ClockGen_ScanSpeed__CONTROL_AUX_CTL_REG )

#define CapSense_SCANSPEED_PERIOD_REG      (*(reg8 *) CapSense_ClockGen_ScanSpeed__PERIOD_REG )
#define CapSense_SCANSPEED_PERIOD_PTR      ( (reg8 *) CapSense_ClockGen_ScanSpeed__PERIOD_REG )

#define CapSense_SCANSPEED_COUNTER_REG     (*(reg8 *) CapSense_ClockGen_ScanSpeed__COUNT_REG )
#define CapSense_SCANSPEED_COUNTER_PTR     ( (reg8 *) CapSense_ClockGen_ScanSpeed__COUNT_REG )


/* Clock Gen - Prescaler REGs definitions */
#if (CapSense_PRESCALER_OPTIONS == CapSense_PRESCALER_UDB)
    #define CapSense_PRESCALER_PERIOD_REG       (*(reg8 *) CapSense_ClockGen_UDB_PrescalerDp_u0__D0_REG)
    #define CapSense_PRESCALER_PERIOD_PTR       ( (reg8 *) CapSense_ClockGen_UDB_PrescalerDp_u0__D0_REG)
    
    #define CapSense_PRESCALER_COMPARE_REG      (*(reg8 *) CapSense_ClockGen_UDB_PrescalerDp_u0__D1_REG)
    #define CapSense_PRESCALER_COMPARE_PTR      ( (reg8 *) CapSense_ClockGen_UDB_PrescalerDp_u0__D1_REG)
    
#elif (CapSense_PRESCALER_OPTIONS == CapSense_PRESCALER_FF)
    #define CapSense_PRESCALER_PERIOD_PTR       ( (reg16 *) CapSense_ClockGen_FF_Prescaler__PER0 )
    #define CapSense_PRESCALER_COMPARE_PTR      ( (reg16 *) CapSense_ClockGen_FF_Prescaler__CNT_CMP0 )
    
    #define CapSense_PRESCALER_CONTROL_REG      (*(reg8 *) CapSense_ClockGen_FF_Prescaler__CFG0 )
    #define CapSense_PRESCALER_CONTROL_PTR      ( (reg8 *) CapSense_ClockGen_FF_Prescaler__CFG0 )
    
    #if (CY_PSOC5A)
        #define CapSense_PRESCALER_CONTROL2_REG     (*(reg8 *) CapSense_ClockGen_FF_Prescaler__CFG1 )
        #define CapSense_PRESCALER_CONTROL2_PTR     ( (reg8 *) CapSense_ClockGen_FF_Prescaler__CFG1 )
    #else
        #define CapSense_PRESCALER_CONTROL2_REG     (*(reg8 *) CapSense_ClockGen_FF_Prescaler__CFG2 )
        #define CapSense_PRESCALER_CONTROL2_PTR     ( (reg8 *) CapSense_ClockGen_FF_Prescaler__CFG2 )
    #endif  /* (CY_PSOC5A) */
    
    #define CapSense_PRESCALER_ACT_PWRMGR_REG   (*(reg8 *) CapSense_ClockGen_FF_Prescaler__PM_ACT_CFG )
    #define CapSense_PRESCALER_ACT_PWRMGR_PTR   ( (reg8 *) CapSense_ClockGen_FF_Prescaler__PM_ACT_CFG )
    #define CapSense_PRESCALER_ACT_PWR_EN                 (CapSense_ClockGen_FF_Prescaler__PM_ACT_MSK )
    
    #define CapSense_PRESCALER_STBY_PWRMGR_REG  (*(reg8 *) CapSense_ClockGen_FF_Prescaler__PM_STBY_CFG )
    #define CapSense_PRESCALER_STBY_PWRMGR_PTR  ( (reg8 *) CapSense_ClockGen_FF_Prescaler__PM_STBY_CFG )
    #define CapSense_PRESCALER_STBY_PWR_EN                (CapSense_ClockGen_FF_Prescaler__PM_STBY_MSK )

#else
    /* No prescaler */
#endif  /* (CapSense_PRESCALER_OPTIONS == CapSense_PRESCALER_UDB) */

/* PRS */
#if (CapSense_PRS_OPTIONS == CapSense_PRS_8BITS)  
    /* Polynomial */
    #define CapSense_POLYNOM_REG        (*(reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__D0_REG )
    #define CapSense_POLYNOM_PTR        ( (reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__D0_REG )
    /* Seed */
    #define CapSense_SEED_REG           (*(reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__A0_REG )
    #define CapSense_SEED_PTR           ( (reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__A0_REG )
    /* Seed COPY */
    #define CapSense_SEED_COPY_REG      (*(reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__F0_REG )
    #define CapSense_SEED_COPY_PTR      ( (reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__F0_REG )
    /* Aux control */
    #define CapSense_AUX_CONTROL_A_REG  (*(reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__DP_AUX_CTL_REG )
    #define CapSense_AUX_CONTROL_A_PTR  ( (reg8 *) CapSense_ClockGen_sC8_PRSdp_u0__DP_AUX_CTL_REG )
        
#elif (CapSense_PRS_OPTIONS == CapSense_PRS_16BITS)
    /* Polynomial */
    #define CapSense_POLYNOM_REG        (*(reg16 *) CapSense_ClockGen_sC16_PRSdp_u0__D0_REG )
    #define CapSense_POLYNOM_PTR        ( (reg16 *) CapSense_ClockGen_sC16_PRSdp_u0__D0_REG )
    /* Seed */
    #define CapSense_SEED_REG           (*(reg16 *) CapSense_ClockGen_sC16_PRSdp_u0__A0_REG )
    #define CapSense_SEED_PTR           ( (reg16 *) CapSense_ClockGen_sC16_PRSdp_u0__A0_REG )
    /* Seed COPY */
    #define CapSense_SEED_COPY_REG      (*(reg16 *) CapSense_ClockGen_sC16_PRSdp_u0__F0_REG )
    #define CapSense_SEED_COPY_PTR      ( (reg16 *) CapSense_ClockGen_sC16_PRSdp_u0__F0_REG )
    /* Aux control */
    #define CapSense_AUX_CONTROL_A_REG  (*(reg8 *) CapSense_ClockGen_sC16_PRSdp_u0__DP_AUX_CTL_REG )
    #define CapSense_AUX_CONTROL_A_PTR  ( (reg8 *) CapSense_ClockGen_sC16_PRSdp_u0__DP_AUX_CTL_REG )
    
    #define CapSense_AUX_CONTROL_B_REG  (*(reg8 *) CapSense_ClockGen_sC16_PRSdp_u1__DP_AUX_CTL_REG )
    #define CapSense_AUX_CONTROL_B_PTR  ( (reg8 *) CapSense_ClockGen_sC16_PRSdp_u1__DP_AUX_CTL_REG )
    
#elif (CapSense_PRS_OPTIONS == CapSense_PRS_16BITS_4X)
    /* Polynomial */   
    #define CapSense_POLYNOM_A__D1_REG      (*(reg8 *) CapSense_ClockGen_b0_PRSdp_a__D1_REG )
    #define CapSense_POLYNOM_A__D1_PTR      ( (reg8 *) CapSense_ClockGen_b0_PRSdp_a__D1_REG )
    
    #define CapSense_POLYNOM_A__D0_REG      (*(reg8 *) CapSense_ClockGen_b0_PRSdp_a__D0_REG )
    #define CapSense_POLYNOM_A__D0_PTR      ( (reg8 *) CapSense_ClockGen_b0_PRSdp_a__D0_REG )
    /* Seed */
    #define CapSense_SEED_A__A1_REG         (*(reg8 *) CapSense_ClockGen_b0_PRSdp_a__A1_REG )
    #define CapSense_SEED_A__A1_PTR         ( (reg8 *) CapSense_ClockGen_b0_PRSdp_a__A1_REG )
    
    #define CapSense_SEED_A__A0_REG         (*(reg8 *) CapSense_ClockGen_b0_PRSdp_a__A0_REG )
    #define CapSense_SEED_A__A0_PTR         ( (reg8 *) CapSense_ClockGen_b0_PRSdp_a__A0_REG )
    /* Seed COPY */
    #define CapSense_SEED_COPY_A__F1_REG    (*(reg8 *) CapSense_ClockGen_b0_PRSdp_a__F1_REG )
    #define CapSense_SEED_COPY_A__F1_PTR    ( (reg8 *) CapSense_ClockGen_b0_PRSdp_a__F1_REG )
    
    #define CapSense_SEED_COPY_A__F0_REG    (*(reg8 *) CapSense_ClockGen_b0_PRSdp_a__F0_REG )
    #define CapSense_SEED_COPY_A__F0_PTR    ( (reg8 *) CapSense_ClockGen_b0_PRSdp_a__F0_REG )
    /* Aux control */
    #define CapSense_AUX_CONTROL_A_REG  (*(reg8 *) CapSense_ClockGen_b0_PRSdp_a__DP_AUX_CTL_REG )
    #define CapSense_AUX_CONTROL_A_PTR  ( (reg8 *) CapSense_ClockGen_b0_PRSdp_a__DP_AUX_CTL_REG )
    
#else
    /* No PRS */
#endif  /* (CapSense_PRS_OPTIONS == CapSense_PRS_8BITS)  */

/* Measure REGs  definitions */
#if (CapSense_IMPLEMENTATION_CH0 == CapSense_MEASURE_IMPLEMENTATION_FF)
    /* Window PWM */
    #define CapSense_PWM_CH0_PERIOD_PTR         ( (reg16 *) CapSense_MeasureCH0_FF_Window__PER0 )
    #define CapSense_PWM_CH0_COUNTER_PTR        ( (reg16 *) CapSense_MeasureCH0_FF_Window__CNT_CMP0 )
    
    #define CapSense_PWM_CH0_CONTROL_REG        (*(reg8 *) CapSense_MeasureCH0_FF_Window__CFG0 )
    #define CapSense_PWM_CH0_CONTROL_PTR        ( (reg8 *) CapSense_MeasureCH0_FF_Window__CFG0 )
    
    #define CapSense_PWM_CH0_CONTROL2_REG       (*(reg8 *) CapSense_MeasureCH0_FF_Window__CFG2 )
    #define CapSense_PWM_CH0_CONTROL2_PTR       ( (reg8 *) CapSense_MeasureCH0_FF_Window__CFG2 )
	
    #define CapSense_PWM_CH0_ACT_PWRMGR_REG     (*(reg8 *) CapSense_MeasureCH0_FF_Window__PM_ACT_CFG )
    #define CapSense_PWM_CH0_ACT_PWRMGR_PTR     ( (reg8 *) CapSense_MeasureCH0_FF_Window__PM_ACT_CFG )
    #define CapSense_PWM_CH0_ACT_PWR_EN                   (CapSense_MeasureCH0_FF_Window__PM_ACT_MSK )
    
    #define CapSense_PWM_CH0_STBY_PWRMGR_REG    (*(reg8 *) CapSense_MeasureCH0_FF_Window__PM_STBY_CFG )
    #define CapSense_PWM_CH0_STBY_PWRMGR_PTR    ( (reg8 *) CapSense_MeasureCH0_FF_Window__PM_STBY_CFG )
    #define CapSense_PWM_CH0_STBY_PWR_EN                  (CapSense_MeasureCH0_FF_Window__PM_STBY_MSK )
    
    /* Raw Counter */
    #define CapSense_RAW_CH0_PERIOD_PTR         ( (reg16 *) CapSense_MeasureCH0_FF_Counter__PER0 )
    #define CapSense_RAW_CH0_COUNTER_PTR        ( (reg16 *) CapSense_MeasureCH0_FF_Counter__CNT_CMP0 )
    
    #define CapSense_RAW_CH0_CONTROL_REG        (*(reg8 *) CapSense_MeasureCH0_FF_Counter__CFG0 )
    #define CapSense_RAW_CH0_CONTROL_PTR        ( (reg8 *) CapSense_MeasureCH0_FF_Counter__CFG0 )
    

    #define CapSense_RAW_CH0_CONTROL2_REG   (*(reg8 *) CapSense_MeasureCH0_FF_Counter__CFG2 )
    #define CapSense_RAW_CH0_CONTROL2_PTR   ( (reg8 *) CapSense_MeasureCH0_FF_Counter__CFG2 )

    
    #define CapSense_RAW_CH0_ACT_PWRMGR_REG     (*(reg8 *) CapSense_MeasureCH0_FF_Counter__PM_ACT_CFG )
    #define CapSense_RAW_CH0_ACT_PWRMGR_PTR     ( (reg8 *) CapSense_MeasureCH0_FF_Counter__PM_ACT_CFG )
    #define CapSense_RAW_CH0_ACT_PWR_EN                   (CapSense_MeasureCH0_FF_Counter__PM_ACT_MSK )
    
    #define CapSense_RAW_CH0_STBY_PWRMGR_REG    (*(reg8 *) CapSense_MeasureCH0_FF_Counter__PM_STBY_CFG )
    #define CapSense_RAW_CH0_STBY_PWRMGR_PTR    ( (reg8 *) CapSense_MeasureCH0_FF_Counter__PM_STBY_CFG )
    #define CapSense_RAW_CH0_STBY_PWR_EN                  (CapSense_MeasureCH0_FF_Counter__PM_STBY_MSK )
#else
     /* Window PWM */
    #define CapSense_PWM_CH0_COUNTER_LO_REG     (*(reg8 *) CapSense_MeasureCH0_UDB_Window_u0__A0_REG )
    #define CapSense_PWM_CH0_COUNTER_LO_PTR     ( (reg8 *) CapSense_MeasureCH0_UDB_Window_u0__A0_REG )
    
    #define CapSense_PWM_CH0_COUNTER_HI_REG     (*(reg8 *) CapSense_MeasureCH0_UDB_Window_u0__A1_REG )
    #define CapSense_PWM_CH0_COUNTER_HI_PTR     ( (reg8 *) CapSense_MeasureCH0_UDB_Window_u0__A1_REG )
    
    #define CapSense_PWM_CH0_PERIOD_LO_REG      (*(reg8 *) CapSense_MeasureCH0_UDB_Window_u0__F0_REG )
    #define CapSense_PWM_CH0_PERIOD_LO_PTR      ( (reg8 *) CapSense_MeasureCH0_UDB_Window_u0__F0_REG )
    
    #define CapSense_PWM_CH0_PERIOD_HI_REG      (*(reg8 *) CapSense_MeasureCH0_UDB_Window_u0__F1_REG )
    #define CapSense_PWM_CH0_PERIOD_HI_PTR      ( (reg8 *) CapSense_MeasureCH0_UDB_Window_u0__F1_REG )
    
    #define CapSense_PWM_CH0_ADD_VALUE_REG      (*(reg8 *) CapSense_MeasureCH0_UDB_Window_u0__D0_REG )
    #define CapSense_PWM_CH0_ADD_VALUE_PTR      ( (reg8 *) CapSense_MeasureCH0_UDB_Window_u0__D0_REG )
    
    #define CapSense_PWM_CH0_AUX_CONTROL_REG    (*(reg8 *) \
                                                            CapSense_MeasureCH0_UDB_Window_u0__DP_AUX_CTL_REG )
    #define CapSense_PWM_CH0_AUX_CONTROL_PTR    ( (reg8 *) \
                                                            CapSense_MeasureCH0_UDB_Window_u0__DP_AUX_CTL_REG )
    
    /* Raw Counter */
    #define CapSense_RAW_CH0_COUNTER_LO_REG      (*(reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__A0_REG )
    #define CapSense_RAW_CH0_COUNTER_LO_PTR      ( (reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__A0_REG )
    
    #define CapSense_RAW_CH0_COUNTER_HI_REG      (*(reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__A1_REG )
    #define CapSense_RAW_CH0_COUNTER_HI_PTR      ( (reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__A1_REG )
    
    #define CapSense_RAW_CH0_PERIOD_LO_REG       (*(reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__F0_REG )
    #define CapSense_RAW_CH0_PERIOD_LO_PTR       ( (reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__F0_REG )
    
    #define CapSense_RAW_CH0_PERIOD_HI_REG       (*(reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__F1_REG )
    #define CapSense_RAW_CH0_PERIOD_HI_PTR       ( (reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__F1_REG )
    
    #define CapSense_RAW_CH0_ADD_VALUE_REG       (*(reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__D0_REG )
    #define CapSense_RAW_CH0_ADD_VALUE_PTR       ( (reg8 *) CapSense_MeasureCH0_UDB_Counter_u0__D0_REG )
    
    #define CapSense_RAW_CH0_AUX_CONTROL_REG     (*(reg8 *) \
                                                            CapSense_MeasureCH0_UDB_Counter_u0__DP_AUX_CTL_REG )
    #define CapSense_RAW_CH0_AUX_CONTROL_PTR     ( (reg8 *) \
                                                            CapSense_MeasureCH0_UDB_Counter_u0__DP_AUX_CTL_REG )

#endif  /* (CapSense_IMPLEMENTATION_CH0 == CapSense_MEASURE_IMPLEMENTATION_FF) */
    
#if (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
    #if (CapSense_IMPLEMENTATION_CH1 == CapSense_MEASURE_IMPLEMENTATION_FF)
        /* Window PWM */
        #define CapSense_PWM_CH1_PERIOD_PTR        ( (reg16 *) CapSense_MeasureCH1_FF_Window__PER0 )
        #define CapSense_PWM_CH1_COUNTER_PTR       ( (reg16 *) CapSense_MeasureCH1_FF_Window__CNT_CMP0 )
        
        #define CapSense_PWM_CH1_CONTROL_REG        (*(reg8 *) CapSense_MeasureCH1_FF_Window__CFG0 )
        #define CapSense_PWM_CH1_CONTROL_PTR        ( (reg8 *) CapSense_MeasureCH1_FF_Window__CFG0 )
        
        #define CapSense_PWM_CH1_CONTROL2_REG   (*(reg8 *) CapSense_MeasureCH1_FF_Window__CFG2 )
        #define CapSense_PWM_CH1_CONTROL2_PTR   ( (reg8 *) CapSense_MeasureCH1_FF_Window__CFG2 )
        
        #define CapSense_PWM_CH1_ACT_PWRMGR_REG   (*(reg8 *) CapSense_MeasureCH1_FF_Window__PM_ACT_CFG )
        #define CapSense_PWM_CH1_ACT_PWRMGR_PTR   ( (reg8 *) CapSense_MeasureCH1_FF_Window__PM_ACT_CFG )
        #define CapSense_PWM_CH1_ACT_PWR_EN                 (CapSense_MeasureCH1_FF_Window__PM_ACT_MSK )
        
        #define CapSense_PWM_CH1_STBY_PWRMGR_REG (*(reg8 *) CapSense_MeasureCH1_FF_Window__PM_STBY_CFG )
        #define CapSense_PWM_CH1_STBY_PWRMGR_PTR ( (reg8 *) CapSense_MeasureCH1_FF_Window__PM_STBY_CFG )
        #define CapSense_PWM_CH1_STBY_PWR_EN               (CapSense_MeasureCH1_FF_Window__PM_STBY_MSK )
            
        /* Raw Counter */
        #define CapSense_RAW_CH1_PERIOD_PTR       ( (reg16 *) CapSense_MeasureCH1_FF_Counter__PER0 )
        #define CapSense_RAW_CH1_COUNTER_PTR      ( (reg16 *) CapSense_MeasureCH1_FF_Counter__CNT_CMP0 )
        
        #define CapSense_RAW_CH1_CONTROL_REG      (*(reg8 *) CapSense_MeasureCH1_FF_Counter__CFG0 )
        #define CapSense_RAW_CH1_CONTROL_PTR      ( (reg8 *) CapSense_MeasureCH1_FF_Counter__CFG0 )
        
        #define CapSense_RAW_CH1_CONTROL2_REG   (*(reg8 *) CapSense_MeasureCH1_FF_Counter__CFG2 )
        #define CapSense_RAW_CH1_CONTROL2_PTR   ( (reg8 *) CapSense_MeasureCH1_FF_Counter__CFG2 )
        
        #define CapSense_RAW_CH1_ACT_PWRMGR_REG  (*(reg8 *) CapSense_MeasureCH1_FF_Counter__PM_ACT_CFG )
        #define CapSense_RAW_CH1_ACT_PWRMGR_PTR  ( (reg8 *) CapSense_MeasureCH1_FF_Counter__PM_ACT_CFG )
        #define CapSense_RAW_CH1_ACT_PWR_EN                (CapSense_MeasureCH1_FF_Counter__PM_ACT_MSK )
        
        #define CapSense_RAW_CH1_STBY_PWRMGR_REG (*(reg8 *) CapSense_MeasureCH1_FF_Counter__PM_STBY_CFG)
        #define CapSense_RAW_CH1_STBY_PWRMGR_PTR ( (reg8 *) CapSense_MeasureCH1_FF_Counter__PM_STBY_CFG)
        #define CapSense_RAW_CH1_STBY_PWR_EN               (CapSense_MeasureCH1_FF_Counter__PM_STBY_MSK)
    
    #else
        /* Window PWM */
        #define CapSense_PWM_CH1_COUNTER_LO_REG   (*(reg8 *) CapSense_MeasureCH1_UDB_Window_u0__A0_REG )
        #define CapSense_PWM_CH1_COUNTER_LO_PTR   ( (reg8 *) CapSense_MeasureCH1_UDB_Window_u0__A0_REG )
        
        #define CapSense_PWM_CH1_COUNTER_HI_REG   (*(reg8 *) CapSense_MeasureCH1_UDB_Window_u0__A1_REG )
        #define CapSense_PWM_CH1_COUNTER_HI_PTR   ( (reg8 *) CapSense_MeasureCH1_UDB_Window_u0__A1_REG )
        
        #define CapSense_PWM_CH1_PERIOD_LO_REG    (*(reg8 *) CapSense_MeasureCH1_UDB_Window_u0__F0_REG )
        #define CapSense_PWM_CH1_PERIOD_LO_PTR    ( (reg8 *) CapSense_MeasureCH1_UDB_Window_u0__F0_REG )
        
        #define CapSense_PWM_CH1_PERIOD_HI_REG    (*(reg8 *) CapSense_MeasureCH1_UDB_Window_u0__F1_REG )
        #define CapSense_PWM_CH1_PERIOD_HI_PTR    ( (reg8 *) CapSense_MeasureCH1_UDB_Window_u0__F1_REG )
        
        #define CapSense_PWM_CH1_ADD_VALUE_REG    (*(reg8 *) CapSense_MeasureCH1_UDB_Window_u0__D0_REG )
        #define CapSense_PWM_CH1_ADD_VALUE_PTR    ( (reg8 *) CapSense_MeasureCH1_UDB_Window_u0__D0_REG )
        
        #define CapSense_PWM_CH1_AUX_CONTROL_REG  (*(reg8 *) \
                                                            CapSense_MeasureCH1_UDB_Window_u0__DP_AUX_CTL_REG )
        #define CapSense_PWM_CH1_AUX_CONTROL_PTR  ( (reg8 *) \
                                                            CapSense_MeasureCH1_UDB_Window_u0__DP_AUX_CTL_REG )
        
        /* Raw Counter */
        #define CapSense_RAW_CH1_COUNTER_LO_REG  (*(reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__A0_REG )
        #define CapSense_RAW_CH1_COUNTER_LO_PTR  ( (reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__A0_REG )
        
        #define CapSense_RAW_CH1_COUNTER_HI_REG  (*(reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__A1_REG )
        #define CapSense_RAW_CH1_COUNTER_HI_PTR  ( (reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__A1_REG )
        
        #define CapSense_RAW_CH1_PERIOD_LO_REG   (*(reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__F0_REG )
        #define CapSense_RAW_CH1_PERIOD_LO_PTR   ( (reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__F0_REG )
        
        #define CapSense_RAW_CH1_PERIOD_HI_REG   (*(reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__F1_REG )
        #define CapSense_RAW_CH1_PERIOD_HI_PTR   ( (reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__F1_REG )
        
        #define CapSense_RAW_CH1_ADD_VALUE_REG   (*(reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__D0_REG )
        #define CapSense_RAW_CH1_ADD_VALUE_PTR   ( (reg8 *) CapSense_MeasureCH1_UDB_Counter_u0__D0_REG )
        
        #define CapSense_RAW_CH1_AUX_CONTROL_REG  (*(reg8 *) \
                                                            CapSense_MeasureCH1_UDB_Counter_u0__DP_AUX_CTL_REG )
        #define CapSense_RAW_CH1_AUX_CONTROL_PTR  ( (reg8 *) \
                                                            CapSense_MeasureCH1_UDB_Counter_u0__DP_AUX_CTL_REG )
        
    #endif  /* CapSense_DESIGN_TYPE */
    
#endif  /* CapSense_DESIGN_TYPE */


/* CapSense Buffer REGs definitions */
#define CapSense_BufCH0_CAPS_CFG0_REG           (*(reg8 *) CapSense_BufCH0__CFG0 )
#define CapSense_BufCH0_CAPS_CFG0_PTR           ( (reg8 *) CapSense_BufCH0__CFG0 )

#define CapSense_BufCH0_CAPS_CFG1_REG           (*(reg8 *) CapSense_BufCH0__CFG1 )
#define CapSense_BufCH0_CAPS_CFG1_PTR           ( (reg8 *) CapSense_BufCH0__CFG1 )

#define CapSense_BufCH0_ACT_PWRMGR_REG          (*(reg8 *) CapSense_BufCH0__PM_ACT_CFG )
#define CapSense_BufCH0_ACT_PWRMGR_PTR          ( (reg8 *) CapSense_BufCH0__PM_ACT_CFG )
#define CapSense_BufCH0_ACT_PWR_EN                        (CapSense_BufCH0__PM_ACT_MSK )

#define CapSense_BufCH0_STBY_PWRMGR_REG         (*(reg8 *) CapSense_BufCH0__PM_STBY_CFG )
#define CapSense_BufCH0_STBY_PWRMGR_PTR         ( (reg8 *) CapSense_BufCH0__PM_STBY_CFG )
#define CapSense_BufCH0_STBY_PWR_EN                       (CapSense_BufCH0__PM_STBY_MSK )

#if (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
    #define CapSense_BufCH1_CAPS_CFG0_REG       (*(reg8 *) CapSense_BufCH1__CFG0 )
    #define CapSense_BufCH1_CAPS_CFG0_PTR       ( (reg8 *) CapSense_BufCH1__CFG0 )
    
    #define CapSense_BufCH1_CAPS_CFG1_REG       (*(reg8 *) CapSense_BufCH1__CFG1 )
    #define CapSense_BufCH1_CAPS_CFG1_PTR       ( (reg8 *) CapSense_BufCH1__CFG1 )
    
    #define CapSense_BufCH1_ACT_PWRMGR_REG      (*(reg8 *) CapSense_BufCH1__PM_ACT_CFG )
    #define CapSense_BufCH1_ACT_PWRMGR_PTR      ( (reg8 *) CapSense_BufCH1__PM_ACT_CFG )
    #define CapSense_BufCH1_ACT_PWR_EN                    (CapSense_BufCH1__PM_ACT_MSK )
    
    #define CapSense_BufCH1_STBY_PWRMGR_REG     (*(reg8 *) CapSense_BufCH1__PM_STBY_CFG )
    #define CapSense_BufCH1_STBY_PWRMGR_PTR     ( (reg8 *) CapSense_BufCH1__PM_STBY_CFG )
    #define CapSense_BufCH1_STBY_PWR_EN                   (CapSense_BufCH1__PM_STBY_MSK )
#endif  /* CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN */

/* ISR Number and Priority to work with CyLib functions */
#define CapSense_IsrCH0_ISR_NUMBER        (CapSense_IsrCH0__INTC_NUMBER)
#define CapSense_IsrCH0_ISR_PRIORITY      (CapSense_IsrCH0__INTC_PRIOR_NUM)

#if (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
    #define CapSense_IsrCH1_ISR_NUMBER        (CapSense_IsrCH1__INTC_NUMBER)
    #define CapSense_IsrCH1_ISR_PRIORITY      (CapSense_IsrCH1__INTC_PRIOR_NUM)
#endif /* CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN */


/***************************************
*       Register Constants
***************************************/

/* Control Register definitions */
#define CapSense_CTRL_SYNC_EN                       (0x01u)
#define CapSense_CTRL_START                         (0x02u)
#define CapSense_CTRL_WINDOW_EN__CH0                (0x04u)
#define CapSense_CTRL_WINDOW_EN__CH1                (0x08u)
/* Addtional bit to verify if component is enalbed */
#define CapSense_CTRL_CAPSENSE_EN                   (0x80u)

#define CapSense_IS_CAPSENSE_ENABLE(reg)            ( ((reg) & CapSense_CTRL_CAPSENSE_EN) != 0u )

/* ClockGen defines */
/* Prescaler */
#define CapSense_PRESCALER_CTRL_ENABLE          (0x01u)
#define CapSense_PRESCALER_CTRL_MODE_CMP        (0x02u) 

#define CapSense_PRESCALER_CTRL_CMP_MODE_SHIFT  (0x04u)

#define CapSense_PRESCALER_CTRL_CMP_LESS_EQ         (0x02u << CapSense_PRESCALER_CTRL_CMP_MODE_SHIFT)

/* Set PRS polynomial */
#define CapSense_PRS8_DEFAULT_POLYNOM           (0xB8u)
#define CapSense_PRS16_DEFAULT_POLYNOM          (0xB400u)

/* Scan Speed */
#define CapSense_SCANSPEED_CTRL_ENABLE          (0x20u)

/* Measure defines */
/* FF Timers */
#define CapSense_MEASURE_FULL_RANGE             (0xFFFFu)
#define CapSense_MEASURE_FULL_RANGE_LOW         (0xFFu)
#define CapSense_MEASURE_CTRL_ENABLE            (0x01u)

#define CapSense_MEASURE_CTRL_MODE_SHIFT        (0x00u)


#define CapSense_MEASURE_CTRL_PULSEWIDTH        (0x01u << CapSense_MEASURE_CTRL_MODE_SHIFT)

/* UDB timers */
#define CapSense_AUXCTRL_FIFO_SINGLE_REG        (0x03u)
 
/* Masks of PTR PC Register */
#define CapSense_DR_MASK            (0x01u)
#define CapSense_DM0_MASK           (0x02u)
#define CapSense_DM1_MASK           (0x04u)
#define CapSense_DM2_MASK           (0x08u)
#define CapSense_BYP_MASK           (0x80u)

#define CapSense_PRT_PC_GND         (CapSense_DM2_MASK)
#define CapSense_PRT_PC_HIGHZ       (CapSense_DM2_MASK |CapSense_DR_MASK)
#define CapSense_PRT_PC_SHIELD      (CapSense_DM2_MASK | CapSense_DM1_MASK | \
                                             CapSense_BYP_MASK)

/* CapSense Buffer definitions */
#define CapSense_CSBUF_BOOST_ENABLE         (0x02u)
#define CapSense_CSBUF_ENABLE               (0x01u)

/* Define direction of Current - Souce as Sink */
#if (CapSense_CURRENT_SOURCE == CapSense_IDAC_SOURCE)
    #define CapSense_IdacCH0_IDIR      (CapSense_IdacCH0_SOURCE)
    #define CapSense_IdacCH1_IDIR      (CapSense_IdacCH1_SOURCE)
#elif (CapSense_CURRENT_SOURCE == CapSense_IDAC_SINK)
    #define CapSense_IdacCH0_IDIR      (CapSense_IdacCH0_SINK)
    #define CapSense_IdacCH1_IDIR      (CapSense_IdacCH1_SINK)
#else
    /* No Idac - Rb selected */
#endif  /* (CapSense_CURRENT_SOURCE == CapSense_IDAC_SOURCE) */


/* Rb init function */
#if (CapSense_CURRENT_SOURCE == CapSense_EXTERNAL_RB)
    void CapSense_InitRb(void);
#endif /* End CapSense_CURRENT_SOURCE */ 

#if (CapSense_IS_COMPLEX_SCANSLOTS)
    void CapSense_EnableScanSlot(uint8 slot) CYREENTRANT;
    void CapSense_DisableScanSlot(uint8 slot) CYREENTRANT;
    
#else
    #define CapSense_EnableScanSlot(slot)   CapSense_EnableSensor(slot)
    #define CapSense_DisableScanSlot(slot)  CapSense_DisableSensor(slot)

#endif  /* End CapSense_IS_COMPLEX_SCANSLOTS */

/* Helper functions - do nto part of public interface*/

/* Find next sensor for One Channel design */
#if (CapSense_DESIGN_TYPE == CapSense_ONE_CHANNEL_DESIGN)
    uint8 CapSense_FindNextSensor(uint8 snsIndex) CYREENTRANT;
#endif  /* End CapSense_DESIGN_TYPE */

/* Find next pair for Two Channels design */
 #if (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
    uint8 CapSense_FindNextPair(uint8 snsIndex) CYREENTRANT;
#endif  /* End CapSense_DESIGN_TYPE */

/* Start and Compete the scan */
void CapSense_PreScan(uint8 sensor) CYREENTRANT;
#if (CapSense_DESIGN_TYPE == CapSense_ONE_CHANNEL_DESIGN)
    void CapSense_PostScan(uint8 sensor) CYREENTRANT;
#else
    void CapSense_PostScanCh0(uint8 sensor) CYREENTRANT;
    void CapSense_PostScanCh1(uint8 sensor) CYREENTRANT;
#endif  /* End CapSense_DESIGN_TYPE */

#if (CapSense_PRESCALER_OPTIONS)
    void CapSense_SetPrescaler(uint8 prescaler) CYREENTRANT;
#endif  /* End CapSense_PRESCALER_OPTIONS */

void CapSense_SetScanSpeed(uint8 scanSpeed) ;

/* SmartSense functions */
#if (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)
    extern uint8 CapSense_lowLevelTuningDone;
    extern void CapSense_AutoTune(void) ;
#endif /* End (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */

/* Global software variables */
extern volatile uint8 CapSense_csv;            /* CapSense CSD status, control variable */
extern volatile uint8 CapSense_sensorIndex;    /* Index of scannig sensor */

#if (CapSense_CURRENT_SOURCE == CapSense_EXTERNAL_RB)
    extern uint8  CapSense_extRbCh0Cur;
    #if (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
        extern uint8  CapSense_extRbCh1Cur;
    #endif /* (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)*/ 
#endif /* (CapSense_CURRENT_SOURCE == CapSense_EXTERNAL_RB) */ 
        
/* Global array of Raw Counts */
extern uint16 CapSense_sensorRaw[CapSense_TOTAL_SENSOR_COUNT];


extern CapSense_BACKUP_STRUCT CapSense_backup;

/****************************************************************************************
*       Obsolete definitions. Not recommended to use. Will be removed in future releases.
*****************************************************************************************/

/* Auto Tuning defualt raw counts value */
#define CapSense_DEFUALT_RAW_COUNTS_VALUE    (384u)

/* IDAC_CR0 registers save/restore flags */
#define CapSense_IdacCH0_RESTORE_CFG (1u)
#define CapSense_IdacCH1_RESTORE_CFG (2u)
/* DAC_CR0 register value when IDAC is stopped*/
#define CapSense_IDAC_STOP_CR0_VAL   (0x1Eu)

/* Idac SetRange */
#define CapSense_IDAC_RANGE_MASK            (0x0Cu)
#define CapSense_IDAC_RANGE_32uA            (0x00u)
#define CapSense_IDAC_RANGE_255uA           (0x04u)
#define CapSense_IDAC_RANGE_2mA             (0x08u)

/* CR0 IDAC Control Register 0 definitions */
/* Bit Field DAC_MODE */
#define CapSense_IDAC_MODE_MASK         (0x10u)
#define CapSense_IDAC_MODE_V            (0x00u)
#define CapSense_IDAC_MODE_I            (0x10u)

/* CR1 Idac Control Register 1 definitions */
/* Bit Field  DAC_I_DIR */
#define CapSense_IDAC_IDIR_MASK         (0x04u)
#define CapSense_IDAC_IDIR_SINK         (0x04u)
#define CapSense_IDAC_IDIR_SRC          (0x00u)

/* Bit Field  DAC_MX_IOFF_SRC */
#define CapSense_IDAC_IDIR_CTL_MASK     (0x02u)
#define CapSense_IDAC_IDIR_CTL_REG      (0x00u)
#define CapSense_IDAC_IDIR_CTL_UDB      (0x02u)

/* Obsolete names of variables */
//#define CapSense_SensorRaw              CapSense_sensorRaw
//#define CapSense_SensorEnableMask       CapSense_sensorEnableMask
//#define CapSense_AnalogSwitchDivider    CapSense_analogSwitchDivider


#endif /* CY_CAPSENSE_CSD_CapSense_H */

 /* [] END OF FILE */
