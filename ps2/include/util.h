#pragma once

#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#include "point.h"

int* random_int_array(size_t);
double* random_double_array(size_t);
float* random_float_array(size_t);
long* random_long_array(size_t);
Point* random_point_array(size_t);
Vector* random_vec_array(size_t size);
int compar_int(const int*, const int*);
int compar_double(const double*, const double*);
int compar_long(const long*, const long*);
int compar_float(const float*, const float*);
int compar_point(const Point*, const Point*);

bool is_ordered(void* base, size_t num, size_t size, int (*compar)(const void*, const void*));
bool are_equal(void* arr1, void* arr2, size_t num, size_t size, int (*compar) (const void*, const void*));
void* duplicate_array(void* arr, size_t num, size_t size);
Point test_array(void* arr, size_t num, size_t size, int (*compar) (const void*, const void*));

void* addition(void* a, void*b);
void* add_doub(double* a, double*b);
void* add_float(float* a, float* b);
void add_long(long* a, long*b);
Point* add_point(Point* a, Point* b);
Vector* add_vec(Vector* a, Vector* b);

void print_int_array(int* base, size_t num);

//mostly for quicksort but...
extern inline void swap(void* source, void* dest, size_t size) 
{
	void* temp = malloc(size);
	memcpy(temp, source, size);
	memcpy(source, dest, size);
	memcpy(dest, temp, size);
	free(temp);
}

inline void* median(void* a, void* b, void* c, int(*compar)(const void*, const void*))
{
	return (*compar)(a, b) < 0 ?
		((*compar)(b, c) < 0 ? b : ((*compar)(a, c) < 0 ? c : a))
		: ((*compar)(b, c) > 0 ? b : ((*compar)(a, c) > 0 ? c : a));
}

inline void* three_med(void* base, int num, int size, int(*compar)(const void*, const void*))
{
	return median(base, (char*)base + (num / 2)*size, (char*)base + (num - 1)*size, compar);
}