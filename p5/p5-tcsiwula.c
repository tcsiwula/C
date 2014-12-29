/****************************************************************
 *	Grade: 73/100
 *	Commets: 1) Command line: 8/10
 *              random should be mod by 1,000,000 -2
 *           2) DEBUG info: 9/9
 *           3) Sorting: 26/26
 *           4) Parralel sort: 0/20
 *           5) Documentation: 10/10
 *           6) Source format: 10/10
 *           7) Quality: 10/15
 *              wrong list swap -5
 ***************************************************************/
// File:                 getinput.c
//
// Author:        %% Tim Siwula %% tcsiwula@dons.usfca.edu %% http://itimmy.com
//
// Purpose:                                    Bitnoic sort algrothim, parallel
//
// Compile:                   gcc -g -Wall -O0 -o clean clean.c -lpthread
//
// Run:                               ./clean <#threads> <#elements> [g] [o]
// Run with 4 threads, 8 random numbers:  ./clean 4 8 g o
// g =                      generate numbers
//
// o =                      print list before
//
// Input:                   Optional numbers if [g] not included in run command.
//
// Output:                                               Sorted list of numbers.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "timer.h"
#include <math.h>
#define DEBUG

//#######BEGIN global functions#######

//get input functions
void Get_input(int argc, char* argv[], int* maxthreads_p, int* elements_p,
								char* make_numbers_p, char* print_before_p);
void Read_list(int array[], int elements);
void Print_list(int array[], int elements, char* title);
void Start_arrays();
void Error(char* prog_name);
unsigned Random_number();

//pthread functions
void* Parallel_bitonic_sort( int thread );
void Update_phase(int thread);
unsigned Get_partner(unsigned partnermask, unsigned swapmask,
						int thread, int partner, int work, int partnerindex);
unsigned Get_slope(unsigned slopemask, int thread, int partner, int slope);
void Sync(int thread);


//qsort functions
void Local_sort(int thread, int start, int work);
int Compare(const void* array_pointer_threadindex,
 							const void* array_pointer_partnerindex);

//swap functions
void Update(int* temp_pointer, int* neighbor_pointer );
void Swap( int threadindex, int partnerindex, int work,
				int slope, int thread, int partner, int start, int end);
void Print_debug(int thread, int phase, int elements );


//#######END global functions#######

//#######BEGIN global variables#######

//get input variables
int elements;
char make_numbers, print_before;
int print_arg = 0, make_numbers_arg = 0;

//array pointers
int* array;
int* temp;
int* storage1;
int* storage2;
int* print_list;

//phase variables
int max_phases, phase = 1;

//swap variables
int swapsperphase, swaps = 0;

//pthread variables
int barrier_thread_count = 0, maxthreads;

//mutex variables
pthread_mutex_t barrier_mutex;
pthread_cond_t ok_to_proceed;

//#######END global variables#######

