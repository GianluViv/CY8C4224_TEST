/***************************************************************************//**
* \file Serial_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_Serial_H)
#define CY_SCB_PINS_Serial_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define Serial_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define Serial_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define Serial_REMOVE_TX_SDA_MISO_PIN      (1u)
#define Serial_REMOVE_SCLK_PIN      (1u)
#define Serial_REMOVE_SS0_PIN      (1u)
#define Serial_REMOVE_SS1_PIN                 (1u)
#define Serial_REMOVE_SS2_PIN                 (1u)
#define Serial_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define Serial_REMOVE_I2C_PINS                (1u)
#define Serial_REMOVE_SPI_MASTER_PINS         (1u)
#define Serial_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define Serial_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define Serial_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define Serial_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define Serial_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define Serial_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define Serial_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define Serial_REMOVE_SPI_SLAVE_PINS          (1u)
#define Serial_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define Serial_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define Serial_REMOVE_UART_TX_PIN             (0u)
#define Serial_REMOVE_UART_RX_TX_PIN          (1u)
#define Serial_REMOVE_UART_RX_PIN             (0u)
#define Serial_REMOVE_UART_RX_WAKE_PIN        (1u)
#define Serial_REMOVE_UART_RTS_PIN            (1u)
#define Serial_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define Serial_RX_WAKE_SCL_MOSI_PIN (0u == Serial_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define Serial_RX_SCL_MOSI_PIN     (0u == Serial_REMOVE_RX_SCL_MOSI_PIN)
#define Serial_TX_SDA_MISO_PIN     (0u == Serial_REMOVE_TX_SDA_MISO_PIN)
#define Serial_SCLK_PIN     (0u == Serial_REMOVE_SCLK_PIN)
#define Serial_SS0_PIN     (0u == Serial_REMOVE_SS0_PIN)
#define Serial_SS1_PIN                (0u == Serial_REMOVE_SS1_PIN)
#define Serial_SS2_PIN                (0u == Serial_REMOVE_SS2_PIN)
#define Serial_SS3_PIN                (0u == Serial_REMOVE_SS3_PIN)

/* Mode defined pins */
#define Serial_I2C_PINS               (0u == Serial_REMOVE_I2C_PINS)
#define Serial_SPI_MASTER_PINS        (0u == Serial_REMOVE_SPI_MASTER_PINS)
#define Serial_SPI_MASTER_SCLK_PIN    (0u == Serial_REMOVE_SPI_MASTER_SCLK_PIN)
#define Serial_SPI_MASTER_MOSI_PIN    (0u == Serial_REMOVE_SPI_MASTER_MOSI_PIN)
#define Serial_SPI_MASTER_MISO_PIN    (0u == Serial_REMOVE_SPI_MASTER_MISO_PIN)
#define Serial_SPI_MASTER_SS0_PIN     (0u == Serial_REMOVE_SPI_MASTER_SS0_PIN)
#define Serial_SPI_MASTER_SS1_PIN     (0u == Serial_REMOVE_SPI_MASTER_SS1_PIN)
#define Serial_SPI_MASTER_SS2_PIN     (0u == Serial_REMOVE_SPI_MASTER_SS2_PIN)
#define Serial_SPI_MASTER_SS3_PIN     (0u == Serial_REMOVE_SPI_MASTER_SS3_PIN)
#define Serial_SPI_SLAVE_PINS         (0u == Serial_REMOVE_SPI_SLAVE_PINS)
#define Serial_SPI_SLAVE_MOSI_PIN     (0u == Serial_REMOVE_SPI_SLAVE_MOSI_PIN)
#define Serial_SPI_SLAVE_MISO_PIN     (0u == Serial_REMOVE_SPI_SLAVE_MISO_PIN)
#define Serial_UART_TX_PIN            (0u == Serial_REMOVE_UART_TX_PIN)
#define Serial_UART_RX_TX_PIN         (0u == Serial_REMOVE_UART_RX_TX_PIN)
#define Serial_UART_RX_PIN            (0u == Serial_REMOVE_UART_RX_PIN)
#define Serial_UART_RX_WAKE_PIN       (0u == Serial_REMOVE_UART_RX_WAKE_PIN)
#define Serial_UART_RTS_PIN           (0u == Serial_REMOVE_UART_RTS_PIN)
#define Serial_UART_CTS_PIN           (0u == Serial_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (Serial_RX_WAKE_SCL_MOSI_PIN)
    #include "Serial_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (Serial_RX_SCL_MOSI) */

#if (Serial_RX_SCL_MOSI_PIN)
    #include "Serial_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (Serial_RX_SCL_MOSI) */

#if (Serial_TX_SDA_MISO_PIN)
    #include "Serial_uart_tx_i2c_sda_spi_miso.h"
#endif /* (Serial_TX_SDA_MISO) */

#if (Serial_SCLK_PIN)
    #include "Serial_spi_sclk.h"
#endif /* (Serial_SCLK) */

#if (Serial_SS0_PIN)
    #include "Serial_spi_ss0.h"
#endif /* (Serial_SS0_PIN) */

#if (Serial_SS1_PIN)
    #include "Serial_spi_ss1.h"
#endif /* (Serial_SS1_PIN) */

#if (Serial_SS2_PIN)
    #include "Serial_spi_ss2.h"
#endif /* (Serial_SS2_PIN) */

#if (Serial_SS3_PIN)
    #include "Serial_spi_ss3.h"
