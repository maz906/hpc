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
	scale_qsort_test(size, 24);
	rigor_qsort_test(size);
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
		printf("Testing prefix sum for size: %d\n", i);
		int* ones = random_int_array(i);
		int* ones_dup = duplicate_array(ones, i, sizeof(int));
		my_qsort(ones, i, sizeof(int), &addition);
		my_qsort(ones_dup, i, sizeof(int), &addition);
		assert(are_equal(ones, ones_dup, i, sizeof(int), &compar_int));
		free(ones); free(ones_dup);
	}
}

void basic_qsort_test(int size, int increment) 
{
	
	int i, j;
	int times = 300;
	int* rand_int; double* rand_double; float* rand_float; long* rand_long; Point* rand_point;
	double int_time = 0, double_time = 0, float_time = 0, long_time = 0, point_time = 0;
	Point int_time_single, double_time_single, long_time_single, point_time_single, float_time_single;
	double int_time_std = 0, double_time_std = 0, float_time_std = 0, long_time_std = 0, point_time_std = 0;
	for (j = increment; j <= size; j += increment)
	{
		for (i = 0; i < times; ++i)
		{
			rand_int = random_int_array(j);
			rand_double = random_double_array(j);
			rand_float = random_float_array(j);
			rand_long = random_long_array(j);
			rand_point = random_point_array(j);
			int_time_single = test_array(rand_int, j, sizeof(int), *compar_int);
			double_time_single = test_array(rand_double, j, sizeof(double), *compar_double);
			float_time_single = test_array(rand_float, j, sizeof(float), *compar_float);
			long_time_single = test_array(rand_long, j, sizeof(long), *compar_long);
			point_time_single = test_array(rand_point, j, sizeof(Point), *compar_point);

			int_time += int_time_single.x;
			double_time += double_time_single.x;
			long_time += long_time_single.x;
			float_time += float_time_single.x;
			point_time += point_time_single.x;

			int_time_std += int_time_single.y;
			double_time_std += double_time_single.y;
			long_time_std += long_time_single.y;
			float_time_std += float_time_single.y;
			point_time_std += point_time_single.y;

		}
		printf("(int) array_size: %d, sort_time (ms): %g\n", j, int_time/times);
		printf("(double) array_size: %d, sort_time (ms): %g\n", j, double_time/times);
		printf("(float) array_size: %d, sort_time (ms): %g\n", j, float_time/times);
		printf("(long) array_size: %d, sort_time (ms): %g\n", j, long_time/times);
		printf("(point) array_size: %d, sort_time (ms): %g\n", j, point_time/times);
		printf("(int) array_size: %d, sort_time_std (ms): %g\n", j, int_time_std/times);
		printf("(double) array_size: %d, sort_time_std (ms): %g\n", j, double_time_std/times);
		printf("(float) array_size: %d, sort_time_std (ms): %g\n", j, float_time_std/times);
		printf("(long) array_size: %d, sort_time_std (ms): %g\n", j, long_time_std/times);
		printf("(point) array_size: %d, sort_time_std (ms): %g\n", j, point_time_std/times);
		printf("\n");
		int_time = double_time = float_time = long_time = point_time = 0;
		int_time_std = double_time_std = long_time_std = float_time_std = point_time_std = 0;
	}
}

Point test_array(void* arri_1, size_t num, size_t size, int (*compar) (const void*, const void*)) 
{
	void* arri_2 = duplicate_array(arri_1, num, size);
	assert(are_equal(arri_1, arri_2, num, size, compar));
	clock_t difference;	
	clock_t start = clock();
	my_qsort(arri_1, num, size, compar);
	difference = clock() - start;	
	clock_t difference_std;
	start = clock();
	qsort(arri_2, num, size, compar);	
	difference_std = clock() - start;
	assert(are_equal(arri_1, arri_2, num, size, compar));
	Point p = { .x = difference * 1000/CLOCKS_PER_SEC, .y = difference_std * 1000/CLOCKS_PER_SEC};
	free(arri_1); free(arri_2);
	return p;
}

