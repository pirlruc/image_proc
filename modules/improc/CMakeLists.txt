cmake_minimum_required(VERSION 3.14-3.18)

project(lib_improc)

include(FetchContent)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"     CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"     CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"     CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"     CACHE PATH "Executable/dll output dir.")
set(CMAKE_INSTALL_PREFIX           "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation dir.")
set(CMAKE_DEBUG_POSTFIX d)
option(IMPROC_WITH_TESTS 			     "Building library with tests"          OFF)
option(IMPROC_WITH_COVERAGE  	     "Building library with code coverage"  OFF)
option(BUILD_SHARED_LIBS           "Building shared libraries"            ON)

# OPENCV
FetchContent_Declare(
  opencv
  GIT_REPOSITORY  https://github.com/opencv/opencv
  GIT_TAG         4.7.0
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv
)
set(WITH_OPENGL           ON )

FetchContent_MakeAvailable(opencv)

message(STATUS "EXECUTABLE_OUTPUT_PATH    : ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "CMAKE_INSTALL_PREFIX      : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "OPENCV_EXTRA_MODULES_PATH : ${OPENCV_EXTRA_MODULES_PATH}")

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Dir: ${CMAKE_INSTALL_PREFIX}")
