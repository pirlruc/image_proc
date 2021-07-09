cmake_minimum_required(VERSION 3.14-3.18)

include(FetchContent)
include(GoogleTest)

# Project configuration
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin" CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Executable/dll output dir.")
set(BUILD_SHARED_LIBS   ON)
set(BUILD_GMOCK         OFF)
set(BUILD_GTEST         ON)

# Add external dependencies
#GOOGLETEST
FetchContent_Declare(
  googletest
  GIT_REPOSITORY  https://github.com/google/googletest.git
  GIT_TAG         release-1.11.0
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/test/external/googletest
)
FetchContent_MakeAvailable(googletest)
# target_include_directories(googletest INTERFACE ${PROJECT_SOURCE_DIR}/external/googletest/include)

mark_as_advanced(
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest      PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)

add_executable(
    ${INFRASTRUCTURE_LIB_OUTPUT_NAME}_test
    
    ${PROJECT_SOURCE_DIR}/test/test_file.cpp
    ${PROJECT_SOURCE_DIR}/test/test_logger.cpp
)
target_link_libraries(${INFRASTRUCTURE_LIB_OUTPUT_NAME}_test  PRIVATE ${INFRASTRUCTURE_LIB_OUTPUT_NAME})
target_link_libraries(${INFRASTRUCTURE_LIB_OUTPUT_NAME}_test  PRIVATE gtest gtest_main)

gtest_discover_tests(
    ${INFRASTRUCTURE_LIB_OUTPUT_NAME}_test
    WORKING_DIRECTORY                           ${PROJECT_SOURCE_DIR}/test
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY    "${PROJECT_SOURCE_DIR}/test"
)
set_target_properties(${INFRASTRUCTURE_LIB_OUTPUT_NAME}_test PROPERTIES FOLDER ${PROJECT_SOURCE_DIR}/test)
