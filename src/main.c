#include <stdint.h>

#include "stm32f411xe.h"

#include "FreeRTOS.h"
#include "task.h"

#include "setup.h"

uint8_t ucHeap[configTOTAL_HEAP_SIZE];

void blink(void *params);

int main(void) {
    setup_clock();
    setup_flash_latency();
    setup_rcc();
    setup_gpio_c();

    xTaskCreate(blink, "blink", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    for (;;);
}

void blink(void *params) {
    (void)params;
    for (;;) {
        LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
