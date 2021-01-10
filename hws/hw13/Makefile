CFLAGS = -Wall -g -Og
CC     = gcc $(CFLAGS)

all: memory_parts print_department

memory_parts : memory_parts.c
	$(CC) -o $@ $^		

print_department : print_department.c
	$(CC) -o $@ $^		

make_dept_directory : make_dept_directory.c
	$(CC) -o $@ $^		

datfile : make_dept_directory
	./make_dept_directory cse_depts.dat

clean:
	rm -f *.o memory_parts print_department make_dept_directory
