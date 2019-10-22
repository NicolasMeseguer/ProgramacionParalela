#include <stdio.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

#define LIMIT 2

int main(){
	float *A = (float *)malloc(ROW*COL*sizeof(float)); //Matriz creada
	float *B = (float *)malloc(ROW*COL*sizeof(float)); //2da Matriz, que usaremos para calcular valores.

	//Primero vamos a inicializar la matriz A, dandole valores
	for(int i=0; i<ROW; ++i)
		for(int j=0;j<COL;j++){
			if(i==0||i==ROW-1||j==0||j==COL-1)
				*(A+(i*ROW)+j)=150.0f;
			else
				*(A+(i*ROW)+j)=(float) (rand()%10);
		}

   	printf("Valor del array A - \n");
	 for(int i=0;i<ROW*COL;++i){
		printf("%f ,",*(A+i));
		if(i!=0 && (i+1)%5==0)
			printf("\n");
	}

	//Forma 2 Jacobi, extremos = 150 y solo sumo por el interior.
	for(int k=0; k<LIMIT;++k){
		#pragma omp parallel for num_threads(2)
		for(int i=1;i<(ROW-1);++i){
			for(int j=1;j<(COL-1);++j){
				int index = i*ROW+j;
				B[index]=A[index+1]+A[index-1]+A[index+ROW]+A[index-ROW];
			}
		}
		float *aux=A;
		A=B;
		B=aux;
	}

	//Este es el valor la matriz que contiene los valores anteriores.
	printf("\nValor del array: \n");
	for(int i=0;i<ROW*COL;++i){
		if(LIMIT%2==0)
			printf("%f ,",*(A+i));
		else
			printf("%f ,",*(B+i));
		if(i!=0 && (i+1)%5==0)
			printf("\n");
	}
}
