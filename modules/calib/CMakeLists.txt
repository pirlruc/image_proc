cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

project(
  improc_calib
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
  option(BUILD_SHARED_LIBS           "Build using shared libraries" ON)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

# Add external dependencies
# EIGEN
FetchContent_Declare(
  eigen
  GIT_REPOSITORY  https://gitlab.com/libeigen/eigen
  GIT_TAG         3.4.0
  SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/eigen
)
# FetchContent_MakeAvailable(eigen)
# target_include_directories(eigen INTERFACE  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/eigen>
#                                             $<INSTALL_INTERFACE:include> )

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

add_library(
  ${PROJECT_NAME}
    
  ${PROJECT_SOURCE_DIR}/include/improc/calib/vector_matrix.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           11)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE        CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/external/eigen)
target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/src)
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/eigen>
                                               $<INSTALL_INTERFACE:include> )
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                               $<INSTALL_INTERFACE:include> )
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                               $<INSTALL_INTERFACE:include> )

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

add_executable(
  ${PROJECT_NAME}_version

  ${PROJECT_SOURCE_DIR}/main.cpp
)
set_target_properties     (${PROJECT_NAME}_version PROPERTIES CXX_STANDARD           11)
set_target_properties     (${PROJECT_NAME}_version PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties     (${PROJECT_NAME}_version PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})
target_include_directories(${PROJECT_NAME}_version PRIVATE    ${CMAKE_BINARY_DIR})
target_link_libraries     (${PROJECT_NAME}_version PRIVATE    ${PROJECT_NAME})

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
