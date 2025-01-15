#include "interpreter.h"
#include <variant>

void Interpreter::run() {
  if ((this->instruction_vector).size() < 1) {
    return; // no instructions, so return early
  }
  // While there are instructions to process, run the vm
  while ((this->instruction_pointer) < (this->instruction_vector).size()) {
    auto current_instruction =
        (this->instruction_vector).at(instruction_pointer);
    // Cases for each instruction
    if (std::holds_alternative<Increment>(current_instruction)) {
      (this->data_array).at(this->data_pointer) +=
          std::get<Increment>(current_instruction).count;

    } else if (std::holds_alternative<Decrement>(current_instruction)) {
      (this->data_array).at(this->data_pointer) -=
          std::get<Decrement>(current_instruction).count;
    } else if (std::holds_alternative<ShiftRight>(current_instruction)) {
      (this->data_pointer) += std::get<ShiftRight>(current_instruction).count;
    } else if (std::holds_alternative<ShiftLeft>(current_instruction)) {
      (this->data_pointer) -= std::get<ShiftLeft>(current_instruction).count;
    } else if (std::holds_alternative<Output>(current_instruction)) {
      std::cout << static_cast<char>((this->data_array).at(this->data_pointer));
    } else if (std::holds_alternative<Input>(current_instruction)) {
      char in = std::cin.get();
    } else if (std::holds_alternative<JumpForward>(current_instruction)) {
      if ((this->data_array).at(this->data_pointer) == 0) {
        this->instruction_pointer =
            std::get<JumpForward>(current_instruction).target;
      }
    } else if (std::holds_alternative<JumpBackward>(current_instruction)) {
      if ((this->data_array).at(this->data_pointer) != 0) {
        this->instruction_pointer =
            std::get<JumpBackward>(current_instruction).target;
      }
    }
    ++(this->instruction_pointer);
  }
}
