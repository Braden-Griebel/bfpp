
#include <variant>

struct ShiftRight {
  int count;
};

struct ShiftLeft {
  int count;
};

struct Increment {
  int count;
};

struct Decrement {
  int count;
};

struct Output {};

struct Input {};

struct LeftBracket {
  int target;
};

struct RightBracket {
  int target;
};

using Instruction = std::variant<ShiftRight, ShiftLeft, Increment, Decrement,
                                 Output, Input, LeftBracket, RightBracket>;
