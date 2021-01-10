#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int hours = 11;
    int minutes = 42;
    int min_ones = minutes % 10;
    int min_tens = (minutes - min_ones)/10;
    int hour_ones = hours % 10;
    int hour_tens = (hours - hour_ones)/10;
    return 0;
}
