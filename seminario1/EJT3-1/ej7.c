#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <unistd.h>

static long num_steps = 100000;

double step;

int main(){
	int i,numthreads=2; double x, pi, sum = 0.0, start;
	step = 1.0/(double) num_steps;
	
	start = omp_get_wtime();
	#pragma omp parallel for private (x,i) shared(step, num_steps)  reduction (+:sum) num_threads(numthreads)
		for(i=1;i<=num_steps;++i){
			x = (i-0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	sum=0.0;
	
	numthreads=4;
	start = omp_get_wtime();
	#pragma omp parallel for private (x,i) shared(step, num_steps)  reduction (+:sum) num_threads(numthreads)
		for(i=1;i<=num_steps;++i){
			x = (i-0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	sum=0.0;
	
	numthreads=6;
	start = omp_get_wtime();
	#pragma omp parallel for private (x,i) shared(step, num_steps)  reduction (+:sum) num_threads(numthreads)
		for(i=1;i<=num_steps;++i){
			x = (i-0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	sum=0.0;
	
	numthreads=8;
	start = omp_get_wtime();
	#pragma omp parallel for private (x,i) shared(step, num_steps)  reduction (+:sum) num_threads(numthreads)
		for(i=1;i<=num_steps;++i){
			x = (i-0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	printf("\n-------------------------------------------\nTiempo de ejecucion del programa con %i hilos: %lfs\n-------------------------------------------\n",numthreads,omp_get_wtime()-start);
	

	pi = step * sum;
	printf("\n%lf\n\n", pi);

	return 0;
}
