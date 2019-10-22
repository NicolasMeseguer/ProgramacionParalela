#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define TAM 4000

void rellenarArray(float *M){
	#pragma omp parallel for schedule(guided) num_threads(4)
	for(int i=0;i<TAM;++i){
		*(M+i)=5.0f;
	}
}

//Se puede hacer con reduction(:+total) o pramga omp critical antes de la posicion de memoria a la que van a acceder todos los hilos.

int main() {
	int numthreads;float total=0.0f;double start;
	float *a=(float *)malloc(sizeof(float)*TAM);
	float *b=(float *)malloc(sizeof(float)*TAM);
	rellenarArray(a);rellenarArray(b);	

	printf("\nTamanyo de los vectores: %i\n", TAM);
	
	start = omp_get_wtime();numthreads=2;
	#pragma omp parallel for schedule(guided) num_threads(numthreads) reduction(+:total)
	for(int i=0;i<TAM;++i)	
		total+=*(a+i)*(*(b+i));
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos, %lfs\n-------------------------------------------\n",numthreads, omp_get_wtime()-start);
	total=0.0f;

	start = omp_get_wtime();numthreads=4;
	#pragma omp parallel for schedule(guided) num_threads(numthreads) reduction(+:total)
	for(int i=0;i<TAM;++i)
		total+=*(a+i)*(*(b+i));
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos, %lfs\n-------------------------------------------\n",numthreads, omp_get_wtime()-start);
	total=0.0f;

	start = omp_get_wtime();numthreads=6;
	#pragma omp parallel for schedule(guided) num_threads(numthreads) reduction(+:total)
	for(int i=0;i<TAM;++i)
		total+=*(a+i)*(*(b+i));
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos, %lfs\n-------------------------------------------\n",numthreads, omp_get_wtime()-start);
	total=0.0f;

	start = omp_get_wtime();numthreads=8;
	#pragma omp parallel for schedule(guided) num_threads(numthreads) reduction(+:total)
	for(int i=0;i<TAM;++i)
		total+=*(a+i)*(*(b+i));
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos, %lfs\n-------------------------------------------\n",numthreads, omp_get_wtime()-start);

	printf("\nResultado final, valor: %f\n", total);
	
	return 0;
}
