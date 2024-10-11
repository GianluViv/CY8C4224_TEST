/*******************************************************************************
* File Name: WHITE.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_WHITE_H) /* Pins WHITE_H */
#define CY_PINS_WHITE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "WHITE_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} WHITE_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   WHITE_Read(void);
void    WHITE_Write(uint8 value);
uint8   WHITE_ReadDataReg(void);
#if defined(WHITE__PC) || (CY_PSOC4_4200L) 
    void    WHITE_SetDriveMode(uint8 mode);
#endif
void    WHITE_SetInterruptMode(uint16 position, uint16 mode);
uint8   WHITE_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void WHITE_Sleep(void); 
void WHITE_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(WHITE__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define WHITE_DRIVE_MODE_BITS        (3)
    #define WHITE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - WHITE_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the WHITE_SetDriveMode() function.
         *  @{
         */
        #define WHITE_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define WHITE_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define WHITE_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define WHITE_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define WHITE_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define WHITE_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define WHITE_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define WHITE_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define WHITE_MASK               WHITE__MASK
#define WHITE_SHIFT              WHITE__SHIFT
#define WHITE_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WHITE_SetInterruptMode() function.
     *  @{
     */
        #define WHITE_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define WHITE_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define WHITE_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define WHITE_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(WHITE__SIO)
    #define WHITE_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(WHITE__PC) && (CY_PSOC4_4200L)
    #define WHITE_USBIO_ENABLE               ((uint32)0x80000000u)
    #define WHITE_USBIO_DISABLE              ((uint32)(~WHITE_USBIO_ENABLE))
    #define WHITE_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define WHITE_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define WHITE_USBIO_ENTER_SLEEP          ((uint32)((1u << WHITE_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << WHITE_USBIO_SUSPEND_DEL_SHIFT)))
    #define WHITE_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << WHITE_USBIO_SUSPEND_SHIFT)))
    #define WHITE_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << WHITE_USBIO_SUSPEND_DEL_SHIFT)))
    #define WHITE_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(WHITE__PC)
    /* Port Configuration */
    #define WHITE_PC                 (* (reg32 *) WHITE__PC)
#endif
/* Pin State */
#define WHITE_PS                     (* (reg32 *) WHITE__PS)
/* Data Register */
#define WHITE_DR                     (* (reg32 *) WHITE__DR)
/* Input Buffer Disable Override */
#define WHITE_INP_DIS                (* (reg32 *) WHITE__PC2)

/* Interrupt configuration Registers */
#define WHITE_INTCFG                 (* (reg32 *) WHITE__INTCFG)
#define WHITE_INTSTAT                (* (reg32 *) WHITE__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define WHITE_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(WHITE__SIO)
    #define WHITE_SIO_REG            (* (reg32 *) WHITE__SIO)
#endif /* (WHITE__SIO_CFG) */

/* USBIO registers */
#if !defined(WHITE__PC) && (CY_PSOC4_4200L)
    #define WHITE_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define WHITE_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define WHITE_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define WHITE_DRIVE_MODE_SHIFT       (0x00u)
#define WHITE_DRIVE_MODE_MASK        (0x07u << WHITE_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins WHITE_H */


/* [] END OF FILE */
