#include <stdio.h>
#include <stdbool.h>
#include "vector/vector.h"

bool is_even(int x)
{
    return x % 2 == 0;
}

int square(int x)
{
    return x * x;
}

void print_item(int x)
{
    printf("%d ", x);
}

int main()
{
    Vector v;
    vec_init(&v);

    // Append values 0 to 9
    for (int i = 0; i < 10; i++)
    {
        vec_append(&v, i);
    }

    printf("Vector contents: ");
    vec_print(&v);

    printf("All even? %s\n", vec_all(&v, is_even) ? "Yes" : "No");

    printf("Squares: ");
    vec_map(&v, square);
    vec_foreach(&v, print_item);
    printf("\n");

    vec_destroy(&v);
    return 0;
}