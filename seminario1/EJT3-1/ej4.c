#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#define TAM 1024

void rellenarArray(float *V){
	for(int i=0;i<TAM;++i)
		*(V+i)=100.0f;
}

int main() {
	int number;
	double start;

	float *x = (float *)malloc(sizeof(float)*TAM);
	float *y = (float *)malloc(sizeof(float)*TAM);
	float alpha=10;
	
	#pragma omp parallel num_threads(2)
	{
		#pragma omp sections
		{
			#pragma omp section
				rellenarArray(x);
			#pragma omp section
				rellenarArray(y);
		}
	}

	//2 Hilos
	number=2;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(y+i)=(*(x+i)*alpha)+*(y+i);
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);



	//4 Hilos
	number=4;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(y+i)=(*(x+i)*alpha)+*(y+i);
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);



	//6 Hilos
	number=6;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(y+i)=(*(x+i)*alpha)+*(y+i);
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);



	//8 Hilos
	number=8;
	start = omp_get_wtime();
	//PROGRAMA
	#pragma omp parallel for num_threads(number)
	for(int i=0; i<TAM; ++i)
		*(y+i)=(*(x+i)*alpha)+*(y+i);
	//FIN PROGRAMA
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",number,omp_get_wtime()-start);


	return 0;	
}
