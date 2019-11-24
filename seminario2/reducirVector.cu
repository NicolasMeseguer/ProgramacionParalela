#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

#define TAM 10
#define TAMBLOCK 2

__global__ void reducirVector(float *dest, float *origin, int *BLOCKS){
  if(blockIdx.x==0){
    float counter=0.0f;
    for(int i=0;i<*BLOCKS;++i){
        for(int j=0;j<TAMBLOCK;++j){
          counter+=origin[i*blockDim.x+j];
      }
    }
  *dest=counter;
  }
}

void inicializarVector(float *vector){
  for(int i=0;i<TAM;++i)
    vector[i]=(float)(rand()%100);
}

void mostrarVector(float *vector){
  for(int i=0;i<TAM;++i)
    printf("%f, ",*(vector+i));
  printf("\n");
}

int main() {
  int memsize = sizeof(float)*TAM;
  float *h_vector, *h_aux;
  h_vector = (float *) malloc(memsize);
  h_aux    = (float *) malloc(memsize);
    
  inicializarVector(h_vector);
  mostrarVector(h_vector);

  float *d_vector, *d_aux;
  int *d_block;
  cudaMalloc(&d_vector, memsize);
  cudaMalloc(&d_aux, memsize);
  cudaMalloc(&d_block, sizeof(int));

  cudaMemcpy(d_vector, h_vector, memsize, cudaMemcpyHostToDevice);

  int block = ceilf((float)TAM/TAMBLOCK);
  int thread = TAMBLOCK;
  cudaMemcpy(d_block, &block, sizeof(int), cudaMemcpyHostToDevice);
  reducirVector <<<block,thread>>> (d_aux, d_vector, d_block);

  cudaMemcpy(h_aux, d_aux, memsize, cudaMemcpyDeviceToHost);
  printf("Vector reducido, valor: %f\n", *(h_aux));
 
  free(h_vector);
  free(h_aux);
  cudaFree(d_vector);
  cudaFree(d_aux);
  return 0;
}
