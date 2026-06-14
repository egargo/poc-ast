.PHONY: build clean

build:
	gcc -std=c23 -o ast main.c ast.c

run:
	./ast

clean:
	rm ast
