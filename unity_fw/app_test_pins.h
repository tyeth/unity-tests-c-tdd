/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/**@file
 *
 * @defgroup app_test_pins
 * @{
 * @ingroup app_common
 *
 * @brief Definitions of a pins used for unit testing.
          Pin pairs (1A, 1B), (2A, 2B), (3A, 3B) are shorted together in the test setups.
 */

#ifndef APP_TEST_PINS_H__
#define APP_TEST_PINS_H__

#include "nrf.h"
#include "boards.h"

#define TEST_PIN_1A     ARDUINO_A0_PIN
#define TEST_PIN_1B     ARDUINO_A5_PIN
#define TEST_PIN_2A     ARDUINO_A1_PIN
#define TEST_PIN_2B     ARDUINO_A4_PIN
#define TEST_PIN_3A     ARDUINO_A2_PIN
#define TEST_PIN_3B     ARDUINO_A3_PIN
#define TEST_PIN_4A     ARDUINO_SDA_PIN
#define TEST_PIN_4B     ARDUINO_SCL_PIN

#endif // APP_TEST_PINS_H__

/** @} */
