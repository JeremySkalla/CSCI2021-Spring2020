#include <stdio.h>

int main(int arc, char **argv) {
    int c = ~(0x80001000);
    int d = 0x80001000;
    printf("%d\n", c);
    printf("%d\n", d);
}
