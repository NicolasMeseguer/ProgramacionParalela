#include <stdio.h>
#include <stdlib.h>

#define TAM 4

void init(float *a, float value){
	for(int i=0;i<TAM;++i)
		*(a+i)=value;
}

int main() {

	float *a = (float *) malloc(sizeof(float)*TAM);
	float *b = (float *) malloc(sizeof(float)*TAM);
	float *c = (float *) malloc(sizeof(float)*TAM);
	int temp=0;
	
	init(a,4.0f);init(b,2.0f);

	#pragma omp parallel for shared(temp) ordered
	for(int i=0; i<TAM; ++i){
		#pragma omp ordered
		{
			temp+= *(a+i)/(*(b+i));
			*(c+i) = temp+temp*temp;
		}
	}

	printf("\n");
	for(int i=0;i<TAM;++i)
		printf("%f ,",*(c+i));
	printf("\n");
}
