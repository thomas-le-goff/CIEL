#include <stdio.h>

int main(void)
{
    int sessions[6] = {2, 3, 5, 8, 7, 5};
    int nbMatieres = 0;

    scanf("%d\n", &nbMatieres);

    int derniereSession = 0;

    for (size_t i = 0; i < nbMatieres; i++)
    {
        char matiere;
        int nbSessions = 0;

        scanf("%c\n", &matiere);
        scanf("%d\n", &nbSessions);

        int nbHeures = 0;

        for (size_t j = 0; j < nbSessions; j++)
        {
            nbHeures += sessions[j + derniereSession];
            derniereSession += 1;
        }
        
        printf("Matiere : %c, NB heures : %d\n", matiere, nbHeures);
    }

    return 0;
}
