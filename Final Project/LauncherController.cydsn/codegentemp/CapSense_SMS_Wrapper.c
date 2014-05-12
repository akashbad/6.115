/*******************************************************************************
* File Name: CapSense_SMS_Wrapper.c
* Version 3.40
*
* Description:
*  This file provides the source code of wrapper between CapSense CSD component 
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense.h"
#include "CapSense_CSHL.h"

#if (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)

extern uint8 CapSense_noiseThreshold[CapSense_WIDGET_CSHL_PARAMETERS_COUNT];
extern uint8 CapSense_hysteresis[CapSense_WIDGET_CSHL_PARAMETERS_COUNT];
extern uint8 CapSense_widgetResolution[CapSense_WIDGET_RESOLUTION_PARAMETERS_COUNT];
extern const uint8 CYCODE CapSense_numberOfSensors[CapSense_SENSORS_TBL_SIZE];

extern uint8 CapSense_fingerThreshold[CapSense_WIDGET_CSHL_PARAMETERS_COUNT];
extern uint8 CapSense_idacSettings[CapSense_TOTAL_SENSOR_COUNT];
extern uint8 CapSense_analogSwitchDivider[CapSense_TOTAL_SCANSLOT_COUNT];

extern void SMS_LIB_V3_CalculateThresholds(uint8 SensorNumber);
extern void SMS_LIB_V3_AutoTune1Ch(void);
extern void SMS_LIB_V3_AutoTune2Ch(void);

uint8  * SMS_LIB_noiseThreshold = CapSense_noiseThreshold;
uint8 * SMS_LIB_hysteresis = CapSense_hysteresis;

uint8 * SMS_LIB_widgetResolution = CapSense_widgetResolution;

const uint8 CYCODE * SMS_LIB_widgetNumber = CapSense_widgetNumber;
const uint8 CYCODE * SMS_LIB_numberOfSensors = CapSense_numberOfSensors;

uint8 * SMS_LIB_fingerThreshold = CapSense_fingerThreshold;
uint8 * SMS_LIB_idacSettings = CapSense_idacSettings;
uint8 * SMS_LIB_prescaler = CapSense_analogSwitchDivider;

uint16 * SMS_LIB_SensorRaw = CapSense_sensorRaw;
uint16 * SMS_LIB_SensorBaseline = CapSense_sensorBaseline;

const uint8 CYCODE SMS_LIB_SensorSensitivity[] = {
    2, 2, 2, 2, 2, 2, 2, 
};


const uint8 CYCODE SMS_LIB_PrescalerTbl[] = {
    1u, 1u, 1u, 1u, 1u, 1u, 2u, 2u, 2u, 2u, 2u, 3u, 3u, 3u, 3u, 3u, 3u, 4u, 4u, 4u, 4u, 4u, 4u, 5u, 5u, 5u, 5u, 5u, 5u, 6u, 6u, 6u, 
};



uint8 SMS_LIB_Table1[CapSense_TOTAL_SENSOR_COUNT];
uint8 SMS_LIB_Table2[CapSense_TOTAL_SENSOR_COUNT];
uint8 SMS_LIB_Table3[CapSense_TOTAL_SENSOR_COUNT];
uint16 SMS_LIB_Table4[CapSense_TOTAL_SENSOR_COUNT];
uint16 SMS_LIB_Table5[CapSense_TOTAL_SENSOR_COUNT];
uint8 SMS_LIB_Table6[CapSense_TOTAL_SENSOR_COUNT];
uint8 SMS_LIB_Table7[CapSense_TOTAL_SENSOR_COUNT];

uint8 SMS_LIB_Table8[CapSense_END_OF_WIDGETS_INDEX];
uint8 SMS_LIB_Table9[CapSense_END_OF_WIDGETS_INDEX];
uint8 SMS_LIB_Table10[CapSense_END_OF_WIDGETS_INDEX];

uint8 SMS_LIB_Var1 = (5u);
uint16 SMS_LIB_Var2 = (10738u);

uint8 SMS_LIB_TotalSnsCnt = CapSense_TOTAL_SENSOR_COUNT;
uint8 SMS_LIB_TotalScanSlCnt = CapSense_TOTAL_SCANSLOT_COUNT;
uint8 SMS_LIB_EndOfWidgInd = CapSense_END_OF_WIDGETS_INDEX;

#if (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
    uint8 SMS_LIB_TotalSnsCnt_CH0 = CapSense_TOTAL_SENSOR_COUNT__CH0;
    uint8 SMS_LIB_TotalSnsCnt_CH1 = CapSense_TOTAL_SENSOR_COUNT__CH1;
#else
    uint8 SMS_LIB_TotalSnsCnt_CH0 = 0u;
    uint8 SMS_LIB_TotalSnsCnt_CH1 = 0u;
#endif  /* (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN) */

/*******************************************************************************
* Function Name: SMS_LIB_ScanSensor
********************************************************************************
*
* Summary:
*  Wrapper to CapSense_ScanSensor function.
*
* Parameters:
*  SensorNumber:  Sensor number.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void SMS_LIB_ScanSensor(uint8 SensorNumber) 
{
    CapSense_ScanSensor(SensorNumber);
}

/*******************************************************************************
* Function Name: SMS_LIB_IsBusy
********************************************************************************
*
* Summary:
*  Wrapper to CapSense_IsBusy function.
*  
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
uint8 SMS_LIB_IsBusy(void) 
{
    return CapSense_IsBusy();
}


/*******************************************************************************
* Function Name: CapSense_CalculateThresholds
********************************************************************************
*
* Summary:
*  Wrapper to SMS_LIB_CalculateThresholds function.
*
* Parameters:
*  SensorNumber:  Sensor number.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CalculateThresholds(uint8 SensorNumber) 
{
    SMS_LIB_V3_CalculateThresholds(SensorNumber);
}


/*******************************************************************************
* Function Name: CapSense_AutoTune
********************************************************************************
*
* Summary:
*  Wrapper for SMS_LIB_AutoTune1Ch or SMS_LIB_AutoTune2Ch function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_AutoTune(void) 
{
    #if (CapSense_DESIGN_TYPE == CapSense_ONE_CHANNEL_DESIGN)
        SMS_LIB_V3_AutoTune1Ch();
    #elif (CapSense_DESIGN_TYPE == CapSense_TWO_CHANNELS_DESIGN)
        SMS_LIB_V3_AutoTune2Ch();
    #endif /* (CapSense_DESIGN_TYPE == CapSense_ONE_CHANNEL_DESIGN) */
}

/*******************************************************************************
* Function Name: SMS_LIB_SetPrescaler
********************************************************************************
*
* Summary:
*  Empty wrapper for version compliance.
*
* Parameters:
*  prescaler:  prascaler value.
*
* Return:
*  None
*
*******************************************************************************/
void SMS_LIB_SetPrescaler(uint8 prescaler) 
{
    prescaler = prescaler;
}

void SMS_LIB_V3_SetAnalogSwitchesSrc_PRS(void) 
{
	CapSense_SetAnalogSwitchesSource(CapSense_ANALOG_SWITCHES_SRC_PRS);
}

void SMS_LIB_V3_SetAnalogSwitchesSrc_Prescaler(void) 
{
	CapSense_SetAnalogSwitchesSource(CapSense_ANALOG_SWITCHES_SRC_PRESCALER);
}

#endif  /* (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */


/* [] END OF FILE */
