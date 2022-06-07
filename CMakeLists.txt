cmake_minimum_required(VERSION 3.14-3.18)

project(
    image_proc
    VERSION     0.3.0
    LANGUAGES   CXX
)
set(IMPROC_SUPERPROJECT_VERSION ${PROJECT_VERSION})

# Add dependencies
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Project configuration
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY      "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(CMAKE_DEBUG_POSTFIX d)
  option(BUILD_SHARED_LIBS            "Build using shared libraries" ON)
  option(IMPROC_WITH_TESTS 			      "Build library with tests"     OFF)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/modules/infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/services       ${CMAKE_BINARY_DIR}/services)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/drawer         ${CMAKE_BINARY_DIR}/drawer)
