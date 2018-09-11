#include<bits/stdc++.h>
#include<mpi.h>

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

int compute_partner(int phase,int rank,int comm_sz){
    int partner;
    if(phase%2==0){
        if(rank%2!=0){
            partner=rank-1;
        }
        else{
            partner=rank+1;
        }
    }
    else{
        if(rank%2!=0){
            partner=rank+1;
        }
        else{
            partner=rank-1;
        }
    }

}

void copyArray(int A[],int B[],int size){
    for(int x=0;x<size;x++){
        A[x]=B[x];
    }
}

void keepSmallerKey(int A[],int B[],int size){
    int C[size];
    int itA=0,itB=0;
    for(int x=0;x<size;x++){
        if(A[itA]>B[itB]){
            C[x]=B[itB];
            itB++;
        }
        else{
            C[x]=A[itA];
            itA++;
        }
    }
    copyArray(A,C,size);
}


void keepLargerKey(int A[],int B[],int size){
    int C[size];
    int pos=size-1;
    int itA=pos,itB=pos;
    
    for(int x=0;x<size;x++){
        if(A[itA]<B[itB]){
            C[pos-x]=B[itB];
            itB--;
        }
        else{
            C[pos-x]=A[itA];
            itA--;
        }
    }
    copyArray(A,C,size);
}

int main(int argc,char **argv){
    int i,myRank,procs,part,ind=0;
    int tag=10;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
    
    string size=argv[1];
    int sizeI=atoi( size.c_str());
    part=(int)(sizeI/(procs));
    int V[sizeI];
    int subV[part];
    if(myRank==0){
        random_vector(V,sizeI);
        print_vect(V,sizeI);
    }
    MPI_Scatter(V, part, MPI_INT, subV,
            part, MPI_INT, 0, MPI_COMM_WORLD);

    //cout<<"Proceso "<<myRank<<": ";
    sort(&subV[0],&subV[part]);
    //print_vect(subV,part);
    int subV2[part];
    int partner;
    for(int phase=0;phase<procs;phase++){
        partner=compute_partner(phase,myRank,procs);
        if(partner!= -1 and partner<procs){
            MPI_Send(&subV[0],part,MPI_INT,partner,tag,MPI_COMM_WORLD);
            MPI_Recv(&subV2,part,MPI_INT,partner,tag,MPI_COMM_WORLD,&status);
            if(myRank<partner){
                keepSmallerKey(subV,subV2,part);
            }
            else{
                keepLargerKey(subV,subV2,part);
            }
        }
        
    }

    //cout<<"Proceso Terminado "<<myRank<<": ";
    //print_vect(subV,part);
    MPI_Send(&subV[0],part,MPI_INT,0,tag,MPI_COMM_WORLD);
    int resFinal[sizeI];
    if(myRank==0){
        
        int cont=0;
        int arrTemp[part];
        for(int x=0;x<procs;x++){
            MPI_Recv(&arrTemp,part,MPI_INT,x,tag,MPI_COMM_WORLD,&status);
            for(int k=0;k<part;k++){
                resFinal[cont]=arrTemp[k];
                cont++;
            }

        }
        cout<<"RESULT FINAL "<<endl;
        print_vect(resFinal,sizeI);
    }
    
    MPI_Finalize();
    return 0;
}

