#include <stdio.h>
#include <stdlib.h>

int M1F, M1C, M2F, M2C;

void rellenarMatriz(float *A, int M, int N){
	for(int i=0;i<(M*N);++i)
		*(A+i)=(float)(rand()%20);
}

void mostrarMatriz(float *A, int M, int N){
	for(int i=0;i<(M*N);++i){
		printf("%f", *(A+i));
		if((i+1)%N==0)
			printf("\n");
		else
			printf(", ");
	}
}

void multiplicarMatriz(float *A, float *B, float *C, int M, int N, int tam){
	for(int i=0;i<M;++i){
		for(int j=0;j<N;++j){
			float res=0;
			for(int k=0; k<tam;++k)
				res+=(*(A+(i*tam)+k))*(*(B+(N*k)+j));
			*(C+(i*N)+j)=(float) res;
		}
	}
}

int main() {
	printf("\nMatriz 1 - Filas : ");fflush(stdin);scanf("%i", &M1F);
	printf("\nMatriz 1 - Columnas : ");fflush(stdin);scanf("%i", &M1C);
	printf("\nMatriz 2 - Filas : ");fflush(stdin);scanf("%i", &M2F);
	printf("\nMatriz 2 - Columnas : ");fflush(stdin);scanf("%i", &M2C);

	if(M1C != M2F){
		printf("\nNo se puede realizar la multiplicacion, M1 Columnas != M2 Filas\n");
		return 0;
	}

	float *A = (float *)malloc(sizeof(float)*M1F*M1C);
	float *B = (float *)malloc(sizeof(float)*M2F*M2C);
	float *C = (float *)malloc(sizeof(float)*M1F*M2C);

	printf("\nDamos valor a las matrices...\n");

	rellenarMatriz(A, M1F, M1C);
	rellenarMatriz(B, M2F, M2C);

	printf("\nMatriz A: \n");
	mostrarMatriz(A, M1F, M1C);

	printf("\nMatriz B: \n");
	mostrarMatriz(B, M2F, M2C);

	multiplicarMatriz(A,B,C,M1F,M2C, M1C);

	printf("\nResultado matriz C:\n");
	mostrarMatriz(C,M1F,M2C);
	free(A);free(B);free(C);
	printf("\n\n\n");
}

