/*******************************************************************************
* File Name: Button_CSHL.h
* Version 2.60
*
* Description:
*  This file provides constants and parameter values for the High Level APIs
*  for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CSHL_Button_H)
#define CY_CAPSENSE_CSD_CSHL_Button_H

#include "Button.h"


/***************************************
*   Condition compilation parameters
***************************************/

#define Button_SIGNAL_SIZE                    (8u)
#define Button_AUTO_RESET                     (0u)
#define Button_RAW_FILTER_MASK                (8u)

/* Signal size definition */
#define Button_SIGNAL_SIZE_UINT8              (8u)
#define Button_SIGNAL_SIZE_UINT16             (16u)

/* Auto reset definition */
#define Button_AUTO_RESET_DISABLE             (0u)
#define Button_AUTO_RESET_ENABLE              (1u)

/* Mask for RAW and POS filters */
#define Button_MEDIAN_FILTER                  (0x01u)
#define Button_AVERAGING_FILTER               (0x02u)
#define Button_IIR2_FILTER                    (0x04u)
#define Button_IIR4_FILTER                    (0x08u)
#define Button_JITTER_FILTER                  (0x10u)
#define Button_IIR8_FILTER                    (0x20u)
#define Button_IIR16_FILTER                   (0x40u)
#define Button_RAW_FILTERS_ENABLED            (0x01u)
#define Button_RAW_FILTERS_DISABLED           (0x00u)

/***************************************
*           API Constants
***************************************/

/* Widgets constants definition */
#define Button_BUTTON0__BTN        (0u)
#define Button_BUTTON1__BTN        (1u)
#define Button_BUTTON2__BTN        (2u)
#define Button_BUTTON3__BTN        (3u)

#define Button_TOTAL_DIPLEXED_SLIDERS_COUNT        (0u)
#define Button_TOTAL_LINEAR_SLIDERS_COUNT          (0u)
#define Button_TOTAL_RADIAL_SLIDERS_COUNT          (0u)
#define Button_TOTAL_TOUCH_PADS_COUNT              (0u)
#define Button_TOTAL_TOUCH_PADS_BASIC_COUNT        (0u)
#define Button_TOTAL_TRACKPAD_GESTURES_COUNT       (0u)
#define Button_TOTAL_BUTTONS_COUNT                 (4u)
#define Button_TOTAL_MATRIX_BUTTONS_COUNT          (0u)
#define Button_TOTAL_GENERICS_COUNT                (0u)

#define Button_POS_FILTERS_MASK                    (0x0u)
#define Button_LINEAR_SLIDERS_POS_FILTERS_MASK     (0x0u)
#define Button_RADIAL_SLIDERS_POS_FILTERS_MASK     (0x0u)
#define Button_TOUCH_PADS_POS_FILTERS_MASK         (0x0u)
#define Button_TRACKPAD_GEST_POS_FILTERS_MASK      (0x0u)

#define Button_UNUSED_DEBOUNCE_COUNTER_INDEX       (4u)

#define Button_TOTAL_PROX_SENSORS_COUNT            (0u)

#define Button_END_OF_SLIDERS_INDEX                (0u)
#define Button_END_OF_TOUCH_PAD_INDEX              (0u)
#define Button_END_OF_BUTTONS_INDEX                (3u)
#define Button_END_OF_MATRIX_BUTTONS_INDEX         (3u)
#define Button_END_OF_WIDGETS_INDEX                (4u)



#define Button_TOTAL_SLIDERS_COUNT            ( Button_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          Button_TOTAL_RADIAL_SLIDERS_COUNT )

#define Button_TOTAL_CENTROIDS_COUNT          ( Button_TOTAL_SLIDERS_COUNT + \
                                                         (Button_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u) +\
                                                         (Button_TOTAL_TRACKPAD_GESTURES_COUNT * 4u))

#define Button_TOTAL_CENTROIDS_BASIC_COUNT    ( Button_TOTAL_SLIDERS_COUNT + \
                                                         (Button_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u))

#define Button_TOTAL_CENTROID_AXES_COUNT      ( Button_TOTAL_SLIDERS_COUNT + \
                                                         (Button_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u) +\
                                                         (Button_TOTAL_TRACKPAD_GESTURES_COUNT * 2u))

#define Button_TOTAL_WIDGET_COUNT             ( Button_TOTAL_LINEAR_SLIDERS_COUNT + \
                                                          Button_TOTAL_RADIAL_SLIDERS_COUNT + \
                                                          Button_TOTAL_TOUCH_PADS_COUNT + \
                                                          Button_TOTAL_BUTTONS_COUNT + \
                                                          Button_TOTAL_MATRIX_BUTTONS_COUNT )

