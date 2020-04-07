
set(COMPONENT support)

set(SUPPORT_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_DIR}_${COMPONENT}-${VERSION}" CACHE STRING
  "The subdirectory where CMake package config files should be installed")

# Gather the library headers & sources
file(GLOB_RECURSE RAPID_SUPPORT_HEADER_FILES FOLLOW_SYMLINKS include/*.h)
file(GLOB_RECURSE RAPID_SUPPORT_SOURCE_FILES FOLLOW_SYMLINKS src/*.cpp)

# Create the library target & namespaced alias
add_library(${COMPONENT} SHARED ${RAPID_SUPPORT_HEADER_FILES} ${RAPID_SUPPORT_SOURCE_FILES})
add_library(${PROJECT}::${COMPONENT} ALIAS ${COMPONENT})

target_include_directories(${COMPONENT}
  PUBLIC
)
target_link_libraries(${COMPONENT}
  PUBLIC
)

TARGET_COMPILE_OPTIONS(${COMPONENT} PRIVATE
  -Wall -Wextra
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  #  -Wmisleading-indentation
  #  -Wduplicated-cond
  #  -Wduplicated-branches
  #  -Wlogical-op
  -Wnull-dereference
  #  -Wuseless-cast
  -Wdouble-promotion
  -Wformat=2
  #  -Wlifetime
  )

install(TARGETS ${COMPONENT}
  EXPORT ${COMPONENT}-targets
  COMPONENT ${COMPONENT}
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
  INCLUDES DESTINATION ${INCLUDE_INSTALL_DIR}
)
install(DIRECTORY include/
  DESTINATION "${INCLUDE_INSTALL_DIR}/${PROJECT}/${COMPONENT}"
  COMPONENT ${COMPONENT}
  FILES_MATCHING PATTERN "*.h"
)

install(
  EXPORT ${COMPONENT}-targets
  FILE "${PROJECT}-${COMPONENT}-config-targets.cmake"
  DESTINATION ${SUPPORT_CMAKE_INSTALL_DIR}
  NAMESPACE ${PROJECT}::
  COMPONENT ${COMPONENT}
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  cmake_modules/${PROJECT}-${COMPONENT}-config.cmake
  ${PROJECT}-${COMPONENT}-config.cmake
  INSTALL_DESTINATION ${SUPPORT_CMAKE_INSTALL_DIR}
  PATH_VARS INCLUDE_INSTALL_DIR SUPPORT_CMAKE_INSTALL_DIR
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-${COMPONENT}-config-version.cmake"
  VERSION ${VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}-${COMPONENT}-config.cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/${PROJECT}-${COMPONENT}-config-version.cmake"
  DESTINATION ${SUPPORT_CMAKE_INSTALL_DIR}
  COMPONENT ${COMPONENT}
)

#if(WITH_EXAMPLES)
#  add_subdirectory(examples)
#endif()