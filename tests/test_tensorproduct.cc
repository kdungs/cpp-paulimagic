#include "paulimagic/tensorproduct.h"

#include <array>
#include <complex>
#include <sstream>
#include <string>

#include <iostream>

auto test_equalityOperator() -> void {
  assert(TensorProduct<1>{} == TensorProduct<1>{PM::I});
}

auto test_inequalityOperator() -> void {
  assert(TensorProduct<1>{} != TensorProduct<1>{PM::X});
}

auto test_multiplicationOperator() -> void {
  assert(((TensorProduct<4>{PM::X} * TensorProduct<4>{PM::Y} *
           TensorProduct<4>{PM::X} * TensorProduct<4>{PM::Y}) ==
          TensorProduct<4>{PM::nI}));
}

auto test_set() -> void {
  auto t = TensorProduct<3>{};
  t.set<0>(PM::X);
  t.set<1>(PM::Y);
  t.set<2>(PM::Z);
  assert((t == TensorProduct<3>{PM::X, PM::Y, PM::Z}));
}

auto test_trace() -> void {
  assert((TensorProduct<4>{}.trace() == std::complex<int>{16, 0}));
  assert((TensorProduct<4>{PM::X}.trace() == std::complex<int>{0, 0}));
  assert((TensorProduct<4>{PM::I, PM::nI, PM::iI, PM::niI}.trace() ==
          std::complex<int>{-16, 0}));
}

auto test_ostreamOperator() -> void {
  std::stringstream ss;
  ss << TensorProduct<3>{PM::X, PM::Y, PM::Z};
  assert(ss.str() == std::string{"[X Y Z]"});
}

auto test_summation() -> void {
  const int N = 4;
  std::complex<int> sum = 0;
  auto array = std::array<PauliMatrix, 3>{PM::X, PM::Y, PM::Z};
  for (int j = 0; j < 3; ++j) {
    for (int i1 = 0; i1 < 4; ++i1) {
      for (int i2 = 0; i2 < 4; ++i2) {
        auto t1 = TensorProduct<N>{};
        auto t2 = TensorProduct<N>{};
        t1.set(i1, array[j]);
        t2.set(i1, array[j]);
        sum += (t1 * t2).trace();
      }
    }
  }
  std::cout << sum << '\n';
  assert(sum.imag() == 0);
  assert(sum.real() == 3 * N / 4);
}

int main() {
  test_equalityOperator();
  test_inequalityOperator();
  test_multiplicationOperator();
  test_set();
  test_trace();
  test_ostreamOperator();
  test_summation();
}
