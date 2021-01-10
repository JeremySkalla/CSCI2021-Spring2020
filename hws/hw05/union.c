// union.c: shows use of a union to manipulate a memory area as an int
// OR as a float OR as an array of characters. Shows both typedef'd
// unions and one-off unions.

#include <stdio.h>
#include <string.h>

// Define a union which overlays bytes
typedef union {                          // shared memory between
  float fl;                              // an int (4 bytes) 
  int in;                                // a float (4 bytes)
  char ch[4];                            // char array (4 bytes)
} flint_t;                               // total size: 4 bytes   

int main(){
  printf("Typedef'd unions\n");

  flint_t flint;                         // 4 bytes, treat as either int or float
  flint.in = 0xC378C000;                 // assign an int value
  printf("%.4f\n",flint.fl);             // print as a float value
  printf("%08x %d\n",flint.in,flint.in); // print as a int value in hex/decimal
  for(int i=0; i<4; i++){                // print chars individually
    unsigned char c = flint.ch[i];
    printf("%d: %02x '%c'\n", i,c,c);
  }

  int mask = ~(0x80000000);              // invert bits leaving single 0 bit
  flint.in = flint.in & mask;            // bitwise AND with mask
  printf("%.4f\n",flint.fl);             // print as a float value

  ///////////////////////////////////////////////////////////////////////////////

  printf("\n");
  printf("Demonstrate one-off unions\n");

  union {                                // a one-off union
    int i;                               // parts of the union
    float f;
    char s[4];                
  } oneoff;                              // variable name of union

  strcpy(oneoff.s,"Bit");                // set the char values

  printf("%e\n",oneoff.f);               // print as a float value
  printf("%08x %d\n",oneoff.i,oneoff.i); // print as a int value in hex/decimal
  for(int i=0; i<4; i++){                // print chars individually
    char c = oneoff.s[i];
    printf("%d: %02x '%c'\n", i,c,c);
  }

  return 0;
}
