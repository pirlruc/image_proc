cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

project(
  image_proc
  VERSION     0.3.0
  LANGUAGES   CXX
)
set(IMPROC_SUPERPROJECT_VERSION ${PROJECT_VERSION})

# Project configuration
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY      "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(CMAKE_DEBUG_POSTFIX d)
  option(IMPROC_WITH_TESTS 			      "Building library with tests"          ON)
  option(IMPROC_WITH_COVERAGE  	      "Building library with code coverage"  OFF)
  option(BUILD_SHARED_LIBS            "Building shared libraries"            ON)
  option(IMPROC_DRAWER_WITH_QRCODE_SUPPORT              "Building drawer module with QR-Code support"                 ON)
  option(IMPROC_DRAWER_WITH_BARCODE_DATA_MATRIX_SUPPORT "Building drawer module with barcode and data matrix support" ON)
  option(IMPROC_DRAWER_WITH_TEXT_SUPPORT                "Building drawer module with text generation support"         ON)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/modules/infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/services       ${CMAKE_BINARY_DIR}/services)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/calib          ${CMAKE_BINARY_DIR}/calib)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/corecv         ${CMAKE_BINARY_DIR}/corecv)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/drawer         ${CMAKE_BINARY_DIR}/drawer)
