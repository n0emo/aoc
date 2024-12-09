name = checksum 
args = test.txt input.txt

$(name): checksum.ml
	ocamlc -o $(name) checksum.ml

.PHONY: run
run: $(name)
	./$(name) $(args)

clean:
	rm $(name) *.cmi *.cmo
