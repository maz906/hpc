#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int numtasks, rank, i, j, N, sum = 0;
	if (argc == 1) {
		N = 0;
	}
	else if (argc == 3)
	{
		switch( (int) argv[1][0])
		{
			case '-':
			case '/':
				switch( (int) argv[1][1])
				{
					case 'N':
					case 'n': 
						N = atoi(argv[2]);
				}
		}
	} 
	else
	{
		printf("Usage: %s [-N/n] [iterations]\n", argv[0]);
		return 1;
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Request reqs;
	
	for (j = 0; j < N; ++j)
	{
		//set up the receives
		for (i = 0; i < numtasks; ++i)
		{
			if (rank == i)
			{
				//should not be Irecv
				MPI_Irecv(&sum, 1, MPI_INT, ((i - 1) % numtasks + numtasks) % numtasks, 1, MPI_COMM_WORLD, &reqs);
			}
		}
		
		//increment and send
		for (i = 0; i < numtasks - 1; ++i)
		{
			if (rank == i)
			{
				sum += rank;
				MPI_Isend(&sum, 1, MPI_INT, (i + 1) % numtasks, 1, MPI_COMM_WORLD, &reqs);	
			}
		}
	}

	MPI_Finalize();

	printf("Accumulated sum: %e\n", sum);
	return 0;
}
