#pragma once

#include <cassert>
#include <ostream>

enum class Prefix { Pos1, Neg1, PosI, NegI };

auto operator-(Prefix p) -> Prefix {
  switch (p) {
    case Prefix::Pos1:
      return Prefix::Neg1;
    case Prefix::Neg1:
      return Prefix::Pos1;
    case Prefix::PosI:
      return Prefix::NegI;
    case Prefix::NegI:
      return Prefix::PosI;
    default:
      assert(false);
  }
};

auto isPositive(Prefix p) noexcept -> bool {
  return p == Prefix::Pos1 || p == Prefix::PosI;
}

auto isReal(Prefix p) noexcept -> bool {
  return p == Prefix::Pos1 || p == Prefix::Neg1;
}

auto timesI(Prefix p) noexcept -> Prefix {
  switch (p) {
    case Prefix::Pos1:
      return Prefix::PosI;
    case Prefix::Neg1:
      return Prefix::NegI;
    case Prefix::PosI:
      return Prefix::Neg1;
    case Prefix::NegI:
      return Prefix::Pos1;
    default:
      assert(false);
  }
}

auto operator*(Prefix lhs, Prefix rhs) noexcept -> Prefix {
  switch (lhs) {
    case Prefix::Pos1:
      return rhs;
    case Prefix::Neg1:
      return -rhs;
    case Prefix::PosI:
      return timesI(rhs);
    case Prefix::NegI:
      return -timesI(rhs);

    default:
      assert(false);
  }
}

auto operator<<(std::ostream& os, Prefix p) -> std::ostream & {
  switch (p) {
    case Prefix::Pos1:
      os << '1';
      break;
    case Prefix::Neg1:
      os << "-1";
      break;
    case Prefix::PosI:
      os << 'i';
      break;
    case Prefix::NegI:
      os << "-i";
      break;
    default:
      assert(false);
  }
  return os;
}
