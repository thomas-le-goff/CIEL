#include <stdio.h>
#include <string.h>

int main(void)
{
    int nbLignes = 0;

    scanf("%d", &nbLignes);

    for (size_t i = 0; i < nbLignes; i++)
    {
        char ligne[1000];
        char ligneInverse[1000];

        scanf(" %[^\n]", ligne);

        int tailleLigne = strlen(ligne);

        for (int j = tailleLigne - 1; j >= 0; j--)
        {
            ligneInverse[tailleLigne - j - 1] = ligne[j];
        }

        ligneInverse[tailleLigne] = '\0';

        printf("%s\n", ligneInverse);
    }

    return 0;
}
