#include <stdio.h>
#include <string.h>

int main(void)
{
    int nbLivres = 0;
    int plsGrandTitre = 0;

    scanf("%d\n", &nbLivres);

    for (size_t i = 0; i < nbLivres; i++)
    {
        char titre[1000];
        scanf("%[^\n]\n", titre);

        int longueurTitre = strlen(titre);

        if (longueurTitre > plsGrandTitre)
        {
            plsGrandTitre = longueurTitre;
            printf("%s\n", titre);
        }
    }

    return 0;
}