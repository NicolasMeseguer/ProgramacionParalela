#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int obtenerMenor(int *a, int tam){
	int res = 0;
	int i;
	#pragma omp parallel for num_threads(4) private(i) reduction(+:res)
	for(i=0;i<tam;++i)
		res+=*(a+i);
	res*=-1;
	return res;
}

int main() {
	printf("Probando, esto funciona !");
	int *a = (int *)malloc(sizeof(int)*20);
	for(int i=0;i<20;++i)
		*(a+i)=rand()%20;
	int res = obtenerMenor(a, 20);
	printf("La resta de todos los elementos es %i\n\n.", res);
}
