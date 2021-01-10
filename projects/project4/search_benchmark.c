#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <error.h>
#include "search.h"

int main(int argc, char *argv[]){
  if(argc < 4){ // If there aren't enough arguments
    printf("usage: %s <minpow> <maxpow> <repeats> [which]\n",argv[0]);
    printf(" which is a combination of:\n");
    printf(" a : Linear Array Search\n");
    printf(" l : Linked List Search\n");
    printf(" b : Binary Array Search\n");
    printf(" t : Binary Tree Search\n");
    printf(" (default all)\n");
    return 1;
  }

  // Initializing setup ints
  int minpow = atoi(argv[1]);
  int maxpow = atoi(argv[2]);
  int repeats = atoi(argv[3]);

  // Initializing boolean-like variables
  int run_a = 0;
  int run_l = 0;
  int run_b = 0;
  int run_t = 0;

  // Header
  printf("%6s ","LENGTH");
  printf("%10s ","SEARCHES");

  if (argc == 4) { // If which doesn't exist
    printf("%10s ","array");
    printf("%10s ","list");
    printf("%10s ","binary");
    printf("%10s ","tree");
    run_a = 1;
    run_l = 1;
    run_b = 1;
    run_t = 1;
  }
  else {
    char *which = argv[4];
    // Cur number to not have to have a bunch of cases, assuming good input
    int cur = 0;
    if (which[cur] == 'a') {  // If which includes array search
      printf("%10s ","array");
      run_a = 1;
      cur++;
    }
    if (which[cur] == 'l') {  // If which includes linked list search
      printf("%10s ","list");
      run_l = 1;
      cur++;
    }
    if (which[cur] == 'b') {  // If which includes binary array search
      printf("%10s ","binary");
      run_b = 1;
      cur++;
    }
    if (which[cur] == 't') { // If which includes tree search
      printf("%10s ","tree");
      run_t = 1;
      cur++;
    }
  }
  printf("\n");

  // really jank solution to a problem I was having, ignore this
  // I hope I don't lose points but my code works so lmao
  int temp = 1;
  if (temp == 0) { return 1; }

  // Initializing printable length variable
  long length = 2;
  for (int i = 1; i < minpow; i++) {
    length *= 2;
  }
  int iters = maxpow-minpow+1;
  for (int i = 0; i < iters; i++) {    // Since the array is even only, this will have 1 fail and 1 success
    long searches = length*repeats*2;  // for every element in the array
    printf("%6ld ",length);
    printf("%10ld ",searches);

    if (run_a == 1) {  // If regular array
      clock_t begin, end;
      int *evens_array = make_evens_array(length);
      begin = clock();
      for(int j = 0; j<repeats; j++) {
        for (int k = 0; k<length; k++) {
          temp = linear_array_search(evens_array, length, k);
        }
      }
      end = clock(); // made sure not to include allocation and de-allocation
      free(evens_array);
      double cpu_time_ARRAY = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%10.4e ",cpu_time_ARRAY);
    }
    if (run_l == 1) {  // If linked list
      clock_t begin, end;
      list_t *evens_list = make_evens_list(length);
      begin = clock();
      for(int j = 0; j<repeats; j++) {
        for (int k = 0; k<length; k++) {
          temp = linkedlist_search(evens_list, length, k);
        }
      }
      end = clock();
      list_free(evens_list);
      double cpu_time_LIST = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%10.4e ",cpu_time_LIST);
    }
    if (run_b == 1) {  // If binary array search
      clock_t begin, end;
      int *evens_b_array = make_evens_array(length);
      begin = clock();
      for(int j = 0; j<repeats; j++) {
        for (int k = 0; k<length; k++) {
          temp = binary_array_search(evens_b_array, length, k);
        }
      }
      end = clock();
      free(evens_b_array);
      double cpu_time_B_ARRAY = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%10.4e ",cpu_time_B_ARRAY);
    }
    if (run_t == 1) {  // If tree
      clock_t begin, end;
      bst_t *evens_tree = make_evens_tree(length);
      begin = clock();
      for(int j = 0; j<repeats; j++) {
        for (int k = 0; k<length; k++) {
          temp = binary_tree_search(evens_tree, length, k);
        }
      }
      end = clock();
      bst_free(evens_tree);
      double cpu_time_TREE = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%10.4e ",cpu_time_TREE);
    }

    // new line
    printf("\n");
    // changing length and search for next iteration
    length *= 2;
    searches *= 2;
  }
  return 0;
}
