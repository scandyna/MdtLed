
add_library(
 Mdt_Led
  Mdt/Led.cpp
)
add_library(Mdt0::Led ALIAS Mdt_Led)

target_link_libraries(
 Mdt_Led
  PUBLIC
    Qt5::Widgets # TODO Mybe private ?
  PRIVATE
    BuildSpecifications
)

target_include_directories(
 Mdt_Led
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

if(BUILD_USE_IPO_LTO)
  set_property(TARGET Mdt_Led PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

include(GNUInstallDirs)
include(MdtInstallDirs)

message("MDT_INSTALL_INCLUDEDIR: ${MDT_INSTALL_INCLUDEDIR}")

set_target_properties(Mdt_Led PROPERTIES EXPORT_NAME Led)

# TODO Should split in 2 install(), one for RUNTIME other for dev
install(
  TARGETS Mdt_Led
  EXPORT Mdt0
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  COMPONENT Mdt_Led_Runtime
)

install(
  EXPORT Mdt0
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MdtLed
  NAMESPACE Mdt0::
  FILE MdtLed_RuntimeConfig.cmake
  COMPONENT Mdt_Led_Runtime
)

install(
  DIRECTORY Mdt
  DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  COMPONENT Mdt_Led_Dev
  FILES_MATCHING
  PATTERN *.h
)

# install(
#   EXPORT MdtLed_Dev
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MdtLed
#   NAMESPACE Mdt0::
#   FILE MdtLed_DevConfig.cmake
#   COMPONENT MdtLed_Dev
# )
