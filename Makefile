all: assignment.out

assignment.out: 
	gcc -Wall -Werror -ansi -o assignment.out assignment.c xor.c huffman.c -lm


clean: 
	rm assignment.out
