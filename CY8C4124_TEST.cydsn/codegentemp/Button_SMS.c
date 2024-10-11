/*******************************************************************************
* File Name: Button_SMS.c
* Version 2.60
*
* Description:
*  This file provides the source code of wrapper between CapSense CSD component
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Button_SMS.h"
#include "Button_PVT.h"

#include "cytypes.h"

#if (Button_TUNING_METHOD == Button__TUNING_AUTO)


/*  Real Charge Divider values */
#if ((0u != Button_IS_M0S8PERI_BLOCK) && (0u == CY_PSOC4_4000))
    /*  Dividers are not chained */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            4u,     4u,     4u,    8u,    8u,    8u,    8u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u,    16u
        };
    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            2u,     2u,     2u,    4u,    4u,    4u,    4u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u
        };
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */

#elif (0u != Button_IS_M0S8PERI_BLOCK)
    /*  Dividers are not chained (PSoC 4000) */
    #if (CYDEV_BCLK__HFCLK__MHZ >= 12u)
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >= 6u)
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u
        };
    #else
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u,    1u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */

#else
    /*  Dividers are chained (PSoC 4100, PSoC 4200) */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            2u,     2u,     2u,    4u,    4u,    4u,    4u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u,    8u
        };

    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    2u,    2u,    2u,    2u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u,    4u
        };
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        const uint8 Button_prescalerTable[Button_PRESCALERS_TBL_SIZE] = {
            1u,     1u,     1u,    1u,    1u,    1u,    1u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u,    2u
        };
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* ((0u != Button_IS_M0S8PERI_BLOCK) && (0u == CY_PSOC4_4000)) */


uint8 Button_noiseEnvelopeTbl[Button_TOTAL_SENSOR_COUNT];
uint8 Button_runningDifferenceTbl[Button_TOTAL_SENSOR_COUNT];
uint8 Button_signRegisterTbl[Button_TOTAL_SENSOR_COUNT];
uint16 Button_sampleMinTbl[Button_TOTAL_SENSOR_COUNT];
uint16 Button_sampleMaxTbl[Button_TOTAL_SENSOR_COUNT];
uint16 Button_previousSampleTbl[Button_TOTAL_SENSOR_COUNT];
uint8 Button_kValueTbl[Button_TOTAL_SENSOR_COUNT];

uint8 Button_sensorSensitivity[] = {
    2u, 2u, 2u, 2u, 
};

Button_CONFIG_TYPE_P4_v2_60 Button_config;
Button_CONFIG_TYPE_POINTERS_P4_v2_60 const Button_configPointers = {
    Button_modulationIDAC,
    Button_compensationIDAC,
    Button_sensorSensitivity,
    Button_senseClkDividerVal,
    Button_sampleClkDividerVal,
    Button_widgetNumber,
    Button_widgetResolution,
    Button_noiseEnvelopeTbl,
    Button_runningDifferenceTbl,
    Button_signRegisterTbl,
    Button_sampleMinTbl,
    Button_sampleMaxTbl,
    Button_previousSampleTbl,
    Button_kValueTbl,
    Button_scanSpeedTbl,
    Button_prescalerTable,
    (const uint8  *)Button_rawDataIndex,
    (const uint8  *)Button_numberOfSensors,
    &Button_GetSensorRaw,
    &Button_PreScan,
    &Button_ReadSensorRaw,
    &Button_GetBitValue,
    &Button_SetBitValue
};


