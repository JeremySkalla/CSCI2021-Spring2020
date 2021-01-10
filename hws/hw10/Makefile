CFLAGS = -Wall -g -Og
CC     = gcc $(CFLAGS)

all: matsums_main

matsums_main : matsums_main.o matsums_funcs.o matvec_util.o
	$(CC) -o $@ $^		

matsums_main.o : matsums_main.c
	$(CC) -c $<		

matsums_funcs.o : matsums_funcs.c
	$(CC) -c $<		

matvec_util.o : matvec_util.c matvec.h
	$(CC) -c $<

clean:
	rm -f *.o mastums_main
