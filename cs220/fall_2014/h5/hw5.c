/* 
 * Author: Tim Siwula
 *
 * File:       hw5.c
 *
 * Purpose:    A "hello,world" program that uses MPI
 *
 * Compile:    mpicc -g -Wall -o mpi_hello0 mpi_hello0.c
 * Run:        mpiexec -n<number of processes> ./mpi_hello0
 *
 * Input:      None
 * Output:     A greeting from each process
 *
 * Algorithm:  Each process sends a message to process 0,
 *             which prints the messages it has received,
 *             as well as its own message.
 */
#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */

const int MAX_STRING = 100;

int main(void) {
   char       greeting[MAX_STRING];
   int        my_rank, p, q;
   int dest = (my_rank + 1) % p;
   int source = (my_rank + p - 1) % p;

   /* Start up MPI */
   MPI_Init(NULL, NULL);

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

sprintf(greeting, "Greetings to %d from process %d of %d", 
            dest, my_ranky p);

   if (p > 1) {
      MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, dest, 0,
            MPI_COMM_WORLD);
         MPI_Recv(greeting, MAX_STRING, MPI_CHAR, source, 
            0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         printf("Proc %d > %s\n", my_rank, greeting);
      } 
   
   /* Shut down MPI */
   MPI_Finalize();
   return 0;
}  /* main */