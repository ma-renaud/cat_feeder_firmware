# Set local variables
set(localVar
  ${${PROJECT_NAME}_INC_DIRECTORIES}
  )

# Add specific directories to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

# Update the project lists
set(${PROJECT_NAME}_INC_DIRECTORIES ${localVar} CACHE INTERNAL "")
