
add_library(
 MdtLed
  Mdt/Led.cpp
)

target_link_libraries(
 MdtLed
  PUBLIC
    Qt5::Widgets # TODO Mybe private ?
  PRIVATE
    BuildSpecifications
)

# set_target_properties(
#  MdtLed
#   PROPERTIES PUBLIC_HEADER
#    Mdt/Led.h
# )

target_include_directories(
 MdtLed
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#    $<INSTALL_INTERFACE:include>
)

if(BUILD_USE_IPO_LTO)
  set_property(TARGET MdtLed PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

include(GNUInstallDirs)
include(MdtInstallDirs)

message("MDT_INSTALL_INCLUDEDIR: ${MDT_INSTALL_INCLUDEDIR}")

install(
  TARGETS MdtLed
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  COMPONENT MdtLed_Runtime
)

install(
  EXPORT MdtLed_Runtime
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MdtLed
  NAMESPACE Mdt::
  FILE MdtLed_RuntimeConfig.cmake
  COMPONENT MdtLed_Runtime
)

install(
  DIRECTORY Mdt
  DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  COMPONENT MdtLed_Dev
  FILES_MATCHING
  PATTERN *.h
)

install(
  EXPORT MdtLed_Dev
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MdtLed
  NAMESPACE Mdt::
  FILE MdtLed_DevConfig.cmake
  COMPONENT MdtLed_Dev
)
