/* File:     branch.c
 *
 * Purpose:  Linux program that determines the larger of two user-input 
 *           long ints.  Calls x86 assembly function to do the comparison.
 *
 * Compile:  gcc -o branch branch.c test.s
 * Run:      ./branch
 *
 * Input:    Two long ints
 * Output:   Which is larger
 *
 * Notes:     
 * 1. This should be run on a 64-bit system.
 */

#include <stdio.h>

long Larger(long a, long b);

int main(void) {
   long a, b, c;

   printf("Enter two distinct ints\n");
   scanf("%ld%ld", &a, &b);

   c = Larger(a, b);

   printf("The larger of %ld and %ld is %ld\n", a, b, c);

   return 0;
}
