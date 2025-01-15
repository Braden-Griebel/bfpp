add_library(bf interpreter.h interpreter.cpp parser.h parser.cpp instructions.h)

target_include_directories(bf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
