#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void trouver_min_max(const int *t, int taille, int *min, int *max)
{
    *min = INT_MAX;
    *max = INT_MIN;

    for (size_t i = 0; i < taille; i++)
    {
        // malgré que t soit un pointeur il est possible d'utiliser la syntaxe d'indexation (offset d'adresse)
        if (t[i] < *min)
        {
            *min = t[i];
        }
        if (t[i] > *max)
        {
            *max = t[i];
        }
    }
}

int main(int argc, char const *argv[])
{
    int n = 0;

    // On récupère le nombre d'éléments que l'utilisateur souhaite renseigner
    printf("Combien d'éléments souhaitez-vous renseigner ? ");
    scanf("%d", &n);

    int *tab = malloc(n);

    if (tab == NULL)
    {
        printf("Une erreur d'allocation est survenue.");
        return 1;
    }

    for (size_t i = 0; i < n; i++)
    {
        printf("Saisissez la valeur N°%zu : ", i);
        scanf("%d", &tab[i]);
    }

    int min = 0;
    int max = 0;

    trouver_min_max(tab, n, &min, &max);

    printf("Minimum = %d, maximum = %d\n", min, max);

    free(tab);

    return 0;
}