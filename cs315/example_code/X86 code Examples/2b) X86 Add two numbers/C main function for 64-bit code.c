/* File:     add.c
 *
 * Purpose:  Linux program that adds two user-input long ints.  Calls x86 
 *           assembly function to do the addition.
 *
 * Compile:  gcc -o add add.c sum.s -I.
 * Run:      ./add
 *
 * Input:    Two long ints
 * Output:   Their sum
 *
 * Notes:     
 * 1. This version should be run on a 64-bit system.
 */

#include <stdio.h>

long Sum(long a, long b);

int main(void) {
   long a, b, c;

   printf("Enter two ints\n");
   scanf("%ld%ld", &a, &b);

   c = Sum(a, b);

   printf("The sum is %ld\n", c);

   return 0;
}
