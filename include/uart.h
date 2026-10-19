#ifndef SANDBOX_UART_H
#define SANDBOX_UART_H

#include <stdint.h>

uint8_t uart_init(void);
uint8_t uart_send(uint8_t *buffer, const uint32_t size);

#endif /* SANDBOX_UART_H */
