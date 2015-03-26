# Pauli Magic :sparkles:
[![Build Status](https://travis-ci.org/kdungs/cpp-paulimagic.svg)](https://travis-ci.org/kdungs/cpp-paulimagic)

A small header-only library that can help you with your tensor arithmetic. This is based on previous work by [McUrbn](https://github.com/McUrbn) for his Bachelor thesis. I merely implemented his ideas.

## Background
The Pauli matrices σ<sub>x</sub>, σ<sub>y</sub>, σ<sub>z</sub> are defined such that σ<sub>i</sub>σ<sub>i</sub>=𝟙. Additionally there are the commutation relations [σ<sub>a</sub>σ<sub>b</sub>]=2ⅈε<sub>abc</sub>σ<sub>c</sub> and the anti-commutation relations {σ<sub>a</sub>σ<sub>b</sub>} = 2δ<sub>ab</sub>𝟙. It follows directly, that σ<sub>a</sub>σ<sub>b</sub>σ<sub>c</sub>=ⅈε<sub>abc</sub>𝟙 and 
σ<sub>a</sub>σ<sub>b</sub>σ<sub>a</sub>σ<sub>b</sub>=-𝟙. For more information see [the corresponding Wikipedia article](https://en.wikipedia.org/wiki/Pauli_matrices).

This program uses said relations to simplify products of expressions containing Pauli matrices.


## Usage
After including the header `paulimagic/expression.h`, expressions can be constructed and multiplied like so:
```cplusplus
auto ex1 = Expression{Prefix::PosI, {PauliMatrix::X, PauliMatrix::Y}};
auto ex2 = Expression{PauliMatrix::Z};
auto ex3 = ex1 * ex2;
std::cout << ex3 << '\n';
```
where ex1 = ⅈσ<sub>x</sub>σ<sub>y</sub> and ex2 = σ<sub>z</sub> such that ex3 = ⅈσ<sub>x</sub>σ<sub>y</sub>σ<sub>z</sub> = ⅈⅈ𝟙= -𝟙.

Please bear in mind that `Expression{PauliMatrix:X, PauliMatrix::Y, PauliMatrix::Z}` should instead be written as `Expression::ImaginaryIdentity`. Using non-simplified expressions is undefined behaviour. Especially 
```cplusplus
assert((Expression{PauliMatrix::X, PauliMatrix::Y, PauliMatrix::Z} * _1) ==
       Expression::ImaginaryIdentity);
```
**will fail**.

