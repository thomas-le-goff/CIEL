#include "stdio.h"
#include "math.h"

int main(int argc, char * argv[] ) 
{
    int position = 0;
    int nbVillage = 0;
    int nbVillageProche = 0;

    scanf("%d", &position);
    scanf("%d", &nbVillage);

    for (int i = 0; i < nbVillage; i++)
    {
        int posVillage = 0;
        scanf("%d", &posVillage);
    
        if (abs(position - posVillage) <= 50)
        {
            nbVillageProche++;
        }
    }
    
    printf("%d", nbVillageProche);
}
