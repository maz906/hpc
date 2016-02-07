#include "point.h"
#include "qsort.h"
#include "qsort_test.h"

#include "stddef.h"

#include "omp.h"

extern int INCREMENT;

void qsort_test(int size)
{
	omp_set_num_threads(6);
	rigor_qsort_test(size);
	basic_qsort_test(size, INCREMENT);
}

void rigor_qsort_test(int size)
{
	size = min(10000, size);
	int i;
	for (i = 1; i <= size; ++i)
	{
		printf("Testing qsort for size: %d\n", i);
		basic_qsort_test(i, INCREMENT);	
	}
}

void basic_qsort_test(int size, int increment)
{
	int i;
	int* rand_int; double* rand_doub; float* rand_float; long* rand_long; Point* rand_point;
	for (i = increment; i <= size; i += increment)
	{
		printf("Testing qsort for size: %d\n", i);	
		rand_int = rand_int_array(i);
		rand_doub = rand_double_array(i);
		rand_float = rand_float_array(i);
		rand_long = rand_long_array(i);
		rand_point = rand_point_array(i);

		test_qsort_array(rand_int, i, size, &compar_int);
		test_qsort_array(rand_doub, i, size, &compar_double);
		test_qsort_array(rand_float, i, size, &compar_float);
		test_qsort_array(rand_long, i, size, &compar_long);
		test_qsort_array(rand_point, i, size, &compar_point);
	}
}

void test_qsort_array(void* arri1, size_t num, size_t size, int(*compar)(const void*, const void*))
{
	void* arri_2 = duplicate_array(arri1, num, size);
	my_qsort(arri_1, num, size, compar);
	qsort(arri_2, num, size, compar);
	assert(are_equal(arri1, arri_2, num, size, compar));
	free(arri1); free(arri_2);
}
