/*******************************************************************************
* File Name: ISR_R.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ISR_R_H)
#define CY_ISR_ISR_R_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_R_Start(void);
void ISR_R_StartEx(cyisraddress address);
void ISR_R_Stop(void);

CY_ISR_PROTO(ISR_R_Interrupt);

void ISR_R_SetVector(cyisraddress address);
cyisraddress ISR_R_GetVector(void);

void ISR_R_SetPriority(uint8 priority);
uint8 ISR_R_GetPriority(void);

void ISR_R_Enable(void);
uint8 ISR_R_GetState(void);
void ISR_R_Disable(void);

void ISR_R_SetPending(void);
void ISR_R_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_R ISR. */
#define ISR_R_INTC_VECTOR            ((reg32 *) ISR_R__INTC_VECT)

/* Address of the ISR_R ISR priority. */
#define ISR_R_INTC_PRIOR             ((reg32 *) ISR_R__INTC_PRIOR_REG)

/* Priority of the ISR_R interrupt. */
#define ISR_R_INTC_PRIOR_NUMBER      ISR_R__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_R interrupt. */
#define ISR_R_INTC_SET_EN            ((reg32 *) ISR_R__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_R interrupt. */
#define ISR_R_INTC_CLR_EN            ((reg32 *) ISR_R__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_R interrupt state to pending. */
#define ISR_R_INTC_SET_PD            ((reg32 *) ISR_R__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_R interrupt. */
#define ISR_R_INTC_CLR_PD            ((reg32 *) ISR_R__INTC_CLR_PD_REG)



#endif /* CY_ISR_ISR_R_H */


/* [] END OF FILE */
