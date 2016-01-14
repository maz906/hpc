#include "qsort.h"
#include "assert.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "string.h"


int main(int argv, char** argc) 
{
	int test_times = 100;
	int max_size = 1000000;
	int increment = 20000;
	test_swap(test_times);
	basic_test(test_times, max_size, increment);
}


bool is_ordered(void* base, size_t num, size_t size, int (*compar)(const void*, const void*))
{
	for (size_t i = 0; i < num - 1; ++i)
 	{
		if (compar(base + size*i, base + size*(i+1)) > 0)
			return false;
  }	
	return true;
}

void test_swap(int times) 
{
	time_t t;
	srand((unsigned) time(&t));
	#pragma omp parallel for
	for (size_t i = 0; i < times; ++i)
	{
		int a = rand();
		int b = rand();
		int a_copy = a;
		int b_copy = b;
		int* aa = &a;
		int* bb = &b;	
		swap(aa, bb, sizeof(int));
		assert((*aa) == b_copy);
		assert((*bb) == a_copy);
	}
}

void basic_test(int times, int size, int increment) 
{
	for (int i = 0; i < times; ++i)
	{
		#pragma omp parallel for
		for (int j = 0; j < size; j += increment)
		{
			printf("Testing problem size: %d\n", j);

			int* intarr = random_int_array(size);
			double* doublearr = random_double_array(size);
			float* floatarr = random_float_array(size);
			long* longarr = random_long_array(size);
			Point* pointarr = random_point_array(size);

			test_array(intarr, size, sizeof(int), *compar_int);
			free(intarr);
			test_array(doublearr, size, sizeof(double), *compar_double);
			free(doublearr);
			test_array(floatarr, size, sizeof(float), *compar_float);
			free(floatarr);
			test_array(longarr, size, sizeof(long), *compar_long);
			free(longarr);
			test_array(pointarr, size, sizeof(Point), *compar_point);
			free(pointarr);
		}
	}
}

void test_array(void* arri_1, size_t num, size_t size, int (*compar) (const void*, const void*)) 
{
	void* arri_2 = duplicate_array(arri_1, num, size);
	my_qsort(arri_1, num, size, compar);
	qsort(arri_2, num, size, compar);	
	assert(are_equal(arri_1, arri_2, num, size, compar));
	free(arri_2);
}

bool are_equal(void* arr1, void* arr2, size_t num, size_t size, int (*compar)(const void*, const void*))
{
	for (size_t i = 0; i < num; ++i) 
	{
		if (compar(arr1 + size*i, arr2 + size*i) != 0) 
		{
			return false;
		}
	}
	return true;
}

void* duplicate_array(void* arr, size_t num, size_t size) 
{
	void* arr2 = calloc(num, size); 
	memcpy(arr2, arr, num*size);
	return arr2;
}

int compar_int(const int* a, const int* b) 
{
	if (*a > *b)
		return 1;
	else if (*a == *b)
		return 0;
	else 
		return -1;
}

int compar_long(const long* a, const long* b)
{
	if (*a > *b)
		return 1;
	else if (*a == *b)
		return 0;
	else 
		return -1;
}

int compar_double(const double* a, const double* b)
{
	if (*a > *b)
		return 1;
	else if (*a == *b)
		return 0;
	else 
		return -1;
}

int compar_float(const float* a, const float* b) 
{
	if (*a > *b)
		return 1;
	else if (*a == *b)
		return 0;
	else 
		return -1;
}

int compar_point(const Point* a, const Point* b)
{
	if (a->y > b->y)
		return 1;
	else if (a->y < b->y)
		return -1;
	else
		return compar_double(&a->x, &b->x);
}

int* random_int_array(size_t num) 
{
	time_t t;
	srand((unsigned) time(&t));
	int* arr = (int*) calloc(num, sizeof(int));
	for (size_t i = 0; i < num; ++i)
	{
		arr[i] = rand() % 10000;
	}
	return arr;
}

long* random_long_array(size_t num)
{
	time_t t;
	srand((unsigned) time(&t));
	long* arr = (long*) calloc(num, sizeof(long));
	for (size_t i = 0; i < num; ++i)
	{
		int random = rand();
		long longrand = (( (long) random ) << 16) + rand();
		arr[i] = longrand;
	}
	return arr;
}

double* random_double_array(size_t size) 
{
	time_t t;
	srand((unsigned) time(&t));
	double* arr = (double*) calloc(size, sizeof(double));
	for (size_t i = 0; i < size; ++i)
	{
		int random = rand() % 25;
		arr[i] = random + (random/(double)(1 + (rand() % 100)));
	}
	return arr;
}

float* random_float_array(size_t size) 
{
	return (float*) random_double_array(size);
}

Point* random_point_array(size_t size)
{
	Point* arr = (Point*) calloc(size, sizeof(Point));
	Point* p = calloc(1, sizeof(Point));
	time_t t;
	srand((unsigned) time(&t));
	for (size_t i = 0; i < size; ++i) 
	{
		int random = rand() % 100000;
		p->x = random + (random/(double)(1 + (rand() % 100)));
		p->y = random + (random/(double)(1 + (rand() % 100)));
		arr[i] = *p; 
	}
	free(p);
	return arr;
}