#define Button_ANY_POS_FILTER                 ( Button_MEDIAN_FILTER | \
                                                          Button_AVERAGING_FILTER | \
                                                          Button_IIR2_FILTER | \
                                                          Button_IIR4_FILTER | \
                                                          Button_JITTER_FILTER )

#define Button_IS_DIPLEX_SLIDER               ( Button_TOTAL_DIPLEXED_SLIDERS_COUNT > 0u)

#define Button_IS_NON_DIPLEX_SLIDER           ( (Button_TOTAL_LINEAR_SLIDERS_COUNT - \
                                                           Button_TOTAL_DIPLEXED_SLIDERS_COUNT) > 0u)
#define Button_ADD_SLIDER_TYPE                ((Button_TOTAL_RADIAL_SLIDERS_COUNT > 0u) ? \
                                                        ((Button_TOTAL_TOUCH_PADS_COUNT > 0u) || \
                                                         (Button_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) : 0u)

#define Button_TOTAL_PROX_SENSOR_COUNT        (Button_TOTAL_PROX_SENSORS_COUNT)

#define Button_WIDGETS_TBL_SIZE               ( Button_TOTAL_WIDGET_COUNT + \
                                                          Button_TOTAL_GENERICS_COUNT)

#define Button_WIDGET_PARAM_TBL_SIZE          (Button_TOTAL_BUTTONS_COUNT + \
                                                         Button_TOTAL_SLIDERS_COUNT +\
                                                         Button_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u + \
                                                         Button_TOTAL_TRACKPAD_GESTURES_COUNT * 2u +\
                                                         Button_TOTAL_MATRIX_BUTTONS_COUNT * 2u)

#define Button_THRESHOLD_TBL_SIZE         (Button_WIDGET_PARAM_TBL_SIZE)
#define Button_DEBOUNCE_CNT_TBL_SIZE      (Button_WIDGET_PARAM_TBL_SIZE)
#define Button_RAW_DATA_INDEX_TBL_SIZE    (Button_WIDGET_PARAM_TBL_SIZE +\
                                                     Button_TOTAL_GENERICS_COUNT)

#define Button_RES_MULT                   (256u)


#define Button_NOT_WIDGET                     (0xFFFFFFFFu)

/*Types of centroids */
#define Button_TYPE_RADIAL_SLIDER             (0x01u)
#define Button_TYPE_LINEAR_SLIDER             (0x02u)
#define Button_TYPE_GENERIC                   (0xFFu)

/* Defines if sensors or widgets are active */
#define Button_SENSOR_IS_ACTIVE               (0x01u)
#define Button_SENSOR_1_IS_ACTIVE             (0x01u)
#define Button_SENSOR_2_IS_ACTIVE             (0x02u)
#define Button_WIDGET_IS_ACTIVE               (0x01u)

/* Defines diplex type of Slider */
#define Button_IS_DIPLEX                      (0x80u)

/* Defines fingers positions on Slider  */
#define Button_POS_PREV                       (0u)
#define Button_POS                            (1u)
#define Button_POS_NEXT                       (2u)
#define Button_CENTROID_ROUND_VALUE           (0x7F00u)
#define Button_MAXIMUM_CENTROID               (0xFFu)

#define Button_NEGATIVE_NOISE_THRESHOLD       (20u)
#define Button_LOW_BASELINE_RESET             (5u)


/***************************************
*        Function Prototypes
***************************************/

void Button_InitializeSensorBaseline(uint32 sensor);
void Button_InitializeAllBaselines(void);
void Button_InitializeEnabledBaselines(void);
void Button_UpdateSensorBaseline(uint32 sensor);
void Button_UpdateBaselineNoThreshold(uint32 sensor);
void Button_UpdateEnabledBaselines(void);
void Button_UpdateWidgetBaseline(uint32 widget);
uint16 Button_GetBaselineData(uint32 sensor);
void Button_SetBaselineData(uint32 sensor, uint16 data);
void Button_BaseInit(uint32 sensor);

#if (Button_IS_DIPLEX_SLIDER)
    uint8 Button_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold, const uint8 *diplex);
#else
    uint8 Button_FindMaximum(uint8 offset, uint8 count, uint8 fingerThreshold);
#endif /* (Button_IS_DIPLEX_SLIDER) */

#if (Button_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
    uint8 Button_CalcCentroid(uint8 maximum, uint8 offset, \
                                    uint8 count, uint32 resolution, uint8 noiseThreshold);
