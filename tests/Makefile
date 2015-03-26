CXXFLAGS=-g -O3 -Wall -Werror -pedantic -std=c++11 --coverage
CXXFLAGS+=-I../

targets = test_prefix test_paulimatrix test_tensorproduct

all: $(targets)

test: $(targets)
	@$(foreach target, $(targets), ./$(target);)

clean:
	rm -f $(targets)
	rm -f *.gcov
	rm -f *.gcno
	rm -f *.gcda
	rm -rf *.dSYM
