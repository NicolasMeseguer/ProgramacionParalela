#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <string.h>
#include <math.h>

#define TAM 7
#define TAMBLOCK 2

__global__ void sumaVectores(float *c, float *a, float *b){ //Kernel, salto a la GPU. Esta funcion es ejecutada por todos los hilos al mismo tiempo.
  	int i = blockIdx.x*blockDim.x+threadIdx.x; //Obtengo el indice para cada iteracion de la funcion sobre cada hilo
    if(i<TAM)
		  c[i]=a[i]+b[i];
}

int main() {
	int memsize = sizeof(float)*TAM;
	
  float *h_a,*h_b,*h_c; //Arrays en el host (CPU & RAM)
	h_a=(float *)malloc(memsize);
	h_b=(float *)malloc(memsize);
	h_c=(float *)malloc(memsize);

  float *d_a,*d_b,*d_c; //Arrays en la GPU
  cudaMalloc(&d_a, memsize);
  cudaMalloc(&d_b, memsize);
  cudaMalloc(&d_c, memsize);

	for(int i=0; i<TAM; ++i)
		h_a[i]=h_b[i]=1.0f;

  /*ESTO NO FUNCIONA, UNA INSTRUCCION NO PUEDE ACCEDER A UN AREA DE MEMORIA DE UN PERIFERICO
  for(int i=0; i<TAM; ++i){
    *(d_a+i)=*(h_a+i);
    *(d_b+i)=*(h_b+i);
    *(d_c+i)=*(h_c+i);
  }
  */
  //Envio el contenido de los arrays(h_a, h_b) CONTENIDO ! Al espacio de memoria ya reservado en la GPU(d_a, d_b). CPU -> GPU | Host -> Device
  cudaMemcpy(d_a, h_a, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_b, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_c, h_c, memsize, cudaMemcpyHostToDevice);//No haria falta puesto que h_c esta vacio pero bueno...
  /**/
  
  int block = ceilf((float)TAM/TAMBLOCK);
  int thread = TAMBLOCK;
  printf("El numero de bloques es %d, y el numero de hilos es %d\n", block, thread);
  sumaVectores <<<block,thread>>> (d_c, d_a, d_b);//El multiplicar ambos numeros tiene que darme N

  //Envio el contenido del array(d_c) CONTENIDO ! Al espacio de memoria ya reservado en la CPU(h_c). GPU -> CPU | Device -> Host
  cudaMemcpy(h_c, d_c, memsize, cudaMemcpyDeviceToHost);

	printf("Resultado del tercer vector, c: \n");
	for(int i=0; i<TAM; ++i)
		printf("%f, ", h_c[i]);

	printf("\n");

  free(h_a);
  free(h_b);
  free(h_c);
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

	return 0;
}