#else
    uint8 Button_CalcCentroid(uint8 maximum, uint8 offset, \
                                    uint8 count, uint16 resolution, uint8 noiseThreshold);
#endif /* (Button_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */


uint8 Button_GetFingerThreshold(uint32 widget);
uint8 Button_GetNoiseThreshold(uint32 widget);
uint8 Button_GetFingerHysteresis(uint32 widget);
uint8 Button_GetNegativeNoiseThreshold(uint32 widget);

#if(Button_TUNING_METHOD != Button__TUNING_NONE)
    void Button_SetFingerThreshold(uint32 widget, uint8 value);
    void Button_SetNoiseThreshold(uint32 widget, uint8 value);
    void Button_SetFingerHysteresis(uint32 widget, uint8 value);
    void Button_SetNegativeNoiseThreshold(uint32 widget, uint8 value);
    void Button_SetDebounce(uint32 widget, uint8 value);
    void Button_SetLowBaselineReset(uint32 sensor, uint8 value);
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */

uint8 Button_GetDiffCountData(uint32 sensor);
void Button_SetDiffCountData(uint32 sensor, uint8 value);

uint32 Button_CheckIsSensorActive(uint32 sensor);
uint32 Button_CheckIsWidgetActive(uint32 widget);
uint32 Button_CheckIsAnyWidgetActive(void);
void Button_EnableWidget(uint32 widget);
void Button_DisableWidget(uint32 widget);
void Button_EnableRawDataFilters(void);
void Button_DisableRawDataFilters(void);

#if (Button_TOTAL_MATRIX_BUTTONS_COUNT)
    uint32 Button_GetMatrixButtonPos(uint32 widget, uint8* pos);
#endif /* (Button_TOTAL_MATRIX_BUTTONS_COUNT) */

#if((Button_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (Button_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 Button_GetCentroidPos(uint32 widget);
#endif /* ((Button_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (Button_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if((Button_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (Button_TOTAL_LINEAR_SLIDERS_COUNT > 0u))
    uint16 Button_GetRadialCentroidPos(uint32 widget);
#endif /* #if((Button_TOTAL_RADIAL_SLIDERS_COUNT > 0u) || (Button_TOTAL_LINEAR_SLIDERS_COUNT > 0u)) */
#if (Button_TOTAL_TOUCH_PADS_COUNT)
    uint32 Button_GetTouchCentroidPos(uint32 widget, uint16* pos);
#endif /* (Button_TOTAL_TOUCH_PADS_COUNT) */

uint32 Button_GetWidgetNumber(uint32 sensor);
uint8 Button_GetLowBaselineReset(uint32 sensor);
uint8 Button_GetDebounce(uint32 widget);

/* Filter function prototypes for High level APIs */

/* Median filter function prototype */
#if ( (0u != (Button_RAW_FILTER_MASK & Button_MEDIAN_FILTER)) || \
      (0u != (Button_POS_FILTERS_MASK & Button_MEDIAN_FILTER)) || \
      ((Button_TUNING_METHOD == Button__TUNING_AUTO)) )
    uint16 Button_MedianFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* ( (0u != (Button_RAW_FILTER_MASK & Button_MEDIAN_FILTER)) || \
      (0u != (Button_POS_FILTERS_MASK & Button_MEDIAN_FILTER)) || \
      ((Button_TUNING_METHOD == Button__TUNING_AUTO)) ) */

/* Averaging filter function prototype */
#if ( (0u != (Button_RAW_FILTER_MASK & Button_AVERAGING_FILTER)) || \
      (0u != (Button_POS_FILTERS_MASK & Button_AVERAGING_FILTER)) )
    uint16 Button_AveragingFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* Button_RAW_FILTER_MASK && Button_POS_FILTERS_MASK */

/* IIR2Filter(1/2prev + 1/2cur) filter function prototype */
#if ( (0u != (Button_RAW_FILTER_MASK & Button_IIR2_FILTER)) || \
      (0u != (Button_POS_FILTERS_MASK & Button_IIR2_FILTER)) )
    uint16 Button_IIR2Filter(uint16 x1, uint16 x2);
#endif /* Button_RAW_FILTER_MASK && Button_POS_FILTERS_MASK */

/* IIR4Filter(3/4prev + 1/4cur) filter function prototype */
#if ( (0u != (Button_RAW_FILTER_MASK & Button_IIR4_FILTER)) || \
      (0u != (Button_POS_FILTERS_MASK & Button_IIR4_FILTER)) )
    uint16 Button_IIR4Filter(uint16 x1, uint16 x2);
