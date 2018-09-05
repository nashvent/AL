#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;
const int MAX_STRING=100;
int main(void ){
    char greeting[MAX_STRING];
    int comm_sz;
    int my_rank;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    cout<<"procesooo "<<my_rank<<endl;
    if(my_rank!=0){
        sprintf(greeting, "Greetings from process %d of %d!",my_rank,comm_sz);
        MPI_Send(greeting,strlen(greeting)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);  
    }
    else{
        printf("Greetings of %d and %d",my_rank,comm_sz);
        for(int x=1;x<comm_sz;x++){
            MPI_Recv(greeting,MAX_STRING,MPI_CHAR,x,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            cout<<greeting<<endl;
        }

    }
    MPI_Finalize();
    return 0;
}