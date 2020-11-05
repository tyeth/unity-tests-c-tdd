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
#include "simple_uart.h"
#include "nrf_drv_uart.h"
#include "app_util_platform.h"
#include <stdint.h>

nrf_drv_uart_t uart_driver = NRF_DRV_UART_INSTANCE(0);

uint8_t simple_uart_get(void)
{
    uint8_t data;
    (void)nrf_drv_uart_rx(&uart_driver, &data,1);
    return data;
}

void simple_uart_put(uint8_t cr)
{
    (void)nrf_drv_uart_tx(&uart_driver, &cr,1);
}

void simple_uart_config(uint8_t rts_pin_number,
                        uint8_t txd_pin_number,
                        uint8_t cts_pin_number,
                        uint8_t rxd_pin_number,
                        bool    hwfc)
{
    nrf_drv_uart_config_t config = NRF_DRV_UART_DEFAULT_CONFIG;
    config.hwfc = hwfc ? NRF_UART_HWFC_ENABLED : NRF_UART_HWFC_DISABLED;
    config.pselcts = cts_pin_number;
    config.pselrts = rts_pin_number;
    config.pselrxd = rxd_pin_number;
    config.pseltxd = txd_pin_number;
    config.baudrate = NRF_UART_BAUDRATE_115200;
    nrf_drv_uart_uninit(&uart_driver);
    (void)nrf_drv_uart_init(&uart_driver, &config, NULL);
}
