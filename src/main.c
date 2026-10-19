#include <stdint.h>
#include <string.h>

#include "stm32f411xe.h"

#include "FreeRTOS.h"
#include "task.h"

#include "setup.h"
#include "i2c.h"
#include "uart.h"

uint8_t ucHeap[configTOTAL_HEAP_SIZE];
uint8_t display[1024];
char log_buffer[32] = "255 | some string 1234567890\n\r";

void blink(void *params);
void on_off(void *params);
void logger(void *params);
void error(void);

int main(void) {
    setup_clock();
    setup_flash_latency();
    setup_rcc();
    setup_gpio_a();
    setup_gpio_b();
    setup_gpio_c();
    
    if (0u != i2c_init())
        error();
    i2c_turn_on();

    if (0u != uart_init())
        error();

    xTaskCreate(blink, "blink", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(on_off, "on_off", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(logger, "log", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    for (;;);
}

void error(void) {
    for (;;) {
        LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
        for (uint32_t i = 0; i < 2000000; ++i) {
            asm volatile ("" ::: "memory");
        }
    }
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

void logger(void *params) {
    (void)params;
    uint8_t counter = 1;
    for (;;) {
        uint8_t h = (counter / 100) % 10;
        uint8_t t = (counter / 10)  % 10;
        uint8_t o =  counter        % 10;
        log_buffer[0] = h + '0';
        log_buffer[1] = t + '0';
        log_buffer[2] = o + '0';

        uart_send((uint8_t *)log_buffer, sizeof(log_buffer));
        vTaskDelay(pdMS_TO_TICKS(2000));
        counter++;
        if (counter == UINT8_MAX)
            counter = 1;
    }
}
