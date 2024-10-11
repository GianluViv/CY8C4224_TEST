/*******************************************************************************
* File Name: Button_Sns.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Button_Sns_ALIASES_H) /* Pins Button_Sns_ALIASES_H */
#define CY_PINS_Button_Sns_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Button_Sns_0			(Button_Sns__0__PC)
#define Button_Sns_0_PS		(Button_Sns__0__PS)
#define Button_Sns_0_PC		(Button_Sns__0__PC)
#define Button_Sns_0_DR		(Button_Sns__0__DR)
#define Button_Sns_0_SHIFT	(Button_Sns__0__SHIFT)
#define Button_Sns_0_INTR	((uint16)((uint16)0x0003u << (Button_Sns__0__SHIFT*2u)))

#define Button_Sns_1			(Button_Sns__1__PC)
#define Button_Sns_1_PS		(Button_Sns__1__PS)
#define Button_Sns_1_PC		(Button_Sns__1__PC)
#define Button_Sns_1_DR		(Button_Sns__1__DR)
#define Button_Sns_1_SHIFT	(Button_Sns__1__SHIFT)
#define Button_Sns_1_INTR	((uint16)((uint16)0x0003u << (Button_Sns__1__SHIFT*2u)))

#define Button_Sns_2			(Button_Sns__2__PC)
#define Button_Sns_2_PS		(Button_Sns__2__PS)
#define Button_Sns_2_PC		(Button_Sns__2__PC)
#define Button_Sns_2_DR		(Button_Sns__2__DR)
#define Button_Sns_2_SHIFT	(Button_Sns__2__SHIFT)
#define Button_Sns_2_INTR	((uint16)((uint16)0x0003u << (Button_Sns__2__SHIFT*2u)))

#define Button_Sns_3			(Button_Sns__3__PC)
#define Button_Sns_3_PS		(Button_Sns__3__PS)
#define Button_Sns_3_PC		(Button_Sns__3__PC)
#define Button_Sns_3_DR		(Button_Sns__3__DR)
#define Button_Sns_3_SHIFT	(Button_Sns__3__SHIFT)
#define Button_Sns_3_INTR	((uint16)((uint16)0x0003u << (Button_Sns__3__SHIFT*2u)))

#define Button_Sns_INTR_ALL	 ((uint16)(Button_Sns_0_INTR| Button_Sns_1_INTR| Button_Sns_2_INTR| Button_Sns_3_INTR))
#define Button_Sns_Button0__BTN			(Button_Sns__Button0__BTN__PC)
#define Button_Sns_Button0__BTN_PS		(Button_Sns__Button0__BTN__PS)
#define Button_Sns_Button0__BTN_PC		(Button_Sns__Button0__BTN__PC)
#define Button_Sns_Button0__BTN_DR		(Button_Sns__Button0__BTN__DR)
#define Button_Sns_Button0__BTN_SHIFT	(Button_Sns__Button0__BTN__SHIFT)
#define Button_Sns_Button0__BTN_INTR	((uint16)((uint16)0x0003u << (Button_Sns__0__SHIFT*2u)))

#define Button_Sns_Button1__BTN			(Button_Sns__Button1__BTN__PC)
#define Button_Sns_Button1__BTN_PS		(Button_Sns__Button1__BTN__PS)
#define Button_Sns_Button1__BTN_PC		(Button_Sns__Button1__BTN__PC)
#define Button_Sns_Button1__BTN_DR		(Button_Sns__Button1__BTN__DR)
#define Button_Sns_Button1__BTN_SHIFT	(Button_Sns__Button1__BTN__SHIFT)
#define Button_Sns_Button1__BTN_INTR	((uint16)((uint16)0x0003u << (Button_Sns__1__SHIFT*2u)))

#define Button_Sns_Button2__BTN			(Button_Sns__Button2__BTN__PC)
#define Button_Sns_Button2__BTN_PS		(Button_Sns__Button2__BTN__PS)
#define Button_Sns_Button2__BTN_PC		(Button_Sns__Button2__BTN__PC)
#define Button_Sns_Button2__BTN_DR		(Button_Sns__Button2__BTN__DR)
#define Button_Sns_Button2__BTN_SHIFT	(Button_Sns__Button2__BTN__SHIFT)
#define Button_Sns_Button2__BTN_INTR	((uint16)((uint16)0x0003u << (Button_Sns__2__SHIFT*2u)))

#define Button_Sns_Button3__BTN			(Button_Sns__Button3__BTN__PC)
#define Button_Sns_Button3__BTN_PS		(Button_Sns__Button3__BTN__PS)
#define Button_Sns_Button3__BTN_PC		(Button_Sns__Button3__BTN__PC)
#define Button_Sns_Button3__BTN_DR		(Button_Sns__Button3__BTN__DR)
#define Button_Sns_Button3__BTN_SHIFT	(Button_Sns__Button3__BTN__SHIFT)
#define Button_Sns_Button3__BTN_INTR	((uint16)((uint16)0x0003u << (Button_Sns__3__SHIFT*2u)))


#endif /* End Pins Button_Sns_ALIASES_H */


/* [] END OF FILE */
