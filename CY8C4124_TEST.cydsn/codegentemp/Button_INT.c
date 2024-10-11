/*******************************************************************************
* File Name: Button_INT.c
* Version 2.60
*
* Description:
*  This file provides the source code of the  Interrupt Service Routine (ISR)
*  for the CapSense CSD component.
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
#include "cyapicallbacks.h"


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START Button_ISR_INTC` */

/* `#END` */


/*******************************************************************************
* Function Name: Button_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when the measure window is closed. The measure window
*  depends on the sensor scan resolution parameter.
*  The ISR has two modes:
*   1. Scans a single sensor and stores the measure result.
*   2. Stores the result of the current measure and starts the next scan till all
*      the enabled sensors are scanned.
*  This interrupt handler is only used in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_csv - used to provide the status and mode of the scanning process.
*   Mode - a single scan or scan of all the enabled sensors.
*   Status - scan is in progress or ready for new scan.
*  Button_sensorIndex - used to store a sensor scanning sensor number.
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(Button_ISR)
{
    static uint8 Button_snsIndexTmp;

    #ifdef Button_ISR_ENTRY_CALLBACK
        Button_ISR_EntryCallback();
    #endif /* Button_ISR_ENTRY_CALLBACK */

    /*  Place your Interrupt code here. */
    /* `#START Button_ISR_ENTER` */

    /* `#END` */

    CyIntDisable(Button_ISR_NUMBER);

    Button_CSD_INTR_REG = 1u;

    Button_PostScan((uint32)Button_sensorIndex);

    if ((Button_csdStatusVar & Button_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        Button_csdStatusVar &= (uint8)~Button_SW_STS_BUSY;
    }
    else
    {
        /* Proceed scanning */
        Button_sensorIndex = Button_FindNextSensor(Button_sensorIndex);

        /* Check end of scan */
        if(Button_sensorIndex < Button_TOTAL_SENSOR_COUNT)
        {
            Button_PreScan((uint32)Button_sensorIndex);
        }
        else
        {
            Button_csdStatusVar &= (uint8)~Button_SW_STS_BUSY;

             /* Check if widget has been scanned */
            if((Button_csdStatusVar & Button_SW_CTRL_WIDGET_SCAN) != 0u)
            {
                /* Restore sensorEnableMask array */
                for(Button_snsIndexTmp = 0u;
                    Button_snsIndexTmp < Button_TOTAL_SENSOR_MASK;
                    Button_snsIndexTmp++)
                {
                    /* Backup sensorEnableMask array */
                    Button_sensorEnableMask[Button_snsIndexTmp] = Button_sensorEnableMaskBackup[Button_snsIndexTmp];
                }
            }
        }
    }
    CyIntEnable(Button_ISR_NUMBER);

    /*  Place your Interrupt code here. */
    /* `#START Button_ISR_EXIT` */

    /* `#END` */

    #ifdef Button_ISR_EXIT_CALLBACK
        Button_ISR_ExitCallback();
    #endif /* Button_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
