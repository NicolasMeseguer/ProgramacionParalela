#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define TAM 100

void asignarValores(float *v){
	for(int i=0;i<TAM;++i)
		*(v+i)=rand()%1000;
}

void obtenerMayor(float *v) {
	float res=0;
	#pragma omp parallel for firstprivate(res) lastprivate(res)
	for(int i=0;i<TAM;++i){
		#pragma omp critical
		{
			if(*(v+i)>res)
				res = *(v+i);
		}
	}
	printf("\nEl valor mas grande del vector es: %f", res);
}

void obtenerMenor(float *v) {
	float res=10000;
	#pragma omp parallel for firstprivate(res) lastprivate(res)
	for(int i=0;i<TAM;++i){
		#pragma omp critical
		{
			if(*(v+i)<res)
				res = *(v+i);
		}
	}
	printf("\nEl valor mas pequenyo del vector es: %f", res);
}

int main() {
	float *v = (float *)malloc(sizeof(float)*TAM);
	asignarValores(v);
	double start = omp_get_wtime();
	#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section
		{
			obtenerMayor(v);
		}
		#pragma omp section
		{
			obtenerMenor(v);
		}
	}
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa %lfs\n-------------------------------------------\n", omp_get_wtime()-start);
	return 0;	
}
