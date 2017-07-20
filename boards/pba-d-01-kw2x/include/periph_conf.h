/*
 * Copyright (C) 2014-2016 Freie Universität Berlin
 * Copyright (C) 2014 PHYTEC Messtechnik GmbH
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_pba-d-01-kw2x
 * @{
 *
 * @file
 * @name        Peripheral MCU configuration for the phyWAVE-KW22 Board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Johann Fischer <j.fischer@phytec.de>
 * @author      Jonas Remmert <j.remmert@phytec.de>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "periph_cpu.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name Clock system configuration
 * @{
 */
#define KINETIS_CPU_USE_MCG               1

#define KINETIS_MCG_USE_ERC               1
#define KINETIS_MCG_USE_PLL               1
#define KINETIS_MCG_DCO_RANGE             (24000000U)
#define KINETIS_MCG_ERC_OSCILLATOR        0
#define KINETIS_MCG_ERC_FRDIV             2
#define KINETIS_MCG_ERC_RANGE             1
#define KINETIS_MCG_ERC_FREQ              4000000
#define KINETIS_MCG_PLL_PRDIV             1
#define KINETIS_MCG_PLL_VDIV0             0
#define KINETIS_MCG_PLL_FREQ              48000000

#define CLOCK_CORECLOCK                   KINETIS_MCG_PLL_FREQ
#define CLOCK_BUSCLOCK                    CLOCK_CORECLOCK
/** @} */

/**
 * @name Timer configuration
 * @{
 */
#define PIT_NUMOF               (2U)
#define PIT_CONFIG {                 \
        {                            \
            .prescaler_ch = 0,       \
            .count_ch = 1,           \
        },                           \
        {                            \
            .prescaler_ch = 2,       \
            .count_ch = 3,           \
        },                           \
    }
#define LPTMR_NUMOF             (0U)
#define LPTMR_CONFIG {}
#define TIMER_NUMOF             ((PIT_NUMOF) + (LPTMR_NUMOF))

#define PIT_BASECLOCK           (CLOCK_BUSCLOCK)
#define PIT_ISR_0               isr_pit1
#define PIT_ISR_1               isr_pit3
#define LPTMR_ISR_0             isr_lptmr0

/** @} */

/**
 * @name UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev    = UART2,
        .freq   = CLOCK_BUSCLOCK,
        .pin_rx = GPIO_PIN(PORT_D, 2),
        .pin_tx = GPIO_PIN(PORT_D, 3),
        .pcr_rx = PORT_PCR_MUX(3),
        .pcr_tx = PORT_PCR_MUX(3),
        .irqn   = UART2_RX_TX_IRQn,
        .scgc_addr = &SIM->SCGC4,
        .scgc_bit = SIM_SCGC4_UART2_SHIFT,
        .mode   = UART_MODE_8N1
    },
    {
        .dev    = UART0,
        .freq   = CLOCK_CORECLOCK,
        .pin_rx = GPIO_PIN(PORT_D, 6),
        .pin_tx = GPIO_PIN(PORT_D, 7),
        .pcr_rx = PORT_PCR_MUX(3),
        .pcr_tx = PORT_PCR_MUX(3),
        .irqn   = UART0_RX_TX_IRQn,
        .scgc_addr = &SIM->SCGC4,
        .scgc_bit = SIM_SCGC4_UART0_SHIFT,
        .mode   = UART_MODE_8N1
    }
};

#define UART_0_ISR          (isr_uart2_rx_tx)
#define UART_1_ISR          (isr_uart0_rx_tx)

#define UART_NUMOF          (sizeof(uart_config) / sizeof(uart_config[0]))
/** @} */

/**
 * @name    ADC configuration
 * @{
 */
