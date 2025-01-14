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
};
