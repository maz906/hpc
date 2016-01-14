#include "qsort.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

/*
 * base - pointer to the first object of the array to be sorted
 * num - number of elements in the array pointed to by base
 * size - size in bytes of each element of the array
 * compar - pointer to function that compares two elements  
 */
void qsort(void* base, size_t num, size_t size,
						int (*compar)(const void*, const void*))
{

	//singleton array, so we are done
	if (num <= 1) return;	
	
	//pivot
	void* pivot = base + size*(num - 1);

	//partition the array
	size_t swappable = 0;

	for (size_t i = 0; i < num; ++i)
	{
		if (compar(base + size*i, pivot) < 0) 
		{
			//if smaller than pivot, switch i with wherever the most recent larger than element is
			swap(base + size*(swappable++), base + size*i, size);
		}
	}

	//put the pivot in the right place	
	swap(pivot, base + size*(swappable), size);

	//sort the other two arrays.
	qsort(base, swappable, size, compar);
	qsort(base + size*(swappable + 1), num - swappable - 1, size, compar);
}

void swap(void* source, void* dest, size_t size) 
{
	void* temp = calloc(1, size);
	memcpy(temp, source, size);
	memcpy(source, dest, size);
	memcpy(dest, temp, size);
}
