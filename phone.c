// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header in tact.
//
// Example using MPI_Send and MPI_Recv to pass a message around in a ring.
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
 
 
//  int k;
//  scanf('%d',&k);
  int n = 0;
  char token[20];
  // Receive from the lower process and send to the higher process. Take care
  // of the special case when you are the first process to prevent deadlock.
if(world_rank != (world_size-1)){
  if (world_rank != 0) {
    MPI_Recv(token, 20, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received token %s from process %d\n", world_rank, token,
           world_rank - 1);
  } else {
    // Set the token's value if you are process 0
  do{
  	scanf("%c",&token[n]);
	n++;
  } while(token[n-1] != '\n');
  }
  MPI_Send(token, 20, MPI_BYTE, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD);
} else{
	MPI_Recv(token, 20, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD,
		MPI_STATUS_IGNORE);
	printf("Process %d received token %s from process %d\n", world_rank, token,
		world_rank - 1);
}
  MPI_Finalize();
}
