CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++11

test: 
	@cd tests && make
	@cd tests && make test

coverage: test
	lcov -o coverage.info --capture --directory .
	lcov -r coverage.info /usr/include/\* -o coverage.info

covhtml: coverage
	genhtml -o coverage coverage.info

clean:
	@cd tests && make clean
	rm -rf coverage*
