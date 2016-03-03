/* File:     matrix_addition.cu
 * Purpose:  Implement vector addition on a gpu using cuda
 *
 * Compile:  nvcc [-g] [-G] -arch=sm_21 -o vec_add vec_add.cu
 * Run:      ./vec_add <n>
 *              n is the vector length
 *
 * Input:    None
 * Output:   Result of vector addition.  If all goes well it should
 *           be a vector consisting of n copies of n+1.
 *
 * Notes:
 * 1.  CUDA is installed on all of the machines in HR 530, HR 235, and
 *     and LS G12
 * 2.  If you get something like "nvcc: command not found" when you try
 *     to compile your program.  Type the following command
 *
 *           $ export PATH=/usr/local/cuda/bin:$PATH
 *
 *     (As usual the "$" is the shell prompt:  just type the rest
 *     of the line.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Kernel for vector addition */
__global__ void Mat_add(float A[], float B[], float C[], int m, int n) {
   /* blockDim.x = threads_per_block                            */
   /* First block gets first threads_per_block components.      */
   /* Second block gets next threads_per_block components, etc. */
   int my_ij = blockDim.x * blockIdx.x + threadIdx.x;

   /* The test shouldn't be necessary */
   if (blockIdx.x < m && threadIdx.x < n)
      C[my_ij] = A[my_ij] + B[my_ij];
}

/* Host code */
int main(int argc, char* argv[]) {
   int n, i, m;
   float *h_x, *h_y, *h_z;
   float *d_x, *d_y, *d_z;
   int threads_per_block;
   int block_count;
   size_t size;

   /* Get number of components in vector */
   if (argc != 2) {
      fprintf(stderr, "usage: %s <vector order>\n", argv[0]);
      exit(0);
   }
   m = strtol(argv[1], NULL, 10);
   n = strtol(argv[1], NULL, 10);
   printf("m = %d, n = %d\n", m, n);
   size = m*n*sizeof(float);

   /* Allocate input vectors in host memory */
   h_x = (float*) malloc(size);
   h_y = (float*) malloc(size);
   h_z = (float*) malloc(size);

    printf("Enter the matrices A and B\n");
    Read_matrix(h_x, m, n);
    Read_matrix(h_y, m, n);

     Print_matrix("A =", h_x, m, n);
     Print_matrix("B =", h_y, m, n);

   /* Allocate vectors in device memory */
   cudaMalloc(&d_x, size);
   cudaMalloc(&d_y, size);
   cudaMalloc(&d_z, size);

   /* Copy vectors from host memory to device memory */
   cudaMemcpy(d_x, h_x, size, cudaMemcpyHostToDevice);
   cudaMemcpy(d_y, h_y, size, cudaMemcpyHostToDevice);


   /* Invoke kernel using block_count blocks, each of which  */
   /* contains threads_per_block threads                     */
   Mat_add<<<i, n>>>(d_A, d_B, d_C, m, n);

   /* Wait for the kernel to complete */
   cudaThreadSynchronize();

   /* Copy result from device memory to host memory */
   /* h_z contains the result in host memory        */
   cudaMemcpy(h_z, d_z, size, cudaMemcpyDeviceToHost);


   Print_matrix("The sum is: ", h_z, m, n);

   /* Free device memory */
   cudaFree(d_x);
   cudaFree(d_y);
   cudaFree(d_z);

   /* Free host memory */
   free(h_x);
   free(h_y);
   free(h_z);

   return 0;
}  /* main */

void Read_matrix(float A[], int m, int n) {
   int i, j;

   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         scanf("%f", &A[i*n+j]);
}

void Print_matrix(char title[], float A[], int m, int n) {
   int i, j;

   printf("%s\n", title);
   for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++)
         printf("%.1f ", A[i*n+j]);
      printf("\n");
   }
}