/*******************************************************************************
* Function Name: Button_AutoTune
********************************************************************************
*
* Summary:
*  Provides the tuning procedure for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   Button_config: the structure which contains configuration parameters
*   Button_senseClkDividerVal[]: used to store the Analog Switch
*   dividers for each sensor.
*   Button_senseClkDividerVal[]: used to store the
*    Analog Switch divider for all sensors.
*   Button_prescalersTuningDone - used to notify the Tuner GUI that
*   the pre-scalers tuning  is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_AutoTune(void)
{
    uint32 curSensor;
    uint32 widget;

    Button_config.totalScanslotsNum = Button_TOTAL_SCANSLOT_COUNT;
    Button_config.totalWidgetsNum = Button_END_OF_WIDGETS_INDEX;
    Button_config.totalSensorsNum = Button_TOTAL_SENSOR_COUNT;

    Button_config.hfclkFreq_MHz = CYDEV_BCLK__HFCLK__MHZ;
    Button_config.sensetivitySeed = Button_SENSETIVITY_FACTOR;

    Button_config.pointers = &Button_configPointers;

    Button_SetAnalogSwitchesSrcDirect();

    for(widget = 0u; widget < Button_config.totalWidgetsNum; widget++)
    {
        Button_widgetResolution[widget] = Button_CALIBRATION_RESOLUTION;
    }


    for(curSensor = 0u; curSensor < Button_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        Button_senseClkDividerVal[curSensor] = Button_CALIBRATION_ASD;
        Button_sampleClkDividerVal[curSensor] = Button_CALIBRATION_MD;
    }

    Button_DisableBaselineIDAC();

    CalibrateSensors_P4_v2_60(&Button_config, Button_CAL_RAW_COUNT);

    #if(0u != Button_TOTAL_CENTROIDS_COUNT)
        Button_NormalizeWidgets(Button_END_OF_WIDGETS_INDEX, Button_modulationIDAC);
    #endif /* (0u != Button_TOTAL_CENTROIDS_COUNT)  */

    TunePrescalers_P4_v2_60(&Button_config);

    #if(Button_PRS_OPTIONS != Button__PRS_NONE)
        Button_prescalersTuningDone = 1u;
    #endif /* (Button_PRS_OPTIONS == Button__PRS_NONE) */

    CalibrateSensors_P4_v2_60(&Button_config, Button_CAL_RAW_COUNT);
    #if(0u != Button_TOTAL_CENTROIDS_COUNT)
        Button_NormalizeWidgets(Button_END_OF_WIDGETS_INDEX, Button_modulationIDAC);
    #endif /* (0u != Button_TOTAL_CENTROIDS_COUNT)  */
    TuneSensitivity_P4_v2_60(&Button_config);

    Button_EnableBaselineIDAC(&Button_config);

    for(curSensor = 0u; curSensor < Button_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        Button_UpdateThresholds(curSensor);
    }
}


/*******************************************************************************
* Function Name: Button_UpdateThresholds
********************************************************************************
*
* Summary:
*  The API updates the Finger Threshold, Hysteresis, Noise Threshold, and
*  Negative Noise Threshold in the AutoTuning (Smartsense) Mode.
*
* Parameters:
*  sensor: sensor number.
*
* Return:
*  None
*
* Global Variables:
*  Button_widgetNumber[] - contains widget Number for given sensor.
*  0 through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  For other sensors the array element equals to 255.
*  Button_numberOfSensors[widget] - Number of sensors in the widget.
*   Button_fingerThreshold[] - contains the level of signal for each sensor
*   that determines if a finger present on the sensor.
*   Button_negativeNoiseThreshold[] - negative Noise Threshold
*   Button_hysteresis[] - the array with hysteresis values.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_UpdateThresholds(uint32 sensor)
{
    uint8 fingerThreshold;
    uint32 widget;

    widget = Button_widgetNumber[sensor];

    #if(0u != Button_FLEXIBLE_THRESHOLDS_EN)
        fingerThreshold = Button_fingerThreshold[widget];
        /* Update Threshold manually (flexible) */
        Button_noiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        Button_negativeNoiseThreshold[widget] = (uint8)(fingerThreshold >> 1u);
        Button_hysteresis[widget] = (uint8)(fingerThreshold >> 3u);
    #else
        /* Calculate Finger Threshold and Noise Threshold with Smartsense (automatic) */
        CalculateThresholds_P4_v2_60(&Button_config, (uint8)sensor, (uint8)widget, Button_fingerThreshold, Button_noiseThreshold);

        fingerThreshold = Button_fingerThreshold[widget];

        /* Update Threshold based on calculated with Smartsense (automatic) */
        Button_negativeNoiseThreshold[widget] = Button_noiseThreshold[widget];

        if(fingerThreshold < Button_THRESHOLD_1)
        {
            Button_hysteresis[widget] = (uint8)(fingerThreshold >> 3u);
        }
        else if(fingerThreshold <  Button_THRESHOLD_2)
        {
            Button_hysteresis[widget] = (uint8)(fingerThreshold >> 4u);
        }
        else if(fingerThreshold <  Button_THRESHOLD_3)
        {
            Button_hysteresis[widget] = (uint8)(fingerThreshold >> 5u);
        }
        else if(fingerThreshold <  Button_THRESHOLD_4)
        {
            Button_hysteresis[widget] = (uint8)(fingerThreshold >> 6u);
        }
        else
        {
            Button_hysteresis[widget] = 0u;
        }
    #endif /* (0u != Button_FLEXIBLE_THRESHOLDS_EN)  */
}