/*-------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
//local variables
long       thread;
pthread_t* thread_handles;
double start, finish;
	//step 1 = declare input
	Get_input( argc, argv, &maxthreads, &elements,
				&make_numbers, &print_before );
	//step2 = initialize input
	array = (int*) malloc( elements*sizeof(int) );
	temp = (int*) malloc( elements*sizeof(int) );
	storage1 = (int*) malloc( elements*sizeof(int) );
	storage2 = (int*) malloc( elements*sizeof(int) );

	Start_arrays();
	//step 4 = print list before sort
	if (print_arg  == 1 )
	{
		Print_list(array, elements, "Before sort (array)");
		//Print_list(temp, elements, "Before sort (temp)");
	}
	//step 5 = start timers
	GET_TIME(start);
	thread_handles = malloc( maxthreads*sizeof( pthread_t ));
	pthread_mutex_init(&barrier_mutex, NULL);
	pthread_cond_init(&ok_to_proceed, NULL);
	for (thread = 0; thread < maxthreads; thread++)
	pthread_create(&thread_handles[thread], NULL,
	 					Parallel_bitonic_sort, (void*) thread);
	for (thread = 0; thread < maxthreads; thread++)
	pthread_join(thread_handles[thread], NULL);
	GET_TIME(finish);
	printf("\nElapsed time = %e seconds\n", finish - start);
	//step 5 results
	//step 8 = free memory
	pthread_mutex_destroy(&barrier_mutex);
	pthread_cond_destroy(&ok_to_proceed);
	free(thread_handles);
	free(array);
	free(temp);
	return(0);
	}

	/*-------------------------------------------------------------------
	* Function:    Parallel_bitonic_sort
	* Purpose:     Each thread calls this to work on the sorting.
	* In args:     thread
	* In/out args: sorted array[]
	*/
	void* Parallel_bitonic_sort( thread)
	{
	//BEGIN local variables for each thread.
		int partner =0, slope;
		unsigned slopemask = 2, partnermask = 1, phasemask = 1, swapmask = 1;
		int work = elements/maxthreads;
		int start = thread * work;
		int end = (thread + 1) * work;

		int partnerindex;
		int threadindex = thread * work;
	//END local variables for each thread.

	//BEGIN global variables for each thread.
		max_phases = log2(maxthreads);
		swapsperphase = pow(2, phase);
	//END global variables for each thread.

	//qsort all thread.
		Local_sort(thread, start, work);

	//phase logic.
		while ( phasemask <= max_phases )
		{
			Sync(thread);
			//if (phase != 1){
			//printf(" \n HERE AGAIN \n ");}

			//        15 77 83 86 35 85 92 93
		//get slope 			//only changes for each phase
			Sync(thread);
			slope = Get_slope(slopemask, thread, partner, slope);
			Sync(thread);

		//swap logic
			while( swapmask < swapsperphase)
			{
				//get partner	//changes for each swap
				//Sync(thread);
				partner = Get_partner(partnermask, swapmask,
				 			thread, partner, work, partnerindex);
				partnerindex = partner * work;
			//	Sync(thread);
				//swap
			//	if (phase != 1){
				//printf(" \n SWAPING AGAIN \n ");}
				Sync(thread);
				if (phase != 1){
					printf(" \n Completed 2nd SWAP  \n ");}
				Swap( threadindex, partnerindex, work, slope, thread,
				 		partner, start, end);
				//Print_list(temp, elements, "After all swaps, after SWAP():");
				Sync(thread);
			swapmask++;
				//keep track of swaps per phase
			//	if (thread == maxthreads-1){
			//	swapmask <<= 1;}
			}//end swap logic
			//update logic
			//if no more swaps remain for phase...

			//exit(0);
			//if (swapmask <= swapsperphase)
			//{
				//have one thread...
				if (thread == 0)
				{
					//reset swapmask 1 for next phase
					swapmask = 1;
					//debug, completed phase blah element butterfly
					Print_debug(thread, phase, elements );
					//go to next phase
					phasemask <<= 1;
				printf(" \n new, phase=%d, phasemask =%d, at line# = %d. \n ",
						phase, phasemask, __LINE__);
					phase++;
				}
			//}//end update logic

	}//end phase logic.
	// 15 77 83 86 35 85 92 93
	//return NULL;
	}//end bitonic sort
