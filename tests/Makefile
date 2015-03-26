CXXFLAGS=-g -O3 -Wall -Werror -pedantic -std=c++11 --coverage
CXXFLAGS+=-I../

targets = test_paulimatrix test_prefix test_expression test_tensor

all: $(targets)

test: $(targets)
	@$(foreach target, $(targets), ./$(target);)

coverage: test
	lcov -o coverage.info --capture --directory .
	lcov -r coverage.info /usr/include/\* -o coverage.info

covhtml: coverage
	genhtml -o coverage coverage.info

clean:
	@rm -f $(targets)
	@rm -f *.gcov
	@rm -f *.gcno
	@rm -f *.gcda
	@rm -f coverage.info
	@rm -rf *.dSYM
	@rm -rf coverage
