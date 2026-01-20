#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <fichier_source> <fichier_destination>\n", argv[0]);
        return 1;
    }

    const char *src_path = argv[1];
    const char *dst_path = argv[2];

    FILE *src = fopen(src_path, "rb");
    if (!src) {
        perror("Erreur ouverture source");
        return 1;
    }

    FILE *dst = fopen(dst_path, "wb");
    if (!dst) {
        perror("Erreur ouverture destination");
        fclose(src);
        return 1;
    }

    int c;
    while ((c = fgetc(src)) != EOF) {
        if (fputc(c, dst) == EOF) {
            perror("Erreur écriture");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    fclose(src);
    fclose(dst);

    printf("Copie terminée.\n");
    return 0;
}