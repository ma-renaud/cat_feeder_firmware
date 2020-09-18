include(CPM)
CPMAddPackage(
  NAME console-cpp
  GIT_REPOSITORY https://gitlab.com/christian-dsa/console.git
  GIT_TAG develop
  DOWNLOAD_ONLY True
  UPDATE_DISCONNECTED ON
)

list(APPEND ${PROJECT_NAME}_INC_DIRECTORIES
  ${console-cpp_SOURCE_DIR}/src
)

list(APPEND ${PROJECT_NAME}_SOURCES
  ${console-cpp_SOURCE_DIR}/src/command_parser.cpp
  ${console-cpp_SOURCE_DIR}/src/command_table.cpp
  ${console-cpp_SOURCE_DIR}/src/console.cpp
)