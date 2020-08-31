# Set local variables
set(localVar
  ${${PROJECT_NAME}_SOURCES}
  )

# Add specific source to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/serial_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/serial_parser_states.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simple_protocol_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_msp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_it.c
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_gpio_memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_uart_memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_rcc_memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_rcc.cpp
  )

# Update the project lists
set(${PROJECT_NAME}_SOURCES ${localVar} CACHE INTERNAL "")

