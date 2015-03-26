CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++11
CXXFLAGS+=-I../

targets = test_paulimatrix test_prefix test_expression test_tensor

all: $(targets)

test:
	@$(foreach target, $(targets), ./$(target);)

clean:
	@rm -f $(targets)
