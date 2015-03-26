#include "paulimagic/paulimatrix.h"

#include <cassert>
#include <sstream>
#include <string>

#include <iostream>

auto test_equalityOperator() -> void {
  assert(PM::I == PM::I);
  assert(PM::X == PM::X);
  assert(PM::Y == PM::Y);
  assert(PM::Z == PM::Z);
}

auto test_inequalityOperator() -> void {
  assert(PM::I != PM::X);
  assert(PM::I != PM::Y);
  assert(PM::I != PM::Z);
  assert(PM::X != PM::I);
  assert(PM::X != PM::Y);
  assert(PM::X != PM::Z);
  assert(PM::Y != PM::I);
  assert(PM::Y != PM::X);
  assert(PM::Y != PM::Z);
  assert(PM::Z != PM::I);
  assert(PM::Z != PM::X);
  assert(PM::Z != PM::Y);
}

auto test_multiplicationOperator() -> void {
  assert(PM::X * PM::Y * PM::Z == PM::iI);
}

auto test_ostreamOperator() -> void {
  std::stringstream ss;
  ss << PM::I << PM::X << PM::Y << PM::Z << PM::nI << PM::nX << PM::nY << PM::nZ
     << PM::iI << PM::iX << PM::iY << PM::iZ << PM::niI << PM::niX << PM::niY
     << PM::niZ;
  assert(ss.str() == std::string{"+𝟙+X+Y+Z-𝟙-X-Y-Zi𝟙iXiYiZ-i𝟙-iX-iY-iZ"});
}

int main() {
  test_equalityOperator();
  test_inequalityOperator();
  test_multiplicationOperator();
  test_ostreamOperator();
}
