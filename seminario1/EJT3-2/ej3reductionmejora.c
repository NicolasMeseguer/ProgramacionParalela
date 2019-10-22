#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1024

int main () {

	int memsize = N*sizeof(float);
	float *a = (float *) malloc (memsize);  
	float *b = (float *) malloc (memsize);

	for (int i=0;i<N; ++i){
		a[i]=b[i]=1.0f;
	}
	
	int numthreads=4;
	omp_set_num_threads(numthreads);
	float *mem = (float*) malloc(sizeof(float)*numthreads),result=0.0f;
	#pragma omp parallel for 
	for (int i=0;i<N; ++i) {
		*(mem+omp_get_thread_num())+= *(a+i)*(*(b+i));
	}
	for(int i=0;i<numthreads;++i)
		result+=*(mem+i);

	printf ("%f, ", result);

	printf ("\n");
}