/*-------------------------------------------------------------------
* Function:    Swap
* Purpose:    Swap  the contents of 2 numbers at a specific point in each array
* In args:     threadindex, partnerindex, work, slope, thread, partner, start,
*				end
* In/out args: none
*/
void Swap( int threadindex, int partnerindex, int work, int slope, int thread,
 			int partner, int start, int end)
{
	//swap depends on slope
	//increasing
//printf(" \n thread %d's slope = %d @ line#%d. \n ", thread, slope, __LINE__);

	if ( (slope == 1) )
	{
		//increasing = low to high.
		//so if right < left, swap.
		//copy left to before writing over.
					int mylength = end - start;
					pthread_mutex_lock(&barrier_mutex);
					int j;
				for (j = 0; j < mylength; j++)
					{
				printf("(increasing)if threadindex %d < %d partnerindex.\n\n",
				 	array[threadindex + j ], array[partnerindex + j]);
						if ( temp[threadindex + j] < temp[partnerindex + j ])
								printf("true.\n\n");

						if (temp[threadindex + j] < temp[partnerindex + j ]);
						{

		storage1[threadindex + j ] = temp[threadindex + j];
		temp[threadindex + j] = temp[partnerindex + j];
		temp[partnerindex + j] = storage1[threadindex + j];
		pthread_mutex_unlock(&barrier_mutex);
						}
					}
//        15 77 83 86 35 85 92 93
	}
	//decreasing
	else if ( (slope == 0) )
	{
		//decreasing = high to low.
		//so if right > left, swap.
		//copy left to before writing over.
//        15 77 83 86 35 85 92 93

		int i;
				//Print_list(temp, elements, "BEFORE DECREASING SWAP");

		//assuming thread is even and so left comparing to right.
		int length = end - start;
		for (i = 0; i < length; i++)
		{
			printf("(decreasing)if threadindex %d < %d partnerindex.\n\n",
			 			array[threadindex + i ], array[partnerindex + i]);
			if ( temp[threadindex + i] < temp[partnerindex + i ])
				printf("true.\n\n");

			if (temp[threadindex + i] < temp[partnerindex + i ]);
			{
				pthread_mutex_lock(&barrier_mutex);
				storage2[partnerindex + i ] = temp[partnerindex + i];
				temp[partnerindex + i ] = temp[threadindex + i ];
				temp[threadindex + i ] = storage2[partnerindex + i];
				//Print_list(temp, elements, "AFTER DECREASING SWAP");
				pthread_mutex_unlock(&barrier_mutex);
			}
		}
	}
if (thread == 0 )
	{
	//Print_list(array, elements, "BEFORE:\n\n");
	Print_list(temp, elements, "AFTER SWAP");
	if (phase != 1)
		{
			Print_list(temp, elements, "AFTER 2nd SWAP");

		}
	}

}
/*-------------------------------------------------------------------
* Function:    Get_slope
* Purpose:     Find a threads slope
* In args:     slopemask, thread, partner, slope
* In/out args: slope
*/
unsigned Get_slope(unsigned slopemask, int thread, int partner, int slope)
{
	//printf(" \n at the top of Get_slope(). \n ");

	//slope logic for each thread

	// while ( slopemask <= swapsperphase )
	// {
		//printf(" \n while ( slopemask <= swapsperphase ) \n ");
		//slopemask <<= 1;

		if( ( thread & slopemask ) == 0 )
			slope = 1;
		else if ( ( thread & slopemask) != 0 )
			slope = 0;
	//}
	//update slopemask for next phase. just one thread should do this!!!!
	if (partner == maxthreads-1)
		{
			printf(" \n updating Get_slope() slopemask at line# = %d. \n ",
			 	__LINE__);

			slopemask <<= 1;
		}
	//printf(" \n at the bottom of Get_slope(). \n ");
	Sync(thread);

	if (phase != 1){
	printf("%d's slope is %d for phase %d. \n", thread, slope, phase);}

	return slope;
}
/*-------------------------------------------------------------------
* Function:    Get_partner
* Purpose:     Find a threads partner
* In args:     partnermask, slopemask, swapmask, thread, partner, work,
*				partnerindex
* In/out args: partner
*/
unsigned Get_partner(unsigned partnermask, unsigned swapmask, int thread,
					int partner, int work, int partnerindex)
{
	//printf(" \n made it to line# = %d. \n ", __LINE__);


//	printf(" \n thread %d's partner = %d. \n ", thread, partner);

	//partner logic for each phase. partnermask is equal to
	//while ( partnermask < maxthreads )
		//{
			partner = thread ^ partnermask;
		//	printf(" \n thread %d's partner = %d. \n ", thread, partner);
		//}
	//	printf(" \n made it to line# = %d. \n ", __LINE__);
	//if their is another swap remaining in phase, increment partnermask
	if ( partnermask < swapsperphase)
		{
			//update partnermask for next swap.
			//just one thread should do this though!!!!
			if (partner == maxthreads-1)
				{
					partnermask <<= 1;
				}
		}
	//	printf(" \n made it to line# = %d. \n ", __LINE__);
	//reset partnermask to one for next phase
	if (swapmask == swapsperphase)
	{
		//have one thread...
		if (thread == maxthreads-1)
		{
		printf(" \n resetting Get_partner() partnermask at line# = %d. \n ",
		 __LINE__);
		partnermask = 1;
		}
	}

	//printf(" \n made it to line# = %d. \n ", __LINE__);
	Sync(thread);
	//partnerindex = partner * work;
	//printf("%d's partner is %d for phase %d.\n", thread, partner, phase);
	return partner;
}
/*-------------------------------------------------------------------
* Function:    Local_sort
* Purpose:     Sort earch threads work using qsort
* In args:     thread, start, work
* In/out args: nothing
*/
void Local_sort(int thread, int start, int work)
{
	qsort( array + start, work, sizeof(int), Compare);
	Sync(thread);
	if (thread == 0){
	Print_list(array, elements, "After qsort");}
}
/*-------------------------------------------------------------------
* Function:    Get_input
* Purpose:     Gets the command line input and processes its arguments
* In args:     argc, argv[], maxthreads_p, elements_p, make_numbers_p,
*				print_beofre_p
* In/out args: nothing
*/
void Get_input(int argc, char* argv[], int* maxthreads_p,
		int* elements_p, char* make_numbers_p, char* print_before_p)
{
	if (argc < 2 ) {
	printf("Too few arguments.");
	Error(argv[0]);
	exit(0);}
	int i;
	for (i = 1; i < argc; i++) // Skip argv[0] (program name).
	{
		if (strcmp(argv[i], "g") == 0)  /* Process optional arguments. */
		{
			make_numbers_arg = 1;
			*make_numbers_p = argv[i][0];
		}
		else if (strcmp(argv[i], "o") == 0 ) /* Process optional arguments. */
		{
				print_arg = 1;
				*print_before_p = argv[i][0];
		}
		else
		{
			/* Process non-optional arguments here. */
			*maxthreads_p = atoi( argv[1] );   //required
			*elements_p = atoi( argv[2] );  //required
			if (*maxthreads_p <= 0 || *elements_p <= 0 )
				{
				printf("Threads or elements are to small.\n");
				Error(argv[0]);
				exit(0);
				}
		}
	}
}
/*-------------------------------------------------------------------
* Function:    Start_arrays
* Purpose:     Creats arrays and populates them based on commands
* In args:     nothing
* In/out args: nothing
*/
void Start_arrays()
{
	//step 3 = fill arrays with numbers
	if ( make_numbers_arg == 1 )
	{
		Random_number();
	}
	else
	{
		Read_list(array, elements);
	}
}
/*-------------------------------------------------------------------
* Function:    Compare
* Purpose:     used for qsort to sort.
* In args:     array_pointer_threadindex, array_pointer_partnerindex
* In/out args: 1, 0, -1
*/
int Compare(const void* array_pointer_threadindex,
 				const void* array_pointer_partnerindex)
{
	int x = *( (int*) array_pointer_threadindex );
	int y = *( (int*) array_pointer_partnerindex );

	if (x < y)
		return -1;
	else if (x == y)
		return 0;
	else
		return 1;
}
/*-------------------------------------------------------------------
* Function:    Read_list
* Purpose:     read in numbers that the user types
* In args:     array[], elements
* In/out args: nothing
*/
void Read_list(int array[], int elements)
{
	long i;
	printf("\nEnter numbers:\n");
	for (i = 0; i < elements; i++)
	{
		scanf("%d", (int*)&array[i]) ;
		//copy elements to temporary array
		temp[i] = array[i];
	}//        15 77 83 86 35 85 92 93

}
/*-------------------------------------------------------------------
* Function:    Error
* Purpose:     Tell users they entere the commands inporperly
* In args:     prog_name
* In/out args: stderr
*/
void Error(char* prog_name)
{
	fprintf(stderr, "##### input violation. #######\n");
	fprintf(stderr, "Run: ./getinput <#threads> <#elements> [g] [o]\n");
}

