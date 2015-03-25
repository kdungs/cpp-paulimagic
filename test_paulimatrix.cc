#include "paulimatrix.h"

#include <cassert>
#include <sstream>
#include <string>

auto test_ostreamOperator() -> void {
  auto ss = std::stringstream{};
  ss << PauliMatrix::X;
  ss << PauliMatrix::Y;
  ss << PauliMatrix::Z;

  assert(ss.str() == std::string{"XYZ"});
}

int main() {
  test_ostreamOperator();
}
