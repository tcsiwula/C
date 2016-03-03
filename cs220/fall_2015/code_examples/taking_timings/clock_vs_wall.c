/* File:     clock_vs_wall.c
 * Purpose:  Illustrate the use of the Unix clock function for timing.
 *
 * Compile:  gcc -g -Wall -o clock_vs_wall clock_vs_wall.c
 * Run:      ./clock_vs_wall <number of iterations in for loop>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "timer.h"

int main(int argc, char* argv[]) {
   long start, finish;
   long i, n;
   double elapsed;
   double x = 0;
   int pm = 1;
   double gstart, gfinish, gelapsed;
   char c;

   if (argc != 2) {
      fprintf(stderr, "usage:  %s <n>\n", argv[0]);
      exit(0);
   }
   n = strtol(argv[1], NULL, 10);

   start = clock();
   GET_TIME(gstart);
   printf("Hit enter to start...");
   scanf("%c", &c);
   for (i = 0; i < n; i++, pm = -pm) 
      x += pm*exp(sin((double) i));
   finish = clock();
   GET_TIME(gfinish);

   elapsed = finish - start;
   elapsed = elapsed/CLOCKS_PER_SEC;
   printf("Clock elapsed time = %.14e seconds\n", elapsed);

   gelapsed = gfinish - gstart;
   printf("Wall clock elapsed time = %.14e seconds\n", gelapsed);
   
   return 0;
}
