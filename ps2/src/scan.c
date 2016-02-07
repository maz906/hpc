#include "scan.h"
#include "util.h"

#include "math.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"


/*
 * base - pointer to first object of array
 * num - number of elements in array pointed to by base
 * size - size of pointers in the array
 * oper - pointer to function that operates on two elements 
 */
void slowScan(void* base, int num, int size, void* (*oper)(void *x1, void *x2))
{
	if (num > 1)
	{
		int i;
		for (i = 1; i < num; ++i)
		{
			int* add = (*oper)((char*)base + (i - 1)*size, (char*)base + i*size);
			memcpy((char*)base + i*size, add, size);
			free(add);
		}
	}
}

/*
 * base - pointer to first object of array
 * num - number of elements in array pointed to by base
 * size - size of pointers in the array
 * oper - pointer to function that operates on two elements 
 */
void genericScan(void* base, int num, int byte_size, void*  (*oper)(void *x1, void* x2)) 
{	
	if (num > 1)
	{
		int d; int k;
		int logg = (int)ceil(log2(num));
		for (d = 0; d < logg; ++d)
		{
			int inc = (int)exp2(d);
			int two_inc = 2 * inc;
#pragma omp parallel for
			for (k = 0; k < num; k += two_inc)
			{
				int idx1 = k + inc - 1;
				int idx2 = k + two_inc - 1;
				if (idx1 >= num || idx2 >= num)
					break;
				void* add = (*oper)((char*)base + (k + inc - 1)*byte_size, (char*)base + (k + two_inc - 1)*byte_size);
				memcpy((char*)base + (k + two_inc - 1)*byte_size, add, byte_size);
				free(add);
			}
		}

		
		for (d = logg - 1; d >= 0; --d)
		{
			int inc = (int)exp2(d);
			int two_inc = 2 * inc;
#pragma omp parallel for
			for (k = 0; k < num; k += two_inc)
			{
				int idx1 = k + inc + two_inc - 1;
				int idx2 = k + two_inc - 1;
				if (idx1 >= num || idx2 >= num)
					break;
				void* add = (*oper)((char*)base + (idx2)*byte_size, (char*)base + (idx1)*byte_size);
				memcpy((char*)base + (idx1)*byte_size, add, byte_size);
				free(add);
		}
		}
	}
}

