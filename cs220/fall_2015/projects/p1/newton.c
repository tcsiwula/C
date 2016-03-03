/*
 ==============================================================================
 Author:       =        Tim Siwula
 Liscense:     =        GPLv2
 File:         =        newton.c
 Version:      =        0.1
 ==============================================================================
 Compile:      =        gcc -g -Wall -o newton newton.c -lm
 Run:          =        ./newton
 ==============================================================================
 Purpose:      =        A program that implements Newton's method for finding
               =        a solution to the equation f(x) = 0.
 ==============================================================================
 Input:        =        1. An initial guess,
               =        2. A maximum error tolerance,
               =        3. A maximum number of iterations.
 ==============================================================================
 Output:       =        1. Wheather the iteration converged,
               =        2. The number of iterations,
               =        3. The approximate solution,
               =        4. The value of the function at the approximate solution
 ==============================================================================
 Note:         =        Enjoy ^_^ 💘
 ==============================================================================
 */

// External libaries
#include <stdio.h>
#include <math.h>

// CUSTOM FUNCTION DEFINITIONS
void get_input_arguments(double* x_0, double* error_tol, double* max_iters);
double newtons_method(double x_0, double error_tol, double max_iters);
double f1(double x);
double f_prime1(double x);
double f2(double x);
double f_prime2(double x);
double f3(double x);
double f_prime3(double x);
double f4(double x);
double f_prime4(double x);

/* ========================================================================= */
int main(void)
{
    double x_0, error_tol, max_iters, result;
    get_input_arguments(&x_0, &error_tol, &max_iters);
    result = newtons_method(x_0, error_tol, max_iters);
    return 0;
}

/*
 ==============================================================================
 Function:     =        newtons_method
 Purpose:      =        Compute the derivative of x
 ==============================================================================
 Input arg:    =        1. x_0: An initial guess,
               =        2. error_tol: A maximum error tolerance,
               =        3. max_iters: A maximum number of iterations.
 ==============================================================================
 Output arg:   =        1. The number of iterations,
               =        2. If the iteration converged,
               =        3. x_new: The approximate solution,
               =        4. The value of the function at the approximate solution
 ==============================================================================
 */
double newtons_method(double x_0, double error_tol, double max_iters)
{
  int count = 0;
  double x_new = x_0;
  printf("Now calculating \n");
  printf(". \n");
  printf(".. \n\n");

  do
  {
      x_0 = x_new;
      count++;

      if (f_prime1(x_0) == 0)
      {
        printf("f_prime( x_old ) is zero!\n");
        break;  /* Get out of here */
      }

      x_new = x_0 - f1(x_0)/f_prime1(x_0);
  }
  while ( fabs(x_new - x_0 )  >  error_tol && (count <= max_iters) );

  printf("Results: \n");
  printf("x_0 = %lf \n", x_0);
  printf("x_new = %lf \n", x_new);
  printf("Number of iterations = %d \n", count);
  printf("count = %d \n", count);
  printf("error_tol = %lf \n", error_tol);

 if (count > max_iters)
 {
   printf("Iteration did not convereg.\n\n");
 }
 else
 {
   printf("Iteration did convereg.\n\n");
 }

  return x_new;
}

/*
 ==============================================================================
 Function:     =        get_input_arguments
 Purpose:      =        Get user input data
 ==============================================================================
 Input arg:    =        1. x_0: An initial guess,
               =        2. error_tol: A maximum error tolerance,
               =        3. max_iters: A maximum number of iterations.
 ==============================================================================
 */
void get_input_arguments(double* x_0, double* error_tol, double* max_iters)
{
    printf("Enter initial guess \n");
    scanf("%lf", x_0);

    printf("Enter maximum error tollerance \n");
    scanf("%lf", error_tol);

    printf("Enter maximum number of iterations throgh the do-while loop \n");
    scanf("%lf", max_iters);
}

/*
 ==============================================================================
 Function:     =        f1 - f5, f1_prime - f5_prime
 Purpose:      =        Produce a unique function to test newtons_method
 ==============================================================================
 Input arg:    =        1. x: A double to perform the function on.
 ==============================================================================
 Output arg:    =       1. x: The double after perfroming the function on it.
 ==============================================================================
 */
double f1(double x)
{
    return pow(x, 2) - 2;
}

double f_prime1(double x)
{
  return x * 2;
}

double f2(double x)
{
    return sin(x);
}

double f_prime2(double x)
{
  return cos(x);
}

double f3(double x)
{
    return pow(fabs((x-1)), 3);
}

double f_prime3(double x)
{
  return 3 * pow(fabs((x-1)), 2);
}

double f4(double x)
{
    return pow(fabs((x - 1)), 1.0/3.0);
}

double f_prime4(double x){
  return (1/3) * pow(fabs((x - 1)), -2.0/3.0);
}
