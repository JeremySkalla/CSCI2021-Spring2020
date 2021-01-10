CFLAGS = -Wall -g -lm
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	save_deltas \
	deltas_main \
	graph_demo \
	graph_file \
	treemap_main \

all : prob1 prob2 prob3

AN=p1
zip :
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi

clean :
	rm -f $(PROGRAMS) *.o

# deltas problem
prob1 : deltas_main save_deltas

deltas_main.o : deltas_main.c deltas.h
	$(CC) -c $<

deltas_main : deltas_main.o read_deltas.o
	$(CC) -o $@ $^

read_deltas.o : read_deltas.c deltas.h
	$(CC) -c $<

save_deltas.o : save_deltas.c deltas.h
	$(CC) -c $<

save_deltas : save_deltas.o 
	$(CC) -o $@ $^

# graphing problem
prob2 : graph_demo graph_file save_deltas

print_graph.o : print_graph.c
	$(CC) -c $<

graph_demo.o : graph_demo.c
	$(CC) -c $<

graph_demo : graph_demo.o print_graph.o
	$(CC) -o $@ $^

graph_file.o : graph_file.c
	$(CC) -c $<

graph_file : graph_file.o print_graph.o read_deltas.o
	$(CC) -o $@ $^

# treemap problem
prob3 : treemap_main

treemap_main : treemap_main.o treemap_funcs.o
	$(CC) -o $@ $^

treemap_main.o : treemap_main.c treemap.h
	$(CC) -c $<

treemap_funcs.o : treemap_funcs.c treemap.h
	$(CC) -c $<

# tree problem
tree_main : tree_main.o tree_funcs.o
	$(CC) -o $@ $^

tree_main.o : tree_main.c tree.h
	$(CC) -c $<

tree_funcs.o : tree_funcs.c tree.h
	$(CC) -c $<

# Testing Targets
test : test-prob1 test-prob2 test-prob3

test-prob1 : prob1
	@chmod u+x testy
	./testy test_prob1.org $(testnum)

test-prob2 : prob2
	@chmod u+x testy
	./testy test_prob2.org $(testnum)

test-prob3 : prob3
	@chmod u+x testy
	./testy test_prob3.org $(testnum)

clean-tests :
	rm -rf test-results
