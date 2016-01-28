#include "assert.h"
#include "stdlib.h"
#include "string.h"

#include "scan_test.h"
#include "qsort.h"
#include "util.h"

void* slowScan(void* base, size_t num, size_t size, void* (*oper)(void *x1, void *x2))
{
	int i;
	void* scanned = calloc(num, size);
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
	for (i = 1; i <= size; ++i)
	{
		printf("Testing prefix sum for size: %d\n", i);
		int* ones = random_int_array(i);
		int* ones_dup = duplicate_array(ones, i, sizeof(int));
		assert(are_equal(ones, ones_dup, i, sizeof(int), &compar_int));
		int* scanned = genericScan(ones, i, sizeof(int), &addition);
		free(ones);
		int* slow_scanned = slowScan(ones_dup, i, sizeof(int), &addition);
		free(ones_dup);
		assert(are_equal(scanned, slow_scanned, i, sizeof(int), &compar_int));
		free(scanned); free(slow_scanned);
	}
}
