#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int numtasks, rank, i;
	int sum;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		for (i = 0; i < numtasks; ++i)
		{
			MPI_Irecv(&sum, 	

		}
	}



}
