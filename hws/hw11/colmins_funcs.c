#include "matvec.h"

// Baseline version
int col_mins1(matrix_t mat, vector_t cmins){
  if(mat.cols != cmins.len){
    printf("size mismatch: mat.cols %ld != cmins.len %ld\n",
           mat.cols,cmins.len);
    return 1;
  }

  for(int j=0; j<mat.cols; j++){
    VSET(cmins, j, MGET(mat,0,j));
    for(int i=1; i<mat.rows; i++){
      if(MGET(mat,i,j) < VGET(cmins,j)){
        VSET(cmins, j, MGET(mat,i,j));
      }
    }
  }
  return 0;
}

// Use of local variables rather than repeated memory references in
// VGET() and MGET() macros.
int col_mins2(matrix_t mat, vector_t cmins){
  if(mat.cols != cmins.len){
    printf("size mismatch: mat.cols %ld != cmins.len %ld\n",
           mat.cols,cmins.len);
    return 1;
  }
  for(int j=0; j<mat.cols; j++){
    int min = MGET(mat,0,j);
    for(int i=1; i<mat.rows; i++){
      int x = MGET(mat,i,j);
      if(x < min){
        min = x;
      }
    }
    VSET(cmins, j, min);
  }
  return 0;
}

// Unroll inner loop to enable more pipelining
int col_mins3(matrix_t mat, vector_t cmins){
  if(mat.cols != cmins.len){
    printf("size mismatch: mat.cols %ld != cmins.len %ld\n",
           mat.cols,cmins.len);
    return 1;
  }

  for(int j=0; j<mat.cols; j++){
    int min_0 = MGET(mat,0,j);  // assumes rows >= 4
    int min_1 = MGET(mat,1,j);
    int min_2 = MGET(mat,2,j);
    int min_3 = MGET(mat,3,j);
    int i;
    for(i=4; i<mat.rows; i+=4){ // unroll x4 for pipelining
      int x_0 = MGET(mat,i+0,j);
      if(x_0 < min_0){
        min_0 = x_0;
      }
      int x_1 = MGET(mat,i+1,j);
      if(x_1 < min_1){
        min_1 = x_1;
      }
      int x_2 = MGET(mat,i+2,j);
      if(x_2 < min_2){
        min_2 = x_2;
      }
      int x_3 = MGET(mat,i+3,j);
      if(x_3 < min_3){
        min_3 = x_3;
      }
    }
    for(; i<mat.rows; i++){     // cleanup loop
      int x_0 = MGET(mat,i+0,j);
      if(x_0 < min_0){
        min_0 = x_0;
      }
    }      
    // consolidate minimum of locals
    int min_a = (min_0 < min_1) ? min_0 : min_1;
    int min_b = (min_2 < min_3) ? min_2 : min_3;
    int min = (min_a < min_b) ? min_a : min_b;
    VSET(cmins, j, min);
  }
  return 0;
}

// Unroll outer loop to enable more pipelining
int col_mins4(matrix_t mat, vector_t cmins){
  if(mat.cols != cmins.len){
    printf("size mismatch: mat.cols %ld != cmins.len %ld\n",
           mat.cols,cmins.len);
    return 1;
  }

  int j;
  for(j=0; j<mat.cols; j+=4){ // unroll x4 for pipelining
    int min_0 = MGET(mat,0,j+0);  // assumes cols >= 4
    int min_1 = MGET(mat,0,j+1);  // deal with 4 columns at a time
    int min_2 = MGET(mat,0,j+2);
    int min_3 = MGET(mat,0,j+3);
    for(int i=1; i<mat.rows; i++){  // iterate over every row
      int x_0 = MGET(mat,i,j+0);
      if(x_0 < min_0){
        min_0 = x_0;
      }
      int x_1 = MGET(mat,i,j+1);
      if(x_1 < min_1){
        min_1 = x_1;
      }
      int x_2 = MGET(mat,i,j+2);
      if(x_2 < min_2){
        min_2 = x_2;
      }
      int x_3 = MGET(mat,i,j+3);
      if(x_3 < min_3){
        min_3 = x_3;
      }
    }
    VSET(cmins,j+0,min_0);      // set mins for 4 columns
    VSET(cmins,j+1,min_1);
    VSET(cmins,j+2,min_2);
    VSET(cmins,j+3,min_3);
  }
  for(; j<mat.cols; j++){      // cleanup loop
    int min_0 = MGET(mat,0,j+0);
    for(int i=1; i<mat.rows; i++){  // iterate over every row
      int x_0 = MGET(mat,i,j+0);
      if(x_0 < min_0){
        min_0 = x_0;
      }
    }
    VSET(cmins,j+0,min_0);
  }
  return 0;
}



// Re-arrange iteration pattern to favor memory access across rows
int col_mins5(matrix_t mat, vector_t cmins){
  if(mat.cols != cmins.len){
    printf("size mismatch: mat.cols %ld != cmins.len %ld\n",
           mat.cols,cmins.len);
    return 1;
  }

  for(int j=0; j<cmins.len; j++){
    VSET(cmins,j, MGET(mat,0,j));
  }

  for(int i=0; i<mat.rows; i++){
    for(int j=0; j<mat.cols; j++){
      int x = MGET(mat,i,j);
      if(x < VGET(cmins,j)){
        VSET(cmins,j,x);
      }
    }
  }
  return 0;
}

