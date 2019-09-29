#include <stdio.h>
#include <stdlib.h>

#define TAM 20

/*
*	Metodo Stencil de para un array sencillo
*	
*	
*	Codigo por Nicolas Meseguer
*/

int main(){
	//Asignacion de tamaño
	float *A = (float *) malloc(sizeof(float)*TAM);
	
	//Asignacion de valores y muestra por pantalla
	printf("\n\n\nArray de valores resultante: \n");
	for(int i=0; i<TAM; ++i){
		*(A+i)=(float)(rand()%50);
		printf("%f - ", *(A+i));
	}

	printf("\n\n\nAplicamos el patron Stencil... \n");
	
	//Aplicamos el metodo Stencil como en el ejercicio dado...
	printf("Nuevo array de valores: \n\n");
	for(int i=0; i<TAM; ++i){
		printf("%f + %f + %f = ", *(A+i-1), *(A+i), *(A+i+1));
		*(A+i)=(float)((*(A+i-1))+(*(A+i))+(*(A+i+1)));
		printf("%f\n", *(A+i));
	}
	
	printf("\n\n\n");

	return 0;
}
