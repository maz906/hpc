#include "qsort.h"
#include "scan.h"
#include "util.h"

#include "assert.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

#include "omp.h"


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
		if (num <= 10)
		{
			int i; int j;
			int* key = malloc(sizeof(int));
			for (i = 1; i < num; ++i)
			{
				memcpy(key, (char*)base + i*size, size);
				j = i - 1;
				while (j >= 0 && (*compar)((char*)base + j*size, key) >= 0)
				{
					memcpy((char*)base + (j + 1)*size, (char*)base + j*size, size);
					j--;
				}
				memcpy((char*)base + (j + 1)*size, key, size);
			}
			return;
		}

		//pivot
		int div = num / 3;
		void* med;
		//if large enough, use ninther
		if (num > 9)
			med = median(three_med(base, div, size, compar), three_med((char*)base + div*size, div, size, compar), three_med((char*)base + 2 * div*size, div, size, compar), compar);
		else //use median of three
			med = median(base, (char*)base + (num / 2)*size, (char*)base + (num - 1)*size, compar);
		void* pivot = malloc(size);
		//swap so the pivot is last, so we'll know where it is
		swap((char*)base + (num - 1)*size, med, size);
		//make permanent copy so pivot doesn't point to different things 
		memcpy(pivot, (char*)base + (num - 1)*size, size);
		//want to get the index for the partitioning
		int swappable;
		select_lower(base, num, size, pivot, &swappable, compar);
		swap((char*)base + size*(num - 1), (char*) base + size*(swappable), size);

		//sort the other two arrays.
		my_qsort(base, swappable, size, compar);
		my_qsort((char*)base + size*(swappable + 1), num - swappable - 1, size, compar);
//#pragma omp parallel sections 
//		{
//#pragma omp section 
//		{
//			my_qsort(base, swappable, size, compar);
//		}
//#pragma omp section 
//		{
//			my_qsort((char*)base + size*(swappable + 1), num - swappable - 1, size, compar);
//		}
//		}
	}
}

//void select_lower_inplace(void* base, size_t num, size_t size, void* pivot, int* swappable, int(*compar)(const void*, const void*))
//{
//	int procs = omp_get_num_threads;
//	int* thread_scan_sums = malloc(procs * sizeof(int));
//#pragma omp parallel
//{
//	int tid = omp_get_thread_num();
//	//smaller chunks of memory better than large ones
//	int* indicator = malloc( (num/procs) * sizeof(int));
//#pragma omp for
//	for (int i = tid * (num / procs); i < (tid + 1)*(num / procs); ++i)
//		indicator[i] = ((*compar)((char*) base + size*i, pivot) == -1) ? 1 : 0;

//	//idk who else to give the last bit to
//#pragma omp master 
//	for (int i = procs * (num / procs); i < num; ++i)
//		indicator[i] = ((*compar)((char*) base + size*i, pivot) == -1) ? 1 : 0;

//	int* scanned = (int*)slowScan(indicator, 0, num/procs , size, &addition);
//	memcpy((char*)thread_scan_sums + tid*sizeof(int), scanned[num / procs - 1], sizeof(int));

////wait for all threads to finish copying their data to thread_scan_sums
//#pragma omp barrier
//#pragma omp single
//	int* thread_scan_sums = slowScan(thread_scan_sums, 0, procs, sizeof(int), &addition);
//#pragma omp for
//	int adjustment = thread_scan_sums[tid]; //this adjustment may be off. needs to be zero in front.
//	for (int i = tid * (num/procs); i < (tid + 1) * (num/procs); ++i)
//	{
//		if (indicator[i])
//		{
//			swap((char*)base + (scanned[i] - 1 + adjustment)*size, (char*)base + i*size, size);
//		}
//	}

//#pragma omp master
//	int adjustment = thread_scan_sums[procs - 1]; //this adjustment may be off. needs to be zero in front.
//	for (int i = procs * (num/procs); i < num; ++i)
//	{
//		if (indicator[i])
//		{
//			swap((char*)base + (scanned[i] - 1 + adjustment)*size, (char*)base + i*size, size);
//		}
//	}
//}
//}


void select_lower(void* base, int num, int size, void* pivot, int* swappable, int (*compar)(const void*, const void*))
{
	int i;
	int* scan = (int*) malloc(num * sizeof(int));	
	#pragma omp parallel for
	for (i = 0; i < num; ++i)
		scan[i] = ((*compar)((char*) base + size*i, pivot) == -1) ? 1 : 0;
	slowScan(scan, num, sizeof(int), &addition);
	memcpy(swappable, &scan[num - 1], sizeof(int));
	#pragma omp parallel for num_threads(1)
	for (i = 0; i < num; ++i)
	{
		if ((*compar)((char*) base + size*i, pivot) == -1)
		{
			swap((char*)base + (scan[i] - 1)*size, (char*)base + i*size, size);
		}

	}
	free(scan);
}