static const adc_conf_t adc_config[] = {
    { .dev = ADC0, .pin = GPIO_PIN(PORT_E, 2), .chan =  1 },
    { .dev = ADC0, .pin = GPIO_PIN(PORT_E, 3), .chan =  1 },
    { .dev = ADC0, .pin = GPIO_PIN(PORT_D, 7), .chan = 22 },
    { .dev = ADC0, .pin = GPIO_PIN(PORT_D, 5), .chan =  6 },
    { .dev = ADC0, .pin = GPIO_PIN(PORT_E, 0), .chan = 10 },
    { .dev = ADC0, .pin = GPIO_PIN(PORT_E, 1), .chan = 11 }
};

#define ADC_NUMOF           (sizeof(adc_config) / sizeof(adc_config[0]))
/** @} */

/**
 * @name    PWM configuration
 * @{
 */
static const pwm_conf_t pwm_config[] = {
    {
        .ftm        = FTM0,
        .chan       = {
            { .pin = GPIO_PIN(PORT_A, 4), .af = 3, .ftm_chan = 1 },
            { .pin = GPIO_PIN(PORT_D, 4), .af = 4, .ftm_chan = 4 },
            { .pin = GPIO_PIN(PORT_D, 6), .af = 4, .ftm_chan = 6 },
            { .pin = GPIO_PIN(PORT_A, 1), .af = 3, .ftm_chan = 1 }
        },
        .chan_numof = 4,
        .ftm_num    = 0
    }
};

#define PWM_NUMOF           (sizeof(pwm_config) / sizeof(pwm_config[0]))
/** @} */


/**
 * @name    SPI device configuration
 *
 * Clock configuration values based on the configured 48Mhz module clock.
 *
 * Auto-generated by:
 * cpu/kinetis_common/dist/calc_spi_scalers/calc_spi_scalers.c
 *
 * @{
 */
static const uint32_t spi_clk_config[] = {
    (
        SPI_CTAR_PBR(0) | SPI_CTAR_BR(8) |          /* -> 93750Hz */
        SPI_CTAR_PCSSCK(0) | SPI_CTAR_CSSCK(8) |
        SPI_CTAR_PASC(0) | SPI_CTAR_ASC(8) |
        SPI_CTAR_PDT(0) | SPI_CTAR_DT(8)
    ),
    (
        SPI_CTAR_PBR(0) | SPI_CTAR_BR(6) |          /* -> 375000Hz */
        SPI_CTAR_PCSSCK(0) | SPI_CTAR_CSSCK(6) |
        SPI_CTAR_PASC(0) | SPI_CTAR_ASC(6) |
        SPI_CTAR_PDT(0) | SPI_CTAR_DT(6)
    ),
    (
        SPI_CTAR_PBR(1) | SPI_CTAR_BR(4) |          /* -> 1000000Hz */
        SPI_CTAR_PCSSCK(1) | SPI_CTAR_CSSCK(3) |
        SPI_CTAR_PASC(1) | SPI_CTAR_ASC(3) |
        SPI_CTAR_PDT(1) | SPI_CTAR_DT(3)
    ),
    (
        SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) |          /* -> 4800000Hz */
        SPI_CTAR_PCSSCK(2) | SPI_CTAR_CSSCK(0) |
        SPI_CTAR_PASC(2) | SPI_CTAR_ASC(0) |
        SPI_CTAR_PDT(2) | SPI_CTAR_DT(0)
    ),
    (
        SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) |          /* -> 8000000Hz */
        SPI_CTAR_PCSSCK(1) | SPI_CTAR_CSSCK(0) |
        SPI_CTAR_PASC(1) | SPI_CTAR_ASC(0) |
        SPI_CTAR_PDT(1) | SPI_CTAR_DT(0)
    )
};

