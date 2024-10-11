/*******************************************************************************
* File Name: Button_SMS.h
* Version 2.60
*
* Description:
*  This file provides the declarations of the wrapper between the CapSense CSD component
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
#if !defined(CY_CAPSENSE_CSD_SMS_Button_H)
#define CY_CAPSENSE_CSD_SMS_Button_H

#include "Button.h"
#include "Button_PVT.h"

#if(0u != Button_CSHL_API_GENERATE)
    #include "Button_CSHL.h"
#endif /* (0u != Button_CSHL_API_GENERATE) */

#define Button_PRESCALERS_TBL_SIZE        (16u)

#define Button_CALIBRATION_FREQ_KHZ       (3000u)
#define Button_CALIBRATION_MD             (2u)

#define Button_MAX_RESOLUTION         (65535u)
#define Button_CALIBRATION_RESOLUTION (0x0FFF0000u)

#define Button_PRS_CORRECTION_DIVIDER (4u)
#define Button_SENSITIVITY_DIVIDER    (10u)

#define Button_SENSITIVITY_MASK           (0x0Fu)
#define Button_FLEXIBLE_THRESHOLDS_EN     (0u)
#define Button_CAL_RAW_COUNT              (3482u)

#define Button_THRESHOLD_1                (220u)
#define Button_THRESHOLD_2                (237u)
#define Button_THRESHOLD_3                (245u)
#define Button_THRESHOLD_4                (250u)


#if (0u != Button_IS_M0S8PERI_BLOCK)
    #define Button_CALIBRATION_ASD        (CYDEV_BCLK__HFCLK__KHZ /\
                                                     Button_CALIBRATION_FREQ_KHZ)
#else
    #define Button_MIN_IMO_FREQ_KHZ       (6000u)
    #if(CYDEV_BCLK__HFCLK__KHZ < Button_MIN_IMO_FREQ_KHZ)
        #define Button_CALIBRATION_ASD            (1u)
    #else
        #define Button_CALIBRATION_ASD    (CYDEV_BCLK__HFCLK__KHZ / Button_CALIBRATION_MD /\
                                                     Button_CALIBRATION_FREQ_KHZ)
    #endif /* (CYDEV_BCLK__HFCLK__KHZ < Button_MIN_IMO_FREQ_KHZ) */
#endif /* (0u != Button_IS_M0S8PERI_BLOCK) */

#if (0u != Button_IS_M0S8PERI_BLOCK)
    /*  Dividers are not chained */
    #if(Button_PRS_OPTIONS != Button__PRS_NONE)
        #define Button_SENSETIVITY_FACTOR (1228u)
    #else
        #define Button_SENSETIVITY_FACTOR (2456u)
    #endif /* (Button_PRS_OPTIONS == Button__PRS_NONE) */
#else
    /*  Dividers are chained */
    #if(Button_PRS_OPTIONS != Button__PRS_NONE)
        #define Button_SENSETIVITY_FACTOR (1228u/Button_CALIBRATION_MD)
    #else
        #define Button_SENSETIVITY_FACTOR (2456u/Button_CALIBRATION_MD)
    #endif /* (Button_PRS_OPTIONS == Button__PRS_NONE) */
#endif /* (0u != Button_IS_M0S8PERI_BLOCK) */


/***************************************
*        Function Prototypes
***************************************/
void Button_AutoTune(void);
void Button_UpdateThresholds(uint32 sensor);
void Button_SetSensitivity(uint32 sensor, uint32 value);
void Button_SetAnalogSwitchesSrcDirect(void);
uint16 Button_GetNoiseEnvelope(uint32 sensor);
uint8 Button_GetSensitivityCoefficient(uint32 sensor);
uint16 Button_GetNormalizedDiffCountData(uint32 sensor);


/***************************************
*     Vars with External Linkage
***************************************/

/*  Real Charge Divider values */
#if (0u != Button_IS_M0S8PERI_BLOCK)
    /*  Dividers are not chained */
    #if (CYDEV_BCLK__HFCLK__MHZ >= 12u)
        extern const uint8 prescalerTable[Button_PRESCALERS_TBL_SIZE];
    #elif (CYDEV_BCLK__HFCLK__MHZ >= 6u)
        extern const uint8 prescalerTable[Button_PRESCALERS_TBL_SIZE];
    #else
        extern const uint8 prescalerTable[Button_PRESCALERS_TBL_SIZE];
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
#else
    /*  Dividers are chained */
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        extern const uint8 prescalerTable[Button_PRESCALERS_TBL_SIZE];
    #elif (CYDEV_BCLK__HFCLK__MHZ >12u)
        extern const uint8 prescalerTable[Button_PRESCALERS_TBL_SIZE];
    #else   /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */
        extern const uint8 prescalerTable[Button_PRESCALERS_TBL_SIZE];
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* (0u != Button_IS_M0S8PERI_BLOCK) */


extern uint8 Button_noiseEnvelopeTbl[Button_TOTAL_SENSOR_COUNT];
extern uint8 Button_runningDifferenceTbl[Button_TOTAL_SENSOR_COUNT];
extern uint8 Button_signRegisterTbl[Button_TOTAL_SENSOR_COUNT];
extern uint16 Button_sampleMinTbl[Button_TOTAL_SENSOR_COUNT];
extern uint16 Button_sampleMaxTbl[Button_TOTAL_SENSOR_COUNT];
extern uint16 Button_previousSampleTbl[Button_TOTAL_SENSOR_COUNT];
extern uint8 Button_kValueTbl[Button_TOTAL_SENSOR_COUNT];


#endif  /* (CY_CAPSENSE_CSD_SMS_Button_H) */

/* [] END OF FILE */
