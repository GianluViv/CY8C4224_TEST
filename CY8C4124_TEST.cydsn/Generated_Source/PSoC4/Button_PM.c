/*******************************************************************************
* File Name: Button_PM.c
* Version 2.60
*
* Description:
*  This file provides Sleep APIs for CapSense CSD Component.
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

static Button_BACKUP_STRUCT Button_backup =
{
    0x00u, /* enableState; */
};


/*******************************************************************************
* Function Name: Button_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the customer configuration of CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_backup - used to save the component state before entering the  sleep
*  mode and none-retention registers.
*
* Side Effects:
*  None
*
*******************************************************************************/
void Button_SaveConfig(void)
{
    if ((Button_CSD_CFG_REG & Button_CSD_CFG_ENABLE) != 0u)
    {
        Button_backup.enableState = 1u;
    }
}


/*******************************************************************************
* Function Name: Button_Sleep
********************************************************************************
*
* Summary:
*  Disables the Active mode power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_backup - used to save the component state before entering the sleep
*  mode.
*
*******************************************************************************/
void Button_Sleep(void)
{
    Button_SaveConfig();

    /* Disable interrupt */
    CyIntDisable(Button_ISR_NUMBER);

    Button_CSD_CFG_REG &= ~(Button_CSD_CFG_SENSE_COMP_EN | Button_CSD_CFG_SENSE_EN);

    #if(Button_IDAC_CNT == 2u)
        Button_CSD_CFG_REG &= ~(Button_CSD_CFG_ENABLE);
    #endif /* (Button_IDAC_CNT == 2u) */

    /* Disable Clocks */
    Button_SenseClk_Stop();
    Button_SampleClk_Stop();
}


/*******************************************************************************
* Function Name: Button_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Must be called only after Button_SaveConfig() routine. Otherwise
*  the component configuration will be overwritten with its initial setting.
*
* Global Variables:
*  Button_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void Button_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Button_Wakeup
********************************************************************************
*
* Summary:
*  Restores the CapSense configuration and non-retention register values.
*  Restores the enabled state of the component by setting the Active mode power template
*  bits for a number of components used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Button_backup - used to save the component state before entering the sleep
*  mode and none-retention registers.
*
*******************************************************************************/
void Button_Wakeup(void)
{
    /* Enable the Clocks */
    Button_SenseClk_Start();
    Button_SampleClk_Start();

    /* Restore CapSense Enable state */
    if (Button_backup.enableState != 0u)
    {
        Button_Enable();
    }
}


/* [] END OF FILE */
