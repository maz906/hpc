#include "scan.h"
#include "scan_time.h"
#include "util.h"

#include "time.h"

#include "omp.h"

extern int INCREMENT;

void scan_time(int size)
{
	scale_scan_time(size, 24, 20);
	basic_scan_time(size, INCREMENT, 20);
}

void scale_scan_time(int size, int procs, int times)
{
	for (int i = 1; i < procs; i *= 2)
	{
		printf("Number of threads: %d\n", i);
		omp_set_num_threads(i);
		basic_scan_time(size, size, times);
	}
}

void basic_scan_time(int size, int increment, int times) 
{
	
	int i, j;
	int* rand_int; double* rand_double; float* rand_float; long* rand_long; Point* rand_point; Vector* rand_vec;
	double int_time = 0, double_time = 0, float_time = 0, long_time = 0, point_time = 0, vec_time = 0;
	double int_time_single, double_time_single, long_time_single, point_time_single, float_time_single, vec_time_single;
	for (j = increment; j <= size; j += increment)
	{
		for (i = 0; i < times; ++i)
		{
			rand_int = random_int_array(j);
			rand_double = random_double_array(j);
			rand_float = random_float_array(j);
			rand_long = random_long_array(j);
			rand_point = random_point_array(j);
			rand_vec = random_vec_array(j);

			int_time_single = time_scan_array(rand_int, j, sizeof(int), &addition);
			double_time_single = time_scan_array(rand_double, j, sizeof(double), &add_doub);
			float_time_single = time_scan_array(rand_float, j, sizeof(float), &add_float);
			long_time_single = time_scan_array(rand_long, j, sizeof(long), &add_long);
			point_time_single = time_scan_array(rand_point, j, sizeof(Point), &add_point);
			vec_time_single = time_scan_array(rand_vec, j, sizeof(Point), &add_vec);

			int_time += int_time_single;
			double_time += double_time_single;
			long_time += long_time_single;
			float_time += float_time_single;
			point_time += point_time_single;
			vec_time += vec_time_single;

		}
		printf("(int) array_size: %d, scan_time (s): %g\n", j, int_time/times);
		printf("(double) array_size: %d, scan_time (s): %g\n", j, double_time/times);
		printf("(float) array_size: %d, scan_time (s): %g\n", j, float_time/times);
		printf("(long) array_size: %d, scan_time (s): %g\n", j, long_time/times);
		printf("(point) array_size: %d, scan_time (s): %g\n", j, point_time/times);
		printf("(vector) array_size: %d, scan_time (s): %g\n", j, vec_time/times);
		printf("\n");
		int_time = double_time = float_time = long_time = point_time = 0;
	}
}

double time_scan_array(void* arri_1, size_t num, size_t size, void*(*oper) (const void*, const void*)) 
{
	double difference;	
	double start = omp_get_wtime();
	genericScan(arri_1, num, size, oper);
	difference = omp_get_wtime() - start;	
	free(arri_1);
	return difference;
}
