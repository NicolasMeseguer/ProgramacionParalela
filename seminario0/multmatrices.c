#include <stdio.h>
#include <stdlib.h>

#define M 5
#define N 5

void rellenarMatriz(float *A, float *B){ 
	for(int i=0;i<(M*N);++i){
		*(A+i)=(float)(rand()%20);
		*(B+i)=(float)(rand()%50);
	}
}

void mostrarMatriz(float *A){
	for(int i=0;i<(M*N);++i){
		printf("%f", *(A+i));
		if((i+1)%N==0)
			printf("\n");
		else
			printf(" ,");
	}
}

void multiplicarMatriz(float *A, float *B, float *C){
	if(M!=N){
		printf("\nLas matrices no se pueden multiplicar...\n");
		C=NULL;
		return;
	}
	
	int tam = N;

	for(int i=0;i<M;++i){
		for(int j=0;j<N;++j){
			float res=0;
			for(int k=0; k<tam;++k){
				res+=(*(A+(i*M)+k))*(*(B+(M*k)+j));
			}
			*(C+(i*M)+j)=res;
		}
	}
}

int main() {
	int memsize = sizeof(float)*M*N;
	float *A = (float *)malloc(memsize);
	float *B = (float *)malloc(memsize);
	float *C = (float *)malloc(memsize);

	printf("\nDamos valor a las matrices...\n");

	rellenarMatriz(A, B);
	
	printf("\nMatriz A: \n");
	mostrarMatriz(A);

	printf("\nMatriz B: \n");
	mostrarMatriz(B); 
	
	multiplicarMatriz(A,B,C);

	printf("\nResultado matriz C:\n");
	mostrarMatriz(C);
	printf("\n\n\n");
}

