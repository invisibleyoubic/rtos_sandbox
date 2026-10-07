add_library(stm32_ll STATIC
    # Src/stm32f4xx_ll_adc.c
    # Src/stm32f4xx_ll_crc.c
    # Src/stm32f4xx_ll_dac.c
    # Src/stm32f4xx_ll_dma.c
    # Src/stm32f4xx_ll_dma2d.c
    # Src/stm32f4xx_ll_exti.c
    # Src/stm32f4xx_ll_fmpi2c.c
    Src/stm32f4xx_ll_gpio.c
    # Src/stm32f4xx_ll_i2c.c
    # Src/stm32f4xx_ll_lptim.c
    # Src/stm32f4xx_ll_pwr.c
    Src/stm32f4xx_ll_rcc.c
    # Src/stm32f4xx_ll_rng.c
    # Src/stm32f4xx_ll_rtc.c
    # Src/stm32f4xx_ll_spi.c
    # Src/stm32f4xx_ll_tim.c
    # Src/stm32f4xx_ll_usart.c
    Src/stm32f4xx_ll_utils.c
)

target_include_directories(stm32_ll PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

target_link_libraries(stm32_ll PUBLIC
    stm32_cmsis
)

target_compile_options(stm32_ll PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)