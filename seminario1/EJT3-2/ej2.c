#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define TAM 40

void rellenarArray(float *M){
	for(int i=0;i<TAM;++i)
		*(M+i)=5.0f;
}

int main() {
	double start;int numthreads=4;
	float *a = (float *)malloc(sizeof(float)*TAM);
	float *b = (float *)malloc(sizeof(float)*TAM);
	float *c = (float *)malloc(sizeof(float)*TAM);
	rellenarArray(a);rellenarArray(b);
	
	start = omp_get_wtime();
	#pragma omp parallel for schedule(static) num_threads(numthreads)
	for(int i=0;i<TAM;++i)
		*(c+i)=*(a+i)+*(b+i);
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos y schedule STATIC, %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	

	start = omp_get_wtime();
	#pragma omp parallel for schedule(dynamic) num_threads(numthreads)
	for(int i=0;i<TAM;++i)
		*(c+i)=*(a+i)+*(b+i);
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos y schedule DYNAMIC, %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	

	start = omp_get_wtime();
	#pragma omp parallel for schedule(guided) num_threads(numthreads)
	for(int i=0;i<TAM;++i)
		*(c+i)=*(a+i)+*(b+i);
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos y schedule GUIDED, %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	
	return 0;	
}
