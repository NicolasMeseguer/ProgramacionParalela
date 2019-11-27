#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <string.h>
#include <math.h>

#define TAM 8
#define NITERACIONES 40
#define TAMBLOCK 2

__global__ void stencil(float *a, float *b){ //Kernel, salto a la GPU. Esta funcion es ejecutada por todos los hilos al mismo tiempo.
  int i = blockIdx.x*blockDim.x+threadIdx.x+1;
  b[i]=(a[i-1]+a[i]+a[i+1])/3;
}

int main() {
	int memsize = sizeof(float)*TAM;
  float *h_a,*h_b; //Arrays en el host (CPU & RAM)
	h_a=(float *)malloc(memsize);
	h_b=(float *)malloc(memsize);

  for(int i=0;i<TAM;++i){
    h_a[i]=h_b[i]=(float)(rand()%20);
  }

  float *d_a,*d_b; //Arrays en la GPU
  cudaMalloc(&d_a, memsize);
  cudaMalloc(&d_b, memsize);

  cudaMemcpy(d_a, h_a, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_b, memsize, cudaMemcpyHostToDevice);
 
  dim3 block((TAM-2)/TAMBLOCK);
  dim3 thread(TAMBLOCK); 
  printf("El numero de bloques es %d, y el numero de hilos es %d\n", block.x, thread.x);
  for(int j=0;j<NITERACIONES;++j){
    stencil <<<block,thread>>> (d_a, d_b);
    cudaThreadSynchronize();
    float *aux=d_b;
    d_b=d_a;
    d_a=aux;
  }

  cudaMemcpy(h_a, d_a, memsize, cudaMemcpyDeviceToHost);
  cudaMemcpy(h_b, d_b, memsize, cudaMemcpyDeviceToHost);

  printf("Vector A:\n");
  for(int i=0;i<TAM;++i)
    printf("%f, ", *(h_a+i));
  
  printf("\n\nVector B:\n");
  for(int i=0;i<TAM;++i)
    printf("%f, ", *(h_b+i));
  printf("\n");

  free(h_a);
  free(h_b);
  cudaFree(d_a);
  cudaFree(d_b);
	return 0;
}
