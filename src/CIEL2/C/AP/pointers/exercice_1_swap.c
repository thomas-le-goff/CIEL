#include <stdio.h>

// Il est important de déclarer la fonction avant la fonction main
// int *x et int *y sont des paramètres du type "adresse d'un entier". 
// L'objet qui permet de manipuler une adresse se nomme un pointeur.
void swap(int *x, int *y)
{
    // on stock la valeur actuellement pointée par y (sauvegarde)
    int temp = *y;
    // la valeur actuellement pointée par y prend la valeur pointée par x.  
    *y = *x;

    // la valeur actuellement pointée par x prend la valeur pointée par temp (l'ancienne valeur pointée par y).  
    *x = temp;
}

int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 22;

    printf("Avant le swap : a = %d, b = %d. \n", a, b);

    // l'opérateur "&" permet de récupérer l'adresse d'une variable
    swap(&a, &b);

    printf("Après le swap : a = %d, b = %d. \n", a, b);

    return 0;
}
