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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "simple_uart.h"
#include "boards.h"
#include "app_fifo.h"
#include "nrf_delay.h"
#include "nordic_common.h"
#include "nrf_gpio.h"
#include "app_test_pins.h"
#include "test_cases.c"
#include "app_error.h"
#include "nrf_log_ctrl.h"
#ifdef FREERTOS
    #include "FreeRTOS.h"
    #include "task.h"
    #include "nrf_drv_clock.h"
#endif
//#define DEBUG
#ifdef DEBUG
#define _TEST_PIN 27
#define _TEST_PIN_CFG nrf_gpio_cfg_output(_TEST_PIN)
#define _TEST_PIN_TOGGLE nrf_gpio_pin_toggle(_TEST_PIN)
#else
#define _TEST_PIN_CFG
#define _TEST_PIN_TOGGLE
#endif


#define APP_TEST_RUNNER_LOG(args...)  \
    do {                              \
        uart_init();                  \
        printf(args);                 \
        app_test_runner_flush();      \
        uart_deinit();                \
    } while (0)

typedef struct {
    app_fifo_t               logger;
    uint8_t                  buffer[TEST_BUFFER_SIZE];
    volatile uint32_t      * p_current_case;
    volatile uint32_t      * p_expected_reset_reason;
    volatile struct _Unity * p_unity;
    uint32_t                 case_count;
} app_tester_t;
static app_tester_t m_test;

static bool m_aborted = false;
static bool m_test_case_finished = false;


void app_test_runner_putc(uint8_t ch)
{
    UNUSED_VARIABLE(app_fifo_put(&(m_test.logger), ch));
}

#if !defined(__ICCARM__)
struct __FILE
{
    int handle;
};
#endif
FILE __stdout;
FILE __stdin;

#if defined(__CC_ARM) ||  defined(__ICCARM__)

int fgetc(FILE * p_file)
{
    int input = (int)simple_uart_get();
    return input;
}
int fputc(int ch, FILE * p_file)
{
    UNUSED_PARAMETER(p_file);
    app_test_runner_putc((uint8_t)ch);
    return ch;
}

#elif defined(__GNUC__)

int _write(int file, const char * p_char, int len)
{
    int i;
    UNUSED_PARAMETER(file);
    for (i = 0; i < len; i++)
    {
        app_test_runner_putc(*p_char++);
    }
    return len;
}

int _read(int file, char * p_char, int len)
{
    UNUSED_PARAMETER(file);
    *p_char = simple_uart_get();
    return 1;
}
#endif


static void uart_init(void)
{
    simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, false);
}

static void uart_deinit(void)
{
#ifdef NRF51
    NRF_UART0->POWER = 0;
    NRF_UART0->POWER = 1;
#else
    NRF_UART0->ENABLE = 0;
#endif
    nrf_delay_ms(1);
}

/**
* @brief Function preparing mask with any reset reason available on mcu.
* @return The mask that connects masks of all possible reset reasons on mcu.
*/
uint32_t app_test_runner_any_resetreas()
{
   uint32_t resetreas = POWER_RESETREAS_RESETPIN_Msk | \
                        POWER_RESETREAS_DOG_Msk      | \
                        POWER_RESETREAS_SREQ_Msk     | \
                        POWER_RESETREAS_LOCKUP_Msk   | \
                        POWER_RESETREAS_OFF_Msk      | \
                        POWER_RESETREAS_LPCOMP_Msk   | \
                        POWER_RESETREAS_DIF_Msk;
#if defined(NRF52)
   resetreas |= POWER_RESETREAS_NFC_Msk;
#endif

#if defined(GRAVITON)
   resetreas |= POWER_RESETREAS_NFC_Msk |
                POWER_RESETREAS_VBUS_Msk;
#endif
   return resetreas;
}

