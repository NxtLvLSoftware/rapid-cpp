# cmake_modules configuration file for rapid framework - network component.
#
# This provides the rapid component targets, which you can depend on by adding it
# to your target_link_libraries().
#

get_filename_component(_RAPID_CMAKEDIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)
foreach(COMPONENT ${rapid_FIND_COMPONENTS})
  include("${_RAPID_CMAKEDIR}/rapid_${COMPONENT}-${VERSION}/rapid-${COMPONENT}-config.cmake")
endforeach()