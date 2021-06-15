cmake_minimum_required(VERSION 3.14-3.18)

project(
    improc_services
    VERSION     1.0
)

# Add dependencies
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	add_subdirectory(${PROJECT_SOURCE_DIR}/../infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
endif()

# Project configuration
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin" CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Executable/dll output dir.")
set(BUILD_SHARED_LIBS                   ON)
set(CMAKE_CXX_STANDARD                  17)
set(CMAKE_CXX_STANDARD_REQUIRED         True)

if (CMAKE_BUILD_TYPE STREQUAL Release)
    set(SERVICES_LIB_OUTPUT_NAME        ${PROJECT_NAME})
    set(INFRASTRUCTURE_LIB_OUTPUT_NAME  improc_infrastructure)
else()
    set(SERVICES_LIB_OUTPUT_NAME        ${PROJECT_NAME}d)
    set(INFRASTRUCTURE_LIB_OUTPUT_NAME  improc_infrastructured)
endif()

message(STATUS "${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

add_library(
    ${SERVICES_LIB_OUTPUT_NAME} SHARED
    
    ${PROJECT_SOURCE_DIR}/src/container.cpp
    ${PROJECT_SOURCE_DIR}/src/context.cpp
    ${PROJECT_SOURCE_DIR}/src/base_service.cpp
    ${PROJECT_SOURCE_DIR}/src/factory.cpp
    ${PROJECT_SOURCE_DIR}/src/batch_service.cpp
)

target_include_directories  (${SERVICES_LIB_OUTPUT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${SERVICES_LIB_OUTPUT_NAME}   INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${SERVICES_LIB_OUTPUT_NAME}   INTERFACE ${PROJECT_SOURCE_DIR}/src)

# Link dependencies
target_link_libraries       (${SERVICES_LIB_OUTPUT_NAME}   PRIVATE   ${INFRASTRUCTURE_LIB_OUTPUT_NAME})
target_link_libraries       (${SERVICES_LIB_OUTPUT_NAME}   INTERFACE ${INFRASTRUCTURE_LIB_OUTPUT_NAME})

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    add_executable(
        ${SERVICES_LIB_OUTPUT_NAME}_test 
        
        ${PROJECT_SOURCE_DIR}/test/main_ex1.cpp
        # ${PROJECT_SOURCE_DIR}/test/main_container.cpp
    )

    target_link_libraries(${SERVICES_LIB_OUTPUT_NAME}_test PRIVATE ${SERVICES_LIB_OUTPUT_NAME})
endif()

# if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
#     add_subdirectory(test)
# endif()
