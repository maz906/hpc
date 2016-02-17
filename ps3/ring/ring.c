#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int numtasks, rank, i, j, N, S;
	if (argc == 1)
	{
		N = 0;
	}
	else if (argc == 3 || argc == 5)
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
		if (argc == 5)
		{
		
			switch( (int) argv[3][0])
			{
				case '-':
				case '/':
					switch( (int) argv[3][1])
					{
						case 'S':
						case 's': 
							S = atoi(argv[4]);
					}
			}
		}
		else
		{
			S = 1;
		}
	}
	else
	{
		printf("Usage: %s [-N/n] [iterations] [-S/s] [array_size]\n", argv[0]);
		return 1;
	}
	
	int* sum = calloc(S, sizeof(int));
	double send_end = 0;
	double recv_end = 0;
	double temp;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	MPI_Request req;

	
	for (j = 0; j < N; ++j)
	{
		if (rank == 0)
		{
			MPI_Isend(sum, S, MPI_INT, rank + 1, j, MPI_COMM_WORLD, &req); 
		}
		

		//set up the receives
		temp = MPI_Wtime();
		MPI_Recv(sum, S, MPI_INT, ((rank - 1) % numtasks + numtasks) % numtasks, j, MPI_COMM_WORLD, &status);
		recv_end += MPI_Wtime() - temp; 

		*sum += rank;
		
		temp = MPI_Wtime();
		MPI_Send(sum, S, MPI_INT, (rank + 1) % numtasks, j, MPI_COMM_WORLD);	
		send_end += MPI_Wtime() - temp;

		
	}

	

	printf("rank: %d, avg send time: %f ms\n", rank, 1000*send_end/N);
	printf("rank: %d, avg recv time: %f ms\n", rank, 1000*recv_end/N);


	//print the accumulated sum last
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

	if (rank == 0)
		printf("Accumulated sum: %d\n", *sum);
	return 0;
}
