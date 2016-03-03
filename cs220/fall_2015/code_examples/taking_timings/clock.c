/* File:     clock.c
 * Purpose:  Illustrate the use of the Unix clock function for timing.
 *
 * Compile:  gcc -g -Wall -o clock clock.c
 * Run:      ./clock <number of iterations in for loop>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[]) {
   long start, finish;
   long i, n;
   double elapsed;
   double x = 0;
   int pm = 1;

   if (argc != 2) {
      fprintf(stderr, "usage:  %s <n>\n", argv[0]);
      exit(0);
   }
   n = strtol(argv[1], NULL, 10);

   printf("CLOCKS_PER_SEC = %ld\n", (long) CLOCKS_PER_SEC);

   start = clock();
   for (i = 0; i < n; i++, pm = -pm) 
      x += pm*exp(sin((double) i));
   finish = clock();

   elapsed = finish - start;
   elapsed = elapsed/CLOCKS_PER_SEC;
   printf("Elapsed time = %.14e seconds\n", elapsed);
   
   return 0;
}
