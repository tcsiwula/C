/* File:     Project_1.c
 * Author:   Tim Siwula
 *
 * Purpose:  Takes three arguments (n, m, u) and computes the temperature.
 *           exact solution is known.
 *
 * Compile:  gcc -g -Wall -o p1_program Project_1.c -lm
 * Run:      ./p1_program
 *
 * Input:    m, the number of grid points in the x-direction is m+1
 *           n, the number of grid points in the t-direction is n+1
 *           k, a constant determining the "frequency" of the solution
 *           name of file in which the data should be stored
 * Output:   A file containing input data for program 1
 *
 * Note:
 *    With input k, the exact solution is
 *
 *       u(x,t) = exp(-k^2 pi^2 t) sin(k pi x)
 */

#include <stdio.h>

const int MAX = 101;
double new_u[MAX], old_u[MAX];

void get_data(int* m_p, int* n_p, int* u_p);
void print_data(int m, double x_h, double t, int k);


int main(void)
{
    int m, n, u, j, k;
    double h_x, h_t;
    double t;
    
    get_data(&m, &n, &u);
    h_x = 1.0/m;
    h_t = 1.0/n;
    
    for (j = 0; j <= n; j++){
        t = j*h_t;
        print_data(m, h_x, t, k);
    }
    
    return 0;
}

void get_data(int* m_p, int* n_p, int* u_p)
{
    printf("Enter 'm' aka bar segments \n");
    scanf("%d", m_p);
    printf("Enter 'n' aka time intervals \n");
    scanf("%d", n_p);
    printf("Enter 'u' aka frequency \n");
    scanf("%d", u_p);
}

void print_data(int m, double h_x, double t, int k)
{
    int i;
    double x;
    
    printf("%.3f ", t);
    for (i=0; i <= m; i++){
        x = i*h_x;
        printf("%.3d ", calculate_data(x,t,k));
    }
    printf("\n");
}





