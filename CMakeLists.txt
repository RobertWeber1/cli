cmake_minimum_required (VERSION 2.6)
project (CommandLineInterfce)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_PATCH 0)
set (SHORT_NAME "CLI")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


add_executable( ${SHORT_NAME}.V${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    tests/test.cc
)
