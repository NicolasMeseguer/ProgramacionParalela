#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#define TAM 4096

void rellenarArray(float *V){
	for(int i=0;i<TAM;++i)
		*(V+i)=100.0f;
}

int main() {
	int number;
	double start;

	float *a = (float *)malloc(sizeof(float)*TAM);
	float *b = (float *)malloc(sizeof(float)*TAM);
	float *c = (float *)malloc(sizeof(float)*TAM);
	
	#pragma omp parallel num_threads(2)
	{
		#pragma omp sections
		{
			#pragma omp section
				rellenarArray(a);
			#pragma omp section
				rellenarArray(b);
		}
	}

	//2 Hilos
	number=2;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(c+i)=*(a+i)+*(b+i);
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);



	//4 Hilos
	number=4;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(c+i)=*(a+i)+*(b+i);
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);



	//6 Hilos
	number=6;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(c+i)=*(a+i)+*(b+i);	
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);



	//8 Hilos
	number=8;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(c+i)=*(a+i)+*(b+i);
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);


	return 0;	
}
