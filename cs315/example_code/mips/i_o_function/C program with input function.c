/* File:     read_int.c
 * Purpose:  Use a function to prompt for an int, read it in, and return it
 *
 * Compile:  gcc -g -Wall -o read_int read_int.c
 * Run:      ./read_int
 *
 * Input:    A single int
 * Output:   prompt for input and the input value
 */
#include <stdio.h>

int Read_int(char prompt[]);

int main(void) {
   int n;

   n = Read_int("Enter an int\n");
   printf("Input value is %d\n", n);
   
   return 0;
}  /* main */


int Read_int(char prompt[]) {
   int n;

   printf("%s", prompt);
   scanf("%d", &n);

   return n;
}  /* Read_int */
