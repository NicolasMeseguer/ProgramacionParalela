#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <string.h>
#include <math.h>

#define TAM 7
#define TAMBLOCK 2

__global__ void sumaVectores(float *c, float *a, float *b, int *escalar){ //Kernel, salto a la GPU. Esta funcion es ejecutada por todos los hilos al mismo tiempo.
  	int i = blockIdx.x*blockDim.x+threadIdx.x; //Obtengo el indice para cada iteracion de la funcion sobre cada hilo
    if(i<TAM)
		  c[i]=(*(escalar)*a[i])+b[i];
}

void inicializarArrays(float *a, float *b){
	for(int i=0; i<TAM; ++i)
		a[i]=b[i]=(float)(rand()%50);
}

int main() {
	int memsize = sizeof(float)*TAM;
	
  /*HOST SIDE CPU & RAM*/
  //Arrays
  float *h_a,*h_b,*h_c;
	h_a=(float *)malloc(memsize);
	h_b=(float *)malloc(memsize);
	h_c=(float *)malloc(memsize);
  //Escalares
  int h_escalar=30;
  int aux_escalar;
  /**/

  //Inicializar valores arrays.
  inicializarArrays(h_a, h_b);  
  
  /*DEVICE SIDE GPU & GRAM*/
  //Arrays
  float *d_a,*d_b,*d_c;
  cudaMalloc(&d_a, memsize);
  cudaMalloc(&d_b, memsize);
  cudaMalloc(&d_c, memsize);
  //Escalares
  int *d_escalar;
  cudaMalloc((void**)&d_escalar, sizeof(int));

  //Envio el contenido de los arrays(h_a, h_b) CONTENIDO ! Al espacio de memoria ya reservado en la GPU(d_a, d_b). CPU -> GPU | Host -> Device
  cudaMemcpy(d_a, h_a, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_b, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_c, h_c, memsize, cudaMemcpyHostToDevice);//No haria falta puesto que h_c esta vacio pero bueno...
  cudaMemcpy(d_escalar, &h_escalar, sizeof(int), cudaMemcpyHostToDevice);

  /*Para comprobar que se ha copiado correctamente vamos a volver a traerlo a host y comprobar su valor mediante un printf.*/
  cudaMemcpy(&aux_escalar, d_escalar, sizeof(int), cudaMemcpyDeviceToHost); 

  int block = ceilf((float)TAM/TAMBLOCK);
  int thread = TAMBLOCK;
  printf("El numero de bloques es %d, y el numero de hilos es %d\n", block, thread);
  printf("El valor del escalar en HOST: %d, en DEVICE: %d\n", h_escalar, aux_escalar);
  sumaVectores <<<block,thread>>> (d_c, d_a, d_b, d_escalar);//El multiplicar ambos numeros tiene que darme N

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
