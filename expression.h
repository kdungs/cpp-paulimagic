#pragma once

#include <array>
#include <iterator>
#include <ostream>
#include <vector>

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
    auto res = *this;
    res.prefix_ = res.prefix_ * rhs.prefix_;

    auto& lm = res.matrices_;
    const auto& rm = rhs.matrices_;
    auto li = static_cast<int>(lm.size() - 1);
    auto ri = 0;
    auto rs = static_cast<int>(rm.size());

    auto handle_equality = [&lm, &li, &rm, &ri]() {
      if (lm[li] != rm[ri]) {
        return false;
      }
      lm.pop_back();
      --li;
      ++ri;
      return true;
    };

    auto handle_permutation = [&res, &lm, &li, &rm, &ri, rs] (bool left) {
      if ((left && li <= 0) || ri + 1 >= rs) {
        return false;
      }
      auto x = left ? lm[li - 1] : rm[ri + 1];
      if (!isPermutation(lm[li], rm[ri], x)) {
        return false;
      }
      if (isCyclic(lm[li], rm[ri], x)) {
        res.prefix_ = res.prefix_ * Prefix::PosI;
      } else {
        res.prefix_ = res.prefix_ * Prefix::NegI;
      }
      lm.pop_back();
      --li;
      ++ri;
      if (left) {
        lm.pop_back();
        --li;
      } else {
        ++ri;
      }
      return true;
    };

    auto handle_abab = [&res, &lm, &li, &rm, &ri, rs] (unsigned loffset) {
      auto arr = std::array<PauliMatrix, 4>{};
      auto k = 0u;
      for (auto i = static_cast<int>(li - loffset); i <= li; ++i, ++k) {
        if (i < 0) {
          return false;
        }
        arr[k] = lm[i];
      }
      for (auto i = ri; k < 4; ++i, ++k) {
        arr[k] = rm[i];
      }
      if (arr[0] != arr[2] || arr[1] != arr[3]) {
        return false;
      }
      lm.pop_back();
      --li;
      ++ri;
      for (auto i = loffset; i > 0; --i) {
        lm.pop_back();
        --li;
      }
      for (auto i = 2 - loffset; i > 0; --i) {
        ++ri;
      }
      return true;
    };

    while (li >= 0 && ri < rs) {
      if (!handle_equality() && !handle_permutation(true) &&
          !handle_permutation(false) && !handle_abab(2) && !handle_abab(1) &&
          !handle_abab(0)) {
        break;
      }
    }

    lm.insert(std::end(lm), std::begin(rm) + ri, std::end(rm));
    return res;
  }

  friend auto operator<<(std::ostream&, const Expression&) -> std::ostream&;

  static const Expression Identity;
  static const Expression NegativeIdentity;
  static const Expression ImaginaryIdentity;
  static const Expression NegativeImaginaryIdentity;

 private:
  Prefix prefix_;
  std::vector<PauliMatrix> matrices_;
};

const auto Expression::Identity = Expression{Prefix::Pos1};
const auto Expression::NegativeIdentity = Expression{Prefix::Neg1};
const auto Expression::ImaginaryIdentity = Expression{Prefix::PosI};
const auto Expression::NegativeImaginaryIdentity = Expression{Prefix::NegI};

auto operator<<(std::ostream& os, const Expression& exp) -> std::ostream & {
  os << exp.prefix();
  if (exp.isIdentity()) {
    os << '1';
  } else {
    std::copy(std::begin(exp.matrices_), std::end(exp.matrices_),
              std::ostream_iterator<PauliMatrix>(os));
  }
  return os;
}
