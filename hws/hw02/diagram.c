// Construct memory diagrams for the blocks below
#include <stdio.h>
int main(int argc, char *argv[]){

  // BLOCK A
  int a = 5;
  int b = 7;
  double x = 4.5;
  int *ip = &a;
  ip = &b;
  int c = *ip;
  *ip = 19;
  // DRAW MEMORY HERE 

  // BLOCK B
  int arr[4] = {12, 14, 16, 18};
  int *arp = arr;
  int brr = 11;
  arr[1] = 23;
  arp[3] = 29;
  arp = &arr[2];
  *arp = brr;
  // *arp = 3;
  // DRAW MEMORY HERE 

  // BLOCK C
  char *cp = NULL;
  char str[8] = "hello";
  str[5] = 'w';
  cp = str + 6;
  *cp = '\0';
  str[0] = 'y';
  // DRAW MEMORY HERE 
}
  
  
  
