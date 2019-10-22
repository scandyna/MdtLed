
add_executable(LedTest src/LedTest.cpp)
target_link_libraries(LedTest PRIVATE BuildSpecifications Mdt0::Led Qt5::Test)
add_test(NAME ledTest COMMAND LedTest)

message("LedTest CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
