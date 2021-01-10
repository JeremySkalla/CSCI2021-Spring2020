#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <format> <filename>\n",argv[0]);
    printf(" <format> is one of\n");
    printf(" text : text ints are in the given filename\n");
    printf(" int  : binary ints are in the given filename\n");
    printf(" 4bit : 4bit binary ints are in the given filename\n");
    return 1;
  }
  char *format = argv[1];
  char *fname = argv[2];

  int data_len = -13;
  int *data_vals = NULL;
  if( strcmp("text", format)==0 ){
    printf("Reading ints using function 'read_text_deltas()'\n");
    data_vals = read_text_deltas(fname, &data_len);
  }
  else if( strcmp("int", format)==0 ){
    printf("Reading ints using function 'read_int_deltas()'\n");
    data_vals = read_int_deltas(fname, &data_len);
  }
  // else if( strcmp("4bit", format)==0 ){
  //   printf("Reading 4bit binary int format\n");
  //   data_vals = read_4bit_deltas(fname, &data_len);
  // }
  else{
    printf("Unknown format '%s'\n",format);
    return 1;
  }

  if(data_vals != NULL){
    printf("Returned pointer was NOT null\n");
    printf("Read %d ints:\n",data_len);
    for(int i=0; i<data_len; i++){
      printf("[%2d] : %d\n",i,data_vals[i]);
    }
    printf("free()'ing memory for deltas\n");
    free(data_vals);
  }
  else{
    printf("Returned NULL pointer\n");
    printf("Read %d ints\n",data_len);
  }
  
  printf("Done\n");
  return 0;
}
