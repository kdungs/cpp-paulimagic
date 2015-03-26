CXXFLAGS=-O3 -Wall -Werror -pedantic -std=c++11

test: 
	@cd tests && make
	@cd tests && make test

coverage:
	@cd tests && make coverage

clean:
	cd tests && make clean
