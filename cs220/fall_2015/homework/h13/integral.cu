/* File:     integral.cu
    Author:  Tim Siwula
 * Purpose:  Implement dot product on a gpu using cuda.  This version
 *           uses a binary tree reduction in which we attempt to reduce
 *           thread divergence.  It also uses shared memory to store
 *           intermediate results.  Assumes both threads_per_block and
 *           blocks_per_grid are powers of 2.
 *
 * Compile:  nvcc -arch=sm_21 -o integral integral.cu
 * Run:      ./integral <n> <a> <b> <blocks> <threads_per_block>
 *              n is the vector length
 *              i.e: ./integral 16 5 1 4 4
 * Input:    None
 * Output:   Result of dot product of a collection of random floats
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define MAX_BLOCK_SZ 512

__device__ float Dev_f(float x) {
         return x*x + 1;
      }

/*-------------------------------------------------------------------
 * Function:    Dev_dot  (kernel)
 * Purpose:     Implement a dot product of floating point vectors
 *              using atomic operations for the global sum
 * In args:     x, y, n
 * Out arg:     z
 *
 */
__global__ void Trap(float a[], float b[], float total[], int n) {
   /* Use tmp to store products of vector components in each block */
   /* Can't use variable dimension here                            */
   __shared__ float block_sum[MAX_BLOCK_SZ];
   int t = blockDim.x * blockIdx.x + threadIdx.x;
   int loc_t = threadIdx.x;
   float h = (b[t]-a[t])/n;
   int left = a[t] + (t * h);
   float right = left + h;
   float tmp_left = Dev_f(left);
   float tmp_right = Dev_f(right);
   float tmp_area = h * (tmp_left + tmp_right);
   float area = .5 * tmp_area;

   if (t < n) block_sum[loc_t] = area;
   __syncthreads();


   /* This uses a tree structure to do the addtions */
   for (int stride = blockDim.x/2; stride >  0; stride /= 2) {
      if (loc_t < stride)
         block_sum[loc_t] += block_sum[loc_t + stride];
      __syncthreads();
   }

   /* Store the result from this cache block in z[blockIdx.x] */
   if (threadIdx.x == 0) {
      total[blockIdx.x] = block_sum[0];
   }
}  /* Dev_dot */

/*-------------------------------------------------------------------
 * Function:  Dot_wrapper
 * Purpose:   CPU wrapper function for GPU dot product
 * Note:      Assumes x_d, y_d have already been
 *            allocated and initialized on device.  Also
 *            assumes z_d has been allocated.
 */
float Dot_wrapper(float a_d[], float b_d[], float total_d[],
      int n, int blocks, int threads) {
   int i;
   float integral = 0.0;
   float total_h[blocks];

   /* Invoke kernel */
   Trap<<<blocks, threads>>>(a_d, b_d, total_d, n);
   cudaThreadSynchronize();

   cudaMemcpy(total_h, total_d, blocks*sizeof(float), cudaMemcpyDeviceToHost);

   for (i = 0; i < blocks; i++)
      integral += total_h[i];
   return integral;
}  /* Dot_wrapper */


/*-------------------------------------------------------------------
 * Host code
 */
void Get_args(int argc, char* argv[], int* n_p, int* a_p, int* b_p, int* threads_per_block_p,
      int* blocks_per_grid_p);
void Setup(int n, int a, int b, int blocks, float** x_h_p, float** y_h_p, float** x_d_p,
      float** y_d_p, float** z_d_p);
float Serial_dot(float x[], float y[], int n);
void Free_mem(float* x_h, float* y_h, float* x_d, float* y_d,
      float* z_d);
float Dot_wrapper(float x_d[], float y_d[], float z_d[],
      int n, int blocks, int threads);

/*-------------------------------------------------------------------
 * main
 */
int main(int argc, char* argv[]) {
   int n, a, b, threads_per_block, blocks_per_grid;
   float *a_h, *b_h, integral = 0;
   float *a_d, *b_d, *total_d;
   double start, finish;  /* Only used on host */

   Get_args(argc, argv, &n, &a, &b, &threads_per_block, &blocks_per_grid);
   Setup(n, a, b, blocks_per_grid, &a_h, &b_h, &a_d, &b_d, &total_d);

   GET_TIME(start);
   integral = Dot_wrapper(a_d, b_d, total_d, n, blocks_per_grid,
         threads_per_block);
   GET_TIME(finish);

   printf("The integral as computed by cuda is: %e\n", integral);
   printf("Elapsed time for cuda = %e seconds\n", finish-start);


   Free_mem(a_h, b_h, total_d, b_d, total_d);

   return 0;
}  /* main */


/*-------------------------------------------------------------------
 * Function:  Get_args
 * Purpose:   Get and check command line args.  If there's an error
 *            quit.
 */
void Get_args(int argc, char* argv[], int* n_p, int* a_p, int* b_p, int* threads_per_block_p,
      int* blocks_per_grid_p) {

   if (argc != 6) {
      fprintf(stderr, "usage: %s <n> <a> <b> <blocks> <threads>\n",
            argv[0]);
      exit(0);
   }
   *n_p = strtol(argv[1], NULL, 10);
   *a_p = strtol(argv[2], NULL, 10);
   *b_p = strtol(argv[3], NULL, 10);
   *blocks_per_grid_p = strtol(argv[4], NULL, 10);
   *threads_per_block_p = strtol(argv[5], NULL, 10);
}  /* Get_args */

/*-------------------------------------------------------------------
 * Function:  Setup
 * Purpose:   Allocate and initialize host and device memory
 */
void Setup(int n, int a, int b, int blocks, float** a_h_p, float** b_h_p, float** a_d_p,
      float** b_d_p, float** total_d_p) {
   int i;
   size_t size = n*sizeof(float);

   /* Allocate input vectors in host memory */
   *a_h_p = (float*) malloc(size);
   *b_h_p = (float*) malloc(size);

   /* Initialize input vectors */
   srandom(1);
   for (i = 0; i < n; i++) {
      (*a_h_p)[i] = random()/((double) RAND_MAX);
      (*b_h_p)[i] = random()/((double) RAND_MAX);
   }

   /* Allocate vectors in device memory */
   cudaMalloc(a_d_p, size);
   cudaMalloc(a_d_p, size);
   cudaMalloc(total_d_p, blocks*sizeof(float));

   /* Copy vectors from host memory to device memory */
   cudaMemcpy(*a_d_p, *a_h_p, size, cudaMemcpyHostToDevice);
   cudaMemcpy(*b_d_p, *b_h_p, size, cudaMemcpyHostToDevice);
}  /* Setup */

/*-------------------------------------------------------------------
 * Function:  Serial_dot
 * Purpose:   Compute a dot product on the cpu
 */
float Serial_dot(float x[], float y[], int n) {
   int i;
   float dot = 0;

   for (i = 0; i < n; i++)
      dot += x[i]*y[i];

   return dot;
}  /* Serial_dot */

/*-------------------------------------------------------------------
 * Function:  Free_mem
 * Purpose:   Free host and device memory
 */
void Free_mem(float* x_h, float* y_h, float* x_d, float* y_d,
      float* z_d) {

   /* Free device memory */
   cudaFree(x_d);
   cudaFree(y_d);
   cudaFree(z_d);

   /* Free host memory */
   free(x_h);
   free(y_h);

}  /* Free_mem */
