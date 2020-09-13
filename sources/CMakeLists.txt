# Set local variables
set(localVar
  ${${PROJECT_NAME}_SOURCES}
  )

# Add specific source to the list
list(APPEND localVar
  ${CMAKE_CURRENT_SOURCE_DIR}/startup.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/serial_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/serial_parser_states.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/simple_protocol_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/isr_vectors.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/console_cmd_table.cpp
  )

# Update the project lists
set(${PROJECT_NAME}_SOURCES ${localVar} CACHE INTERNAL "")

