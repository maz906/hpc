#include "qsort.h"
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
}

void* addition(void* a, void*b) 
{
	int sum = *(int*)a + *(int*)b;
	int* toReturn = (int*)calloc(1, sizeof(int));
	memcpy(toReturn, &sum, sizeof(int));
	//TODO: fix segfault thrown at this line
	return toReturn;
}

void select_lower(void* base, size_t num, size_t size, void* pivot, size_t* swappable, int (*compar)(const void*, const void*))
{

	int i;
	int* t = (int*) calloc(num, sizeof(int));	
	#pragma omp parallel for
	for (i = 0; i < num; ++i)
		t[i] = ((*compar)((char*) base + size*i, pivot) == -1) ? 1 : 0;
	int* scan = (int*) genericScan(t, num, size, addition);
	//not sure this line is the right move
	memcpy(swappable, scan + (num - 1)*size, size);
	
	#pragma omp parallel for
	for (i = 0; i < num; ++i)
		if (t[i])
			swap((char*) base + (*(scan + i*size) - 1)*size, (char*) base + i*size, size);

	swap(pivot, (char*) base + size*(*swappable), size);
	free(t);
}


/*
 * base - pointer to first object of array
 * n - number of elements in array pointed to by base
 * l - size of pointers in the array
 * oper - pointer to function that operates on two elements 
 */
void* genericScan(void* base, size_t n, size_t l, void*  (*oper)(void *x1, void* x2)) 
{	
	void* scan = calloc(n, l); 
	if (n == 1) { memcpy(scan, base, l); return scan; }
	bool isOdd = (n % 2 == 1);
	int size = isOdd ? (n / 2 + 1) : (n / 2);
	void* b = calloc(size, l);
	int i;
	#pragma omp parallel for
	for (i = 0; i < n / 2; ++i)
	{
		memcpy((char*)b + i*l, (*oper) ((char*)base + 2 * i*l, (char*)base + (2 * i + 1)*l), l);
	}

	//edge case if n is odd
	//if (isOdd)
	//{
	//	memcpy((char*)b + (n / 2)*l, (char*)base + 2 * n*l, l);
	//}
	void* c = genericScan(b, size, l, oper);
	memcpy(scan, base, l);	
	#pragma omp parallel for
	for (i = 0; i < n; ++i)
		if (i % 2 == 0)
			memcpy((char*)scan + i*l, (*oper)((char*)c + (i/2)*l, (char*)base + i*l), l);
		else
			memcpy((char*)scan + i*l, (char*)c + (i/2)*l, l);
	free(b);
	return scan;
}


