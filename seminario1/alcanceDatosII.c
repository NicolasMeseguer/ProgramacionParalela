#include <stdio.h>
#include <stdlib.h>

#define TAM 4

void init(float *a, float value){
	for(int i=0;i<TAM;++i)
		*(a+i)=1.0f;
}

int main() {
	int memsize = sizeof(float)*TAM;
	float *a = (float *) malloc(memsize);
	float *b = (float *) malloc(memsize);
	float *c = (float *) malloc(memsize);
	float cons=2.0f;
	
	init(a);init(b);init(c);

	#pragma omp parallel for lastprivate(cons)
	for(int i=0; i<TAM; ++i){
		cons+=1;
	}
	
	printf("%f", cons);
	printf("\n");
}
