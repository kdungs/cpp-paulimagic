#include "paulimagic/tensorproduct.h"

#include <complex>

auto test_multiplication() -> void {
  assert(((TensorProduct<4>{PM::X} * TensorProduct<4>{PM::Y} *
           TensorProduct<4>{PM::X} * TensorProduct<4>{PM::Y}) ==
          TensorProduct<4>{PM::nI}));
}

auto test_trace() -> void {
  assert((TensorProduct<4>{}.trace() == std::complex<int>{16, 0}));
}

int main() {
  test_multiplication();
  test_trace();
}
