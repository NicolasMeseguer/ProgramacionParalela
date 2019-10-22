#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define TAM 1024

float* asignarMemoria(){
	float *a = (float *) malloc(sizeof(float)*TAM);
	return a;
}

void asignarValor(float *v){
	for(int i=0;i<TAM;++i)
		*(v+i)=1.0f;
}

int main() {
	double start;
	int numthreads;
	float *vector = asignarMemoria(), resultado=0.0f;
	asignarValor(vector);

	numthreads=2;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads) firstprivate(vector) reduction(+:resultado)
	for(int i=0; i<TAM; ++i){
		resultado += *(vector+i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	resultado=0;
	numthreads=4; 
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads) firstprivate(vector) reduction(+:resultado)
	for(int i=0; i<TAM; ++i){
		resultado += *(vector+i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	resultado=0;
	numthreads=6;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads) firstprivate(vector) reduction(+:resultado)
	for(int i=0; i<TAM; ++i){
		resultado+=*(vector+i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	resultado=0;
	numthreads=8;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads) firstprivate(vector) reduction(+:resultado)
	for(int i=0; i<TAM; ++i){
		resultado+=*(vector+i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	printf("\nResultado: %f", resultado);
	return 0;	
}
