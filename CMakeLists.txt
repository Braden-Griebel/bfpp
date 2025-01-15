cmake_minimum_required(VERSION 3.24...3.31)

project(Bfpp VERSION 0.1 DESCRIPTION "Brainfuck interpreter written in c++" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  cli11_proj
  QUIET
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.3.2
)

FetchContent_MakeAvailable(cli11_proj)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

add_subdirectory(src)

add_executable(bfpp bfpp.cpp)
target_link_libraries(bfpp PRIVATE CLI11::CLI11)
target_link_libraries(bfpp PRIVATE bf)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
