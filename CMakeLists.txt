cmake_minimum_required (VERSION 3.11)

#Enable the foldeer cmake as cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#enable the compile database generation for clang-tidy and other clang tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "export the build rules into a JSON files for clang-tidy" FORCE)

#enable the toolcahin file if not in unit test mode
if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "UTest")
  #Use a specific compiler version here
  set(COMPILER_VERSION_REQUIRED "9.2.1" CACHE STRING "Use the fixed compiler version" FORCE)
  if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi-gcc.cmake" CACHE UNINITIALIZED "toolchain file")
  endif()
endif()

# Set the project name
project(cat_feeder VERSION 0.0.1 LANGUAGES CXX C ASM)

include(CPM)
CPMAddPackage(
  NAME console
  GIT_REPOSITORY https://gitlab.com/christian-dsa/console.git
  GIT_TAG develop
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/console
  DOWNLOAD_ONLY True
  UPDATE_DISCONNECTED ON
)

#Set Version
message(STATUS "Compiling Version: ${${PROJECT_NAME}_VERSION} of project ${PROJECT_NAME}")

set(${PROJECT_NAME}_SOURCES "" CACHE INTERNAL "list of all sources to include in project" FORCE)
set(${PROJECT_NAME}_INC_DIRECTORIES "" CACHE INTERNAL "list of all directorys to include in project" FORCE)
set(${STM32_SOURCES} "" CACHE INTERNAL "list of all sources to include in project" FORCE)
set(${STM32_INC_DIRECTORIES} "" CACHE INTERNAL "list of all directorys to include in project" FORCE)

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "UTest")
  #Disable all internal unit testing for all known libraries
  set(BUILD_TESTS OFF CACHE INTERNAL "" FORCE)

  add_definitions("-DSTM32F030x8")

  include(STM32F0)
  string(REPLACE " " ";" STM_COMMON_COMPILE_FLAGS ${STM_COMMON_COMPILE_FLAGS})
  set(PROJECT_COMMON_COMPILE_FLAGS "${STM_COMMON_COMPILE_FLAGS}" CACHE STRING "" FORCE)

  #Add the compiler flag that are GLOBAL for all the libraries for Debug and Release
  string(APPEND CMAKE_CXX_FLAGS "-fno-use-cxa-atexit -fno-exceptions	-fno-rtti -g")
  string(APPEND CMAKE_C_FLAGS "-g ")
  string(APPEND CMAKE_CXX_FLAGS_DEBUG " -O0")
  string(APPEND CMAKE_C_FLAGS_DEBUG " -O0")
  string(APPEND CMAKE_CXX_FLAGS_RELEASE " -Os")
  string(APPEND CMAKE_C_FLAGS_RELEASE " -Os")

else()
  #Add the compiler flag that are GLOBAL for all the libraries for UTest
  string(APPEND CMAKE_CXX_FLAGS_UTEST "-DDEBUG-O0")
  string(APPEND CMAKE_C_FLAGS_UTEST "-DDEBUG-O0")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "UTest")
  set(CMAKE_BUILD_TYPE Debug)
  add_subdirectory(includes)
  enable_testing()
  add_subdirectory(test)
else()
  add_subdirectory(system)
  add_subdirectory(drivers)
  add_subdirectory(includes)
  add_subdirectory(sources)
  include(console)

  add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${STM32_SOURCES}
    )

  target_compile_options(${PROJECT_NAME} PUBLIC
    ${PROJECT_COMMON_COMPILE_FLAGS}
    )

  target_include_directories(${PROJECT_NAME}
    PRIVATE ${${PROJECT_NAME}_INC_DIRECTORIES}
    PRIVATE ${STM32_INC_DIRECTORIES}
    )

  target_link_libraries(${PROJECT_NAME}
    ${PROJECT_COMMON_COMPILE_FLAGS}
    -L"${CMAKE_SOURCE_DIR}/ldscripts"
    -T"STM32F030R8Tx_FLASH.ld"
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--print-memory-usage
    )
  #add target only compile flags.
  #set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS )

  #set the standards use by this target.
  target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
  target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)
  set_target_properties( ${PROJECT_NAME} PROPERTIES SUFFIX ".elf" )

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf  ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_NM_UTIL} -C -r --size-sort -S   ${PROJECT_NAME}.elf > ${PROJECT_NAME}.nm
    )
endif()