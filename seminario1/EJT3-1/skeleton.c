nclude <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

int main() {
	double start = omp_get_wtime();

	//PROGRAMA
	sleep(5);
	//FIN PROGRAMA

	printf("\n-------------------------------------------\nTiempo de ejecucion del programa %lfs\n-------------------------------------------\n", omp_get_wtime()-start);
	return 0;	
}
