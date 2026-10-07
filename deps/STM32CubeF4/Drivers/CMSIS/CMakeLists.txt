add_library(stm32_cmsis INTERFACE)

target_include_directories(stm32_cmsis INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/ST/STM32F4xx/Include
)

target_compile_definitions(stm32_cmsis INTERFACE
    STM32F411xE
)