#endif /* (Serial_SS3_PIN) */

#if (Serial_I2C_PINS)
    #include "Serial_scl.h"
    #include "Serial_sda.h"
#endif /* (Serial_I2C_PINS) */

#if (Serial_SPI_MASTER_PINS)
#if (Serial_SPI_MASTER_SCLK_PIN)
    #include "Serial_sclk_m.h"
#endif /* (Serial_SPI_MASTER_SCLK_PIN) */

#if (Serial_SPI_MASTER_MOSI_PIN)
    #include "Serial_mosi_m.h"
#endif /* (Serial_SPI_MASTER_MOSI_PIN) */

#if (Serial_SPI_MASTER_MISO_PIN)
    #include "Serial_miso_m.h"
#endif /*(Serial_SPI_MASTER_MISO_PIN) */
#endif /* (Serial_SPI_MASTER_PINS) */

#if (Serial_SPI_SLAVE_PINS)
    #include "Serial_sclk_s.h"
    #include "Serial_ss_s.h"

#if (Serial_SPI_SLAVE_MOSI_PIN)
    #include "Serial_mosi_s.h"
#endif /* (Serial_SPI_SLAVE_MOSI_PIN) */

#if (Serial_SPI_SLAVE_MISO_PIN)
    #include "Serial_miso_s.h"
#endif /*(Serial_SPI_SLAVE_MISO_PIN) */
#endif /* (Serial_SPI_SLAVE_PINS) */

#if (Serial_SPI_MASTER_SS0_PIN)
    #include "Serial_ss0_m.h"
#endif /* (Serial_SPI_MASTER_SS0_PIN) */

#if (Serial_SPI_MASTER_SS1_PIN)
    #include "Serial_ss1_m.h"
#endif /* (Serial_SPI_MASTER_SS1_PIN) */

#if (Serial_SPI_MASTER_SS2_PIN)
    #include "Serial_ss2_m.h"
#endif /* (Serial_SPI_MASTER_SS2_PIN) */

#if (Serial_SPI_MASTER_SS3_PIN)
    #include "Serial_ss3_m.h"
#endif /* (Serial_SPI_MASTER_SS3_PIN) */

#if (Serial_UART_TX_PIN)
    #include "Serial_tx.h"
#endif /* (Serial_UART_TX_PIN) */

#if (Serial_UART_RX_TX_PIN)
    #include "Serial_rx_tx.h"
#endif /* (Serial_UART_RX_TX_PIN) */

#if (Serial_UART_RX_PIN)
    #include "Serial_rx.h"
#endif /* (Serial_UART_RX_PIN) */

#if (Serial_UART_RX_WAKE_PIN)
    #include "Serial_rx_wake.h"
#endif /* (Serial_UART_RX_WAKE_PIN) */

#if (Serial_UART_RTS_PIN)
    #include "Serial_rts.h"
#endif /* (Serial_UART_RTS_PIN) */

#if (Serial_UART_CTS_PIN)
    #include "Serial_cts.h"