static const spi_conf_t spi_config[] = {
    {
        .dev      = SPI0,
        .pin_miso = GPIO_PIN(PORT_C, 7),
        .pin_mosi = GPIO_PIN(PORT_C, 6),
        .pin_clk  = GPIO_PIN(PORT_C, 5),
        .pin_cs   = {
            GPIO_PIN(PORT_C, 4),
            GPIO_UNDEF,
            GPIO_UNDEF,
            GPIO_UNDEF,
            GPIO_UNDEF
        },
        .pcr      = GPIO_AF_2,
        .simmask  = SIM_SCGC6_SPI0_MASK
    },
    {
        .dev      = SPI1,
        .pin_miso = GPIO_PIN(PORT_B, 17),
        .pin_mosi = GPIO_PIN(PORT_B, 16),
        .pin_clk  = GPIO_PIN(PORT_B, 11),
        .pin_cs   = {
            GPIO_PIN(PORT_B, 10),
            GPIO_UNDEF,
            GPIO_UNDEF,
            GPIO_UNDEF,
            GPIO_UNDEF
        },
        .pcr      = GPIO_AF_2,
        .simmask  = SIM_SCGC6_SPI1_MASK
    }
};

#define SPI_NUMOF           (sizeof(spi_config) / sizeof(spi_config[0]))
/** @} */


/**
 * @name I2C configuration
 * @{
 */
#define I2C_NUMOF               (1U)
#define I2C_CLK                 (48e6)
#define I2C_0_EN                1
#define I2C_IRQ_PRIO            1
/* Low (10 kHz): MUL = 4, SCL divider = 2560, total: 10240 */
#define KINETIS_I2C_F_ICR_LOW        (0x3D)
#define KINETIS_I2C_F_MULT_LOW       (2)
/* Normal (100 kHz): MUL = 2, SCL divider = 240, total: 480 */
#define KINETIS_I2C_F_ICR_NORMAL     (0x1F)
#define KINETIS_I2C_F_MULT_NORMAL    (1)
/* Fast (400 kHz): MUL = 1, SCL divider = 128, total: 128 */
#define KINETIS_I2C_F_ICR_FAST       (0x17)
#define KINETIS_I2C_F_MULT_FAST      (0)
/* Fast plus (1000 kHz): MUL = 1, SCL divider = 48, total: 48 */
#define KINETIS_I2C_F_ICR_FAST_PLUS  (0x10)
#define KINETIS_I2C_F_MULT_FAST_PLUS (0)

/* I2C 0 device configuration */
#define I2C_0_DEV               I2C1
#define I2C_0_CLKEN()           (SIM->SCGC4 |= (SIM_SCGC4_I2C1_MASK))
#define I2C_0_CLKDIS()          (SIM->SCGC4 &= ~(SIM_SCGC4_I2C1_MASK))
#define I2C_0_IRQ               I2C1_IRQn
#define I2C_0_IRQ_HANDLER       isr_i2c1
/* I2C 0 pin configuration */
#define I2C_0_PORT              PORTE
#define I2C_0_PORT_CLKEN()      (SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK))
#define I2C_0_PIN_AF            6
#define I2C_0_SDA_PIN           0
#define I2C_0_SCL_PIN           1
#define I2C_0_PORT_CFG          (PORT_PCR_MUX(I2C_0_PIN_AF) | PORT_PCR_ODE_MASK)

/** @} */


/**
 * @name GPIO configuration
 * @{
 */
#define GPIO_IRQ_PRIO       CPU_DEFAULT_IRQ_PRIO
/** @} */

/**
* @name RTT and RTC configuration
* @{
*/
#define RTT_NUMOF            (1U)
#define RTC_NUMOF            (1U)
#define RTT_DEV              RTC
#define RTT_IRQ              RTC_IRQn
#define RTT_IRQ_PRIO         10
#define RTT_UNLOCK()         (SIM->SCGC6 |= (SIM_SCGC6_RTC_MASK))
#define RTT_ISR              isr_rtc
#define RTT_FREQUENCY        (1)
#define RTT_MAX_VALUE        (0xffffffff)
/** @} */

/**
 * @name Random Number Generator configuration
 * @{
 */
#define KINETIS_RNGA        RNG
#define HWRNG_CLKEN()       (SIM->SCGC6 |= (1 << 9))
#define HWRNG_CLKDIS()      (SIM->SCGC6 &= ~(1 << 9))

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
