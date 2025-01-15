#include <array>
#include <cstddef>
#include <iostream>
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
  Interpreter(std::vector<Instruction> instructions)
      : instruction_vector(instructions), instruction_pointer(0),
        data_pointer(0) {};
  /*! @brief Run the VM and interpret the brainfuck program.
   */
  void run();
};
