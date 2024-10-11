/*******************************************************************************
* File Name: Button.h
* Version 2.60
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_Button_H)
#define CY_CAPSENSE_CSD_Button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "core_cm0_psoc4.h"
#include "CyLib.h"

#include "Button_IP.h"
#include "Button_SenseClk.h"
#include "Button_SampleClk.h"

/* Constants set by Customizer */
#define Button_TOTAL_SENSOR_COUNT            (4u)
#define Button_TOTAL_SCANSLOT_COUNT          (4u)
#define Button_INDEX_TABLE_SIZE              (0u)

/* Define Sensors */
#define Button_SENSOR_BUTTON0__BTN    (0u)
#define Button_SENSOR_BUTTON1__BTN    (1u)
#define Button_SENSOR_BUTTON2__BTN    (2u)
#define Button_SENSOR_BUTTON3__BTN    (3u)

#define Button_TOTAL_SENSOR_MASK (((Button_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)

/* Interrupt handler */
CY_ISR_PROTO(Button_ISR);

/* ISR Number and Priority to work with CyLib functions */
#define Button_ISR_NUMBER        (Button_ISR__INTC_NUMBER)
#define Button_ISR_PRIORITY      (Button_ISR__INTC_PRIOR_NUM)

/***************************************
*   Condition compilation parameters
***************************************/

#define Button_CONNECT_INACTIVE_SNS       (0u)
#define Button_IS_COMPLEX_SCANSLOTS       (0u)
#define Button_COMPLEX_SCANSLOTS_NUM      (0u)
#define Button_DEDICATED_SENSORS_NUM      (0u)
#define Button_PORT_PIN_CONFIG_TBL_ZISE   (4u)

#define Button_IDAC_CNT                   (2u)
#define Button_IDAC1_POLARITY             (0u)
#define Button_IDAC1_RANGE_VALUE          (0u)
#define Button_IDAC2_RANGE_VALUE          (0u)

#define Button_MULTIPLE_FREQUENCY_SET     (1u)
#define Button_FILTER_ENABLE              (0u)
#define Button_PRS_OPTIONS                (0u)

#define Button_WATER_PROOF                (0u)

#define Button_TUNING_METHOD              (2u)
#define Button_TUNER_API_GENERATE         (0u)

#define Button_CSHL_API_GENERATE          (1u)

#define Button_CMOD_PREGARGE_OPTION       (1u)
#define Button_CSH_TANK_PREGARGE_OPTION   (1u)
#define Button_IS_SHIELD_ENABLE           (0u)
#define Button_CSH_TANK_ENABLE            (0u)

#define Button_SHIELD_DELAY               (0u)
#define Button_AUTOCALIBRATION_ENABLE     (0u)

#define Button_IS_OVERSAMPLING_EN         (1u)

#define Button_CSD_4B_PWM_MODE            (0u)
#define Button_CSD_4B_PWM_COUNT           (0u)

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* Current source definitions */
#define Button__IDAC_SOURCE 0
#define Button__IDAC_SINK 1

#define Button__IDAC_4X 0
#define Button__IDAC_8X 1

#define Button__PRS_NONE 0
#define Button__PRS_8BITS 1
#define Button__PRS_12BITS 2
#define Button__PRS_AUTO 3

/* Connection of inactive sensors definitions */
#define Button__GROUND 0
#define Button__HIZ_ANALOG 1
#define Button__SHIELD 2

/* Precharge options definitions */
#define Button__CAPPRIOBUF 0
#define Button__CAPPRVREF 1

/* Method of tuning */
#define Button__TUNING_NONE 0
#define Button__TUNING_MANUAL 1
#define Button__TUNING_AUTO 2

/* Dead band PWM modulator options */
#define Button__PWM_OFF 0
#define Button__PWM_HIGH 2
#define Button__PWM_LOW 3


#define Button_DELAY_EXTRACYCLES_NUM          (9u)
#define Button_GLITCH_ELIMINATION_TIMEOUT     (0u)
#define Button_GLITCH_ELIMINATION_CYCLES_CALC (Button_GLITCH_ELIMINATION_TIMEOUT * CYDEV_BCLK__SYSCLK__MHZ)

#if(Button_GLITCH_ELIMINATION_CYCLES_CALC >= Button_DELAY_EXTRACYCLES_NUM)
    #define Button_GLITCH_ELIMINATION_CYCLES (Button_GLITCH_ELIMINATION_CYCLES_CALC -\
                                                        Button_DELAY_EXTRACYCLES_NUM)
#else
    #define Button_GLITCH_ELIMINATION_CYCLES (Button_GLITCH_ELIMINATION_CYCLES_CALC)
#endif /* (Button_GLITCH_ELIMINATION_CYCLES_CALC >= Button_DELAY_EXTRACYCLES_NUM) */

#define Button_INITIAL_CLK_DIVIDER            (CYDEV_BCLK__HFCLK__KHZ / CYDEV_BCLK__SYSCLK__KHZ)


/* Structure to save registers before going to sleep */
typedef struct
{
    uint8 enableState;
} Button_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/
void Button_Init(void);
void Button_CsdHwBlockInit(void);
void Button_Enable(void);
void Button_Start(void);
void Button_Stop(void);
void Button_SaveConfig(void);
void Button_Sleep(void);
void Button_RestoreConfig(void);
void Button_Wakeup(void);
uint32 Button_IsBusy(void);
void Button_ScanSensor(uint32 sensor);
void Button_ScanWidget(uint32 widget);
void Button_ScanEnabledWidgets(void);
uint16 Button_ReadSensorRaw(uint32 sensor);
void Button_WriteSensorRaw(uint32 sensor, uint16 value);
void Button_ClearSensors(void);
void Button_SetShieldDelay(uint32 delay);
uint32 Button_ReadCurrentScanningSensor(void);

