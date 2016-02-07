#include "qsort.h"
#include "scan.h"
#include "util.h"

#include "assert.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

#include "omp.h"


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
void my_qsort(void* base, int num, int size,
						int (*compar)(const void*, const void*))
{

	//singleton array, so we are done
	if (num > 1)
	{
		if (num <= 20)
		{
			int i; int j;
			int* key = malloc(size);
			for (i = 1; i < num; ++i)
			{
				memcpy(key, (char*)base + i*size, size);
				j = i - 1;
				while (j >= 0 && (*compar)(key, (char*)base + j*size) < 0)
				{
					memcpy((char*)base + (j + 1)*size, (char*)base + j*size, size);
					j--;
				}
<<<<<<< HEAD
				memcpy((char*)base + (j + 1)*size, key, size);
			}
			free(key);
			return;
		}

		int div = num / 3;
		void* med;
		//if large enough, use ninther
		med = median(three_med(base, div, size, compar), three_med((char*)base + div*size, div, size, compar), three_med((char*)base + 2 * div*size, div, size, compar), compar);
		//med = median(base, (char*)base + (num / 2)*size, (char*)base + (num - 1)*size, compar);
		void* pivot = malloc(size);
		//swap so the pivot is last, so we'll know where it is
		swap((char*)base + (num - 1)*size, med, size);
		//make permanent copy so pivot doesn't point to different things 
		memcpy(pivot, (char*)base + (num - 1)*size, size);
		//want to get the index for the partitioning
		int swappable;
		if (num <= 4000)
			partition_seq(base, num, size, pivot, &swappable, compar);
		else /* partition_inplace seems to work best with the above combination */
			partition_inplace(base, num, size, pivot, &swappable, compar);
		swap((char*)base + size*(num - 1), (char*) base + size*(swappable), size);

		//sort the other two arrays. this is to force tail recursion...
		if (swappable < num - 2 * swappable - 2)
		{
			my_qsort(base, swappable, size, compar);
			my_qsort((char*)base + size*(swappable + 1), num - swappable - 1, size, compar);
		}
		else
		{
			my_qsort((char*)base + size*(swappable + 1), num - swappable - 1, size, compar);
			my_qsort(base, swappable, size, compar);
		}
	}
}

/* keep getting write access violations. not sure why... */
void partition_inplace2(void* base, size_t num, size_t size, void* pivot, int* swappable, int(*compar)(const void*, const void*))
{
	int* thread_scan_sums;
	int procs;
#pragma omp parallel
	{
		procs = omp_get_num_threads();
#pragma omp single 
		{
			thread_scan_sums = (int*) calloc((procs + 1), sizeof(int));
		}
		int tid = omp_get_thread_num();
		//smaller chunks of memory better than large ones

		for (int i = tid * (num / procs); i < (tid + 1)*(num / procs); ++i)
			if ((*compar)((char*)base + size*i, pivot) == -1)
			{
				thread_scan_sums[tid]++;
			}

		//idk who else to give the last bit to
#pragma omp single 
		for (int i = procs * (num / procs); i < num; ++i)
			if ((*compar)((char*)base + size*i, pivot) == -1)
			{
				thread_scan_sums[procs]++;
			}
#pragma omp single
			{
				slowScan(thread_scan_sums, procs + 1, sizeof(int), &addition);
				*swappable = thread_scan_sums[procs];
			}
#pragma omp barrier
		int less_than_in_reg = thread_scan_sums[tid];
		int lt_sofar = thread_scan_sums[tid - 1];
		for (int i = tid * (num / procs); i < (tid + 1)*(num / procs); ++i)
			if ((*compar)((char*)base + size*i, pivot) == -1)
			{
				swap((char*)base + (lt_sofar++)*size, (char*)base + i*size, size);
			}
#pragma omp single 
			{
				int less_than_in_reg = thread_scan_sums[procs];
				int lt_sofar = thread_scan_sums[procs - 1];
				for (int i = procs * (num / procs); i < num; ++i)
					if ((*compar)((char*)base + size*i, pivot) == -1)
					{
						swap((char*)base + (lt_sofar++)*size, (char*)base + i*size, size);
					}
			}
	}
}


void partition_inplace(void* base, size_t num, size_t size, void* pivot, int* swappable, int(*compar)(const void*, const void*))
{
	int* thread_scan_sums;
	int procs;
#pragma omp parallel
	{
		procs = omp_get_num_threads();
#pragma omp single 
		{
			thread_scan_sums = (int*) calloc((procs + 1), sizeof(int));
		}
		int tid = omp_get_thread_num();
		//smaller chunks of memory better than large ones

		for (int i = tid * (num / procs); i < (tid + 1)*(num / procs); ++i)
			if ((*compar)((char*)base + size*i, pivot) == -1)
			{
				thread_scan_sums[tid]++;
			}

		//idk who else to give the last bit to
#pragma omp master 
		for (int i = procs * (num / procs); i < num; ++i)
			if ((*compar)((char*)base + size*i, pivot) == -1)
			{
				thread_scan_sums[procs]++;
			}
	}
//wait for all threads to finish copying their data to thread_scan_sums
	slowScan(thread_scan_sums, procs + 1, sizeof(int), &addition);
	int swapp = 0;
	*swappable = thread_scan_sums[procs];
	for (int i = 0; i < num; ++i)
		if ((*compar)((char*)base + size*i, pivot) == -1 && swapp < swappable)
		{
			swap((char*)base + (swapp++)*size, (char*)base + i*size, size);
		}
	free(thread_scan_sums);
}


void partition(void* base, int num, int size, void* pivot, int* swappable, int (*compar)(const void*, const void*))
{
	int i;
	int* scan = (int*) malloc(num * sizeof(int));	
	//#pragma omp parallel for schedule(dynamic) firstprivate(pivot)
	for (i = 0; i < num; ++i)
		scan[i] = ((*compar)((char*) base + size*i, pivot) == -1) ? 1 : 0;
	genericScan(scan, num, sizeof(int), &addition);
	memcpy(swappable, &scan[num - 1], sizeof(int));
	for (i = 0; i < num; ++i)
	{
		if ((*compar)((char*) base + size*i, pivot) == -1)
		{
			swap((char*)base + (scan[i] - 1)*size, (char*)base + i*size, size);
		}

	}
	free(scan);
}

void partition_seq(void* base, int num, int size, void* pivot, int* swappable, int(*compar)(const void*, const void*))
{
	int swapp = 0;
	for (int i = 0; i < num; ++i)
		if ((*compar)((char*)base + size*i, pivot) == -1)
		{
			swap((char*)base + (swapp++)*size, (char*)base + i*size, size);
		}
	*swappable = swapp;
}


