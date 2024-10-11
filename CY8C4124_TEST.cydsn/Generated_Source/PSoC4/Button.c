/*******************************************************************************
* File Name: Button.c
* Version 2.60
*
* Description:
*  This file provides the source code for scanning APIs for the CapSense CSD
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

#include "Button.h"
#include "Button_PVT.h"
#include "cypins.h"
#include "cyapicallbacks.h"

#if(0u != Button_CSHL_API_GENERATE)
    #include "Button_CSHL.h"
#endif /* (0u != Button_CSHL_API_GENERATE) */

/* This definition is intended to prevent unexpected linker error.
   For more details please see the IAR Technical Note 49981 */
#if defined(__ICCARM__)
    extern void Button_EnableSensor(uint32 sensor);
    extern void Button_DisableSensor(uint32 sensor);
#endif /* (__ICCARM__) */

/* SmartSense functions */
#if (Button_TUNING_METHOD == Button__TUNING_AUTO)
    uint8 Button_lowLevelTuningDone = 0u;
    uint8 Button_scanSpeedTbl[((Button_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
#endif /* (Button_TUNING_METHOD == Button__TUNING_AUTO) */

#if(Button_PRS_OPTIONS != Button__PRS_NONE)
    uint8 Button_prescalersTuningDone = 0u;
#endif /* (Button_PRS_OPTIONS == Button__PRS_NONE) */

/* Global software variables */
volatile uint8 Button_csdStatusVar = 0u;   /* CapSense CSD status, variable */
volatile uint8 Button_sensorIndex = 0u;    /* Index of scannig sensor */

/* Global array of Raw Counts */
uint16 Button_sensorRaw[Button_TOTAL_SENSOR_COUNT] = {0u};

/* Backup variables for trim registers*/
#if (Button_IDAC1_POLARITY == Button__IDAC_SINK)
    uint8 Button_csdTrim2;
#else
    uint8 Button_csdTrim1;
#endif /* (Button_IDAC1_POLARITY == Button__IDAC_SINK) */

/* Global array of un-scanned sensors state */
uint8 Button_unscannedSnsDriveMode[Button_PORT_PIN_CONFIG_TBL_ZISE];

/* Backup array for Button_sensorEnableMask */
uint8 Button_sensorEnableMaskBackup[(((Button_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];

/* Configured constants and arrays by Customizer */
uint8 Button_sensorEnableMask[(((Button_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)] = {
0xFu, };

reg32 * Button_pcTable[] = {
    (reg32 *)Button_Sns__Button0__BTN__PC, 
    (reg32 *)Button_Sns__Button1__BTN__PC, 
    (reg32 *)Button_Sns__Button2__BTN__PC, 
    (reg32 *)Button_Sns__Button3__BTN__PC, 
};

const uint8 Button_portTable[] = {
    Button_Sns__Button0__BTN__PORT, 
    Button_Sns__Button1__BTN__PORT, 
    Button_Sns__Button2__BTN__PORT, 
    Button_Sns__Button3__BTN__PORT, 
};

const uint32 Button_maskTable[] = {
    Button_Sns__Button0__BTN__MASK, 
    Button_Sns__Button1__BTN__MASK, 
    Button_Sns__Button2__BTN__MASK, 
    Button_Sns__Button3__BTN__MASK, 
};

const uint8 Button_pinShiftTbl[] = {
    (uint8) Button_Sns__Button0__BTN__SHIFT, 
    (uint8) Button_Sns__Button1__BTN__SHIFT, 
    (uint8) Button_Sns__Button2__BTN__SHIFT, 
    (uint8) Button_Sns__Button3__BTN__SHIFT, 
};

uint8 Button_modulationIDAC[Button_TOTAL_SENSOR_COUNT];
uint8 Button_compensationIDAC[Button_TOTAL_SENSOR_COUNT];

uint32 Button_widgetResolution[Button_RESOLUTIONS_TBL_SIZE] = {
    Button_RESOLUTION_12_BITS,
    Button_RESOLUTION_12_BITS,
    Button_RESOLUTION_12_BITS,
    Button_RESOLUTION_12_BITS,
};

uint8 Button_senseClkDividerVal[Button_TOTAL_SCANSLOT_COUNT];
uint8 Button_sampleClkDividerVal[Button_TOTAL_SCANSLOT_COUNT];

const uint8 Button_widgetNumber[Button_TOTAL_SENSOR_COUNT] = {
    0u, /* Button0__BTN */
    1u, /* Button1__BTN */
    2u, /* Button2__BTN */
    3u, /* Button3__BTN */
};

reg32* const Button_prtSelTbl[Button_CFG_REG_TBL_SIZE] = {
    ((reg32 *) CYREG_HSIOM_PORT_SEL0),
    ((reg32 *) CYREG_HSIOM_PORT_SEL1),
    ((reg32 *) CYREG_HSIOM_PORT_SEL2),
    ((reg32 *) CYREG_HSIOM_PORT_SEL3),
    ((reg32 *) CYREG_HSIOM_PORT_SEL4),
};

reg32* const Button_prtCfgTbl[Button_CFG_REG_TBL_SIZE] = {
    ((reg32 *) CYREG_PRT0_PC),
    ((reg32 *) CYREG_PRT1_PC),
    ((reg32 *) CYREG_PRT2_PC),
    ((reg32 *) CYREG_PRT3_PC),
    ((reg32 *) CYREG_PRT4_PC),
};

reg32* const Button_prtDRTbl[Button_CFG_REG_TBL_SIZE] = {
    ((reg32 *) CYREG_PRT0_DR),
    ((reg32 *) CYREG_PRT1_DR),
    ((reg32 *) CYREG_PRT2_DR),
    ((reg32 *) CYREG_PRT3_DR),
    ((reg32 *) CYREG_PRT4_DR),
};



/*******************************************************************************
* Function Name: Button_Init
********************************************************************************
*
* Summary:
*  API initializes default CapSense configuration provided by the customizer that defines
*  the mode of component operations and resets all the sensors to an inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_immunityIndex - defines immunity level.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_Init(void)
{
    uint32 curSensor;

    #if(Button_IS_SHIELD_ENABLE)

        #if((Button_CSH_TANK_PREGARGE_OPTION == Button__CAPPRIOBUF) || (0u != Button_CSH_TANK_ENABLE))
            uint32 newRegValue;

            newRegValue = Button_CTANK_CONNECTION_REG;
            newRegValue &= ~(Button_CSD_CTANK_CONNECTION_MASK);
            newRegValue |= Button_CSD_CTANK_TO_AMUXBUS_B;
            Button_CTANK_CONNECTION_REG = newRegValue;

            #if(Button_CSH_TANK_PREGARGE_OPTION == Button__CAPPRIOBUF)
                newRegValue = Button_CTANK_PORT_PC_REG;
                newRegValue &= ~(Button_CSD_CTANK_PC_MASK);
                newRegValue |= Button_CTANK_PC_STRONG_MODE;
                Button_CTANK_PORT_PC_REG = newRegValue;

                newRegValue = Button_CTANK_PORT_DR_REG;
                newRegValue &= ~(Button_CTANK_DR_MASK);
                newRegValue |= Button_CTANK_DR_CONFIG;
                Button_CTANK_PORT_DR_REG = newRegValue;
            #endif /* (Button_CSH_TANK_PREGARGE_OPTION == Button__CAPPRIOBUF) */

        #endif /* ((Button_CSH_TANK_PREGARGE_OPTION == Button__CAPPRIOBUF) || (Button_CSH_TANK_ENABLE)) */

        Button_EnableShieldElectrode((uint32)Button_SHIELD_PIN_NUMBER, (uint32)Button_SHIELD_PORT_NUMBER);

    #endif /* (Button_IS_SHIELD_ENABLE) */

    for(curSensor = 0u; curSensor < Button_TOTAL_SENSOR_COUNT; curSensor++)
    {
        Button_SetUnscannedSensorState(curSensor, Button_CONNECT_INACTIVE_SNS);
    }

    Button_CsdHwBlockInit();
    Button_SetShieldDelay(Button_SHIELD_DELAY );

    /* Clear all sensors */
    Button_ClearSensors();
}

/*******************************************************************************
* Function Name: Button_CsdHwBlockInit
********************************************************************************
*
* Summary:
*  Initialises the hardware parameters of the CSD block
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_csdTrim1 - Contains IDAC trim register value for Sourcing Mode.
*  Button_csdTrim2 - Contains IDAC trim register value for Sinking Mode.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_CsdHwBlockInit(void)
{
    uint32 newRegValue;

        /* Set trim registers for CSD Mode */
    #if (Button_IDAC1_POLARITY == Button__IDAC_SINK)
        /* iDAC1 Sinking Mode */
        Button_csdTrim2 = (uint8)Button_CSD_TRIM2_REG;
        newRegValue = Button_csdTrim2;
        newRegValue &= Button_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)((uint32)Button_SFLASH_CSD_TRIM2_REG & (uint32)Button_CSFLASH_TRIM_IDAC1_MASK);

        #if (Button_IDAC_CNT == 2u)
            /* iDAC2 Sinking Mode */
            newRegValue &= Button_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)((uint32)Button_SFLASH_CSD_TRIM2_REG & (uint32)Button_CSFLASH_TRIM_IDAC2_MASK);
        #endif /* (Button_IDAC_CNT == 2u) */
        Button_CSD_TRIM2_REG = newRegValue;
    #else
        /* iDAC1 Sourcing Mode */
        Button_csdTrim1 = (uint8)Button_CSD_TRIM1_REG;
        newRegValue = Button_csdTrim1;
        newRegValue &= Button_CSD_IDAC1_TRIM_MASK;
        newRegValue |= (uint32)((uint32)Button_SFLASH_CSD_TRIM1_REG & (uint32)Button_CSFLASH_TRIM_IDAC1_MASK);
        #if (Button_IDAC_CNT == 2u)
             /* iDAC2 Sourcing Mode */
            newRegValue &= Button_CSD_IDAC2_TRIM_MASK;
            newRegValue |= (uint32)((uint32)Button_SFLASH_CSD_TRIM1_REG & (uint32)Button_CSFLASH_TRIM_IDAC2_MASK);
        #endif
        Button_CSD_TRIM1_REG = newRegValue;
    #endif /* (Button_IDAC1_POLARITY == Button__IDAC_SINK) */

    /* Configure CSD and IDAC */
    #if (Button_IDAC_CNT > 1u)
        Button_CSD_IDAC_REG = Button_DEFAULT_CSD_IDAC_CONFIG;
        Button_CSD_CFG_REG = Button_DEFAULT_CSD_CONFIG;
    #else
        Button_CSD_IDAC_REG &= ~(Button_CSD_IDAC1_MODE_MASK  | Button_CSD_IDAC1_DATA_MASK);
        Button_CSD_IDAC_REG |= Button_DEFAULT_CSD_IDAC_CONFIG;

        Button_CSD_CFG_REG &= ~(Button_CSD_CONFIG_MASK);
        Button_CSD_CFG_REG |= (Button_DEFAULT_CSD_CONFIG);
    #endif /* (Button_IDAC_CNT > 1u) */


    /* Connect Cmod to AMUX bus */
    newRegValue = Button_CMOD_CONNECTION_REG;
    newRegValue &= ~(Button_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= Button_CSD_CMOD_TO_AMUXBUS_A;
    Button_CMOD_CONNECTION_REG = newRegValue;

    /* Configure Dead Band PWM if it is enabled */
    #if(Button_CSD_4B_PWM_MODE != Button__PWM_OFF)
        Button_CSD_4B_PWM_REG = Button_DEFAULT_CSD_4B_PWM_CONFIG;
    #endif /* (Button_CSD_4B_PWM_MODE != Button__PWM_OFF) */

    /* Setup ISR */
    CyIntDisable(Button_ISR_NUMBER);
    #if !defined(CY_EXTERNAL_INTERRUPT_CONFIG)
        (void)CyIntSetVector(Button_ISR_NUMBER, &Button_ISR);
        CyIntSetPriority(Button_ISR_NUMBER, Button_ISR_PRIORITY);
    #endif /* (CY_EXTERNAL_INTERRUPT_CONFIG) */
}


/*******************************************************************************
* Function Name: Button_Enable
********************************************************************************
*
* Summary:
*  Enables the CSD block and related resources to an active mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_Enable(void)
{
    uint32 newRegValue;

    /* Enable Clocks */
    Button_SenseClk_Stop();
    Button_SampleClk_Stop();

    Button_SampleClk_SetDividerValue((uint16)Button_INITIAL_CLK_DIVIDER);
    Button_SenseClk_SetDividerValue((uint16)Button_INITIAL_CLK_DIVIDER);

    #if (0u == Button_IS_M0S8PERI_BLOCK)
        Button_SenseClk_Start();
        Button_SampleClk_Start();
    #else
        Button_SampleClk_Start();
        Button_SenseClk_StartEx(Button_SampleClk__DIV_ID);
    #endif /* (0u == Button_IS_M0S8PERI_BLOCK) */

    /* Enable the CSD block */
    newRegValue = Button_CSD_CFG_REG;
    newRegValue |= (Button_CSD_CFG_ENABLE | Button_CSD_CFG_SENSE_COMP_EN
                                                   | Button_CSD_CFG_SENSE_EN);
    Button_CSD_CFG_REG = newRegValue;

    /* Enable interrupt */
    CyIntEnable(Button_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: Button_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin the component operation. CapSense_Start()
*  calls the CapSense_Init() function, and then calls the CapSense_Enable()
*  function. Initializes the registers and starts the CSD method of the CapSense
*  component. Resets all the sensors to an inactive state. Enables interrupts for
*  sensors scanning. When the SmartSense tuning mode is selected, the tuning procedure
*  is applied for all the sensors. The CapSense_Start() routine must be called before
*  any other API routines.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*   Button_initVar - used to check the initial configuration,
*   modified on the first function call.
*  Button_lowLevelTuningDone - Used to notify the Tuner GUI that
*   tuning of the scanning parameters is done.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_Start(void)
{

    static uint8 Button_initVar = 0u;

    #if((0u != Button_AUTOCALIBRATION_ENABLE) && (Button_TUNING_METHOD != Button__TUNING_AUTO))
        uint32 curSensor;
        uint32 rawLevel;
        uint32 widget;
    #endif /* ((0u != Button_AUTOCALIBRATION_ENABLE) && (Button_TUNING_METHOD != Button__TUNING_AUTO)) */

    if (Button_initVar == 0u)
    {
        Button_Init();
        Button_initVar = 1u;
    }
    Button_Enable();

    /* AutoTunning start */
    #if(Button_TUNING_METHOD == Button__TUNING_AUTO)
        #if(0u != Button_CSHL_API_GENERATE)
            Button_AutoTune();
            Button_lowLevelTuningDone = 1u;
        #endif /* (0u != Button_CSHL_API_GENERATE) */
    #else
        #if(0u != Button_AUTOCALIBRATION_ENABLE)

            #if(Button_IDAC_CNT > 1u)
                Button_CSD_IDAC_REG &= ~(Button_CSD_IDAC2_MODE_MASK);
            #endif /* (Button_IDAC_CNT > 1u) */

            for(curSensor = 0u; curSensor < Button_TOTAL_SCANSLOT_COUNT; curSensor++)
            {
                widget = Button_widgetNumber[curSensor];
                rawLevel = Button_widgetResolution[widget] >> Button_RESOLUTION_OFFSET;

                /* Calibration level should be equal to 85% from scanning resolution */
                rawLevel = (rawLevel * 85u) / 100u;

                Button_CalibrateSensor(curSensor, rawLevel, Button_modulationIDAC);
            }

            #if(0u != Button_TOTAL_CENTROIDS_COUNT)
                Button_NormalizeWidgets(Button_END_OF_WIDGETS_INDEX, Button_modulationIDAC);
            #endif /* (0u != Button_TOTAL_CENTROIDS_COUNT)  */

            #if(Button_IDAC_CNT > 1u)
                for(curSensor = 0u; curSensor < Button_TOTAL_SCANSLOT_COUNT; curSensor++)
                {
                    Button_compensationIDAC[curSensor] = Button_modulationIDAC[curSensor] / 2u;
                    Button_modulationIDAC[curSensor] = (Button_modulationIDAC[curSensor] + 1u) / 2u;
                }
                Button_CSD_IDAC_REG |= Button_CSD_IDAC2_MODE_FIXED;
            #endif /* (Button_IDAC_CNT > 1u) */

        #endif /* (0u != Button_AUTOCALIBRATION_ENABLE) */

    #endif /* ((Button_TUNING_METHOD == Button__TUNING_AUTO) */

    /* Initialize Advanced Centroid */
    #if(Button_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
        Button_AdvancedCentroidInit();
    #endif /* (Button_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */

    /* Connect sense comparator input to AMUXA */
    Button_CSD_CFG_REG |= Button_CSD_CFG_SENSE_INSEL;
}


/*******************************************************************************
* Function Name: Button_Stop
********************************************************************************
*
* Summary:
*  Stops the sensor scanning, disables component interrupts, and resets all the
*  sensors to an inactive state. Disables the Active mode power template bits for
*  the subcomponents used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_csdTrim1 - Contains the IDAC trim register value for the Sourcing Mode.
*  Button_csdTrim2 - Contains the IDAC trim register value for vSinking Mode.
*
* Side Effects:
*  This function should be called after scans are completed.
*
*******************************************************************************/
void Button_Stop(void)
{
    /* Disable interrupt */
    CyIntDisable(Button_ISR_NUMBER);

    Button_CSD_CFG_REG &= ~(Button_CSD_CFG_SENSE_COMP_EN | Button_CSD_CFG_SENSE_EN);

    #if(Button_IDAC_CNT == 2u)
        Button_CSD_CFG_REG &= ~(Button_CSD_CFG_ENABLE);
    #endif /* (Button_IDAC_CNT == 2u) */

    /* Disable the Clocks */
    Button_SenseClk_Stop();
    Button_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: Button_FindNextSensor
********************************************************************************
*
* Summary:
*  Finds the next sensor to scan.
*
* Parameters:
*  snsIndex:  Current index of sensor.
*
* Return:
*  Returns the next sensor index to scan.
*
* Global Variables:
*  Button_sensorEnableMask[] - used to store bit masks of the enabled sensors.
*
* Side Effects:
*  This function affects the  current scanning and should not
*  be used outside the component.
*
*******************************************************************************/
uint8 Button_FindNextSensor(uint8 snsIndex)
{
    uint32 enableFlag;

    /* Check if sensor enabled */
    do
    {
        /* Proceed with next sensor */
        snsIndex++;
        if(snsIndex == Button_TOTAL_SENSOR_COUNT)
        {
            break;
        }
        enableFlag = Button_GetBitValue(Button_sensorEnableMask, (uint32)snsIndex);
    }
    while(enableFlag == 0u);

    return ((uint8)snsIndex);
}


/*******************************************************************************
* Function Name: Button_ScanSensor
********************************************************************************
*
* Summary:
*  Sets the scan settings and starts scanning a sensor. After scanning is complete,
*  the ISR copies the measured sensor raw data to the global raw sensor array.
*  Use of the ISR ensures this function is non-blocking.
*  Each sensor has a unique number within the sensor array.
*  This number is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  Button_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and mode of scan as single scan.
*  Button_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to the provided sensor argument.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_ScanSensor(uint32 sensor)
{
    /* Clears status/control variable and set sensorIndex */
    Button_csdStatusVar = 0u;
    Button_sensorIndex = (uint8)sensor;

    /* Start of sensor scan */
    Button_csdStatusVar = (Button_SW_STS_BUSY | Button_SW_CTRL_SINGLE_SCAN);
    Button_PreScan(sensor);
}


#if(0u != Button_CSHL_API_GENERATE)
/*******************************************************************************
* Function Name: Button_ScanWidget
********************************************************************************
*
* Summary:
*  Sets the scan settings and starts scanning a widget.
*
* Parameters:
*  uint32 widget: Widget number.
*
* Return:
*  None
*
* Global Variables:
*  Button_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and clears the single scan mode.
*  Button_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to 0xFF and provided to function Button_FindNextSensor or
*  Button_sensorEnableMask[] - used to store bit masks of the enabled sensors.
*  Button_sensorEnableMaskBackup[] - used to backup bit masks of the enabled
*   sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_ScanWidget(uint32 widget)
{
    uint32 sensorsPerWidget;
    uint32 lastSensor;
    uint32 snsIndex;

    /* Get first sensor in widget */
    Button_sensorIndex = Button_rawDataIndex[widget];

    /* Get number of sensors in widget */
    sensorsPerWidget = Button_numberOfSensors[widget];

    /* Check if generic Sensor */
    if(sensorsPerWidget == 0u)
    {
        sensorsPerWidget = 1u;
    }

    /* Get last sensor in widget */
    lastSensor = (Button_rawDataIndex[widget] + sensorsPerWidget) - 1u;

    /* Backup sensorEnableMask array */
    for(snsIndex = 0u; snsIndex < Button_TOTAL_SENSOR_MASK; snsIndex++)
    {
        /* Backup sensorEnableMask array */
        Button_sensorEnableMaskBackup[snsIndex] = Button_sensorEnableMask[snsIndex];
    }

    /* Update sensorEnableMask to scan the sensors that belong to widget */
    for(snsIndex = 0u; snsIndex < Button_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        /* Update sensorEnableMask array bits to scan the widget only */
        if((snsIndex >= Button_sensorIndex) && (snsIndex <= lastSensor))
        {
            /* Set sensor bit to scan */
            Button_SetBitValue(Button_sensorEnableMask, snsIndex, 1u);
        }
        else
        {
            /* Reset sensor bit to do not scan */
            Button_SetBitValue(Button_sensorEnableMask, snsIndex, 0u);
        }
    }

    /* Check end of scan condition */
    if(Button_sensorIndex < Button_TOTAL_SENSOR_COUNT)
    {
        /* Set widget busy bit in status/control variable*/
        Button_csdStatusVar = (Button_SW_STS_BUSY | Button_SW_CTRL_WIDGET_SCAN);
        /* Scan first sensor of widget*/
        Button_PreScan((uint32)Button_sensorIndex);
    }
}
#endif /* (0u != Button_CSHL_API_GENERATE) */


/*******************************************************************************
* Function Name: Button_ScanEnableWidgets
********************************************************************************
*
* Summary:
*  This is the preferred method to scan all of the enabled widgets.
*  The API starts scanning a sensor within the enabled widgets.
*  The ISR continues scanning the sensors until all the enabled widgets are scanned.
*  Use of the ISR ensures this function is non-blocking.
*  All the widgets are enabled by default except proximity widgets.
*  The proximity widgets must be manually enabled as their long scan time
*  is incompatible with a fast response required of other widget types.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_csdStatusVar - used to provide the status and mode of the scanning process.
*  Sets the busy status(scan in progress) and clears the single scan mode.
*  Button_sensorIndex - used to store a sensor scanning sensor number.
*  Sets to 0xFF and provided to function Button_FindNextSensor or
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_ScanEnabledWidgets(void)
{
    /* Clears status/control variable and set sensorIndex */
    Button_csdStatusVar = 0u;
    Button_sensorIndex = 0xFFu;

    /* Find next sensor */
    Button_sensorIndex = (uint8)Button_FindNextSensor(Button_sensorIndex);

    /* Check end of scan condition */
    if(Button_sensorIndex < Button_TOTAL_SENSOR_COUNT)
    {
        Button_csdStatusVar |= Button_SW_STS_BUSY;
        Button_PreScan((uint32)Button_sensorIndex);
    }
}


/*******************************************************************************
* Function Name: Button_IsBusy
********************************************************************************
*
* Summary:
*  Returns the state of the CapSense component. 1 means that scanning in
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
*  Button_csdStatusVar - used to provide the status and mode of the scanning process.
*  Checks the busy status.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_IsBusy(void)
{
    return ((uint32)((0u != (Button_csdStatusVar & Button_SW_STS_BUSY)) ? 1u : 0u));
}


/*******************************************************************************
* Function Name: Button_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns sensor raw data from the global CapSense_sensorRaw[ ] array.
*  Each scan sensor has a unique number within the sensor array.
*  This number is assigned by the CapSense customizer in sequence.
*  Raw data can be used to perform calculations outside of the CapSense
*  provided framework.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns the current raw data value for a defined sensor number.
*
* Global Variables:
*  Button_sensorRaw[] - used to store sensors raw data.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint16 Button_ReadSensorRaw(uint32 sensor)
{
    return Button_sensorRaw[sensor];
}


/*******************************************************************************
* Function Name: Button_WriteSensorRaw
********************************************************************************
*
* Summary:
*  This API writes the raw count value passed as an argument to the sensor Raw count array.
*
* Parameters:
*  sensor:  Sensor number.
*  value: Raw count value.
*
* Global Variables:
*  Button_sensorRaw[] - used to store sensors raw data.
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_WriteSensorRaw(uint32 sensor, uint16 value)
{
    Button_sensorRaw[sensor] = value;
}


#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    /*******************************************************************************
    * Function Name: Button_SetScanResolution
    ********************************************************************************
    *
    * Summary:
    *  Sets a value of the sensor scan resolution for a widget.
    *  The MIN resolution can be set 8-bit. The MAX Resolution can be set 16 bit.
    *  This function is not available for the tuning mode "None".
    *
    * Parameters:
    *  widget:     Widget index.
    *  resolution: Represents the resolution value. The following defines which are available in the
    *              Button.h file should be used:
    *              Button_RESOLUTION_6_BITS
    *              Button_RESOLUTION_7_BITS
    *              Button_RESOLUTION_8_BITS
    *              Button_RESOLUTION_9_BITS
    *              Button_RESOLUTION_10_BITS
    *              Button_RESOLUTION_11_BITS
    *              Button_RESOLUTION_12_BITS
    *              Button_RESOLUTION_13_BITS
    *              Button_RESOLUTION_14_BITS
    *              Button_RESOLUTION_15_BITS
    *              Button_RESOLUTION_16_BITS
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  Button_widgetResolution[] - used to store scan resolution of each widget.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_SetScanResolution(uint32 widget, uint32 resolution)
    {
        Button_widgetResolution[widget] = resolution;
    }
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */


/*******************************************************************************
* Function Name: Button_GetScanResolution
********************************************************************************
*
* Summary:
*  Returns the resolution value for the appropriate sensor.
*  This function is not available for tuning mode "None".
*
* Parameters:
*  widget:     Widget index.
*
* Return:
*  resolution: Returns the resolution value for the appropriate sensor.
*              The resolution values are defined in the Button.h file
*              The defines are encountered below:
*              Button_RESOLUTION_6_BITS
*              Button_RESOLUTION_7_BITS
*              Button_RESOLUTION_8_BITS
*              Button_RESOLUTION_9_BITS
*              Button_RESOLUTION_10_BITS
*              Button_RESOLUTION_11_BITS
*              Button_RESOLUTION_12_BITS
*              Button_RESOLUTION_13_BITS
*              Button_RESOLUTION_14_BITS
*              Button_RESOLUTION_15_BITS
*              Button_RESOLUTION_16_BITS
*
* Global Variables:
*  Button_widgetResolution[] - used to store scan resolution of every widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_GetScanResolution(uint32 widget)
{
    return(Button_widgetResolution[widget]);
}


/*******************************************************************************
* Function Name: Button_ClearSensors
********************************************************************************
*
* Summary:
*  Resets all the sensors to the non-sampling state by sequentially disconnecting
*  all the sensors from Analog MUX Bus and putting them to an inactive state.
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
void Button_ClearSensors(void)
{
    uint32 snsIndex;

    for (snsIndex = 0u; snsIndex < Button_TOTAL_SENSOR_COUNT; snsIndex++)
    {
        Button_DisableScanSlot(snsIndex);
    }
}


#if (Button_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: Button_EnableScanSlot
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
    *  Button_portTable[]  - used to store the port number that pin
    *  belongs to for each sensor.
    *  Button_maskTable[]  - used to store the pin within the port for
    *  each sensor.
    *  Button_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  Bit 7 (msb) is used to define the sensor type: single or complex.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_EnableScanSlot(uint32 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 *index;
        /* Read sensor type: single or complex */
        uint8 snsType = Button_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & Button_COMPLEX_SS_FLAG) == 0u)
        {
            /* Enable sensor (single) */
            Button_EnableSensor(slot);
        }
        else
        {
            /* Enable complex sensor */
            snsType &= ~Button_COMPLEX_SS_FLAG;
            index = &Button_indexTable[snsType];
            snsNumber = Button_maskTable[slot];

            for (j = 0u; j < snsNumber; j++)
            {
                Button_EnableSensor(index[j]);
            }
        }
    }


    /*******************************************************************************
    * Function Name: Button_DisableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Disables the selected slot. The corresponding pin/pins is/are disconnected
    *  from the Analog Mux Bus and connected to GND, High_Z or Shield electrode.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  Button_portTable[]  - used to store the port number that pin
    *  belongs to for each sensor.
    *  Button_maskTable[]  - used to store the pin within the port for
    *  each sensor.
    *  Button_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in a port and mask table for
    *  complex sensors.
    *  7bit(msb) is used to define the sensor type: single or complex.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_DisableScanSlot(uint32 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 *index;

        /* Read sensor type: single or complex */
        uint8 snsType = Button_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & Button_COMPLEX_SS_FLAG) == 0u)
        {
            /* Disable sensor (single) */
            Button_DisableSensor(slot);
        }
        else
        {
            /* Disable complex sensor */
            snsType &= ~Button_COMPLEX_SS_FLAG;
            index = &Button_indexTable[snsType];
            snsNumber = Button_maskTable[slot];

            for (j=0; j < snsNumber; j++)
            {
                Button_DisableSensor(index[j]);
            }
        }
    }