uint32 Button_GetScanResolution(uint32 widget);
uint32 Button_GetSenseClkDivider(uint32 sensor);
uint32 Button_GetModulatorClkDivider(uint32 sensor);
uint32 Button_GetModulationIDAC(uint32 sensor);
uint32 Button_GetCompensationIDAC(uint32 sensor);
uint32 Button_GetIDACRange(void);

#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    void Button_SetScanResolution(uint32 widget, uint32 resolution);
    void Button_SetSenseClkDivider(uint32 sensor, uint32 senseClk);
    void Button_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk);
    void Button_SetModulationIDAC(uint32 sensor, uint32 modIdacValue);
    void Button_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue);
    void Button_SetIDACRange(uint32 iDacRange);
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */


void Button_SetDriveModeAllPins(uint32 driveMode);
void Button_RestoreDriveModeAllPins(void);
void Button_SetUnscannedSensorState(uint32 sensor, uint32 sensorState);
void Button_NormalizeWidgets(uint32 widgetsNum, uint8 dataPtr[]);

/***************************************
*           API Constants
***************************************/

/* PWM Resolution */
#define Button_CNT_MSB_RESOLUTION_8_BITS  (0x00u)
#define Button_CNT_MSB_RESOLUTION_9_BITS  (0x01u)
#define Button_CNT_MSB_RESOLUTION_10_BITS (0x03u)
#define Button_CNT_MSB_RESOLUTION_11_BITS (0x07u)
#define Button_CNT_MSB_RESOLUTION_12_BITS (0x0Fu)
#define Button_CNT_MSB_RESOLUTION_13_BITS (0x1Fu)
#define Button_CNT_MSB_RESOLUTION_14_BITS (0x3Fu)
#define Button_CNT_MSB_RESOLUTION_15_BITS (0x7Fu)
#define Button_CNT_MSB_RESOLUTION_16_BITS (0xFFu)

#define Button_ONE_CYCLE                  (0x00010000Lu)

#define Button_WINDOW_APPEND              (0xFFFF0000Lu)
#define Button_RESOLUTION_6_BITS          (0x003F0000Lu)
#define Button_RESOLUTION_7_BITS          (0x007F0000Lu)
#define Button_RESOLUTION_8_BITS          (0x00FF0000Lu)
#define Button_RESOLUTION_9_BITS          (0x01FF0000Lu)
#define Button_RESOLUTION_10_BITS         (0x03FF0000Lu)
#define Button_RESOLUTION_11_BITS         (0x07FF0000Lu)
#define Button_RESOLUTION_12_BITS         (0x0FFF0000Lu)
#define Button_RESOLUTION_13_BITS         (0x1FFF0000Lu)
#define Button_RESOLUTION_14_BITS         (0x3FFF0000Lu)
#define Button_RESOLUTION_15_BITS         (0x7FFF0000Lu)
#define Button_RESOLUTION_16_BITS         (0xFFFF0000Lu)

#define Button_RESOLUTION_OFFSET          (16u)
#define Button_MSB_RESOLUTION_OFFSET      (22u)
#define Button_RESOLUTIONS_TBL_SIZE       (4u)

/* Software Status Register Bit Masks */
#define Button_SW_STS_BUSY                (0x01u)
/* Software Control Register Bit Masks */
#define Button_SW_CTRL_SINGLE_SCAN        (0x80u)

/* Software Control Register Bit Masks for scanning one widget */
#define Button_SW_CTRL_WIDGET_SCAN        (0x40u)

/* Flag for complex scan slot */
#define Button_COMPLEX_SS_FLAG            (0x80u)

/* Flag for scanning is complete */
#define Button_NOT_SENSOR                 (0xFFFFFFFFLu)

/* Number of bits for each pin in PC register. */
#define Button_PC_PIN_CFG_SIZE            (0x03u)

/* Number of bits for each pin in HSIOM register. */
#define Button_HSIOM_PIN_CFG_SIZE         (0x04u)

#define Button_CFG_REG_TBL_SIZE           (5u)

/***************************************
*             Registers
***************************************/

#define Button_CSD_ID_REG             (*(reg32 *)  Button_CSD_FFB__CSD_ID)
#define Button_CSD_ID_PTR             ( (reg32 *)  Button_CSD_FFB__CSD_ID)

#define Button_CSD_CFG_REG            (*(reg32 *)  Button_CSD_FFB__CSD_CONFIG)
#define Button_CSD_CFG_PTR            ( (reg32 *)  Button_CSD_FFB__CSD_CONFIG)

#define Button_CSD_IDAC_REG           (*(reg32 *)  Button_IDAC1_cy_psoc4_idac__CSD_IDAC)
#define Button_CSD_IDAC_PTR           ( (reg32 *)  Button_IDAC1_cy_psoc4_idac__CSD_IDAC)

#define Button_CSD_CNT_REG            (*(reg32 *) Button_CSD_FFB__CSD_COUNTER)
#define Button_CSD_CNT_PTR            ( (reg32 *) Button_CSD_FFB__CSD_COUNTER)

#define Button_CSD_STAT_REG           (*(reg32 *) Button_CSD_FFB__CSD_STATUS)
#define Button_CSD_STAT_PTR           ( (reg32 *) Button_CSD_FFB__CSD_STATUS)

#define Button_CSD_INTR_REG           (*(reg32 *) Button_CSD_FFB__CSD_INTR)
#define Button_CSD_INTR_PTR           ( (reg32 *) Button_CSD_FFB__CSD_INTR)

