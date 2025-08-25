# 📦 Vector (Dynamic Array) — C Library

A modern and powerful implementation of a dynamic array (vector) in C, inspired by Java's `ArrayList` and functional programming concepts. This library provides core operations, higher-order functions, transformation utilities, and statistical methods — all written in clean, modular, and reusable C code.

---

## 🚀 Features

- Dynamic resizing
- Element access and mutation
- Search and index functions
- Transformations (map, filter, subvec, concat, reverse)
- Aggregations (sum, min, max, average)
- Functional utilities (`map`, `filter`, `foreach`, `all`, `any`, `none`)
- Equality and comparison operations
- Debugging and utility methods

---

## 🛠️ Getting Started

### 📁 Folder Structure

```
your-project/
├── vector/
│   ├── vector.h         # Header file
│   ├── vector.c         # Implementation
│   └── README.md        # This file
├── functional/
│   └── functional.h     # Function pointer typedefs
└── main.c               # Your test file
```

### 🔧 Build Instructions

Compile with:

```bash
gcc -o main main.c vector/vector.c functional/functional.c
```

Or use with Makefile:

```bash
make
```

Ensure functional.h is properly included and defines:

```c
typedef bool (*Predicate)(int);
typedef int (*Function)(int);
typedef void (*Consumer)(int);
```

## 🧪 Example Usage

```c
#include "vector/vector.h"
#include <stdio.h>

int main() {
    Vector vec = vec_create();
    vec_add(&vec, 10);
    vec_add(&vec, 20);
    vec_add(&vec, 30);
    vec_print(&vec); // Output: [10, 20, 30]

    vec_reverse(&vec);
    vec_print(&vec); // Output: [30, 20, 10]

    vec_destroy(&vec);
    return 0;
}
```

## 📚 Function Reference

### 🧱 Core Management

| Function                                                  | Description                                             |
| --------------------------------------------------------- | ------------------------------------------------------- |
| `Vector vec_create()`                                     | Creates a new vector with default capacity.             |
| `Vector vec_create_with_capacity(int initial_capacity)`   | Creates a vector with the specified initial capacity.   |
| `void vec_trim_to_size(Vector *vec)`                      | Reduces capacity to current size.                       |
| `void vec_ensure_capacity(Vector *vec, int min_capacity)` | Ensures the vector has at least the specified capacity. |
| `void vec_clear(Vector *vec)`                             | Clears all elements without deallocating memory.        |
| `void vec_destroy(Vector *vec)`                           | Frees the memory used by the vector.                    |
| `int vec_size(const Vector *vec)`                         | Returns the number of elements.                         |
| `int vec_capacity(const Vector *vec)`                     | Returns the current capacity.                           |
| `bool vec_is_empty(const Vector *vec)`                    | Returns true if the vector has no elements.             |

---

### ✍️ Element Modification

| Function                                               | Description                                                        |
| ------------------------------------------------------ | ------------------------------------------------------------------ |
| `void vec_add(Vector *vec, int element)`               | Adds an element to the end.                                        |
| `void vec_add_all(Vector *vec, Vector *other)`         | Adds all elements from another vector.                             |
| `void vec_insert(Vector *vec, int index, int element)` | Inserts an element at a specific index.                            |
| `void vec_insert_sorted(Vector *vec, int element)`     | Inserts an element into the vector while maintaining sorted order. |
| `int vec_remove(Vector *vec, int index)`               | Removes the element at the given index and returns it.             |
| `void vec_remove_if(Vector *vec, Predicate predicate)` | Removes elements matching a condition.                             |
| `int vec_set(Vector *vec, int index, int element)`     | Sets a new value at the given index and returns the old value.     |
| `void vec_add_first(Vector *vec, int element)`         | Inserts element at the beginning.                                  |
| `void vec_add_last(Vector *vec, int element)`          | Inserts element at the end.                                        |
| `int vec_remove_first(Vector *vec)`                    | Removes and returns the first element.                             |
| `int vec_remove_last(Vector *vec)`                     | Removes and returns the last element.                              |

---

### 🔍 Element Access & Search

| Function                                                                         | Description                                                              |
| -------------------------------------------------------------------------------- | ------------------------------------------------------------------------ |
| `int vec_get(const Vector *vec, int index)`                                      | Gets the value at the specified index.                                   |
| `int vec_get_first(const Vector *vec)`                                           | Gets the first element.                                                  |
| `int vec_get_last(const Vector *vec)`                                            | Gets the last element.                                                   |
| `bool vec_contains(const Vector *vec, int element)`                              | Checks if vector contains the element.                                   |
| `bool vec_contains_all(const Vector *vec, const Vector *other)`                  | Returns true if all elements of `other` exist in `vec`.                  |
| `int vec_indexof(const Vector *vec, int element)`                                | Index of the first occurrence.                                           |
| `int vec_indexof_range(const Vector *vec, int element, int start, int end)`      | Index of the element in a sub-range.                                     |
| `int vec_last_indexof(const Vector *vec, int element)`                           | Last index of the element.                                               |
| `int vec_last_indexof_range(const Vector *vec, int element, int start, int end)` | Last index in a specific range.                                          |
| `int vec_binary_search(const Vector *vec, int element)`                          | Binary search for sorted vector.                                         |
| `bool vec_is_sorted(const Vector *vec)`                                          | Checks whether the elements in the vector are sorted in ascending order. |

