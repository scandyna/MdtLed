
cmake_minimum_required(VERSION 3.10)

project(MdtLed VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_C_STANDARD 11)


set(MDT_CMAKE_MODULE_PREFIX_PATH CACHE PATH "Path to the root of MdtCMakeModules. (For example: /opt/MdtCMakeModules).")
if(MDT_CMAKE_MODULE_PREFIX_PATH)
  list(APPEND CMAKE_PREFIX_PATH "${MDT_CMAKE_MODULE_PREFIX_PATH}")
endif()
find_package(MdtCMakeModules REQUIRED)

# Define a optional Qt prefix path
include(AddQt5ToCMakePrefixPath)
set(QT_PREFIX_PATH CACHE PATH "Path to the root of Qt distribution. (For example: /opt/qt/Qt5/5.13.1/gcc_64). If empty, system distribution is considered.")
add_qt5_to_cmake_prefix_path("${QT_PREFIX_PATH}")

# Sanitizers are available for Clang and gcc on 64 bit , non Windows architecture
if( ( (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") ) AND (${CMAKE_SIZEOF_VOID_P} EQUAL 8) AND (NOT WIN32) )
  option(SANITIZER_ENABLE_ADDRESS "Enable address sanitizer" OFF)
  option(SANITIZER_ENABLE_LEAK "Enable leak sanitizer" OFF)
  option(SANITIZER_ENABLE_UNDEFINED "Enable undefined sanitizer" OFF)
  option(SANITIZER_ENABLE_THREAD "Enable thread sanitizer (can be incompatible with other sanitizers)" OFF)
endif()

option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(WARNING_AS_ERROR "Threat warnings as errors" ON)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel Custom)
option(BUILD_DESIGNER_PLUGIN "Build the plugin for Qt Designer" ON)
option(BUILD_TESTS "Build the tests" ON)


set(SANITIZER_OPTIONS)
if(SANITIZER_ENABLE_ADDRESS)
  list(APPEND SANITIZER_OPTIONS "-fsanitize=address")
#   set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
endif()
if(SANITIZER_ENABLE_LEAK)
  list(APPEND SANITIZER_OPTIONS "-fsanitize=leak")
#   set(CMAKE_CXX_FLAGS "-fsanitize=leak ${CMAKE_CXX_FLAGS}")
endif()
if(SANITIZER_ENABLE_UNDEFINED)
  list(APPEND SANITIZER_OPTIONS "-fsanitize=undefined")
#   set(CMAKE_CXX_FLAGS "-fsanitize=undefined ${CMAKE_CXX_FLAGS}")
endif()
if(SANITIZER_ENABLE_THREAD)
  list(APPEND SANITIZER_OPTIONS "-fsanitize=thread")
#   set(CMAKE_CXX_FLAGS "-fsanitize=thread ${CMAKE_CXX_FLAGS}")
endif()


# Custom build
#
# CMake provides some buid type (CMAKE_BUILD_TYPE): Debug Release RelWithDebInfo MinSizeRel
# For some cases, it can be useful to have other combinations,
# for example debug build (debug symbols and assertions) with optimizations.

if(MSVC)
 set(AVAILABLE_OPTIMIZATION_LEVELS "/O0" "/O1" "/O2" "/Os")
else()
  set(AVAILABLE_OPTIMIZATION_LEVELS "-O0" "-O1" "-O2" "-O3" "-Os")
endif()

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Custom" )
  option(CUSTOM_BUILD_TYPE_USE_DEBUG_SYMBOLS "Add debug symbols (-g on Gcc/Clang, /DEBUG on MSVC)" ON)
  option(CUSTOM_BUILD_TYPE_DEFINE_NDEBUG "Set -DNDEBUG definition (will disable assert)" OFF)
  set(CUSTOM_BUILD_TYPE_OPTIMIZATION_LEVEL "3" CACHE STRING "Set optimization level")
  set_property(CACHE CUSTOM_BUILD_TYPE_OPTIMIZATION_LEVEL PROPERTY STRINGS ${AVAILABLE_OPTIMIZATION_LEVELS})
else()
  unset(CUSTOM_BUILD_TYPE_USE_DEBUG_SYMBOLS CACHE)
  unset(CUSTOM_BUILD_TYPE_DEFINE_NDEBUG CACHE)
  unset(CUSTOM_BUILD_TYPE_OPTIMIZATION_LEVEL CACHE)
endif()

set(CUSTOM_BUILD_TYPE_OPTIONS)
if(MSVC)
  if(CUSTOM_BUILD_TYPE_USE_DEBUG_SYMBOLS)
    list(APPEND CUSTOM_BUILD_TYPE_OPTIONS "/DEBUG")
  endif()
else()
  if(CUSTOM_BUILD_TYPE_USE_DEBUG_SYMBOLS)
    list(APPEND CUSTOM_BUILD_TYPE_OPTIONS "-g")
  endif()
endif()
list(APPEND CUSTOM_BUILD_TYPE_OPTIONS ${CUSTOM_BUILD_TYPE_OPTIMIZATION_LEVEL})

set(CUSTOM_BUILD_TYPE_DEFINITIONS)
if(CUSTOM_BUILD_TYPE_DEFINE_NDEBUG)
  list(APPEND CUSTOM_BUILD_TYPE_DEFINITIONS "NDEBUG")
endif()

# Provide LPO/LTO option if supported
# Note: CMake before 3.9 does only support Intel compiler on Linux.
#       Check documentation of the CheckIPOSupported module,
#       and also CMP0069 policy.
include(CheckIPOSupported)
check_ipo_supported(RESULT HAVE_IPO_LTO)
if(HAVE_IPO_LTO)
  option(BUILD_USE_IPO_LTO "Use link-time optimization" ON)
endif()


# TODO Interface Target


# TODO must use:
# if(SANITIZER_OPTIONS)
#   target_compile_options(target, BEFORE PRIVATE ${SANITIZER_OPTIONS})
# endif()

# TODO Provide config package files

if(MSVC)
  set(WARNING_OPTIONS "/W4" "/WX")
else()
  set(WARNING_OPTIONS "-Wall" "-Wextra")
  if(WARNING_AS_ERROR)
    list(APPEND WARNING_OPTIONS "-Werror")
  endif()
endif()

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# if(WARNING_AS_ERROR)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
# endif()

set(QT_NO_CAST_DEFINITIONS QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_BYTEARRAY)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

# TODO must use target_compile_definitions(target PRIVATE ${QT_NO_CAST_DEFINITIONS}) , else it will propagate to the uer of the library
# add_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII -DQT_NO_CAST_FROM_BYTEARRAY)

add_library(BuildSpecifications INTERFACE)
if(SANITIZER_OPTIONS)
  target_compile_options(BuildSpecifications BEFORE INTERFACE ${SANITIZER_OPTIONS})
endif()
target_compile_options(BuildSpecifications INTERFACE ${WARNING_OPTIONS})
if(CUSTOM_BUILD_TYPE_OPTIONS)
  target_compile_options(BuildSpecifications INTERFACE ${CUSTOM_BUILD_TYPE_OPTIONS})
endif()
target_compile_definitions(BuildSpecifications INTERFACE ${QT_NO_CAST_DEFINITIONS})
if(CUSTOM_BUILD_TYPE_DEFINITIONS)
  target_compile_definitions(BuildSpecifications INTERFACE ${CUSTOM_BUILD_TYPE_DEFINITIONS})
endif()


find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

if(BUILD_TESTS)
  find_package(Qt5 COMPONENTS Test REQUIRED)
  enable_testing()
endif()

add_subdirectory(Led_Widgets)

if(BUILD_DESIGNER_PLUGIN)
  find_package(Qt5 COMPONENTS Designer REQUIRED)
  add_subdirectory(Led_Designer)
endif()
