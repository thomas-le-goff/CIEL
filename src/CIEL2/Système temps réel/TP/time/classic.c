#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    long long n = 0;

    if (argc > 1) {
        n = atoll(argv[1]);
    } else {
        printf("Entrez un entier positif n : ");
        if (scanf("%lld", &n) != 1 || n < 0) {
            fprintf(stderr, "Entrée invalide.\n");
            return 1;
        }
    }

    long long i;
    long long sum = 0;

    for (i = 1; i <= n; i++) {
        sum += i;
    }

    printf("La somme des entiers de 1 à %lld est : %lld\n", n, sum);

    return 0;
}