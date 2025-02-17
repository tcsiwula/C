/* File:     swap.c
 * Purpose:  Swap two user input ints
 *
 * Compile:  gcc -g -Wall -o swap swap.c
 * Run:      ./swap
 *
 * Input:    Two ints
 * Output:   The two ints with their order reversed.
 *
 * Example Run:
 * $ ./swap
 * Please enter two ints
 * 63 -111
 * The two ints, in reverse order, are:
 * -111 63
 * Bye!
 */
#include <stdio.h>

// void Swap( /* Fill in Formal Argument List */);
void Swap(int *x_p, int* y_p);

int main(void) {
   int x, y;

   printf("Please enter two ints\n");
   scanf("%d%d", &x, &y);
// Swap(/* Fill in Actual Argument List */);
   Swap(&x, &y);
   printf("The two ints, in reverse order, are:\n");
   printf("%d %d\n", x, y);
   printf("Bye!\n");

   return 0;
}  /* main */

/*---------------------------------------------------------------------
 * Function:     Swap
 * Purpose:      Swap the arguments
 * In/out args:  x_p:  pointer to first value
 *               y_p:  pointer to second value
 * Note:  
 *    In args are arguments whose value at the start of the function
 *       is used by the function
 *    Out args are arguments whose value is computed and returned by 
 *       the function
 *    In/out args are arguments that are both input and output args
 */
// void Swap( /* Fill in Formal Argument List */) {
void Swap(int* x_p, int* y_p) {
// /* Fill in Body of Function */
   int temp;

   temp = *x_p;
   *x_p = *y_p;
   *y_p = temp;
}  /* Swap */
