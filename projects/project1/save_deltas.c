#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"

#define MODE_TEXT  1
#define MODE_INT   2
#define MODE_4BIT  3

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <format> <filename>\n",argv[0]);
    printf("reads input from stdin and outputs in given format to <filename>\n");
    printf("if typing numbers in, press Ctrl-D to end input\n");
    printf(" <format> is one of\n");
    printf(" text : text ints are in the given filename\n");
    printf(" int  : binary ints are in the given filename\n");
    printf(" 4bit : 4bit binary ints are in the given filename\n");
    return 1;
  }
  char *format = argv[1];
  char *fname = argv[2];
  int mode = -1;
  if( strcmp("text", format)==0 ){
    mode = MODE_TEXT;
  }
  else if( strcmp("int", format)==0 ){
    mode = MODE_INT;
  }
  else if( strcmp("4bit", format)==0 ){
    mode = MODE_4BIT;
  }
  else{
    printf("Unknown format '%s'\n",format);
    return 1;
  }

  FILE *fout = fopen(fname,"w");
  int curr, prev;
  int result = fscanf(stdin,"%d",&curr); // handle first number
  if(result == EOF){
    fclose(fout);
    printf("error: no numbers given\n");
    return 1;
  }
  if(mode == MODE_TEXT){
    fprintf(fout,"%d ",curr);
  }
  else if(mode == MODE_INT || mode == MODE_4BIT ){
    fwrite(&curr,sizeof(int),1,fout);
  }

  int count = 1;
  prev=curr;

  while(fscanf(stdin,"%d",&curr) != EOF){
    if(mode == MODE_TEXT){
      int delta = curr - prev;
      fprintf(fout,"%d ",delta);
      prev = curr;
      count++;
    }
    else if(mode == MODE_INT){
      int delta = curr - prev;
      fwrite(&delta,sizeof(int),1,fout);
      prev = curr;
      count++;
    }
    else if(mode == MODE_4BIT){
      int prev2 = prev;
      prev = curr;
      if(fscanf(stdin,"%d",&curr) == EOF){
        printf("incorrect length of input for 4bit format\n");
        fclose(fout);
        return 1;
      }
      int delta1 = prev - prev2;
      int delta2 = curr - prev;
      // printf("[%d]: %d\n",count,delta1);
      // printf("[%d]: %d\n",count+1,delta2);
      if(delta1 > 7 || delta1 < -8 || delta2 > 7 || delta2 < -8){
        printf("index %d: too large for 4bit: %d %d\n",
               count,delta1, delta2);
        return 1;
      }
      char byte =
        ((delta1 << 0 ) & 0b00001111) |
        ((delta2 << 4 ) & 0b11110000);
      fwrite(&byte, 1, 1, fout);
      count+=2;
      prev = curr;
    }
  }
  if(MODE_TEXT){
    fprintf(fout,"\n");
  }
  fclose(fout);
  printf("wrote %d ints to %s in %s format\n",
         count, fname, format);
  return 0;
}
