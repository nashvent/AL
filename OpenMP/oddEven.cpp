#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
using namespace std;

void random_vector(int vrand[], int x){
    for(int i=0;i<x;i++){
        int nrand=rand()%1009+1;
        vrand[i]=nrand;
    }
}

void print_vect(int V[],int Vsize){
    for(int x=0;x<Vsize;x++){
        cout<<V[x]<<" ";
    }
    cout<<endl;
}

// ./ov #HILOS #ELEMENTOS
int main(int argc, char *argv[]){
     //srand (time(NULL));
    int thread_count=strtol(argv[1],NULL,10);
    int part;
    string size=argv[2];
    int n=atoi( size.c_str());
    part=(int)(n/(thread_count));
    int V[n];
    int i,tmp;
    random_vector(V,n);
    //print_vect(V,n);
    int phase;

    /*Read write locks*/
    clock_t tStart = clock();

    for(phase=0;phase<n;phase++){
        if(phase%2==0){
        # pragma omp parallel for num_threads(thread_count) default(none) shared(V,n) private(i,tmp) 
            for(i=1;i<n;i+=2)
                if(V[i-1]>V[i]){
                    //swap(V[i-1],V[i]);
                    tmp=V[i-1];
                    V[i-1]=V[i];
                    V[i]=V[i-1];
                }
                    
        }
            
        else{
        # pragma omp parallel for num_threads(thread_count) default(none) shared(V,n) private(i,tmp) 
            for( i=1;i<n-1;i+=2)
                if(V[i]>V[i+1]){
                    //swap(V[i],V[i+1]);
                    tmp=V[i];
                    V[i]=V[i+1];
                    V[i+1]=tmp;
                }
                    
        }
            
    }
    cout<<"oddEven1 "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
    //print_vect(V,n);
    return 0;
}