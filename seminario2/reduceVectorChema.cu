#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#define N 8

__global__ void reduceVector (float *d_a) {


  int i = blockIdx.x*blockDim.x+threadIdx.x; 

  d_a[i] = d_a[i] + d_a[i+(N/2)];
  __syncthreads();
  if (threadIdx.x<(blockDim.x/2))
    d_a[i] = d_a[i] +d_a[i+(N/4)];
  __syncthreads(); 
  if (threadIdx.x<(blockDim.x/4))
    d_a[i] = d_a[i] +d_a[i+(N/8)];
}

int main () {

	int memsize = N*sizeof(float);
	float *a = (float *) malloc (memsize);  
	float resultado =0.0f; 
  float *d_a; 
  cudaMalloc (&d_a, memsize);
 

	for (int i=0;i<N; ++i){
		a[i]=1.0f;
	}

  cudaMemcpy (d_a, a, memsize, cudaMemcpyHostToDevice);
	dim3 block (1);
  dim3 thread (N/2);

  reduceVector<<< block, thread>>> (d_a); 

  cudaMemcpy (&resultado,d_a, sizeof(float), cudaMemcpyDeviceToHost);

	printf ("%f",resultado);

	
	printf ("\n");
}






