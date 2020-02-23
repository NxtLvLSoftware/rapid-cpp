# cmake_modules configuration file for the rapid frameworks network component
#
# This provides the rapid::network target, which you can depend on by adding it
# to your target_link_libraries().
#
# It also defines the following variables, although using these directly is not
# necessary if you use the rapid::network target instead.
#  RAPID_NETWORK_INCLUDE_DIRS
#  RAPID_NETWORK_LIBRARIES

@PACKAGE_INIT@

include(CMakeFindDependencyMacro)

set_and_check(RAPID_INCLUDE_DIR "@PACKAGE_INCLUDE_INSTALL_DIR@")
set_and_check(RAPID_CMAKE_DIR "@PACKAGE_NETWORK_CMAKE_INSTALL_DIR@")

# find_dependency() ends up changing PACKAGE_PREFIX_DIR, so save
# rapid::network's prefix directory in the RAPID_NETWORK_PREFIX_DIR variable
set(RAPID_NETWORK_PREFIX_DIR "${PACKAGE_PREFIX_DIR}")

# Include the rapid-network-config-version.cmake & rapid-network-config-targets.cmake
# files, which are generated from our cmake_modules rules
if (NOT TARGET rapid::network)
  include("${RAPID_CMAKE_DIR}/rapid-network-config-version.cmake")
  include("${RAPID_CMAKE_DIR}/rapid-network-config-targets.cmake")
endif()

# Set RAPID_NETWORK_LIBRARIES to the rapid::network target
set(RAPID_NETWORK_LIBRARIES rapid::network)

# Append the rapid::network target to RAPID_LIBRARIES
set(RAPID_LIBRARIES "${RAPID_NETWORK_LIBRARIES} rapid::network")

if (NOT rapid_network_FIND_QUIETLY)
  message(STATUS "Found rapid::network: ${RAPID_NETWORK_PREFIX_DIR}")
endif()