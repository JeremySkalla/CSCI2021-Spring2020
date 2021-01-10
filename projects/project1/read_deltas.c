// Jeremy Skalla

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int *read_text_deltas(char *fname, int *len) {
    // File Checking
    struct stat fileStats;
    if (stat(fname, &fileStats) < 0 || (fileStats.st_size < sizeof(int))){
        *len = -1;
        return NULL;
    }
    FILE *inputFile = fopen(fname, "r");

    // Finding the correct length
    int length = 0;
    int *temp = malloc(sizeof(int));
    while (fscanf(inputFile, "%d", temp) == 1) {
        length++;
    }
    *len = length;

    // Allocating the pointer with the correct amount of memory then rewinding
    int *deltas = malloc(sizeof(int)* (*len));
    rewind(inputFile);

    // Putting original data into the pointer
    for (int i=0; i <= *len; i++) {
        if (i==0) {
            fscanf(inputFile, "%d", &deltas[i]);
        }
        else {
            fscanf(inputFile, "%d", &deltas[i]);
        }
    }

    // Editing data
    for (int i=1; i < *len; i++) {
        deltas[i] = deltas[i] + deltas[i-1];
    }

    // Closing the file and freeing the temp variable I used earlier
    fclose(inputFile);
    free(temp);

    return deltas;
}

int *read_int_deltas(char *fname, int *len) {
    //Using stat() to find out the file size and allocate it to a pointer
    struct stat fileStats;
    if (stat(fname, &fileStats) != 0 || fileStats.st_size < sizeof(int)) {
        *len = -1;
        return NULL;
    }
    int *deltas = malloc(fileStats.st_size);

    // Opening the file and running through the data, making delta changes as it goes
    *len = ((fileStats.st_size)/(sizeof(int)));

    FILE *inputFile = fopen(fname, "r");
    for (int i=0; i < *len; i++) {
        fread(&deltas[i], sizeof(int), 1, inputFile);
        if (i>0) {
            deltas[i] = deltas[i] + deltas[i-1];
        }
    }

    fclose(inputFile);

    return deltas;
}
