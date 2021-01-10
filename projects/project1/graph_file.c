// Jeremy Skalla

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "deltas.h"

int main(int argc, char *argv[]) {
    // Basic argument setup
    if(argc < 3) {
      printf("usage: %s <format> <filename> <height>\n",argv[0]);
      printf(" <format> is one of\n");
      printf(" text : text ints are in the given filename\n");
      printf(" int  : binary ints are in the given filename\n");
      return 1;
    }
    char *format = argv[1];
    char *fname = argv[2];
    int height = atoi(argv[3]);

    // Pseudo-echo and reading the deltas
    int data_len = -69;
    int *data_vals = NULL;
    if( strcmp("text", format)==0 ) {
      printf("Reading text format\n");
      data_vals = read_text_deltas(fname, &data_len);
    }
    else if( strcmp("int", format)==0 ) {
      printf("Reading int format\n");
      data_vals = read_int_deltas(fname, &data_len);
    }
    else {
      printf("Unknown format '%s'\n",format);
      return 1;
    }

    print_graph(data_vals, data_len, height);

    // Freeing deltas
    free(data_vals);

    return 0;
}
