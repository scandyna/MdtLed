
add_library(
 Mdt_Led
  Mdt/Led.cpp
)
add_library(Mdt::Led ALIAS Mdt_Led)

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
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
#    $<INSTALL_INTERFACE:include>
  PRIVATE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Impl>
)

# target_include_directories(
#  Mdt_Led
#   PRIVATE
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
# #    $<INSTALL_INTERFACE:include>
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Impl>
# )

set_target_properties(Mdt_Led
  PROPERTIES
    PUBLIC_HEADER
      "Mdt/Led.h"
)

get_target_property(Mdt_Led_public_header Mdt_Led PUBLIC_HEADER)
message("PUBLIC_HEADER: ${Mdt_Led_public_header}")

get_target_property(Mdt_Led_inclues Mdt_Led INTERFACE_INCLUDE_DIRECTORIES)
message("INTERFACE_INCLUDE_DIRECTORIES: ${Mdt_Led_inclues}")


if(BUILD_USE_IPO_LTO)
  set_property(TARGET Mdt_Led PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set(MDT_INSTALL_PACKAGE_NAME Mdt0)

include(GNUInstallDirs)
include(MdtInstallDirs)

message("MDT_INSTALL_INCLUDEDIR: ${MDT_INSTALL_INCLUDEDIR}")

# set_target_properties(Mdt_Led PROPERTIES INTERFACE_FIND_PACKAGE_NAME Mdt0Led)
# set_target_properties(Qt5::Widgets PROPERTIES INTERFACE_FIND_PACKAGE_NAME Qt5Widgets)

include(MdtPackageConfigHelpers)

# mdt_set_target_package_properties_if_not(
#   TARGET Mdt_Led
#   PACKAGE_NAME Mdt0Led
#   PACKAGE_VERSION ${PROJECT_VERSION}
#   PACKAGE_VERSION_EXACT
#   PATHS ..
# )

# mdt_set_target_package_properties_if_not(
#   TARGET Qt5::Widgets
#   PACKAGE_NAME Qt5Widgets
# )

# set_target_properties(Qt5::Widgets
#   PROPERTIES
#     INTERFACE_FIND_PACKAGE_NAME Qt5Widgets
#     INTERFACE_FIND_PACKAGE_PATHS ..
# )


mdt_get_target_package_name(mdtLedPackageName1 Mdt::Led)
mdt_get_target_package_name(mdtLedPackageName2 Mdt_Led)
mdt_get_target_package_name(qt5WidgetsPackageName Qt5::Widgets)

message("mdtLedPackageName1: ${mdtLedPackageName1}")
message("mdtLedPackageName2: ${mdtLedPackageName2}")
message("qt5WidgetsPackageName: ${qt5WidgetsPackageName}")

if(mdtLedPackageName1)
  message("mdtLedPackageName1 found: ${mdtLedPackageName1}")
endif()
if(qt5WidgetsPackageName)
  message("qt5WidgetsPackageName found: ${qt5WidgetsPackageName}")
endif()

set_target_properties(Mdt_Led
  PROPERTIES
    EXPORT_NAME Led
    EXPORT_NAMESPACE Mdt0::
    INTERFACE_FIND_PACKAGE_NAME Mdt0Led
    INTERFACE_FIND_PACKAGE_VERSION ${PROJECT_VERSION}
    INTERFACE_FIND_PACKAGE_EXACT TRUE
    INTERFACE_FIND_PACKAGE_PATHS ..
)

# mdt_set_target_install_rpath_property(
#   TARGET Mdt_Led
#   PATHS .
# )
# get_target_property(Mdt_Led_Rpath Mdt_Led INSTALL_RPATH)
# message("Mdt::LED INSTALL_RPATH: ${Mdt_Led_Rpath}")

install(
  TARGETS Mdt_Led
  EXPORT Mdt0LedTargets
  RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Mdt_Led_Runtime
  LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Mdt_Led_Runtime
  ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Mdt_Led_Dev
  PUBLIC_HEADER
    DESTINATION ${MDT_INSTALL_INCLUDEDIR}/Mdt
  INCLUDES
    DESTINATION ${MDT_INSTALL_INCLUDEDIR}
)

install(
  EXPORT Mdt0LedTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0Led
  NAMESPACE Mdt0::
  FILE Mdt0LedTargets.cmake
  COMPONENT Mdt_Led_Dev
)

# install(
#   DIRECTORY Mdt
#   DESTINATION ${MDT_INSTALL_INCLUDEDIR}
#   COMPONENT Mdt_Led_Dev
#   FILES_MATCHING
#   PATTERN *.h
# )

mdt_install_package_config_file(
  TARGETS Mdt_Led
  TARGETS_EXPORT_FILE Mdt0LedTargets.cmake
  FILE Mdt0LedConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0Led
  COMPONENT Mdt_Led_Dev
)

mdt_install_package_config_version_file(
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY ExactVersion
  FILE "${CMAKE_CURRENT_BINARY_DIR}/Mdt0LedConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0Led
  COMPONENT Mdt_Led_Dev
)

# include(CMakePackageConfigHelpers)
# write_basic_package_version_file(
#   "${CMAKE_CURRENT_BINARY_DIR}/Mdt0LedConfigVersion.cmake"
#   VERSION ${PROJECT_VERSION}
#   COMPATIBILITY ExactVersion
# )
# 
# install(
#   FILES "${CMAKE_CURRENT_BINARY_DIR}/Mdt0LedConfigVersion.cmake"
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0Led
#   COMPONENT Mdt_Led_Dev
# )


# include(CMakePackageConfigHelpers)
# configure_package_config_file(
#   "${CMAKE_SOURCE_DIR}/Mdt0LedConfig.cmake.in"
#   Mdt0LedConfig.cmake
#   INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0Led
# )

# install(
#   FILES "${CMAKE_CURRENT_BINARY_DIR}/Mdt0LedConfig.cmake"
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0Led
#   COMPONENT Mdt_Led_Dev
# )

# install(
#   TARGETS Mdt_Led
#   EXPORT Mdt0Led
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   INCLUDES DESTINATION ${MDT_INSTALL_INCLUDEDIR}
#   COMPONENT Mdt_Led_Dev
# )

# install(
#   EXPORT MdtLed_Dev
#   DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MdtLed
#   NAMESPACE Mdt0::
#   FILE MdtLed_DevConfig.cmake
#   COMPONENT MdtLed_Dev
# )

if(NOT MDT_INSTALL_IS_UNIX_SYSTEM_WIDE)
#   include(MdtInstallNamespacePackageConfigFile)
  mdt_install_namespace_package_config_file(
    INSTALL_NAMESPACE Mdt0
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0
    COMPONENT Mdt_Led_Dev
  )
  mdt_install_namespace_package_config_version_file(
    INSTALL_NAMESPACE Mdt0
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY ExactVersion
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Mdt0
    COMPONENT Mdt_Dev
  )
endif()


