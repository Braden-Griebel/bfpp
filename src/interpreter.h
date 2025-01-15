#pragma once
#include <array>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

#include "instructions.h"

/*! @brief VM interpreter for brainfuck.
 *
 * Takes a vector of instructions, and creates a empty data array, then runs the
 * instructions.
 */
class Interpreter {
  /*! @brief The data array, made of 30,000 bytes
   */
  std::array<unsigned char, 30000> data_array;
  /*! @brief Instructions to executed by the VM.
   */
  std::vector<Instruction> instruction_vector;
  /*! @brief current position in the data_array.
   */
  int data_pointer;
  /*! @brief current position in the instruction_vector.
   */
  int instruction_pointer;

public:
  /*! @brief Construct a interpreter from a vector of instructions.
   */
  explicit Interpreter(std::vector<Instruction> instructions)
      : data_array(), instruction_vector(std::move(instructions)),
        data_pointer(0), instruction_pointer(0) {};
  /*! @brief Run the VM and interpret the brainfuck program.
   */
  void run();
  // Functions intended mainly for testing
  [[nodiscard]] int get_data_pointer() const {return this->data_pointer;};
  [[nodiscard]] int get_instruction_pointer() const {return this->instruction_pointer;};
  [[nodiscard]] unsigned char get_data_at(const int position) const{return (this->data_array).at(position);};

};
