// Jeremy Skalla

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void print_graph(int *data, int len, int max_height) {
    int min = data[0];
    int max = data[0];
    for (int i = 0; i < len; i++) { // Determines mins and maxes
        if (min > data[i]) {
            min = data[i];
        }
        else if (max < data[i]) {
            max = data[i];
        }
    }
    int range = max-min;
    double units_per_height = range / ((double)max_height);

    printf("length: %d\n", len);
    printf("min: %d\n", min);
    printf("max: %d \n", max);
    printf("range: %d\n", range);
    printf("max_height: %d\n", max_height);
    printf("units_per_height: %.2f\n", units_per_height); //Figure out how to format floats

    //Printing the top line
    printf("     ");
    for (int i = 0; i < len; i++) {
        if ((i % 5) == 0) {
            printf("+");
        }
        else {
            printf("-");
        }
    }
    printf("\n");

    //Printing data
    int current_height;
    for (int i = max_height; i >= 0; i--) {
        current_height = (int)(min + (i * units_per_height));
        printf("%3d |", current_height);
        for (int j = 0; j < len; j++) {
            if (data[j] >= current_height) {
                printf("X");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    //Printing bottom line
    printf("     ");
    for (int i = 0; i < len; i++) {
        if ((i % 5) == 0) {
            printf("+");
        }
        else {
            printf("-");
        }
    }
    printf("\n");

    //Printing axis
    printf("     ");
    for (int i = 0; i < len; i++) {
        if ((i % 5) == 0) {
            printf("%d", i);
        }
        else if (((i-1) % 5) == 0 && i>10) {
            continue;
        }
        else {
            printf(" ");
        }
    }
    printf("\n");
}
