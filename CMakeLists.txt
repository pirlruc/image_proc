cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_INSTALL_PREFIX           "${CMAKE_BINARY_DIR}/install"  CACHE PATH "Installation dir.")

project(
    image_proc
    VERSION     0.1.0
    LANGUAGES   CXX
)
set(IMPROC_SUPERPROJECT_VERSION ${PROJECT_VERSION})

# Add dependencies
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Project configuration
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  option(BUILD_SHARED_LIBS           "Build using shared libraries" ON)
  option(WITH_TEST                   "Build library with main test" OFF)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/modules/infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/services       ${CMAKE_BINARY_DIR}/services)
# add_subdirectory(${CMAKE_SOURCE_DIR}/modules/corecv         ${CMAKE_BINARY_DIR}/corecv)

install(
  EXPORT      improc_infrastructure_target 
  FILE        improc_infrastructure_target.cmake
  DESTINATION lib/cmake/improc_infrastructure
)
install(
  EXPORT      improc_services_target
  FILE        improc_services_target.cmake
  DESTINATION lib/cmake/improc_services
)  

include(CMakePackageConfigHelpers)
# Generate the library config file that includes the exports
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/config.cmake.in
  
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
# Generate the version file for the config file
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_config_version.cmake
  VERSION "${image_proc_VERSION_MAJOR}.${image_proc_VERSION_MINOR}.${image_proc_VERSION_PATCH}"
  COMPATIBILITY AnyNewerVersion
)

# Install the configuration file
install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_config_version.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
)

# Generate the export targets for the build tree (after the install(TARGETS ) command)
export(
  EXPORT    improc_infrastructure_target
  FILE      ${CMAKE_CURRENT_BINARY_DIR}/improc_infrastructure_target.cmake
)
export(
  EXPORT    improc_services_target
  FILE      ${CMAKE_CURRENT_BINARY_DIR}/improc_services_target.cmake
)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${image_proc_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${image_proc_VERSION_MINOR}")
include(CPack)