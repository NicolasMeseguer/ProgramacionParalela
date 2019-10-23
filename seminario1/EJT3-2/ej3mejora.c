#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define TAM 4000
#define IT 10

void rellenarArray(float *M){
	#pragma omp parallel for schedule(guided)
	for(int i=0;i<TAM;++i){
		*(M+i)=5.0f;
	}
}

int main() {
	double start,tiempo2=0,tiempo4=0,tiempo6=0,tiempo8=0;float total=0.0f;int numthreads;
	float *a=(float *)malloc(sizeof(float)*TAM);
	float *b=(float *)malloc(sizeof(float)*TAM);
	rellenarArray(a);rellenarArray(b);	

	printf("\nTamanyo de los vectores: %i\n", TAM);
	omp_set_nested(1);
	#pragma omp paralel for schedule(guided) num_threads(4) reduction(+:tiempo2,+:tiempo4,+:tiempo6,+:tiempo8)
	for(int j=0;j<IT;++j){
		start = omp_get_wtime();numthreads=2;
		#pragma omp parallel for schedule(guided) reduction(+:total) num_threads(numthreads)
		for(int i=0;i<TAM;++i){
			total+=*(a+i)*(*(b+i));
		}
		if(j!=0 && j!=IT-1)
			tiempo2+=omp_get_wtime()-start;
		total=0.0f;
	
		start = omp_get_wtime();numthreads=4;
		#pragma omp parallel for schedule(guided) reduction(+:total) num_threads(numthreads)
		for(int i=0;i<TAM;++i){
			total+=*(a+i)*(*(b+i));
		}
		if(j!=0 && j!=IT-1)
			tiempo4+=omp_get_wtime()-start;
		total=0.0f;
	
		start = omp_get_wtime();numthreads=6;
		#pragma omp parallel for schedule(guided) reduction(+:total) num_threads(numthreads)
		for(int i=0;i<TAM;++i){
			total+=*(a+i)*(*(b+i));
		}
		if(j!=0 && j!=IT-1)
			tiempo6+=omp_get_wtime()-start;
		total=0.0f;
	
		start = omp_get_wtime();numthreads=8;
		#pragma omp parallel for schedule(guided) reduction(+:total) num_threads(numthreads)
		for(int i=0;i<TAM;++i){
			total+=*(a+i)*(*(b+i));
		}
		if(j!=0 && j!=IT-1)
			tiempo8+=omp_get_wtime()-start;
	}
	printf("\nTiempo medio con 2 hilos: %lfs", tiempo2/(IT-2));
	printf("\nTiempo medio con 4 hilos: %lfs", tiempo4/(IT-2));
	printf("\nTiempo medio con 6 hilos: %lfs", tiempo6/(IT-2));
	printf("\nTiempo medio con 8 hilos: %lfs", tiempo8/(IT-2));
	printf("\nResultado final, valor: %f\n", total);
	
	return 0;
}
