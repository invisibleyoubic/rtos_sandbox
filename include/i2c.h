#ifndef SANDBOX_I2C_H
#define SANDBOX_I2C_H

#include <stdint.h>

uint8_t i2c_init(void);
uint8_t i2c_turn_on(void);
uint8_t i2c_send(uint8_t *buffer);

#endif /* SANDBOX_I2C_H */
