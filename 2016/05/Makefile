CXX = clang++ -std=c++20
CFLAGS = -Wall -Wextra -pedantic -Werror=return-type -ggdb -O3

main: main.cpp ../common.hpp
	$(CXX) $(CFLAGS) main.cpp -o main -lmd

.PHONY: run
run: main
	@for test in $(shell find . -name '*.txt' | sort -t '\0' -n); \
	do \
		echo "Running with" $$test ":" ; \
		./main $$test | sed 's/^/    /'; \
	done