#endif /* (Serial_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (Serial_RX_SCL_MOSI_PIN)
    #define Serial_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define Serial_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define Serial_RX_SCL_MOSI_HSIOM_MASK      (Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Serial_RX_SCL_MOSI_HSIOM_POS       (Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define Serial_RX_SCL_MOSI_HSIOM_SEL_GPIO  (Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define Serial_RX_SCL_MOSI_HSIOM_SEL_I2C   (Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define Serial_RX_SCL_MOSI_HSIOM_SEL_SPI   (Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define Serial_RX_SCL_MOSI_HSIOM_SEL_UART  (Serial_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (Serial_RX_WAKE_SCL_MOSI_PIN)
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_MASK      (Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_POS       (Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define Serial_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (Serial_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define Serial_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) Serial_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Serial_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) Serial_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Serial_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (Serial_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define Serial_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) Serial_INTCFG_TYPE_MASK << \
                                                                           Serial_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins Serial_RX_SCL_MOSI_PIN or Serial_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (Serial_RX_SCL_MOSI_PIN) */

#if (Serial_TX_SDA_MISO_PIN)
    #define Serial_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define Serial_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define Serial_TX_SDA_MISO_HSIOM_MASK      (Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define Serial_TX_SDA_MISO_HSIOM_POS       (Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define Serial_TX_SDA_MISO_HSIOM_SEL_GPIO  (Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define Serial_TX_SDA_MISO_HSIOM_SEL_I2C   (Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define Serial_TX_SDA_MISO_HSIOM_SEL_SPI   (Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define Serial_TX_SDA_MISO_HSIOM_SEL_UART  (Serial_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (Serial_TX_SDA_MISO_PIN) */

#if (Serial_SCLK_PIN)
    #define Serial_SCLK_HSIOM_REG   (*(reg32 *) Serial_spi_sclk__0__HSIOM)
    #define Serial_SCLK_HSIOM_PTR   ( (reg32 *) Serial_spi_sclk__0__HSIOM)
    
    #define Serial_SCLK_HSIOM_MASK      (Serial_spi_sclk__0__HSIOM_MASK)
    #define Serial_SCLK_HSIOM_POS       (Serial_spi_sclk__0__HSIOM_SHIFT)
    #define Serial_SCLK_HSIOM_SEL_GPIO  (Serial_spi_sclk__0__HSIOM_GPIO)
    #define Serial_SCLK_HSIOM_SEL_I2C   (Serial_spi_sclk__0__HSIOM_I2C)
    #define Serial_SCLK_HSIOM_SEL_SPI   (Serial_spi_sclk__0__HSIOM_SPI)
    #define Serial_SCLK_HSIOM_SEL_UART  (Serial_spi_sclk__0__HSIOM_UART)
#endif /* (Serial_SCLK_PIN) */

#if (Serial_SS0_PIN)
    #define Serial_SS0_HSIOM_REG   (*(reg32 *) Serial_spi_ss0__0__HSIOM)
    #define Serial_SS0_HSIOM_PTR   ( (reg32 *) Serial_spi_ss0__0__HSIOM)
    
    #define Serial_SS0_HSIOM_MASK      (Serial_spi_ss0__0__HSIOM_MASK)
    #define Serial_SS0_HSIOM_POS       (Serial_spi_ss0__0__HSIOM_SHIFT)
    #define Serial_SS0_HSIOM_SEL_GPIO  (Serial_spi_ss0__0__HSIOM_GPIO)
    #define Serial_SS0_HSIOM_SEL_I2C   (Serial_spi_ss0__0__HSIOM_I2C)
    #define Serial_SS0_HSIOM_SEL_SPI   (Serial_spi_ss0__0__HSIOM_SPI)
#if !(Serial_CY_SCBIP_V0 || Serial_CY_SCBIP_V1)
    #define Serial_SS0_HSIOM_SEL_UART  (Serial_spi_ss0__0__HSIOM_UART)
#endif /* !(Serial_CY_SCBIP_V0 || Serial_CY_SCBIP_V1) */
#endif /* (Serial_SS0_PIN) */

#if (Serial_SS1_PIN)
    #define Serial_SS1_HSIOM_REG  (*(reg32 *) Serial_spi_ss1__0__HSIOM)
    #define Serial_SS1_HSIOM_PTR  ( (reg32 *) Serial_spi_ss1__0__HSIOM)
    
    #define Serial_SS1_HSIOM_MASK     (Serial_spi_ss1__0__HSIOM_MASK)
    #define Serial_SS1_HSIOM_POS      (Serial_spi_ss1__0__HSIOM_SHIFT)
    #define Serial_SS1_HSIOM_SEL_GPIO (Serial_spi_ss1__0__HSIOM_GPIO)
    #define Serial_SS1_HSIOM_SEL_I2C  (Serial_spi_ss1__0__HSIOM_I2C)
    #define Serial_SS1_HSIOM_SEL_SPI  (Serial_spi_ss1__0__HSIOM_SPI)
#endif /* (Serial_SS1_PIN) */

#if (Serial_SS2_PIN)
    #define Serial_SS2_HSIOM_REG     (*(reg32 *) Serial_spi_ss2__0__HSIOM)
    #define Serial_SS2_HSIOM_PTR     ( (reg32 *) Serial_spi_ss2__0__HSIOM)
    
    #define Serial_SS2_HSIOM_MASK     (Serial_spi_ss2__0__HSIOM_MASK)
    #define Serial_SS2_HSIOM_POS      (Serial_spi_ss2__0__HSIOM_SHIFT)
    #define Serial_SS2_HSIOM_SEL_GPIO (Serial_spi_ss2__0__HSIOM_GPIO)
    #define Serial_SS2_HSIOM_SEL_I2C  (Serial_spi_ss2__0__HSIOM_I2C)
    #define Serial_SS2_HSIOM_SEL_SPI  (Serial_spi_ss2__0__HSIOM_SPI)
#endif /* (Serial_SS2_PIN) */

#if (Serial_SS3_PIN)
    #define Serial_SS3_HSIOM_REG     (*(reg32 *) Serial_spi_ss3__0__HSIOM)
    #define Serial_SS3_HSIOM_PTR     ( (reg32 *) Serial_spi_ss3__0__HSIOM)
    
    #define Serial_SS3_HSIOM_MASK     (Serial_spi_ss3__0__HSIOM_MASK)
    #define Serial_SS3_HSIOM_POS      (Serial_spi_ss3__0__HSIOM_SHIFT)
    #define Serial_SS3_HSIOM_SEL_GPIO (Serial_spi_ss3__0__HSIOM_GPIO)
    #define Serial_SS3_HSIOM_SEL_I2C  (Serial_spi_ss3__0__HSIOM_I2C)
    #define Serial_SS3_HSIOM_SEL_SPI  (Serial_spi_ss3__0__HSIOM_SPI)
#endif /* (Serial_SS3_PIN) */

#if (Serial_I2C_PINS)
    #define Serial_SCL_HSIOM_REG  (*(reg32 *) Serial_scl__0__HSIOM)
    #define Serial_SCL_HSIOM_PTR  ( (reg32 *) Serial_scl__0__HSIOM)
    
    #define Serial_SCL_HSIOM_MASK     (Serial_scl__0__HSIOM_MASK)
    #define Serial_SCL_HSIOM_POS      (Serial_scl__0__HSIOM_SHIFT)
    #define Serial_SCL_HSIOM_SEL_GPIO (Serial_sda__0__HSIOM_GPIO)
    #define Serial_SCL_HSIOM_SEL_I2C  (Serial_sda__0__HSIOM_I2C)
    
    #define Serial_SDA_HSIOM_REG  (*(reg32 *) Serial_sda__0__HSIOM)
    #define Serial_SDA_HSIOM_PTR  ( (reg32 *) Serial_sda__0__HSIOM)
    
    #define Serial_SDA_HSIOM_MASK     (Serial_sda__0__HSIOM_MASK)
    #define Serial_SDA_HSIOM_POS      (Serial_sda__0__HSIOM_SHIFT)
    #define Serial_SDA_HSIOM_SEL_GPIO (Serial_sda__0__HSIOM_GPIO)
    #define Serial_SDA_HSIOM_SEL_I2C  (Serial_sda__0__HSIOM_I2C)
#endif /* (Serial_I2C_PINS) */

#if (Serial_SPI_SLAVE_PINS)
    #define Serial_SCLK_S_HSIOM_REG   (*(reg32 *) Serial_sclk_s__0__HSIOM)
    #define Serial_SCLK_S_HSIOM_PTR   ( (reg32 *) Serial_sclk_s__0__HSIOM)
    
    #define Serial_SCLK_S_HSIOM_MASK      (Serial_sclk_s__0__HSIOM_MASK)
    #define Serial_SCLK_S_HSIOM_POS       (Serial_sclk_s__0__HSIOM_SHIFT)
    #define Serial_SCLK_S_HSIOM_SEL_GPIO  (Serial_sclk_s__0__HSIOM_GPIO)
    #define Serial_SCLK_S_HSIOM_SEL_SPI   (Serial_sclk_s__0__HSIOM_SPI)
    
    #define Serial_SS0_S_HSIOM_REG    (*(reg32 *) Serial_ss0_s__0__HSIOM)
    #define Serial_SS0_S_HSIOM_PTR    ( (reg32 *) Serial_ss0_s__0__HSIOM)
    
    #define Serial_SS0_S_HSIOM_MASK       (Serial_ss0_s__0__HSIOM_MASK)
    #define Serial_SS0_S_HSIOM_POS        (Serial_ss0_s__0__HSIOM_SHIFT)
    #define Serial_SS0_S_HSIOM_SEL_GPIO   (Serial_ss0_s__0__HSIOM_GPIO)  
    #define Serial_SS0_S_HSIOM_SEL_SPI    (Serial_ss0_s__0__HSIOM_SPI)
#endif /* (Serial_SPI_SLAVE_PINS) */

#if (Serial_SPI_SLAVE_MOSI_PIN)
    #define Serial_MOSI_S_HSIOM_REG   (*(reg32 *) Serial_mosi_s__0__HSIOM)
    #define Serial_MOSI_S_HSIOM_PTR   ( (reg32 *) Serial_mosi_s__0__HSIOM)
    
    #define Serial_MOSI_S_HSIOM_MASK      (Serial_mosi_s__0__HSIOM_MASK)
    #define Serial_MOSI_S_HSIOM_POS       (Serial_mosi_s__0__HSIOM_SHIFT)
    #define Serial_MOSI_S_HSIOM_SEL_GPIO  (Serial_mosi_s__0__HSIOM_GPIO)
    #define Serial_MOSI_S_HSIOM_SEL_SPI   (Serial_mosi_s__0__HSIOM_SPI)
#endif /* (Serial_SPI_SLAVE_MOSI_PIN) */

#if (Serial_SPI_SLAVE_MISO_PIN)
    #define Serial_MISO_S_HSIOM_REG   (*(reg32 *) Serial_miso_s__0__HSIOM)
    #define Serial_MISO_S_HSIOM_PTR   ( (reg32 *) Serial_miso_s__0__HSIOM)
    
    #define Serial_MISO_S_HSIOM_MASK      (Serial_miso_s__0__HSIOM_MASK)
    #define Serial_MISO_S_HSIOM_POS       (Serial_miso_s__0__HSIOM_SHIFT)
    #define Serial_MISO_S_HSIOM_SEL_GPIO  (Serial_miso_s__0__HSIOM_GPIO)
    #define Serial_MISO_S_HSIOM_SEL_SPI   (Serial_miso_s__0__HSIOM_SPI)
#endif /* (Serial_SPI_SLAVE_MISO_PIN) */

#if (Serial_SPI_MASTER_MISO_PIN)
    #define Serial_MISO_M_HSIOM_REG   (*(reg32 *) Serial_miso_m__0__HSIOM)
    #define Serial_MISO_M_HSIOM_PTR   ( (reg32 *) Serial_miso_m__0__HSIOM)
    
    #define Serial_MISO_M_HSIOM_MASK      (Serial_miso_m__0__HSIOM_MASK)
    #define Serial_MISO_M_HSIOM_POS       (Serial_miso_m__0__HSIOM_SHIFT)
    #define Serial_MISO_M_HSIOM_SEL_GPIO  (Serial_miso_m__0__HSIOM_GPIO)
    #define Serial_MISO_M_HSIOM_SEL_SPI   (Serial_miso_m__0__HSIOM_SPI)
#endif /* (Serial_SPI_MASTER_MISO_PIN) */

#if (Serial_SPI_MASTER_MOSI_PIN)
    #define Serial_MOSI_M_HSIOM_REG   (*(reg32 *) Serial_mosi_m__0__HSIOM)
    #define Serial_MOSI_M_HSIOM_PTR   ( (reg32 *) Serial_mosi_m__0__HSIOM)
    
    #define Serial_MOSI_M_HSIOM_MASK      (Serial_mosi_m__0__HSIOM_MASK)
    #define Serial_MOSI_M_HSIOM_POS       (Serial_mosi_m__0__HSIOM_SHIFT)
    #define Serial_MOSI_M_HSIOM_SEL_GPIO  (Serial_mosi_m__0__HSIOM_GPIO)
    #define Serial_MOSI_M_HSIOM_SEL_SPI   (Serial_mosi_m__0__HSIOM_SPI)
#endif /* (Serial_SPI_MASTER_MOSI_PIN) */

#if (Serial_SPI_MASTER_SCLK_PIN)
    #define Serial_SCLK_M_HSIOM_REG   (*(reg32 *) Serial_sclk_m__0__HSIOM)
    #define Serial_SCLK_M_HSIOM_PTR   ( (reg32 *) Serial_sclk_m__0__HSIOM)
    
    #define Serial_SCLK_M_HSIOM_MASK      (Serial_sclk_m__0__HSIOM_MASK)
    #define Serial_SCLK_M_HSIOM_POS       (Serial_sclk_m__0__HSIOM_SHIFT)
    #define Serial_SCLK_M_HSIOM_SEL_GPIO  (Serial_sclk_m__0__HSIOM_GPIO)
    #define Serial_SCLK_M_HSIOM_SEL_SPI   (Serial_sclk_m__0__HSIOM_SPI)
#endif /* (Serial_SPI_MASTER_SCLK_PIN) */

#if (Serial_SPI_MASTER_SS0_PIN)
    #define Serial_SS0_M_HSIOM_REG    (*(reg32 *) Serial_ss0_m__0__HSIOM)
    #define Serial_SS0_M_HSIOM_PTR    ( (reg32 *) Serial_ss0_m__0__HSIOM)
    
    #define Serial_SS0_M_HSIOM_MASK       (Serial_ss0_m__0__HSIOM_MASK)
    #define Serial_SS0_M_HSIOM_POS        (Serial_ss0_m__0__HSIOM_SHIFT)
    #define Serial_SS0_M_HSIOM_SEL_GPIO   (Serial_ss0_m__0__HSIOM_GPIO)
    #define Serial_SS0_M_HSIOM_SEL_SPI    (Serial_ss0_m__0__HSIOM_SPI)
#endif /* (Serial_SPI_MASTER_SS0_PIN) */

#if (Serial_SPI_MASTER_SS1_PIN)
    #define Serial_SS1_M_HSIOM_REG    (*(reg32 *) Serial_ss1_m__0__HSIOM)
    #define Serial_SS1_M_HSIOM_PTR    ( (reg32 *) Serial_ss1_m__0__HSIOM)
    
    #define Serial_SS1_M_HSIOM_MASK       (Serial_ss1_m__0__HSIOM_MASK)
    #define Serial_SS1_M_HSIOM_POS        (Serial_ss1_m__0__HSIOM_SHIFT)
    #define Serial_SS1_M_HSIOM_SEL_GPIO   (Serial_ss1_m__0__HSIOM_GPIO)
    #define Serial_SS1_M_HSIOM_SEL_SPI    (Serial_ss1_m__0__HSIOM_SPI)
#endif /* (Serial_SPI_MASTER_SS1_PIN) */

#if (Serial_SPI_MASTER_SS2_PIN)
    #define Serial_SS2_M_HSIOM_REG    (*(reg32 *) Serial_ss2_m__0__HSIOM)
    #define Serial_SS2_M_HSIOM_PTR    ( (reg32 *) Serial_ss2_m__0__HSIOM)
    
    #define Serial_SS2_M_HSIOM_MASK       (Serial_ss2_m__0__HSIOM_MASK)
    #define Serial_SS2_M_HSIOM_POS        (Serial_ss2_m__0__HSIOM_SHIFT)
    #define Serial_SS2_M_HSIOM_SEL_GPIO   (Serial_ss2_m__0__HSIOM_GPIO)
    #define Serial_SS2_M_HSIOM_SEL_SPI    (Serial_ss2_m__0__HSIOM_SPI)
#endif /* (Serial_SPI_MASTER_SS2_PIN) */

#if (Serial_SPI_MASTER_SS3_PIN)
    #define Serial_SS3_M_HSIOM_REG    (*(reg32 *) Serial_ss3_m__0__HSIOM)
    #define Serial_SS3_M_HSIOM_PTR    ( (reg32 *) Serial_ss3_m__0__HSIOM)
    
    #define Serial_SS3_M_HSIOM_MASK      (Serial_ss3_m__0__HSIOM_MASK)
    #define Serial_SS3_M_HSIOM_POS       (Serial_ss3_m__0__HSIOM_SHIFT)
    #define Serial_SS3_M_HSIOM_SEL_GPIO  (Serial_ss3_m__0__HSIOM_GPIO)
    #define Serial_SS3_M_HSIOM_SEL_SPI   (Serial_ss3_m__0__HSIOM_SPI)
#endif /* (Serial_SPI_MASTER_SS3_PIN) */

#if (Serial_UART_RX_PIN)
    #define Serial_RX_HSIOM_REG   (*(reg32 *) Serial_rx__0__HSIOM)
    #define Serial_RX_HSIOM_PTR   ( (reg32 *) Serial_rx__0__HSIOM)
    
    #define Serial_RX_HSIOM_MASK      (Serial_rx__0__HSIOM_MASK)
    #define Serial_RX_HSIOM_POS       (Serial_rx__0__HSIOM_SHIFT)
    #define Serial_RX_HSIOM_SEL_GPIO  (Serial_rx__0__HSIOM_GPIO)
    #define Serial_RX_HSIOM_SEL_UART  (Serial_rx__0__HSIOM_UART)
#endif /* (Serial_UART_RX_PIN) */

#if (Serial_UART_RX_WAKE_PIN)
    #define Serial_RX_WAKE_HSIOM_REG   (*(reg32 *) Serial_rx_wake__0__HSIOM)
    #define Serial_RX_WAKE_HSIOM_PTR   ( (reg32 *) Serial_rx_wake__0__HSIOM)
    
    #define Serial_RX_WAKE_HSIOM_MASK      (Serial_rx_wake__0__HSIOM_MASK)
    #define Serial_RX_WAKE_HSIOM_POS       (Serial_rx_wake__0__HSIOM_SHIFT)
    #define Serial_RX_WAKE_HSIOM_SEL_GPIO  (Serial_rx_wake__0__HSIOM_GPIO)
    #define Serial_RX_WAKE_HSIOM_SEL_UART  (Serial_rx_wake__0__HSIOM_UART)
#endif /* (Serial_UART_WAKE_RX_PIN) */

#if (Serial_UART_CTS_PIN)
    #define Serial_CTS_HSIOM_REG   (*(reg32 *) Serial_cts__0__HSIOM)
    #define Serial_CTS_HSIOM_PTR   ( (reg32 *) Serial_cts__0__HSIOM)
    
    #define Serial_CTS_HSIOM_MASK      (Serial_cts__0__HSIOM_MASK)
    #define Serial_CTS_HSIOM_POS       (Serial_cts__0__HSIOM_SHIFT)
    #define Serial_CTS_HSIOM_SEL_GPIO  (Serial_cts__0__HSIOM_GPIO)
    #define Serial_CTS_HSIOM_SEL_UART  (Serial_cts__0__HSIOM_UART)
#endif /* (Serial_UART_CTS_PIN) */

#if (Serial_UART_TX_PIN)
    #define Serial_TX_HSIOM_REG   (*(reg32 *) Serial_tx__0__HSIOM)
    #define Serial_TX_HSIOM_PTR   ( (reg32 *) Serial_tx__0__HSIOM)
    
    #define Serial_TX_HSIOM_MASK      (Serial_tx__0__HSIOM_MASK)
    #define Serial_TX_HSIOM_POS       (Serial_tx__0__HSIOM_SHIFT)
    #define Serial_TX_HSIOM_SEL_GPIO  (Serial_tx__0__HSIOM_GPIO)
    #define Serial_TX_HSIOM_SEL_UART  (Serial_tx__0__HSIOM_UART)
#endif /* (Serial_UART_TX_PIN) */

#if (Serial_UART_RX_TX_PIN)
    #define Serial_RX_TX_HSIOM_REG   (*(reg32 *) Serial_rx_tx__0__HSIOM)
    #define Serial_RX_TX_HSIOM_PTR   ( (reg32 *) Serial_rx_tx__0__HSIOM)
    
    #define Serial_RX_TX_HSIOM_MASK      (Serial_rx_tx__0__HSIOM_MASK)
    #define Serial_RX_TX_HSIOM_POS       (Serial_rx_tx__0__HSIOM_SHIFT)
    #define Serial_RX_TX_HSIOM_SEL_GPIO  (Serial_rx_tx__0__HSIOM_GPIO)
    #define Serial_RX_TX_HSIOM_SEL_UART  (Serial_rx_tx__0__HSIOM_UART)
#endif /* (Serial_UART_RX_TX_PIN) */

#if (Serial_UART_RTS_PIN)
    #define Serial_RTS_HSIOM_REG      (*(reg32 *) Serial_rts__0__HSIOM)
    #define Serial_RTS_HSIOM_PTR      ( (reg32 *) Serial_rts__0__HSIOM)
    
    #define Serial_RTS_HSIOM_MASK     (Serial_rts__0__HSIOM_MASK)
    #define Serial_RTS_HSIOM_POS      (Serial_rts__0__HSIOM_SHIFT)    
    #define Serial_RTS_HSIOM_SEL_GPIO (Serial_rts__0__HSIOM_GPIO)
    #define Serial_RTS_HSIOM_SEL_UART (Serial_rts__0__HSIOM_UART)    
#endif /* (Serial_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define Serial_HSIOM_DEF_SEL      (0x00u)
#define Serial_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for Serial_CY_SCBIP_V0 
* and Serial_CY_SCBIP_V1. It is not recommended to use them for 
* Serial_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define Serial_HSIOM_UART_SEL     (0x09u)
#define Serial_HSIOM_I2C_SEL      (0x0Eu)
#define Serial_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define Serial_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define Serial_RX_SCL_MOSI_PIN_INDEX       (0u)
#define Serial_TX_SDA_MISO_PIN_INDEX       (1u)
#define Serial_SCLK_PIN_INDEX       (2u)
#define Serial_SS0_PIN_INDEX       (3u)
#define Serial_SS1_PIN_INDEX                  (4u)
#define Serial_SS2_PIN_INDEX                  (5u)
#define Serial_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define Serial_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << Serial_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define Serial_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << Serial_RX_SCL_MOSI_PIN_INDEX)
#define Serial_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << Serial_TX_SDA_MISO_PIN_INDEX)
#define Serial_SCLK_PIN_MASK     ((uint32) 0x01u << Serial_SCLK_PIN_INDEX)
#define Serial_SS0_PIN_MASK     ((uint32) 0x01u << Serial_SS0_PIN_INDEX)
#define Serial_SS1_PIN_MASK                ((uint32) 0x01u << Serial_SS1_PIN_INDEX)
#define Serial_SS2_PIN_MASK                ((uint32) 0x01u << Serial_SS2_PIN_INDEX)
#define Serial_SS3_PIN_MASK                ((uint32) 0x01u << Serial_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define Serial_INTCFG_TYPE_MASK           (0x03u)
#define Serial_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define Serial_PIN_DM_ALG_HIZ  (0u)
#define Serial_PIN_DM_DIG_HIZ  (1u)
#define Serial_PIN_DM_OD_LO    (4u)
#define Serial_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define Serial_DM_MASK    (0x7u)
#define Serial_DM_SIZE    (3u)
#define Serial_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) Serial_DM_MASK << (Serial_DM_SIZE * (pos)))) >> \
                                                              (Serial_DM_SIZE * (pos)) )

