/*******************************************************************************
* File Name: WHITE.h  
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

#if !defined(CY_PINS_WHITE_ALIASES_H) /* Pins WHITE_ALIASES_H */
#define CY_PINS_WHITE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define WHITE_0			(WHITE__0__PC)
#define WHITE_0_PS		(WHITE__0__PS)
#define WHITE_0_PC		(WHITE__0__PC)
#define WHITE_0_DR		(WHITE__0__DR)
#define WHITE_0_SHIFT	(WHITE__0__SHIFT)
#define WHITE_0_INTR	((uint16)((uint16)0x0003u << (WHITE__0__SHIFT*2u)))

#define WHITE_INTR_ALL	 ((uint16)(WHITE_0_INTR))


#endif /* End Pins WHITE_ALIASES_H */


/* [] END OF FILE */
