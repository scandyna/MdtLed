
add_library(MdtLed Mdt/Led.cpp)
target_link_libraries(
 MdtLed
  PUBLIC
    Qt5::Widgets
  PRIVATE
    BuildSpecifications
)
if(BUILD_USE_IPO_LTO)
  set_property(TARGET MdtLed PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()


message("Led CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("Led CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message("Led CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message("Led CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")



