/* File:     rd_prt_int.c
 * Purpose:  Use a function to prompt for an int, read it in, and return it
 *           Use a function to print the result
 *
 * Compile:  gcc -g -Wall -o rd_prt_int rd_prt_int.c
 * Run:      ./rd_prt_int
 *
 * Input:    A single int
 * Output:   prompt for input and the input value
 */
#include <stdio.h>

int Read_int(char prompt[]);
void Print_int(char message[], int n);

int main(void) {
   int n;

   n = Read_int("Enter an int\n");
   Print_int("Input value is",  n);
   
   return 0;
}  /* main */


int Read_int(char prompt[]) {
   int n;

   printf("%s", prompt);
   scanf("%d", &n);

   return n;
}  /* Read_int */


void Print_int(char message[], int n) {
   printf("%s %d\n", message, n);
}  /* Print_int */
