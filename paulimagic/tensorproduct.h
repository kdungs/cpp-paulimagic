#pragma once

#include <iostream>

#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <iterator>
#include <numeric>
#include <ostream>
#include <utility>

#include "prefix.h"
#include "paulimatrix.h"

template <std::size_t N>
class TensorProduct {
 public:
  template <typename... PMATS>
  TensorProduct(PMATS&&... pms)
      : elements_{{std::forward<PMATS>(pms)...}} {}

  template <std::size_t I, typename PMAT>
  auto set(PMAT&& pm) -> void {
    static_assert(I < N, "Index has to be within range.");
    elements_[I] = std::forward<PMAT>(pm);
  }

  auto operator*(const TensorProduct<N>& rhs) -> TensorProduct<N> {
    auto res = TensorProduct<N>{};
    for (auto i = 0u; i < N; ++i) {
      res.elements_[i] = elements_[i] * rhs.elements_[i];
    }
    return res;
  }

  template <typename T = int, typename C = std::complex<T>>
  auto trace() const noexcept -> C {
    return std::accumulate(std::begin(elements_), std::end(elements_), C{1, 0},
                           [](C acc, const PauliMatrix& pm) {
                             return acc * pm.trace();
                           });
  }

  template <std::size_t M>
  friend auto operator<<(std::ostream&, const TensorProduct<M>&) -> std::ostream&;

 private:
  std::array<PauliMatrix, N> elements_;
};

template <std::size_t N>
auto operator<<(std::ostream& os, const TensorProduct<N>& t) -> std::ostream & {
  os << '[';
  std::copy(std::begin(t.elements_), std::end(t.elements_),
            std::ostream_iterator<PauliMatrix>(os, " "));
  os << "\b]";
  return os;
}