#define Button_CSD_INTR_SET_REG       (*(reg32 *) Button_CSD_FFB__CSD_INTR_SET)
#define Button_CSD_INTR_SET_PTR       ( (reg32 *) Button_CSD_FFB__CSD_INTR_SET)

#define Button_CSD_4B_PWM_REG         (*(reg32 *) Button_CSD_FFB__CSD_PWM)
#define Button_CSD_4B_PWM_PTR         ( (reg32 *) Button_CSD_FFB__CSD_PWM)

#define Button_CSD_TRIM1_REG          (*(reg32 *) Button_IDAC1_cy_psoc4_idac__CSD_TRIM1)
#define Button_CSD_TRIM1_PTR          ( (reg32 *) Button_IDAC1_cy_psoc4_idac__CSD_TRIM1)

#define Button_CSD_TRIM2_REG          (*(reg32 *) Button_IDAC1_cy_psoc4_idac__CSD_TRIM2)
#define Button_CSD_TRIM2_PTR          ( (reg32 *) Button_IDAC1_cy_psoc4_idac__CSD_TRIM2)

#if (2u == Button_M0S8CSD_BLOCK_CNT)
    #if (Button_CSD_FFB__CSD_NUMBER != 1u)
        #define Button_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
        #define Button_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

        #define Button_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
        #define Button_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #else
        #define Button_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)
        #define Button_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)

        #define Button_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
        #define Button_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
    #endif /* (Button_CSD_FFB__CSD_NUMBER != 1u) */
#else
    #define Button_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
    #define Button_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

    #define Button_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #define Button_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
#endif /* (2u == Button_M0S8CSD_BLOCK_CNT) */

/* Port function select */
#define Button_PORT_SEL0_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )
#define Button_PORT_SEL0_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )

#define Button_PORT_SEL1_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )
#define Button_PORT_SEL1_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )

#define Button_PORT_SEL2_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )
#define Button_PORT_SEL2_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )

#define Button_PORT_SEL3_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )
#define Button_PORT_SEL3_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )

#define Button_PORT_SEL4_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )
#define Button_PORT_SEL4_PTR          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )


#define Button_PORT0_PC_REG          (*(reg32 *) CYREG_PRT0_PC )
#define Button_PORT0_PC_PTR          (*(reg32 *) CYREG_PRT0_PC )

#define Button_PORT1_PC_REG          (*(reg32 *) CYREG_PRT1_PC )
#define Button_PORT1_PC_PTR          (*(reg32 *) CYREG_PRT1_PC )

#define Button_PORT2_PC_REG          (*(reg32 *) CYREG_PRT2_PC )
#define Button_PORT2_PC_PTR          (*(reg32 *) CYREG_PRT2_PC )

#define Button_PORT3_PC_REG          (*(reg32 *) CYREG_PRT3_PC )
#define Button_PORT3_PC_PTR          (*(reg32 *) CYREG_PRT3_PC )

#define Button_PORT4_PC_REG          (*(reg32 *) CYREG_PRT4_PC )
#define Button_PORT4_PC_PTR          (*(reg32 *) CYREG_PRT4_PC )


#define Button_PORT0_DR_REG          (*(reg32 *) CYREG_PRT0_DR )
#define Button_PORT0_DR_PTR          (*(reg32 *) CYREG_PRT0_DR )

#define Button_PORT1_DR_REG          (*(reg32 *) CYREG_PRT1_DR )
#define Button_PORT1_DR_PTR          (*(reg32 *) CYREG_PRT1_DR )

#define Button_PORT2_DR_REG          (*(reg32 *) CYREG_PRT2_DR )
#define Button_PORT2_DR_PTR          (*(reg32 *) CYREG_PRT2_DR )

#define Button_PORT3_DR_REG          (*(reg32 *) CYREG_PRT3_DR )
#define Button_PORT3_DR_PTR          (*(reg32 *) CYREG_PRT3_DR )

#define Button_PORT4_DR_REG          (*(reg32 *) CYREG_PRT4_DR )
#define Button_PORT4_DR_PTR          (*(reg32 *) CYREG_PRT4_DR )



#define Button_CMOD_CONNECTION_REG        (*(reg32 *) Button_Cmod__0__HSIOM)
#define Button_CMOD_PORT_PC_REG           (*(reg32 *) Button_Cmod__0__PC)
#define Button_CMOD_PORT_DR_REG           (*(reg32 *) Button_Cmod__0__DR)

#define Button_CTANK_CONNECTION_REG       (*(reg32 *) Button_Csh_tank__0__HSIOM)
#define Button_CTANK_PORT_PC_REG          (*(reg32 *) Button_Csh_tank__0__PC)
#define Button_CTANK_PORT_DR_REG          (*(reg32 *) Button_Csh_tank__0__DR)

/***************************************
*       Register Constants
***************************************/

/* Port configuration defines */
#define Button_CSD_HSIOM_MASK                 (0x0000000FLu)

#define Button_CSD_SENSE_PORT_MODE            (0x00000004Lu)
#define Button_CSD_SHIELD_PORT_MODE           (0x00000005Lu)

#define Button_AMUXA_CONNECTION_MODE          (0x00000006Lu)
#define Button_AMUXB_CONNECTION_MODE          (0x00000007Lu)

#define Button_CSD_PIN_MODE_MASK              (0x00000007Lu)
#define Button_CSD_PIN_DRIVE_MASK             (0x00000001Lu)

#define Button_CSD_PIN_DM_STRONG              (0x00000006Lu)
#define Button_CSD_PIN_DM_HIGH_Z              (0x00000000Lu)