#endif  /* Button_IS_COMPLEX_SCANSLOTS */


/*******************************************************************************
* Function Name: Button_EnableSensor
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
*  Button_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  Button_pinShiftTbl[] - used to store position of pin that
*  configured as sensor in port.
*  Button_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  Button_PrtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_EnableSensor(uint32 sensor)
{
    uint8  pinModeShift;
    uint8  pinHSIOMShift;
    uint8 interruptState;
    uint32 newRegisterValue;
    uint32 port;

    port = (uint32) Button_portTable[sensor];
    pinModeShift = Button_pinShiftTbl[sensor]  * Button_PC_PIN_CFG_SIZE;
    pinHSIOMShift = Button_pinShiftTbl[sensor] * Button_HSIOM_PIN_CFG_SIZE;

    interruptState = CyEnterCriticalSection();

    newRegisterValue = *Button_prtSelTbl[port];
    newRegisterValue &= ~(Button_CSD_HSIOM_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)Button_CSD_SENSE_PORT_MODE << pinHSIOMShift);

    *Button_prtCfgTbl[port] &= (uint32)~((uint32)Button_CSD_PIN_MODE_MASK << pinModeShift);
    *Button_prtSelTbl[port] = newRegisterValue;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Button_DisableSensor
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
*  Button_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  Button_pinShiftTbl[] - used to store position of pin that
*  configured as a sensor in the port.
*  Button_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  Button_PrtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_DisableSensor(uint32 sensor)
{
    uint8 interruptState;
    uint32 newRegisterValue;

    uint32 port = (uint32) Button_portTable[sensor];
    uint8  pinHSIOMShift = Button_pinShiftTbl[sensor] * Button_HSIOM_PIN_CFG_SIZE;
    uint8  pinModeShift = Button_pinShiftTbl[sensor]  * Button_PC_PIN_CFG_SIZE;

    uint32 inactiveConnect = Button_SNS_HIZANALOG_CONNECT;
    uint32 sensorState = Button_unscannedSnsDriveMode[sensor];

    *Button_prtSelTbl[port] &= ~(Button_CSD_HSIOM_MASK << pinHSIOMShift);

    #if(Button_IS_SHIELD_ENABLE != 0)
    if(sensorState != (uint32)Button__SHIELD)
    {
    #else
        /* Connected to Ground if shield is disabled */
        if(sensorState == (uint32)Button__SHIELD)
        {
            sensorState = (uint32)Button__GROUND;
        }
    #endif /* (Button_IS_SHIELD_ENABLE) */
        if(sensorState != (uint32)Button__HIZ_ANALOG)
        {
            /* Connected to Ground */
            inactiveConnect = (uint32)Button_SNS_GROUND_CONNECT;
        }

        interruptState = CyEnterCriticalSection();

        /* Set drive mode */
        newRegisterValue = *Button_prtCfgTbl[port];
        newRegisterValue &= ~(Button_CSD_PIN_MODE_MASK << pinModeShift);
        newRegisterValue |=  (uint32)(inactiveConnect << pinModeShift);
        *Button_prtCfgTbl[port] =  newRegisterValue;

        CyExitCriticalSection(interruptState);

        *Button_prtDRTbl[port]  &=  (uint32)~(uint32)((uint32)1u << Button_pinShiftTbl[sensor]);
    #if(Button_IS_SHIELD_ENABLE != 0)
    }
    else
    {
        /* Connect to Shield */
        *Button_prtSelTbl[port] |= (Button_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
    }
    #endif /* (Button_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: Button_SetDriveModeAllPins
********************************************************************************
*
* Summary:
* This API sets the drive mode of port pins used by the CapSense
* component (sensors, guard, shield, shield tank and Cmod) to drive the
* mode specified by the argument.
*
* Parameters:
*  driveMode:  Drive mode definition.
*
* Return:
*  None
*
* Global Variables:
*  Button_portTable[] - used to store the port number that pin
*  belongs to for each sensor.
*  Button_pinShiftTbl[] - used to store position of pin that
*  configured as a sensor in the port.
*
* Side Effects:
*  This API shall be called only after CapSense component is stopped.
*
*******************************************************************************/
void Button_SetDriveModeAllPins(uint32 driveMode)
{
    uint8 curSensor;
    #if (Button_IS_COMPLEX_SCANSLOTS)
        uint8 snsNumber;
        uint8 snsType;
    #endif  /* Button_IS_COMPLEX_SCANSLOTS */
    uint32 prtNumberTmp;
    uint32 pinNumberTmp;

    for(curSensor = 0u; curSensor < Button_TOTAL_SENSOR_COUNT; curSensor++)
    {
        #if (Button_IS_COMPLEX_SCANSLOTS)
            /* Read sensor type: single or complex */
            snsType = Button_portTable[curSensor];

            /* Check if sensor is complex */
            if ((snsType & Button_COMPLEX_SS_FLAG) == 0u)
            {
                /* The sensor is not complex */
                snsNumber = curSensor;
            }
            else
            {
                /* Get dedicated sensor ID of the complex sensor */
                snsType &= ~Button_COMPLEX_SS_FLAG;
                snsNumber = Button_indexTable[snsType];
            }

            prtNumberTmp = Button_portTable[snsNumber];
            pinNumberTmp = Button_pinShiftTbl[snsNumber];
        #else
            prtNumberTmp = Button_portTable[curSensor];
            pinNumberTmp = Button_pinShiftTbl[curSensor];
        #endif  /* Button_IS_COMPLEX_SCANSLOTS */

        Button_SetPinDriveMode(driveMode, pinNumberTmp, prtNumberTmp);
    }

    Button_SetPinDriveMode(driveMode, (uint32)Button_CMOD_PIN_NUMBER, (uint32)Button_CMOD_PRT_NUMBER);

    #if(0u != Button_CSH_TANK_ENABLE)
        Button_SetPinDriveMode(driveMode, (uint32)Button_CTANK_PIN_NUMBER, (uint32)Button_CTANK_PRT_NUMBER);
    #endif /* (0u != Button_CSH_TANK_ENABLE) */

    #if(0u != Button_IS_SHIELD_ENABLE)
        Button_SetPinDriveMode(driveMode, (uint32)Button_SHIELD_PIN_NUMBER, (uint32)Button_SHIELD_PORT_NUMBER);
    #endif /* (0u != Button_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: Button_RestoreDriveModeAllPins
********************************************************************************
*
* Summary:
*  This API restores the drive for all the CapSense port pins to the original
*  state.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*
* Side Effects:
*  This API is called only after the CapSense component is stopped.
*
*******************************************************************************/
void Button_RestoreDriveModeAllPins(void)
{
    uint32 newRegisterValue;

    Button_SetDriveModeAllPins(CY_SYS_PINS_DM_ALG_HIZ);

    newRegisterValue = Button_CMOD_CONNECTION_REG;
    newRegisterValue &= ~(Button_CSD_CMOD_CONNECTION_MASK);
    newRegisterValue |= Button_CSD_CMOD_TO_AMUXBUS_A;
    Button_CMOD_CONNECTION_REG = newRegisterValue;

    #if(0u != Button_CSH_TANK_ENABLE)
        newRegisterValue = Button_CTANK_CONNECTION_REG;
        newRegisterValue &= ~(Button_CSD_CTANK_CONNECTION_MASK);
        newRegisterValue |= Button_CSD_CTANK_TO_AMUXBUS_B;
        Button_CTANK_CONNECTION_REG = newRegisterValue;
    #endif/* (0u != Button_CSH_TANK_ENABLE) */

    #if(0u != Button_IS_SHIELD_ENABLE)
        newRegisterValue = *Button_prtSelTbl[Button_SHIELD_PORT_NUMBER];
        newRegisterValue &= ~(Button_CSD_HSIOM_MASK << ((uint32)Button_SHIELD_PIN_NUMBER * Button_HSIOM_PIN_CFG_SIZE));
        newRegisterValue |= (Button_CSD_SHIELD_PORT_MODE << ((uint32)Button_SHIELD_PIN_NUMBER * Button_HSIOM_PIN_CFG_SIZE));
        *Button_prtSelTbl[Button_SHIELD_PORT_NUMBER] = newRegisterValue;
    #endif /* (0u != Button_IS_SHIELD_ENABLE) */
}


/*******************************************************************************
* Function Name: Button_SetPinDriveMode
********************************************************************************
*
* Summary:
* This API sets the drive mode for the appropriate port/pin.
*
* Parameters:
*  driveMode:  Drive mode definition.
*  portNumber: contains port number (0, 1, 2).
*  pinNumber: contains pin number (0, 1, 2, ... , 7).
*
* Return:
*  None
*
* Global Variables:
*  Button_prtSelTbl[] - Contains pointers to the HSIOM
*  registers for each port.
*  Button_prtCfgTb[] - Contains pointers to the port config
*  registers for each port.
*
* Side Effects:
*  This API is called only after CapSense component is stopped.
*
*******************************************************************************/
void Button_SetPinDriveMode(uint32 driveMode, uint32 pinNumber, uint32 portNumber)
{
    uint32  pinModeShift;
    uint32 newRegisterValue;

    pinModeShift  = pinNumber * Button_PC_PIN_CFG_SIZE;

    newRegisterValue = *Button_prtCfgTbl[portNumber];
    newRegisterValue &= ~(Button_CSD_PIN_MODE_MASK << pinModeShift);
    newRegisterValue |=  (uint32)((uint32)driveMode << pinModeShift);
    *Button_prtCfgTbl[portNumber] =  newRegisterValue;
}


/*******************************************************************************
* Function Name: Button_PreScan
********************************************************************************
*
* Summary:
*  Sets required settings, enables a sensor, removes Vref from AMUX and starts the
*  scanning process of the sensor.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
* Button_widgetNumber[] - This array contains numbers of widgets for each sensor.
* Button_widgetResolution[] - Contains the widget resolution.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_PreScan(uint32 sensor)
{
    uint8 widget;
    uint8 interruptState;
    uint32 newRegValue;
    uint32 counterResolution;

    #if(Button_PRS_OPTIONS == Button__PRS_AUTO)
        uint8 senseClkDivMath;
        uint8 sampleClkDivMath;
    #endif /* (Button_PRS_OPTIONS == Button__PRS_AUTO) */

    #if ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
         (0 != Button_IS_OVERSAMPLING_EN))
        uint32 oversamplingFactor;
    #endif /* ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
               (0 != Button_IS_OVERSAMPLING_EN)) */

    /* Define widget sensor belongs to */
    widget = Button_widgetNumber[sensor];

    /* Recalculate Counter Resolution to MSB 16 bits */
    counterResolution = Button_widgetResolution[widget];

    #if ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
         (0 != Button_IS_OVERSAMPLING_EN))
        oversamplingFactor = Button_GetBitValue(Button_scanSpeedTbl, sensor);

        if(counterResolution < Button_RESOLUTION_16_BITS)
        {
            counterResolution <<= oversamplingFactor;
            counterResolution |= (uint32)(Button_RESOLUTION_8_BITS);
        }
    #endif /* ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
               (0 != Button_IS_OVERSAMPLING_EN)) */

    #if (0u != Button_IS_M0S8PERI_BLOCK)
        Button_SenseClk_Stop();
        Button_SampleClk_Stop();
    #endif /* (0u != Button_IS_M0S8PERI_BLOCK) */

    #if (0u != Button_MULTIPLE_FREQUENCY_SET)
        Button_SampleClk_SetDividerValue((uint16)Button_sampleClkDividerVal[sensor]);
        Button_SenseClk_SetDividerValue((uint16)Button_senseClkDividerVal[sensor]);
    #else
        Button_SampleClk_SetDividerValue((uint16)Button_sampleClkDividerVal);
        Button_SenseClk_SetDividerValue((uint16)Button_senseClkDividerVal);
    #endif /* (0u != Button_MULTIPLE_FREQUENCY_SET) */

    #if (0u != Button_IS_M0S8PERI_BLOCK)
        Button_SampleClk_Start();
        Button_SenseClk_StartEx(Button_SampleClk__DIV_ID);

        #if(Button_PRS_OPTIONS == Button__PRS_NONE)
            CyIntDisable(Button_ISR_NUMBER);
            Button_CSD_CNT_REG = Button_ONE_CYCLE;
            while(0u != (Button_CSD_CNT_REG & Button_RESOLUTION_16_BITS))
            {
            /* Wait until scanning is complete */
            }
            Button_CSD_INTR_REG = 1u;
            CyIntClearPending(Button_ISR_NUMBER);
            CyIntEnable(Button_ISR_NUMBER);
        #endif /* Button_PRS_OPTIONS == Button__PRS_NONE */
    #endif /* (0u != Button_IS_M0S8PERI_BLOCK) */

