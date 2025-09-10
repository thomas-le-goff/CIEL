#include "stdio.h"

int in_rect(int x, int y, int r_x1, int r_x2, int r_y1, int r_y2)
{
    return x >= r_x1 && x <= r_x2 && y >= r_y1 && y <= r_y2;
}

int main(int argc, char *argv[])
{
    int nbJetons = 0;

    scanf("%d", &nbJetons);

    for (int i = 0; i < nbJetons; i++)
    {
        int x = 0;
        int y = 0;

        scanf("%d", &x);
        scanf("%d", &y);

        if (!in_rect(x, y, 0, 90, 0, 70))
        {
            printf("En dehors de la feuille\n");
        }

        else if (in_rect(x, y, 10, 85, 10, 55) && !(in_rect(x, y, 25, 50, 20, 45)))
        {
            printf("Dans une zone bleue\n");
        }
        else if (in_rect(x, y, 15, 45, 60, 90) || in_rect(x, y, 60, 85, 60, 90))
        {
            printf("Dans une zone rouge\n");
        }
        else
        {
            printf("Dans une zone jaune\n");
        }
    }

    return 0;
}

// int main(int argc, char * argv[] )
// {
//     int nbJetons = 0;

//     scanf("%d", &nbJetons);

//     for (int i = 0; i < nbJetons; i++)
//     {
//         int x = 0;
//         int y = 0;

//         scanf("%d", &x);
//         scanf("%d", &y);

//         if (x < 0 || x > 90 || y < 0 || y > 70)
//         {
//             printf("En dehors de la feuille\n");
//         }

//         else if (x >= 10 && x <= 85 && y >= 10 && y <= 55 && !(x >= 25 && x <= 50 && y >= 20 && y <= 45))
//         {
//             printf("Dans une zone bleue\n");
//         }
//         else if (y >= 60 && ((x >= 15 && x <= 45) || (x >= 60 && x <= 85)))
//         {
//             printf("Dans une zone rouge\n");
//         }
//         else
//         {
//             printf("Dans une zone jaune\n");
//         }
//     }

//     return 0;
// }
