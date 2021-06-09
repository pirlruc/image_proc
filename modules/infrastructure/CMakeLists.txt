cmake_minimum_required(VERSION 3.14-3.18)

project(
  improc_infrastructure
  VERSION 1.0
)

include(FetchContent)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin" CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Executable/dll output dir.")
set(BUILD_SHARED_LIBS   ON)

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
