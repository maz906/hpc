#include "qsort.h"
#include "assert.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "string.h"

void print_int_array(int* base, size_t num) 
{
	for (size_t i = 0; i < num; ++i) 
	{
		printf("%d ", base[i]);
	}
	printf("\n");
}

int main(int argv, char** argc) 
{
	if (argv < 4)
	{
		printf("Usage: ./test_qsort [iterations] [max_problem_size] [increment_step]\n");
		return 1;
	}
	test_swap(atoi(argc[1]));
	basic_test(atoi(argc[1]), atoi(argc[2]), atoi(argc[3]));
	return 0;
}


bool is_ordered(void* base, size_t num, size_t size, int (*compar)(const void*, const void*))
{
	for (size_t i = 0; i < num - 1; ++i)
 	{
		if (compar(((char*)base) + size*i, ((char*)base) + size*(i+1)) > 0)
			return false;
  }	
	return true;
}

void test_swap(size_t times) 
{
	time_t t;
	srand((unsigned) time(&t));
	int i;
	#pragma omp parallel for
	for (i = 0; i < times; ++i)
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

void basic_test(size_t times, size_t size, size_t increment) 
{
	int i, j;
	double int_time = 0, double_time = 0, float_time = 0, long_time = 0, point_time = 0;
	double int_time_single, double_time_single, long_time_single, point_time_single, float_time_single;
	for (j = 0; j < size; j += increment)
	{
		#pragma omp parallel for
		for (i = 0; i < times; ++i)
		{
			int_time_single = test_array(random_int_array(j), j, sizeof(int), *compar_int);
			double_time_single = test_array(random_double_array(j), j, sizeof(double), *compar_double);
			float_time_single = test_array(random_float_array(j), j, sizeof(float), *compar_float);
			long_time_single = test_array(random_long_array(j), j, sizeof(long), *compar_long);
			point_time_single = test_array(random_point_array(j), j, sizeof(Point), *compar_point);

			#pragma omp atomic
			int_time += int_time_single;
			#pragma omp atomic
			double_time += double_time_single;
			#pragma omp atomic
			long_time += long_time_single;
			#pragma omp atomic
			float_time += float_time_single;
			#pragma omp atomic
			point_time += point_time_single;
		}
		printf("(int) array_size: %d, sort_time (ms): %f\n", j, int_time/times);
		printf("(double) array_size: %d, sort_time (ms): %f\n", j, double_time/times);
		printf("(float) array_size: %d, sort_time (ms): %f\n", j, float_time/times);
		printf("(long) array_size: %d, sort_time (ms): %f\n", j, long_time/times);
		printf("(point) array_size: %d, sort_time (ms): %f\n", j, point_time/times);
		printf("\n");
		int_time = double_time = float_time = long_time = point_time = 0;
	}
}

double test_array(void* arri_1, size_t num, size_t size, int (*compar) (const void*, const void*)) 
{
	void* arri_2 = duplicate_array(arri_1, num, size);
	clock_t difference;	
	clock_t start = clock();
	my_qsort(arri_1, num, size, compar);
	difference = clock() - start;	
	qsort(arri_2, num, size, compar);	
	assert(are_equal(arri_1, arri_2, num, size, compar));
	free(arri_2);
	return difference * 1000/CLOCKS_PER_SEC;
}

bool are_equal(void* arr1, void* arr2, size_t num, size_t size, int (*compar)(const void*, const void*))
{
	for (size_t i = 0; i < num; ++i) 
	{
		if (compar(((char*)arr1) + size*i, ((char*)arr2) + size*i) != 0) 
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
