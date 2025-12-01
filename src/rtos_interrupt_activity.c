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

int main( void )
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    gpio_init(EXT_SIG_PIN);
    gpio_set_dir(EXT_SIG_PIN, GPIO_IN);

    TaskHandle_t runner_task_handle;
    xTaskCreate(blink_task, "RunnerThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &runner_task_handle);
    vTaskStartScheduler();
    
    //busy_task(NULL);

    //ms_blink(NULL);
    
    //gpio_put(LED_PIN, 1);
    //gpio_set_irq_enabled_with_callback(EXT_SIG_PIN, GPIO_IRQ_EDGE_RISE, true, &ext_sig_callback);
    while(1);
    return 0;
}