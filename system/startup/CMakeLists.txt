# Set local variables
set(localVar
  ${STM32_SOURCES}
  )

# Add specific source to the list
list(APPEND localVar
  #${CMAKE_CURRENT_SOURCE_DIR}/startup_stm32f030x8.s
  )

# Update the project lists
set(STM32_SOURCES ${localVar} CACHE INTERNAL "")

