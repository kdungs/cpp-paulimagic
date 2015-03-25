#pragma once

#include <vector>
#include <ostream>
#include <iterator>

#include "paulimatrix.h"
#include "prefix.h"

class Expression {
 public:
  Expression(Prefix p, std::initializer_list<PauliMatrix> ms)
      : prefix_{p}, matrices_{ms} {}
  explicit Expression(Prefix p) : Expression{p, {}} {}
  explicit Expression(std::initializer_list<PauliMatrix> ms)
      : Expression{Prefix::Pos1, ms} {}

  auto prefix() const noexcept -> Prefix { return prefix_; }
  auto isPositive() const noexcept -> bool { return ::isPositive(prefix_); }
  auto isReal() const noexcept -> bool { return ::isReal(prefix_); }
  auto isIdentity() const noexcept -> bool { return matrices_.empty(); }

  auto operator*(const Expression& rhs) const -> Expression {
    auto result = *this;

    return result;
  }

  friend auto operator<<(std::ostream&, const Expression&) -> std::ostream&;

  static const Expression Identity;
  static const Expression NegativeIdentity;
  static const Expression ImaginaryIdentity;
  static const Expression NegativeImaginaryIdentity;

 private:
  auto simplify() noexcept -> void;
  Prefix prefix_;
  std::vector<PauliMatrix> matrices_;
};

const auto Expression::Identity = Expression{Prefix::Pos1};
const auto Expression::NegativeIdentity = Expression{Prefix::Neg1};
const auto Expression::ImaginaryIdentity = Expression{Prefix::PosI};
const auto Expression::NegativeImaginaryIdentity = Expression{Prefix::NegI};

auto operator<<(std::ostream& os, const Expression& exp) -> std::ostream & {
  os << exp.prefix();
  if (!exp.isIdentity()) {
    std::copy(std::begin(exp.matrices_), std::end(exp.matrices_),
              std::ostream_iterator<PauliMatrix>(os));
  }
  return os;
}

auto Expression::simplify() noexcept -> void {}
