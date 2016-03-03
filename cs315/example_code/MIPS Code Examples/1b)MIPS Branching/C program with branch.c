/* File:     branch.c
 * Purpose:  Read an int and determine whether it's nonnegative or negative
 *
 * Compile:  gcc -g -Wall -o branch branch.c
 * Run:      ./branch
 *
 * Input:    A single int
 * Output:   Whether the input int is nonnegative or negative
 */
#include <stdio.h>

int main(void) {
   int n;

   scanf("%d", &n);
   if (n >= 0)
      printf("The input value is >= 0\n");
   else
      printf("The input value is negative\n");
   
   return 0;
}
