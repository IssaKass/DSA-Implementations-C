#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

typedef bool (*Predicate)(int);
typedef int (*Function)(int);
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