void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    (void)pc;
    error_info_t const * p_error_info = (error_info_t const *)info;

    printf("app_error fault - id 0x%08X, code: 0x%08X\r\n"
           "%s:%u\r\n",
        (unsigned int)id, (unsigned int)(p_error_info->err_code),
        (char const *)p_error_info->p_file_name, p_error_info->line_num);
    Unity.TestFile = (char const *)p_error_info->p_file_name;
    UNITY_TEST_FAIL(p_error_info->line_num, "app_error fault");
}


static void app_test_runner_flush(void)
{
    uint8_t chr;

    while (NRF_SUCCESS == app_fifo_get(&(m_test.logger), &chr))
    {
        simple_uart_put(chr);
    }
}

void app_test_runner_set_expected_reset(uint32_t reason)
{
    *(m_test.p_expected_reset_reason) = reason;
}

static void app_test_runner_init(void)
{
    UNUSED_VARIABLE(app_fifo_init(&(m_test.logger), m_test.buffer, TEST_BUFFER_SIZE));

    nrf_delay_ms(650);

    //lint -save -e40
#if defined(__CC_ARM)
#pragma push
#pragma diag_suppress 170
#endif
    m_test.p_unity                 = (struct _Unity *)RAM_UNITY_ADDRESS;
    m_test.p_expected_reset_reason = (uint32_t *)(RAM_UNITY_ADDRESS + sizeof(struct _Unity));
#if defined(__CC_ARM)
#pragma pop
#endif
    //lint -restore

    m_test.p_current_case = &(NRF_POWER->GPREGRET);
    m_test.case_count     = sizeof(m_test_cases) / sizeof(case_t);
}

static void app_test_runner_summary(bool end_with_reset)
{
    __disable_irq();
    uart_deinit();
    uart_init();
    app_test_runner_flush();
    app_test_runner_set_expected_reset(POWER_RESETREAS_SREQ_Msk);
    __enable_irq();

    if (end_with_reset)
    {
        NVIC_SystemReset();
    }
}


#if TEST_MODE == AUTOMATIC_TEST_MODE

static void app_test_runner_finalize(void)
{
    if (*(m_test.p_current_case) < m_test.case_count)
    {
        *(m_test.p_unity) = Unity;
        (*(m_test.p_current_case))++;
    }

    bool end_with_reset = true;
    if (*(m_test.p_current_case) == m_test.case_count)
    {
        Unity = *(m_test.p_unity);
        UNUSED_VARIABLE(UnityEnd());
        end_with_reset = false;
    }

    app_test_runner_summary(end_with_reset);
}

static void app_test_runner_automatic(void)
{
    app_test_runner_init();

    uint32_t expected_reset_reason = (*(m_test.p_expected_reset_reason));
    // Currently no reset is expected.
    (*(m_test.p_expected_reset_reason)) = 0;

#ifndef NRF51
    uint32_t gpregret2 = NRF_POWER->GPREGRET2;
    //iar don't like operations on 2 volatiles
    uint32_t actual_reset_reason = NRF_POWER->RESETREAS | gpregret2;
#else
    uint32_t actual_reset_reason = NRF_POWER->RESETREAS;
#endif
    // Clear all known bits in reset reason register.
    NRF_POWER->RESETREAS = app_test_runner_any_resetreas();

    // Pin reset means - we are starting the tests, from the first test case.
    bool unexpected_reset = false;
    if (actual_reset_reason & POWER_RESETREAS_RESETPIN_Msk)
    {
#ifndef NRF51
        NRF_POWER->GPREGRET2 = 0;
#endif
        *(m_test.p_current_case) = 0;

        Unity.TestFile = TEST_NAME;
        UnityBegin();

        // Copy the 'Unity' structure to a place where it survives reset.
        *(m_test.p_unity) = Unity;
    }
    else
    {
        // Restore the contents of the 'Unity' structure as it was before reset.
        Unity = *(m_test.p_unity);

        // If the reason of the recent reset does not match what is expected
        // signal it as a test failure, since this may indicate some hidden
        // issue.
        if ((expected_reset_reason & actual_reset_reason) == 0)
        {
            APP_TEST_RUNNER_LOG("Reset reason: 0x%08X\r\n"
                                "    expected: 0x%08X\r\n",
                (unsigned int)actual_reset_reason,
                (unsigned int)expected_reset_reason);

            unexpected_reset = true;
            // This is needed to prevent UnityAbort(), which is called from
            // UnityFail(), from executing longjmp().
            m_aborted = true;

            Unity = *(m_test.p_unity);
            Unity.CurrentTestName = m_test_cases[(*(m_test.p_current_case))].name;
            Unity.TestFile = __FILE__;
            UnityFail("unexpected_reset", __LINE__);
            UnityConcludeTest();
        }
    }

    uint32_t current_case = (*(m_test.p_current_case));
    if (!unexpected_reset && (current_case < m_test.case_count))
    {
        RUN_TEST(m_test_cases[current_case], 0);
        m_test_case_finished = true;
    }

    app_test_runner_finalize();
}


