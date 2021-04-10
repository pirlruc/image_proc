cmake_minimum_required(VERSION 3.14-3.18)

project(lib_infrastructure)

include(FetchContent)

#SPDLOG
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY  https://github.com/gabime/spdlog
  GIT_TAG         v1.8.5
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/spdlog
)

# JSONCPP
FetchContent_Declare(
  jsoncpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
  GIT_TAG        1.9.4
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/jsoncpp
)
set(JSONCPP_WITH_TESTS  OFF)
set(BUILD_SHARED_LIBS   ON)

FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(jsoncpp)
