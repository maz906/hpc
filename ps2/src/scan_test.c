#include "assert.h"
#include "stdlib.h"
#include "string.h"

#include "scan_test.h"
#include "qsort.h"
#include "util.h"

#include "omp.h"

void* slowScan(void* base, size_t num, size_t size, void* (*oper)(void *x1, void *x2))
{
	int i;
	void* scanned = malloc(num * size);
	memcpy(scanned, base, size);
	for (i = 1; i < num; ++i)
	{
		int* add = (*oper)((char*)scanned + (i - 1)*size, (char*)base + i*size);
		memcpy((char*)scanned + i*size, add, size);
		free(add);
	}
	return scanned;
}

void scan_test(int size)
{
	basic_scan_test(size);
}

void basic_scan_test(int size)
{
	int i;
	double start; double end;
	for (i = size; i <= size; ++i)
	{
		printf("Testing prefix sum for size: %d\n", i);
		int* ones = random_int_array(i);
		int* ones_dup = duplicate_array(ones, i, sizeof(int));
		assert(are_equal(ones, ones_dup, i, sizeof(int), &compar_int));
		start = omp_get_wtime();
		int* scanned = genericScan(ones, i, sizeof(int), &addition);
		end = omp_get_wtime();
		printf("generic scan (ints) total time: %f", end - start);
		free(ones);
		int* slow_scanned = slowScan(ones_dup, i, sizeof(int), &addition);
		free(ones_dup);
		assert(are_equal(scanned, slow_scanned, i, sizeof(int), &compar_int));
		free(scanned); free(slow_scanned);

	}
}

void basic_vector_scan_test(int size)
{
	int i;
	double start; double end;
	for (i = size; i <= size; ++i)
	{
		printf("Testing prefix sum for size: %d\n", i);
		Vector* ones = random_vector_array(i);
		Vector* ones_dup = duplicate_array(ones, i, sizeof(Vector));
		assert(are_equal(ones, ones_dup, i, sizeof(Vector), &compar_int));
		start = omp_get_wtime();
		Vector* scanned = genericScan(ones, i, sizeof(Vector), &addition);
		end = omp_get_wtime();
		printf("generic scan (points) total time: %f", end - start);
		free(ones);
		Vector* slow_scanned = slowScan(ones_dup, i, sizeof(Vector), &addition);
		free(ones_dup);
		assert(are_equal(scanned, slow_scanned, i, sizeof(Vector), &compar_int));
		free(scanned); free(slow_scanned);
	}
}

void basic_point_scan_test(int size)
{
	int i;
	double start; double end;
	for (i = size; i <= size; ++i)
	{
		printf("Testing prefix sum for size: %d\n", i);
		Point* ones = random_vector_array(i);
		Point* ones_dup = duplicate_array(ones, i, sizeof(Point));
		assert(are_equal(ones, ones_dup, i, sizeof(Point), &compar_int));
		start = omp_get_wtime();
		Point* scanned = genericScan(ones, i, sizeof(Point), &addition);
		end = omp_get_wtime();
		printf("generic scan (vectors) total time: %f", end - start);
		free(ones);
		Point* slow_scanned = slowScan(ones_dup, i, sizeof(Point), &addition);
		free(ones_dup);
		assert(are_equal(scanned, slow_scanned, i, sizeof(Point), &compar_int));
		free(scanned); free(slow_scanned);
	}
}
