// debug_scramble.c: accepts a command line argument integer which is
// an index into an array of 'responses': only one response will give
// success for the program.  The array is randomly scrambled making it
// difficult to determine where the correct response is located. This
// serves as motivation to use the debugger to determine the position
// at runtime.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 16

void pb_srand(unsigned long seed);
unsigned int pb_rand();

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("need a command line args: <int>\n");
    exit(1);
  }

  int guess = atoi(argv[1]);

  char *arr[SIZE];
  arr[0] = "you betcha";
  for(int i=1; i<SIZE; i++){
    arr[i] = "nope";
  }

  pb_srand(123456789);          // seed random number generator
  for(int i=0; i<100; i++){     // scramble
    int idx = abs(pb_rand()) % SIZE;
    int jdx = abs(pb_rand()) % SIZE;
    char *tmp = arr[idx];
    arr[idx] = arr[jdx];
    arr[jdx] = tmp;
  }

  if(strcmp(arr[guess],"you betcha") == 0){ // check guess
    printf("Oh yaaah! Have some hotdish\n");
    return 0;
  }
  else{
    printf("Ho dere: maybe have another look, eh?\n");
    return 1;
  }
}

unsigned long state = 1;

void pb_srand(unsigned long seed){
  state = seed;
}
unsigned int pb_rand() {
  state = state * 1103515245 + 12345;
  return (unsigned int)(state/65536) % 32768;
}

