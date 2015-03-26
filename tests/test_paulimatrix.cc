#include "paulimagic/paulimatrix.h"

#include <cassert>
#include <sstream>
#include <string>

auto test_isPermutation() -> void {
  assert(isPermutation(PauliMatrix::X, PauliMatrix::Y, PauliMatrix::Z));
  assert(!isPermutation(PauliMatrix::X, PauliMatrix::X, PauliMatrix::Z));
}

auto test_isCyclic() -> void {
  assert(isCyclic(PauliMatrix::X, PauliMatrix::Y, PauliMatrix::Z));
  assert(isCyclic(PauliMatrix::Y, PauliMatrix::Z, PauliMatrix::X));
  assert(isCyclic(PauliMatrix::Z, PauliMatrix::X, PauliMatrix::Y));

  assert(!isCyclic(PauliMatrix::X, PauliMatrix::Z, PauliMatrix::Y));
  assert(!isCyclic(PauliMatrix::Y, PauliMatrix::X, PauliMatrix::Z));
  assert(!isCyclic(PauliMatrix::Z, PauliMatrix::Y, PauliMatrix::X));
}

auto test_isAcyclic() -> void {
  assert(isAcyclic(PauliMatrix::X, PauliMatrix::Z, PauliMatrix::Y));
  assert(isAcyclic(PauliMatrix::Y, PauliMatrix::X, PauliMatrix::Z));
  assert(isAcyclic(PauliMatrix::Z, PauliMatrix::Y, PauliMatrix::X));

  assert(!isAcyclic(PauliMatrix::X, PauliMatrix::Y, PauliMatrix::Z));
  assert(!isAcyclic(PauliMatrix::Y, PauliMatrix::Z, PauliMatrix::X));
  assert(!isAcyclic(PauliMatrix::Z, PauliMatrix::X, PauliMatrix::Y));
}

auto test_ostreamOperator() -> void {
  std::stringstream ss;
  ss << PauliMatrix::X;
  ss << PauliMatrix::Y;
  ss << PauliMatrix::Z;

  assert(ss.str() == std::string{"XYZ"});
}

int main() {
  test_isPermutation();
  test_isCyclic();
  test_isAcyclic();
  test_ostreamOperator();
}
