include(CPM)
CPMAddPackage(
  NAME console-cpp
  GIT_REPOSITORY https://gitlab.com/christian-dsa/console.git
  GIT_TAG develop
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/console
  DOWNLOAD_ONLY True
  UPDATE_DISCONNECTED ON
)

list(APPEND ${PROJECT_NAME}_INC_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/console/src
)

list(APPEND ${PROJECT_NAME}_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/console/src/command_parser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/console/src/command_table.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/console/src/console.cpp
)