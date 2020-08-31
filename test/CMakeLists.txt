cmake_minimum_required(VERSION 3.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

get_filename_component(TESTED_CMAKE_CURRENT_SOURCE_DIR "../" REALPATH)
set(TESTED_INC_DIRECTORYS ${${PROJECT_NAME}_INC_DIRECTORIES})

project(${PROJECT_NAME}_tests C CXX)

include(CPM)
CPMAddPackage(
  NAME Catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 2.13.0
  OPTIONS
  "BUILD_TESTING OFF"
  "CATCH_BUILD_EXAMPLES OFF"
  "CATCH_ENABLE_COVERAGE OFF"
)

add_subdirectory(sources)
add_subdirectory(includes)

# Add selected sources from tested project
list(APPEND TESTED_SOURCES
  ${TESTED_CMAKE_CURRENT_SOURCE_DIR}/sources/simple_protocol_parser.cpp
  ${TESTED_CMAKE_CURRENT_SOURCE_DIR}/sources/serial_parser.cpp
  ${TESTED_CMAKE_CURRENT_SOURCE_DIR}/sources/serial_parser_states.cpp
  ${TESTED_CMAKE_CURRENT_SOURCE_DIR}/sources/f0_gpio_memory.cpp
  ${TESTED_CMAKE_CURRENT_SOURCE_DIR}/sources/f0_rcc_memory.cpp
  )

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${TESTED_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_INC_DIRECTORYS} ${TESTED_INC_DIRECTORYS})

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PUBLIC -Wunused-parameter -Wextra -Wall)

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
  target_compile_options(${PROJECT_NAME} PUBLIC -O0)
else ()
  target_compile_options(${PROJECT_NAME} PUBLIC -O3)
endif ()

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})