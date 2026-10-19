#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include <stdint.h>

#include "setup.h"

uint8_t setup_gpio_a(void) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    LL_GPIO_InitTypeDef gpio_a_init_struct;
    uint8_t rc = 0;

    // A9
    gpio_a_init_struct.Pin = LL_GPIO_PIN_9;
    gpio_a_init_struct.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_a_init_struct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_a_init_struct.Alternate = LL_GPIO_AF_7;    // tx
    gpio_a_init_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_a_init_struct.Pull = LL_GPIO_PULL_UP;

    rc = (uint8_t)LL_GPIO_Init(GPIOA, &gpio_a_init_struct);
    if (0 != rc)
        return rc;

    // A10
    gpio_a_init_struct.Pin = LL_GPIO_PIN_10;
    gpio_a_init_struct.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_a_init_struct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_a_init_struct.Alternate = LL_GPIO_AF_7;    // rx
    gpio_a_init_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_a_init_struct.Pull = LL_GPIO_PULL_UP;

    rc = (uint8_t)LL_GPIO_Init(GPIOA, &gpio_a_init_struct);
    if (0 != rc)
        return rc;

    return rc;
}

uint8_t setup_gpio_b(void) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

    LL_GPIO_InitTypeDef gpio_b_init_struct;
    uint8_t rc = 0;

    // B6
    gpio_b_init_struct.Pin = LL_GPIO_PIN_6;
    gpio_b_init_struct.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_b_init_struct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_b_init_struct.Alternate = LL_GPIO_AF_4;
    gpio_b_init_struct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    gpio_b_init_struct.Pull = LL_GPIO_PULL_NO;

    rc = (uint8_t)LL_GPIO_Init(GPIOB, &gpio_b_init_struct);
    if (0 != rc)
        return rc;

    // B7
    gpio_b_init_struct.Pin = LL_GPIO_PIN_7;
    gpio_b_init_struct.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_b_init_struct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_b_init_struct.Alternate = LL_GPIO_AF_4;
    gpio_b_init_struct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    gpio_b_init_struct.Pull = LL_GPIO_PULL_NO;

    rc = (uint8_t)LL_GPIO_Init(GPIOB, &gpio_b_init_struct);
    if (0 != rc)
        return rc;

    return rc;
}

uint8_t setup_gpio_c(void) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    
    LL_GPIO_InitTypeDef gpio_c_init_struct;
    uint8_t rc = 0;
    
    // C13
    gpio_c_init_struct.Pin = LL_GPIO_PIN_13;
    gpio_c_init_struct.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_c_init_struct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_c_init_struct.Alternate = LL_GPIO_AF_0;
    gpio_c_init_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_c_init_struct.Pull = LL_GPIO_PULL_NO;

    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
    rc = (uint8_t)LL_GPIO_Init(GPIOC, &gpio_c_init_struct);
    if (rc != 0)
        return rc;

    return rc;
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
    while (LL_RCC_SYS_CLKSOURCE_STATUS_HSI != LL_RCC_GetSysClkSource()) {}

    LL_RCC_PLL_Disable();
    while (0u != LL_RCC_PLL_IsReady()) {}

    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

    // 96 MHz
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 192, LL_RCC_PLLP_DIV_2);
    // 48 MHz
    LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 192, LL_RCC_PLLQ_DIV_4);

    LL_RCC_PLL_Enable();
    while (0u == LL_RCC_PLL_IsReady()) {}

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_SYS_CLKSOURCE_STATUS_PLL != LL_RCC_GetSysClkSource()) {}

    // I2C
    LL_RCC_PLLI2S_Enable();
    while (0u == LL_RCC_PLLI2S_IsReady()) {}

    return 0;
}
