CFLAGS = -Wall -Werror -g 
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	clock_main \
	puzzlebox   \


all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o

############################################################
# 'make zip' to create p1-code.zip for submission
AN=p2
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi


# clock problem
clock_main : clock_main.o clock_sim.o clock_update.o
	$(CC) -o $@ $^

clock_main.o : clock_main.c clock.h
	$(CC) -c $<

clock_sim.o : clock_sim.c clock.h
	$(CC) -c $<

clock_update.o : clock_update.c clock.h
	$(CC) -c $<


# debugging problem
puzzlebox.o : puzzlebox.c
	$(CC) -c $<

puzzlebox : puzzlebox.o
	$(CC) -o $@ $^


# Testing Targets
test-setup :
	@chmod u+rx testy

test: test-prob1 test-prob2


test-prob1: clock_main test_clock test-setup
	./testy test_prob1.org $(testnum)

test_clock : test_clock.c clock_sim.o clock_update.o
	$(CC) -o $@ $^

test-prob2 : puzzlebox
	./puzzlebox input.txt

clean-tests : clean
	rm -f test-data/*.tmp test_clock

