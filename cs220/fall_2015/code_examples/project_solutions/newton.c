/* File:     newton.c 
 * Purpose:  Use Newton's method to solve f(x) = 0.
 * Author:   Peter Pacheco
 *
 * Compile:  Using Linux and gcc
 *           gcc -g -Wall -o newton newton.c -lm
 * Usage:    ./newton
 *
 * Input:    x_0:        initial guess 
 *           tol:        max difference between successive iterates 
 *           max_iters:  maximum number of iterations
 * Output:   Whether the iteration converged, the approximate 
 *           solution x, f(x), and the number of iterations. 
 *
 * Notes:    f(x) and f'(x) are hardwired
 */

#include <stdio.h>
#include <math.h>

double newton(double x_0, double tol, int max_iters, 
          int* iters_p, int* converged_p);
double f(double x);
double f_prime(double x);

/*------------------------------------------------------------*/
int main(void) {
   double x_0;       /* Initial guess                */
   double x;         /* Approximate solution         */
   double tol;       /* Maximum error                */
   int    max_iters; /* Maximum number of iterations */
   int    iters;     /* Actual number of iterations  */
   int    converged; /* Whether iteration converged  */

   printf("Enter x_0, tol, and max_iters\n");
   scanf("%lf %lf %d", &x_0, &tol, &max_iters);

   printf("x_0 = %f, tol = %f, max_iters = %d\n", 
         x_0, tol, max_iters);

   x = newton(x_0, tol, max_iters, &iters, &converged);

   if (converged) {
      printf("Method converged after %d iterations.\n", 
          iters);
      printf("The approximate solution is %.15e\n", x);
      printf("f(%.15e) = %.15e\n", x, f(x));
   } else {
      printf("Method didn't converge after %d iterations.\n", 
          iters);
      printf("The final estimate was %.15e\n", x);
      printf("f(%.15e) = %.15e\n", x, f(x));
  }

   return 0;
}  /* main */


/*------------------------------------------------------------
 * Function:  newton
 * Purpose:  Implement Newton's method
 * Input arguments:  x_0, tol, max_iters
 * Output arguments: iters_p and converged_p
 *
 * Note: Estimate error in x_new by |x_new - x_old|
 */
double newton(double x_0, double tol, int max_iters, 
          int* iters_p, int* converged_p) {
   double x_new = x_0;
   double x_old;
   double divisor;
   int    iter = 0;

   do {
      iter++;
      x_old = x_new;
      divisor = f_prime(x_old);
      if (divisor == 0.0) {
         printf("f_prime = 0!\n");
         break;
      }
      x_new = x_old - f(x_old)/divisor;
#     ifdef DEBUG
      printf("x_new = %.10e, x_old = %.10e, divisor = %.10e, error est = %.10e\n",
            x_new, x_old, divisor, fabs(x_new - x_old));
#     endif 
   } while (fabs(x_new - x_old) > tol && iter < max_iters);

   if (fabs(x_new - x_old) <= tol)
      *converged_p = 1;
   else
      *converged_p = 0;
   *iters_p = iter;
   
   return x_new;
}  /* newton */


/*------------------------------------------------------------
 * Function: f
 */
double f(double x) {
   double y;

// f1;  exact = sqrt(2) = 1.4142135623
// y = x*x - 2;

// f2;  exact depends on x_0.  Should be 0, pi, 2pi, etc.
// y = sin(x);

// f3;  exact = 1
y = (x-1)*(x-1)*(x-1);
 
// f4;  exact = 1
// y = pow(fabs(x-1), 1.0/3.0);
// if (x-1 < 0) y = -y;

// f5;  exact = -0.6823278038
// y = x*x*x + x + 1.0;

// f6;  exact = 56,771.0543
// y = 2.68e-5*x*x + 4.36e-4*x + 1.18e-1 - 86400;
   
   return y;
}  /* f */


/*------------------------------------------------------------
 * Function:  f_prime 
 */
double f_prime(double x) {
   double y;

// f1'
// y = 2*x;

// f2'
// y = cos(x);

// f3'
y = 3*(x-1)*(x-1);

// f4'
// y = pow(fabs(x-1), -2.0/3.0)/3.0;

// f5'
// y = 3*x*x + 1;

// f6'
// y = 2*2.68e-5*x + 4.36e-4;

   return y;
}  /* f_prime */
