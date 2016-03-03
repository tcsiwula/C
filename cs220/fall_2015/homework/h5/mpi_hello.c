/* File:       mpi_hello.c
 *
 * Purpose:    A "hello,world" program that uses MPI
 *
 * Compile:    mpicc -g -Wall -o mpi_hello mpi_hello.c
 * Run:        mpiexec -n<number of processes> mpi_hello
 *
 * Input:      None
 * Output:     A greeting from each process
 *
 * Algorithm:  Each process sends a message to process 0,
 *             which prints the messages it has received,
 *             as well as its own message.
 */
// Modify the MPI "hello" program so that instead of having each process send its message to process 0, each process sends its message to the next higher ranked process, with process p-1 sending to process 0. When a process receives a message, it prints the message and calls MPI_Finalize. Note that the penguin cluster doesn't allow a process to send a message to itself. So you'll need to treat the case p = 1 separately: just have process 0 print out a message and quit.


// for q, send to q + 1. if q = p-1, send to 0, if q = 1, send to 0
//  recv, print, finalize


#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */

const int MAX_STRING = 100;

int main(void)
{
   char       greeting[MAX_STRING];
   int        my_rank, p, dest, source;

   /* Start up MPI */
   MPI_Init(NULL, NULL);

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   if (p == 1)
   {
      printf("Greetings from process %d of %d\n", my_rank, p);
   }
   else if (p > 1)
   {
      if(my_rank == 0)
      {
        dest = 1;
        source = my_rank+1;
        printf("Greetings from process %d of %d\n", my_rank, p);
      	MPI_Recv(greeting, MAX_STRING, MPI_CHAR, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("%s\n", greeting); 
     }
     	else
      {
        dest = my_rank -1;
        source = my_rank+1;
        sprintf(greeting, "Greetings from process %d of %d \n", my_rank, p);
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
	
	if(my_rank < p-1)
	{
		MPI_Recv(greeting, MAX_STRING, MPI_CHAR, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%s\n", greeting);
	}
	}	
   }

   /* Shut down MPI */
   MPI_Finalize();
   return 0;
}  /* main */