#endif /* Button_RAW_FILTER_MASK && Button_POS_FILTERS_MASK */

/* IIR8Filter(7/8prev + 1/8cur) filter function prototype - RawCounts only */
#if (0u != (Button_RAW_FILTER_MASK & Button_IIR8_FILTER))
    uint16 Button_IIR8Filter(uint16 x1, uint16 x2);
#endif /* Button_RAW_FILTER_MASK */

/* IIR16Filter(15/16prev + 1/16cur) filter function prototype - RawCounts only */
#if (0u != (Button_RAW_FILTER_MASK & Button_IIR16_FILTER))
    uint16 Button_IIR16Filter(uint16 x1, uint16 x2);
#endif /* Button_RAW_FILTER_MASK */

/* JitterFilter filter function prototype */
#if ( (0u != (Button_RAW_FILTER_MASK & Button_JITTER_FILTER)) || \
      (0u != (Button_POS_FILTERS_MASK & Button_JITTER_FILTER)) || \
      (0u != (Button_TRACKPAD_GEST_POS_FILTERS_MASK & Button_JITTER_FILTER)))
    uint16 Button_JitterFilter(uint16 x1, uint16 x2);
#endif /* ( (0u != (Button_RAW_FILTER_MASK & Button_JITTER_FILTER)) || \
       *    (0u != (Button_POS_FILTERS_MASK & Button_JITTER_FILTER)) )
       *    (0u != (Button_TRACKPAD_GEST_POS_FILTERS_MASK & Button_JITTER_FILTER)) )
       */


/***************************************
*     Vars with External Linkage
***************************************/
extern uint16 Button_sensorBaseline[Button_TOTAL_SENSOR_COUNT];
extern uint8  Button_sensorBaselineLow[Button_TOTAL_SENSOR_COUNT];
extern uint8 Button_sensorSignal[Button_TOTAL_SENSOR_COUNT];
extern uint8  Button_sensorOnMask[Button_TOTAL_SENSOR_MASK];

extern uint8 Button_lowBaselineResetCnt[Button_TOTAL_SENSOR_COUNT];
extern uint8 Button_lowBaselineReset[Button_TOTAL_SENSOR_COUNT];

/* Generated by Customizer */
#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    extern uint8 Button_fingerThreshold[Button_WIDGET_PARAM_TBL_SIZE];
    extern uint8 Button_noiseThreshold[Button_WIDGET_PARAM_TBL_SIZE];
    extern uint8 Button_negativeNoiseThreshold[Button_WIDGET_PARAM_TBL_SIZE];
    extern uint8 Button_hysteresis[Button_WIDGET_PARAM_TBL_SIZE];
    extern uint8  Button_debounce[Button_WIDGET_PARAM_TBL_SIZE];
#else
    extern const uint8 Button_fingerThreshold[Button_WIDGET_PARAM_TBL_SIZE];
    extern const uint8 Button_noiseThreshold[Button_WIDGET_PARAM_TBL_SIZE];
    extern const uint8 Button_hysteresis[Button_WIDGET_PARAM_TBL_SIZE];
    extern const uint8  Button_debounce[Button_WIDGET_PARAM_TBL_SIZE];
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */

extern const uint8 Button_rawDataIndex[Button_RAW_DATA_INDEX_TBL_SIZE];
extern const uint8 Button_numberOfSensors[Button_RAW_DATA_INDEX_TBL_SIZE];

#if (0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT)
    #if (Button_TUNING_METHOD != Button__TUNING_NONE)
        extern uint8 Button_posFiltersMask[Button_TOTAL_CENTROID_AXES_COUNT];
    #else
        extern const uint8 Button_posFiltersMask[Button_TOTAL_CENTROID_AXES_COUNT];
    #endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */

    extern uint32 Button_centroidMult[Button_TOTAL_CENTROID_AXES_COUNT];
#endif /* (0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT) */

/***************************************
*        Obsolete Names
***************************************/
#define Button_SensorRaw              Button_sensorRaw
#define Button_SensorEnableMask       Button_sensorEnableMask
#define Button_SensorBaseline         Button_sensorBaseline
#define Button_SensorBaselineLow      Button_sensorBaselineLow
#define Button_SensorSignal           Button_sensorSignal
#define Button_SensorOnMask           Button_sensorOnMask
#define Button_LowBaselineResetCnt    Button_lowBaselineResetCnt

#endif /* CY_CAPSENSE_CSD_CSHL_Button_H */

/* [] END OF FILE */
