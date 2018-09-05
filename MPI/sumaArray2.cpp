#include<bits/stdc++.h>
#include<mpi.h>
#define TAM 12

using namespace std;

int main(int argc,char **argv){
    int i,myRank,procs,part,ind=0;
    int vet[TAM];
    int tag=10;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
    part=(int)(TAM/(procs-1));
    int suma=0;
    if(myRank==0){
        for(i=0;i<TAM;i++){
            vet[i]=i;
        }
        for(i=1;i<procs;i++){
            MPI_Send(&vet[ind],part,MPI_INT,i,tag,MPI_COMM_WORLD);
            ind=ind+part;
        }
        
        for(i=1;i<procs;i++){
            int sumaParc;
            MPI_Recv(&sumaParc,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
            suma+=sumaParc;
            cout<<"Proceso 0 recive "<<sumaParc<<endl;
        }
        cout<<"SUma total "<<suma<<endl;
    }
    else{
        MPI_Recv(vet,part,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
        cout<<"Proc "<<myRank<<" recibe: [";
        for(i=0;i<part;i++){
            suma+=vet[i];
            cout<<vet[i]<<",";
        }
        MPI_Send(&suma,1,MPI_INT,0,tag,MPI_COMM_WORLD);
        cout<<"] FINAL de proc"<<myRank<<" suma: "<<suma<<endl;

    }
    MPI_Finalize();

    return 0;
}