#include<stdio.h>
#include "mpi.h"
#include <stdlib.h>

using namespace std;
int main(int argc, char** argv)
{	
	int mrank;
	int nxtRank;
	int mtag;
	int pingCount;
	int limit = 10;
	int size;
	float sTime, eTime, totTime;
	MPI_Status status;

	//initialize MPI
	printf("init \n");
	if (MPI_Init(NULL, NULL) != MPI_SUCCESS)
	{
		printf("MPI initialization error \n");
        	exit(1);
   	}

	//get rank
	printf("rank \n");
	MPI_Comm_rank(MPI_COMM_WORLD, &mrank);
	nxtRank = (mrank + 1) % 2;
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	pingCount = 0;

	//while(pingCount < limit)
	//{
	printf("why am I sucking? \n");
		if(mrank == 0)
		{
			pingCount += 1;
			sTime = MPI_Wtime(); //start time

			MPI_Send(&pingCount, 1, MPI_INT, nxtRank, mtag, MPI_COMM_WORLD);
			MPI_Recv(&pingCount, 1, MPI_INT, mrank, mtag, MPI_COMM_WORLD, &status);
		}
		else
		{
			MPI_Recv(&pingCount, 1, MPI_INT, mrank, mtag, MPI_COMM_WORLD, &status);
			MPI_Send(&pingCount, 1, MPI_INT, mrank, mtag, MPI_COMM_WORLD);
		}
		
		eTime = MPI_Wtime(); //end time
		totTime = eTime - sTime;
	printf("why am I sucking? again \n");
		printf("Sent::: A rank: %d: Received %d  from %d\n",
      					 mrank, pingCount, status.MPI_SOURCE);
		printf("PROCESS %d: Time: %f \n", pingCount, totTime);
		

	//}
	
	//finalize MPI

	MPI_Finalize();

	return 0;
}
