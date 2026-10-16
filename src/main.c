#include <stdint.h>
#include <string.h>

#include "stm32f411xe.h"

#include "FreeRTOS.h"
#include "task.h"

#include "setup.h"
#include "i2c.h"

uint8_t ucHeap[configTOTAL_HEAP_SIZE];
uint8_t display[1024];

void blink(void *params);
void on_off(void *params);

int main(void) {
    setup_clock();
    setup_flash_latency();
    setup_rcc();
    setup_gpio_b();
    setup_gpio_c();
    
    i2c_init();
    i2c_turn_on();

    xTaskCreate(blink, "blink", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(on_off, "on_off", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

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

void on_off(void *params) {
    (void)params;
    uint8_t isZero = 1;
    for (;;) {
        if (isZero) {
            memset(display, 0x00, 1024);
        }
        else {
            memset(display, 0xFF, 1024);
        }
        i2c_send(display);
        vTaskDelay(pdMS_TO_TICKS(3000));
        isZero = !isZero;
    }
}
