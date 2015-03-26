#pragma once

#include <cassert>
#include <complex>
#include <ostream>

#include "prefix.h"

class PauliMatrix {
 public:
  enum class BasicPauliMatrix { Identity, SigmaX, SigmaY, SigmaZ };

  PauliMatrix(Prefix p, BasicPauliMatrix m) noexcept : p_{p}, m_{m} {}
  explicit PauliMatrix(BasicPauliMatrix m) noexcept
      : PauliMatrix{Prefix::Pos1, m} {}
  explicit PauliMatrix(Prefix p) noexcept
      : PauliMatrix{p, BasicPauliMatrix::Identity} {}
  PauliMatrix() noexcept
      : PauliMatrix{Prefix::Pos1, BasicPauliMatrix::Identity} {}

  auto operator==(const PauliMatrix& rhs) const noexcept -> bool {
    return p_ == rhs.p_ && m_ == rhs.m_;
  }
  auto operator!=(const PauliMatrix& rhs) const noexcept -> bool {
    return !(*this == rhs);
  }

  auto operator*(const PauliMatrix& rhs) const noexcept -> PauliMatrix {
    auto m = mult(m_, rhs.m_);
    return PauliMatrix{p_ * rhs.p_ * m.p_, m.m_};
  }

  template <typename T = int, typename C = std::complex<T>>
  auto trace() const noexcept -> C {
    if (m_ != BasicPauliMatrix::Identity) {
      return C{0, 0};
    }
    switch (p_) {
      case  Prefix::Pos1:
        return C{2, 0};
      case  Prefix::Neg1:
        return C{-2, 0};
      case  Prefix::PosI:
        return C{0, 2};
      case  Prefix::NegI:
        return C{0, -2};
      default:
        assert(false);
    }
  }

  friend auto operator<<(std::ostream&, const PauliMatrix&) -> std::ostream&;

 private:
  auto mult(BasicPauliMatrix lhs, BasicPauliMatrix rhs) const noexcept
      -> PauliMatrix {
    if (lhs == BasicPauliMatrix::Identity) {  // 𝟙a = a
      return PauliMatrix{rhs};
    }
    if (rhs == BasicPauliMatrix::Identity) {  // a𝟙 = a
      return PauliMatrix{lhs};
    }
    if (lhs == rhs) {  // aa = 𝟙
      return PauliMatrix{};
    }
    if (lhs == BasicPauliMatrix::SigmaX) {
      if (rhs == BasicPauliMatrix::SigmaY) {
        return PauliMatrix{Prefix::PosI, BasicPauliMatrix::SigmaZ};
      }
      return PauliMatrix{Prefix::NegI, BasicPauliMatrix::SigmaY};
    }

    if (lhs == BasicPauliMatrix::SigmaY) {
      if (rhs == BasicPauliMatrix::SigmaZ) {
        return PauliMatrix{Prefix::PosI, BasicPauliMatrix::SigmaX};
      }
      return PauliMatrix{Prefix::NegI, BasicPauliMatrix::SigmaZ};
    }

    if (rhs == BasicPauliMatrix::SigmaX) {
      return PauliMatrix{Prefix::PosI, BasicPauliMatrix::SigmaY};
    }
    return PauliMatrix{Prefix::NegI, BasicPauliMatrix::SigmaX};
  }

  Prefix p_;
  BasicPauliMatrix m_;
};

auto operator<<(std::ostream& os, PauliMatrix::BasicPauliMatrix m)
    -> std::ostream & {
  switch (m) {
    case PauliMatrix::BasicPauliMatrix::Identity:
      os << "𝟙";
      break;
    case PauliMatrix::BasicPauliMatrix::SigmaX:
      os << 'X';
      break;
    case PauliMatrix::BasicPauliMatrix::SigmaY:
      os << 'Y';
      break;
    case PauliMatrix::BasicPauliMatrix::SigmaZ:
      os << 'Z';
      break;
    default:
      assert(false);  // This should never happen!
  }
  return os;
}

auto operator<<(std::ostream& os, const PauliMatrix& pm) -> std::ostream & {
  os << pm.p_ << pm.m_;
  return os;
}

namespace PM {
static const auto I = PauliMatrix{PauliMatrix::BasicPauliMatrix::Identity};
static const auto X = PauliMatrix{PauliMatrix::BasicPauliMatrix::SigmaX};
static const auto Y = PauliMatrix{PauliMatrix::BasicPauliMatrix::SigmaY};
static const auto Z = PauliMatrix{PauliMatrix::BasicPauliMatrix::SigmaZ};
static const auto nI =
    PauliMatrix{Prefix::Neg1, PauliMatrix::BasicPauliMatrix::Identity};
static const auto nX =
    PauliMatrix{Prefix::Neg1, PauliMatrix::BasicPauliMatrix::SigmaX};
static const auto nY =
    PauliMatrix{Prefix::Neg1, PauliMatrix::BasicPauliMatrix::SigmaY};
static const auto nZ =
    PauliMatrix{Prefix::Neg1, PauliMatrix::BasicPauliMatrix::SigmaZ};
static const auto iI =
    PauliMatrix{Prefix::PosI, PauliMatrix::BasicPauliMatrix::Identity};
static const auto iX =
    PauliMatrix{Prefix::PosI, PauliMatrix::BasicPauliMatrix::SigmaX};
static const auto iY =
    PauliMatrix{Prefix::PosI, PauliMatrix::BasicPauliMatrix::SigmaY};
static const auto iZ =
    PauliMatrix{Prefix::PosI, PauliMatrix::BasicPauliMatrix::SigmaZ};
static const auto niI =
    PauliMatrix{Prefix::NegI, PauliMatrix::BasicPauliMatrix::Identity};
static const auto niX =
    PauliMatrix{Prefix::NegI, PauliMatrix::BasicPauliMatrix::SigmaX};
static const auto niY =
    PauliMatrix{Prefix::NegI, PauliMatrix::BasicPauliMatrix::SigmaY};
static const auto niZ =
    PauliMatrix{Prefix::NegI, PauliMatrix::BasicPauliMatrix::SigmaZ};
};
