// optimized versions of matrix diagonal summing
#include "matvec.h"
#include <stdlib.h>

// You can write several different versions of your optimized function
// in this file and call one of them in the last function.

int sumdiag_VER1(matrix_t mat, vector_t vec) {
  // local variables for all non-pointer fields
  long len = vec.len;
  long rows = mat.rows;
  long cols = mat.cols;
  if(len != (rows + cols - 1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }

  int *vdata = vec.data;                                  // local variable for the vector data
  for(int i=0; i<len; i++){                               // diagonal sums to all 0s
    vdata[i] = 0;
  }

  int *mdata = mat.data;                                  // local variable for the matrix data
  for(int r=0; r < rows; r++){                            // run thru in row-column order
    int c = 0;
    for(int d=rows-r-1; d<rows; d++,c++){
      // printf("\nr = %d , c = %d , d = %d ", r,c,d);    //debug stuff
      vdata[d] = (mdata[(r * cols) + c] + vdata[d]);      // add onto the diag sum
    }
  }

  for(int r=0; r < rows-1; r++){                           // run thru in row-column order
    int d = cols;
    for(int c=r+1; c<cols; c++,d++){
      // printf("\nr = %d , c = %d , d = %d ", r,c,d);    // debug stuff
      vdata[d] = (mdata[(r * cols) + c] + vdata[d]);      // add onto the diag sum
    }
  }
  return 0;                                               // return success
}

int sumdiag_VER2(matrix_t mat, vector_t vec) {
  return 0;
}

int sumdiag_OPTM(matrix_t mat, vector_t vec) {
  // call your preferred version of the function
  return sumdiag_VER1(mat, vec);
}
