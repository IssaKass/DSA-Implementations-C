#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include "../functional/functional.h"

#ifndef DEFAULT_CAPACITY
#define DEFAULT_CAPACITY 10
#endif

#ifndef GROW_FACTOR
#define GROW_FACTOR 2
#endif

typedef struct
{
    int *data;
    int size;     // Current number of elements
    int capacity; // Maximum number of elements before re-allocation
} Vector;

// -----------------------------------------------------------------------------
// CORE MANAGEMENT (Creation, Destruction, Properties, Internal Resize)
// -----------------------------------------------------------------------------

Vector vec_create();
Vector vec_create_with_capacity(int initial_capacity);
void vec_trim_to_size(Vector *vec);
void vec_ensure_capacity(Vector *vec, int min_capacity);
void vec_clear(Vector *vec);
void vec_destroy(Vector *vec);

int vec_size(const Vector *vec);
int vec_capacity(const Vector *vec);
bool vec_is_empty(const Vector *vec);

// -----------------------------------------------------------------------------
// ELEMENT MODIFICATION (Add, Insert, Remove, Set)
// -----------------------------------------------------------------------------

void vec_add(Vector *vec, int element);
void vec_add_all(Vector *vec, Vector *other);

void vec_insert(Vector *vec, int index, int element);

int vec_remove(Vector *vec, int index);
void vec_remove_if(Vector *vec, Predicate predicate);

int vec_set(Vector *vec, int index, int element);

// Convenience functions for modifying ends of the vector
void vec_add_first(Vector *vec, int element);
void vec_add_last(Vector *vec, int element);
int vec_remove_first(Vector *vec);
int vec_remove_last(Vector *vec);

// -----------------------------------------------------------------------------
// ELEMENT ACCESS & INFORMATION (Get, Search, Indexing)
// -----------------------------------------------------------------------------

int vec_get(const Vector *vec, int index);
int vec_get_first(const Vector *vec);
int vec_get_last(const Vector *vec);

bool vec_contains(const Vector *vec, int element);
bool vec_contains_all(const Vector *vec, const Vector *other);

int vec_indexof(const Vector *vec, int element);
int vec_indexof_range(const Vector *vec, int element, int start, int end);
int vec_last_indexof(const Vector *vec, int element);
int vec_last_indexof_range(const Vector *vec, int element, int start, int end);

int vec_binary_search(const Vector *vec, int element);

// -----------------------------------------------------------------------------
// TRANSFORMATION & DERIVATION (New Vectors or In-Place Structure Change)
// -----------------------------------------------------------------------------

Vector vec_map(const Vector *vec, Function mapper);
void vec_replace_all(Vector *vec, Function mapper);
Vector vec_filter(const Vector *vec, Predicate predicate);
Vector vec_subvec(const Vector *vec, int from_index, int to_index);
Vector vec_limit(const Vector *vec, int max_size);
Vector vec_skip(const Vector *vec, int n);
Vector vec_concat(const Vector *v1, const Vector *v2);
void vec_reverse(Vector *vec);
int *vec_to_array(const Vector *vec);

// -----------------------------------------------------------------------------
// AGGREGATION & STATISTICS (Single Value Calculations)
// -----------------------------------------------------------------------------

int vec_min(const Vector *vec);
int vec_max(const Vector *vec);
int vec_sum(const Vector *vec);
double vec_average(const Vector *vec);
int vec_product(const Vector *vec);
int vec_count(const Vector *vec, int element);

// -----------------------------------------------------------------------------
// PREDICATE-BASED LOGIC (Checks all/any/none elements)
// -----------------------------------------------------------------------------

bool vec_all(const Vector *vec, Predicate predicate);
bool vec_any(const Vector *vec, Predicate predicate);
bool vec_none(const Vector *vec, Predicate predicate);

int vec_find_first(const Vector *vec, Predicate predicate);
int vec_find_last(const Vector *vec, Predicate predicate);

// -----------------------------------------------------------------------------
// HIGHER-ORDER UTILITIES (Generic application of functions)
// -----------------------------------------------------------------------------

void vec_foreach(const Vector *vec, Consumer action);

// -----------------------------------------------------------------------------
// UTILITY & DEBUGGING (Miscellaneous Helpers)
// -----------------------------------------------------------------------------

char *vec_to_string(const Vector *vec);
void vec_printf(const Vector *vec);
void vec_swap(Vector *vec, int i, int j);

bool vec_equals(const Vector *vec1, const Vector *vec2);

#endif // VECTOR_H