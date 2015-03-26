#include "prefix.h"

#include <cassert>
#include <sstream>
#include <string>

auto test_isPositive() -> void {
  assert(isPositive(Prefix::Pos1));
  assert(!isPositive(Prefix::Neg1));
  assert(isPositive(Prefix::PosI));
  assert(!isPositive(Prefix::NegI));
}
auto test_isReal() -> void {
  assert(isReal(Prefix::Pos1));
  assert(isReal(Prefix::Neg1));
  assert(!isReal(Prefix::PosI));
  assert(!isReal(Prefix::NegI));
}

auto test_negationOperator() -> void {
  assert(-Prefix::Pos1 == Prefix::Neg1);
  assert(-Prefix::Neg1 == Prefix::Pos1);
  assert(-Prefix::PosI == Prefix::NegI);
  assert(-Prefix::NegI == Prefix::PosI);
}

auto test_timesI() -> void {
  assert(timesI(Prefix::Pos1) == Prefix::PosI);
  assert(timesI(Prefix::Neg1) == Prefix::NegI);
  assert(timesI(Prefix::PosI) == Prefix::NegI);
  assert(timesI(Prefix::NegI) == Prefix::PosI);
}

auto test_multiplicationOperator() -> void {
  // +1 * x
  assert(Prefix::Pos1 * Prefix::Pos1 == Prefix::Pos1);
  assert(Prefix::Pos1 * Prefix::Neg1 == Prefix::Neg1);
  assert(Prefix::Pos1 * Prefix::PosI == Prefix::PosI);
  assert(Prefix::Pos1 * Prefix::NegI == Prefix::NegI);
  // -1 * x
  assert(Prefix::Neg1 * Prefix::Pos1 == Prefix::Neg1);
  assert(Prefix::Neg1 * Prefix::Neg1 == Prefix::Pos1);
  assert(Prefix::Neg1 * Prefix::PosI == Prefix::NegI);
  assert(Prefix::Neg1 * Prefix::NegI == Prefix::PosI);
  // +i * x
  assert(Prefix::PosI * Prefix::Pos1 == Prefix::PosI);
  assert(Prefix::PosI * Prefix::Neg1 == Prefix::NegI);
  assert(Prefix::PosI * Prefix::PosI == Prefix::Neg1);
  assert(Prefix::PosI * Prefix::NegI == Prefix::Pos1);
  // -i * x
  assert(Prefix::NegI * Prefix::Pos1 == Prefix::NegI);
  assert(Prefix::NegI * Prefix::Neg1 == Prefix::PosI);
  assert(Prefix::NegI * Prefix::PosI == Prefix::Pos1);
  assert(Prefix::NegI * Prefix::NegI == Prefix::Neg1);
}

auto test_ostreamOperator() -> void {
  std::stringstream ss;
  ss << Prefix::Pos1 << ',';
  ss << Prefix::Neg1 << ',';
  ss << Prefix::PosI << ',';
  ss << Prefix::NegI;

  assert(ss.str() == std::string{"+,-,i,-i"});
}

int main() {
  test_isPositive();
  test_isReal();
  test_negationOperator();
  test_multiplicationOperator();
  test_ostreamOperator();
}
