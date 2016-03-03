/****************************************************************
 *	Grade: 13/100 fail compiling -50%
 *	Commets: 1) Command line test: 0/10
 *           2) Prime test: 0/45
 *           3) Documentation: 10/10
 *           4) Source format: 10/10
 *           5) Quality: 5/25
 *              should use while loop to merge -15
 *              no swapping -5
 ***************************************************************/
// File:     p4.c
//
// Author:	Tim Siwula, tcsiwul@dons.usfca.edu
//
//  Purpose:  Find all primes less than or equal to an input value.
//           This version doesn't bother checking even ints.
//
// Input:    n:  integer >= 2 (from command line)
//
// Output:   Sorted list of primes between 2 and n,
//
// Compile:  mpicc -g -Wall -o p4 p4.c -lm
//
// Usage:    mpiexec -n 4 ./p4 10
//
//             n:  max int to test for primality
//

//libaray imports
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <string.h>

//global function initialization
void Usage(char prog[]);
int Is_prime(int i);
void Merge(int* local_array, int* array_index, int neighbor[], 
    int neighbor[array_index], int** temp_p);

//primes_p = local_array


//main function
int main(int argc, char* argv[])
{
    //local variable initialization
   int number_of_processors, 
   my_processor_rank, 
   users_number,
   i, 
   array_index = 0;
   
  //mpi initialization variables.
  MPI_Init(&argc, &argv);
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &number_of_processors);
  MPI_Comm_rank(comm, &my_processor_rank);

  //array initialization
  int array_storage = users_number / (2*number_of_processors) + 2;
  int* local_array = malloc( array_storage * sizeof(int));
  int* final_list_of_primes = malloc( number_of_processors * sizeof(int));
  
  //for processor zero, only.
  if ( my_processor_rank = 0 )
    {
    	//grab number of primes from stdin
    	users_number = strtol(argv[1], NULL, 10);
 		printf("Hello from processor %d. \n", my_processor_rank );
        printf("2 is prime\n");

        //2 is always prime
        //processor 0 should be hard coded for 2, the only even prime case.
        local_array[0] = 2;

        //increment array index to keep track of length
        array_index++;

        printf("Now broadcasting users_number (%d) to number_of_processors (%d). \n", 
        users_number, number_of_processors);
    }

    //send number of primes from stdin to all other processes
    //all process call bcast to get process 0 to send users_number to it.
    MPI_Bcast(&users_number, 1, MPI_INT, 1, comm);

	//cyclic distribution
	for ( i = 3 + my_processor_rank*2; i <= users_number; i+=2*number_of_processors)
	{
		//pass i to the is prime method for computation.
		if (Is_prime(i))
		{
			//i is prime. add i to local_array.
			local_array[array_index] = i;

			//incrememnt array index to keep track of length.
			array_index++;
		}
	}

	//Phase 1: MPI_Allgather
	//get all data and put into an array for each processor
	//use allgater. send each local_array's index of total primes
	MPI_Allgather(&array_index, 1, MPI_INT, 
		final_list_of_primes, 1, MPI_INT, comm);

	//can now malloc the following since MPI_Allgather
	int sum_of_all_primes = 0;
	for (i =0; i < final_list_of_primes; i++)
	{  
	    sum_of_all_primes = sum_of_all_primes + final_list_of_primes[i];
	}
	
//reference example for storage above working code
//int array_storage = users_number / (2*number_of_processors) + 2;
//int* local_array = malloc( array_storage * sizeof(int));

	//Step 2: Tree communication
	//define and generalize phases
	//phases: even, odd, zero, last
	//actions: send, receive, idle, drop

	//each processor should have a row called start
	//use start to malloc each processors 
	// reccv_array, primes_array, temporary_array
	//malloc 3 arrays
int receive_array_storage = ;
int* recieve_array = malloc( recv_array_storage * sizeof(int));
  
int local_array_storage = ;
int* local_array = malloc( local_array_storage * sizeof(int));

