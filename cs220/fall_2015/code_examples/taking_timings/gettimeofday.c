/* File:     gettimeofday.c
 * Purpose:  Illustrate the use of the Unix gettimeofday function for timing.
 *
 * Compile:  gcc -g -Wall -o gettimeofday gettimeofday.c
 * Run:      ./gettimeofday <number of iterations in for loop>
 *
 * Note:     Needs the header file timer.h in the same directory
 *           as the source during compilation.
 */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"  /* Should be in the same directory as this file */
#include <math.h>

int main(int argc, char* argv[]) {
   double start, finish;
   long i, n;
   double elapsed;
   double x = 0;
   int pm = 1;

   if (argc != 2) {
      fprintf(stderr, "usage:  %s <n>\n", argv[0]);
      exit(0);
   }
   n = strtol(argv[1], NULL, 10);

   /* Note that GET_TIME is a macro, not a function.  So the arg
    * should just be a double -- not a pointer to a double */
   GET_TIME(start);
   for (i = 0; i < n; i++, pm = -pm) 
      x += pm*exp(sin((double) i));
   GET_TIME(finish);

   elapsed = finish - start;
   printf("Elapsed time = %.14e seconds\n", elapsed);
   
   return 0;
}
