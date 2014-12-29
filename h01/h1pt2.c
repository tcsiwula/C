/* File:    trap.c
 * Purpose: Calculate area using trapezoidal rule.
 *
 * Input:   a, b, n
 * Output:  estimate of area between x-axis, x = a, x = b, and graph of f(x)
 *          using n trapezoids.
 *
 * Compile: gcc -g -Wall -o trap trap.c
 * Run:     ./trap
 *
 * Note:    The function f(x) is hardwired.
 */

#include <stdio.h>
#include <math.h>

double Trap(double  a, double  b, int n, double h);
double Simp(double  a, double  b, int n, double h);

double s(double x);
double f(double x);    /* Function we're integrating */

int main(void) {
    double  area, area2;       /* Store result in area       */
    double  a, b;       /* Left and right endpoints   */
    int     n;          /* Number of trapezoids       */
    double  h;          /* Trapezoid base width       */
    
    printf("Enter a, b, and n\n");
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%d", &n);
    
    h = (b-a)/n;
    area = Trap(a, b, n, h);
    
    if(n%2 == 0){
        area2 = Simp(a, b, n, h);
        printf("With n = %d parabolas, our estimate\n", n);
        printf("of the area from %f to %f = %.15f\n",
               a, b, area2);
        double abs = area - area2;
        
        int num = fabs(abs);
        printf("The absolute vale of the difference between %f and %f is %d.", area, area2, num);
    
       
    }
    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the area from %f to %f = %.15f\n",
           a, b, area);
    
    main();
    return 0;
}  /* main */

/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Estimate area using the trapezoidal rule
 * Input args:   a: left endpoint
 *               b: right endpoint
 *               n: number of trapezoids
 *               h: stepsize = length of base of trapezoids
 * Return val:   Trapezoidal rule estimate of area between x-axis,
 *               x = a, x = b, and graph of f(x)
 */
double Trap(double a, double b, int n, double h) {
    double area;   /* Store result in area  */
    double x;
    int i;
    
    area = (f(a) + f(b))/2.0;
    for (i = 1; i <= n-1; i++) {
        x = a + i*h;
        area = area + f(x);
    }
    area = area*h;
    
    return area;
} /*  Trap  */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
    double return_val;
    
    return_val = x*x + 1;
    return return_val;
}  /* f */

/*------------------------------------------------------------------
 * Function:     Simp
 * Purpose:      Estimate area using the simpson rule
 * Input args:   a: left endpoint
 *               b: right endpoint
 *               n: number of trapezoids
 *               h: stepsize = length of base of trapezoids
 * Return val:   Simpson rule estimate of area between x-axis,
 *               x = a, x = b, and graph of f(x)
 */
double Simp(double a, double b, int n, double h) {
    double area;   /* Store result in area  */
    double x;
    int i;
    
    area =  f(a) + f(b);
    for (i = 1; i <= n-1; i++) {
        x = a + i*h;
        
        if (i%2 == 0){
            
        area = area + ( 2 * f(x) );
        }
        else
            {
        area = area + ( 4 * f(x) );

            }
    }
    
    area = area*(h/3);
    return area;
} /*  Trap  */
