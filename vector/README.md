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
gcc -o main main.c vector/vector.c
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

### 📦 Creation & Destruction

| Function                                                | Description                                    |
| ------------------------------------------------------- | ---------------------------------------------- |
| `Vector vec_create()`                                   | Creates an empty vector with default capacity. |
| `Vector vec_create_with_capacity(int initial_capacity)` | Creates an empty vector with given capacity.   |
| `void vec_destroy(Vector *vec)`                         | Frees the memory used by the vector.           |

---

### ⚙️ Core Operations

| Function                                               | Description                                    |
| ------------------------------------------------------ | ---------------------------------------------- |
| `void vec_add(Vector *vec, int element)`               | Appends an element to the end of the vector.   |
| `void vec_clear(Vector *vec)`                          | Removes all elements without freeing capacity. |
| `void vec_insert(Vector *vec, int index, int element)` | Inserts an element at a specific index.        |
| `int vec_remove(Vector *vec, int index)`               | Removes the element at the given index.        |
| `int vec_set(Vector *vec, int index, int element)`     | Sets a value at a given index.                 |
| `int vec_get(const Vector *vec, int index)`            | Retrieves the element at the given index.      |
| `int vec_size(const Vector *vec)`                      | Returns the current number of elements.        |

---

### 🔍 Search & Indexing

| Function                                                     | Description                                 |
| ------------------------------------------------------------ | ------------------------------------------- |
| `bool vec_contains(const Vector *vec, int element)`          | Checks if the element exists in the vector. |
| `int vec_indexof(const Vector *vec, int element)`            | Returns the index of the first occurrence.  |
| `int vec_last_indexof(const Vector *vec, int element)`       | Returns the index of the last occurrence.   |
| `int vec_find_first(const Vector *vec, Predicate predicate)` | Finds first index matching predicate.       |
| `int vec_find_last(const Vector *vec, Predicate predicate)`  | Finds last index matching predicate.        |

---

### 🧪 Comparison & Equality

| Function                                                  | Description                               |
| --------------------------------------------------------- | ----------------------------------------- |
| `bool vec_equals(const Vector *vec1, const Vector *vec2)` | Checks if two vectors have same elements. |

---

### 🔁 Transformation

| Function                                                             | Description                                  |
| -------------------------------------------------------------------- | -------------------------------------------- |
| `Vector vec_map(const Vector *vec, Function mapper)`                 | Returns a new vector with mapped values.     |
| `Vector vec_filter(const Vector *vec, Predicate predicate)`          | Returns a new vector with filtered elements. |
| `Vector vec_subvec(const Vector *vec, int from_index, int to_index)` | Extracts a subvector from `[from, to)`.      |
| `Vector vec_limit(const Vector *vec, int max_size)`                  | Returns the first `n` elements.              |
| `Vector vec_skip(const Vector *vec, int n)`                          | Skips the first `n` elements.                |
| `Vector vec_concat(const Vector *v1, const Vector *v2)`              | Returns a new vector combining two vectors.  |
| `void vec_reverse(Vector *vec)`                                      | Reverses the vector in-place.                |

---

### 📊 Aggregation & Statistics

| Function                                | Description                          |
| --------------------------------------- | ------------------------------------ |
| `int vec_min(const Vector *vec)`        | Returns the minimum value.           |
| `int vec_max(const Vector *vec)`        | Returns the maximum value.           |
| `int vec_sum(const Vector *vec)`        | Returns the sum of all elements.     |
| `double vec_average(const Vector *vec)` | Returns the average of all elements. |

---

### 🧠 Boolean Predicate Logic

| Function                                                | Description                                    |
| ------------------------------------------------------- | ---------------------------------------------- |
| `bool vec_all(const Vector *vec, Predicate predicate)`  | Returns true if all elements match predicate.  |
| `bool vec_any(const Vector *vec, Predicate predicate)`  | Returns true if any element matches predicate. |
| `bool vec_none(const Vector *vec, Predicate predicate)` | Returns true if no element matches predicate.  |

---

### 🧬 Higher-Order Functions

| Function                                               | Description                         |
| ------------------------------------------------------ | ----------------------------------- |
| `void vec_foreach(const Vector *vec, Consumer action)` | Applies a function to each element. |

---

### 🛠 Utilities

| Function                                   | Description                        |
| ------------------------------------------ | ---------------------------------- |
| `void vec_print(const Vector *vec)`        | Prints all elements in the vector. |
| `void vec_swap(Vector *vec, int i, int j)` | Swaps two elements.                |
| `bool vec_is_empty(const Vector *vec)`     | Checks if vector has no elements.  |
