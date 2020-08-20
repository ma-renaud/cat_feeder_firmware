# Set local variables
set(localVar
  ${STM32_SOURCES}
  )

# Add specific source to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_pwr.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_i2c_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_rcc_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_uart_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_uart.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_i2c.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_tim_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_dma.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_rcc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_tim.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_pwr_ex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_cortex.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_flash.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_gpio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_flash_ex.c
  )

# Update the project lists
set(STM32_SOURCES ${localVar} CACHE INTERNAL "")

