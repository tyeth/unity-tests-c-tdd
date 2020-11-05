/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
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
 * @defgroup app_test_runner
 * @{
 * @ingroup app_common
 *
 * @brief
 */

#ifndef APP_TEST_RUNNER_H__
#define APP_TEST_RUNNER_H__

#ifdef UNITY_FRAMEWORK_H
#error Do not include unity.h file directly when creating target test. Include this app_test_runner.h only.
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "nrf_error.h"
#include "app_test_pins.h"

#define RUN_TEST(test_case, line_num) UnityDefaultTestRun((test_case).func, \
                                                          (test_case).name, \
                                                          line_num)

#include "unity.h"

#define TEST_ERROR_CHECK(err_code)     UNITY_TEST_ASSERT_EQUAL_INT32((NRF_SUCCESS), (err_code), __LINE__, NULL)

#define TEST_BUFFER_SIZE  1024
#define UNITY_NOINIT_BUFFER_SIZE 0x200
#ifndef SOFTDEVICE_PRESENT
#define RAM_UNITY_ADDRESS (0x20000000UL)
#else
//lint -save -e27 -e10 -e19
#if defined ( __CC_ARM )
    extern uint32_t Image$$RW_IRAM1$$Base;
    #define RAM_UNITY_ADDRESS (uint32_t) (&Image$$RW_IRAM1$$Base - UNITY_NOINIT_BUFFER_SIZE)
#elif defined ( __ICCARM__ )
    extern uint32_t __ICFEDIT_region_RAM_start__;
    #define RAM_UNITY_ADDRESS (uint32_t) (&__ICFEDIT_region_RAM_start__- UNITY_NOINIT_BUFFER_SIZE)
#elif defined   ( __GNUC__ )
    extern uint32_t __data_start__;
#define RAM_UNITY_ADDRESS (uint32_t) (&__data_start__ - UNITY_NOINIT_BUFFER_SIZE)
#endif//__CC_ARM
//lint -restore
#endif
#define AUTOMATIC_TEST_MODE 0
#define MANUAL_TEST_MODE    1

#define TEST_CASE(new_case) \
    {                       \
        new_case,           \
        #new_case           \
    }

typedef struct
{
    UnityTestFunction func;
    const char      * name;
} case_t;

/**
 * @brief Configure the masks of expected reset reasons
 *
 * This function needs to be called before expected reset.
 * After reset last test would be repeated.
 * @param reas Expected reset reason mask
 */
void app_test_runner_set_expected_reset(uint32_t reas);

#endif // APP_TEST_RUNNER_H__

/** @} */
