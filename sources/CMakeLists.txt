# Set local variables
set(localVar
  ${${PROJECT_NAME}_SOURCES}
  )

# Add specific source to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}/f0GpioMemory.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/serialParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/serialParserStates.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simpleProtocolParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_hal_msp.c
  ${CMAKE_CURRENT_SOURCE_DIR}/stm32f0xx_it.c
  ${CMAKE_CURRENT_SOURCE_DIR}/rcc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0UartMemory.cpp
  )

# Update the project lists
set(${PROJECT_NAME}_SOURCES ${localVar} CACHE INTERNAL "")

