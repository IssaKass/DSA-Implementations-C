#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef bool (*Predicate)(int);
typedef int (*Function)(int);
typedef void (*Consumer)(int);

typedef struct
{
    int *data;
    int length;
    int capacity;
} Vector;

// ========================================
// Initialization & Memory Management
// ========================================

void vec_init(Vector *vec);

Vector vec_create(size_t initial_capacity);

void vec_destroy(Vector *vec);

void vec_clear(Vector *vec);

// ========================================
// Size & Capacity Information
// ========================================

int vec_size(const Vector *vec);

int vec_capacity(const Vector *vec);

bool vec_is_empty(const Vector *vec);

// ========================================
// Element Modification (Adding, Removing & Bulk)
// ========================================

void vec_append(Vector *vec, int item);

void vec_set(Vector *vec, int index, int value);

void vec_fill(Vector *vec, int value, int count);

// ========================================
// Element Access & Retrieval
// ========================================

int vec_get(const Vector *vec, int index);

int vec_first(const Vector *vec);

int vec_last(const Vector *vec);

// ========================================
// Search & Query Functions
// ========================================

int vec_find(const Vector *vec, int target);

bool vec_contains(const Vector *vec, int target);

int vec_count(const Vector *vec, int value);

bool vec_equals(const Vector *vec1, const Vector *vec2);

// ========================================
// Higher-Order Predicate Functions
// ========================================

bool vec_all(const Vector *vec, Predicate predicate);

bool vec_any(const Vector *vec, Predicate predicate);

bool vec_none(const Vector *vec, Predicate predicate);

Vector vec_filter(const Vector *vec, Predicate predicate);

// ========================================
// Statistical & Aggregate Functions
// ========================================

int vec_sum(const Vector *vec);

double vec_average(const Vector *vec);

int vec_max(const Vector *vec);

int vec_min(const Vector *vec);

int vec_product(const Vector *vec);

int vec_range(const Vector *vec);

// ========================================
// Transformation & Conversion Functions
// ========================================

void vec_map(const Vector *vec, Function function);

Vector vec_slice(const Vector *vec, int start, int end);

void vec_to_array(const Vector *vec, int *array);

void vec_foreach(const Vector *vec, Consumer consumer);

// ========================================
// Utility Functions
// ========================================

void vec_print(const Vector *vec);

void vec_debug(const Vector *vec);

void vec_copy(Vector *dest, const Vector *src);

#endif // VECTOR_H