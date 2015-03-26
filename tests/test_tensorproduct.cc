#include "paulimagic/tensorproduct.h"

#include <complex>
#include <sstream>
#include <string>

auto test_equalityOperator() -> void {
  assert(TensorProduct<1>{} == TensorProduct<1>{PM::I});
}

auto test_inequalityOperator() -> void {}

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

int main() {
  test_equalityOperator();
  test_inequalityOperator();
  test_multiplicationOperator();
  test_set();
  test_trace();
  test_ostreamOperator();
}
