// Header for deltas problem

#ifndef DELTAS_H
#define DELTAS_H 1

int *read_text_deltas(char *fname, int *len);
int *read_int_deltas(char *fname, int *len);
int *read_4bit_deltas(char *fname, int *len);

void print_graph(int *data, int len, int max_height);

#endif
