// Author: Tim Siwula
// Homework Assignment 9 part 1
// daxpy.c

// * Compile:  gcc -g -Wall -o daxpy daxpy.c -lpthread
// * Run:   			daxpy <num_threads>

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// global variables
int num_threads, n;
double* x;
double* y;
double alpha;

// functions
void Get_data(double input[], int n, int flag);
void Print_results(double output[], int n);
void *Daxpy(void* my_thread);

// main
int main(int argc, char* argv[])
{
	long thread_object;
	pthread_t* my_thread;
	num_threads = strtol(argv[1], NULL, 10);
	my_thread = malloc(num_threads*sizeof(pthread_t));
	printf("Enter size of n: \n");
	scanf("%d", &n);
	x = malloc(n*sizeof(double));
	y = malloc(n*sizeof(double));
	Get_data(x, n, 0);
	Get_data(y, n, 1);
	printf("Enter a value for alpha: \n");
	scanf("%lf", &alpha);

	for (thread_object = 0; thread_object < num_threads; thread_object++)
	{
	pthread_create(&my_thread[thread_object], NULL, Daxpy, (void*) thread_object);
	}

	for(thread_object = 0; thread_object < num_threads; thread_object++)
	{
		pthread_join(my_thread[thread_object], NULL);
	}

	Print_results(y, n);

	free(x);
	free(y);
	free(my_thread);

	return 0;
}
void Get_data(double input[], int n, int flag)
{
	int iterator;

	if (flag == 0)
	{
		printf("Please enter the vector for x now. \n");
	}
	else
	{
		printf("Please enter the vector for y now. \n");
	}

	for(iterator = 0; iterator < n; iterator++)
	{
		scanf("%lf", &input[iterator]);
	}
}

void Print_results(double output[], int n)
{
	int iterator;

	printf("You Daxpy reslts are : \n");

	for (iterator = 0; iterator < n; iterator++)
	{
		printf("%4.1f ", output[iterator]);
	}
	printf("\n");
}

void *Daxpy(void* my_thread)
{
	int iterator;
	long my_rank = (long) my_thread;
	int loc_n = n/num_threads;
	int loc_n_start = my_rank * loc_n;
	int loc_n_stop = loc_n_start + loc_n;

	for (iterator = loc_n_start; iterator < loc_n_stop; iterator++)
	{
		y[iterator] += alpha * x[iterator];
	}

	return NULL;
}
