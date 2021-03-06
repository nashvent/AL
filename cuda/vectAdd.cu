#include <stdio.h>

__global__
void vecAddKernel(float *A, float *B, float *C, int n){
  int i = blockDim.x*blockIdx.x + threadIdx.x;
  if(i<n) C[i] = A[i] + B[i];
}

void vecAdd(float* A, float* B, float* C, int n){
  int size = n*sizeof(float);
  float *d_A, *d_B, *d_C;
  cudaMalloc((void **) &d_A, size);
  cudaMemcpy(d_A,A,size,cudaMemcpyHostToDevice);
  cudaMalloc((void **) &d_B, size);
  cudaMemcpy(d_B,B,size,cudaMemcpyHostToDevice);
  cudaMalloc((void **) &d_C, size);

  vecAddKernel<<<ceil(n/256.0), 256>>>(d_A,d_B,d_C,n);

  cudaMemcpy(C,d_C,size,cudaMemcpyDeviceToHost);

  cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
}

void datosRandom(float *array,int n){
  for(int i = 0; i < n; i++){
    array[i] = 1;
  }
}

void printVector(float *array,int n){
  for(int i = 0; i < n; i++){
    printf("%f ", array[i]);
  }
  printf("\n");
}

int main(){
  int n;
  float *h_A,*h_B,*h_C;
  scanf("%d", &n);
  h_A = (float*) malloc(n*sizeof(float));
  h_B = (float*) malloc(n*sizeof(float));
  h_C = (float*) malloc(n*sizeof(float));
  datosRandom(h_A,n);
  datosRandom(h_B,n);
  vecAdd(h_A,h_B,h_C,n);
  printVector(h_C,n);

  return 0;
}


