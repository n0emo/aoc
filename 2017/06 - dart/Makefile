args = test.txt input.txt

memory.exe: memory.dart
	dart compile exe memory.dart

.PHONY: run
run: memory.exe
	./memory.exe $(args)

.PHONY: clean
clean:
	rm *.exe -f