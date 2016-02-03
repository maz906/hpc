#include "qsort.h"
#include "point.h"
#include "scan_test.h"
#include "util.h"
#include "test.h"

#include "assert.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "string.h"

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

void experiment(int size);
void scale_test(int procs, size_t times, size_t size, size_t increment);


int main(int argv, char** argc) 
{
	if (argv < 4)
	{
		printf("Usage: ./test_qsort [iterations] [max_problem_size] [increment_step]\n");
		return 1;
	}
	scale_test(24, atoi(argc[1]), atoi(argc[2]), atoi(argc[3]));
	return 0;
}

void scale_test(int procs, size_t times, size_t size, size_t increment)
{
	for (int i = procs; i <= procs; i *= 2)
	{
		omp_set_num_threads(i);
		printf("Setting number of processes: %d\n", i);
		basic_test(times, size, increment);
	}
}

void experiment(int size)
{

	int* ptr1 = (int*)malloc(size *sizeof(int));
	for (int i = 0; i < size; ++i)
		ptr1[i] = i;
	
	int* ptr2 = (int*) malloc(size *sizeof(int));
	memcpy(ptr2, ptr1, sizeof(int) * size);
	for (int i = 0; i < size; ++i)
		ptr2[i]++;

	assert(are_equal(ptr1, ptr2, size, sizeof(int), *compar_int));
}


void basic_test(size_t times, size_t size, size_t increment) 
{
	
	int i, j;
	double int_time = 0, double_time = 0, float_time = 0, long_time = 0, point_time = 0;
	Point int_time_single, double_time_single, long_time_single, point_time_single, float_time_single;
	double int_time_std = 0, double_time_std = 0, float_time_std = 0, long_time_std = 0, point_time_std = 0;
	for (j = increment; j <= size; j += increment)
	{
		for (i = 0; i < times; ++i)
		{
			int_time_single = test_int_array(j, sizeof(int));
			int_time += int_time_single.x;
			int_time_std += int_time_single.y;

			//double_time_single = test_double_array(j, sizeof(double));
			//double_time += double_time_single.x;
			//double_time_std += double_time_single.y;

			//float_time_single = test_float_array(j, sizeof(float));
			//float_time += float_time_single.x;
			//float_time_std += float_time_single.y;

			//long_time_single = test_long_array(j, sizeof(long));
			//long_time += long_time_single.x;
			//long_time_std += long_time_single.y;

			//point_time_single = test_Point_array(j, sizeof(Point));
			//point_time += point_time_single.x;
			//point_time_std += point_time_single.y;
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


