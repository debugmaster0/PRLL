#include<iostream>
#include "mpi.h"
#include <stdio.h>

using namespace std;
int main(int argc, char** argv)
{	
	int mrank, nxtRank, mtag, pingCount;
	int limit = 10;
	float sTime, eTime;
	MPI::Status status;

	//initialize MPI
	
	if (MPI_Init(NULL, NULL) != MPI_SUCCESS)
	{
       		cout<<"MPI initialization error"<<endl;
        	return exit(1);
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

			cout<<"Sent::: A rank: "<<mrank<<", to B rank: "<<nxtRank<<", Data Sent :" <<pingcount<<endl;
		}
		else
		{
			MPI_Recv(&pingCount, 1, MPI::INT, nxtRank, mtag, MPI_COMM_WORLD, &status);

			cout<<"Received::: B rank: "<<nxtRank<<", from A rank: "<<mRank<<", Data Sent :" <<pingcount<<endl;
		
		}
		
		eTime = MPI_Wtime(); //end time
		cout<<"PROCESS "<<pingCount<<" Time : "<< eTime - sTime <<endl;

	}
	
	//finalize MPI

	MPI::Finalize();

	return 0;
}