#define Button_CSD_CMOD_CONNECTION_MASK   (uint32)(Button_Cmod__0__HSIOM_MASK)
#define Button_CSD_CMOD_TO_AMUXBUS_A      (uint32)(Button_AMUXA_CONNECTION_MODE << Button_Cmod__0__HSIOM_SHIFT)
#define Button_CSD_CMOD_TO_AMUXBUS_B      (uint32)(Button_AMUXB_CONNECTION_MODE << Button_Cmod__0__HSIOM_SHIFT)

#if(0u != Button_CSH_TANK_ENABLE)
    #define Button_CSD_CTANK_CONNECTION_MASK  (uint32)(Button_Csh_tank__0__HSIOM_MASK)
    #define Button_CSD_CTANK_TO_AMUXBUS_A     (uint32)(Button_AMUXA_CONNECTION_MODE << Button_Csh_tank__0__HSIOM_SHIFT)
    #define Button_CSD_CTANK_TO_AMUXBUS_B     (uint32)(Button_AMUXB_CONNECTION_MODE << Button_Csh_tank__0__HSIOM_SHIFT)
#endif /* (0u != Button_CSH_TANK_ENABLE) */

#define  Button_CSD_CMOD_PC_MASK          (uint32)(Button_CSD_PIN_MODE_MASK <<\
                                                            ((uint32)Button_Cmod__0__SHIFT * Button_PC_PIN_CFG_SIZE))
#define  Button_CMOD_PC_STRONG_MODE       (uint32)(Button_CSD_PIN_DM_STRONG <<\
                                                            ((uint32)Button_Cmod__0__SHIFT * Button_PC_PIN_CFG_SIZE))
#define  Button_CMOD_PC_HIGH_Z_MODE       (uint32)(Button_CSD_PIN_DM_HIGH_Z <<\
                                                            ((uint32)Button_Cmod__0__SHIFT * Button_PC_PIN_CFG_SIZE))

#if(0u != Button_CSH_TANK_ENABLE)
    #define  Button_CSD_CTANK_PC_MASK         (uint32)(Button_CSD_PIN_MODE_MASK <<\
                                                                ((uint32)Button_Csh_tank__0__SHIFT * Button_PC_PIN_CFG_SIZE))
    #define  Button_CTANK_PC_STRONG_MODE      (uint32)(Button_CSD_PIN_DM_STRONG <<\
                                                                ((uint32)Button_Csh_tank__0__SHIFT * Button_PC_PIN_CFG_SIZE))
    #define  Button_CTANK_PC_HIGH_Z_MODE      (uint32)(Button_CSD_PIN_DM_HIGH_Z <<\
                                                                ((uint32)Button_Csh_tank__0__SHIFT * Button_PC_PIN_CFG_SIZE))
#endif /* (0u != Button_CSH_TANK_ENABLE) */

#define  Button_CMOD_DR_VSSIO             (uint32)(Button_Cmod__0__MASK)
#define  Button_CMOD_DR_VDDIO             (0x00000000Lu)
#define  Button_CMOD_DR_MASK              (uint32)(Button_Cmod__0__MASK)

#if(0u != Button_CSH_TANK_ENABLE)
    #define  Button_CTANK_DR_VSSIO            (uint32)(Button_Csh_tank__0__MASK)
    #define  Button_CTANK_DR_VDDIO            (0x00000000Lu)
    #define  Button_CTANK_DR_MASK             (uint32)(Button_Csh_tank__0__MASK)
#endif /* (0u != Button_CSH_TANK_ENABLE) */

#define  Button_CMOD_PIN_NUMBER               (Button_Cmod__0__SHIFT)
#define  Button_CMOD_PRT_NUMBER               (Button_Cmod__0__PORT)

#if(0u != Button_CSH_TANK_ENABLE)
    #define  Button_CTANK_PIN_NUMBER          (Button_Csh_tank__0__SHIFT)
    #define  Button_CTANK_PRT_NUMBER          (Button_Csh_tank__0__PORT)
#endif /* (0u != Button_CSH_TANK_ENABLE) */

/* ID register fields position */
#define Button_CSD_ID_ID__POS                 (0x00u)
#define Button_CSD_ID_REV__POS                (0x10u)

#define Button_CSD_ID_ID                      (0xFFLu << Button_CSD_ID_ID__POS)
#define Button_CSD_ID_REV                     (0xFFLu << Button_CSD_ID_REV__POS)

/* CSD_CONFIG register fields position */
#define Button_CSD_CFG_DSI_SAMPLE_EN_POS      (0x00u)
#define Button_CSD_CFG_SAMPLE_SYNC_POS        (0x01u)
#define Button_CSD_CFG_FILTER_EN_POS          (0x03u)
#define Button_CSD_CFG_PRS_CLEAR_POS          (0x05u)
#define Button_CSD_CFG_PRS_SELECT_POS         (0x06u)
#define Button_CSD_CFG_PRS_12_8_POS           (0x07u)
#define Button_CSD_CFG_DSI_SENSE_EN_POS       (0x08u)
#define Button_CSD_CFG_SHIELD_DELAY_POS       (0x09u)
#define Button_CSD_CFG_SENSE_COMP_BW_POS      (0x0Bu)
#define Button_CSD_CFG_SENSE_EN_POS           (0x0Cu)
#define Button_CSD_CFG_REFBUF_EN_POS          (0x0Du)
#define Button_CSD_CFG_CHARGE_IO_POS          (0x0Eu)
#define Button_CSD_CFG_COMP_PIN_POS           (0x0Fu)
#define Button_CSD_CFG_POLARITY_POS           (0x10u)
#define Button_CSD_CFG_MUTUAL_CAP_POS         (0x12u)
#define Button_CSD_CFG_SENSE_COMP_EN_POS      (0x13u)
#define Button_CSD_CFG_REFBUF_OUTSEL_POS      (0x15u)
#define Button_CSD_CFG_SENSE_INSEL_POS        (0x16u)
#define Button_CSD_REFBUF_DRV_POS             (0x17u)
#define Button_CSD_CFG_DDFTSEL_POS            (0x1Au)
#define Button_CSD_CFG_ADFTEN_POS             (0x1Du)
#define Button_CSD_CFG_DDFTCOMP_POS           (0x1Eu)
#define Button_CSD_CFG_ENABLE_POS             (0x1Fu)