#if(Button_PRS_OPTIONS != Button__PRS_NONE)

    #if(Button_TUNING_METHOD == Button__TUNING_AUTO)
        if(Button_prescalersTuningDone != 0u)
        {
    #endif /* (Button_TUNING_METHOD == Button__TUNING_AUTO) */

            CyIntDisable(Button_ISR_NUMBER);

            newRegValue = Button_CSD_CFG_REG;
            newRegValue |= Button_CSD_CFG_PRS_SELECT;

            #if(Button_PRS_OPTIONS == Button__PRS_AUTO)

                newRegValue &= ~(Button_PRS_MODE_MASK);

                #if (0u != Button_MULTIPLE_FREQUENCY_SET)
                    senseClkDivMath = Button_senseClkDividerVal[sensor];
                    sampleClkDivMath = Button_sampleClkDividerVal[sensor];
                #else
                    senseClkDivMath = Button_senseClkDividerVal;
                    sampleClkDivMath = Button_sampleClkDividerVal;
                #endif /* ( Button_MULTIPLE_FREQUENCY_SET) */

                #if(0u == Button_IS_M0S8PERI_BLOCK)
                    senseClkDivMath *= sampleClkDivMath;
                #endif /* (0u == Button_IS_M0S8PERI_BLOCK) */

                if((senseClkDivMath * Button_RESOLUTION_12_BITS) <
                   (sampleClkDivMath * Button_widgetResolution[widget]))
                {
                    newRegValue |= Button_CSD_PRS_12_BIT;
                }
            #endif /* (Button_PRS_OPTIONS == Button__PRS_AUTO) */

            Button_CSD_CFG_REG = newRegValue;

            CyIntEnable(Button_ISR_NUMBER);

    #if(Button_TUNING_METHOD == Button__TUNING_AUTO)
        }
    #endif /* (Button_PRS_OPTIONS != Button__PRS_NONE) */

