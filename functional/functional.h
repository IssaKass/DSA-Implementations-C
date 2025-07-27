#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

// Predicate: Takes an int, returns true/false
typedef bool (*Predicate)(int);

// Function: Takes an int, returns an int (for map, etc.)
typedef int (*Function)(int);

// Consumer: Takes an int, returns nothing (for foreach)
typedef void (*Consumer)(int);

// Common predicates
bool is_even(int x);
bool is_odd(int x);
bool is_positive(int x);
bool is_negative(int x);
bool is_zero(int x);

// Common functions
int negate(int x);
int square(int x);

// Common consumers
void print_int(int x);

#endif // FUNCTIONAL_H