/* CSD_STATUS register fields position */
#define Button_CSD_STAT_CSD_CHARGE_POS        (0x00u)
#define Button_CSD_STAT_CSD_SENSE_POS         (0x01u)
#define Button_CSD_STAT_COMP_OUT_POS          (0x02u)
#define Button_CSD_STAT_SAMPLE_POS            (0x03u)

/* CSD_IDAC control register fields position */
#define Button_CSD_IDAC1_MODE_MASK_POS        (0x08u)
#define Button_CSD_IDAC1_MODE_FIXED_POS       (0x08u)
#define Button_CSD_IDAC1_MODE_VARIABLE_POS    (0x08u)
#define Button_CSD_IDAC1_MODE_DSI_POS         (0x08u)
#define Button_CSD_IDAC1_RANGE_8X_POS         (0x0Au)
#define Button_CSD_IDAC1_DATA_MASK_POS        (0x00u)

#define Button_CSD_IDAC2_MODE_MASK_POS        (0x18u)
#define Button_CSD_IDAC2_MODE_FIXED_POS       (0x18u)
#define Button_CSD_IDAC2_MODE_VARIABLE_POS    (0x18u)
#define Button_CSD_IDAC2_MODE_DSI_POS         (0x18u)
#define Button_CSD_IDAC2_RANGE_8X_POS         (0x1Au)
#define Button_CSD_IDAC2_DATA_MASK_POS        (0x10u)

/* CSD_COUNTER register fields position */
#define Button_CSD_CNT_COUNTER_POS            (0x00u)
#define Button_CSD_CNT_PERIOD_POS             (0x10u)

/* CSD_CONFIRG register definitions */
#define Button_CSD_CFG_DSI_SAMPLE_EN          (0x01Lu << Button_CSD_CFG_DSI_SAMPLE_EN_POS)
#define Button_CSD_CFG_SAMPLE_SYNC            (0x01Lu << Button_CSD_CFG_SAMPLE_SYNC_POS)
#define Button_CSD_CFG_FILTER_EN              (0x01Lu << Button_CSD_CFG_FILTER_EN_POS)
#define Button_CSD_CFG_PRS_CLEAR              (0x01Lu << Button_CSD_CFG_PRS_CLEAR_POS)
#define Button_CSD_CFG_PRS_SELECT             (0x01Lu << Button_CSD_CFG_PRS_SELECT_POS)
#define Button_CSD_CFG_PRS_12_8               (0x01Lu << Button_CSD_CFG_PRS_12_8_POS)
#define Button_CSD_CFG_DSI_SENSE_EN           (0x01Lu << Button_CSD_CFG_DSI_SENSE_EN_POS)
#define Button_CSD_CFG_SHIELD_DELAY_MASK      (0x03Lu << Button_CSD_CFG_SHIELD_DELAY_POS)
#define Button_CSD_CFG_SENSE_COMP_BW          (0x01Lu << Button_CSD_CFG_SENSE_COMP_BW_POS)
#define Button_CSD_CFG_SENSE_EN               (0x01Lu << Button_CSD_CFG_SENSE_EN_POS)
#define Button_CSD_CFG_REFBUF_EN              (0x01Lu << Button_CSD_CFG_REFBUF_EN_POS)
#define Button_CSD_CFG_CHARGE_IO              (0x01Lu << Button_CSD_CFG_CHARGE_IO_POS)
#define Button_CSD_CFG_COMP_PIN_CH2           (0x01Lu << Button_CSD_CFG_COMP_PIN_POS)
#define Button_CSD_CFG_POLARITY_VDDIO         (0x01Lu << Button_CSD_CFG_POLARITY_POS)
#define Button_CSD_CFG_MUTUAL_CAP             (0x01Lu << Button_CSD_CFG_MUTUAL_CAP_POS)
#define Button_CSD_CFG_SENSE_COMP_EN          (0x01Lu << Button_CSD_CFG_SENSE_COMP_EN_POS)
#define Button_CSD_CFG_REFBUF_OUTSEL          (0x01Lu << Button_CSD_CFG_REFBUF_OUTSEL_POS)
#define Button_CSD_CFG_SENSE_INSEL            (0x01Lu << Button_CSD_CFG_SENSE_INSEL_POS)
#define Button_CSD_REFBUF_DRV_MASK            (0x03Lu << Button_CSD_REFBUF_DRV_POS)
#define Button_CSD_REFBUF_DRV_LOW             (0x01Lu << Button_CSD_REFBUF_DRV_POS)
#define Button_CSD_REFBUF_DRV_MEDIUM          (0x02Lu << Button_CSD_REFBUF_DRV_POS)
#define Button_CSD_REFBUF_DRV_HIGH            (0x03Lu << Button_CSD_REFBUF_DRV_POS)
#define Button_CSD_CFG_DDFTSEL_MASK           (0x07Lu << Button_CSD_CFG_DDFTSEL_POS)
#define Button_CSD_CFG_ADFTEN                 (0x01Lu << Button_CSD_CFG_ADFTEN_POS)
#define Button_CSD_CFG_DDFTCOMP_MASK          (0x03Lu << Button_CSD_CFG_DDFTCOMP_POS)
#define Button_CSD_CFG_DDFTCOMP_REFCOMP       (0x01Lu << Button_CSD_CFG_DDFTCOMP_POS)
#define Button_CSD_CFG_DDFTCOMP_SENSECOMP     (0x02Lu << Button_CSD_CFG_DDFTCOMP_POS)
#define Button_CSD_CFG_ENABLE                 (0x01Lu << Button_CSD_CFG_ENABLE_POS)

