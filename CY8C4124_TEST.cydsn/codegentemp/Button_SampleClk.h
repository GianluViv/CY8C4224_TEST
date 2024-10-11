/*******************************************************************************
* File Name: Button_SampleClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Button_SampleClk_H)
#define CY_CLOCK_Button_SampleClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Button_SampleClk_StartEx(uint32 alignClkDiv);
#define Button_SampleClk_Start() \
    Button_SampleClk_StartEx(Button_SampleClk__PA_DIV_ID)

#else

void Button_SampleClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Button_SampleClk_Stop(void);

void Button_SampleClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Button_SampleClk_GetDividerRegister(void);
uint8  Button_SampleClk_GetFractionalDividerRegister(void);

#define Button_SampleClk_Enable()                         Button_SampleClk_Start()
#define Button_SampleClk_Disable()                        Button_SampleClk_Stop()
#define Button_SampleClk_SetDividerRegister(clkDivider, reset)  \
    Button_SampleClk_SetFractionalDividerRegister((clkDivider), 0u)
#define Button_SampleClk_SetDivider(clkDivider)           Button_SampleClk_SetDividerRegister((clkDivider), 1u)
#define Button_SampleClk_SetDividerValue(clkDivider)      Button_SampleClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Button_SampleClk_DIV_ID     Button_SampleClk__DIV_ID

#define Button_SampleClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Button_SampleClk_CTRL_REG   (*(reg32 *)Button_SampleClk__CTRL_REGISTER)
#define Button_SampleClk_DIV_REG    (*(reg32 *)Button_SampleClk__DIV_REGISTER)

#define Button_SampleClk_CMD_DIV_SHIFT          (0u)
#define Button_SampleClk_CMD_PA_DIV_SHIFT       (8u)
#define Button_SampleClk_CMD_DISABLE_SHIFT      (30u)
#define Button_SampleClk_CMD_ENABLE_SHIFT       (31u)

#define Button_SampleClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Button_SampleClk_CMD_DISABLE_SHIFT))
#define Button_SampleClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Button_SampleClk_CMD_ENABLE_SHIFT))

#define Button_SampleClk_DIV_FRAC_MASK  (0x000000F8u)
#define Button_SampleClk_DIV_FRAC_SHIFT (3u)
#define Button_SampleClk_DIV_INT_MASK   (0xFFFFFF00u)
#define Button_SampleClk_DIV_INT_SHIFT  (8u)

#else 

#define Button_SampleClk_DIV_REG        (*(reg32 *)Button_SampleClk__REGISTER)
#define Button_SampleClk_ENABLE_REG     Button_SampleClk_DIV_REG
#define Button_SampleClk_DIV_FRAC_MASK  Button_SampleClk__FRAC_MASK
#define Button_SampleClk_DIV_FRAC_SHIFT (16u)
#define Button_SampleClk_DIV_INT_MASK   Button_SampleClk__DIVIDER_MASK
#define Button_SampleClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Button_SampleClk_H) */

/* [] END OF FILE */
