#include "catch2/catch_test_macros.hpp"

#include "instructions.h"
#include "interpreter.h"
#include "parser.h"
#include <variant>

TEST_CASE("Brainfuck++ can parse Brainfuck", "[parser]")
 {
  SECTION("Brainfuck++ can parse (repeated) +") {
    std::string plus1 = "+";
    std::string plus2 = "++";
    std::string plus4 = "++++";

    auto parse_plus1 = Parser{plus1};
    auto parse_plus2 = Parser{plus2};
    auto parse_plus4 = Parser{plus4};

    auto plus1_instructions = parse_plus1.parse();
    auto plus2_instructions = parse_plus2.parse();
    auto plus4_instructions = parse_plus4.parse();

    CHECK(plus1_instructions.size() == 1);
    CHECK(plus2_instructions.size() == 1);
    CHECK(plus4_instructions.size() == 1);

    CHECK(std::get<Increment>(plus1_instructions.at(0)).count == 1);
    CHECK(std::get<Increment>(plus2_instructions.at(0)).count == 2);
    CHECK(std::get<Increment>(plus4_instructions.at(0)).count == 4);
  }

  SECTION("Brainfuck++ can parse (repeated) -") {
    std::string minus1 = "-";
    std::string minus2 = "--";
    std::string minus4 = "----";

    auto parse_minus1 = Parser{minus1};
    auto parse_minus2 = Parser{minus2};
    auto parse_minus4 = Parser{minus4};

    auto minus1_instructions = parse_minus1.parse();
    auto minus2_instructions = parse_minus2.parse();
    auto minus4_instructions = parse_minus4.parse();

    CHECK(minus1_instructions.size() == 1);
    CHECK(minus2_instructions.size() == 1);
    CHECK(minus4_instructions.size() == 1);

    CHECK(std::get<Decrement>(minus1_instructions.at(0)).count == 1);
    CHECK(std::get<Decrement>(minus2_instructions.at(0)).count == 2);
    CHECK(std::get<Decrement>(minus4_instructions.at(0)).count == 4);
  }

  SECTION("Brainfuck++ can parse (repeated) >") {
    std::string right_shift1 = ">";
    std::string right_shift2 = ">>";
    std::string right_shift4 = ">>>>";

    auto parse_right_shift1 = Parser{right_shift1};
    auto parse_right_shift2 = Parser{right_shift2};
    auto parse_right_shift4 = Parser{right_shift4};

    auto right_shift1_instructions = parse_right_shift1.parse();
    auto right_shift2_instructions = parse_right_shift2.parse();
    auto right_shift4_instructions = parse_right_shift4.parse();

    CHECK(right_shift1_instructions.size() == 1);
    CHECK(right_shift2_instructions.size() == 1);
    CHECK(right_shift4_instructions.size() == 1);

    CHECK(std::get<ShiftRight>(right_shift1_instructions.at(0)).count == 1);
    CHECK(std::get<ShiftRight>(right_shift2_instructions.at(0)).count == 2);
    CHECK(std::get<ShiftRight>(right_shift4_instructions.at(0)).count == 4);
  }

  SECTION("Brainfuck++ can parse (repeated) <") {
    std::string left_shift1 = "<";
    std::string left_shift2 = "<<";
    std::string left_shift4 = "<<<<";

    auto parse_left_shift1 = Parser{left_shift1};
    auto parse_left_shift2 = Parser{left_shift2};
    auto parse_left_shift4 = Parser{left_shift4};

    auto left_shift1_instructions = parse_left_shift1.parse();
    auto left_shift2_instructions = parse_left_shift2.parse();
    auto left_shift4_instructions = parse_left_shift4.parse();

    CHECK(left_shift1_instructions.size() == 1);
    CHECK(left_shift2_instructions.size() == 1);
    CHECK(left_shift4_instructions.size() == 1);

    CHECK(std::get<ShiftLeft>(left_shift1_instructions.at(0)).count == 1);
    CHECK(std::get<ShiftLeft>(left_shift2_instructions.at(0)).count == 2);
    CHECK(std::get<ShiftLeft>(left_shift4_instructions.at(0)).count == 4);
  }

  SECTION("Brainfuck++ can parse ."){
    auto parse_period = Parser{"."};

    auto period_instructions = parse_period.parse();

    CHECK(period_instructions.size() == 1);

    CHECK(std::holds_alternative<Output>(period_instructions.at(0)));
  }

  SECTION("Brainfuck++ can parse ,"){
    auto parse_comma = Parser{","};

    auto comma_instructions = parse_comma.parse();

    CHECK(comma_instructions.size() == 1);

    CHECK(std::holds_alternative<Input>(comma_instructions.at(0)));
  }

  SECTION("Brainfuck++ can parse []"){
    auto parse_bracket = Parser{"[]"};

    auto bracket_instructions = parse_bracket.parse();

    CHECK(bracket_instructions.size() == 2);

    CHECK(std::holds_alternative<JumpForward>(bracket_instructions.at(0)));
    CHECK(std::holds_alternative<JumpBackward>(bracket_instructions.at(1)));

    CHECK(std::get<JumpForward>(bracket_instructions.at(0)).target == 1);
    CHECK(std::get<JumpBackward>(bracket_instructions.at(1)).target == 0);
  }

  SECTION("Brainfuck++ can parse a combination of symbold"){
    auto parser = Parser{"+++---->><<>[+++],."};

    auto instructions = parser.parse();

    CHECK(instructions.size() == 10);

    CHECK(std::holds_alternative<Increment>(instructions.at(0)));
    CHECK(std::holds_alternative<Decrement>(instructions.at(1)));
    CHECK(std::holds_alternative<ShiftRight>(instructions.at(2)));
    CHECK(std::holds_alternative<ShiftLeft>(instructions.at(3)));
    CHECK(std::holds_alternative<ShiftRight>(instructions.at(4)));
    CHECK(std::holds_alternative<JumpForward>(instructions.at(5)));
    CHECK(std::holds_alternative<Increment>(instructions.at(6)));
    CHECK(std::holds_alternative<JumpBackward>(instructions.at(7)));
    CHECK(std::holds_alternative<Input>(instructions.at(8)));
    CHECK(std::holds_alternative<Output>(instructions.at(9)));
  }
}

