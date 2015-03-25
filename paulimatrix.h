#pragma once

#include <cassert>
#include <ostream>

enum class PauliMatrix { X, Y, Z };

auto isPermutation(PauliMatrix a, PauliMatrix b, PauliMatrix c) noexcept
    -> bool {
  return a != b && a != c && b != c;
}

auto isCyclic(PauliMatrix a, PauliMatrix b, PauliMatrix c) noexcept -> bool {
  assert(isPermutation(a, b, c));
  return (a == PauliMatrix::X && b == PauliMatrix::Y) ||
         (b == PauliMatrix::X && c == PauliMatrix::Y) ||
         (c == PauliMatrix::X && a == PauliMatrix::Y);
}

auto isAcyclic(PauliMatrix a, PauliMatrix b, PauliMatrix c) noexcept -> bool {
  assert(isPermutation(a, b, c));
  return (a == PauliMatrix::X && b == PauliMatrix::Z) ||
         (b == PauliMatrix::X && c == PauliMatrix::Z) ||
         (c == PauliMatrix::X && a == PauliMatrix::Z);
}

auto operator<<(std::ostream& os, PauliMatrix m) -> std::ostream & {
  switch (m) {
    case PauliMatrix::X:
      os << 'X';
      break;
    case PauliMatrix::Y:
      os << 'Y';
      break;
    case PauliMatrix::Z:
      os << 'Z';
      break;
    default:
      assert(false);  // This should never happen!
  }
  return os;
}
