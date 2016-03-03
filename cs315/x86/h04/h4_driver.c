/* File:     h4_driver.c
 *
 * Purpose:  Linux program that adds two user-input long ints.  Calls x86
 *           assembly function to do the addition.
 *
 * Compile:  gcc -o h4_driver h4_driver.c h4_driver.s
 * Run:      ./h4_driver
 *
 * Input:    Two long ints
 * Output:   Their sum
 *
 * Notes:
 * 1. This version should be run on a 64-bit system.
 */

#include <stdio.h>

long Driver(long a, long b);

int main(void) {
    long a, b, c;

    printf("Enter two ints\n");
    scanf("%ld%ld", &a, &b);

    c = Driver(a, b);

    printf("The sum is %ld\n", c);

    return 0;
}
