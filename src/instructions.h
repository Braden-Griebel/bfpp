#pragma once
#include <variant>

struct ShiftRight {
  int count;
  ShiftRight(int in_count) : count(in_count) {};
};

struct ShiftLeft {
  int count;
  ShiftLeft(int in_count) : count(in_count) {};
};

struct Increment {
  int count;
  Increment(int in_count) : count(in_count) {};
};

struct Decrement {
  int count;
  Decrement(int in_count) : count(in_count) {};
};

struct Output {};

struct Input {};

struct JumpForward {
  int target;
  JumpForward() : target(0) {};
};

struct JumpBackward {
  int target;
  JumpBackward() : target(0) {};
};

using Instruction = std::variant<ShiftRight, ShiftLeft, Increment, Decrement,
                                 Output, Input, JumpForward, JumpBackward>;
