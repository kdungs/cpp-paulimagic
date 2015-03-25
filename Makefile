CXX=clang++
CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++11 -stdlib=libc++ -lc++abi

test: test_paulimatrix test_prefix test_expression test_tensor
	./test_paulimatrix
	./test_prefix
	./test_expression
	./test_tensor

clean:
	rm -f test_paulimatrix
	rm -f test_prefix
	rm -f test_expression
	rm -f test_tensor