#endif /* (Button_PRS_OPTIONS == Button__PRS_NONE) */

    /* Set Idac Value */
    CyIntDisable(Button_ISR_NUMBER);
    newRegValue = Button_CSD_IDAC_REG;

#if (Button_IDAC_CNT == 1u)
    newRegValue &= ~(Button_CSD_IDAC1_DATA_MASK);
    newRegValue |= Button_modulationIDAC[sensor];
#else
    newRegValue &= ~(Button_CSD_IDAC1_DATA_MASK | Button_CSD_IDAC2_DATA_MASK);
    newRegValue |= (Button_modulationIDAC[sensor] |
                            (uint32)((uint32)Button_compensationIDAC[sensor] <<
                            Button_CSD_IDAC2_DATA_OFFSET));
#endif /* (Button_IDAC_CNT == 1u) */

    Button_CSD_IDAC_REG = newRegValue;

#if(Button_CMOD_PREGARGE_OPTION == Button__CAPPRIOBUF)
    newRegValue = Button_CMOD_CONNECTION_REG;
    newRegValue &= ~(Button_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= Button_CSD_CMOD_TO_AMUXBUS_A;
    Button_CMOD_CONNECTION_REG = newRegValue;

    newRegValue = Button_CMOD_PORT_PC_REG;
    newRegValue &= ~(Button_CSD_CMOD_PC_MASK);
    newRegValue |= Button_CMOD_PC_HIGH_Z_MODE;
    Button_CMOD_PORT_PC_REG = newRegValue;
#endif /* (Button_CMOD_PREGARGE_OPTION == Button__CAPPRIOBUF) */

    /* Disconnect Vref Buffer from AMUX */
    newRegValue = Button_CSD_CFG_REG;
    newRegValue &= ~(Button_PRECHARGE_CONFIG_MASK);
    newRegValue |= Button_CTANK_PRECHARGE_CONFIG;

    CyIntEnable(Button_ISR_NUMBER);

    /* Enable Sensor */
    Button_EnableScanSlot(sensor);

    interruptState = CyEnterCriticalSection();
    Button_CSD_CFG_REG = newRegValue;

    /* `#START Button_PreSettlingDelay_Debug` */

    /* `#END` */

#ifdef Button_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK
    Button_PreScan_Pre_SettlingDelay_Debug_Callback();
#endif /* Button_PRE_SCAN_PRE_SETTLING_DELAY_DEBUG_CALLBACK */

    CyDelayCycles(Button_GLITCH_ELIMINATION_CYCLES);

    /* `#START Button_PreScan_Debug` */

    /* `#END` */

#ifdef Button_PRE_SCAN_DEBUG_CALLBACK
    Button_PreScan_Debug_Callback();
#endif /* Button_PRE_SCAN_DEBUG_CALLBACK */

    Button_CSD_CNT_REG = counterResolution;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Button_PostScan
********************************************************************************
*
* Summary:
*  Stores the results of measurement in the Button_sensorRaw[] array,
*  sets the scanning sensor in the non-sampling state, turns off Idac(Current Source IDAC),
*  disconnects the IDAC(Sink mode), and applies Vref on AMUX.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  Button_sensorRaw[] - used to store sensors raw data.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_PostScan(uint32 sensor)
{
    uint32 newRegValue;
#if ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
     (0 != Button_IS_OVERSAMPLING_EN))
    uint32 oversamplingFactor;
    uint32 widget;
#endif /* ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
           (0 != Button_IS_OVERSAMPLING_EN)) */

    /* `#START Button_PostScan_Debug` */

    /* `#END` */

