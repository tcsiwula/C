/****************************************************************
 *	Grade: 1/8
 *	Commets: 1) Fail compiling  -50%
 *           2) No input output -4
 *           3) Wrong calculation -2
 *
 *
 ***************************************************************/
	// Author: Tim Siwula
	// Assignment9


#include <stdio.h>
#indlude <stdlib.h>
#include <pthread.h>


	//global variables
double number_of_threads, alpha;
double array_x[number_of_threads], array_y[number_of_threads];

	//daxpy function each thread calls
void* Daxpy(void* rank);

int main(int argc, char* argv[])
{
	long thread_x;
	pthread_t* pthread_t_object;

		// step1 get number_of_threads from user

	number_of_threads = strtol(argv[1], NULL, 10);

		//step2 allocate storage for x,y
		//pthread_t_object = malloc(number_of_threads * sizeof(pthread_t_object)); //example model
	pthread_t_object = malloc(number_of_threads * sizeof( array_x * array_y ));
		//pthread_t_object = malloc(number_of_threads * sizeof(array_y)); //need multiple storages or just one shared?

		//step3 read in x, y, alpha


	for thread_x = 0; thread_x < number_of_threads; thread_x++)

	pthread_create(&pthread_t_object[thread_x], NULL, Daxpy, (void*) thread_x);
	printf("Hello from thread 0");

	for(thread_x = 0; thread_x < number_of_threads; thread_x++)
		{
		pthread_join(pthread_t_object[thread_x], NULL);
		}

	free(pthread_t_object);
	return 0;
}


	//serial implementation
	//turn into parallel via block distribution

void* Daxpy(void* rank)
{
	long my_rank = (long) rank;

		//serialize attempt
		//model from pth_mat_vect

	int i, j;
	int local_m = m/thread_count;
	int my_first_row = my_rank * local_m;
	int my_last_row = (my_rank+1) * local_m - 1;

	for ( i = my_first_row; i <= my+last_row; i++)
		{
		y[i] = 0.0;
		for (j = 0; j < n; j++)
			{
			y[i] += A[i][j]*x[j];
			}
		}

	printf("Hello from thread %ld of %d\n", my_rank, number_of_threads);
	return NULL;
}


