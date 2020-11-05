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
#include "app_test_runner.h"

#define TEST_MODE AUTOMATIC_TEST_MODE
#define TEST_NAME "Test Example"

#include "nrf_delay.h"

void setUp(void)
{

}

void tearDown(void)
{

}



void test_success(void)
{
    TEST_ASSERT_TRUE(true);
}

void test_fail(void)
{
    TEST_ASSERT_TRUE(false);
}


case_t m_test_cases[] = {
    TEST_CASE(test_success),
    TEST_CASE(test_fail)
};
