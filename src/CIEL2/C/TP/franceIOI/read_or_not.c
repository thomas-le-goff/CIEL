#include <stdio.h>

int strlen_hm(const char *str)
{
    char *c = str;
    while (c != '\0')
        c++;

    return (size_t)(c - str);
}

int main(void)
{
    int nbLivres = 0;
    int plsGrandTitre = 0;

    scanf("%d\n", &nbLivres);

    for (size_t i = 0; i < nbLivres; i++)
    {
        char titre[1001];
        scanf("%[^\n]\n", titre);

        int longueurTitre = strlen_hm(titre);

        if (longueurTitre > plsGrandTitre)
        {
            plsGrandTitre = longueurTitre;
            printf("%s\n", titre);
        }
    }

    return 0;
}