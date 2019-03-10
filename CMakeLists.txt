cmake_minimum_required (VERSION 2.6)
project (libcli CXX)

################################################################################
# Version-file #
################

set(${PROJECT_NAME}_VERSION_SRC "${CMAKE_CURRENT_BINARY_DIR}/version.cc")
set(${PROJECT_NAME}_NAMESPACE "cli")

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/version.cc
	OUTPUT __version_${PROJECT_NAME}
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tool/version_writer.sh ${CMAKE_CURRENT_SOURCE_DIR} ${${PROJECT_NAME}_NAMESPACE} ${PROJECT_NAME} > ${CMAKE_CURRENT_BINARY_DIR}/version.cc
)

add_custom_target(${PROJECT_NAME}_version
	ALL
	DEPENDS __version_${PROJECT_NAME}
)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/version.cc PROPERTIES GENERATED TRUE)


################################################################################
# Library #
###########

add_library( ${PROJECT_NAME}
	${${PROJECT_NAME}_VERSION_SRC}
)

target_include_directories( ${PROJECT_NAME}
	PUBLIC src/
)


################################################################################
# Unit test #
#############

add_executable( ${PROJECT_NAME}-test EXCLUDE_FROM_ALL
    test/catch.cc
    test/version.cc
    test/output_stream.cc
    test/serialize.cc
    test/parameter_sequence.cc
    test/vt102.cc
)

target_include_directories( ${PROJECT_NAME}-test
	PRIVATE test/
)

target_link_libraries( ${PROJECT_NAME}-test
	${PROJECT_NAME}
)

target_compile_options( ${PROJECT_NAME}-test
	PRIVATE "-Wall"
	PRIVATE "-Werror"
	PRIVATE "-std=c++14"
)