#ifdef Button_POST_SCAN_DEBUG_CALLBACK
    Button_PostScan_Debug_Callback();
#endif /* Button_POST_SCAN_DEBUG_Callback */

    /* Read SlotResult from Raw Counter */
    Button_sensorRaw[sensor]  = (uint16)Button_CSD_CNT_REG;

#if ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
     (0 != Button_IS_OVERSAMPLING_EN))
    widget = Button_widgetNumber[sensor];
    if(Button_widgetResolution[widget] < Button_RESOLUTION_16_BITS)
    {
        oversamplingFactor = Button_GetBitValue(Button_scanSpeedTbl, sensor);
        Button_sensorRaw[sensor] >>= oversamplingFactor;
    }
#endif /* ((Button_TUNING_METHOD == Button__TUNING_AUTO) &&\
           (0 != Button_IS_OVERSAMPLING_EN)) */

    /* Disable Sensor */
    Button_DisableScanSlot(sensor);

    CyIntDisable(Button_ISR_NUMBER);

#if(Button_CMOD_PREGARGE_OPTION == Button__CAPPRIOBUF)
    newRegValue = Button_CMOD_CONNECTION_REG;
    newRegValue &= ~(Button_CSD_CMOD_CONNECTION_MASK);
    newRegValue |= Button_CSD_CMOD_TO_AMUXBUS_B;
    Button_CMOD_CONNECTION_REG = newRegValue;

    newRegValue = Button_CMOD_PORT_PC_REG;
    newRegValue &= ~(Button_CSD_CMOD_PC_MASK);
    newRegValue |= Button_CMOD_PC_STRONG_MODE;
    Button_CMOD_PORT_PC_REG = newRegValue;

    newRegValue = Button_CMOD_PORT_DR_REG;
    newRegValue &= ~(Button_CMOD_DR_MASK);
    newRegValue |= Button_CMOD_DR_CONFIG;
    Button_CMOD_PORT_DR_REG = newRegValue;
