#include "paulimagic/tensorproduct.h"

#include <iostream>

auto test_multiplication() -> void {}
auto test_trace() -> void {}

int main() {
  test_multiplication();
  test_trace();

  auto t1 = TensorProduct<4>{PM::X, PM::I, PM::nY, PM::I};
  auto t2 = TensorProduct<4>{};
  t2.set<0>(PM::nX);
  t2.set<2>(PM::Y);

  std::cout << t1 << "⊗";
  std::cout << t2 << '=';
  std::cout << t1 * t2 << '\n';
  std::cout << "Tr(t1 ⊗ t2) = " << (t1 * t2).trace() << '\n';
}