/*******************************************************************************
* Function Name: Button_SetAnalogSwitchesSrcDirect
********************************************************************************
*
* Summary:
*  This API switches the charge clock source to prescaler.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_SetAnalogSwitchesSrcDirect(void)
{
    Button_CSD_CFG_REG &= ~(Button_CSD_CFG_PRS_SELECT);
}


/*******************************************************************************
* Function Name: Button_DisableBaselineIDAC
********************************************************************************
*
* Summary:
*  The API disables the Compensation IDAC.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_DisableBaselineIDAC(void)
{
    uint32 newRegValue;

    newRegValue = Button_CSD_IDAC_REG;

    newRegValue &= ~(Button_CSD_IDAC1_MODE_MASK | Button_CSD_IDAC2_MODE_MASK);
    newRegValue |= Button_CSD_IDAC1_MODE_VARIABLE;

    Button_CSD_IDAC_REG = newRegValue;
}


/*******************************************************************************
* Function Name: Button_EnableBaselineIDAC
********************************************************************************
*
* Summary:
*  The API enables the Compensation IDAC.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_compensationIDAC[] - used to store a 7-bit idac value for all the sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void  Button_EnableBaselineIDAC(const Button_CONFIG_TYPE_P4_v2_60 *config)
{
    uint32 curSensor;
    uint32 newRegValue;

    for(curSensor = 0u; curSensor < config->totalScanslotsNum; curSensor++)
    {
        Button_compensationIDAC[curSensor] = Button_modulationIDAC[curSensor] / 2u;
        Button_modulationIDAC[curSensor] = (Button_modulationIDAC[curSensor] + 1u) / 2u;
    }

    CyIntDisable(Button_ISR_NUMBER);

    newRegValue = Button_CSD_IDAC_REG;
    newRegValue &= ~(Button_CSD_IDAC1_MODE_MASK | Button_CSD_IDAC2_MODE_MASK);
    newRegValue |= (Button_CSD_IDAC1_MODE_VARIABLE | Button_CSD_IDAC2_MODE_FIXED);
    Button_CSD_IDAC_REG = newRegValue;

    CyIntEnable(Button_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: Button_SetSensitivity
********************************************************************************
*
* Summary:
*  This API sets the sensitivity value for the sensor. The sensitivity
*  value is used during the auto-tuning algorithm executed as part of the CapSense_Start API.
*  This API is called by the application layer prior to calling the CapSense_Start API.
*  Calling this API after execution of CapSense_Start API has no effect.
*
* Parameters:
*  sensor  Sensor index
*  data    Sensitivity of the sensor. Possible values are below
*  1 - 0.1pf sensitivity
*  2 - 0.2pf sensitivity
*  3 - 0.3pf sensitivity
*  4 - 0.4pf sensitivity
*  5 - 0.5pf sensitivity
*  6 - 0.6pf sensitivity
*  7 - 0.7pf sensitivity
*  8 - 0.8pf sensitivity
*  9 - 0.9pf sensitivity
*  10 - 1.0pf sensitivity
*  All other values, set sensitivity to 1.0pf
*
*  Return Value:
*   None
*
* Global Variables:
* Button_sensorSensitivity[] - This 8-bits array contains Sensitivity in the LSB nibble
*                                and Noise Reset Counter value in the MSB nibble.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_SetSensitivity(uint32 sensor, uint32 value)
{
    if(value > 10u)
    {
        value = 10u;
    }

    /* Clear SensorSensitivity value in LSB nibble */
    Button_sensorSensitivity[sensor] &= (uint8)~Button_SENSITIVITY_MASK;
    /* Set SensorSensitivity value in LSB nibble */
    Button_sensorSensitivity[sensor] |= (uint8)value;
}


/*******************************************************************************
* Function Name: Button_GetSensitivityCoefficient
********************************************************************************
*
* Summary:
*  This API returns the K coefficient for the appropriate sensor.
*
* Parameters:
*  sensor:  Sensor index
*
*  Return Value:
*   K - value for the appropriate sensor.
*
* Global Variables:
*  Button_kValueTbl[] - This 8-bits array contains the K value for each sensor.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 Button_GetSensitivityCoefficient(uint32 sensor)
{
    return (Button_kValueTbl[sensor]);
}


/*******************************************************************************
* Function Name: Button_GetNoiseEnvelope
********************************************************************************
*
* Summary:
*  This function returns the noise value of a
*  component.
*
* Parameters:
*  sensor - Sensor number.
*
* Return:
*  The noise envelope value of the sensor
*  indicated by argument.
*
* Global Variables:
*  Button_noiseEnvelopeTbl[] - array with Noise Envelope.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 Button_GetNoiseEnvelope(uint32 sensor)
{
    return((uint16)((uint16)Button_noiseEnvelopeTbl[sensor] << 1u) + 1u);
}


/*******************************************************************************
* Function Name: Button_GetNormalizedDiffCountData
********************************************************************************
*
* Summary:
*  This API returns normalized difference count data.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  This API returns a normalized count value of the sensor indicated by the
*  argument.
*
* Global Variables:
*  Button_sensorSignal[] - array with difference counts for sensors
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 Button_GetNormalizedDiffCountData(uint32 sensor)
{
    return (uint16)(((uint32)Button_sensorSignal[sensor] << 7u) / Button_kValueTbl[sensor]);
}

#endif /* (Button_TUNING_METHOD == Button__TUNING_AUTO) */

/* [] END OF FILE */
