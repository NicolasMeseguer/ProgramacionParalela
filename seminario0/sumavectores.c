#include <stdio.h>

#define TAM 8

int main() {
	float *a,*b,*c;
	int memsize = sizeof(flaot)*TAM;//Ahorramos dos multiplicaciones
	a=(float *)malloc(memsize);
	b=(float *)malloc(memsize);
	c=(float *)malloc(memsize);

	for(int i=0; i<TAM; ++i)//Con ++i evitamos la creacion de un objeto nuevo
		a[i]=b[i]=c[i]=1.0f;//Con 1.0f, obligamos explicitamente que la variable sea de punto flotante

	for(int i=0; i<TAM; ++i)
		c[i]=a[i]+b[i];

	printf("Resultado del tercer vector: ");
	for(inti=0; i<TAM; ++i)
		printf("%f", c[i]);

	return 0;
}
