#include <stdio.h>

#define MAX_DEPLACEMENTS 1000
#define MAX_TYPE_DEPLACEMENT 6

int main(void)
{
    int deplacementsInverses[MAX_TYPE_DEPLACEMENT] = {-1, 2, 1, 3, 5, 4};
    int nbDeplacements = 0;

    scanf("%d", &nbDeplacements);

    if (nbDeplacements > MAX_DEPLACEMENTS)
    {
        return -1;
    }

    int parcours[nbDeplacements];

    for (size_t i = 0; i < nbDeplacements; i++)
    {
        scanf("%d", &parcours[i]);
    }

    for (size_t i = nbDeplacements; i > 0; i--)
    {
        int deplacement = parcours[i - 1];
        if (deplacement >= MAX_TYPE_DEPLACEMENT)
        {
            return -1;
        }

        int deplacementInverse = deplacementsInverses[deplacement];
        printf("%d\n", deplacementInverse);
    }

    return 0;
}