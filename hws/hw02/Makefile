# Makefile: standard looking makeefile to enable easy build/test. The
# conventions in this file will used in much of the class such as
# 'make' , 'make test', and 'make clean'. Students do not need to
# fully understand this file, just how to use the build commands on
# the command line.

# flags to pass to compiler and compile command
CFLAGS = -Wall -g
CC     = gcc $(CFLAGS)

# variable defining programs to build
PROGRAMS = \
	list_main \


all : $(PROGRAMS)			      # default target is to build all PROGRAMS

%.o : %.c list.h			      # shortcut to compile all .o's from .c's
	$(CC) -c $<

list_main : list_main.o list_funcs.o list.h   # create the list_main program
	$(CC) -o $@ $^

test : list_main			      #run the automated tests, defaults to all tests
	./testy test_list_main.org $(testnum)

clean :					      # remove compiled programs and object files
	rm -f $(PROGRAMS) *.o

