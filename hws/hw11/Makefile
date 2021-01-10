CFLAGS = -Wall -g -Og
CC     = gcc $(CFLAGS)

all: colmins_main

colmins_main : colmins_main.o colmins_funcs.o matvec_util.o
	$(CC) -o $@ $^		

colmins_main.o : colmins_main.c
	$(CC) -c $<		

colmins_funcs.o : colmins_funcs.c
	$(CC) -c $<		

matvec_util.o : matvec_util.c matvec.h
	$(CC) -c $<

clean:
	rm -f *.o colmins_main
