#include "stdio.h"
#include "math.h"
#include "limits.h"

int main(int argc, char * argv[] ) 
{
    int nbMarchands = 0;
    int prixMin = INT_MAX;
    int prixMinPos = -1;

    scanf("%d", &nbMarchands);

    for (int i = 1; i <= nbMarchands; i++)
    {
        int prixMarchand = 0;
        scanf("%d", &prixMarchand);

        if (prixMarchand <= prixMin) 
        {
            prixMin = prixMarchand;
            prixMinPos = i;
        }
    }
    
    printf("%d", prixMinPos);

    return 0;
}
