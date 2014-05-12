/*******************************************************************************
* File Name: CapSense_CSHL.h
* Version 3.40
*
* Description:
*  This file provides constants and parameter values for the High Level APIs
*  for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CSHL_CapSense_H)
#define CY_CAPSENSE_CSD_CSHL_CapSense_H

#include "CapSense.h"


/***************************************
*   Condition compilation parameters
***************************************/

#define CapSense_SIGNAL_SIZE                (8u)
#define CapSense_AUTO_RESET                 (0u)
#define CapSense_RAW_FILTER_MASK            (8u)

/* Signal size definition */
#define CapSense_SIGNAL_SIZE_UINT8          (8u)
#define CapSense_SIGNAL_SIZE_UINT16         (16u)

/* Auto reset definition */
#define CapSense_AUTO_RESET_DISABLE         (0u)
#define CapSense_AUTO_RESET_ENABLE          (1u)

/* Mask for RAW and POS filters */
#define CapSense_MEDIAN_FILTER              (0x01u)
#define CapSense_AVERAGING_FILTER           (0x02u)
#define CapSense_IIR2_FILTER                (0x04u)
#define CapSense_IIR4_FILTER                (0x08u)
#define CapSense_JITTER_FILTER              (0x10u)
#define CapSense_IIR8_FILTER                (0x20u)
#define CapSense_IIR16_FILTER               (0x40u)


/***************************************
*           API Constants
***************************************/

/* Widgets constants definition */
#define CapSense_LINEARSLIDER0__LS        (0u)
#define CapSense_BUTTON0__BTN        (1u)
#define CapSense_BUTTON1__BTN        (2u)

#define CapSense_TOTAL_DIPLEXED_SLIDERS_COUNT        (0u)
#define CapSense_TOTAL_LINEAR_SLIDERS_COUNT          (1u)
#define CapSense_TOTAL_RADIAL_SLIDERS_COUNT          (0u)
#define CapSense_TOTAL_TOUCH_PADS_COUNT              (0u)
#define CapSense_TOTAL_BUTTONS_COUNT                 (2u)
#define CapSense_TOTAL_MATRIX_BUTTONS_COUNT          (0u)
#define CapSense_TOTAL_GENERICS_COUNT                (0u)

#define CapSense_POS_FILTERS_MASK        (8u)
#define CapSense_LINEAR_SLIDERS_POS_FILTERS_MASK        (8u)
#define CapSense_RADIAL_SLIDERS_POS_FILTERS_MASK        (0u)
#define CapSense_TOUCH_PADS_POS_FILTERS_MASK        (0u)

#define CapSense_UNUSED_DEBOUNCE_COUNTER_INDEX   (2u)


#define CapSense_END_OF_SLIDERS_INDEX   (0u)
#define CapSense_END_OF_TOUCH_PAD_INDEX   (0u)
#define CapSense_END_OF_BUTTONS_INDEX   (2u)
#define CapSense_END_OF_MATRIX_BUTTONS_INDEX   (2u)
#define CapSense_END_OF_WIDGETS_INDEX   (3u)


#define CapSense_TOTAL_SLIDERS_COUNT            ( CapSense_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          CapSense_TOTAL_RADIAL_SLIDERS_COUNT )
                                                          
#define CapSense_TOTAL_CENTROIDS_COUNT          ( CapSense_TOTAL_SLIDERS_COUNT + \
                                                         (CapSense_TOTAL_TOUCH_PADS_COUNT*2u) )

#define CapSense_TOTAL_WIDGET_COUNT             ( CapSense_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          CapSense_TOTAL_RADIAL_SLIDERS_COUNT + \
                                                          CapSense_TOTAL_TOUCH_PADS_COUNT + \
                                                          CapSense_TOTAL_BUTTONS_COUNT + \
                                                          CapSense_TOTAL_MATRIX_BUTTONS_COUNT )
                                                           
#define CapSense_ANY_POS_FILTER                 ( CapSense_MEDIAN_FILTER | \
                                                          CapSense_AVERAGING_FILTER | \
                                                          CapSense_IIR2_FILTER | \
                                                          CapSense_IIR4_FILTER | \
                                                          CapSense_JITTER_FILTER )
                                                         
#define CapSense_IS_DIPLEX_SLIDER               ( CapSense_TOTAL_DIPLEXED_SLIDERS_COUNT > 0u)

#define CapSense_IS_NON_DIPLEX_SLIDER           ( (CapSense_TOTAL_LINEAR_SLIDERS_COUNT - \
                                                           CapSense_TOTAL_DIPLEXED_SLIDERS_COUNT) > 0u)
#define CapSense_ADD_SLIDER_TYPE                ((CapSense_TOTAL_RADIAL_SLIDERS_COUNT > 0u) ? \
                                                        ((CapSense_TOTAL_TOUCH_PADS_COUNT > 0u) || \
                                                         (CapSense_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) : 0u)
                                                         
#define CapSense_WIDGET_CSHL_PARAMETERS_COUNT           (CapSense_TOTAL_WIDGET_COUNT + \
                                                                 CapSense_TOTAL_TOUCH_PADS_COUNT + \
                                                                 CapSense_TOTAL_MATRIX_BUTTONS_COUNT)

