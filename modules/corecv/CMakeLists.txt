cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

if(NOT DEFINED IMPROC_SUPERPROJECT_VERSION)
  set(IMPROC_SUPERPROJECT_VERSION 1.0.0)
endif()

project(
  improc_corecv
  VERSION   ${IMPROC_SUPERPROJECT_VERSION}
  LANGUAGES   CXX
)

include(FetchContent)

# Project configuration
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(CMAKE_DEBUG_POSTFIX d)
  option(IMPROC_WITH_TESTS 			     "Building library with tests"  ON)
  option(BUILD_SHARED_LIBS           "Building shared libraries"    ON)
endif()

# Add external dependencies
# OPENCV
FetchContent_Declare(
  opencv_contrib
  GIT_REPOSITORY  https://github.com/opencv/opencv_contrib.git
  GIT_TAG         4.5.4
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv_contrib
)
FetchContent_GetProperties(opencv_contrib)
if(NOT opencv_contrib_POPULATED)
  FetchContent_Populate(opencv_contrib)
endif()

FetchContent_Declare(
  opencv
  GIT_REPOSITORY  https://github.com/opencv/opencv
  GIT_TAG         4.5.4
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv
)
set(OPENCV_EXTRA_MODULES_PATH ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv_contrib/modules)
set(WITH_TBB              ON )
set(WITH_V4L              ON )
set(WITH_OPENGL           ON )
FetchContent_MakeAvailable(opencv)

# # DLIB
# FetchContent_Declare(
#   dlib
#   GIT_REPOSITORY  https://github.com/davisking/dlib
#   GIT_TAG         v19.22
#   SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/dlib
# )
# FetchContent_MakeAvailable(dlib)

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Dir: ${CMAKE_INSTALL_PREFIX}")

# add_library(
#   ${PROJECT_NAME}
    
#   ${PROJECT_SOURCE_DIR}/include/improc/exceptions.hpp
#   ${PROJECT_SOURCE_DIR}/include/improc/corecv/logger_improc.hpp
#   ${PROJECT_SOURCE_DIR}/include/improc/services/convert_color_space.hpp
#   ${PROJECT_SOURCE_DIR}/include/improc/services/resize_image.hpp
  
#   ${PROJECT_SOURCE_DIR}/src/color_space.cpp
#   ${PROJECT_SOURCE_DIR}/src/threshold_type.cpp
#   ${PROJECT_SOURCE_DIR}/src/kernel_shape.cpp
#   ${PROJECT_SOURCE_DIR}/src/interpolation_type.cpp
#   ${PROJECT_SOURCE_DIR}/src/morphological_oper.cpp
#   ${PROJECT_SOURCE_DIR}/src/image_format.cpp
#   ${PROJECT_SOURCE_DIR}/src/image.cpp
# )

# set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           17)
# set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
# set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE        CXX)
# set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
# set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

# target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
# target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/src)
# target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
#                                                $<INSTALL_INTERFACE:include> )
# target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
#                                                $<INSTALL_INTERFACE:include> )

# SET(OpenCV_DIR ${CMAKE_INSTALL_PREFIX})
# find_package(OpenCV REQUIRED)
# target_include_directories(${PROJECT_NAME} PRIVATE    ${OpenCV_INCLUDE_DIRS})
# target_include_directories(${PROJECT_NAME} INTERFACE  $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIRS}>
#                                                       $<INSTALL_INTERFACE:include> )
                                               
# # Link dependencies
# target_link_libraries       (${PROJECT_NAME}   PRIVATE   servproc_services)
# target_link_libraries       (${PROJECT_NAME}   PRIVATE   ${OpenCV_LIBS})
# target_link_libraries       (${PROJECT_NAME}   INTERFACE servproc_services)
# target_link_libraries       (${PROJECT_NAME}   INTERFACE ${OpenCV_LIBS})

# if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
#   add_subdirectory(${PROJECT_SOURCE_DIR}/test ${CMAKE_BINARY_DIR}/test)
# endif()

# # Create executable file to get version of library
# configure_file(
#   ${PROJECT_SOURCE_DIR}/version/version_config.hpp.in 
#   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp
# )

# add_executable(
#   ${PROJECT_NAME}_version

#   ${PROJECT_SOURCE_DIR}/version/main.cpp
# )
# set_target_properties     (${PROJECT_NAME}_version PROPERTIES CXX_STANDARD           11)
# set_target_properties     (${PROJECT_NAME}_version PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
# set_target_properties     (${PROJECT_NAME}_version PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})
# target_include_directories(${PROJECT_NAME}_version PRIVATE    ${CMAKE_BINARY_DIR})

# # # Install configuration
# # set(${PROJECT_NAME}_libs ${PROJECT_NAME} opencv)
# # install(
# #   TARGETS     ${${PROJECT_NAME}_libs}
# #   DESTINATION lib
# #   EXPORT      ${PROJECT_NAME}_target 
# # )
# # # install(FILES   ${PROJECT_SOURCE_DIR}/external/opencv/LICENSE                     DESTINATION share/licenses/improc/opencv)

# # install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/corecv/logger_improc.h     DESTINATION include/improc/corecv)

# # install(TARGETS ${PROJECT_NAME}_version                         DESTINATION bin)
# # install(FILES   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.hpp  DESTINATION include)
