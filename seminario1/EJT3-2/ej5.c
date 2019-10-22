#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define MTAM 1000
#define VTAM 1000

void rellenarMatriz(float *M){
	#pragma omp parallel for schedule(guided)
	for(int i=0;i<(MTAM*MTAM);++i)
		*(M+i)=5.0f;
}

void rellenarVector(float *V){
	#pragma omp parallel for schedule(guided)
	for(int i=0;i<VTAM;++i)
		*(V+i)=5.0f;
}

int main() {
	double start;

	float *matriz = (float *)malloc(sizeof(float)*MTAM*MTAM);
	float *vector = (float *)malloc(sizeof(float)*VTAM);
	float *vectorresultado = (float *)malloc(sizeof(float)*VTAM);
	rellenarMatriz(matriz);rellenarVector(vector);

	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(4)
	for(int i=0; i<VTAM;++i) {
		*(vectorresultado+i)=0.0f;
		for(int j=0;j<VTAM;++j){
			*(vectorresultado+i)+=*(vector+j)*(matriz[i*MTAM+j]);
		}
	}
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa %lfs\n-------------------------------------------\n", omp_get_wtime()-start);
	return 0;	
}
