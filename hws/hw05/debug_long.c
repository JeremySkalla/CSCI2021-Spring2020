// debug_long.c: debugging exercise which uses a union to share memory
// between a 8-byte long and an 8-byte character array.  The correct
// command line argument must be given as a character string to match
// the numeric long. the correct input can be determined by using the
// debugger to stop the program and examine the memory location as a
// string.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  union {                       // shared memory between
    long lo;                    // an long (8 bytes) 
    char ch[8];                 // char array (8 bytes)
  } chlo;                       // total size: 8 bytes   

  // Demonstrate that memory can be interpretted as...
  strcpy(chlo.ch,"Dude??");
  printf("chlo.lo: %016lx (hex)\n", chlo.lo,chlo.lo);  // as a number
  printf("chlo.lo: %ld (decimal)\n",chlo.lo);
  printf("chlo.ch: %s\n",chlo.ch);                     // as a string

  if(argc < 2){
    printf("need a command line arg: string\n");
    exit(1);
  }
  long lng = 36783801071443;    // what IS lng??
  
  union{
    long lo;
    char ch[8];
  } chlo2;

  strcpy(chlo2.ch, argv[1]);

  if(chlo2.lo == lng){
    printf("Yup, equal!\n");
    return 0;
  }
  else{
    printf("Nope, not equal... And then?\n");
    return -1;
  }
}
