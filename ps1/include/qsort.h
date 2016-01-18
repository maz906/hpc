#include "stddef.h"
#include "stdbool.h"

typedef struct _Point {
	double x;
	double y;
} Point;

void swap (void* source, void* dest, size_t size);
void my_qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));

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
void basic_test(int times, int size);
void test_swap(int times);
bool is_ordered(void* base, size_t num, size_t size, int (*compar)(const void*, const void*));
bool are_equal(void* arr1, void* arr2, size_t num, size_t size, int (*compar) (const void*, const void*));
void* duplicate_array(void* arr, size_t num, size_t size);
double test_array(void* arr, size_t num, size_t size, int (*compar) (const void*, const void*));
