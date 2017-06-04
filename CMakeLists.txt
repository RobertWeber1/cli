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
# so that we will find version.h
include_directories(
    "${PROJECT_BINARY_DIR}"
    "./include/"
    "src/"
)


#add_executable( ${SHORT_NAME}.V${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
#    src/commands.cc
#    tests/test.cc
#)


# add_executable( winTest
# 	src/layoutobject.cc
# 	#src/layout.cc
#     src/cliwindow.cc
#     src/line.cc
#     tests/cliwindowTest.cc
# )

# add_executable( constraintTest
# 	src/layoutobject.cc
# 	tests/constraintTest.cc
# )

# target_link_libraries( constraintTest
# 	cli
# )


# add_executable( layoutTest
# 	src/cliwindow.cc
# 	src/util.cc
# 	src/line.cc
# 	src/layoutobject.cc
# 	src/layout.cc
# 	src/hlayout.cc
# 	src/vlayout.cc
# 	src/border.cc
# 	tests/layoutTest.cc
# )

# add_executable( terminalTest
# 	tests/terminalTest.cc
# 	src/border.cc
# )


# add_executable( inputTest
# 	tests/inputTest.cc
# 	src/inputmultiplexer.cc
# )


# add_executable( viewTest
# 	tests/viewTest.cc
# 	src/util.cc
# 	src/view.cc
# 	src/layoutobject.cc
# 	src/layout.cc
# 	src/hlayout.cc
# 	src/vlayout.cc
# 	src/cliwindow.cc
# 	src/border.cc
# 	src/line.cc
# )


add_library(cli
	src/util.cc
	src/line.cc
	src/data.cc
	src/window.cc
	src/layoutobject.cc
	src/border/element.cc
	src/border/buffer.cc
)


add_executable( runUnitTests_${SHORT_NAME}
	tests/testUtils.cc
	tests/unitTest_border.cc
	tests/unitTestLine.cc
	tests/unitTestData.cc
	tests/unitTestWindow.cc
	tests/unitTests.cc
)

target_link_libraries( runUnitTests_${SHORT_NAME}
	cli
)




# enable_testing()

# add_test( lineTest lineTest 0)
