#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

#define N 8 

__global__ void reduceVector(float *a, int thread){
  int id = blockIdx.x*blockDim.x+threadIdx.x;
  for(int s=N/2; s>=1; s/=2){
    if(id<s)
      *(a+id) += *(a+id+s);
    __syncthreads();
  }
}

int main() {
  int memsize = sizeof(float)*N;
  float *a =(float *) malloc(memsize);
  float *d_a;

  for(int i=0;i<N;++i){
    *(a+i)=(float)(rand()%10);
    printf("%f ,", *(a+i));
  }
  printf("\n");

  cudaMalloc(&d_a, memsize);
  cudaMemcpy(d_a, a, memsize, cudaMemcpyHostToDevice);

  int thread = (int) ceilf((double)N/2);
  reduceVector <<<1, thread>>> (d_a, thread);
    
  cudaMemcpy(a, d_a, memsize, cudaMemcpyDeviceToHost);
  printf("%f ,", *a);
  printf("\n\n");
  free(a);cudaFree(d_a);
}
