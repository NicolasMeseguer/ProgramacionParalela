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
	float *vector = asignarMemoria();
	asignarValor(vector);

	numthreads=1;//Como hago realloc con dos hilos ? El array se me fopasdkasf
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads) firstprivate(vector)
	for(int i=TAM; i>=0; --i){
		vector = (float *) realloc(vector, i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);

	vector = asignarMemoria();asignarValor(vector);
	numthreads=1; 
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads)
	for(int i=TAM; i>=0; --i){
		vector = (float *) realloc(vector, i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	vector = asignarMemoria();asignarValor(vector);	
	numthreads=1;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads)
	for(int i=TAM; i>=0; --i){
		vector = (float *) realloc(vector, i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	vector = asignarMemoria();asignarValor(vector);	
	numthreads=1;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(numthreads)
	for(int i=TAM; i>=0; --i){
		vector = (float *) realloc(vector, i);
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	return 0;	
}
