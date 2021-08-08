cmake_minimum_required(VERSION 3.14-3.18)

project(
  improc_infrastructure
  VERSION   1.0.0
)

include(FetchContent)

# Project configuration
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(CMAKE_INSTALL_PREFIX           "${CMAKE_BINARY_DIR}/install"  CACHE PATH "Installation dir.")
  option(BUILD_SHARED_LIBS           "Build using shared libraries" ON)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

# Add external dependencies
#SPDLOG
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY  https://github.com/gabime/spdlog
  GIT_TAG         v1.9.1
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/spdlog
)
FetchContent_MakeAvailable(spdlog)
target_include_directories(spdlog INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/spdlog/include>
                                            $<INSTALL_INTERFACE:include> )

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
# target_include_directories(jsoncpp_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/jsoncpp/include>
#                                                                    $<INSTALL_INTERFACE:include> )

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

add_library(
  ${PROJECT_NAME}
    
  ${PROJECT_SOURCE_DIR}/include/improc/exception.h
  ${PROJECT_SOURCE_DIR}/include/improc/improc_defs.h
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logger_singleton.h
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/benchmark_singleton.h
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logger_infrastructure.h
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/jsonfile_parser.h

  ${PROJECT_SOURCE_DIR}/src/file.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/src)
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                               $<INSTALL_INTERFACE:include> )
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                               $<INSTALL_INTERFACE:include> )

# Link dependencies
target_link_libraries       (${PROJECT_NAME}   PRIVATE   spdlog)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   jsoncpp_lib)
target_link_libraries       (${PROJECT_NAME}   INTERFACE spdlog)
target_link_libraries       (${PROJECT_NAME}   INTERFACE jsoncpp_lib)

# Tests configuration
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
set(${PROJECT_NAME}_libs ${PROJECT_NAME} spdlog jsoncpp_lib)
install(
  TARGETS     ${${PROJECT_NAME}_libs}
  DESTINATION lib
  EXPORT      ${PROJECT_NAME}_target 
)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/file.h                    DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logger_singleton.h        DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/benchmark_singleton.h     DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logger_infrastructure.h   DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/jsonfile_parser.h         DESTINATION include/improc/infrastructure)

install(TARGETS ${PROJECT_NAME}_version                       DESTINATION bin)
install(FILES   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_config.h  DESTINATION include)
