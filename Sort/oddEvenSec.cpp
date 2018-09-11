#include <bits/stdc++.h>
#include <stdlib.h>  
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

void oddEvenSort(int a[],int n){
    int phase,i,temp;
    for(phase=0;phase<n;phase++){
        if(phase%2==0){
            for(i=1;i<n;i+=2){
                if(a[i-1]>a[i]){
                    swap(a[i-1],a[i]);
                }
            }
        }
        else{
            for(i=1;i<n-1;i+=2){
                if(a[i+1]<a[i]){
                    swap(a[i+1],a[i]);
                }
            }
        }
            
    }
}

int main(int argc, char *argv[]){
    srand (time(NULL));
    string size=argv[1];
    cout<<"OddEven "<<size<<" elementos"<<endl;
    int sizeI=atoi( size.c_str());
    int V[sizeI];
    random_vector(V,sizeI);
    print_vect(V,sizeI);
    oddEvenSort(V,sizeI);
    //sort(&V[0],&V[sizeI]);
    print_vect(V,sizeI);
    return 0;
}