int temp_array_storage = local_array_storage + receive_array_storage; 
int* temp_array = malloc( temp_array_storage * sizeof(int));
  
	int even_processor_array_index = 0, odd_processor_array_index = 0;
	int even_array_storage =  ( (number_of_processors - 2) / 2 + 1);
    int* even_processor_array = malloc( even_array_storage * sizeof(int));
    int odd_array_storage =  ( (number_of_processors - 1) / 2 + 1);
    int* odd_processor_array = malloc( odd_array_storage * sizeof(int));
    
    int remaining_processors = number_of_processors;
    int neighbor_size;
 
	int last_processor = number_of_processors - 1;
	int	first_processor = my_processor_rank;
	

	    //if the number of processors is even
	if( ( number_of_processors % 2 == 0) )
	{
	    //even case
		neighbor_size = total_primes[my_rank - 2]; 
		
		for ( a = number_of_processors; a > 2; a--)
		{
		Merge(
		}
	}	
	else 
	if( ( number_of_processors % 2 == 1) )
	{
	    //even case
		neighbor_size = total_primes[my_rank - 1]; 
		
		for ( j = number_of_processors; j > 2; a--)
		{
		Merge(
		}
	}	
		
    //define phase 1: odd_processors send. even processors receive
    //odd = send | odd_processor >=1 && odd_processor != last_proessor
 
    //odd processors only. exclude last_processor as well.
    if( (my_processor_rank % 2 == 1) && 
        ( my_processor_rank != last_processor ) ) 
    { 
        remaining_processors - 1;
        //send all odds to even neighbors
        for ( odd_processor = 0; odd_processor <= odd_processor_index; 
                odd_processor++) 
        {   
            //define neighbor
            even_neighbor = my_processor_rank - 1;
           
            //send to neighbor aka merge with neighbor   
            //int* i, int i_index, int* neighbor, int neighbor_index        
            Merge( odd_processor_array[odd_processor], 
            array_index,
             even_neighbor[array_index], even_neighbor);
        }
    }

    //define phase 2: even_processors send. odd processors receive
    //even = send | even_processor >=2 && even_processor != last_proessor
    
    //even processors only. exclude both first_process and last_process.
    if( (my_processor_rank % 2 == 1) && 
        ( my_processor_rank != last_processor) &&
        ( my_processor_rank != first_processor) ) 
    { 
        remaining_processors - 1;
        //send all evens to odd neighbors
        for ( even_processor = 0; even_processor <= even_processor_index; 
                 even_processor++)
        {   
            //define neighbor
            odd_neighbor = my_processor_rank - 2;
           
            //send to neighbor aka merge with neighbor           
            Merge( even_processor_array[even_processor], 
            my_processor_rank[array_index],
            odd_neighbor[my_processor_rank],
            odd_neighbor);
        }
    }

//define phase 3
//phase type: last_processor sends to first_processor.
//final_phase = send last_processor | even_processor >=2 &&
// even_processor != last_proessor

if (remaining_processors = 2) //last phase, only two processors left.
{
    //merge last_processor to first_processor
    Merge(last_processor, first_processor);
}

 //debug printing
	for (i =0; i < array_index; i++)
	{
		printf("Processor %d's index %d = %d. Net primes is %d. \n", 
				my_processor_rank, i, local_array[i], array_index );
	}
	//end debug printing

    //return malloc memory
    free(local_array);

    //close mpi
   MPI_Finalize();

   //close c program
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
int Is_prime(int i) 
{
	int j;

   for (j = 2; j <= sqrt( i ); j++)
      if (i % j == 0)
         return 0;
   return 1;
}  /* Is_prime */

//merge function
int Merge(int* i, int i_index, int* neighbor, int neighbor_index)
{
int p, a, j;

//malloc merge_array
//merge_array = my_processor_rank[array_index]
//equivently: i[array_index] + neighbor[array_index]
int merge_array_size = i[array_index] + neighbor[array_index];
int* merge_array = malloc( merge_array_size * sizeof(int));

//add neighbor's primes to merge_array
int merge_array_index = 0;
for (p = 0; p <= neighbor[array_index]; p++)
{
    merge_array[merge_array_index] = neighbor[p];
    merge_array_index++;
}

//add i's primes to merge_array
for (a = 0; a <= i[array_index]; a++)
{
    merge_array[merge_array_index] = i[a];
    merge_array_index++;
}

//re-malloc neighbor[array_index] to neighbor[merge_array_index]
neighbor = malloc( merge_array_index * sizeof( int));

//transfer merge_array into neighbor
for (j = 0; j <= merge_array_index; j++)
{
    neighbor[j] = merge_array[j];
}
}

