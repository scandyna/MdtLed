
# TODO Should use exports with -fvisibility=hidden etc..
#      For tests, create a shared library that also compiles sources
#      if access to implementation details must be accessed.

add_executable(LedTest src/LedTest.cpp)
target_link_libraries(LedTest PRIVATE BuildSpecifications Mdt::Led Qt5::Test)
add_test(NAME ledTest COMMAND LedTest)

message("LedTest CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
