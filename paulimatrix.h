#pragma once

#include <cassert>
#include <ostream>

enum class PauliMatrix { X, Y, Z };

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