#endif /* (Button_CMOD_PREGARGE_OPTION == Button__CAPPRIOBUF) */

    /* Connect Vref Buffer to AMUX bus  */
    newRegValue = Button_CSD_CFG_REG;
    newRegValue &= ~(Button_PRECHARGE_CONFIG_MASK);
    newRegValue |= Button_CMOD_PRECHARGE_CONFIG;
    Button_CSD_CFG_REG = newRegValue;

    /* Set Idac Value = 0 */
#if (Button_IDAC_CNT == 1u)
    Button_CSD_IDAC_REG &= ~(Button_CSD_IDAC1_DATA_MASK);
#else
    Button_CSD_IDAC_REG &= ~(Button_CSD_IDAC1_DATA_MASK | Button_CSD_IDAC2_DATA_MASK);
#endif /* (Button_IDAC_CNT == 1u) */

    CyIntEnable(Button_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: Button_EnableShieldElectrode
********************************************************************************
*
* Summary:
*  This API enables or disables the shield electrode on a specified port pin.
*
* Parameters:
*  portNumber: contains the shield electrode port number (0, 1, 2).
*  pinNumber: contains the shield electrode pin number (0, 1, 2, ... , 7).
*
* Return:
*  None
*
* Global Variables:
*  Button_prtCfgTbl[] - Contains pointers to the port config registers for each port.
*  Button_prtSelTbl[] - Contains pointers to the HSIOM registers for each port.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_EnableShieldElectrode(uint32 pinNumber, uint32 portNumber)
{
    uint32 newRegValue;

    *Button_prtCfgTbl[portNumber] &= ~(Button_CSD_PIN_MODE_MASK << (pinNumber * Button_PC_PIN_CFG_SIZE));
    newRegValue = *Button_prtSelTbl[portNumber];
    newRegValue &= ~(Button_CSD_HSIOM_MASK << (pinNumber * Button_HSIOM_PIN_CFG_SIZE));
    newRegValue |= (Button_CSD_SHIELD_PORT_MODE << (pinNumber * Button_HSIOM_PIN_CFG_SIZE));
    *Button_prtSelTbl[portNumber] = newRegValue;
}


/*******************************************************************************
* Function Name: Button_SetShieldDelay
********************************************************************************
*
* Summary:
*  This API sets a shield delay.
*
* Parameters:
*  delay:  shield delay value:
*                               0 - no delay
*                               1 - 1 cycle delay
*                               2 - 2 cycles delay
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
void Button_SetShieldDelay(uint32 delay)
{
    uint32 newRegValue;

    delay &= 0x03u;

    newRegValue = Button_CSD_CFG_REG;
    newRegValue &= (uint32)(~(uint32)Button_SHIELD_DELAY);
    newRegValue |= (delay << Button_CSD_CFG_SHIELD_DELAY_POS);
    Button_CSD_CFG_REG = newRegValue;
}


/*******************************************************************************
* Function Name: Button_ReadCurrentScanningSensor
********************************************************************************
*
* Summary:
*  This API returns scanning sensor number when sensor scan is in progress.
*  When sensor scan is completed the API returns
*  $INSTANCE_NAME`_NOT_SENSOR (0xFFFFFFFF) (when no sensor is scanned).
*
* Parameters:
*   None.
*
* Return:
*  Returns Sensor number if sensor is being scanned and
*  $INSTANCE_NAME`_NOT_SENSOR (0xFFFFFFFF) if scanning is complete.
*
* Global Variables:
*  Button_sensorIndex - the sensor number is being scanned.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_ReadCurrentScanningSensor(void)
{
    return ((uint32)(( 0u != (Button_csdStatusVar & Button_SW_STS_BUSY)) ?
                     Button_sensorIndex : Button_NOT_SENSOR));
}


/*******************************************************************************
* Function Name: Button_GetBitValue
********************************************************************************
*
* Summary:
*  The API returns a bit status of the bit in the table array which contains the masks.
*
* Parameters:
*  table[] - array with bit masks.
*  position - position of bit in the table[] array.
*
* Return:
*  0 - bit is not set; 1 - bit is set.
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_GetBitValue(const uint8 table[], uint32 position)
{
    uint32 offset;
    uint8 enMask;

    /* position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for an appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of the
       table[] array.
    */
    enMask = 0x01u << (position & 0x07u);

    return ((0u !=(table[offset] & enMask)) ? 1Lu : 0Lu);
}


