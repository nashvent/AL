#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

#define N 20
#define BLOCK_DIM 10
#define TILE_WIDTH 4

using namespace std;

// 4.2

__global__
void matMultKernel(int *d_M, int *d_N, int *d_P, int Width){
  int Row = blockIdx.y*blockDim.y + threadIdx.y;
  int Col = blockIdx.x*blockDim.x + threadIdx.x;
  int k = 0;
  if(Row < Width && Col < Width){
      float Pvalue = 0;
      for(k = 0; k < Width; ++k){
          Pvalue += d_M[Row*Width + k] * d_N[k*Width+Col];
      }
      d_P[Row*Width+Col] = Pvalue;
  }
}


// 4.5
__global__
void matMultKernel_tile(int *d_M, int *d_N, int *d_P, int Width){

  __shared__ int Mds[TILE_WIDTH][TILE_WIDTH];
  __shared__ int Nds[TILE_WIDTH][TILE_WIDTH];

  int bx = blockIdx.x; int by = blockIdx.y;
  int tx = threadIdx.x; int ty = threadIdx.y;
 
  int Row = by*TILE_WIDTH + ty;
  int Col = bx*TILE_WIDTH + tx;

  float Pvalue = 0;
  int  ph,k;
  for(ph = 0; ph < Width/TILE_WIDTH; ++ph){
     Mds[ty][tx] = d_M[Row*Width+ph*TILE_WIDTH + tx];
     Nds[ty][tx] = d_N[(ph*TILE_WIDTH + ty) * Width + Col];
     __syncthreads();
     for(k = 0; k < TILE_WIDTH; ++k){
      Pvalue += Mds[ty][k] * Nds[k][tx];
     }
     __syncthreads();
  }
  d_P[Row*Width + Col] = Pvalue;
}

void imprimir_Matriz(int matrix[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            cout<<matrix[i][j]<<' ';
        }
        cout<<endl;
    }
}

int main() {
    int a[N][N], b[N][N], c[N][N];
    int *dev_a, *dev_b, *dev_c;

    int size = N * N * sizeof(int);
    srand(time(NULL));
    for(int i=0; i<N; i++)
        for (int j=0; j<N; j++){
            a[i][j] = 1;
            b[i][j] = 1;
        }

    imprimir_Matriz(a);
    cout<<endl;
    imprimir_Matriz(b);


    cudaMalloc((void**)&dev_a, size);
    cudaMalloc((void**)&dev_b, size);
    cudaMalloc((void**)&dev_c, size);
    cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);
    
    
    dim3 dimGrid(ceil(N/4.0),ceil(N/4.0),1);
    dim3 dimBlock(TILE_WIDTH,TILE_WIDTH,1);
    //matMultKernel_tile<<<dimGrid,dimBlock>>>(dev_a,dev_b,dev_c, N);     
    matMultKernel<<<dimGrid,dimBlock>>>(dev_a,dev_b,dev_c, N);

    cudaDeviceSynchronize();
    cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);
    
    cout<<endl;
    
    imprimir_Matriz(c);

    cudaFree(dev_a); cudaFree(dev_b); cudaFree(dev_c);

    return 0;
}