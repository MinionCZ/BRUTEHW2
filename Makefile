main: main.c
	clang -pedantic -Wall -std=c99 -Werror main.c -o main -lm
	./main -prg
clear:
	rm main