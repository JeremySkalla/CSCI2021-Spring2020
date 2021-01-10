#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// scale array x by multiplyin each element by a
void ax(int a, int *x, long len ){
  long i;
  for(i=0; i<len-4; i+=4){
    x[i+0] *= a;
    x[i+1] *= a;
    x[i+2] *= a;
    x[i+3] *= a;
  }
  for(; i<len; i++){
    x[i+0] *= a;
  }    
}

// add arrays x and y storing in x
void xpy(int *x, int *y, long len ){
  long i;
  for(i=0; i<len-4; i+=4){
    x[i+0] += y[i+0];
    x[i+1] += y[i+1];
    x[i+2] += y[i+2];
    x[i+3] += y[i+3];
  }
  for(; i<len; i++){
    x[i+0] += y[i+0];
  }    
}

// multiply each el of x by a and add on y
int axpy(int a, int *x, int *y, long len ){
  long i;
  for(i=0; i<len-4; i+=4){
    x[i+0] = a*x[i+0] + y[i+0];
    x[i+1] = a*x[i+1] + y[i+1];
    x[i+2] = a*x[i+2] + y[i+2];
    x[i+3] = a*x[i+3] + y[i+3];
  }
  for(; i<len; i++){
    x[i+0] = a*x[i+0] + y[i+0];
  }
  // timing fairness loops
  for(i=0; i<len-4; i+=4){}
  for(; i<len; i++){}
}

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <minsize> <maxsize>\n",argv[0]);
    return 1;
  }
  int minsize = atoi(argv[1]);
  int maxsize = atoi(argv[2]);

  printf("%10s ","SIZE");
  printf("%10s ","ax xpy");
  printf("%10s ","axpy");
  printf("\n");

  for(long s=minsize; s<=maxsize; s++){
    long size = 1 << s;

    printf("%10ld ",size);

    int *x1 = malloc(sizeof(int)*size);
    int *x2 = malloc(sizeof(int)*size);
    int *y  = malloc(sizeof(int)*size);
    for(long i=0; i<size; i++){
      x1[i] = i;
      x2[i] = i;
      y[i]  = i;
    }

    clock_t begin, end;
    int a = 19;
    
    begin = clock();
    ax(a,x1,size);
    xpy(x1,y,size);
    end = clock();
    double cpu_time1 = ((double) (end - begin)) / CLOCKS_PER_SEC;
    printf("%10.4e ",cpu_time1);
      
    begin = clock();
    axpy(a,x2,y,size);
    end = clock();
    double cpu_time2 = ((double) (end - begin)) / CLOCKS_PER_SEC;
    printf("%10.4e ",cpu_time2);

    printf("\n");

    // Check answer
    for(long i=0; i<size; i++){
      assert(x1[i] == x2[i]);
    }

    free(x1);
    free(x2);
    free(y);
  }

  return 0;
}
