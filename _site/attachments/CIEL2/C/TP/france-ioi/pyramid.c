#include "stdio.h"

int main(int argc, char * argv[]) 
{
    int nbPierreFournie = 0;
    scanf("%d", &nbPierreFournie);

    int nbPierreUtile = 0;
    int nbEtage = 0;
    int nbPierreEtage = 1;

    while ((nbPierreFournie - nbPierreUtile) >= nbPierreEtage)
    {
        nbEtage++;
        nbPierreUtile += nbPierreEtage;
        nbPierreEtage = (nbEtage+1)*(nbEtage+1);
    }
    

    printf("%d\n", nbEtage);
    printf("%d\n", nbPierreUtile);
}
