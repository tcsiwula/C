/* File:  
 *    hw_11.c
 *      Author: Tim Siwula
 * Purpose:
 *    Generate random numbers with function that isn't threadsafe.
 *
 * Compile:
 *    gcc -g -Wall -o hw_11 hw_11.c -lpthread
 * Usage:
 *    ./hw_11 <thread_count> <number of random numbers per thread>
 *
 * Input:
 *    None
 * Output:
 *    Random numbers from each thread
 *
 * Warning:
 *    Tim Siwula is godsend and made this program thread safe.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
//#include <semaphore.h>


#define MR_MULTIPLIER 279470273 
#define MR_INCREMENT 0
#define MR_MODULUS 4294967291U

int thread_count;
int n;


void Usage(char* prog_name);

unsigned My_random(unsigned seed);

void *Thread_work(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long        thread;
   pthread_t* thread_handles; 

   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   n = strtol(argv[2], NULL, 10);

   thread_handles = malloc(thread_count*sizeof(pthread_t));

   printf("Enter text\n");
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
          Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL);

   free(thread_handles);
   return 0;
}  /* main */


/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <thread count> <number of random vals per thread>\n", 
         prog_name);
   exit(0);
}  /* Usage */


/*-------------------------------------------------------------------
 * Function:    Thread_work
 * Purpose:     Each thread calls a function and prints a message
 * In arg:      rank
 * Global vars: thread_count (in) 
 * Return val:  Ignored
 */
void *Thread_work(void* rank) 
{
    long my_rank = (long) rank;
    int i;
    int seed = 0;

 
   My_random(seed);  /* "Seed" Random number generator */
  
   for (i = 0; i < n; i++) 
   {

    printf("Th %ld > %u\n", my_rank, My_random(0));
    seed = my_rank+1;
}
   return NULL;
}  /* Thread_work */


/*-------------------------------------------------------------------
 * Function:    My_random
 * Purpose:     Generate random numbers
 * In arg:      seed  (ignored if = 0)
 * Ret val:     A "random" unsigned int
 *
 * Note:        The first time the function is called, the random
 *              number should be "seeded" with a nonzero argument,
 *              and the return value ignored.  Subsequent calls 
 *              should have a zero argument and the return values
 *              will form a "pseudo-random" sequence.
 */
unsigned My_random(unsigned seed) 
{
    //unsigned int seed;
    unsigned long storage;
   
   //seed
   //if (seed != 0) random_number = seed;
   
   //compute
   storage = seed*MR_MULTIPLIER; 
   seed = storage % MR_MODULUS;
   

   return seed;
}  /* My_random */
