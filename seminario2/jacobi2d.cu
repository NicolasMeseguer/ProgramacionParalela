#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N 8
#define TAMBLOCK 2

#define LIMIT 10

__global__ void jacobi2d(float *A, float *B){
    int ind = (((blockIdx.y*blockDim.y+threadIdx.y)+1)*N)+((blockIdx.x*blockDim.x+threadIdx.x)+1);
		*(B+ind)=*(A+ind)+*(A+ind+1)+*(A+ind-1)+*(A+ind+N)+*(A+ind-N);
}

int main(){
  int memsize=N*N*sizeof(float);
	float *A = (float *)malloc(memsize); //Matriz creada
	float *B = (float *)malloc(memsize); //2da Matriz, que usaremos para calcular valores.
  float *d_a, *d_b; 

  cudaMalloc(&d_a, memsize);
  cudaMalloc(&d_b, memsize);
	//Primero vamos a inicializar la matriz A, dandole valores
	for(int i=0; i<N; ++i)
		for(int j=0;j<N;++j){
			if((i==0||i==N)&&(j==0||j==N))
				*(A+(i*N)+j)=150.0f;
			else
				*(A+(i*N)+j)=(float) (rand()%10);
	}
  
  cudaMemcpy(d_a, A, memsize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, B, memsize, cudaMemcpyHostToDevice);

  dim3 block((N-2)/TAMBLOCK, (N-2)/TAMBLOCK);
  dim3 thread(TAMBLOCK, TAMBLOCK);

	//Forma 2 Jacobi, extremos = 150 y solo sumo por el interior.
  for(int k=0; k<LIMIT;++k){
		
    jacobi2d <<<block, thread>>> (d_a, d_b);

    float *aux=d_a;
		d_a=d_b;
		d_b=aux;
	}

  cudaMemcpy(A, d_a, memsize, cudaMemcpyDeviceToHost);  

	printf("\nValor del array A: \n");
	for(int i=0;i<N*N;++i){
		printf("%f ,",*(A+i));
		if(i!=0 && (i+1)%8==0)
			printf("\n");
	}
	
	//Este es el valor la matriz que contiene los valores anteriores.
	/*printf("\nValor del array B: \n");
	for(int i=0;i<ROW*COL;++i){
		printf("%f ,",*(B+i));
		if(i!=0 && (i+1)%5==0)
			printf("\n");
	}*/
}
