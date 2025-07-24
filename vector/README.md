# Vector (Dynamic Array) — C Library

A dynamic array (vector) implementation in C with comprehensive features including resizing, element access, higher-order functions, and statistical operations.

---

## Features

- Automatic resizing (with capacity doubling)
- Element insertion, access, modification, and bulk fill
- Search, count, and equality checks
- Higher-order functions: `all`, `any`, `none`, `filter`
- Statistical calculations: `sum`, `average`, `max`, `min`, `product`, `range`
- Transformation utilities: `map`, `slice`, `foreach`
- Debug printing and safe memory management

---

## Files

- `vector.h` — Public API and type declarations
- `vector.c` — Function implementations

---

## How to Use

1. **Clone the repository** or copy the `vector/` folder into your C project.
2. **Include the header** in your file:

```c
#include "vector/vector.h"
```

3. Compile your program with the vector source:

```bash
gcc main.c vector/vector.c -o main
```

## Usage Example

```c
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
```
