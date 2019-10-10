#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAM 8

int main() {
	float *a,*b,*c;
	int memsize = sizeof(float)*TAM;//Ahorramos dos multiplicaciones
	a=(float *)malloc(memsize);
	b=(float *)malloc(memsize);
	c=(float *)malloc(memsize);	

	for(int i=0; i<TAM; ++i)//Con ++i evitamos la creacion de un objeto nuevo
		a[i]=b[i]=1.0f;//Con 1.0f, obligamos explicitamente que la variable sea de punto flotante

	int id;
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		id=omp_get_thread_num(); //Alternativa a pragma omp for 
		for(int i=(id*2); i<((id*2)+2); ++i)
			c[i]=a[i]+b[i];
	}


	printf("Resultado del tercer vector, c: \n");
	for(int i=0; i<TAM; ++i)
		printf("%f, ", c[i]);

	printf("\n");

	return 0;
}
