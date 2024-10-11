/*******************************************************************************
* File Name: Button_TunerHelper.h
* Version 2.60
*
* Description:
*  This file provides constants and structure declarations for the tuner helper
*  APIs for the CapSense CSD component.
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_Button_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_Button_H

#include "Button.h"

#if(0u != Button_CSHL_API_GENERATE)
    #include "Button_CSHL.h"
#endif /* (0u != Button_CSHL_API_GENERATE) */

#if (Button_TUNER_API_GENERATE)
    #include "Button_MBX.h"
#endif /* (Button_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define Button_DEFAULT_MAILBOXES_NUMBER       (1u)

#define Button_CENTROID_POSITION_BUFFER_SIZE  (2u)
#define Button_MB_POSITION_BUFFER_SIZE        (2u)

#define Button_DEFAULT_TRACKPAD_INDEX         (0u)

#define Button_FIRST_FINGER_INDEX             (0u)
#define Button_SECOND_FINGER_INDEX            (1u)

#define Button_FIRST_FINGER_X_INDEX           (0u)
#define Button_FIRST_FINGER_Y_INDEX           (1u)

#define Button_SECOND_FINGER_X_INDEX          (2u)
#define Button_SECOND_FINGER_Y_INDEX          (3u)

#define Button_GESTURE_TYPE_MASK              (0xF0u)
#define Button_INERTIAL_SCROLL                (0xB0u)
#define Button_NON_INERTIAL_SCROLL            (0xC0u)


/***************************************
*        Function Prototypes
***************************************/

void Button_TunerStart(void);
void Button_TunerComm(void);

#if (Button_TUNER_API_GENERATE)
   Button_NO_STRICT_VOLATILE void Button_ProcessAllWidgets(volatile Button_OUTBOX *outbox);
#endif /* (Button_TUNER_API_GENERATE) */


/***************************************
*     Vars with External Linkage
***************************************/
#if (Button_TUNER_API_GENERATE)
    extern volatile Button_MAILBOXES Button_mailboxesComm;
#endif /* (Button_TUNER_API_GENERATE) */

#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_Button_H)*/


/* [] END OF FILE */
