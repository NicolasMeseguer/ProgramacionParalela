#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000

int main () {

	int memsize = N*sizeof(float);
	float *a = (float *) malloc (memsize);  
	float resultado =0.0f; 

	for (int i=0;i<N; ++i){
		a[i]=1.0f;
	}

	omp_set_num_threads(4); 

	#pragma omp parallel for reduction (+:resultado)
	for (int i=0;i<N; ++i) {
		resultado+= a[i];
	}

	printf ("%f",resultado);

	
	printf ("\n");
}