#if (Serial_TX_SDA_MISO_PIN)
    #define Serial_CHECK_TX_SDA_MISO_PIN_USED \
                (Serial_PIN_DM_ALG_HIZ != \
                    Serial_GET_P4_PIN_DM(Serial_uart_tx_i2c_sda_spi_miso_PC, \
                                                   Serial_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (Serial_TX_SDA_MISO_PIN) */

#if (Serial_SS0_PIN)
    #define Serial_CHECK_SS0_PIN_USED \
                (Serial_PIN_DM_ALG_HIZ != \
                    Serial_GET_P4_PIN_DM(Serial_spi_ss0_PC, \
                                                   Serial_spi_ss0_SHIFT))
#endif /* (Serial_SS0_PIN) */

/* Set bits-mask in register */
#define Serial_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define Serial_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define Serial_SET_HSIOM_SEL(reg, mask, pos, sel) Serial_SET_REGISTER_BITS(reg, mask, pos, sel)
#define Serial_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        Serial_SET_REGISTER_BITS(reg, mask, pos, intType)
#define Serial_SET_INP_DIS(reg, mask, val) Serial_SET_REGISTER_BIT(reg, mask, val)

/* Serial_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  Serial_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (Serial_CY_SCBIP_V0)
#if (Serial_I2C_PINS)
    #define Serial_SET_I2C_SCL_DR(val) Serial_scl_Write(val)

    #define Serial_SET_I2C_SCL_HSIOM_SEL(sel) \
                          Serial_SET_HSIOM_SEL(Serial_SCL_HSIOM_REG,  \
                                                         Serial_SCL_HSIOM_MASK, \
                                                         Serial_SCL_HSIOM_POS,  \
                                                         (sel))
    #define Serial_WAIT_SCL_SET_HIGH  (0u == Serial_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (Serial_RX_WAKE_SCL_MOSI_PIN)
    #define Serial_SET_I2C_SCL_DR(val) \
                            Serial_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define Serial_SET_I2C_SCL_HSIOM_SEL(sel) \
                    Serial_SET_HSIOM_SEL(Serial_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   Serial_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   Serial_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define Serial_WAIT_SCL_SET_HIGH  (0u == Serial_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (Serial_RX_SCL_MOSI_PIN)
    #define Serial_SET_I2C_SCL_DR(val) \
                            Serial_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define Serial_SET_I2C_SCL_HSIOM_SEL(sel) \
                            Serial_SET_HSIOM_SEL(Serial_RX_SCL_MOSI_HSIOM_REG,  \
                                                           Serial_RX_SCL_MOSI_HSIOM_MASK, \
                                                           Serial_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define Serial_WAIT_SCL_SET_HIGH  (0u == Serial_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define Serial_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define Serial_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define Serial_WAIT_SCL_SET_HIGH  (0u)
#endif /* (Serial_I2C_PINS) */

/* SCB I2C: sda signal */
#if (Serial_I2C_PINS)
    #define Serial_WAIT_SDA_SET_HIGH  (0u == Serial_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (Serial_TX_SDA_MISO_PIN)
    #define Serial_WAIT_SDA_SET_HIGH  (0u == Serial_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define Serial_WAIT_SDA_SET_HIGH  (0u)
#endif /* (Serial_MOSI_SCL_RX_PIN) */
#endif /* (Serial_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (Serial_RX_SCL_MOSI_PIN)
    #define Serial_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (Serial_RX_WAKE_SCL_MOSI_PIN)
    #define Serial_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) Serial_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(Serial_UART_RX_WAKE_PIN)
    #define Serial_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) Serial_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (Serial_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define Serial_REMOVE_MOSI_SCL_RX_WAKE_PIN    Serial_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define Serial_REMOVE_MOSI_SCL_RX_PIN         Serial_REMOVE_RX_SCL_MOSI_PIN
#define Serial_REMOVE_MISO_SDA_TX_PIN         Serial_REMOVE_TX_SDA_MISO_PIN
#ifndef Serial_REMOVE_SCLK_PIN
#define Serial_REMOVE_SCLK_PIN                Serial_REMOVE_SCLK_PIN
#endif /* Serial_REMOVE_SCLK_PIN */
#ifndef Serial_REMOVE_SS0_PIN
#define Serial_REMOVE_SS0_PIN                 Serial_REMOVE_SS0_PIN
#endif /* Serial_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define Serial_MOSI_SCL_RX_WAKE_PIN   Serial_RX_WAKE_SCL_MOSI_PIN
#define Serial_MOSI_SCL_RX_PIN        Serial_RX_SCL_MOSI_PIN
#define Serial_MISO_SDA_TX_PIN        Serial_TX_SDA_MISO_PIN
#ifndef Serial_SCLK_PIN
#define Serial_SCLK_PIN               Serial_SCLK_PIN
#endif /* Serial_SCLK_PIN */
#ifndef Serial_SS0_PIN
#define Serial_SS0_PIN                Serial_SS0_PIN
#endif /* Serial_SS0_PIN */

#if (Serial_MOSI_SCL_RX_WAKE_PIN)
    #define Serial_MOSI_SCL_RX_WAKE_HSIOM_REG     Serial_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Serial_MOSI_SCL_RX_WAKE_HSIOM_PTR     Serial_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Serial_MOSI_SCL_RX_WAKE_HSIOM_MASK    Serial_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Serial_MOSI_SCL_RX_WAKE_HSIOM_POS     Serial_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Serial_MOSI_SCL_RX_WAKE_INTCFG_REG    Serial_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Serial_MOSI_SCL_RX_WAKE_INTCFG_PTR    Serial_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Serial_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   Serial_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Serial_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  Serial_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (Serial_RX_WAKE_SCL_MOSI_PIN) */

#if (Serial_MOSI_SCL_RX_PIN)
    #define Serial_MOSI_SCL_RX_HSIOM_REG      Serial_RX_SCL_MOSI_HSIOM_REG
    #define Serial_MOSI_SCL_RX_HSIOM_PTR      Serial_RX_SCL_MOSI_HSIOM_PTR
    #define Serial_MOSI_SCL_RX_HSIOM_MASK     Serial_RX_SCL_MOSI_HSIOM_MASK
    #define Serial_MOSI_SCL_RX_HSIOM_POS      Serial_RX_SCL_MOSI_HSIOM_POS
#endif /* (Serial_MOSI_SCL_RX_PIN) */

#if (Serial_MISO_SDA_TX_PIN)
    #define Serial_MISO_SDA_TX_HSIOM_REG      Serial_TX_SDA_MISO_HSIOM_REG
    #define Serial_MISO_SDA_TX_HSIOM_PTR      Serial_TX_SDA_MISO_HSIOM_REG
    #define Serial_MISO_SDA_TX_HSIOM_MASK     Serial_TX_SDA_MISO_HSIOM_REG
    #define Serial_MISO_SDA_TX_HSIOM_POS      Serial_TX_SDA_MISO_HSIOM_REG
#endif /* (Serial_MISO_SDA_TX_PIN_PIN) */

#if (Serial_SCLK_PIN)
    #ifndef Serial_SCLK_HSIOM_REG
    #define Serial_SCLK_HSIOM_REG     Serial_SCLK_HSIOM_REG
    #define Serial_SCLK_HSIOM_PTR     Serial_SCLK_HSIOM_PTR
    #define Serial_SCLK_HSIOM_MASK    Serial_SCLK_HSIOM_MASK
    #define Serial_SCLK_HSIOM_POS     Serial_SCLK_HSIOM_POS
    #endif /* Serial_SCLK_HSIOM_REG */
#endif /* (Serial_SCLK_PIN) */

#if (Serial_SS0_PIN)
    #ifndef Serial_SS0_HSIOM_REG
    #define Serial_SS0_HSIOM_REG      Serial_SS0_HSIOM_REG
    #define Serial_SS0_HSIOM_PTR      Serial_SS0_HSIOM_PTR
    #define Serial_SS0_HSIOM_MASK     Serial_SS0_HSIOM_MASK
    #define Serial_SS0_HSIOM_POS      Serial_SS0_HSIOM_POS
    #endif /* Serial_SS0_HSIOM_REG */
#endif /* (Serial_SS0_PIN) */

#define Serial_MOSI_SCL_RX_WAKE_PIN_INDEX Serial_RX_WAKE_SCL_MOSI_PIN_INDEX
#define Serial_MOSI_SCL_RX_PIN_INDEX      Serial_RX_SCL_MOSI_PIN_INDEX
#define Serial_MISO_SDA_TX_PIN_INDEX      Serial_TX_SDA_MISO_PIN_INDEX
#ifndef Serial_SCLK_PIN_INDEX
#define Serial_SCLK_PIN_INDEX             Serial_SCLK_PIN_INDEX
#endif /* Serial_SCLK_PIN_INDEX */
#ifndef Serial_SS0_PIN_INDEX
#define Serial_SS0_PIN_INDEX              Serial_SS0_PIN_INDEX
#endif /* Serial_SS0_PIN_INDEX */

#define Serial_MOSI_SCL_RX_WAKE_PIN_MASK Serial_RX_WAKE_SCL_MOSI_PIN_MASK
#define Serial_MOSI_SCL_RX_PIN_MASK      Serial_RX_SCL_MOSI_PIN_MASK
#define Serial_MISO_SDA_TX_PIN_MASK      Serial_TX_SDA_MISO_PIN_MASK
#ifndef Serial_SCLK_PIN_MASK
#define Serial_SCLK_PIN_MASK             Serial_SCLK_PIN_MASK
#endif /* Serial_SCLK_PIN_MASK */
#ifndef Serial_SS0_PIN_MASK
#define Serial_SS0_PIN_MASK              Serial_SS0_PIN_MASK
#endif /* Serial_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_Serial_H) */


/* [] END OF FILE */
