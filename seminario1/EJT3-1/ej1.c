#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

int main() {
	double start = omp_get_wtime();

	//PROGRAMA
	int threads;
	printf("\nIntroduce el numero de hilos a ejecutar: ");fflush(stdin);scanf("%i", &threads);
	printf("\nEstamos ejecutando %i hilo\n", omp_get_num_threads()); //Como aun no hemos entrado, el num de hilos es 1
	#pragma omp parallel num_threads(threads) //A partir de aqui, hace fork, y salen X hilos
	{
		#pragma omp single //Se ejecuta unicamente en 1 hilo
		printf("\nRegion en paralelo hay %i hilos", omp_get_num_threads());

		int id = omp_get_thread_num();
		printf("\nMi ID de hilo es %i", id);
		
	}
	//FIN PROGRAMA

	printf("\n-------------------------------------------\nTiempo de ejecucion del programa %lfs\n-------------------------------------------\n", omp_get_wtime()-start);
	return 0;	
}
