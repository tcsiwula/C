//
//  Homework_Assignment_2.c
//  CS220
//
//  Created by Tim on 9/3/14.
//  Copyright (c) 2014 tcsiwula. All rights reserved.
//

#include <stdio.h>

void read_array(int my_array[], int size);
void print_array(int my_array[], int size);
void reverse_array(int my_array[], int size);
int my_array[20];
int limit;
int size;

int main(void){
    printf("Enter the number of elements you would like to input, no greater than 20.\n");
    scanf("%d", &limit);
    size = limit;
    read_array(my_array, size);
    print_array(my_array, size);
    reverse_array(my_array, size);
    print_array(my_array, size);
    
    return 0;
}

void read_array(int my_array[], int size) {
    int i;
    printf("Now enter your elements.\n");
    
    for (i = 0; i < limit; i++)
    {
        scanf("%d", &my_array[i]);
    }
}

void print_array(int my_array[], int size){
    int i;
    printf("\nYour array is: ");
    for(i = 0; i < size; i++)
    {
    printf("%d", my_array[i]);
    }
    printf("\n");
}

void reverse_array(int my_array[], int size) {
    int i;
    int j = limit-1;
    int new_array[limit];
    for(i=0; i<limit; i++)
    {
        if(j > -1)
        {
            new_array[i] = my_array[j];
            j--;
        }
    }
    
    for(i=0; i<limit; i++)
    {
        my_array[i] = new_array[i];

    }
}