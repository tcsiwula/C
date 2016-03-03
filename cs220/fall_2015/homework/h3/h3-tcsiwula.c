/*
 * Main function:
 * 1/1 - Array declaration (variable declaration)
 * 1/1 - Get n
 * 1/1 - Get the array
 * 2/2 - function call
 * 2/2 - Print result
 *
 * Shift function args:
 * 6/6 - arguments (2 pts each) (-1 for each pointer)
 * 
 * 6/6 - Shift function
 *
 * Total: 19/19
 */

/*
 ==============================================================================
 Author:       =        Tim Siwula
 File:         =        circular_shift.c
 Date:         =        Sep 18 2015
 Version:      =        0.2
 Liscense:     =        GPLv2
 ==============================================================================
 Compile:      =        gcc -g -Wall -o circular_shift circular_shift.c -lm
 Run:          =        ./circular_shift
 ==============================================================================
 Purpose:      =        A program that implements a right circular shift of an
               =        array of ints.
 ==============================================================================
 Input:        =        1. The number of elements in the array,
               =        2. The actual array elements,
               =        3. The number of places for the right circular shift.
 ==============================================================================
 Output:       =        1. Print the shifted array
 ==============================================================================
 Note:         =        Enjoy ^_^ 💘
 ==============================================================================
 */

 // External libaries
 #include <stdio.h>

 // CUSTOM FUNCTION DEFINITIONS
void Read_array(int array_of_elements[], int number_of_elements);
void circular_shift(int size, int array_of_elements[], int shift_amount);
void Print_array(int array_of_elements[], int number_of_elements);

 /* ========================================================================= */
 int main(void)
 {
     int size, shift_amount;

     do
     {
        printf("How many elements in your array? > 0 && < 20 \n");
        scanf("%d", &size);
     }
     while ( size > 20 || size < 1);

     int array_of_elements[size];

     printf("Enter the elements of your array. \n");
     Read_array(array_of_elements, size);

     printf("How many places would you like to shift array? \n");
     scanf("%d", &shift_amount);

     printf("Before: \n");
     Print_array(array_of_elements, size);

     circular_shift(size, array_of_elements, shift_amount);

     printf("After: \n");
     Print_array(array_of_elements, size);

     return 0;
 }

 /*
  ==============================================================================
  Function:     =        Read_array
  Purpose:      =        Read in elements into an array from user
  ==============================================================================
  Input arg:    =        1. number_of_elements: Size of an array,
                =        2. array_of_elements: An array.
  ==============================================================================
  */
void Read_array(int array_of_elements[], int size)
 {
     int i;
     for (i = 0; i < size; i++ )
         scanf("%d", &array_of_elements[i]);
 }

/*
 ==============================================================================
 Function:     =        Print_array
 Purpose:      =        print the contents of the array
 ==============================================================================
 Input arg:    =        1. number_of_elements: Size of an array,
               =        2. array_of_elements: An array.
 ==============================================================================
 */
void Print_array(int array_of_elements[], int size)
{
    int i;
    for (i = 0; i < size; i++ )
        printf("%d", array_of_elements[i]);
    printf("\n");
}

 /*
  ==============================================================================
  Function:     =        circular_shift
  Purpose:      =        Compute the derivative of x
  ==============================================================================
  Input arg:    =        1. size: size of the array,
                =        2. array_of_elements[]: An array to be shifted,
                =        3. shift_amount: The amount to be shifted.
  ==============================================================================
  */
 void circular_shift(int size, int array_of_elements[], int shift_amount)
 {
     int i, j, z;
     int start = size - shift_amount;
     int tmp_array[size];

     // copy the shifted bits into the beggining of tmp array
     for (i = 0; i < shift_amount; i++)
     {
         tmp_array[i] = array_of_elements[start + i];
     }

     // copy the beggining of the orginal after the shifted bits
     for (j = 0; j < start; j++)
     {
         tmp_array[i] = array_of_elements[j];
         i = i+1;
     }

     // copy from tmp back into array
     for (z = 0; z < size; z++)
     {
         array_of_elements[z] = tmp_array[z];
     }
 }
