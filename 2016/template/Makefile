CXX = clang++ -std=c++20
CFLAGS = -Wall -Wextra -pedantic -ggdb
ARGS = 

main: main.cpp
	$(CXX) $(CFLAGS) main.cpp -o main

.PHONY: run
run: main
	./main $(ARGS)

