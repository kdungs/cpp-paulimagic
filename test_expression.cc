#include "expression.h"

#include <cassert>
#include <sstream>
#include <string>

auto test_isPositive() -> void {
  assert(Expression::Identity.isPositive());
  assert(!Expression::NegativeIdentity.isPositive());
  assert(Expression::ImaginaryIdentity.isPositive());
  assert(!Expression::NegativeImaginaryIdentity.isPositive());
  assert(Expression{PauliMatrix::X}.isPositive());
}

auto test_isReal() -> void {
  assert(Expression::Identity.isReal());
  assert(Expression::NegativeIdentity.isReal());
  assert(!Expression::ImaginaryIdentity.isReal());
  assert(!Expression::NegativeImaginaryIdentity.isReal());
  assert(Expression{PauliMatrix::X}.isReal());
}

auto test_isIdentity() -> void {
  assert(Expression::Identity.isIdentity());
  assert(Expression::NegativeIdentity.isIdentity());
  assert(Expression::ImaginaryIdentity.isIdentity());
  assert(Expression::NegativeImaginaryIdentity.isIdentity());
  assert(!Expression{PauliMatrix::X}.isIdentity());
}

auto test_multiplicationOperator() -> void {
  const auto& _1 = Expression::Identity;
  const auto& n1 = Expression::NegativeIdentity;
  const auto& i = Expression::ImaginaryIdentity;
  const auto& ni = Expression::NegativeImaginaryIdentity;

  // 1 * _
  assert(_1 * _1 == _1);
  assert(_1 * n1 == n1);
  assert(_1 * i == i);
  assert(_1 * ni == ni);
  // -1 * x
  assert(n1 * _1 == n1);
  assert(n1 * n1 == _1);
  assert(n1 * i == ni);
  assert(n1 * ni == i);
  // i * x
  assert(i * _1 == i);
  assert(i * n1 == ni);
  assert(i * i == n1);
  assert(i * ni == _1);
  // -i * x
  assert(ni * _1 == ni);
  assert(ni * n1 == i);
  assert(ni * i == _1);
  assert(ni * ni == n1);

  auto x = Expression{PauliMatrix::X};
  auto nx = Expression{Prefix::Neg1, {PauliMatrix::X}};
  auto ix = Expression{Prefix::PosI, {PauliMatrix::X}};
  auto nix = Expression{Prefix::NegI, {PauliMatrix::X}};
  auto y = Expression{PauliMatrix::Y};
  auto z = Expression{PauliMatrix::Z};
  auto xy = Expression{PauliMatrix::X, PauliMatrix::Y};
  auto xz = Expression{PauliMatrix::X, PauliMatrix::Z};
  auto yx = Expression{PauliMatrix::Y, PauliMatrix::X};
  auto yz = Expression{PauliMatrix::Y, PauliMatrix::Z};
  auto zx = Expression{PauliMatrix::Z, PauliMatrix::X};
  auto zy = Expression{PauliMatrix::Z, PauliMatrix::Y};

  // Multiplication with (prefixed) identity
  assert(x * _1 == x);  // a1 = a
  assert(_1 * x == x);  // 1a = a
  assert(x * n1 == nx);  // a(-1) = -a
  assert(n1 * x == nx);  // -1a = -a
  assert(x * i == ix);  // a(i1) = ia
  assert(i * x == ix);  // i1a = ia
  assert(x * ni == nix);  // a(-i1) = -ia
  assert(ni * x == nix);  // -i1a = -ia
  // Squares are identity: aa = 1
  assert(x * x == _1);
  assert(y * y == _1);
  assert(z * z == _1);
  assert(xy * yx == _1);  // abba = a(bb)a = a1a = aa = 1
  assert(xz * zx == _1);
  assert(yx * xy == _1);
  assert(yz * zy == _1);
  assert(zx * xz == _1);
  assert(zy * yz == _1);
  // Not commutative: ab ≠ ba
  assert(x * y != y * x);
  assert(x * z != z * x);
  assert(y * z != z * y);
  // Cyclic permutations: abc = i
  assert(xy * z == i);
  assert(x * yz == i);
  assert(yz * x == i);
  assert(y * zx == i);
  assert(zx * y == i);
  assert(z * xy == i);
  // Acyclic permutations: acb = -i
  assert(zy * x == ni);  // acb = -i
  assert(z * yx == ni);  // acb = -i
  // abab = -1
  assert(xy * xy == n1);
  assert(xz * xz == n1);
  assert(yx * yx == n1);
  assert(yz * yz == n1);
  assert(zx * zx == n1);
  assert(zy * zy == n1);
}

auto test_ostreamOperator() -> void {
  std::stringstream ss;
  ss << Expression{Prefix::NegI, {PauliMatrix::X, PauliMatrix::Y}};
  assert(ss.str() == std::string{"-iXY"});
}

int main() {
  test_isPositive();
  test_isReal();
  test_isIdentity();
  test_multiplicationOperator();
  test_ostreamOperator();
}
