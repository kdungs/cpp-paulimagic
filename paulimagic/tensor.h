#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>
#include <numeric>
#include <ostream>
#include <utility>

#include "expression.h"
#include "prefix.h"

template <std::size_t N>
class Tensor {
 public:
   template <std::size_t I, typename EXPRESSION>
   auto set(EXPRESSION&& ex) -> void {
    static_assert(I < N, "Index has to be within range.");
    elements_[I] = std::forward<EXPRESSION>(ex);
   }

   auto operator*(const Tensor<N>& rhs) -> Tensor<N> {
     auto res = Tensor<N>{};
     for (auto i = 0u; i < N; ++i) {
       res.elements_[i] = elements_[i] * rhs.elements_[i];
     }
     return res;
   }

   auto trace() const noexcept -> double {
     if (std::all_of(std::begin(elements_), std::end(elements_),
                     [](const Expression& e) { return e.isIdentity(); })) {
       auto p = std::accumulate(
           std::begin(elements_), std::end(elements_), Prefix::Pos1,
           [](Prefix acc, const Expression& exp) { return acc * exp.prefix(); });
       assert(isReal(p) && "trace has to be real");
       auto sign = isPositive(p) ? 1.0 : -1.0;
       return sign * std::pow(2.0, N);
     }
     return 0.0;
   }

   template <std::size_t M>
   friend auto operator<<(std::ostream&, const Tensor<M>&) -> std::ostream&;

 private:
  std::array<Expression, N> elements_;
};

template <std::size_t N>
auto operator<<(std::ostream& os, const Tensor<N>& t) -> std::ostream& {
  os << '[';
  std::copy(std::begin(t.elements_), std::end(t.elements_),
            std::ostream_iterator<Expression>(os, " "));
  os << "\b]";
  return os;
}
