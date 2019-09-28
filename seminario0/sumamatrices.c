#include <stdio.h>
#include <stdlib.h>

#define FILAS 5
#define COL 5

/*
*	Codigo sencillo para la suma de dos matrices dinamicas, el resultado se guarda en una 3ra.
*	La declaracion, asignacion y suma de valores se hacen de manera dinamica.
*	
*	El tamanyo de las FILAS y COLUMNAS se establece por defecto, otro modelo seria en el que el usuario lo introduce por teclado.
*	
*	Codigo desarrollado y escrito por Nicolas Meseguer Iborra.
*/

int main(){
	float **m1,**m2,**m3;
	m1 = (float **)malloc(sizeof(float *)*FILAS);
	m2 = (float **)malloc(sizeof(float *)*FILAS);
	m3 = (float **)malloc(sizeof(float *)*FILAS);
	
	//Asignacion de memoria
	float memsize = sizeof(float)*COL;

	for(int i=0;i<FILAS;++i)
		*(m1+i)=(float *)malloc(memsize);

	for(int i= 0; i<FILAS; ++i)
		*(m2+i)=(float *)malloc(memsize);

	for(int i= 0; i<FILAS; ++i)
		*(m3+i)=(float *)malloc(memsize);
		

	printf("\nYa hemos reservado memoria para nuestras matrices m1,m2,m3 !\n");

	//Asignacion de valores a las matrices dinamicas
	for(int i=0; i<FILAS; ++i){
		for(int j=0; j<COL; ++j){
			*(*(m1+i)+j)=3.0f;
			*(*(m2+i)+j)=2.0f;
			*(*(m3+i)+j)=(*(*(m1+i)+j))+(*(*(m2+i)+j));
		}
	}
	
	printf("Suma realizada con exito...\n");
	
	//Muestra de la matriz dinamica
	printf("Matriz dinamica :\n\n");
	for(int i=0; i<FILAS; ++i){
		for(int j=0; j<COL; ++j)
			printf("%f ", *(*(m3+i)+j));
		printf("\n");
	}

	printf("\n\n\n\n\n\n\n\n");
	return 0;
}
