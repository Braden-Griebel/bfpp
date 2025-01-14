cmake_minimum_required(VERSION 3.24...3.31)

project(Bfpp VERSION 0.1 DESCRIPTION "Brainfuck interpreter written in c++" LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  cli11_proj
  QUIET
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.3.2
)

FetchContent_MakeAvailable(cli11_proj)

add_executable(bfpp bfpp.cpp)
target_link_libraries(bfpp PRIVATE CLI11::CLI11)