#elif TEST_MODE == MANUAL_TEST_MODE

static void app_test_runner_finalize(void)
{
    app_test_runner_summary();
}

static void app_test_runner_manual(void)
{
    uint32_t index;

    app_test_runner_init();
    Unity.TestFile = TEST_NAME;

    uart_init();

    APP_TEST_RUNNER_LOG("CASE COUNT: %u\r\n", (unsigned int)m_test.case_count);

    while (1)
    {
        scanf("%u", (unsigned int *)&index);
        APP_TEST_RUNNER_LOG("%u\r\n", (unsigned int)index);

        if (index < m_test.case_count)
        {
            break;
        }
        APP_TEST_RUNNER_LOG("INDEX OUT OF RANGE\r\n");
    }

    uart_deinit();

    RUN_TEST(m_test_cases[index], 0);

    app_test_runner_summary(false);
}


#endif

// Redefinition for unity weak function called to abort the test
void UnityAbort(void)
{
    // Prevent nested calling of this function, for instance from tearDown().
    if (m_aborted)
    {
        return;
    }
    m_aborted = true;

    if (m_test_case_finished)
    {
        UnityPrint("WARNING: TEST_ABORT called for a finished test case.");
        UNITY_OUTPUT_CHAR('\r'); UNITY_OUTPUT_CHAR('\n');
        app_test_runner_flush();

        // This is can happen when a test case is finished successfully,
        // but then, during app_test_runner_finalize(), an assertion fails
        // in some interrupt handler that this test case hasn't entirely
        // deactivated. Most likely this indicates that the test case should
        // clean up better before exiting, but it might reveal some hidden
        // problem as well.

        // This failure indication was (most likely) spurious, return to
        // normal testing routine.
        Unity.CurrentTestFailed = false;
        return;
    }

    uint32_t isr_vector_num = (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk);
    if (isr_vector_num > 0)
    {
        tearDown();
        UnityConcludeTest();
        /* Aborting test from the exception level */
        app_test_runner_finalize();
        while (1)
        {
            // This would be used in the case of manual test - loop until the reset
        }
    }
    else
    {
        /* Aborting test from the thread level */
        longjmp(Unity.AbortFrame, 1);
    }
}

#ifdef FREERTOS

void testTask(void *pvParameter)
{
    UNUSED_PARAMETER(pvParameter);

#else /* !FREERTOS */

int main(void)
{

#endif /* FREERTOS */

#if TEST_MODE == AUTOMATIC_TEST_MODE
    (void)NRF_LOG_INIT(NULL);
    app_test_runner_automatic();
#elif TEST_MODE == MANUAL_TEST_MODE
    app_test_runner_manual();
#endif

    while (1)
    {

    }
}

#ifdef FREERTOS

int main(void)
{
    TaskHandle_t testTaskHandle;
    ret_code_t err_code;
    /* Clock startup */
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    
    // Create task
    UNUSED_VARIABLE(xTaskCreate( testTask, "TST", configMINIMAL_STACK_SIZE + 256, NULL, 1, &testTaskHandle));
    // Start FreeRTOS scheduler.
    vTaskStartScheduler();
    // Should never be here
    while (1)
    {
        // I am dead now and I have nothing to do
    }
}

#endif
