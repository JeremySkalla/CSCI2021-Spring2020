#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <error.h>
#include "search.h"

typedef int (*search_t)(void*,int,int);
typedef void* (*setup_t)(int);
typedef void (*cleanup_t)(void *);

typedef struct {
  char *id; // Printable name, no use for full name as never printed
  char letter; // to help with the which field
  int run;  // to know whether to run the specific type of data testing or not
  int (*search_t)(void*, int, int); // search algorithm
  void* (*setup_t)(int); // setup function
  void (*cleanup_t)(void*); // cleanup function
} searchalg_t;

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

  searchalg_t algs[] = { // Table of search algs
    {"array", 'a', 1, (search_t) linear_array_search, (setup_t) &make_evens_array, (cleanup_t) free},
    {"list", 'l', 1, (search_t) linkedlist_search, (setup_t) &make_evens_list, (cleanup_t) list_free},
    {"binary", 'b', 1, (search_t) binary_array_search, (setup_t) &make_evens_array, (cleanup_t) free},
    {"tree", 't', 1, (search_t) binary_tree_search, (setup_t) &make_evens_tree, (cleanup_t) bst_free},
    {NULL}
  };

  // Header
  printf("%6s ","LENGTH");
  printf("%10s ","SEARCHES");

  // Header pt 2
  if (argc == 4) { // If no input for which
    for (int i = 0; algs[i].id != NULL; i++) {
      printf("%10s ",algs[i].id);
    }
  }
  else {  // If specified which
    char *which = argv[4];
    // Cur number to not have to have a bunch of cases, assuming good input
    int cur = 0;
    for (int i = 0; algs[i].id != NULL; i++) {
      if (which[cur] != algs[i].letter) {
        algs[i].run = 0;
      }
      else {
        printf("%10s ",algs[i].id);
        cur++;
      }
    }
  }
  printf("\n");

  // really jank solution to a problem I was having, ignore this
  // to explain, basically, it says I wasn't using temp at all but I was
  // so I just ran this to make the compiler shut up
  int temp = 1;
  if (temp == 0) { return 1; }


  // Initializing printable length variable
  long length = 2;
  for (int i = 1; i < minpow; i++) {
    length *= 2;
  }
  int iters = maxpow-minpow+1;
  for (int i = 0; i < iters; i++) {
    long searches = length*repeats*2;
    printf("%6ld ",length);
    printf("%10ld ",searches);
    for (int j = 0; algs[j].id != NULL; j++) {
      clock_t begin, end;
      searchalg_t alg = algs[j];
      void *temp2 = alg.setup_t(length);
      begin = clock();
      for(int k = 0; k<repeats; k++) {
        for (int a = 0; a<length; a++) {
          temp = alg.search_t(temp2, length, a);
        }
      }
      end = clock();
      alg.cleanup_t(temp2);
      double cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
      printf("%10.4e ",cpu_time);
    }
    // new line
    printf("\n");
    // changing length and search for next iteration
    length *= 2;
    searches *= 2;
  }
  return 0;
}
