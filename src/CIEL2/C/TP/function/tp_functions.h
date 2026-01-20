#include <stdlib.h>
#include <limits.h>

typedef struct
{
    float x;
    float y;
} Point;

int counter_val(int a);

void counter_ref(int *a);

void counter_global();

int add(int a, int b);

Point scale_point_by_value(Point p, int s);

void scale_point_by_ref(Point *p, int s);

int sum_array_max_out(int size, int array[size], int *sum);