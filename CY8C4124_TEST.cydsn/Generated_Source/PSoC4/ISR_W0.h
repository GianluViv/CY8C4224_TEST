/*******************************************************************************
* File Name: ISR_W0.h
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
#if !defined(CY_ISR_ISR_W0_H)
#define CY_ISR_ISR_W0_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_W0_Start(void);
void ISR_W0_StartEx(cyisraddress address);
void ISR_W0_Stop(void);

CY_ISR_PROTO(ISR_W0_Interrupt);

void ISR_W0_SetVector(cyisraddress address);
cyisraddress ISR_W0_GetVector(void);

void ISR_W0_SetPriority(uint8 priority);
uint8 ISR_W0_GetPriority(void);

void ISR_W0_Enable(void);
uint8 ISR_W0_GetState(void);
void ISR_W0_Disable(void);

void ISR_W0_SetPending(void);
void ISR_W0_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_W0 ISR. */
#define ISR_W0_INTC_VECTOR            ((reg32 *) ISR_W0__INTC_VECT)

/* Address of the ISR_W0 ISR priority. */
#define ISR_W0_INTC_PRIOR             ((reg32 *) ISR_W0__INTC_PRIOR_REG)

/* Priority of the ISR_W0 interrupt. */
#define ISR_W0_INTC_PRIOR_NUMBER      ISR_W0__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_W0 interrupt. */
#define ISR_W0_INTC_SET_EN            ((reg32 *) ISR_W0__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_W0 interrupt. */
#define ISR_W0_INTC_CLR_EN            ((reg32 *) ISR_W0__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_W0 interrupt state to pending. */
#define ISR_W0_INTC_SET_PD            ((reg32 *) ISR_W0__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_W0 interrupt. */
#define ISR_W0_INTC_CLR_PD            ((reg32 *) ISR_W0__INTC_CLR_PD_REG)



#endif /* CY_ISR_ISR_W0_H */


/* [] END OF FILE */
