#include <stdio.h>
#include <stdlib.h>

#define FILAS 5
#define COL 5

/*
*
*	Creacion de una matriz dinamica y posterior print para mostrarla por pantalla.
*
*	Codigo creado por Nicolas Meseguer Ibora
*/

int main(){
	float **matriz;
	matriz = (float **)malloc(sizeof(float *)*FILAS);
	
	//Asignacion de memoria
	float memsize = sizeof(float)*COL;
	for(int i=0;i<FILAS;++i)
		matriz[i]=(float *)malloc(memsize);

	printf("\nYa hemos reservado memoria para nuestra matriz !\n");

	//Asignacion de valores a la matriz dinamica
	for(int i=0; i<FILAS; ++i){
		for(int j=0; j<COL; ++j)
			matriz[i][j]=1.0f;
	}
	
	//Muestra de la matriz dinamica
	printf("Matriz dinamica :\n\n");
	for(int i=0; i<FILAS; ++i){
		for(int j=0; j<COL; ++j)
			printf("%f ", matriz[i][j]);
		printf("\n");
	}

	printf("\n\n\n\n\n\n\n\n");
	return 0;
}
