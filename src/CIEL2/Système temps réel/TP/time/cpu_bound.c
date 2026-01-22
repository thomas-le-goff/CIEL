#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    long long iterations = 500000000LL;
    if (argc > 1) {
        iterations = atoll(argv[1]);
    }

    volatile double x = 0.0;

    for (long long i = 0; i < iterations; i++) {
        x += sqrt((double)i);
    }

    printf("Résultat final : %f\n", x);

    return 0;
}