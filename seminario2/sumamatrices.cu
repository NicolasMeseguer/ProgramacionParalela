#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <string.h>
#include <math.h>

#define N 4 //Filas
#define M 4 //Columnas

__global__ void sumaMatrices(float *c, float *a, float *b){ //Kernel, salto a la GPU. Esta funcion es ejecutada por todos los hilos al mismo tiempo.
  int i = (blockIdx.y*blockDim.y+threadIdx.y)*N+(blockIdx.x*blockDim.x+threadIdx.x);
  c[i]=a[i]+b[i];
}

int main() {
	int memsize = sizeof(float )*N*M;
  float *h_a,*h_b,*h_c; //Arrays en el host (CPU & RAM)
	h_a=(float *)malloc(memsize);
	h_b=(float *)malloc(memsize);
	h_c=(float *)malloc(memsize);

  

  float *d_a,*d_b,*d_c; //Arrays en la GPU
  cudaMalloc(&d_a, memsize);
  cudaMalloc(&d_b, memsize);
  cudaMalloc(&d_c, memsize);

	for(int i=0; i<N*M; ++i)
		h_a[i]=h_b[i]=(float) i;

  cudaMemcpy(d_a, h_a, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_b, memsize, cudaMemcpyHostToDevice);
 
  dim3 block(2,2);
  dim3 thread(2,2); 
  printf("El numero de bloques es %d, y el numero de hilos es %d\n", block.x, thread.x);
  sumaMatrices <<<block,thread>>> (d_c, d_a, d_b);//El multiplicar ambos numeros tiene que darme N

  //Envio el contenido del array(d_c) CONTENIDO ! Al espacio de memoria ya reservado en la CPU(h_c). GPU -> CPU | Device -> Host
  cudaMemcpy(h_c, d_c, memsize, cudaMemcpyDeviceToHost);

	printf("Resultado del tercer vector, c: \n");
	for(int i=0; i<N*M; ++i){
		printf("%f, ", h_c[i]);
    if(i%N==0)
      printf("\n");
  }

	printf("\n");

  free(h_a);
  free(h_b);
  free(h_c);
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

	return 0;
}
