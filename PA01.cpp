#include<iostream>
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
	float sTime, eTime;
	MPI_Status status;

	//initialize MPI
	
	if (MPI_Init(NULL, NULL) != MPI_SUCCESS)
	{
       		cout<<"MPI initialization error"<<endl;
        	exit(1);
   	}

	//get rank

	MPI_COMM_rank(MPI_COMM_WORLD, &mrank);
	nxtRank = (mrank + 1) % 2;

	pingCount = 0;

	while(pingCount < limit)
	{
		if(mrank == pingCount%2)
		{
			pingCount += 1;
			sTime = MPI_Wtime(); //start time

			MPI_Send(&pingCount, 1, MPI::INT, nxtRank, mtag, MPI_COMM_WORLD);
			MPI_Recv(&pingCount, 1, MPI::INT, mrank, mtag, MPI_COMM_WORLD, &status);

			cout<<"Sent::: A rank: "<<mrank<<", to B rank: "<<nxtRank<<", Data Sent :" <<pingCount<<endl;
		}
		else
		{
			MPI_Recv(&pingCount, 1, MPI::INT, mrank, mtag, MPI_COMM_WORLD, &status);
			MPI_Send(&pingCount, 1, MPI::INT, mrank, mtag, MPI_COMM_WORLD);

			cout<<"Received::: B rank: "<<nxtRank<<", from A rank: "<<mrank<<", Data Sent :" <<pingCount<<endl;
		
		}
		
		eTime = MPI_Wtime(); //end time
		cout<<"PROCESS "<<pingCount<<" Time : "<< eTime - sTime <<endl;

	}
	
	//finalize MPI

	MPI::Finalize();

	return 0;
}
