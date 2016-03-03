/* File:     main.c
 * Purpose:  Driver program for x86 assembler function that computes n!
 *
 * Compile:  gcc -g -Wall -o fact main.c fact.s
 * Run:      ./fact <n>
 *
 * Notes:
 * 1.  This program should be run on a 64-bit Linux system.
 * 2.  With the macro ALL_IN_C defined, the program will use
 *     use a C function to compute n factorial:
 *
 *     $ gcc -g -Wall -DALL_IN_C -o fact main.c
 *
 */
#include <stdio.h>
#include <stdlib.h>

long Fact(long n);

int main(int argc, char* argv[]) {
   long n, nfact;

   if (argc != 2) {
      fprintf(stderr, "usage: %s <n>\n", argv[0]);
      exit(0);
   }

   n = strtol(argv[1], NULL, 10);

   nfact = Fact(n);

   printf("%ld! = %ld\n", n, nfact);

   return 0;
}  

#ifdef ALL_IN_C
long Fact(long n) {
   long i, nfact;

   nfact = 1;
   for (i = 1; i <= n; i++)
      nfact = nfact*i;

   return nfact;
}
#endif
