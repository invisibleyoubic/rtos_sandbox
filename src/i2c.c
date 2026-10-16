#include "stm32f411xe.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_i2c.h"
#include <stdint.h>

#include "i2c.h"

uint8_t i2c_init(void) {
    LL_I2C_InitTypeDef i2c_struct;
    LL_I2C_StructInit(&i2c_struct);
    return (uint8_t)LL_I2C_Init(I2C1, &i2c_struct);
}

uint8_t i2c_turn_on(void) {
    LL_I2C_GenerateStartCondition(I2C1);
    while (!LL_I2C_IsActiveFlag_SB(I2C1)) {}

    // target address
    LL_I2C_TransmitData8(I2C1, 0x78);
    while (!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}
    (void)READ_REG(I2C1->SR2);

    uint8_t commands[] = {0x00, 0x8D, 0x14, 0xAF, 0x20, 0x00, 0x21, 0x00, 127, 0x22, 0x00, 7, 0xA8, 0x3F};
    for (uint8_t i = 0; i < sizeof(commands); ++i) {
        while (!LL_I2C_IsActiveFlag_TXE(I2C1)) {}
        LL_I2C_TransmitData8(I2C1, commands[i]);
    }
    while (!LL_I2C_IsActiveFlag_TXE(I2C1) || !LL_I2C_IsActiveFlag_BTF(I2C1)) {}

    LL_I2C_GenerateStopCondition(I2C1);
    while (LL_I2C_IsActiveFlag_BUSY(I2C1)) {}

    return 0;
}

uint8_t i2c_send(uint8_t *buffer) {
    LL_I2C_GenerateStartCondition(I2C1);
    while (!LL_I2C_IsActiveFlag_SB(I2C1)) {}

    // target address
    LL_I2C_TransmitData8(I2C1, 0x78);
    while (!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}
    (void)READ_REG(I2C1->SR2);

    while (!LL_I2C_IsActiveFlag_TXE(I2C1)) {}
    LL_I2C_TransmitData8(I2C1, 0x40);

    for (uint16_t i = 0; i < 1024; ++i) {
        while (!LL_I2C_IsActiveFlag_TXE(I2C1)) {}
        LL_I2C_TransmitData8(I2C1, buffer[i]);
    }
    while (!LL_I2C_IsActiveFlag_TXE(I2C1) || !LL_I2C_IsActiveFlag_BTF(I2C1)) {}

    LL_I2C_GenerateStopCondition(I2C1);
    while (LL_I2C_IsActiveFlag_BUSY(I2C1)) {}

    return 0;
}
