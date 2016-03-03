/* File:     Circular_shift.c
 * Purpose:  Shift an array to the right.  Elements "falling off" 
 *           the end are shifted (in order) to beginning.
 * Input:
 *    n:  number of elements in the input array
 *    A:  the input array
 *    shift:  the amount to shift.
 *
 * Output:
 *    A:  after the shift
 * Notes:
 *    1. Maximum array size is defined in global constant MAX
 *    2. There's no check on input array sizes
 */
#include <stdio.h>

/* This is somewhat equivalent to a final variable in Java */
const int MAX = 100;

void Read_array(int A[], int n);
void Print_array(int A[], int n);
void Circular_shift(int A[], int n, int shift);

/*-------------------------------------------------------------------*/
int main(void) {
   int A[MAX];
   int n, shift;

   printf("How many elements in the array?\n");
   scanf("%d", &n);

   printf("Enter the elements of the array.\n");
   Read_array(A, n);

   printf("How much should we shift?\n");
   scanf("%d", &shift);
   Circular_shift(A, n, shift);
   
   printf("After the shift = \n");
   Print_array(A, n);
   return 0;
}  /* main */


/*-------------------------------------------------------------------
 * Function:   Read_array
 * Purpose:    read in the contents of the array A
 * Input arg:  n, the number of elements to be read
 * Output arg: A, the array
 */
void Read_array(int A[], int n) {
   int i;
   for (i = 0; i < n; i++)
      scanf("%d", &A[i]);
}  /* Read_array */


/*-------------------------------------------------------------------
 * Function:   Print_array
 * Purpose:    print the contents of the array A
 * Input args:
 *    n, the number of elements to be read
 *    A, the array
 */
void Print_array(int A[], int n) {
   int i;
   for (i = 0; i < n; i++)
      printf("%d ", A[i]);
   printf("\n");
}  /* Print_array */


/*-------------------------------------------------------------------
 * Function:   Circular_shift
 * Purpose:    Shift the contents of the array shift places to the
 *             the right.  Elements falling off the end of the array 
 *             are shifted in order to the beginning
 * Input args:
 *    n:      the number of elements in A
 *    shift:  the amount of the shift
 * Input/Output arg:
 *    A:      the original array, and the shifted array
 */
void Circular_shift(int A[], int n, int shift) {
   int i, new_i, tmp_A[n], tmp;

   for (i = 0; i < n; i++) {
      new_i = (i + shift) % n;
      tmp_A[new_i] = A[i];
   }

   for (i = 0; i < n; i++)
      A[i] = tmp_A[i];
}  /* Circular_shift */
