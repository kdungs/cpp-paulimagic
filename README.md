# Pauli Magic :sparkles: [![Build Status](https://travis-ci.org/kdungs/cpp-paulimagic.svg)](https://travis-ci.org/kdungs/cpp-paulimagic) [![Coverage Status](https://coveralls.io/repos/kdungs/cpp-paulimagic/badge.svg?branch=master)](https://coveralls.io/r/kdungs/cpp-paulimagic?branch=master)

A small header-only library that can help you with traces of tensor products that contain Pauli matrices. This is based on previous work by [McUrbn](https://github.com/McUrbn) for his Bachelor thesis. I merely implemented his ideas.

## Background
The Pauli matrices σ<sub>x</sub>, σ<sub>y</sub>, σ<sub>z</sub> are traceless 2×2-matrices that are defined such that σ<sub>i</sub>σ<sub>i</sub>=𝟙. Additionally there are the commutation relations [σ<sub>a</sub>σ<sub>b</sub>]=2ⅈε<sub>abc</sub>σ<sub>c</sub> and the anti-commutation relations {σ<sub>a</sub>σ<sub>b</sub>} = 2δ<sub>ab</sub>𝟙. It follows directly, that for a≠b, σ<sub>a</sub>σ<sub>b</sub>=ⅈε<sub>abc</sub>σ<sub>c</sub>. For more information see [the corresponding Wikipedia article](https://en.wikipedia.org/wiki/Pauli_matrices).

For the product of two tensor products (a<sub>1</sub>⊗b<sub>1</sub>) and (a<sub>2</sub>⊗b<sub>2</sub>) it holds (_this is very much a simplification, for more detail check out [this Wikipedia article on the "Tensor product of algebras
"](https://en.wikipedia.org/wiki/Tensor_product_of_algebras)_) that (a<sub>1</sub>⊗b<sub>1</sub>)(a<sub>2</sub>⊗b<sub>2</sub>) = (a<sub>1</sub>a<sub>2</sub>⊗b<sub>1</sub>b<sub>2</sub>). Also for traces of tensor products it holds that Tr(a⊗b) = Tr(a)Tr(b).

This program uses said relations to simplify tensor products containing Pauli matrices and ultimately calculates traces of those.

## Usage

Here's a minimal program that calculates the trace of the product of four tensor products:
```cplusplus
#include <iostream>

#include "paulimagic/tensorproduct.h"

int main() {
  std::cout << (TensorProduct<4>{PM::X} * TensorProduct<4>{PM::Y} *
                TensorProduct<4>{PM::Z, PM::I, PM::iI} *
                TensorProduct<4>{PM::I, PM::nI}).trace() << '\n';
}
```

Compile it with the flags `-O3 -Wall -Werror -pedantic -std=c++11 -I/path/to/cpp-paulimagic`. It should print out the result `(16,0)` representing the complex number 16+0ⅈ. Verifying this result is left as an exercise for the gentle reader.
