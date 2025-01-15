#include <deque>
#include <exception>
#include <string>
#include <vector>

#include "instructions.h"

/*! @brief Parse source code into instructions
 */
class Parser {
  /*! @brief Source code being parsed*/
  std::string source;
  /*! @brief Current position in source code*/
  int current;
  /*! @brief Parsed instructions*/
  std::vector<Instruction> instructions;

  /*! @brief Read a group of symbols from source.
   *
   * Read from the source until encountering a character other than 'symbol',
   * used for grouping characters.
   */
  int gulp(char symbol);
  /*! @brief Match [] characters so they can be jumped between.
   *
   * Sets the `target` value for all the Jump instructions
   * @param symbol symbol to gulp
   * @returns number of characters matching `symbol` which were passed.
   */
  void match_jumps();

  /*! @brief check whether full source code has been processed.
   * @returns true if current is past end of the source code, and false
   * otherwise.
   */
  bool is_at_end();

public:
  /*! @brief construct parser from source code*/
  Parser(std::string source_code) : source(source_code), current(0) {};
  std::vector<Instruction> parse();
};

enum ParseErrorType { unmatched_jump };

class ParseError : public std::exception {
public:
  std::string message;
  std::string full_message;
  ParseErrorType error_type;
  ParseError(std::string message, ParseErrorType error_type)
      : message(message), error_type(error_type) {};
  const char *what() {
    switch (this->error_type) {
    case ParseErrorType::unmatched_jump:
      (this->full_message) =
          "Unmatched Jump found during parsing: " + (this->message);
      break;
    }
    return (this->full_message).c_str();
  }
};
