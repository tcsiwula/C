/* File:     p4.c
 * Purpose:  Find all primes less than or equal to an input value.
 *           This version doesn't bother checking even ints.
 *
 * Input:    n:  integer >= 2 (from command line)
 * Output:   Sorted list of primes between 2 and n,
 *
 * Compile:  gcc -g -Wall -o p4 p4.c -lm
 * Usage:    ./p4 <n>
 *              n:  max int to test for primality
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <string.h>

//constants
const int MAX_STRING = 100;

//global functions
int Bcast(int users_number, int my_processor_rank, int number_of_processors, MPI_Comm comm);
void Usage(char prog[]);
int Is_prime(int i);

//main function
int main(int argc, char* argv[])
{
    //local variables.
   int current_processor, number_of_processors, my_processor_rank, users_number, result;
   char greeting[MAX_STRING];
   MPI_Comm comm;

	//extract n from user, assign to variable
    users_number = strtol(argv[1], NULL, 10);

  //mpi initialization variables.
  MPI_Init(&argc, &argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &number_of_processors);
  MPI_Comm_rank(comm, &my_processor_rank);


  //for processor zero, only.
  if ( my_processor_rank ==0 )
    {
    	//say hello
    	printf("Greeting from process %d of %d. \n", my_processor_rank, number_of_processors);
        printf("Enter an int\n");
      	scanf("%d", &users_number);
        printf("You would like me to find the primes up to %d. \n", users_number);
    }


    result = Bcast(users_number, my_processor_rank, number_of_processors, comm);
    printf("Hello from processor %d. \n", my_processor_rank ); 

   

   MPI_Finalize();
   return 0;
}  /* main */

/*-------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a brief message explaining how the program is run.
 *            The quit.
 * In arg:    prog:  name of the executable
 */
void Usage(char prog[]) {
   fprintf(stderr, "usage: %s <n>\n", prog);
   fprintf(stderr, "   n = max integer to test for primality\n");
   exit(0);
}  /* Usage */

/*-------------------------------------------------------------------
 * Function:   Is_prime
 * Purpose:    Determine whether the argument is prime
 * Input arg:  i
 * Return val: true (nonzero) if arg is prime, false (zero) otherwise
 */
int Is_prime(int users_number) {
   int limit;

   for (limit = 2; limit <= sqrt(users_number); limit++)
      if (users_number % limit == 0)
         return 0;
   return 1;
}  /* Is_prime */

/*-----------------------------------------------------------------*/
/* Function:    Bcast
 * Purpose:     Broadcast a value from process 0 to all the other
 *              processes
 *
 * Input args:  in_val = the value to be broadcast from process 0
 *              my_rank = process's rank
 *              p = number of processes
 *              comm = communicator
 * Return val:  on each process the value broadcast by process 0
 *
 * Notes:
 *    1.  Uses tree structured communication.
 *    2.  The pairing of the processes is done using bitwise
 *        exclusive or.  Here's a table showing the rule for
 *        for bitwise exclusive or
 *           X Y X^Y
 *           0 0  0
 *           0 1  1
 *           1 0  1
 *           1 1  0
 *        Here's a table showing the process pairing with 8
 *        processes (r = my_rank, other column heads are 
 *        bitmask)
 *           r     001 010 100 
 *           -     --- --- ---
 *           0 000 001 010 100  
 *           1 001 000 011 101
 *           2 010  x  000 110
 *           3 011  x  001 111
 *           4 100  x   x  000
 *           5 101  x   x  001
 *           6 110  x   x  010
 *           7 111  x   x  011
 */
int Bcast(int in_val, int my_rank, int p, MPI_Comm comm) {
   int        partner;
   unsigned   bitmask = 1;
   int        participate = bitmask << 1;

#  ifdef DEBUG
   printf("Proc %d > bitmask = %d\n", my_rank, bitmask);
   fflush(stdout);
#  endif
   while (bitmask < p) {
      if (my_rank < participate) {
         partner = my_rank ^ bitmask;
#        ifdef DEBUG
         printf("Proc %d > bitmask = %d, partner = %d\n",
            my_rank, bitmask, partner);
         fflush(stdout);
#        endif
         if (my_rank < partner) {
            if (partner < p )
               MPI_Send(&in_val, 1, MPI_INT, partner, 0, comm);
         } else {
            MPI_Recv(&in_val, 1, MPI_INT, partner, 0, comm, 
                  MPI_STATUS_IGNORE); 
         }
      }
      bitmask <<= 1;
      participate <<= 1;
   }
   return in_val;

}  /* Bcast */