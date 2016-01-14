#include "qsort.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

int* random_int_array(size_t);
double* random_double_array(size_t);
void print_int_array(int*, size_t);
void print_double_array(double*, size_t);
int compar_int(const int*, const int*);
int compar_double(const double*, const double*);
void basic_test(int size);
void test_swap();
bool is_ordered(void* base, size_t num, size_t size, int (*compar)(const void*, const void*));

int main(int argv, char** argc) 
{
	test_swap();
	basic_test(atoi(argc[1]));
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

void test_swap() 
{
	int a = 3;
	int b = 5;
	int* aa = &a;
	int* bb = &b;	
	printf("aa: %d, bb: %d\n", *aa, *bb);
	swap(aa, bb, sizeof(int));
	printf("aa: %d, bb: %d\n", *aa, *bb);
}

void basic_test(int size) 
{
	int* arr = random_int_array(size);
	printf("Unsorted:\n");
	print_int_array(arr, size);
	printf("Is sorted: %d\n", is_ordered(arr, size, sizeof(int), *compar_int));
	qsort(arr, size, sizeof(int), *compar_int);
	printf("Sorted:\n");
	print_int_array(arr, size);
	printf("Is sorted: %d\n", is_ordered(arr, size, sizeof(int), *compar_int));
	double* arr_d = random_double_array(size);
	printf("Unsorted:\n");
	print_double_array(arr_d, size);
	printf("Is sorted: %d\n", is_ordered(arr_d, size, sizeof(double), *compar_double));
	qsort(arr_d, size, sizeof(double), *compar_double);
	printf("Sorted:\n");
	print_double_array(arr_d, size);
	printf("Is sorted: %d\n", is_ordered(arr_d, size, sizeof(double), *compar_double));
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

int compar_double(const double* a, const double* b)
{
	if (*a > *b)
		return 1;
	else if (*a == *b)
		return 0;
	else 
		return -1;
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

void print_int_array(int* base, size_t num) 
{
	for (size_t i = 0; i < num; ++i) 
	{
		printf("%d ", base[i]);
	}
	printf("\n");
}

void print_double_array(double* base, size_t num) 
{
	for (size_t i = 0; i < num; ++i) 
	{
		printf("%f ", base[i]);
	}
	printf("\n");
}
