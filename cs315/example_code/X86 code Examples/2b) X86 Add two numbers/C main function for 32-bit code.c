/* File:     add_int.c
 *
 * Purpose:  Linux program that adds two user-input ints.  Calls x86 assembly
 *           function to do the addition.
 *
 * Compile:  gcc [-m32] -o add_int add_int.c sum_int.s 
 * Run:      ./add_int
 *
 * Input:    Two ints
 * Output:   Their sum
 *
 * Notes:     
 * 1. This program may not compile on 64-bit systems:  32-bit libraries
 *    and header files need to be installed.  
 * 2. The -m32 command line option should only be necessary on 64-bit
 *    systems.
 */
#include <stdio.h>

int Sum(int a, int b);

int main(void) {
   int a, b, c;

   printf("Enter two ints\n");
   scanf("%d%d", &a, &b);

   c = Sum(a, b);

   printf("The sum is %d\n", c);

   return 0;
}
