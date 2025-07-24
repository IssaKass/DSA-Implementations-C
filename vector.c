#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef INITIAL_CAPACITY
#define INITIAL_CAPACITY 10
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

// ========================================
// Initialization & Memory Management
// ========================================

void vec_init(Vector *vec)
{
    vec->capacity = INITIAL_CAPACITY;
    vec->length = 0;
    vec->data = (int *)malloc(vec->capacity * sizeof(int));
    if (!vec->data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

Vector vec_create(size_t initial_capacity)
{
    Vector vec;
    vec.capacity = (initial_capacity > 0) ? initial_capacity : INITIAL_CAPACITY;
    vec.length = 0;
    vec.data = (int *)malloc(initial_capacity * sizeof(int));
    if (!vec.data)
    {
        fprintf(stderr, "Memory allocation failed during vec_create\n");
        exit(EXIT_FAILURE);
    }
    return vec;
}

void vec_destroy(Vector *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->length = 0;
    vec->capacity = 0;
}

void vec_clear(Vector *vec)
{
    vec->length = 0;
}

// ========================================
// Size & Capacity Information
// ========================================

int vec_size(const Vector *vec)
{
    return vec->length;
}

int vec_capacity(const Vector *vec)
{
    return vec->capacity;
}

bool vec_is_empty(const Vector *vec)
{
    return vec->length == 0;
}

// ========================================
// Element Modification (Adding, Removing & Bulk)
// ========================================

void vec_append(Vector *vec, int item)
{
    if (vec->length == vec->capacity)
        vec_grow(vec);

    vec->data[vec->length++] = item;
}

void vec_set(Vector *vec, int index, int value)
{
    if (index < 0 || index >= vec->length)
    {
        fprintf(stderr, "vec_set: Index %d out of bounds (length %d)\n", index, vec->length);
        exit(EXIT_FAILURE);
    }
    vec->data[index] = value;
}

void vec_fill(Vector *vec, int value, int count)
{
    if (count < 0)
    {
        fprintf(stderr, "vec_fill: count cannot be negative\n");
        exit(EXIT_FAILURE);
    }

    if (vec->data != NULL && vec->capacity > 0)
    {
        free(vec->data);
        vec->data = NULL; // Set to NULL after freeing
    }

    vec->length = count;
    vec->capacity = count;

    vec->data = (int *)malloc(count * sizeof(int));

    if (count > 0)
    { // Only allocate if count is positive
        vec->data = (int *)malloc(count * sizeof(int));
        if (!vec->data)
        {
            fprintf(stderr, "vec_fill: Memory allocation failed\n");
            vec->length = 0; // Reset to safe state on failure
            vec->capacity = 0;
            exit(EXIT_FAILURE);
        }
        // Fill the allocated memory with the specified value
        for (int i = 0; i < count; i++)
        {
            vec->data[i] = value;
        }
    }
    else
    {
        // If count is 0, ensure data is NULL and capacity is 0 for an empty vector
        vec->data = NULL;
        vec->capacity = 0;
    }
}

// ========================================
// Element Access & Retrieval
// ========================================

int vec_get(const Vector *vec, int index)
{
    if (index < 0 || index >= vec->length)
    {
        fprintf(stderr, "vec_get: Index %d out of bounds (length %d)\n", index, vec->length);
        exit(EXIT_FAILURE);
    }
    return vec->data[index];
}

int vec_first(const Vector *vec)
{
    if (vec->length == 0)
    {
        fprintf(stderr, "vec_first: Vector is empty\n");
        exit(EXIT_FAILURE);
    }
    return vec->data[0];
}

int vec_last(const Vector *vec)
{
    if (vec->length == 0)
    {
        fprintf(stderr, "vec_last: Vector is empty\n");
        exit(EXIT_FAILURE);
    }
    return vec->data[vec->length - 1];
}

// ========================================
// Search & Query Functions
// ========================================

int vec_find(const Vector *vec, int target)
{
    for (int i = 0; i < vec->length; i++)
    {
        if (vec->data[i] == target)
            return i;
    }
    return -1;
}

bool vec_contains(const Vector *vec, int target)
{
    return vec_find(vec, target) != -1;
}

int vec_count(const Vector *vec, int value)
{
    int count = 0;
    for (int i = 0; i < vec->length; i++)
    {
        if (vec->data[i] == value)
            count++;
    }
    return count;
}

bool vec_equals(const Vector *vec1, const Vector *vec2)
{
    if (vec1->length != vec2->length)
        return false;

    for (int i = 0; i < vec1->length; i++)
    {
        if (vec1->data[i] != vec2->data[i])
            return false;
    }
    return true;
}

// ========================================
// Higher-Order Predicate Functions
// ========================================

bool vec_all(const Vector *vec, Predicate predicate)
{
    for (int i = 0; i < vec->length; i++)
    {
        if (!predicate(vec->data[i]))
            return false;
    }
    return true;
}

bool vec_any(const Vector *vec, Predicate predicate)
{
    for (int i = 0; i < vec->length; i++)
    {
        if (predicate(vec->data[i]))
            return true;
    }
    return false;
}

bool vec_none(const Vector *vec, Predicate predicate)
{
    for (int i = 0; i < vec->length; i++)
    {
        if (predicate(vec->data[i]))
            return false;
    }
    return true;
}

Vector vec_filter(const Vector *vec, Predicate predicate)
{
    int length = 0;

    for (int i = 0; i < vec->length; i++)
    {
        if (predicate(vec->data[i]))
            length++;
    }

    Vector result;
    result.length = result.capacity = length;
    result.data = (int *)malloc(length * sizeof(int));

    if (result.data == NULL)
    {
        fprintf(stderr, "Memory allocation failed in vec_filter.\n");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    for (int i = 0; i < vec->length; i++)
    {
        if (predicate(vec->data[i]))
            result.data[j++] = vec->data[i];
    }

    return result;
}

// ========================================
// Statistical & Aggregate Functions
// ========================================

int vec_sum(const Vector *vec)
{
    int sum = 0;
    for (int i = 0; i < vec->length; i++)
    {
        sum += vec->data[i];
    }
    return sum;
}

double vec_average(const Vector *vec)
{
    if (vec->length == 0)
        return 0.0;

    return (double)vec_sum(vec) / vec->length;
}

int vec_max(const Vector *vec)
{
    if (vec->length == 0)
    {
        fprintf(stderr, "vec_max: Vector is empty, cannot find maximum\n");
        exit(EXIT_FAILURE);
    }

    int max_val = vec->data[0];
    for (int i = 1; i < vec->length; i++)
    {
        if (vec->data[i] > max_val)
            max_val = vec->data[i];
    }
    return max_val;
}

int vec_min(const Vector *vec)
{
    if (vec->length == 0)
    {
        fprintf(stderr, "Vector is empty\n");
        exit(EXIT_FAILURE);
    }

    int min_val = vec->data[0];
    for (int i = 1; i < vec->length; i++)
    {
        if (vec->data[i] < min_val)
            min_val = vec->data[i];
    }
    return min_val;
}

int vec_product(const Vector *vec)
{
    int product = 1;
    for (int i = 0; i < vec->length; i++)
    {
        product *= vec->data[i];
    }
    return product;
}

int vec_range(const Vector *vec)
{
    if (vec->length == 0)
    {
        fprintf(stderr, "vec_range: Vector is empty, cannot calculate range\n");
        exit(EXIT_FAILURE);
    }
    return vec_max(vec) - vec_min(vec);
}

// ========================================
// Transformation & Conversion Functions
// ========================================

void vec_map(const Vector *vec, Function function)
{
    for (int i = 0; i < vec->length; i++)
    {
        vec->data[i] = function(vec->data[i]);
    }
}

Vector vec_slice(const Vector *vec, int start, int end)
{
    if (start < 0 || start > vec->length || end < 0 || end > vec->length || start > end)
    {
        fprintf(stderr, "Error in vec_slice: invalid start or end index (start=%d, end=%d, length=%d)\n", start, end, vec->length);
        exit(EXIT_FAILURE);
    }

    Vector result;
    result.length = result.capacity = end - start;
    result.data = NULL;

    if (result.length > 0)
    { // Only allocate memory if the slice is not empty
        result.data = (int *)malloc(result.capacity * sizeof(int));
        if (!result.data)
        {
            fprintf(stderr, "vec_slice: Memory allocation failed\n");
            // Ensure result is in a safe, empty state on failure
            result.length = 0;
            result.capacity = 0;
            exit(EXIT_FAILURE);
        }
        // Copy elements from the source vector to the new slice
        for (int i = 0; i < result.length; i++)
        {
            result.data[i] = vec->data[start + i];
        }
    }
    else
    {
        // If the slice is empty, ensure data is NULL and capacity is 0
        result.data = NULL;
        result.capacity = 0;
    }

    return result;
}

void vec_to_array(const Vector *vec, int *array)
{
    for (int i = 0; i < vec->length; i++)
    {
        array[i] = vec->data[i];
    }
}

void vec_foreach(const Vector *vec, Consumer consumer)
{
    for (int i = 0; i < vec->length; i++)
    {
        consumer(vec->data[i]);
    }
}

// ========================================
// Utility Functions
// ========================================

void vec_print(const Vector *vec)
{
    printf("[");
    for (int i = 0; i < vec->length; i++)
    {
        printf("%d", vec->data[i]);
        if (i < vec->length - 1)
            printf(", ");
    }
    printf("]\n");
}

void vec_debug(const Vector *vec)
{
    printf("Vector Debug Info:\n");
    printf("  Address : %p\n", (void *)vec->data);
    printf("  Length  : %d\n", vec->length);
    printf("  Capacity: %d\n", vec->capacity);
    printf("  Values  : ");
    vec_print(vec);
}

void vec_copy(Vector *dest, const Vector *src)
{
    // It's important to free existing data in dest if it was previously initialized
    if (dest->data != NULL)
    {
        free(dest->data);
    }

    dest->length = src->length;
    dest->capacity = src->capacity;

    dest->data = (int *)malloc(dest->capacity * sizeof(int));

    if (dest->capacity > 0)
    {
        dest->data = (int *)malloc(dest->capacity * sizeof(int));
        // CRITICAL FIX: Check if malloc FAILED (returned NULL).
        if (dest->data == NULL)
        {
            fprintf(stderr, "vec_copy: Memory allocation failed\n");
            // It's good practice to reset the dest vector to a safe, empty state on failure
            dest->length = 0;
            dest->capacity = 0;
            exit(EXIT_FAILURE); // Exit or return an error code
        }
        // Copy the actual elements from the source to the newly allocated destination.
        // Only copy up to src->length, as capacity might be larger than length,
        // and we only care about the valid elements.
        memcpy(dest->data, src->data, src->length * sizeof(int));
    }
    else
    {
        // If source is empty, destination should also be empty with NULL data
        dest->data = NULL;
    }
}
