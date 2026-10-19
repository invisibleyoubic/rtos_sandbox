#include "stm32f4xx.h"
#include "stm32f4xx_ll_usart.h"
#include <stdint.h>

#include "uart.h"

uint8_t uart_init(void) {
    LL_USART_InitTypeDef usart_struct;
    LL_USART_StructInit(&usart_struct);
    usart_struct.BaudRate = 115200U;
    if (0u != LL_USART_Init(USART1, &usart_struct))
        return 1;
    LL_USART_Enable(USART1);
    return 0;
}

uint8_t uart_send(uint8_t *buffer, const uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        while (!LL_USART_IsActiveFlag_TXE(USART1)) {}
        LL_USART_TransmitData8(USART1, buffer[i]);
    }
    if (size > 0)
        while (!LL_USART_IsActiveFlag_TC(USART1)) {}
    return 0;
}
