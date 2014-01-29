//
//  main.c
//  C
//
//  Created by Tim on 12/31/13.
//  Copyright (c) 2013 Tim Siwula. All rights reserved.
//

#include <stdio.h>

int main()

/*
    printf("Section 1.1 - Getting Started. \n \n");

    
    printf("Hello, World. This is Tim's first C program. Amazing.\n \n");
    
    printf("This is a tab escape sequence. \t ok? \n");
    printf("This is a backspace escape sequence. \b ok? \n");
    printf("This is a double quote escape sequence. \" ok? \n");
    printf("This is a backspace escape sequence. \\ ok? \n");
    printf("This is a new line escape sequence. \n ok? \n");
*/
    
    
    
{
        float fahr, celsius;
        int lower, upper, step;
        
        lower = 0;      /* lower limit of temperature table */
        upper = 300;    /* upper limit */
        step = 20;      /* step size */
        
        fahr = lower;
        while (fahr <= upper)
        {
            celsius = 5 * (fahr-32) / 9;
            printf("%3.0f %10.1f\n", fahr, celsius);
            fahr = fahr + step;
        }
    
}
