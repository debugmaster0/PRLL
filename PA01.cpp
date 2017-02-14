#include<iostream>
#include "mpi.h"

int main()
{	
	int mrank, nxtRank, mtag, pingCount, commSize;
	int arraySize = 10;
	float sTime, eTime;
	MPI::Status status;

	//initialize MPI
	
	if (MPI_Init() != MPI_SUCCESS)
	{
       		std::cout<<"MPI initialization error"<<endl;
        	return exit(1);
   	}

	//get rank

	mrank = MPI::COMM_WORLD.Get_rank();
	nxtRank = mrank + 1;

	//get size
	
	commSize = MPI::COMM_WORLD.Get_Size();

	pingCount = 0;

	while(pingCount < arraySize)
	{
		if(mrank == 0)
		{
			sTime = MPI_Wtime(); //start time
			pingCount += 1;

			MPI_Send(&pingCount, 1, MPI::INT, nxtRank, mtag, MPI_COMM_WORLD);

			MPI_Recv(&pingCount, 1, MPI::INT, nxtRank, mtag, MPI_COMM_WORLD, &status);

			std::cout<<"Sent::: A rank: "<<mrank<<", to B rank: "<<nxtRank<<", Data Sent :" <<pingcount<<endl;
		}
		else
		{
			MPI_Recv(&pingCount, 1, MPI::INT, mrank, mtag, MPI_COMM_WORLD, &status);

			MPI_Send(&pingCount, 1, MPI::INT, mrank, mtag, MPI_COMM_WORLD);

			std::cout<<"Received::: B rank: "<<nxtRank<<", from A rank: "<<mRank<<", Data Sent :" <<pingcount<<endl;
		
		}
		
		eTime = MPI_Wtime(); //end time
		std::cout<<"PROCESS "<<pingCount<<" Time : "<< eTime - sTime <<endl;

	}
	
	//finalize MPI

	MPI::Finalize();

	return 0;
}
