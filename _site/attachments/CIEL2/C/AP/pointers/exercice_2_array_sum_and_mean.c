#include <stdio.h>

// Il est important de déclarer la fonction avant la fonction main.
// taille_tab contient la taille du tableau (le nombre d'éléments).
// tab correspond au tableau
// somme et moyenne sont des les adresses vers des variables qui recevront respectivement la valeur de la somme et celle de la moyenne.
void calculer_somme_moyenne(int taille_tab, int tab[taille_tab], int *somme, float *moyenne)
{
    // on s'assurer que les variables pointées ne contiennent pas déjà une valeur initiale.
    // pour la somme, si on ne fait pas cette opération le résultat risque d'être faux.
    *moyenne = 0;
    *somme = 0;

    // On itère sur le tableau pour faire la somme de ses éléments
    // size_t est le type utilisé pour les index.
    int *iter = tab;
    for (size_t i = 0; i < taille_tab; i++)
    {
        // il est important d'utiliser l'opérateur de déréférencement (*) pour modifier la valeur pointée et non pas l'adresse.
        *somme += *iter;

        // Incrémenter un pointeur permet de passer à "l'adresse suivante" c'est l'équivalent de "tab[i]"
        iter++;
    }

    // calcul de la moyenne, il est important de modifier le type de "taille_tab" (ou somme) pour avoir un résultat flottant (cast)
    *moyenne = (*somme) / (float)taille_tab;
}

int main(int argc, char const *argv[])
{
    int notes[] = {10, 12, 13, 14, 20, 15};
    int somme = 0;
    float moyenne = 0;

    // l'opérateur "&" permet de récupérer l'adresse d'une variable
    calculer_somme_moyenne(6, notes, &somme, &moyenne);

    printf("Somme = %d, moyenne = %.2f.\n", somme, moyenne);
}
