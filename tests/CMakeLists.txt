# Get Catch2

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test_bfpp.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain bf)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}.extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)