/* CSD_STATUS register definitions */
#define Button_CSD_STAT_CSD_CHARGE            (0x01Lu << Button_CSD_STAT_CSD_CHARGE_POS)
#define Button_CSD_STAT_CSD_SENSE             (0x01Lu << Button_CSD_STAT_CSD_SENSE_POS)
#define Button_CSD_STAT_COMP_OUT              (0x01Lu << Button_CSD_STAT_COMP_OUT_POS)
#define Button_CSD_STAT_SAMPLE                (0x01Lu << Button_CSD_STAT_SAMPLE_POS)

/* CSD_IDAC control register definitions */
#define Button_CSD_IDAC1_MODE_MASK            (0x03Lu << Button_CSD_IDAC1_MODE_MASK_POS)
#define Button_CSD_IDAC1_MODE_FIXED           (0x01Lu << Button_CSD_IDAC1_MODE_FIXED_POS)
#define Button_CSD_IDAC1_MODE_VARIABLE        (0x02Lu << Button_CSD_IDAC1_MODE_VARIABLE_POS)
#define Button_CSD_IDAC1_MODE_DSI             (0x03Lu << Button_CSD_IDAC1_MODE_DSI_POS)
#define Button_CSD_IDAC1_RANGE_8X             (0x01Lu << Button_CSD_IDAC1_RANGE_8X_POS)
#define Button_CSD_IDAC1_DATA_MASK            (0xFFLu << Button_CSD_IDAC1_DATA_MASK_POS)

#define Button_CSD_IDAC2_MODE_MASK            (0x03Lu << Button_CSD_IDAC2_MODE_MASK_POS)
#define Button_CSD_IDAC2_MODE_FIXED           (0x01Lu << Button_CSD_IDAC2_MODE_FIXED_POS)
#define Button_CSD_IDAC2_MODE_VARIABLE        (0x02Lu << Button_CSD_IDAC2_MODE_VARIABLE_POS)
#define Button_CSD_IDAC2_MODE_DSI             (0x03Lu << Button_CSD_IDAC2_MODE_DSI_POS)
#define Button_CSD_IDAC2_RANGE_8X             (0x01Lu << Button_CSD_IDAC2_RANGE_8X_POS)
#define Button_CSD_IDAC2_DATA_MASK            (0x7FLu << Button_CSD_IDAC2_DATA_MASK_POS)

#define Button_CSD_IDAC2_DATA_OFFSET          (16u)

#define Button_CSD_IDAC1_TRIM_MASK            (0xFFFFFFF0u)
#define Button_CSD_IDAC2_TRIM_MASK            (0xFFFFFF0Fu)

#define Button_CSFLASH_TRIM_IDAC1_MASK        (0x0Fu)
#define Button_CSFLASH_TRIM_IDAC2_MASK        (0xF0)

#define Button_CSD_4B_PWM_MODE_OFFSET         (4u)
#define Button_CSD_4B_PWM_MODE_DEFAULT        (Button_CSD_4B_PWM_MODE << Button_CSD_4B_PWM_MODE_OFFSET)

#define Button_CSD_4B_PWM_COUNT_MASK          (0x0000000Fu)
#define Button_CSD_4B_PWM_MODE_MASK           (0x00000030u)

#define Button_CSD_IDAC_PRECHARGE_CONFIG      (Button_CSD_IDAC1_MODE_FIXED |\
                                                        Button_PRECHARGE_IDAC1_VAL)

/* CSD_COUNTER register definitions */
#define Button_CSD_CNT_COUNTER                (0xFFLu << Button_CSD_CNT_COUNTER_POS )
#define Button_CSD_CNT_PERIOD                 (0xFFLu << Button_CSD_CNT_PERIOD_POS)

#define Button_CSD_PRS_8_BIT                  (0x00000000u)
#define Button_CSD_PRS_12_BIT                 (Button_CSD_CFG_PRS_12_8)
#define Button_PRS_MODE_MASK                  (Button_CSD_CFG_PRS_12_8)

/***************************************
*    Initial Parameter Constants
***************************************/

#if (0u != Button_FILTER_ENABLE)
    #define Button_DEFAULT_FILTER_STATE       (Button_CSD_CFG_FILTER_EN)

#else
    #define Button_DEFAULT_FILTER_STATE       (0u)

#endif /* (Button_PRS_OPTIONS == Button_PRS_8BITS) */

#define Button_DEFAULT_CSD_4B_PWM_CONFIG      (Button_CSD_4B_PWM_MODE_DEFAULT | Button_CSD_4B_PWM_COUNT)

/* Set PRS */
#if (Button_PRS_OPTIONS == Button__PRS_8BITS)
    #define Button_DEFAULT_MODULATION_MODE    Button_CSD_CFG_PRS_SELECT

#elif (Button_PRS_OPTIONS == Button__PRS_12BITS)
    #define Button_DEFAULT_MODULATION_MODE    (Button_CSD_CFG_PRS_12_8 |\
                                                        Button_CSD_CFG_PRS_SELECT)
#else
    #define Button_DEFAULT_MODULATION_MODE    (0u)
#endif /* (Button_PRS_OPTIONS == Button_PRS_8BITS) */

