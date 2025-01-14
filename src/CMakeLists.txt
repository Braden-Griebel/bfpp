add_library(bf interpreter.h interpreter.cpp parser.h parser.cpp)

target_include_directories(bf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
