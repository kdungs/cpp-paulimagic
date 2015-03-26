# Pauli Magic :sparkles:
[![Build Status](https://travis-ci.org/kdungs/cpp-paulimagic.svg)](https://travis-ci.org/kdungs/cpp-paulimagic) [![Coverage Status](https://coveralls.io/repos/kdungs/cpp-paulimagic/badge.svg?branch=master)](https://coveralls.io/r/kdungs/cpp-paulimagic?branch=master)

A small header-only library that can help you with your tensor arithmetic. This is based on previous work by [McUrbn](https://github.com/McUrbn) for his Bachelor thesis. I merely implemented his ideas.

## Background
The Pauli matrices σ<sub>x</sub>, σ<sub>y</sub>, σ<sub>z</sub> are defined such that σ<sub>i</sub>σ<sub>i</sub>=𝟙. Additionally there are the commutation relations [σ<sub>a</sub>σ<sub>b</sub>]=2ⅈε<sub>abc</sub>σ<sub>c</sub> and the anti-commutation relations {σ<sub>a</sub>σ<sub>b</sub>} = 2δ<sub>ab</sub>𝟙. It follows directly, that σ<sub>a</sub>σ<sub>b</sub>σ<sub>c</sub>=ⅈε<sub>abc</sub>𝟙 and 
σ<sub>a</sub>σ<sub>b</sub>σ<sub>a</sub>σ<sub>b</sub>=-𝟙. For more information see [the corresponding Wikipedia article](https://en.wikipedia.org/wiki/Pauli_matrices).

This program uses said relations to simplify products of expressions containing Pauli matrices.


## Usage
_Changed a lot with recent PR. Will be updated shortly._
