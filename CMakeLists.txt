cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(rtos_sandbox
    LANGUAGES CXX C ASM
)

add_subdirectory(deps)

add_executable(${PROJECT_NAME}
    src/main.c
    src/system_stm32f4xx.c
    startup/startup_stm32f411xe.s
)

target_include_directories(${PROJECT_NAME} PRIVATE
    include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    stm32_cmsis
    stm32_ll
    free_rtos
)

target_link_options(${PROJECT_NAME} PRIVATE
    -T${CMAKE_SOURCE_DIR}/linker/STM32F411CEUX_FLASH.ld

    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard

    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard

    -ffunction-sections
    -fdata-sections

    -Wall
    -Wextra
    -Wpedantic
    -Werror

    -Wshadow
    -Wconversion
    -Wsign-conversion
    -Wcast-align
    -Wcast-qual
    -Wpointer-arith
    -Wstrict-prototypes
    -Wmissing-prototypes
    -Wmissing-declarations
    -Wredundant-decls
    -Wundef
    -Wformat=2
    -Wformat-security
    -Wswitch-enum
    -Wdouble-promotion

    -ffunction-sections
    -fdata-sections
    -fno-common
    
    -Wl,--gc-sections
)