#define CapSense_WIDGET_RESOLUTION_PARAMETERS_COUNT     (CapSense_WIDGET_CSHL_PARAMETERS_COUNT + \
                                                                 CapSense_TOTAL_GENERICS_COUNT)
                                                                 
#define CapSense_SENSORS_TBL_SIZE (CapSense_TOTAL_LINEAR_SLIDERS_COUNT + \
                                        CapSense_TOTAL_RADIAL_SLIDERS_COUNT + \
                                        CapSense_TOTAL_BUTTONS_COUNT + \
                                        CapSense_TOTAL_GENERICS_COUNT + \
                                        (CapSense_TOTAL_TOUCH_PADS_COUNT * 2u) + \
                                        (CapSense_TOTAL_MATRIX_BUTTONS_COUNT * 2u))
                                        
/*Types of centroids */
#define CapSense_TYPE_RADIAL_SLIDER         (0x01u)
#define CapSense_TYPE_LINEAR_SLIDER         (0x02u)
#define CapSense_TYPE_GENERIC               (0xFFu)

/* Defines is slot active */
#define CapSense_SENSOR_1_IS_ACTIVE     (0x01u)
#define CapSense_SENSOR_2_IS_ACTIVE     (0x02u)
#define CapSense_WIDGET_IS_ACTIVE       (0x01u)

/* Defines diplex type of Slider */
#define CapSense_IS_DIPLEX              (0x80u)

/* Defines max fingers on TouchPad  */
#define CapSense_POS_PREV               (0u)
#define CapSense_POS                    (1u)
#define CapSense_POS_NEXT               (2u)
#define CapSense_CENTROID_ROUND_VALUE   (0x7F00u)

#define CapSense_NEGATIVE_NOISE_THRESHOLD        (20u)
#define CapSense_LOW_BASELINE_RESET              (5u)


/***************************************
*        Function Prototypes
***************************************/
void CapSense_BaseInit(uint8 sensor) ;
void CapSense_InitializeSensorBaseline(uint8 sensor) \
                                               ;
void CapSense_InitializeAllBaselines(void) ;
void CapSense_InitializeEnabledBaselines(void) \
                                                 ;
void CapSense_UpdateSensorBaseline(uint8 sensor) ;
void CapSense_UpdateEnabledBaselines(void) ;
uint8 CapSense_CheckIsSensorActive(uint8 sensor) ;
uint8 CapSense_CheckIsWidgetActive(uint8 widget) ;
uint8 CapSense_CheckIsAnyWidgetActive(void) ;
void CapSense_EnableWidget(uint8 widget) ;
void CapSense_DisableWidget(uint8 widget) ;
#if (CapSense_TOTAL_MATRIX_BUTTONS_COUNT)
    uint8 CapSense_GetMatrixButtonPos(uint8 widget, uint8* pos) \
	                                          ;
#endif /* (CapSense_TOTAL_MATRIX_BUTTONS_COUNT) */

#if (CapSense_TOTAL_LINEAR_SLIDERS_COUNT)
    uint16 CapSense_GetCentroidPos(uint8 widget) ;
#endif /* (CapSense_TOTAL_LINEAR_SLIDERS_COUNT) */
#if (CapSense_TOTAL_RADIAL_SLIDERS_COUNT)
    uint16 CapSense_GetRadialCentroidPos(uint8 widget) \
                                                 ;
#endif /* (CapSense_TOTAL_RADIAL_SLIDERS_COUNT) */
#if (CapSense_TOTAL_TOUCH_PADS_COUNT)
    uint8 CapSense_GetTouchCentroidPos(uint8 widget, uint16* pos) \
	                                           ;
#endif /* (CapSense_TOTAL_TOUCH_PADS_COUNT) */

#if (CapSense_IS_DIPLEX_SLIDER)
    uint8 CapSense_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold, const uint8 CYCODE *diplex)
                                       ;
#else 
    uint8 CapSense_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold)
                                       ;
#endif /* (CapSense_IS_DIPLEX_SLIDER) */

#if(CapSense_TOTAL_CENTROIDS_COUNT)
    uint8 CapSense_CalcCentroid(uint8 maximum, uint8 offset, 
                                        uint8 count, uint16 resolution, uint8 noiseThreshold)
	                                    ;
#endif /* (CapSense_TOTAL_CENTROIDS_COUNT) */

/* SmartSense functions */
#if (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)
    extern void CapSense_CalculateThresholds(uint8 SensorNumber)
           ;
#endif /* (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */

/* Median filter function prototype */
#if ( (CapSense_RAW_FILTER_MASK & CapSense_MEDIAN_FILTER) | \
      (CapSense_POS_FILTERS_MASK & CapSense_MEDIAN_FILTER) )
    uint16 CapSense_MedianFilter(uint16 x1, uint16 x2, uint16 x3)
    ;
#endif /* CapSense_RAW_FILTER_MASK && CapSense_POS_FILTERS_MASK */

