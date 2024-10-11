/*******************************************************************************
* File Name: Button_PVT.h
* Version 2.60
*
* Description:
*  This file provides constants and structure declarations for the
*  CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_CSD_PVT_Button_H)
#define CY_CAPSENSE_CSD_PVT_Button_H

#include "Button.h"

#if(0u != Button_CSHL_API_GENERATE)
    #include "Button_CSHL.h"
#endif /* (0u != Button_CSHL_API_GENERATE) */

#if(Button_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
    #include "Button_GESTURE.h"
#endif /* (Button_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */

typedef struct
{
    #if (Button_IS_COMPLEX_SCANSLOTS)
    uint8 sensor;
    #endif  /* Button_IS_COMPLEX_SCANSLOTS */
    uint8 pinNumber;
    uint8 portNumber;
    uint8 idacValue;
    uint16 senseClkDiv;
    uint16 sampleClkDiv;
    uint8 avgSamplesNum;
    uint16 calibrationCount;
    uint32 scanResolution;
}Button_CP_MEASURE_CONFIG;

typedef struct
{
    uint8 *idac1LevelsTbl;
    uint8 *idac2LevelsTbl;
    uint8 *sensetivityTbl;
    uint8 *chargeDivTbl;
    uint8 *modDivTbl;
    const uint8 *widgetNubmersTbl;
    uint32 *resolutionsTbl;
    uint8 *noiseEnvelopeTbl;
    uint8 *runningDifferenceTbl;
    uint8 *signRegisterTbl;
    uint16 *sampleMinTbl;
    uint16 *sampleMaxTbl;
    uint16 *previousSampleTbl;
    uint8 *kValueTbl;
    uint8 *scanSpeedTbl;
    const uint8 *prescalerTable;
    uint8 const *rawDataIndex;
    uint8 const *numberOfSensors;
    uint16 (*ptrGetRaw)(uint32 sensor);
    void (*ptrPreScan)(uint32 sensor);
    uint16 (*ptrReadSensorRaw)(uint32 sensor);
    uint32 (*ptrGetBitValue)(const uint8 table[], uint32 position);
    void (*ptrSetBitValue)(uint8 table[], uint32 position, uint32 value);
}Button_CONFIG_TYPE_POINTERS_P4_v2_60;

typedef struct
{
    uint8 totalScanslotsNum;
    uint8 totalWidgetsNum;
    uint8 totalSensorsNum;
    uint16 sensetivitySeed;
    uint16 hfclkFreq_MHz;
    Button_CONFIG_TYPE_POINTERS_P4_v2_60 const * pointers;
}Button_CONFIG_TYPE_P4_v2_60;

#define Button_AVG_SAMPLES_NUM        (1u)


/***************************************
*        Function Prototypes
***************************************/
void Button_PreScan(uint32 sensor);
void Button_PostScan(uint32 sensor);

void Button_EnableSensor(uint32 sensor);
void Button_DisableSensor(uint32 sensor);

#if (Button_IS_COMPLEX_SCANSLOTS)
    void Button_EnableScanSlot(uint32 slot);
    void Button_DisableScanSlot(uint32 slot);
#else
    #define Button_EnableScanSlot(slot)   Button_EnableSensor(slot)
    #define Button_DisableScanSlot(slot)  Button_DisableSensor(slot)
#endif  /* End Button_IS_COMPLEX_SCANSLOTS */

void Button_EnableShieldElectrode(uint32 pinNumber, uint32 portNumber);

uint32 Button_GetBitValue(const uint8 table[], uint32 position);
void Button_SetBitValue(uint8 table[], uint32 position, uint32 value);

/* Find next sensor for One Channel design */
uint8 Button_FindNextSensor(uint8 snsIndex);

void Button_SetPinDriveMode(uint32 driveMode, uint32 pinNumber, uint32 portNumber);
void Button_CalibrateSensor(uint32 sensor, uint32 rawLevel, uint8 idacLevelsTbl[]);
uint16  Button_GetSensorRaw(uint32 sensor);

void Button_DisableBaselineIDAC(void);
void Button_EnableBaselineIDAC(const Button_CONFIG_TYPE_P4_v2_60 *config);

uint32 Button_GetLowCp(Button_CP_MEASURE_CONFIG *config);
uint32 Button_GetHighCp(const Button_CP_MEASURE_CONFIG *config);
uint32 Button_CalibrateIDAC(Button_CP_MEASURE_CONFIG *config);
uint16 Button_ScanSensorCp(const Button_CP_MEASURE_CONFIG *config);

void Button_ConnectElectrode(uint32 pinNumber, uint32 portNumber);
void Button_DisconnectElectrode(uint32 pinNumber, uint32 portNumber);

void TunePrescalers_P4_v2_60(void *config);
void TuneSensitivity_P4_v2_60(void *config);
void MeasureNoiseEnvelope_P4_v2_60(void *config, const uint8 sensorNumber, const uint16 *rawData);
void CalculateThresholds_P4_v2_60(void *config, const uint8 sensorNumber, const uint8 widget, uint8 *fingerThres, uint8 *noiseThres);
void CalibrateSensors_P4_v2_60(void *config, uint16 rawLevel);
void CalibrateOneDAC_P4_v2_60(void *config, uint16 rawLevel, uint32 curSensor, uint8 *idacLevelsTbl);


#endif /* CY_CAPSENSE_CSD_PVT_Button_H */
