#include <stdlib.h>
#include <stdio.h>

int isPrime(int x) {
    int d;
    for (d = 2; d < x; d++)
        if (x % d == 0)
            return 0;
    return 1;
}

void main(int argc, char * * argv) {
    if (argc < 2) {
        fprintf(stderr, "Not enough parameters\n");
        exit(EXIT_FAILURE);
    }
    int x = atoi(argv[1]);
    if (isPrime(x)) {
        fprintf(stdout, "%d is prime\n", x);
    } else {
        fprintf(stdout, "%d is not prime\n", x);
    }
    exit(EXIT_SUCCESS);
}