---

### 🔁 Transformation & Derivation

| Function                                                             | Description                                                                                                      |
| -------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| `Vector vec_map(const Vector *vec, Function mapper)`                 | Creates a new vector by applying a function to each element.                                                     |
| `void vec_replace_all(Vector *vec, Function mapper)`                 | Applies function in-place to all elements.                                                                       |
| `Vector vec_filter(const Vector *vec, Predicate predicate)`          | Filters elements and returns a new vector.                                                                       |
| `Vector vec_subvec(const Vector *vec, int from_index, int to_index)` | Returns a subvector from range.                                                                                  |
| `Vector vec_limit(const Vector *vec, int max_size)`                  | Returns the first `n` elements.                                                                                  |
| `Vector vec_skip(const Vector *vec, int n)`                          | Returns a vector skipping the first `n` elements.                                                                |
| `Vector vec_concat(const Vector *v1, const Vector *v2)`              | Concatenates two vectors.                                                                                        |
| `void vec_reverse(Vector *vec)`                                      | Reverses the vector in-place.                                                                                    |
| `Vector vec_shift_left(const Vector *vec, int positions)`            | Returns a new vector with elements shifted left by the given number of positions (vacated spots filled with 0).  |
| `Vector vec_shift_right(const Vector *vec, int positions)`           | Returns a new vector with elements shifted right by the given number of positions (vacated spots filled with 0). |
| `Vector vec_rotate_left(const Vector *vec, int positions)`           | Returns a new vector with elements rotated left by the given number of positions.                                |
| `Vector vec_rotate_right(const Vector *vec, int positions)`          | Returns a new vector with elements rotated right by the given number of positions.                               |
| `int *vec_to_array(const Vector *vec)`                               | Returns a heap-allocated array copy.                                                                             |
| `void vec_rearrange(Vector *vec)`                                    | Rearranges the vector elements (e.g., separating positives/negatives or evens/odds depending on implementation). |
| `Vector vec_merge(const Vector *vec1, const Vector *vec2)`           | Merges two **sorted vectors** into a new sorted vector.                                                          |
| `Vector vec_union(const Vector *vec1, const Vector *vec2)`           | Returns a vector containing the union of two sets (unique elements from both).                                   |
| `Vector vec_intersection(const Vector *vec1, const Vector *vec2)`    | Returns a vector containing the intersection of two sets (common elements only).                                 |
| `Vector vec_difference(const Vector *vec1, const Vector *vec2)`      | Returns a vector containing the difference of two sets (elements in `vec1` that are not in `vec2`).              |

---

### 📊 Aggregation & Statistics

| Function                                        | Description                      |
| ----------------------------------------------- | -------------------------------- |
| `int vec_min(const Vector *vec)`                | Minimum value.                   |
| `int vec_max(const Vector *vec)`                | Maximum value.                   |
| `int vec_sum(const Vector *vec)`                | Sum of all elements.             |
| `double vec_average(const Vector *vec)`         | Average of elements.             |
| `int vec_product(const Vector *vec)`            | Product of all elements.         |
| `int vec_count(const Vector *vec, int element)` | Count occurrences of an element. |

---

### ✅ Predicate-Based Logic

| Function                                                     | Description                           |
| ------------------------------------------------------------ | ------------------------------------- |
| `bool vec_all(const Vector *vec, Predicate predicate)`       | Returns true if all match predicate.  |
| `bool vec_any(const Vector *vec, Predicate predicate)`       | Returns true if any match predicate.  |
| `bool vec_none(const Vector *vec, Predicate predicate)`      | Returns true if none match predicate. |
| `int vec_find_first(const Vector *vec, Predicate predicate)` | Finds index of first match.           |
| `int vec_find_last(const Vector *vec, Predicate predicate)`  | Finds index of last match.            |

---

### 🎯 Higher-Order Utilities

| Function                                               | Description                                  |
| ------------------------------------------------------ | -------------------------------------------- |
| `void vec_foreach(const Vector *vec, Consumer action)` | Applies a consumer function to each element. |

---

### 🛠️ Utility & Debugging

| Function                                                  | Description                                           |
| --------------------------------------------------------- | ----------------------------------------------------- |
| `char *vec_to_string(const Vector *vec)`                  | Returns string representation (heap-allocated).       |
| `void vec_printf(const Vector *vec)`                      | Prints the vector to stdout.                          |
| `void vec_swap(Vector *vec, int i, int j)`                | Swaps two elements.                                   |
| `bool vec_equals(const Vector *vec1, const Vector *vec2)` | Checks if vectors are equal (same order and content). |

---