/* Set IDAC ranges */
#if (Button_IDAC1_RANGE_VALUE == Button__IDAC_8X)
    #define Button_DEFAULT_IDAC1_RANGE        Button_CSD_IDAC1_RANGE_8X
    #define Button_DEFAULT_IDAC2_RANGE        Button_CSD_IDAC2_RANGE_8X
#else
    #define Button_DEFAULT_IDAC1_RANGE        (0u)
    #define Button_DEFAULT_IDAC2_RANGE        (0u)
#endif /* (Button_IDAC1_RANGE_VALUE == Button_IDAC_RANGE_8X) */

/* Set IDAC polarity */
#if(Button_IDAC1_POLARITY == Button__IDAC_SINK)

    #define Button_DEFAULT_IDAC_POLARITY      Button_CSD_CFG_POLARITY_VDDIO
    #define Button_CMOD_DR_CONFIG             Button_CMOD_DR_VDDIO
    #define Button_CTANK_DR_CONFIG            Button_CTANK_DR_VDDIO
#else

    #define Button_DEFAULT_IDAC_POLARITY      (0u)
    #define Button_CMOD_DR_CONFIG             Button_CMOD_DR_VSSIO
    #define Button_CTANK_DR_CONFIG            Button_CTANK_DR_VSSIO
#endif /* (Button_IDAC_OPTIONS == Button_IDAC_SINK) */

#define Button_SNS_GROUND_CONNECT             (6u)
#define Button_SNS_HIZANALOG_CONNECT          (0u)

/* Inactive sensors connection configuration */
#if (Button_CONNECT_INACTIVE_SNS == Button__GROUND)
    #define Button_CSD_INACTIVE_CONNECT       (Button_SNS_GROUND_CONNECT)
#else
    #define Button_CSD_INACTIVE_CONNECT       (Button_SNS_HIZANALOG_CONNECT)
#endif /* Button_CONNECT_INACTIVE_SNS == Button__GROUND */

#if(Button_IS_SHIELD_ENABLE)
    #define Button_SHIELD_PORT_NUMBER Button_Shield__PORT
    #define Button_SHIELD_PIN_NUMBER  Button_Shield__SHIFT
#endif /* (Button_IS_SHIELD_ENABLE) */

/* Defining default CSD configuration according to settings in customizer. */
#define Button_DEFAULT_CSD_CONFIG             (Button_DEFAULT_FILTER_STATE |\
                                                         Button_DEFAULT_MODULATION_MODE |\
                                                         Button_CSD_CFG_SENSE_COMP_BW |\
                                                         Button_DEFAULT_IDAC_POLARITY |\
                                                         Button_CSD_CFG_REFBUF_OUTSEL |\
                                                         Button_CSD_REFBUF_DRV_HIGH)

#define Button_CSD_CONFIG_MASK                (Button_CSD_CFG_FILTER_EN |\
                                                         Button_CSD_CFG_PRS_SELECT |\
                                                         Button_CSD_CFG_PRS_12_8 |\
                                                         Button_CSD_CFG_SENSE_COMP_BW |\
                                                         Button_CSD_CFG_REFBUF_EN |\
                                                         Button_CSD_CFG_REFBUF_OUTSEL |\
                                                         Button_CSD_CFG_POLARITY_VDDIO |\
                                                         Button_CSD_CFG_REFBUF_OUTSEL  |\
                                                         Button_CSD_REFBUF_DRV_MASK)


/* Defining the default IDACs configuration according to settings in customizer. */
#if (Button_IDAC_CNT == 1u)
    #define Button_DEFAULT_CSD_IDAC_CONFIG    (Button_CSD_IDAC1_MODE_VARIABLE |\
                                                             Button_DEFAULT_IDAC1_RANGE)
#else
    #define Button_DEFAULT_CSD_IDAC_CONFIG    (Button_CSD_IDAC1_MODE_VARIABLE |\
                                                             Button_CSD_IDAC2_MODE_FIXED |\
                                                             Button_DEFAULT_IDAC1_RANGE |\
                                                             Button_DEFAULT_IDAC2_RANGE)
#endif /* (Button_IDAC_CNT == 1u) */

/* Defining mask intended for clearing bits related to pre-charging options. */
#define Button_PRECHARGE_CONFIG_MASK          (Button_CSD_CFG_REFBUF_EN |\
                                                         Button_CSD_CFG_CHARGE_IO |\
                                                         Button_CSD_CFG_COMP_PIN_CH2  |\
                                                         Button_CSD_CFG_REFBUF_OUTSEL)

/* Cmod the precharge mode configuration */
#if(Button_CMOD_PREGARGE_OPTION == Button__CAPPRVREF)

    #define Button_CMOD_PRECHARGE_CONFIG      (Button_CSD_CFG_REFBUF_EN |\
                                                         Button_CSD_CFG_COMP_PIN_CH2)

#else

    #define Button_CMOD_PRECHARGE_CONFIG      (Button_CSD_CFG_REFBUF_OUTSEL |\
                                                         Button_CSD_CFG_REFBUF_EN |\
                                                         Button_CSD_CFG_CHARGE_IO)

#endif /* (Button_CMOD_PREGARGE_OPTION == Button__CAPPRVREF) */

/* Ctank the precharge mode configuration */
#if(Button_CSH_TANK_PREGARGE_OPTION == Button__CAPPRVREF)

    #if(0u != Button_IS_SHIELD_ENABLE)
        #define  Button_CTANK_PRECHARGE_CONFIG    (Button_CSD_CFG_REFBUF_EN |\
                                                             Button_CSD_CFG_PRS_CLEAR |\
                                                             Button_CSD_CFG_REFBUF_OUTSEL)
    #else
        #define  Button_CTANK_PRECHARGE_CONFIG    (Button_CSD_CFG_REFBUF_OUTSEL |\
                                                             Button_CSD_CFG_PRS_CLEAR)
    #endif /* (0u != Button_IS_SHIELD_ENABLE) */

