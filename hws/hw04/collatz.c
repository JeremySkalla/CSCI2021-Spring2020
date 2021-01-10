#include <stdio.h>

// "Optimized" version of collatz computation using bitwise operations
int collatz_bitwise(int n, int print_output){
  int neg_mask = 0x1 << 31;     // A
  if(n & neg_mask){             // A
    return -1;
  }
  int steps = 0;
  if(print_output){
    printf("Step %d: %d\n",steps,n);
  }
  while(n > 1){
    if(n & 0x1){                // B
      n = ((n << 2) - n) + 1;   // C
    }
    else{
      n = n >> 1;               // D
    }
    steps++;
    if(print_output){
      printf("Step %d: %d\n",steps,n);
    }
  }
  return steps;
}

// Main function to which makes use of Collatz functions.
int main(int argc, char **argv){
  int nstart;
  printf("Enter the starting integer: ");
  scanf("%d", &nstart);

  int verbose;
  printf("Show output of steps (0:NO, any other int: yes): ");
  scanf("%d", &verbose);

  int steps = collatz_bitwise(nstart,verbose);
  printf("The starting value %d converged to 1 in %d steps\n",
         nstart,steps);
  return 0;    
}

