#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef DEFAULT_CAPACITY
#define DEFAULT_CAPACITY 10
#endif

static void vec_grow(Vector *vec)
{
    vec->capacity *= 2;
    int *new_data = (int *)realloc(vec->data, vec->capacity * sizeof(int));
    if (!new_data)
    {
        fprintf(stderr, "Memory re-allocation failed during resize\n");
        exit(EXIT_FAILURE);
    }
    vec->data = new_data;
}

//
// ─── CREATION & DESTRUCTION ─────────────────────────────────────────────
//

Vector vec_create()
{
    return vec_create_with_capacity(DEFAULT_CAPACITY);
}

Vector vec_create_with_capacity(int initial_capacity)
{
    Vector vec;
    vec.capacity = initial_capacity;
    vec.size = 0;
    vec.data = (int *)malloc(initial_capacity * sizeof(int));
    if (!vec.data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return vec;
}

void vec_destroy(Vector *vec)
{
    free(vec->data);
    vec->size = vec->capacity = 0;
    vec->data = NULL;
}

//
// ─── CORE OPERATIONS ────────────────────────────────────────────────────
//

void vec_add(Vector *vec, int element)
{
    if (vec->size == vec->capacity)
        vec_grow(vec);

    vec->data[vec->size++] = element;
}

void vec_clear(Vector *vec)
{
    vec->size = 0;
}

void vec_insert(Vector *vec, int index, int element)
{
    if (index < 0 || index > vec->size)
    {
        fprintf(stderr, "Index out of bounds in vec_insert (index=%d, size=%d)\n", index, vec->size);
        exit(EXIT_FAILURE);
    }

    if (vec->size >= vec->capacity)
    {
        vec_grow(vec);
    }

    for (int i = vec->size; i > index; i--)
    {
        vec->data[i] = vec->data[i - 1];
    }

    vec->data[index] = element;
    vec->size++;
}

int vec_remove(Vector *vec, int index)
{
    if (index < 0 || index >= vec->size)
    {
        fprintf(stderr, "Index out of bounds in vec_remove (index=%d, size=%d)\n", index, vec->size);
    }

    int element = vec->data[index];

    for (int i = index; i < vec->size - 1; i++)
    {
        vec->data[i] = vec->data[i + 1];
    }

    vec->size--;

    return element;
}

void vec_remove_if(Vector *vec, Predicate predicate)
{
    int write = 0;

    for (int read = 0; read < vec->size; read++)
    {
        if (!predicate(vec->data[read]))
            vec->data[write++] = vec->data[read];
    }

    vec->size = write;
}

int vec_get(const Vector *vec, int index)
{
    if (index < 0 || index >= vec->size)
    {
        fprintf(stderr, "Index %d is out of range [0..%d]", index, vec->size);
        exit(EXIT_FAILURE);
    }
    return vec->data[index];
}

int vec_set(Vector *vec, int index, int element)
{
    if (index < 0 || index >= vec->size)
    {
        fprintf(stderr, "Index %d is out of range [0..%d]", index, vec->size);
        exit(EXIT_FAILURE);
    }

    int previous_element = vec->data[index];
    vec->data[index] = element;

    return previous_element;
}

int vec_size(const Vector *vec)
{
    return vec->size;
}

//
// ─── SEARCH & INDEXING ──────────────────────────────────────────────────
//

bool vec_contains(const Vector *vec, int element)
{
    for (int i = 0; i < vec->size; i++)
    {
        if (vec->data[i] == element)
            return true;
    }
    return false;
}

int vec_indexof(const Vector *vec, int element)
{
    for (int i = 0; i < vec->size; i++)
    {
        if (vec->data[i] == element)
            return i;
    }
    return -1;
}

int vec_last_indexof(const Vector *vec, int element)
{
    for (int i = vec->size - 1; i >= 0; i--)
    {
        if (vec->data[i] == element)
            return i;
    }
    return -1;
}

int vec_find_first(const Vector *vec, Predicate predicate)
{
    for (int i = 0; i < vec->size; i++)
    {
        if (predicate(vec->data[i]))
            return vec->data[i];
    }
    return -1;
}

int vec_find_last(const Vector *vec, Predicate predicate)
{
    for (int i = vec->size - 1; i >= 0; i--)
    {
        if (predicate(vec->data[i]))
            return vec->data[i];
    }
    return -1;
}

int vec_binary_search(const Vector *vec, int element)
{
    if (vec->size == 0)
        return -1;

    int left = 0;
    int right = vec->size - 1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (vec->data[mid] == element)
            return mid;
        else if (vec->data[mid] < element)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

//
// ─── COMPARISON & EQUALITY ──────────────────────────────────────────────
//

bool vec_equals(const Vector *v1, const Vector *v2)
{
    if (v1->size != v2->size)
        return false;

    for (int i = 0; i < v1->size; i++)
    {
        if (v1->data[i] != v2->data[i])
            return false;
    }

    return true;
}

//
// ─── TRANSFORMATION ─────────────────────────────────────────────────────
//

Vector vec_map(const Vector *vec, Function mapper)
{
    Vector result = vec_create_with_capacity(vec->size);

    for (int i = 0; i < vec->size; i++)
    {
        vec_add(&result, mapper(vec->data[i]));
    }

    return result;
}

Vector vec_filter(const Vector *vec, Predicate predicate)
{
    Vector result = vec_create_with_capacity(vec->capacity);

    for (int i = 0; i < vec->size; i++)
    {
        if (predicate(vec->data[i]))
            vec_add(&result, vec->data[i]);
    }

    return result;
}

Vector vec_subvec(const Vector *vec, int from_index, int to_index)
{
    if (from_index < 0 || to_index > vec->size)
    {
        fprintf(stderr, "Index is out of range\n");
        exit(EXIT_FAILURE);
    }

    if (from_index > to_index)
    {
        fprintf(stderr, "Indices are out of order\n");
        exit(EXIT_FAILURE);
    }

    Vector subvec;
    subvec.capacity = subvec.size = to_index - from_index;
    subvec.data = (int *)malloc(subvec.size * sizeof(int));

    if (!subvec.data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < subvec.size; i++)
    {
        subvec.data[i] = vec->data[from_index + i];
    }

    return subvec;
}

Vector vec_limit(const Vector *vec, int max_size)
{
    if (max_size < 0)
    {
        fprintf(stderr, "%d is negative\n", max_size);
        exit(EXIT_FAILURE);
    }

    Vector result = vec_create_with_capacity(max_size);

    for (int i = 0; i < max_size; i++)
    {
        vec_add(&result, vec->data[i]);
    }

    return result;
}

Vector vec_skip(const Vector *vec, int n)
{
    if (n < 0)
    {
        fprintf(stderr, "%d is negative\n", n);
        exit(EXIT_FAILURE);
    }

    if (n > vec->size)
    {
        return vec_create();
    }

    int result_size = vec->size - n;
    Vector result = vec_create_with_capacity(result_size);

    for (int i = 0; i < result_size; i++)
    {
        vec_add(&result, vec->data[n + i]);
    }

    return result;
}

Vector vec_concat(const Vector *v1, const Vector *v2)
{
    Vector result = vec_create_with_capacity(v1->size + v2->size);

    for (int i = 0; i < v1->size; i++)
    {
        vec_add(&result, v1->data[i]);
    }
    for (int i = 0; i < v2->size; i++)
    {
        vec_add(&result, v2->data[i]);
    }

    return result;
}

void vec_reverse(Vector *vec)
{
    for (int i = 0; i < vec->size / 2; i++)
    {
        int temp = vec->data[i];
        vec->data[i] = vec->data[vec->size - 1 - i];
        vec->data[vec->size - 1 - i] = temp;
    }
}

//
// ─── AGGREGATION & STATISTICS ───────────────────────────────────────────
//

int vec_min(const Vector *vec)
{
    if (vec->size == 0)
        return 0;

    int min = vec->data[0];

    for (int i = 0; i < vec->size; i++)
    {
        if (vec->data[i] < min)
            min = vec->data[i];
    }

    return min;
}

int vec_max(const Vector *vec)
{
    if (vec->size == 0)
        return 0;

    int max = vec->data[0];

    for (int i = 0; i < vec->size; i++)
    {
        if (vec->data[i] > max)
            max = vec->data[i];
    }

    return max;
}

int vec_sum(const Vector *vec)
{
    int sum = 0;

    for (int i = 0; i < vec->size; i++)
    {
        sum += vec->data[i];
    }

    return sum;
}

double vec_average(const Vector *vec)
{
    return (double)vec_sum(vec) / vec->size;
}

int vec_product(const Vector *vec)
{
    int product = 1;

    for (int i = 0; i < vec->size; i++)
    {
        product *= vec->data[i];
    }

    return product;
}

int vec_count(const Vector *vec, int element)
{
    int count = 0;

    for (int i = 0; i < vec->size; i++)
    {
        if (vec->data[i] == element)
            count++;
    }

    return count;
}

//
// ─── BOOLEAN PREDICATE LOGIC ────────────────────────────────────────────
//

bool vec_all(const Vector *vec, Predicate predicate)
{
    for (int i = 0; i < vec->size; i++)
    {
        if (!predicate(vec->data[i]))
            return false;
    }
    return true;
}

bool vec_any(const Vector *vec, Predicate predicate)
{
    for (int i = 0; i < vec->size; i++)
    {
        if (predicate(vec->data[i]))
            return true;
    }
    return true;
}

bool vec_none(const Vector *vec, Predicate predicate)
{
    for (int i = 0; i < vec->size; i++)
    {
        if (predicate(vec->data[i]))
            return false;
    }
    return true;
}

//
// ─── HIGHER ORDER FUNCTIONS ─────────────────────────────────────────────
//

void vec_foreach(const Vector *vec, Consumer action)
{
    for (int i = 0; i < vec->size; i++)
    {
        action(vec->data[i]);
    }
}

//
// ─── UTILITIES ──────────────────────────────────────────────────────────
//

void vec_print(const Vector *vec)
{
    printf("[");
    for (int i = 0; i < vec->size; i++)
    {
        if (i != vec->size - 1)
            printf("%d, ", vec->data[i]);
        else
            printf("%d", vec->data[i]);
    }
    printf("]\n");
}

void vec_swap(Vector *vec, int i, int j)
{
    if (i < 0 || i >= vec->size || j < 0 || j >= vec->size)
    {
        fprintf(stderr, "Index out of bounds in vec_swap (i=%d, j=%d, size=%d)\n", i, j, vec->size);
        exit(EXIT_FAILURE);
    }

    int temp = vec->data[i];
    vec->data[i] = vec->data[j];
    vec->data[j] = temp;
}

bool vec_is_empty(const Vector *vec)
{
    return vec->size == 0;
}
