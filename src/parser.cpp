#include "parser.h"
#include <variant>

std::vector<Instruction> Parser::parse() {
  while (!is_at_end()) {
    auto cur_symbol = (this->source).at(this->current);
    switch (cur_symbol) {
    case '>':
      (this->instructions).push_back(ShiftRight{gulp('>')});
      break;
    case '<':
      (this->instructions).push_back(ShiftLeft{gulp('<')});
      break;
    case '+':
      (this->instructions).push_back(Increment{gulp('+')});
      break;
    case '-':
      (this->instructions).push_back(Decrement{gulp('-')});
      break;
    case '[':
      (this->instructions).push_back(JumpForward{});
      ++(this->current);
      break;
    case ']':
      (this->instructions).push_back(JumpBackward{});
      ++(this->current);
      break;
    case '.':
      (this->instructions).push_back(Output{});
      ++(this->current);
      break;
    case ',':
      (this->instructions).push_back(Input{});
      ++(this->current);
      break;
    default:
      ++(this->current);
    }
  }
  // Connect the jump characters
  this->match_jumps();
  // Get a copy of the instructions to return, then set instructions property to
  // an empty vector
  auto return_instructions = this->instructions;
  this->instructions = std::vector<Instruction>{};
  return return_instructions;
}

int Parser::gulp(const char symbol) {
  int count = 0;
  while (!is_at_end()) {
    auto cur_symbol = source.at(current);
    if (cur_symbol == symbol) {
      ++count;
      ++(this->current);
      continue;
    }
    switch (source.at(current)) {
    case '>':
    case '<':
    case '+':
    case '-':
    case '[':
    case ']':
    case '.':
    case ',':
      return count;
    default:
      ++(this->current);
    }
  }
  return count;
}

/*! @brief Check if the full source code has been processed.
 */
bool Parser::is_at_end() {
  if (this->current >= (this->source).length()) {
    return true;
  }
  return false;
}

/*! @brief Connect matching jump operations in instructions together
 */
void Parser::match_jumps() {
  // Create a deque to store jumps when encountered
  auto jumps = std::deque<int>{};
  auto current_position = 0;
  // Starting from the beggining of the instructions, start stepping through
  while (current_position < (this->instructions).size()) {
    auto current_instruction = (this->instructions).at(current_position);
    if (std::holds_alternative<JumpForward>(current_instruction)) {
      jumps.push_back(current_position);
    } else if (std::holds_alternative<JumpBackward>(current_instruction)) {
      // Ensure the jump queue is not empty
      if (!(jumps.size() > 0)) {
        throw ParseError{"Unmatched right bracket",
                         ParseErrorType::unmatched_jump};
      }
      // Get the matching jump position
      int matching_jump = jumps.back();
      jumps.pop_back();
      // Connect the two jumps together
      std::get<JumpBackward>((this->instructions).at(current_position)).target =
          matching_jump;
      std::get<JumpForward>((this->instructions).at(matching_jump)).target =
          current_position;
    }
    ++current_position;
  }
  // If there are any remaining jumps in the queue, there is an unmatched jump
  // in the source
  if (jumps.size() > 0) {
    throw ParseError{"Unmatched left bracket", ParseErrorType::unmatched_jump};
  }
}
