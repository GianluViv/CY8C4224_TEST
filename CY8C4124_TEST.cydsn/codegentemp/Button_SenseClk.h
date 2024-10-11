/*******************************************************************************
* File Name: Button_SenseClk.h
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

#if !defined(CY_CLOCK_Button_SenseClk_H)
#define CY_CLOCK_Button_SenseClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Button_SenseClk_StartEx(uint32 alignClkDiv);
#define Button_SenseClk_Start() \
    Button_SenseClk_StartEx(Button_SenseClk__PA_DIV_ID)

#else

void Button_SenseClk_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Button_SenseClk_Stop(void);

void Button_SenseClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Button_SenseClk_GetDividerRegister(void);
uint8  Button_SenseClk_GetFractionalDividerRegister(void);

#define Button_SenseClk_Enable()                         Button_SenseClk_Start()
#define Button_SenseClk_Disable()                        Button_SenseClk_Stop()
#define Button_SenseClk_SetDividerRegister(clkDivider, reset)  \
    Button_SenseClk_SetFractionalDividerRegister((clkDivider), 0u)
#define Button_SenseClk_SetDivider(clkDivider)           Button_SenseClk_SetDividerRegister((clkDivider), 1u)
#define Button_SenseClk_SetDividerValue(clkDivider)      Button_SenseClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Button_SenseClk_DIV_ID     Button_SenseClk__DIV_ID

#define Button_SenseClk_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Button_SenseClk_CTRL_REG   (*(reg32 *)Button_SenseClk__CTRL_REGISTER)
#define Button_SenseClk_DIV_REG    (*(reg32 *)Button_SenseClk__DIV_REGISTER)

#define Button_SenseClk_CMD_DIV_SHIFT          (0u)
#define Button_SenseClk_CMD_PA_DIV_SHIFT       (8u)
#define Button_SenseClk_CMD_DISABLE_SHIFT      (30u)
#define Button_SenseClk_CMD_ENABLE_SHIFT       (31u)

#define Button_SenseClk_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Button_SenseClk_CMD_DISABLE_SHIFT))
#define Button_SenseClk_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Button_SenseClk_CMD_ENABLE_SHIFT))

#define Button_SenseClk_DIV_FRAC_MASK  (0x000000F8u)
#define Button_SenseClk_DIV_FRAC_SHIFT (3u)
#define Button_SenseClk_DIV_INT_MASK   (0xFFFFFF00u)
#define Button_SenseClk_DIV_INT_SHIFT  (8u)

#else 

#define Button_SenseClk_DIV_REG        (*(reg32 *)Button_SenseClk__REGISTER)
#define Button_SenseClk_ENABLE_REG     Button_SenseClk_DIV_REG
#define Button_SenseClk_DIV_FRAC_MASK  Button_SenseClk__FRAC_MASK
#define Button_SenseClk_DIV_FRAC_SHIFT (16u)
#define Button_SenseClk_DIV_INT_MASK   Button_SenseClk__DIVIDER_MASK
#define Button_SenseClk_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Button_SenseClk_H) */

/* [] END OF FILE */
