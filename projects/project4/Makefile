CFLAGS = -Wall -Werror -g -Og
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	sumdiag_print \
	sumdiag_benchmark \
	search_benchmark \

all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o vgcore.* 

AN=p4
zip :
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi


%.o : %.c
	$(CC) -c $<


# Matrix diagonal summing optimization problem
sumdiag_print : sumdiag_print.o matvec_util.o sumdiag_base.o sumdiag_optm.o
	$(CC) -o $@ $^

sumdiag_benchmark : sumdiag_benchmark.o matvec_util.o sumdiag_base.o sumdiag_optm.o
	$(CC) -o $@ $^


# Search Algorithm Problem
search_benchmark : search_benchmark.o search_funcs.o
	$(CC) -o $@ $^

# run with valgrind to check for memory problems
test: sumdiag_benchmark sumdiag_print search_benchmark
	@chmod u+x ./testy 
	./testy test_valgrind.org

prob1-valgrind: sumdiag_benchmark sumdiag_print
	@chmod u+x ./testy 
	./testy test_valgrind.org 1 2 3 4 5

prob2-valgrind: search_benchmark
	@chmod u+x ./testy 
	./testy test_valgrind.org 6 7 8 9 10

clean-tests :
	rm -rf test-results


