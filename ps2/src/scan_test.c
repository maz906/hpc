#include "assert.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#include "scan.h"
#include "scan_test.h"
#include "util.h"

extern int INCREMENT;

void scan_test(int size)
{
	rigor_scan_test(size);
	basic_scan_test(size, INCREMENT);
}
/**
  * Tests every single size from min(10000, size).
  *
  */
void rigor_scan_test(int size)
{
	size = min(10000, size);
	int i;
	for (i = 1; i <= size; i += 10)
	{
		printf("Testing prefix sum for size: %d\n", i);
		int* ones = random_int_array(i);
		int* ones_dup = duplicate_array(ones, i, sizeof(int));
		genericScan(ones, i, sizeof(int), &addition);
		slowScan(ones_dup, i, sizeof(int), &addition);
		assert(are_equal(ones, ones_dup, i, sizeof(int), &compar_int));
		free(ones); free(ones_dup);
	}
}

/**
  * To be used for timing
  *
  *
  */
void basic_scan_test(int size, int increment)
{
	int i; int* temp_ones; int* temp_ones_dup;
	for (i = increment; i <= size; i += increment)
	{

		printf("Testing prefix sum for size: %d\n", i);
		int* ones = random_int_array(i);
		int* ones_dup = (int*) duplicate_array(ones, i, sizeof(int));
		genericScan(ones, i, sizeof(int), &addition);
		slowScan(ones_dup, i, sizeof(int), &addition);
		assert(are_equal(ones, ones_dup, i, sizeof(int), &compar_int));
		free(ones); free(ones_dup);
	}
}
