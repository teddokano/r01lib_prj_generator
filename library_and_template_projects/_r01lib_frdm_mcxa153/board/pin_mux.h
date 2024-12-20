/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define PCR_IBE_ibe1 0x01u          /*!<@brief Input Buffer Enable: Enables */
#define PORT1_PCR0_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT1_PCR1_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT1_PCR3_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR0_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR12_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR13_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR16_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR1_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR2_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR4_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR5_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT2_PCR6_MUX_mux00 0x00u  /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT3_PCR27_MUX_mux10 0x02u /*!<@brief Pin Multiplex Control: Alternative 2 (chip-specific) */
#define PORT3_PCR28_MUX_mux10 0x02u /*!<@brief Pin Multiplex Control: Alternative 2 (chip-specific) */
#define PORT3_PCR29_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT3_PCR30_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT3_PCR31_MUX_mux00 0x00u /*!<@brief Pin Multiplex Control: Alternative 0 (GPIO) */
#define PORT3_PCR7_MUX_mux101 0x05u /*!<@brief Pin Multiplex Control: Alternative 5 (chip-specific) */

/*! @name PORT3_12 (number 38), ARD_D5
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D5_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D5_GPIO_PIN 12U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D5_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D5_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D5_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D5_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_13 (number 37), ARD_D6
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D6_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D6_GPIO_PIN 13U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D6_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D6_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D6_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D6_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_31 (number 30), ARD_A4
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_A4_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_A4_GPIO_PIN 31U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_A4_GPIO_PIN_MASK (1U << 31U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_A4_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_A4_PIN 31U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_A4_PIN_MASK (1U << 31U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_30 (number 31), ARD_A5
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_A5_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_A5_GPIO_PIN 30U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_A5_GPIO_PIN_MASK (1U << 30U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_A5_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_A5_PIN 30U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_A5_PIN_MASK (1U << 30U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT1_12 (number 6), ARD_A1
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_A1_GPIO GPIO1                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_A1_GPIO_PIN 12U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_A1_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_A1_PORT PORT1                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_A1_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_A1_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT1_13 (number 7), ARD_A2
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_A2_GPIO GPIO1                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_A2_GPIO_PIN 13U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_A2_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_A2_PORT PORT1                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_A2_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_A2_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT2_0 (number 14), ARD_A3
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_A3_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_A3_GPIO_PIN 0U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_A3_GPIO_PIN_MASK (1U << 0U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_A3_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_A3_PIN 0U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_A3_PIN_MASK (1U << 0U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT2_4 (number 18), ARD_D2
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D2_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D2_GPIO_PIN 4U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D2_GPIO_PIN_MASK (1U << 4U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D2_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D2_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D2_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT2_5 (number 19), ARD_D4
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D4_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D4_GPIO_PIN 5U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D4_GPIO_PIN_MASK (1U << 5U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D4_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D4_PIN 5U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D4_PIN_MASK (1U << 5U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT3_15 (number 35), ARD_D8
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D8_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D8_GPIO_PIN 15U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D8_GPIO_PIN_MASK (1U << 15U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D8_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D8_PIN 15U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D8_PIN_MASK (1U << 15U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_14 (number 36), ARD_D9
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D9_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D9_GPIO_PIN 14U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D9_GPIO_PIN_MASK (1U << 14U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D9_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D9_PIN 14U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D9_PIN_MASK (1U << 14U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT2_12 (number 22), ARD_D13
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D13_GPIO GPIO2                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D13_GPIO_PIN 12U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D13_GPIO_PIN_MASK (1U << 12U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D13_PORT PORT2                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D13_PIN 12U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D13_PIN_MASK (1U << 12U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT2_13 (number 23), ARD_D11
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D11_GPIO GPIO2                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D11_GPIO_PIN 13U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D11_GPIO_PIN_MASK (1U << 13U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D11_PORT PORT2                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D11_PIN 13U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D11_PIN_MASK (1U << 13U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT2_16 (number 24), ARD_D12
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D12_GPIO GPIO2                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D12_GPIO_PIN 16U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D12_GPIO_PIN_MASK (1U << 16U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D12_PORT PORT2                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D12_PIN 16U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D12_PIN_MASK (1U << 16U)      /*!<@brief PORT pin mask */
                                                         /* @} */

/*! @name PORT2_6 (number 20), ARD_D10
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D10_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D10_GPIO_PIN 6U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D10_GPIO_PIN_MASK (1U << 6U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D10_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D10_PIN 6U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D10_PIN_MASK (1U << 6U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_1 (number 45), ARD_D7
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D7_GPIO GPIO3               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D7_GPIO_PIN 1U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D7_GPIO_PIN_MASK (1U << 1U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D7_PORT PORT3               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D7_PIN 1U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D7_PIN_MASK (1U << 1U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT1_4 (number 62), ARD_D0
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D0_GPIO GPIO1               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D0_GPIO_PIN 4U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D0_GPIO_PIN_MASK (1U << 4U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D0_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D0_PIN 4U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D0_PIN_MASK (1U << 4U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT1_5 (number 63), ARD_D1
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D1_GPIO GPIO1               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D1_GPIO_PIN 5U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D1_GPIO_PIN_MASK (1U << 5U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D1_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D1_PIN 5U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D1_PIN_MASK (1U << 5U)      /*!<@brief PORT pin mask */
                                                       /* @} */

/*! @name PORT1_10 (number 4), ARD_A0
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_A0_GPIO GPIO1                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_A0_GPIO_PIN 10U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_A0_GPIO_PIN_MASK (1U << 10U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_A0_PORT PORT1                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_A0_PIN 10U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_A0_PIN_MASK (1U << 10U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT3_29 (number 32), SW2
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SW2_GPIO GPIO3                /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SW2_GPIO_PIN 29U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_SW2_GPIO_PIN_MASK (1U << 29U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_SW2_PORT PORT3                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SW2_PIN 29U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SW2_PIN_MASK (1U << 29U)      /*!<@brief PORT pin mask */
                                                     /* @} */

/*! @name PORT1_7 (number 1), SW3
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_SW3_GPIO GPIO1               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_SW3_GPIO_PIN 7U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_SW3_GPIO_PIN_MASK (1U << 7U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_SW3_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_SW3_PIN 7U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_SW3_PIN_MASK (1U << 7U)      /*!<@brief PORT pin mask */
                                                    /* @} */

/*! @name PORT1_9 (number 3), ARD_D19
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ARD_D19_GPIO GPIO1               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ARD_D19_GPIO_PIN 9U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ARD_D19_GPIO_PIN_MASK (1U << 9U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ARD_D19_PORT PORT1               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ARD_D19_PIN 9U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ARD_D19_PIN_MASK (1U << 9U)      /*!<@brief PORT pin mask */
                                                        /* @} */

/*! @name PORT2_2 (number 16), ADC0
  @{ */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_ADC0_GPIO GPIO2               /*!<@brief GPIO peripheral base pointer */
#define BOARD_INITPINS_ADC0_GPIO_PIN 2U              /*!<@brief GPIO pin number */
#define BOARD_INITPINS_ADC0_GPIO_PIN_MASK (1U << 2U) /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ADC0_PORT PORT2               /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ADC0_PIN 2U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ADC0_PIN_MASK (1U << 2U)      /*!<@brief PORT pin mask */
                                                     /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
