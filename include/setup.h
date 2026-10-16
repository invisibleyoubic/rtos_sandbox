#ifndef SANDBOX_SETUP_H
#define SANDBOX_SETUP_H

#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_gpio.h"
#include <stdint.h>

uint8_t setup_gpio_b(void);
uint8_t setup_gpio_c(void);
uint8_t setup_rcc(void);
uint8_t setup_flash_latency(void);
uint8_t setup_clock(void);

#endif /* SANDBOX_SETUP_H */
