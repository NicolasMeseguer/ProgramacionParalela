#include <stdio.h>
#include <omp.h>

int main(){
	int numthreads = omp_get_num_threads();
	int id = omp_get_thread_num();
	int count = 0;
	printf("Hilos en ejecucion: %i, su ID es: %i\n", numthreads, id); //Numero de hilos en ejecucion en esta funcion y el ID de dicho hilo
	printf("----------------------------------------------------\n");	
	//omp_set_num_threads(5); Establecer hilos maximos
	#pragma omp parallel shared(count) //Fork, el hilo comienza a dividirse 
	{
		numthreads = omp_get_num_threads(); //cada hilo tiene su variable privada, por eso entre ellas no se sbreescriben
		id = omp_get_thread_num(); //Privadas y Compartidas
		
		

		/*if(count==4){
			printf("Este es el quinto hilo en orden secuencial.\n");
			printf("Hilos en ejecucion: %i, su ID es: %i\n", numthreads, id);
		}
		count++;*/



		/*if(id == 5) //Hilo cuya ID es 5
			printf("Hilos en ejecucion: %i, su ID es: %i\n", numthreads, id); //Numero de hilos en ejecucion en esta funcion y el ID de dicho hilo*/



		printf("Hilos en ejecucion: %i, su ID es: %i\n", numthreads, id); //Numero de hilos en ejecucion en esta funcion y el ID de dicho hilo
	}

	numthreads = omp_get_num_threads();
	id = omp_get_thread_num();
	printf("----------------------------------------------------\n");	
	printf("Hilos en ejecucion: %i, su ID es: %i\n", numthreads, id); //Numero de hilos en ejecucion en esta funcion y el ID de dicho hilo
	
	return 0;
}
