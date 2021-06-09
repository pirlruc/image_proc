cmake_minimum_required(VERSION 3.14-3.18)

project(
  improc_test
  VERSION 1.0
)

include(FetchContent)

set(BUILD_SHARED_LIBS ON)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/googletest
)

FetchContent_MakeAvailable(googletest)
