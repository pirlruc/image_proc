cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

if(NOT DEFINED IMPROC_SUPERPROJECT_VERSION)
  set(IMPROC_SUPERPROJECT_VERSION 1.0.0)
endif()

project(
  improc_calib
  VERSION     ${IMPROC_SUPERPROJECT_VERSION}
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
  option(IMPROC_WITH_TESTS 			     "Building library with tests"          OFF)
  option(IMPROC_WITH_COVERAGE  	     "Building library with code coverage"  OFF)
  option(BUILD_SHARED_LIBS           "Building shared libraries"            ON)
endif()

# Add external dependencies
# EIGEN
FetchContent_Declare(
  eigen
  GIT_REPOSITORY  https://gitlab.com/libeigen/eigen
  GIT_TAG         3.4.0
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/eigen
)
set(EIGEN_SPLIT_LARGE_TESTS OFF)
set(EIGEN_BUILD_DOC         OFF)
set(BUILD_TESTING           OFF)
FetchContent_MakeAvailable(eigen)
target_include_directories(eigen INTERFACE  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/eigen>
                                            $<INSTALL_INTERFACE:include> )
                                            
# VISP
# FetchContent_Declare(
#   visp
#   GIT_REPOSITORY  https://github.com/lagadic/visp
#   GIT_TAG         v3.4.0
#   SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/visp
# )
# FetchContent_MakeAvailable(visp)
# target_include_directories(visp INTERFACE  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/visp>
#                                             $<INSTALL_INTERFACE:include> )

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Dir: ${CMAKE_INSTALL_PREFIX}")

set(
  IMPROC_CALIB_LIB_FILES

  ${PROJECT_SOURCE_DIR}/include/improc/calib/logger_calib.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/calib/point_matrix.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/calib/pixel_matrix.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/calib/homography_matrix.hpp
)

add_library(${PROJECT_NAME} SHARED ${IMPROC_CALIB_LIB_FILES})
add_library(improc::calib ALIAS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} improc::services eigen)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE        CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

target_include_directories  (${PROJECT_NAME}  PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                              $<INSTALL_INTERFACE:include> )

# Link dependencies
target_link_libraries       (${PROJECT_NAME}   PRIVATE   improc::services)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   eigen)
target_link_libraries       (${PROJECT_NAME}   INTERFACE improc::services)
target_link_libraries       (${PROJECT_NAME}   INTERFACE eigen)

# Tests configuration
if(IMPROC_WITH_TESTS)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test     ${CMAKE_BINARY_DIR}/improc_calib_test)
endif()

# Install configuration
set(${PROJECT_NAME}_libs ${PROJECT_NAME} improc_services eigen)
install(
  TARGETS     ${${PROJECT_NAME}_libs}
  DESTINATION lib
  EXPORT      ${PROJECT_NAME}_target 
)
install(FILES     ${PROJECT_SOURCE_DIR}/external/eigen/COPYING.MPL2 DESTINATION share/licenses/improc/eigen)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/improc              DESTINATION include)