/*-------------------------------------------------------------------
* Function:    Sync
* Purpose:     Barrier for threads
* In args:     thread
* In/out args: nothing
*/
void Sync(int thread)
{
	pthread_mutex_lock(&barrier_mutex);
	barrier_thread_count++;
		if (barrier_thread_count == maxthreads)
		{
			barrier_thread_count = 0;
			pthread_cond_broadcast(&ok_to_proceed);
		}
		else
		{
			while (pthread_cond_wait(&ok_to_proceed, &barrier_mutex) != 0);
		}
	pthread_mutex_unlock(&barrier_mutex);
}
/*-------------------------------------------------------------------
* Function:    Print_list
* Purpose:     Print the list of an array of integers
* In args:     array[], elements, title
* In/out args: array[i] <= array[maxsize];
*/
void Print_list(int array[], int elements, char* title)
{
	int i;
	{
		printf("\n%s %d:\n", title, phase);
		for (i = 0; i < elements; i++)
		printf("%d ", array[i]);
		printf("\n");
	}
}
/*-------------------------------------------------------------------
* Function:    Random_number
* Purpose:     Generate random numbers
* In args:     none
* In/out args: none
*/
unsigned Random_number()
{
	unsigned long i = 0;
	unsigned long j = 0;
	unsigned seed = 1;
	for (i = 1; i <= elements; i++)
	{
		j = ( srandom(seed) % 999999);
		array[i] = j;
		temp[i] = j;
		j++;
	}
	return (0);
}
/*-------------------------------------------------------------------
* Function:    Print_debug
* Purpose:     prings out data related to phase in sort
* In args:     thread, phase, elements
* In/out args: phase, swapsperphase
*/
void Print_debug(int thread, int phase, int elements )
{
	if ( thread == 0)
		{
			printf("\Finished phase %d, of %d-element butterfly. \n",
			phase, swapsperphase);
		}
}
