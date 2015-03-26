#pragma once

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

  auto operator==(const TensorProduct<N>& rhs) const noexcept -> bool {
    return elements_ == rhs.elements_;
  }

  auto operator!=(const TensorProduct<N>& rhs) const noexcept -> bool {
    return !(*this == rhs);
  }

  auto operator*(const TensorProduct<N>& rhs) const -> TensorProduct<N> {
    auto res = TensorProduct<N>{};
    for (auto i = 0u; i < N; ++i) {
      res.elements_[i] = elements_[i] * rhs.elements_[i];
    }
    return res;
  }

  template <std::size_t I, typename PMAT>
  auto set(PMAT&& pm) -> void {
    static_assert(I < N, "Index has to be within range.");
    elements_[I] = std::forward<PMAT>(pm);
  }

  template <typename T = int, typename C = std::complex<T>>
  auto trace() const noexcept -> C {
    return std::accumulate(
        std::begin(elements_), std::end(elements_), C{1, 0},
        [](C acc, const PauliMatrix& pm) { return acc * pm.trace(); });
  }

 private:
  template <std::size_t M>
  friend auto operator<<(std::ostream&, const TensorProduct<M>&) -> std::ostream
      &;

  std::array<PauliMatrix, N> elements_;
};

template <std::size_t N>
auto operator<<(std::ostream& os, const TensorProduct<N>& t) -> std::ostream & {
  os << '[';
  std::copy(std::begin(t.elements_), std::end(t.elements_) - 1,
            std::ostream_iterator<PauliMatrix>(os, " "));
  os << t.elements_[N - 1];
  os << ']';
  return os;
}
