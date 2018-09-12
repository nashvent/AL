#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;


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

int main(int argc,char **argv){
    int i,myRank,procs,part,ind=0;
    int tag=10;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
    
    int sizeVector=procs-1;

    int vect[sizeVector];
    int vect2[sizeVector];
    int vectR[sizeVector];
    

    if(myRank==0){

        random_vector(vect,sizeVector);
        cout<<"Vector: ";
        print_vect(vect,sizeVector);
        cout<<endl;
    }
    MPI_Bcast(&vect,sizeVector,MPI_INT,0,MPI_COMM_WORLD);
    
    if(myRank==0){
        int **matrix;
        matrix = new int *[sizeVector];
        for(int i = 0; i <sizeVector; i++){
            matrix[i] = new int[sizeVector];
            
        }
        random_matriz(matrix,sizeVector);
        cout<<"Matriz"<<endl;
        print_matriz(matrix,sizeVector);
        for(i=1;i<procs;i++){
            MPI_Send(&matrix[i-1][0],sizeVector,MPI_INT,i,tag,MPI_COMM_WORLD);
        }
        for(i=1;i<procs;i++){
            int result;
            MPI_Recv(&result,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
            vectR[i-1]=result;
        }

    }
    else{
        MPI_Recv(&vect2,sizeVector,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
        cout<<"Parte q me toca proc:"<<myRank<<endl;
        int res=multiplicarArrArr(vect,vect2,sizeVector);
        MPI_Send(&res,1,MPI_INT,0,tag,MPI_COMM_WORLD);
    }

    if(myRank==0){
        cout<<"Reusltado "<<endl;
        print_vect(vectR,sizeVector);
    }

    MPI_Finalize();
    return 0;
}