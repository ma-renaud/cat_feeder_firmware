# Set local variables
set(localVar
  ${STM32_INC_DIRECTORIES}
  )

# Add specific directories to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

# Update the project lists
set(STM32_INC_DIRECTORIES ${localVar} CACHE INTERNAL "")

