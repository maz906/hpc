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

	//partition the array: non-parallel
	//size_t swappable = 0, i;
	//for (i = 0; i < num; ++i)
	//{
	//	if ((*compar)((char*)base + size*i, pivot) < 0) 
	//	{
	//		//if smaller than pivot, switch i with wherever the most recent larger than element is
	//		swap((char*)base + size*(swappable++), (char*)base + size*i, size);
	//	}
	//}
	size_t* swappable;
	select_lower(base, num, size, pivot, swappable, compar);
	//put the pivot in the right place	
	//non-parallel
	//swap(pivot, (char*)base + size*(swappable), size);

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
	int aa = * (int*) a;
	int bb = * (int*) b;
	int sum = aa + bb;
	int* toReturn;
	memcpy(toReturn, &sum, sizeof(int));
	return toReturn;
}

void select_lower(void* base, size_t num, size_t size, void* pivot, size_t* swappable, int (*compar)(const void*, const void*))
{

	int i;
	int* t = (int*) calloc(num, sizeof(int));	
	#pragma omp parallel for
	for (i = 0; i < num; ++i)
		t[i] = (*compar)((char*) base + size*i, pivot);
	int* scan = (int*) genericScan(base, num, size, addition);
	swappable = (size_t*) (scan + (num - 1)*size);
	
	#pragma omp parallel for
	for (i = 0; i < num; ++i)
		if (t[i])
			swap(base + (*(scan + i*size) - 1)*size, base + i*size, size);

	swap(pivot, base + size*(*swappable), size);
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
	void* b = calloc(n/2, l);
	if (n == 1) { memcpy(scan, base, l); }
	int i;
	#pragma omp parallel for
	for (i = 0; i < n/2; ++i) 
		memcpy(b+i*l, (*oper)(base + 2*i*l, base + (2*i + 1)*l), l); 

	//edge case if n is odd
	if (i % 2 == 0)
		memcpy(b + i*l, base + 2*i*l, l);

	void* c = genericScan(b, n/2, l, oper);
	memcpy(scan, base, l);	
	#pragma omp parallel for
	for (i = 0; i < n; ++i)
		if (i % 2 == 0)
			memcpy(scan + i*l, (*oper)(c + (i/2)*l, base + i*l), l);
		else
			memcpy(scan + i*l, c + (i/2)*l, l);
	free(b);
	return scan;
}


