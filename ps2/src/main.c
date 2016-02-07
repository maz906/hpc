#include "qsort_test.h"
#include "qsort_time.h"
#include "scan_time.h"
#include "scan_test.h"

#include "stdio.h"

int INCREMENT;
int ITERS;

int main(int argv, char** argc) 
{
	if (argv < 4)
	{
		printf("Usage: ./test_qsort [iterations] [max_problem_size] [increment_step]\n");
		return 1;
	}
	INCREMENT = atoi(argc[3]);
	ITERS = atoi(argc[1]);
	//scan_test(atoi(argc[2]));
	//scan_time(atoi(argc[2]));
	//qsort_test(atoi(argc[2]));
	qsort_time(atoi(argc[2]));
	return 0;
}
