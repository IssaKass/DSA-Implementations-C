#include <stdio.h>
#include <stdbool.h>
#include "functional.h"

bool is_even(int x)
{
    return x % 2 == 0;
}

bool is_odd(int x)
{
    return x % 2 != 0;
}

bool is_positive(int x)
{
    return x > 0;
}

bool is_negative(int x)
{
    return x < 0;
}

bool is_zero(int x)
{
    return x == 0;
}

int negate(int x)
{
    return -x;
}

int square(int x)
{
    return x * x;
}

void print_int(int x)
{
    printf("%d ", x);
}