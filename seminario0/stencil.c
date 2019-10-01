#include <stdio.h>
#include <stdlib.h>

#define TAM 20
#define NUM_ITER 100

/*
*	Metodo Stencil de para un array sencillo
*	
*	
*	Codigo por Nicolas Meseguer
*/

int main(){
	//Asignacion de tamaño
	float *A = (float *) malloc(sizeof(float)*TAM);
	float *B = (float *) malloc(sizeof(float)*TAM);	
	int temp;	

	//Asignacion de valores y muestra por pantalla
	printf("\n\n\nArray de valores resultante: \n");
	for(int i=0; i<TAM; ++i){
		*(A+i)=(float)(rand()%50);
		printf("%f - ", *(A+i));
	}

	printf("\n\n\nAplicamos el patron Stencil... \n");
	
	//Aplicamos el metodo Stencil como en el ejercicio dado...
	printf("Nuevo array de valores: \n\n");
	*B = *A;
	temp = TAM-1;
	*(B+temp) = *(A+temp);

	for(int j=0; j<NUM_ITER; ++j){
		printf("\nIteracion %i: \n\n", j+1);
		for(int i=1; i<TAM-1; ++i){
			printf("%f + %f + %f = ", *(A+i-1), *(A+i), *(A+i+1));
			*(B+i)=(float)((*(A+i-1))+(*(A+i))+(*(A+i+1))*0.3);
			printf("%f\n", *(B+i));
		}
		//Intercambio los punteros para ejecutarlo infinitamente
		float *aux = A;
		A = B;
		B = aux;
	}

	//Resultado...
	printf("Resultado tras aplicar Stencil...\n");
	for(int i=0;i<TAM;++i)
		printf("%f ,", *(B+i));
	
	printf("\n\n\n");

	return 0;
}
