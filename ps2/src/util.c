#include "assert.h"
#include "stddef.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"


#include "point.h"
#include "time.h"


void* addition(void* a, void*b) 
{
	int sum = *(int*)a + *(int*)b;
	int* toReturn = (int*)malloc(sizeof(int));
	memcpy(toReturn, &sum, sizeof(int));
	return toReturn;
}

void* add_doub(double* a, double*b)
{
	double sum = *(double*)a + *(double*)b;
	double* toReturn = (double*)malloc(sizeof(double));
	memcpy(toReturn, &sum, sizeof(double));
	return toReturn;
}
void* add_float(float* a, float* b)
{
	float sum = *(float*)a + *(float*)b;
	float* toReturn = (float*)malloc(sizeof(float));
	memcpy(toReturn, &sum, sizeof(float));
	return toReturn;
}

void add_long(long* a, long*b)
{
	long sum = *(long*)a + *(long*)b;
	long* toReturn = (long*)malloc(sizeof(long));
	memcpy(toReturn, &sum, sizeof(long));
	return toReturn;
}

Point* add_point(Point* a, Point* b)
{
	Point* sum = malloc(sizeof(Point));
	sum->x = a->x + b->x;
	sum->y = a->y + b->y;
	return sum;
}

Vector* add_vec(Vector* a, Vector* b)
{
	Vector* vec = (Vector*) malloc(sizeof(Vector));
	vec->x = a->x + b->x;
	vec->y = a->y + b->y;
	vec->z = a->z + b->z;
	return vec;
}

void print_int_array(int* base, size_t num) 
{
	size_t i;
	for (i = 0; i < num; ++i) 
	{
		printf("%d ", base[i]);
	}
	printf("\n");
}

bool is_ordered(void* base, size_t num, size_t size, int (*compar)(const void*, const void*))
{
	size_t i;
	for (i = 0; i < num - 1; ++i)
 	{
		if (compar(((char*)base) + size*i, ((char*)base) + size*(i+1)) > 0)
			return false;
  }	
	return true;
}

bool are_equal(void* arr1, void* arr2, size_t num, size_t size, int (*compar)(const void*, const void*))
{
	size_t i;
	for (i = 0; i < num; ++i) 
	{
		if ((*compar)((char*)arr1 + size*i, (char*)arr2 + size*i) != 0)
			return false;
	}
	return true;
}

void* duplicate_array(void* arr, size_t num, size_t size) 
{
	void* arr2 = malloc(num* size); 
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
	int* arr = (int*) malloc(num * sizeof(int));
	size_t i;
	for (i = 0; i < num; ++i)
	{
		arr[i] = rand() % 10000;
	}
	return arr;
}

long* random_long_array(size_t num)
{
	time_t t;
	srand((unsigned) time(&t));
	long* arr = (long*) malloc(num * sizeof(long));
	size_t i;
	for (i = 0; i < num; ++i)
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
	double* arr = (double*) malloc(size * sizeof(double));
	size_t i;
	for (i = 0; i < size; ++i)
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
	Point* arr = (Point*) malloc(size* sizeof(Point));
	Point* p = (Point*) malloc(sizeof(Point));
	time_t t;
	srand((unsigned) time(&t));
	size_t i;
	for (i = 0; i < size; ++i) 
	{
		int random = rand() % 100000;
		p->x = random + (random/(double)(1 + (rand() % 100)));
		p->y = random + (random/(double)(1 + (rand() % 100)));
		arr[i] = *p; 
	}
	free(p);
	return arr;
}
Vector* random_vec_array(size_t size)
{
	Vector* arr = (Vector*) malloc(size* sizeof(Vector));
	Vector* p = (Vector*) malloc(sizeof(Vector));
	time_t t;
	srand((unsigned) time(&t));
	size_t i;
	for (i = 0; i < size; ++i) 
	{
		int random = rand() % 100000;
		p->x = random + (random/(double)(1 + (rand() % 100)));
		p->y = random + (random/(double)(1 + (rand() % 100)));
		p->z = random + (random/(double)(1 + (rand() % 100)));
		arr[i] = *p; 
	}
	free(p);
	return arr;
}
