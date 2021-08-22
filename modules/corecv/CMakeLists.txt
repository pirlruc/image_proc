cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

project(
  improc_corecv
  VERSION   1.0.0
)

include(FetchContent)

# Add dependencies
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Project configuration
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(DESTDIR                        "${CMAKE_BINARY_DIR}/install"  CACHE PATH "Installation dir.")
  option(BUILD_SHARED_LIBS           "Build using shared libraries" ON)
  set(CMAKE_DEBUG_POSTFIX d)

  add_subdirectory(${PROJECT_SOURCE_DIR}/../infrastructure  ${CMAKE_BINARY_DIR}/infrastructure)
  add_subdirectory(${PROJECT_SOURCE_DIR}/../services        ${CMAKE_BINARY_DIR}/services)
endif()

# Add external dependencies
# OPENCV
FetchContent_Declare(
  opencv_contrib
  GIT_REPOSITORY  https://github.com/opencv/opencv_contrib.git
  GIT_TAG         4.5.3
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv_contrib
)
FetchContent_GetProperties(opencv_contrib)
if(NOT opencv_contrib_POPULATED)
  FetchContent_Populate(opencv_contrib)
endif()

FetchContent_Declare(
  opencv
  GIT_REPOSITORY  https://github.com/opencv/opencv
  GIT_TAG         4.5.3
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv
)
set(OPENCV_EXTRA_MODULES_PATH ${CMAKE_CURRENT_BINARY_DIR}/../external/opencv_contrib/modules)
set(WITH_TBB              ON )
set(WITH_V4L              ON )
set(WITH_OPENGL           ON )
FetchContent_MakeAvailable(opencv)

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

add_library(
  ${PROJECT_NAME}
    
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/logger_improc.h
  ${PROJECT_SOURCE_DIR}/src/image.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           11)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})
target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/src)
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                               $<INSTALL_INTERFACE:include> )
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                               $<INSTALL_INTERFACE:include> )

find_package(OpenCV REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE    ${OpenCV_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} INTERFACE  $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIRS}>
                                                      $<INSTALL_INTERFACE:include> )

# Link dependencies
target_link_libraries       (${PROJECT_NAME}   PRIVATE   improc_infrastructure)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   improc_services)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   ${OpenCV_LIBS})
target_link_libraries       (${PROJECT_NAME}   INTERFACE improc_infrastructure)
target_link_libraries       (${PROJECT_NAME}   INTERFACE improc_services)
target_link_libraries       (${PROJECT_NAME}   INTERFACE ${OpenCV_LIBS})

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test ${CMAKE_BINARY_DIR}/test)
endif()

# Create executable file to get version of library
configure_file(
  ${PROJECT_SOURCE_DIR}/version/version_config.h.in 
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.h
)

add_executable(
  ${PROJECT_NAME}_version

  ${PROJECT_SOURCE_DIR}/version/main.cpp
)
set_target_properties     (${PROJECT_NAME}_version PROPERTIES CXX_STANDARD           11)
set_target_properties     (${PROJECT_NAME}_version PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties     (${PROJECT_NAME}_version PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})
target_include_directories(${PROJECT_NAME}_version PRIVATE    ${CMAKE_BINARY_DIR})

# Install configuration
# install(
#   TARGETS     ${PROJECT_NAME}
#   DESTINATION lib
#   EXPORT      ${PROJECT_NAME}_target 
# )
# install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/services/logger_services.h     DESTINATION include/improc/services)
# install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/services/context.h             DESTINATION include/improc/services)
# install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/services/base_service.h        DESTINATION include/improc/services)
# install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/services/factory.h             DESTINATION include/improc/services)
# install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/services/sequence_service.h    DESTINATION include/improc/services)

install(TARGETS ${PROJECT_NAME}_version                         DESTINATION bin)
install(FILES   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.h    DESTINATION include)
