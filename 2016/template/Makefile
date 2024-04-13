CXX = clang++ -std=c++20
CFLAGS = -Wall -Wextra -pedantic -ggdb
ARGS = test1.txt

main: main.cpp ../common.hpp
	$(CXX) $(CFLAGS) main.cpp -o main

.PHONY: run
run: main
	@for test in $(shell find . -name '*.txt'); \
	do \
		echo "Running with" $$test ":" ; \
		./main $$test | sed 's/^/    /'; \
	done
