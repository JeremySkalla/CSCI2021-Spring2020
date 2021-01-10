// Comparison of col_minX implementations

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "matvec.h"

void check_answer(vector_t expect, vector_t actual, char *id);

typedef struct {
  char *id;
  int (*min_func)(matrix_t, vector_t);
} minfuncs_t;

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <rows> <cols>\n",argv[0]);
    return 1;
  }
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);

  minfuncs_t funcs[] = {
    {"col_mins1",col_mins1},
    {"col_mins2",col_mins2},
    {"col_mins3",col_mins3},
    {"col_mins4",col_mins4},
    {"col_mins5",col_mins5},
    {NULL, NULL}
  };  

  // Allocate the matrix and fill it in with 1,2,3,4...
  matrix_t mat;
  int ret = matrix_init(&mat, rows,cols);
  if(ret){ return ret; }
  matrix_fill_sequential(mat);

  // Variables for timing
  clock_t begin, end;
  double cpu_time;

  // Output vectors
  vector_t mins_a, mins_b;

  for(int i=0; funcs[i].id!=NULL; i++){
    minfuncs_t func = funcs[i];
    vector_init(&mins_b, mat.cols);
    begin = clock();
    ret = func.min_func(mat,mins_b);
    end = clock();
    cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
    printf("%14s CPU usage: %.4e sec\n",
           func.id,cpu_time);
    if(i==0){
      mins_a = mins_b;          // save result of first to compare to others
    }
    else{
      check_answer(mins_a, mins_b, func.id);
      vector_free_data(&mins_b); // free data
    }
  } 

  matrix_free_data(&mat);       // clean up data
  vector_free_data(&mins_a);

  return 0;
}

void check_answer(vector_t expect, vector_t actual, char *id){
  // Check answer
  for(int i=0; i<expect.len; i++){
    int e = VGET(expect,i);    
    int a = VGET(actual,i);
    if(e != a){
      printf("ERROR: %s produced incorrect results\n",id);
      printf("Element %d: expect %d  actual %d\n",i,e,a);
      break;
    }
  }
}
