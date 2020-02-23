# Build rapid framework libraries
#
#

cmake_minimum_required(VERSION 3.15)

set(PROJECT rapid)
set(VERSION "0.0.1-dev#1")
set(CMAKE_CXX_STANDARD 17)

project(rapid)

# includes
set(CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules"
  ${CMAKE_MODULE_PATH}
)

set(INCLUDE_INSTALL_DIR include CACHE STRING
  "The subdirectory where header files should be installed")
set(LIB_INSTALL_DIR lib CACHE STRING
  "The subdirectory where libraries should be installed")
set(BIN_INSTALL_DIR bin CACHE STRING
  "The subdirectory where binaries should be installed")
set(CMAKE_INSTALL_DIR "lib/cmake/${PROJECT}" CACHE STRING
  "The subdirectory where CMake package config files should be installed")
set(RAPID_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_DIR}-${VERSION}" CACHE STRING
  "The subdirectory where CMake package config files should be installed")

option(BUILD_EVENT "Enable building event library." ON)
option(BUILD_NETWORK "Enable building network library." ON)

if(BUILD_EVENT)
#    add_subdirectory(event)
endif()

if(BUILD_NETWORK)
    add_subdirectory(network)
endif()

# Generate the rapid.cmake file for installation so that projects
# that use rapid can easily depend on it in their cmake_modules
# files using "find_package(rapid CONFIG)"
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config.cmake"
  "${RAPID_CMAKE_INSTALL_DIR}/${PROJECT}-config.cmake"
  @ONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config-version.cmake"
  VERSION ${VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config.cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-config-version.cmake"
  DESTINATION ${RAPID_CMAKE_INSTALL_DIR}
)

# Generate a pkg-config file so that downstream projects that don't use
# cmake_modules can depend on rapid using pkg-config.
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/lib${PROJECT}.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/lib${PROJECT}.pc.gen"
  @ONLY
)