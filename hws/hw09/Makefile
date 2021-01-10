# -Og debug optimization to prevent loops from collapsing
CFLAGS = -Wall -g -Og
CC     = gcc $(CFLAGS)

all: superscalar_main

superscalar_main : superscalar_main.o superscalar_funcs.o
	$(CC) -o $@ $^		

superscalar_main.o : superscalar_main.c
	$(CC) -c $<		

superscalar_funcs.o : superscalar_funcs.c
	$(CC) -c $<		

clean:
	rm -f superscalar_main.o superscalar_funcs.o superscalar_main
