#include "stdio.h"
#include "math.h"

int main( int argc, char * argv[] ) 
{
    double paper_thickness = 0.110;
    printf("%1f", (paper_thickness*pow(2, 15))/10);
}
