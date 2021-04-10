cmake_minimum_required(VERSION 3.14-3.18)

project(lib_improc)

include(FetchContent)

#OPENCV
FetchContent_Declare(
  opencv
  GIT_REPOSITORY  https://github.com/opencv/opencv
  GIT_TAG         4.5.2
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv
)
set(BUILD_SHARED_LIBS     ON )
set(BUILD_WEBP            OFF)
set(BUILD_opencv_highgui  OFF)
set(BUILD_PROTOBUF        OFF)
set(WITH_WEBP             OFF)
set(WITH_DSHOW            OFF)
set(WITH_PROTOBUF         OFF)

FetchContent_MakeAvailable(opencv)
