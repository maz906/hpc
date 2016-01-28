#pragma once

#include "point.h"

int* random_int_array(size_t);
double* random_double_array(size_t);
float* random_float_array(size_t);
long* random_long_array(size_t);
Point* random_point_array(size_t);
int compar_int(const int*, const int*);
int compar_double(const double*, const double*);
int compar_long(const long*, const long*);
int compar_float(const float*, const float*);
int compar_point(const Point*, const Point*);
void basic_test(size_t times, size_t size, size_t increment);
bool is_ordered(void* base, size_t num, size_t size, int (*compar)(const void*, const void*));
bool are_equal(void* arr1, void* arr2, size_t num, size_t size, int (*compar) (const void*, const void*));
void* duplicate_array(void* arr, size_t num, size_t size);
Point test_array(void* arr, size_t num, size_t size, int (*compar) (const void*, const void*));

void* addition(void* a, void*b);
