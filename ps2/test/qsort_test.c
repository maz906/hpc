#include "qsort.h"
#include "point.h"
#include "qsort_test.h"
#include "util.h"

#include "assert.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "string.h"

#include "omp.h"

extern int INCREMENT;

void qsort_test(int size)
{
	omp_set_num_threads(6);
	//rigor_qsort_test(size);
	basic_qsort_test(size, INCREMENT);
}

void scale_qsort_test(int procs, int size)
{
	for (int i = 1; i < procs; i *= 2)
	{
		printf("Number of threads: %d\n", i);
		omp_set_num_threads(i);
		basic_qsort_test(size, INCREMENT);
	}
}

void rigor_qsort_test(int size)
{
	size = min(10000, size);
	int i;
	for (i = 1; i <= size; ++i)
	{
		printf("Testing qsort for size: %d\n", i);
		int* ones = random_int_array(i);
		int* ones_dup = duplicate_array(ones, i, sizeof(int));
		my_qsort(ones, i, sizeof(int), &compar_int);
		qsort(ones_dup, i, sizeof(int), &compar_int);
		assert(are_equal(ones, ones_dup, i, sizeof(int), &compar_int));
		free(ones); free(ones_dup);
	}
}

void basic_qsort_test(int size, int increment) 
{
	
	int i, j;
	int* rand_int; double* rand_double; float* rand_float; long* rand_long; Point* rand_point; 
	for (j = increment; j <= size; j += increment)
	{
			rand_int = random_int_array(j);
			rand_double = random_double_array(j);
			rand_float = random_float_array(j);
			rand_long = random_long_array(j);
			rand_point = random_point_array(j);
			test_qsort_array(rand_int, j, sizeof(int), &compar_int);
			test_qsort_array(rand_double, j, sizeof(double), &compar_double);
			test_qsort_array(rand_float, j, sizeof(float), &compar_float);
			test_qsort_array(rand_long, j, sizeof(long), &compar_long);
			test_qsort_array(rand_point, j, sizeof(Point), &compar_point);
			free(rand_int); free(rand_double); free(rand_long); free(rand_point); free(rand_float);
		}
}

void test_qsort_array(void* arri_1, size_t num, size_t size, int (*compar) (const void*, const void*)) 
{
	void* arri_2 = duplicate_array(arri_1, num, size);
	my_qsort(arri_1, num, size, compar);
	qsort(arri_2, num, size, compar);	
	assert(are_equal(arri_1, arri_2, num, size, compar));
	free(arri_1); free(arri_2);
}

