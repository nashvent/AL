#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
using namespace std;
int thread_count;

void random_vector(int vrand[], int x){
    for(int i=0;i<x;i++){
        int nrand=rand()%17+1;
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

int multiplicarArrArr(int V1[],int V2[],int Vsize){
    int res=0;
    for(int x=0;x<Vsize;x++){
        res=res+(V1[x]*V2[x]);
    }
    return res;
}



void *sum(void * p){
    return NULL;
}

int main(int argc, char* argv[]){
    
    
    
    
    long thread;
    pthread_t*thread_handles;
    thread_count=strtol(argv[1],NULL,10);
    thread_handles= (pthread_t*) malloc(thread_count * sizeof(pthread_t));    
    
    srand (time(NULL));
  
    int sizeVector=atoi(argv[1]);
    int vect[sizeVector];
    int vect2[sizeVector];
    int vectR[sizeVector];

    int **matrix;
    matrix = new int *[sizeVector];
    for(int i = 0; i <sizeVector; i++){
        matrix[i] = new int[sizeVector];
        
    }
    random_matriz(matrix,sizeVector);
    cout<<"Matriz"<<endl;
    print_matriz(matrix,sizeVector);


    random_vector(vect,sizeVector);
    cout<<"Vector: ";
    print_vect(vect,sizeVector);
    cout<<endl;



    /*Read write locks*/
    clock_t tStart = clock();
    for(thread=0;thread<thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL,
        sum,NULL);
    }

    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    cout<<"Tiempo RWL "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
    return 0;
}