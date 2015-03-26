#include "paulimagic/paulimatrix.h"

#include <cassert>
#include <sstream>
#include <string>

auto test_equalityOperator() -> void {
  assert(PM::I == PM::I);
  assert(PM::X == PM::X);
  assert(PM::Y == PM::Y);
  assert(PM::Z == PM::Z);
}

auto test_inequalityOperator() -> void {
  assert(PM::I != PM::X);
  assert(PM::I != PM::Y);
  assert(PM::I != PM::Z);
  assert(PM::X != PM::I);
  assert(PM::X != PM::Y);
  assert(PM::X != PM::Z);
  assert(PM::Y != PM::I);
  assert(PM::Y != PM::X);
  assert(PM::Y != PM::Z);
  assert(PM::Z != PM::I);
  assert(PM::Z != PM::X);
  assert(PM::Z != PM::Y);
}

auto test_multiplicationOperator() -> void {
  assert(PM::I * PM::I == PM::I);
  assert(PM::I * PM::X == PM::X);
  assert(PM::I * PM::Y == PM::Y);
  assert(PM::I * PM::Z == PM::Z);
  assert(PM::I * PM::nI == PM::nI);
  assert(PM::I * PM::nX == PM::nX);
  assert(PM::I * PM::nY == PM::nY);
  assert(PM::I * PM::nZ == PM::nZ);
  assert(PM::I * PM::iI == PM::iI);
  assert(PM::I * PM::iX == PM::iX);
  assert(PM::I * PM::iY == PM::iY);
  assert(PM::I * PM::iZ == PM::iZ);
  assert(PM::I * PM::niI == PM::niI);
  assert(PM::I * PM::niX == PM::niX);
  assert(PM::I * PM::niY == PM::niY);
  assert(PM::I * PM::niZ == PM::niZ);
  assert(PM::X * PM::I == PM::X);
  assert(PM::X * PM::X == PM::I);
  assert(PM::X * PM::Y == PM::iZ);
  assert(PM::X * PM::Z == PM::niY);
  assert(PM::X * PM::nI == PM::nX);
  assert(PM::X * PM::nX == PM::nI);
  assert(PM::X * PM::nY == PM::niZ);
  assert(PM::X * PM::nZ == PM::iY);
  assert(PM::X * PM::iI == PM::iX);
  assert(PM::X * PM::iX == PM::iI);
  assert(PM::X * PM::iY == PM::nZ);
  assert(PM::X * PM::iZ == PM::Y);
  assert(PM::X * PM::niI == PM::niX);
  assert(PM::X * PM::niX == PM::niI);
  assert(PM::X * PM::niY == PM::Z);
  assert(PM::X * PM::niZ == PM::nY);

  assert(PM::Y * PM::I == PM::Y);
  assert(PM::Y * PM::X == PM::niZ);
  assert(PM::Y * PM::Y == PM::I);
  assert(PM::Y * PM::Z == PM::iX);

  assert(PM::Z * PM::I == PM::Z);
  assert(PM::Z * PM::X == PM::iY);
  assert(PM::Z * PM::Y == PM::niX);
  assert(PM::Z * PM::Z == PM::I);
}

auto test_trace() -> void {
  using C = std::complex<int>;
  assert((PM::I.trace() == C{2, 0}));
  assert((PM::X.trace() == C{0, 0}));
  assert((PM::Y.trace() == C{0, 0}));
  assert((PM::Z.trace() == C{0, 0}));
  assert((PM::nI.trace() == C{-2, 0}));
  assert((PM::nX.trace() == C{0, 0}));
  assert((PM::nY.trace() == C{0, 0}));
  assert((PM::nZ.trace() == C{0, 0}));
  assert((PM::iI.trace() == C{0, 2}));
  assert((PM::iX.trace() == C{0, 0}));
  assert((PM::iY.trace() == C{0, 0}));
  assert((PM::iZ.trace() == C{0, 0}));
  assert((PM::niI.trace() == C{0, -2}));
  assert((PM::niX.trace() == C{0, 0}));
  assert((PM::niY.trace() == C{0, 0}));
  assert((PM::niZ.trace() == C{0, 0}));
}

auto test_ostreamOperator() -> void {
  std::stringstream ss;
  ss << PM::I << PM::X << PM::Y << PM::Z << PM::nI << PM::nX << PM::nY << PM::nZ
     << PM::iI << PM::iX << PM::iY << PM::iZ << PM::niI << PM::niX << PM::niY
     << PM::niZ;
  assert(ss.str() == std::string{"𝟙XYZ-𝟙-X-Y-Zi𝟙iXiYiZ-i𝟙-iX-iY-iZ"});
}

int main() {
  test_equalityOperator();
  test_inequalityOperator();
  test_multiplicationOperator();
  test_trace();
  test_ostreamOperator();
}
