#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include <stdint.h>

#include "setup.h"

uint8_t setup_gpio_c(void) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    LL_GPIO_InitTypeDef gpio_c_init_struct = {
        .Pin = LL_GPIO_PIN_13,
        .Mode = LL_GPIO_MODE_OUTPUT,
        .Speed = LL_GPIO_SPEED_FREQ_LOW,
        .Alternate = LL_GPIO_AF_0,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull = LL_GPIO_PULL_NO
    };
    return (uint8_t)LL_GPIO_Init(GPIOC, &gpio_c_init_struct);
}

uint8_t setup_rcc(void) {
    return 0;
}

uint8_t setup_flash_latency(void) {

    return 0;
}

uint8_t setup_clock(void) {
    LL_RCC_HSI_Enable();
    while (0u == LL_RCC_HSI_IsReady()) {}

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
    while (LL_RCC_SYS_CLKSOURCE_HSI != LL_RCC_GetSysClkSource()) {}

    LL_RCC_PLL_Disable();
    while (0u != LL_RCC_PLL_IsReady()) {}

    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    // 96 MHz
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 192, LL_RCC_PLLP_DIV_2);
    // 48 MHz
    LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 192, LL_RCC_PLLQ_DIV_4);

    LL_RCC_PLL_Enable();
    while (0u == LL_RCC_PLL_IsReady()) {}

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_SYS_CLKSOURCE_PLL != LL_RCC_GetSysClkSource()) {}

    return 0;
}
