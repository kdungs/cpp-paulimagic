#include "tensor.h"

#include <iostream>

int main() {
  auto t1 = Tensor<4>{};
  t1.set<0>(Expression{PauliMatrix::X});
  t1.set<2>(Expression::NegativeIdentity);

  auto t2 = Tensor<4>{};
  t2.set<0>(Expression{PauliMatrix::Y, PauliMatrix::Z});
  t2.set<2>(Expression::NegativeImaginaryIdentity);

  std::cout << t1 << '\n';
  std::cout << t2 << '\n';
  std::cout << t1 * t2 << '\n';
  std::cout << (t1 * t2).trace() << '\n';
}