#else

    #define  Button_CTANK_PRECHARGE_CONFIG    (Button_CSD_CFG_REFBUF_OUTSEL |\
                                                         Button_CSD_CFG_REFBUF_EN |\
                                                         Button_CSD_CFG_CHARGE_IO |\
                                                         Button_CSD_CFG_PRS_CLEAR |\
                                                         Button_CSD_CFG_COMP_PIN_CH2)
#endif /* (Button_CSH_TANK_PREGARGE_OPTION == Button__CAPPRIOBUF) */

#define Button_MAX_UINT_8                     (0xFFu)
#define Button_MAX_UINT_16                    (0xFFFFu)
#define Button_MAX_UINT_32                    (0xFFFFFFFFLu)

/***************************************
*     Vars with External Linkage
***************************************/
/* SmartSense functions */
#if (Button_TUNING_METHOD == Button__TUNING_AUTO)
    extern uint8 Button_lowLevelTuningDone;
    extern uint8 Button_scanSpeedTbl[((Button_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
    extern void Button_AutoTune(void);
#endif /* (Button_TUNING_METHOD == Button__TUNING_AUTO) */

#if(Button_PRS_OPTIONS != Button__PRS_NONE)
    extern uint8 Button_prescalersTuningDone;
#endif /* (Button_PRS_OPTIONS == Button__PRS_NONE) */

/* Global software variables */
extern volatile uint8 Button_csdStatusVar;
extern volatile uint8 Button_sensorIndex;
extern uint16 Button_sensorRaw[Button_TOTAL_SENSOR_COUNT];
extern uint8 Button_unscannedSnsDriveMode[Button_PORT_PIN_CONFIG_TBL_ZISE];
extern uint8 Button_sensorEnableMaskBackup[Button_TOTAL_SENSOR_MASK];
extern uint8 Button_sensorEnableMask[Button_TOTAL_SENSOR_MASK];

#if ((Button_TUNING_METHOD != Button__TUNING_NONE) || (0u != Button_AUTOCALIBRATION_ENABLE))
    extern uint8 Button_modulationIDAC[Button_TOTAL_SENSOR_COUNT];
    extern uint8 Button_compensationIDAC[Button_TOTAL_SENSOR_COUNT];
#else
    extern const uint8 Button_modulationIDAC[Button_TOTAL_SENSOR_COUNT];
    extern const uint8 Button_compensationIDAC[Button_TOTAL_SENSOR_COUNT];
#endif /* ((Button_TUNING_METHOD != Button__TUNING_NONE) || (0u != Button_AUTOCALIBRATION_ENABLE)) */

#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    extern uint32 Button_widgetResolution[Button_RESOLUTIONS_TBL_SIZE];
    #if (0u != Button_MULTIPLE_FREQUENCY_SET)
        extern uint8 Button_senseClkDividerVal[Button_TOTAL_SCANSLOT_COUNT];
        extern uint8 Button_sampleClkDividerVal[Button_TOTAL_SCANSLOT_COUNT];
    #else
        extern uint8 Button_senseClkDividerVal;
        extern uint8 Button_sampleClkDividerVal;
    #endif /* (0u != Button_MULTIPLE_FREQUENCY_SET) */
#else
    extern const uint32 Button_widgetResolution[Button_RESOLUTIONS_TBL_SIZE];
    #if (0u != Button_MULTIPLE_FREQUENCY_SET)
        extern const uint8 Button_senseClkDividerVal[Button_TOTAL_SCANSLOT_COUNT];
        extern const uint8 Button_sampleClkDividerVal[Button_TOTAL_SCANSLOT_COUNT];
    #else
        extern const uint8 Button_senseClkDividerVal;
        extern const uint8 Button_sampleClkDividerVal;
    #endif /* (0u != Button_MULTIPLE_FREQUENCY_SET) */
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE)  */

extern const uint8 Button_widgetNumber[Button_TOTAL_SENSOR_COUNT];

extern reg32* const Button_prtSelTbl[Button_CFG_REG_TBL_SIZE];
extern reg32* const Button_prtCfgTbl[Button_CFG_REG_TBL_SIZE];
extern reg32* const Button_prtDRTbl[Button_CFG_REG_TBL_SIZE];
extern reg32 * Button_pcTable[Button_PORT_PIN_CONFIG_TBL_ZISE];

extern const uint8  Button_portTable[Button_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint32 Button_maskTable[Button_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint8  Button_pinShiftTbl[Button_PORT_PIN_CONFIG_TBL_ZISE];

#if (0u != Button_INDEX_TABLE_SIZE)
extern const uint8 CYCODE Button_indexTable[Button_INDEX_TABLE_SIZE];
#endif /* (0u != Button_INDEX_TABLE_SIZE)) */

/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define  Button_PrescalersTuningDone         Button_prescalersTuningDone
#define  Button_SensorRaw                    Button_sensorRaw
#define  Button_PRSResolutionTbl             Button_prsResolutionTbl
#define  Button_SensorEnableMask             Button_sensorEnableMask
#define  Button_Clk1DividerVal               Button_senseClkDividerVal
#define  Button_Clk2DividerVal               Button_sampleClkDividerVal
#define  Button_PrtSelTbl                    Button_prtSelTbl
#define  Button_PrtCfgTbl                    Button_prtCfgTbl
#define  Button_PrtDRTbl                     Button_prtDRTbl
#define  Button_idac1Settings                Button_modulationIDAC
#define  Button_idac2Settings                Button_compensationIDAC

#endif /* CY_CAPSENSE_CSD_Button_H */


 /* [] END OF FILE */
