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

int main( void )
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    gpio_init(EXT_SIG_PIN);
    gpio_set_dir(EXT_SIG_PIN, GPIO_IN);
    

    ms_blink(NULL);
    
    while(1);
    return 0;
}