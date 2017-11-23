cmake_minimum_required(VERSION 2.8)
project(some_test)

set(SRC_FILES test.cpp)
set(HDR_FILES test.h)
add_executable(some_test ${SRC_FILES} ${HDR_FILES})
set_target_properties(some_test
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "../bin"
)
