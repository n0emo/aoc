args = test.txt input.txt

maze: maze.f90
	gfortran maze.f90 -o maze

.PHONY: run
run: maze
	./maze $(args)
