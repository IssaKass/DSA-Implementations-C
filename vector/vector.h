#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include "../functional/functional.h"

typedef struct
{
    int *data;
    int size;
    int capacity;
} Vector;

//
// ─── CREATION & DESTRUCTION ─────────────────────────────────────────────
//

Vector vec_create();
Vector vec_create_with_capacity(int initial_capacity);
void vec_destroy(Vector *vec);

//
// ─── CORE OPERATIONS ────────────────────────────────────────────────────
//

void vec_add(Vector *vec, int element);
void vec_clear(Vector *vec);
void vec_insert(Vector *vec, int index, int element);
int vec_remove(Vector *vec, int index);
int vec_set(Vector *vec, int index, int element);
int vec_get(const Vector *vec, int index);
int vec_size(const Vector *vec);

//
// ─── SEARCH & INDEXING ──────────────────────────────────────────────────
//

bool vec_contains(const Vector *vec, int element);
int vec_indexof(const Vector *vec, int element);
int vec_last_indexof(const Vector *vec, int element);
int vec_find_first(const Vector *vec, Predicate predicate);
int vec_find_last(const Vector *vec, Predicate predicate);

//
// ─── COMPARISON & EQUALITY ──────────────────────────────────────────────
//

bool vec_equals(const Vector *vec1, const Vector *vec2);

//
// ─── TRANSFORMATION ─────────────────────────────────────────────────────
//

Vector vec_map(const Vector *vec, Function mapper);
Vector vec_filter(const Vector *vec, Predicate predicate);
Vector vec_subvec(const Vector *vec, int from_index, int to_index);
Vector vec_limit(const Vector *vec, int max_size);
Vector vec_skip(const Vector *vec, int n);
Vector vec_concat(const Vector *v1, const Vector *v2);
void vec_reverse(Vector *vec);

//
// ─── AGGREGATION & STATISTICS ───────────────────────────────────────────
//

int vec_min(const Vector *vec);
int vec_max(const Vector *vec);
int vec_sum(const Vector *vec);
double vec_average(const Vector *vec);

//
// ─── BOOLEAN PREDICATE LOGIC ────────────────────────────────────────────
//

bool vec_all(const Vector *vec, Predicate predicate);
bool vec_any(const Vector *vec, Predicate predicate);
bool vec_none(const Vector *vec, Predicate predicate);

//
// ─── HIGHER ORDER FUNCTIONS ─────────────────────────────────────────────
//

void vec_foreach(const Vector *vec, Consumer action);



void vec_print(const Vector *vec);
void vec_swap(Vector *vec, int i, int j);
bool vec_is_empty(const Vector *vec);

#endif // VECTOR_H