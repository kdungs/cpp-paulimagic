CXX=clang++
CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++11 -stdlib=libc++ -lc++abi

test: test_paulimatrix test_prefix test_expression
	./test_paulimatrix
	./test_prefix
	./test_expression

test_paulimatrix: test_paulimatrix.cc

test_prefix: test_prefix.cc

test_expression: test_expression.cc

clean:
	rm -f test_paulimatrix
	rm -f test_prefix
	rm -f test_expression
