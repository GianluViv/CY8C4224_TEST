/*******************************************************************************
* File Name: Button_TunerHelper.c
* Version 2.60
*
* Description:
*  This file provides the source code of the Tuner helper APIs for the CapSense CSD
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

#include "Button_TunerHelper.h"
#include "cyapicallbacks.h"

#if (Button_TUNER_API_GENERATE)
    #include "SCB.h"
    #include "SCB_EZI2C.h"
    volatile Button_MAILBOXES Button_mailboxesComm;
#endif  /* (Button_TUNER_API_GENERATE) */

/* `#START Button_TunerHelper_HEADER` */

/* `#END` */

/*******************************************************************************
* Function Name: Button_TunerStart
********************************************************************************
*
* Summary:
*  Initializes the CapSense CSD component and EzI2C communication component to use
*  a mailbox data structure for communication with the Tuner GUI.
*  Start the scanning, after initialization is complete.
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
*******************************************************************************/
void Button_TunerStart(void)
{
    #if (0u != Button_TUNER_API_GENERATE)

        /* Init mbx and quick check */
        Button_InitMailbox(&Button_mailboxesComm.csdMailbox);
        Button_mailboxesComm.numMailBoxes = Button_DEFAULT_MAILBOXES_NUMBER;

        /* Start CapSense and baselines */
        Button_Start();

        /* Initialize baselines */
        #if(0u != Button_CSHL_API_GENERATE)
            Button_InitializeEnabledBaselines();
        #endif /* (0u != Button_CSHL_API_GENERATE) */

        /* Start EzI2C, clears buf pointers */
        SCB_Start();

        /* Setup EzI2C buffers */
        SCB_EzI2CSetBuffer1(sizeof(Button_mailboxesComm), sizeof(Button_mailboxesComm),
                                                   (volatile uint8 *) &Button_mailboxesComm);

        /* Starts scan all enabled sensors */
        Button_ScanEnabledWidgets();

    #endif  /* (0u != Button_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: Button_TunerComm
********************************************************************************
*
* Summary:
*  This function is blocking. It waits till scanning loop is completed and applies
*  the new parameters from the Tuner GUI if available (the manual tuning mode only). Updates
*  the enabled baselines and state of widgets. Waits while the Tuner GUI reports that
*  the mailbox content  could be modified. Then loads the report data into the outbox
*  and sets a busy flag. Starts a new scanning loop.
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
*******************************************************************************/
void Button_TunerComm(void)
{
    #if (0u != Button_TUNER_API_GENERATE)
        if (0u == Button_IsBusy())
        {
            /* Apply new settings */
            #if((Button_TUNING_METHOD != Button__TUNING_NONE) &&\
                (0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                (Button_TUNING_METHOD == Button__TUNING_MANUAL))

                Button_ReadMessage(&Button_mailboxesComm.csdMailbox);

            #endif  /* ((Button_TUNING_METHOD != Button__TUNING_NONE) &&\
                        (0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                        (Button_TUNING_METHOD == Button__TUNING_MANUAL)) */

            #if(0u != Button_CSHL_API_GENERATE)
                /* Update all baselines and process all widgets */
                Button_UpdateEnabledBaselines();
                Button_ProcessAllWidgets(&Button_mailboxesComm.csdMailbox.outbox);
            #endif /* (0u != Button_CSHL_API_GENERATE) */

            Button_PostMessage(&Button_mailboxesComm.csdMailbox);

            /* Enable EZI2C interrupts, after scan complete */
            SCB_EnableInt();

            while((Button_mailboxesComm.csdMailbox.type != Button_TYPE_ID) ||
                  (0u != (SCB_EzI2CGetActivity() & SCB_EZI2C_STATUS_BUSY))){}

            /* Disable EZI2C interrupts, while scanning */
            SCB_DisableInt();

            /* Start scan all sensors */
            Button_ScanEnabledWidgets();
        }
    #endif /* (0u != Button_TUNER_API_GENERATE) */
}


#if ((0u != Button_TUNER_API_GENERATE) && (0u != Button_CSHL_API_GENERATE))
    /*******************************************************************************
    * Function Name: Button_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Calls the required functions to update all the widgets' state:
    *   - Button_GetCentroidPos() - calls only if linear sliders are
    *     available.
    *   - Button_GetRadialCentroidPos() - calls only if the  radial slider is
    *     available.
    *   - Button_GetTouchCentroidPos() - calls only if the  touchpad slider
    *     available.
    *   - Button_CheckIsAnyWidgetActive();
    *  The results of operations are copied to OUTBOX.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  Button_OUTBOX outbox - the structure which is used as an output
    *  buffer to report data to the Tuner GUI.
    *  Update fields:
    *    - position[];
    *    - OnMask[];
    *
    * Global Variables:
    *  None
    *
    *******************************************************************************/
    void Button_ProcessAllWidgets(volatile Button_OUTBOX *outbox)
    {
        uint8  i = 0u;

        #if (0u != Button_TOTAL_MATRIX_BUTTONS_COUNT)
            uint8 mbPositionBuf[Button_MB_POSITION_BUFFER_SIZE];
        #endif /* (0u != Button_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if (0u != Button_TOTAL_TOUCH_PADS_BASIC_COUNT)
            uint16 centroidPosBuf[Button_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != Button_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if(0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT)
            Button_POSITION_STRUCT trackpadPosBuf[Button_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if ( (0u != Button_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != Button_TOTAL_TOUCH_PADS_COUNT) || \
              (0u != Button_TOTAL_MATRIX_BUTTONS_COUNT))
            uint8 widgetCnt;
        #endif  /* ((0u != Button_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != Button_TOTAL_TOUCH_PADS_COUNT)) ||
                *   (0u != Button_TOTAL_MATRIX_BUTTONS_COUNT)
                */

        /* Calculate widget with centroids */
        #if (0u != Button_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < Button_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->centroidPosition[i] = (uint16)Button_GetCentroidPos((uint32)i);
            }
        #endif /* (0u != Button_TOTAL_LINEAR_SLIDERS_COUNT) */

        #if (0u != Button_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + Button_TOTAL_RADIAL_SLIDERS_COUNT); i++)
            {
                outbox->centroidPosition[i] = (uint16)Button_GetRadialCentroidPos((uint32)i);
            }
        #endif /* (0u != Button_TOTAL_RADIAL_SLIDERS_COUNT) */

        #if (0u != Button_TOTAL_TOUCH_PADS_BASIC_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (Button_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u)); i=i+2u)
            {
                if(Button_GetTouchCentroidPos((uint32)i, centroidPosBuf) == 0u)
                {
                    outbox->centroidPosition[i + Button_FIRST_FINGER_X_INDEX] = Button_MAX_UINT_16;
                    outbox->centroidPosition[i + Button_FIRST_FINGER_Y_INDEX] = Button_MAX_UINT_16;
                }
                else
                {
                    outbox->centroidPosition[i + Button_FIRST_FINGER_X_INDEX] =
                    (uint16) centroidPosBuf[Button_FIRST_FINGER_X_INDEX];

                    outbox->centroidPosition[i + Button_FIRST_FINGER_Y_INDEX] =
                    (uint16) centroidPosBuf[Button_FIRST_FINGER_Y_INDEX];
                }
            }
        #endif /* (0u != Button_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if (0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (Button_TOTAL_TRACKPAD_GESTURES_COUNT * 4u)); i=i+4u)
            {
                outbox->fingersNum[Button_DEFAULT_TRACKPAD_INDEX] =
                (uint8)Button_GetDoubleTouchCentroidPos(trackpadPosBuf);

                outbox->gestureID[Button_DEFAULT_TRACKPAD_INDEX] =
                (uint8)Button_DecodeAllGestures((uint32)outbox->fingersNum[Button_DEFAULT_TRACKPAD_INDEX], trackpadPosBuf);

                #if((0u != Button_ST_SCROLL_GEST_ENABLED) || (0u != Button_DT_SCROLL_GEST_ENABLED))
                    /*
                    Report Scroll count only for scroll and Inertial Scroll gestures.
                    For all other gestures report scroll count as zero to tuner.
                     */
                    if (((outbox->gestureID[Button_DEFAULT_TRACKPAD_INDEX] & Button_GESTURE_TYPE_MASK) == Button_NON_INERTIAL_SCROLL) ||
                        ((outbox->gestureID[Button_DEFAULT_TRACKPAD_INDEX] & Button_GESTURE_TYPE_MASK) == Button_INERTIAL_SCROLL))
                    {
                        outbox->scrollCnt = Button_GetScrollCnt();
                    }
                    else
                    {
                        outbox->scrollCnt = 0u;
                    }
                #endif /* ((0u != Button_ST_SCROLL_GEST_ENABLED) || (0u != Button_DT_SCROLL_GEST_ENABLED)) */

                outbox->centroidPosition[i + Button_FIRST_FINGER_X_INDEX] = Button_MAX_UINT_16;
                outbox->centroidPosition[i + Button_FIRST_FINGER_Y_INDEX] = Button_MAX_UINT_16;
                outbox->centroidPosition[i + Button_SECOND_FINGER_X_INDEX] = Button_MAX_UINT_16;
                outbox->centroidPosition[i + Button_SECOND_FINGER_Y_INDEX] = Button_MAX_UINT_16;

                if(0u != outbox->fingersNum[Button_DEFAULT_TRACKPAD_INDEX])
                {
                    outbox->centroidPosition[i + Button_FIRST_FINGER_X_INDEX] =
                    (uint16) trackpadPosBuf[Button_FIRST_FINGER_INDEX].x;

                    outbox->centroidPosition[i + Button_FIRST_FINGER_Y_INDEX] =
                    (uint16) trackpadPosBuf[Button_FIRST_FINGER_INDEX].y;

                    if(outbox->fingersNum[Button_DEFAULT_TRACKPAD_INDEX] > 1u)
                    {
                        outbox->centroidPosition[i + Button_SECOND_FINGER_X_INDEX] =
                        (uint16) trackpadPosBuf[Button_SECOND_FINGER_INDEX].x;

                        outbox->centroidPosition[i + Button_SECOND_FINGER_Y_INDEX] =
                        (uint16) trackpadPosBuf[Button_SECOND_FINGER_INDEX].y;
                    }
                }
            }
        #endif /* (0u != Button_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if (0u != Button_TOTAL_MATRIX_BUTTONS_COUNT)
            i += Button_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0u;
            for(; widgetCnt < (Button_TOTAL_MATRIX_BUTTONS_COUNT * 2u); widgetCnt += 2u)
            {
                if(Button_GetMatrixButtonPos((uint32)i, mbPositionBuf) == 0u)
                {
                    outbox->mbPosition[widgetCnt] = Button_MAX_UINT_8;
                    outbox->mbPosition[widgetCnt+1u] = Button_MAX_UINT_8;
                }
                else
                {
                    outbox->mbPosition[widgetCnt] = mbPositionBuf[0u];
                    outbox->mbPosition[widgetCnt+1u] = mbPositionBuf[1u];
                }
                i += 2u;
            }
        #endif /* (0u != Button_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if(0u != Button_CSHL_API_GENERATE)
            /* Update On/Off State */
            (void)Button_CheckIsAnyWidgetActive();

            /* Copy OnMask */
            for(i=0u; i < Button_TOTAL_SENSOR_MASK_COUNT; i++)
            {
                outbox->onMask[i]  = Button_sensorOnMask[i];
            }
        #endif /* (0u != Button_CSHL_API_GENERATE) */

        /* `#START Button_ProcessAllWidgets_Debug` */

        /* `#END` */

        #ifdef Button_PROCESS_ALL_WIDGETS_CALLBACK
            Button_ProcessAllWidgets_Callback();
        #endif /* Button_PROCESS_ALL_WIDGETS_CALLBACK */
    }


#endif /* ((0u != Button_TUNER_API_GENERATE) && (0u != Button_CSHL_API_GENERATE)) */


/* [] END OF FILE */
