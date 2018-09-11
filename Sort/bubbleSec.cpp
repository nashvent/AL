#include <bits/stdc++.h>
#include <stdlib.h>  
using namespace std;

typedef vector<int> vect;

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

void bubbleSort(int a[],int n){
    int list_lenght,i,temp;
    for(list_lenght=n;list_lenght>=2;list_lenght--){
        for(i=0;i<list_lenght-1;i++){
            if(a[i]>a[i+1]){
                temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
            }
        }    
    }
}

int main(int argc, char *argv[]){
    
    string size=argv[1];
    cout<<"Bubble "<<size<<" elementos"<<endl;

    int sizeI=atoi( size.c_str());
    int V[sizeI];
    random_vector(V,sizeI);
    print_vect(V,sizeI);
    bubbleSort(V,sizeI);
    print_vect(V,sizeI);
    

    return 0;
}