#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <string.h>
#include <math.h>

#define TAM 10
#define TAMBLOCK 2

__global__ void sumaVectores(float *b, float *a){ //Kernel, salto a la GPU. Esta funcion es ejecutada por todos los hilos al mismo tiempo.
  	int i = blockIdx.x*blockDim.x+threadIdx.x; //Obtengo el indice para cada iteracion de la funcion sobre cada hilo
    if(i<TAM && i!=0 && i!=TAM-1)
		  b[i]=(a[i-1]*a[i]*a[i+1])/3;
}

int main() {
	int memsize = sizeof(float)*TAM;
	
  float *h_a,*h_b; //Arrays en el host (CPU & RAM)
	h_a=(float *)malloc(memsize);
	h_b=(float *)malloc(memsize);

  float *d_a,*d_b; //Arrays en la GPU
  cudaMalloc(&d_a, memsize);
  cudaMalloc(&d_b, memsize);

	for(int i=0; i<TAM; ++i)
		h_a[i]=(float)(rand()%50);

  //Envio el contenido de los arrays(h_a, h_b) CONTENIDO ! Al espacio de memoria ya reservado en la GPU(d_a, d_b). CPU -> GPU | Host -> Device
  cudaMemcpy(d_a, h_a, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_a, memsize, cudaMemcpyHostToDevice);
    
  int block = ceilf((float)TAM/TAMBLOCK);
  int thread = TAMBLOCK;
  printf("El numero de bloques es %d, y el numero de hilos es %d\n", block, thread);
  sumaVectores <<<block,thread>>> (d_b, d_a);//El multiplicar ambos numeros tiene que darme N

  //Envio el contenido del array(d_c) CONTENIDO ! Al espacio de memoria ya reservado en la CPU(h_c). GPU -> CPU | Device -> Host
  cudaMemcpy(h_b, d_b, memsize, cudaMemcpyDeviceToHost);

	printf("Resultado del tercer vector, c: \n");
	for(int i=0; i<TAM; ++i)
		printf("%f, ", h_b[i]);

	printf("\n");

  free(h_a);
  free(h_b);
  cudaFree(d_a);
  cudaFree(d_b);
	return 0;
}
