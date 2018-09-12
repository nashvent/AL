#include<bits/stdc++.h>
#include<mpi.h>
#define TAM 100

using namespace std;

int main(int argc,char **argv){
    int i,myRank,procs,part,ind=0;
    int tag=10;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
    int temp=0;
    if(myRank==0){
        MPI_Send(&temp,1,MPI_INT,(myRank+1)%procs,tag,MPI_COMM_WORLD);
    }

    while(temp<TAM){
        MPI_Recv(&temp,1,MPI_INT,(myRank-1)%procs,tag,MPI_COMM_WORLD,&status);
        temp++;
        cout<<"Proceso: "<<myRank<<" estado: "<<temp<<endl;
        MPI_Send(&temp,1,MPI_INT,(myRank+1)%procs,tag,MPI_COMM_WORLD);
     
    }
    MPI_Finalize();

    return 0;
}