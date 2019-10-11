#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

int main() {
	double start = omp_get_wtime();
	int A = 5, i;
	
	//PROGRAMA
	
	printf("\n\n\nCASO 1 - A, como variable privada !\n");
	#pragma omp parallel num_threads(4) private(A) //Variable A es privada a cada hilo y esta no esta inicializada, el valor que toma es aleatorio
	{
		printf("\nEl valor de A es: %i", A);
	}
	printf("\nFuera del paralelismo, el valor de A sigue siendo el mismo, no se ha modificado: %i", A);	
	
	printf("\n\n\nCASO 2 - A, como variable firstprivate !\n");
	#pragma omp parallel num_threads(4) firstprivate(A) //Variable A es privada a cada hilo pero se inicializa con el valor de A
	{
		printf("\nEl valor de A es: %i", A);
		A++;
	}
	printf("\nFuera del paralelismo, el valor de A sigue siendo el mismo: %i", A);

	
	printf("\n\n\nCASO 3 - A, como variable shared !\n");
	#pragma omp parallel num_threads(4) shared(A)
	{
		printf("\nEl valor de A es: %i", A);
		A++;
	}
	printf("\nFuera del paralelismo, como he modificado la A y es compartida por todos ellos, el valor ha aumentado: %i", A);
		
	printf("\n\n\nCASO 4 - i, como variable lastprivate !\n"); //La variable A es privada a la funcion, pero al acabar toma el último valor
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for lastprivate(i)
		for(i=0;i<8;++i)
			printf("\nIncrementamos el valor de la i en 1, %i", i);
	}
	printf("\nFuera del paralelismo, se puede acceder al valor de i con el ultimo valor tomado: %i",i);



	//FIN PROGRAMA

	printf("\n-------------------------------------------\nTiempo de ejecucion del programa %lfs\n-------------------------------------------\n", omp_get_wtime()-start);
	return 0;	
}
