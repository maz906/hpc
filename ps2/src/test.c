#include "point.h"
#include "qsort.h"
#include "util.h"
#include "test.h"

#include "assert.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

Point run(void* arri_1, void* arri_2, size_t num, size_t size, int (*compar) (const void*, const void*))
{
	clock_t start;
	//assert(are_equal(arri_1, arri_2, num, size, compar));
	clock_t difference;	clock_t difference_std;
	start = clock();
	qsort(arri_2, num, size, compar);	
	difference_std = clock() - start;
	//assert(!is_ordered(arri_2, num, size, compar));
	//time the standard library
	start = clock();
	my_qsort(arri_1, num, size, compar);
	difference = clock() - start;	
	//we're just testing for speed now
	//print_int_array(arri_1, num);
	//print_int_array(arri_2, num);
	assert(are_equal(arri_1, arri_2, num, size, compar));
	free(arri_1); free(arri_2);
	Point p = { .x = difference * 1000/CLOCKS_PER_SEC, .y = difference_std * 1000/CLOCKS_PER_SEC};
	return p;
}

Point test_int_array(size_t num, size_t size) 
{
	void* compar = &compar_int;
	int* arri_1 = random_int_array(num);
	int* arri_2 = (int*) duplicate_array(arri_1, num, size);
	return run(arri_1, arri_2, num, size, compar);
}

Point test_float_array(size_t num, size_t size)
{
	void* compar = &compar_float;
	float* arri1 = random_float_array(num);
	float* arri2 = (float*)duplicate_array(arri1, num, size);
	return run(arri1, arri2, num, size, compar);
}
Point test_double_array(size_t num, size_t size)
{
	void* compar = &compar_double;
	double* arri1 = random_double_array(num);
	double* arri2 = (double*)duplicate_array(arri1, num, size);
	return run(arri1, arri2, num, size, compar);
}
Point test_long_array(size_t num, size_t size)
{
	void* compar = &compar_long;
	long* arri1 = random_long_array(num);
	long* arri2 = (long*)duplicate_array(arri1, num, size);
	return run(arri1, arri2, num, size, compar);
}
Point test_Point_array(size_t num, size_t size)
{
	void* compar = &compar_point;
	Point* arri1 = random_point_array(num);
	Point* arri2 = (Point*)duplicate_array(arri1, num, size);
	return run(arri1, arri2, num, size, compar);
}