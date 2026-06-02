#include "tp_functions.h"

int global_counter = 0;

int counter_val(int a)
{
    return a + 1;
}

void counter_ref(int *a)
{
    (*a)++;
}

void counter_global()
{
    global_counter++;
}

int add(int a, int b)
{
    return a + b;
}

Point scale_point_by_value(Point p, int s)
{
    p.x = p.x * s;
    p.y = p.y * s;

    return p;
}

void scale_point_by_ref(Point *p, int s)
{
    p->x = p->x * s;
    p->y = p->y * s;
}

int sum_array_max_out(int size, int array[size], int *sum)
{
    int max = INT_MIN;
    (*sum) = 0;
    for (size_t i = 0; i < size; i++)
    {
        (*sum) += array[i];
        if (max < array[i])
        {
            max = array[i];
        }
    }

    return max;
}