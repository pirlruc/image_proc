cmake_minimum_required(VERSION 3.14-3.18)

project(
    improc_services
    VERSION     1.0
)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add dependencies
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	add_subdirectory(../infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
endif()

# Project configuration
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Archive output dir.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Library output dir.")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin" CACHE PATH "PDB (MSVC debug symbol)output dir.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Executable/dll output dir.")
set(BUILD_SHARED_LIBS                   ON)

if (CMAKE_BUILD_TYPE STREQUAL Release)
    set(LIBRARY_OUTPUT_NAME ${PROJECT_NAME})
else()
    set(LIBRARY_OUTPUT_NAME ${PROJECT_NAME}d)
endif()

add_library(
    ${LIBRARY_OUTPUT_NAME} SHARED
    
    include/improc/services/exception.h

    src/container.cpp
    src/context.cpp
    src/factory.cpp
    src/base_service.cpp
)

target_include_directories  (${LIBRARY_OUTPUT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${LIBRARY_OUTPUT_NAME}   INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${LIBRARY_OUTPUT_NAME}   INTERFACE ${PROJECT_SOURCE_DIR}/src)

# Link dependencies
target_link_libraries       (${LIBRARY_OUTPUT_NAME}   PRIVATE   spdlog)
target_link_libraries       (${LIBRARY_OUTPUT_NAME}   PRIVATE   jsoncpp_lib)

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    add_executable(
        improc_services_test 
        main_ex2.cpp
    )

    target_link_libraries(improc_services_test PRIVATE ${LIBRARY_OUTPUT_NAME})
    target_link_libraries(improc_services_test PRIVATE spdlog)
    target_link_libraries(improc_services_test PRIVATE jsoncpp_lib)
endif()

# if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
#     add_subdirectory(test)
# endif()
