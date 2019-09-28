#include <stdio.h>
#include <stdlib.h>

/*
*	Codigo basico con la implementacion de un hola mundo y la peitcion al usuario de un numero que se mostrara por pantalla.
*/

int main() {

	printf("Nuestro primer hola mundo !!\n");

	int a;
	printf("Introduce un numero del 1-10: ");
	scanf("%i",&a);
	printf("\nHas introducido el - %i\n\n\n", a);
	return 0;
}
