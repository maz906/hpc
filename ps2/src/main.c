#include "qsort_test.h"
#include "scan_time.h"
#include "scan_test.h"

#include "stdio.h"

int INCREMENT;

int main(int argv, char** argc) 
{
	if (argv < 4)
	{
		printf("Usage: ./test_qsort [iterations] [max_problem_size] [increment_step]\n");
		return 1;
	}
	INCREMENT = atoi(argc[3]);
	scan_test(atoi(argc[2]));
	//scan_time(atoi(argc[2]));
	//basic_test(atoi(argc[1]), atoi(argc[2]), atoi(argc[3]));
	return 0;
}
