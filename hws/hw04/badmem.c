#include <stdio.h>
#include <stdlib.h>


// Struct to count positive/negative
// numbers in arrays.
typedef struct {
  int poss, negs;
} pn_t;

void set_pn(int *arr, int len, pn_t *pn);
// Scans through array arr counting positive/negative numbers and
// adjusting the fields of the specified. Zero is considered a
// positive number. If arr is NULL or len is less than 0, does not
// change pn.

int main(){
  int arr1[5] = {3, 0, -1, 7, -4};
  pn_t *pn1;
  set_pn(arr1, 5, pn1);
  // pn1: {.poss=3, .neg=2}
  
  int arr2[3] = {-1, -2, -4};
  pn_t *pn2;
  set_pn(arr2, 3, pn2);
  // pn2: {.poss=0, .neg=3}

  int *arr3 = NULL;
  pn_t *pn3;
  set_pn(arr3, -1, pn3);
  // pn3: NULL

  return 0;
}
  
void set_pn(int *arr, int len, pn_t * pn){
  if(arr==NULL || len < 0){
    return;
  }
  pn->negs = 0;
  pn->poss = 0;
  for(int i=0; i<len; i++){
    if(arr[i] < 0){
      pn->negs++;
    }
    else{
      pn->poss++;
    }
  }
  return;
}
