add_library(free_rtos STATIC
    src/tasks.c
    src/queue.c
    src/list.c

    portable/GCC/ARM_CM4F/port.c
    portable/MemMang/heap_4.c
)

target_include_directories(free_rtos PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/GCC/ARM_CM4F

# FreeRTOSConfig.h
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(free_rtos PUBLIC
    stm32_cmsis
)

target_compile_options(free_rtos PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)