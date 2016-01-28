#include "scan_test.h"
#include "qsort.h"
#include "util.h"


void scan_test(int size)
{
	int* temp = random_int_array(size);
	genericScan(temp, size, sizeof(int), &addition);
}