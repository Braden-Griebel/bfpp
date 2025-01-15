#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#include <CLI/CLI.hpp>

#include "interpreter.h"
#include "parser.h"

int main(int argc, char **argv) {
  CLI::App app{"Brainfuck++"};

  // Set up options
  // Only option currently is just a file to interpret
  std::optional<std::string> in_file;
  app.add_option(
         "file", in_file,
         "Path to file to intepret, will read from stdin if not provided")
      ->check(CLI::ExistingFile);

  // Read in source from file if file argument passed, otherwise try stdin
  std::string input_string;
  std::string file_buffer;
  if (in_file.has_value()) {
    std::ifstream input_file_stream{in_file.value()};

    while (std::getline(input_file_stream, file_buffer)) {
      input_string += file_buffer;
    }
  } else {
    while (std::getline(std::cin, file_buffer)) {
      input_string += file_buffer;
    }
  }

  //std::cout<<input_string;

  // Create the parser
  auto bf_parser = Parser{input_string};
  // Parse the input into instructions
  auto instructions = bf_parser.parse();

  // Load the instructions into the interpreter
  auto bf_interpreter = Interpreter{instructions};
  bf_interpreter.run();

  return EXIT_SUCCESS;
}
