#include <stdio.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

#define LIMIT 5

int main(){
	float *A = (float *)malloc(ROW*COL*sizeof(float)); //Matriz creada
	float *B = (float *)malloc(ROW*COL*sizeof(float)); //2da Matriz, que usaremos para calcular valores.

	//Primero vamos a inicializar la matriz A, dandole valores
	for(int i=0; i<ROW; ++i)
		for(int j=0;j<COL;j++)
			*(A+(i*ROW)+j)=(float) (rand()%10);

    printf("Valor del array A - \n");
    for(int i=0;i<ROW*COL;++i){
		printf("%f ,",*(A+i));
		if(i!=0 && (i+1)%5==0)
			printf("\n");
	}

	//Aplicamos Jacobi a nuestra matriz
	for(int k=0; k<LIMIT; ++k){
        printf("\n\nIteracion %i: \n", k);
		for(int i=0; i<ROW; ++i){
			for(int j=0; j<COL; ++j){

                float ij = *(A+(ROW*i)+j);
                float j1,j2,i1,i2;

                //Si estoy en la ultima columna de la fila ? El siguiente puntero vale 0
                if(j==(COL-1))
                    j1 = 0.0;
                else
                    j1 = *(A+(ROW*i)+j+1);

                //Si estoy en la primera columna de la fila ? El puntero anterior vale 0
                if(j==0)
                    j2 = 0.0;
                else
                    j2 = *(A+(ROW*i)+j-1);
				
		//Si estoy en la ultima fila ? El siguiente valor 0
                if(i==(ROW-1))
                    i1 = 0.0;
                else
                    i1 = *(A+(ROW*(i+1))+j);

		//Si estoy en la primera fila ? El valor anterior vale 0
                if(i==0)
                    i2 = 0.0;
                else
                    i2 = *(A+(ROW*(i-1))+j);


                printf("\n[%i][%i] = 1/3 + %f + %f + %f + %f + %f = ", i, j, ij, j1, j2, i1, i2);
				*(B+(i*ROW)+j)=0.3*(ij+j1+j2+i1+i2);
                printf("%f \n", *(B+(i*ROW)+j));
			}
		}
        float *aux = A;
        A=B;
        B=aux;
	}

	printf("\nValor del array A: \n");
	for(int i=0;i<ROW*COL;++i){
		printf("%f ,",*(A+i));
	}

	printf("\nValor del array B: \n");
	for(int i=0;i<ROW*COL;++i){
		printf("%f ,",*(B+i));
	}
}
