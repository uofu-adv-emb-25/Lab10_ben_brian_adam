/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

const uint led_pin = 34;

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE


void ms_blink(__unused void* params)
{
    bool on = true;
    for(;;)
    {
        on = !on;
        cyw43_arch_gpio_put(led_pin, on);
        sleep_ms(333);
    }
}

void runner_task(__unused void* params)
{
    TaskHandle_t ms_blink_task;
    xTaskCreate(ms_blink, "msBlinkTask", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &ms_blink_task);
    
}

int main( void )
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    cyw43_arch_gpio_put(led_pin, true);
    TaskHandle_t runner_task_handle;
    xTaskCreate(runner_task, "RunnerThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &runner_task_handle);
    vTaskStartScheduler();
    return 0;
}
