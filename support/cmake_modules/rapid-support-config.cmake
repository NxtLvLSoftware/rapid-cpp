# cmake_modules configuration file for the rapid frameworks network component
#
# This provides the rapid::support target, which you can depend on by adding it
# to your target_link_libraries().
#
# It also defines the following variables, although using these directly is not
# necessary if you use the rapid::support target instead.
#  RAPID_SUPPORT_INCLUDE_DIRS
#  RAPID_SUPPORT_LIBRARIES

@PACKAGE_INIT@

include(CMakeFindDependencyMacro)

set_and_check(RAPID_INCLUDE_DIR "@PACKAGE_INCLUDE_INSTALL_DIR@")
set_and_check(RAPID_CMAKE_DIR "@PACKAGE_SUPPORT_CMAKE_INSTALL_DIR@")

# find_dependency() ends up changing PACKAGE_PREFIX_DIR, so save
# rapid::support's prefix directory in the RAPID_SUPPORT_PREFIX_DIR variable
set(RAPID_SUPPORT_PREFIX_DIR "${PACKAGE_PREFIX_DIR}")

# Include the rapid-support-config-version.cmake & rapid-support-config-targets.cmake
# files, which are generated from our cmake_modules rules
if (NOT TARGET rapid::support)
  include("${RAPID_CMAKE_DIR}/rapid-support-config-version.cmake")
  include("${RAPID_CMAKE_DIR}/rapid-support-config-targets.cmake")
endif()

# Set RAPID_SUPPORT_LIBRARIES to the rapid::support target
set(RAPID_SUPPORT_LIBRARIES rapid::support)

# Append the rapid::support target to RAPID_LIBRARIES
set(RAPID_LIBRARIES "${RAPID_SUPPORT_LIBRARIES} rapid::support")

if (NOT support)
  message(STATUS "Found rapid::support: ${RAPID_SUPPORT_PREFIX_DIR}")
endif()