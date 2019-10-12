
cmake_minimum_required(VERSION 3.10)

project(MdtLedTest)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(MdtLed REQUIRED)

enable_testing()

add_executable(MdtLedTestPackage src/MdtLedTestPackage.cpp)
target_link_libraries(MdtLedTestPackage Qt5::Widgets MdtLed)
add_test(NAME mdtLedTestPackage COMMAND MdtLedTestPackage)
