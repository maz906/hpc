#include "qsort.h"
#include "util.h"

#include "assert.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

void swap(void* source, void* dest, size_t size) 
{
	void* temp = calloc(1, size);
	memcpy(temp, source, size);
	memcpy(source, dest, size);
	memcpy(dest, temp, size);
	free(temp);
}

/*
 * base - pointer to the first object of the array to be sorted
 * num - number of elements in the array pointed to by base
 * size - size in bytes of each element of the array
 * compar - pointer to function that compares two elements  
 */
void my_qsort(void* base, size_t num, size_t size,
						int (*compar)(const void*, const void*))
{

	//singleton array, so we are done
	if (num <= 1) return;	
	
	//pivot
	void* pivot = (char*)base + size*(num - 1);
	size_t* swappable = (size_t*) calloc(1, sizeof(size_t));
	select_lower(base, num, size, pivot, swappable, compar);

	//sort the other two arrays.
	#pragma omp parallel sections 
	{
		#pragma omp section 
		{
			qsort(base, *swappable, size, compar);
		}
		#pragma omp section 
		{
			qsort((char*)base + size*(*swappable + 1), num - *swappable - 1, size, compar);
		}
	}
	free(swappable);
}


void select_lower(void* base, size_t num, size_t size, void* pivot, size_t* swappable, int (*compar)(const void*, const void*))
{

	int i;
	int* t = (int*) calloc(num, sizeof(int));	
	#pragma omp parallel for
	for (i = 0; i < num; ++i)
		t[i] = ((*compar)((char*) base + size*i, pivot) == -1) ? 1 : 0;
	int* scan = (int*) genericScan(t, num, sizeof(int), &addition);
	memcpy(swappable, scan + (num - 1)*sizeof(int), size);
	
	//this is an illegal write access in here
	#pragma omp parallel for
	for (i = 0; i < num; ++i)
		if (t[i])
		{

			printf("Size: %d, idx: %d\n", num, i);
			//assert((char*)base + (*(scan + i*sizeof(int)) - 1)*size != NULL);
			//assert((char*)base + i*size != NULL);
			swap((char*)base + (*(scan + i*sizeof(int)) - 1)*size, (char*)base + i*size, size);
		}
	swap(pivot, (char*) base + size*(*swappable), size);
	free(t);
}


/*
 * base - pointer to first object of array
 * n - number of elements in array pointed to by base
 * l - size of pointers in the array
 * oper - pointer to function that operates on two elements 
 */
void* genericScan(void* base, size_t num, size_t byte_size, void*  (*oper)(void *x1, void* x2)) 
{	
	void* scan = calloc(num, byte_size); 
	if (num == 1) { memcpy(scan, base, byte_size); return scan; }
	bool isOdd = (num % 2 == 1);
	int size = isOdd ? (num / 2 + 1) : (num / 2);
	void* b = calloc(size, byte_size);
	int i;
	#pragma omp parallel for
	for (i = 0; i < num / 2; ++i)
	{
		int* add = (*oper) ((char*)base + 2 * i*byte_size, (char*)base + (2 * i + 1)*byte_size);
		memcpy((char*)b + i*byte_size, add, byte_size);
		free(add);
	}

	//edge case if n is odd
	if (isOdd)
	{
		memcpy((char*)b + (num / 2)*byte_size, (char*)base + (num - 1)*byte_size, byte_size);
	}
	void* c = genericScan(b, size, byte_size, oper);
	//free(b);
	memcpy(scan, base, byte_size);	
	#pragma omp parallel for
	for (i = 1; i < num; ++i)
		if (i % 2 == 0)
		{
			int* add = (*oper)((char*)base + i*byte_size, (char*)c + (i/2 - 1)*byte_size);
			memcpy((char*)scan + i*byte_size, add, byte_size);
			free(add);
		}
		else
		{
			memcpy((char*)scan + i*byte_size, (char*)c + (i / 2)*byte_size, byte_size);
		}
	return scan;
}


