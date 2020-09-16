# Set local variables
set(localVar
  ${${PROJECT_NAME}_SOURCES}
  )

# Add specific source to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_gpio_memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_uart_memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_rcc_memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_basic_timer_memory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_rcc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_uart.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_basic_timer.cpp
  )

# Update the project lists
set(${PROJECT_NAME}_SOURCES ${localVar} CACHE INTERNAL "")

