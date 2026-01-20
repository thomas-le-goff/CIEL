#include "stdio.h"

int main( int argc, char * argv[] )
{
int nbr_legumes = 0;
int i = 0;

scanf("%d", &nbr_legumes);

while(i < nbr_legumes) {
   double poid = 0;
   double age = 0;
   double prix = 0;
   
   scanf("%lf", &poid);
   scanf("%lf", &age);
   scanf("%lf", &prix);
   
   printf("%lf \n", prix/poid);
   i++;
}
}