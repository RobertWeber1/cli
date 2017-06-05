cmake_minimum_required (VERSION 2.6)
project (CommandLineInterfce)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_PATCH 0)
set (SHORT_NAME "CLI")

configure_file (
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)

include_directories(
    "${PROJECT_BINARY_DIR}"
    "./include/"
    "src/"
)


add_library(cli
	#src/util.cc
	#src/line.cc
	#src/data.cc
	#src/window.cc
	#src/layoutobject.cc
	src/util/properties.cc
	src/util/point.cc
	src/util/size.cc
	src/util/size_constraint.cc
	src/util/size_hint.cc
	src/border/element.cc
	src/border/buffer.cc
	src/layout/layout.cc
	src/layout/layout_object.cc
	src/layout/vertical_layout.cc
	src/layout/horizontal_layout.cc
)


add_executable( runUnitTests_${SHORT_NAME}
	tests/testUtils.cc
	tests/unitTest_border.cc
	tests/unitTest_layout.cc
	#tests/unitTestLine.cc
	#tests/unitTestData.cc
	#tests/unitTestWindow.cc
	tests/unitTests.cc
)


target_link_libraries( runUnitTests_${SHORT_NAME}
	cli
)

enable_testing()

add_test( unit_tests_${SHORT_NAME} runUnitTests_${SHORT_NAME} 0 )
