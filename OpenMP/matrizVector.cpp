#include <stdio.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <omp.h>
using namespace std;

void random_vector(int vrand[], int x){
    for(int i=0;i<x;i++){
        int nrand=1;
        vrand[i]=nrand;
    }
}

void random_matriz(int** vrand, int x){
    for(int i = 0; i <x; i++){
        random_vector(vrand[i],x);
    }        
}

void print_vect(int V[],int Vsize){
    for(int x=0;x<Vsize;x++){
        cout<<V[x]<<" ";
    }
    cout<<endl;
}

void print_matriz(int** V,int Vsize){
    for(int x=0;x<Vsize;x++){
        for(int i=0;i<Vsize;i++){
            cout<<V[x][i]<<" ";
        }       
        cout<<endl;
    }
    cout<<endl;
}


int main(int argc,char* argv[]){
    int thread_count=strtol(argv[1],NULL,10);
    string sz=argv[2];
    int size=atoi( sz.c_str());;
    int **matrix;
    int vect[size],vect2[size];
    random_vector(vect,size);
    matrix = new int *[size];
    for(int i = 0; i <size; i++){
        matrix[i] = new int[size];        
    }
    random_matriz(matrix,size);

    int i,j;
    clock_t tStart = clock();

    # pragma omp parallel for num_threads(thread_count) default(none) private(i,j) shared(matrix,vect,vect2,size)
    for(i=0;i<size;i++){
        vect2[i]=0.0;
        for(j=0;j<size;j++){
            vect2[i]+=matrix[i][j]*vect[j];
        }
    }

    cout<<"matriz "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
   
    return 0;
}

