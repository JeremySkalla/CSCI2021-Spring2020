// Comparison of row-wise and column-wise summing

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "matvec.h"

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <rows> <cols>\n",argv[0]);
    return 1;
  }
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);

  // Allocate the matrix and fill it in with 1,2,3,4...
  matrix_t mat;
  int ret = matrix_init(&mat, rows,cols);
  if(ret){ return ret; }
  matrix_fill_sequential(mat);

  // Variables for timing
  clock_t begin, end;
  double cpu_time;

  // ROW SUMS
  vector_t rsums;
  vector_init(&rsums, mat.rows);
  vector_fill_sequential(rsums);
  begin = clock();                 // get current moment
  ret = row_sums(mat,rsums);       // run row_sums
  end = clock();                   // get later moment to compare to start
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%14s CPU usage: %.4e sec\n", "row_sums",cpu_time);

  // COL SUMS
  vector_t csums;
  vector_init(&csums, mat.cols);
  vector_fill_sequential(csums);
  begin = clock();                 // get current moment
  ret = col_sums(mat,csums);       // run col_sums
  end = clock();                   // get later moment to compare to start
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%14s CPU usage: %.4e sec\n", "col_sums",cpu_time);

  // OPT_COL SUMS
  vector_t ocsums;
  vector_init(&ocsums, mat.cols);
  vector_fill_sequential(ocsums);
  begin = clock();                 // get current moment
  ret = opt_col_sums(mat,ocsums);  // run opt_col_sums
  end = clock();                   // get later moment to compare to start
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%14s CPU usage: %.4e sec\n", "opt_col_sums",cpu_time);

  // Check answer
  for(int i=0; i<csums.len; i++){
    int cs = VGET(csums,i);
    int os = VGET(ocsums,i);
    if(cs != os){
      printf("ERROR: opt_col_sums produced incorrect results\n");
      printf("Element %d: expect %d  actual %d\n",i,cs,os);
      break;
    }
  }
  vector_free_data(&ocsums);

  matrix_free_data(&mat);       // clean up data
  vector_free_data(&rsums);
  vector_free_data(&csums);

  return 0;
}
