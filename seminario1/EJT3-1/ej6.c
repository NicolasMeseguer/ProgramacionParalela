#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

int main() {
	double start = omp_get_wtime();
	int threads = 5;
	printf("\nEstoy en el master thread, mi id es %i y ademas, solo hay %i hilo.", omp_get_thread_num(), omp_get_num_threads());
	//PROGRAMA
	printf("\n-------------------------------------------\nRegion paralela !\n-------------------------------------------");
	#pragma omp parallel num_threads(threads)
	{
		#pragma omp master
		{
				printf("\nHola, dentro de la region paralela, yo soy el Master Thread ! ID %i", omp_get_thread_num());
		}
		#pragma omp barrier
		if(omp_get_thread_num()!=0)
			printf("\nNo soy el master thread, pero mi ID es %i", omp_get_thread_num());	
	
	}
	//FIN PROGRAMA

	printf("\n-------------------------------------------\nTiempo de ejecucion del programa %lfs\n-------------------------------------------\n", omp_get_wtime()-start);
	return 0;	
}