/*******************************************************************************
* Function Name: Button_SetBitValue
********************************************************************************
*
* Summary:
*  The API sets a bit status of the bit in the table array which contains masks.
*
* Parameters:
*  table[] - array with bit masks.
*  position - position of bit in the table[] array.
*  value: 0 - bit is not set; 1 - bit is set.
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
void Button_SetBitValue(uint8 table[], uint32 position, uint32 value)
{
    uint32 offset;
    uint8 enMask;

    /* position is divided by 8 to calculate the element of the
       table[] array that contains the enable bit
       for an appropriate sensor.
    */
    offset = (position >> 3u);

    /* The enMask calculation for the appropriate sensor. Operation (position & 0x07u)
       intends to calculate the enable bit offset for the 8-bit element of the
       table[] array.
    */
    enMask = 0x01u << (position & 0x07u);

    if(0u != value)
    {
        table[offset] |= enMask;
    }
    else
    {
        table[offset] &= (uint8)~(enMask);
    }
}



/*******************************************************************************
* Function Name: Button_GetSenseClkDivider
********************************************************************************
*
* Summary:
*  This API returns a value of the sense clock divider for the  sensor.
*
* Parameters:
*  sensor: sensor index. The index value can be
*  from 0 to (Button_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the sense clock divider of the sensor.
*
* Global Variables:
*  Button_senseClkDividerVal[] - stores the sense clock divider values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_GetSenseClkDivider(uint32 sensor)
{
    #if(0u != Button_MULTIPLE_FREQUENCY_SET)
        return((uint32)Button_senseClkDividerVal[sensor]);
    #else
        return((uint32)Button_senseClkDividerVal);
    #endif /* (0u != Button_MULTIPLE_FREQUENCY_SET) */
}

#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    /*******************************************************************************
    * Function Name: Button_SetSenseClkDivider
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the sense clock divider for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  senseClk: represents the sense clock value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Button_senseClkDividerVal[] - stores the sense clock divider values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_SetSenseClkDivider(uint32 sensor, uint32 senseClk)
    {
        #if(0u != Button_MULTIPLE_FREQUENCY_SET)
            Button_senseClkDividerVal[sensor] = (uint8)senseClk;
        #else
            Button_senseClkDividerVal = (uint8)senseClk;
        #endif /* (0u != Button_MULTIPLE_FREQUENCY_SET) */
    }
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */


/*******************************************************************************
* Function Name: Button_GetModulatorClkDivider
********************************************************************************
*
* Summary:
*  This API returns a value of the modulator sample clock divider for the  sensor.
*
* Parameters:
*  sensor: sensor index. The value of index can be
*  from 0 to (Button_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the modulator sample clock divider for the  sensor.
*
* Global Variables:
*  Button_sampleClkDividerVal[] - stores the modulator sample divider values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_GetModulatorClkDivider(uint32 sensor)
{
    #if(0u != Button_MULTIPLE_FREQUENCY_SET)
        return((uint32)Button_sampleClkDividerVal[sensor]);
    #else
        return((uint32)Button_sampleClkDividerVal);
    #endif /* (0u != Button_MULTIPLE_FREQUENCY_SET) */
}

#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    /*******************************************************************************
    * Function Name: Button_SetModulatorClkDivider
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the modulator sample clock divider for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  modulatorClk: represents the modulator sample clock value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Button_sampleClkDividerVal[] - stores the modulator sample divider values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk)
    {
        #if(0u != Button_MULTIPLE_FREQUENCY_SET)
            Button_sampleClkDividerVal[sensor] = (uint8)modulatorClk;
        #else
            Button_sampleClkDividerVal = (uint8)modulatorClk;
        #endif /* (0u != Button_MULTIPLE_FREQUENCY_SET) */
    }
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */

/*******************************************************************************
* Function Name: Button_GetModulationIDAC
********************************************************************************
*
* Summary:
*  This API returns a value of the modulation IDAC for the  sensor.
*
* Parameters:
*  sensor: sensor index. The index value can be
*  from 0 to (Button_TOTAL_SENSOR_COUNT-1).
*
* Return:
*  This API returns the modulation IDAC of the sensor.
*
* Global Variables:
*  Button_modulationIDAC[] - stores modulation IDAC values.
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_GetModulationIDAC(uint32 sensor)
{
        return((uint32)Button_modulationIDAC[sensor]);
}

#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    /*******************************************************************************
    * Function Name: Button_SetModulationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of the modulation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  compIdacValue: represents the modulation IDAC data register value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Button_modulationIDAC[] - array with modulation IDAC values
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_SetModulationIDAC(uint32 sensor, uint32 modIdacValue)
    {
        Button_modulationIDAC[sensor] = (uint8)modIdacValue;
    }
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */


#if(Button_IDAC_CNT > 1u)
    /*******************************************************************************
    * Function Name: Button_GetCompensationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API returns a value of the compensation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor: sensor index. The index value can be
    *  from 0 to (Button_TOTAL_SENSOR_COUNT-1).
    *
    * Return:
    *  This API returns the compensation IDAC of the sensor.
    *
    * Global Variables:
    *  Button_compensationIDAC[] - stores the compensation IDAC values.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint32 Button_GetCompensationIDAC(uint32 sensor)
    {
        return((uint32)Button_compensationIDAC[sensor]);
    }
#endif /* (Button_IDAC_CNT > 1u) */


#if((Button_TUNING_METHOD != Button__TUNING_NONE) && (Button_IDAC_CNT > 1u))
    /*******************************************************************************
    * Function Name: Button_SetCompensationIDAC
    ********************************************************************************
    *
    * Summary:
    *  This API sets a value of compensation IDAC for the  sensor.
    *
    * Parameters:
    *  sensor:  Sensor index.
    *  compIdacValue: represents the compensation IDAC data register value.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Button_compensationIDAC[] - an array with compensation IDAC values
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue)
    {
        Button_compensationIDAC[sensor] = (uint8)compIdacValue;
    }
#endif /* ((Button_TUNING_METHOD != Button__TUNING_NONE) && (Button_IDAC_CNT > 1u)) */

