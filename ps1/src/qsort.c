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

	//partition the array
	size_t swappable = 0, i;
	for (i = 0; i < num; ++i)
	{
		if ((*compar)((char*)base + size*i, pivot) < 0) 
		{
			//if smaller than pivot, switch i with wherever the most recent larger than element is
			swap((char*)base + size*(swappable++), (char*)base + size*i, size);
		}
	}

	//put the pivot in the right place	
	swap(pivot, (char*)base + size*(swappable), size);

	//sort the other two arrays.
	qsort(base, swappable, size, compar);
	qsort((char*)base + size*(swappable + 1), num - swappable - 1, size, compar);
}

