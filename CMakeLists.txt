cmake_minimum_required(VERSION 3.14-3.18)

project(
    image_proc
    VERSION     1.0.0
)

# Add dependencies
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	add_subdirectory(${CMAKE_SOURCE_DIR}/modules/infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
	add_subdirectory(${CMAKE_SOURCE_DIR}/modules/services       ${CMAKE_BINARY_DIR}/services)
endif()
