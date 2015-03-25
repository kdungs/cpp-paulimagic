#include "expression.h"

#include <cassert>
#include <sstream>
#include <string>

#include <iostream>

auto test_isPositive() -> void {}
auto test_isReal() -> void {}
auto test_isIdentity() -> void {}

auto test_multiplicationOperator() -> void {
  auto left = Expression{PauliMatrix::Y, PauliMatrix::Z};
  auto right = Expression{PauliMatrix::Y, PauliMatrix::Z};

  std::cout << left*right << '\n';
}

auto test_ostreamOperator() -> void {}

int main() {
  test_isPositive();
  test_isReal();
  test_isIdentity();

  test_multiplicationOperator();
}
