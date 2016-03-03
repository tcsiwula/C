/* File:     mpi_wtime.c
 * Purpose:  Illustrate the use of the MPI_Wtime function for timing.
 *
 * Compile:  mpicc -g -Wall -o mpi_wtime mpi_wtime.c
 * Run:      mpiexec -n 1 ./mpi_wtime <number of iterations in for loop>
 *
 * Note:     Only run this with one process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
   double start, finish;
   long i, n;
   double elapsed;
   double x = 0;
   int pm = 1;

   MPI_Init(&argc, &argv);

   if (argc != 2) {
      fprintf(stderr, "usage:  %s <n>\n", argv[0]);
      exit(0);
   }
   n = strtol(argv[1], NULL, 10);

   start = MPI_Wtime();
   for (i = 0; i < n; i++, pm = -pm) 
      x += pm*exp(sin((double) i));
   finish = MPI_Wtime();

   elapsed = finish - start;
   printf("Elapsed time = %.14e seconds\n", elapsed);
   printf("Resolution of MPI_Wtime = %.14e seconds\n", MPI_Wtick());
   
   MPI_Finalize();

   return 0;
}