TEST_CASE("Brainfuck++ can interpret Brainfuck")
{
  SECTION("Brainfuck++ can interpret (repeated) +"){
    auto source = "++++";

    auto parser = Parser{source};

    auto interpreter = Interpreter {parser.parse()};

    interpreter.run();

    // The first cell in the data array should have been incremented 4 times
    CHECK(static_cast<int>(interpreter.get_data_at(0))==4);
    // Instruction pointer should have stepped past the end of the instructions
    CHECK(interpreter.get_instruction_pointer() == 1);
    // Data pointer should still be at 0
    CHECK(interpreter.get_data_pointer()==0);
  }

  SECTION("Brainfuck++ can interpret (repeated) -"){
    auto source = "++++--";

    auto parser = Parser{source};

    auto interpreter = Interpreter {parser.parse()};

    interpreter.run();

    // The first cell in the data array should have been incremented 4 times
    CHECK(static_cast<int>(interpreter.get_data_at(0))==2);
    // Instruction pointer should have stepped past the end of the instructions
    CHECK(interpreter.get_instruction_pointer() == 2);
    // Data pointer should still be at 0
    CHECK(interpreter.get_data_pointer()==0);
  }

  SECTION("Brainfuck++ can interpret (repeated) >"){
    auto source = ">>>>";

    auto parser = Parser{source};

    auto interpreter = Interpreter {parser.parse()};

    interpreter.run();

    // The first cells should still be 0
    CHECK(static_cast<int>(interpreter.get_data_at(1))==0);
    CHECK(static_cast<int>(interpreter.get_data_at(0))==0);
    CHECK(static_cast<int>(interpreter.get_data_at(2))==0);
    CHECK(static_cast<int>(interpreter.get_data_at(3))==0);
    // Instruction pointer should have stepped past the end of the instructions
    CHECK(interpreter.get_instruction_pointer() == 1);
    // Data pointer should have moved to 4
    CHECK(interpreter.get_data_pointer()==4);
  }

  SECTION("Brainfuck++ can interpret (repeated) <"){
    auto source = ">>>>>>>><<<";

    auto parser = Parser{source};

    auto interpreter = Interpreter {parser.parse()};

    interpreter.run();

    // Instruction pointer should have stepped past the end of the instructions
    CHECK(interpreter.get_instruction_pointer() == 2);
    // Data pointer should have moved to 4
    CHECK(interpreter.get_data_pointer()==5);
  }

  SECTION("Brainfuck++ can interpret skipped []"){
    auto source = "[++++]";

    auto parser = Parser{source};

    auto interpreter = Interpreter {parser.parse()};

    interpreter.run();

    // The first cell in the data array should be 0
    CHECK(interpreter.get_data_at(0)==0);
    // Instruction pointer should have stepped past the end of the instructions
    CHECK(interpreter.get_instruction_pointer() == 3);
    // Data pointer should have moved to 4
    CHECK(interpreter.get_data_pointer()==0);
  }

  SECTION("Brainfuck++ can interpret non-skipped []"){
    auto source = "+[>++++<-]";

    auto parser = Parser{source};

    auto interpreter = Interpreter {parser.parse()};

    interpreter.run();

    /*The data in the first cell should have been returned to 0,
    and the second ell should have been incremented to 4*/
    CHECK(static_cast<int>(interpreter.get_data_at(0))==0);
    CHECK(static_cast<int>(interpreter.get_data_at(1))==4);
    // Instruction pointer should have stepped past the end of the instructions
    CHECK(interpreter.get_instruction_pointer() == 7);
    // Data pointer should have moved back to 0
    CHECK(interpreter.get_data_pointer()==0);
  }
}
