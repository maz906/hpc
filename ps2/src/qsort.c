#include "qsort.h"
#include "scan_test.h"
#include "util.h"

#include "assert.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

#include "omp.h"

inline void swap(void* source, void* dest, size_t size) 
{
	//more optimal way besides memcpy?
	void* temp = malloc(size);
	memcpy(temp, source, size);
	memcpy(source, dest, size);
	memcpy(dest, temp, size);
	free(temp);
}

inline void* median(void* a, void* b, void* c, int (*compar)(const void*, const void*)) 
{
	return (*compar)(a, b) < 0 ? 
				  ( (*compar)(b, c) < 0 ? b : ((*compar)(a, c) < 0 ? c : a))
				: ( (*compar)(b, c) > 0 ? b : ((*compar)(a, c) > 0 ? c : a));
}

inline void* three_med(void* base, int num, int size, int (*compar)(const void*, const void*))
{
	return median(base, (char*)base + (num / 2)*size, (char*)base + (num - 1)*size, compar);
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
	if (num > 1)
	{	
		//insertion sort if small enough
		//if (num <= 7)
		//{
		//	int i; int j;
		//	for (i = 1; i < num; ++i)
		//	{
		//		int* swap = (char*)base + i*size;
		//		while (j >= 0 && (*compar)((char*)base + j*size, swap) > 0)
		//		{
		//			memcpy((char*)base + (j + 1)*size, (char*)base + j*size, size);
		//			j--;
		//		}
		//		memcpy((char*)base + (j + 1)*size, swap, size);
		//	}
		//	return;
		//}	
		
		//pivot
		//pick last item as pivot
		//void* pivot = (char*)base + (num - 1)*size;
		//median of three
		//void* pivot = median(base, (char*)base + size*(num / 2), (char*)base + size*(num - 1), compar);
		//ninther strategy
		int div = num / 3;
		void* pivot = median(three_med(base, div, size, compar), three_med((char*)base + div*size, div, size, compar), three_med((char*)base + 2 * div*size, div, size, compar), compar);
		swap(pivot, (char*)base + (num - 1)*size, size);
		pivot = (char*)base + (num - 1)*size;
		//print_int_array(base, num);
		int swappable;
		select_lower(base, num, size, pivot, &swappable, compar);
		//printf("swappable: %d\n", swappable);
		//print_int_array(base, num);
		//sort the other two arrays.
		#pragma omp parallel sections 
		{
			#pragma omp section 
			{
				qsort(base, swappable, size, compar);
			}
			#pragma omp section 
			{
				qsort((char*)base + size*(swappable + 1), num - swappable - 1, size, compar);
			}
		}
	}

}


void select_lower(void* base, size_t num, size_t size, void* pivot, int* swappable, int (*compar)(const void*, const void*))
{

	//printf("pivot: %d\n", *(int*)pivot);
	int i;
	int* scan = (int*) malloc(num * sizeof(int));	
	int* scan_copy = scan;
	#pragma omp parallel for 
	for (i = 0; i < num; ++i)
		scan[i] = ((*compar)((char*)base + size*i, pivot) == -1) ? 1 : 0;
	scan = (int*) genericScan(scan, num, sizeof(int), &addition);

	memcpy(swappable, &scan[num - 1], sizeof(int));
	#pragma omp parallel for num_threads(1)
	for (i = 0; i < num; ++i)
	{
		int comparison = (*compar)((char*)base + size*i, pivot) == -1;
		if (comparison)
		{
			swap((char*)base + (scan[i] - 1)*size, (char*)base + i*size, size);
		}
	}
	swap((char*) base + size*(*swappable), pivot, size);
	free(scan); free(scan_copy);
}


/*
 * base - pointer to first object of array
 * n - number of elements in array pointed to by base
 * l - size of pointers in the array
 * oper - pointer to function that operates on two elements 
 */
void* genericScan(void* base, size_t num, size_t byte_size, void*  (*oper)(void *x1, void* x2)) 
{	
	void* scan = malloc(num * byte_size); 
	if (num == 1) { memcpy(scan, base, byte_size); return scan; }
	bool isOdd = (num % 2 == 1);
	int size = isOdd ? (num / 2 + 1) : (num / 2);
	void* b = malloc(size * byte_size);
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
	free(b);
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


