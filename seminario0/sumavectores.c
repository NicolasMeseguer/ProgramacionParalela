#include <stdio.h>
#include <stdlib.h>

#define TAM 8

/*
*	Primer archivo de C orientado a Programacion Paralela, con buenos metodos.
*
*	Creacion de dos vectores y asignacion a un tercero que se mostrara por pantalla.
*
*	Codigo creado por Nicolas Meseguer.
*/

int main() {
	float *a,*b,*c;
	int memsize = sizeof(float)*TAM;//Ahorramos dos multiplicaciones
	a=(float *)malloc(memsize);
	b=(float *)malloc(memsize);
	c=(float *)malloc(memsize);

	for(int i=0; i<TAM; ++i)//Con ++i evitamos la creacion de un objeto nuevo
		a[i]=b[i]=1.0f;//Con 1.0f, obligamos explicitamente que la variable sea de punto flotante

	for(int i=0; i<TAM; ++i)
		c[i]=a[i]+b[i];

	printf("Resultado del tercer vector, c: \n");
	for(int i=0; i<TAM; ++i)
		printf("%f, ", c[i]);

	printf("\n");

	return 0;
}
