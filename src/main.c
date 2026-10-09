#include "setup.h"

int main(void) {
    setup_flash_latency();
    setup_clock();
    setup_rcc();
    setup_gpio_c();

    while (1) {
        LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
        for (uint32_t i = 0; i < 1000000; ++i) {
            asm volatile ("" ::: "memory");
        }
    }
}