/*******************************************************************************
* Function Name: Button_GetIDACRange
********************************************************************************
*
* Summary:
*  This API returns a value that indicates the IDAC range used by the
*  component to scan sensors. The IDAC range is common for all the sensors.
*
* Parameters:
*  None
*
* Return:
*  This API Returns a value that indicates the IDAC range:
*      0 - IDAC range set to 4x
*      1 - IDAC range set to 8x
*
* Global Variables:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint32 Button_GetIDACRange(void)
{
    return((0u != (Button_CSD_IDAC_REG & Button_CSD_IDAC1_RANGE_8X)) ? 1uL : 0uL);
}

#if (Button_TUNING_METHOD != Button__TUNING_NONE)
    /*******************************************************************************
    * Function Name: Button_SetIDACRange
    ********************************************************************************
    *
    * Summary:
    *  This API sets the IDAC range to the 4x (1.2uA/bit) or 8x (2.4uA/bit) mode.
    *  The IDAC range is common for all the sensors and common for the modulation and
    *  compensation IDACs.
    *
    * Parameters:
    *  iDacRange:  represents value for IDAC range
    *  0 -  IDAC range set to 4x (1.2uA/bit)
    *  1 or >1 - IDAC range set to 8x (2.4uA/bit)
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void Button_SetIDACRange(uint32 iDacRange)
    {
        if(iDacRange != 0u)
        {
            /*  IDAC range = 8x (2.4uA/bit) */
            Button_CSD_IDAC_REG |= (Button_CSD_IDAC1_RANGE_8X |\
                                              Button_CSD_IDAC2_RANGE_8X);
        }
        else
        {
            /*  IDAC range = 4x (1.2uA/bit) */
            /*  IDAC range = 8x (2.4uA/bit) */
            Button_CSD_IDAC_REG &= ~(Button_CSD_IDAC1_RANGE_8X |\
                                               Button_CSD_IDAC2_RANGE_8X);
        }
    }
#endif /* (Button_TUNING_METHOD != Button__TUNING_NONE) */


#if((0u != Button_AUTOCALIBRATION_ENABLE) || (Button_TUNING_METHOD == Button__TUNING_AUTO))
    /*******************************************************************************
    * Function Name: Button_GetSensorRaw
    ********************************************************************************
    *
    * Summary:
    *  The API updates and gets uprated raw data from the sensor.
    *
    * Parameters:
    *  sensor - Sensor number.
    *
    * Return:
    *  Returns the current raw data value for a defined sensor number.
    *
    * Global Variables:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint16  Button_GetSensorRaw(uint32 sensor)
    {
        uint32 curSample;
        uint32 avgVal = 0u;

        for(curSample = 0u; curSample < Button_AVG_SAMPLES_NUM; curSample++)
        {

            Button_ScanSensor((uint32)sensor);
            while(Button_IsBusy() == 1u)
            {
                /* Wait while sensor is busy */
            }
            avgVal += Button_ReadSensorRaw((uint32)sensor);
        }

        return((uint16)(avgVal / Button_AVG_SAMPLES_NUM));
    }
#endif /* ((0u != Button_AUTOCALIBRATION_ENABLE) && (Button_TUNING_METHOD == Button__TUNING_AUTO)) */


#if((0u != Button_AUTOCALIBRATION_ENABLE) && (Button_TUNING_METHOD != Button__TUNING_AUTO))
    /*******************************************************************************
    * Function Name: Button_CalibrateSensor
    ********************************************************************************
    *
    * Summary:
    *  Computes the one sensor IDAC value, which provides the raw signal on
    *  a specified level, with a specified prescaler, speed, and resolution.
    *
    * Parameters:
    *  sensor - Sensor Number.
    *
    *  rawLevel -  Raw data level which should be reached during the calibration
    *              procedure.
    *
    *  idacLevelsTbl - Pointer to the modulatorIdac data register configuration table.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Button_CalibrateSensor(uint32 sensor, uint32 rawLevel, uint8 idacLevelsTbl[])
    {
        uint8 mask;
        uint16 rawData;

        rawData = 0u;

        mask = 0x80u;
        /* Init IDAC for null Channel */
        idacLevelsTbl[sensor] = 0x00u;

        do
        {
            /* Set bit for null Channel */
            idacLevelsTbl[sensor] |= mask;

            /* Scan null Channel and get Rawdata */
            rawData = Button_GetSensorRaw(sensor);

            /* Decrease IDAC until Rawdata reaches rawLevel */
            if(rawData < rawLevel)
            {
                /* Reset bit for null Channel  */
                idacLevelsTbl[sensor] &= (uint8)~mask;
            }

            mask >>= 1u;
        }
        while(mask > 0u);

    }
#endif /* ((0u != Button_AUTOCALIBRATION_ENABLE) && (Button_TUNING_METHOD != Button__TUNING_AUTO)) */


/*******************************************************************************
* Function Name: Button_SetUnscannedSensorState
********************************************************************************
*
* Summary:
*  This API sets a state for un-scanned sensors.
*  It is possible to set the state to Ground, High-Z, or the shield electrode.
*  The un-scanned sensor can be connected to a shield electrode only if the shield is
*  enabled. If the shield is disabled and this API is called with the parameter which
*  indicates the shield state, the un-scanned sensor will be connected to Ground.
*
* Parameters:
*  sensor - Sensor Number.
*  sensorState: This parameter indicates un-scanned sensor state:
*
*     Button__GROUND 0
*     Button__HIZ_ANALOG 1
*     Button__SHIELD 2
*
* Return:
*  None.
*
* Global Variables:
*  Button_unscannedSnsDriveMode[] - used to store the state for
*  un-scanned sensors.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_SetUnscannedSensorState(uint32 sensor, uint32 sensorState)
{
    #if(Button_IS_COMPLEX_SCANSLOTS)
        uint8 snsType;
        uint8 curSensor;
        uint16 snsNumber;

        /* Read sensor type: single or complex */
        snsType = Button_portTable[sensor];

        /* Check if sensor is complex */
        if(0u != (snsType & Button_COMPLEX_SS_FLAG))
        {
            snsType &= (uint8)~Button_COMPLEX_SS_FLAG;
            snsNumber = (uint16)Button_maskTable[sensor];

            for (curSensor=0u; curSensor < snsNumber; curSensor++)
            {
                sensor = Button_indexTable[snsType + curSensor];
                Button_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
            }
        }
        else
        {
            Button_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
        }
    #else
        Button_unscannedSnsDriveMode[sensor] = (uint8)sensorState;
    #endif /* (Button_IS_COMPLEX_SCANSLOTS) */
}

#if(0u != Button_TOTAL_CENTROIDS_COUNT)
/*******************************************************************************
* Function Name: Button_NormalizeWidgets
********************************************************************************
*
* Summary:
*  This API aligns all the parameters of the widget to the maximum parameter.
*
* Parameters:
*  uint32 widgetsNum: Number of widgets.
*  uint8 *dataPrt: pointer to array with widget parameters.
*
* Return:
*  None
*
* Global Variables:
*  Button_numberOfSensors[] - Number of sensors in the widget.
*  Button_rawDataIndex[currentWidget] - Contains the  1st sensor
*  position in the widget.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_NormalizeWidgets(uint32 widgetsNum, uint8 dataPtr[])
{
    uint32 currentWidget;
    uint32 currentSensor;
    uint32 lastSensor;
    uint32 sensorsPerWidget;
    uint32 maxPerWidget;

    for(currentWidget = 0u; currentWidget < widgetsNum; currentWidget++)
    {
        maxPerWidget = 0u;

        sensorsPerWidget = Button_numberOfSensors[currentWidget];
        currentSensor = Button_rawDataIndex[currentWidget];
        lastSensor = currentSensor + sensorsPerWidget;

        while(currentSensor < lastSensor)
        {
            if(maxPerWidget < dataPtr[currentSensor])
            {
                maxPerWidget = dataPtr[currentSensor];
            }
            currentSensor++;
        }

        currentSensor = Button_rawDataIndex[currentWidget];

        while(currentSensor < lastSensor)
        {
            dataPtr[currentSensor] = (uint8)maxPerWidget;
            currentSensor++;
        }
    }
}
#endif /* (0u != Button_TOTAL_CENTROIDS_COUNT) */

/* [] END OF FILE */
