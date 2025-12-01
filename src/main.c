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
#include <pico/sync.h>


#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void ms_blink(__unused void* params)
{
    int toggle = 0;
    for(;;)
    {
        toggle = !toggle;
        gpio_put(LED_PIN, toggle);
        sleep_ms(333);
    }
}

void blink_task(__unused void* params)
{
    int toggle = 0;
    for(;;)
    {
        toggle = !toggle;
        gpio_put(LED_PIN, toggle);
        vTaskDelay(pdMS_TO_TICKS(333));
    }
}

void busy_task(__unused void *params)
{
    while(1) {
        uint32_t k;
        for (int i = 0; i < 30; i++)
        {
            uint32_t j = 0;
            j = ((~j >> i) + 1) * 27644437;
            k = j;
        }
    }
}

static void ext_sig_callback(unsigned int _a, long unsigned int _b)
{
    static volatile int led_state = 0;
    gpio_put(LED_PIN, led_state);
    led_state = !led_state;

}

int main( void )
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    gpio_init(EXT_SIG_PIN);
    gpio_set_dir(EXT_SIG_PIN, GPIO_IN);

    //TaskHandle_t runner_task_handle;
    //xTaskCreate(busy_task, "RunnerThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &runner_task_handle);
    //vTaskStartScheduler();
    
    //busy_task(NULL);

    //ms_blink(NULL);
    
    gpio_put(LED_PIN, 1);
    gpio_set_irq_enabled_with_callback(EXT_SIG_PIN, GPIO_IRQ_EDGE_RISE, true, &ext_sig_callback);
    while(1);
    return 0;
}
