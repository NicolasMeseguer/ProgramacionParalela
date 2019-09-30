#include <stdio.h>
#include <stdlib.h>

#define TAM 5

int main(){
	float *arrayvectores = (float *)malloc(sizeof(float)*TAM);
	float sumres;	

	printf("\n\nEjercicio 4, Calcular la suma de todos los elementos de un arraya...\n\n");
	
	printf("1) Primero rellenamos el array.\n");
	//Relleno el array de valores(float) introducidos por teclado y almaceno la suma.
	for(int i=0;i<TAM;++i){
		float *tempaddress = arrayvectores+i;
		printf("\nIntroduce un valor para la posicion %i: ", i+1);
		scanf("%f", tempaddress);
		sumres+=*(tempaddress);
	}

	//Algo de UX para que el usuario crea que realizamos la suma
	printf("\n2) Realizamos la suma de los valores del array...\n");

	//Printeo el resultado obtenido.
	printf("Resultado de la suma del vector: %f\n\n", sumres);
}
