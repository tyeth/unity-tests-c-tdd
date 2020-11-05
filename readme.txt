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
 
This is an example to showcase how to run unit test using unity test framework on nrf5x chip.
Test suite project consists of:
- test_cases.c file which contains test cases (implementation and array used by unit test framework)
- unit test framework in folder unity_fw. It contains modified unity framework (http://www.throwtheswitch.org/unity/), framework for executing unit tests on target (app_test_runner.c and simple_uart.c). 
- makefiles for pca10040 and pca10056 boards

The unit test framework ideas:
- app_test_runner.c includes "test_cases.c" which holds the table with test to execute
- each test is separated by the reset.
- if framework detects pin reset as the reset reason it resets the counter and start executing first test.
- whenever printf is called in the test string is buffered in ram
- once test is completed buffered string is flushed (partial unit test report) and sw reset occurs.
- last test case flushes last test report and summary

Running:

- This example is based on nRF5 SDK 13.0.0 and should be copied to examples/peripheral folder.
- Go to armgcc folder (for example test_example\pca10040\blank\armgcc)
- call 'make flash' and flash the output to connected board
- open uart console (e.g. PuTTY)
- call 'nrfjproj -p' to trigger pin reset