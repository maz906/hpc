#include "qsort.h"
#include "stddef.h"

int main(int argc, char** argv) 
{

}

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
	if (num <= 1)
		return;	
	
	//pivot
	void* pivot = base + (num - 1);

	//partition the array
	size_t left_array = 0;
	size_t right_array = 0;

	for (size_t i = 0; i < num; ++i)
	{
		if (compar(base + i, pivot) > 0)
		{
			right_array++;
		}
		else if (compar(base + i, pivot) < 0) 
		{
			left_array++;		
			swap(base + i, base + right_array);
		}
	}

	//put the pivot in the right place	
	swap(pivot, base + right_array + 1);
	qsort(base, num/2, size, compar);
	qsort(base + num/2, num/2, size, compar);
}

void swap(void* source, void* dest) 
{
	void* temp = source;
	source = dest;
	dest = temp;
}
