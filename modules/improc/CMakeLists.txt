cmake_minimum_required(VERSION 3.14-3.18)

project(lib_improc)

include(FetchContent)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"     CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"     CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"     CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"     CACHE PATH "Executable/dll output dir.")
set(CMAKE_INSTALL_PREFIX           "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation dir.")
set(BUILD_SHARED_LIBS     ON )

#OPENCV
FetchContent_Declare(
  opencv
  GIT_REPOSITORY  https://github.com/opencv/opencv
  GIT_TAG         4.5.3
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv
)
set(WITH_OPENGL           ON )

FetchContent_MakeAvailable(opencv)

message(STATUS "EXECUTABLE_OUTPUT_PATH    : ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "CMAKE_INSTALL_PREFIX      : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "OPENCV_EXTRA_MODULES_PATH : ${OPENCV_EXTRA_MODULES_PATH}")
