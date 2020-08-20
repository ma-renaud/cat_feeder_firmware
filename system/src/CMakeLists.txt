# Set local variables
set(localVar
  ${STM32_SOURCES}
  )

# Add specific source to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}/system_stm32f0xx.c
  )

# Update the project lists
set(STM32_SOURCES ${localVar} CACHE INTERNAL "")

add_subdirectory(stm32f0xx_hal_driver)
