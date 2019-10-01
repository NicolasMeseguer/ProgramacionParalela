#include <stdio.h>
#include <stdlib.h>

#define FILAS 5
#define COLUMNAS 5

int main(){
	float *matriz;
	matriz = (float *)malloc(sizeof(float)*FILAS*COLUMNAS);
	
	/*//Una forma de rellenarlo
	for(int i=0;i<FILAS*COLUMNAS;++i)
		*(matriz+i)=(float)(rand()%50);
	*/
	
	//Otra forma de rellenar el array como si fuese de dos dimensiones, pero recordemos que es una matriz unidemimensional !
	for(int i=0; i<FILAS; ++i)	
		for(int j=0; j<COLUMNAS; ++j)
			*(matriz+((i*FILAS)+j))=(float)(rand()%50);
	
	printf("\n");
	for(int i=0; i<FILAS*COLUMNAS; ++i)
		printf("%f ,", *(matriz+i));
}	
