# Set local variables
set(localSources
  ${${PROJECT_NAME}_SOURCES}
  )
#---------------

# Add specific source to the list
list(APPEND localSources
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/f0_gpio_memory_test.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/f0_gpio_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simple_protocol_parser_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simple_protocol_parser_logic_test.cpp
  )
#---------------

# Update the project lists
set(${PROJECT_NAME}_SOURCES ${localSources} CACHE INTERNAL "")
#---------------