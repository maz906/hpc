#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int numtasks, rank, i, j, N, sum = 0;
	if (argc == 1)
	{
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
	MPI_Status status;
	MPI_Request req;
	
	for (j = 0; j < N; ++j)
	{
		if (rank == 0)
		{
			MPI_Isend(&sum, 1, MPI_INT, rank + 1, j, MPI_COMM_WORLD, &req); 
		}
		

		//set up the receives
		MPI_Recv(&sum, 1, MPI_INT, ((rank - 1) % numtasks + numtasks) % numtasks, j, MPI_COMM_WORLD, &status);
		sum += rank;
		MPI_Send(&sum, 1, MPI_INT, (rank + 1) % numtasks, j, MPI_COMM_WORLD);	

		
	}

	MPI_Finalize();

	if (rank == 0)
		printf("Accumulated sum: %d\n", sum);
	return 0;
}
