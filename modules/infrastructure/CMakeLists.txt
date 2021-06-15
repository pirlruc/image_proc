cmake_minimum_required(VERSION 3.14-3.18)

project(
  improc_infrastructure
  VERSION 1.0
)

include(FetchContent)

# Project configuration
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin" CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Executable/dll output dir.")
set(BUILD_SHARED_LIBS   ON)

# Add external dependencies
#SPDLOG
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY  https://github.com/gabime/spdlog
  GIT_TAG         v1.8.5
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/spdlog
)
FetchContent_MakeAvailable(spdlog)
target_include_directories(spdlog INTERFACE ${PROJECT_SOURCE_DIR}/external/spdlog/include)

# JSONCPP
FetchContent_Declare(
  jsoncpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
  GIT_TAG        1.9.4
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/jsoncpp
)
set(JSONCPP_WITH_TESTS    OFF)
set(JSONCPP_WITH_EXAMPLE  OFF)
FetchContent_MakeAvailable(jsoncpp)
# Already added in jsoncpp CMakeLists
# target_include_directories(jsoncpp_lib INTERFACE ${PROJECT_SOURCE_DIR}/external/jsoncpp/include)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_BUILD_TYPE STREQUAL Release)
    set(INFRASTRUCTURE_LIB_OUTPUT_NAME ${PROJECT_NAME})
else()
    set(INFRASTRUCTURE_LIB_OUTPUT_NAME ${PROJECT_NAME}d)
endif()

message(STATUS "${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

add_library(
    ${INFRASTRUCTURE_LIB_OUTPUT_NAME} SHARED
    
    ${PROJECT_SOURCE_DIR}/include/improc/exception.h
    ${PROJECT_SOURCE_DIR}/include/improc/improc_defs.h

    ${PROJECT_SOURCE_DIR}/src/file.cpp
)

target_include_directories  (${INFRASTRUCTURE_LIB_OUTPUT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${INFRASTRUCTURE_LIB_OUTPUT_NAME}   INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${INFRASTRUCTURE_LIB_OUTPUT_NAME}   INTERFACE ${PROJECT_SOURCE_DIR}/src)

# Link dependencies
target_link_libraries       (${INFRASTRUCTURE_LIB_OUTPUT_NAME}   PRIVATE   spdlog)
target_link_libraries       (${INFRASTRUCTURE_LIB_OUTPUT_NAME}   PRIVATE   jsoncpp_lib)
target_link_libraries       (${INFRASTRUCTURE_LIB_OUTPUT_NAME}   INTERFACE spdlog)
target_link_libraries       (${INFRASTRUCTURE_LIB_OUTPUT_NAME}   INTERFACE jsoncpp_lib)

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    add_executable(
        ${INFRASTRUCTURE_LIB_OUTPUT_NAME}_test 
        
        ${PROJECT_SOURCE_DIR}/test/main.cpp
    )

    target_link_libraries(${INFRASTRUCTURE_LIB_OUTPUT_NAME}_test  PRIVATE ${INFRASTRUCTURE_LIB_OUTPUT_NAME})
endif()
