#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

//OpenMP asignara un hilo distinto a cada section, si tenemos dos siempre asignara el hilo 1 a 1 section y el 2 a otra section

void tarea_uno(){
	float contador=0.0f;
	for(int i=0;i<100;++i)
		contador*=i;
}

void tarea_dos(){
	int a[10], b[10];
	for(int i=0;i<10;++i)
		b[i]=a[i]=(int) 2;

	for(int i=0;i<10;++i)
		b[i]=a[i]*i;
}


int main() {
	int number =10;double start;
	#pragma omp parallel num_threads(number) private(start)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				printf("\nLlamando a tarea 1!");
				start = omp_get_wtime();
				tarea_uno();
				printf("\n-------------------------------------------\nTiempo de ejecucion en el hilo %i, %lfs\n-------------------------------------------\n",omp_get_thread_num(), omp_get_wtime()-start);
			}
			#pragma omp section
			{
				printf("\nLlamando a tarea 2!");
				start = omp_get_wtime();
				tarea_dos();
				printf("\n-------------------------------------------\nTiempo de ejecucion en el hilo %i, %lfs\n-------------------------------------------\n",omp_get_thread_num(), omp_get_wtime()-start);
			}
		}
	
	}
	return 0;	
}