/* Averaging filter function prototype */
#if ( (CapSense_RAW_FILTER_MASK & CapSense_AVERAGING_FILTER) | \
      (CapSense_POS_FILTERS_MASK & CapSense_AVERAGING_FILTER) )
    uint16 CapSense_AveragingFilter(uint16 x1, uint16 x2, uint16 x3)
    ;
#endif /* CapSense_RAW_FILTER_MASK && CapSense_POS_FILTERS_MASK */

/* IIR2Filter(1/2prev + 1/2cur) filter function prototype */
#if ( (CapSense_RAW_FILTER_MASK & CapSense_IIR2_FILTER) | \
      (CapSense_POS_FILTERS_MASK & CapSense_IIR2_FILTER) )
    uint16 CapSense_IIR2Filter(uint16 x1, uint16 x2) ;
#endif /* CapSense_RAW_FILTER_MASK && CapSense_POS_FILTERS_MASK */

/* IIR4Filter(3/4prev + 1/4cur) filter function prototype */
#if ( (CapSense_RAW_FILTER_MASK & CapSense_IIR4_FILTER) | \
      (CapSense_POS_FILTERS_MASK & CapSense_IIR4_FILTER) )
    uint16 CapSense_IIR4Filter(uint16 x1, uint16 x2) ;
#endif /* CapSense_RAW_FILTER_MASK && CapSense_POS_FILTERS_MASK */

/* IIR8Filter(7/8prev + 1/8cur) filter function prototype - RawCounts only */
#if (CapSense_RAW_FILTER_MASK & CapSense_IIR8_FILTER)
    uint16 CapSense_IIR8Filter(uint16 x1, uint16 x2) ;
#endif /* CapSense_RAW_FILTER_MASK */

/* IIR16Filter(15/16prev + 1/16cur) filter function prototype - RawCounts only */
#if (CapSense_RAW_FILTER_MASK & CapSense_IIR16_FILTER)
    uint16 CapSense_IIR16Filter(uint16 x1, uint16 x2) ;
#endif /* CapSense_RAW_FILTER_MASK */

/* JitterFilter filter function prototype */
#if ( (CapSense_RAW_FILTER_MASK & CapSense_JITTER_FILTER) | \
      (CapSense_POS_FILTERS_MASK & CapSense_JITTER_FILTER) )
    uint16 CapSense_JitterFilter(uint16 x1, uint16 x2) ;
#endif /* CapSense_RAW_FILTER_MASK && CapSense_POS_FILTERS_MASK */

/* Storage of filters data */
#if ( (CapSense_RAW_FILTER_MASK & CapSense_MEDIAN_FILTER) | \
      (CapSense_RAW_FILTER_MASK & CapSense_AVERAGING_FILTER) )

    extern uint16 CapSense_rawFilterData1[CapSense_TOTAL_SENSOR_COUNT];
    extern uint16 CapSense_rawFilterData2[CapSense_TOTAL_SENSOR_COUNT];

#elif ( (CapSense_RAW_FILTER_MASK & CapSense_IIR2_FILTER)   | \
        (CapSense_RAW_FILTER_MASK & CapSense_IIR4_FILTER)   | \
        (CapSense_RAW_FILTER_MASK & CapSense_JITTER_FILTER) | \
        (CapSense_RAW_FILTER_MASK & CapSense_IIR8_FILTER)   | \
        (CapSense_RAW_FILTER_MASK & CapSense_IIR16_FILTER) )
        
    extern uint16 CapSense_rawFilterData1[CapSense_TOTAL_SENSOR_COUNT];

#else
    /* No Raw filters */
#endif  /* ( (CapSense_RAW_FILTER_MASK & CapSense_MEDIAN_FILTER) || \
        *    (CapSense_RAW_FILTER_MASK & CapSense_AVERAGING_FILTER) )
        */

extern uint8 CapSense_sensorEnableMask[(((CapSense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
extern const uint8 CYCODE CapSense_widgetNumber[CapSense_TOTAL_SENSOR_COUNT];

extern uint16 CapSense_sensorBaseline[CapSense_TOTAL_SENSOR_COUNT];
extern uint8 CapSense_sensorBaselineLow[CapSense_TOTAL_SENSOR_COUNT];
extern uint8 CapSense_sensorSignal[CapSense_TOTAL_SENSOR_COUNT];
extern uint8 CapSense_sensorOnMask[(((CapSense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];

extern uint8 CapSense_lowBaselineResetCnt[CapSense_TOTAL_SENSOR_COUNT];

/****************************************************************************************
*       Obsolete definitions. Not recommended to use. Will be removed in future releases.
*****************************************************************************************/

/* Obsolete names of variables */
//#define CapSense_SensorBaseline          CapSense_sensorBaseline
//#define CapSense_SensorBaselineLow       CapSense_sensorBaselineLow
//#define CapSense_SensorSignal            CapSense_sensorSignal
//#define CapSense_SensorOnMask            CapSense_sensorOnMask
//#define CapSense_LowBaselineResetCnt     CapSense_lowBaselineResetCnt


#endif /* CY_CAPSENSE_CSD_CSHL_CapSense_H */

/* [] END OF FILE */
