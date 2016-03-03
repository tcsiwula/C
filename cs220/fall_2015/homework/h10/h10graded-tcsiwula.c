/*
Run-time for cluster node   1   /   1
Run-time for lab machine    1   /   1
 include semaphore.h    1   /   1
Global def of *one* semaphore   1   /   1
Delete def of mutex 1   /   1
Include call to sem_init:  Last arg to sem_init must be 1   1   /   1
Delete call to pthread_mutex_init   1   /   1
Include call to sem_destroy     1   /   1
Delete call to pthread_mutex_destroy    1   /   1
Include call to sem_wait    1   /   1
Delete call to pthread_mutex_lock   1   /   1
Include call to sem_post    1   /   1
Delete call to pthread_mutex_unlock 1   /   1
            
Total   13  /   13
*/

/* File:     h10.c Tim Swiula
 *
 * Purpose:  Lock and unlock a mutex many times, and report on elapsed time
 *
 * Compile:  gcc -g -Wall -o h10 h10.c -lpthread
 * Run:      ./h10 <thread_count> <n>
 *              n:  number of times the mutex is locked and unlocked
 *                  by each thread
 *
 * Input:    none
 * Output:   Total number of times mutex was locked and elapsed time for
 *           the threads
 */


 /*
    Performance Results:

    SEMAPHORES: Fastest
    Penguin cluster:          #1 Elapsed time = 3.795835e+00 seconds
                              #2 Elapsed time = 3.907970e+00 seconds
                              #3 Elapsed time = 3.983516e+00 seconds

    MUTEXES: Second Fastest
    Penguin cluster:          #1 Elapsed time = 9.011760e-01 seconds
                              #2 Elapsed time = 7.851551e-01 seconds
                              #3 Elapsed time = 7.570360e-01 seconds


    SEMAPHORES: Fourth fastest
    G1227:                    #1 Elapsed time = 1.389312e+00 seconds
                              #2 Elapsed time = 1.396292e+00 seconds
                              #3 Elapsed time = 1.374954e+00 seconds

    MUTEXES: Third fastest
    G1227:                    #1 Elapsed time = 1.169187e+00 seconds
                              #2 Elapsed time = 1.098740e+00 seconds
                              #3 Elapsed time = 1.222717e+00 seconds

 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "timer.h"

int thread_count;
int n;
int total = 0;
sem_t my_semaphore;

void Usage(char prog_name[]);
void* Lock_and_unlock(void* rank);

int main(int argc, char* argv[]) {
   pthread_t* thread_handles;
   long thread;
   double start, finish;

   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   n = strtol(argv[2], NULL, 10);

   thread_handles = malloc(thread_count*sizeof(pthread_t));
   sem_init(&my_semaphore, 0, 1);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL, Lock_and_unlock,
            (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);
   GET_TIME(finish);

   printf("Total number of times my_semaphore was locked and unlocked: %d\n",
         total);
   printf("Elapsed time = %e seconds\n", finish-start);

   sem_destroy(&my_semaphore);

   free(thread_handles);
   return 0;
}  /* main */

/*---------------------------------------------------------------------
 * Function:   Usage
 * Purpose:    Print a message explaining how to start the program.
 *             Then quit.
 * In arg:     prog_name:  name of program from command line
 */
void Usage(char prog_name[]) {
   fprintf(stderr, "usage: %s <thread_count> <n>\n", prog_name);
   fprintf(stderr, "    n: number of times my_semaphore is locked and ");
   fprintf(stderr, "unlocked by each thread\n");
   exit(0);
}  /* Usage */


/*---------------------------------------------------------------------
 * Function:   Lock_and_unlock
 * Purpose:    Repeatedly lock and unlock a mutex to determine performance
 *             of mutexes
 * In arg:     rank:  thread rank
 * In globals: thread_count:  number of threads
 *             n:  number of times each thread should lock and unlock mutex
 *             mutex:
 * In/out global:  total:  total number of times mutex is locked and unlocked.
 */
void* Lock_and_unlock(void* rank)
{
   long my_rank = (long) rank;  /* unused */
   int i;

   for (i = 0; i < n; i++)
   {
      sem_wait(&my_semaphore);
      total++;
      sem_post(&my_semaphore);
   }
   return NULL;
}  /* Lock_and_unlock */
