// Demonstrate two's complement in C
#include <stdio.h>
int main(){
  char num = 0b01011100;
  //  char num = 92;            // initial signed positive number
  char neg = (~num) + 1;        // negate: invert bits (~ operator) and add 1
  char pos = (~neg) + 1;        // positive: invert then add 1
  printf("%d %d %d\n",          // print number, negated version, and positive
         num,neg,pos);
  return 0;
}
